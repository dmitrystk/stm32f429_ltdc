#pragma once

#include "stm32f4xx.h"
#include <stdint.h>

typedef enum
{
    MODER_INPUT,
    MODER_GPIO,
    MODER_AF,
    MODER_ANALOG
} GPIO_MODER_Type;

typedef enum
{
    OTYPER_PP,
    OTYPER_OD
} GPIO_OTYPER_Type;

typedef enum
{
    OSPEEDR_LOW,
    OSPEEDR_MEDIUM,
    OSPEEDR_HIGH,
    OSPEEDR_VERY_HIGH
} GPIO_OSPEEDR_Type;

typedef enum
{
    PUPDR_PULL_NONE,
    PUPDR_PULL_UP,
    PUPDR_PULL_DOWN
} GPIO_PUPDR_Type;

typedef enum
{
    AF_0,
    AF_1,
    AF_2,
    AF_3,
    AF_4,
    AF_5,
    AF_6,
    AF_7,
    AF_8,
    AF_9,
    AF_10,
    AF_11,
    AF_12,
    AF_13,
    AF_14,
    AF_15,
    AF_NONE
} GPIO_AF_Type;

#define MASK1BIT(pin)   ((uint32_t)~(1 << (pin * 1)))
#define MASK2BIT(pin)   ((uint32_t)~(3 << (pin * 2)))
#define MASK4BIT(pin)   ((uint32_t)~(15 << (pin * 4)))
#define AFMASKL(pin)	((uint32_t)~(15 << (pin * 4)))
#define AFMASKH(pin)	((uint32_t)~(15 << ((pin - 8) * 4)))

void Pin_Cfg(GPIO_TypeDef * GPIO, uint8_t pin, GPIO_MODER_Type mode, GPIO_OTYPER_Type type, GPIO_OSPEEDR_Type speed, GPIO_PUPDR_Type pull, GPIO_AF_Type af);
