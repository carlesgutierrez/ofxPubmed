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
    sSpaceCit = "%0D";
    sSlash = "%2F";
    sQuotes = "%22";
    
    //Search Commands
    sSpaceWords = "|";
    sAnd = "+AND+";
    sOr = "+OR+";
    sNot = "+NOT+";
    sTerm = "&term=";
    
    //date Commmands
    sdataType= "&datetype=";
    sMindate = "&mindate=";
    sMaxdate = "&maxdate=";
    
    //search Document with Id
    sDocFetch = "efetch.fcgi?";
    sId = "&id=";
    
    //Main control variables
    request = "empty";
    parsingSuccessful = false;
    bHitRequest = false;
    
    //json
	retMode = "&retmode=json";
	retAbstrack = "&rettype=abstract";
    myRequestData.clear();
	//myAbstrData
	
	//event
	ofAddListener(guiPubMedEvent::onUpdateSearch, this, &ofxPubMed::listenerAddTextSearchBar);
	
}
//--------------------------------------------------------------
ofxPubMed::~ofxPubMed(){
	
}

//--------------------------------------------------------------
void ofxPubMed::setup(){

}
//--------------------------------------------------------------
void ofxPubMed::update(){
	 myGuiPubMed.update();
}
//--------------------------------------------------------------
void ofxPubMed::draw(){
    
    int x = 20;
    int y = 40;
	
    int bottomText = ofGetHeight()-ofGetHeight()*0.2;
    int bottomRequest = ofGetHeight()-ofGetHeight()*0.1;
    int rightArea = ofGetWidth()*0.2;
	int textwidth = 130;
	
	int xwarnings = 150;
	int tabwarnings = 150;
	int accumPos = 100;
	
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("Hit RETURN to load Request ", x, bottomText);
    ofDrawBitmapString("The actual request is = ", x, bottomRequest-TEXTLINEHEIGHT);
    ofDrawBitmapString(myGuiPubMed.newEvent.query, x, bottomRequest);
    
    //Results json
   
    ofDrawBitmapString("[PMID] results:", rightArea - textwidth, y);

    //Draw results
    if(myRequestData["esearchresult"]["idlist"].size()<1)
    ofDrawBitmapString("No items founds", rightArea, y);
    
    for(int i=0; i< myRequestData["esearchresult"]["idlist"].size(); i++)
	{
		std::string text  = myRequestData["esearchresult"]["idlist"][i].asString();
		ofDrawBitmapString(text, rightArea, i*TEXTLINEHEIGHT+y);
	}
    
    //Draw errors
    vector <string> errors  = myRequestData["esearchresult"]["errorlist"].getMemberNames();
    for(int i=0; i< errors.size(); i++)
	{
        
        if(i==0){
            int numfieldsnotfound = myRequestData["esearchresult"]["errorlist"]["fieldsnotfound"].size();
            if(numfieldsnotfound)ofDrawBitmapString(errors[i]+":", rightArea+xwarnings, y+(i+1)*TEXTLINEHEIGHT);
        }
        else{
            int numphrasesnotfound = myRequestData["esearchresult"]["errorlist"]["phrasesnotfound"].size();
            if(numphrasesnotfound)ofDrawBitmapString(errors[i]+":", rightArea+xwarnings, y+(i+1)*TEXTLINEHEIGHT);
        }
        
    }
    
    //Draw Warnings
    vector <string> warnings  = myRequestData["esearchresult"]["warninglist"].getMemberNames();
    for(int i=0; i< warnings.size(); i++)
	{
        int numwarnings = myRequestData["esearchresult"]["warninglist"]["outputmessages"].size();
        if(i==0)accumPos += y + TEXTLINEHEIGHT + (i)*TEXTLINEHEIGHT;
        
        if(i==0){ // outputmessages
            int numOutputMessages = myRequestData["esearchresult"]["warninglist"]["outputmessages"].size();
            if(numOutputMessages)ofDrawBitmapString(warnings[i]+":", rightArea+xwarnings, accumPos);
            for (int j=0; j< numOutputMessages;j++) {
                accumPos += (j)*TEXTLINEHEIGHT;
                ofDrawBitmapString(myRequestData["esearchresult"]["warninglist"]["outputmessages"][j].asString(), rightArea+xwarnings+tabwarnings, accumPos);
            }
        }
        else if(i==1){ // phrasesignored
            accumPos += TEXTLINEHEIGHT;
            int numphrasesignored = myRequestData["esearchresult"]["warninglist"]["phrasesignored"].size();
            if(numphrasesignored>0)ofDrawBitmapString(warnings[i]+":", rightArea+xwarnings, accumPos);
            for (int j=0; j< numphrasesignored;j++) {
				accumPos += (j)*TEXTLINEHEIGHT;
                ofDrawBitmapString(myRequestData["esearchresult"]["warninglist"]["phrasesignored"][j].asString(), rightArea+xwarnings+tabwarnings, accumPos);
            }
        }
        else if(i==2){ // quotedphrasesnotfound
            accumPos += TEXTLINEHEIGHT;
            ofDrawBitmapString(warnings[i]+":", rightArea+xwarnings, accumPos);
        }
        
    }
    
    if(!parsingSuccessful && bHitRequest)ofDrawBitmapString("Failed to parse JSON", rightArea - textwidth, y - TEXTLINEHEIGHT);

}

