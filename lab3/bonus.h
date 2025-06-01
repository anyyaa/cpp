#pragma once
#include <vector>
#include "cell.h"

class Bonus {
public:
    virtual ~Bonus() = default;
    virtual void apply(std::vector<std::vector<Cell>>& grid) = 0;
    virtual void render(SDL_Renderer* renderer, int x, int y) const = 0;
    virtual void onDoubleClick(std::vector<std::vector<Cell>>& grid) = 0;

    int targetX, targetY;
    int color;
};