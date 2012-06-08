//
//  RibbonAgent.h
//  emptyExample
//
//  Created by Ben McChesney on 6/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_RibbonAgent_h
#define emptyExample_RibbonAgent_h

#include "ofMain.h"
#include "Agent.h"

class RibbonAgent : public Agent
{
    public : 
        virtual void drawSegment( ColorPoint p1 , ColorPoint p2 ) 
        {
            ofSetColor ( p1.color ) ; 
            ofLine( p1.position.x , p1.position.y , p2.position.x , p2.position.y ) ; 
        }
        
};


#endif
