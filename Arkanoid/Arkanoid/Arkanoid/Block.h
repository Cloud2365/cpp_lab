#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>

class Ball;
class Game;

class Block {
public:
    virtual ~Block() = default;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void setPosition(float x, float y) = 0;
    virtual sf::FloatRect getBounds() const = 0;
    virtual bool hit() = 0;           
    virtual int getHealth() const = 0;
    virtual void onHit(Ball& ball, Game& game) = 0; 
    virtual int getScore() const = 0;
};

#endif

