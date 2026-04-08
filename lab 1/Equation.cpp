#include "Equation.h"
#include "Constans.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <algorithm>

Equation::Equation(double a, double b, double c) : a(a), b(b), c(c) {}

double Equation::discriminant() const {
    return b * b - 4 * a * c;
}

void Equation::getRoots(double& x1, double& x2) const {
    double D = discriminant();
    double sqrtD = std::sqrt(D);
    x1 = (-b - sqrtD) / (2 * a);
    x2 = (-b + sqrtD) / (2 * a);
    if (x1 > x2) std::swap(x1, x2);
}

bool Equation::hasRealRoots() const {
    return discriminant() >= -EPS;
}

std::vector<Equation> Equation::readFromFile(const std::string& filename) {
    std::vector<Equation> equations;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return equations;
    }
    double a, b, c;
    while (file >> a >> b >> c) {
        if (std::fabs(a) < EPS) {
            std::cerr << "Предупреждение: a = 0, пропускаем." << std::endl;
            continue;
        }
        equations.emplace_back(a, b, c);
    }
    file.close();
    return equations;
}