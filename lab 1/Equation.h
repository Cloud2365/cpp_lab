#ifndef EQUATION_H
#define EQUATION_H

#include <vector>
#include <string>

class Equation {
private:
    double a, b, c;

public:
    Equation(double a = 0, double b = 0, double c = 0);

    double discriminant() const;
    void getRoots(double& x1, double& x2) const;
    bool hasRealRoots() const;

    static std::vector<Equation> readFromFile(const std::string& filename);
};

#endif

