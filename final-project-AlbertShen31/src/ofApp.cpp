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
    
    drawHill();
    
    box2d.createGround();
    
    car.setup(box2d.getWorld(), 250, 500, 10);
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    if (moveRight && speed <= 50) {
        speed += .5;
    } else if (moveLeft && speed >= -50) {
        speed -= .5;
    } else  {
        speed *= 0.99;
    }
    car.setMotorSpeed(speed);
    
//    b2Vec2 temp((car.frontWheel.body->GetWorldCenter().x - 10)/OFX_BOX2D_SCALE, (car.frontWheel.body->GetWorldCenter().y-10)/OFX_BOX2D_SCALE);
//    b2Vec2 &origin = temp;
//    box2d.getWorld()->ShiftOrigin(origin);
//
    
//    ofTranslate(car.frontWheel.body->GetWorldCenter().x, car.frontWheel.body->GetWorldCenter().y, 0);
    
    
//
//    ofPushMatrix();
//    draw();
    box2d.update();
//    ofPopMatrix();
    box2d.createGround(0, 720, 10000, 720);
    
    box2d.getWorld()->Step(1/50.0, 8, 3);
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofTranslate(-car.frontWheel.body->GetWorldCenter().x/OFX_BOX2D_SCALE, car.frontWheel.body->GetWorldCenter().y/OFX_BOX2D_SCALE, 0);
//    b2Vec2 temp((car.frontWheel.body->GetWorldCenter().x - 10)/OFX_BOX2D_SCALE, (car.frontWheel.body->GetWorldCenter().y-10)/OFX_BOX2D_SCALE);
//    b2Vec2 &origin = temp;
//    box2d.getWorld()->ShiftOrigin(origin);


//    ofSetHexColor(0x444342);
//    ofNoFill();
//    for (int i=0; i<lines.size(); i++) {
//        lines[i].draw();
//    }
    
    ofSetHexColor(0x444342);
    ofNoFill();
    for (int i=0; i<edges.size(); i++) {
        edges[i].get()->draw();
    }

    edge.draw();
    car.draw();
    box2d.createGround(0, 720, 10000, 720);
    
    string info = "";
    info += "Press r to reset terrain\n";
    info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
    ofSetHexColor(0x444342);
    ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 't') {
      ofToggleFullscreen();
    } else if(key == 'r') {
        drawHill();
    } else if(key == 'a') {
        moveRight = false;
        moveLeft = true;
    } else if(key == 'd') {
        moveRight = true;
        moveLeft = false;
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
//    auto edge = std::make_shared<ofxBox2dEdge>();
//    lines.back().addVertex(x, y);
//    lines.back().simplify();
//
//    for (auto i=0; i<lines.back().size(); i++) {
//        edge.get()->addVertex(lines.back()[i]);
//    }
//
//    edge.get()->create(box2d.getWorld());
//    edges.push_back(edge);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    lines.push_back(ofPolyline());
    lines.back().addVertex(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
//    auto edge = std::make_shared<ofxBox2dEdge>();
//    lines.back().addVertex(x, y);
//    lines.back().simplify();
//
//    for (auto i=0; i<lines.back().size(); i++) {
//        edge.get()->addVertex(lines.back()[i]);
//    }
//
//    edge.get()->create(box2d.getWorld());
//    edges.push_back(edge);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    box2d.createGround();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::drawHill() {
    int randomHeight = rand() % 100;
    edge.clear();
    int startY = rand() % 100 + 450;
    int endY = rand() % 100 + 450;
    int bezierY = rand() % 200 + 100;
    edge.addVertex(0, startY);
    edge.bezierTo(300 + rand() % 100, startY + bezierY, 700 + rand() % 100, endY - bezierY, 1024, endY);
    edge.create(box2d.getWorld());
}
