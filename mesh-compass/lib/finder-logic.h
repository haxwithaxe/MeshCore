/* Given the compass, gps, and remote telemetry tell the display how to steer the user
 *
 */
#define FINDER_UNSET 255
#define FINDER_ERROR 245

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

	float direction_to_target();
	float heading();
	float heading_to_target();
}

class FinderTarget : FinderNode {

	bool _is_set = false;

	bool is_set();
	void set_address(fixme_node_address_type address);
}
