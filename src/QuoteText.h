//
//  QuoteText.h
//  emptyExample
//
//  Created by Ben McChesney on 3/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_QuoteText_h
#define emptyExample_QuoteText_h

#include "ofMain.h"
#include "QuotePath.h"
#include "AgentEvent.h"
#include "WordBlock.h"


class QuoteText
{
    public :
        
    QuoteText ( ) { }
    
    void init ( ) ; 
    void setup ( string fontPath , int fontSize ) ;
    void addLine ( string line ) ;                  //add line
    
    ofRectangle normalizeRectangle ( ofRectangle rect ,  bool verboseLog = false ) ;
    
    ofPoint getNextTarget ( int pathIndex ) ; 
    ofPoint startNewCharacter( int pathIndex ) ;
    ofPoint getPointByChar( int charIndex , int pathIndex) ;       //Get x , y of a character
 
    vector<string> textLines ;      //Text line by line
    ofTrueTypeFont font ;           //Font
    string fontPath ; 
    float fontSize ; 
    
    
    vector<QuotePath*> quotePaths ; 
    void createQuotePath ( ) ; 
    
    QuotePath * getQuotePathAt ( int index ) ; 
    
    void resetQuotePaths() ; 
    
    ofVec2f charTranslateOffset ;   //offset for all the characters from 0 , 0 
    
    void clearQuotes ( ) ; 
    
    void debugDraw( ) ; 

    void addWordBlock ( string word , ofPoint position , int fontSize ) ; 
    vector<WordBlock*> wordBlocks ;
    
    void drawWordBlocks ( ) ; 
    
    void inputDown ( float x , float y ) ;
    void inputMove ( float x , float y ) ;
    void inputUp ( float x , float y ) ;
};


#endif
