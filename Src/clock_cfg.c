#include "stm32f4xx.h"
#include "clock_cfg.h"

__inline void Clock_Init(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    // Enable HSE
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);

    // Wait till HSE is ready and if Time out is reached exit
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
        else
        {
            HSEStatus = (uint32_t)0x00;
        }

    if (HSEStatus == (uint32_t)0x01)
    {
        // Select regulator voltage output Scale 1 mode, System frequency up to 180 MHz
        RCC->APB1ENR |= RCC_APB1ENR_PWREN;
        PWR->CR |= PWR_CR_VOS;

        // HCLK = SYSCLK / 1
        RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

        // PCLK2 = HCLK / 2
        RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

        // PCLK1 = HCLK / 4
        RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

        // Configure the main PLL
        RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) | (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);

        // Enable the main PLL
        RCC->CR |= RCC_CR_PLLON;

        // Wait till the main PLL is ready
        while((RCC->CR & RCC_CR_PLLRDY) == 0){};

        // Configure Flash prefetch, Instruction cache, Data cache and wait state
        FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_LATENCY_5WS;

        // Select the main PLL as system clock source
        RCC->CFGR = (RCC->CFGR & ((uint32_t)~(RCC_CFGR_SW))) | RCC_CFGR_SW_PLL;

        // Wait till the main PLL is used as system clock source
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL){};
    }
        else
        { 
            // Hmm... Today is not my day
            while (1){};
        }
}

void PLLSAI_Init(void)
{
    // PLLSAI Init
    RCC->PLLSAICFGR = (PLLSAI_N  << 6) | (PLLSAI_Q << 24) | (PLLSAI_R << 28);
    RCC->DCKCFGR = (RCC->DCKCFGR & (~RCC_DCKCFGR_PLLSAIDIVR)) | (PLLSAI_DIVR  << 16);
    // Enable SAI PLL
    RCC->CR |= RCC_CR_PLLSAION;
    // Wait for SAI PLL ready
    while((RCC->CR & RCC_CR_PLLSAIRDY) == 0){};
}
