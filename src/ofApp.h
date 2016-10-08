#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofVideoGrabber video;
    
    ofxCvHaarFinder faceFinderFront;
    ofxCvHaarFinder faceFinderSide;
    ofxCvHaarFinder eyeFinder;
    ofxCvBlob leftEye;
    ofxCvBlob rightEye;
    
    ofImage image;
    ofImage small;
    int multiplier;
    int width,height;
    
    ofxIntSlider offset;
    ofxFloatSlider scale;
    ofxIntSlider cropWidth;
    ofxIntSlider alpha;
    ofxIntSlider max;
    ofxIntSlider min;
    ofxToggle face;
    ofxToggle showblob;
    
    ofxPanel gui;
    
    ofxAssimpModelLoader model;
    
    ofLight light;
    ofMaterial material;

};
