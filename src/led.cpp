#include <Arduino.h>
#include "led.h"
#include "constants.h"

void led::ledON()
{
    digitalWrite(PINO_LED, HIGH);
}

void led::ledOFF()
{
    digitalWrite(PINO_LED, LOW);
}

void led::blink(int seconds)
{
#ifdef ENABLE_LED
    int count = 0;
    while (count < seconds)
    {
        led::ledON();
        delay(500);

        led::ledOFF();
        delay(500);
        count++;
    }
#endif
}

void led::initLed()
{
#ifdef ENABLE_LED
    pinMode(PINO_LED, OUTPUT);
#endif
}