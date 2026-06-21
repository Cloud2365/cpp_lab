#include "IndestructibleBlock.h"
#include "Constants.h"
#include "Ball.h"
#include "Game.h"

IndestructibleBlock::IndestructibleBlock() {
    shape.setSize(sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT));
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color(100, 100, 100));
}

void IndestructibleBlock::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void IndestructibleBlock::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

sf::FloatRect IndestructibleBlock::getBounds() const {
    return shape.getGlobalBounds();
}

bool IndestructibleBlock::hit() {
    return false;
}

int IndestructibleBlock::getHealth() const {
    return 999;
}

void IndestructibleBlock::onHit(Ball& ball, Game& game) {
   
}

int IndestructibleBlock::getScore() const {
    return 0;
}