#include "Paddle.h"
#include "Constants.h"
#include <iostream>

Paddle::Paddle() {
    width = PADDLE_WIDTH;
    height = PADDLE_HEIGHT;
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(width / 2, height / 2);
    x = WINDOW_WIDTH / 2;
    y = WINDOW_HEIGHT - 30;
    shape.setPosition(x, y);
}

void Paddle::update(float dt) {
    shape.setPosition(x, y);
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Paddle::moveLeft(float dt) {
    x -= PADDLE_SPEED * dt;
    if (x < width / 2) x = width / 2;
    shape.setPosition(x, y);
}

void Paddle::moveRight(float dt) {
    x += PADDLE_SPEED * dt;
    if (x > WINDOW_WIDTH - width / 2) x = WINDOW_WIDTH - width / 2;
    shape.setPosition(x, y);
}

void Paddle::setWidth(float newWidth) {
    width = newWidth;
    shape.setSize(sf::Vector2f(width, height));
    shape.setOrigin(width / 2, height / 2);
    if (x - width / 2 < 0) x = width / 2;
    if (x + width / 2 > WINDOW_WIDTH) x = WINDOW_WIDTH - width / 2;
}

sf::FloatRect Paddle::getBounds() const {
    return shape.getGlobalBounds();
}

sf::Vector2f Paddle::getPosition() const {
    return sf::Vector2f(x, y);
}