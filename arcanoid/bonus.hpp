#pragma once
#include "common.hpp"

class Bonus {
protected:
    SDL_Rect rect;
    bool active;

public:
    Bonus(int x, int y);
    virtual ~Bonus() = default;

    virtual void applyEffect() = 0;
    virtual void render(SDL_Renderer* renderer) const = 0;

    void update();
    bool isActive() const;
    const SDL_Rect& getRect() const;
};

class ExtraBallBonus : public Bonus {
public:
    ExtraBallBonus(int x, int y);
    void applyEffect() override;
    void render(SDL_Renderer* renderer) const override;
};

class PaddleSizeBonus : public Bonus {
public:
    PaddleSizeBonus(int x, int y);
    void applyEffect() override;
    void render(SDL_Renderer* renderer) const override;
};

class BallSpeedBonus : public Bonus {
public:
    BallSpeedBonus(int x, int y);
    void applyEffect() override;
    void render(SDL_Renderer* renderer) const override;
};

class StickyPaddleBonus : public Bonus {
public:
    StickyPaddleBonus(int x, int y);
    void applyEffect() override;
    void render(SDL_Renderer* renderer) const override;
};

class SafetyBottomBonus : public Bonus {
public:
    SafetyBottomBonus(int x, int y);
    void applyEffect() override;
    void render(SDL_Renderer* renderer) const override;
};

extern std::vector<std::unique_ptr<Bonus>> bonuses;
void updateBonuses();