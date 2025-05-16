#include "bonus.hpp"
#include "game.hpp"
#include "common.hpp"

Bonus::Bonus(int x, int y) : rect{ x, y, BONUS_SIZE, BONUS_SIZE }, active(true) {}

void Bonus::update() { rect.y += 2; }
bool Bonus::isActive() const { return active; }
const SDL_Rect& Bonus::getRect() const { return rect; }

ExtraBallBonus::ExtraBallBonus(int x, int y) : Bonus(x, y) {}
void ExtraBallBonus::applyEffect() {
    if (!balls.empty()) {
        Ball newBall = balls[0];
        newBall.x += 10;
        newBall.y += 10;
        newBall.vx = -balls[0].vx;
        newBall.vy = balls[0].vy;
        newBall.attached = false;
        balls.push_back(newBall);
    }
}
void ExtraBallBonus::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

PaddleSizeBonus::PaddleSizeBonus(int x, int y) : Bonus(x, y) {}
void PaddleSizeBonus::applyEffect() {
    paddle.w += 30;
    if (paddle.w > SCREEN_WIDTH) paddle.w = SCREEN_WIDTH;
}
void PaddleSizeBonus::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

BallSpeedBonus::BallSpeedBonus(int x, int y) : Bonus(x, y) {}
void BallSpeedBonus::applyEffect() {
    for (auto& ball : balls) {
        ball.speed += 1.5f;
    }
    speedBonusBouncesLeft = 5;
}
void BallSpeedBonus::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

StickyPaddleBonus::StickyPaddleBonus(int x, int y) : Bonus(x, y) {}
void StickyPaddleBonus::applyEffect() {
    sticky = true;
    stickyHitsLeft = 3;
}
void StickyPaddleBonus::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

SafetyBottomBonus::SafetyBottomBonus(int x, int y) : Bonus(x, y) {}
void SafetyBottomBonus::applyEffect() {
    safetyBottomActive = true;
}
void SafetyBottomBonus::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 128, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void updateBonuses() {
    for (auto it = bonuses.begin(); it != bonuses.end(); ) {
        if (!(*it)->isActive()) {
            it = bonuses.erase(it);
            continue;
        }

        (*it)->update();

        if (SDL_HasIntersection(&(*it)->getRect(), &paddle)) {
            (*it)->applyEffect();
            it = bonuses.erase(it);
        }
        else if ((*it)->getRect().y > SCREEN_HEIGHT) {
            it = bonuses.erase(it);
        }
        else {
            ++it;
        }
    }
}