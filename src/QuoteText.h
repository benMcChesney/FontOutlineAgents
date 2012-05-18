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
#include "AgentEvent.h"


class QuoteText
{
    public :
        
    QuoteText ( ) { }
    
        
    void setup ( string fontPath , int fontSize ) ;
    ofPoint getPointByChar( int charIndex ) ;       //Get x , y of a character
    void addLine ( string line ) ;                  //add line
    
    ofRectangle normalizeRectangle ( ofRectangle rect ,  bool verboseLog = false ) ;
    
    ofPoint getNextTarget ( ) ; 
    ofPoint startNewCharacter( ) ;
 
    int curLine ;                   //current line
    vector<string> textLines ;      //Text line by line
    int curTextIndex ;              //cur line index
    char letter;                    //current character

    ofTrueTypeFont font ;           //Font

    ofTTFCharacter character ;
    ofVec2f charTranslateOffset ;   //offset for all the characters from 0 , 0
    ofRectangle charBounds ;        //Bounds of the current character ( 0 , 0 , width , height ) 
    string text ;                   //current line text
    
    int targetIndex ;               //Target for the next index
    int nextIndex ;                 //next index
   // int curContour ;                //current contour of the letter
   // int curMaxContours ;            //total # of contours in character
    
    ofVec3f letterOffset ;          //offset for drawing the current letter

    //bool hasLooped ;                //for repeating over contour points to fully close shapes
    //int maxLoopIndex ;
    
    vector<ofVec2f> characterPoints ; 
    void collectAllPointsCharacter( )  ;
    
    bool bTeleportFlag ;
    ofVec2f getNextPathPoint( ) ; 
    
    void endPath ( ) ; 
    
    bool bFinished ;                //Finished drawing the quote
    
    
};


#endif
