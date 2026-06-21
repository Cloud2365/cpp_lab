#include "EnlargePaddleBonus.h"
#include "Constants.h"
#include "Game.h"

EnlargePaddleBonus::EnlargePaddleBonus(float x, float yPos) : y(yPos), active(true) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, yPos);
}

void EnlargePaddleBonus::apply(Game& game) {
    game.enlargePaddle();
}

void EnlargePaddleBonus::update(float dt) {
    y += BONUS_FALL_SPEED * dt;
    shape.setPosition(shape.getPosition().x, y);
    if (y > WINDOW_HEIGHT) active = false;
}

void EnlargePaddleBonus::draw(sf::RenderWindow& window) {
    if (active) window.draw(shape);
}

sf::FloatRect EnlargePaddleBonus::getBounds() const {
    return shape.getGlobalBounds();
}

bool EnlargePaddleBonus::isActive() const {
    return active;
}

void EnlargePaddleBonus::setPosition(float x, float y) {
    shape.setPosition(x, y);
}