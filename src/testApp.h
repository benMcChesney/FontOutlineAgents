#pragma once

#include "ofMain.h"
#include "Agent.h"
#include "ColorPool.h"
#include "QuoteText.h"
#include "QuotePath.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        //Agent agent ; 
        vector<Agent*> agents ; 
    
        QuoteText quote ;
   
        ColorPool colorPool ; 
        int screenshotCount ; 
    
    
};
