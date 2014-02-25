#include "guiPubMed.h"

//----------------------------------------------

guiPubMed::guiPubMed()
{
	
	//Load all my Tags in Vectors
    myVisibleSelItems.assign(myVisibleSelItemsArray, myVisibleSelItemsArray+MAXITEMS);
    myVisibleDatasSelItems.assign(myVisibleDatasSelItemsArray, myVisibleDatasSelItemsArray+MAXITEMSDATAS);
    andOrNot.assign(andOrNotArray, andOrNotArray+MAXadd);
}

//----------------------------------------------
guiPubMed::~guiPubMed()
{
}

//--------------------------------------------------------------
void guiPubMed::exit() {
    delete gui;
}

//--------------------------------------------------------------

void guiPubMed::setup(){

	int searchFields= 1;
//	searchFieldsH	= 100;
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
	searchCanvasW	= tabCanvasW;
	searchCanvasH	= tabCanvasH;

	// Dropdown list
	dropDownX	= 0;
	dropDownY	= 0;
	dropDownW	= 190;
	
	// Search field Canvas
	searchFieldX	= dropDownW;
	searchFieldY	= 0;
	searchFieldW	= 320;
	searchFieldH	= 0;

	// add buuton
	addButtonX =	dropDownW + searchCanvasW;
	addButtonY =	0;
	addButtonW =	50;
	
	//setup Search Bar GUi
	setupPubMedGUI();
	addSearchField();

}

//--------------------------------------------------------------
void guiPubMed::setupPubMedGUI(){
//	gui->setFont("fonts/Arial Unicode.ttf");
	
    gui = new ofxUICanvas(searchCanvasX, searchCanvasY, searchCanvasW, searchCanvasH);
	gui->setWidgetFontSize(OFX_UI_FONT_MEDIUM);

	int i = searchFields;
	
	// Dropdown list
    gui->addDropDownList("dropDown"+ofToString(i), myVisibleSelItems, dropDownW, dropDownX, dropDownY);
	ofxUIDropDownList *w = (ofxUIDropDownList *)  gui->getWidget("dropDown"+ofToString(i));
	w->setAllowMultiple(false);
	w->setAutoClose(true);
	w->setShowCurrentSelected(true);
	w->setLabelText("Select");
	ofxUIWidgetWithLabel *wwl = (ofxUIWidgetWithLabel *)  w->getLabelWidget();
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	
	
	// Text Input
	gui->addTextInput("textField"+ofToString(i), "Type here ", searchFieldW, searchFieldH, searchFieldX, searchFieldY);
	ofxUITextInput *t = (ofxUITextInput *)  gui->getWidget("textField"+ofToString(i));
	t->setAutoClear(true);
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	
	
	// Add button
	gui->addDropDownList("+"+ofToString(i), andOrNot, addButtonW, addButtonX, addButtonY);
	ofxUIDropDownList *add = (ofxUIDropDownList *)  gui->getWidget("+"+ofToString(i));
	add->setAllowMultiple(false);
	add->setAutoClose(true);
	add->setShowCurrentSelected(true);
//	add->setDrawBack(true);
//	add->setLabelVisible(false);
//	add->setState(1);
//	add->setValue(true);
	add->setLabelText("And");
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	
	gui->addSpacer(50);
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
	
    ofAddListener(gui->newGUIEvent,this,&guiPubMed::guiEvent);
}
//*searchFields*searchFieldH);
//--------------------------------------------------------------
void guiPubMed::addSearchField(){
	
	searchFields++;
	int i = searchFields;
	
	// Dropdown list
    gui->addDropDownList("dropDown"+ofToString(i), myVisibleSelItems, dropDownW, dropDownX, dropDownY);
	ofxUIDropDownList *w = (ofxUIDropDownList *)  gui->getWidget("dropDown"+ofToString(i));
	w->setAllowMultiple(false);
	w->setAutoClose(true);
	w->setShowCurrentSelected(true);
	w->setLabelText("Select");
	ofxUIWidgetWithLabel *wwl = (ofxUIWidgetWithLabel *)  w->getLabelWidget();
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	
	
	// Text Input
	gui->addTextInput("textField"+ofToString(i), "Type here ", searchFieldW, searchFieldH, searchFieldX, searchFieldY);
	ofxUITextInput *t = (ofxUITextInput *)  gui->getWidget("textField"+ofToString(i));
	t->setAutoClear(true);
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
	
	
	// Add search
	gui->addDropDownList("+"+ofToString(i), andOrNot, addButtonW, addButtonX, addButtonY);
	ofxUIDropDownList *add = (ofxUIDropDownList *)  gui->getWidget("+"+ofToString(i));
	add->setAllowMultiple(false);
	add->setAutoClose(true);
	add->setShowCurrentSelected(true);
	add->setLabelText("-");
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);

	gui->addSpacer(50);
	gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
}

