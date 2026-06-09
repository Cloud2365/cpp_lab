#include "Game.h"
#include "Constants.h"
#include "BlockFactory.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid") {
    window.setFramerateLimit(60);
    score = 0;
    lives = INITIAL_LIVES;
    stickyMode = false;
    extraBottom = false;
    extraBottomUsed = false;


    spawnBlocks();
}

void Game::spawnBlocks() {
    blocks.clear();
    for (int row = 0; row < BLOCK_ROWS; ++row) {
        for (int col = 0; col < BLOCK_COLS; ++col) {
            float x = BLOCK_OFFSET_X + col * BLOCK_WIDTH;
            float y = BLOCK_OFFSET_Y + row * BLOCK_HEIGHT;

            auto block = BlockFactory::createRandomBlock();
            block->setPosition(x, y);
            blocks.push_back(std::move(block));
        }
    }
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        if (dt > 0.033f) dt = 0.033f; 
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            if (ball.isStuck()) ball.release();
        }
    }
}

void Game::update(float dt) {
    // Управление кареткой
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        paddle.moveLeft(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        paddle.moveRight(dt);

    // Мяч
    if (ball.isStuck()) {
        ball.stickToPaddle(paddle.getPosition().x, paddle.getPosition().y - PADDLE_HEIGHT / 2);
    }
    else {
        ball.update(dt);
    }

    // Проверка выхода мяча за нижнюю границу
    if (ball.getBounds().top + ball.getBounds().height > WINDOW_HEIGHT) {
        if (extraBottom && !extraBottomUsed) {
            extraBottomUsed = true;
            ball.reboundY();
            ball.setPosition(ball.getBounds().left + ball.getBounds().width / 2, WINDOW_HEIGHT - 20);
        }
        else {
            lives--;
            if (lives <= 0) {
                window.close();
                return;
            }
 
            ball.stickToPaddle(paddle.getPosition().x, paddle.getPosition().y - PADDLE_HEIGHT / 2);
        }
    }

    // Обновление бонусов
    for (auto it = bonuses.begin(); it != bonuses.end(); ) {
        (*it)->update(dt);
        if (!(*it)->isActive()) {
            it = bonuses.erase(it);
        }
        else {
            if ((*it)->getBounds().intersects(paddle.getBounds())) {
                (*it)->apply(*this);
                it = bonuses.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    checkCollisions();
}

void Game::checkCollisions() {
    // Стены
    sf::FloatRect ballBounds = ball.getBounds();
    if (ballBounds.left < 0 || ballBounds.left + ballBounds.width > WINDOW_WIDTH) {
        ball.reboundX();
        ballBounds = ball.getBounds();
    }
    if (ballBounds.top < 0) {
        ball.reboundY();
        ballBounds = ball.getBounds();
    }

    // Каретка
    if (!ball.isStuck() && ballBounds.intersects(paddle.getBounds())) {
        float hitPos = ballBounds.left + ballBounds.width / 2 - paddle.getBounds().left;
        float paddleWidth = paddle.getBounds().width;
        float angle = (hitPos / paddleWidth - 0.5f) * 1.2f;
        sf::Vector2f vel = ball.getVelocity();
        float speed = std::sqrt(vel.x * vel.x + vel.y * vel.y);
        vel.x = angle * speed;
        vel.y = -std::sqrt(std::max(0.0f, speed * speed - vel.x * vel.x));
        ball.setVelocity(vel.x, vel.y);
        if (stickyMode && !ball.isStuck()) {
            ball.stickToPaddle(paddle.getPosition().x, paddle.getPosition().y - PADDLE_HEIGHT / 2);
        }
    }

    // Блоки
    for (int i = 0; i < blocks.size(); ) {
        sf::FloatRect blockBounds = blocks[i]->getBounds();
        ballBounds = ball.getBounds();

        if (ballBounds.intersects(blockBounds)) {
            float overlapLeft = ballBounds.left + ballBounds.width - blockBounds.left;
            float overlapRight = blockBounds.left + blockBounds.width - ballBounds.left;
            float overlapTop = ballBounds.top + ballBounds.height - blockBounds.top;
            float overlapBottom = blockBounds.top + blockBounds.height - ballBounds.top;
            float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

            if (minOverlap == overlapTop || minOverlap == overlapBottom) {
                ball.reboundY();
            }
            else {
                ball.reboundX();
            }

            blocks[i]->onHit(ball, *this);

            if (blocks[i]->hit()) {
                score += blocks[i]->getScore();
                blocks.erase(blocks.begin() + i);
                continue;
            }
            ++i;
        }
        else {
            ++i;
        }
    }
}

void Game::addBonus(std::unique_ptr<Bonus> bonus) {
    bonuses.push_back(std::move(bonus));
}

void Game::enlargePaddle() {
    paddle.setWidth(PADDLE_WIDTH * 1.5f);
}

void Game::shrinkPaddle() {
    paddle.setWidth(PADDLE_WIDTH * 0.7f);
}

void Game::speedUpBall() {
    sf::Vector2f vel = ball.getVelocity();
    vel *= 1.3f;
    ball.setVelocity(vel.x, vel.y);
}

void Game::slowDownBall() {
    sf::Vector2f vel = ball.getVelocity();
    vel *= 0.7f;
    ball.setVelocity(vel.x, vel.y);
}

void Game::enableStickyMode() {
    stickyMode = true;
}

void Game::enableExtraBottom() {
    extraBottom = true;
    extraBottomUsed = false;
}

void Game::randomizeBallTrajectory() {
    ball.randomizeVelocity(BALL_SPEED);
}

Paddle& Game::getPaddle() {
    return paddle;
}

Ball& Game::getBall() {
    return ball;
}

void Game::render() {
    window.clear(sf::Color::Black);

    ball.draw(window);
    paddle.draw(window);

    for (auto& block : blocks) {
        block->draw(window);
    }

    for (auto& bonus : bonuses) {
        bonus->draw(window);
    }

 

    window.display();
}
