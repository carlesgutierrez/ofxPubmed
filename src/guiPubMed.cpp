#include "guiPubMed.h"

//----------------------------------------------

guiPubMed::guiPubMed()
{
	
	//Load all my Tags in Vectors
    myVisibleSelItems.assign(myVisibleSelItemsArray, myVisibleSelItemsArray+MAXITEMS);
    myVisibleDatasSelItems.assign(myVisibleDatasSelItemsArray, myVisibleDatasSelItemsArray+MAXITEMSDATAS);
	
}

//----------------------------------------------
guiPubMed::~guiPubMed()
{
}

//--------------------------------------------------------------
void guiPubMed::exit() {
    delete pmGuiItems1;
	delete pmGuiItems2;
}

//--------------------------------------------------------------

void guiPubMed::setup(){

	int lineHeight = 35;
	int totalHeight = 500;
	
	// tabCanvas
	tabCanvasX		= 570;
	tabCanvasY		= 50;
	tabCanvasW		= 600;
	tabCanvasH		= lineHeight+OFX_UI_GLOBAL_SPACING_HEIGHT*2;
	toggleW			= 100;
	toggleH			= lineHeight;
	
	// Search field
	searchCanvasX	= tabCanvasX+1;
	searchCanvasY	= tabCanvasY+tabCanvasH-1;
	searchCanvasW	= tabCanvasW;
	searchCanvasH	= lineHeight+OFX_UI_GLOBAL_WIDGET_SPACING*2;

	searchFieldX	= 0;
	searchFieldY	= lineHeight;
	searchFieldW	= searchCanvasW-OFX_UI_GLOBAL_WIDGET_SPACING*2;
	searchFieldH	= lineHeight;
	
	// Tweets Canvas
	dim				= 50;
	sliderW			= 20;
	space			= OFX_UI_GLOBAL_WIDGET_SPACING;
	WidgetW			= tabCanvasW-sliderW-OFX_UI_GLOBAL_WIDGET_SPACING*2;
	bsnap			= false;
	
	tweetsCanvasX	= searchCanvasX;
	tweetsCanvasY	= searchCanvasY+searchCanvasH;
	tweetsCanvasW	= tabCanvasW-sliderW;
	tweetsCanvasH	= totalHeight+tabCanvasH;

	// postCanvas
	postCanvasX	= searchCanvasX;
	postCanvasY	= searchCanvasY;
	postCanvasW	= searchCanvasW;
	postCanvasH	= totalHeight+tabCanvasH+searchCanvasH;
	postFieldH	= lineHeight*2;

	//setup Search Bar GUi
	setupPubMedGUI();
	//	setupPubMedGuiDatas();
	
}

//--------------------------------------------------------------
void guiPubMed::setupPubMedGUI(){
	
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    int width = 200;
    int height = 200;
    
//	pmGuiItems1->setFont("fonts/Arial Unicode.ttf");
	
    pmGuiItems1 = new ofxUICanvas(xInit, 0, width, height);
	textInputCanvas->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
	
    for(int i = 0; i<myVisibleSelItems.size(); i++)
		cout << "myVisibleSelItems[i] = " << myVisibleSelItems[i] << endl;
	
    pmGuiItems1->addDropDownList("Select item option", myVisibleSelItems, width);
    pmGuiItems1->addDropDownList("Select data option", myVisibleDatasSelItems, width);
    
    // TODO BAD ACCESS al Text Input!!
//    pmGuiItems1->addTextInput("pmGui Text", "Search Text", width);
    
	pmGuiItems1->addTextInput("TEXT INPUT", "Type here ", searchFieldW, searchFieldH, searchFieldX, searchFieldY)->setAutoClear(true);

	
    pmGuiItems1->addToggle("Data Mode", false, 20, 20);
    pmGuiItems1->addToggle("Item Mode", false, 20, 20);
    
    pmGuiItems1->addToggle("Add new search", false, 20, 20); // if ad d is true, then set visible.
    
    ofAddListener(pmGuiItems1->newGUIEvent,this,&guiPubMed::guiEvent);
}


//--------------------------------------------------------------
void guiPubMed::setupPubMedGuiDatas(){
    //TODO PETANDO a la minima insercion....
    int width = 200;
    int height = 200;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING*2 + width;
	
    pmGuiItems2 = new ofxUICanvas( xInit, 0, width, height);
    
    pmGuiItems2->addDropDownList("Select item option", myVisibleSelItems, width);
    pmGuiItems2->addDropDownList("Select data option", myVisibleDatasSelItems, width);
    //pmGuiItems->addTextInput("pmGui Text", "Search Text", width); // TODO no funciona el Text Input!
    
    pmGuiItems2->addToggle("Data Mode", false, 20, 20);
    pmGuiItems2->addToggle("Item Mode", false, 20, 20);
    
    pmGuiItems2->addToggle("Add new search", false, 20, 20);
}

//--------------------------------------------------------------
void guiPubMed::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
	cout << "got event from: " << name << endl;
	
	if(name == "Select item option")
	{
		ofxUILabel *elabel = (ofxUILabel *) e.widget;
		//TEST
        //cout << "ITEM SELECTED: " << elabel->getLabel() << endl;
		
	}
    else if(name == "pmGui Text")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
        if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            cout << "ON ENTER: ";
            //            ofUnregisterKeyEvents((testApp*)this);
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: ";
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: ";
            //            ofRegisterKeyEvents(this);
        }
        string output = textinput->getTextString();
        cout << output << endl;
    }
    else if(name == "B1")
	{
        ofxUIButton *button = (ofxUIButton *) e.widget;
        cout << "value: " << button->getValue() << endl;
	}
	
	
	
}

