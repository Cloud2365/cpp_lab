#include "HealthBlock.h"
#include "Constants.h"
#include "Ball.h"

HealthBlock::HealthBlock() : health(2) {
    shape.setSize(sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT));
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(255, 165, 0));
}

void HealthBlock::draw(sf::RenderWindow& window) {
    if (health > 0) window.draw(shape);
}

void HealthBlock::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

sf::FloatRect HealthBlock::getBounds() const {
    return shape.getGlobalBounds();
}

bool HealthBlock::hit() {
    health--;
    return health <= 0;
}

int HealthBlock::getHealth() const {
    return health;
}

void HealthBlock::onHit(Ball& ball) {

}

int HealthBlock::getScore() const {
    return SCORE_PER_HIT;
}