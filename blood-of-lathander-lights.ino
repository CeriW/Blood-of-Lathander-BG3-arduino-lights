#include <FastLED.h>

#define NUM_LEDS 13
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

// Warm yellow in HSV
const CHSV warmYellow = CHSV(35, 255, 255);
const CRGB white = CRGB::White;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  // start off with warm yellow
  leds[0] = warmYellow;
  FastLED.show();

  delay(1000);

  uint8_t minBrightness = 100;
  uint8_t maxBrightness = 255;

  // Fade out
  for (int i = maxBrightness; i >= minBrightness; i--) {
    leds[0] = CHSV(warmYellow.h, warmYellow.s, i);
    FastLED.show();
    delay(10);
  }

  delay(500);

  // Fade in
  for (int i = minBrightness; i <= maxBrightness; i++) {
    leds[0] = CHSV(warmYellow.h, warmYellow.s, i);
    FastLED.show();
    delay(10);
  }

  delay(500);
}
