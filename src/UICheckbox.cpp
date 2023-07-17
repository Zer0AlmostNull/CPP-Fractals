#include "UICheckbox.h"
#include "circle.h";

UICheckbox::UICheckbox(RenderContext& _ctx, bool& _value_reference, SDL_Rect _rect, SDL_Color _background_color, SDL_Color _dot_color):
	ctx(_ctx),
	value_reference(_value_reference),
	rect(_rect),
	background_color(_background_color),
	dot_color(_dot_color) {}

void UICheckbox::update(v2_i& mouse_pos, u32& mouse_state)
{ 
	bool _prev_mouse_down = _is_mouse_down;

	_is_mouse_on = checkCollision(rect, mouse_pos.x, mouse_pos.y);
	_is_mouse_down = mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT);

	// check for mouse collision
	if (_is_mouse_down && !_prev_mouse_down && _is_mouse_on)
	{
		// invert state
		value_reference = !value_reference;
	}
}

void UICheckbox::draw()
{
	// draw background
	SDL_SetRenderDrawColor(ctx.renderer, background_color.r, background_color.g, background_color.b, 0xFF);
	SDL_RenderFillRect(ctx.renderer, &rect);

	// darw dot inside
	if (value_reference)
	{
		SDL_SetRenderDrawColor(ctx.renderer, dot_color.r, dot_color.g, dot_color.b, 0xFF);
		SDL_RenderFillCircle(ctx.renderer, rect.x + rect.w / 2, rect.y + rect.h / 2, .9f*min(rect.w, rect.h) / 2);
	}

};