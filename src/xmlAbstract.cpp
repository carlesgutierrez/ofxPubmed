//
//  xmlAbstract.cpp
//  httpRequestPubMed
//
//  Created by carles on 03/03/14.
//
//

#include "xmlAbstract.h"

//--------------------------------------------------------------
xmlAbstract::xmlAbstract(){
	counterSavedXmls = 0;
	vPmids.reserve(20);
	vTitles.reserve(20);
	vAbstractTexts.reserve(20);
	vAuthors.reserve(20);
	vPublicationTypes.reserve(20);
}
//--------------------------------------------------------------
xmlAbstract::~xmlAbstract(){
	
}

//--------------------------------------------------------------
void xmlAbstract::setup(){

}

//--------------------------------------------------------------
void xmlAbstract::registerURL(){
	ofRegisterURLNotification(this);
}

//--------------------------------------------------------------
void xmlAbstract::unRegisterURL(){
	ofUnregisterURLNotification(this);
}

//--------------------------------------------------------------
void xmlAbstract::update(){}

//--------------------------------------------------------------
void xmlAbstract::draw(int x, int y){
	
	int namelegnth = 130;
	int incrementline = 24; //TEXTLINEHEIGHT 24
	int accumtext = 0;
	
	for(int i=0; i< numIds; i++){
		ofDrawBitmapString("Abstracts["+ ofToString(i,0)+ "]", x, y+accumtext);
		ofDrawBitmapString(vAbstractTexts[i], x + namelegnth, y+accumtext);
		accumtext += incrementline;
	}
	
	
	//Move fordware reward from ids results
	
	//settings.pushTag("positions");
	
	//Get string text in FTGL
	
	//Draw Texts in text canvas of size of Main window.
	
}

//-------------------------------------------------------
void xmlAbstract::saveXml(){
	//string filename = "file"+ofToString(counterSavedXmls,0)+".xml";
    string filename = "file.xml";
	myxml.saveFile(filename);
	counterSavedXmls++;
}

//--------------------------------------------------------------
int xmlAbstract::loadAbstracts(string request){
		
	myxml.clear(); // Clear results
	
	ofRegisterURLNotification(this); // init URL callbacks
	
	ofLogVerbose("xmlAbstract") << "request for loadAbstracts= " << request << endl;
	ofLoadURLAsync(request, "async_req");
	int id = myxml.loadFromBuffer(request);
	return(id);
}

//--------------------------------------------------------------
int xmlAbstract::getNumAbstractsAvaible(ofxXmlSettings myxml){
	return numIds;
}

//--------------------------------------------------------------
void xmlAbstract::resetInfo(){
	numIds = 0;
	vTitles.clear();
	vAbstractTexts.clear();
	vPmids.clear();
	vAuthors.clear();
	vPublicationTypes.clear();
}

//--------------------------------------------------------------
void xmlAbstract::getInfoAbstracts(ofxXmlSettings myxml){
	
	//reset last values
	resetInfo();
	
	myxml.pushTag("PubmedArticleSet"); //1
	  
	numIds = myxml.getNumTags("PubmedArticle"); //save numIds (num of articles) founds
	
	for(int i = 0; i < numIds; i++){
		
		myxml.pushTag("PubmedArticle", i); //2
		myxml.pushTag("MedlineCitation"); //3
		
		//myxml.pushTag("Article PubModel=\"Print-Electronic\"");
		myxml.pushTag("Article"); //4
						
		//Title
			string sArticleTitle = myxml.getValue("ArticleTitle", "default");
			vTitles.push_back(sArticleTitle);
			
			//Authors
		
		//AbstractText
		myxml.pushTag("Abstract"); //5
		string sArticleAbstrack = myxml.getValue("AbstractText", "default");
		vAbstractTexts.push_back(sArticleAbstrack);
		
		myxml.popTag();//5
		myxml.popTag();//4
		myxml.popTag();//3
		myxml.popTag();//2
		
	}
	
	myxml.popTag();//1
	
	ofLogVerbose("xmlAbstract= ") << numIds << endl;

}

//--------------------------------------------------------------
void xmlAbstract::urlResponse(ofHttpResponse & response) {
    if (response.status==200 && response.request.name == "async_req") {
        myxml.loadFromBuffer(response.data.getBinaryBuffer());
        bLoading = false;
		saveXml();//save results with an active counter file0, file1, file2...
		
		getInfoAbstracts(myxml);

    } else {
		ofLogVerbose("xmlAbstract") << "load my xmlAbstracts" << endl;
		ofLogVerbose("xmlAbstract") << response.status << " " << response.error << endl;
		if (response.status != -1) bLoading = false;
    }
	
	ofUnregisterURLNotification(this);
}