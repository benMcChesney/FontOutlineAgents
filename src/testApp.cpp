#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    ofSetLogLevel(OF_LOG_VERBOSE) ; 
    ofBackground( 225 ) ; 
    ofSetFrameRate( 60 ) ; 
    ofSetVerticalSync( true ) ; 
    
    //This is just an easy way to grab a color from a color palette
    /* blue - green *
    colorPool.addColor( ofColor( 70 , 148 , 140 ) ) ; 
    colorPool.addColor( ofColor( 187 , 229 , 160 ) ) ; 
    colorPool.addColor( ofColor( 149 , 208 , 171 ) ) ; 
    colorPool.addColor( ofColor( 10 , 33 , 43 ) ) ; 
    */
    
    colorPool.addColor( ofColor( 242 , 202 , 82 ) ) ; 
    colorPool.addColor( ofColor( 242 , 163 , 65 ) ) ; 
    colorPool.addColor( ofColor( 217 , 99 , 30 ) ) ; 
    colorPool.addColor( ofColor( 89 , 25 , 2 ) ) ; 
    
    //Add our quote in line by line
    quote.addLine( "TESTING" ) ; 
//    quote.addLine( "WELCOME OUR" ) ; 
//    quote.addLine( "NEW ROBOT" ) ; 
//    quote.addLine( "OVERLORDS") ; 
    quote.setup( "Batang.ttf" , 60 ) ; 
    
   
    int numAgents = 5 ; 
    for ( int i = 0 ; i < numAgents ; i++ ) 
    {
        
        //Create our agent 
        Agent* agent = new Agent() ; 
        agent->colorPool.addColor( colorPool.getRandomColor() ) ; 
        agent->colorPool.addColor( colorPool.getRandomColor() ) ; 
        
        // ( x , y ) , speed, maxTurn
        agent->setup( ofVec2f ( ofGetWidth()/2 , ofGetHeight()/2 ) , ofVec2f( 0.3f , 0 ) , 20.0f ) ; 
        agent->color = agent->colorPool.getRandomColor() ;
            
        quote.createQuotePath( ) ; 
        cout << "making agent : " << i << endl ; 
        ofPoint p1 = quote.getPointByChar ( 0 , i ) ; 
        agent->startNewPath() ; 
        agent->position = p1 ; 
        agent->target = p1 ; 
        
       
        
        
        agents.push_back( agent ) ; 
        
    }
    
    setupGUI( ) ; 
    //cout << "p1 : " << p1 << endl ; 
    
    
    
    
}


//--------------------------------------------------------------
void testApp::update()
{
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
            QuotePath * qp = quote.getQuotePathAt( count ) ; 
           // if ( qp 
            if ( qp->bTeleportFlag == true ) 
            {
                (*a)->position = _position ; 
                qp->bTeleportFlag = false ; 
                (*a)->startNewPath() ; 
            }
            
            (*a)->bTarget = false ; 
            (*a)->setTarget ( _position ) ;
        }
        count++ ; 
    }
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


void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 
    
	if(name == "MAX SPEED")
		a_maxSpeed = ((ofxUISlider *) e.widget)->getScaledValue(); 
    
    if(name == "MAX FORCE")
		a_maxForce = ((ofxUISlider *) e.widget)->getScaledValue(); 
    
    if(name == "BUFFER DIST")
		a_targetBuffer = ((ofxUISlider *) e.widget)->getScaledValue(); 
    
    if(name ==  "PATH SAMPLING" )
		a_pathSampling =(int) ((ofxUISlider *) e.widget)->getScaledValue(); 
    
    gui->saveSettings("GUI/settings.xml") ; 
    
    vector<Agent*>::iterator a ; 
    for ( a = agents.begin() ; a != agents.end() ; a++ )
    {
        (*a)->maxVelocity = a_maxSpeed ; 
        (*a)->maxForce = a_maxForce ; 
        (*a)->targetBufferDist = a_targetBuffer ; 
        (*a)->pathSampling = a_pathSampling ; 
    }
}

void testApp::setupGUI ( ) 
{
    float canvasHeight = 250 ;
    float sliderLength = 150 ;
    float padding = 15 ; 
    gui = new ofxUICanvas( 0 , ofGetHeight() - canvasHeight , ofGetWidth() , canvasHeight );
    
    //gui->addWidgetDown(new ofxUILabel("SLIDERS", OFX_UI_FONT_LARGE));         
    
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 12.0f, a_maxSpeed, "MAX SPEED")); 
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 5.0f, a_maxForce, "MAX FORCE")); 
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 25.0f, a_targetBuffer, "BUFFER DIST")); 
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 1 , 14 , a_pathSampling, "PATH SAMPLING")); 
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    gui->loadSettings( "GUI/settings.xml" ) ; 
}
