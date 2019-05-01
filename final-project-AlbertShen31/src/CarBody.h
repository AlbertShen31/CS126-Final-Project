

#pragma once
#include "ofMain.h"
#include "ofxBox2dBaseShape.h"

// It would be nice to use ofRectangle but it is top/left and
// box2d needs a center rectangle.

class CarBody : public ofxBox2dBaseShape {

private:
    float width, height;
    
public:
	ofVboMesh mesh;
	//------------------------------------------------
	CarBody();	
	
	//------------------------------------------------
	void setup(b2World * b2dworld, ofRectangle rec);
	void setup(b2World * b2dworld, float x, float y, float w, float h);
	   
	//------------------------------------------------
    float getWidth()  { return width * 2;  }
    float getHeight() { return height * 2; }
    
    void updateMesh();
    void draw();

};














