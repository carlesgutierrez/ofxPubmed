#pragma once

#include "ofMain.h"
#include "ofxUI.h"
//#include "guiEvent.h"
#include "ofxPubMed.h"


#define MAXITEMS 35
#define MAXITEMSDATAS 6

class guiPubMed {

public:

	guiPubMed();
	~guiPubMed();

	void setup();
	void update();
	void draw();
	void exit();
	
private:
	
	//USED IN APP
    string myVisibleSelItemsArray[MAXITEMS] = {"[Alliation]","[All Fields]", "[Author]", "[Author-Corporate]", "[Author-First]", "[Author - Full]", "[Author - Identifier]", "[Author - Last]", "[Book]", "[EC/RN Number]", "[Editor]", "[Filter]", "[Grant Number]", "[ISBN]", "[Investigator]", "[Investigator - Full]", "[Issue]", "[Journal]", "[Language]", "[Location ID]", "[MeSH Major Topic]", "[MeSH Subheading]", "[MeSH Subheading]", "[Other Term]", "[Pagination]", "[Pharmacological Action]", "[Publication Type]", "[Publisher]", "[Secondary Source ID]", "[Supplementary Concept]", "[Text Word]", "[Title]", "[Title/Abstract]", "[Transliterated Title]", "[Volume]"};
    vector<string> myVisibleSelItems;
    
    string myVisibleDatasSelItemsArray[MAXITEMSDATAS] = {"[Date - Completion]", "[Date - Create]", "[Date - Entrez]","[Date - MeSH]", "[Date - Modification]", "[Date - Publication]"};
    vector<string> myVisibleDatasSelItems;

    //GUIS
    void setupPubMedGUI();
    void setupPubMedGuiDatas();
    void guiEvent(ofxUIEventArgs &e);
    ofxUICanvas *pmGuiItems1;
    ofxUICanvas *pmGuiItems2;

	
	// tabCanvas
	float tabCanvasX;
	float tabCanvasY;
	float tabCanvasW;
	float tabCanvasH;
	float toggleW;
	float toggleH;
	
	// postCanvas
	float postCanvasX;
	float postCanvasY;
	float postCanvasW;
	float postCanvasH;
	float postFieldH;
	
	// tweetsCanvas
	float tweetsCanvasX;
	float tweetsCanvasY;
	float tweetsCanvasW;
	float tweetsCanvasH;
	
	// searchCanvas
	float searchCanvasX;
	float searchCanvasY;
	float searchCanvasW;
	float searchCanvasH;
	
	// search field
	float textInputY;
	float searchFieldX;
	float searchFieldY;
	float searchFieldW;
	float searchFieldH;
	
	bool bsnap;
	float space;
	float dim;
	float WidgetW;
	float sliderW;
		
};

