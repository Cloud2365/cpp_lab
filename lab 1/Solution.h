#ifndef SOLUTION_H
#define SOLUTION_H

class Equation; 

class Solution {
private:
    double root1, root2;

public:
    Solution(double r1 = 0, double r2 = 0);
    double getRoot1() const;
    double getRoot2() const;

    bool isCorrectFor(const Equation& eq) const;
};

#endif
