#include "game.hpp"
#include "render.hpp"
#include "common.hpp"
#include <SDL.h>

void render() {
    SDL_SetRenderDrawColor(renderer, 173, 216, 230, 255);  // Фон
    SDL_RenderClear(renderer);

    // Отображение блоков
    for (const auto& block : blocks) {
        if (!block.active) continue;
        switch (block.type) {
        case STANDARD:
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); break; // жёлтый
        case BONUS:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); break; // зелёный
        case STRONG_2:
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); break; // оранжевый
        case STRONG_3:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break; // красный
        case INDESTRUCTIBLE:
            SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255); break;
        }

        SDL_RenderFillRect(renderer, &block.rect);
    }

    // Отображение панели
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);

    // Отображение мячей
    for (const auto& ball : balls) {
        SDL_Rect ballRect = { (int)ball.x, (int)ball.y, BALL_SIZE, BALL_SIZE };
        SDL_RenderFillRect(renderer, &ballRect);
    }

    // Отображение бонусов
    for (const auto& bonus : bonuses) {
        if (!bonus.active) continue;

        // Цвет бонуса зависит от его типа
        switch (bonus.type) {
        case 0:
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); break; // красный для второго шарика
        case 1:
            SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255); break; // бирюзовый для расширения панели
        case 2:
            SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); break; // оранжевый для увеличения скорости
        case 3:
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); break; // зелёный для прилипания
        case 4:
            SDL_SetRenderDrawColor(renderer, 128, 0, 255, 255); break; // фиолетовый

        }

        SDL_RenderFillRect(renderer, &bonus.rect);
    }

    SDL_RenderPresent(renderer);
}