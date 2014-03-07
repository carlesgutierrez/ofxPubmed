#include "guiPubMed.h"

//----------------------------------------------
guiPubMed::guiPubMed()
{
	//Load all my Tags in Vectors
    myVisibleSelItems.assign(myVisibleSelItemsArray, myVisibleSelItemsArray+MAXITEMS);
    myVisibleDatasSelItems.assign(myVisibleDatasSelItemsArray, myVisibleDatasSelItemsArray+MAXITEMSDATAS);
	myVisibleSelItemsWithoutDatas.assign(myVisibleSelItemsArrayWithoutDatas, myVisibleSelItemsArrayWithoutDatas+MAXITEMS-MAXITEMSDATAS);
    andOrNot.assign(andOrNotArray, andOrNotArray+MAXadd);
	
	//Request
	//The same tags but with not spaces admited for html requests
    myRequestSelItems.assign(myRequestSelItemsArray, myRequestSelItemsArray+MAXITEMS);
    //myRequestDataSelItems.assign(myRequestDataSelItemsArray, myRequestDataSelItemsArray+MAXITEMSDATAS);
	andOrNotRequest.assign(andOrNotRequestedArray, andOrNotRequestedArray+MAXadd);
	
	//Set false my vector of recognixe if actual data inside selected items is DataSeachBar or TextField
	for (int i=0; i< MAXSEARCHBARS; i++) {
		myDataTypeSelected.push_back(false);
	}
	
	currentSearchBar= -1;
	searchBars		= 0;
	//	searchBarsH	= 100;
	int lineHeight	= 35;
	
	// tabCanvas
	tabCanvasX		= 0;
	tabCanvasY		= 0;
	tabCanvasW		= 600;
	tabCanvasH		= 600;
	toggleW			= 100;
	toggleH			= lineHeight;
	
	// Search field Canvas
	searchCanvasX	= tabCanvasX;
	searchCanvasY	= tabCanvasY;
	searchCanvasW	= tabCanvasW ;
	searchCanvasH	= tabCanvasH;
	
	// Dropdown list
	dropDownX		= 0;
	dropDownY		= 0;
	dropDownW		= 190;
	
	// Search field Canvas
	searchFieldX	= dropDownW;
	searchFieldY	= 0;
	searchFieldW	= 320;
	searchFieldH	= 0;
	
	// Search field Datas Canvas
	searchFieldDataX = dropDownW + OFX_UI_GLOBAL_WIDGET_SPACING*2 + OFX_UI_GLOBAL_PADDING;
	searchFieldDataY = OFX_UI_GLOBAL_WIDGET_SPACING;
	searchFieldDataW = searchFieldW *.5 - OFX_UI_GLOBAL_WIDGET_SPACING*.75;
	searchFieldDataH = OFX_UI_GLOBAL_SLIDER_WIDTH;
	
	// add buuton
	addButtonX		=	dropDownW + searchCanvasW;
	addButtonY		=	0;
	addButtonW		=	50;
	
	//Texts to send //resize to use them as array
	textString.resize(MAXSEARCHBARS);
	fromDateString.resize(MAXSEARCHBARS);
	toDateString.resize(MAXSEARCHBARS);
	reftypeString.resize(MAXSEARCHBARS);
	conjuctiontypeString.resize(MAXSEARCHBARS);
	andOrNotRequest.resize(MAXSEARCHBARS);
	
	//search button
	searchbuttonW	= 190;
	searchbuttonH	= 30;
	searchbuttonX	= searchCanvasW/2-searchbuttonW/2;
	searchbuttonY	= searchCanvasH-searchbuttonH-OFX_UI_GLOBAL_WIDGET_SPACING;
	
	//setup Search Bar GUi
	setupPubMedGUI();
	addSearchField();
	addSearchField();
}

//----------------------------------------------
guiPubMed::~guiPubMed()
{
	delete gui;
}

