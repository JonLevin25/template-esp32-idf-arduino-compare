#include <Arduino.h>

#define DELAY_MS 1000
#define BAUDRATE 9600
#define MSG "Msg from ARDUINO FW"

void setup()
{
    Serial.begin(115200);
    Serial2.begin(BAUDRATE, SERIAL_8N1, 16, 17); // TODO: what is "inverted?" MSB vs LSB first?
}

void loop()
{
    while (Serial2.available()) {
        String str = Serial2.readString();
        Serial.println(str);
    }

    if (Serial2.availableForWrite()) {
        Serial2.write(MSG);
    }

    delay(DELAY_MS);
}
