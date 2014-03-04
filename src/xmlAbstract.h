//
//  xmlAbstract.h
//  httpRequestPubMed
//
//  Created by carles on 03/03/14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"

class xmlAbstract {
	
public:
	
	xmlAbstract();
	~xmlAbstract();
	
	void setup();
	void update();
	void draw();
	
	void registerURL();
	void unRegisterURL();

	void saveXml();
	//ofxXmlSettings* getXml();
	
	int loadAbstracts(string request);
	
	ofHttpResponse httpResponse;
	void urlResponse(ofHttpResponse & response);
	
private:

	int counterSavedXmls;
	bool bLoading;
	ofxXmlSettings myxml;
};