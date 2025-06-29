#include <FastLED.h>

#define NUM_LEDS 13
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

// Warm yellow in HSV
const CHSV warmYellow = CHSV(35, 255, 255);
const CRGB white = CRGB::White;

uint8_t minBrightness = 100;
uint8_t maxBrightness = 255;

int warmYellowLoopsBeforeWhite = 3;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}

void fadeOutInWarmYellow(int led) {
  // Fade out
  for (int i = maxBrightness; i >= minBrightness; i--) {
    leds[led] = CHSV(warmYellow.h, warmYellow.s, i);
    FastLED.show();
    delay(10);
  }

  // Fade in
  for (int i = minBrightness; i <= maxBrightness; i++) {
    leds[led] = CHSV(warmYellow.h, warmYellow.s, i);
    FastLED.show();
    delay(10);
  }
}

void loop() {
  // start off with warm yellow
  leds[0] = warmYellow;
  FastLED.show();

  delay(1000);



  EVERY_N_MILLISECONDS(2000) {
    fadeOutInWarmYellow(0);
    fadeOutInWarmYellow(5);
  }
  // for (int loop = 0; loop < warmYellowLoopsBeforeWhite; loop++){
  // }
}
