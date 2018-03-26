
//Fade LED

#include "FastLED.h"

#define NUM_LEDS 24
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

const int LED = 0; // which LED to fade?
byte hue, saturation;

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);

  hue = 10;
  saturation = 255; 
}

void loop() {

  for(int brightness = 0; brightness < 256; brightness++) {
    leds[LED] = CHSV(hue, saturation, brightness);
    FastLED.show();
    delay(5);
  }
  
  for(int brightness = 255; brightness >= 0; brightness--) {
    leds[LED] = CHSV(hue, saturation, brightness);
    FastLED.show();
    delay(5);
  }

  delay(100);
}
