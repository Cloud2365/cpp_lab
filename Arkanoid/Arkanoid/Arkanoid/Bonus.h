#pragma once
#ifndef BONUS_H
#define BONUS_H

#include <SFML/Graphics.hpp>

enum BonusType {
    ENLARGE_PADDLE,
    SHRINK_PADDLE,
    SPEED_UP_BALL,
    SLOW_DOWN_BALL,
    STICKY_PADDLE,
    EXTRA_LIFE_BOTTOM,
    RANDOM_TRAJECTORY
};

class Bonus {
public:
    Bonus(BonusType t, float x, float y);
    void update(float dt);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    bool isActive() const;
    BonusType getType() const;

private:
    BonusType type;
    sf::RectangleShape shape;
    float y;
    bool active;
};

#endif