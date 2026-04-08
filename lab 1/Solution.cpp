#include "Solution.h"
#include "Equation.h"
#include "Constans.h"
#include <cmath>
#include <algorithm>

Solution::Solution(double r1, double r2) : root1(r1), root2(r2) {}

double Solution::getRoot1() const { return root1; }
double Solution::getRoot2() const { return root2; }

bool Solution::isCorrectFor(const Equation& eq) const {
    if (!eq.hasRealRoots()) return false;

    double correctX1, correctX2;
    eq.getRoots(correctX1, correctX2);

    double s1 = root1, s2 = root2;
    if (s1 > s2) std::swap(s1, s2);
    if (correctX1 > correctX2) std::swap(correctX1, correctX2);

    return (std::fabs(s1 - correctX1) < EPS && std::fabs(s2 - correctX2) < EPS);
}