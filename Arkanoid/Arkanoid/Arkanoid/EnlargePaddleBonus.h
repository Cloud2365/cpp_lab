#ifndef ENLARGE_PADDLE_BONUS_H
#define ENLARGE_PADDLE_BONUS_H

#include "Bonus.h"

class EnlargePaddleBonus : public Bonus {
public:
    EnlargePaddleBonus(float x, float y);
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