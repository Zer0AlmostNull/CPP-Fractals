#include <SDL.h>

#include "UIElement.h"
#include "render_context.h"
#include "circle.h"
#include "types.h"

#pragma once

class UISlider : public UIElement
{
	RenderContext& ctx;

	f32 internal_float;

	f32& value_reference;
	f32 min_value, max_value;
	
	SDL_Rect background_rect, foreground_rect, handle_rect;
	SDL_Color foreground_color, background_color, handle_color;

	void update_graphics();

public:
	UISlider(RenderContext& _ctx, SDL_Rect _rect, u16 _handle_width,
			f32& _value_reference, f32 _min_value, f32 _max_value, f32 _start_value,
			SDL_Color _bar_color = SDL_Color{ 255, 255, 255 },
			SDL_Color _background_color = SDL_Color{ 30, 30, 30 },
			SDL_Color _handle_color = SDL_Color{ 200, 0, 0 });

	void draw();
	void update(v2_i& mouse_pos, u32& mouse_state);

};
