#ifndef BONUS_FACTORY_H
#define BONUS_FACTORY_H

#include <memory>
#include "Bonus.h"

class BonusFactory {
public:
    static std::unique_ptr<Bonus> createRandomBonus(float x, float y);
};

#endif