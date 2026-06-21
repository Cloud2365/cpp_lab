#ifndef BONUS_BLOCK_H
#define BONUS_BLOCK_H

#include "Block.h"

class BonusBlock : public Block {
public:
    BonusBlock();
    void draw(sf::RenderWindow& window) override;
    void setPosition(float x, float y) override;
    sf::FloatRect getBounds() const override;
    bool hit() override;
    int getHealth() const override;
    void onHit(Ball& ball, Game& game) override;
    int getScore() const override;

private:
    sf::RectangleShape shape;
    int health;
};

#endif