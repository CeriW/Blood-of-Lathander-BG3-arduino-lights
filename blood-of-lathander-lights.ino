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

int minBrightness = 50;
int maxBrightness = 255;
int interval = 80;
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

  // for (int i = 0; i <=10; i++){
  //   pixels.setBrightness(10 * i);
  //   pixels.show();
  //   delay(100);
  // }

  // For all pixels...
  for (int i = 0; i < NUMPIXELS; i++) {

    int randomWhiteLED1 = random(0, 6);
    int randomWhiteLED2 = random(7, 12);


    // Go from min brightness to max brightness
    for (int brightness = minBrightness; brightness <= maxBrightness; brightness += stepSize) {
      setAllPixelsYellow();
      pixels.setPixelColor(randomWhiteLED1, white.r, white.g, white.b);
      pixels.setPixelColor(randomWhiteLED2, white.r, white.g, white.b);

      pixels.setBrightness(brightness);
      pixels.show();
      delay(interval);
    }

    // Then go from max brightness to min brightness
    for (int brightness = maxBrightness; brightness > minBrightness; brightness -= stepSize) {
      // setAllPixelsYellow();
      pixels.setBrightness(brightness);
      pixels.show();
      delay(interval);
    }

    setAllPixelsYellow();


    // pixels.setPixelColor(i - 4, coolWhite.r, coolWhite.g, coolWhite.b);
    // pixels.setPixelColor(i - 1, warmYellow.r, warmYellow.g, warmYellow.b);
    // pixels.setPixelColor(i + 4, warmYellow.r, warmYellow.g, warmYellow.b);

    // pixels.setPixelColor(i - 5, coolWhite.r, coolWhite.g, coolWhite.b);
    // pixels.setPixelColor(i, coolWhite.r, coolWhite.g, coolWhite.b);
    // pixels.setPixelColor(i + 5, coolWhite.r, coolWhite.g, coolWhite.b);

    // pixels.show();
    // delay(interval);






    // pixels.show();
    // delay(interval);


    // pixels.setPixelColor(i, myColour.r, myColour.g, myColour.b);
    // pixels.show();
    // delay(300);
  }

  // for (int i = 0; i < NUMPIXELS; i++) {
  //   pixels.clear();
  //   pixels.setPixelColor(i, pixels.Color(red.r, red.g, red.g));
  //   pixels.setPixelColor(i+1, pixels.Color(green.r, green.g, green.b));
  //   pixels.setPixelColor(i+2, pixels.Color(blue.r, blue.g, blue.b));

  //   pixels.show();
  //   delay(300);
  // }
}
