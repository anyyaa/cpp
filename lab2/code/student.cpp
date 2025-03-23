#include "student.hpp"
#include <cstdlib>
#include <ctime>

using namespace std;

Student::Student(const string& name) : name(name) {}

string Student::getName() const {
    return name;
}

GoodStudent::GoodStudent(const string& name) : Student(name) {}

vector<double> GoodStudent::solveEquation(const QuadraticEquation& eq) {
    return eq.solve();
}

AverageStudent::AverageStudent(const string& name) : Student(name) {}

vector<double> AverageStudent::solveEquation(const QuadraticEquation& eq) {
    if (rand() % 2 == 0) {
        return eq.solve();
    }
    else {
        return { 0.0 };
    }
}

BadStudent::BadStudent(const string& name) : Student(name) {}

vector<double> BadStudent::solveEquation(const QuadraticEquation& eq) {
    return { 0.0 }; 
}