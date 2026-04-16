#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include "Solution.h"
#include "Equation.h"

enum class StudentType {
    GOOD,
    AVERAGE,
    BAD
};

class Student {
protected:
    std::string name;
public:
    Student(const std::string& name);
    virtual ~Student() = default;
    virtual Solution solve(const Equation& eq) const = 0;
    virtual StudentType getType() const = 0;
    std::string getName() const;
};

class GoodStudent : public Student {
public:
    GoodStudent(const std::string& name);
    Solution solve(const Equation& eq) const override;
    StudentType getType() const override;
};

class AverageStudent : public Student {
public:
    AverageStudent(const std::string& name);
    Solution solve(const Equation& eq) const override;
    StudentType getType() const override;
};

class BadStudent : public Student {
public:
    BadStudent(const std::string& name);
    Solution solve(const Equation& eq) const override;
    StudentType getType() const override;
};

#endif
