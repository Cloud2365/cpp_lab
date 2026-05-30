
#include "Block.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>

Block::Block(BlockType t, int hp) : type(t), health(hp) {
    shape.setSize(sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT));
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    switch (type) {
    case INDESTRUCTIBLE:
        shape.setFillColor(sf::Color(100, 100, 100));
        break;
    case BONUS:
        shape.setFillColor(sf::Color::Yellow);
        break;
    case SPEED_BOOST:
        shape.setFillColor(sf::Color::Cyan);
        break;
    case HEALTH:
        shape.setFillColor(sf::Color(255, 165, 0));
        break;
    default:
        shape.setFillColor(sf::Color::Red);
        break;
    }
}

void Block::draw(sf::RenderWindow& window) {
    if (health > 0 || type == INDESTRUCTIBLE)
        window.draw(shape);
}

void Block::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

sf::FloatRect Block::getBounds() const {
    return shape.getGlobalBounds();
}

bool Block::hit() {
    if (type == INDESTRUCTIBLE) return false;
    health--;
    return (health <= 0);
}

bool Block::isIndestructible() const {
    return type == INDESTRUCTIBLE;
}

bool Block::hasBonus() const {
    return type == BONUS;
}

bool Block::givesSpeedBoost() const {
    return type == SPEED_BOOST;
}

int Block::getHealth() const {
    return health;
}

BlockType Block::getType() const {
    return type;
}

void Block::takeDamage() {
    if (type != INDESTRUCTIBLE) health--;
}

BlockType Block::getRandomBlockType() {
    float r = static_cast<float>(rand()) / RAND_MAX;
    float accum = 0.0f;
    for (int i = 0; i < 5; ++i) {
        accum += BLOCK_PROBABILITIES[i];
        if (r < accum) return static_cast<BlockType>(i);
    }
    return NORMAL;
}