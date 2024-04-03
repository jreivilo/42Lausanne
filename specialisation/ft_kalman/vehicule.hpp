#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <vector>

struct Vehicule {
	std::vector<double> true_position;
	double speed;
	std::vector<double> acceleration;
	std::vector<double> direction;
	std::vector<double> gps_position;
};