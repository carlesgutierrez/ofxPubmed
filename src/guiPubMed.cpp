#include "guiPubMed.h"

//----------------------------------------------
guiPubMed::guiPubMed()
{
	//Load all my Tags in Vectors
    myVisibleSelItems.assign(myVisibleSelItemsArray, myVisibleSelItemsArray+MAXITEMS);
    myVisibleDatasSelItems.assign(myVisibleDatasSelItemsArray, myVisibleDatasSelItemsArray+MAXITEMSDATAS);
    andOrNot.assign(andOrNotArray, andOrNotArray+MAXadd);
	
	
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
	
	textString.reserve(10);
	
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
	ofxUIDropDownList *w = (ofxUIDropDownList *)  gui->getWidget("dropDown_"+ofToString(i));
	ofxUITextInput *t = (ofxUITextInput *)  gui->getWidget("textField_"+ofToString(i));
	ofxUIDropDownList *add = (ofxUIDropDownList *)  gui->getWidget("addButton_"+ofToString(i));
	delete w;
	delete t;
	delete add;
	
	searchBars--;
}

//--------------------------------------------------------------
void guiPubMed::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
	ofLogVerbose() << "-- New event from: " << name;
	
	// Get the current searchBar number
	if (ofIsStringInString(name, "_")){
		vector<string> splitted	= ofSplitString(name, "_");
		currentSearchBar = ofToInt(splitted[1]);
		//	cout << "searchBars = "<< searchBars << endl;
		//	cout << "currentS = "<< currentSearchBar << endl;
	}
    
	
	//---------------------------------------------
	if(name == " Search"){
//        ofNotifyEvent(onStartSearch, searchButtonStatus);
		// NOTIFY Search EVENT HERE
        ofLogVerbose() << "Do the sarch event ";
    }
	
	//---------------------------------------------
	else if(name == "textField_"+ofToString(currentSearchBar))
	{
		ofxUITextInput *t = (ofxUITextInput *) e.widget;
		string output = t->getTextString();
		cout << output << endl;
		// NOTIFY TextField EVENT HERE
		
		if(t->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER){
//			ofLogVerbose() << "ON ENTER:";
			textString[currentSearchBar]	=	t->getTextString();
		}else if(t->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS){
//			ofLogVerbose() << "ON FOCUS:";
			t->setTextString("");
		}else if(t->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS){
//			ofLogVerbose() << "ON BLUR:";
			textString[currentSearchBar]	=	t->getTextString();
		}
	}
	
	//---------------------------------------------
	else if(name == "And"){
		ofLogVerbose() << "AND";
		if(searchBars == currentSearchBar)	letsAddNewSearchField = true;
		// NOTIFY EVENT HERE
	}else if(name == "Or"){
		ofLogVerbose() << "OR";
		if(searchBars == currentSearchBar)	letsAddNewSearchField = true;
		// NOTIFY EVENT HERE
	}else if(name == "Not"){
		ofLogVerbose() << "NOT";
		if(searchBars == currentSearchBar)	letsAddNewSearchField = true;
		// NOTIFY EVENT HERE
	}else if(name == "-"){
		ofLogVerbose() << " -";
		// NOTIFY EVENT HERE
		//		if(searchBars == currentSearchBar)	bRemoveSearchField = true;
	}
	
	//---------------------------------------------
	else{
		for(vector<string>::iterator it = myVisibleSelItems.begin(); it != myVisibleSelItems.end(); ++it)
		{
			if ((*it)==name){
				ofLogVerbose() << "Dropdown_"<< currentSearchBar <<" "<< (*it);
				// NOTIFY Dropdown EVENT HERE
			}
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