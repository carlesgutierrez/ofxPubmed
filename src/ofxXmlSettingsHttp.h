//
//  ofxXmlSettingsHttp.h
//  httpRequestPubMed
//
//  Created by Carles on 17/02/14.
//
//

#ifndef __httpRequestPubMed__ofxXmlSettingsHttp__
#define __httpRequestPubMed__ofxXmlSettingsHttp__

#include "ofxXmlSettings.h"

#include <iostream>

class ofxXmlSettingsHttp {

public:

    ofxXmlSettingsHttp();
    ~ofxXmlSettingsHttp();
    
    void loadfromHttp(string url);
    
    void clear();
    
    ofxXmlSettings* getXml();
    void saveXml();
    
    bool loadXml(ofxXmlSettings & xml, string fileName);
    
    bool loading;

private:   
	
	ofxXmlSettings myxml;
};

#endif /* defined(__httpRequestPubMed__ofxXmlSettingsHttp__) */
