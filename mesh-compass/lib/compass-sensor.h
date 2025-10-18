/* Transform the compass sensor output into a useful format. 
 *
 */

// Float sized Pi (regular rounded)
#define PI 3.141593


class Compass {

	protected:
	fixme_sensor_type sensor;

	public:
	Compass::Compass(const uint_8 device_id);
	// Do last minute setup
	void begin();
	// Return the heading of this node
	float heading();

}
