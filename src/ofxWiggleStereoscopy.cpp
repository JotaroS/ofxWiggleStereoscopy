//
//  ofxWiggleStereoscopy.cpp
//
//  Created by jotaro on 2017/08/15.
//
//
#include "ofxWiggleStereoscopy.h"

#define STRINGIFY(A) #A

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

    string shaderProgram = STRINGIFY(
        uniform vec2 u_resolution;
        uniform float u_time;

        uniform sampler2DRect src;
        uniform sampler2DRect displacementMap;

        uniform vec2 offset;
        uniform vec2 mapDimensions;
        uniform vec4 dimensions;

        uniform float focus;
        uniform float scale;
        uniform float alpha;
        void main() {
            vec2 pos = gl_TexCoord[0].st;

            float r = texture2DRect(src, pos).r;
            float g = texture2DRect(src, pos).g;
            float b = texture2DRect(src, pos).b;
            float a = texture2DRect(src, pos).a;

            float gr = (r + g + b) / 3.0; //set intencity

            vec4 color = vec4(r, g, b, a); //set src color
            float aspect = u_resolution.x / u_resolution.y;
            vec2 scale2 = vec2(scale * min(1.0, 1.0 / aspect), scale * min(1.0, aspect)) * vec2(1, -1) * vec2(1);
            vec2 mapCords = gl_TexCoord[0].st;
            float map = texture2DRect(displacementMap, mapCords).r;
            map = map * -1.0 + focus;
            vec2 disCords = gl_TexCoord[0].st;
            disCords += offset * map * scale2;           //deform coordinate based on offset and scale
            gl_FragColor = texture2DRect(src, disCords); //maybe this should be deleted??

            // wiggle light color
            float _r = texture2DRect(src, disCords).r;
            float _g = texture2DRect(src, disCords).g;
            float _b = texture2DRect(src, disCords).b;
            float _a = texture2DRect(src, disCords).a;

            vec4 dstcolor = vec4(_r, _g, _b, alpha); // set alpha level

            gl_FragColor = dstcolor;
        }

        );

    // load shader script
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader.linkProgram();
}

//--------------------------------------------------------------
ofxWiggleStereoscopy::ofxWiggleStereoscopy()
{
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
    shader.setUniform1f("focus", focus);                                  // fixtation point [0,1]
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
    shader.setUniform1f("focus", focus);                                  // fixtation point [0,1]
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