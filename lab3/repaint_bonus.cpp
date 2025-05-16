#include "repaint_bonus.h"
#include <algorithm>
#include <vector>

RepaintBonus::RepaintBonus(int x, int y, int clr) {
    targetX = x;
    targetY = y;
    color = clr;
}

void RepaintBonus::apply(std::vector<std::vector<Cell>>& grid) {
    std::vector<std::pair<int, int>> candidates;
    for (int dy = -3; dy <= 3; ++dy) {
        for (int dx = -3; dx <= 3; ++dx) {
            int nx = targetX + dx;
            int ny = targetY + dy;
            if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE) {
                if (!(abs(dx) + abs(dy) == 1)) {
                    candidates.push_back({ nx, ny });
                }
            }
        }
    }

    std::random_shuffle(candidates.begin(), candidates.end());
    grid[targetY][targetX].color = color;
    for (int j = 0; j < std::min(2, (int)candidates.size()); ++j) {
        int tx = candidates[j].first;
        int ty = candidates[j].second;
        grid[ty][tx].color = color;
    }
}

void RepaintBonus::render(SDL_Renderer* renderer, int x, int y) const {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    int cx = x * CELL_SIZE + CELL_SIZE / 2;
    int cy = y * CELL_SIZE + CELL_SIZE / 2;
    int r = CELL_SIZE / 6;
    SDL_Rect bonusMark = { cx - r, cy - r, r * 2, r * 2 };
    SDL_RenderFillRect(renderer, &bonusMark);
}

void RepaintBonus::onDoubleClick(std::vector<std::vector<Cell>>& grid) {
    std::vector<std::pair<int, int>> neighbors;
    for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
            int nx = targetX + dx;
            int ny = targetY + dy;
            if ((dx != 0 || dy != 0) && nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE) {
                neighbors.push_back({ nx, ny });
            }
        }
    }
    std::random_shuffle(neighbors.begin(), neighbors.end());

    for (int j = 0; j < std::min(3, (int)neighbors.size()); ++j) {
        int nx = neighbors[j].first;
        int ny = neighbors[j].second;
        grid[ny][nx].color = color;
    }
}
