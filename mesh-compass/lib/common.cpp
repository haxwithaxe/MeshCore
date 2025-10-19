
#include "common.h"
/* Normalize radians to no more than a full rotation.
 * 
 * Arguments:
 *	rads: Some number or radians as a float.
 *
 */
float normalize_radians(float rads) {
	if (rads > M_TAU) {
		return rads - M_TAU * (rads % M_TAU);
	} else if (rads < 0) {
		return rads + M_TAU * (rads % M_TAU);
	}
	return rads;
}


Location::Location(float lat_, float lon_) {
  lat = lat_;
  lon = lon_;
  _is_set = true;
}

Location::Location() {
  lat = 0;
  lon = 0;
  _is_set = false;
}

float Location::diff_meters(float lat_, float lon_) {
  // Uses haversine formula to get distance between two points in meters.
  float d_lon_rad = DEG_TO_RAD(lon_ - lon);
  float d_lat_rad = DEG_TO_RAD(lat_ - lat);
  a = sq(sin(d_lat_rad / 2)) + cos(DEG_TO_RAD(lat)) * cos(DEG_TO_RAD(lat_) * sq(sin(d_lon_rad / 2));
  c = 2 * atan2(sqrt(a), sqrt(1 - a));
  return EARTH_RADIUS * c;
}

void Location::update(float lat_, float lon_) {
  if (lat_ == NULL || lon_ == NULL) {
    return _is_set;
  }
  lat = lat_;
  lon = lon_;
  _is_set = true;
}

bool Location::is_set() {
  return _is_set;
}
