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
    
    
        bool bRunAgents ; 
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
        float a_numAgents ; 
    
        void exportPDF( ) ;
        void exportPNG( ) ; 
    
        void keyPressed( int key ) ;
        void createNewAgent( ) ; 
    
        void resetAgents( ) ; 
    
        void saveProjectFile( ) ;
        void openProjectFile( ) ; 
    
        ofxXmlSettings projectXml ; 
    
        float a_rOffsetMaxSpeed ; 
        float a_rOffsetMaxTurn ; 
    
        ofTrueTypeFont instructionsFont ; 
    
        ofEasyCam cam ; 
    
    
};
