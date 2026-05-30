#include "Bonus.h"
#include "Constants.h"

Bonus::Bonus(BonusType t, float x, float yPos) : type(t), y(yPos), active(true) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(x, yPos);
}

void Bonus::update(float dt) {
    y += BONUS_FALL_SPEED * dt;
    shape.setPosition(shape.getPosition().x, y);
    if (y > WINDOW_HEIGHT) active = false;
}

void Bonus::draw(sf::RenderWindow& window) {
    if (active) window.draw(shape);
}

sf::FloatRect Bonus::getBounds() const {
    return shape.getGlobalBounds();
}

bool Bonus::isActive() const {
    return active;
}

BonusType Bonus::getType() const {
    return type;
}