#include <SDL.h>
#include <vector>
#include <tuple>

#include "types.h"

#pragma once

class ColorGradient
{
	std::vector<std::tuple<SDL_Color, f32>> colors;

public:
	ColorGradient() {}
	ColorGradient(std::vector<std::tuple<SDL_Color, f32>> &_colors);

	u32 get_color(f32 value);
};