//--------------------------------------------------------------
void guiPubMed::update()
{
    if(letsAddNewSearchField)
	{
        addSearchField();
        letsAddNewSearchField = false;
    }
	
	if(bRemoveSearchField)
	{
        removeLastSearchField();
        bRemoveSearchField = false;
    }
}
//--------------------------------------------------------------
void guiPubMed::setupPubMedGUI()
{
	int i = searchBars;
	
	//	Create gui
    gui = new ofxUICanvas(searchCanvasX, searchCanvasY, searchCanvasW, searchCanvasH);
	ofAddListener(gui->newGUIEvent,this,&guiPubMed::guiEvent);
	gui->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
	
	// Add Search Button
	ofxUILabelButton* search = new ofxUILabelButton("Search",
													false,
													searchbuttonW,
													searchbuttonH,
													searchbuttonX,
													searchbuttonY);
	gui -> addWidget(search	);
}

//--------------------------------------------------------------
void guiPubMed::addSearchField()
{
	searchBars++;
	int i = searchBars;
	
	// Dropdown list
	//gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_LEFT);
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	
	ofxUIDropDownList* w = gui->addDropDownList("dropDown_"+ofToString(i),
												myVisibleSelItems,
												dropDownW,
												dropDownX,
												dropDownY);
	w->setAllowMultiple(false);
	w->setAutoClose(true);
	w->setShowCurrentSelected(true);
	w->setLabelText("Select");
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	
	// Text Input
	//textString.push_back("type here");
	ofxUITextInput *t =	gui->addTextInput("textField_"+ofToString(i),
										  "type here",
										  searchFieldW,
										  searchFieldH,
										  searchFieldX,
										  searchFieldY);
	t->setAutoClear(false);
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	
	// Add button
	ofxUIDropDownList *add = gui->addDropDownList("addButton_"+ofToString(i),
												  andOrNot,
												  addButtonW,
												  addButtonX,
												  addButtonY);
	add->setAllowMultiple(false);
	add->setAutoClose(true);
	add->setShowCurrentSelected(true);
	add->setLabelText("-");
	if(searchBars == 1)	add->setLabelText("And");

}

//--------------------------------------------------------------
bool guiPubMed::changeDataToSearchField(int _currentSearchBar){
	
	bool bchangedtoTextField = false;
	// Remove last search Bar
	int i = _currentSearchBar;
	
	if(i>-1){
		//remove Data textinputs
		gui->removeWidget("textFieldDataFrom_"+ofToString(i));
		gui->removeWidget("textFieldDataTo_"+ofToString(i));
		
		//add textfiled
		gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
		//textString.push_back("type here");
		
		//add text datas
		gui->addWidgetEastOf(new ofxUITextInput("textField_"+ofToString(i),
												"type here",
												searchFieldW,
												0,
												0,
												0,
												OFX_UI_FONT_MEDIUM),"dropDown_"+ofToString(i));
		
		ofxUITextInput *t = (ofxUITextInput *)gui->getWidget("textField_"+ofToString(i));
		t->setAutoClear(false);
		
		bchangedtoTextField = true;
	}
	
	return bchangedtoTextField;

}

