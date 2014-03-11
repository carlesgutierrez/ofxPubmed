#pragma once

#include "ofMain.h"
#include "ofxUI.h"

#include "guiPubMedEvent.h"
#include "Poco/DateTimeParser.h"


#define MAXITEMS 40
#define MAXITEMSDATAS 6
#define MAXadd 4
#define MAXSEARCHBARS 10

class guiPubMed {

public:

	guiPubMed();
	~guiPubMed();

	void update();
	void keyPressed(int key);
	
	guiPubMedEvent newEvent;
	
	//some utils necesary for this GUI
	bool isDate(string name);
	string getPresentData();
	
private:
    
	/////////
	//USED IN APP (Visible)
    string myVisibleSelItemsArray [MAXITEMS] = {"Affiliation","All Fields", "Author", "Author-Corporate", "Author-First", "Author - Full", "Author - Identifier", "Author - Last", "Book", "Date - Completion", "Date - Create", "Date - Entrez","Date - MeSH", "Date - Modification", "Date - Publication", "EC/RN Number", "Editor", "Filter", "Grant Number", "ISBN", "Investigator", "Investigator - Full", "Issue", "Journal", "Language", "Location ID", "MeSH Major Topic", "MeSH Subheading", "Other Term", "Pagination", "Pharmacological Action", "Publication Type", "Publisher", "Secondary Source ID", "Supplementary Concept", "Text Word", "Title", "Title/Abstract", "Transliterated Title", "Volume"};
    vector<string> myVisibleSelItems;
	
	string myVisibleSelItemsArrayWithoutDatas[MAXITEMS-MAXITEMSDATAS] = {"Affiliation","All Fields", "Author", "Author-Corporate", "Author-First", "Author - Full", "Author - Identifier", "Author - Last", "Book", "EC/RN Number", "Editor", "Filter", "Grant Number", "ISBN", "Investigator", "Investigator - Full", "Issue", "Journal", "Language", "Location ID", "MeSH Major Topic", "MeSH Subheading", "Other Term", "Pagination", "Pharmacological Action", "Publication Type", "Publisher", "Secondary Source ID", "Supplementary Concept", "Text Word", "Title", "Title/Abstract", "Transliterated Title", "Volume"};
    vector<string> myVisibleSelItemsWithoutDatas;
	
    string myVisibleDatasSelItemsArray [MAXITEMSDATAS] = {"Date - Completion", "Date - Create", "Date - Entrez","Date - MeSH", "Date - Modification", "Date - Publication"};
    vector<string> myVisibleDatasSelItems;
	string andOrNotArray [MAXadd] = {"And", "Or", "Not", "-"};
    vector<string> andOrNot;
	
	/////////
	//TO SEND TO HTTP (raw Request)
    string myRequestSelItemsArray[MAXITEMS] = {"[Affiliation]","[All%20Fields]", "[Author]", "[Author%20-%20Corporate]", "[Author%20-%20First]", "[Author%20-%20Full]", "[Author%20- Identifier]", "[Author%20-%20Last]", "[Book]", "[Date%20-%20Completion]", "[Date%20-%20Create]", "[Date%20-%20Entrez]","[Date%20-%20MeSH]", "[Date%20-%20Modification]", "[Date%20-%20Publication]", "[EC/RN%20Number]", "[Editor]", "[Filter]", "[Grant%20Number]", "[ISBN]", "[Investigator]", "[Investigator%20-%20Full]", "[Issue]", "[Journal]", "[Language]", "[Location%20ID]", "[MeSH%20Major%20Topic]", "[MeSH%20Subheading", "[Other%20Term]", "[Pagination]", "[Pharmacological%20Action]", "[Publication%20Type]", "[Publisher]", "[Secondary%20Source ID]", "[Supplementary%20Concept]", "[Text%20Word]", "[Title]", "[Title/Abstract]", "[Transliterated%20Title]", "[Volume]"};
    vector<string> myRequestSelItems;
		
	string andOrNotRequestedArray [MAXadd] = {"+AND+", "+OR+", "+NOT+", "-"}; 
	vector<string> andOrNotRequest;
	
	/////////
	//Data Reserved to send by events
	string			requestString;
	vector<string>	textString;
	vector<string>	reftypeString;
	vector<string>	conjuctiontypeString;
	
	vector<string>  reftypeData;
	vector<string>	fromDateString;
	vector<string>	toDateString;
	
	void updateRequest();
	void sendRequest();

    //GUIS
    ofxUICanvas *gui;
	void setupPubMedGUI();
    void addSearchField();
	void setupPubMedGuiDatas();
	bool changeSearchFieldToData(int i);
	bool changeDataToSearchField(int i);
	void removeLastSearchField();
    void guiEvent(ofxUIEventArgs &e);
	
	vector<bool>	myDataTypeSelected;
	
	int countDataFilled();
	
    bool letsAddNewSearchField;
	bool bRemoveSearchField;

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
	
	// searchCanvasData
	float searchFieldDataX;
	float searchFieldDataY;
	float searchFieldDataW;
	float searchFieldDataH;
	
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
	float searchbuttonX;
	float searchbuttonY;
	
	bool bsnap;
	float space;
	float dim;
	float WidgetW;
	float sliderW;
	
};

