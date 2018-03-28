#include "FastLED.h"
#define NUM_LEDS 12
#define DATA_PIN 0
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  
  int r = random(0, NUM_LEDS);
  leds[r] = CRGB::Red;
  
  FastLED.show();
  delay(1000);
}
