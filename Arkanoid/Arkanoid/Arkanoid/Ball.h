#pragma once
#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball();
    void update(float dt);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    void reboundX();
    void reboundY();
    void setVelocity(float vx, float vy);
    void randomizeVelocity(float speed);
    void stickToPaddle(float paddleX, float paddleY);
    bool isStuck() const;
    void release();
    sf::Vector2f getVelocity() const;

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    bool stuck;
};

#endif