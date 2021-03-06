//
//  QuotePath.cpp
//  emptyExample
//
//  Created by Ben McChesney on 5/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "QuotePath.h"
#include <iostream>

void QuotePath::setup( ofTrueTypeFont * _font )
{
    curWord = 0 ;
    curTextIndex = 0 ;
    targetIndex = 1 ;
    nextIndex = 2 ;

    //The text is one line at a time
    //cout << "textLines.size() " << textLines.size() << endl ;
    text = textLines[curWord] ;
    letter = text[curTextIndex] ;
    setFont( _font ) ;
    /*
    font = _font ;
    character = font->getCharacterAsPoints(letter);
    collectAllPointsCharacter( ) ;
    curTextIndex = -1 ;
    targetIndex = 0 ;
    nextIndex = 1 ;
    collectAllPointsCharacter( ) ;
    bTeleportFlag = true ;
    bFinished = false ;

    bHasLooped = false ;
    maxLoopIndex = 15 ;*/

}
void QuotePath::setFont( ofTrueTypeFont * _font )
{
    font = _font ;
    character = font->getCharacterAsPoints(letter);
    collectAllPointsCharacter( ) ;
    curTextIndex = -1 ;
    targetIndex = 0 ;
    nextIndex = 1 ;
    collectAllPointsCharacter( ) ;
    bTeleportFlag = true ;
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

void QuotePath::updateCharacter( )
{
    character = font->getCharacterAsPoints( letter );
}


