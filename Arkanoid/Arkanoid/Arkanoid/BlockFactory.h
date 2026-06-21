#ifndef BLOCK_FACTORY_H
#define BLOCK_FACTORY_H

#include <memory>
#include "Block.h"

class BlockFactory {
public:
    static std::unique_ptr<Block> createRandomBlock();
};

#endif