#include "QuadraticEquation.hpp"
#include "student.hpp"
#include "teacher.hpp"
#include <fstream>
#include <ctime>

using namespace std;

int main() {
    srand(time(0)); //для случайного результата у среднего студента

    Teacher teacher;

    GoodStudent goodStudent("Anna");
    AverageStudent averageStudent("Ivan");
    BadStudent badStudent("Liza");

    ifstream inputFile("equations.txt");
    double a, b, c;
    while (inputFile >> a >> b >> c) {
        QuadraticEquation eq(a, b, c);

        auto goodSolution = goodStudent.solveEquation(eq);
        teacher.receiveMail(eq, goodSolution, goodStudent.getName());
        auto averageSolution = averageStudent.solveEquation(eq);
        teacher.receiveMail(eq, averageSolution, averageStudent.getName());
        auto badSolution = badStudent.solveEquation(eq);
        teacher.receiveMail(eq, badSolution, badStudent.getName());
    }
    teacher.checkMail();
    teacher.publishResults();
    return 0;
}
