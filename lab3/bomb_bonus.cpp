#include "bomb_bonus.h"
#include <algorithm>
#include <vector>

BombBonus::BombBonus(int x, int y, int clr) {
    targetX = x;
    targetY = y;
    color = clr;
}

void BombBonus::apply(std::vector<std::vector<Cell>>& grid) {
    std::vector<std::pair<int, int>> allCells;
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            allCells.push_back({ x, y });
        }
    }
    std::random_shuffle(allCells.begin(), allCells.end());
    for (int j = 0; j < 5 && j < (int)allCells.size(); ++j) {
        int tx = allCells[j].first;
        int ty = allCells[j].second;
        grid[ty][tx].toBeDestroyed = true;
    }
}

void BombBonus::render(SDL_Renderer* renderer, int x, int y) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    int cx = x * CELL_SIZE + CELL_SIZE / 2;
    int cy = y * CELL_SIZE + CELL_SIZE / 2;
    int r = CELL_SIZE / 6;
    SDL_Rect bonusMark = { cx - r, cy - r, r * 2, r * 2 };
    SDL_RenderFillRect(renderer, &bonusMark);
}

void BombBonus::onDoubleClick(std::vector<std::vector<Cell>>& grid) {
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int nx = targetX + dx;
            int ny = targetY + dy;
            if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE) {
                grid[ny][nx].toBeDestroyed = true;
            }
        }
    }
}