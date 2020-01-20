#include "stm32f4xx.h"
#include "spi_cfg.h"
#include "gpio_cfg.h"

__inline void SPI5_IO_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    
    Pin_Cfg(GPIOF, 7, MODER_AF, OTYPER_PP, OSPEEDR_HIGH, PUPDR_PULL_NONE, AF_5);    // SPI5_SCK
    Pin_Cfg(GPIOF, 9, MODER_AF, OTYPER_PP, OSPEEDR_HIGH, PUPDR_PULL_NONE, AF_5);    // SPI5_MISO
}

__inline void SPI5_Core_Init(void)
{
    RCC->APB2ENR |= RCC_APB2ENR_SPI5EN;
    SPI5->CR1 = SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE | SPI_CR1_MSTR | SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_1 | SPI_CR1_BR_0;
    SPI5->CR1 |= SPI_CR1_SPE;
}

__inline void SPI_Write_Byte(SPI_TypeDef* hw, uint8_t data)
{
    while (! (hw->SR & SPI_SR_TXE)){};
    (*(volatile uint8_t*)((uint32_t)&(hw->DR))) = data;
    while (! (hw->SR & SPI_SR_TXE)){};
    while (hw->SR & SPI_SR_BSY){};
}

__inline void SPI_Write_Buf(SPI_TypeDef* hw, uint8_t* buf, uint32_t len)
{
    while (len--)
    {
        while (! (hw->SR & SPI_SR_TXE)){};
        (*(volatile uint8_t*)((uint32_t)&(hw->DR))) = *(buf++);
    }
    while (! (hw->SR & SPI_SR_TXE)){};
    while (hw->SR & SPI_SR_BSY){};
}
