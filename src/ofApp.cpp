#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0,0,0);
    multiplier = 2;
    width = 1280;
    height = 720;
    offset = 60;
    
    video.setup(width, height, true);
    video.videoSettings();
    
    haarFinder.setup("haarcascade_frontalface_default.xml");
    bot.load("wire.png");
    ratio = bot.getHeight() / bot.getWidth();
    
    gui.setup(); // most of the time you don't need a name
    gui.add(offset.setup("Offset", 100, 0, 500));
    gui.add(alpha.setup("Alpha", 255, 0, 255));
    gui.add(face.setup("Camera", false));
    gui.add(showblob.setup("Blobs", false));
    gui.add(max.setup("Max", 50000, 10000, 100000));
    gui.add(min.setup("Min", 20000, 10000, 100000));
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    
    if (video.isFrameNew()) {
        image = ofImage(video.getPixels());
        ofImage small;
        small.clone(image);
        small.setImageType(OF_IMAGE_GRAYSCALE);
        small.resize(width/multiplier,height/multiplier);
        haarFinder.findHaarObjects(small);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    // ofSetColor(255, 0, 0);
    if(face) {
        image.draw(0,0);
    }
    ofNoFill();
    ofSetColor(255, 255, 255, alpha);
    
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
    
    bot.draw(mainblob.boundingRect.getTopLeft().x*multiplier, mainblob.boundingRect.getTopLeft().y*multiplier-offset, mainblob.boundingRect.width*multiplier, mainblob.boundingRect.height*ratio*multiplier);
    
    alpha = ofMap(mainblob.area, min, max, 0, 255);
        
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
