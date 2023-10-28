#ifndef UTILS_HPP
#define UTILS_HPP

#ifndef DEBUG
#define DEBUG 1
#endif

//CONFIG
# define MAX_CLIENTS 10
# define BUFF_SIZE 1024
# define EOL "\n"
# define USERLEN 10

//COLORS
# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

//ERRORS
# define SUCCESS 0
# define FAILURE 1
# define BREAK 2
# define QUIT 3

//INCLUDES
# include <iostream>
# include <string>
# include <vector>
# include <map>
# include <sstream>
# include <sys/types.h>
# include <sys/socket.h>
# include <netdb.h>
# include <poll.h>

void 	print(std::string type, int client_socket, char *message);
void	send_message_client(int const client_fd, std::string client_buffer);

#endif