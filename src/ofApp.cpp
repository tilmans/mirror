#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    model.loadModel("cgtuts-facial-setup.dae");

    video.setup(1280, 720, true);
    
    gui.setup();
    gui.add(videoDisplay.setup("Video [v]", true));
    gui.add(showFace.setup("Face [f]", false));
    gui.add(showGuide.setup("Face Guide [g]", false));
    gui.add(showHead.setup("Head [h]", true));
    gui.add(x.setup("X", 0, -500, 500));
    gui.add(y.setup("Y", -175, -500, 500));
    gui.add(z.setup("Z", 100, -500, 500));
    gui.add(scale.setup("Scale", 0.51, 0, 2));

    tracker.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    
    if (video.isFrameNew()) {
        image = ofImage(video.getPixels());
        image.mirror(false,true);

        tracker.update(image);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    if (videoDisplay)
        image.draw(0, 0);
    
    if (showHead) {
        if (tracker.size() > 0) {
            ofPushView();
            
            tracker.getInstances()[0].loadPoseMatrix();
            
            model.setRotation(0, 180, 1, 0, 0);
            model.setPosition(x, y, z);
            model.setScale(scale, scale, scale);
            
            light.setPosition(ofGetWidth()/2, ofGetHeight()/2, 600);
            light.enable();
            
            material.begin();
            ofEnableDepthTest();
            model.drawFaces();
            ofDisableDepthTest();
            material.end();
            
            ofPopView();
        }
    }

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
    
    if (key == 'h')
        showHead = !showHead;
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
