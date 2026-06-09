#ifndef BONUS_H
#define BONUS_H

#include <SFML/Graphics.hpp>

class Game;

class Bonus {
public:
    virtual ~Bonus() = default;
    virtual void apply(Game& game) = 0;     
    virtual void update(float dt) = 0;       
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual bool isActive() const = 0;
    virtual void setPosition(float x, float y) = 0;
};

#endif