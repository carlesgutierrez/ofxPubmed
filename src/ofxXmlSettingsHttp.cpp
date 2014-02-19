//
//  ofxXmlSettingsHttp.cpp
//  httpRequestPubMed
//
//  Created by Carles on 17/02/14.
//
//

#include "ofxXmlSettingsHttp.h"

//----------------------------------------
ofxXmlSettingsHttp::ofxXmlSettingsHttp(){
    
}

//---------------------------------------------------------
ofxXmlSettingsHttp::~ofxXmlSettingsHttp(){
    
}

//-------------------------------------------------------
void ofxXmlSettingsHttp::loadfromHttp(string url){
    loadXml(myxml, url);
    
}

//-------------------------------------------------------
void ofxXmlSettingsHttp::clear(){
    myxml.clear();
}

//-------------------------------------------------------
ofxXmlSettings* ofxXmlSettingsHttp::getXml(){
    return &myxml;
}

//-------------------------------------------------------
void ofxXmlSettingsHttp::saveXml(){
    myxml.saveFile("file.xml");
}

//------------------------------------------------------
bool ofxXmlSettingsHttp::loadXml(ofxXmlSettings & xml, string fileName){

	if(fileName.substr(0, 5) == "<?xml") {
		//return xml.loadFile(ofLoadURL(fileName).data);
        return xml.loadFromBuffer(fileName/*ofLoadURL(fileName).data*/);
	}else{
     cout << "Error Loading URL incorrect format" << endl;
        return false;
    }

}