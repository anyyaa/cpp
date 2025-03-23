#ifndef STUDENT_H
#define STUDENT_H

#include "QuadraticEquation.hpp"
#include <vector>
#include <string>

class Student {
protected:
    std::string name;

public:
    Student(const std::string& name);
    virtual std::vector<double> solveEquation(const QuadraticEquation& eq) = 0;
    std::string getName() const;
};

class GoodStudent : public Student {
public:
    GoodStudent(const std::string& name);
    std::vector<double> solveEquation(const QuadraticEquation& eq) override;
};

class AverageStudent : public Student {
public:
    AverageStudent(const std::string& name);
    std::vector<double> solveEquation(const QuadraticEquation& eq) override;
};

class BadStudent : public Student {
public:
    BadStudent(const std::string& name);
    std::vector<double> solveEquation(const QuadraticEquation& eq) override;
};

#endif