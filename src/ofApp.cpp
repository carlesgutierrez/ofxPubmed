#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    myGuiPubMed.setup();
}


//--------------------------------------------------------------
void ofApp::update(){
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	myPubMed.draw();
}

//--------------------------------------------------------------
void ofApp::exit() {
	myGuiPubMed.exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    myPubMed.keyPressed(key);
	myGuiPubMed.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
