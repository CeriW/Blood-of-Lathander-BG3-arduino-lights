#include <FastLED.h>

#define NUM_LEDS 13
#define DATA_PIN 3

CRGB leds[NUM_LEDS];

// Warm yellow in HSV
const CHSV warmYellow = CHSV(35, 255, 255);
const CHSV white = CHSV(0, 0, 100);



int warmYellowLoopsBeforeWhite = 1;
int interval = 500;

int dimBrightness = 50;


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
    fadeOut(led, warmYellow, 255, 128);
    fadeIn(led, warmYellow, 128, 255);
  }

  // For the next loop we take the brightness all the way down to 0.
  // This means we don't get a jump between one colour and another.
  fadeOut(led, warmYellow, 255, 0);

  // Now we fade in with white
  fadeIn(led, white, 0, 255);

  // And make the white fade back to 0
  fadeOut(led, white, 255, 0);

  // Now fade back in with yellow to minimum brightness so we can start the loop again
  fadeIn(led, warmYellow, 0, 255);
}


void loop() {
  // start off with warm yellow
  // leds[0] = warmYellow;
  FastLED.show();

  EVERY_N_MILLISECONDS(interval) {

    int whiteLED1 = random(0, NUM_LEDS / 3);
    int whiteLED2 = random(NUM_LEDS / 3, NUM_LEDS / 3 * 2);
    int whiteLED3 = random(NUM_LEDS / 3 * 2, NUM_LEDS);



    // Choose a random LED to dim which isn't one of the white ones
    int dimLED1 = random(0, NUM_LEDS / 2);
    while (dimLED1 == whiteLED1 || dimLED1 == whiteLED2 || dimLED1 == whiteLED3) {
      dimLED1 = random(0, NUM_LEDS / 2);
    }

    // Choose another random LED to dim which isn't one of the white ones
    int dimLED2 = random(0, NUM_LEDS / 2);
    while (dimLED2 == whiteLED1 || dimLED2 == whiteLED2 || dimLED2 == whiteLED3 || dimLED2 == dimLED1) {
      dimLED2 = random(0, NUM_LEDS / 2);
    }


    for (int loop = 0; loop < warmYellowLoopsBeforeWhite - 1; loop++) {
      // For first few loops, go from half brightness to full brightness and back again
      fadeOut(whiteLED1, warmYellow, 255, 128);
      fadeOut(whiteLED2, warmYellow, 255, 128);
      fadeOut(whiteLED3, warmYellow, 255, 128);

      fadeIn(whiteLED1, warmYellow, 128, 255);
      fadeIn(whiteLED2, warmYellow, 128, 255);
      fadeIn(whiteLED3, warmYellow, 128, 255);
    }

    // For the next loop we take the brightness all the way down to 0.
    // This means we don't get a jump between one colour and another.
    fadeOut(whiteLED1, warmYellow, 255, 0);
    fadeOut(whiteLED2, warmYellow, 255, 0);
    fadeOut(whiteLED3, warmYellow, 255, 0);


    // Now we fade in with white
    fadeIn(whiteLED1, white, 0, 255);
    fadeIn(whiteLED2, white, 0, 255);
    fadeIn(whiteLED3, white, 0, 255);


    // Alternate between making the white ones white and the dim ones dim
    fadeOut(whiteLED1, white, 255, 0);
    fadeOut(dimLED1, warmYellow, 255, dimBrightness);
    fadeOut(whiteLED2, white, 255, 0);
    fadeOut(dimLED2, warmYellow, 255, dimBrightness);
    fadeOut(whiteLED3, white, 255, 0);


    // Let's make the dim ones bright again



    // Now fade back in with yellow to minimum brightness so we can start the loop again
    fadeIn(whiteLED1, warmYellow, 0, 255);
    fadeIn(dimLED1, warmYellow, dimBrightness, 255);
    fadeIn(whiteLED2, warmYellow, 0, 255);
    fadeIn(dimLED2, warmYellow, dimBrightness, 255);
    fadeIn(whiteLED3, warmYellow, 0, 255);
  }
}
