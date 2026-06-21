#include "SpeedBoostBlock.h"
#include "Constants.h"
#include "Ball.h"
#include "Game.h"
#include <cmath>

SpeedBoostBlock::SpeedBoostBlock() : health(1) {
    shape.setSize(sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT));
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color::Cyan);
}

void SpeedBoostBlock::draw(sf::RenderWindow& window) {
    if (health > 0) window.draw(shape);
}

void SpeedBoostBlock::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

sf::FloatRect SpeedBoostBlock::getBounds() const {
    return shape.getGlobalBounds();
}

bool SpeedBoostBlock::hit() {
    health--;
    return health <= 0;
}

int SpeedBoostBlock::getHealth() const {
    return health;
}

void SpeedBoostBlock::onHit(Ball& ball, Game& game) {
    sf::Vector2f vel = ball.getVelocity();
    vel *= 1.2f;
    ball.setVelocity(vel.x, vel.y);
}

int SpeedBoostBlock::getScore() const {
    return SCORE_PER_HIT;
}