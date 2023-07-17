#include <vector>
#include <thread>

#include "render_context.h"
#include "types.h"
#include "color_gradient.h"

#include "Vector2.hpp"

#pragma once

// Julia Set -> https://en.wikipedia.org/wiki/Julia_set
class JuliaFractal
{
	RenderContext& ctx;

	std::vector<std::thread> rendering_threads;

	ColorGradient color_gradient;

	void process_lines(const u16 start_y, const u16 line_count);

public:
	// number of iteration of fractal calulation
	u16 max_iter = 200;

	// starting variable for julia's set 
	v2 _const = v2(.5f, .5f);

	// zoom of rendering camaera
	f32 zoom = 1.0f;

	// displacement of rendering samera
	v2 displacement = v2(0.0f, 0.0f);

	// indicates to draw fractal with a gradient
	bool use_gradient = false;



	JuliaFractal(RenderContext&);

	void update(f32);
	void draw();


	u8 julia(const v2& z0);

};