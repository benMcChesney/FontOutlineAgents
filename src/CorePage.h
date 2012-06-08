//
//  CorePage.h
//  emptyExample
//
//  Created by Ben McChesney on 6/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_CorePage_h
#define emptyExample_CorePage_h

class CorePage
{
    public :
        CorePage ( ) 
        { 
            bInput = false ; 
            translation = ofPoint( ) ; 
        } 
    
        virtual void setup ( )
        {
            bounds = ofRectangle( 0 , 0, ofGetWidth() , ofGetHeight() ) ; 
            color = ofColor( ofRandom( 255 ) , ofRandom( 255 ) , ofRandom( 255 ) ) ; 
            
        } 
    
        virtual void update ( ) { } 
        virtual void draw ( ) 
        {
            ofPushMatrix() ; 
                ofTranslate( translation.x , translation.y ) ;
                ofSetColor( color ) ; 
                ofRect( bounds ) ;
            ofPopMatrix() ; 
        } 
    
        virtual void input( float x , float y ) { } 
    
    virtual void keyPressed ( int key ) { } 
        
        ofPoint translation ; 
        bool bInput ;
    
        ofRectangle bounds ;
        ofColor color ;
};


#endif
