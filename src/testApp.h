#pragma once

#include "ofMain.h"
#include "Agent.h"
#include "ColorPool.h"
#include "QuoteText.h"
#include "QuotePath.h"
#include "ofxUI.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        //Agent agent ; 
        vector<Agent*> agents ; 
    
        QuoteText quote ;
        ColorPool colorPool ; 
    
        ofxUICanvas *gui;   
        void setupGUI( ) ; 
        void guiEvent(ofxUIEventArgs &e) ; 
    
        float a_maxSpeed ; 
        float a_maxForce ; 
        float a_targetBuffer ; 
        float a_pathSampling ; 
    
    
};
