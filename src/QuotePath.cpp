//
//  QuotePath.cpp
//  emptyExample
//
//  Created by Ben McChesney on 5/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "QuotePath.h"
#include <iostream>

void QuotePath::setup( ) 
{
    curLine = 0 ; 
    curTextIndex = 0 ;
    targetIndex = 1 ; 
    nextIndex = 2 ; 
    
    
    //The text is one line at a time
    text = textLines[curLine] ; 
    letter = text[curTextIndex] ; 
    character = font->getCharacterAsPoints(letter);
    collectAllPointsCharacter( ) ;
    curTextIndex = -1 ; 
    targetIndex = 0 ; 
    nextIndex = 1 ; 
    collectAllPointsCharacter( ) ;
    bTeleportFlag = false ; 
    bFinished = false ; 
    
    bHasLooped = false ; 
    maxLoopIndex = 15 ; 
    

}

void QuotePath::collectAllPointsCharacter( )
{   
    characterPoints.clear() ; 
    for(int k = 0; k <(int)character.getOutline().size(); k++)
    {
        
        for(int i = 0; i < (int)character.getOutline()[k].size(); i++)
        {
            ofVec2f p = character.getOutline()[k].getVertices()[i] ; 
            characterPoints.push_back( p ) ; 
        }
    }
}

void QuotePath::endPath ( ) 
{
    targetIndex = 0 ; 
    nextIndex = 1 ;
}
