#include "UISlider.h"


void UISlider::update_graphics()
{
	// recalculate rect positions 
	foreground_rect.w = background_rect.w * internal_float;

	// recalculate handel rect
	handle_rect.x = background_rect.x + foreground_rect.w - handle_rect.w / 2;
}

UISlider::UISlider(RenderContext& _ctx, SDL_Rect _rect, u16 _handle_width,
	f32& _value_reference, f32 _min_value, f32 _max_value, f32 _start_value,
	SDL_Color _bar_color, SDL_Color _background_color, SDL_Color _handle_color) : 
	ctx(_ctx),
	//
	value_reference(_value_reference),
	min_value(_min_value),
	max_value(_max_value),
	//
	background_rect(_rect),
	handle_rect({_rect.x, _rect.y, _handle_width,_rect.h}),
	foreground_rect({_rect.x, _rect.y, (int)(_rect.w * _start_value), _rect.h}),
	internal_float(_start_value),
	//
	foreground_color(_bar_color),
	background_color(_background_color),
	handle_color(_handle_color)

{
	// set proper value
	value_reference = min_value + (max_value - min_value) * internal_float;

	update_graphics();
}

void UISlider::draw()
{
	// draw background rect
	SDL_SetRenderDrawColor(ctx.renderer, background_color.r, background_color.g, background_color.b, 0xFF);
	SDL_RenderFillRect(ctx.renderer, &background_rect);

	// draw filling
	SDL_SetRenderDrawColor(ctx.renderer, foreground_color.r, foreground_color.g, foreground_color.b, 0xFF);
	SDL_RenderFillRect(ctx.renderer, &foreground_rect);

	// draw the hande
	SDL_SetRenderDrawColor(ctx.renderer, handle_color.r, handle_color.g, handle_color.b, 0xFF);
	SDL_RenderFillRect(ctx.renderer, &handle_rect);
}

void UISlider::update(v2_i& mouse_pos, u32& mouse_state)
{
	// if mouse is down
	if (mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT) && 
		checkCollision(background_rect, mouse_pos.x, mouse_pos.y))
	{
		// get internal float based on mouse position
		internal_float = max(min((f32)abs(mouse_pos.x - background_rect.x)/background_rect.w, 1.0f), 0.0f);
		
		// set proper value
		value_reference = min_value + (max_value - min_value) * internal_float;

		update_graphics();

	}

	// update 
}


