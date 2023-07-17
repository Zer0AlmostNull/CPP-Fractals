#include <SDL.h>
#include "UIElement.h"
#include "UILabel.h"

#include "types.h"
#include "render_context.h"

#pragma once

class UIButton : public UIElement
{
	RenderContext& ctx;

	SDL_Rect rect;
	SDL_Color background_color;
	SDL_Color highlighted_color;

	// on click function
	void (*onClick)();

	UILabel text_label;
	
	bool _is_mouse_on = false;
	bool _is_mouse_down = false;

public:
	UIButton(RenderContext& _ctx, SDL_Rect _rect,
		std::string _text, u16 _text_width, u16 _text_height, TTF_Font *font,
		SDL_Color _background_color, SDL_Color _highlighted_color, SDL_Color _text_color,
		void (*onClick)());

	void draw();
	void update(v2_i& mouse_pox, u32& mouse_state);

};