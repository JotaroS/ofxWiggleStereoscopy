#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    wiggle = new ofxWiggleStereoscopy("Flowers.jpg", "Flowers-depthmap.jpg");
}

//--------------------------------------------------------------
void ofApp::update()
{
    float x = 10 * cos(ofGetFrameNum() / 4.0f);
    float y = 10 * sin(ofGetFrameNum() / 4.0f);
    wiggle->update(ofVec2f(x, y));
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofBackgroundGradient(ofColor(127), ofColor(0), OF_GRADIENT_LINEAR);
    wiggle->draw(100, 100);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
