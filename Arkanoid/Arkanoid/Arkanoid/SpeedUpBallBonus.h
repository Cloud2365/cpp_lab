#ifndef SPEED_UP_BALL_BONUS_H
#define SPEED_UP_BALL_BONUS_H

#include "Bonus.h"

class SpeedUpBallBonus : public Bonus {
public:
    SpeedUpBallBonus(float x, float y);
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