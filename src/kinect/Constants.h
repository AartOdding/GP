#pragma once

#include <chrono>



namespace kinect {


	class Constants {

		friend class Kinect;

	public:

		static constexpr int DEPTH_IMAGE_WIDTH{ 640 };
		static constexpr int DEPTH_IMAGE_HEIGHT{ 480 };

		static constexpr int MIN_CUTOFF_DISTANCE{ 500 };
		static constexpr int MAX_CUTOFF_DISTANCE{ 5000 };


	private:

		static constexpr std::chrono::milliseconds SLEEP_TIME_MS{ 10ms };

		static constexpr float SIMPLIFICATION_DISTANCE{ 5.0f };

		static constexpr int   PIXELS_PER_DEPTH_SAMPLE{ 700 };
		static constexpr int   MAX_BLOBS_CONSIDERED{ 8 };
		static constexpr int   THRESHOLD_AFTER_FILTERING{ 10 };

		static constexpr int   MIN_HOLE_AREA{ 1000 };
		static constexpr int   MIN_OUTLINE_AREA{ 2000 };

		static constexpr int   MIN_AREA{ MIN_HOLE_AREA < MIN_OUTLINE_AREA ? MIN_HOLE_AREA : MIN_OUTLINE_AREA };
		static constexpr int   MAX_AREA{ DEPTH_IMAGE_WIDTH * DEPTH_IMAGE_HEIGHT };

	};

} // namespace kinect

