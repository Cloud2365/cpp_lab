#include "SpeedUpBallBonus.h"
#include "Constants.h"
#include "Game.h"

SpeedUpBallBonus::SpeedUpBallBonus(float x, float yPos) : y(yPos), active(true) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color::Cyan);
    shape.setPosition(x, yPos);
}

void SpeedUpBallBonus::apply(Game& game) {
    game.speedUpBall();
}

void SpeedUpBallBonus::update(float dt) {
    y += BONUS_FALL_SPEED * dt;
    shape.setPosition(shape.getPosition().x, y);
    if (y > WINDOW_HEIGHT) active = false;
}

void SpeedUpBallBonus::draw(sf::RenderWindow& window) {
    if (active) window.draw(shape);
}

sf::FloatRect SpeedUpBallBonus::getBounds() const {
    return shape.getGlobalBounds();
}

bool SpeedUpBallBonus::isActive() const {
    return active;
}

void SpeedUpBallBonus::setPosition(float x, float y) {
    shape.setPosition(x, y);
}