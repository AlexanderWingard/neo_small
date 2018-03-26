#include "FastLED.h"
#include <RotaryEncoder.h>

#define encoder_click_pin 3

// Setup a RoraryEncoder for pins A3 and A2:
RotaryEncoder encoder(A3, A2);

// How many leds in your strip?
#define NUM_LEDS 24


#define DATA_PIN 6
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

typedef struct pixel {
  int h;
  byte s;
  byte v;
};

pixel dial[] = {
  {189, 100, 30}, // 12
  {0, 0, 0},
  {189, 100, 1}, // 1
  {0, 0, 0},
  {189, 100, 1}, // 2
  {0, 0, 0},
  {189, 100, 30}, // 3
  {0, 0, 0},
  {189, 100, 1}, // 4
  {0, 0, 0},
  {189, 100, 1}, // 5
  {0, 0, 0},
  {189, 100, 30}, // 6
  {0, 0, 0},
  {189, 100, 1}, // 7
  {0, 0, 0},
  {189, 100, 1}, // 8
  {0, 0, 0},
  {189, 100, 30}, // 9
  {0, 0, 0},
  {189, 100, 1}, // 10
  {0, 0, 0},
  {189, 100, 1}, // 11
  {0, 0, 0},
};

const int NUM_TICKS = NUM_LEDS - 1;
double hours = 11;
double minutes = 59;
double seconds = 59;
double tickDelay = 60 / NUM_LEDS;

int state = 0;
boolean clicked = false;
void setup() {
  Serial.begin(57600);
  Serial.println("Clock... :"+ state);
  Serial.println(map(0.5, 0, 11, 0, 23));
  pinMode(encoder_click_pin, INPUT);
  digitalWrite(encoder_click_pin, HIGH);
  attachInterrupt(1, knob_pressed, RISING);
  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
  state = 0;
}

double deltaMinutes = (60.0 / NUM_LEDS);

void loop() {
  static int encoderPosition = 0;
  encoder.tick();
  int newPos = encoder.getPosition();

  switch(state) {
    case 0: // Clock display mode
      displayTime();
      clicked = false;
      break;
    
    case 1: // Time set mode
      setTime();
      if (encoderPosition != newPos) {
       
        if(newPos - encoderPosition > 0) { // knob turned right
          tickForward();
        } else { // knob turned right
          tickReverse();
        }

        setTime();
        Serial.println(hours);
        Serial.println(minutes);
        encoderPosition = newPos;
      } // if 
      clicked = false;
      break;
  }
}

void displayTime() {
  //for (int i=0; i < NUM_LEDS; i++) {
  //  if(clicked)
  //    break;
    drawDial();
    drawHands();
    tickMinuteHand(map(minutes, 0, 59, 0, NUM_TICKS));

    
    
    seconds = seconds + tickDelay;
    if (seconds >= 59) {
      seconds = 0;
      tickForward();
    }

  FastLED.show();
}

void setTime() {
  seconds = 0;
  drawDial();
  drawHands();
  FastLED.show();
}


void tickForward() {
    minutes = minutes + deltaMinutes;
    hours = hours + (deltaMinutes / 60.0);
    checkAndResetTime();
}

void tickReverse() {
    minutes = minutes - deltaMinutes;
    hours = hours - (deltaMinutes / 60.0);
    checkAndResetTime();
}

void checkAndResetTime() {
  if (minutes > 59)
    minutes = 0;
  if (hours > 11)
    hours = 0;
  if (minutes < 0)
    minutes = 59;
  if (hours < 0)
    hours = 11;  
}

void knob_pressed(){
  detachInterrupt(1);
  if(!clicked) {
    clicked = true;
    if(state <= 0) {
      state = 1;
    } else {
      state = 0;
    }
  }
  attachInterrupt(1, knob_pressed, RISING);
}


// Tick and fade minute hand
void tickMinuteHand(int pos) {

  int brightness = 100;


  //NeoPixel Ring with 60 LEDS will be 1 LED per minute...
  //But NeoPixel can have different number of LEDS...
  //Here delay is in milliseconds (seconds * 1000)
  double delayPerLED = (60 / NUM_LEDS) * 1000;

  brightness = brightness / 2;
  //delay per iteration per loop...
  double animationDelay = (delayPerLED / brightness) / 2;
  
  for(int i=0; i <= brightness; i++) {
    if(clicked)
      break;
      
    leds[pos] = CHSV(hue(3), 255, i*2); // sec LED
    FastLED.show();
    delay(animationDelay);
  }
  for(int i=brightness; i >= 0; i--) {
    if(clicked)
      break;
     
    leds[pos] = CHSV(hue(3), 255, i*2); // sec LED
    FastLED.show();
    delay(animationDelay);
  }
}



void drawDial() {
  for(int i=0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(dial[i].h, dial[i].s, dial[i].v);
  }
}

void drawHands() {
  leds[(int)floor(mapf(hours, 0, 11, 0, NUM_TICKS))] = CHSV(hue(122), 255, 100); // hour LED
  leds[(int)floor(mapf(minutes, 0, 59, 0, NUM_TICKS))] = CHSV(hue(3), 255, 100); // min LED
}

byte hue(int h) {
  return map(h, 0, 359, 0, 255);
}

double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
