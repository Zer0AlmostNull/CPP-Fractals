#include "color_gradient.h"

#include "macros.h"

#include <algorithm>


// Linear interpolation function
u32 lerp(const SDL_Color& color1, const SDL_Color& color2, f32 t) {

	u8 r = static_cast<u8>(color1.r + t * (color2.r - color1.r));
	u8 g = static_cast<u8>(color1.g + t * (color2.g - color1.g));
	u8 b = static_cast<u8>(color1.b + t * (color2.b - color1.b));

	return (r << 24) | (g << 16) | (b << 8) | 0xFF;
}

u32 color_to_u32(const SDL_Color& color)
{
	return (color.r << 24) | (color.r << 16) | (color.b << 8) | 0xFF;
}


ColorGradient::ColorGradient(std::vector<std::tuple<SDL_Color, f32>>& _colors) : colors(_colors)
{
	// sort colors to make it easier
	std::sort(colors.begin(), colors.end(), [](const std::tuple<SDL_Color, f32>& a, const std::tuple<SDL_Color, f32>& b) {
		return std::get<1>(a) < std::get<1>(b);
		});
}

u32 ColorGradient::get_color(f32 value)
{
	// return black if gradient is empty
	if (size(colors) == 0) return 0xFF;

	// first or last color if value is grater or lower
	if (value <= std::get<1>(colors.front())) return color_to_u32(std::get<0>(colors.front()));
	else if (value >= std::get<1>(colors.back())) return color_to_u32(std::get<0>(colors.back()));
	
	// find two points for interpolation
	size_t i = 1;
	while (value > std::get<1>(colors[i]))
		++i;
	
	const auto& color1 = std::get<0>(colors[i - 1]);
	const auto& color2 = std::get<0>(colors[i]);
	const f32 t = (value - std::get<1>(colors[i - 1])) / (std::get<1>(colors[i]) - std::get<1>(colors[i - 1]));

	return lerp(color1, color2, t);

}
