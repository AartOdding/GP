#include "Settings.h"
#include "Kinect.h"
#include "Constants.h"



namespace kinect {


	void Settings::setAngle(Kinect& kinect, int angle) {
		std::lock_guard<std::mutex> lock(kinect.kinect_lock);
		kinect.kinect.setCameraTiltAngle(angle);
	}


	float Settings::getAngle(Kinect& kinect) {
		std::lock_guard<std::mutex> lock(kinect.kinect_lock);
		return kinect.kinect.getCurrentCameraTiltAngle();
	}

	/*
	void Settings::setUseMirroring(Kinect& kinect, bool value) {
		std::lock_guard<std::mutex> lock(kinect.kinect_lock);
		kinect.settings.use_mirroring = value;
	}


	bool Settings::getUseMirroring(Kinect& kinect) {
		std::lock_guard<std::mutex> lock(kinect.kinect_lock);
		return kinect.settings.use_mirroring;
	}*/

	/*
	void Settings::setUseBackgroundSubtraction(Kinect& kinect, bool value) {
		std::lock_guard<std::mutex> lock(kinect.kinect_lock);
		kinect.settings.use_background_subtraction = value;
	}


	bool Settings::getUseBackgroundSubtraction(Kinect& kinect) {
		std::lock_guard<std::mutex> lock(kinect.kinect_lock);
		return kinect.settings.use_background_subtraction;
	}*/


	void Settings::setCutoffDistance(Kinect& kinect, int distance_mm) {
		if (distance_mm > Constants::MIN_CUTOFF_DISTANCE && distance_mm < Constants::MAX_CUTOFF_DISTANCE) {
			std::lock_guard<std::mutex> lock(kinect.kinect_lock);
			kinect.cutoff_distance_mm = distance_mm;
			kinect.kinect.setDepthClipping(Constants::MIN_CUTOFF_DISTANCE, distance_mm);
		}
	}


	int Settings::getCutoffDistance(Kinect& kinect) {
		std::lock_guard<std::mutex> lock(kinect.kinect_lock);
		return kinect.cutoff_distance_mm;
	}

	/*
	void Settings::setCutoffDistances(Kinect& kinect, int near_dist_mm, int far_dist_mm) {
		std::lock_guard<std::mutex> lock(kinect.kinect_lock);
		kinect.settings.near_cutoff_mm = near_dist_mm < Constants::MIN_CUTOFF_DISTANCE ? Constants::MIN_CUTOFF_DISTANCE : near_dist_mm;
		kinect.settings.far_cutoff_mm = far_dist_mm > Constants::MAX_CUTOFF_DISTANCE ? Constants::MAX_CUTOFF_DISTANCE : far_dist_mm;
		int near_clipping = kinect.settings.near_cutoff_mm - Constants::BUFFER_DISTANCE_MM;
		int far_clipping = kinect.settings.far_cutoff_mm + Constants::BUFFER_DISTANCE_MM;
		kinect.kinect.setDepthClipping(near_clipping, far_clipping);
		kinect.near_brightness_cutoff = ofMap(kinect.settings.near_cutoff_mm, near_clipping, far_clipping, 255, 0, true);
		kinect.far_brightness_cutoff = ofMap(kinect.settings.far_cutoff_mm, near_clipping, far_clipping, 255, 0, true);
	}


	int Settings::getNearCutoffDistance(Kinect& kinect) {
		std::lock_guard<std::mutex> lock(kinect.kinect_lock);
		return kinect.settings.near_cutoff_mm;
	}


	int Settings::getFarCutoffDistance(Kinect& kinect) {
		std::lock_guard<std::mutex> lock(kinect.kinect_lock);
		return kinect.settings.far_cutoff_mm;
	}
	*/
	/*
	void Settings::setFilteringMode(Kinect& kinect, FilteringMode mode) {
		std::lock_guard<std::mutex> lock(kinect.kinect_lock);
	}


	FilteringMode Settings::getFilteringMode(Kinect& kinect) {
		std::lock_guard<std::mutex> lock(kinect.kinect_lock);
		return kinect.settings.filtering_mode;
	}
	*/

} // namespace kinect
