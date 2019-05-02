//
//  Car.hpp
//  CS126FinalProject
//
//  Created by Albert Shen on 4/27/19.
//

#pragma once
#include "ofMain.h"
#include "ofxBox2dBaseShape.h"
#include "Wheel.h"
#include "CarBody.h"

class Car : public ofxBox2dBaseShape {
    
private:
    
    
public:
    Wheel frontWheel;
    Wheel backWheel;
    b2DistanceJoint* joint;
//    b2WheelJoint* frontJoint;
//    b2WheelJoint* backJoint;
    b2RevoluteJoint* frontJoint;
    b2RevoluteJoint* backJoint;
    CarBody carBody;
    float motorSpeed;
    
    void setup(b2World * b2dworld, float x, float y, float radius);
    
    Car();
    
    void setMotorSpeed(float amt);
    
    void draw();
};
