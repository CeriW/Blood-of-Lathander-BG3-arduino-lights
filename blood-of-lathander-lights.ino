#include <Adafruit_NeoPixel.h>
#define PIN 3
#define NUMPIXELS 13

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Define a type and store some colours for my use
struct RGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

RGB warmYellow = { 255, 125, 0 };
RGB coolYellow = { 255, 175, 0 };
RGB white = { 255, 255, 255 };

int minBrightness = 50 / 20;   // LEDs completely off would be 0
int maxBrightness = 255 / 20;  // Maximum brightness on the LEDs would be 255
int interval = 300;
int stepSize = 2;


void setup() {

  pixels.begin();
  pixels.setBrightness(minBrightness);
  setAllPixelsYellow();
}

void setAllPixelsYellow() {
  for (int ledRef = 0; ledRef < NUMPIXELS; ledRef++) {
    pixels.setPixelColor(ledRef, warmYellow.r, warmYellow.g, warmYellow.b);
    pixels.show();
  }
}

void loop() {

  setAllPixelsYellow();
  pixels.setPixelColor(random(0, 6), white.r, white.g, white.b);
  pixels.setPixelColor(random(7, 12), white.r, white.g, white.b);
  pixels.setPixelColor(random(0, 6), coolYellow.r, coolYellow.g, coolYellow.b);
  pixels.setPixelColor(random(7, 12), coolYellow.r, coolYellow.g, coolYellow.b);
  pixels.show();
  delay(interval);

  // Fade from min brightness to max brightness
  for (int brightness = minBrightness; brightness <= maxBrightness; brightness += stepSize) {
    pixels.setBrightness(brightness);
    pixels.show();
    delay(interval);
  };

  // Then fade from max down to min again
  for (int brightness = maxBrightness; brightness >= minBrightness; brightness -= stepSize) {
    pixels.setBrightness(brightness);
    pixels.show();
    delay(interval);
  };





  // for (int i = 0; i <=10; i++){
  //   pixels.setBrightness(10 * i);
  //   pixels.show();
  //   delay(100);
  // }

  // // CYCLE 1
  // // For all pixels...
  // for (int i = 0; i < NUMPIXELS; i++) {

  //   int randomWhiteLED1 = random(0, 6);
  //   int randomWhiteLED2 = random(7, 12);
  //   setAllPixelsYellow();

  //   // Go from min brightness to max brightness
  //   for (int brightness = minBrightness; brightness <= maxBrightness; brightness += stepSize) {
  //     // setAllPixelsYellow();

  //     pixels.setPixelColor(randomWhiteLED1, white.r, white.g, white.b);
  //     pixels.setPixelColor(randomWhiteLED2, white.r, white.g, white.b);

  //     // pixels.setBrightness(brightness);
  //     pixels.show();
  //     delay(interval);
  //   }

  //   // Then go from max brightness to min brightness
  //   for (int brightness = maxBrightness; brightness > minBrightness; brightness -= stepSize) {
  //     // setAllPixelsYellow();
  //     // pixels.setBrightness(brightness);
  //     pixels.show();
  //     delay(interval);
  //   }
  // }

  // // CYCLE 2
  // for (int i = 0; i < NUMPIXELS; i += 2) {

  //   int randomWhiteLED1 = random(0, 6);
  //   int randomWhiteLED2 = random(7, 12);
  //   setAllPixelsYellow();


  //   // Go from min brightness to max brightness
  //   for (int brightness = minBrightness; brightness <= maxBrightness; brightness += stepSize) {
  //     // setAllPixelsYellow();


  //     // pixels.setPixelColor(randomWhiteLED1, white.r, white.g, white.b);
  //     // pixels.setPixelColor(randomWhiteLED2, white.r, white.g, white.b);

  //     pixels.setBrightness(brightness);
  //     pixels.show();
  //     delay(interval);
  //   }

  //   // Then go from max brightness to min brightness
  //   for (int brightness = maxBrightness; brightness > minBrightness; brightness -= stepSize) {
  //     // setAllPixelsYellow();
  //     pixels.setBrightness(brightness);
  //     pixels.show();
  //     delay(interval);
  //   }
  // }
}
