#ifndef BOMB_BONUS_H
#define BOMB_BONUS_H

#include "Bonus.h"

class BombBonus : public Bonus {
public:
    BombBonus(float x, float y, int targetRow, int targetCol);
    void apply(Grid& grid) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
    bool isActive() const override;
    void setPosition(float x, float y) override;

private:
    sf::RectangleShape shape;
    float y;
    bool active;
    int targetRow, targetCol;
};

#endif

