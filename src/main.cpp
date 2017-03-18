#include "ofMain.h"
#include "ofApp.h"



int main( ){
	ofSetupOpenGL(1800, 900, OF_WINDOW);
	ofRunApp(new ofApp());
}
/*
int main() {
	ofAppGLFWWindow win;
	//win.setNumSamples(8);  
	win.setMultiDisplayFullscreen(true); //this makes the fullscreen window span across all your monitors  

	ofSetupOpenGL(&win, 4480, 1080, OF_FULLSCREEN);
	ofRunApp(new ofApp());
}*/

