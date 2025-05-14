#include "common.hpp"
#include <cstdlib>

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Rect paddle;
std::vector<Ball> balls;
std::vector<Block> blocks;
std::vector<Bonus> bonuses;
bool sticky = false;
int stickyHitsLeft = 0;
int score = 0;
bool extraBallGiven = false;
bool safetyBottomActive = false;

void initGame() {
    paddle = { SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2, SCREEN_HEIGHT - 40, PADDLE_WIDTH, PADDLE_HEIGHT };
    balls.clear();
    Ball ball = { (float)(paddle.x + PADDLE_WIDTH / 2.0f), (float)(paddle.y - BALL_SIZE), 0.0f, -1.0f, 5.0f, true };
    balls.push_back(ball);
    blocks.clear();

    const int GAP = 2;
    const int blockWidth = (SCREEN_WIDTH - (COLS - 1) * GAP) / COLS;
    const int blockHeight = 25;

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            Block block;
            block.rect = { j * (blockWidth + GAP), i * (blockHeight + GAP) + 50, blockWidth, blockHeight };
            int type = rand() % 10;
            if (type < 4) block.type = STANDARD, block.hitsLeft = 1;
            else if (type == 4) block.type = BONUS, block.hitsLeft = 1;
            else if (type == 5) block.type = STRONG_2, block.hitsLeft = 2;
            else if (type == 6) block.type = STRONG_3, block.hitsLeft = 3;
            else block.type = INDESTRUCTIBLE, block.hitsLeft = -1;

            block.active = true;
            block.opacity = 255;
            blocks.push_back(block);
        }
    }
}

void processInput(bool& quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) quit = true;
        if (e.type == SDL_MOUSEMOTION) paddle.x = e.motion.x - paddle.w / 2;
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            for (auto& ball : balls) {
                if (ball.attached) {
                    ball.vx = 0;
                    ball.vy = -1;
                    ball.attached = false;
                }
            }
        }
    }
    if (paddle.x < 0) paddle.x = 0;
    if (paddle.x + paddle.w > SCREEN_WIDTH) paddle.x = SCREEN_WIDTH - paddle.w;
}
