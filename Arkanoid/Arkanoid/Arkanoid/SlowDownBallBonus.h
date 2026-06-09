#ifndef SLOW_DOWN_BALL_BONUS_H
#define SLOW_DOWN_BALL_BONUS_H

#include "Bonus.h"

class SlowDownBallBonus : public Bonus {
public:
    SlowDownBallBonus(float x, float y);
    void apply(Game& game) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) override;
    sf::FloatRect getBounds() const override;
    bool isActive() const override;
    void setPosition(float x, float y) override;

private:
    sf::RectangleShape shape;
    float y;
    bool active;
};

#endif