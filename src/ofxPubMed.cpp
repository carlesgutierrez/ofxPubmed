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
    
    //Search vars
    sRelDate = "&reldate=";     //60
    sDateType = "&datetype=";   //edat
    sRetMax = "&datetype=";     //100
    sUseHist = "&usehistory=";  //y
    
    //Html commands
    sSpaceCit =  "%0D";
    sSlash = "%2F";
    sQuotes = "%22";
    
    //Search Commands
    sSpaceWords = "|";
    sAnd = "+AND+";
    sOr = "+OR+";
    sNot = "+NOT+";
    sTerm = "&term=";
    
    //date Commmands
    sMindate = "&mindate=";
    sMaxdate = "&maxdate=";
    
    //search Document with Id
    sDocFetch = "efetch.fcgi?";
    sId = "&id=";

    
    //Load all my Tags in Vectors
    myVisibleSelItems.assign(myVisibleSelItemsArray, myVisibleSelItemsArray+MAXITEMS);
    myVisibleDatasSelItems.assign(myVisibleDatasSelItemsArray, myVisibleDatasSelItemsArray+MAXITEMSDATAS);
    //The same tags but with not spaces admited for html requests
    myRequestSelItems.assign(myRequestSelItemsArray, myRequestSelItemsArray+MAXITEMS);
    myRequestDataSelItems.assign(myRequestDataSelItemsArray, myRequestDataSelItemsArray+MAXITEMSDATAS);
    
    //Main control variables
    request = "empty";
    parsingSuccessful = false;
    bHitRequest = false;
    
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
    //setupPubMedGuiDatas();
}


//--------------------------------------------------------------
void ofxPubMed::draw(){
    
    int x = 20;
    int y = 40;
    int bottomText = ofGetHeight()-100;
    int bottomRequest = ofGetHeight()-50;
    int rightArea = ofGetWidth()-700;
    
 
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("Hit RETURN to load Request ", x, bottomText);
    ofDrawBitmapString("The actual request is = ", x, bottomRequest-TEXTLINEHEIGHT);
    ofDrawBitmapString(request, x, bottomRequest);
    
    //Results json
    int textwidth = 130;
    ofDrawBitmapString("[PMID] results:", rightArea - textwidth, y);

    //Draw results
    if(myData["esearchresult"]["idlist"].size()<1)
    ofDrawBitmapString("No results", rightArea, y);
    
    for(int i=0; i< myData["esearchresult"]["idlist"].size(); i++)
	{
		std::string text  = myData["esearchresult"]["idlist"][i].asString();
		ofDrawBitmapString(text, rightArea, i*TEXTLINEHEIGHT+y);
	}
    
    //Draw errors
    vector <string> errors  = myData["esearchresult"]["errorlist"].getMemberNames();
    for(int i=0; i< errors.size(); i++)
	{
        ofDrawBitmapString(errors[i], rightArea, y+(i+1)*TEXTLINEHEIGHT);
    }
    
    //Draw Warnings
    
    vector <string> warnings  = myData["esearchresult"]["warninglist"].getMemberNames();
    for(int i=0; i< warnings.size(); i++)
	{
        ofDrawBitmapString(warnings[i], rightArea, y+(i+1)*TEXTLINEHEIGHT);
        for (int j=0; j< myData["esearchresult"]["warninglist"]["outputmessages"].size();j++) {
            ofDrawBitmapString(myData["esearchresult"]["warninglist"]["outputmessages"][j].asString(), rightArea+200, (i+1)*TEXTLINEHEIGHT+y+(j)*TEXTLINEHEIGHT);
        }
    }
    
    /*
    "warninglist" : {
        "outputmessages" : [
                            "Range operator ':' not supported in field [All Fields]. Search terms that include a colon must be enclosed in double quotes.",
                            "No items found."
                            ],
        "phrasesignored" : [],
        "quotedphrasesnotfound" : []
    }*/
    
    if(!parsingSuccessful && bHitRequest)ofDrawBitmapString("Failed to parse JSON", rightArea - textwidth, y - TEXTLINEHEIGHT);

}

//--------------------------------------------------------------
void ofxPubMed::keyPressed(int key){

    
    //Direct Request for Test and apply with RETURN
    if(key == '1'){
        request = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=cancer&datetype=edat&mindate=2011&maxdate=2012";
    }
    else if(key == '2'){
        request = "http://www.ncbi.nlm.nih.gov/pubmed?term=%28%221991%2F02%2F21%22[Date%20-%20Completion]%20%3A%20%223000%22[Date%20-%20Completion]%29";
    }
    else if(key == '3'){
        request = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=%23hand[All%20Fields]+AND+sports[All%20Fields]+AND+water[All Fields]";
    }
    
    //Progressive Request
    // Hit 4 then 5 .. and finallt apply with RETURN
    else if(key == '4'){
        //starteSearchRequest("aspirin hart attack prevention", "[All%20Fields]");
        starteSearchRequest("aspirin", "[All%20Fields]");
    }
    else if(key == '5'){
        addANDSimpleTagRequest("exercise sports", "[All%20Fields]");
    }
    else if(key == '6'){
        addORSimpleTagRequest("high performance", "[All%20Fields]");
    }
    else if(key == '7'){
        addDataTagRequest("1991/10/20","present", "[pDate]");
    }
    else if(key == '8'){
        addDataTagRequest("1991","2014", "[All%20Fields]");
    }
    
    //General Request is under construction
    bHitRequest = false;
    
    //Apply request Type
    //Add Json request
    if(key == OF_KEY_RETURN){
        applyRequest();
        bHitRequest = true;
    }

    //Reset actual request
    if(key == 127)request="";
}


//--------------------------------------------------------------
void ofxPubMed::applyRequest() {
    
    myData.clear();
    
    // Now parse the JSON
    parsingSuccessful = myData.open(request+"&retmode=json");
    
    if (parsingSuccessful) {
        cout << myData.getRawString(true) << endl;
        cout << "esearchresult size= " << myData["esearchresult"].size() << endl;

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
string ofxPubMed::setformatForSearch(string text){
    std::replace( text.begin(), text.end(), ' ', '|');
    return text;
}

//--------------------------------------------------------------
void ofxPubMed::starteSearchRequest(string item, string addtype){
    
    request.clear();
    request = sBaseRequest + sBasicSearching + sDatabase +
    sTerm + setformatForSearch(item) + addtype;
    
    //example
    //http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=climb[All Fields] AND strech[All Fields]
}

//--------------------------------------------------------------
void ofxPubMed::addANDSimpleTagRequest(string newitem, string addtype){
    request += sAnd + setformatForSearch(newitem) + addtype;
    cout << "Add AND simple TAG, now request is= " << request << endl;
}

//--------------------------------------------------------------
void ofxPubMed::addORSimpleTagRequest(string newitem, string addtype){
    request += sOr + setformatForSearch(newitem) + addtype;
    cout << "Add OR simple TAG, now request is= " << request << endl;
}

//--------------------------------------------------------------
void ofxPubMed::addDataTagRequest(string from_data, string to_data, string addtype){
    //request += sQuotes + from_data + sQuotes + addtype + sQuotes+  to_data + sQuotes + addtype;
    request += sMindate + from_data + addtype + sMaxdate + to_data + addtype;
    
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
    
    // TODO BAD ACCESS al Text Input!!
    //pmGuiItems1->addTextInput("pmGui Text", "Search Text", width);
    
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