#include "UILabel.h"

UILabel::UILabel(RenderContext& _ctx, std::string _text,
	SDL_Rect _rect,
	SDL_Color _text_color, TTF_Font* _font) :
	ctx(_ctx),
	text(_text),
	text_rect(_rect),
	text_color(_text_color),
	font(_font){}

void UILabel::draw()
{
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text.c_str(), text_color);

	SDL_Texture* Message = SDL_CreateTextureFromSurface(ctx.renderer, surfaceMessage);

	SDL_RenderCopy(ctx.renderer, Message, NULL, &text_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}

