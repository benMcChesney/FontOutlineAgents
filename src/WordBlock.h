//
//  WordBlock.h
//  emptyExample
//
//  Created by Ben McChesney on 6/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_WordBlock_h
#define emptyExample_WordBlock_h

#include "ofMain.h"

class WordBlock
{
    public :
        WordBlock( ) { }

        ofPoint translate ;
        float fontSize ;
        ofTrueTypeFont font ;
        string word ;
        string fontPath ;

        ofRectangle bounds ;
        int wordIndex ;


        ofPoint dragOffset ;
        bool bDragging ;

        bool bEditable ;

        float lastDrag ;
        float doubleClickDelay ;

        void setup ( string _fontPath , float _fontSize , string _word , int _wordIndex , ofPoint _translate )
        {
            translate = _translate ;
            fontPath = _fontPath ;
            fontSize = _fontSize ;
            font.loadFont( fontPath , fontSize , true , true , true ) ;

            word = _word ;
            bounds = font.getStringBoundingBox( word , 0 , 0 ) ;
            wordIndex = _wordIndex ;

            bDragging = false ;
            dragOffset = ofPoint ( 0 , 0 ) ;
            bEditable = false ;

            lastDrag = -2 ;
            doubleClickDelay = 0.4f ;
        }

        void startDrag ( float x , float y )
        {
            bDragging = true ;
            dragOffset = ofPoint ( translate.x - x , translate.y - y ) ;

            float nowTime = ofGetElapsedTimef() ;
            if ( lastDrag > 0 )
            {
                cout << "now: " << nowTime << " is < " << lastDrag + doubleClickDelay << endl ;
                if ( nowTime < ( lastDrag + doubleClickDelay ) )
                {
                    bEditable = !bEditable ;
                }
            }
            lastDrag = nowTime ;
        }

        void updateDrag ( float x , float y )
        {
            translate = dragOffset + ofPoint ( x , y ) ;
        }

        void endDrag ( )
        {
            bDragging = false ;
            dragOffset = ofPoint ( ) ;
            lastDrag = -2 ;
        }

        void updateWord ( )
        {
            font.loadFont( fontPath , fontSize , true , true , true ) ;
            bounds = font.getStringBoundingBox( word , 0 , 0 ) ;
            //cout << "bounds : w " << bounds.width << " , " << bounds.height << endl ;
//            bounds = font.getStringBoundingBox( word , 0 , 0 ) ;
            //bounds = font.getStringBoundingBox( word , 0 , 0 ) ;
        }

        void draw ( )
        {
            ofPushStyle() ;
            ofSetRectMode( OF_RECTMODE_CORNER ) ;

            if ( bEditable == true )
            {
                ofSetColor( 255 , 15 , 15 ) ;
                float padding = 10 ;
                ofRect( translate.x - padding , translate.y - padding - bounds.height , bounds.width + padding * 2 , bounds.height + padding * 2 ) ;
            }

            ofSetColor ( 115 , 115 , 115 ) ;
            cout << "translate: " << translate.x << " , " << translate.y << endl ;
            cout << "word : " << word << endl ;
            ofRect( translate.x , translate.y - bounds.height , bounds.width , bounds.height  )  ;
            ofSetColor( 255 , 255 , 255 ) ;
            font.drawString( word , translate.x , translate.y ) ;
            ofPopStyle() ;
        }

        bool hitTest ( float x , float y )
        {
            return ( ( x > translate.x && x < translate.x + bounds.width ) && ( y > ( translate.y - bounds.height ) && y < translate.y ) ) ;
        }
};

#endif
