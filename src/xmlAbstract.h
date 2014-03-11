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

#define MAXRET 20

class xmlAbstract {
	
public:
	
	xmlAbstract();
	~xmlAbstract();
	
	void setup();
	void update();
	void draw(int x, int y);
	void registerURL();
	void unRegisterURL();
	
	void keyPressed(int key);
	
	void resetInfo();

	void saveXml();
	//ofxXmlSettings* getXml();
	int getNumAbstractsAvaible(ofxXmlSettings myxml);
	void getInfoAbstracts(ofxXmlSettings myxml);
	
	int loadAbstracts(string request);
	
	ofHttpResponse httpResponse;
	void urlResponse(ofHttpResponse & response);
	
	//geters
	vector<string> getTitle();
	vector<string>  getAbstractTexts();
	vector<string>  getPubIds();
	//vector<string>  getAuthors();
	
	
private:

	int numIds;
	int counterSavedXmls;
	bool bLoading;
	ofxXmlSettings myxml;
	
	vector<string> vPmids;
	vector<string> vTitles;
	vector<string> vAbstractTexts;

	//vector<string> vPublicationTypes;
	//vector<string> 	vAuthorsLastNanme;
};