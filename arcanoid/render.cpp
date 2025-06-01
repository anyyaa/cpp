#include "render.hpp"
#include "common.hpp"
#include "block.hpp"
#include "bonus.hpp"
void render() {
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);
    SDL_RenderClear(renderer);

    for (const auto& block : blocks) {
        if (block->isActive()) {
            block->render(renderer);
        }
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);

    for (const auto& ball : balls) {
        SDL_Rect ballRect = { (int)ball.x, (int)ball.y, BALL_SIZE, BALL_SIZE };
        SDL_RenderFillRect(renderer, &ballRect);
    }

    for (const auto& bonus : bonuses) {
        if (bonus->isActive()) {
            bonus->render(renderer);
        }
    }

    SDL_RenderPresent(renderer);
}