//
//  ofxPubMed.cpp
//  httpRequestPubMed
//
//  Created by Carles on 19/02/14.
//
//

#include "ofxPubMed.h"

//--------------------------------------------------------------
ofxPubMed::ofxPubMed(){
    
    sBaseRequest = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/";
    sDatabase = "db=pubmed";
    sBasicSearching = "esearch.fcgi?";
    
    //search ID with Tags
    sBasicCitation = "ecitmatch.cgi?db=pubmed&rettype=xml&bdata=";
    
    //Html commands
    sSpaceCit =  "%0D";
    sSlash = "%2F";
    sQuotes = "%22";
    
    //Search Commands
    sSpaceWords = "|";
    sAnd = "+AND+";
    sOr = "+OR+";
    sTerm = "&term=";
    
    //search Document with Id
    sDocFetch = "efetch.fcgi?";
    sId = "&id=";
    
    //Load all my Tags in Vectors
    myVisibleSelItems.assign(myVisibleSelItemsArray, myVisibleSelItemsArray+MAXITEMS);
    myVisibleDatasSelItems.assign(myVisibleDatasSelItemsArray, myVisibleDatasSelItemsArray+MAXITEMSDATAS);
    //Used in request ( no spaces admited )
    myRequestSelItems.assign(myRequestSelItemsArray, myRequestSelItemsArray+MAXITEMS);
    myRequestDataSelItems.assign(myRequestDataSelItemsArray, myRequestDataSelItemsArray+MAXITEMSDATAS);
    
    //json
    myData.clear();
}
//--------------------------------------------------------------
ofxPubMed::~ofxPubMed(){
}

//--------------------------------------------------------------
void ofxPubMed::setup(){
    
 
    
    //setup Search Bar GUi
    setupPubMedGUI();
    setupPubMedGuiDatas();
    
}


//--------------------------------------------------------------
void ofxPubMed::draw(){
 
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("hit spacebar to load requested info", 10, ofGetHeight()-100);
    
    //json
    for(int i=0; i< myData["esearchresult"].size(); i++)
	{
		std::string text  = myData["esearchresult"]["idlist"][i].asString();
		ofDrawBitmapString(text, 20, i*24+40);
	}

}

//--------------------------------------------------------------
void ofxPubMed::keyPressed(int key){
    
   //After call this
    
    //Hardcode Request
    if(key == '1'){
        request = "http://www.ncbi.nlm.nih.gov/pubmed?term=(\"1991/02/21\"[Date - Completion] : \"3000[Date - Completion])\"";
    }
    else if(key == '2'){
        request = "http://www.ncbi.nlm.nih.gov/pubmed?term=%28%221991%2F02%2F21%22[Date%20-%20Completion]%20%3A%20%223000%22[Date%20-%20Completion]%29";
    }
    else if(key == '3'){
        request = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=%23hand[All%20Fields]+AND+sports[All%20Fields]+AND+water[All Fields]";
    }
    
    //Progressive request, First 4, then 5, then RETURN
    else if(key == '4'){
        starteSearchRequest("strech", "[All%20Fields]");
    }
    else if(key == '5'){
        addANDSimpleTagRequest("high%20performance", "[All%20Fields]");
    }
    else if(key == '6'){
        addORSimpleTagRequest("high%20performance", "[All%20Fields]");
    }
    else if(key == '6'){
        addDataTagRequest("1991/10/20","present", "[Date - Publication]");
    }
    else if(key == '7'){
        addDataTagRequest("1991/10/20","2014/02/21", "[Date - Publication]");
    }
    
    //After this Ckeck: file.xml for results // todo : Draw result in the screen
    else if(key == OF_KEY_RETURN){
        applyRequest();
    }
    else if(key == OF_KEY_DEL){
        applyDataRequest();
    }
    
}


//--------------------------------------------------------------
void ofxPubMed::applyRequest() {
    
    // Now parse the JSON
    bool parsingSuccessful = myData.open(request+"&retmode=json");
    
    if (parsingSuccessful) {
        cout << myData.getRawString(true) << endl;
    }
    else {
        cout  << "Failed to parse JSON" << endl;
    }
        
}

//--------------------------------------------------------------
void ofxPubMed::applyDataRequest() {
    
    // Now parse the JSON
    bool parsingSuccessful = myData.open(request);
    
    if (parsingSuccessful) {
        cout << myData.getRawString(true) << endl;
    }
    else {
        cout  << "Failed to parse JSON" << endl;
    }
    
}


//--------------------------------------------------------------
void ofxPubMed::exit() {
    delete pmGuiItems1;
	delete pmGuiItems2;
}


//--------------------------------------------------------------
void ofxPubMed::starteSearchRequest(string item, string addtype){
    
    request.clear();
    request = sBaseRequest + sBasicSearching + sDatabase +
    sTerm + item + addtype;
    
    //example
    //http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=climb[All Fields] AND strech[All Fields]
}

//--------------------------------------------------------------
void ofxPubMed::addANDSimpleTagRequest(string newitem, string addtype){
    request += sAnd + newitem + addtype;
    cout << "Add AND simple TAG, now request is= " << request << endl;
}

//--------------------------------------------------------------
void ofxPubMed::addORSimpleTagRequest(string newitem, string addtype){
    request += sOr + newitem + addtype;
    cout << "Add OR simple TAG, now request is= " << request << endl;
}

//--------------------------------------------------------------
void ofxPubMed::addDataTagRequest(string from_data, string to_data, string addtype){
    request += sQuotes + from_data + sQuotes + addtype + sQuotes+  to_data + sQuotes + addtype;
    cout << "Data TAG, now request is= " << request << endl;
}

//--------------------------------------------------------------
void ofxPubMed::addConsecutiveTagRequest(string newitem, string addtype){
    request += sAnd + newitem + addtype;
    cout << "Add consecutive TAG, now request is= " << request << endl;
}

//--------------------------------------------------------------
void ofxPubMed::setupPubMedGUI(){
   
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    int width = 200;
    int height = 200;
    //pmGuiItems.setFont("fonts/Arial Unicode.ttf");
   
    pmGuiItems1 = new ofxUICanvas(xInit, 0, width, height);

    for(int i = 0; i<myVisibleSelItems.size(); i++) cout << "myVisibleSelItems[i] = " << myVisibleSelItems[i] << endl;
   
    pmGuiItems1->addDropDownList("Select item option", myVisibleSelItems, width);
    pmGuiItems1->addDropDownList("Select data option", myVisibleDatasSelItems, width);
    //pmGuiItems->addTextInput("pmGui Text", "Search Text", width); // TODO no funciona el Text Input!
    
    pmGuiItems1->addToggle("Data Mode", false, 20, 20);
    pmGuiItems1->addToggle("Item Mode", false, 20, 20);
    
    pmGuiItems1->addToggle("Add new search", false, 20, 20); // if ad d is true, then set visible.
    
    ofAddListener(pmGuiItems1->newGUIEvent,this,&ofxPubMed::guiEvent);
}

//--------------------------------------------------------------
void ofxPubMed::setupPubMedGuiDatas(){
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
void ofxPubMed::guiEvent(ofxUIEventArgs &e)
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