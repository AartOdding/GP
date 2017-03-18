#pragma once

#include <vector>

#include "Ring.h"



namespace kinect {

	struct Blob {

		Ring<true> outline;
		ofRectangle bounding_box;
		std::vector<Ring<false>> holes;
		float distance;
		std::vector<std::pair<int, int>> samples;


		bool contains_point(ofVec2f point) {
			if (outline.encloses(point)) {
				for (auto& hole : holes) {
					if (hole.encloses(point)) {
						return false;
					}
 				}
				return true;
			}
			return false;
		}


		float area() {
			float hole_area{ 0 };
			for (auto& h : holes) {
				hole_area += h.area();
			}
			return outline.area() - hole_area;
		}

	};

}
