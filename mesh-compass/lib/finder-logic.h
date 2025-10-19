/* Given the compass, gps, and remote telemetry tell the display how to steer the user
 *
 */

#include "common.h"

#define ORIENTATION_CHECK_INTERVAL_MS 50


class FinderNode {

	MyMesh _mesh;
	fixme_meshcore_node_type _node;  // FIXME: Find meshcore node type
	uint8_t* _address;
	Location _last_location;

	FinderNode(MyMesh mesh);
	void from_config();
	void query_location();
	float lat();
	float lon();
}

class FinderSelf : FinderNode {

	FinderTarget _target;
	Accelerometer _accel;
	Compass _compass;

	FinderSelf(MyMesh mesh);
	void loop();
	void find_home();
	void find_target();
	float direction_to_target();
	float heading_to_target();
}

class FinderTarget : FinderNode {

	bool _is_set = false;

	float last_mod = 0;
	uint8_t battery_status;

	void from_config() = 0;
	bool is_set();
	void set_address(fixme_node_address_type address);
}
