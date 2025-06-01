#pragma once
#include <SDL.h>
#include "constants.h"

struct Cell {
    int color;
    bool toBeDestroyed = false;

    virtual ~Cell() = default;
    virtual void render(SDL_Renderer* renderer, int x, int y, float offset) const;
};