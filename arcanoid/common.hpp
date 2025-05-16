#pragma once

#include <SDL.h>
#include <vector>
#include <memory>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>

// Константы игры
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PADDLE_WIDTH = 100;
const int PADDLE_HEIGHT = 20;
const int BALL_SIZE = 10;
const int BLOCK_WIDTH = 60;
const int BLOCK_HEIGHT = 20;
const int ROWS = 6;
const int COLS = 10;
const int BONUS_SIZE = 20;

// Глобальные переменные
extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Rect paddle;
extern int score;
extern bool sticky;
extern int stickyHitsLeft;
extern bool safetyBottomActive;
extern bool firstBonusDropped;
extern int speedBonusBouncesLeft;

// Структуры данных
struct Ball {
    float x, y;
    float vx, vy;
    float speed;
    bool attached;
};

extern std::vector<Ball> balls;