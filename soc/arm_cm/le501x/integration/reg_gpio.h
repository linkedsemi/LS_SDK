#ifndef REG_GPIO_H_
#define REG_GPIO_H_
#include "reg_gpio_type.h"
#include "reg_exti_type.h"

#define LSGPIOA ((reg_lsgpio_t *)(0x48000000))
#define LSGPIOB ((reg_lsgpio_t *)(0x48000400))
#define LSGPIOC ((reg_lsgpio_t *)(0x48000800))
#define EXTI    ((reg_lsexti_t *)(0x40010400))


#endif //(REG_LSGPIO_H_)
