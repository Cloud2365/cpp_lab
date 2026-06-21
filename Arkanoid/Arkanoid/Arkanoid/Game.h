#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Bonus.h"

class Game {
public:
    Game();
    void run();

    // Методы для бонусов
    void addBonus(std::unique_ptr<Bonus> bonus);
    void enlargePaddle();
    void shrinkPaddle();
    void speedUpBall();
    void slowDownBall();
    void enableStickyMode();
    void enableExtraBottom();
    void randomizeBallTrajectory();

    Paddle& getPaddle();
    Ball& getBall();

private:
    void processEvents();
    void update(float dt);
    void render();
    void spawnBlocks();
    void checkCollisions();

    sf::RenderWindow window;
    Ball ball;
    Paddle paddle;
    std::vector<std::unique_ptr<Block>> blocks;
    std::vector<std::unique_ptr<Bonus>> bonuses;
    int score;
    int lives;
    bool stickyMode;
    bool extraBottom;
    bool extraBottomUsed;
    sf::Font font;
    sf::Text scoreText;
    sf::Text livesText;
};

#endif