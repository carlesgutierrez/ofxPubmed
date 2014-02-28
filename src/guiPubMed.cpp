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
	
	//Textes to send //resize to use them as array
	textString.resize(MAXSEARCHBARS);
	reftypeString.resize(MAXSEARCHBARS);
	conjuctiontypeString.resize(MAXSEARCHBARS);
	andOrNotRequest.resize(MAXSEARCHBARS);
	
	//search button
	searchbuttonW	= 190;
	searchbuttonH	= 30;

	
	//setup Search Bar GUi
	setupPubMedGUI();
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
    gui->addButton(" Search", false, searchbuttonW, searchbuttonH);

	// Dropdown list
    gui->addDropDownList("dropDown_"+ofToString(i), myVisibleSelItems, dropDownW, dropDownX, dropDownY);
	ofxUIDropDownList *w = (ofxUIDropDownList *)  gui->getWidget("dropDown_"+ofToString(i));
	w->setAllowMultiple(false);
	w->setAutoClose(true);
	w->setShowCurrentSelected(true);
	w->setLabelText("Select");
	ofxUIWidgetWithLabel *wwl = (ofxUIWidgetWithLabel *)  w->getLabelWidget();
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
		
	// Text Input
	textString.push_back("type here");
	gui->addTextInput("textField_"+ofToString(i), textString[i], searchFieldW, searchFieldH, searchFieldX, searchFieldY);
	ofxUITextInput *t = (ofxUITextInput *)  gui->getWidget("textField_"+ofToString(i));
	t->setAutoClear(false);
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	
	// Add button
	gui->addDropDownList("addButton_"+ofToString(i), andOrNot, addButtonW, addButtonX, addButtonY);
	ofxUIDropDownList *add = (ofxUIDropDownList *)  gui->getWidget("addButton_"+ofToString(i));
	add->setAllowMultiple(false);
	add->setAutoClose(true);
	add->setShowCurrentSelected(true);
	add->setLabelText("And");
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	
}

//--------------------------------------------------------------
void guiPubMed::addSearchField(){
	
	searchBars++;
	int i = searchBars;
	
	// Dropdown list
    gui->addDropDownList("dropDown_"+ofToString(i), myVisibleSelItems, dropDownW, dropDownX, dropDownY);
	ofxUIDropDownList *w = (ofxUIDropDownList *)  gui->getWidget("dropDown_"+ofToString(i));
	w->setAllowMultiple(false);
	w->setAutoClose(true);
	w->setShowCurrentSelected(true);
	w->setLabelText("Select");
	ofxUIWidgetWithLabel *wwl = (ofxUIWidgetWithLabel *)  w->getLabelWidget();
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	
	// Text Input
	textString.push_back("type here");
	gui->addTextInput("textField_"+ofToString(i), textString[i], searchFieldW, searchFieldH, searchFieldX, searchFieldY);
	ofxUITextInput *t = (ofxUITextInput *)  gui->getWidget("textField_"+ofToString(i));
	t->setAutoClear(false);
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	
	// Add button
	gui->addDropDownList("addButton_"+ofToString(i), andOrNot, addButtonW, addButtonX, addButtonY);
	ofxUIDropDownList *add = (ofxUIDropDownList *)  gui->getWidget("addButton_"+ofToString(i));
	add->setAllowMultiple(false);
	add->setAutoClose(true);
	add->setShowCurrentSelected(true);
	add->setLabelText("-");
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);

}

//--------------------------------------------------------------
void guiPubMed::removeSearchField(){
	int i = searchBars;
	
	if(i>0){
		ofxUIDropDownList *w = (ofxUIDropDownList *)  gui->getWidget("dropDown_"+ofToString(i));
		ofxUITextInput *t = (ofxUITextInput *)  gui->getWidget("textField_"+ofToString(i));
		ofxUIDropDownList *add = (ofxUIDropDownList *)  gui->getWidget("addButton_"+ofToString(i));
		delete w;
		delete t;
		delete add;
		
		searchBars--;
	}
}

