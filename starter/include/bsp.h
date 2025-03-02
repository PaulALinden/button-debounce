#ifndef BSP_H
#define BSP_H

#include <Arduino.h>

#define BSP_LOW LOW
#define BSP_HIGH HIGH
#define BSP_INPUT_PULLUP INPUT_PULLUP

static inline void bsp_pin_mode(uint8_t pin, uint8_t mode) { pinMode(pin, mode); }

static inline int bsp_digital_read(uint8_t pin) { return digitalRead(pin); }

#endif /* BSP_H */