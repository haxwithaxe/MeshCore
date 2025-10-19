#include "common.h"
#include "finder-logic.h"
#include "accelerometer-sensor.h"
#include "compass-sensor.h"
#include <math.h> // nrf52 or Arduino math.h
/* Given the compass, gps, and remote telemetry tell the display how to steer the user
 *
 */

FinderNode::FinderNode(SensorMesh *mesh) {
  _mesh = &mesh;
}

// The current latitude of the node.
float FinderNode::lat() {
  return _last_location.lat;
}

// The current longitude of the node.
float FinderNode::lon() {
  return _last_location.lon;
}

FinderSelf::FinderSelf(SensorMesh *mesh) {
  _mesh = &mesh;
  _target = FinderTarget();
  _accel = Accelerometer();
  _accel.begin();
  _compass = Compass();
  _compass.begin();
  _nav_display = NavDisplay();
  _nav_display.begin();
  _last_orientation_check_ms = millis(); // FIXME: ?millis?
}

void FinderSelf::loop() {
  // Check orientation and update target periodically
  if (_last_orientation_check_ms - millis() > ORIENTATION_CHECK_INTERVAL_MS) {  // FIXME: real test and ?millis()?
    if (_accel.upside() == HOME_UP) {  // FIXME: real test for orientation
      head_home();
    } else {
      find_target();  // FIXME: default to finding the non-home target
    }
  }
  // Check direction and update display periodically
  
  _nav_display.loop();
}

// Load the Finder settings from the meshcore config.
void FinderSelf::from_config() {
  if (_accel.upside() == HOME_UP) {  // FIXME: real test for orientation
    find_home();
  } else {
    find_target();  // Default to finding the non-home target
  }
}

// Set the non-home node as the target
void FinderSelf::find_target() {
  NodePrefs* prefs = _mesh.getNodePrefs();
  uint8_t* target_address = prefs->fixme_custom_pref__target_address;  // FIXME: create custom config
  _target.set_address(target_address);  // target_address can be NULL
}

// Set the home node as the target
void FinderSelf::find_home() {
  NodePrefs* prefs = _mesh.getNodePrefs();
  uint8_t* target_address = prefs->fixme_custom_pref__home_address;  // FIXME: create custom config
  _target.set_address(target_address);  // target_address can be NULL
}

// Query this node's state for its location.
void FinderSelf::query_location() {
  NodePrefs* prefs = _mesh.getNodePrefs();
  _last_location.update(prefs.node_lat, prefs.node_lon);
}

// Difference in direction for this node to point to get the user to move
//   toward the target in radians clockwise from north.
float FinderSelf::direction_rad() {
  float d_heading = _compass.heading() - heading_to_target_rad();
  return normalize_radians(d_heading);
}

// Direction from user to target in radians clockwise from north.
float FinderSelf::heading_to_target_rad() {
  if (!_target.is_set()) {
    return FINDER_UNSET;
  }
  float d_lat_mapdeg = lat()-_target.lat();
  float d_lon_mapdeg = lon()-_target.lon();
  float rad_off_east = atan2f(d_lat_mapdeg, d_lon_mapdeg);
  // Rotate the angles counter-clockwise so 0rad at east becomes 0rad at 
  //   north
  return normalize_radians(rad_off_east + (M_TAU * 0.25));
}

void FinderTarget::set_address(uint8_t* address) {
  _address = address;
  if (_address != NULL) {
    _is_set = true;
  }
}


// The target node address is set
bool FinderTarget::is_set() {
  return _is_set;
}

// Passively use last broadcast location
void FinderTarget::query_location() {
  ContactInfo* target = lookupContactByPubKey(_address, pub_key_length);
  if (&target == NULL) {
    return
  }
  if (target->last_mod is too old) { // FIXME: real test
    //FIXME: warn user or refuse to render hints
  }
  if (target->?battery_status? is dead) { // FIXME: real test and real attrib
    //FIXME: warn user or refuse to render hints
  }
  _is_set = _last_location.update(target->gps_lat, target->gps_lon);
}
