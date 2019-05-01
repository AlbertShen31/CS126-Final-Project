//
//  Car.cpp
//  CS126FinalProject
//
//  Created by Albert Shen on 4/27/19.
//

#include "Car.h"

Car::Car() {
    
}

void Car::setup(b2World * b2dworld, float x, float y, float radius) {
    body.setPhysics(10.0, 0.53, 0.9);
    body.setup(b2dworld, x + (radius * 5 / 2), y - 2 * radius, 7 * radius, 2 * radius);
    
    frontWheel.setPhysics(3.0, 0.53, 0.9);
    frontWheel.setup(b2dworld, x + 5 * radius, y, radius);
    
    backWheel.setup(b2dworld, x, y, radius);
    backWheel.setPhysics(3.0, 0.53, 0.9);
    
    b2DistanceJointDef distJointDef;
    distJointDef.Initialize(frontWheel.body, backWheel.body, frontWheel.body->GetWorldCenter(), backWheel.body->GetWorldCenter());
    joint = (b2DistanceJoint*)b2dworld->CreateJoint( &distJointDef );

    
    b2RevoluteJointDef jointDef;
    jointDef.Initialize(body.body, frontWheel.body, frontWheel.body->GetWorldCenter());
    frontJoint = (b2RevoluteJoint*)b2dworld->CreateJoint( &jointDef );
    frontJoint->EnableMotor(true);
    frontJoint->SetMaxMotorTorque(100);
    
    jointDef.Initialize(body.body, backWheel.body, backWheel.body->GetWorldCenter());
    backJoint = (b2RevoluteJoint*)b2dworld->CreateJoint( &jointDef );
    backJoint->EnableMotor(true);
    backJoint->SetMaxMotorTorque(100);
}

void Car::setMotorSpeed(float amt) {
    frontJoint->SetMotorSpeed(amt);
    backJoint->SetMotorSpeed(amt);
}

void Car::draw() {
    frontWheel.draw();
    backWheel.draw();
    body.draw();
}
