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
    
	loading=false;
	ofRegisterURLNotification(this);
    
    sBaseRequest = "http://eutils.ncbi.nlm.nih.gov/entrez/eutils/";
    sDatabase = "db=pubmed";
    sBasicSearching = "esearch.fcgi?";
    sBasicCitation = "ecitmatch.cgi?db=pubmed&rettype=xml&bdata=";
    sSpaceCit =  "%0D";
    sSpaceWords = "|";
    sAnd = "+AND+";
    sTerm = "&term=";
}


//--------------------------------------------------------------
void ofxPubMed::draw(){
 
    ofSetColor(0, 0, 0);
    ofDrawBitmapString("hit spacebar to load xml from web", 10, ofGetHeight()/2);
    if(loading)
    ofDrawBitmapString("loading...", 10, ofGetHeight()+20);

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
void ofxPubMed::applyRequest(string myPersonalRequest){
    
    ofLoadURLAsync(request, myPersonalRequest);
    cout << "applyRequest = " << request << endl;
    
}

//--------------------------------------------------------------
void ofxPubMed::addSimpleTagRequest(string newitem, string addtype){
    request += sAnd + newitem + addtype;
    cout << "Add simple TAG, now request is= " << request << endl;
}
//--------------------------------------------------------------
void ofxPubMed::addConsecutiveTagRequest(string newitem, string addtype){
    request += sAnd + newitem + addtype;
    cout << "Add consecutive TAG, now request is= " << request << endl;
}

//--------------------------------------------------------------
void ofxPubMed::urlResponse(ofHttpResponse & response){
	
    if(response.status==200 && response.request.name == "myRequest_1"){
		//img.loadImage(response.data);
		xmlFromHttp.loadfromHttp(response.data.getBinaryBuffer());
		//save xml
        xmlFromHttp.saveXml();
		loading=false;
	}else{
		cout << response.status << " " << response.error << endl;
		if(response.status!=-1) loading=false;
	}
}

/*
 //--------------------------------------------------------------
 string ofApp::buildAnyRawStrRequest(){
 
 }
 
 //--------------------------------------------------------------
 string ofApp::SearchPubMedCitationData(string inuts, string ){
 
 }
 */

//--------------------------------------------------------------
void ofxPubMed::keyPressed(int key){
    
   //After call this
    
    xmlFromHttp.clear();
	
    //Hardcode Request
    if(key == '1'){
        ofLoadURLAsync("http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=%23hand+AND+sports+AND+water","myRequest_1");
    }
    else if(key == '2'){
        ofLoadURLAsync("http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=%23hand[Author%20-%20Full]+AND+sports[Author%20-%20Full]+AND+water[Book]","myRequest_1");
    }
    else if(key == '3'){
        ofLoadURLAsync("http://eutils.ncbi.nlm.nih.gov/entrez/eutils/esearch.fcgi?db=pubmed&term=%23hand[All%20Fields]+AND+sports[All%20Fields]+AND+water[All Fields]","myRequest_1");
    }
    
    //Progressive request, First 4, then 5, then RETURN
    else if(key == '4'){
        starteSearchRequest("ultimate", "[All%20Fields]");
    }
    else if(key == '5'){
        addSimpleTagRequest("sport", "[All%20Fields]");
    }
    //After this Ckeck: file.xml for results // todo : Draw result in the screen
    else if(key == OF_KEY_RETURN){
        applyRequest("myRequest_1");
    }
    
    loading =true;
}

//--------------------------------------------------------------
void ofxPubMed::exit() {
	ofUnregisterURLNotification(this);
}
