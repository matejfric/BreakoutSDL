#include "logic.h"

void bubble_sort(int *arr, int len)
{
    int temp;
    bool swapped;
    do
    {
        swapped = 0;
        for (int i = 0; i < len - 1; i++)
        {
            if (arr[i] < arr[i + 1])
            {
                temp = arr[i + 1];
                arr[i + 1] = arr[i];
                arr[i] = temp;
                swapped = 1;
            }
        }
        len--;
    } while (swapped);
}

void sort_highscores(void)
{
    if (score > highscores[HIGHSCORE_NUM - 1])
        {
            highscores[HIGHSCORE_NUM - 1] = score;
            bubble_sort(highscores, HIGHSCORE_NUM);
        }
}

void reset(int _lives)
{
    bonus = 0;
    SDL_Delay(1000);
    if (!_lives)
    {
        sort_highscores();
        new_game(LIVES, 0);
    }
    else
    {
        init_paddle();
        init_ball();
    }
}

void game(void)
{
    // Ball & bricks collision.
    bool flag_destroyed; 
    bool flag_win = 1;
    for (int i = 0; i < rows; i++)
    {
        flag_destroyed = 0;
        for (int j = 0; j < cols; j++)
        {
            if (bricks[i * cols + j])
            {
                flag_win = 0;
                brick.x = coords[i * cols + j].x;
                brick.y = coords[i * cols + j].y;
                if (SDL_HasIntersection(&brick, &ball))
                {
                    bricks[i * cols + j] = 0;
                    flag_destroyed = 1;
                    score += 1 + bonus;
                    bonus++;
                    // Determines which side the ball collided with.
                    int ball_cx = ball.x + ball.w / 2;
                    int ball_cy = ball.y + ball.h / 2;
                    int brick_cx = brick.x + brick.w / 2;
                    int brick_cy = brick.y + brick.h / 2;
                    int dx = ball_cx - brick_cx;
                    int dy = ball_cy - brick_cy;
                    int half_width = (ball.w + brick.w) / 2;
                    int half_height = (ball.h + brick.h) / 2;
                    int wy = half_width * dy;
                    int hx = half_height * dx;
                    if (wy > hx) // Bottom or left
                    {
                        if (wy > -hx && oldball.y > ball.y) // Bottom
                        {
                            ball.y = brick.y + brick.h;
                            ball_vy = -ball_vy;
                        }
                        else if (oldball.x < ball.x) // Left
                        {
                            ball.x = brick.x - ball.w; 
                            ball_vx = -ball_vx;
                        }
                    }
                    else // Top or right
                    {
                        if (wy > -hx && oldball.x > ball.x) // Right
                        {
                            ball.x = brick.x + brick.w; 
                            ball_vx = -ball_vx;
                        }
                        else if (oldball.y < ball.y) // Top
                        {
                            ball.y = brick.y - ball.h; 
                            ball_vy = -ball_vy;
                        }
                    }
                    if (flag_destroyed) // If a brick was destroyed move out of the loop.
                        goto next;
                }
            }
        }
    }
    next:
    // Check if all bricks have been destroyed.
    if (flag_win)
        new_game(++lives, 2 * score);
    // Paddle & ball collision.
    if (SDL_HasIntersection(&paddle, &ball))
    {
        bonus = 0;
        ball.y = paddle.y - ball.h;
        float x = (float)((paddle.x + (paddle.w / 2.0f)) - (ball.x + ball.w / 2.0f));
        float norm = x / (paddle.w / 2.0f);
        float angle = norm * MAX_ANGLE;
        ball_vx = BALL_SPEED * sinf(-angle);
        ball_vy = -BALL_SPEED * cosf(angle);
    }
    // Wall collions.
    // Left
    if (ball.x < BORDER)
    {
        ball.x = BORDER;
        ball_vx = -ball_vx;
    }
    // Right
    if (ball.x > WINDOW_WIDTH - BORDER - ball.w)
    {
        ball.x = WINDOW_WIDTH - BORDER - ball.w;
        ball_vx = -ball_vx;
    }
    // Bottom
    if (ball.y > WINDOW_HEIGHT)
    {
        reset(--lives);
    }
    // Top
    if (ball.y < HUD + BORDER)
    {
        ball.y = HUD + BORDER;
        ball_vy = -ball_vy;
    }
    // Increment ball position.
    oldball.x = ball.x;
    oldball.y = ball.y;
    ball.x += (int)ball_vx;
    ball.y += (int)ball_vy;
}