#include "bsp.h"
#include "button.h"

#define BUTTON_PIN 34

static hw_timer_t *timer = NULL;
static volatile bool updateFlag = false;

void IRAM_ATTR onTimer()
{
    updateFlag = true;
}

void setup()
{
    Serial.begin(115200);
    button_init(BUTTON_PIN);
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 2000, true);
    timerAlarmEnable(timer);
}

void loop()
{
    if (updateFlag)
    {
        button_update_state();
        if (button_get_state() == BUTTON_FALLING_EDGE)
        {
            Serial.println("Falling edge");
        }
        updateFlag = false;
    }
}
