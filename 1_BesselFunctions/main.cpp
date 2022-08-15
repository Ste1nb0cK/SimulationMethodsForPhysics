#include <iostream>
#include "Bessel.hpp"
#include "Bisection.hpp"

int main(int argc, char **argv) {
    double alpha = std::atof(argv[1]); //order of the function
    double x = std::atof(argv[2]);
    std::cout.precision(16); std::cout.setf(std::ios::scientific);
    std::cout << BesselFunctions(alpha, x) << std::endl;

    return 0;
}
