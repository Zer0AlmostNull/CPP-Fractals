#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

#include "UIElement.h"

#include "types.h"
#include "render_context.h"

#pragma once

class UICheckbox : public UIElement
{
	RenderContext& ctx;

	bool& value_reference;

	SDL_Rect rect;
	SDL_Color background_color;
	SDL_Color dot_color;

	bool _is_mouse_on = false;
	bool _is_mouse_down = false;
public:
	UICheckbox(RenderContext& _ctx, bool& _value_reference, SDL_Rect _rect,
		SDL_Color _background_color, SDL_Color _dot_color);

	void draw();
	void update(v2_i& mouse_pos, u32& mouse_state);

};