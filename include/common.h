#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "defs.h"

bool *bricks; // 0...destroyed; 1...present
int highscores[HIGHSCORE_NUM];
int rows, cols, width, height;

typedef struct
{
    int x;
    int y;
} Coords;
Coords *coords; // Brick x and y coordinates

typedef struct
{
    SDL_Point p;
} Mouse;
Mouse m;

SDL_Renderer *renderer;
SDL_Surface *surface;
SDL_Texture *texture;
SDL_Window *window;
TTF_Font *font, *lfont;

SDL_Rect paddle, ball, brick,
border_left, border_right, border_top,
play, leaderboard, back_to_menu, exit_to_menu;