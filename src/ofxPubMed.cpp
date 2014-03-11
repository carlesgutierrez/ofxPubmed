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
    sRelDate = "&reldate=";
    sDateType = "&datetype=";
    sRetMax = "&datetype=";
    sUseHist = "&usehistory=";
    
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
    myRequestData.clear();

	retAbstrack = "&rettype=abstract";
	myAbstrackData.clear();
	
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
    ofDrawBitmapString("Request= ", x, bottomRequest);
    ofDrawBitmapString(request, x + 80, bottomRequest); //myGuiPubMed.newEvent.query
    
    //Results json
    ofDrawBitmapString("[PMID] results:", rightArea - textwidth, y);

    //Draw results
    if(myRequestData["esearchresult"]["idlist"].size()<1)
    ofDrawBitmapString("No items founds", rightArea, y);
    
	//PubMed IDs found
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
	
	//Draw Download Xml resutls
	myAbstracts.draw(rightArea + textwidth, y);

}

//--------------------------------------------------------------
void ofxPubMed::keyPressed(int key){

	myGuiPubMed.keyPressed(key);
	myAbstracts.keyPressed(key); // press 's' for save xml file results
	
    //Direct Request for Test and apply with RETURN
    if(key == '1'){
        request = "http://www.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?pubmed&term=((Pei[Author])+AND+2006/12/01[Date%20-%20Create]%3A3000[Date%20-%20Create])+AND+(2001[Date%20-%20Create]%3A3000[Date%20-%20Create])";
    }
    else if(key == '2'){
        request = "http://www.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?pubmed&term=((Pei[Author])+AND+(\"2006/12/01\"[Date%20-%20Create]%3A\"3000\"[Date%20-%20Create]))+AND+(\"2001\"[Date%20-%20Create]%3A\"3000\"[Date%20-%20Create])";
		ofLogVerbose("guiPubMed") << "request: " << request << endl;
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
	
	if(key == 'R'){
		applyRequest(); // fast tests using 1,2,3... options
		//General Request is under construction
		bHitRequest = false;
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
        ofLogVerbose("guiPubMed") << myRequestData.getRawString(true) << endl;
        ofLogVerbose("guiPubMed") << "Num Pubmed Results= " << myRequestData["esearchresult"]["idlist"].size() << endl;
		
		if(myRequestData["esearchresult"]["idlist"].size() > 0)applyRequestAbstrack(myRequestData);

    }
    else {
        cout  << "Failed to parse JSON" << endl;
    }        
}

//--------------------------------------------------------------
void ofxPubMed::applyRequestAbstrack(ofxJSONElement jsRequested) {

	string fetchstring = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/efetch.fcgi?db=pubmed";
    string abstrackjson = "&rettype=abstract&retmode=xml";
	
	myPubIDs.clear();
	
	//Search pubmed ids
	for(int i=0; i< jsRequested["esearchresult"]["idlist"].size(); i++){
		std::string idpubmed  = jsRequested["esearchresult"]["idlist"][i].asString();
		myPubIDs.push_back(idpubmed);
	}
	
	//build request string
	string requestAbstracts = fetchstring + "&id=";
	if(myPubIDs.size()>0)requestAbstracts += myPubIDs[0];
	for (int i=1; i<myPubIDs.size(); i++) {
		requestAbstracts += ","+myPubIDs[i];
	}
	
	ofLogVerbose("guiPubMed") << "requestAbstracts= " << requestAbstracts << endl;
	
	if(myPubIDs.size()>0){
		
		// Now set and parse the results //TODO JSON not allowed // XML by default and textmode is return is json is requested
		int idrequest = myAbstracts.loadAbstracts(requestAbstracts + abstrackjson);
			
		ofLogVerbose("xmlAbstract") << cout << "xmlAbstract parsingSuccessful idrequest = " << idrequest << endl;
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
	myAbstracts.resetInfo();
	
    request += sBasicSearching + sDatabase; //+ sTerm
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


///////// old direct methods /////////////
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
///////////////////////

//listener from gui
//--------------------------------------------------------------
void ofxPubMed::listenerAddTextSearchBar(guiPubMedEvent & args) {
   
	reseteSearch();
	
	ofLogVerbose("GuiVerbose")<< "Addind and Apply query (by listener). Query: " << args.query << endl;
	addTagRequest(setformatForSearch(args.query));
	
	applyRequest();
	bHitRequest = true;
}