//--------------------------------------------------------------
void guiPubMed::updateRequest(){
	
	//Clear Esearch Request to basic mode
	bool searchButtonStatus = true;
	
	guiPubMedEvent newEvent; //if this would be called as static, will save last values used...
	
	ofLogVerbose("GuiVerbose") <<"updateRequest num searchBars: " << searchBars << endl;

	for (int i = 0 ; i <= searchBars - 1; i++) {
		
		//event to set Request ready to start
		string conjuctiontype = conjuctiontypeString[i]; // +AND+
		string reftype = reftypeString[i]; // "[Title]"
		string text =  textString[i];
		
		if(conjuctiontype.empty())conjuctiontype = "+AND+";
		if(reftype.empty())conjuctiontype = "[All%20Fields]";
		if(!text.empty())newEvent.query += text + reftype + conjuctiontype;
		
		ofLogVerbose("GuiVerbose") << "Query under construcction: " << newEvent.query << endl;
	}
	
	string text =  textString[searchBars];
	string reftype = reftypeString[searchBars]; // "[Title]"
	newEvent.query += text + reftype;
	
	ofNotifyEvent(guiPubMedEvent::onUpdateSearch, newEvent);
}

//--------------------------------------------------------------
void guiPubMed::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
	ofLogVerbose("GuiVerbose")<< "-- New event from: " << name;
	
	// Get the current searchBar number
	if (ofIsStringInString(name, "_")){
		vector<string> splitted	= ofSplitString(name, "_");
		currentSearchBar = ofToInt(splitted[1]);
		//	cout << "searchBars = "<< searchBars << endl;
		//	cout << "currentS = "<< currentSearchBar << endl;
	}
    
	
	//--------------------------------set a BasiceSearch Request-------------
	if(name == " Search"){
		// NOTIFY Search EVENT HERE
        ofLogVerbose("GuiVerbose")<< "Click Search Button";
		if(e.widget->getState() == OFX_UI_STATE_OVER){
			ofLogVerbose("GuiVerbose")<< "Do the sarch event::updateRequest";
			updateRequest();
		}
    }
	//---------------------------------------------
	else if(name == "textField_"+ofToString(currentSearchBar))
	{
		ofxUITextInput *t = (ofxUITextInput *) e.widget;
		string output = t->getTextString();
		ofLogVerbose("GuiVerbose") << "Pick textInput where selected text was: " << output << endl;
		
		if(t->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER){
			textString[currentSearchBar]	=	t->getTextString(); //ofLogVerbose("GuiVerbose")<< "ON ENTER:";
		}else if(t->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS){
			t->setTextString(""); //ofLogVerbose("GuiVerbose")<< "ON FOCUS:";
		}else if(t->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS){
			textString[currentSearchBar]	=	t->getTextString();//ofLogVerbose("GuiVerbose")<< "ON BLUR:";
		}
	}
	
	//---------------------------------------------
	else if(name == "And"){

		ofLogVerbose("GuiVerbose") << "AND";
		if(searchBars == currentSearchBar){
			letsAddNewSearchField = true;
			conjuctiontypeString[currentSearchBar] = andOrNotRequest[0];
		}
		// NOTIFY EVENT HERE
	}else if(name == "Or"){
		ofLogVerbose("GuiVerbose") << "OR";
		if(searchBars == currentSearchBar){
			letsAddNewSearchField = true;
			conjuctiontypeString[currentSearchBar] = andOrNotRequest[1];
		}
		// NOTIFY EVENT HERE
	}else if(name == "Not"){
		ofLogVerbose("GuiVerbose") << "NOT";
		if(searchBars == currentSearchBar){
			letsAddNewSearchField = true;
			conjuctiontypeString[currentSearchBar] = andOrNotRequest[2];
		}
		// NOTIFY EVENT HERE
	}else if(name == "-"){
		ofLogVerbose("GuiVerbose") << " -";
		// NOTIFY EVENT HERE
		// if(searchBars == currentSearchBar)	bRemoveSearchField = true;
	}
	
	//---------------------------------------------
	else{
		
		//return myRequestSelItems from my myVisibleSelItems
		int myit = 0;
		for(vector<string>::iterator it = myVisibleSelItems.begin(); it != myVisibleSelItems.end(); ++it){
			
			if ((*it)==name){
				ofLogVerbose("GuiVerbose")<< "Dropdown_"<< currentSearchBar <<" "<< (*it);
				// NOTIFY Dropdown EVENT HERE
				reftypeString[currentSearchBar]= myRequestSelItems[myit];
				ofLogVerbose("GuiVerbose")<< "reftypeString[currentSearchBar]= "<< reftypeString[currentSearchBar] << endl;
			}
			myit++;
		}
	}
	
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