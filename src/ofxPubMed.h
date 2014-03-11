//
//  ofxPubMed.h
//  httpRequestPubMed
//
//  Created by Carles on 19/02/14.
//
//

#pragma once

#include <iostream>
#include "ofMain.h"
#include "ofxJSONElement.h"
#include "guiPubMedEvent.h"
#include "guiPubMed.h"
#include "xmlAbstract.h"


//#define MAXITEMS 35
//#define MAXITEMSDATAS 6
#define TEXTLINEHEIGHT 24

class ofxPubMed {
    
public:
    
    ofxPubMed();
    ~ofxPubMed();
    
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    
    void applyRequest();
	void applyRequestAbstrack(ofxJSONElement jsondata);
    
    
    //Search ID Functions
    void changeBasicSearchRequest(string basicSearch);
	void resetBase();
	void reseteSearch();
	
    void starteSearchRequestWithItem(string item, string addtype);
	void addTagRequest(string query);
	void addANDSimpleTagRequest(string newitem, string addtype);
    void addORSimpleTagRequest(string newitem, string addtype);
    void addConsecutiveTagRequest(string newitem, string addtype);
    void addDataTagRequest(string fromdata, string todata, string type);
    void addDataTypeRequest(string datatype);
    void addRelDateRequest(string reldate, string days);
    void addMinMaxDataSearchRequest(string datemin, string typedatemin, string datemax, string typedatemax);

    string setformatForSearch(string text);
	
	//events
	void listenerStartSearchBar(bool & args);
	void listenerAddTextSearchBar(guiPubMedEvent & args);
	
	//gui
	guiPubMed myGuiPubMed;
	
	void activeDrawRaw();
	void deActiveDrawRaw();

private:
	
	bool bDrawRawResults;
	
    //String for requests

    string request;
	
    string sBaseRequest;
    string sDatabase;
    string sBasicSearching;
    string sBasicRequest;
    string sBasicCitation;

    string sRelDate;
    string sDateType;
    string sRetMax;
    string sUseHist;
    
    string sSpaceCit;
    string sSpaceWords;
    string sAnd;
    string sOr;
    string sNot;
    
    string sTerm;
    string sSlash;
    string sQuotes;
    
    string sDocFetch;
    string sId;
    
    string sdataType;
    string sMindate;
    string sMaxdate;
    
    bool bHitRequest;
    bool parsingSuccessful;

	string retMode;
    ofxJSONElement myRequestData;
	
	string retAbstrack;
	ofxJSONElement myAbstrackData;
	vector<string> myPubIDs;
	
	xmlAbstract myAbstracts;
};
