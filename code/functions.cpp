#include <iostream>
#include <cmath>
#include "functions.hpp"

void print(double root1, double root2) {
    std::cout << "found roots: " << root1 << " and " << root2 << std::endl;
}

void print(double root1) {
    std::cout << "only one root: " << root1 << std::endl;
}

void get_error() {
    std::cout << "error: complex roots." << std::endl;
}

void find_roots(double a, double b, double c) {
    double discrim = b * b - 4 * a * c; 
    if (discrim < 0) {
        get_error();
    }
    else if (discrim == 0) {
        double root1 = -b / (2 * a);
        print(root1);
    }
    else {
        double root1 = (-b + sqrt(discrim)) / (2 * a);
        double root2 = (-b - sqrt(discrim)) / (2 * a);
        print(root1, root2);
    }
}

void get_coefs(double& a, double& b, double& c) {
    std::cout << "enter the coefficients a, b and c: ";
    std::cin >> a >> b >> c;
}
