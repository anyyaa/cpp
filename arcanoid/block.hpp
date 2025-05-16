#pragma once
#include "common.hpp"

class Block {
protected:
    SDL_Rect rect;
    int hitsLeft;
    bool active;

public:
    Block(int x, int y, int w, int h, int hits);
    virtual ~Block() = default;

    virtual void onHit();
    virtual void render(SDL_Renderer* renderer) const = 0;
    virtual void spawnBonus() const {}

    bool isActive() const;
    const SDL_Rect& getRect() const;
    int getHitsLeft() const;
};

class StandardBlock : public Block {
public:
    StandardBlock(int x, int y);
    void render(SDL_Renderer* renderer) const override;
    void onHit() override;
};

class BonusBlock : public Block {
public:
    BonusBlock(int x, int y);
    void render(SDL_Renderer* renderer) const override;
    void onHit() override;
    void spawnBonus() const override;
};

class StrongBlock : public Block {
public:
    StrongBlock(int x, int y, int hits);
    void render(SDL_Renderer* renderer) const override;
    void onHit() override;
};

class IndestructibleBlock : public Block {
public:
    IndestructibleBlock(int x, int y);
    void render(SDL_Renderer* renderer) const override;
    void onHit() override;
};

extern std::vector<std::unique_ptr<Block>> blocks;