//--------------------------------------------------------------
bool guiPubMed::changeSearchFieldToData(int _currentSearchBar)
{
	bool bchangedtoData = false;
	// Remove last search Bar
	int i = _currentSearchBar;
	
	if(i>-1){
		//remove textinput
		gui->removeWidget("textField_"+ofToString(i));
		
		//add text datas
		gui->addWidgetEastOf(new ofxUITextInput("textFieldDataFrom_"+ofToString(i),
												textString[i],
												searchFieldDataW,
												0,
												0,
												0,
												OFX_UI_FONT_MEDIUM),"dropDown_"+ofToString(i));

		ofxUITextInput *t = (ofxUITextInput *)gui->getWidget("textFieldDataFrom_"+ofToString(i));
		t->setAutoClear(false);
		t->setTextString("YYYY/MM/DD");
		t->setOnlyDataInput(true);

		
		gui->addWidgetEastOf(new ofxUITextInput("textFieldDataTo_"+ofToString(i),
												textString[i],
												searchFieldDataW,
												0,
												0,
												0,
												OFX_UI_FONT_MEDIUM), "textFieldDataFrom_"+ofToString(i));
	
		t = (ofxUITextInput *)gui->getWidget("textFieldDataTo_"+ofToString(i));
		t->setAutoClear(false);
		t->setTextString(getPresentData());
		t->setOnlyDataInput(true);


		
		// Set the last label on "-"
		//ofxUIDropDownList *add = (ofxUIDropDownList *)  gui->getWidget("addButton_"+ofToString(i-1));
		//add->setLabelText("-");
		bchangedtoData = true;
	}
	
	return bchangedtoData;

}
//--------------------------------------------------------------
string guiPubMed::getPresentData(){
	//check OF data format
	string Y = "%Y";
	string M = "%n";
	string D = "%e";
	string formatActualdata = Y + "/" + M + "/" + D;
	formatActualdata = ofGetTimestampString(formatActualdata);
	
	return formatActualdata;
}

//--------------------------------------------------------------
void guiPubMed::removeLastSearchField()
{
	// Remove last search Bar
	int i = searchBars;
	if(i>1){
		gui->removeWidget("dropDown_"+ofToString(i));
		gui->removeWidget("textField_"+ofToString(i));
		gui->removeWidget("addButton_"+ofToString(i));
		searchBars--;

		// Set the last label on "-"
		ofxUIDropDownList *add = (ofxUIDropDownList *)  gui->getWidget("addButton_"+ofToString(i-1));
		add->setLabelText("-");

	}
}

//--------------------------------------------------------------
void guiPubMed::sendRequest()
{
	ofNotifyEvent(guiPubMedEvent::onUpdateSearch, newEvent);
	
}

//--------------------------------------------------------------
void guiPubMed::updateRequest()
{
	//My event to send
	newEvent.query="";
	//TextFields types
	string conjuctiontype;
	string reftype;
	string text;
	//Data types
	string datafrom;
	string dataTo;
	string datetype = "&datetype=";
	string sMindate = "&mindate=";
	string sMaxdate = "&maxdate=";
	string sTerm = "&term=";
		
	ofLogVerbose("guiPubMed") <<"updateRequest num searchBars: " << searchBars;

	//TODO Check empty textInputs
	//TODO then searchBars where should start to build request phrase
	
	//set term questionarie //TODO anyway?
	newEvent.query += sTerm;
	
	//Set all open brakets
	string openBraket = "(";
	for (int i = 0; i <= searchBars-2; i++) newEvent.query += openBraket;
	
	
	//Add inputtext + searchType + ) + ADN/OR/NOT
	for (int i = 0 ; i <= searchBars; i++){
		
		//Set our vars
		string closeBraket = "";
		if(i!=searchBars)closeBraket = ")";
		
		//Check all params to set right search mode
		conjuctiontype = conjuctiontypeString[i];
		reftype = reftypeString[i];
		
		if((conjuctiontype.empty()&&i!=searchBars))conjuctiontype = "+AND+";
		if(i == 0)conjuctiontype = ""; //avoid to set AND fisrt position
		//conjuctiontype = ""; //avoid to set AND after date type..
			
		if(reftype.empty())reftype = "[All%20Fields]";
		
		if(!myDataTypeSelected[i]){
			//if serachText
			text =  textString[i];
			//set final request to send by event
			if(!text.empty()){
				newEvent.query += conjuctiontype + text + reftype + closeBraket;
				ofLogVerbose("guiPubMed") << "Current query: " << newEvent.query;
			}
		}
		else {
			//else then textData related
			datafrom = fromDateString[i];
			dataTo = toDateString[i];
			if(dataTo.empty())dataTo = getPresentData();
			//set final request to send by event
			if(!text.empty()){
				newEvent.query += datetype + reftype + sMindate + datafrom + sMaxdate + dataTo;
				ofLogVerbose("guiPubMed") << "Current query: " << newEvent.query;
			}
		}

	}
	
	
}

