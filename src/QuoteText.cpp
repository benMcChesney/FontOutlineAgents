//
//  QuoteText.cpp
//  emptyExample
//
//  Created by Ben McChesney on 3/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "QuoteText.h"

void QuoteText::setup ( string fontPath , int fontSize ) 
{
    //Setup our font
    font.loadFont( fontPath , fontSize , true, true, true );
    
    //Default parameters
   // maxLoopIndex = 4 ; 
    curLine = 0 ; 
    curTextIndex = 0 ;
    targetIndex = 1 ; 
    nextIndex = 2 ; 
    
    
    //The text is one line at a time
    text = textLines[curLine] ; 
    letter = text[curTextIndex] ; 
    character = font.getCharacterAsPoints(letter);
    bTeleportFlag = false ; 
    bFinished = false ; 
    
    curTextIndex = -1 ; 
    targetIndex = 0 ; 
    nextIndex = 1 ; 
    
    bHasLooped = false ; 
    maxLoopIndex = 5 ; 
    
    startNewCharacter(  ) ; 
}

ofPoint QuoteText::getPointByChar( int charIndex ) 
{
    //Apply the character offset and the letter offset
    ofPoint p1 = character.getOutline()[charIndex].getVertices()[targetIndex] + charTranslateOffset + letterOffset ; 
    
    return p1 ; 
}

void QuoteText::addLine ( string line ) 
{
    textLines.push_back( line ) ; 
}


ofPoint QuoteText::startNewCharacter( ) 
{
    bTeleportFlag = true ; 
    endPath( ) ; 
    
    //Move the character to the right
    letterOffset.x += charBounds.width + 10 ; 
    
    curTextIndex++ ; 
    //cout << "1 ) curTextIndex is : " <<  curTextIndex << endl ; 
    //cout << "curLine : " << curLine << endl ; 
    //If the index has looped over all the vertices
    if ( curTextIndex > text.size()-1 ) 
    {
        letterOffset.x = 0 ; 
        curTextIndex = 0 ; 
        curLine++  ;
        //cout << "textLines.size() " << textLines.size() << endl ; 
        if ( curLine < textLines.size() )
        {
        //    cout << "old text was : " << text << endl ; 
            text = textLines[curLine] ; 
        //    cout << "newText is : " << text << endl ; 
        }
        else
        {
            bFinished = true ; 
            return ofVec3f( ) ; 
        }
        //    cout << "INVALID TEXT LINE!! : " << curLine << endl ; 
          
        letterOffset.y += charBounds.height + 15 ;
        
        
        if ( curLine > textLines.size()-1 )
            return ofVec3f( )  ; 
        
        bTeleportFlag = true ; 
        //We loop around to complete the contour for a few more indicies
        curTextIndex = 0 ; 
    }
    
    //cout << "2 ) curTextIndex is : " <<  curTextIndex << endl ; 
    
    //Get the current letter, if it's a space move on
    letter = text[curTextIndex] ; 
    if ( letter == ' ' )
        startNewCharacter() ; 
    //cout << "The Letter is : " << letter << endl ; 
    //First we get the outline points of the letter as a font
    character = font.getCharacterAsPoints(letter);
    collectAllPointsCharacter() ; 
    
    targetIndex = 0 ; 
    nextIndex = 0 ; 
    ofPoint p = getNextTarget( ) ; 
     
    //Calculate the bounds of the rectangle
    charBounds = ofRectangle( 0 , 0 , 0 , 0 ) ; 
    for(int k = 0; k <(int)character.getOutline().size(); k++)
    {
        
        for(int i = 0; i < (int)character.getOutline()[k].size(); i++)
        {
            ofPoint p = character.getOutline()[k].getVertices()[i] ; 
            if ( p.x < charBounds.x ) 
                charBounds.x = p.x ; 
            if ( p.y < charBounds.y ) 
                charBounds.y = p.y ; 
            if ( p.x > charBounds.width ) 
                charBounds.width = p.x ; 
            if ( p.y > charBounds.height ) 
                charBounds.height = p.y ; 
        }
    }
    
    //Format it in a coordinate space that's easy to play with
    charBounds = normalizeRectangle( charBounds , false ) ; 
    
    return p ; 
    
}

void QuoteText::collectAllPointsCharacter()
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

/*
ofVec2f QuoteText::getNextPathPoint( ) 
{
    int maxIndex = characterPoints.size() - 1 ; 
    if ( targetIndex > maxIndex ) 
    {
        if ( bHasLooped == false )
        {
            bHasLooped = true ; 
            targetIndex = 0 ; 
            nextIndex = 0 ; 
            return getNextTarget() ; 
        }
        
    }
    else
    {
        if ( bHasLooped == true ) 
        {
            if ( targetIndex > maxLoopIndex ) 
            {
                ofVec2f p = startNewCharacter() ;
                //ofNotifyEvent(AgentEvent::Instance()->TELEPORT_NEW_TARGET, p ) ; 
                bTeleportFlag = true ;
                bHasLooped = false ; 
                return  p ; 

            }
        }
        nextIndex = targetIndex + 1 ; 
        if ( nextIndex > maxIndex ) 
            nextIndex = 0 ; 
        return getNextTarget() ; 
    }
}
*/

void QuoteText::endPath ( ) 
{
    targetIndex = 0 ; 
    nextIndex = 1 ; 
}

ofRectangle QuoteText::normalizeRectangle ( ofRectangle rect , bool verboseLog )
{
    //Formats the rectangle to ( 0 , 0 , w , h ) 
    ofRectangle newRect = ofRectangle ( 0 , 0 , abs( rect.x ) + rect.width , abs( rect.y ) + rect.height ) ; 
    
    if ( verboseLog == true ) 
    {
        cout << "newRect : " << newRect.x << " , " << newRect.y << " , " << newRect.width << " , " << newRect.height << endl ;
    }
    return newRect ; 
    
}

ofPoint QuoteText::getNextTarget( ) 
{
    int startIndex = targetIndex ; 
    targetIndex++ ;
    if ( targetIndex > characterPoints.size()-1 ) 
    {
        targetIndex = 0 ; 
        cout << "loop over! " << endl ; 
        return startNewCharacter() ;
    }

    ofPoint p1 = characterPoints[startIndex] ;
    ofPoint p2 = characterPoints[targetIndex] ;
    //How much to space out the letters in the x on each letter and y on each new line
    charTranslateOffset = ofVec2f( 100 , 150 ) ; 
   
    float angleBetween( atan2(p2.y - p1.y , p2.x - p1.x ) ) ; 
    ofVec2f _position = charTranslateOffset + characterPoints[targetIndex] + letterOffset  ; 

    if ( bTeleportFlag == true ) 
    {
        ofNotifyEvent(AgentEvent::Instance()->TELEPORT_NEW_TARGET, _position ) ; 
        //startNewCharacter() ; 
    }
    else
        ofNotifyEvent(AgentEvent::Instance()->NEW_AGENT_TARGET, _position ) ; 
    
    return _position ;
}
