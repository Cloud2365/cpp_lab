#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>
#include <memory>
#include "Constants.h"

class Bonus;

class Grid {
public:
    Grid();
    void initRandom();
    void draw(sf::RenderWindow& window);
    void swap(int r1, int c1, int r2, int c2);
    void processMatches(bool refill = true);
    void applyGravity();
    void addNewGems();
    int getCell(int row, int col) const;
    void setCell(int row, int col, int value);
    bool hasMatches();
    void addBonus(std::unique_ptr<Bonus> bonus);
    void updateBonuses(float dt, const sf::FloatRect& paddleBounds);
    void drawBonuses(sf::RenderWindow& window);
    bool hasActiveBonuses() const;

private:
    std::vector<std::vector<int>> grid;
    std::vector<std::unique_ptr<Bonus>> bonuses;
};

#endif

