#include <SPI.h>
#include "MAX31855.h"

#define RGB_BRIGHTNESS 10 // Change white brightness (max 255)
#define WAIT_FOR_SERIAL_CONNECTION true

#ifdef RGB_BUILTIN
#undef RGB_BUILTIN
#endif
#define RGB_BUILTIN 10

const int dataPin   = 4; // DO
const int clockPin  = 6; // CLK
const int selectPin = 7; // CS

MAX31855 thermoCouple(selectPin, &SPI);

float btTemp,etTemp = 0.f;

void setup() {
  neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0); // red
  if (WAIT_FOR_SERIAL_CONNECTION) {
    Serial.begin(115200);
    while (!Serial)
      ;
    Serial.println("Connected.");
  }
  neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0);
}

void loop() {
  int status = thermoCouple.read();

  if (status != STATUS_OK) {
    neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0); // red
  } else {
    neopixelWrite(RGB_BUILTIN,0,0,RGB_BRIGHTNESS); // green
    float temperature = thermoCouple.getTemperature();
    btTemp = temperature;
    etTemp = temperature;
  }

  Serial.printf("bt=%f,et=%f,status=%d\n", btTemp, etTemp, status);
  delay(500);
  neopixelWrite(RGB_BUILTIN,0,0,0); // Off
  delay(500);
}
