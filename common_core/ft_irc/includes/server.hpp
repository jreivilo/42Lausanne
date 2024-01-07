#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <time.h>
#include <csignal>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <poll.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <algorithm>
#include <fcntl.h>


#include "utils.hpp"
#include "client.hpp"
#include "channel.hpp"


extern bool kill_serv;

class Server
{
	public:
		Server(std::string port, std::string password, struct tm * time);
		
		~Server(void);

		Client*		get_client(int client_fd);
		Client*		get_client(std::string nickname);
		Channel* 	get_channel(std::string channel_name);

		int		build_server(void);
		int		run_server(void);

		int		create_client(int client_socket, std::vector<struct pollfd> & new_pollfds, int nb_pollfds);
		int		read_client(std::vector<struct pollfd> & pollfds, std::vector<struct pollfd>::iterator it);
		int 	write_client(std::vector<struct pollfd> & pollfds, std::vector<struct pollfd>::iterator it);
		int		error_client(std::vector<struct pollfd> & pollfds, std::vector<struct pollfd>::iterator it);
		void	delete_client(std::vector<struct pollfd> & pollfds, std::vector<struct pollfd>::iterator it);


		//PARSING
		int	parse_message(std::vector<struct pollfd>::iterator it, std::string message);
		void	init_user(std::vector<struct pollfd>::iterator it, std::string command, std::string params);
		void	exec_command(std::vector<struct pollfd>::iterator it, std::string command, std::string params);
		//COMMANDS
		//PASS 		
		void 	pass(std::vector<struct pollfd>::iterator it, const std::string& params);
		//NICK
		void 	nick(std::vector<struct pollfd>::iterator it, const std::string& params);
		bool 	is_nickname_used(const std::string& nickname);
		//USER
		void 	user(std::vector<struct pollfd>::iterator it, const std::string& params);
		bool 	is_user_used(const std::string& user);
		//JOIN
		void	join(std::vector<struct pollfd>::iterator it, const std::string& params);
		//PRIVATE MESSAGE
		void	privmsg(std::vector<struct pollfd>::iterator it, const std::string& params);
		bool	is_channel(std::string channel_name);
		bool	is_nick(std::string nickname);
		void	deliver_to_channel(std::vector<struct pollfd>::iterator it, std::string channel_name, std::string message);
		void	deliver_to_client(std::vector<struct pollfd>::iterator it, std::string nickname, std::string message);
		//KICK
		void	kick(std::vector<struct pollfd>::iterator it, const std::string& params);

		//INVITE
		void	invite(std::vector<struct pollfd>::iterator it, const std::string& params);

		//TOPIC
		void	topic(std::vector<struct pollfd>::iterator it, const std::string& params);

		//MODE -i -t -k -o -l
		void	mode(std::vector<struct pollfd>::iterator it, const std::string& params);



	private:
		Server(void);
		Server(Server const & src);
		// Server & operator=(Server const & rhs);

		std::string			_port;
		std::string			_password;
		struct tm *			_time;

		int					_server_socket;
		struct addrinfo		_server_addrinfo;
		struct addrinfo *	_server_addrinfo_ptr;

		std::map<const int, Client>		_clients;
		std::map<const std::string, Channel>	_channels;
};





#endif // SERVER_HPP
