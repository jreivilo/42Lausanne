#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "vehicule.hpp"

#define TRUE 1
#define FALSE 0
#define ERROR -1

int parse_msg(char* buffer, Vehicule& vehicule);