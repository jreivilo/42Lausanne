#include "../includes/matrix.hpp"

Eigen::Matrix<double, 9, 9> init_F() {
    Eigen::Matrix<double, 9, 9> F = Eigen::Matrix<double, 9, 9>::Zero();

    // Set the specific elements based on the given structure
    F(0,0) = 1;
    F(0,1) = TIME_STEP;
    F(0,2) = std::pow(TIME_STEP, 2) / 2;
    F(1,1) = 1;
    F(1,2) = TIME_STEP;
    F(2,2) = 1;

    F(3,3) = 1;
    F(3,4) = TIME_STEP;
    F(3,5) = std::pow(TIME_STEP, 2) / 2;
    F(4,4) = 1;
    F(4,5) = TIME_STEP;
    F(5,5) = 1;

    F(6,6) = 1;
    F(6,7) = TIME_STEP;
    F(6,8) = std::pow(TIME_STEP, 2) / 2;
    F(7,7) = 1;
    F(7,8) = TIME_STEP;
    F(8,8) = 1;

    return F;
}

Eigen::Matrix<double, 9, 9> init_P() {
    Eigen::Matrix<double, 9, 9> matrix = Eigen::Matrix<double, 9, 9>::Zero();
    return matrix;
}

Eigen::Matrix<double, 9, 9> init_R() {
    Eigen::Matrix<double, 9, 9> R = Eigen::Matrix<double, 9, 9>::Zero();

    // Set specific diagonal entries
    R(0,0) = STD_GPS * STD_GPS;
    R(1,1) = STD_GYRO * STD_GYRO;
    R(2,2) = STD_ACC * STD_ACC;
    R(3,3) = STD_GPS * STD_GPS;
    R(4,4) = STD_GYRO * STD_GYRO;
    R(5,5) = STD_ACC * STD_ACC;
    R(6,6) = STD_GPS * STD_GPS;
    R(7,7) = STD_GYRO * STD_GYRO;
    R(8,8) = STD_ACC * STD_ACC;

    return R;
}

Eigen::Matrix<double, 9, 9> init_Q() {
    Eigen::Matrix<double, 9, 9> Q = Eigen::Matrix<double, 9, 9>::Zero();

    // Populate the matrix with specific values according to the original C function
    Q(0,0) = std::pow(TIME_STEP, 4)/4;
    Q(0,1) = Q(1,0) = std::pow(TIME_STEP, 3)/2;
    Q(0,2) = Q(2,0) = std::pow(TIME_STEP, 2)/2;
	Q(1,1) = std::pow(TIME_STEP, 2);
    Q(1,2) = Q(2,1) = TIME_STEP;
    Q(2,2) = 1;

    Q(3,3) = std::pow(TIME_STEP, 4)/4;
    Q(3,4) = Q(4,3) = std::pow(TIME_STEP, 3)/2;
    Q(3,5) = Q(5,3) = std::pow(TIME_STEP, 2)/2;
	Q(4,4) = std::pow(TIME_STEP, 2);
    Q(4,5) = Q(5,4) = TIME_STEP;
    Q(5,5) = 1;

    Q(6,6) = std::pow(TIME_STEP, 4)/4;
    Q(6,7) = Q(7,6) = std::pow(TIME_STEP, 3)/2;
    Q(6,8) = Q(8,6) = std::pow(TIME_STEP, 2)/2;
	Q(7,7) = std::pow(TIME_STEP, 2);
    Q(7,8) = Q(8,7) = TIME_STEP;
    Q(8,8) = 1;

    // Multiply entire matrix by STD_ACC
    Q *= STD_ACC * STD_ACC;

    return Q;
}

Eigen::Matrix<double, 9, 1> init_Z(Vehicule& vehicule) {
	Eigen::Matrix<double, 9, 1> Z = Eigen::Matrix<double, 9, 1>::Zero();

std::vector<double> r_speed = { vehicule.speed[0], vehicule.speed[1], vehicule.speed[2] };
	r_speed = rotateVector(r_speed, vehicule.direction[0], vehicule.direction[1], vehicule.direction[2]);

	// Set the specific elements based on the given structure
	Z(0,0) = vehicule.true_position[0];
	Z(1,0) = vehicule.speed[0];
	Z(2,0) = vehicule.acceleration[0];
	Z(3,0) = vehicule.true_position[1];
	Z(4,0) = vehicule.speed[1];
	Z(5,0) = vehicule.acceleration[1];
	Z(6,0) = vehicule.true_position[2];
	Z(7,0) = vehicule.speed[2];
	Z(8,0) = vehicule.acceleration[2];

	return Z;
}

Eigen::Matrix<double, 9, 1> init_X(Vehicule& vehicule) {
	Eigen::Matrix<double, 9, 1> X = Eigen::Matrix<double, 9, 1>::Zero();


	// Set the specific elements based on the given structure
	X(0,0) = vehicule.guessed_position[0];
	X(1,0) = vehicule.speed[0];
	X(2,0) = vehicule.acceleration[0];
	X(3,0) = vehicule.guessed_position[1];
	X(4,0) = vehicule.speed[1];
	X(5,0) = vehicule.acceleration[1];
	X(6,0) = vehicule.guessed_position[2];
	X(7,0) = vehicule.speed[2];
	X(8,0) = vehicule.acceleration[2];

	return X;
}