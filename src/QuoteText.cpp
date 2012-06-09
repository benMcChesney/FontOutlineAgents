//
//  QuoteText.cpp
//  emptyExample
//
//  Created by Ben McChesney on 3/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>

#include "QuoteText.h"

void QuoteText::init ( ) 
{
    font.loadFont( fontPath , fontSize, true , true , true ) ; 
}

void QuoteText::setup ( string _fontPath , int _fontSize ) 
{
    fontPath = _fontPath ; 
    fontSize = _fontSize ; 
    cout << "fontSize : " << fontSize << endl ; 
    //Setup our font
    font.loadFont( fontPath , fontSize, true , true , true ) ; 
    //charTranslateOffset = ofVec2f( 100 , 150 ) ;

}

void QuoteText::createQuotePath ( ) 
{
    QuotePath * qp = new QuotePath( ) ; 
    vector<string> textLines ; 
    for ( int i = 0 ; i < wordBlocks.size() ; i++ ) 
    {
        textLines.push_back( wordBlocks[ i ]->word ) ; 
    }
    qp->textLines = textLines ; 
    qp->font = &font ; 
    qp->setup( ) ;

    // vector<QuotePath*> quotePaths ; 
    quotePaths.push_back( qp ) ; 
}

void QuoteText::addWordBlock ( string word , ofPoint position , int _fontSize , bool _bEditable  )
{
    WordBlock * wb = new WordBlock() ; 
    wb->setup( fontPath , _fontSize , word , wordBlocks.size() , position ) ; 
    wb->bEditable = _bEditable ; 
    wordBlocks.push_back( wb ) ; 
    
              //void setup ( string _fontPath , float _fontSize , string _word , int _wordIndex ) 
}


WordBlock * QuoteText::getLastWordBlockRef( ) 
{
    WordBlock * wb = wordBlocks[ wordBlocks.size() -1 ] ; 
    if ( wb->bEditable == true ) 
        return wb ;
    else
        return NULL ; 
}

//addWordBlock

//vector<WordBlock*> wordBlocks ;

ofPoint QuoteText::getPointByChar( int charIndex , int pathIndex ) 
{
    //Apply the character offset and the letter offset
    QuotePath * qp = getQuotePathAt ( pathIndex ) ; 
    if ( qp == NULL ) 
    {
        cout << "getPointByChar(" << charIndex << " , " << pathIndex << "failed " << endl ;
        return ofVec2f( ) ; 
    }
    //quotePaths[pathIndex] ; 
   // cout << "quotePath is not NULL!" << endl ;
    //cout << "charIndex : " << charIndex << endl ;
   // cout << "qp->targetIndex" << qp->targetIndex << endl ; 
    //qp->collectAllPointsCharacter() ; 
   // ofPoint p1 = qp->characterPoints[charIndex] ; 
    //vector<ofPoint> pts = qp->character.getOutline()[charIndex].getVertices() ;
    //cout << "pts.size() " << endl ;
  
    ofPoint p1 = qp->character.getOutline()[charIndex].getVertices()[ qp->targetIndex ] + qp->letterOffset ; 
    //cout << "p1 is : " << p1.x << " , " << p1.y << endl ; 
    return p1 ; 
}

