#ifndef HEALTH_BLOCK_H
#define HEALTH_BLOCK_H

#include "Block.h"

class HealthBlock : public Block {
public:
    HealthBlock();
    void draw(sf::RenderWindow& window) override;
    void setPosition(float x, float y) override;
    sf::FloatRect getBounds() const override;
    bool hit() override;
    int getHealth() const override;
    void onHit(Ball& ball) override;
    int getScore() const override;

private:
    sf::RectangleShape shape;
    int health;
};

#endif