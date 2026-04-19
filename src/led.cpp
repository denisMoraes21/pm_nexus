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
    int count = 0;
    while (count < seconds)
    {
        led::ledON();
        delay(500);

        led::ledOFF();
        delay(500);
        count++;
    }
}

void led::initLed()
{
    pinMode(PINO_LED, OUTPUT);
}