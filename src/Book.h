//
//  Book.h
//  emptyExample
//
//  Created by Ben McChesney on 6/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_Book_h
#define emptyExample_Book_h

#include "ofMain.h"
#include "CorePage.h"
#include "CircleButton.h"

#include "Tweenzor.h"


class Book
{
        public :
            Book ( ) 
            {
        
            }
    
            CircleButton prevButton ;
            CircleButton nextButton ;
            int pageIndex ; 
            float xOffset ; 
    
            void setup ( )
            {
                float r = 35 ;
                
                prevButton.setup( r * 1.5f , ofGetHeight()/2 , r , "PREV" ) ; 
                nextButton.setup( ofGetWidth() - ( r * 1.5f ) , ofGetHeight()/2 , r , "NEXT" ) ;
                
                xOffset = 0 ;
            }
    
            void update ( )
            {
        
            }
    
            void draw ( ) 
            {
                if ( pages.size() > 0 ) 
                {
                    ofPushMatrix( ) ; 
                        ofTranslate( xOffset , 0 ) ; 
                        for ( int i = 0 ; i < pages.size() ; i++ ) 
                        {
                            pages[i]->draw( ) ;
                        }
                    
                    ofPopMatrix( ) ; 
                    
                    nextButton.draw( ) ; 
                    prevButton.draw( ) ; 
                }
            }
    
    
    
            void addPage( CorePage* page ) 
            {
                pages.push_back( page ) ; 
                pageIndex = 0 ; 
                pages[pageIndex]->bInput = true ; 
            }
    
            void keyPressed ( int key ) 
            {
                pages[pageIndex]->keyPressed( key ) ; 
            }
    
            void input ( float x , float y )
            {
                if ( nextButton.hitTest( x , y ) == true ) 
                {
                    pages[pageIndex]->bInput = false ; 
                   
                    if ( pageIndex < pages.size()-1 ) 
                    {
                        pageIndex++ ;
                        cout << "pageIndex ++ " << pageIndex << endl ; 
                        Tweenzor::add( &xOffset , xOffset , pageIndex * -ofGetWidth() , 0.0f , 1.0f , EASE_OUT_QUAD ) ; 
                    }
                     pages[pageIndex]->bInput = true ; 
                                        
                }
                
                if ( prevButton.hitTest( x , y ) == true )
                {
                    pages[pageIndex]->bInput = false ; 
                    if ( pageIndex > 0 ) 
                    {
                        pageIndex-- ;
                        cout << "pageIndex -- " << pageIndex << endl ; 
                        Tweenzor::add( &xOffset , xOffset , pageIndex * -ofGetWidth() , 0.0f , 1.0f , EASE_OUT_QUAD ) ; 
                    }
                    pages[pageIndex]->bInput = true ; 
                }
                
                if ( pages.size() > 0 ) 
                {
                    for ( int i = 0 ; i < pages.size() ; i++ ) 
                    {
                        pages[i]->input ( x , y ) ; 
                    }
                }
            }
    
            vector<CorePage*>   pages ;
    
    
};


#endif
