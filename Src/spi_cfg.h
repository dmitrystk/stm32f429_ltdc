#pragma once

#include <stdint.h>

void SPI5_IO_Init(void);
void SPI5_Core_Init(void);

void SPI_Write_Byte(SPI_TypeDef* hw, uint8_t data);
void SPI_Write_Buf(SPI_TypeDef* hw, uint8_t* buf, uint32_t len);

