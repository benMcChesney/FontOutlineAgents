//
//  CircleButton.h
//  emptyExample
//
//  Created by Ben McChesney on 6/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_CircleButton_h
#define emptyExample_CircleButton_h

class CircleButton
{
    public :
        CircleButton( ) { }
            
        void setup( float _x , float _y , float _radius , string _name )
        {
            x = _x ; 
            y = _y ;
            radius = _radius ;
            name = _name ;
        }
    
        void update ( )
        {
        
        }
    
        void draw ( )
        {
            ofSetColor( 5 , 5 , 5 ) ; 
            ofCircle( x , y , radius ) ;
            
            ofSetColor( 215 , 215 , 215 ) ;
            ofDrawBitmapString( name , x - radius/2 , y + 5 ) ; 
        }
        
        string name ;
        bool bActive ;
    
        float x , y ;
        float radius ;
    
        bool hitTest( float iX , float iY ) 
        {
            return ( ofDist( x , y , iX , iY ) < radius ) ; 
        }
};

#endif
