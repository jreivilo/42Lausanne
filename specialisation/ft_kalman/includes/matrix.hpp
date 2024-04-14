#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <iostream>
#include <vector>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <Eigen/Dense>
#include <Eigen/Dense>

#include "vehicule.hpp"
#include "rotation.hpp"
#include "defines.hpp"

Eigen::Matrix<double, 9, 9> init_F();
Eigen::Matrix<double, 9, 9> init_P();
Eigen::Matrix<double, 9, 9> init_R();
Eigen::Matrix<double, 9, 9> init_Q();
Eigen::Matrix<double, 9, 1> init_Z(Vehicule& vehicule);
Eigen::Matrix<double, 9, 1> init_X(Vehicule& vehicule);


#endif