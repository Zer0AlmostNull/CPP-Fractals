#include "math.h"

#include "SDL_events.h"
#include "SDL_render.h"

#include "julia_fractal.h"


u32 RGB_to_u32(u8 r, u8 g, u8 b)
{
	return (r << 24) | (g << 16) | (b << 8) | 0xFF;
}

JuliaFractal::JuliaFractal(RenderContext& _rc) : ctx(_rc)
{
	// reserve space for threads
	rendering_threads.reserve(MAX_THREADS);

	// create color gradient
	std::vector<std::tuple<SDL_Color, f32>>colors = {
			//std::make_tuple(SDL_Color{148, 0, 211, 255}, 0.0f), // Violet at value 0.0
			//std::make_tuple(SDL_Color{75, 0, 130, 255}, 0.2f),  // Indigo at value 0.2
			std::make_tuple(SDL_Color{0, 0, 255, 255}, 0.0f),   // Blue at value 0.4
			std::make_tuple(SDL_Color{0, 255, 0, 255}, 0.25f),   // Green at value 0.5
			std::make_tuple(SDL_Color{255, 255, 0, 255}, 0.5f), // Yellow at value 0.6
			std::make_tuple(SDL_Color{255, 127, 0, 255}, 0.75f), // Orange at value 0.8
			std::make_tuple(SDL_Color{255, 0, 0, 255}, 1.0f)    // Red at value 1.0
	};

	color_gradient = ColorGradient(colors);
}


void JuliaFractal::update(f32 _zoom)
{
	// make zoom non linear
	zoom = expf(5 * _zoom - 5);
}

void JuliaFractal::draw()
{

	// add threads to vector
	while (size(rendering_threads) < MAX_THREADS)
	{
		rendering_threads.emplace_back(&JuliaFractal::process_lines, this, size(rendering_threads) * LINES_PER_THREAD, LINES_PER_THREAD);
	}

	for (auto& thread : rendering_threads)
	{
		thread.join();
	}

	// Clear the vector to remove all threads
	rendering_threads.clear();
}

void JuliaFractal::process_lines(const u16 start_y, const u16 line_count)
{
	// process each line
	for (u16 y = start_y; y < start_y + line_count; y++)
	{
		for (u16 x = 0; x < WND_WIDTH; x++)
		{
			// calculate place on the graph (unit circle)
			const v2 plot_pos = ((v2(x - WND_WIDTH_HALF,
								y - WND_HEIGHT_HALF)) * SPACE_SCALE) * zoom + displacement;

			// get number og iteration
			const u8 iter = julia(plot_pos);

			// callculate value from range [0, 1] ... TODO: maybe non linear?
			const f32 value = (f32)iter / max_iter;


			// draw pixel in buffer
			if (use_gradient)
				ctx.buff[y * WND_WIDTH + x] = color_gradient.get_color(value);
			else
				ctx.buff[y * WND_WIDTH + x] = RGB_to_u32(value * 255, value * 255, value * 255);
		}

	}
}

u8 JuliaFractal::julia(const v2& z0)
{
	v2 zn = z0;

	u8 iteration{ 0 };
	while (v2::dotProduct(zn, zn) < 4.0f && iteration < max_iter)
	{
		zn = v2(zn.x * zn.x - zn.y * zn.y, 2.0f * zn.x * zn.y) + _const;

		iteration++;
	}

	return iteration;
}
