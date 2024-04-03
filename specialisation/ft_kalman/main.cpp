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

#define LOCALHOST "127.0.0.1"


int check_args(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: " << argv[0] << " -h <port>" << std::endl;
		return ERROR;
	}

	std::string option = argv[1];
	std::string port = argv[2];

	if (option != "-h") {
		std::cerr << "Invalid option: " << option << std::endl;
		return ERROR;
	}

	if (port.find_first_not_of("0123456789") != std::string::npos) {
		std::cerr << "Invalid port: " << port << std::endl;
		return ERROR;
	}

	return 0;
}

int init_udp_connection(int& client, struct sockaddr_in& server, std::string port) {
	// init client
	client = socket(AF_INET, SOCK_DGRAM, 0); //DGRAM for UDP and STREAM for TCP
	//https://www.avast.com/fr-fr/c-tcp-vs-udp-difference#:~:text=TCP%20garantit%20une%20transmission%20sans,et%20au%20streaming%20en%20direct.
	if (client < 0) {
		std::cerr << "Error: socket" << std::endl;
		return ERROR;
	}

	// init struct sockaddr_in
	memset(&server, 0, sizeof(server)); // init struct with 0
	server.sin_family = AF_INET;
	server.sin_port = htons(std::stoi(port));
	server.sin_addr.s_addr = inet_addr(LOCALHOST);

	return 0;
}

int send_handshake(int client, struct sockaddr_in server) {
	//send READY to server as specified in the help message
	if (sendto(client, "READY", strlen("READY"), 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
		std::cerr << "Error: sendto" << std::endl;
		return ERROR;
	}
	std::cout << "READY sent to server" << std::endl;

	return 0;
}

void removeBracketsAndContents(std::string& str) {
    size_t start = 0;
    while ((start = str.find("[", start)) != std::string::npos) {
        size_t end = str.find("]", start);
        if (end != std::string::npos) {
            // Erase including brackets
            str.erase(start, end - start + 1);
        } else {
            // No closing bracket found, break to avoid infinite loop
            break;
        }
    }
	return;
}

void get_true_position(std::string msg, Vehicule& vehicule) {
	vehicule.true_position.clear();
	for (int i = 0; i < 3; i++) {
		msg = msg.substr(msg.find("\n") + 1);
		std::string true_position = msg.substr(0, msg.find("\n"));
		vehicule.true_position.push_back(std::stod(true_position));
	}
}

void get_speed(std::string msg, Vehicule& vehicule) {
	msg = msg.substr(msg.find("\n") + 1);
	std::string speed = msg.substr(0, msg.find("\n"));
	std::cout << "Speed: " << speed << std::endl;
	vehicule.speed = std::stod(speed);
}

void get_acceleration(std::string msg, Vehicule& vehicule) {
	vehicule.acceleration.clear();
	for (int i = 0; i < 3; i++) {
		msg = msg.substr(msg.find("\n") + 1);
		std::string acceleration = msg.substr(0, msg.find("\n"));
		vehicule.acceleration.push_back(std::stod(acceleration));
	}
}

void get_direction(std::string msg, Vehicule& vehicule) {
	vehicule.direction.clear();
	for (int i = 0; i < 3; i++) {
		msg = msg.substr(msg.find("\n") + 1);
		std::string direction = msg.substr(0, msg.find("\n"));
		vehicule.direction.push_back(std::stod(direction));
	}
}

void print_vehicule(Vehicule vehicule) {
	std::cout << "True position: ";
	for (int i = 0; i < vehicule.true_position.size(); i++) {
		std::cout << vehicule.true_position[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Speed: " << vehicule.speed << std::endl;

	std::cout << "Acceleration: ";
	for (int i = 0; i < vehicule.acceleration.size(); i++) {
		std::cout << vehicule.acceleration[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Direction: ";
	for (int i = 0; i < vehicule.direction.size(); i++) {
		std::cout << vehicule.direction[i] << " ";
	}
	std::cout << std::endl;
}

int parse_msg(char* buffer, Vehicule& vehicule) {
	std::string msg(buffer);
	std::string first_token = msg.substr(0, msg.find("\n"));
	removeBracketsAndContents(first_token);

	std::cout << "Msg: " << msg << std::endl;
	std::cout << "First token: \"" << first_token << "\""<< std::endl;
	std::cout << "COucou1" << std::endl;

	// std::cout << "Message: " << msg << std::endl;
	if (first_token == "Trajectory Generation. . .")
		return 1;
	if (first_token == "Trajectory Generated!")
		return 1;
	if (first_token == "MSG_START")
		return 1;
	if (first_token == "TRUE POSITION")
	{
		get_true_position(msg, vehicule);
		return 1;
	}
	if (first_token == "SPEED") 
	{
		get_speed(msg, vehicule);
		return 1;
	}
	if (first_token == "ACCELERATION")
	{
		get_acceleration(msg, vehicule);
		return 1;
	}
	if (first_token == "DIRECTION")
	{
		get_direction(msg, vehicule);
		return 1;
	}
	if (first_token == "GPS_POSITION")
	{
		std::cout << "Get gps position" << std::endl;
		return 1;
	}
	if (first_token == "MSG_END")
		return 1;
	
	std::cout << "Message not recognized" << std::endl;
	std::cout << "Message: " << msg << std::endl;
	return 0;
}

int main(int argc, char* argv[]) {

	if (check_args(argc, argv) == ERROR) {
		return 1;
	}
	std::string port = argv[2];

	// init udp connection
	int client;
	struct sockaddr_in server;
	if (init_udp_connection(client, server, port) == ERROR) {
		return 1;
	}

	if (send_handshake(client, server) == ERROR) {
		return 1;
	}

	// receive message from server
	Vehicule vehicule;
	for(int i = 0; i < 8; i++) {
		char buffer[1024];
		memset(buffer, 0, sizeof(buffer)); // init buffer with 0
		if (recvfrom(client, buffer, sizeof(buffer), 0, NULL, NULL) < 0) {
			std::cerr << "Error: recvfrom" << std::endl;
			return 1;
		}
		else {
			// std::cout << "Message from server: " << buffer << std::endl;
		}
		parse_msg(buffer, vehicule);
	}
	print_vehicule(vehicule);

	// print coucou
	std::cout << "Coucou" << std::endl;

	return 0;
}