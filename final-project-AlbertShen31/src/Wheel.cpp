/*
 *  Wheel.cpp
 *  ofxBox2dExample
 *
 *  Created by Todd Vanderlin on 3/7/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#include "Wheel.h"

//------------------------------------------------
Wheel::Wheel() {
}

//------------------------------------------------
void Wheel::setup(b2World * b2dworld, float x, float y, float radius) {

    if(b2dworld == NULL) {
        ofLog(OF_LOG_NOTICE, "Wheel :: setup : - must have a valid world -");
        return;
    }

    // these are used to create the shape
    b2CircleShape shape;

    shape.m_p.SetZero();
    shape.m_radius        = radius / OFX_BOX2D_SCALE;
    this->radius        = radius;

    fixture.shape        = &shape;
    fixture.density        = density;
    fixture.friction    = friction;
    fixture.restitution    = bounce;

    bodyDef.type    = b2_dynamicBody;

    bodyDef.position.Set(x/OFX_BOX2D_SCALE, y/OFX_BOX2D_SCALE);

    body  = b2dworld->CreateBody(&bodyDef);
    body->CreateFixture(&fixture);

    alive = true;
}

void Wheel::setup(b2World * b2dworld, ofVec2f &pts, float radius) {
    setup(b2dworld, pts.x, pts.y, radius);
}


//------------------------------------------------
float Wheel::getRadius() {
    return radius;
}

//------------------------------------------------
/*
 TODO: Should we even do this....?
 Im not sure about this it seems like a bad idea.
 I cant figure out another way to change the radius of
 a shape that we have

 -- any help here :) --

 here is a solution for changing the radius on the fly without
 destroying the shape - chrispie

 */
void Wheel::setRadius(float r) {
    this->radius = r;

    for (b2Fixture* f= body->GetFixtureList(); f; f = f->GetNext())
    {
        f->GetShape()->m_radius=r/OFX_BOX2D_SCALE;
    }
}

//------------------------------------------------
void Wheel::draw() {

    if(!isBody()) return;

    ofPushMatrix();
    ofTranslate(getPosition().x, getPosition().y, 0);
    ofRotateDeg(getRotation(), 0, 0, 1);
    ofDrawCircle(0, 0, radius);

    ofPushStyle();
    ofEnableAlphaBlending();
    ofSetColor(0);
    ofDrawLine(0, 0, radius, 0);
    if(isSleeping()) {
        ofSetColor(255, 100);
        ofDrawCircle(0, 0, radius);
    }
    ofPopStyle();

    ofPopMatrix();

}

void Wheel::rotate(float amt) {
    body->ApplyTorque(amt, true);
}
