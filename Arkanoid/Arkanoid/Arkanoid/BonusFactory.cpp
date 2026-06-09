#include "BonusFactory.h"
#include "Constants.h"
#include "EnlargePaddleBonus.h"
#include "ShrinkPaddleBonus.h"
#include "SpeedUpBallBonus.h"
#include "SlowDownBallBonus.h"
#include "StickyPaddleBonus.h"
#include "ExtraLifeBottomBonus.h"
#include "RandomTrajectoryBonus.h"

std::unique_ptr<Bonus> BonusFactory::createRandomBonus(float x, float y) {
    std::uniform_int_distribution<int> dist(0, 6);
    int type = dist(getRng());

    switch (type) {
    case 0: return std::make_unique<EnlargePaddleBonus>(x, y);
    case 1: return std::make_unique<ShrinkPaddleBonus>(x, y);
    case 2: return std::make_unique<SpeedUpBallBonus>(x, y);
    case 3: return std::make_unique<SlowDownBallBonus>(x, y);
    case 4: return std::make_unique<StickyPaddleBonus>(x, y);
    case 5: return std::make_unique<ExtraLifeBottomBonus>(x, y);
    case 6: return std::make_unique<RandomTrajectoryBonus>(x, y);
    default: return std::make_unique<EnlargePaddleBonus>(x, y);
    }
}