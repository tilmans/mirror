#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include "ofxFaceTracker2.h"

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
    ofxFaceTracker2 tracker;
        
    ofImage image;
    
    ofxToggle videoDisplay;
    ofxToggle showFace;
    ofxToggle showGuide;
    ofxToggle showHead;
    ofxFloatSlider x;
    ofxFloatSlider y;
    ofxFloatSlider z;
    ofxFloatSlider scale;
    ofxPanel gui;

    ofxAssimpModelLoader model;
    ofLight light;
    ofMaterial material;
};
