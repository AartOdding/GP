#include "ofApp.h"
#include "ofxKinect.h"

//#include "kinect_constants.h"


void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetWindowTitle("Aart Odding - 2016");

	//near_clipping.addListener(this, &ofApp::nearClippingChanged);
	far_clipping.addListener(this, &ofApp::farClippingChanged);
	use_mirroring.addListener(this, &ofApp::mirroringChanged);
	angle.addListener(this, &ofApp::angleChanged);
	sample_background.addListener(this, &ofApp::sampleBackground);

	gui.setup();
	gui.add(settings.setup());
	gui.add(connected_devices.setup());
	gui.setPosition(50, 20);
	settings.setName("Kinect Settings");
	connected_devices.setName("Kinect Serials:");

	//settings.add(near_clipping.setup("Near threshold mm", 500, 0, 6000));
	settings.add(far_clipping.setup("Far threshold mm", 3000, 0, 6000));
	settings.add(angle.setup("Angle", 0, -25, 25));
	settings.add(use_mirroring.setup("Use mirroring", true));
	settings.add(sample_background.setup("background"));
	/*
	for (std::string serial = ofxKinect::nextAvailableSerial(); serial != ""; serial = ofxKinect::nextAvailableSerial()) {
		KinectData* new_kinect = new KinectData;
		new_kinect->kinect = make_unique<Kinect>();
		new_kinect->kinect->start(serial);
		connected_devices.add(new_kinect->serial.setup(serial));
		kinects.push_back(new_kinect);
	}*/
	main.start(ofxKinect::nextAvailableSerial());
}


void ofApp::farClippingChanged(int& far_dist) {
	//int near_dist = kinect::Settings::getNearCutoffDistance(main);
	main.set_cutoff_distance(far_dist);
	/*
	for (KinectData* kd : kinects) {
		int near_dist = kd->kinect->getNearCutoffDistance();
		kd->kinect->setCutoffDistances(near_dist, far_dist);
	}*/
}


void ofApp::sampleBackground() {
	cout << "hey there\n";
	main.sample_background(30);
}

/*
void ofApp::nearClippingChanged(int& near_dist) {
	int far_dist = kinect::Settings::getFarCutoffDistance(main);
	kinect::Settings::setCutoffDistances(main, near_dist, far_dist);
	
	for (KinectData* kd : kinects) {
		int far_dist = kd->kinect->getFarCutoffDistance();
		kd->kinect->setCutoffDistances(near_dist, far_dist);
	}
}*/


void ofApp::angleChanged(int& angle) {
	main.set_angle(angle);
	/*
	main.setAngle(angle);
	for (KinectData* kd : kinects) {
		kd->kinect->setAngle(angle);
	}*/
}


void ofApp::mirroringChanged(bool& val) {
	//kinect::Settings::setUseMirroring(main, val);
	/*
	for (KinectData* kd : kinects) {
		kinect::Settings::setUseMirroring(*(kd->kinect), val);
	}*/
}


void ofApp::update(){
	main.copy_raw_image(main_raw);
	main.copy_processed_image(main_processed);
	for (KinectData* kd : kinects) {
		kd->kinect->copy_raw_image(kd->raw);
		kd->kinect->copy_processed_image(kd->processed);
	}

	if (main.has_blobs()) {
		blobs = main.get_blobs();
	}


}

void ofApp::draw() {

	ofBackground(245, 245, 245);
	
	/*
	int x_pos = 50;
	
	ofSetColor(255, 255, 255);
	for (KinectData* kd : kinects) {
		kd->raw.draw(x_pos, 250, 320, 240);
		kd->processed.draw(x_pos, 540, 320, 240);
		x_pos += 370;
	}*/

	
	//main_raw.draw(50, 250, 320, 240);
	//main_processed.draw(50, 540, 320, 240);

	gui.draw();

	ofTranslate(600, 100);

	ofSetLineWidth(5);

	

	//if (!data.empty()) {

		//if (data->size() > 0) cout << (*data)[0].distance << '\n';
	//auto x = 20;

	for (auto& blob : blobs) {
		ofSetColor(0, 0, 0);
		drawRing(blob.outline);
		for (auto& hole : blob.holes) {
			drawRing(hole);
		}
		ofSetColor(255, 0, 0);
		for (auto& pt : blob.samples) {
			ofDrawCircle(pt.first, pt.second, 5);
		}
	}
	
}