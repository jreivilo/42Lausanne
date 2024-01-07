#include "../../includes/server.hpp"

Server::Server(std::string port, std::string password, struct tm *time)
{
	_port = port;
	_password = password;
	_time = time;

	_server_socket = 0;

	_server_addrinfo_ptr = NULL;
	_server_addrinfo.ai_family = AF_UNSPEC;
	_server_addrinfo.ai_socktype = SOCK_STREAM;
	_server_addrinfo.ai_flags = AI_PASSIVE;
}

Server::~Server(void)
{
}

// GETTERS
Client *Server::get_client(int client_fd)
{
	std::map<const int, Client>::iterator it = _clients.find(client_fd);
	if (it == _clients.end())
	{
		std::cout << RED << "[Server] Error: client not found" << RESET << std::endl;
		return (NULL);
	}
	else
		return (&it->second);
}

Client *Server::get_client(std::string nickname)
{
	std::map<const int, Client>::iterator it = _clients.begin();
	while (it != _clients.end())
	{
		if (it->second.get_nick() == nickname)
			return (&it->second);
		it++;
	}
	std::cout << RED << "[Server] Error: client not found" << RESET << std::endl;
	return (NULL);
}

Channel *Server::get_channel(std::string channel_name)
{
	std::map<const std::string, Channel>::iterator it = _channels.find(channel_name);
	if (it == _channels.end())
	{
		std::cout << RED << "[Server] Error: channel not found" << RESET << std::endl;
		return (NULL);
	}
	else
		return (&it->second);
}

