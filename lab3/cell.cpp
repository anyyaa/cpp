#include "cell.h"
#include "constants.h"
#include <SDL.h>

void Cell::render(SDL_Renderer* renderer, int x, int y, float offset) const {
    SDL_Rect rect = {
        x * CELL_SIZE,
        static_cast<int>(y * CELL_SIZE + offset),
        CELL_SIZE - 2,
        CELL_SIZE - 2
    };

    switch (color) {
    case 0: SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break;
    case 1: SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); break;
    case 2: SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); break;
    case 3: SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); break;
    case 4: SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); break;
    case 5: SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); break;
    case 6: SDL_SetRenderDrawColor(renderer, 128, 64, 255, 255); break;
    }
    SDL_RenderFillRect(renderer, &rect);
}