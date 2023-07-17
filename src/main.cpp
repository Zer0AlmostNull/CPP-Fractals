#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include <iostream>
#include <memory>
#include <vector>


#include "julia_fractal.h"

#include "UISlider.h"
#include "UIButton.h"
#include "UILabel.h"
#include "UICheckbox.h"


#include "types.h"
#include "settings.h"
#include "macros.h"
#include "render_context.h"


RenderContext rc;
bool render_ui = true;

void save_to_file(std::string path = "./img.bmp");

int main(int argc, char* args[])
{
    // Init SDL
    ASSERT(!SDL_Init(SDL_INIT_EVERYTHING),
        "SDL failed to initialize: %s\n",
        SDL_GetError());

    ASSERT(!TTF_Init(),
        "SDL_TTF failed to initialize: %s\n",
        TTF_GetError());


    // create window
    rc.window = SDL_CreateWindow("Fractals", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WND_WIDTH, WND_HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    ASSERT(rc.window, "Failed to initialize window: %s\n", SDL_GetError());

    // create renderer  
    rc.renderer = SDL_CreateRenderer(rc.window, -1, SDL_RENDERER_PRESENTVSYNC);
    ASSERT(rc.renderer, "Failed to initialize renderer: %s\n", SDL_GetError());

    // Create a streaming texture
    rc.texture = SDL_CreateTexture(rc.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WND_WIDTH, WND_HEIGHT);
    ASSERT(rc.texture, "Failed to initialize texture: %s\n", SDL_GetError());

    // init fractal
    JuliaFractal fract(rc);

    // setup drawing threadr
    bool _is_drawing = true;
    std::thread drawing_thread;

    // start drawing
    drawing_thread = std::thread([&]() {
        fract.draw();
        _is_drawing = false;
        });


    // Create UI elements
    // open font
    TTF_Font* pixel_font = TTF_OpenFont("./assets/fonts/PressStart2P-Regular.ttf", 24);
    ASSERT(pixel_font, "Filed to load font: %s\n", TTF_GetError());

    // its able to hide all ui
    UIButton toggle_ui_button{rc,
        SDL_Rect({ WND_WIDTH-100, WND_HEIGHT - 70, 100, 70 }),
        "toggle ui", 90, 30, pixel_font,
        SDL_Color({ 255, 0, 0 }),
        SDL_Color({ 122, 0, 0 }),
        SDL_Color({ 255, 255, 255 }),
        []() { render_ui = !render_ui; } // Use the correct lambda capture syntax
    };


    // manipulation variables
    f32 slider_max_iter = fract.max_iter;
    f32 slider_prev_zoom = 1.0f;
    f32 slider_zoom = 1.0f;

    const u8 ui_margin = 20;
    const u8 ui_height = 30;
    const u8 ui_width = 100;

    // polymorphism ++
    std::vector<std::unique_ptr<UIElement>> ui_elements;

    // SLIDERS
    ui_elements.push_back(std::make_unique<UISlider>(rc,
        SDL_Rect({ ui_margin, ui_margin, ui_width, ui_height }), 10,
        fract._const.x, -1.0f, 1.0f, 0));
    ui_elements.push_back(std::make_unique<UISlider>(rc,
        SDL_Rect({ ui_margin, ui_margin * 2 + ui_height, ui_width, ui_height}), 10,
        fract._const.y, -1.0f, 1.0f, .5f));
    ui_elements.push_back(std::make_unique<UISlider>(rc,
        SDL_Rect({ WND_WIDTH - ui_width - ui_margin, ui_margin, ui_width, ui_height}), 10,
        slider_max_iter, 2, 300, slider_max_iter / 300));
    ui_elements.push_back(std::make_unique<UISlider>(rc,
        SDL_Rect({ WND_WIDTH - ui_width - ui_margin, ui_margin * 2 + ui_height, ui_width, ui_height}), 10,
        slider_zoom, 0, 1.1f, 1));
    ui_elements.push_back(std::make_unique<UISlider>(rc,
        SDL_Rect({ WND_WIDTH - ui_width - ui_margin, ui_margin * 3 + 2 * ui_height, ui_width, ui_height }), 10,
        fract.displacement.x, -.5f, .5f, .5));
    ui_elements.push_back(std::make_unique<UISlider>(rc,
        SDL_Rect({ WND_WIDTH - ui_width - ui_margin, ui_margin * 4 + 3 * ui_height, ui_width, ui_height }), 10,
        fract.displacement.y, -.5f, .5f, .5));

    // LABELS
    ui_elements.push_back(std::make_unique<UILabel>(rc, "a:", 
       SDL_Rect({0, ui_margin + ui_height / 2 - 10, 20, 20}), 
       SDL_Color{255, 255, 255 }, 
       pixel_font));
    ui_elements.push_back(std::make_unique<UILabel>(rc, "b:",
      SDL_Rect({0, ui_margin * 2 + ui_height + ui_height / 2 - 10, 20, 20 }),
      SDL_Color{255, 255, 255 },
      pixel_font));
    ui_elements.push_back(std::make_unique<UILabel>(rc, "iteration:",
      SDL_Rect({WND_WIDTH - ui_width - ui_margin - 110, ui_margin, 110, 25 }),
      SDL_Color{255, 255, 255 },
      pixel_font));
    ui_elements.push_back(std::make_unique<UILabel>(rc, "zoom:",
      SDL_Rect({WND_WIDTH - ui_width - ui_margin - 110, 2 * ui_margin + ui_height, 70, 25 }),
      SDL_Color{255, 255, 255 },
      pixel_font));
    ui_elements.push_back(std::make_unique<UILabel>(rc, "dx:",
        SDL_Rect({ WND_WIDTH - ui_width - ui_margin - 110, 3 * ui_margin + 2 * ui_height, 50, 25 }),
        SDL_Color{ 255, 255, 255 },
        pixel_font));
    ui_elements.push_back(std::make_unique<UILabel>(rc, "dy:",
        SDL_Rect({ WND_WIDTH - ui_width - ui_margin - 110, 4 * ui_margin + 3 * ui_height, 50, 25 }),
        SDL_Color{ 255, 255, 255 },
        pixel_font));
    ui_elements.push_back(std::make_unique<UILabel>(rc, "gradient:",
        SDL_Rect({ WND_WIDTH - ui_width - ui_margin - 110, 5 * ui_margin + 4 * ui_height + 5, 110, 25 }),
        SDL_Color{ 255, 255, 255 },
        pixel_font));


    // BUTTONS
    // save button
    ui_elements.push_back(std::make_unique<UIButton>(rc,
        SDL_Rect({ 0,WND_HEIGHT-70, 100, 70 }),
        "save", 50, 35, pixel_font,
        SDL_Color({ 255, 0, 0}),
        SDL_Color({ 122, 0, 0 }),
        SDL_Color({ 255, 255, 255 }),
        [] { save_to_file(); }));

    // CHECKBOXES
    ui_elements.push_back(std::make_unique<UICheckbox>(rc, fract.use_gradient,
        SDL_Rect({ WND_WIDTH  - 90, 5 * ui_margin + 4 * ui_height, 40, 40}),
        SDL_Color({200, 200, 200}),
        SDL_Color({30, 30, 30})));


    // event loop
    SDL_Event windowEvent;

    // main loop
    while (1)
    {   
        // event handling
        if (SDL_PollEvent(&windowEvent))
        {
            if (windowEvent.type == SDL_QUIT)
                break;
        }

        // update fractal zoom
        if (slider_prev_zoom != slider_zoom)
        {
            slider_prev_zoom = slider_zoom;
            fract.update(slider_zoom);
        }

        // update fractal max iteration number
        if(fract.max_iter != (u16)slider_max_iter)
            fract.max_iter = (u16)slider_max_iter;

        // if drawing is finished start another
        if (!_is_drawing && drawing_thread.joinable())
        {
            drawing_thread.join();
            _is_drawing = true;

            drawing_thread = std::thread([&]() {
                fract.draw();
                _is_drawing = false;
                });
        }

        // copy buffers
        SDL_UpdateTexture(rc.texture, NULL, rc.buff, WND_WIDTH * sizeof(u32));
        SDL_RenderCopyEx(
            rc.renderer,
            rc.texture,
            NULL,
            NULL,
            0.0,
            NULL,
            SDL_FLIP_VERTICAL);
        
        // get mouse position and state
        v2_i mouse_pos(-1,-1);
        u32 mouse_state = SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);

        // draw ui elements
        if(render_ui)
        for (auto& element : ui_elements)
        {
            (*element).update(mouse_pos, mouse_state);
            (*element).draw();
        }
        toggle_ui_button.update(mouse_pos, mouse_state);
        toggle_ui_button.draw();

        SDL_RenderPresent(rc.renderer);

        // reset rendering
        SDL_SetRenderDrawColor(rc.renderer, 0, 0, 0, 255);
        SDL_RenderClear(rc.renderer);

        // reset the screen
        // std::memset(rc.buff, 0, PIXEL_COUNT * sizeof(u32));
    }

    // end drawing thread
    drawing_thread.join();


    // cleaning
    TTF_CloseFont(pixel_font);
    TTF_Quit();

    SDL_DestroyWindow(rc.window);
    SDL_Quit();
    

    return 0;
}

void save_to_file(std::string path)
{
    SDL_Surface* screenSurface = SDL_CreateRGBSurfaceWithFormatFrom(rc.buff, WND_WIDTH, WND_HEIGHT,
        32, WND_WIDTH * sizeof(u32), SDL_PIXELFORMAT_RGBA8888);

    SDL_SaveBMP(screenSurface, path.c_str());
    printf("Saved screenshot to: %s \n", path.c_str());

    SDL_FreeSurface(screenSurface);
}