#pragma once

#define SDRAM_BASE 0xD0000000
#define SDRAM_SIZE 0x00800000

void SDRAM_IO_Init(void);
void SDRAM_Init(void);
