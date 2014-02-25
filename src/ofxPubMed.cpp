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
    sdataType= "&datetype=";
    sMindate = "&mindate=";
    sMaxdate = "&maxdate=";
    
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
    int rightArea = ofGetWidth()-500;
    
 
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("Hit RETURN to load Request ", x, bottomText);
    ofDrawBitmapString("The actual request is = ", x, bottomRequest-TEXTLINEHEIGHT);
    ofDrawBitmapString(request, x, bottomRequest);
    
    //Results json
    int textwidth = 130;
    ofDrawBitmapString("[PMID] results:", rightArea - textwidth, y);

    //Draw results
    if(myData["esearchresult"]["idlist"].size()<1)
    ofDrawBitmapString("No items founds", rightArea, y);
    
    for(int i=0; i< myData["esearchresult"]["idlist"].size(); i++)
	{
		std::string text  = myData["esearchresult"]["idlist"][i].asString();
		ofDrawBitmapString(text, rightArea, i*TEXTLINEHEIGHT+y);
	}
    
    //Draw errors
    vector <string> errors  = myData["esearchresult"]["errorlist"].getMemberNames();
    for(int i=0; i< errors.size(); i++)
	{
        
        if(i==0){
            int numfieldsnotfound = myData["esearchresult"]["errorlist"]["fieldsnotfound"].size();
            if(numfieldsnotfound)ofDrawBitmapString(errors[i], rightArea, y+(i+1)*TEXTLINEHEIGHT);
        }
        else{
            int numphrasesnotfound = myData["esearchresult"]["errorlist"]["phrasesnotfound"].size();
            if(numphrasesnotfound)ofDrawBitmapString(errors[i], rightArea, y+(i+1)*TEXTLINEHEIGHT);
        }
        
    }
    
    //Draw Warnings
    int accumPos = 0;
    vector <string> warnings  = myData["esearchresult"]["warninglist"].getMemberNames();
    for(int i=0; i< warnings.size(); i++)
	{
        int numwarnings = myData["esearchresult"]["warninglist"]["outputmessages"].size();
        if(i==0)accumPos += y + TEXTLINEHEIGHT + (i)*TEXTLINEHEIGHT;
        
        if(i==0){ // outputmessages
            int numOutputMessages = myData["esearchresult"]["warninglist"]["outputmessages"].size();
            if(numOutputMessages)ofDrawBitmapString(warnings[i], rightArea, accumPos);
            for (int j=0; j< numOutputMessages;j++) {
                accumPos += (j)*TEXTLINEHEIGHT;
                ofDrawBitmapString(myData["esearchresult"]["warninglist"]["outputmessages"][j].asString(), rightArea+200, accumPos);
            }
        }
        else if(i==1){ // phrasesignored
            accumPos += TEXTLINEHEIGHT;
            int numphrasesignored = myData["esearchresult"]["warninglist"]["phrasesignored"].size();
            if(numphrasesignored>0)ofDrawBitmapString(warnings[i], rightArea, accumPos);
            for (int j=0; j< numphrasesignored;j++) {
                
            }
        }
        else if(i==2){ // quotedphrasesnotfound
            accumPos += TEXTLINEHEIGHT;
            ofDrawBitmapString(warnings[i], rightArea, accumPos);
        }
        
    }
    
    if(!parsingSuccessful && bHitRequest)ofDrawBitmapString("Failed to parse JSON", rightArea - textwidth, y - TEXTLINEHEIGHT);

}

//--------------------------------------------------------------
void ofxPubMed::keyPressed(int key){

    if (key == ' ') {
        setBasiceSearchRequest();
    }
    
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
void ofxPubMed::setBasiceSearchRequest(){
    request.clear();
    request += sBaseRequest;
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
