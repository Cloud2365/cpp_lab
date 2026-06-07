#include "Bonus.h"
#include "Grid.h"
#include "Constants.h"
#include <cstdlib>
#include <set>
#include <vector>


void Bonus::tryDrop(const std::vector<std::pair<int,int>>& cluster, Grid& grid) {

    if (rand() % 100 >= BONUS_PROBABILITY_PERCENT) return;

    int srcIdx = rand() % cluster.size();
    int srcRow = cluster[srcIdx].first;
    int srcCol = cluster[srcIdx].second;
    int originalColor = grid.getCell(srcRow, srcCol);

    std::vector<std::pair<int,int>> candidates;
    for (int dr = -BONUS_RADIUS; dr <= BONUS_RADIUS; dr++) {
        for (int dc = -BONUS_RADIUS; dc <= BONUS_RADIUS; dc++) {
            if (std::abs(dr) + std::abs(dc) > BONUS_RADIUS) continue;
            int nr = srcRow + dr;
            int nc = srcCol + dc;
            if (nr >= 0 && nr < GRID_SIZE && nc >= 0 && nc < GRID_SIZE) {
                candidates.push_back({nr, nc});
            }
        }
    }
    if (candidates.empty()) return;

    int targetIdx = rand() % candidates.size();
    std::pair<int,int> target = candidates[targetIdx];

    int bonusType = rand() % 2;
    if (bonusType == 0) {
        recolor(target, originalColor, grid);
    }
    else {
        bomb(grid, target);   
    }
}

void Bonus::recolor(const std::pair<int,int>& target, int originalColor, Grid& grid) {
    std::set<std::pair<int,int>> toRecolor;
    toRecolor.insert(target);

    std::vector<std::pair<int,int>> farCandidates;
    for (int dr = -BONUS_RADIUS; dr <= BONUS_RADIUS; dr++) {
        for (int dc = -BONUS_RADIUS; dc <= BONUS_RADIUS; dc++) {
            if (std::abs(dr) + std::abs(dc) > BONUS_RADIUS) continue;
            int nr = target.first + dr;
            int nc = target.second + dc;
            if (nr >= 0 && nr < GRID_SIZE && nc >= 0 && nc < GRID_SIZE) {
                if (std::abs(dr) + std::abs(dc) > 1) {
                    farCandidates.push_back({nr, nc});
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

    for (auto& cell : toRecolor) {
        grid.setCell(cell.first, cell.second, originalColor);
    }
}

void Bonus::bomb(Grid& grid, const std::pair<int, int>& target) {
    std::vector<std::pair<int, int>> nonEmpty;
    for (int r = 0; r < GRID_SIZE; r++) {
        for (int c = 0; c < GRID_SIZE; c++) {
            if (grid.getCell(r, c) != -1) {
                nonEmpty.push_back({ r, c });
            }
        }
    }

    // Убедимся, что target есть в списке (добавим, если нет)
    bool targetIncluded = false;
    for (const auto& cell : nonEmpty) {
        if (cell == target) {
            targetIncluded = true;
            break;
        }
    }
    if (!targetIncluded && grid.getCell(target.first, target.second) != -1) {
        nonEmpty.push_back(target);
    }

    int destroyed = 0;
    while (destroyed < BOMB_DESTROY_COUNT && !nonEmpty.empty()) {
        int idx = rand() % nonEmpty.size();
        grid.setCell(nonEmpty[idx].first, nonEmpty[idx].second, -1);
        nonEmpty.erase(nonEmpty.begin() + idx);
        destroyed++;
    }
}

