#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <queue>
#include <memory>
#include "game.h"
#include <SDL.h>



int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("GEMS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    srand((unsigned)time(0));

    initGrid();
    findMatches();
    destroyMatches();
    applyGravity();
    applyBonuses();

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;

            if (!isAnimating && e.type == SDL_MOUSEBUTTONDOWN) {
                int x = e.button.x / CELL_SIZE;
                int y = e.button.y / CELL_SIZE;

                Uint32 now = SDL_GetTicks();
                if (x == lastClickX && y == lastClickY && now - lastClickTime < DOUBLE_CLICK_DELAY) {
                    handleDoubleClick(x, y);
                    lastClickX = lastClickY = -1;
                    lastClickTime = 0;
                    continue;
                }
                else {
                    lastClickX = x;
                    lastClickY = y;
                    lastClickTime = now;
                }

                if (selectedX == -1) {
                    selectedX = x;
                    selectedY = y;
                }
                else {
                    if (isAdjacent(x, y, selectedX, selectedY)) {
                        swapCells(x, y, selectedX, selectedY);
                        findMatches();
                        destroyMatches();
                        applyGravity();
                    }
                    selectedX = selectedY = -1;
                }
            }
        }

        if (isAnimating) {
            updateAnimations();
        }
        else {
            findMatches();
            destroyMatches();
            applyGravity();
        }

        renderGrid();
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}