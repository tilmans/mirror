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
    
    eyeFinder.setup("cascades/haarcascades_cuda/haarcascade_eye_tree_eyeglasses.xml");
    faceFinderFront.setup("cascades/haarcascades_cuda/haarcascade_frontalface_default.xml");
    
    gui.setup(); // most of the time you don't need a name
    gui.add(offset.setup("Offset", 300, 0, 500));
    gui.add(scale.setup("Scale", 3, 0, 10));
    gui.add(cropWidth.setup("Crop", 300, 100, 1000));
    gui.add(alpha.setup("Alpha", 255, 0, 255));
    gui.add(brightness.setup("Brightness", .5, 0, 1));
    gui.add(contrast.setup("Contrast", .5, 0, 1));
    gui.add(face.setup("Camera", true));
    gui.add(showblob.setup("Blobs", true));
    gui.add(max.setup("Max", 60000, 10000, 100000));
    gui.add(min.setup("Min", 35000, 10000, 100000));

    gui.add(minsize.setup("MinSize", 100, 0, 1000));
    gui.add(maxsize.setup("maxSize", 30000, 0, 10000));
}

//--------------------------------------------------------------
void ofApp::update(){
    video.update();
    
    if (video.isFrameNew()) {
        image = ofImage(video.getPixels());
        image.crop(image.getWidth()/2-cropWidth/2,0,cropWidth,image.getHeight());
        image.mirror(false, true);
        ofImage small;
        small.clone(image);
        small.setImageType(OF_IMAGE_GRAYSCALE);
        small.resize(image.getWidth()/multiplier,image.getHeight()/multiplier);
        cvi.setFromPixels(small);
        cvi.brightnessContrast(brightness, contrast);
        faceFinderFront.findHaarObjects(cvi);
        eyeFinder.findHaarObjects(cvi);
        contour.findContours(cvi,minsize,maxsize,100,false,true);
        ofLog() << "Blobs found" << contour.nBlobs;
        
        /*
        for (int i=0; i<haarFinder.blobs.size(); i++) {
            ofxCvBlob blob = haarFinder.blobs[i];
            if (blob.area > mainblob.area) {
                mainblob = blob;
            }
            if(showblob) {
                ofDrawRectangle(blob.boundingRect.getTopLeft().x*multiplier, blob.boundingRect.getTopLeft().y*multiplier, blob.boundingRect.width*multiplier, blob.boundingRect.height*multiplier);
            }
        }
         */
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255, 255);

    float xscale = (float)ofGetWidth()/(float)image.getWidth();
    float yscale = (float)ofGetHeight()/(float)image.getHeight();
    if(face) {
        image.draw(ofGetWidth()/2-cropWidth/2,0,image.getWidth(),image.getHeight());
    }
    
    ofxCvBlob mainblob;
    ofNoFill();
    if (showblob) {
        ofImage small;
        small.setFromPixels(cvi.getPixels());
        small.draw(ofGetWidth()-small.getWidth(), ofGetHeight()-small.getHeight(), small.getWidth(), small.getHeight());
        
        ofSetColor(255, 0, 0, 255);
        for (int i=0; i<faceFinderFront.blobs.size(); i++) {
            ofxCvBlob blob = faceFinderFront.blobs[i];
            mainblob = blob;
            ofDrawRectangle(
                            ofGetWidth()/2-cropWidth/2+blob.boundingRect.getTopLeft().x*multiplier,
                            blob.boundingRect.getTopLeft().y*multiplier,
                            blob.boundingRect.width*multiplier,
                            blob.boundingRect.height*multiplier);
        }
        ofSetColor(0, 255, 0, 255);
        for (int i=0; i<eyeFinder.blobs.size(); i++) {
            ofxCvBlob blob = eyeFinder.blobs[i];
            ofDrawRectangle(
                            ofGetWidth()/2-cropWidth/2+blob.boundingRect.getTopLeft().x*multiplier,
                            blob.boundingRect.getTopLeft().y*multiplier,
                            blob.boundingRect.width*multiplier,
                            blob.boundingRect.height*multiplier);
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
    contour.draw();
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
