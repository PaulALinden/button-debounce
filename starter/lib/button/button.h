#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

#define BUTTON_UNINITIALIZED (0U)
#define BUTTON_FALLING_EDGE (1U)
#define BUTTON_RISING_EDGE (2U)
#define BUTTON_RELEASED (3U)
#define BUTTON_PRESSED (4U)


/**
 * @brief This function is used to initialize the module.
 *
 * @param pin The pin number used to connect a button.
 */
void button_init(uint8_t pin);

/**
 * @brief This function is used to update the debounced state of the button.
 *        This function is called intervally by the client.
 *
 */
void button_update_state(void);

/**
 * @brief This function is used to get the debounced state of the button.
 *
 * @return uint8_t The state; BUTTON_UNINITIALIZED if the module has not been initialized, otherwise
 *                            BUTTON_PRESSED, BUTTON_RELEASED, BUTTON_RISING_EDGE or BUTTON_FALLING_EDGE
 */
uint8_t button_get_state(void);
uint8_t button_get_pin(void);
uint8_t button_get_mode(void);
bool button_is_stable(void);
#endif /* BUTTON_H */