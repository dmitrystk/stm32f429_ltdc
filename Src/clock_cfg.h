#pragma once

#define HSE_STARTUP_TIMEOUT 500
/************************* PLL Parameters *************************************/
// PLL_VCO = (HSE_VALUE or HSI_VALUE / PLL_M) * PLL_N
#define PLL_M      4
#define PLL_N      180
// SYSCLK = PLL_VCO / PLL_P
#define PLL_P      2
// USB OTG FS, SDIO and RNG Clock =  PLL_VCO / PLLQ
#define PLL_Q       8

/************************* PLLSAI Parameters *************************************/
// PLLLCDCLK = (HSE_VALUE or HSI_VALUE / PLL_M) * PLLSAI_N / PLLSAI_R / PLLSAI_DIVR(3)
// HSE = 8MHz =>  PLLLCDCLK = ‭6,34375‬MHz

#define PLLSAI_N     203
#define PLLSAI_R     4
#define PLLSAI_DIVR  3
#define PLLSAI_Q     4

void Clock_Init(void);
void PLLSAI_Init(void);

