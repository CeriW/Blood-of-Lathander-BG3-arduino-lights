#include <FastLED.h>

#define NUM_LEDS 13
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

// Warm yellow in HSV
const CHSV warmYellow = CHSV(35, 255, 255);
const CHSV white = CHSV(0, 0, 100);

uint8_t minBrightness = 50
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

    int whiteLED1 = random(0, NUM_LEDS /3);
    int whiteLED2 = random(NUM_LEDS / 3, NUM_LEDS / 3 * 2);
    int whiteLED3 = random(NUM_LEDS / 3 * 2, NUM_LEDS);


    int dimLED1 = random(0, NUM_LEDS / 2);
    int dimLED2 = random(NUM_LEDS / 2, NUM_LEDS);
    // yellowWhiteLoop(targetLEDs);


  for (int loop = 0; loop < warmYellowLoopsBeforeWhite - 1; loop++) {
    // For first few loops, go from mid brightness to max brightness and back again
    fadeOut(whiteLED1, warmYellow, maxBrightness, minBrightness);
    fadeOut(whiteLED2, warmYellow, maxBrightness, minBrightness);
    fadeOut(whiteLED3, warmYellow, maxBrightness, minBrightness);

    fadeIn(whiteLED1, warmYellow, minBrightness, maxBrightness);
    fadeIn(whiteLED2, warmYellow, minBrightness, maxBrightness);
    fadeIn(whiteLED3, warmYellow, minBrightness, maxBrightness);
  }

  // For the next loop we take the brightness all the way down to 0.
  // This means we don't get a jump between one colour and another.
  fadeOut(whiteLED1, warmYellow, maxBrightness, 0);
  fadeOut(whiteLED2, warmYellow, maxBrightness, 0);
  fadeOut(whiteLED3, warmYellow, maxBrightness, 0);


  // Now we fade in with white
  fadeIn(whiteLED1, white, 0, maxBrightness);
  fadeIn(whiteLED2, white, 0, maxBrightness);
  fadeIn(whiteLED3, white, 0, maxBrightness);

  // Let's make the dim ones fade out a little
  fadeOut(dimLED1, warmYellow, maxBrightness, minBrightness);
  fadeOut(dimLED2, warmYellow, maxBrightness, minBrightness);


  // And make the white fade back to 0
  fadeOut(whiteLED1, white, maxBrightness, 0);
  fadeOut(whiteLED2, white, maxBrightness, 0);
  fadeOut(whiteLED3, white, maxBrightness, 0);

  // Let's make the dim ones bright again
  fadeIn(dimLED1, warmYellow, minBrightness, maxBrightness);
  fadeIn(dimLED2, warmYellow, minBrightness, maxBrightness);


  // Now fade back in with yellow to minimum brightness so we can start the loop again
  fadeIn(whiteLED1, warmYellow, 0, maxBrightness);
  fadeIn(whiteLED2, warmYellow, 0, maxBrightness);
  fadeIn(whiteLED3, warmYellow, 0, maxBrightness);
  }
}