//--------------------------------------------------------------
bool guiPubMed::isDateTypeSelected(string name){

	bool bFoundDataType = false;
	
	for(int i = 0; i<myVisibleDatasSelItems.size();i++){
		if(name.compare(myVisibleDatasSelItems[i]) == 0) bFoundDataType = true;
	}
	
	return bFoundDataType;
}

//--------------------------------------------------------------
void guiPubMed::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
	ofLogVerbose("guiPubMed")<< "-- New event from: " << name;
	
	// Get the current searchBar number
	if (ofIsStringInString(name, "_")){
		vector<string> splitted	= ofSplitString(name, "_");
		currentSearchBar = ofToInt(splitted[1]);
	}
    
	
	//---------------------------------------------
	if(name == "Search"){
		if(e.widget->getState() == OFX_UI_STATE_OVER)
		{
			ofLogVerbose("guiPubMed")<< "Search Button: Start";
			sendRequest();
		}
    }
	//---------------------------------------------
	else if(name == "textField_"+ofToString(currentSearchBar))
	{
		ofxUITextInput *t = (ofxUITextInput *) e.widget;
		ofLogVerbose("guiPubMed") << "TextInput current text: " << t->getTextString();
		ofLogVerbose("guiPubMed") << "getTriggerType " << t->getTriggerType() << endl;

		if(t->getInputTriggerType() ==  OFX_UI_TEXTINPUT_ON_ENTER){
			textString[currentSearchBar]	=	t->getTextString();
			ofLogVerbose("guiPubMed")<< "ON ENTER: " << textString[currentSearchBar] << endl;
		}else if(t->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS){
			//t->setTextString("");
			ofLogVerbose("guiPubMed")<< "ON FOCUS: " << textString[currentSearchBar] << endl;
		}else if(t->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS){
			textString[currentSearchBar]	=	t->getTextString();
			ofLogVerbose("guiPubMed")<< "ON BLUR: textinut: " << textString[currentSearchBar] << endl;
		}
	}

	//---------------------------------------------
	else if(name == "And")
	{
		ofLogVerbose("guiPubMed") << "AND";
		if(searchBars == currentSearchBar)	cout << "ADDED" << endl,		letsAddNewSearchField = true;
		conjuctiontypeString[currentSearchBar] = andOrNotRequest[0];

	}
	else if(name == "Or")
	{
		ofLogVerbose("guiPubMed") << "OR";
		if(searchBars == currentSearchBar)	cout << "ADDED" << endl,		letsAddNewSearchField = true;
		conjuctiontypeString[currentSearchBar] = andOrNotRequest[1];

	}
	else if(name == "Not")
	{
		ofLogVerbose("guiPubMed") << "NOT";
		if(searchBars == currentSearchBar)	cout << "ADDED" << endl,		letsAddNewSearchField = true;
		conjuctiontypeString[currentSearchBar] = andOrNotRequest[2];

	}
	else if(name == "-")
	{
		ofLogVerbose("guiPubMed") << "-";
		if(searchBars == currentSearchBar)
		{
			bRemoveSearchField = true;
		}
		else
		{
			// TODO:
			// Set the label to the last used (instead of "-")
			// following code does not work (of course..)
			//			ofxUIDropDownList *add = (ofxUIDropDownList *)  gui->getWidget("addButton_"+ofToString(currentSearchBar));
			//			ofxUIToggle *t = (ofxUIToggle *) e.widget;
			//			add->setLabelText(t->getName());
			//			cout <<"Toggle name ="<< t->getName()<< endl;
		}
	}
	else if(name == "textFieldDataFrom_"+ofToString(currentSearchBar))
	{
		ofxUITextInput *t = (ofxUITextInput *) e.widget;
		ofLogVerbose("guiPubMed") << "Date TextInput current text: " << t->getTextString();
		ofLogVerbose("guiPubMed") << "Date getTriggerType " << t->getTriggerType() << endl;
		if(t->getInputTriggerType() ==  OFX_UI_TEXTINPUT_ON_ENTER)
		{
			fromDateString[currentSearchBar] = t->getTextString();
			ofLogVerbose("guiPubMed")<< "ON ENTER:";
		}else if(t->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
		{
			//???
			ofLogVerbose("guiPubMed")<< "ON FOCUS:";
		}else if(t->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
		{
			fromDateString[currentSearchBar] = t->getTextString();
			ofLogVerbose("guiPubMed")<< "ON BLUR:";
		}

	}
	else if(name == "textFieldDataTo_"+ofToString(currentSearchBar))
	{
		ofxUITextInput *t = (ofxUITextInput *) e.widget;
		ofLogVerbose("guiPubMed") << "Date TextInput current text: " << t->getTextString();
		ofLogVerbose("guiPubMed") << "Date getTriggerType " << t->getTriggerType() << endl;
		if(t->getInputTriggerType() ==  OFX_UI_TEXTINPUT_ON_ENTER)
		{
			toDateString[currentSearchBar] = t->getTextString();
			ofLogVerbose("guiPubMed")<< "ON ENTER:";
		}else if(t->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
		{
			toDateString[currentSearchBar] = t->getTextString();
			ofLogVerbose("guiPubMed")<< "ON FOCUS:";
		}else if(t->getInputTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
		{
			toDateString[currentSearchBar] = t->getTextString();
			ofLogVerbose("guiPubMed")<< "ON BLUR:";
		}
	}
	else
	{	//DROPDOWN MENU
		int myit = 0;
		for(vector<string>::iterator it = myVisibleSelItems.begin(); it != myVisibleSelItems.end(); ++it)
		{
			if ((*it)==name)
			{
				ofLogVerbose("guiPubMed")<< "Dropdown_"<< currentSearchBar <<" "<< (*it);
				//Get type of reference
				reftypeString[currentSearchBar]= myRequestSelItems[myit];
				
				
				//Swicht mode
				/////////////////////////////////Date case
				bool bFoundDataType = false;
				int idFound = -1;
				for(int i = 0; i<myVisibleDatasSelItems.size();i++){
					//Check if == and not a already Datatype
					if(name.compare(myVisibleDatasSelItems[i]) == 0 && !myDataTypeSelected[currentSearchBar]){
							
						//If searchfield is Active change to data
						ofLogVerbose("guiPubMed") << "Change textinput to Data Inputs i=" << i << endl;
						bool changedone = changeSearchFieldToData(currentSearchBar);
						if(changedone)myDataTypeSelected[currentSearchBar] = true;
						bFoundDataType = true;
						idFound = i;
					}
					else if(name.compare(myVisibleDatasSelItems[i]) == 0){
						bFoundDataType = true;
					}
				}
				//////////////////////////////////Non Date case
				if(!bFoundDataType){
					//If that's normal search field type (so not found any datatype ) then return to thar format
					for(int i = 0; i< myVisibleSelItems.size();i++){
						//Check if == and That was Datatype
						if(name.compare(myVisibleSelItems[i]) == 0 && myDataTypeSelected[currentSearchBar]){
							bool changedone = changeDataToSearchField(currentSearchBar);
							if(changedone)myDataTypeSelected[currentSearchBar] = false;
							ofLogVerbose("guiPubMed") << "Change Data Inputs to textinput id=" << i << endl;
						}
					}
				}
			}
			myit++;
		}
	}
	
	//Finally update current textInpunt and parameters into the requests string
	updateRequest();
	cout << endl;
}


//--------------------------------------------------------------
void guiPubMed::keyPressed(int key){

/*
    //Direct Request for Test and apply with RETURN
    if(key == 'l'){
		cout << "pressed l" << endl;
		addSearchField();
    }
  */
}