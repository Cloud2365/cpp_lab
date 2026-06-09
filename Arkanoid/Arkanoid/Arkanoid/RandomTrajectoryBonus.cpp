#include "RandomTrajectoryBonus.h"
#include "Constants.h"
#include "Game.h"

RandomTrajectoryBonus::RandomTrajectoryBonus(float x, float yPos) : y(yPos), active(true) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color(128, 0, 128));  // фиолетовый
    shape.setPosition(x, yPos);
}

void RandomTrajectoryBonus::apply(Game& game) {
    game.randomizeBallTrajectory();
}

void RandomTrajectoryBonus::update(float dt) {
    y += BONUS_FALL_SPEED * dt;
    shape.setPosition(shape.getPosition().x, y);
    if (y > WINDOW_HEIGHT) active = false;
}

void RandomTrajectoryBonus::draw(sf::RenderWindow& window) {
    if (active) window.draw(shape);
}

sf::FloatRect RandomTrajectoryBonus::getBounds() const {
    return shape.getGlobalBounds();
}

bool RandomTrajectoryBonus::isActive() const {
    return active;
}

void RandomTrajectoryBonus::setPosition(float x, float y) {
    shape.setPosition(x, y);
}