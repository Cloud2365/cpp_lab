#include "BlockFactory.h"
#include "NormalBlock.h"
#include "IndestructibleBlock.h"
#include "BonusBlock.h"
#include "SpeedBoostBlock.h"
#include "HealthBlock.h"
#include "Constants.h"

std::unique_ptr<Block> BlockFactory::createRandomBlock() {
    std::uniform_real_distribution<float> dist(0.0f, 1.0f);
    float r = dist(getRng());
    float accum = 0.0f;

    for (int i = 0; i < 5; ++i) {
        accum += BLOCK_PROBABILITIES[i];
        if (r < accum) {
            switch (i) {
            case 0: return std::make_unique<NormalBlock>();
            case 1: return std::make_unique<IndestructibleBlock>();
            case 2: return std::make_unique<BonusBlock>();
            case 3: return std::make_unique<SpeedBoostBlock>();
            case 4: return std::make_unique<HealthBlock>();
            default: return std::make_unique<NormalBlock>();
            }
        }
    }
    return std::make_unique<NormalBlock>();
}