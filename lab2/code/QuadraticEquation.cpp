#include "QuadraticEquation.hpp"
#include <cmath>

using namespace std;

QuadraticEquation::QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}

vector<double> QuadraticEquation::solve() const {
    vector<double> roots;
    double discriminant = b * b - 4 * a * c;

    const double epsilon = 0.0000001; 
    if (discriminant < -epsilon) {
        return roots;
    }
    else if (abs(discriminant) < epsilon) {
        double root = -b / (2.0 * a);
        if (abs(root) < epsilon) {
            root = 0; 
        }
        roots.push_back(root);
        roots.push_back(root); 
    }
    else {
        double root1 = (-b + sqrt(discriminant)) / (2.0 * a);
        double root2 = (-b - sqrt(discriminant)) / (2.0 * a);

        if (abs(root1) < epsilon) {
            root1 = 0;
        }
        if (abs(root2) < epsilon) {
            root2 = 0; 
        }

        roots.push_back(root1);
        roots.push_back(root2);
    }

    return roots;
}

void QuadraticEquation::print() const {
    cout << a << "x^2 + " << b << "x + " << c << " = 0" << endl;
}