//
//  ofxWiggleStereoscopy.hpp
//  example-wiggle
//
//  Created by jotaro on 2017/08/15.
//
//

#ifndef ofxWiggleStereoscopy_h
#define ofxWiggleStereoscopy_h
#pragma once

#include "ofMain.h"

class ofxWiggleStereoscopy
{
  public:
    void setup();
    void update();
    void update(const ofVec2f &_wiggle);
    void draw(int x, int y, int w, int h);
    void draw(int x, int y);
    void setImage(string _image);
    void setImage(ofImage _image);
    void setDepthImage(string _dimage);
    void setDepthImage(ofImage _dimage);
    void setImages(string _image, string _dimage);
    void setImages(ofImage _image, ofImage _dimage);

    ofImage image;
    ofImage depth;

    float focus = 0.5f;
    //constructor
    ofxWiggleStereoscopy();
    ofxWiggleStereoscopy(string image, string depth);

  private:
    ofShader shader;
    ofVec2f wiggle;
};

#endif /* ofxWiggleStereoscopy_hpp */
