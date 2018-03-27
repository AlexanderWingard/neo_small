
//Multiple Blink

#include "FastLED.h"

#define NUM_LEDS 24
#define DATA_PIN 6

CRGB leds[NUM_LEDS];

//------------------------- //
class Blinker {
  private:
    int address;
    CRGB color;
    long interval;
    bool state;
    unsigned long previousMillis;

  public:
    Blinker(int address, CRGB color, long interval);
    void blink();
    
};
// Blinker(Address, Color, Interval)
Blinker led1 = Blinker(0, CRGB::Red, 300);
Blinker led2 = Blinker(2, CRGB::Green, 100);
Blinker led3 = Blinker(4, CRGB::Yellow, 1000);
Blinker led4 = Blinker(12, CRGB::Blue, 50);


void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}


void loop() {
  led1.blink();
  led2.blink();
  led3.blink();
  led4.blink();
}






// ------ Implement Blinker class ------ //

Blinker::Blinker(int address, CRGB color, long interval) {
  this->address = address;
  this->color = color;
  this->interval = interval;
  this->previousMillis = 0;
  this->state = false;
}

void Blinker::blink() {
  if(millis() - this->previousMillis >= this->interval) {
    this->previousMillis = millis();
    if(this->state) //On? Turn it off.
      leds[this->address] = CRGB::Black;
    else // Turn it on.
      leds[this->address] = this->color;
    this->state = !this->state; // Flip state
    FastLED.show();
  }
}



