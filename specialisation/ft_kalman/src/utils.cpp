#include "../includes/utils.hpp"

#include <iostream>

// ANSI escape code for green text
#define YELLOW_TEXT "\033[33m"
// ANSI escape code to reset text color
#define RESET_TEXT "\033[0m"

// void print_vehicule(Vehicule vehicule) {
// 	std::cout << YELLOW_TEXT << "Printing vehicule" << std::endl;
// 	std::cout << YELLOW_TEXT << "True position: ";
// 	for (int i = 0; i < vehicule.true_position.size(); i++) {
// 		std::cout << vehicule.true_position[i] << " ";
// 	}
// 	std::cout << RESET_TEXT << std::endl;

// 	std::cout << YELLOW_TEXT << "Guessed position: ";
// 	for (int i = 0; i < vehicule.guessed_position.size(); i++) {
// 		std::cout << vehicule.guessed_position[i] << " ";
// 	}
// 	std::cout << RESET_TEXT << std::endl;
	
// 	std::cout << YELLOW_TEXT << "Speed: ";
// 	for (int i = 0; i < vehicule.speed.size(); i++) {
// 		std::cout << vehicule.speed[i] << " ";
// 	}
// 	std::cout << RESET_TEXT << std::endl;

// 	std::cout << YELLOW_TEXT << "Acceleration: ";
// 	for (int i = 0; i < vehicule.acceleration.size(); i++) {
// 		std::cout << vehicule.acceleration[i] << " ";
// 	}
// 	std::cout << RESET_TEXT << std::endl;

// 	std::cout << YELLOW_TEXT << "Direction: ";
// 	for (int i = 0; i < vehicule.direction.size(); i++) {
// 		std::cout << vehicule.direction[i] << " ";
// 	}
// 	std::cout << RESET_TEXT << std::endl;
// 	std::cout << std::endl;
// }