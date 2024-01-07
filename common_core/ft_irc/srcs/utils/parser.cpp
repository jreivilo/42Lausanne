#include "../../includes/server.hpp"
#include <sstream>
#include <vector>

int Server::parse_message(std::vector<struct pollfd>::iterator it, std::string message)
{
	std::string command;
	std::string params;
	std::istringstream msgStream(message);

	Client *cli = get_client(it->fd);

	std::string line;
	while (std::getline(msgStream, line, '\n')) // Assuming commands are separated by '\n'
	{
		std::istringstream buf(line);

		// Split the message into command and params
		std::getline(buf, command, ' ');

		std::streamsize available = buf.rdbuf()->in_avail();

		if (command[command.size() - 1] == '\r')
		{
			command.erase(command.size() - 1);
		}

		if (available > 0)
		{
			std::getline(buf, params);
			if (params[params.size() - 1] == '\r')
				params.erase(params.size() - 1);
		}

		if (DEBUG)
		{
			std::cout << "[Server] Command: " << command << std::endl;
			std::cout << "[Server] Params: " << params << std::endl;
		}

		// Your existing logic here
		if (command == "QUIT")
		{
			return (QUIT);
		}
		if ((command == "PASS") && cli->get_is_authorized() == false)
		{
			pass(it, params);
		}
		if (cli->get_is_authorized() == false)
			continue;

		if (cli->get_is_registrered() == false)
		{
			if (DEBUG)
				std::cout << "[Server] Client is not registered" << std::endl;
			init_user(it, command, params);
			if (cli->get_is_registrered() == true)
			{
				std::string reply = "001 RPL_WELCOME :Welcome to the Internet Relay Network " + cli->get_nick();
				cli->set_write_buffer(reply);
			}
		}
		else
		{
			if (DEBUG)
				std::cout << "[Server] Client is registered" << std::endl;
			exec_command(it, command, params);
		}
	}
	return (SUCCESS);
}

void Server::init_user(std::vector<struct pollfd>::iterator it, std::string command, std::string params)
{
	if (command == "NICK")
	{
		nick(it, params);
	}
	if (command == "USER")
	{
		user(it, params);
	}
	// If both nickname and username are set, set is_registered to true
	if (get_client(it->fd)->get_is_registrered() == true)
	{
		get_client(it->fd)->set_is_connected(true);
	}
}

void Server::exec_command(std::vector<struct pollfd>::iterator it, std::string command, std::string params)
{
	if (command == "NICK")
	{
		nick(it, params);
	}
	else if (command == "USER")
	{
		user(it, params);
	}
	else if (command == "JOIN")
	{
		join(it, params);
	}
	else if (command == "PRIVMSG")
	{
		privmsg(it, params);
	}
	else if (command == "KICK")
	{
		kick(it, params);
	}
	else if (command == "TOPIC")
	{
		topic(it, params);
	}
	else if (command == "INVITE")
	{
		invite(it, params);
	}
	else if (command == "MODE")
	{
		mode(it, params);
	}
	else
	{
		Client *cli = get_client(it->fd);
		std::string reply = "421 ERR_UNKNOWNCOMMAND :Unknown command";
		cli->set_write_buffer(reply);
	}
}
