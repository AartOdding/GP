#include "Kinect.h"
#include "RandomRange.h"

// WARNING: A blob can have two holes, where one hole is inside of the other. it can also have another blob inside
//          of it, but this would become its own Blob instance.
// WARNING: Because of simplification of the blobs, extremely rarely a blob might become selfintersecting, or
//          intersecting with a hole. Also very very very rarely a hole could accidently not be assigned to its
//          outline.



namespace kinect {


	Kinect::Kinect() {
		raw_image.allocate(Constants::DEPTH_IMAGE_WIDTH, Constants::DEPTH_IMAGE_HEIGHT);
		processed_image.allocate(Constants::DEPTH_IMAGE_WIDTH, Constants::DEPTH_IMAGE_HEIGHT);
		background_image.allocate(Constants::DEPTH_IMAGE_WIDTH, Constants::DEPTH_IMAGE_HEIGHT);
		background_image.set(0.0f);

		kinect.setRegistration(false);
		kinect.init(false, false, false);
	}


	Kinect::~Kinect() {
		kinect.close();
		if (kinect_thread.joinable()) {
			kinect_thread.join();
		}
	}


	void Kinect::start(const std::string& serial) {
		kinect.setDepthClipping(Constants::MIN_CUTOFF_DISTANCE, cutoff_distance_mm);
		kinect.open(serial);
		kinect_thread = thread(&Kinect::main, this);
	}


	void Kinect::sample_background(int n_frames) {
		std::lock_guard<std::mutex> guard(kinect_lock);
		background_buffer.clear();
		frames_to_sample = n_frames;
	}


	void Kinect::copy_raw_image(ofxCvGrayscaleImage& destination) {
		std::lock_guard<std::mutex> guard(kinect_lock);
		destination = raw_image;
	}


	void Kinect::copy_processed_image(ofxCvGrayscaleImage& destination) {
		std::lock_guard<std::mutex> guard(kinect_lock);
		destination = processed_image;
	}


	void Kinect::copy_background_image(ofxCvGrayscaleImage& destination) {
		std::lock_guard<std::mutex> guard(kinect_lock);
		destination = background_image;
	}


	bool Kinect::has_blobs() {
		return blobs_available.load();
	}


	std::vector<Blob>&& Kinect::get_blobs() {
		std::lock_guard<std::mutex> guard(blobs_lock);
		blobs_available = false;
		return std::move(blobs);
	}


	void Kinect::set_angle(int angle) {
		std::lock_guard<std::mutex> lock(kinect_lock);
		kinect.setCameraTiltAngle(angle);
	}


	float Kinect::get_angle() {
		std::lock_guard<std::mutex> lock(kinect_lock);
		return kinect.getCurrentCameraTiltAngle();
	}


	void Kinect::set_cutoff_distance(int distance_mm) {
		if (distance_mm > Constants::MIN_CUTOFF_DISTANCE && distance_mm < Constants::MAX_CUTOFF_DISTANCE) {
			std::lock_guard<std::mutex> lock(kinect_lock);
			cutoff_distance_mm = distance_mm;
			kinect.setDepthClipping(Constants::MIN_CUTOFF_DISTANCE, distance_mm);
		}
	}


	int Kinect::get_cutoff_distance() {
		std::lock_guard<std::mutex> lock(kinect_lock);
		return cutoff_distance_mm;
	}


	void Kinect::main() {

		while (kinect.isConnected()) {
			kinect.update();

			if (kinect.isFrameNewDepth()) {

				{
					std::lock_guard<std::mutex> guard(kinect_lock);
					raw_image.setFromPixels(kinect.getDepthPixels());

					if (frames_to_sample > 0) {
						background_buffer.add(raw_image);
						if (--frames_to_sample <= 0) {
							background_buffer.copy_to(background_image);
						}
					}

					cvSub(raw_image.getCvImage(), background_image.getCvImage(), processed_image.getCvImage());
					processed_image.threshold(Constants::THRESHOLD_AFTER_FILTERING);

					contour_finder.findContours( processed_image, Constants::MIN_AREA, 
						Constants::MAX_AREA, Constants::MAX_BLOBS_CONSIDERED, true, true);
				}

				std::vector<Blob> new_blobs;

				for (auto& blob : contour_finder.blobs) {
					if (!blob.hole && blob.area > Constants::MIN_OUTLINE_AREA) {
						new_blobs.push_back( { Ring<true>(blob.pts), blob.boundingRect } );
						Blob& newest{ new_blobs.back() };
						newest.outline.simplify(Constants::SIMPLIFICATION_DISTANCE);

						for (auto& hole : contour_finder.blobs) {
							if (hole.hole && newest.outline.encloses(hole.pts[0]) && hole.area > Constants::MIN_HOLE_AREA) {
								newest.holes.push_back(Ring<false>(hole.pts));
								newest.holes.back().simplify(Constants::SIMPLIFICATION_DISTANCE);
							}
						}
					}
				}

				for (auto& blob : new_blobs) {
					float depth{ 0 };
					int count{ 0 };
					int n_samples = blob.area() / Constants::PIXELS_PER_DEPTH_SAMPLE;
					while (count < n_samples) {
						auto pt = RandomRange::normal_point(blob.bounding_box);
						if (blob.contains_point(ofVec2f(pt.first, pt.second))) {
							blob.samples.push_back(pt);
							depth += depth_at(pt);
							++count;
						}
					}
					blob.distance = depth / count;
				}

				std::lock_guard<std::mutex> guard(blobs_lock);
				blobs = std::move(new_blobs);
				blobs_available = true;
			}
			else {
				std::this_thread::sleep_for(Constants::SLEEP_TIME_MS);
			}
		}
	}


	float Kinect::depth_at(Point point) {
		uint8_t brightness{ raw_image.getPixels().getColor(point.first, point.second)[0] };
		return ofMap(brightness, 255, 0, Constants::MIN_CUTOFF_DISTANCE, cutoff_distance_mm);
	}

} // namespace kinect
