#include "../includes/parsing.hpp"


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

void get_guessed_position(std::string msg, Vehicule& vehicule) {
	vehicule.guessed_position.clear();
	for (int i = 0; i < 3; i++) {
		msg = msg.substr(msg.find("\n") + 1);
		std::string guessed_position = msg.substr(0, msg.find("\n"));
		vehicule.guessed_position.push_back(std::stod(guessed_position));
	}
}

void get_speed(std::string msg, Vehicule& vehicule) {
	msg = msg.substr(msg.find("\n") + 1);
	std::string speed = msg.substr(0, msg.find("\n"));
	vehicule.speed.clear();
	//[speed, 0, 0]
	vehicule.speed.push_back(std::stod(speed) / 3.6);
	vehicule.speed.push_back(0);
	vehicule.speed.push_back(0);
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

void update_guessed_position(Vehicule& vehicule) {
	int alpha = 1;
	vehicule.guessed_position[0] = vehicule.true_position[0] + alpha * (vehicule.guessed_position[0] - vehicule.true_position[0]);
	vehicule.guessed_position[1] = vehicule.true_position[1] + alpha * (vehicule.guessed_position[1] - vehicule.true_position[1]);
	vehicule.guessed_position[2] = vehicule.true_position[2] + alpha * (vehicule.guessed_position[2] - vehicule.true_position[2]);
}

int parse_msg(char* buffer, Vehicule& vehicule) {
	std::string msg(buffer);
	std::string first_token = msg.substr(0, msg.find("\n"));
	removeBracketsAndContents(first_token);

	// std::cout << "Msg: " << msg << std::endl;
	// std::cout << "First token: \"" << first_token << "\""<< std::endl;

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
		get_guessed_position(msg, vehicule);
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
	if (first_token == "POSITION")
	{
		vehicule.z_reiceived = true;
		get_true_position(msg, vehicule);
		update_guessed_position(vehicule);
		return 1;
	}
	if (first_token == "MSG_END")
	{
		// printf("End of message\n\n");
		return -1;
	}
	if (first_token == "GOODBYE.")
	{
		printf("Goodbye\n\n");
		return -2;
	}
	
	std::cout << "Message not recognized" << std::endl;
	std::cout << "Message: " << msg << std::endl;
	return 0;
}