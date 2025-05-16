#pragma once
#include <SDL.h>
#include <vector>
#include <memory>
#include "cell.h"
#include "bonus.h"
#include "constants.h"

extern std::vector<std::unique_ptr<Bonus>> pendingBonuses;
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern std::vector<std::vector<Cell>> grid;
extern int selectedX, selectedY;
extern bool isAnimating;
extern float animationOffset[GRID_SIZE][GRID_SIZE];
extern float animationSpeed;
extern int lastClickX, lastClickY;
extern Uint32 lastClickTime;

void initGrid();
void renderGrid();
void swapCells(int x1, int y1, int x2, int y2);
bool isAdjacent(int x1, int y1, int x2, int y2);
void findMatches();
void destroyMatches();
void applyGravity();
void applyBonuses();
void updateAnimations();
void handleDoubleClick(int x, int y);