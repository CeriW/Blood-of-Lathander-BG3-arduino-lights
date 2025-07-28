#include <FastLED.h>

#define NUM_LEDS 16
#define DATA_PIN 9

// The number of LEDs that are in the spikes.
// For my prop, there are 13 spikes, plus 3 more LEDs - 2 in the main sphere and one in the pummel.
#define SPIKE_LEDS 13

const int TOP_SPIKE = 0;
const int UPPER_HEMISPHERE_SPIKES[] = {1, 2, 4, 5};
const int SIDE_SPIKES[] = {3, 6, 8, 11};
const int LOWER_HEMISPHERE_SPIKES[] = {7, 9, 10, 12};
const int INTERNAL_LEDS[] = {13, 14};
const int PUMMEL_LED = 15;

CRGB leds[NUM_LEDS];

const CHSV warmYellow = CHSV(35, 255, 255);
const CHSV white = CHSV(0, 0, 100);

int dimBrightness = 50; // The brightness for the dimmest point, from a max of 255
int maxBrightness = 255;
int fadeSpeed = 2.5; // How fast the LEDs fade in and out. Higher numbers will be slower


void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.clear();

  fill_solid(leds, NUM_LEDS, warmYellow);
  FastLED.show();
}

void fadeIn(int led, CHSV colour) {
  for (int i = dimBrightness; i <= maxBrightness; i++) {
    leds[led] = CHSV(colour.h, colour.s, i);
    FastLED.show();
    delay(fadeSpeed);
  }
  // Ensure final brightness
  leds[led] = CHSV(colour.h, colour.s, maxBrightness);
  FastLED.show();
}

void fadeOut(int led, CHSV colour) {
  for (int i = maxBrightness; i >= dimBrightness; i--) {
    leds[led] = CHSV(colour.h, colour.s, i);
    FastLED.show();
    delay(fadeSpeed);
  }
  // Ensure final brightness
  leds[led] = CHSV(colour.h, colour.s, dimBrightness);
  FastLED.show();
}

void fadeAllInOut(CHSV colour) {
  // Fade all LEDs in and out yellow for fun
  for (int i = maxBrightness; i > dimBrightness; i--) {
    fill_solid(leds, NUM_LEDS, CHSV(colour.h, colour.s, i));
    FastLED.show();
    delay(10);
  }

  for (int i = dimBrightness; i <= maxBrightness; i++) {
    fill_solid(leds, NUM_LEDS, CHSV(colour.h, colour.s, i));
    FastLED.show();
    delay(10);
  }
}


void loop() {


  fadeAllInOut(warmYellow);
  fadeAllInOut(warmYellow);
  // fadeAllInOut(warmYellow);


  int whiteLED1 = UPPER_HEMISPHERE_SPIKES[random(0, 3)];
  int whiteLED2 = LOWER_HEMISPHERE_SPIKES[random(0, 3)];
  int whiteLED3 = SIDE_SPIKES[random(0, 3)];

  // Choose a random LED to dim which isn't one of the white ones
  int dimLED1 = random(0, SPIKE_LEDS / 3);
  while (dimLED1 == whiteLED1 || dimLED1 == whiteLED2 || dimLED1 == whiteLED3) {
    dimLED1 = random(0, SPIKE_LEDS / 3);
  }

  // Choose another random LED to dim which isn't one of the white ones
  int dimLED2 = random(SPIKE_LEDS / 3, SPIKE_LEDS / 3 * 2);
  while (dimLED2 == whiteLED1 || dimLED2 == whiteLED2 || dimLED2 == whiteLED3 || dimLED2 == dimLED1) {
    dimLED2 = random(SPIKE_LEDS / 3, SPIKE_LEDS / 3 * 2);
  }

  // Choose another random LED to dim which isn't one of the white ones
  int dimLED3 = random(SPIKE_LEDS / 3 * 2, SPIKE_LEDS);
  while (dimLED3 == whiteLED1 || dimLED3 == whiteLED2 || dimLED3 == whiteLED3 || dimLED3 == dimLED1 || dimLED3 == dimLED2) {
    dimLED3 = random(SPIKE_LEDS / 3 * 2, SPIKE_LEDS);
  }

  fadeOut(whiteLED1, warmYellow);  // Keep our whiteLED1 yellow, but fade to nothing
  fadeOut(dimLED1, warmYellow);    // Make dimLED1 dim
  fadeOut(whiteLED2, warmYellow);  // Keep our whiteLED2 yellow, but fade to nothing
  fadeOut(dimLED2, warmYellow);    // Make dimLED1 dim
  fadeOut(whiteLED3, warmYellow);  // Keep our whiteLED3 yellow, but fade to nothing
  fadeOut(dimLED3, warmYellow);    // Make dimLED3 dim


  // Current state:
  // dimLED1: dim
  // dimLED2: dim
  // dimLED3: dim
  // whiteLED1: off
  // whiteLED2: off
  // whiteLED3: off

  // -------

  fadeIn(whiteLED1, white);  // fade whiteLED1 to full white brightness
  fadeIn(whiteLED2, white);  // fade whiteLED2 to full white brightness
  fadeIn(whiteLED3, white);  // fade whiteLED3 to full white brightness

  fadeIn(dimLED1, warmYellow);  // bring dim leds back to full brightness
  fadeIn(dimLED2, warmYellow);  // bring dim leds back to full brightness
  fadeIn(dimLED3, warmYellow);  // bring dim leds back to full brightness

  fadeIn(PUMMEL_LED, warmYellow);


  // Current state:
  // dimLED1: max brightness
  // dimLED1: max brightness
  // dimLED3: max brightness
  // whiteLED1: max brightness (white)
  // whiteLED2: max brightness (white)
  // whiteLED3: max brightness (white)

  // -------

  // Dim and re-brighten dim leds
  fadeOut(dimLED1, warmYellow);  // dimLED1 dim again
  fadeOut(dimLED2, warmYellow);  // dimLED2 dim again
  fadeOut(dimLED3, warmYellow);  // dimLED3 dim again
  fadeOut(PUMMEL_LED, warmYellow);

  fadeIn(dimLED1, warmYellow);  // bring dim leds back to full brightness
  fadeIn(dimLED2, warmYellow);  // bring dim leds back to full brightness
  fadeIn(dimLED3, warmYellow);  // bring dim leds back to full brightness
  fadeIn(PUMMEL_LED, warmYellow);



  // Current state:
  // dimLED1: max brightness
  // dimLED2: max brightness
  // dimLED3: max brightness
  // whiteLED1: max brightness (white)
  // whiteLED2: max brightness (white)
  // whiteLED3: max brightness (white)

  // -------

  fadeOut(whiteLED1, white);  // fade whiteLED1 to nothing
  fadeOut(whiteLED2, white);  // fade whiteLED2 to nothing
  fadeOut(whiteLED3, white);  // fade whiteLED2 to nothing
  fadeOut(PUMMEL_LED, warmYellow);

  // Current state:
  // dimLED1: max brightness
  // dimLED2: max brightness
  // dimLED3: max brightness
  // whiteLED1: off
  // whiteLED2: off
  // whiteLED3: off

  // -------

  fadeIn(whiteLED1, warmYellow);
  fadeIn(whiteLED2, warmYellow);
  fadeIn(whiteLED3, warmYellow);
  fadeIn(PUMMEL_LED, warmYellow);

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
