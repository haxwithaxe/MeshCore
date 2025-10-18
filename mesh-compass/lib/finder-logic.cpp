#include "finder-logic.h"
#include <cmath>
/* Given the compass, gps, and remote telemetry tell the display how to steer the user
 *
 */


FinderNode::FinderNode(SensorMesh *mesh) {
	_mesh = &mesh;
}

FinderSelf::FinderSelf(SensorMesh *mesh) {
	_mesh = &mesh;
	_target = FinderTarget(mesh);
}

void FinderSelf::from_config() {
	NodePrefs* prefs = _mesh.getNodePrefs();
	uint8_t* target_address = prefs->fixme_custom_pref__target_address;  // FIXME: create custom config
	if (target_address != NULL) {  // FIXME: real test
		_target.set_address(target_address);
	} else {
		// set null value
		_target.set_address(NULL);
	}
}

// Query this node's state for its location.
void FinderSelf::query_location() {
	NodePrefs* prefs = _mesh.getNodePrefs();
	_last_location.update(prefs.node_lat, prefs.node_lon);
}

// The current latitude of this node.
float FinderSelf::lat() {
	return _last_location.lat;
}

// The current longitude of this node.
float FinderSelf::lon() {
	return _last_location.lon;
}

// --- HEADINGS --- FIXME: remove for real code
/* To get the direction to point the user take the difference of 
 *   heading_to_target_rad and heading_rad.
 */
float FinderSelf::heading_to_target_rad() {
	if (!_target.is_set()) {
		return FINDER_UNSET;
	}
	float d_lat_mapdeg = lat()-_target.lat();
	float d_lon_mapdeg = lon()-_target.lon();
	float tan_off_east_west = d_lat_mapdeg/d_lon_mapdeg;
	float rad_off_east_west = atan(tan_off_east_west);
	// Rotate the angles counter-clockwise so 0rad at east becomes 0rad at 
	//   north
	if (d_lat_mapdeg >= 0 && d_lon_mapdeg >= 0) {
		// FIXME: adjust from east up to north up (add quarter)
	} else if (d_lat_mapdeg >= 0 && d_lon_mapdeg < 0) {
		// FIXME: adjust from -(0-180) to 180-360 (add 4 quarters)
	} else if (d_lat_mapdeg < 0 && d_lon_mapdeg >= 0) {
		// FIXME: adjust from south up to north up (add half)
	} else {  // d_lat_mapdeg < 0 && d_lon_mapdeg < 0
		// FIXME: add 3 quarters
	}
}

// direction of Finder node
float FinderSelf::heading_rad() {
	// FIXME: get heading from compass module
}

// --- END HEADINGS --- FIXME: remove for real code

void FinderTarget::set_address(uint8_t* address) {
	_address = address;
	if (_address != NULL) {
		_is_set = true;
	}
}

void FinderTarget::from_config() {
	NodePrefs* prefs = _mesh.getNodePrefs();
	_address = prefs->fixme_custom_pref__target_address;
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

// Last known latitude of the target
float FinderTarget::lat() {
	return _last_location.lat;
}

// Last known longitude of the target
float FinderTarget::lon() {
	return _last_location.lon;
}
