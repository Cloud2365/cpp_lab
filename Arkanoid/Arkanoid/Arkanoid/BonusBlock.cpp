#include "BonusBlock.h"
#include "Constants.h"
#include "Ball.h"
#include "Game.h"
#include "BonusFactory.h"

BonusBlock::BonusBlock() : health(1) {
    shape.setSize(sf::Vector2f(BLOCK_WIDTH, BLOCK_HEIGHT));
    shape.setOutlineThickness(1);
    shape.setOutlineColor(sf::Color::Black);
    shape.setFillColor(sf::Color::Yellow);
}

void BonusBlock::draw(sf::RenderWindow& window) {
    if (health > 0) window.draw(shape);
}

void BonusBlock::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

sf::FloatRect BonusBlock::getBounds() const {
    return shape.getGlobalBounds();
}

bool BonusBlock::hit() {
    health--;
    return health <= 0;
}

int BonusBlock::getHealth() const {
    return health;
}

void BonusBlock::onHit(Ball& ball, Game& game) {
    if (ball.getVelocity().y > 0) {
        sf::FloatRect bounds = getBounds();
        game.addBonus(BonusFactory::createRandomBonus(
            bounds.left + bounds.width / 2,
            bounds.top + bounds.height
        ));
    }
}

int BonusBlock::getScore() const {
    return SCORE_PER_HIT;
}