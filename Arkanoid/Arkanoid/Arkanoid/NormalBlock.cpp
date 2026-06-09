#include "NormalBlock.h"
#include "Constants.h"
#include "Ball.h"
#include "Game.h"

NormalBlock::NormalBlock() : health(1) {
    shape.setSize(sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT));
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color::Red);
}

void NormalBlock::draw(sf::RenderWindow& window) {
    if (health > 0) window.draw(shape);
}

void NormalBlock::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

sf::FloatRect NormalBlock::getBounds() const {
    return shape.getGlobalBounds();
}

bool NormalBlock::hit() {
    health--;
    return health <= 0;
}

int NormalBlock::getHealth() const {
    return health;
}

void NormalBlock::onHit(Ball& ball, Game& game) {
   
}

int NormalBlock::getScore() const {
    return SCORE_PER_HIT;
}