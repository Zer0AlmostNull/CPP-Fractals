#include "types.h"
#include "math.h"

#include "macros.h"

#pragma once

// ---------- SCREEN ---------

const u16 WND_WIDTH = 1280;
const u16 WND_HEIGHT = 720;

const u16 WND_WIDTH_HALF = WND_WIDTH / 2;
const u16 WND_HEIGHT_HALF = WND_HEIGHT / 2;

const u32 PIXEL_COUNT = WND_WIDTH * WND_HEIGHT;

const f32 SPACE_SCALE = 1.0f / min(WND_HEIGHT_HALF, WND_WIDTH_HALF);


// ------- multithreading ------
const u8 MAX_THREADS = 4;
const u16 LINES_PER_THREAD = WND_HEIGHT / MAX_THREADS;


