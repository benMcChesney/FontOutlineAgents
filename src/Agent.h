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
    
        float wallDistance ; 
    
        ofVec2f target, position, velocity, force, acceleration ; 
        float maxVelocity , maxForce ; 
    
    
        int colorInterpolateNum ;
        int curIndex ;
    
        ColorPool * colorPool ; 
        vector<ColorTrail> paths ; 
        ColorTrail curPath ; 
    

        
        ofVec2f cartesianToPolar ( ofVec2f v ) 
        { 
            cout << "v: " << v.x <<","<<v.y<<endl ; 
            float x = v.x ; 
            float y = v.y ; 
            float radius= sqrt( x * x + y * y );
            float angle= atan( x / y ) ;
            ofVec2f v2 = ofVec2f ( radius , angle ) ; 
            cout << "v2: " << v2.x <<","<<v2.y<<endl ; 
            return v2 ; 
            
        }
    
    /*
     ofEvents<ofVec2f> NEW_AGENT_TARGET ;
     ofEvents<ofVec2f> TELEPORT_NEW_TARGET ;
     */
    
        void startNewPath( ) 
        {
            paths.push_back( curPath ) ; 
            curPath.clear() ; 
        }   
        
        ofVec2f polarToCartesian ( ofVec2f v ) 
        {
            float r = v.x ;
            float a = v.y ; 
            //float x = r * cos( a );
            //float y = r * sin( a );
            ofVec2f v2 = ofVec2f ( r * sin( a ) , r * cos( a ) ) ; 
            return v2 ;    
        }
    
        void newAgentTargetHandler ( ofVec2f &args ) 
        {
            setTarget ( args ) ; 
        }
        
    /*
        void teleportNewTargetHandler ( ofVec2f &args ) 
        {
            cout << "teleport handler called!" << endl ; 
            position = args ; 
            setTarget ( args ) ; 
            startNewPath() ; 
        }
    */
    
        void setup( ofVec2f p , ofVec2f a , float _wallDistance = 1.0f )
        {
            wallDistance = _wallDistance ; 
            position = p ; 
            acceleration = a ; 
            bTarget = false ; 
            
            position = ofVec2f ( ofGetWidth()/2 , ofGetHeight()/2 ) ; 
            //velocity = ofVec2f ( 1 ,  ofRandom( TWO_PI )  ) ;
            
            velocity = ( ofRandom(TWO_PI) , ofRandom( TWO_PI ) ) ;
            acceleration = ofVec2f( .4 , .4 ) ; 
            
            force = ofVec2f( 0.0f , 0.0f ) ; 
            maxVelocity = ofRandom( 1, 2 )  ;
            
            //Max turn
            maxForce = 5.0f  ; 
            
            colorInterpolateNum = 10 ; 
            nextColor = colorPool->getRandomColor() ; 
            
            curIndex = 0 ; 
       //     ofAddListener( AgentEvent::Instance()->NEW_AGENT_TARGET, this , &Agent::newAgentTargetHandler ) ; 
       //     ofAddListener( AgentEvent::Instance()->TELEPORT_NEW_TARGET, this , &Agent::teleportNewTargetHandler ) ; 
            
        }
    
        void update( ) 
        {
            float dist = ofDist ( position.x , position.y , target.x , target.y ) ; 
            if ( dist < 10.0f ) 
            {
                bTarget = true ; 
            }
            
            if ( ofGetFrameNum() % 4 == 0 ) 
            {
                curIndex++ ; 
                ColorPoint cp ; 
                

                if ( curIndex == colorInterpolateNum )
                {
                    curIndex = 0 ; 
                    color = nextColor ; 
                    nextColor = colorPool->getRandomColor() ; 
                }
                
                float ratio = (float)curIndex / (float)colorInterpolateNum ; 
                ofColor lerp = color.lerp( nextColor , ratio ) ;
                cp.color = lerp ; 
                cp.position = position ; 
                curPath.addPoint( cp ) ; //.push_back( cp ) ; 
            }
            force.limit(maxForce);
            velocity += force;
            
            velocity.limit(maxVelocity);
            position += velocity;
            
            /*
             NO WRAP
            int w = ofGetWidth() ; 
            int h = ofGetHeight() ; 
            if ( position.x < 0 ) 
                position.x += w ; 
            if ( position.x > w ) 
                position += -w ; 
            if ( position.y < 0 ) 
                position.y += h ; 
            if ( position.y > h ) 
                position.y += -h ; 
            */
            seek( target ) ; 
        }
    
        void addForce ( ofVec2f _force ) 
        {
            force += _force ; 
        }
        
        void seek(ofVec2f oTarget)
        {
            
            //From Roxlu's Voids code ( www.roxlu.com ) 
            // This is how it works.
            // 1. We calculate the change in position which would bring
            // use directly to the target. This is "desired_vel". Though we don't
            // want to jump directly to this target, but slowly move to it.
            ofVec2f desiredVelocity = oTarget - position;
            
            // 2. Therefore we want to move to this position at the maximum
            // allowed speed. We do this by normalizing the vector and then
            // multiplying it with the maximum allowed speed. This is exactly
            // what ofxVec3f.scale() does.
            desiredVelocity.scale(maxVelocity);
            
            // 3. Now we have the maximum desired velocity at the maximum speed.
            // Though we need to adjust this speed as we want to go into that direction
            // at the best we are allowed, which is the remaining velocity.
            desiredVelocity -= velocity;
            
            addForce(desiredVelocity);
            
            //cout << "Desired vel: " << desired_vel.x << ", " << desired_vel.y << endl;
        }
    
        void setTarget( ofVec2f _target ) 
        {
            target = _target ; 
            bTarget = false ; 
        }
    
        void draw( )
        {
            ofSetLineWidth( 5.0f ) ; 
            ofPushMatrix() ; 
                ofTranslate( position.x , position.y , 0 ) ; 
            
                float arrow_len = 14;
                ofVec2f arrow_end = ( velocity.normalized() * arrow_len );
                ofFill();
            
                ofSetColor(color.r , color.g, color.b );
                ofLine( 0, 0 , arrow_end.x, arrow_end.y );
            
                ofSetColor ( 255 , 255 , 255 ) ; 
                ofCircle ( 0 , 0 , 4 ) ; 
            ofPopMatrix() ; 
            ofSetLineWidth( 2.0f ) ; 
            
            ofPushMatrix() ;
            if ( paths.size() > 0 ) 
            {
                for ( int i = 0 ; i < paths.size() ; i++ ) 
                {
                    vector<ColorPoint> path = paths[i].trail ;
                    if ( path.size() > 0 ) 
                    {
                        for ( int i = 0 ; i < path.size()-1 ; i++ ) 
                        {
                            ofSetColor ( path[i].color ) ; 
                            ofLine( path[i].position.x , path[i].position.y , path[i+1].position.x , path[i+1].position.y ) ; 
                        }
                    }
                }
            }
            
            vector<ColorPoint> cpts = curPath.trail ;
            if ( cpts.size() > 0 ) 
            {
                for ( int i = 0 ; i < cpts.size()-1 ; i++ ) 
                {
                    ofSetColor ( cpts[i].color ) ; 
                    ofLine( cpts[i].position.x , cpts[i].position.y , cpts[i+1].position.x , cpts[i+1].position.y ) ; 
                }
            }
            ofPopMatrix() ; 
        }
    
};

#endif