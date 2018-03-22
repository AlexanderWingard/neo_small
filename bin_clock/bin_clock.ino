#include "FastLED.h"
#define NUM_LEDS 12
#define DATA_PIN 0
CRGB leds[NUM_LEDS];


void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(20);
}

void loop() {
  unsigned long ts = millis();
  int minute = (ts / 1000 / 60);
  int ms = ts % 1000;

  leds[mod(8, NUM_LEDS)] = CRGB::White;
  leds[mod(8, NUM_LEDS)].fadeLightBy(map(cubicwave8(map(ms, 0, 1000, 0, 255)), 0, 255, 0, 255));
  for(uint8_t i = 1; i < NUM_LEDS; i++) {
    leds[mod(8+i, NUM_LEDS)] = bitRead(minute, i-1) == 1 ? ColorFromPalette(RainbowColors_p, map(i, 1, NUM_LEDS, 0, 255)) : CRGB::Black;
  }
  FastLED.show();
}

int mod( int x, int y ){
   return x<0 ? ((x+1)%y)+y-1 : x%y;
}

