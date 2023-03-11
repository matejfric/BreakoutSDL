#pragma once

#include "common.h"

void draw_text(TTF_Font *font,
               const char *text,
               const unsigned int x,
               const unsigned int y,
               int flag_align,
               int colour);