#include "../../includes/utils.hpp"

void print(std::string type, int client_socket, char *message)
{
	if (message)
		std::cout << std::endl
				  << type << client_socket << " << "
				  << BLUE << message << RESET;
}

void send_message_client(int const client_fd, std::string client_buffer)
{
	std::istringstream buf(client_buffer);
	std::string reply;

	send(client_fd, client_buffer.c_str(), client_buffer.size(), 0);
	while (getline(buf, reply))
	{
		std::cout << "[Server] Message sent to client " << client_fd << " >> " << CYAN << reply << RESET << std::endl;
	}
}
