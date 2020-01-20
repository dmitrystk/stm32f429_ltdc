#include "stm32f4xx.h"
#include "ili9341.h"
#include "spi_cfg.h"
#include "delay.h"
#include "gpio_cfg.h"

void ili9341_IO_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN | RCC_AHB1ENR_GPIODEN;
    
    Pin_Cfg(GPIOD, 13, MODER_GPIO, OTYPER_PP, OSPEEDR_VERY_HIGH, PUPDR_PULL_NONE, AF_NONE);   // LCD_WRX
    Pin_Cfg(GPIOC,  2, MODER_GPIO, OTYPER_PP, OSPEEDR_VERY_HIGH, PUPDR_PULL_NONE, AF_NONE);   // LCD_NCS
}

void ili9341_Init(void)
{
    // Configure LCD
    ili9341_Write_Cmd(0xCA);
    ili9341_Write_Data(0xC3);
    ili9341_Write_Data(0x08);
    ili9341_Write_Data(0x50);
    ili9341_Write_Cmd(LCD_POWERB);
    ili9341_Write_Data(0x00);
    ili9341_Write_Data(0xC1);
    ili9341_Write_Data(0x30);
    ili9341_Write_Cmd(LCD_POWER_SEQ);
    ili9341_Write_Data(0x64);
    ili9341_Write_Data(0x03);
    ili9341_Write_Data(0x12);
    ili9341_Write_Data(0x81);
    ili9341_Write_Cmd(LCD_DTCA);
    ili9341_Write_Data(0x85);
    ili9341_Write_Data(0x00);
    ili9341_Write_Data(0x78);
    ili9341_Write_Cmd(LCD_POWERA);
    ili9341_Write_Data(0x39);
    ili9341_Write_Data(0x2C);
    ili9341_Write_Data(0x00);
    ili9341_Write_Data(0x34);
    ili9341_Write_Data(0x02);
    ili9341_Write_Cmd(LCD_PRC);
    ili9341_Write_Data(0x20);
    ili9341_Write_Cmd(LCD_DTCB);
    ili9341_Write_Data(0x00);
    ili9341_Write_Data(0x00);
    ili9341_Write_Cmd(LCD_FRMCTR1);
    ili9341_Write_Data(0x00);
    ili9341_Write_Data(0x1B);
    ili9341_Write_Cmd(LCD_DFC);
    ili9341_Write_Data(0x0A);
    ili9341_Write_Data(0xA2);
    ili9341_Write_Cmd(LCD_POWER1);
    ili9341_Write_Data(0x10);
    ili9341_Write_Cmd(LCD_POWER2);
    ili9341_Write_Data(0x10);
    ili9341_Write_Cmd(LCD_VCOM1);
    ili9341_Write_Data(0x45);
    ili9341_Write_Data(0x15);
    ili9341_Write_Cmd(LCD_VCOM2);
    ili9341_Write_Data(0x90);
    ili9341_Write_Cmd(LCD_MAC);
    ili9341_Write_Data(0xC8);
    ili9341_Write_Cmd(LCD_3GAMMA_EN);
    ili9341_Write_Data(0x00);
    ili9341_Write_Cmd(LCD_RGB_INTERFACE);
    ili9341_Write_Data(0xC2);
    ili9341_Write_Cmd(LCD_DFC);
    ili9341_Write_Data(0x0A);
    ili9341_Write_Data(0xA7);
    ili9341_Write_Data(0x27);
    ili9341_Write_Data(0x04);

    // Colomn address set
    ili9341_Write_Cmd(LCD_COLUMN_ADDR);
    ili9341_Write_Data(0x00);
    ili9341_Write_Data(0x00);
    ili9341_Write_Data(0x00);
    ili9341_Write_Data(0xEF);
    // Page address set
    ili9341_Write_Cmd(LCD_PAGE_ADDR);
    ili9341_Write_Data(0x00);
    ili9341_Write_Data(0x00);
    ili9341_Write_Data(0x01);
    ili9341_Write_Data(0x3F);
    ili9341_Write_Cmd(LCD_INTERFACE);
    ili9341_Write_Data(0x01);
    ili9341_Write_Data(0x00);
    ili9341_Write_Data(0x06);
    ili9341_Write_Cmd(LCD_GRAM);
    delay_ms(200);

    ili9341_Write_Cmd(LCD_GAMMA);
    ili9341_Write_Data(0x01);

    ili9341_Write_Cmd(LCD_PGAMMA);
    ili9341_Write_Data(0x0F);
    ili9341_Write_Data(0x29);
    ili9341_Write_Data(0x24);
    ili9341_Write_Data(0x0C);
    ili9341_Write_Data(0x0E);
    ili9341_Write_Data(0x09);
    ili9341_Write_Data(0x4E);
    ili9341_Write_Data(0x78);
    ili9341_Write_Data(0x3C);
    ili9341_Write_Data(0x09);
    ili9341_Write_Data(0x13);
    ili9341_Write_Data(0x05);
    ili9341_Write_Data(0x17);
    ili9341_Write_Data(0x11);
    ili9341_Write_Data(0x00);
    ili9341_Write_Cmd(LCD_NGAMMA);
    ili9341_Write_Data(0x00);
    ili9341_Write_Data(0x16);
    ili9341_Write_Data(0x1B);
    ili9341_Write_Data(0x04);
    ili9341_Write_Data(0x11);
    ili9341_Write_Data(0x07);
    ili9341_Write_Data(0x31);
    ili9341_Write_Data(0x33);
    ili9341_Write_Data(0x42);
    ili9341_Write_Data(0x05);
    ili9341_Write_Data(0x0C);
    ili9341_Write_Data(0x0A);
    ili9341_Write_Data(0x28);
    ili9341_Write_Data(0x2F);
    ili9341_Write_Data(0x0F);

    ili9341_Write_Cmd(LCD_SLEEP_OUT);
    delay_ms(200);
    ili9341_Write_Cmd(LCD_DISPLAY_ON);
    // GRAM start writing
    ili9341_Write_Cmd(LCD_GRAM);
}

void ili9341_NCS_High(void)
{
    GPIOC->BSRR = 1 << 2;
}

void ili9341_NCS_Low(void)
{
    GPIOC->BSRR = 1 << (2 + 16);
}

void ili9341_WRX_High(void)
{
    GPIOD->BSRR = 1 << 13;
}

void ili9341_WRX_Low(void)
{
    GPIOD->BSRR = 1 << (13 + 16);
}

void ili9341_Write_Cmd(uint8_t address)
{
    ili9341_WRX_Low();

    ili9341_NCS_Low();
    SPI_Write_Byte(SPI5, address);
    ili9341_NCS_High();
}

void ili9341_Write_Data(uint8_t value)
{
    ili9341_WRX_High();

    ili9341_NCS_Low();
    SPI_Write_Byte(SPI5, value);
    ili9341_NCS_High();
}
