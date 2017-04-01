#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    width = 1280;
    height = 720;
    
    video.setup(width, height, true);
    
    gui.setup(); // most of the time you don't need a name
    gui.add(videoDisplay.setup("Video [v]", true));
    gui.add(showFace.setup("Face [f]", true));
    gui.add(showGuide.setup("Face Guide [g]", true));

    tracker.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    
    if (video.isFrameNew()) {
        image = ofImage(video.getPixels());
        image.mirror(false,true);

        tracker.update(image);
        
        vector<ofxFaceTracker2Instance> inst = tracker.getInstances();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (videoDisplay)
        image.draw(0, 0);
    
    if (showFace)
        tracker.drawDebug();
    
    if (showGuide)
        tracker.drawDebugPose();

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'v')
        videoDisplay = !videoDisplay;
    
    if (key == 'f')
        showFace = !showFace;
    
    if (key == 'g')
        showGuide = !showGuide;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
