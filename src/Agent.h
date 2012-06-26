//
//  Agent.h
//  emptyExample
//
//  Created by Ben McChesney on 2/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_Agent_h
#define emptyExample_Agent_h

#include "ofMain.h"
#include "ColorPool.h"
#include "ColorTrail.h"
#include "AgentEvent.h"


class Agent
{
    public :
        Agent ( ) { }

        ofColor color ;
        ofColor nextColor ;
        bool bTarget ;
        float targetBufferDist ;    //How close until selecting a new target

        float wallDistance ;

        //acceleration,
        ofVec2f target, position,  force, velocity ;
        float maxVelocity , maxForce ;


        int colorInterpolateNum ;
        int curIndex ;
        int pathSampling ;
        bool bFinished ;

        ColorPool colorPool ;
        vector<ColorTrail> paths ;
        ColorTrail curPath ;

    /*
     ofEvents<ofVec2f> NEW_AGENT_TARGET ;
     ofEvents<ofVec2f> TELEPORT_NEW_TARGET ;
     */
        void setup( ofVec2f p , ofVec2f a , float _wallDistance ) ;
        void update( ) ;
        void draw( bool bDrawAgent = true ) ;
        void drawAgent( ) ;
        void drawEntirePath ( ) ;

        void startNewPath( )  ;
        void newAgentTargetHandler ( ofVec2f &args ) ;


        void addForce ( ofVec2f _force ) ;
        void seek(ofVec2f oTarget) ;
        void setTarget( ofVec2f _target ) ;

        virtual void drawSegment( ColorPoint p1 , ColorPoint p2 ) ;

};

#endif
