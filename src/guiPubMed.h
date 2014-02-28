#pragma once

#include "ofMain.h"
#include "ofxUI.h"

#include "guiPubMedEvent.h"


#define MAXITEMS 34
#define MAXITEMSDATAS 6
#define MAXadd 4
#define MAXSEARCHBARS 10

class guiPubMed {

public:

	guiPubMed();
	~guiPubMed();

	void update();
	void draw();
	void keyPressed(int key);
	
private:
    
    bool letsAddNewSearchField;
	bool bRemoveSearchField;
	
	/////////
	//USED IN APP (Visible)
    string myVisibleSelItemsArray [MAXITEMS] = {"Alliation","All Fields", "Author", "Author-Corporate", "Author-First", "Author - Full", "Author - Identifier", "Author - Last", "Book", "EC/RN Number", "Editor", "Filter", "Grant Number", "ISBN", "Investigator", "Investigator - Full", "Issue", "Journal", "Language", "Location ID", "MeSH Major Topic", "MeSH Subheading", "Other Term", "Pagination", "Pharmacological Action", "Publication Type", "Publisher", "Secondary Source ID", "Supplementary Concept", "Text Word", "Title", "Title/Abstract", "Transliterated Title", "Volume"};
    vector<string> myVisibleSelItems;
    string myVisibleDatasSelItemsArray [MAXITEMSDATAS] = {"Date - Completion", "Date - Create", "Date - Entrez","Date - MeSH", "Date - Modification", "Date - Publication"};
    vector<string> myVisibleDatasSelItems;
	string andOrNotArray [MAXadd] = {"And", "Or", "Not", "-"};
    vector<string> andOrNot;
	/////////
	//TO SEND TO HTTP (Request)
	//USED IN REQUEST
    string myRequestSelItemsArray[MAXITEMS] = {"[Alliation]","[All%20Fields]", "[Author]", "[Author%20-%20Corporate]", "[Author%20-%20First]", "[Author%20-%20Full]", "[Author%20- Identifier]", "[Author%20-%20Last]", "[Book]", "[EC/RN%20Number]", "[Editor]", "[Filter]", "[Grant%20Number]", "[ISBN]", "[Investigator]", "[Investigator%20-%20Full]", "[Issue]", "[Journal]", "[Language]", "[Location%20ID]", "[MeSH%20Major%20Topic]", "[MeSH%20Subheading", "[Other%20Term]", "[Pagination]", "[Pharmacological%20Action]", "[Publication%20Type]", "[Publisher]", "[Secondary%20Source ID]", "[Supplementary%20Concept]", "[Text%20Word]", "[Title]", "[Title/Abstract]", "[Transliterated%20Title]", "[Volume]"};
    vector<string> myRequestSelItems;
    
    string myRequestDataSelItemsArray[MAXITEMSDATAS] = { "[DCOM]", "[DA]", "[EDAT]","[MHDA]", "[Date%20-%20Modification]", "[DP]",};
    vector<string> myRequestDataSelItems;
	
	string andOrNotRequestedArray [MAXadd] = {"+And+", "+Or+", "+Not+", "-"}; // TODO remove "-" to avoid search problems since we use directely this string request from gui.
	vector<string> andOrNotRequest;
	
	/////////
	//Data Reserved to send by events
	vector<string>	textString;
	vector<string>	reftypeString;
	vector<string>	conjuctiontypeString;
	void updateRequest();


    //GUIS
    void setupPubMedGUI();
    void addSearchField();
	void setupPubMedGuiDatas();
	void removeSearchField();
    void guiEvent(ofxUIEventArgs &e);
    ofxUICanvas *gui;

	int currentSearchBar;
	int searchBars;
	int searchBarsW;
	
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
	
	// search button
	float searchbuttonW;
	float searchbuttonH;
	
	bool bsnap;
	float space;
	float dim;
	float WidgetW;
	float sliderW;
	
};

