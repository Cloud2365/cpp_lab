#include "Game.h"
#include "Constants.h"


Game::Game(): window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "GEMS")
    , selectedRow(-1)
    , selectedCol(-1)
    , waitingForSecond(false) {
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            int mouseX = event.mouseButton.x;
            int mouseY = event.mouseButton.y;
            int col = mouseX / CELL_SIZE;
            int row = mouseY / CELL_SIZE;

            if (row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE) {
                if (!waitingForSecond) {
                    if (grid.getCell(row, col) != -1) {
                        selectedRow = row;
                        selectedCol = col;
                        waitingForSecond = true;
                    }
                }
                else {
                    if (grid.getCell(row, col) != -1 && std::abs(selectedRow - row) + std::abs(selectedCol - col) == 1) {
                        grid.swap(selectedRow, selectedCol, row, col);
                        if (grid.hasMatches()) {
                            grid.processMatches(true);
                        }
                        else {
                            grid.swap(selectedRow, selectedCol, row, col);
                        }
                    }
                    waitingForSecond = false;
                    selectedRow = -1;
                    selectedCol = -1;
                }
            }
        }
    }
}



void Game::render() {
    window.clear(sf::Color::Black);
    grid.draw(window);

    if (waitingForSecond && selectedRow != -1 && selectedCol != -1) {
        sf::RectangleShape highlight(sf::Vector2f(CELL_SIZE, CELL_SIZE));
        highlight.setPosition(selectedCol * CELL_SIZE, selectedRow * CELL_SIZE);
        highlight.setFillColor(sf::Color(255, 255, 255, 100)); 
        window.draw(highlight);
    }

    window.display();
}