//--------------------------------------------------------------
void guiPubMed::removeSearchField(){
	int i = searchFields;
	ofxUIDropDownList *w = (ofxUIDropDownList *)  gui->getWidget("dropDown"+ofToString(i));
	ofxUITextInput *t = (ofxUITextInput *)  gui->getWidget("textField"+ofToString(i));
	ofxUIDropDownList *add = (ofxUIDropDownList *)  gui->getWidget("+"+ofToString(i));
	delete w;
	delete t;
	delete add;
	
	searchFields--;
}

//--------------------------------------------------------------
void guiPubMed::guiEvent(ofxUIEventArgs &e)
{

	string name = e.widget->getName();
	int kind = e.widget->getKind();
	cout << "got event from: " << name << endl;

	// check which searchfield has been pressed
	for (int i = 0 ; i<=searchFields; i++) {
		
		//---------------------------------------------
		if(name == "dropDown"+ofToString(i))
		{
			ofxUIDropDownList *dropDown = (ofxUIDropDownList *) e.widget;
			vector <int> i = dropDown->getSelectedIndeces();
			//TEST
			//cout << "ITEM SELECTED: " << elabel->getLabel() << endl;
		}
		
		//---------------------------------------------
		else if(name == "textField"+ofToString(i))
		{
			ofxUITextInput *t = (ofxUITextInput *) e.widget;
			t->setAutoClear(true);
			if(t->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER){
				cout << "ON ENTER: ";
				//            ofUnregisterKeyEvents((testApp*)this);
			
			}else if(t->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS){
				cout << "ON FOCUS: ";
			
			}else if(t->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS){
				cout << "ON BLUR: ";
				//            ofRegisterKeyEvents(this);
			}
			
			string output = t->getTextString();
			cout << output << endl;
		}
		
		//---------------------------------------------
		else if(name == "+"+ofToString(i))
		{
			cout << "*******************************"<< endl;
			ofxUIDropDownList *add = (ofxUIDropDownList *) e.widget;
			
			// get the current selection on the Add dropdown
			vector <int> current =	add->getSelectedIndeces();
			cout <<"current size"<< current.size()<< endl;
			for (int j= 0; j<current.size(); j++) {
				cout <<"current j"<< current[j]<< endl;
				
				if( current[0] == 0 ){
					cout << "add search field! " << endl;
					addSearchField();
//					add->setLabelText("-");
				}else if(current[0] == 1){
					cout << "or" << endl;
					addSearchField();
//					add->setLabelText("-");
				}else if(current[0] == 2){
					cout << "not" << endl;
					addSearchField();
//					add->setLabelText("-");
				}else if(current[0] == 3){
					cout << "-" << endl;
//					removeSearchField();
//					add->setLabelText("+");
				}
			}
		}
	}// end for
	cout << ".." << endl;
}


//--------------------------------------------------------------
void guiPubMed::keyPressed(int key){
	
    //Direct Request for Test and apply with RETURN
    if(key == 'l'){
		cout << "pressed l" << endl;
		addSearchField();
    }
    
}