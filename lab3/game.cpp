#include "game.h"
#include <SDL.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include "repaint_bonus.h"
#include "bomb_bonus.h"

std::vector<std::unique_ptr<Bonus>> pendingBonuses;
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
std::vector<std::vector<Cell>> grid(GRID_SIZE, std::vector<Cell>(GRID_SIZE));
int selectedX = -1, selectedY = -1;
bool isAnimating = false;
float animationOffset[GRID_SIZE][GRID_SIZE] = {};
float animationSpeed = 4.0f;
int lastClickX = -1, lastClickY = -1;
Uint32 lastClickTime = 0;

void initGrid() {
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            grid[y][x].color = rand() % COLOR_COUNT;
            grid[y][x].toBeDestroyed = false;
        }
    }
}

void renderGrid() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            grid[y][x].render(renderer, x, y, animationOffset[y][x]);

            for (const auto& bonus : pendingBonuses) {
                if (bonus->targetX == x && bonus->targetY == y) {
                    bonus->render(renderer, x, y);
                    break;
                }
            }
        }
    }

    SDL_RenderPresent(renderer);
}

void swapCells(int x1, int y1, int x2, int y2) {
    std::swap(grid[y1][x1], grid[y2][x2]);
}

bool isAdjacent(int x1, int y1, int x2, int y2) {
    return (abs(x1 - x2) + abs(y1 - y2)) == 1;
}

void findMatches() {
    bool visited[GRID_SIZE][GRID_SIZE] = {};

    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            if (grid[y][x].color < 0 || visited[y][x]) continue;

            std::vector<std::pair<int, int>> cluster;
            int targetColor = grid[y][x].color;

            std::queue<std::pair<int, int>> q;
            q.push({ x, y });
            visited[y][x] = true;

            while (!q.empty()) {
                auto current = q.front(); q.pop();
                int cx = current.first;
                int cy = current.second;
                cluster.push_back(current);

                for (int dy = -1; dy <= 1; ++dy) {
                    for (int dx = -1; dx <= 1; ++dx) {
                        if (abs(dx) + abs(dy) != 1) continue;
                        int nx = cx + dx;
                        int ny = cy + dy;
                        if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE && !visited[ny][nx]) {
                            if (grid[ny][nx].color == targetColor) {
                                visited[ny][nx] = true;
                                q.push({ nx, ny });
                            }
                        }
                    }
                }
            }

            if (cluster.size() >= 3) {
                for (const auto& cell : cluster) {
                    grid[cell.second][cell.first].toBeDestroyed = true;
                }

                if (cluster.size() > 3) {
                    auto center = cluster[rand() % cluster.size()];
                    if (rand() % 2 == 0) {
                        pendingBonuses.push_back(std::make_unique<RepaintBonus>(center.first, center.second, targetColor));
                    }
                    else {
                        pendingBonuses.push_back(std::make_unique<BombBonus>(center.first, center.second, targetColor));
                    }
                }
            }
        }
    }
}

void destroyMatches() {
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            if (grid[y][x].toBeDestroyed) {
                grid[y][x].color = -1;
                grid[y][x].toBeDestroyed = false;
            }
        }
    }
}

void applyGravity() {
    isAnimating = false;

    for (int x = 0; x < GRID_SIZE; ++x) {
        for (int y = GRID_SIZE - 1; y >= 0; --y) {
            if (grid[y][x].color == -1) {
                for (int ny = y - 1; ny >= 0; --ny) {
                    if (grid[ny][x].color != -1) {
                        grid[y][x].color = grid[ny][x].color;
                        grid[ny][x].color = -1;
                        animationOffset[y][x] = -CELL_SIZE * (y - ny);
                        isAnimating = true;
                        break;
                    }
                }
            }
        }

        for (int y = 0; y < GRID_SIZE; ++y) {
            if (grid[y][x].color == -1) {
                grid[y][x].color = rand() % COLOR_COUNT;
                animationOffset[y][x] = -CELL_SIZE * (GRID_SIZE - y);
                isAnimating = true;
            }
        }
    }
}

void applyBonuses() {
    for (auto& bonus : pendingBonuses) {
        bonus->apply(grid);
    }
    pendingBonuses.clear();
}

void updateAnimations() {
    bool stillAnimating = false;
    for (int y = 0; y < GRID_SIZE; ++y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            if (animationOffset[y][x] != 0.0f) {
                if (animationOffset[y][x] < 0) {
                    animationOffset[y][x] += animationSpeed;
                    if (animationOffset[y][x] > 0) animationOffset[y][x] = 0;
                }
                else {
                    animationOffset[y][x] -= animationSpeed;
                    if (animationOffset[y][x] < 0) animationOffset[y][x] = 0;
                }
                stillAnimating = true;
            }
        }
    }
    isAnimating = stillAnimating;
}

void handleDoubleClick(int x, int y) {
    for (auto it = pendingBonuses.begin(); it != pendingBonuses.end(); ++it) {
        if ((*it)->targetX == x && (*it)->targetY == y) {
            (*it)->onDoubleClick(grid);
            pendingBonuses.erase(it);
            renderGrid();
            SDL_Delay(300);
            break;
        }
    }
}
