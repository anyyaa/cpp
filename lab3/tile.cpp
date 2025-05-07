#include "tile.hpp"

Tile::Tile() : color(TileColor::None), row(0), col(0), falling(false), removing(false), alpha(255.0f) {}

Tile::Tile(TileColor color, int row, int col)
    : color(color), row(row), col(col), falling(false), removing(false), alpha(255.0f) {}

void Tile::update(float deltaTime) {
    if (removing) {
        alpha -= 300 * deltaTime;
        if (alpha < 0) {
            alpha = 0;
            color = TileColor::None;
            removing = false;
        }
    }
}

void Tile::render(SDL_Renderer* renderer, int tileSize) {
    if (color == TileColor::None)
        return;

    SDL_Rect rect = { col * tileSize, row * tileSize, tileSize, tileSize };

    Uint8 r = 0, g = 0, b = 0;
    switch (color) {
    case TileColor::Red: r = 255; break;
    case TileColor::Green: g = 255; break;
    case TileColor::Blue: b = 255; break;
    case TileColor::Yellow: r = 255; g = 255; break;
    default: break;
    }

    SDL_SetRenderDrawColor(renderer, r, g, b, static_cast<Uint8>(alpha));
    SDL_RenderFillRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // рамка
    SDL_RenderDrawRect(renderer, &rect);
}

void Tile::setFalling(bool value) {
    falling = value;
}

void Tile::setRemoving(bool value) {
    removing = value;
    if (value) alpha = 255.0f;
}

bool Tile::isEmpty() const {
    return color == TileColor::None;
}

TileColor Tile::getColor() const {
    return color;
}

void Tile::setColor(TileColor newColor) {
    color = newColor;
    alpha = 255.0f;
}
