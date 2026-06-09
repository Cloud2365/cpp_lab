#include "StickyPaddleBonus.h"
#include "Constants.h"
#include "Game.h"

StickyPaddleBonus::StickyPaddleBonus(float x, float yPos) : y(yPos), active(true) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color::White);
    shape.setPosition(x, yPos);
}

void StickyPaddleBonus::apply(Game& game) {
    game.enableStickyMode();
}

void StickyPaddleBonus::update(float dt) {
    y += BONUS_FALL_SPEED * dt;
    shape.setPosition(shape.getPosition().x, y);
    if (y > WINDOW_HEIGHT) active = false;
}

void StickyPaddleBonus::draw(sf::RenderWindow& window) {
    if (active) window.draw(shape);
}

sf::FloatRect StickyPaddleBonus::getBounds() const {
    return shape.getGlobalBounds();
}

bool StickyPaddleBonus::isActive() const {
    return active;
}

void StickyPaddleBonus::setPosition(float x, float y) {
    shape.setPosition(x, y);
}