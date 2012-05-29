//
//  ColorTrail.h
//  emptyExample
//
//  Created by Ben McChesney on 2/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_ColorTrail_h
#define emptyExample_ColorTrail_h

#include "ofMain.h"


struct ColorPoint
{
    ofColor color ; 
    ofVec2f position ; 
    float radius ; 
};

class ColorTrail
{
    public : 
        ColorTrail( ) { } 
    
        vector<ColorPoint> trail ; 
        
        void addPoint ( ColorPoint cp ) 
        {
            trail.push_back( cp ) ; 
        }
    
        void clear ( ) 
        {
            trail.clear() ; 
        }
    
};

#endif
