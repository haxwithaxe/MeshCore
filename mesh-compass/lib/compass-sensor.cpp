/* Transform the compass sensor output into a useful format. 
 * Docs: https://learn.adafruit.com/lsm303-accelerometer-slash-compass-breakout/coding
 */

#include "common.h"
#include "compass-sensor.h"


Compass::Compass() {
 Adafruit_LSM303DLH_Mag_Unified mag = Adafruit_LSM303DLH_Mag_Unified(COMPASS_DEVICE_ID);
}

void Compass::begin() {
  sensor.enableAutoRange(true);
  /* Initialise the sensor */
  if (!sensor.begin()) {
    Serial.println("Ooops, no LSM303DLH detected ... Check your wiring!");
  }
}

// Return the heading of this node in radians
float Compass::heading_rad() {
  sensors_event_t event;
  sensor.getEvent(&event);
  float heading_rad = atan2f(event.magnetic.y, event.magnetic.x);
  if (heading_rad < 0) {
    return normalize_radians(heading_rad);
  }
  return heading_rad;
}
