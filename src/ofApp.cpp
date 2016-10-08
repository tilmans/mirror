#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    model.loadModel("cgtuts-facial-setup.dae");
    
    ofBackground(0,0,0);
    multiplier = 2;
    width = 1280;
    height = 720;
    
    video.setup(width, height, true);
    video.videoSettings();
    
    haarFinder.setup("haarcascade_frontalface_default.xml");
    // bot.load("wire.png");
    ratio = bot.getHeight() / bot.getWidth();
    
    gui.setup(); // most of the time you don't need a name
    gui.add(offset.setup("Offset", 300, 0, 500));
    gui.add(scale.setup("Scale", 3, 0, 10));
    gui.add(alpha.setup("Alpha", 255, 0, 255));
    gui.add(face.setup("Camera", true));
    gui.add(showblob.setup("Blobs", false));
    gui.add(max.setup("Max", 60000, 10000, 100000));
    gui.add(min.setup("Min", 35000, 10000, 100000));
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    
    if (video.isFrameNew()) {
        image = ofImage(video.getPixels());
        image.mirror(false, true);
        ofImage small;
        small.clone(image);
        small.setImageType(OF_IMAGE_GRAYSCALE);
        small.resize(width/multiplier,height/multiplier);
        haarFinder.findHaarObjects(small);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255, 255);

    float xscale = (float)ofGetWidth()/(float)1280;
    float yscale = (float)ofGetHeight()/(float)720;
    if(face) {
        ofSetColor(255, 255, 255, 255);
        image.draw(0,0,ofGetWidth(),ofGetHeight());
    }
    ofNoFill();
    // ofSetColor(255, 255, 255, alpha);
    
    ofxCvBlob mainblob;
    for (int i=0; i<haarFinder.blobs.size(); i++) {
        ofxCvBlob blob = haarFinder.blobs[i];
        if (blob.area > mainblob.area) {
            mainblob = blob;
        }
        if(showblob) {
            ofDrawRectangle(blob.boundingRect.getTopLeft().x*multiplier, blob.boundingRect.getTopLeft().y*multiplier, blob.boundingRect.width*multiplier, blob.boundingRect.height*multiplier);
        }
    }
    
    alpha = ofMap(mainblob.area, min, max, 0, 255);
    
    light.setPosition(ofGetWidth()/2, ofGetHeight()/2, 600);
    light.enable();
    material.begin();
    float mainscale = mainblob.boundingRect.width / ofGetWidth() * scale;
    //model.setPosition(ofGetWidth()/2, (float)ofGetHeight() * 0.75 , 0);
    model.setScale(mainscale, mainscale, mainscale);
    model.setPosition(mainblob.centroid.x*multiplier*xscale, mainblob.centroid.y*multiplier*yscale+offset, 0);
    ofEnableDepthTest();
    model.drawFaces();
    ofDisableDepthTest();

    gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
