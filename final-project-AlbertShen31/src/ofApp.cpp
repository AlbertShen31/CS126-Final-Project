#include "ofApp.h"
#define PTM_RATIO 32.0
int windowWidth = 1024;
int windowHeight = 768;


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
    car.setup(box2d.getWorld(), 100, spawnHeight, 10);
    box2d.createGround();
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
    
    box2d.update();
    box2d.createGround();
    
    if (car.frontWheel.getPosition().x > windowWidth) {
        drawHill();
        resetCar(car.frontWheel.getPosition().y, car.carBody.getRotation());
    }
    
    box2d.getWorld()->Step(1/50.0, 8, 3);
}

//--------------------------------------------------------------
void ofApp::draw(){
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
        resetCar(spawnHeight, 0);
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
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    windowWidth = w;
    windowHeight = h;
    box2d.createGround();
    drawHill();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::drawHill() {
    edge.clear();
    int startY = rand() % 100 + 450;
    int endY = rand() % 100 + 450;
    int bezierY = rand() % 200 + 100;
    spawnHeight = startY - 50;
    
    edge.addVertex(0, startY);
    edge.bezierTo(300 + rand() % 100, startY + bezierY, 700 + rand() % 100, endY - bezierY, windowWidth, endY);
    edge.create(box2d.getWorld());
}

void ofApp::resetCar(int height, float rotation) {
    car.destroy();
    car.setup(box2d.getWorld(), 0, height, 10);
    car.carBody.setRotation(rotation);
}
