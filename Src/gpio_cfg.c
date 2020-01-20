#include "gpio_cfg.h"

void Pin_Cfg(GPIO_TypeDef * GPIO, uint8_t pin, GPIO_MODER_Type mode, GPIO_OTYPER_Type type, GPIO_OSPEEDR_Type speed, GPIO_PUPDR_Type pull, GPIO_AF_Type af)
{
    GPIO->MODER = (GPIO->MODER & ((uint32_t)~(0x03 << (pin * 2)))) | (mode << (pin * 2));
    GPIO->OTYPER = (GPIO->OTYPER & ((uint32_t)~(0x01 << pin))) | (type << pin);
    GPIO->OSPEEDR = (GPIO->OSPEEDR & ((uint32_t)~(0x03 << (pin * 2)))) | (speed << (pin * 2));
    GPIO->PUPDR = (GPIO->PUPDR & ((uint32_t)~(0x03 << (pin * 2)))) | (pull << (pin * 2));
    if (af != AF_NONE)
    {
        if (pin > 7)
        {
            GPIO->AFR[1] = (GPIO->AFR[1] & ((uint32_t)~(0x0F << ((pin - 8) * 4)))) | (af << ((pin - 8) * 4));
        }
            else
            {
                GPIO->AFR[0] = (GPIO->AFR[0] & ((uint32_t)~(0x0F << (pin * 4)))) | (af << ((pin) * 4));
            }
    }
}
