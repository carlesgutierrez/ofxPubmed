//
//  ofxPubMed.cpp
//  httpRequestPubMed
//
//  Created by Carles on 19/02/14.
//
//

#include "ofxPubMed.h"

//--------------------------------------------------------------
void ofxPubMed::setup(){
    
    sBaseRequest = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/";
    sDatabase = "db=pubmed";
    sBasicSearching = "esearch.fcgi?";
  
    //search ID with Tags
    sBasicCitation = "ecitmatch.cgi?db=pubmed&rettype=xml&bdata=";
    sSpaceCit =  "%0D";
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
        request = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=%23hand+AND+sports+AND+water";
        
    }
    else if(key == '2'){
        request = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=%23hand[Author%20-%20Full]+AND+sports[Author%20-%20Full]+AND+water[Book]";
        
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
    //After this Ckeck: file.xml for results // todo : Draw result in the screen
    else if(key == OF_KEY_RETURN){
        applyRequest();
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
void ofxPubMed::exit() {
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
void ofxPubMed::addConsecutiveTagRequest(string newitem, string addtype){
    request += sAnd + newitem + addtype;
    cout << "Add consecutive TAG, now request is= " << request << endl;
}

//--------------------------------------------------------------
void ofxPubMed::setupPubMedGUI(){
   
    float dim = 16;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 255-xInit;
    int width = 200;
    
    //pmGuiItems.setFont("fonts/Arial Unicode.ttf");
    
   
    pmGuiItems.addWidgetDown(new ofxUILabel("DROP DOWN", OFX_UI_FONT_SMALL));
    for(int i = 0; i<myVisibleSelItems.size(); i++) cout << "myVisibleSelItems[i] = " << myVisibleSelItems[i] << endl;
    pmGuiItems.addDropDownList("SEARCH OPTIONS", myVisibleSelItems, width);
    
    pmGuiItems.setFontSize(OFX_UI_FONT_MEDIUM, 12);
    pmGuiItems.addTextInput("SELECT OPTION", "Input Text", length-xInit);
    //pmGuiItems.addTextInput("TEXT INPUT", "Input Text", length-xInit)->setAutoClear(false);
    
    ofAddListener(pmGuiItems.newGUIEvent,this,&ofxPubMed::guiEvent);
}

//--------------------------------------------------------------
void ofxPubMed::setupPubMedGuiDatas(){
    //TODO PETANDO a la minima insercion....
    
    int width = 200;
    float dim = 16;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING*2 + width;
    float length = 255-xInit;
    
    //pmGuiDatas.setFont("fonts/Arial Unicode.ttf");
    //pmGuiDatas.addTextInput("DD/MM/YY", "Input Text Data", length-xInit)->setAutoClear(true);
   // pmGuiDatas.addTextInput("DD MM YY", "Data Text", length-xInit);

   // pmGuiDatas.addWidgetRight(new ofxUILabel("DROP DOWN DATA", OFX_UI_FONT_SMALL));
    //for(int i = 0; i<myRequestSelItems(); i++) cout << "myRequestSelItems[i] = " << myRequestSelItems[i] << endl;
    //pmGuiDatas.addDropDownList("SEARCH DATA OPTIONS", myRequestSelItems, width);
    
   // ofAddListener(pmGuiDatas.newGUIEvent,this,&ofxPubMed::guiEvent);
}

//--------------------------------------------------------------
void ofxPubMed::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();
	int kind = e.widget->getKind();
	cout << "got event from: " << name << endl;
	
	if(name == "SEARCH OPTIONS")
	{
		ofxUILabel *elabel = (ofxUILabel *) e.widget;
		//TEST
        //cout << "ITEM SELECTED: " << elabel->getLabel() << endl;
	
	}
    else if(name == "TEXT INPUT")
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
	
	
	
}