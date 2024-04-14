#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>



// #include "../includes/vehicule.hpp"
#include "../includes/parsing.hpp"
#include "../includes/utils.hpp"
#include "../includes/rotation.hpp"
#include "../includes/matrix.hpp"
#include "../includes/defines.hpp"




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


void get_info(Vehicule& vehicule, int client, struct sockaddr_in server) {
	char buffer[1024];
	for (int i = 0; i < 8; i++) {
		memset(buffer, 0, sizeof(buffer)); // init buffer with 0
		if (recvfrom(client, buffer, sizeof(buffer), 0, NULL, NULL) < 0) {
			std::cerr << "Error: recvfrom" << std::endl;
			return;
		}
		else {
			if (parse_msg(buffer, vehicule) == -1)
			{
				print_vehicule(vehicule);
				return;
			}
		}
	}
}

void calculate_position(Vehicule& vehicule) {
	std::vector<double> r_speed = { vehicule.speed[0], vehicule.speed[1], vehicule.speed[2] };
	r_speed = rotateVector(r_speed, vehicule.direction[0], vehicule.direction[1], vehicule.direction[2]);

	std::vector<double> r_acceleration = { vehicule.acceleration[0], vehicule.acceleration[1], vehicule.acceleration[2] };
	r_acceleration = rotateVector(r_acceleration, vehicule.direction[0], vehicule.direction[1], vehicule.direction[2]);

	//update position
	vehicule.guessed_position[0] += r_speed[0] * TIME_STEP + 0.5 * vehicule.acceleration[0] * TIME_STEP * TIME_STEP;
	vehicule.guessed_position[1] += r_speed[1] * TIME_STEP + 0.5 * vehicule.acceleration[1] * TIME_STEP * TIME_STEP;
	vehicule.guessed_position[2] += r_speed[2] * TIME_STEP + 0.5 * vehicule.acceleration[2] * TIME_STEP * TIME_STEP;

	//update speed
	vehicule.speed[0] += r_acceleration[0] * TIME_STEP;
	vehicule.speed[1] += r_acceleration[1] * TIME_STEP;
	vehicule.speed[2] += r_acceleration[2] * TIME_STEP;
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
	float n = 0;
	Eigen::Matrix<double, 9, 1> X = Eigen::Matrix<double, 9, 1>::Zero();
	Eigen::Matrix<double, 9, 1> X_next = Eigen::Matrix<double, 9, 1>::Zero();
	Eigen::Matrix<double, 9, 1> Z = Eigen::Matrix<double, 9, 1>::Zero();
	Eigen::Matrix<double, 9, 9> F = init_F();
	Eigen::Matrix<double, 9, 9> P = init_P();
	Eigen::Matrix<double, 9, 9> R = init_R();
	Eigen::Matrix<double, 9, 9> Q = init_Q();
	Eigen::Matrix<double, 9, 9> H = Eigen::Matrix<double, 9, 9>::Identity();
	Eigen::Matrix<double, 9, 9> K = Eigen::Matrix<double, 9, 9>::Zero();

	//init
	P = F * P * F.transpose() + Q;

	while (true) {
		std::cout << "----------------" << std::endl;
		std::cout << "---Start loop---" << std::endl;

		get_info(vehicule, client, server);
		if (vehicule.z_reiceived) 
		{
			X = init_X(vehicule);
			Z = init_Z(vehicule);

			//display matrices
			// std::cout << "P: " << std::endl << P << std::endl;
			// std::cout << "K: " << std::endl << K << std::endl;
			// std::cout << "X: " << std::endl << X << std::endl;
			// std::cout << "Z: " << std::endl << Z << std::endl;

			//Update
			K = P * H.transpose() * (H * P * H.transpose() + R).inverse();
			std::cout << "K: " << std::endl << K << std::endl;
			X_next = X + K * (Z - H * X);
			P = (Eigen::Matrix<double, 9, 9>::Identity() - K * H) * P * (Eigen::Matrix<double, 9, 9>::Identity() - K * H).transpose() + K * R * K.transpose();

			//Predict
			X = F * X_next;
			std::cout << "X_next: " << std::endl << X_next << std::endl;
			P = F * P * F.transpose() + Q;

			vehicule.guessed_position[0] = X_next(0);
			vehicule.guessed_position[1] = X_next(3);
			vehicule.guessed_position[2] = X_next(6);
			vehicule.speed[0] = X_next(1);
			vehicule.speed[1] = X_next(4);
			vehicule.speed[2] = X_next(7);
			vehicule.acceleration[0] = X_next(2);
			vehicule.acceleration[1] = X_next(5);
			vehicule.acceleration[2] = X_next(8);

			vehicule.z_reiceived = false;
		}
		calculate_position(vehicule);

		//new position
		std::string new_position = std::to_string(vehicule.guessed_position[0]) + " " + std::to_string(vehicule.guessed_position[1]) + " " + std::to_string(vehicule.guessed_position[2]);
		std::cout << GREEN_TEXT << "New position: " << new_position << RESET_TEXT << std::endl;
		if (sendto(client, new_position.c_str(), strlen(new_position.c_str()), 0, (struct sockaddr*)&server, sizeof(server)) < 0) {
			std::cerr << "Error: sendto" << std::endl;
			return 1;
		}
		n++;
		std::cout << "Time " << n/100 << std::endl;
		std::cout << "---End loop---" << std::endl;
		std::cout << "----------------" << std::endl;
		std::cout << std::endl;
	}
}