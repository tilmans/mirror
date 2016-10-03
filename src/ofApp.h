#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

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
    
    ofxCvHaarFinder haarFinder;
    ofImage image;
    ofImage bot;
    int multiplier;
    int width,height;
    float ratio;
    // int offset;
    
    //ofxFloatSlider radius;
    //ofxColorSlider color;
    //ofxVec2Slider center;
    ofxIntSlider offset;
    ofxIntSlider alpha;
    ofxIntSlider max;
    ofxIntSlider min;
    ofxToggle face;
    ofxToggle showblob;
    //ofxButton twoCircles;
    //ofxButton ringButton;
    //ofxLabel screenSize;
    
    ofxPanel gui;

};
