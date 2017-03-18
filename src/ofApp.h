#pragma once

#include <vector>
#include "ofMain.h"
#include "kinect/Kinect.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"
#include "Ring.h"


struct KinectData {
	unique_ptr<kinect::Kinect> kinect;
	ofxLabel serial;
	ofxCvGrayscaleImage raw;
	ofxCvGrayscaleImage processed;
};


class ofApp : public ofBaseApp{

public:

	void setup();
	void update();
	void draw();

	void farClippingChanged(int&);
	//void nearClippingChanged(int&);
	void angleChanged(int&);
	void mirroringChanged(bool&);
	void sampleBackground();

private:
	
	template<typename RING>
	void drawRing(RING ring) {

		bool started = false;
		ofVec2f last;

		for (const ofVec2f& point : ring) {
			if (!started) {
				last = point;
				started = true;
			}
			else {
				ofDrawLine(last, point);
				last = point;
			}
		}
	}

	vector<kinect::Blob> blobs;

	vector<KinectData*> kinects;

	kinect::Kinect main;
	ofxCvGrayscaleImage main_raw;
	ofxCvGrayscaleImage main_processed;

	ofxPanel gui;
	ofxGuiGroup connected_devices;
	ofxGuiGroup settings;

	//ofxIntSlider near_clipping;
	ofxIntSlider far_clipping;
	ofxIntSlider angle;
	ofxToggle use_mirroring;
	ofxButton sample_background;

};
