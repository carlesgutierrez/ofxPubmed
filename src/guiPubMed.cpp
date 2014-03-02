#include "guiPubMed.h"

//----------------------------------------------
guiPubMed::guiPubMed()
{
	//Load all my Tags in Vectors
    myVisibleSelItems.assign(myVisibleSelItemsArray, myVisibleSelItemsArray+MAXITEMS);
    myVisibleDatasSelItems.assign(myVisibleDatasSelItemsArray, myVisibleDatasSelItemsArray+MAXITEMSDATAS);
    andOrNot.assign(andOrNotArray, andOrNotArray+MAXadd);
	
	//Request
	//The same tags but with not spaces admited for html requests
    myRequestSelItems.assign(myRequestSelItemsArray, myRequestSelItemsArray+MAXITEMS);
    myRequestDataSelItems.assign(myRequestDataSelItemsArray, myRequestDataSelItemsArray+MAXITEMSDATAS);
	andOrNotRequest.assign(andOrNotRequestedArray, andOrNotRequestedArray+MAXadd);
	
	
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
	
	// add buuton
	addButtonX		=	dropDownW + searchCanvasW;
	addButtonY		=	0;
	addButtonW		=	50;
	
	//Texts to send //resize to use them as array
	textString.resize(MAXSEARCHBARS);
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
void guiPubMed::update(){
    
    if(letsAddNewSearchField){
        addSearchField();
        letsAddNewSearchField = false;
    }
	
	if(bRemoveSearchField){
        removeSearchField();
        bRemoveSearchField = false;
    }
}
//--------------------------------------------------------------
void guiPubMed::setupPubMedGUI(){
	
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
void guiPubMed::addSearchField(){
	
	searchBars++;
	int i = searchBars;
	
	// Dropdown list
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
	textString.push_back("type here");
	ofxUITextInput *t =	gui->addTextInput("textField_"+ofToString(i),
										  textString[i],
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
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
}

//--------------------------------------------------------------
void guiPubMed::removeSearchField(){

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
void guiPubMed::sendRequest(){

	ofNotifyEvent(guiPubMedEvent::onUpdateSearch, newEvent);
	
}
//--------------------------------------------------------------
void guiPubMed::updateRequest(){
	
	newEvent.query="";
		
//	ofLogVerbose("guiPubMed") <<"updateRequest num searchBars: " << searchBars;

	for (int i = 1 ; i <= searchBars; i++)
	{
		//event to set Request ready to start
		string conjuctiontype = conjuctiontypeString[i]; // +AND+
		string reftype = reftypeString[i]; // "[Title]"
		string text =  textString[i];

		cout <<"conjuctiontype ="<<conjuctiontype<< endl;
		
		if(reftype.empty())reftype = "[All%20Fields]";
		if(!text.empty())newEvent.query += text + reftype + conjuctiontype;
	}
	ofLogVerbose("guiPubMed") << "Current query: " << newEvent.query;
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
//			cout << "searchBars = "<< searchBars << endl;
//			cout << "currentS = "<< currentSearchBar << endl;
	}
    
	
	//---------------------------------------------
	if(name == "Search"){
		if(e.widget->getState() == OFX_UI_STATE_OVER){
			ofLogVerbose("guiPubMed")<< "Do the sarch.";
			sendRequest();
		}
    }
	//---------------------------------------------
	else if(name == "textField_"+ofToString(currentSearchBar))
	{
		ofxUITextInput *t = (ofxUITextInput *) e.widget;
		ofLogVerbose("guiPubMed") << "TextInput current text: " << t->getTextString();
		
		if(t->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
		{
			textString[currentSearchBar]	=	t->getTextString(); //ofLogVerbose("guiPubMed")<< "ON ENTER:";
		}else if(t->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
		{
//			t->setTextString("");									//ofLogVerbose("guiPubMed")<< "ON FOCUS:";
		}else if(t->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
		{
			textString[currentSearchBar]	=	t->getTextString();	//ofLogVerbose("guiPubMed")<< "ON BLUR:";
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
	
	//---------------------------------------------
	else{
		
		//return myRequestSelItems from my myVisibleSelItems
		int myit = 0;
		for(vector<string>::iterator it = myVisibleSelItems.begin(); it != myVisibleSelItems.end(); ++it){
			
			if ((*it)==name){
				ofLogVerbose("guiPubMed")<< "Dropdown_"<< currentSearchBar <<" "<< (*it);
				reftypeString[currentSearchBar]= myRequestSelItems[myit];
//				ofLogVerbose("guiPubMed")<< "reftypeString[currentSearchBar]= "<< reftypeString[currentSearchBar];
			}
			myit++;
		}
	}
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