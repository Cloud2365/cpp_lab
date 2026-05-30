#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Bonus.h"

class Game {

public:
    Game();
    void run();

private:
    void processEvents();
    void update(float dt);
    void render();
    void spawnBlocks();
    void checkCollisions();
    void applyBonus(BonusType type);

    sf::RenderWindow window;
    Ball ball;
    Paddle paddle;
    std::vector<Block> blocks;
    std::vector<Bonus> bonuses;
    int score;
    int lives;
    bool stickyMode;   // прилипание м€ча к каретке
    bool extraBottom;
    bool extraBottomUsed;
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;
};

#endif