#include "ofApp.h"
#define PTM_RATIO 32.0

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofBackgroundHex(0xfdefc2);
    ofSetLogLevel(OF_LOG_NOTICE);
    ofDisableAntiAliasing();
    ofEnableSmoothing();
    
    
    box2d.init();
    box2d.setGravity(0, 9.81);
    box2d.setFPS(60.0);
    ofSetHexColor(0xf6c738);
    box2d.createGround();
    
//    car.setup(box2d.getWorld(), 250, 700, 10);

    
    auto wheel1 = std::make_shared<Wheel>();
    wheel1.get()->setPhysics(3.0, 0.53, 0.9);
    wheel1.get()->setup(box2d.getWorld(), 50, 700, 10);
    wheels.push_back(wheel1);

    auto wheel2 = std::make_shared<Wheel>();
    wheel2.get()->setPhysics(3.0, 0.53, 0.9);
    wheel2.get()->setup(box2d.getWorld(), 100, 700, 10);
    wheels.push_back(wheel2);

    auto joint = std::make_shared<ofxBox2dJoint>();

    joint.get()->setup(box2d.getWorld(), wheels[0].get()->body, wheels[1].get()->body);
    joint.get()->setLength(25);
    joints.push_back(joint);

    carBody.setPhysics(3.0, 0.53, 0.9);
    carBody.setup(box2d.getWorld(), 75, 680, 70, 20);

    b2RevoluteJointDef jointDef;
    jointDef.Initialize(carBody.body, wheels[0].get()->body, wheels[0]->body->GetWorldCenter());
    revJoint1 = (b2RevoluteJoint*)box2d.getWorld()->CreateJoint( &jointDef );
    revJoint1->EnableMotor(true);
    revJoint1->SetMaxMotorTorque(10000);

    b2RevoluteJointDef jointDef2;
    jointDef2.Initialize(carBody.body, wheels[1].get()->body, wheels[1]->body->GetWorldCenter());
    revJoint2 = (b2RevoluteJoint*)box2d.getWorld()->CreateJoint( &jointDef2 );
    revJoint2->EnableMotor(true);
    revJoint2->SetMaxMotorTorque(10000);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if (moveRight && speed <= 50) {
        speed+= .5;
    } else if (moveLeft && speed >= -50) {
        speed-= .5;
    } else  {
        speed *= 0.9;
    }
    
    revJoint1->SetMotorSpeed(speed);
    revJoint2->SetMotorSpeed(speed);
    b2Vec2 temp(carBody.body->GetWorldCenter().x - 10, carBody.body->GetWorldCenter().y - 20);
    b2Vec2 &origin = temp;
    box2d.getWorld()->ShiftOrigin(origin);
//    car.setMotorSpeed(speed);
    box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofTranslate(carBody.body->GetWorldCenter().x-b2World, carBody.body->GetWorldCenter().y, 0);
    
    
    ofFill();
    ofSetHexColor(0xf6c738);
    for(int i=0; i<wheels.size(); i++) {
        wheels[i].get()->draw();
    }

    ofSetHexColor(0x444342);
    ofNoFill();
    for (int i=0; i<lines.size(); i++) {
        lines[i].draw();
    }
    for (int i=0; i<edges.size(); i++) {
        edges[i].get()->draw();
    }

    for (int i=0; i<cars.size(); i++) {
        cars[i].get()->draw();
    }

    carBody.draw();
//    car.draw();
    
    // draw the ground
    ofFill();
    ofSetHexColor(0xa6c7f8);
    
    box2d.drawGround();
    
    string info = "";
//    info += "Press [w] for wheels\n";
    info += "Total Bodies: "+ofToString(box2d.getBodyCount())+"\n";
    info += "Total Joints: "+ofToString(box2d.getJointCount())+"\n\n";
    info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
    ofSetHexColor(0x444342);
    ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 't') {
      ofToggleFullscreen();
    }
    
    if(key == 'w') {
        auto car1 =std::make_shared<Car>();
        car1.get()->setup(box2d.getWorld(), mouseX, mouseY, 10);
        cars.push_back(car1);
    }
    
    if(key == 'a') {
        moveRight = false;
        moveLeft = true;
        for (int i = 0; i < 2; ++i) {
//            wheels[i]->rotate(-10);
        }
    } else if(key == 'd') {
        moveRight = true;
        moveLeft = false;
        for (int i = 0; i < 2; ++i) {
//            wheels[i]->rotate(10);
        }
    } else {
        moveRight = false;
        moveLeft = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    moveRight = false;
    moveLeft = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    //lines.back().addVertex(x, y);
    auto edge = std::make_shared<ofxBox2dEdge>();
    lines.back().addVertex(x, y);
    lines.back().simplify();
    
    for (auto i=0; i<lines.back().size(); i++) {
        edge.get()->addVertex(lines.back()[i]);
    }
    
    edge.get()->create(box2d.getWorld());
    edges.push_back(edge);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    lines.push_back(ofPolyline());
    lines.back().addVertex(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    auto edge = std::make_shared<ofxBox2dEdge>();
    lines.back().addVertex(x, y);
    lines.back().simplify();
    
    for (auto i=0; i<lines.back().size(); i++) {
        edge.get()->addVertex(lines.back()[i]);
    }
    
    edge.get()->create(box2d.getWorld());
    edges.push_back(edge);
    
    //lines.clear();
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ofFill();
    ofSetHexColor(0xf6c738);
    box2d.createGround();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

