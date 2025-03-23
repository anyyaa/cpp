#include "teacher.hpp"
#include <iostream>

using namespace std;

void Teacher::receiveMail(const QuadraticEquation& eq, const vector<double>& solution, const string& studentName) {
    mailQueue.push_back({ eq, {solution, studentName} });
}

void Teacher::checkMail() {
    for (const auto& mail : mailQueue) {
        const auto& eq = mail.first;
        const auto& solution = mail.second.first;
        const auto& studentName = mail.second.second;

        auto correctSolution = eq.solve();
        bool isCorrect = (solution == correctSolution);
        bool found = false;
        for (auto& result : resultsTable) {
            if (result.first == studentName) {
                if (isCorrect) {
                    result.second++; 
                }
                found = true;
                break;
            }
        }
        if (!found) {
            resultsTable.push_back({ studentName, isCorrect ? 1 : 0 });
        }
    }
    mailQueue.clear();
}

void Teacher::publishResults() const {
    cout << "results table:" << endl;
    for (const auto& result : resultsTable) {
        cout << result.first << ": " << result.second << " correct solutions" << endl;
    }
}