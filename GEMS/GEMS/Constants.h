#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

const int WINDOW_SIZE = 800; // размер окна
const int GRID_SIZE = 8; // размер поля в клетках
const int CELL_SIZE = WINDOW_SIZE / GRID_SIZE; // размер клетки
const int BONUS_RADIUS = 3;				// радиус бонуса
const int BOMB_DESTROY_COUNT = 5;      // сколько клеток уничтожает бомба
const int RECOLOR_TARGETS = 3;         // сколько клеток перекрашивает бонус
const int BONUS_PROBABILITY_PERCENT = 30; // шанс выпадения бонуса

#endif

