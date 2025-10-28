/* Given the compass, gps, and remote telemetry tell the display how to steer the user
 *
 */
#include "mesh.h"
#include "common.h"

#define ORIENTATION_CHECK_INTERVAL_MS 50


class FinderNode {

	protected:
	MyMesh _mesh;
	uint8_t* _address;
	Location _last_location;

	public:
	FinderNode(MyMesh mesh);
	void from_config();
	void query_location();
	float lat();
	float lon();
};

class FinderTarget : FinderNode {

	protected:
	bool _is_set = false;

	public:
	float last_mod = 0;
	uint8_t battery_status;

	void from_config() = 0;
	bool is_set();
	void set_address(uint8_t* address);
};

class FinderSelf : FinderNode {

	protected:
	FinderTarget _target;
	Accelerometer _accel;
	Compass _compass;

	public:
	FinderSelf(MyMesh mesh);
	void loop();
	void find_home();
	void find_target();
	float direction_to_target();
	float heading_to_target();
};

