#pragma once
#include <SDL.h>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int PADDLE_WIDTH = 100;
const int PADDLE_HEIGHT = 20;
const int BALL_SIZE = 10;
const int BLOCK_WIDTH = 60;
const int BLOCK_HEIGHT = 20;
const int ROWS = 6;
const int COLS = 10;

enum BlockType {
    STANDARD,
    BONUS,
    STRONG_2,
    STRONG_3,
    INDESTRUCTIBLE
};

struct Block {
    SDL_Rect rect;
    BlockType type;
    int hitsLeft;
    bool active;
    float opacity;
};

struct Ball {
    float x, y;
    float vx, vy;
    float speed;
    bool attached;
};

struct Bonus {
    SDL_Rect rect;
    int type;
    bool active;
};

extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Rect paddle;
extern std::vector<Ball> balls;
extern std::vector<Block> blocks;
extern std::vector<Bonus> bonuses;
extern bool sticky;
extern int stickyHitsLeft;
extern int score;
extern bool extraBallGiven;
extern bool safetyBottomActive;
