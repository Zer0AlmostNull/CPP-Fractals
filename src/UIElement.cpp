#include "UIElement.h"

bool checkCollision(const SDL_Rect& rect, int& mouseX, int& mouseY)
{
	return mouseX >= rect.x && mouseX <= rect.x + rect.w &&
		mouseY >= rect.y && mouseY <= rect.y + rect.h;
}
