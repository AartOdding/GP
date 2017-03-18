#pragma once

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>


class ofVec2f;
class ofVec3f;



	///////////////////////
	//                   //
	//      ofVec2f      //
	//                   //
	///////////////////////

namespace boost {
	namespace geometry {
		namespace traits {

			template<> struct tag<ofVec2f> {
				typedef point_tag type;
			};

			template<> struct coordinate_type<ofVec2f> {
				typedef float type;
			};

			template<> struct coordinate_system<ofVec2f> {
				typedef cs::cartesian type;
			};

			template<> struct dimension<ofVec2f> : boost::mpl::int_<2> {
			};

			template<>
			struct access<ofVec2f, 0> {
				static float get(const ofVec2f& p) {
					return p.x;
				}

				static void set(ofVec2f& p, float value) {
					p.x = value;
				}
			};

			template<>
			struct access<ofVec2f, 1> {
				static float get(const ofVec2f& p) {
					return p.y;
				}

				static void set(ofVec2f& p, float value) {
					p.y = value;
				}
			};

		} // namespace traits
	} // namespace geometry
} // namespace boost



	///////////////////////
	//                   //
	//      ofVec3f      //
	//                   //
	///////////////////////

namespace boost {
	namespace geometry {
		namespace traits {

			template<> struct tag<ofVec3f> {
				typedef point_tag type;
			};

			template<> struct coordinate_type<ofVec3f> {
				typedef float type;
			};

			template<> struct coordinate_system<ofVec3f> {
				typedef cs::cartesian type;
			};

			template<> struct dimension<ofVec3f> : boost::mpl::int_<3> {
			};

			template<>
			struct access<ofVec3f, 0> {
				static float get(const ofVec3f& p) {
					return p.x;
				}

				static void set(ofVec3f& p, float value) {
					p.x = value;
				}
			};

			template<>
			struct access<ofVec3f, 1> {
				static float get(const ofVec3f& p) {
					return p.y;
				}

				static void set(ofVec3f& p, float value) {
					p.y = value;
				}
			};

			template<>
			struct access<ofVec3f, 2> {
				static float get(const ofVec3f& p) {
					return p.z;
				}

				static void set(ofVec3f& p, float value) {
					p.z = value;
				}
			};

		} // namespace traits
	} // namespace geometry
} // namespace boost
