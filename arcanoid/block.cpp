#include "block.hpp"
#include "bonus.hpp"
#include "common.hpp"

Block::Block(int x, int y, int w, int h, int hits)
    : rect{ x, y, w, h }, hitsLeft(hits), active(true) {}

void Block::onHit() {
    hitsLeft--;
    if (hitsLeft <= 0) active = false;
}

bool Block::isActive() const { return active; }
const SDL_Rect& Block::getRect() const { return rect; }
int Block::getHitsLeft() const { return hitsLeft; }

StandardBlock::StandardBlock(int x, int y) : Block(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, 1) {}
void StandardBlock::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
void StandardBlock::onHit() {
    Block::onHit();
    score += 10;
}

BonusBlock::BonusBlock(int x, int y) : Block(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, 1) {}
void BonusBlock::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
void BonusBlock::onHit() {
    Block::onHit();
    score += 10;
    spawnBonus();
}
void BonusBlock::spawnBonus() const {
    std::unique_ptr<Bonus> bonus;

    if (!firstBonusDropped) {
        bonus = std::make_unique<ExtraBallBonus>(rect.x + rect.w / 2, rect.y + rect.h);
        firstBonusDropped = true;
    }
    else {
        int type = rand() % 5;
        switch (type) {
        case 0: bonus = std::make_unique<ExtraBallBonus>(rect.x + rect.w / 2, rect.y + rect.h); break;
        case 1: bonus = std::make_unique<PaddleSizeBonus>(rect.x + rect.w / 2, rect.y + rect.h); break;
        case 2: bonus = std::make_unique<BallSpeedBonus>(rect.x + rect.w / 2, rect.y + rect.h); break;
        case 3: bonus = std::make_unique<StickyPaddleBonus>(rect.x + rect.w / 2, rect.y + rect.h); break;
        case 4: bonus = std::make_unique<SafetyBottomBonus>(rect.x + rect.w / 2, rect.y + rect.h); break;
        }
    }

    bonuses.push_back(std::move(bonus));
}

StrongBlock::StrongBlock(int x, int y, int hits) : Block(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, hits) {}
void StrongBlock::render(SDL_Renderer* renderer) const {
    if (hitsLeft == 3)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    else if (hitsLeft == 2)
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255);
    else if (hitsLeft == 1)
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
void StrongBlock::onHit() {
    hitsLeft--;
    if (hitsLeft <= 0) {
        active = false;
        score += 10;
    }
    else {
        score += 5;
    }
}

IndestructibleBlock::IndestructibleBlock(int x, int y) : Block(x, y, BLOCK_WIDTH, BLOCK_HEIGHT, -1) {}
void IndestructibleBlock::render(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &rect);
}
void IndestructibleBlock::onHit() {
    // Ничего не делаем - блок неразрушимый
}