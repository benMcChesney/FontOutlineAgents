#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
   
    ofBackground( 255 , 255 , 255 ) ; 
    ofSetFrameRate( 60 ) ; 
    ofSetVerticalSync( true ) ; 
    
    //This is just an easy way to grab a color from a color palette
    colorPool.addColor( ofColor( 70 , 148 , 140 ) ) ; 
    colorPool.addColor( ofColor( 187 , 229 , 160 ) ) ; 
    colorPool.addColor( ofColor( 149 , 208 , 171 ) ) ; 
    colorPool.addColor( ofColor( 10 , 33 , 43 ) ) ; 
    
    //Create our agent 
    agent = Agent() ;
    agent.colorPool = &colorPool ; 
    // ( x , y ) , speed, maxTurn
    agent.setup( ofVec2f ( ofGetWidth()/2 , ofGetHeight()/2 ) , ofVec2f( 0.3f , 0 ) , 20.0f ) ; 
    agent.color = colorPool.getRandomColor() ; 

    //Add our quote in line by line
    quote.addLine( "I FOR ONE" ) ; 
    quote.addLine( "WELCOME OUR" ) ; 
    quote.addLine( "NEW ROBOT" ) ; 
    quote.addLine(  "OVERLORDS") ; 
    quote.setup( "Batang.ttf" , 60 ) ; 
    
    //For recording movies
    screenshotCount = 0 ; 
    
    ofPoint p1 = quote.getPointByChar ( 0 ) ; 
    agent.startNewPath() ; 
    agent.position = p1 ; 
    
}
//--------------------------------------------------------------
void testApp::update()
{
    
    agent.update() ; 
    
    if ( quote.bFinished ) 
        return ; 
    //Flag if the target needs to be changed
    if ( agent.bTarget == true ) 
    {
        ofPoint _position = quote.getNextTarget() ; 
        if ( quote.bTeleportFlag == true ) 
        {
            cout << "SHOULD BE TELEPORTING!!!" << endl ; 
            agent.position = _position ; 
            quote.bTeleportFlag = false ; 
            agent.startNewPath() ; 
        }
      //  if ( _position == NULL ) 
      //  {
      //      _position = quote.startNewCharacter() ; 
      //  }
        agent.bTarget = false ; 
        /*
        if ( _position.z > 0 ) 
        {
            cout << "jump to new location!" << endl ;
            agent.startNewPath() ; 
            agent.position = _position ; 
        }*/
        
        agent.setTarget ( _position ) ;
    }
}
 
//--------------------------------------------------------------
void testApp::draw()
{       
    //Call the agent draw() ! Nice and simple
    agent.draw() ; 
}
