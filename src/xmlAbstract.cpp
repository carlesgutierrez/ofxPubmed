//
//  xmlAbstract.cpp
//  httpRequestPubMed
//
//  Created by carles on 03/03/14.
//
//

#include "xmlAbstract.h"

//--------------------------------------------------------------
xmlAbstract::xmlAbstract(){
	counterSavedXmls = 0;
}
//--------------------------------------------------------------
xmlAbstract::~xmlAbstract(){
	
}

//--------------------------------------------------------------
void xmlAbstract::setup(){
	counterSavedXmls = 0;
}

//--------------------------------------------------------------
void xmlAbstract::registerURL(){
	ofRegisterURLNotification(this);
}

//--------------------------------------------------------------
void xmlAbstract::unRegisterURL(){
	ofUnregisterURLNotification(this);
}

//--------------------------------------------------------------
void xmlAbstract::update(){}

//--------------------------------------------------------------
void xmlAbstract::draw(){
	
	//Get number of Ids
	
	//Move fordware reward from ids results
	
	//settings.pushTag("positions");
	
	//int numberOfSavedPoints = settings.getNumTags("position");
	
	//Get string text in FTGL
	
	//Draw Texts in text canvas of size of Main window.
	
}

//-------------------------------------------------------
void xmlAbstract::saveXml(){
	//string filename = "file"+ofToString(counterSavedXmls,0)+".xml";
    string filename = "file.xml";
	myxml.saveFile(filename);
	counterSavedXmls++;
}

//--------------------------------------------------------------
int xmlAbstract::loadAbstracts(string request){
	
	myxml.clear();
	
	ofRegisterURLNotification(this);
	
	ofLogVerbose("xmlAbstract") << "request for loadAbstracts= " << request << endl;
	ofLoadURLAsync(request, "async_req");
	int id = myxml.loadFromBuffer(request);
	return(id);
}

//--------------------------------------------------------------
void xmlAbstract::urlResponse(ofHttpResponse & response) {
    if (response.status==200 && response.request.name == "async_req") {
        myxml.loadFromBuffer(response.data.getBinaryBuffer());
        bLoading = false;
		saveXml();//save results with an active counter file0, file1, file2...

    } else {
		ofLogVerbose("xmlAbstract") << "load my xmlAbstracts" << endl;
		ofLogVerbose("xmlAbstract") << response.status << " " << response.error << endl;
		if (response.status != -1) bLoading = false;
    }
	
	ofUnregisterURLNotification(this);
}