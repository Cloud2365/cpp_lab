#include "Student.h"
#include "Constans.h"
#include <cstdlib> 

Student::Student(const std::string& name) : name(name) {}
std::string Student::getName() const { return name; }

// ----- GoodStudent -----
GoodStudent::GoodStudent(const std::string& name) : Student(name) {}

Solution GoodStudent::solve(const Equation& eq) const {
    double x1, x2;
    eq.getRoots(x1, x2);
    return Solution(x1, x2);
}

StudentType GoodStudent::getType() const { return StudentType::GOOD; }

// ----- AverageStudent -----
AverageStudent::AverageStudent(const std::string& name) : Student(name) {}

Solution AverageStudent::solve(const Equation& eq) const {
    int random = rand() % 100;
    if (random < AVERAGE_PROBABILITY * 100) { 
        double x1, x2;
        eq.getRoots(x1, x2);
        return Solution(x1, x2);
    }
    else {
        double wrongRoot1 = (rand() % 20 - 10) + (rand() % 100) / 100.0;
        double wrongRoot2 = (rand() % 20 - 10) + (rand() % 100) / 100.0;
        return Solution(wrongRoot1, wrongRoot2);
    }
}

StudentType AverageStudent::getType() const { return StudentType::AVERAGE; }

// ----- BadStudent -----
BadStudent::BadStudent(const std::string& name) : Student(name) {}

Solution BadStudent::solve(const Equation& eq) const {
    double wrongRoot1 = (rand() % 20 - 10) + (rand() % 100) / 100.0;
    double wrongRoot2 = (rand() % 20 - 10) + (rand() % 100) / 100.0;
    return Solution(wrongRoot1, wrongRoot2);
}

StudentType BadStudent::getType() const { return StudentType::BAD; }

