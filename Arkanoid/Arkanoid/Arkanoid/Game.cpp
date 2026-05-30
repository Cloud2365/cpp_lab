// Game.cpp (основная логика)
#include "Game.h"
#include "Constants.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arkanoid") {
    //window.setFramerateLimit(60);
    srand(static_cast<unsigned>(time(nullptr)));
    score = 0;
    lives = INITIAL_LIVES;
    stickyMode = false;
    extraBottom = false;
    extraBottomUsed = false;


   /* // Вариант 1: Arial.ttf (с заглавной буквы)
    font.loadFromFile("D:/games/arial.ttf");

    scoreText.setFont(font);
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    livesText.setFont(font);
    livesText.setCharacterSize(20);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(WINDOW_WIDTH - 100, 10);
    */

    spawnBlocks();
}

void Game::spawnBlocks() {
    blocks.clear();
    for (int row = 0; row < BLOCK_ROWS; ++row) {
        for (int col = 0; col < BLOCK_COLS; ++col) {
            float x = BLOCK_OFFSET_X + col * BLOCK_WIDTH;
            float y = BLOCK_OFFSET_Y + row * BLOCK_HEIGHT;

            // Случайный тип блока
            BlockType type = Block::getRandomBlockType();  // функция из Block.cpp
            int health = (type == HEALTH) ? 2 : 1;
            blocks.emplace_back(type, health);
            blocks.back().setPosition(x, y);
        }
    }
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
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
    // Управление кареткой с учётом dt
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        paddle.moveLeft(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        paddle.moveRight(dt);

    // Если мяч прилип к каретке, следуем за ней
    if (ball.isStuck()) {
        ball.stickToPaddle(paddle.getPosition().x, paddle.getPosition().y - PADDLE_HEIGHT / 2);
    }
    else {
        //std::cout << "Updating ball, dt=" << dt << std::endl;
        ball.update(dt);
    }

    // Проверка выхода мяча за нижнюю границу
    if ( ball.getBounds().top + ball.getBounds().height > WINDOW_HEIGHT) {
        if (extraBottom && !extraBottomUsed) {
            extraBottomUsed = true;
            // дно отражает мяч
            ball.reboundY();
            ball.setPosition(ball.getBounds().left + ball.getBounds().width / 2, WINDOW_HEIGHT - 20);
        }
        else {
            lives--;
            if (lives <= 0) {
                window.close();
                return;
            }
            // сброс мяча на каретку
            ball.stickToPaddle(paddle.getPosition().x, paddle.getPosition().y - PADDLE_HEIGHT / 2);
        }
    }

    // Обновление бонусов
    for (auto it = bonuses.begin(); it != bonuses.end(); ) {
        it->update(dt);
        if (!it->isActive()) {
            it = bonuses.erase(it);
        }
        else {
            if (it->getBounds().intersects(paddle.getBounds())) {
                applyBonus(it->getType());
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
    if (ball.getBounds().left < 0 || ball.getBounds().left + ball.getBounds().width > WINDOW_WIDTH)
        ball.reboundX();
    if (ball.getBounds().top < 0)
        ball.reboundY();

    // Каретка
    if (!ball.isStuck() && ball.getBounds().intersects(paddle.getBounds())) {
        float hitPos = ball.getBounds().left + ball.getBounds().width / 2 - paddle.getBounds().left;
        float paddleWidth = paddle.getBounds().width;
        float angle = (hitPos / paddleWidth - 0.5f) * 1.2f; // от -0.6 до 0.6
        sf::Vector2f vel = ball.getVelocity();
        float speed = sqrt(vel.x * vel.x + vel.y * vel.y);
        vel.x = angle * speed;
        vel.y = -sqrt(speed * speed - vel.x * vel.x);
        ball.setVelocity(vel.x, vel.y);
        if (stickyMode && !ball.isStuck()) {
            ball.stickToPaddle(paddle.getPosition().x, paddle.getPosition().y - PADDLE_HEIGHT / 2);
        }
    }

    // Блоки
// Блоки
    for (int i = 0; i < blocks.size(); ) {
        sf::FloatRect ballBounds = ball.getBounds();
        sf::FloatRect blockBounds = blocks[i].getBounds();

        if (ballBounds.intersects(blockBounds)) {
            // Вычисляем перекрытие по каждой стороне
            float overlapLeft = ballBounds.left + ballBounds.width - blockBounds.left;
            float overlapRight = blockBounds.left + blockBounds.width - ballBounds.left;
            float overlapTop = ballBounds.top + ballBounds.height - blockBounds.top;
            float overlapBottom = blockBounds.top + blockBounds.height - ballBounds.top;

            float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

            if (minOverlap == overlapTop || minOverlap == overlapBottom) {
                ball.reboundY(); // удар сверху/снизу
            }
            else {
                ball.reboundX(); // удар слева/справа
            }

            if (!blocks[i].isIndestructible()) {
                if (blocks[i].givesSpeedBoost()) {
                    sf::Vector2f vel = ball.getVelocity();
                    vel *= 1.2f;
                    ball.setVelocity(vel.x, vel.y);
                }
                if (blocks[i].hasBonus() && ball.getVelocity().y > 0) {
                    int bonusType = rand() % 7;
                    bonuses.emplace_back(static_cast<BonusType>(bonusType),
                        blocks[i].getBounds().left + blocks[i].getBounds().width / 2,
                        blocks[i].getBounds().top + blocks[i].getBounds().height);
                }
                if (blocks[i].hit()) {
                    score += SCORE_PER_HIT;
                    blocks.erase(blocks.begin() + i);
                    continue;
                }
            }
            ++i;
        }
        else {
            ++i;
        }
    }
}

void Game::applyBonus(BonusType type) {
    switch (type) {
    case ENLARGE_PADDLE:
        paddle.setWidth(PADDLE_WIDTH * 1.5f);
        break;
    case SHRINK_PADDLE:
        paddle.setWidth(PADDLE_WIDTH * 0.7f);
        break;
    case SPEED_UP_BALL:
    {
        sf::Vector2f vel = ball.getVelocity();
        vel *= 1.3f;
        ball.setVelocity(vel.x, vel.y);
    }
    break;
    case SLOW_DOWN_BALL:
    {
        sf::Vector2f vel = ball.getVelocity();
        vel *= 0.7f;
        ball.setVelocity(vel.x, vel.y);
    }
    break;
    case STICKY_PADDLE:
        stickyMode = true;
        break;
    case EXTRA_LIFE_BOTTOM:
        extraBottom = true;
        extraBottomUsed = false;
        break;
    case RANDOM_TRAJECTORY:
        ball.randomizeVelocity(BALL_SPEED);
        break;
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    ball.draw(window);
    paddle.draw(window);
    for (auto& block : blocks) block.draw(window);
    for (auto& bonus : bonuses) bonus.draw(window);
    // обновление текста счёта и жизней
    //scoreText.setString("Score: " + std::to_string(score));
    //livesText.setString("Lives: " + std::to_string(lives));
    //window.draw(scoreText);
    //window.draw(livesText);
    window.display();
}