#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    wiggle1 = new ofxWiggleStereoscopy("Flowers.jpg", "Flowers-depthmap.jpg");
    wiggle2 = new ofxWiggleStereoscopy("cafe_gogh_small.jpg", "cafe_depth_small.png");

}

//--------------------------------------------------------------
void ofApp::update(){
    float x = 10 * cos(ofGetFrameNum() / 4.0f);
    float y = 10 * sin(ofGetFrameNum() / 4.0f);
    wiggle1->update(ofVec2f(x, y));
    wiggle2->update(ofVec2f(x, 0));
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackgroundGradient(ofColor(127), ofColor(0), OF_GRADIENT_LINEAR);
    wiggle1->draw(100, 100);
    wiggle2->draw(500, 100);
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
