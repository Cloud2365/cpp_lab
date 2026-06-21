#include "ShrinkPaddleBonus.h"
#include "Constants.h"
#include "Game.h"

ShrinkPaddleBonus::ShrinkPaddleBonus(float x, float yPos) : y(yPos), active(true) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color::Blue);
    shape.setPosition(x, yPos);
}

void ShrinkPaddleBonus::apply(Game& game) {
    game.shrinkPaddle();
}

void ShrinkPaddleBonus::update(float dt) {
    y += BONUS_FALL_SPEED * dt;
    shape.setPosition(shape.getPosition().x, y);
    if (y > WINDOW_HEIGHT) active = false;
}

void ShrinkPaddleBonus::draw(sf::RenderWindow& window) {
    if (active) window.draw(shape);
}

sf::FloatRect ShrinkPaddleBonus::getBounds() const {
    return shape.getGlobalBounds();
}

bool ShrinkPaddleBonus::isActive() const {
    return active;
}

void ShrinkPaddleBonus::setPosition(float x, float y) {
    shape.setPosition(x, y);
}