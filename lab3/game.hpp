#pragma once
#include "gameboard.hpp"
#include <SDL.h>

class Game {
public:
    Game();
    ~Game();

    bool init();
    void run();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    GameBoard* board;

    const int SCREEN_WIDTH = 800;
    const int SCREEN_HEIGHT = 600;
    const int TILE_SIZE = 40;

    void handleEvents();
    void update(float deltaTime);
    void render();
};
