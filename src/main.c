#include "main.h"

Uint32 last_frame, this_frame;
void limit_fps(void);
void assert_malloc(bool *arr);
void move_paddle(void);

int main(void)
{
    srand((int)time(NULL));
    load_bricks();
    load_highscores();
    bricks = (bool *)malloc(rows * cols * sizeof(bool));
    assert_malloc(bricks);
    init_SDL();
    init_buttons();
    init_borders();
    new_game(LIVES, 0);
    atexit(cleanup);
    bool quit, leave_menu, leave_leaderboard;
    quit = leave_leaderboard = 0;
menu:
    leave_menu = 0;
    // Main menu loop
    while (!leave_menu)
    {
        last_frame = SDL_GetTicks();
        input();
        menu();
        // Play button
        if (lmb && SDL_PointInRect(&m.p, &play))
        {
            leave_menu = 1;
        }
        // Leaderboard button
        if (lmb && SDL_PointInRect(&m.p, &leaderboard))
        {
            // Leaderboard screen
            while (!leave_leaderboard)
            {
                last_frame = SDL_GetTicks();
                input();
                show_leaderboard();
                if (lmb && SDL_PointInRect(&m.p, &back_to_menu))
                {
                    leave_leaderboard = 1;
                }
                limit_fps();
            }
            leave_leaderboard = 0;
        }
        limit_fps();
    }
    // Game loop
    while (!quit)
    {
        last_frame = SDL_GetTicks();
        game();
        input();
        move_paddle();
        update();
        // Menu button
        if (lmb && SDL_PointInRect(&m.p, &exit_to_menu))
        {
            goto menu;
        }
        limit_fps();
    }
    return 0;
}

void limit_fps(void)
{
    this_frame = SDL_GetTicks() - last_frame;
    if (this_frame < (1000 / FPS))
        SDL_Delay(1000 / FPS - this_frame);
}

void assert_malloc(bool *arr)
{
    if (!arr)
    {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        exit(1);
    }
}

void move_paddle(void)
{
    if (left_arrow)
    {
        if (paddle.x - PADDLE_SPEED < BORDER)
            paddle.x = BORDER;
        else
            paddle.x -= PADDLE_SPEED;
    }
    if (right_arrow)
    {
        if (paddle.x + PADDLE_SPEED > WINDOW_WIDTH - paddle.w - BORDER)
            paddle.x = WINDOW_WIDTH - paddle.w - BORDER;
        else
            paddle.x += PADDLE_SPEED;
    }
}