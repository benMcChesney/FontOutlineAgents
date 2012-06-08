//
//  SplashPage.h
//  emptyExample
//
//  Created by Ben McChesney on 6/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_SplashPage_h
#define emptyExample_SplashPage_h


#include "ofMain.h"
#include "CorePage.h"
#include "HitRectImage.h"

class SplashPage : public CorePage
{

    
    public:
        SplashPage ( ) 
        {
            CorePage::CorePage( ) ; 
        } 
    
        float splashPageAlpha ; 
        
        HitRectImage newProjectBtn ; 
        HitRectImage loadProjectBtn ;
        
    
        virtual void setup ( )
        {
            bounds = ofRectangle( 0 , 0, ofGetWidth() , ofGetHeight() ) ; 
            color = ofColor( ofRandom( 255 ) , ofRandom( 255 ) , ofRandom( 255 ) ) ; 
            splashPageAlpha = 255.0f ; 
            ofPoint center = ofPoint ( ofGetWidth() / 2 , ofGetHeight() / 2 ) ; 
            newProjectBtn.setup( "GUI/new_button.png" ,center.x , center.y - 75 , true )  ; 
            loadProjectBtn.setup( "GUI/load_button.png" ,center.x , center.y + 75 , true )  ;
        } 
        
        virtual void update ( ) { } 
        virtual void draw ( ) 
        {
            
            
            ofPushMatrix() ; 
                ofTranslate( translation.x , translation.y ) ;
                ofSetColor( color ) ; 
                ofRect( bounds ) ;
            
               // if ( splashPageAlpha > 0.0f ) 
               // {
                    ofSetColor( 0 , 0 , 0, splashPageAlpha ) ; 
                    ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ;
                    
                    ofSetColor ( 255 , 255 , 255 , splashPageAlpha ) ; 
                    newProjectBtn.draw( ) ; 
                    loadProjectBtn.draw( ) ; 
               // }
            

            ofPopMatrix() ; 
        }   
    
        virtual void input ( float x , float y ) 
        {
            if ( !bInput ) return ;
            
            //if ( splashPageAlpha > 0.0f ) 
            //{
                if ( newProjectBtn.hitTest( x , y ) == true ) 
                {
                    cout << " NEW PROJECT!! " << endl ; 
                   // initProject() ; 
                    
                }
                else if ( loadProjectBtn.hitTest( x , y ) == true ) 
                {
                    cout << " OPENING PROJECT!" << endl ;
                    //openProjectFile() ;   
                }
            //}

        }
};


#endif
