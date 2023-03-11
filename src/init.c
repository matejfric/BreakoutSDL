#include "init.h"

int lives, score, bonus;
float ball_vx, ball_vy;

void init_buttons(void)
{
    // Offset from the left side of the screen
    int x = 60;

    play.x = x;
    play.y = WINDOW_HEIGHT / 3;
    play.w = WINDOW_WIDTH - x * 2;
    play.h = WINDOW_HEIGHT / 7;

    leaderboard.x = x;
    leaderboard.y = WINDOW_HEIGHT - WINDOW_HEIGHT / 3;
    leaderboard.w = WINDOW_WIDTH - x * 2;
    leaderboard.h = WINDOW_HEIGHT / 7;

    back_to_menu.x = x;
    back_to_menu.y = WINDOW_HEIGHT - 100;
    back_to_menu.w = WINDOW_WIDTH - x * 2;
    back_to_menu.h = (WINDOW_HEIGHT / 7) / 2;

    exit_to_menu.x = 15;
    exit_to_menu.y = HUD / 5;
    exit_to_menu.w = 110;
    exit_to_menu.h = HUD - 2 * exit_to_menu.y;
}

void init_paddle(void)
{
    paddle.w = WINDOW_WIDTH / 4;
    paddle.h = PADDLE_HEIGHT;
    paddle.x = WINDOW_WIDTH / 2 - paddle.w / 2;
    paddle.y = WINDOW_HEIGHT - paddle.h - BORDER;
}

void init_ball(void)
{
    ball.w = ball.h = BALL_SIZE;
    ball.x = paddle.x + paddle.w / 2 + ball.w / 2;
    ball.y = paddle.y - ball.h;
    ball_vx = (float)(rand() % BALL_SPEED - BALL_SPEED / 2);
    ball_vy = (float)(-(BALL_SPEED - BALL_SPEED / 3));
}

void init_borders(void)
{
    border_left.x = 0;
    border_left.y = HUD;
    border_left.w = BORDER;
    border_left.h = WINDOW_HEIGHT - border_right.y;

    border_right.x = WINDOW_WIDTH - BORDER;
    border_right.y = HUD;
    border_right.w = BORDER;
    border_right.h = WINDOW_HEIGHT - border_right.y;

    border_top.x = BORDER;
    border_top.y = HUD;
    border_top.w = WINDOW_WIDTH - 2 * BORDER;
    border_top.h = BORDER;
}

void new_game(int _lives, int _score)
{
    init_paddle();
    init_ball();
    score = _score;
    lives = _lives;
    bonus = 0;
    brick.w = width;
    brick.h = height;
    for (int i = 0; i < rows * cols; i++)
        bricks[i] = 1;
}

void init_SDL(void)
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        exit(1);
    }

    if (TTF_Init() == -1)
    {
        fprintf(stderr, "TTF_Init Error: %s\n", TTF_GetError());
        exit(1);
    }

    font = TTF_OpenFont("font.ttf", FONT_SIZE);
    lfont = TTF_OpenFont("font.ttf", FONT_SIZE * 2);

    if (!(font || lfont))
    {
        fprintf(stderr, "TTF_OpenFont Error: %s\n", TTF_GetError());
        exit(1);
    }

    window = SDL_CreateWindow("The Breakout", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }
}

void cleanup(void)
{
    sort_highscores();
    save_highscores();
    free(coords);
    free(bricks);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_CloseFont(lfont);
    TTF_Quit();
    SDL_Quit();
}