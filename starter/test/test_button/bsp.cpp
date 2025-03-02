#include "bsp.h"

static uint8_t last_state = 0;      

void bsp_pin_mode(uint8_t pin, uint8_t mode)
{
    (void)pin; 
    (void)mode; 
}

int bsp_digital_read(uint8_t pin)
{
    (void)pin;
    return last_state;
}

void bsp_set_pin_state(uint8_t pin, uint8_t state)
{
    (void)pin;
    last_state = state; 
}