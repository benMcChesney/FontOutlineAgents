//
//  AgentEvent.h
//  emptyExample
//
//  Created by Ben McChesney on 3/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_AgentEvent_h
#define emptyExample_AgentEvent_h

#include "ofEvents.h"
#include "ofMain.h"

class AgentEvent
{
    public :
        AgentEvent() { } 
    
        static AgentEvent* Instance()
        {
            static AgentEvent inst ; 
            return &inst ; 
        }
    
        ofEvent<ofVec2f> NEW_AGENT_TARGET ;
        ofEvent<ofVec2f> TELEPORT_NEW_TARGET ;
    
    
};


#endif
