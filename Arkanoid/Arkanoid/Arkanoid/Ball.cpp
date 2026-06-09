#include "Ball.h"
#include "Constants.h"
#include <cmath>

Ball::Ball() {
    shape.setRadius(BALL_RADIUS);
    shape.setFillColor(sf::Color::White);
    shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
    stuck = true;
}

void Ball::update(float dt) {
    if (!stuck) {
        shape.move(velocity * dt);
    }
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Ball::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

sf::Vector2f Ball::getPosition() const {
    return shape.getPosition();
}

sf::FloatRect Ball::getBounds() const {
    return shape.getGlobalBounds();
}

void Ball::reboundX() {
    velocity.x = -velocity.x;
}

void Ball::reboundY() {
    velocity.y = -velocity.y;
}

void Ball::setVelocity(float vx, float vy) {
    velocity = sf::Vector2f(vx, vy);
    stuck = false;
}

void Ball::randomizeVelocity(float speed) {
    std::uniform_int_distribution<int> dist(0, 359);
    float angle = dist(getRng()) * 3.14159f / 180.0f;
    velocity.x = std::cos(angle) * speed;
    velocity.y = std::sin(angle) * speed;
    stuck = false;
}

void Ball::stickToPaddle(float paddleX, float paddleY) {
    shape.setPosition(paddleX, paddleY - BALL_RADIUS);
    stuck = true;
}

bool Ball::isStuck() const {
    return stuck;
}

void Ball::release() {
    if (stuck) {
        velocity = sf::Vector2f(200.0f, -200.0f);
        stuck = false;
    }
}

sf::Vector2f Ball::getVelocity() const {
    return velocity;
}

