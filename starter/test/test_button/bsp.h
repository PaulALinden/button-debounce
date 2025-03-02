#ifndef BSP_H
#define BSP_H

#include <stdint.h>

#define BSP_LOW 0
#define BSP_HIGH 1
#define BSP_INPUT_PULLUP 0x05

void bsp_pin_mode(uint8_t pin, uint8_t mode);
int bsp_digital_read(uint8_t pin);
void bsp_set_pin_state(uint8_t pin, uint8_t state);

#endif /* BSP_H */