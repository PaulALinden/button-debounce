#include "button.h"
#include "bsp.h"
#include <iostream>

#define STABLE_LIMIT 5
#define UNINITIALIZED_PIN 255

typedef struct
{
    const uint8_t mode;
    const uint8_t stable_limit;
    uint8_t pin;
    uint8_t count;
    uint8_t previous_state;
    uint8_t state;
} button_t;

static button_t button = {BSP_INPUT_PULLUP, STABLE_LIMIT, UNINITIALIZED_PIN, 0, 0, BUTTON_UNINITIALIZED};

void button_init(uint8_t pin)
{
    button.pin = pin;
    bsp_pin_mode(button.pin, button.mode);
    button.state = BUTTON_RELEASED;
}

void button_update_state(void)
{
    uint8_t current_state = bsp_digital_read(button.pin);

    if (current_state != button.previous_state)
    {
        button.count = 1;
    }
    else
    {
        button.count++;
    }

    if (current_state == BSP_LOW && button.state != BUTTON_PRESSED)
    {
        if (button.count == 1)
        {
            button.state = BUTTON_FALLING_EDGE;
        }
        else
        {
            button.state = BUTTON_PRESSED;
        }
    }
    else if (current_state == BSP_HIGH && button.state != BUTTON_RELEASED)
    {
        if (button.count == 1)
        {
            button.state = BUTTON_RISING_EDGE;
        }
        else
        {
            button.state = BUTTON_RELEASED;
        }
    }

    button.previous_state = current_state;
}

uint8_t button_get_state(void)
{
    return button.state;
}

uint8_t button_get_pin(void)
{
    return button.pin;
}

uint8_t button_get_mode(void)
{
    return button.mode;
}

bool button_is_stable(void)
{
    if (button.pin == UNINITIALIZED_PIN)
    {
        return false;
    }

    return (button.count >= button.stable_limit);
}

