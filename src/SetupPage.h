//
//  SplashPage.h
//  emptyExample
//
//  Created by Ben McChesney on 6/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_setupPage_h
#define emptyExample_setupPage_h


#include "ofMain.h"
#include "CorePage.h"
#include "HitRectImage.h"

class SetupPage : public CorePage
{
    
    
public:
    SetupPage ( ) 
    {
        CorePage::CorePage( ) ; 
    } 
    
    ofTrueTypeFont instructionsFont ; 
    
    HitRectImage loadFontBtn ;
    HitRectImage addLineBtn ;
    HitRectImage finishSetupBtn ;
    
    int fontSize ;
    
    
    virtual void setup ( )
    {
        bounds = ofRectangle( 0 , 0, ofGetWidth() , ofGetHeight() ) ; 
        color = ofColor( ofRandom( 255 ) , ofRandom( 255 ) , ofRandom( 255 ) ) ; 
        ofPoint center = ofPoint ( ofGetWidth() / 2 , ofGetHeight() / 2 ) ; 
  
        loadFontBtn.setup ( "GUI/load_font_button.png" , center.x - 150 , center.y - 175 , true ) ;
        loadFontBtn.hitRect.width *= 0.5f ; 
        loadFontBtn.hitRect.height *= 0.5f ; 
        
        addLineBtn.setup( "GUI/add_text_line.png" ,center.x - 240 , center.y + 35 , true )  ;  
        
        finishSetupBtn.setup( "GUI/finish_setup_button.png" ,center.x , center.y + 300 , true )  ;   
        
        instructionsFont.loadFont("GUI/NewMedia Fett.ttf", 16 ) ; 
        fontSize = 14 ; 
    } 
    
    virtual void keyPressed ( int key ) 
    {
        switch ( key ) 
        {
                //right
            case 356 :
                if ( fontSize > 0 ) 
                    fontSize-- ; 
                break ; 
                //left
            case 358 :
                fontSize += 1 ; 
                break ; 
                
            /*    
            case 127 : 
                //st = myString.substr(0, myString.size()-1);
                if ( newTextLine.size() > 0 ) 
                    newTextLine = newTextLine.substr( 0 , newTextLine.size()-1 ) ; 
                break ; 
           */     
        }
        
       // if ( key != 127 && newTextLine.size() < 40 )
       //     newTextLine += key ; 

    }
    virtual void update ( ) { } 
    virtual void draw ( ) 
    {
        ofSetColor( 255 , 255 , 255 ) ; 
        ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ; 
        
        ofPoint textStart = ofPoint ( loadFontBtn.hitRect.x + 250 , loadFontBtn.hitRect.y + 20 ) ; 
        
        ofColor titleBack = ofColor ( 225 , 225 , 225 ) ; 
        ofColor titleText = ofColor ( 65 , 65 , 65 ) ; 
        
        ofColor pathBack = ofColor ( 255 , 255 , 255 ) ; 
        ofColor pathText = ofColor( 20 , 20 , 20 ) ; 
        
        //Draw Font PATH Title
        ofRect( instructionsFont.getStringBoundingBox( "FONT PATH: " , textStart.x , textStart.y ) ) ; 
        instructionsFont.drawString( "FONT PATH: " , textStart.x , textStart.y ) ; 
        
        //Draw Font PATH value
    
      //  ofRect( instructionsFont.getStringBoundingBox( quote.fontPath , textStart.x , textStart.y + 40 ) ) ; 
    //    instructionsFont.drawString( quote.fontPath , textStart.x , textStart.y + 40 ) ;
        
        //Draw Font Size TITLE
        ofRect( instructionsFont.getStringBoundingBox( "FONT SIZE: " , textStart.x , textStart.y + 140 ) ) ; 
        instructionsFont.drawString( "FONT SIZE \n( right / left ) : " , textStart.x , textStart.y + 140 ) ; 
        
        //Draw Font Size VALUE
        ofRect( instructionsFont.getStringBoundingBox( "FONT SIZE: " , textStart.x , textStart.y + 200 ) ) ; 
    //    instructionsFont.drawString( ofToString( quote.fontSize ) , textStart.x , textStart.y + 200 ) ; 
        
        textStart.y = addLineBtn.hitRect.y + 35  ; 
        loadFontBtn.draw( ) ;
     //   fontSize = quote.fontSize ;
        
     //   int numLines = quote.textLines.size() ; 
    //    cout << "numLines " << numLines << endl ; 
    //    float ySpacing  = 20.0f ; 
    //    float totalHeight = numLines * ySpacing ;
        
        ofPushMatrix( ) ;
        //ofTranslate( 0 , totalHeight ) ; 
        addLineBtn.draw( )  ;
        ofPopMatrix( ) ; 
        /*
        for ( int i = 0 ; i < numLines ; i++ ) 
        {
            ofSetColor( 20 , 20 , 20 ) ;
            cout << "line : " << i << " is : " << quote.textLines[i] << endl ; 
            instructionsFont.drawString( quote.textLines[i] , addLineBtn.hitRect.x + addLineBtn.hitRect.width + 50 ,  textStart.y + (i) * ySpacing ); 
        }*/
        
        //ofSetColor( 255 , newProjectAlpha ) ; 
        finishSetupBtn.draw( )  ;
        
       // ofSetColor ( pathText , newProjectAlpha ) ; 
     //   instructionsFont.drawString( newTextLine , addLineBtn.hitRect.x + addLineBtn.hitRect.width + 50 ,  textStart.y + totalHeight ) ;
    }   
    
    virtual void input ( float x , float y ) 
    {
        if ( !bInput ) return ;
        
        if ( loadFontBtn.hitTest( x , y ) == true )
        {
            ofFileDialogResult ttfResult = ofSystemLoadDialog( "Open any TTF or OTF font" ) ; 
            string path = ttfResult.getPath() ; 
            int ttfIndex = path.find( ".ttf" ) ;
            int otfIndex = path.find( ".otf" ) ; 
            
            if ( ttfIndex > 0 || otfIndex > 0 ) 
            {
                cout << "valid ttf or otf file" << endl ; 
                int lastIndex = path.find_last_of("/") ; 
                string shortName = path.substr( lastIndex+1 ) ; 
            //    quote.fontPath = shortName ; //ofToDataPath( path )  ; 
                
            }
        }
        
        if ( addLineBtn.hitTest( x , y ) == true ) 
        {
          //  quote.addLine( newTextLine ) ; 
          //  newTextLine = "blank" ; 
            //Tweenzor::add( &addLineBtn.hitRect.y , addLineBtn.hitRect.y , addLineBtn.hitRect.y + ySpacing , 0.0f , 0.5f , EASE_OUT_QUAD ) ; 
        }
        
        if ( finishSetupBtn.hitTest( x , y ) )
        {
          //  quote.init ( ) ; 
          //  resetAgents() ; 
           // Tweenzor::add( &newProjectAlpha , newProjectAlpha  , 0.0f , 0.0f , 0.5f , EASE_OUT_QUAD ) ; 
          //  Tweenzor::add( &canvasAlpha , canvasAlpha , 255.0f , 0.5f , 0.5f , EASE_OUT_QUAD ) ;
           // gui->setVisible( true ) ; 
        }
        
        
    }
};


#endif
