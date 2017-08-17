//
//  ofxWiggleStereoscopy.cpp
//  myWiggleStereoscopyTest
//
//  Created by jotaro on 2017/08/15.
//
//
#include "ofxWiggleStereoscopy.h"
//--------------------------------------------------------------
//--------------------------------------------------------------
ofxWiggleStereoscopy::ofxWiggleStereoscopy(string _image, string _depth)
{

    // load image on ofImage object
    image.load(_image);
    depth.load(_depth);

// shows hardware pipeline of machine (for mac GL2)
#ifdef TARGET_OPENGLES
    cout << "ES2" << endl;
#else
    if (ofIsGLProgrammableRenderer())
    {
        cout << "GL3" << endl;
    }
    else
    {
        cout << "GL2" << endl;
    }
#endif

    // load shader script
    shader.load("", "shader/wiggle/wiggle.frag");
}

//--------------------------------------------------------------
ofxWiggleStereoscopy::ofxWiggleStereoscopy()
{
}

//--------------------------------------------------------------
void ofxWiggleStereoscopy::update()
{
    // update wiggle value (based on sine curve)
    wiggle_val = wiggleAmnt * sin(ofGetFrameNum() / 4.0f);
}

//--------------------------------------------------------------
void ofxWiggleStereoscopy::update(const ofVec2f &_wiggle)
{
    // update wiggle value (based on sine curve)
    wiggle = _wiggle;
}

//--------------------------------------------------------------
void ofxWiggleStereoscopy::draw(int x, int y, int w, int h)
{

    ofSetColor(255);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.begin();
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    shader.setUniform2f("dimentions", w, h);
    shader.setUniform2f("mapDimentions", w, h);
    shader.setUniformTexture("src", image.getTexture(), 1);
    shader.setUniformTexture("displacementMap", depth.getTexture(), 2); // depthmap
    shader.setUniform1f("focus", 0.5);                                  // fixtation point [0,1]
    shader.setUniform1f("scale", 1.0f);
    shader.setUniform2f("offset", wiggle);
    shader.setUniform1f("alpha", 1.0);
    image.draw(x, y, w, h);
    shader.end();
}

//--------------------------------------------------------------
void ofxWiggleStereoscopy::draw(int x, int y)
{
    int w = image.getWidth();
    int h = image.getHeight();
    ofSetColor(255);
    // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader.begin();
    shader.setUniform1f("u_time", ofGetElapsedTimef());
    shader.setUniform2f("u_resolution", ofGetWidth(), ofGetHeight());
    shader.setUniform2f("dimentions", w, h);
    shader.setUniform2f("mapDimentions", w, h);
    shader.setUniformTexture("src", image.getTexture(), 1);
    shader.setUniformTexture("displacementMap", depth.getTexture(), 2); // depthmap
    shader.setUniform1f("focus", 0.5);                                  // fixtation point [0,1]
    shader.setUniform1f("scale", 1.0f);
    shader.setUniform2f("offset", wiggle);
    shader.setUniform1f("alpha", 1.0);
    image.draw(x, y, w, h);
    shader.end();
}

//--------------------------------------------------------------
void ofxWiggleStereoscopy::setImage(string _image)
{
    image.load(_image);
}

//--------------------------------------------------------------
void ofxWiggleStereoscopy::setImage(ofImage _image)
{
    image = _image;
}

//--------------------------------------------------------------
void ofxWiggleStereoscopy::setDepthImage(string _dimage)
{
    depth.load(_dimage);
}

//--------------------------------------------------------------
void ofxWiggleStereoscopy::setDepthImage(ofImage _dimage)
{
    depth = _dimage;
}