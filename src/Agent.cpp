//
//  Agent.cpp
//  emptyExample
//
//  Created by Ben McChesney on 6/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Agent.h"

void Agent::startNewPath( )
{
    paths.push_back( curPath ) ;
    curPath.clear() ;
}

void Agent::newAgentTargetHandler ( ofVec2f &args )
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

void Agent::setup( ofVec2f p , ofVec2f a , float _wallDistance = 1.0f )
{
    targetBufferDist = 10.0f ;
    wallDistance = _wallDistance ;
    position = p ;
    //acceleration = a ;
    bTarget = false ;

    position = ofVec2f ( ofGetWidth()/2 , ofGetHeight()/2 ) ;
    //velocity = ofVec2f ( 1 ,  ofRandom( TWO_PI )  ) ;

    velocity = ( ofRandom(TWO_PI) , ofRandom( TWO_PI ) ) ;
    //acceleration = ofVec2f( .4 , .4 ) ;

    force = ofVec2f( 0.0f , 0.0f ) ;
    maxVelocity = ofRandom( 1, 2 )  ;

    //Max turn
    maxForce = 5.0f  ;

    colorInterpolateNum = 10 ;
    nextColor = colorPool.getRandomColor() ;
    pathSampling = 4 ;
    curIndex = 0 ;

    bFinished = false ;
    //     ofAddListener( AgentEvent::Instance()->NEW_AGENT_TARGET, this , &Agent::newAgentTargetHandler ) ;
    //     ofAddListener( AgentEvent::Instance()->TELEPORT_NEW_TARGET, this , &Agent::teleportNewTargetHandler ) ;

}

void Agent::update( )
{
    if ( bFinished )
        return ;
    float dist = ofDist ( position.x , position.y , target.x , target.y ) ;
    if ( dist < targetBufferDist )
    {
        bTarget = true ;
    }

    if ( ofGetFrameNum() % pathSampling == 0 )
    {
        curIndex++ ;
        ColorPoint cp ;


        if ( curIndex == colorInterpolateNum )
        {
            curIndex = 0 ;
            color = nextColor ;
            nextColor = colorPool.getRandomColor() ;
        }

        float ratio = (float)curIndex / (float)colorInterpolateNum ;
        ofColor lerp = color.lerp( nextColor , ratio ) ;
        cp.color = lerp ;
        cp.color.a = ofRandom( 255.0f * .7 , 255.0f * 1.0f ) ;
        cp.position = position ;
        cp.radius =  ofRandom ( 0.25 , 4 ) ; //4 + sin( ofGetElapsedTimef() ) * 1 ;
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

void Agent::addForce ( ofVec2f _force )
{
    force += _force ;
}

void Agent::seek(ofVec2f oTarget)
{

    //From Roxlu's Boids code ( www.roxlu.com )
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

void Agent::setTarget( ofVec2f _target )
{
    target = _target ;
    bTarget = false ;
}

void Agent::drawAgent( )
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
}

void Agent::drawEntirePath( )
{
    ofPushMatrix( ) ;
    if ( paths.size() > 0 )
    {
        for ( int i = 0 ; i < paths.size() ; i++ )
        {
            vector<ColorPoint> path = paths[i].trail ;
            if ( path.size() > 0 )
            {
                for ( int i = 0 ; i < path.size()-1 ; i++ )
                {
                    drawSegment( path[i] , path[i+1] ) ;
                }
            }
        }
    }
    ofPopMatrix( ) ;
}

void Agent::draw( bool bDrawAgent )
{
    if ( bDrawAgent )
    {
        drawAgent() ;
    }
    ofSetLineWidth( 2.0f ) ;

    //ofRectMode( OF_RECTMODE_CENTER ) ;
    ofPushMatrix() ;
    vector<ColorPoint> cpts = curPath.trail ;
    if ( cpts.size() > 1 )
    {
        for ( int i = 0 ; i < cpts.size()-2 ; i++ )
        {
            drawSegment( cpts[i] , cpts[i+1] ) ;
        }
    }
    ofPopMatrix() ;

    // ofRectMode( OF_RECTMODE_CORNER ) ;
}

void Agent::drawSegment( ColorPoint p1 , ColorPoint p2 )
{
    ofSetColor ( p1.color ) ;
    //ofLine( p1.position.x , p1.position.y , p2.position.x , p2.position.y ) ;
    ofCircle( p1.position , p1.radius ) ;
}
