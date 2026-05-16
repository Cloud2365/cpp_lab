#pragma once
#ifndef BONUS_H
#define BONUS_H

#include <vector>
#include <utility>

class Grid;

class Bonus {
public:
    // Основной метод: попытаться выбросить бонус из кластера
    static void tryDrop(const std::vector<std::pair<int, int>>& cluster, Grid& grid);

private:
    static void recolor(const std::pair<int, int>& target, int originalColor, Grid& grid);
    static void bomb(Grid& grid);
};

#endif

