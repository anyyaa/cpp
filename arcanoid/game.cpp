#include "game.hpp"
#include "ball.hpp"
#include "bonus.hpp"
#include "render.hpp"
#include "common.hpp"
#include "block.hpp"

void initGame() {
    paddle = { SCREEN_WIDTH / 2 - PADDLE_WIDTH / 2, SCREEN_HEIGHT - 40, PADDLE_WIDTH, PADDLE_HEIGHT };
    balls.clear();
    Ball ball = { (float)(paddle.x + PADDLE_WIDTH / 2.0f), (float)(paddle.y - BALL_SIZE), 0.0f, -1.0f, 5.0f, true };
    balls.push_back(ball);
    blocks.clear();
    bonuses.clear();
    score = 0;
    sticky = false;
    stickyHitsLeft = 0;
    safetyBottomActive = false;
    speedBonusBouncesLeft = 0;

    const int GAP = 2;
    const int blockWidth = (SCREEN_WIDTH - (COLS - 1) * GAP) / COLS;
    const int blockHeight = 25;

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            int x = j * (blockWidth + GAP);
            int y = i * (blockHeight + GAP) + 50;

            int type = rand() % 10;
            if (type < 4) {
                blocks.push_back(std::make_unique<StandardBlock>(x, y));
            }
            else if (type == 4) {
                blocks.push_back(std::make_unique<BonusBlock>(x, y));
            }
            else if (type == 5 || type == 6) {
                blocks.push_back(std::make_unique<StrongBlock>(x, y, 2));
            }
            else if (type == 7) {
                blocks.push_back(std::make_unique<StrongBlock>(x, y, 3));
            }
            else {
                blocks.push_back(std::make_unique<IndestructibleBlock>(x, y));
            }
        }
    }
}

void processInput(bool& quit) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }
        if (e.type == SDL_MOUSEMOTION) {
            paddle.x = e.motion.x - paddle.w / 2;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN) {
            for (auto& ball : balls) {
                if (ball.attached) {
                    ball.vx = 0;
                    ball.vy = -1;
                    ball.attached = false;
                    break;
                }
            }
        }
    }

    if (paddle.x < 0) paddle.x = 0;
    if (paddle.x + paddle.w > SCREEN_WIDTH) paddle.x = SCREEN_WIDTH - paddle.w;
}