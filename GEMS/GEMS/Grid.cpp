#include "Grid.h"
#include "Bonus.h"
 

Grid::Grid() {
	grid.resize(GRID_SIZE, std::vector<int>(GRID_SIZE, 0));
	initRandom();

}
static const sf::Color COLORS[] = {
	sf::Color::Blue,
	sf::Color::Green,
	sf::Color::Red,
	sf::Color::Yellow,
	sf::Color::Cyan,
	sf::Color::Magenta,
	sf::Color(255, 128, 0),
	sf::Color(128, 0, 128)
};

void Grid::initRandom() {
	for (int row = 0; row < GRID_SIZE; row++) {
		for (int col = 0; col < GRID_SIZE; col++) {
			grid[row][col] = rand() % 8;
		}
	}
    processMatches(true);

}
void Grid::draw(sf::RenderWindow& window) {
    
	for (int row = 0; row < GRID_SIZE; row++) {
		for (int col = 0; col < GRID_SIZE; col++) {

			sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
			cell.setPosition(col * CELL_SIZE, row * CELL_SIZE);
            int type = grid[row][col];
            if (type >= 0 && type < 8) {
                cell.setFillColor(COLORS[type]);
            }
            else {
                cell.setFillColor(sf::Color(80, 80, 80));
            }
			window.draw(cell);
		}

	}
}
void Grid::swap(int r1, int c1, int r2, int c2) {
	int temp = grid[r1][c1];
	grid[r1][c1] = grid[r2][c2];
	grid[r2][c2] = temp;

}

void Grid::processMatches(bool refill) {
    bool changed = true;
    while (changed) {
        changed = false;

        std::vector<std::vector<bool>> visited(GRID_SIZE, std::vector<bool>(GRID_SIZE, false));
        std::vector<std::vector<bool>> toRemove(GRID_SIZE, std::vector<bool>(GRID_SIZE, false));

        for (int row = 0; row < GRID_SIZE; row++) {
            for (int col = 0; col < GRID_SIZE; col++) {
                if (!visited[row][col] && grid[row][col] != -1) {
                    int color = grid[row][col];
                    std::vector<std::pair<int, int>> cluster;
                    std::queue<std::pair<int, int>> q;

                    q.push({ row, col });
                    visited[row][col] = true;

                    int dr[] = { 1, -1, 0, 0 };
                    int dc[] = { 0, 0, 1, -1 };

                    while (!q.empty()) {
                        auto [r, c] = q.front(); q.pop();
                        cluster.push_back({ r, c });

                        for (int i = 0; i < 4; i++) {
                            int nr = r + dr[i];
                            int nc = c + dc[i];
                            if (nr >= 0 && nr < GRID_SIZE && nc >= 0 && nc < GRID_SIZE &&
                                !visited[nr][nc] && grid[nr][nc] == color) {
                                visited[nr][nc] = true;
                                q.push({ nr, nc });
                            }
                        }
                    }

                    if (cluster.size() >= 3) {
                        changed = true;
                        Bonus::tryDrop(cluster, *this);
                        for (auto& p : cluster) {
                            toRemove[p.first][p.second] = true;
                        }
                    }
                }
            }
        }

        if (!changed) break;

        for (int row = 0; row < GRID_SIZE; row++) {
            for (int col = 0; col < GRID_SIZE; col++) {
                if (toRemove[row][col]) {
                    grid[row][col] = -1;
                }
            }
        }

        applyGravity();

        if (refill) {
            addNewGems();
        }
    }
}

void Grid::applyGravity() {
    for (int col = 0; col < GRID_SIZE; col++) {
        std::vector<int> vals;
        for (int row = 0; row < GRID_SIZE; row++) {
            if (grid[row][col] != -1) {
                vals.push_back(grid[row][col]);
            }
        }
        while (vals.size() < GRID_SIZE) {
            vals.insert(vals.begin(), -1);
        }
        for (int row = 0; row < GRID_SIZE; row++) {
            grid[row][col] = vals[row];
        }
    }
}
void Grid::addNewGems() {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == -1) {
                grid[row][col] = rand() % 8;
            }
        }
    }
}
int Grid::getCell(int row, int col) const {
    return grid[row][col];
}

void Grid::setCell(int row, int col, int value) {
    grid[row][col] = value;
}

