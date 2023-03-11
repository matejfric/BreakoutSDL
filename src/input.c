#include "input.h"

bool right_arrow, left_arrow, lmb;

void input(void)
{
    SDL_Event e;
    SDL_GetMouseState(&m.p.x, &m.p.y);
    while (SDL_PollEvent(&e))
    {
        switch (e.type)
        {
        case SDL_QUIT:
            exit(0);
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                lmb = 1;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if (e.button.button == SDL_BUTTON_LEFT)
            {
                lmb = 0;
            }
            break;
        case SDL_KEYDOWN:
            if (e.key.repeat == 0)
            {
                if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                    right_arrow = 1;

                if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
                    left_arrow = 1;
            }
            break;
        case SDL_KEYUP:
            if (e.key.repeat == 0)
            {
                if (e.key.keysym.scancode == SDL_SCANCODE_RIGHT)
                    right_arrow = 0;

                if (e.key.keysym.scancode == SDL_SCANCODE_LEFT)
                    left_arrow = 0;
            }
            break;
        default:
            break;
        }
    }
}