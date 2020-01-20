#include "delay.h"

volatile uint32_t CountMS = 0;

uint32_t get_CountMS(void)
{
    return CountMS;
}

void delay_ms(uint32_t ms)
{
    uint32_t temp = CountMS;
    while ((CountMS - temp) < ms){};
}

void SysTick_Handler(void)
{
    CountMS++;
}
