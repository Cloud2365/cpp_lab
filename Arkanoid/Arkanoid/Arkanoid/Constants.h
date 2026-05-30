#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

const int PADDLE_WIDTH = 80;
const int PADDLE_HEIGHT = 15;
const float PADDLE_SPEED = 400.0f;

const float BALL_RADIUS = 8.0f;
const float BALL_SPEED = 300.0f;



const float BLOCK_PROBABILITIES[] = {
    0.6f,   // NORMAL
    0.1f,   // INDESTRUCTIBLE
    0.1f,   // BONUS
    0.1f,   // SPEED_BOOST
    0.1f    // HEALTH
};
const int BLOCK_TYPES_COUNT = 5;

const int BLOCK_ROWS = 5;
const int BLOCK_COLS = 10;
const float BLOCK_WIDTH = 70.0f;
const float BLOCK_HEIGHT = 30.0f;
const float BLOCK_OFFSET_X = (WINDOW_WIDTH - BLOCK_COLS * BLOCK_WIDTH) / 2;
const float BLOCK_OFFSET_Y = 50.0f;

const int INITIAL_LIVES = 3;
const int SCORE_PER_HIT = 10;

const float BONUS_FALL_SPEED = 150.0f;

#endif