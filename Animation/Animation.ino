
//Walk LED

#include "FastLED.h"

#define NUM_LEDS 24
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

const int SPEED = 100;


void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}

int i = 0;
void loop() {
  leds[i % NUM_LEDS] = CRGB::Black;
  leds[(i+1) % NUM_LEDS] = ColorFromPalette(RainbowColors_p, (i+1) % 255);
  FastLED.show();
  delay(SPEED);
  i++;
}
