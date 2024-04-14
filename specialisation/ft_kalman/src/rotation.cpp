#include "../includes/rotation.hpp"

// Define a function to perform the rotation
std::vector<double> rotateVector(const std::vector<double>& v, double phi, double psi, double theta) {
    // Assuming v is of the form [x, y, z]
    if (v.size() != 3) {
        std::cerr << "Vector must be 3-dimensional." << std::endl;
        return {};
    }

	// Convert the angles to radians
	phi = phi * M_PI / 180;
	psi = psi * M_PI / 180;
	theta = theta * M_PI / 180;

    // Calculate the cosine and sine of the angles to avoid recomputation
    double cosPhi = cos(phi), sinPhi = sin(phi);
    double cosPsi = cos(psi), sinPsi = sin(psi);
    double cosTheta = cos(theta), sinTheta = sin(theta);

    // Define the rotation matrices
    double Rx[3][3] = {
        {1, 0, 0},
        {0, cosPhi, -sinPhi},
        {0, sinPhi, cosPhi}
    };

    double Ry[3][3] = {
        {cosPsi, 0, sinPsi},
        {0, 1, 0},
        {-sinPsi, 0, cosPsi}
    };

    double Rz[3][3] = {
        {cosTheta, -sinTheta, 0},
        {sinTheta, cosTheta, 0},
        {0, 0, 1}
    };

    // Apply rotation Rz * Ry * Rx to the vector
    std::vector<double> temp = {0, 0, 0}, result = {0, 0, 0};

    // First apply Rz
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp[i] += Rz[i][j] * v[j];
        }
    }

    // Then apply Ry to the result of Rz * v
    std::vector<double> temp2 = {0, 0, 0};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp2[i] += Ry[i][j] * temp[j];
        }
    }

    // Finally, apply Rx to the result of Ry * (Rz * v)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i] += Rx[i][j] * temp2[j];
        }
    }

    return result;
}

std::vector<double> inverseRotateVector(const std::vector<double>& v, double phi, double psi, double theta) {
    if (v.size() != 3) {
        std::cerr << "Vector must be 3-dimensional." << std::endl;
        return {};
    }

    // Convert the angles to radians and negate them for inverse rotation
    phi = -phi * M_PI / 180;
    psi = -psi * M_PI / 180;
    theta = -theta * M_PI / 180;

    // Calculate the cosine and sine of the negated angles
    double cosPhi = cos(phi), sinPhi = sin(phi);
    double cosPsi = cos(psi), sinPsi = sin(psi);
    double cosTheta = cos(theta), sinTheta = sin(theta);

    // Define the inverse rotation matrices (note the negation of sine components)
    double RxInv[3][3] = {
        {1, 0, 0},
        {0, cosPhi, sinPhi},
        {0, -sinPhi, cosPhi}
    };

    double RyInv[3][3] = {
        {cosPsi, 0, -sinPsi},
        {0, 1, 0},
        {sinPsi, 0, cosPsi}
    };

    double RzInv[3][3] = {
        {cosTheta, sinTheta, 0},
        {-sinTheta, cosTheta, 0},
        {0, 0, 1}
    };

    // Apply inverse rotation RxInv * RyInv * RzInv to the vector
    std::vector<double> temp = {0, 0, 0}, result = {0, 0, 0};

    // First apply RxInv
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp[i] += RxInv[i][j] * v[j];
        }
    }

    // Then apply RyInv to the result of RxInv * v
    std::vector<double> temp2 = {0, 0, 0};
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            temp2[i] += RyInv[i][j] * temp[j];
        }
    }

    // Finally, apply RzInv to the result of RyInv * (RxInv * v)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result[i] += RzInv[i][j] * temp2[j];
        }
    }

    return result;
}