#include "button.h"
#include "bsp.h"
#include "unity.h"

#define BUTTON_PIN 34

//Help function to simulate repeated updates on button
static void repeat_button_update(uint8_t pin_state, size_t updates)
{
    bsp_set_pin_state(BUTTON_PIN, pin_state);
    for (size_t i = 0; i < updates; i++)
    {
        button_update_state();
    }
}

void test_button_uninitialized(void)
{
    TEST_ASSERT_EQUAL_UINT8(BUTTON_UNINITIALIZED, button_get_state());
    TEST_ASSERT_EQUAL(BSP_INPUT_PULLUP, button_get_mode());
    TEST_ASSERT_EQUAL(255, button_get_pin());
    TEST_ASSERT_FALSE(button_is_stable());
}

void test_button_initialized(void)
{
    button_init(BUTTON_PIN);
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
    TEST_ASSERT_EQUAL(BSP_INPUT_PULLUP,button_get_mode());
    TEST_ASSERT_EQUAL(BUTTON_PIN, button_get_pin());
}

void test_button_pressed(void)
{
    button_init(BUTTON_PIN);
    repeat_button_update(BSP_LOW, 5);
    TEST_ASSERT_EQUAL_UINT8(BUTTON_PRESSED, button_get_state());
}

void test_button_released(void)
{
    button_init(BUTTON_PIN);
    repeat_button_update(BSP_HIGH, 5);
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
}

void test_button_rising_edge(void)
{
    button_init(BUTTON_PIN);
    repeat_button_update(BSP_LOW, 5); //Set state to pressed
    bsp_set_pin_state(BUTTON_PIN, BSP_HIGH);
    button_update_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RISING_EDGE, button_get_state());
}

void test_button_falling_edge(void)
{
    button_init(BUTTON_PIN);
    repeat_button_update(BSP_HIGH, 5);//Set state to released
    bsp_set_pin_state(BUTTON_PIN, BSP_LOW);
    button_update_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_FALLING_EDGE, button_get_state());
}

void test_button_stable_pressed(void)
{
    button_init(BUTTON_PIN);
    repeat_button_update(BSP_LOW, 5);
    TEST_ASSERT_EQUAL_UINT8(BUTTON_PRESSED, button_get_state());
    TEST_ASSERT_TRUE(button_is_stable());

    button_update_state(); // Extra call for ensuring stable state after 5.
    TEST_ASSERT_EQUAL_UINT8(BUTTON_PRESSED, button_get_state());
    TEST_ASSERT_TRUE(button_is_stable());
}

void test_button_stable_released(void)
{
    button_init(BUTTON_PIN);
    repeat_button_update(BSP_HIGH, 5);
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
    TEST_ASSERT_TRUE(button_is_stable());
    
    button_update_state(); // Extra call for ensuring stable state after 5.
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
    TEST_ASSERT_TRUE(button_is_stable());
}

void test_button_unstable_state(void)
{
    button_init(BUTTON_PIN);
    bsp_set_pin_state(BUTTON_PIN, BSP_LOW);
    button_update_state(); // RISING_EDGE
    TEST_ASSERT_EQUAL_UINT8(BUTTON_FALLING_EDGE, button_get_state());
    TEST_ASSERT_FALSE(button_is_stable());// Unstable

    bsp_set_pin_state(BUTTON_PIN, BSP_HIGH);
    button_update_state(); // FALLING_EDGE
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RISING_EDGE, button_get_state());
    TEST_ASSERT_FALSE(button_is_stable()); // Unstable

    bsp_set_pin_state(BUTTON_PIN, BSP_LOW);
    button_update_state(); // RISING_EDGE
    TEST_ASSERT_EQUAL_UINT8(BUTTON_FALLING_EDGE, button_get_state());
    TEST_ASSERT_FALSE(button_is_stable()); // Unstable
}

void test_button_debouncing(void)
{
    button_init(BUTTON_PIN);
    repeat_button_update(BSP_LOW, 3);
    TEST_ASSERT_EQUAL_UINT8(BUTTON_PRESSED, button_get_state());
    TEST_ASSERT_FALSE(button_is_stable());

    repeat_button_update(BSP_HIGH, 3);
    button_update_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RELEASED, button_get_state());
    TEST_ASSERT_FALSE(button_is_stable());
}

void setUp(void)
{
}
void tearDown(void)
{
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_button_uninitialized);
    RUN_TEST(test_button_initialized);
    RUN_TEST(test_button_pressed);
    RUN_TEST(test_button_released);
    RUN_TEST(test_button_rising_edge);
    RUN_TEST(test_button_falling_edge);
    RUN_TEST(test_button_stable_pressed);
    RUN_TEST(test_button_stable_released);
    RUN_TEST(test_button_unstable_state);
    RUN_TEST(test_button_debouncing);
    return UNITY_END(); 
}
