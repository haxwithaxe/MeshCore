/* Manage the navigation display (LED array)
 *
 * Docs: https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
 */
#include "common.h"
#include "display-logic.h"

// Which pin on the Arduino is connected to the NeoPixels?
#define LED_PIN 6  // FIXME: Update when finalized

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 8  // FIXME: Update when finalized

// FIXME: color macros/defines?

NavDisplay::NavDisplay() {
  // Declare our NeoPixel strip object:
  Adafruit_NeoPixel _strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
  // Argument 1 = Number of pixels in NeoPixel strip
  // Argument 2 = Arduino pin number (most are valid)
  // Argument 3 = Pixel type flags, add together as needed:
  //   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
  //   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
  //   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
  //   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
  //   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)
}

void NavDisplay::begin() {
  _strip.begin();
  _strip.show(); // Initialize all pixels to 'off'
}

void NavDisplay::loop() {
  // FIXME: Update blinking/pulsing/chasing
}

// Set the direction relative to the device that the user should go
// Hot/Cold color change?
// Gradient pointing the way?
// Distance color change?
void NavDisplay::set_direction(float heading_rad) {
  // FIXME: do smart thing
  // Push changes to the array
  _strip.show();
}

// Display lights on dorsal side, ventral side, or power save
void NavDisplay::set_orientation(orientation_up_t upside) {
  // FIXME: do smart thing
  // Push changes to the array
  _strip.show();
}

// Do something to warn the user
// blink/pulse/chase?
void NavDisplay::set_warning(bool enable) {
  // FIXME: do smart thing
  // Push changes to the array
  _strip.show();
}

// Do something to alert the user of a serious error
// blink/pulse/chase?
void NavDisplay::set_error(bool enable) {
  // FIXME: do smart thing
  // Push changes to the array
  _strip.show();
}

