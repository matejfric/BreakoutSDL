#pragma once

#include "common.h"
#include "res.h"
#include "logic.h"

extern int lives, score, bonus;
extern float ball_vx, ball_vy;

void init_SDL(void);
void cleanup(void);

void new_game(int _lives, int _score);

void init_ball(void);
void init_paddle(void);
void init_borders(void);
void init_buttons(void);

