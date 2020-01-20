#include "stm32f4xx.h"
#include "clock_cfg.h"
#include "spi_cfg.h"
#include "ili9341.h"
#include "sdram_cfg.h"
#include "ltdc_cfg.h"
#include "drawing.h"
#include "delay.h"

#define X_MIN   (0 + 20)
#define X_MAX   ((LCD_ACTIVE_WIDTH-1) - 20)
#define Y_MIN   (0 + 20)
#define Y_MAX   ((LCD_ACTIVE_HEIGHT-1) - 20)

void SDRAM_Init(void);

int main(void)
{
    uint16_t x = 20;
    uint16_t y = 100;
    uint8_t r = 20;
    uint8_t direction = 1;
    int8_t a = -2;
    int16_t b = 100;
    uint16_t color = COLOR_BLACK;

    // Clock settings - SYSCLK 180 MHz
    Clock_Init();
    PLLSAI_Init();
    SysTick_Config(180000);

    SDRAM_IO_Init();
    SDRAM_Init();

    LTDC_IO_Init();
    LTDC_Core_Init();

    SPI5_IO_Init();
    SPI5_Core_Init();

    ili9341_IO_Init();
    ili9341_Init();

    while (1)
    {
        if ((y <= Y_MIN) || (y >= Y_MAX))
        {
            a = -a;
            b = 2*y-b;
            color = COLOR_BLUE;
        }

        if ((direction == 1) && (x == X_MAX))
        {
            direction = 0;
            a = -a;
            b = 2*y-b;
            color = COLOR_RED;
        }

        if ((direction == 0) && (x == X_MIN))
        {
            direction = 1;
            a = -a;
            b = 2*y-b;
            color = COLOR_BLACK;
        }

        if (direction == 1)
        {
            x++;
        }
            else
            {
                x--;
            }

        y = a*x + b;

        Draw_Circle(x, y, r, color);
        delay_ms(10);
        Draw_Circle(x, y, r, COLOR_WHITE);
    }
}

