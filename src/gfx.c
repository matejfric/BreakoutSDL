#include "gfx.h"

// Leaderboard screen
void show_leaderboard(void)
{
    // Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // Title
    draw_text(lfont, "HIGHSCORES", 0, WINDOW_HEIGHT / 10, 1, 2);
    // Back to menu button
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &back_to_menu);
    // Button hover
    if (SDL_PointInRect(&m.p, &back_to_menu))
        draw_text(font, "BACK TO MENU", 0, back_to_menu.y + back_to_menu.h / 2 - FONT_SIZE / 2, 1, 1);
    else
        draw_text(font, "BACK TO MENU", 0, back_to_menu.y + back_to_menu.h / 2 - FONT_SIZE / 2, 1, 0);
    // Display highscores
    for (int i = 0; i < HIGHSCORE_NUM; i++)
    {
        char buf[100];
        sprintf(buf, "%d.", i + 1);
        draw_text(font, buf, 120, 200 + i * (FONT_SIZE + 20), 0, 0);
        sprintf(buf, "%d", highscores[i]);
        draw_text(font, buf, 0, 200 + i * (FONT_SIZE + 20), 1, 0);
    }
    // Render current scene
    SDL_RenderPresent(renderer);
}

void menu(void)
{
    // Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // Title
    draw_text(lfont, "THE BREAKTOUT", 0, WINDOW_HEIGHT / 10, 1, 2);
    // Buttons
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &play);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &leaderboard);
    // Hover
    if (SDL_PointInRect(&m.p, &play))
        draw_text(lfont, "PLAY", 0, play.y + play.h / 2 - FONT_SIZE, 1, 1);
    else
        draw_text(lfont, "PLAY", 0, play.y + play.h / 2 - FONT_SIZE, 1, 0);
    if (SDL_PointInRect(&m.p, &leaderboard))
        draw_text(lfont, "LEADERBOARD", 0, leaderboard.y + leaderboard.h / 2 - FONT_SIZE, 1, 1);
    else
        draw_text(lfont, "LEADERBOARD", 0, leaderboard.y + leaderboard.h / 2 - FONT_SIZE, 1, 0);
    // Render current scene
    SDL_RenderPresent(renderer);
}

void update(void)
{
    // Background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    // Bricks
    void (*colors[])(void) = {red, orange, yellow, green, blue, teal};
    for (int i = 0; i < rows; i++)
    {
        (*colors[i % 6])();
        for (int j = 0; j < cols; j++)
        {
            if (bricks[i * cols + j])
            {
                brick.x = coords[i * cols + j].x;
                brick.y = coords[i * cols + j].y;
                SDL_RenderFillRect(renderer, &brick);
            }
        }
    }
    // Borders
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    SDL_RenderFillRect(renderer, &border_top);
    SDL_RenderFillRect(renderer, &border_left);
    SDL_RenderFillRect(renderer, &border_right);
    // Paddle
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &paddle);
    // Ball
    SDL_RenderFillRect(renderer, &ball);
    // Text
    char text[64];
    char hp[64];
    if (score > highscores[HIGHSCORE_NUM-1])
    {
        sprintf(text, "HIGHSCORE: %d", score);
        draw_text(font, text, BORDER, 15, 1, 2);
    }
    else
    {
        sprintf(text, "SCORE: %d", score);
        draw_text(font, text, BORDER, 15, 1, 0);
    }
    sprintf(hp, "LIVES: %d", lives);
    draw_text(font, hp, 0, 15, 2, 0);
    // Exit to menu button
    SDL_SetRenderDrawColor(renderer, 96, 96, 96, 255);
    SDL_RenderFillRect(renderer, &exit_to_menu);
    if (SDL_PointInRect(&m.p, &exit_to_menu))
        draw_text(font, "MENU", exit_to_menu.x+10, exit_to_menu.y + 1 + exit_to_menu.h / 2 - FONT_SIZE/2, 0, 1);
    else
        draw_text(font, "MENU", exit_to_menu.x+10, exit_to_menu.y + 1 + exit_to_menu.h / 2 - FONT_SIZE/2, 0, 0);
    // Render current scene
    SDL_RenderPresent(renderer);
}

// Colours
void red(void)
{
    SDL_SetRenderDrawColor(renderer, 210, 50, 50, 255);
}
void orange(void)
{
    SDL_SetRenderDrawColor(renderer, 210, 120, 50, 255);
}
void yellow(void)
{
    SDL_SetRenderDrawColor(renderer, 255, 200, 50, 255);
}
void green(void)
{
    SDL_SetRenderDrawColor(renderer, 130, 255, 100, 255);
}
void blue(void)
{
    SDL_SetRenderDrawColor(renderer, 80, 130, 255, 255);
}
void teal(void)
{
    SDL_SetRenderDrawColor(renderer, 100, 200, 255, 255);
}