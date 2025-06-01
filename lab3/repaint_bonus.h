#pragma once
#include "bonus.h"

class RepaintBonus : public Bonus {
public:
    RepaintBonus(int x, int y, int clr);
    void apply(std::vector<std::vector<Cell>>& grid) override;
    void render(SDL_Renderer* renderer, int x, int y) const override;
    void onDoubleClick(std::vector<std::vector<Cell>>& grid) override;
};