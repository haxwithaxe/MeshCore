#pragma once

/* Transform the accelerometer sensor output into a useful format. 
 * 
 * 3 orientation states:
 *   Homing side up - tell the finder to use the home target
 *   Finder side up - tell the finder to look for the selected target
 *   Nose down - Do power save stuff
 */

#include <Adafruit_LSM303_Accel.h>
#include <Adafruit_Sensor.h>
#include <Wire.h> // FIXME: is this needed?

#include "common.h"

#ifndef ACCELEROMETER_DEVICE_ID
  #define ACCELEROMETER_DEVICE_ID 79323
#endif


class Accelerometer {

  protected:
    Adafruit_LSM303_Accel_Unified sensor;

  public:
    Accelerometer();
    // Do last minute setup
    void begin();
    // Return the orientation of the node
    orientation_up_t upside();

};
