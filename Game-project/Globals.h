#pragma once

// Screen Dimensions constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

const int METER = SCREEN_WIDTH / 32; // 32 metres across width of screen

const int GRID_ROWS = SCREEN_HEIGHT / METER;
const int GRID_COLS = SCREEN_WIDTH / METER;

const int FPS_TARGET = 60;
