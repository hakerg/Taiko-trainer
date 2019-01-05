#pragma once
#include <allegro5\allegro.h>
#include <chrono>
#include "math_defines.h"
#include "Vector2D.h"

#define BACKGROUND_COLOR al_map_rgb(0, 0, 0)
#define BLACK_BAR_COLOR al_map_rgb(32, 32, 32)
#define INNER_TARGET_COLOR al_map_rgb(72, 72, 72)
#define OUTER_TARGET_COLOR al_map_rgb(128, 128, 128)
#define PINK_SQUARE_COLOR al_map_rgb(255, 64, 128)
#define KEYS_OVERLAY_COLOR al_map_rgb(255, 240, 224)

#define CIRCLE_DON_COLOR al_map_rgb(235, 69, 44)
#define CIRCLE_KATSU_COLOR al_map_rgb(67, 142, 172)
#define CIRCLE_BACKGROUND_COLOR al_map_rgb(0, 0, 0)
#define CIRCLE_OVERLAY_COLOR al_map_rgb(255, 255, 255)


const uc::Vector2D<unsigned> SCREEN_SIZE(800, 600);
const unsigned SUB_FRAME_BUFFER_SIZE = 8;
const unsigned MAX_REGISTERED_HITS = 256;
const double INIT_SROLLING_SPEED = 800.0;
const double SROLLING_SPEED_STEP = 80.0;
const double INIT_BPM = 120.0;
const double BPM_STEP = 5.0;
const std::chrono::seconds READY_TIME(3);
const std::chrono::seconds CIRCLE_APPEAR_TIME(1);
const std::chrono::seconds CIRCLE_DISAPPEAR_TIME(1);
const double KEYS_OVERLAY_DAMPING = PI;


const float BLACK_BAR_X1 = 0.0f;
const float BLACK_BAR_Y1 = 177.0f;
const float BLACK_BAR_X2 = 800.0f;
const float BLACK_BAR_Y2 = 317.0f;

const float TARGET_X = 199.5f;
const float TARGET_Y = 245.5f;
const float INNER_TARGET_RADIUS = 35.0f;
const float OUTER_TARGET_RADIUS = 39.0f;
const float OUTER_TARGET_THICKNESS = 2.5f;

const float PINK_SQUARE_X1 = 0.0f;
const float PINK_SQUARE_Y1 = 176.0f;
const float PINK_SQUARE_X2 = 138.0f;
const float PINK_SQUARE_Y2 = 316.0f;

const float KEYS_OVERLAY_X = 70.75f;
const float KEYS_OVERLAY_Y = 246.5f;
const float KEYS_OVERLAY_RADIUS_X = 57.75f;
const float KEYS_OVERLAY_RADIUS_Y = 51.5f;
const float KEYS_OVERLAY_INNER_RADIUS_X = KEYS_OVERLAY_RADIUS_X * SQRT1_2;
const float KEYS_OVERLAY_INNER_RADIUS_Y = KEYS_OVERLAY_RADIUS_Y * SQRT1_2;
const float KEYS_OVERLAY_THICKNESS = 5.0f;


const float SMALL_CIRCLE_BACKGROUND_RADIUS = 35.0f;
const float SMALL_CIRCLE_INNER_RADIUS = 28.5f;
const float SMALL_CIRCLE_OVERLAY_RADIUS = 32.0f;
const float SMALL_CIRCLE_OVERLAY_THICKNESS = 4.0f;


const int FONT_SIZE = 30;