//
//  guiPubMedEvent.h
//  httpRequestPubMed
//
//  Created by carles on 26/02/14.
//
//

#pragma once

#include "ofMain.h"

class guiPubMedEvent : public ofEventArgs {
public:
	
	string query;
	
    static ofEvent <guiPubMedEvent> onUpdateSearch;
};
