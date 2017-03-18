#pragma once

//#include <memory>

#include <boost/geometry.hpp>

#include <ofVec2f.h>
#include <ofVec3f.h>
#include <ofRectangle.h>

#include "ofGeometryTraits.h"


// TODO add way to append points
// TODO add reverse iterators
// TODO move parts to cpp file
// TODO fix bounding box wrong y coordinates
// TODO find out what happens if algotithms are called on invalid rings
// TODO add combining multiple geometries

template<bool CLOCK_WISE> class Ring {

	template<bool CW>
	friend class Ring;
	//typedef boost::geometry::model::ring<ofVec2f, CLOCK_WISE>> ring_type;
	//template<bool CW>
	//using ring_type = boost::geometry::model::ring<ofVec2f, CW>>;

public:

	Ring() { }

	template<typename POINT_TYPE>
	Ring(const std::vector<POINT_TYPE>& points) : ring{ points.begin(), points.end() } {
		boost::geometry::correct(ring);
	}

	template<typename BEGIN_IT, typename END_IT>
	Ring(BEGIN_IT begin, END_IT end) : ring{ begin, end } {
		boost::geometry::correct(ring);
	}

	/*
	bool is_valid() {
		return boost::geometry::is_valid(ring);
	}*/

	/*
	void correct() {
		boost::geometry::correct(ring);
	}*/


	// TODO place ring in simplify twice
	void simplify(float max_point_distance) {
		boost::geometry::model::ring<ofVec2f, CLOCK_WISE> result;
		boost::geometry::simplify(ring, result, max_point_distance);
		ring = result;
		flag_update_all();
	}


	bool encloses(ofVec2f point) {
		return boost::geometry::within(point, ring);
	}


	template<bool CW>
	bool encloses(const Ring<CW>& other) {
		return boost::geometry::within(other.ring, ring);
	}


	template<bool CW>
	bool overlaps(const Ring<CW>& other) {
		return boost::geometry::overlaps(ring, other.ring);
	}
	
	
	float area() {
		if (area_needs_update) {
			_area = boost::geometry::area(ring);
			area_needs_update = false;
		}
		return _area;
	}


	float perimeter() {
		if (perimeter_needs_update) {
			_perimeter = boost::geometry::perimeter(ring);
			perimeter_needs_update = false;
		}
		return _perimeter;
	}
	
	/*
	ofRectangle bounding_box() {
		if (bounding_box_needs_update) {
			boost::geometry::model::box<ofVec2f> temporary;
			boost::geometry::envelope(*ring, temporary);
			_bounding_box.set(temporary.min_corner(), temporary.max_corner());
			bounding_box_needs_update = false;
		}
		return _bounding_box;
	}*/


	ofVec2f centroid() {
		if (centroid_needs_update) {
			boost::geometry::centroid(ring, _centroid);
			centroid_needs_update = false;
		}
		return _centroid;
	}


	inline decltype(auto) begin()       { return boost::begin(ring); }
	inline decltype(auto) begin() const { return boost::const_begin(ring); }
	inline decltype(auto) end()         { return boost::end(ring); }
	inline decltype(auto) end()   const { return boost::const_end(ring); }

	
	// NRVO
	template<bool CW>
	Ring<CLOCK_WISE> combined_with(Ring<CW>& other) {
		if (overlaps(other)) {
			std::vector<boost::geometry::model::ring<ofVec2f, CLOCK_WISE>> out;
			boost::geometry::union_(ring, other.ring, out);
			return Ring<CLOCK_WISE>(boost::begin(out[0]), boost::end(out[0]));
		}
		return Ring<CLOCK_WISE>();
	}


private:

	float       _area;
	float       _perimeter;
	//ofRectangle _bounding_box;
	ofVec2f     _centroid;

	bool area_needs_update{ true };
	bool perimeter_needs_update{ true };
	//bool bounding_box_needs_update{ true };
	bool centroid_needs_update{ true };

	boost::geometry::model::ring<ofVec2f, CLOCK_WISE> ring;


	void flag_update_all() {
		area_needs_update = true;
		perimeter_needs_update = true;
		//bounding_box_needs_update = true;
		centroid_needs_update = true;
	}

};
