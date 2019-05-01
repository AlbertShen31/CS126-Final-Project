#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "Wheel.h"
#include "CarBody.h"
#include "Car.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
    
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
    
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    float speed;
    bool moveRight = false;
    bool moveLeft = false;
		
    ofxBox2d box2d;   // the box2d world
    CarBody carBody;
    Car car;
    b2WheelJoint* wheelJoint;
    b2WheelJoint* wheelJoint2;
    b2RevoluteJoint* revJoint1;
    b2RevoluteJoint* revJoint2;
    
    
    
    vector <shared_ptr <Car> > cars;
    vector <shared_ptr <Wheel> > wheels;
    vector <shared_ptr <ofxBox2dRect> > boxes;
    vector <shared_ptr <ofxBox2dEdge> > edges;
    vector <ofPolyline> lines;
    vector <shared_ptr <ofxBox2dJoint> > joints;
};