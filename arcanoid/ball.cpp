#include "ball.hpp"
#include "game.hpp"  
#include "bonus.hpp"  
#include <cmath>
void updateBalls() {
    for (size_t i = 0; i < balls.size(); ++i) {
        Ball& ball = balls[i];

        // Если шарик прикреплен к панели, держим его там
        if (ball.attached) {
            ball.x = (float)(paddle.x + paddle.w / 2.0f);
            ball.y = (float)(paddle.y - BALL_SIZE);
            continue;
        }

        ball.x += ball.vx * ball.speed;
        ball.y += ball.vy * ball.speed;

        // Проверка отскока от стен
        if (ball.x < 0 || ball.x + BALL_SIZE > SCREEN_WIDTH) ball.vx = -ball.vx;
        if (ball.y < 0) ball.vy = -ball.vy;

        // Если шарик падает ниже панели, то уменьшаем количество жизней
        if (ball.y > SCREEN_HEIGHT) {
            if (safetyBottomActive) {
                // отскакиваем от "дно-каретки"
                ball.y = SCREEN_HEIGHT - BALL_SIZE - 1;
                ball.vy = -fabs(ball.vy);
                safetyBottomActive = false; // одноразовое
            }
            else if (balls.size() > 1) {
                balls.erase(balls.begin() + i);
                i--;
            }
            else {
                score -= 10;
                resetBall(ball);
            }
        }



        SDL_Rect ballRect = { (int)ball.x, (int)ball.y, BALL_SIZE, BALL_SIZE };

        // Отскок от панели
        if (SDL_HasIntersection(&ballRect, &paddle)) {
            ball.vy = -fabs(ball.vy);
            float hitPos = ((float)(ball.x + BALL_SIZE / 2.0) - paddle.x) / paddle.w - 0.5f;
            ball.vx = hitPos * 2.0f;
            if (sticky) {
                ball.attached = true;
                stickyHitsLeft--;
                if (stickyHitsLeft <= 0) sticky = false;
            }
        }

        // Отскок от блоков
        for (auto& block : blocks) {
            if (!block.active) continue;
            if (SDL_HasIntersection(&ballRect, &block.rect)) {
                if (block.type != INDESTRUCTIBLE) {
                    block.hitsLeft--;
                    if (block.hitsLeft <= 0) {
                        block.active = false;
                        score += 10;
                        if (block.type == BONUS) {
                            spawnBonus(block.rect.x + block.rect.w / 2, block.rect.y + block.rect.h);
                        }
                    }
                    else {
                        // Понижение "прочности"
                        switch (block.type) {
                        case STRONG_3:
                            block.type = STRONG_2;
                            break;
                        case STRONG_2:
                            block.type = STANDARD;
                            break;
                        default:
                            break;
                        }
                        score += 5;
                    }
                }

                // Вычисление предыдущей позиции
                float prevX = ball.x - ball.vx * ball.speed;
                float prevY = ball.y - ball.vy * ball.speed;
                SDL_Rect prevRect = { (int)prevX, (int)prevY, BALL_SIZE, BALL_SIZE };

                // Определение направления отскока
                bool fromLeft = prevRect.x + BALL_SIZE <= block.rect.x;
                bool fromRight = prevRect.x >= block.rect.x + block.rect.w;
                bool fromTop = prevRect.y + BALL_SIZE <= block.rect.y;
                bool fromBottom = prevRect.y >= block.rect.y + block.rect.h;

                if ((fromLeft && !fromRight) || (!fromLeft && fromRight)) {
                    ball.vx = -ball.vx;
                }
                if ((fromTop && !fromBottom) || (!fromTop && fromBottom)) {
                    ball.vy = -ball.vy;
                }
            }
        }

        // Обработка столкновений между шарами
        for (size_t i = 0; i < balls.size(); ++i) {
            for (size_t j = i + 1; j < balls.size(); ++j) {
                Ball& a = balls[i];
                Ball& b = balls[j];

                float dx = (a.x + BALL_SIZE / 2) - (b.x + BALL_SIZE / 2);
                float dy = (a.y + BALL_SIZE / 2) - (b.y + BALL_SIZE / 2);
                float distance = std::sqrt(dx * dx + dy * dy);

                if (distance < BALL_SIZE) {  // простая круговая проверка
                    // Нормализуем вектор
                    float nx = dx / distance;
                    float ny = dy / distance;

                    // Обмен скоростей по направлению столкновения
                    float v1 = a.vx * nx + a.vy * ny;
                    float v2 = b.vx * nx + b.vy * ny;

                    float exchange = v1 - v2;

                    a.vx -= exchange * nx;
                    a.vy -= exchange * ny;
                    b.vx += exchange * nx;
                    b.vy += exchange * ny;

                    // Немного раздвигаем шарики, чтобы не залипли
                    float overlap = BALL_SIZE - distance;
                    a.x += nx * (overlap / 2);
                    a.y += ny * (overlap / 2);
                    b.x -= nx * (overlap / 2);
                    b.y -= ny * (overlap / 2);
                }
            }
        }

    }
}

void resetBall(Ball& ball) {
    ball.x = (float)(paddle.x + paddle.w / 2.0f);
    ball.y = (float)(paddle.y - BALL_SIZE);
    ball.vx = 0;
    ball.vy = -1;
    ball.speed = 5.0f;
    ball.attached = true;
}