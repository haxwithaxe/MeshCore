/* Transform the accelerometer sensor output into a useful format. 
 * 
 * 3 orientation states:
 *   Homing side up - tell the finder to use the home target
 *   Finder side up - tell the finder to look for the selected target
 *   Nose down - Do power save stuff
 *
 * Docs: https://learn.adafruit.com/lsm303-accelerometer-slash-compass-breakout/coding
 */

#include "common.h"
#include "accelerometer-sensor.h"

Accelerometer::Accelerometer() {
  Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(ACCELEROMETER_DEVICE_ID);
}

// Do last minute setup
void Accelerometer::begin() {
  if (!sensor.begin()) {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while (1)
      ;
  }
  /* Accelerometer modes
   * LSM303_MODE_NORMAL
   * LSM303_MODE_LOW_POWER
   * LSM303_MODE_HIGH_RESOLUTION
   */
  sensor.setMode(LSM303_MODE_NORMAL);
}
// Return the orientation of the node
orientation_up_t Accelerometer::upside() {
  sensors_event_t event;
  sensor.getEvent(&event);
  float x = event.acceleration.x;
  float y = event.acceleration.y;
  float z = event.acceleration.z;
  // FIXME: figure out what is what direction and use the below to figure out what side is where.
  // if one of x, y, z is roughly +/- 9m/s/s it's the up-down axis
  // if Pythagoras says the combo of any two vectors is roughly +/- 9m/s/s that is the up-down axis
  // Same for the combo or all 3 just using `c**2 = x**2 + y**2 + z**2`
  // return HOME_UP or TARGET_UP or NEITHER_UP depending on what we decide is which side
  // END FIXME
}
