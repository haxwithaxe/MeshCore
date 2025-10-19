#pragma once

/* Transform the compass sensor output into a useful format. 
 *
 */

#include <Adafruit_LSM303DLH_Mag.h>
#include <Adafruit_Sensor.h>
#include <Wire.h> // FIXME: is this needed?

#include "common.h"

#ifndef COMPASS_DEVICE_ID
  #define COMPASS_DEVICE_ID 38823
#endif


class Compass {

	protected:
		Adafruit_LSM303DLH_Mag_Unified sensor;

	public:
		Compass::Compass();
		// Do last minute setup
		void begin();
		// Return the heading of this node
		float heading_rad();

}
