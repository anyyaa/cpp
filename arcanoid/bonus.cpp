#include "common.hpp"

void spawnBonus(int x, int y) {
    Bonus bonus;
    bonus.rect = { x, y, 20, 20 };
    if (!extraBallGiven) {
        bonus.type = 0; 
        extraBallGiven = true;
    }
    else {
        bonus.type = rand() % 5;
    }

    bonus.active = true;
    bonuses.push_back(bonus);
}


void updateBonuses() {
    for (auto& bonus : bonuses) {
        if (!bonus.active) continue;
        bonus.rect.y += 2; 
        if (SDL_HasIntersection(&bonus.rect, &paddle)) {
            switch (bonus.type) {
            case 0: { 
                if (!balls.empty()) {
                    
                    Ball newBall = balls[0];
                    newBall.x += 10;
                    newBall.y += 10;
                    newBall.vx = -balls[0].vx;
                    newBall.vy = balls[0].vy;
                    newBall.attached = false;
                    balls.push_back(newBall);
                }
                break;
            }
            case 1:
                paddle.w += 30;
                if (paddle.w > SCREEN_WIDTH) paddle.w = SCREEN_WIDTH;
                break;
            case 2:
               
                for (auto& ball : balls) {
                    ball.speed += 1.5f;
                }
                break;
            case 3:
                sticky = true;
                stickyHitsLeft = 3;
                break;
            case 4:
                safetyBottomActive = true;
                break;

            }
            bonus.active = false;
        }

        if (bonus.rect.y > SCREEN_HEIGHT) {
            bonus.active = false;
        }
    }
}
