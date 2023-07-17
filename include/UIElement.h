#include <SDL.h>
#include "types.h"

#pragma once

bool checkCollision(const SDL_Rect& rect, int& mouseX, int& mouseY);

class UIElement {
public: 
    virtual void draw() = 0;
    virtual void update(v2_i & mouse_pox, u32 & mouse_state) = 0;

};