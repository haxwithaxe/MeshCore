#pragma once

#include <Adafruit_NeoPixel.h>

#include "common.h"


class NavDisplay {

  protected:
  Adafruit_NeoPixel _strip;

  public:
  NavDisplay();
  void begin();
  void loop();

  // Set the direction relative to the device that the user should go
  // Hot/Cold color change?
  // Gradient pointing the way?
  // Distance color change?
  void set_direction(float heading_rad);
  // Display lights on dorsal side, ventral side, or power save
  void set_orientation(orientation_up_t upside);
  // Do something to warn the user
  // blink/pulse/chase?
  void set_warning(bool enable);
  // Do something to alert the user of a serious error
  // blink/pulse/chase?
  void set_error(bool enable);
};
