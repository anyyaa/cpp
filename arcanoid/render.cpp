#include "game.hpp"
#include "render.hpp"
#include "common.hpp"
#include <SDL.h>

void render() {
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);  
    SDL_RenderClear(renderer);

    for (const auto& block : blocks) {
        if (!block.active) continue;
        switch (block.type) {
        case STANDARD:
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); break; 
        case BONUS:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); break; 
        case STRONG_2:
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); break; 
        case STRONG_3:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break; 
        case INDESTRUCTIBLE:
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); break;
        }

        SDL_RenderFillRect(renderer, &block.rect);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);

    for (const auto& ball : balls) {
        SDL_Rect ballRect = { (int)ball.x, (int)ball.y, BALL_SIZE, BALL_SIZE };
        SDL_RenderFillRect(renderer, &ballRect);
    }

    for (const auto& bonus : bonuses) {
        if (!bonus.active) continue;

        switch (bonus.type) {
        case 0:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break; 
        case 1:
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); break; 
        case 2:
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); break; 
        case 3:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); break; 
        case 4:
            SDL_SetRenderDrawColor(renderer, 128, 0, 255, 255); break; 

        }

        SDL_RenderFillRect(renderer, &bonus.rect);
    }

    SDL_RenderPresent(renderer);
}
