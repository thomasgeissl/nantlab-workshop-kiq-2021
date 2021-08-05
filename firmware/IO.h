#pragma once
#include "./config.h"

#include <Adafruit_NeoPixel.h>
#include <Ultrasonic.h>


class IO {
  public:
    //  matrix
    //      IO(): ultrasonic(Ultrasonic(PIN_TRIG, PIN_ECHO)), strip(Adafruit_NeoPixel(LED_COUNT, PIN_LED, NEO_GRB + NEO_KHZ800)) {}
    // ring
    IO(): ultrasonic(Ultrasonic(PIN_TRIG, PIN_ECHO)), strip(Adafruit_NeoPixel(LED_COUNT, PIN_LED, (LED_COUNT == 16 ? NEO_RGB : NEO_GRB)+ NEO_KHZ800)) {}

    void begin() {
      Serial.begin(9600);
      strip.begin();
      strip.clear();
      strip.show();
      strip.setBrightness(50);
    }
    void update() {
      distance = ultrasonic.read();
      micLevel = analogRead(PIN_MIC);
    }
    void print() {
      String message = "distance: ";
      message += distance;
      message += ", ";
      message += "micLevel: ";
      message += micLevel;
      Serial.println(message);
    }
    void setColorAtIndex(int i, byte red, byte green, byte blue) {
      strip.setPixelColor(i, strip.Color(red, green, blue));
    }
    void setColorAtCoordinate(int x, int y, byte red, byte green, byte blue) {
      strip.setPixelColor(y * 8 + x, strip.Color(red, green, blue));
    }
    void show() {
      strip.show();
    }
    void clear() {
      strip.clear();
    }

    // Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
    void rainbow(int wait) {
      // Hue of first pixel runs 5 complete loops through the color wheel.
      // Color wheel has a range of 65536 but it's OK if we roll over, so
      // just count from 0 to 5*65536. Adding 256 to firstPixelHue each time
      // means we'll make 5*65536/256 = 1280 passes through this outer loop:
      for (long firstPixelHue = 0; firstPixelHue < 5 * 65536; firstPixelHue += 256) {
        for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
          // Offset pixel hue by an amount to make one full revolution of the
          // color wheel (range of 65536) along the length of the strip
          // (strip.numPixels() steps):
          int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
          // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
          // optionally add saturation and value (brightness) (each 0 to 255).
          // Here we're using just the single-argument hue variant. The result
          // is passed through strip.gamma32() to provide 'truer' colors
          // before assigning to each pixel:
          strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
        }
        strip.show(); // Update strip with new contents
        delay(wait);  // Pause for a moment
      }
    }

    Adafruit_NeoPixel strip;
    Ultrasonic ultrasonic;
    int distance;
    int micLevel;

};
