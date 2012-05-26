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
    character = font.getCharacterAsPoints(letter);
    curTextIndex = -1 ; 
    targetIndex = 0 ; 
    nextIndex = 1 ; 
    
    bTeleportFlag = false ; 
    bFinished = false ; 
    
    bHasLooped = false ; 
    maxLoopIndex = 15 ; 
    

}

void QuotePath::endPath ( ) 
{
    targetIndex = 0 ; 
    nextIndex = 1 ;
}
