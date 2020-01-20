#pragma once

#include <stdint.h>

#define MAKE_RGB(R,G,B) (uint16_t)(((R & 0x1F) << 11) | ((G & 0x3F) << 5) | (B & 0x1F))

#define COLOR_BLACK     MAKE_RGB(0,0,0)
#define COLOR_BLUE      MAKE_RGB(0,0,255)
#define COLOR_GREEN     MAKE_RGB(0,255,0)
#define COLOR_RED       MAKE_RGB(255,0,0)
#define COLOR_WHITE     MAKE_RGB(255,255,255)

void Draw_Pixel(uint16_t x, uint16_t y, uint16_t color);
void Draw_Circle (uint16_t xc, uint16_t yc, uint16_t radius, uint16_t color);