//--------------------------------------------------------------
void ofxPubMed::keyPressed(int key){

	myGuiPubMed.keyPressed(key);
	
    //Direct Request for Test and apply with RETURN
    if(key == '1'){
        request = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=cancer&datetype=edat&mindate=2011&maxdate=2012";
    }
    else if(key == '2'){
        request = "http://www.ncbi.nlm.nih.gov/pubmed&term=aspirine&mindate=1991/02/21[pDate]&maxdate=2013/02/21[pDate]";
    }
    else if(key == '3'){
        request = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=cancer&reldate=60&datetype=edat&retmax=100&usehistory=y";
    }
    
    //Progressive Request
    // Hit 4 then 5 .. and finallt apply with RETURN
    else if(key == '4'){
        starteSearchRequestWithItem("aspirin hart attack prevention", "[All%20Fields]");
    }
    else if(key == '5'){
        addRelDateRequest(sRelDate, "60");
        addDataTypeRequest("EDAT");
    }
    else if(key == '6'){
        addMinMaxDataSearchRequest("1991/02/12","[DA]","2013/12/30","[DCOM]");
    }
    else if(key == '7'){
        addORSimpleTagRequest("high performance", "[All%20Fields]");
    }
    else if(key == '8'){
        addDataTagRequest("1991/10/20","present", "[pDate]");
    }
    else if(key == '9'){
        addDataTagRequest("1991","2014", "[All%20Fields]");
    }
    
    //General Request is under construction
    bHitRequest = false;
    
    //Apply request Type
    //Add Json request
    if(key == OF_KEY_RETURN){
		//apply manual request?
    }

    //Reset actual request
    if(key == 127)request="";
}


//--------------------------------------------------------------
void ofxPubMed::applyRequest() {
    
    myRequestData.clear();
    
    // Now parse the JSON
    parsingSuccessful = myRequestData.open(request+retMode);
    
    if (parsingSuccessful) {
        cout << myRequestData.getRawString(true) << endl;
        cout << "esearchresult size= " << myRequestData["esearchresult"].size() << endl;

    }
    else {
        cout  << "Failed to parse JSON" << endl;
    }        
}

//--------------------------------------------------------------
void ofxPubMed::resetBase(){
    request.clear();
    request += sBaseRequest;
}

//--------------------------------------------------------------
void ofxPubMed::reseteSearch(){
	resetBase();
    request += sBasicSearching + sDatabase + sTerm;
}

//--------------------------------------------------------------
string ofxPubMed::setformatForSearch(string text){
    std::replace( text.begin(), text.end(), ' ', '|');
    return text;
}
//--------------------------------------------------------------
void ofxPubMed::changeBasicSearchRequest(string basicSearch){
    sBaseRequest = basicSearch;
}

//--------------------------------------------------------------
void ofxPubMed::starteSearchRequestWithItem(string item, string addtype){
    
    request.clear();
    request = sBaseRequest + sBasicSearching + sDatabase +
    sTerm + setformatForSearch(item) + addtype;
    
    //example
    //http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=climb[All Fields] AND strech[All Fields]
}
//--------------------------------------------------------------
void ofxPubMed::addTagRequest(string query){
    request += query;
    cout << "Add TAG Request, now request is= " << request << endl;
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
void ofxPubMed::addDataTypeRequest(string datatype){
    request += sdataType + datatype;
}
                                   
//--------------------------------------------------------------
void ofxPubMed::addRelDateRequest(string reldate, string days){
   request += reldate + days;
}

//--------------------------------------------------------------
void ofxPubMed::addMinMaxDataSearchRequest(string datemin, string typedatemin, string datemax, string typedatemax){
    request += datemin + typedatemin + datemax + typedatemax;
}

//listener from gui
//--------------------------------------------------------------
void ofxPubMed::listenerAddTextSearchBar(guiPubMedEvent & args) {
   
	reseteSearch();
	
	ofLogVerbose("GuiVerbose")<< "Addind and Apply query (by listener). Query: " << args.query << endl;
	addTagRequest(setformatForSearch(args.query));
	
	applyRequest();
	bHitRequest = true;
}

