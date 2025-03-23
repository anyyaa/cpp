#ifndef TEACHER_H
#define TEACHER_H

#include "QuadraticEquation.hpp"
#include <vector>
#include <string>
#include <utility>

class Teacher {
private:
    std::vector<std::pair<QuadraticEquation, std::pair<std::vector<double>, std::string>>> mailQueue;
    std::vector<std::pair<std::string, int>> resultsTable;

public:
    void receiveMail(const QuadraticEquation& eq, const std::vector<double>& solution, const std::string& studentName);
    void checkMail();
    void publishResults() const;
};

#endif