#ifndef VEHICULE_HPP
#define VEHICULE_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>

struct Vehicule {
	std::vector<double> true_position;
	std::vector<double> speed;
	std::vector<double> acceleration;
	std::vector<double> direction;
	std::vector<double> guessed_position;
	bool z_reiceived = false;
};

#endif