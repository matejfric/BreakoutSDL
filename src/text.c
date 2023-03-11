#include "text.h"

// flag_align:
// 0...left
// 1...centre
// 2...right
// colour:
// 0...white
// 1...blue
// 2...red
void draw_text(TTF_Font *font,
               const char *text,
               const unsigned int x,
               const unsigned int y,
               int flag_align,
               int colour)
{
    int text_width = 0;
    int text_height = 0;
    SDL_Color text_colour[3] = {
        {255, 255, 255, 255},
        {0, 120, 210, 255},
        {175, 0, 90, 255}};

    // TTF_RenderUTF8_Blended for better looking text rendering.
    // TTF_RenderUTF8_Solid for better performance.
    if (!(surface = TTF_RenderUTF8_Solid(font, text, text_colour[colour])))
    {
        fprintf(stderr, "\nTTF_RenderText_Solid Error: %s\n", TTF_GetError());
        exit(1);
    }

    if (!(texture = SDL_CreateTextureFromSurface(renderer, surface)))
    {
        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_FreeSurface(surface);
    surface = NULL;

    if (SDL_QueryTexture(texture, NULL, NULL, &text_width, &text_height))
    {
        fprintf(stderr, "SDL_QueryTexture Error: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Rect dst_rect;
    switch (flag_align)
    {
    case 1: // align to the centre
        dst_rect.x = WINDOW_WIDTH / 2 - text_width / 2;
        dst_rect.y = y;
        dst_rect.w = text_width;
        dst_rect.h = text_height;
        break;
    case 2: // align to the right
        dst_rect.x = WINDOW_WIDTH - BORDER - text_width;
        dst_rect.y = y;
        dst_rect.w = text_width;
        dst_rect.h = text_height;
        break;
    default: // align to the left
        dst_rect.x = x;
        dst_rect.y = y;
        dst_rect.w = text_width;
        dst_rect.h = text_height;
        break;
    }
    SDL_RenderCopy(renderer, texture, NULL, &dst_rect);
    SDL_DestroyTexture(texture);
    texture = NULL;
}