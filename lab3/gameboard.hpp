#pragma once
#include "tile.hpp"
#include <vector>
#include <SDL.h>

class GameBoard {
public:
    GameBoard(int rows, int cols, int tileSize);

    void update(float deltaTime);
    void render(SDL_Renderer* renderer);

    void handleClick(int x, int y);
    void reset();

private:
    int rows, cols, tileSize;
    std::vector<std::vector<Tile>> grid;

    void generateRandomTiles();
    void checkAndRemoveMatches();
    void dropTiles();
    bool isInBounds(int row, int col);
    void floodFill(int row, int col, TileColor color, std::vector<std::pair<int, int>>& outGroup, std::vector<std::vector<bool>>& visited);
};
