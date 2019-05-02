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
    carBody.setPhysics(5.0, 0.13, 0.9);
    carBody.setup(b2dworld, x + (radius * 5 / 2), y - 2 * radius, 7 * radius, 2 * radius);
    
    frontWheel.setPhysics(3.0, 0.13, 0.9);
    frontWheel.setup(b2dworld, x + 5 * radius, y, radius);
    
    backWheel.setPhysics(3.0, 0.13, 0.9);
    backWheel.setup(b2dworld, x, y, radius);
    
    b2DistanceJointDef distJointDef;
    distJointDef.Initialize(frontWheel.body, backWheel.body, frontWheel.body->GetWorldCenter(), backWheel.body->GetWorldCenter());
    joint = (b2DistanceJoint*)b2dworld->CreateJoint( &distJointDef );

    
//    b2WheelJointDef jointDef1;
//    jointDef1.Initialize(carBody.body, frontWheel.body, carBody.body->GetWorldCenter(), frontWheel.body->GetWorldCenter());
//    frontJoint = (b2WheelJoint*)b2dworld->CreateJoint( &jointDef1 );
//    frontJoint->EnableMotor(true);
//    frontJoint->SetMaxMotorTorque(1000);
//
//    b2WheelJointDef jointDef2;
//    jointDef2.Initialize(carBody.body, backWheel.body, carBody.body->GetWorldCenter(), backWheel.body->GetWorldCenter());
//    backJoint = (b2WheelJoint*)b2dworld->CreateJoint( &jointDef2 );
//    backJoint->EnableMotor(true);
//    backJoint->SetMaxMotorTorque(1000);
    
    b2RevoluteJointDef jointDef1;
    jointDef1.Initialize(carBody.body, frontWheel.body, frontWheel.body->GetWorldCenter());
    frontJoint = (b2RevoluteJoint*)b2dworld->CreateJoint( &jointDef1 );
    frontJoint->EnableMotor(true);
    frontJoint->SetMaxMotorTorque(10000);
    
    b2RevoluteJointDef jointDef2;
    jointDef2.Initialize(carBody.body, backWheel.body, backWheel.body->GetWorldCenter());
    backJoint = (b2RevoluteJoint*)b2dworld->CreateJoint( &jointDef2 );
    backJoint->EnableMotor(true);
    backJoint->SetMaxMotorTorque(10000);
}

void Car::setMotorSpeed(float amt) {
    frontJoint->SetMotorSpeed(amt);
    backJoint->SetMotorSpeed(amt);
}

void Car::draw() {
    frontWheel.draw();
    backWheel.draw();
    carBody.draw();
}
