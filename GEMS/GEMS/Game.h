#pragma once
#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Grid.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void render();

    sf::RenderWindow window;
    Grid grid;
    int selectedRow, selectedCol;
    bool waitingForSecond;
};

#endif

