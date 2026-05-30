#pragma once
#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>


enum BlockType {
    NORMAL = 0,
    INDESTRUCTIBLE,
    BONUS,
    SPEED_BOOST,
    HEALTH
};

class Block {
public:
    Block(BlockType type, int health = 1);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    sf::FloatRect getBounds() const;
    static BlockType getRandomBlockType();
    bool hit();  // возвращает true если блок уничтожен
    bool isIndestructible() const;
    bool hasBonus() const;
    bool givesSpeedBoost() const;
    int getHealth() const;
    BlockType getType() const;
    void takeDamage();

private:
    BlockType type;
    int health;
    sf::RectangleShape shape;
};

#endif