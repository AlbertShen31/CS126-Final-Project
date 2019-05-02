/*
 *  CarBody.cpp
 *  ofxBox2dExample
 *
 *  Created by Todd Vanderlin on 3/7/11.
 *  Copyright 2011 Interactive Design. All rights reserved.
 *
 */

#include "CarBody.h"



//------------------------------------------------

CarBody::CarBody() {
}

//------------------------------------------------
void CarBody::setup(b2World * b2dworld, ofRectangle rec) {
	setup(b2dworld, rec.x, rec.y, rec.width, rec.height);
}

//------------------------------------------------
void CarBody::setup(b2World * b2dworld, float x, float y, float w, float h) {

	if(b2dworld == NULL) {
		ofLog(OF_LOG_NOTICE, "- must have a valid world -");
		return;
	}

    w /= 2;
    h /= 2;
	width = w; height = h;

	b2PolygonShape shape;
	shape.SetAsBox(width/OFX_BOX2D_SCALE, height/OFX_BOX2D_SCALE);

	fixture.shape		= &shape;
	fixture.density		= density;
	fixture.friction	= friction;
	fixture.restitution = bounce;

	b2BodyDef bodyDef;
	bodyDef.type	= b2_dynamicBody;
	bodyDef.position.Set(x/OFX_BOX2D_SCALE, y/OFX_BOX2D_SCALE);


	body = b2dworld->CreateBody(&bodyDef);
	body->CreateFixture(&fixture);

    updateMesh();
    alive = true;
}

// Temporary fix until OF 0.8.0
static void rectangle(ofPath & path, const ofRectangle & r){
    path.moveTo(r.getTopLeft());
    path.lineTo(r.getTopRight());
    path.lineTo(r.getBottomRight());
    path.lineTo(r.getBottomLeft());
    path.close();
}

//------------------------------------------------
void CarBody::updateMesh() {

    float w = getWidth();
    float h = getHeight();
    ofPath path;
    // Temporary fix until OF 0.8.0
    rectangle(path, ofRectangle(-w/2, -h/2, w, h));
    mesh.clear();
    mesh = path.getTessellation();
    mesh.setUsage(GL_STATIC_DRAW);
}



//------------------------------------------------
void CarBody::draw() {

	if(body == NULL) {
		return;
	}

    ofPushMatrix();
    ofTranslate(ofxBox2dBaseShape::getPosition());
    ofRotateDeg(getRotation());
    // Temporary fix until we switch to OF 0.8.0.
    mesh.draw();
    ofPopMatrix();

}
