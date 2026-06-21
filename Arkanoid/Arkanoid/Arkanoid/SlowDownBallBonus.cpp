#include "SlowDownBallBonus.h"
#include "Constants.h"
#include "Game.h"

SlowDownBallBonus::SlowDownBallBonus(float x, float yPos) : y(yPos), active(true) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color::Magenta);
    shape.setPosition(x, yPos);
}

void SlowDownBallBonus::apply(Game& game) {
    game.slowDownBall();
}

void SlowDownBallBonus::update(float dt) {
    y += BONUS_FALL_SPEED * dt;
    shape.setPosition(shape.getPosition().x, y);
    if (y > WINDOW_HEIGHT) active = false;
}

void SlowDownBallBonus::draw(sf::RenderWindow& window) {
    if (active) window.draw(shape);
}

sf::FloatRect SlowDownBallBonus::getBounds() const {
    return shape.getGlobalBounds();
}

bool SlowDownBallBonus::isActive() const {
    return active;
}

void SlowDownBallBonus::setPosition(float x, float y) {
    shape.setPosition(x, y);
}