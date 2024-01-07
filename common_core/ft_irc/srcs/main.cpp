#include "../includes/server.hpp"

bool kill_serv = false;

static void signal_handler(int signal)
{
	(void)signal;
	kill_serv = true;
}

int check_arguments(std::string port, std::string password)
{
	// check port
	if (atoi(port.c_str()) < 1024 || atoi(port.c_str()) > 65535)
	{
		std::cout << RED << "Port must be between 1024 and 65535" << RESET << std::endl;
		return (FAILURE);
	}
	if (port.find_first_of("abcdefghijklmnopqrstuvwxyz") != std::string::npos)
	{
		std::cout << RED << "Port must be a number" << RESET << std::endl;
		return (FAILURE);
	}
	// check password
	if (password.size() < 1 || password.size() > 8)
	{
		std::cout << RED << "Password must be between 1 and 8 characters" << RESET << std::endl;
		return (FAILURE);
	}
	return (SUCCESS);
}

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		// Time
		time_t time_info;
		struct tm *tm_info;
		time(&time_info);				 // set time_info to current time
		tm_info = localtime(&time_info); // set tm_info to local time

		if (check_arguments(argv[1], argv[2]) == FAILURE)
			return (FAILURE);

		signal(SIGINT, signal_handler);
		Server server(argv[1], argv[2], tm_info); // argv[1] = port and argv[2] = password
		try
		{
			if (server.build_server())
				return (FAILURE);
			if (server.run_server())
				return (FAILURE);
		}
		catch (const std::exception &e)
		{
			std::cerr << RED << "Exception: " << e.what() << RESET << '\n';
			return (FAILURE);
		}
	}
	else
	{
		std::cout << RED << "./ircserv <port> <password>" << RESET << std::endl;
		return (FAILURE);
	}
}
