#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

#include <vector>
#include <iostream>

class QuadraticEquation {
private:
    double a, b, c;

public:
    QuadraticEquation(double a = 0, double b = 0, double c = 0);
    std::vector<double> solve() const;
    void print() const;
};

#endif