// PARSING
int Server::build_server()
{
	int rv;
	struct addrinfo hints;
	memset(&hints, 0, sizeof hints);
	// Initialize the hints structure
	hints.ai_family = AF_UNSPEC;	 // Use AF_INET6 to force IPv6, or AF_INET for IPv4
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
	hints.ai_flags = AI_PASSIVE;	 // Fill in my IP for me

	if ((rv = getaddrinfo(NULL, _port.c_str(), &hints, &_server_addrinfo_ptr)) != 0)
	{
		std::cerr << RED << "[Server] Error: getaddrinfo failed" << gai_strerror(rv) << RESET << std::endl;
		return (FAILURE);
	}
	else
		std::cout << GREEN << "[Server] getaddrinfo done" << RESET << std::endl;

	_server_socket = socket(_server_addrinfo_ptr->ai_family, _server_addrinfo_ptr->ai_socktype, _server_addrinfo_ptr->ai_protocol);
	if (_server_socket == -1)
	{
		std::cerr << RED << "[Server] Error: socket creation failed" << RESET << std::endl;
		return (FAILURE);
	}
	else
		std::cout << GREEN << "[Server] Socket created" << RESET << std::endl;
	int yes = 1;
	if (setsockopt(_server_socket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
	{
		std::cerr << RED << "[Server] Error: setsockopt failed" << RESET << std::endl;
		return (FAILURE);
	}
	else
		std::cout << GREEN << "[Server] setsockopt done" << RESET << std::endl;
	if (bind(_server_socket, _server_addrinfo_ptr->ai_addr, _server_addrinfo_ptr->ai_addrlen) == -1)
	{
		std::cerr << RED << "[Server] Error: bind failed" << RESET << std::endl;
		return (FAILURE);
	}
	else
		std::cout << GREEN << "[Server] bind done" << RESET << std::endl;
	fcntl(_server_socket, F_SETFL, O_NONBLOCK);
	if (listen(_server_socket, MAX_CLIENTS) == -1)
	{
		std::cerr << RED << "[Server] Error: listen failed" << RESET << std::endl;
		return (FAILURE);
	}
	else
		std::cout << GREEN << "[Server] listen done" << RESET << std::endl;
	freeaddrinfo(_server_addrinfo_ptr);
	return (SUCCESS);
}

int Server::run_server()
{
	// Initialize pollfds
	std::vector<pollfd> pollfds;
	pollfd server_pollfd;
	server_pollfd.fd = _server_socket;
	server_pollfd.events = POLLIN;
	pollfds.push_back(server_pollfd);

	// init clients
	Client *client_default = new Client(0);
	client_default->set_nick("sudo");
	client_default->set_user("sudosu");
	client_default->set_realname("sudo su");

	// Init channels
	Channel *channel_default = new Channel("#default");
	channel_default->set_key("plouf");
	channel_default->set_topic("default topic");
	channel_default->set_mode("nt");
	channel_default->add_operator("sudo");
	channel_default->set_max_users(10);
	_channels.insert(std::pair<const std::string, Channel>("#default", *channel_default));

	// Loop
	while (kill_serv == false)
	{
		if (poll(pollfds.data(), pollfds.size(), -1) == -1)
		{
			std::cerr << RED << "[Server] Error: poll failed" << RESET << std::endl;
			return (FAILURE);
		}

		// Check for new connection
		std::vector<pollfd> new_pollfds;
		std::vector<pollfd>::iterator it = pollfds.begin();
		while (it != pollfds.end())
		{
			if (it->revents & POLLIN) // => If the fd is ready to read
			{
				if (it->fd == _server_socket)
				{
					if (create_client(_server_socket, new_pollfds, pollfds.size()) == FAILURE)
						continue;
				}
				else
				{
					int ret = read_client(pollfds, it);
					if (ret == FAILURE)
						continue;
					if (ret == QUIT)
					{
						delete_client(pollfds, it);
						continue;
					}
				}
			}
			else if (it->revents & POLLOUT) // => If the fd is ready to write
			{
				if (write_client(pollfds, it) == BREAK)
					break;
			}
			else if (it->revents & POLLERR) // => If the fd is closed
			{
				if (error_client(pollfds, it) == BREAK)
					break;
				else
					return (FAILURE);
			}
			it++;
		}
		// Add new clients to pollfds
		for (size_t i = 0; i < new_pollfds.size(); i++)
			pollfds.push_back(new_pollfds[i]);
	}
	return (SUCCESS);
}

int Server::create_client(int client_socket, std::vector<pollfd> &new_pollfds, int nb_pollfds)
{
	int client_fd = accept(client_socket, NULL, NULL);
	if (client_fd == -1)
	{
		std::cerr << RED << "[Server] Error: accept failed" << RESET << std::endl;
		return (FAILURE);
	}
	if (nb_pollfds >= MAX_CLIENTS)
	{
		std::cout << RED << "[Server] Error: max clients reached" << RESET << std::endl;
		send(client_fd, "[Server] ERROR: max clients reached", 26, 0);
		close(client_fd);
		return (FAILURE);
	}
	else
	{
		// Add new client to new_pollfds
		pollfd client_pollfd;
		client_pollfd.fd = client_fd;
		client_pollfd.events = POLLIN | POLLOUT; // => POLLIN = ready to read, POLLOUT = ready to write
		new_pollfds.push_back(client_pollfd);

		// Create new client
		Client new_client(client_fd);
		_clients.insert(std::pair<const int, Client>(client_fd, new_client));
		std::cout << PURPLE << "[Server] New client created on fd " << client_fd << RESET << std::endl;
	}
	return (SUCCESS);
}

int Server::read_client(std::vector<pollfd> &pollfds, std::vector<pollfd>::iterator it)
{
    Client *client;
    client = get_client(it->fd);

    char buffer[BUFF_SIZE];
    int ret;

    memset(buffer, 0, BUFF_SIZE); // => Fill buffer with 0
    ret = recv(it->fd, buffer, BUFF_SIZE, 0);
    if (ret == -1)
    {
        std::cerr << RED << "[Server] Error: recv failed" << RESET << std::endl;
        delete_client(pollfds, it);
        return (FAILURE);
    }
    else if (ret == 0)
    {
        std::cout << PURPLE << "[Server] Deconnection on fd " << it->fd << RESET << std::endl;
        delete_client(pollfds, it);
        return (FAILURE);
    }
    else
    {
        print("[Server] Partial message from client ", it->fd, buffer);
        
        // Append the new data to the read buffer
        client->append_read_buffer(buffer, ret);

        // Check if the message/command is complete
        if (client->get_read_buffer().find(EOL) != std::string::npos)
        {
            try
            {
				int ret;
                ret = parse_message(it, client->get_read_buffer());
				if (ret == QUIT)
					return (QUIT);
                client->clear_read_buffer();
            }
            catch (const std::exception &e)
            {
                std::cerr << RED << "[SERVER] Exception: " << e.what() << RESET << '\n';
                if (client->get_is_registrered() == true)
                    client->set_is_connected(false);
                return (BREAK);
            }
        }
    }
    return (SUCCESS);
}

int Server::write_client(std::vector<struct pollfd> &pollfds, std::vector<struct pollfd>::iterator it)
{
	Client *client;
	client = get_client(it->fd);
	if (client == NULL)
		std::cerr << RED << "[Server] Error: client not found" << RESET << std::endl;
	else
	{
		send_message_client(it->fd, client->get_write_buffer());
		client->clear_write_buffer();
		if (client->get_is_connected() == false)
		{
			delete_client(pollfds, it);
			return (BREAK);
		}
	}
	return (SUCCESS);
}

int Server::error_client(std::vector<struct pollfd> &pollfds, std::vector<struct pollfd>::iterator it)
{
	if (it->fd == _server_socket)
	{
		std::cerr << RED << "[Server] Error: server socket goes brrrr" << RESET << std::endl;
		return (FAILURE);
	}
	else
	{
		delete_client(pollfds, it);
		return (BREAK);
	}
}

void Server::delete_client(std::vector<struct pollfd> &pollfds, std::vector<struct pollfd>::iterator it)
{
	std::cout << PURPLE << "[Server] Deconnection on fd " << it->fd << RESET << std::endl;
	close(it->fd);
	_clients.erase(it->fd);
	pollfds.erase(it);
	std::cout << PURPLE << "[Server] Client deleted on fd " << it->fd << RESET << std::endl;
	return;
}
