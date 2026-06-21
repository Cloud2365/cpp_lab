#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <random>
#include <chrono>

// Размеры окна
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 600;

// Каретка
constexpr int PADDLE_WIDTH = 80;
constexpr int PADDLE_HEIGHT = 15;
constexpr float PADDLE_SPEED = 400.0f;

// Мяч
constexpr float BALL_RADIUS = 8.0f;
constexpr float BALL_SPEED = 300.0f;

// Блоки
constexpr int BLOCK_ROWS = 5;
constexpr int BLOCK_COLS = 10;
constexpr float BLOCK_WIDTH = 70.0f;
constexpr float BLOCK_HEIGHT = 30.0f;
constexpr float BLOCK_OFFSET_X = (WINDOW_WIDTH - BLOCK_COLS * BLOCK_WIDTH) / 2;
constexpr float BLOCK_OFFSET_Y = 50.0f;


const float BLOCK_PROBABILITIES[] = {
    0.6f,   // NORMAL
    0.1f,   // INDESTRUCTIBLE
    0.1f,   // BONUS
    0.1f,   // SPEED_BOOST
    0.1f    // HEALTH
};

// Игровые параметры
constexpr int INITIAL_LIVES = 3;
constexpr int SCORE_PER_HIT = 10;
constexpr float BONUS_FALL_SPEED = 150.0f;

// Генератор случайных чисел (глобальный для всего проекта)
inline std::mt19937& getRng() {
    static std::mt19937 rng(static_cast<unsigned>(
        std::chrono::steady_clock::now().time_since_epoch().count()
        ));
    return rng;
}

#endif

