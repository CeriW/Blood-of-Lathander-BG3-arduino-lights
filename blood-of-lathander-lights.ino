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

  fill_solid(leds, NUM_LEDS, warmYellow);
  FastLED.show();
}

void fadeIn(int led, CHSV colour, int from, int to) {
  for (int i = from; i <= to; i++) {
    leds[led] = CHSV(colour.h, colour.s, i);
    FastLED.show();
    // delay(5);
  }
}

void fadeOut(int led, CHSV colour, int from, int to) {
  for (int i = from; i >= to; i--) {
    leds[led] = CHSV(colour.h, colour.s, i);
    FastLED.show();
    // delay(5);
  }
}


// void yellowWhiteLoop(int led) {



//   for (int loop = 0; loop < warmYellowLoopsBeforeWhite - 1; loop++) {
//     // For first few loops, go from mid brightness to max brightness and back again
//     fadeOut(led, warmYellow, 255, 128);
//     fadeIn(led, warmYellow, 128, 255);
//   }

//   // For the next loop we take the brightness all the way down to 0.
//   // This means we don't get a jump between one colour and another.
//   fadeOut(led, warmYellow, 255, 0);

//   // Now we fade in with white
//   fadeIn(led, white, 0, 255);

//   // And make the white fade back to 0
//   fadeOut(led, white, 255, 0);

//   // Now fade back in with yellow to minimum brightness so we can start the loop again
//   fadeIn(led, warmYellow, 0, 255);
// }


void loop() {
  // start off with warm yellow
  // leds[0] = warmYellow;
  FastLED.show();

  // starting from all LEDS warm yellow maximum brightness...
  // fill_solid(leds, NUM_LEDS, warmYellow);


  // EVERY_N_MILLISECONDS(interval) {

  int whiteLED1 = random(0, NUM_LEDS / 3);
  int whiteLED2 = random(NUM_LEDS / 3, NUM_LEDS / 3 * 2);
  int whiteLED3 = random(NUM_LEDS / 3 * 2, NUM_LEDS);

  // Choose a random LED to dim which isn't one of the white ones
  int dimLED1 = random(0, NUM_LEDS / 3);
  while (dimLED1 == whiteLED1 || dimLED1 == whiteLED2 || dimLED1 == whiteLED3) {
    dimLED1 = random(0, NUM_LEDS / 3);
  }

  // Choose another random LED to dim which isn't one of the white ones
  int dimLED2 = random(NUM_LEDS / 3, NUM_LEDS / 3 * 2);
  while (dimLED2 == whiteLED1 || dimLED2 == whiteLED2 || dimLED2 == whiteLED3 || dimLED2 == dimLED1) {
    dimLED2 = random(NUM_LEDS / 3, NUM_LEDS / 3 * 2);
  }

  // Choose another random LED to dim which isn't one of the white ones
  int dimLED3 = random(NUM_LEDS / 3 * 2, NUM_LEDS);
  while (dimLED3 == whiteLED1 || dimLED3 == whiteLED2 || dimLED3 == whiteLED3 || dimLED3 == dimLED1 || dimLED3 == dimLED2) {
    dimLED3 = random(NUM_LEDS / 3 * 2, NUM_LEDS);
  }

  fadeOut(whiteLED1, warmYellow, 255, dimBrightness);  // Keep our whiteLED1 yellow, but fade to nothing
  fadeOut(dimLED1, warmYellow, 255, dimBrightness);    // Make dimLED1 dim
  fadeOut(whiteLED2, warmYellow, 255, dimBrightness);  // Keep our whiteLED2 yellow, but fade to nothing
  fadeOut(dimLED2, warmYellow, 255, dimBrightness);    // Make dimLED1 dim
  fadeOut(whiteLED3, warmYellow, 255, dimBrightness);  // Keep our whiteLED3 yellow, but fade to nothing
  fadeOut(dimLED3, warmYellow, 255, dimBrightness);    // Make dimLED3 dim


  // Current state:
  // dimLED1: dim
  // dimLED2: dim
  // dimLED3: dim
  // whiteLED1: off
  // whiteLED2: off
  // whiteLED3: off

  // -------

  fadeIn(whiteLED1, white, dimBrightness, 255);  // fade whiteLED1 to full white brightness
  fadeIn(whiteLED2, white, dimBrightness, 255);  // fade whiteLED2 to full white brightness
  fadeIn(whiteLED3, white, dimBrightness, 255);  // fade whiteLED3 to full white brightness

  fadeIn(dimLED1, warmYellow, dimBrightness, 255);  // bring dim leds back to full brightness
  fadeIn(dimLED2, warmYellow, dimBrightness, 255);  // bring dim leds back to full brightness
  fadeIn(dimLED3, warmYellow, dimBrightness, 255);  // bring dim leds back to full brightness


  // Current state:
  // dimLED1: max brightness
  // dimLED1: max brightness
  // dimLED3: max brightness
  // whiteLED1: max brightness (white)
  // whiteLED2: max brightness (white)
  // whiteLED3: max brightness (white)

  // -------

  // Dim and re-brighten dim leds
  fadeOut(dimLED1, warmYellow, 255, dimBrightness);  // dimLED1 dim again
  fadeOut(dimLED2, warmYellow, 255, dimBrightness);  // dimLED2 dim again
  fadeOut(dimLED3, warmYellow, 255, dimBrightness);  // dimLED3 dim again

  fadeIn(dimLED1, warmYellow, dimBrightness, 255);  // bring dim leds back to full brightness
  fadeIn(dimLED2, warmYellow, dimBrightness, 255);  // bring dim leds back to full brightness
  fadeIn(dimLED3, warmYellow, dimBrightness, 255);  // bring dim leds back to full brightness


  // Current state:
  // dimLED1: max brightness
  // dimLED2: max brightness
  // dimLED3: max brightness
  // whiteLED1: max brightness (white)
  // whiteLED2: max brightness (white)
  // whiteLED3: max brightness (white)

  // -------

  fadeOut(whiteLED1, white, 255, dimBrightness);  // fade whiteLED1 to nothing
  fadeOut(whiteLED2, white, 255, dimBrightness);  // fade whiteLED2 to nothing
  fadeOut(whiteLED3, white, 255, dimBrightness);  // fade whiteLED2 to nothing

  // Current state:
  // dimLED1: max brightness
  // dimLED2: max brightness
  // dimLED3: max brightness
  // whiteLED1: off
  // whiteLED2: off
  // whiteLED3: off

  // -------

  fadeIn(whiteLED1, warmYellow, dimBrightness, 255);
  fadeIn(whiteLED2, warmYellow, dimBrightness, 255);
  fadeIn(whiteLED3, warmYellow, dimBrightness, 255);

  // Current state:
  // dimLED1: max brightness
  // dimLED2: max brightness
  // dimLED3: max brightness
  // whiteLED1: max brightness (yellow)
  // whiteLED2: max brightness (yellow)
  // whiteLED3: max brightness (yellow)
  // }

  delay(10);
}
