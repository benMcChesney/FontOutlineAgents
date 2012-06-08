//
//  QuotePath.h
//  emptyExample
//
//  Created by Ben McChesney on 5/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_QuotePath_h
#define emptyExample_QuotePath_h

#include "ofMain.h"

class QuotePath
{
    public : 
        QuotePath( ) { } 
        
        void setup ( ) ;
    
        //have to track their own indicies inside characters
        int curLine ;                   //current line
        int curTextIndex ;              //current character index
        char letter;                    //current character
        
        vector<string> textLines ;      //Text line by line
        
        ofTrueTypeFont *font ;           //Font
        
        ofTTFCharacter character ;
        ofRectangle charBounds ;        //Bounds of the current character ( 0 , 0 , width , height ) 
        string text ;                   //current line text
        
        int targetIndex ;               //Target for the next index
        int nextIndex ;                 //next index
        ofVec3f letterOffset ;          //offset for drawing the current letter
        
        bool bHasLooped ;                //for repeating over contour points to fully close shapes
        int maxLoopIndex ;
    
        vector<ofVec2f> characterPoints ; //x , y of each character point
    
        bool bTeleportFlag ;
        bool bFinished ;                //Finished drawing the quote

        void endPath ( )  ; 
        void collectAllPointsCharacter( )  ;
    
        
        
};


#endif
