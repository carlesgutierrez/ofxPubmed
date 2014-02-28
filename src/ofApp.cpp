#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofLog(OF_LOG_VERBOSE, "GuiVerbose");
	ofSetLogLevel("GuiVerbose", OF_LOG_VERBOSE); //check COUTS from Collisions
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
		ofSetLogLevel(OF_LOG_SILENT); //Play ChinoP clean of COUTS!
	}
	else if(key == OF_KEY_F2){
		ofSetLogLevel(OF_LOG_VERBOSE); //Set active all Verbose commets (OF verboses included)
	}
	else if(key == OF_KEY_F3){
		ofLog(OF_LOG_VERBOSE, "GuiVerbose");
		ofSetLogLevel("GuiVerbose", OF_LOG_VERBOSE); //check COUTS from Collisions
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
