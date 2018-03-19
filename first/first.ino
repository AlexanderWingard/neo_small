#include "FastLED.h"
#define NUM_LEDS 16
#define DATA_PIN 7
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(1000);
  
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(1000);
}
