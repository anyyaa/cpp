#include "ball.hpp"
#include "game.hpp"
#include "common.hpp"
#include "block.hpp"
void resetBall(Ball& ball) {
    ball.x = (float)(paddle.x + paddle.w / 2.0f);
    ball.y = (float)(paddle.y - BALL_SIZE);
    ball.vx = 0;
    ball.vy = -1;
    ball.speed = 5.0f;

    bool alreadyAttached = false;
    for (const auto& b : balls) {
        if (b.attached) {
            alreadyAttached = true;
            break;
        }
    }

    ball.attached = sticky && !alreadyAttached;
}

void updateBalls() {
    for (size_t i = 0; i < balls.size(); ++i) {
        Ball& ball = balls[i];

        if (ball.attached) {
            ball.x = (float)(paddle.x + paddle.w / 2.0f);
            ball.y = (float)(paddle.y - BALL_SIZE);
            continue;
        }

        ball.x += ball.vx * ball.speed;
        ball.y += ball.vy * ball.speed;

        bool bounced = false;

        if (ball.x < 0 || ball.x + BALL_SIZE > SCREEN_WIDTH) {
            ball.vx = -ball.vx;
            ball.x = std::max(0.0f, std::min(ball.x, (float)(SCREEN_WIDTH - BALL_SIZE)));
            bounced = true;
        }
        if (ball.y < 0) {
            ball.vy = -ball.vy;
            ball.y = 0;
            bounced = true;
        }

        if (ball.y > SCREEN_HEIGHT) {
            if (safetyBottomActive) {
                ball.y = SCREEN_HEIGHT - BALL_SIZE - 1;
                ball.vy = -fabs(ball.vy);
                safetyBottomActive = false;
                bounced = true;
            }
            else if (balls.size() > 1) {
                balls.erase(balls.begin() + i);
                i--;
                continue;
            }
            else {
                score = std::max(0, score - 10);
                resetBall(ball);
                continue;
            }
        }

        SDL_Rect ballRect = { (int)ball.x, (int)ball.y, BALL_SIZE, BALL_SIZE };

        if (SDL_HasIntersection(&ballRect, &paddle)) {
            ball.vy = -fabs(ball.vy);
            float hitPos = ((float)(ball.x + BALL_SIZE / 2.0) - paddle.x) / paddle.w - 0.5f;
            ball.vx = hitPos * 2.0f;

            if (sticky) {
                bool alreadyAttached = false;
                for (const auto& b : balls) {
                    if (b.attached) {
                        alreadyAttached = true;
                        break;
                    }
                }

                if (!alreadyAttached) {
                    ball.attached = true;
                    stickyHitsLeft--;
                    if (stickyHitsLeft <= 0) sticky = false;
                }
            }
        }

        for (auto& block : blocks) {
            if (!block->isActive()) continue;

            if (SDL_HasIntersection(&ballRect, &block->getRect())) {
                block->onHit();
                bounced = true;

                float prevX = ball.x - ball.vx * ball.speed;
                float prevY = ball.y - ball.vy * ball.speed;
                SDL_Rect prevRect = { (int)prevX, (int)prevY, BALL_SIZE, BALL_SIZE };

                bool fromLeft = prevRect.x + BALL_SIZE <= block->getRect().x;
                bool fromRight = prevRect.x >= block->getRect().x + block->getRect().w;
                bool fromTop = prevRect.y + BALL_SIZE <= block->getRect().y;
                bool fromBottom = prevRect.y >= block->getRect().y + block->getRect().h;

                if ((fromLeft && !fromRight) || (!fromLeft && fromRight)) {
                    ball.vx = -ball.vx;
                }
                if ((fromTop && !fromBottom) || (!fromTop && fromBottom)) {
                    ball.vy = -ball.vy;
                }
            }
        }

        for (size_t j = i + 1; j < balls.size(); ++j) {
            Ball& other = balls[j];

            float dx = (ball.x + BALL_SIZE / 2) - (other.x + BALL_SIZE / 2);
            float dy = (ball.y + BALL_SIZE / 2) - (other.y + BALL_SIZE / 2);
            float distance = std::sqrt(dx * dx + dy * dy);

            if (distance < BALL_SIZE) {
                bounced = true;
                float nx = dx / distance;
                float ny = dy / distance;

                float v1 = ball.vx * nx + ball.vy * ny;
                float v2 = other.vx * nx + other.vy * ny;

                float exchange = v1 - v2;
                ball.vx -= exchange * nx;
                ball.vy -= exchange * ny;
                other.vx += exchange * nx;
                other.vy += exchange * ny;

                float overlap = BALL_SIZE - distance;
                ball.x += nx * overlap / 2;
                ball.y += ny * overlap / 2;
                other.x -= nx * overlap / 2;
                other.y -= ny * overlap / 2;
            }
        }

        if (bounced && speedBonusBouncesLeft > 0) {
            speedBonusBouncesLeft--;
            if (speedBonusBouncesLeft == 0) {
                for (auto& b : balls) {
                    b.speed = 5.0f;
                }
            }
        }
    }
}