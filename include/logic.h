#pragma once

#include "common.h"
#include "init.h"
#include "gfx.h"

void game(void);
void sort_highscores(void);
void bubble_sort(int *arr, int len);

typedef struct
{
    int x;
    int y;
} Old_ball;
Old_ball oldball;