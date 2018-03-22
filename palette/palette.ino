#include "FastLED.h"
#define NUM_LEDS 12
#define DATA_PIN 0
CRGB leds[NUM_LEDS];


void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
}

void loop() {
  unsigned long ts = millis();
  int second = (ts / 1000) % 60;
  int c = (ts / 25) % 255;
  int ms = ts % 1000;
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i].fadeToBlackBy(1); // = CRGB::Black;
  }

  leds[mod(second+0, NUM_LEDS)] = ColorFromPalette(RainbowColors_p, c);
  //leds[mod(second+0, NUM_LEDS)].fadeLightBy(10 - cubicwave8((ms-500) * 0.255));
  FastLED.show();
}

int mod( int x, int y ){
   return x<0 ? ((x+1)%y)+y-1 : x%y;
}

