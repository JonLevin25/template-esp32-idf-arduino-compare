#include <Arduino.h>

#define BLINK_GPIO CONFIG_BLINK_GPIO
#define BLINK_DELAY 1000

void setup()
{
    Serial.begin(115200);
    pinMode(BLINK_GPIO, OUTPUT);
}

void loop()
{
    Serial.println("led on");
    digitalWrite(BLINK_GPIO, HIGH);
    delay(BLINK_DELAY);
    
    Serial.println("led off");
    digitalWrite(BLINK_GPIO, LOW);
    delay(BLINK_DELAY);
}