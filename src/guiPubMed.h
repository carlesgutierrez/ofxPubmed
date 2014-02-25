#pragma once

#include "ofMain.h"
#include "ofxUI.h"
//#include "guiEvent.h"
#include "ofxPubMed.h"


#define MAXITEMS 34
#define MAXITEMSDATAS 6
#define MAXadd 4

class guiPubMed {

public:

	guiPubMed();
	~guiPubMed();

	void setup();
	void update();
	void draw();
	void exit();
	void keyPressed(int key);
	
	
private:
    
    bool letsAddNewSearchField;
	
	//USED IN APP
    string myVisibleSelItemsArray [MAXITEMS] = {"Alliation","All Fields", "Author", "Author-Corporate", "Author-First", "Author - Full", "Author - Identifier", "Author - Last", "Book", "EC/RN Number", "Editor", "Filter", "Grant Number", "ISBN", "Investigator", "Investigator - Full", "Issue", "Journal", "Language", "Location ID", "MeSH Major Topic", "MeSH Subheading", "Other Term", "Pagination", "Pharmacological Action", "Publication Type", "Publisher", "Secondary Source ID", "Supplementary Concept", "Text Word", "Title", "Title/Abstract", "Transliterated Title", "Volume"};
    vector<string> myVisibleSelItems;
    
    string myVisibleDatasSelItemsArray [MAXITEMSDATAS] = {"Date - Completion", "Date - Create", "Date - Entrez","Date - MeSH", "Date - Modification", "Date - Publication"};
    vector<string> myVisibleDatasSelItems;

	string andOrNotArray [MAXadd] = {"And", "Or", "Not", "-"};
    vector<string> andOrNot;
	
    //GUIS
    void setupPubMedGUI();
    void addSearchField();
	void setupPubMedGuiDatas();
	void removeSearchField();
    void guiEvent(ofxUIEventArgs &e);
    ofxUICanvas *gui;

	int searchFields;
	int searchFieldsH;
	
	// tabCanvas
	float tabCanvasX;
	float tabCanvasY;
	float tabCanvasW;
	float tabCanvasH;
	float toggleW;
	float toggleH;
    int newbuttonW;
    int newbuttonH;
	
	// postCanvas
	float postCanvasX;
	float postCanvasY;
	float postCanvasW;
	float postCanvasH;
	float postFieldH;
		
	// searchCanvas
	float searchCanvasX;
	float searchCanvasY;
	float searchCanvasW;
	float searchCanvasH;
	
	// postCanvas
	float dropDownX;
	float dropDownY;
	float dropDownW;
	float dropDownH;
	
	// search field
	float textInputY;
	float searchFieldX;
	float searchFieldY;
	float searchFieldW;
	float searchFieldH;
	
	float addButtonX;
	float addButtonY;
	float addButtonW;
	float addButtonH;
	
	
	bool bsnap;
	float space;
	float dim;
	float WidgetW;
	float sliderW;
		
};

