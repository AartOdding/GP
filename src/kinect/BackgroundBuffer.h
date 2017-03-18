#pragma once

#include "ofxOpenCv.h"



class BackgroundBuffer {

public:

	BackgroundBuffer(int w, int h) : width{ w }, height{ h } {
		pixels.allocate(w, h, OF_IMAGE_GRAYSCALE);
		pixels.set(0);
	}

	void add(const ofxCvGrayscaleImage& source) {
		auto img_pixels{ source.getPixels() };
		for (int i{ 0 }; i < width * height; ++i) {
			if (img_pixels[i] > pixels[i]) {
				pixels[i] = img_pixels[i];
			}
		}
	}

	void clear() {
		pixels.set(0);
	}

	void copy_to(ofxCvGrayscaleImage& destination) {
		destination.setFromPixels(pixels);
	}


private:

	ofPixels pixels;
	const int width;
	const int height;

};
