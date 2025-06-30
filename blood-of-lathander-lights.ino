#include <FastLED.h>

#define NUM_LEDS 13
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

// Warm yellow in HSV
const CHSV warmYellow = CHSV(35, 255, 255);
const CHSV white = CHSV(0, 0, 100);

uint8_t minBrightness = 100;
uint8_t maxBrightness = 255;

int warmYellowLoopsBeforeWhite = 2;
int interval = 500;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}

// For a specified LED, make it a colour then fade between 'from' and 'to' brightnesses
void fadeIn(int led, CHSV colour, int from, int to) {

  for (int i = from; i <= to;) {

    // Store the time this loop started in milliseconds.
    uint8_t start = millis();

    leds[led] = CHSV(colour.h, colour.s, i);
    FastLED.show();

    // We can't use delay(10) because it blocks everything else from doing anything.
    // We shall instead keep checking whether 10ms have passed and then move onto the next loop
    if (millis() > start + 50) {
      i++;
    }
  }
}

void fadeOut(int led, CHSV colour, int from, int to) {

  for (int i = from; i >= to;) {

    // Store the time this loop started in milliseconds.
    uint8_t start = millis();

    leds[led] = CHSV(colour.h, colour.s, i);
    FastLED.show();

    // We can't use delay(10) because it blocks everything else from doing anything.
    // We shall instead keep checking whether 10ms have passed and then move onto the next loop
    if (millis() > start + 50) {
      i--;
    }
  }
}

void yellowWhiteLoop(int led) {
  for (int loop = 0; loop < warmYellowLoopsBeforeWhite - 1; loop++) {
    // For first few loops, go from mid brightness to max brightness and back again
    fadeOut(led, warmYellow, maxBrightness, minBrightness);
    fadeIn(led, warmYellow, minBrightness, maxBrightness);
  }

  // For the next loop we take the brightness all the way down to 0.
  // This means we don't get a jump between one colour and another.
  fadeOut(led, warmYellow, maxBrightness, 0);

  // Now we fade in with white
  fadeIn(led, white, 0, maxBrightness);

  // And make the white fade back to 0
  fadeOut(led, white, maxBrightness, 0);

  // Now fade back in with yellow to minimum brightness so we can start the loop again
  fadeIn(led, warmYellow, 0, maxBrightness);
}


void loop() {
  // start off with warm yellow
  // leds[0] = warmYellow;
  FastLED.show();

  EVERY_N_MILLISECONDS(interval) {
    int targetLED1 = random(0, NUM_LEDS /3);
    int targetLED2 = random(NUM_LEDS / 3, NUM_LEDS / 3 * 2);
    int targetLED3 = random(NUM_LEDS / 3 * 2, NUM_LEDS);

    // yellowWhiteLoop(targetLEDs);


  for (int loop = 0; loop < warmYellowLoopsBeforeWhite - 1; loop++) {
    // For first few loops, go from mid brightness to max brightness and back again
    fadeOut(targetLED1, warmYellow, maxBrightness, minBrightness);
    fadeOut(targetLED2, warmYellow, maxBrightness, minBrightness);
    fadeOut(targetLED3, warmYellow, maxBrightness, minBrightness);

    fadeIn(targetLED1, warmYellow, minBrightness, maxBrightness);
    fadeIn(targetLED2, warmYellow, minBrightness, maxBrightness);
    fadeIn(targetLED3, warmYellow, minBrightness, maxBrightness);
  }

  // For the next loop we take the brightness all the way down to 0.
  // This means we don't get a jump between one colour and another.
  fadeOut(targetLED1, warmYellow, maxBrightness, 0);
  fadeOut(targetLED2, warmYellow, maxBrightness, 0);
  fadeOut(targetLED3, warmYellow, maxBrightness, 0);


  // Now we fade in with white
  fadeIn(targetLED1, white, 0, maxBrightness);
  fadeIn(targetLED2, white, 0, maxBrightness);
  fadeIn(targetLED3, white, 0, maxBrightness);


  // And make the white fade back to 0
  fadeOut(targetLED1, white, maxBrightness, 0);
  fadeOut(targetLED2, white, maxBrightness, 0);
  fadeOut(targetLED3, white, maxBrightness, 0);


  // Now fade back in with yellow to minimum brightness so we can start the loop again
  fadeIn(targetLED1, warmYellow, 0, maxBrightness);
  fadeIn(targetLED2, warmYellow, 0, maxBrightness);
  fadeIn(targetLED3, warmYellow, 0, maxBrightness);
  }
}
