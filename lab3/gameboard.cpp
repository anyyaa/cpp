#include "gameboard.hpp"
#include <cstdlib>
#include <ctime>
#include <queue>
#include <set>
#include <iostream>

GameBoard::GameBoard(int rows, int cols, int tileSize)
    : rows(rows), cols(cols), tileSize(tileSize)
{
    grid.resize(rows, std::vector<Tile>(cols));
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    generateRandomTiles();
}

void GameBoard::generateRandomTiles() {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            TileColor color = static_cast<TileColor>((std::rand() % 4) + 1); // 1 to 4 colors
            grid[row][col] = Tile(color, row, col);
        }
    }
}

void GameBoard::update(float deltaTime) {
    // ќбновление состо€ни€ плиток
    for (auto& row : grid)
        for (auto& tile : row)
            tile.update(deltaTime);

    // ѕрименение гравитации (плитки, которые удалены, должны "упасть")
    dropTiles();
}

void GameBoard::render(SDL_Renderer* renderer) {
    for (auto& row : grid)
        for (auto& tile : row)
            tile.render(renderer, tileSize);
}

void GameBoard::handleClick(int x, int y) {
    int col = x / tileSize;
    int row = y / tileSize;

    if (!isInBounds(row, col)) return;

    TileColor clickedColor = grid[row][col].getColor();
    std::vector<std::pair<int, int>> connectedTiles;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

    floodFill(row, col, clickedColor, connectedTiles, visited);

    if (connectedTiles.size() >= 3) {
        for (const auto& tilePos : connectedTiles) {
            int r = tilePos.first;
            int c = tilePos.second;
            grid[r][c].setRemoving(true);
        }
    }
}

void GameBoard::reset() {
    for (auto& row : grid) {
        for (auto& tile : row) {
            tile.setRemoving(false);
            tile.setFalling(false);
        }
    }
    generateRandomTiles();
}

bool GameBoard::isInBounds(int row, int col) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

void GameBoard::floodFill(int row, int col, TileColor color, std::vector<std::pair<int, int>>& outGroup, std::vector<std::vector<bool>>& visited) {
    if (!isInBounds(row, col)) return;
    if (visited[row][col]) return;
    if (grid[row][col].getColor() != color) return;

    visited[row][col] = true;
    outGroup.push_back({ row, col });

    const int directions[4][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    for (const auto& dir : directions) {
        floodFill(row + dir[0], col + dir[1], color, outGroup, visited);
    }
}

void GameBoard::checkAndRemoveMatches() {
    // Ётот метод можно использовать дл€ удалени€ плиток, если количество одинаковых плиток более 3
    // ” нас это теперь будет происходить в handleClick, так что этот метод пока не нужен
}

void GameBoard::dropTiles() {
    // ѕлитки должны падать вниз после удалени€, если есть пустые места
    for (int col = 0; col < cols; ++col) {
        // ѕройти по столбцу
        for (int row = rows - 1; row >= 0; --row) {
            if (grid[row][col].isEmpty()) {
                // Ќайти плитку выше
                for (int k = row - 1; k >= 0; --k) {
                    if (!grid[k][col].isEmpty()) {
                        // ѕлитка падает вниз
                        grid[row][col] = grid[k][col];
                        grid[row][col].setRemoving(false);
                        grid[row][col].setFalling(true);
                        grid[k][col] = Tile(TileColor::None, k, col);
                        break;
                    }
                }
            }
        }
    }
}
