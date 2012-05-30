//
//  HitRectImage.h
//  emptyExample
//
//  Created by Ben McChesney on 5/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_HitRectImage_h
#define emptyExample_HitRectImage_h

#include "ofMain.h"

class HitRectImage
{
    public : 
        HitRectImage ( ) { } 
    
        void setup( string filePath , float x , float y , bool bCenter = false )
        {
            image.loadImage( filePath ) ; 
            hitRect = ofRectangle( x , y , image.width , image.height ) ; 
            
            if ( bCenter == true ) 
                hitRect = ofRectangle( x - image.width/2 , y - image.height/2 , image.width , image.height ) ; 
        }
    
        void draw( )
        {
            image.draw( hitRect.x , hitRect.y , hitRect.width , hitRect.height ) ; 
        }
    
        bool hitTest ( float x , float y ) 
        {
            return (( x > hitRect.x && x < hitRect.x + hitRect.width ) && ( y > hitRect.y && y < hitRect.y + hitRect.height ) ) ; 
        }
    
        ofRectangle hitRect ;
        ofImage image ;
};


#endif
