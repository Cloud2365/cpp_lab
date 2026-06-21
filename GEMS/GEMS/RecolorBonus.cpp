#include "RecolorBonus.h"
#include "Grid.h"
#include "Constants.h"
#include <set>
#include <cstdlib>

RecolorBonus::RecolorBonus(int color, float x, float y, int targetRow, int targetCol)
    : originalColor(color), active(true), y(y), targetRow(targetRow), targetCol(targetCol) {
    shape.setSize(sf::Vector2f(20, 20));
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x, y);
}

void RecolorBonus::apply(Grid& grid) {
    std::set<std::pair<int, int>> toRecolor;
    toRecolor.insert({ targetRow, targetCol });

    std::vector<std::pair<int, int>> farCandidates;
    for (int dr = -BONUS_RADIUS; dr <= BONUS_RADIUS; dr++) {
        for (int dc = -BONUS_RADIUS; dc <= BONUS_RADIUS; dc++) {
            if (std::abs(dr) + std::abs(dc) > BONUS_RADIUS) continue;
            int nr = targetRow + dr;
            int nc = targetCol + dc;
            if (nr >= 0 && nr < GRID_SIZE && nc >= 0 && nc < GRID_SIZE) {
                if (std::abs(dr) + std::abs(dc) > 1) {
                    farCandidates.push_back({ nr, nc });
                }
            }
        }
    }

    int needed = RECOLOR_TARGETS - 1;
    while (needed > 0 && !farCandidates.empty()) {
        int idx = rand() % farCandidates.size();
        toRecolor.insert(farCandidates[idx]);
        farCandidates.erase(farCandidates.begin() + idx);
        needed--;
    }

    for (const auto& cell : toRecolor) {
        grid.setCell(cell.first, cell.second, originalColor);
    }
}

void RecolorBonus::update(float dt) {
    y += BONUS_FALL_SPEED * dt;
    shape.setPosition(shape.getPosition().x, y);
    if (y > WINDOW_HEIGHT) active = false;
}

void RecolorBonus::draw(sf::RenderWindow& window) {
    if (active) window.draw(shape);
}

sf::FloatRect RecolorBonus::getBounds() const {
    return shape.getGlobalBounds();
}

bool RecolorBonus::isActive() const {
    return active;
}

void RecolorBonus::setPosition(float x, float y) {
    shape.setPosition(x, y);
}

