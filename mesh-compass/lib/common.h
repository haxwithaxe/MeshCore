#pragma once

#include <math.h>  // FIXME: I think this is available via nrf52 or Arduino libs

#define FINDER_UNSET 999999.0

// M_PI is available in math.h
#define M_TAU M_PI * 2

#define DEG_TO_RAD(deg) (deg * M_PI / 180.0)
#define EARTH_CIRCUMFRENCE 40074997.0  // meters
#define EARTH_RADIUS 6378137.0  // meters

typedef enum {
	HOME_UP
	TARGET_UP
	NEITHER_UP
} orientation_up_t;


/* Normalize radians to no more than a full rotation.
 * 
 * Arguments:
 *	rads: Some number or radians as a float.
 *
 */
float normalize_radians(float rads);


class Location {

  protected:
    bool _is_set;

  public:
    float lat;
    float lon;

    Location(float lat_, float lon_);

    Location();

    float diff_meters(float lat_, float lon_);

    void update(float lat_, float lon_);

    bool is_set();
}
