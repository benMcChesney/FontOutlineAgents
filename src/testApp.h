#pragma once

#include "ofMain.h"
#include "Agent.h"
#include "ColorPool.h"
#include "QuoteText.h"
#include "QuotePath.h"
#include "ofxUI.h"
#include "HitRectImage.h"
#include "ofxTweenzor.h"
#include "RibbonAgent.h"
//s#include "ofxColorPicker.h"
#include "WordBlock.h"

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

        ofxUIDropDownList *ddl;
        ofxUICanvas *gui;

        void setupGUI( ) ;
        void guiEvent(ofxUIEventArgs &e) ;

        float a_maxSpeed ;
        float a_maxForce ;
        float a_targetBuffer ;
        float a_pathSampling ;
        float a_numAgents ;

        void exportPDF( ) ;

        void keyPressed( int key ) ;
        void createNewAgent( ) ;

        void resetAgents( ) ;

        void saveProjectFile( ) ;
        void openProjectFile( ) ;

        ofxXmlSettings projectXml ;

        float a_rOffsetMaxSpeed ;
        float a_rOffsetMaxTurn ;


        void mousePressed ( int x , int y , int button ) ;
        void mouseDragged ( int x , int y , int button ) ;
        void mouseReleased( int x , int y , int button ) ;

        void createNewWordBlock ( ) ;
        void initProject ( ) ;

        float canvasAlpha ;
        int fontSize ;

        string newTextLine ;
        float ySpacing ;

//        ofxColorPicker	colorPicker ;
        bool bDebugDraw ;

        float newFontSize ;

        void updateNewWordBlock ( string _word , float _fontSize ) ;


};
