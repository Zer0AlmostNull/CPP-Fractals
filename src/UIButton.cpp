#include "UIButton.h"



UIButton::UIButton(RenderContext& _ctx, SDL_Rect _rect, std::string _text, u16 _text_width, u16 _text_height, TTF_Font* _font, SDL_Color _background_color, SDL_Color _highlighted_color, SDL_Color _text_color, void(*_onClick)()) :
	ctx(_ctx),
	rect(_rect),

	background_color(_background_color),
	highlighted_color(_highlighted_color),
	onClick(_onClick),
	//	UILabel(RenderContext& _ctx, std::string _text, SDL_Rect _rect, SDL_Color _text_color, TTF_Font* _font);
	text_label({_ctx, _text, SDL_Rect({ _rect.x + (_rect.w - _text_width)/2 , _rect.y + (_rect.h - _text_height) / 2, _text_width, _text_height}), _text_color, _font})
{
}

void UIButton::draw()
{
	// Draw background
	const SDL_Color& curr_color = _is_mouse_on ? highlighted_color : background_color;

	SDL_SetRenderDrawColor(ctx.renderer, curr_color.r, curr_color.g, curr_color.b, 0xFF);
	SDL_RenderFillRect(ctx.renderer, &rect);

	// Draw text

	text_label.draw();

}

void UIButton::update(v2_i& mouse_pos, u32& mouse_state)
{
	bool _prev_mouse_down = _is_mouse_down;

	_is_mouse_on = checkCollision(rect, mouse_pos.x, mouse_pos.y);
	_is_mouse_down = mouse_state & SDL_BUTTON(SDL_BUTTON_LEFT);

	// check for mouse collision
	if ( _is_mouse_down && !_prev_mouse_down  && _is_mouse_on)
	{
		onClick();
	}
	
}
