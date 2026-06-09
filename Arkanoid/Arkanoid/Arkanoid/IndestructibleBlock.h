#ifndef INDESTRUCTIBLE_BLOCK_H
#define INDESTRUCTIBLE_BLOCK_H

#include "Block.h"

class IndestructibleBlock : public Block {
public:
    IndestructibleBlock();
    void draw(sf::RenderWindow& window) override;
    void setPosition(float x, float y) override;
    sf::FloatRect getBounds() const override;
    bool hit() override;
    int getHealth() const override;
    void onHit(Ball& ball, Game& game) override;
    int getScore() const override;

private:
    sf::RectangleShape shape;
};

#endif