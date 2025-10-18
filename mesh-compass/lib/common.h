
class Location {

	float lat = 0;
	float lon = 0;
	bool _is_set = false;

	Location(float lat_, float lon_) {
		lat = lat_;
		lon = lon_;
		_is_set = true;
	}

	Location() {
		lat = 0;
		lon = 0;
	}

	bool is_set() {
		return _is_set
	}

	void update(float lat_, float lon_) {
		if (lat_ == NULL || lon_ == NULL) {
			return _is_set;
		}
		lat = lat_;
		lon = lon_;
		_is_set = true;
		return true;
	}
}
