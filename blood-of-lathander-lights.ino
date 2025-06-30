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
int interval = 2000;

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}


// // Makes the specified LED fade in and out for a specified colour
// void fadeInOut({int led, CHSV colour, int start, int middle, int end) {

//   // Fade in
//   for (int i = start; i <= middle; i++) {
//     leds[led] = CHSV(colour.h, colour.s, i);
//     FastLED.show();
//     delay(10);
//   }

//   // Fade out
//   for (int i = middle; i >= end; i--) {
//     leds[led] = CHSV(colour.h, colour.s, i);
//     FastLED.show();
//     delay(10);
//   }
// }


// For a specified LED, make it a colour then fade between 'from' and 'to' brightnesses
void fadeIn(int led, CHSV colour, int from, int to) {
  for (int i = from; i <= to; i++) {
    leds[led] = CHSV(colour.h, colour.s, i);
    FastLED.show();
    delay(10);
  }
}

void fadeOut(int led, CHSV colour, int from, int to) {
  for (int i = from; i >= to; i--) {
    leds[led] = CHSV(colour.h, colour.s, i);
    FastLED.show();
    delay(10);
  }
}

// void completeFadeOut(int led, CHSV colour){
//   for (int i = minBrightness; i > 0; i--){
//     leds[led] = CHSV(colour.h, colour.s, i);
//     FastLED.show();
//     delay(10);
//   }
// }

void loop() {
  // start off with warm yellow
  // leds[0] = warmYellow;
  FastLED.show();

  for (int loop = 0; loop < warmYellowLoopsBeforeWhite - 1; loop++) {
    // For first few loops, go from mid brightness to max brightness and back again
    // fadeInOut(0, warmYellow, minBrightness, maxBrightness, minBrightness);
    fadeIn(0, warmYellow, minBrightness, maxBrightness);
    delay(200);
    fadeOut(0, warmYellow, maxBrightness, minBrightness);
  }

  // For the next loop we take the brightness all the way down to 0.
  // This means we don't get a jump between one colour and another.
  fadeOut(0, warmYellow, minBrightness, 0);
  
  // Now we fade in with white
  fadeIn(0, white, 0, maxBrightness);

  // And make the white fade back to 0
  fadeOut(0, white, maxBrightness, 0);

  // Now fade back in with yellow to minimum brightness so we can start the loop again
  fadeIn(0, warmYellow, 0, minBrightness);



  // EVERY_N_MILLISECONDS(5000) {


    // fadeInOut(0, white, )

    // fadeInOut(0, warmYellow, 0, maxBrightness);
    // fadeInOut(0, white, 0, maxBrightness);
    // fadeInOut()
  // }
  // for (int loop = 0; loop < warmYellowLoopsBeforeWhite; loop++){
  // }
}
