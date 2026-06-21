#include "ExtraLifeBottomBonus.h"
#include "Constants.h"
#include "Game.h"

ExtraLifeBottomBonus::ExtraLifeBottomBonus(float x, float yPos) : y(yPos), active(true) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color(0, 255, 255));  // æ¸ëòûé
    shape.setPosition(x, yPos);
}

void ExtraLifeBottomBonus::apply(Game& game) {
    game.enableExtraBottom();
}

void ExtraLifeBottomBonus::update(float dt) {
    y += BONUS_FALL_SPEED * dt;
    shape.setPosition(shape.getPosition().x, y);
    if (y > WINDOW_HEIGHT) active = false;
}

void ExtraLifeBottomBonus::draw(sf::RenderWindow& window) {
    if (active) window.draw(shape);
}

sf::FloatRect ExtraLifeBottomBonus::getBounds() const {
    return shape.getGlobalBounds();
}

bool ExtraLifeBottomBonus::isActive() const {
    return active;
}

void ExtraLifeBottomBonus::setPosition(float x, float y) {
    shape.setPosition(x, y);
}