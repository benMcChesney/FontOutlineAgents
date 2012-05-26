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
    
    //Add our quote in line by line
    quote.addLine( "I FOR ONE" ) ; 
    quote.addLine( "WELCOME OUR" ) ; 
    quote.addLine( "NEW ROBOT" ) ; 
    quote.addLine(  "OVERLORDS") ; 
    quote.setup( "Batang.ttf" , 60 ) ; 
    
    //For recording movies
    screenshotCount = 0 ; 

    int numAgents = 1 ; 
    for ( int i = 0 ; i < numAgents ; i++ ) 
    {
        
        //Create our agent 
        Agent* agent = new Agent() ; 
        agent->colorPool = &colorPool ; 
        // ( x , y ) , speed, maxTurn
        agent->setup( ofVec2f ( ofGetWidth()/2 , ofGetHeight()/2 ) , ofVec2f( 0.3f , 0 ) , 20.0f ) ; 
        agent->color = colorPool.getRandomColor() ;
            
        ofPoint p1 = quote.getPointByChar ( 0 , i ) ; 
        agent->startNewPath() ; 
        agent->position = p1 ; 
        agent->target = p1 ; 
        
        QuotePath * qp = new QuotePath( ) ; 
        qp->setup( ) ;
        quote.addQuotePath( qp ) ; 
        
        
        agents.push_back( agent ) ; 
    }
    //cout << "p1 : " << p1 << endl ; 
    
    
    
    
}
//--------------------------------------------------------------
void testApp::update()
{
   // if ( quote.bFinished ) 
   //     return ; 
    
    int count = 0 ; 
    vector<Agent*>::iterator a ; 
    for ( a = agents.begin() ; a != agents.end() ; a++ )
    {
        (*a)->update() ; 
        //TODO: this feels so hacky make this actually use an event
        //Pass the index ? or a reference to the agent itseld ? 
        //Flag if the target needs to be changed
        if ( (*a)->bTarget == true ) 
        {
            ofPoint _position = quote.getNextTarget( count ) ; 
            QuotePath * qp = quote.getQuotePathAt( 0 ) ; 
           // if ( qp 
            if ( quote.bTeleportFlag == true ) 
            {
                //cout << "SHOULD BE TELEPORTING!!!" << endl ; 
                (*a)->position = _position ; 
                quote.bTeleportFlag = false ; 
                (*a)->startNewPath() ; 
            }
            
            (*a)->bTarget = false ; 
            (*a)->setTarget ( _position ) ;
        }
        count++ ; 
    }
    
  /*
   
    if ( agent.bTarget == true ) 
    {
        ofPoint _position = quote.getNextTarget() ; 
        if ( quote.bTeleportFlag == true ) 
        {
            //cout << "SHOULD BE TELEPORTING!!!" << endl ; 
            agent.position = _position ; 
            quote.bTeleportFlag = false ; 
            agent.startNewPath() ; 
        }
        
        agent.bTarget = false ; 
        agent.setTarget ( _position ) ;
    }
   */
}
 
//--------------------------------------------------------------
void testApp::draw()
{       
    //Call the agent draw() ! Nice and simple
    vector<Agent*>::iterator a ; 
    for ( a = agents.begin() ; a != agents.end() ; a++ )
    {
        (*a)->draw() ; 
    }
}
