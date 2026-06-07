#include "BombBonus.h"
#include "Grid.h"
#include "Constants.h"
#include <cstdlib>

BombBonus::BombBonus(float x, float y, int targetRow, int targetCol)
    : active(true), y(y), targetRow(targetRow), targetCol(targetCol) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(x, y);
}

void BombBonus::apply(Grid& grid) {
    std::vector<std::pair<int, int>> nonEmpty;
    for (int r = 0; r < GRID_SIZE; r++) {
        for (int c = 0; c < GRID_SIZE; c++) {
            if (grid.getCell(r, c) != -1) {
                nonEmpty.push_back({ r, c });
            }
        }
    }

    bool targetIncluded = false;
    for (const auto& cell : nonEmpty) {
        if (cell.first == targetRow && cell.second == targetCol) {
            targetIncluded = true;
            break;
        }
    }
    if (!targetIncluded && grid.getCell(targetRow, targetCol) != -1) {
        nonEmpty.push_back({ targetRow, targetCol });
    }

    int destroyed = 0;
    while (destroyed < BOMB_DESTROY_COUNT && !nonEmpty.empty()) {
        int idx = rand() % nonEmpty.size();
        grid.setCell(nonEmpty[idx].first, nonEmpty[idx].second, -1);
        nonEmpty.erase(nonEmpty.begin() + idx);
        destroyed++;
    }
}

