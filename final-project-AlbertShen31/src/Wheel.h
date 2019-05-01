

#pragma once
#include "ofMain.h"
#include "ofxBox2dCircle.h"

class Wheel : public ofxBox2dCircle {
	
private:
	
	float radius;
	
public:
	
	//------------------------------------------------
	Wheel();
	
    //------------------------------------------------
    void setup(b2World * b2dworld, float x, float y, float radius);
    void setup(b2World * b2dworld, ofVec2f &pts, float radius);

    //------------------------------------------------
    float getRadius();
    void  setRadius(float r);
    
    //------------------------------------------------
    virtual void draw();
    
    
    void rotate(float amt);
};














