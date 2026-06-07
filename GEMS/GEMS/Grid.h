#pragma once
#ifndef GRID_H
#define GRID_H


#include <SFML/Graphics.hpp>
#include <vector>
#include <queue>  
#include "Constants.h"

class Grid {
private:
	std::vector<std::vector<int>> grid;


public:
	Grid();
	void draw(sf::RenderWindow& window);
	void initRandom();
	void swap(int r1, int c1, int r2, int c2);
	void processMatches(bool refill = true);
	void applyGravity();
	void addNewGems();
	int getCell(int row, int col) const;
	void setCell(int row, int col, int value);
	bool hasMatches();

};
#endif