ofPoint QuoteText::startNewCharacter( int pathIndex ) 
{
    QuotePath * qp = quotePaths[pathIndex] ; 
    
    qp->bTeleportFlag = true ; 
    qp->endPath( ) ; 
    
    //Move the character to the right
      string soFar = qp->text.substr( 0 , qp->curTextIndex ) ; 
    ofRectangle soFarBounds = qp->font->getStringBoundingBox( soFar, 0 , 0 ) ;
    qp->letterOffset.x += qp->charBounds.width + 10 ; ; //qp->font->getStringBoundingBox( ofToString(qp->text[qp->curTextIndex]) , 0 , 0 ).width ; 
    //qp->charBounds.width + 10 ; 
    
    qp->curTextIndex++ ; 
    //cout << "1 ) curTextIndex is : " <<  curTextIndex << endl ; 
    //cout << "curLine : " << curLine << endl ; 
    //If the index has looped over all the vertices
    if ( qp->curTextIndex > qp->text.size()-1 ) 
    {
        qp->letterOffset.x = 0 ; 
        qp->curTextIndex = 0 ; 
        qp->curLine++  ;
        //cout << "textLines.size() " << textLines.size() << endl ; 
        if ( qp->curLine < qp->textLines.size() )
        {
        //    cout << "old text was : " << text << endl ; 
            qp->text = wordBlocks[qp->curLine]->word ; 
            //qp->letterOffset = wordBlocks[qp->curLine]->translate ; 
        //    cout << "newText is : " << text << endl ; 
        }
        else
        {
            qp->bFinished = true ; 
            return ofVec3f( ) ; 
        }
        //    cout << "INVALID TEXT LINE!! : " << curLine << endl ; 
          
        //qp->letterOffset.y += qp->charBounds.height + 15 ;
        
        
        if ( qp->curLine > wordBlocks.size() - 1 )
            return ofVec3f( )  ; 
        
        qp->bTeleportFlag = true ; 
        //We loop around to complete the contour for a few more indicies
        qp->curTextIndex = 0 ; 
    }
    
    //cout << "2 ) curTextIndex is : " <<  curTextIndex << endl ; 
    
    //Get the current letter, if it's a space move on
    qp->letter = qp->text[qp->curTextIndex] ; 
    if ( qp->letter == ' ' )
        startNewCharacter( pathIndex ) ; 
    //cout << "The Letter is : " << letter << endl ; 
    //First we get the outline points of the letter as a font
    qp->character = font.getCharacterAsPoints( qp->letter );
    qp->collectAllPointsCharacter() ; 
    //..collectAllPointsCharacter( pathIndex ) ; 
    
    qp->targetIndex = 0 ; 
    qp->nextIndex = 0 ; 
    ofPoint p = getNextTarget( pathIndex ) ; 
     
    //Calculate the bounds of the rectangle
    ofRectangle charBounds = ofRectangle( 0 , 0 , 0 , 0 ) ; 
    for(int k = 0; k <(int)qp->character.getOutline().size(); k++)
    {
        
        for(int i = 0; i < (int)qp->character.getOutline()[k].size(); i++)
        {
            ofPoint p = qp->character.getOutline()[k].getVertices()[i] ; 
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
    qp->charBounds = normalizeRectangle( charBounds , false ) ; 
    
    return p ; //+ wordBlocks[ qp->curLine ]->translate ; 
    
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

ofPoint QuoteText::getNextTarget( int pathIndex ) 
{
    QuotePath * qp = getQuotePathAt ( pathIndex ) ; 
    if ( qp == NULL ) 
        return ofPoint( ) ; 
    
    if ( qp->bFinished == true ) 
        return ofPoint( ); 
    
    int startIndex = qp->targetIndex ; 
    qp->targetIndex++ ;
    if ( qp->targetIndex > qp->characterPoints.size()-1 ) 
    {
        if ( qp->bHasLooped == false ) 
        {
            qp->bHasLooped = true ; 
        }
        qp->targetIndex = 0 ; 
    }

    if ( qp->bHasLooped == true ) 
    {
        if ( qp->targetIndex >= qp->maxLoopIndex ) 
        {
            qp->targetIndex = 0 ; 
            qp->bHasLooped = false ; 
            cout << "loop over! " << endl ; 
            return startNewCharacter( pathIndex ) ; 
        }
    }
    ofPoint p1 = qp->characterPoints[startIndex] ;
    ofPoint p2 = qp->characterPoints[qp->targetIndex] ;
    //How much to space out the letters in the x on each letter and y on each new line
    
   
    //float angleBetween( atan2(p2.y - p1.y , p2.x - p1.x ) ) ; 
    //cout << "qp->characterPoints.size() " << qp->characterPoints.size() << endl; 
    ofVec2f _position =  qp->characterPoints[qp->targetIndex]  + qp->letterOffset  +  wordBlocks[qp->curLine]->translate  ; 
/*
    if ( bTeleportFlag == true ) 
    {
        ofNotifyEvent(AgentEvent::Instance()->TELEPORT_NEW_TARGET, _position ) ; 
        //startNewCharacter() ; 
    }
    else
        ofNotifyEvent(AgentEvent::Instance()->NEW_AGENT_TARGET, _position ) ; 
  */  
    return _position ;
}

void QuoteText::inputDown ( float x , float y )
{
    for ( int b = 0 ; b < wordBlocks.size() ; b++ ) 
    {
        if ( wordBlocks[ b ]->hitTest( x , y ) == true ) 
        {
            wordBlocks[ b ]->startDrag( x , y ) ; 
        }
    }
}

void QuoteText::inputMove ( float x , float y ) 
{
    for ( int b = 0 ; b < wordBlocks.size() ; b++ ) 
    {
        if ( wordBlocks[ b ]->bDragging ) 
        {
            wordBlocks[ b ]->updateDrag( x , y ) ; 
        }
    }
}

void QuoteText::inputUp ( float x , float y ) 
{
    for ( int b = 0 ; b < wordBlocks.size() ; b++ ) 
    {
        if ( wordBlocks[ b ]->bDragging ) 
        {
            wordBlocks[ b ]->endDrag() ; 
        }
    }
}

QuotePath* QuoteText::getQuotePathAt ( int index )
{
    if ( index < quotePaths.size() ) 
    {
        return quotePaths[ index ] ; 
    }
    else
    {
        cout << " not a valid quotePath Index : " << index << " / " << quotePaths.size() -1 << endl ; 
        return NULL ; 
    }
}

void QuoteText::drawWordBlocks()
{
    for ( int i = 0 ; i < wordBlocks.size() ; i++ ) 
    {
        wordBlocks[i]->draw( ) ; 
    }
}

void QuoteText::resetQuotePaths()
{
    quotePaths.clear() ; 
}

