 #pragma once

#include <vector>
#include <thread>
#include <memory>
#include <mutex>
#include <string>
#include <atomic>

#include <ofxOpenCv.h>
#include <ofxKinect.h>

#include "kinect/Constants.h"
#include "kinect/Blob.h"
#include "kinect/BackgroundBuffer.h"



namespace kinect {


	class Kinect {

		typedef std::pair<int, int> Point;

	public:

		/* 
		 * Constructor: Creates a new Kinect object. If no Settings object is given as provided the default
		 * settings will be used.
		 */
		Kinect();


		/*
		 * Destructor: Deletes the Kinect object. It is important that this gets called to close the kinect
		 * stream, and kill the thread running it.
		 */
		~Kinect();


		/*
		 * Open the kinect with given Serial ID, and start up a new thread to read it out.
		 */
		void start(const std::string&);


		/*
		* This function captures the raw image of the kinect over n_frames frames, and creates
		* an avarage over time image of the background. This image can then be used to be subtracted
		* from the raw image, to remove background objects.
		*/
		void sample_background(int);


		/*
		* Receive a shared pointer (thread safe) to the vector of the latest found blobs. These blobs are
		* the outlines of the objects in front of the kinect, mirrored if use_mirroring is true
		*/
		bool has_blobs();
		std::vector<Blob>&& get_blobs();


		/*
		 * Thread safe functions to copy the images used to find the blobs. Image is copies into the given 
		 * image reference. The raw image is the black and white depth image received from the kinect.
		 * The background image is the image subtracted from the raw image, to filter it out.
		 * The Processed image is the result of said subtraction.
		 */
		void copy_raw_image(ofxCvGrayscaleImage&);
		void copy_background_image(ofxCvGrayscaleImage&);
		void copy_processed_image(ofxCvGrayscaleImage&);
		

		void set_angle(int);
		float get_angle();

		void set_cutoff_distance(int);
		int get_cutoff_distance();

	private:

		void  main();
		float depth_at(Point);

		int cutoff_distance_mm { 4000 };
		int frames_to_sample   { 0 };
		std::atomic_bool blobs_available{ false };

		std::thread kinect_thread;
		std::mutex blobs_lock;
		std::mutex kinect_lock;

		std::vector<Blob> blobs;

		ofxKinect kinect;
		ofxCvContourFinder contour_finder;

		ofxCvGrayscaleImage raw_image;
		ofxCvGrayscaleImage processed_image;
		ofxCvGrayscaleImage background_image;

		BackgroundBuffer background_buffer{ Constants::DEPTH_IMAGE_WIDTH, Constants::DEPTH_IMAGE_HEIGHT };


	}; // class Kinect


} // namespace kinect
