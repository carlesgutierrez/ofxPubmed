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
    sTerm = "&term=";
    
    //search Document with Id
    sDocFetch = "efetch.fcgi?";
    sId = "&id=";

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

}


//--------------------------------------------------------------
void ofxPubMed::draw(){
    
    int x = 20;
    int y = 40;
    int bottomText = ofGetHeight()-100;
    int bottomRequest = ofGetHeight()-50;
    int rightArea = ofGetWidth()-400;
    
 
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
        starteSearchRequest("strech", "[All%20Fields]");
    }
    else if(key == '5'){
        addANDSimpleTagRequest("high%20performance", "[All%20Fields]");
    }
    else if(key == '6'){
        addORSimpleTagRequest("high%20performance", "[All%20Fields]");
    }
    else if(key == '7'){
        addDataTagRequest("1991/10/20","present", "[pDate]");
    }
    else if(key == '8'){
        addDataTagRequest("1991/10/20","2014/02/21", "[pDate]");
    }
    
    //General Request is under construction
    bHitRequest = false;
    
    //Apply request Type
    //Add Json request
    if(key == OF_KEY_RETURN){
        applyRequest();
        bHitRequest = true;
    }
    
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
