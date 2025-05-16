#define SDL_MAIN_HANDLED
#include "common.hpp"
#include "game.hpp"
#include "render.hpp"
#include "ball.hpp"
#include "bonus.hpp"
#include "block.hpp"

// В main.cpp после #include, но до функций
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Rect paddle;
int score = 0;
bool sticky = false;
int stickyHitsLeft = 0;
bool safetyBottomActive = false;
bool firstBonusDropped = false;
int speedBonusBouncesLeft = 0;

std::vector<Ball> balls;
std::vector<std::unique_ptr<Block>> blocks;
std::vector<std::unique_ptr<Bonus>> bonuses;

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Arkanoid - Score: 0",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    srand((unsigned)time(0));
    initGame();

    bool quit = false;
    while (!quit) {
        processInput(quit);
        updateBalls();
        updateBonuses();
        render();

        std::string title = "Arkanoid - Score: " + std::to_string(score);
        SDL_SetWindowTitle(window, title.c_str());

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}