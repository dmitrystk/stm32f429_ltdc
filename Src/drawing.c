#include "sdram_cfg.h"
#include "ltdc_cfg.h"

void Draw_Pixel(uint16_t x, uint16_t y, uint16_t color)
{
    if ((x >= 0) && (x < LCD_ACTIVE_WIDTH) && (y >= 0) && (y < LCD_ACTIVE_HEIGHT))
    {
        *((uint16_t *) (SDRAM_BASE + (x * PIXEL_WIDHT) + (y * (LCD_ACTIVE_WIDTH * PIXEL_WIDHT)))) = color;
    }
}

void Draw_Circle(uint16_t xc, uint16_t yc, uint16_t radius, uint16_t color)
{
    for(int16_t y1=-radius; y1<=radius; y1++)
    {
        for(int16_t x1=-radius; x1<=radius; x1++)
        {
            if(x1*x1+y1*y1 <= radius*radius)
            {
                Draw_Pixel(x1+xc, y1+yc, color);
            }
        }
    }
}
