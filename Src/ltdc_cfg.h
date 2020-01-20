#pragma once

#include <stdint.h>

#define HSYNC               10
#define HBP                 20
#define LCD_ACTIVE_WIDTH    240
#define HFP                 10

#define VSYNC               2
#define VBP                 2
#define LCD_ACTIVE_HEIGHT   320
#define VFP                 4

#define PIXEL_WIDHT         2

void LTDC_IO_Init(void);
void LTDC_Core_Init(void);


