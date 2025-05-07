#pragma once
#include <SDL.h>

enum class TileColor {
    None,
    Red,
    Green,
    Blue,
    Yellow
};

class Tile {
public:
    Tile();
    Tile(TileColor color, int row, int col);

    void update(float deltaTime);
    void render(SDL_Renderer* renderer, int tileSize);

    void setFalling(bool value);
    void setRemoving(bool value);
    bool isEmpty() const;

    TileColor getColor() const;
    void setColor(TileColor color);

    int row, col;

private:
    TileColor color;
    bool falling;
    bool removing;
    float alpha; // для анимации исчезновения
};
