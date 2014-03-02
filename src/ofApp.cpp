#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofLog(OF_LOG_VERBOSE, "guiPubMed");
	ofSetLogLevel("guiPubMed", OF_LOG_VERBOSE); //check COUTS from Collisions
}


//--------------------------------------------------------------
void ofApp::update(){
	myPubMed.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	myPubMed.draw();
}

//--------------------------------------------------------------
void ofApp::exit() {

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    myPubMed.keyPressed(key);
	
	if(key == OF_KEY_F1){
		ofSetLogLevel(OF_LOG_SILENT);
	}
	else if(key == OF_KEY_F2){
		ofSetLogLevel(OF_LOG_VERBOSE);
	}
	else if(key == OF_KEY_F3){
		ofLog(OF_LOG_VERBOSE, "guiPubMed");
		ofSetLogLevel("guiPubMed", OF_LOG_VERBOSE);
	}
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
