#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

#include "UIElement.h"

#include "types.h"
#include "render_context.h"

#pragma once

class UILabel: public UIElement
{
	RenderContext& ctx;

	std::string text;
	SDL_Rect text_rect;
	SDL_Color text_color;
	TTF_Font* font;


public:
	UILabel(RenderContext& _ctx, std::string _text, SDL_Rect _rect,
		SDL_Color _text_color, TTF_Font* _font);

	void draw();
	void update(v2_i& mouse_pos, u32& mouse_state) { }

};