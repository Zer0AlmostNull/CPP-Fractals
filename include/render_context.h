#include <SDL_render.h>

#include "types.h"
#include "settings.h"

#pragma once

struct RenderContext
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;

    u32 buff[WND_WIDTH * WND_HEIGHT] = { 0 };
};