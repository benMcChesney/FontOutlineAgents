#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
    bRunAgents = false ; 
    
    instructionsFont.loadFont("GUI/NewMedia Fett.ttf", 16 ) ; 
    
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
    quote.addLine( "NOW TESTING" ) ;
//    quote.addLine( "WELCOME OUR" ) ; 
//    quote.addLine( "NEW ROBOT" ) ; 
//    quote.addLine( "OVERLORDS") ; 
    quote.setup( "Batang.ttf" , 60 ) ; 
    
  /* 
    for ( int i = 0 ; i < a_numAgents ; i++ ) 
    {
        createNewAgent( ) ; 
    }
*/  
    setupGUI( ) ; 
    //cout << "p1 : " << p1 << endl ; 

    
}


//--------------------------------------------------------------
void testApp::update()
{
    if ( !bRunAgents ) 
        return ; 
    
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
            
            if ( qp->bFinished == true ) 
            {
                
                (*a)->bFinished = true ; 
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
    ofPushMatrix() ;
   
    ofTranslate( quote.charTranslateOffset.x , quote.charTranslateOffset.y , 0 ) ; 
    
    //Call the agent draw() ! Nice and simple
    vector<Agent*>::iterator a ; 
    for ( a = agents.begin() ; a != agents.end() ; a++ )
    {
        (*a)->draw() ; 
    }
    
    ofPopMatrix() ; 
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
    
    if ( name == "NUM AGENTS" ) 
    {
        a_numAgents =(int) ((ofxUISlider *) e.widget)->getScaledValue(); 
        resetAgents( ) ; 
    }
    
    if ( name == "CHAR TRANSLATE X" ) 
    {
        quote.charTranslateOffset.x = ((ofxUISlider *) e.widget)->getScaledValue(); 
    }
    
    if ( name == "CHAR TRANSLATE Y" ) 
    {
        quote.charTranslateOffset.y = ((ofxUISlider *) e.widget)->getScaledValue(); 
    }
    
    
    if ( name == "MAX SPEED R OFFSET" ) 
    {
        a_rOffsetMaxSpeed = ((ofxUISlider *) e.widget)->getScaledValue(); 
    }
    
    
    
    if ( name == "MAX FORCE R OFFSET"  ) 
    {
        a_rOffsetMaxTurn = ((ofxUISlider *) e.widget)->getScaledValue(); 
    }
    

    gui->saveSettings("GUI/settings.xml") ; 
    
    vector<Agent*>::iterator a ; 
    for ( a = agents.begin() ; a != agents.end() ; a++ )
    {
        (*a)->maxVelocity = a_maxSpeed + ofRandom( -a_rOffsetMaxSpeed , a_rOffsetMaxSpeed ) ; 
        (*a)->maxForce = a_maxForce  + ofRandom( -a_rOffsetMaxTurn , a_rOffsetMaxTurn ) ; 
        (*a)->targetBufferDist = a_targetBuffer ; 
        (*a)->pathSampling = a_pathSampling ; 
        
    }
}

void testApp::createNewAgent()
{
    int index = agents.size() ; 
    //Create our agent 
    Agent* agent = new Agent() ; 
    agent->colorPool.addColor( colorPool.getRandomColor() ) ; 
    agent->colorPool.addColor( colorPool.getRandomColor() ) ; 
    
    // ( x , y ) , speed, maxTurn
    agent->setup( ofVec2f ( ofGetWidth()/2 , ofGetHeight()/2 ) , ofVec2f( 0.3f , 0 ) , 20.0f ) ; 
    agent->color = agent->colorPool.getRandomColor() ;
    
    quote.createQuotePath( ) ; 
   // cout << "making agent : " << i << endl ; 
    ofPoint p1 = quote.getPointByChar ( 0 , index ) ; 
    agent->startNewPath() ; 
    agent->position = p1 ; 
    agent->target = p1 ; 
    
    agent->maxVelocity = a_maxSpeed ; 
    agent->maxForce = a_maxForce ; 
    agent->targetBufferDist = a_targetBuffer ; 
    agent->pathSampling = a_pathSampling ; 
    

    agents.push_back( agent ) ; 

}

void testApp::exportPDF( ) 
{
    ofFileDialogResult result = ofSystemSaveDialog("quote", "Save your font layers" ) ; 
    
    
    //ofBackground( 0 , 0, 0 ) ; 
    for ( int i = 0 ; i < agents.size() ; i++ ) 
    {
        string _fileName = result.getPath() +"_"+ ofToString( i ) + ".pdf" ; 
        ofBeginSaveScreenAsPDF( _fileName ) ; 
        ofSetColor( 255 , 255 , 255 , 0 ) ; 
        ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ; 
        ofTranslate( quote.charTranslateOffset.x , quote.charTranslateOffset.y ) ; 
        //ofSetColor( 0 , 0 , 0 ) ; 
        //ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ; 
        agents[i]->draw( false ) ; 
        ofEndSaveScreenAsPDF() ; 
    }
    
    
    string combinedName = result.getPath() +"_combined.pdf" ; 
    ofBeginSaveScreenAsPDF( combinedName ) ; 
    ofSetColor( 255 , 255 , 255 , 0 ) ; 
    ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ;
    ofTranslate( quote.charTranslateOffset.x , quote.charTranslateOffset.y ) ; 

    for ( int i = 0 ; i < agents.size() ; i++ ) 
    {
        //string _fileName = result.getPath() +"_"+ ofToString( i ) + ".pdf" ; 
               //ofSetColor( 0 , 0 , 0 ) ; 
        //ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ; 
        agents[i]->draw( false ) ; 
        
    }
    ofEndSaveScreenAsPDF() ; 

    
}

void testApp::exportPNG( ) 
{
    ofFileDialogResult result = ofSystemSaveDialog("quote", "Save your font layers" ) ; 
    
    
    //ofBackground( 0 , 0, 0 ) ; 
    for ( int i = 0 ; i < agents.size() ; i++ ) 
    {
        string _fileName = result.getPath() +"_"+ ofToString( i ) + ".png" ; 
        //ofBeginSaveScreenAsPDF( _fileName ) ; 
        ofBackground( 0 , 0 , 0 ) ; 
        ofSetColor( 255 , 255 , 255 , 0 ) ; 
        ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ; 
        ofTranslate( quote.charTranslateOffset.x , quote.charTranslateOffset.y ) ; 
        //ofSetColor( 0 , 0 , 0 ) ; 
        //ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ; 
        agents[i]->draw( false ) ; 
        ofSaveScreen( _fileName ) ; 
       // ofEndSaveScreenAsPDF() ; 
    }
    
    
    string combinedName = result.getPath() +"_combined.png" ; 
   // ofBeginSaveScreenAsPDF( combinedName ) ; 
    ofSetColor( 255 , 255 , 255 , 0 ) ; 
    ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ;
    ofTranslate( quote.charTranslateOffset.x , quote.charTranslateOffset.y ) ; 
    
    for ( int i = 0 ; i < agents.size() ; i++ ) 
    {
        //string _fileName = result.getPath() +"_"+ ofToString( i ) + ".pdf" ; 
        //ofSetColor( 0 , 0 , 0 ) ; 
        //ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ; 
        agents[i]->draw( false ) ; 
        
    }
    
    ofSaveScreen( combinedName ) ; 
    //ofEndSaveScreenAsPDF() ; 
    
    
}

void testApp::setupGUI ( ) 
{
    float canvasHeight = 250 ;
    float sliderLength = 150 ;
    float padding = 15 ; 
    gui = new ofxUICanvas( 0 , ofGetHeight() - canvasHeight , ofGetWidth() , canvasHeight );
    
    //gui->addWidgetDown(new ofxUILabel("SLIDERS", OFX_UI_FONT_LARGE));         
    
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 12.0f, a_maxSpeed, "MAX SPEED")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f, 4.0f, a_rOffsetMaxSpeed , "MAX SPEED R OFFSET" )) ;

    
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 5.0f, a_maxForce, "MAX FORCE"));
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f, 4.0f, a_rOffsetMaxTurn , "MAX FORCE R OFFSET" )) ; 
    
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 25.0f, a_targetBuffer, "BUFFER DIST")); 
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 1 , 14 , a_pathSampling, "PATH SAMPLING")); 
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 1 , 125 , a_numAgents, "NUM AGENTS")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f , 250.0f , quote.charTranslateOffset.x , "CHAR TRANSLATE X")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f , 250.0f , quote.charTranslateOffset.y , "CHAR TRANSLATE Y")); 
    
    

    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    gui->loadSettings( "GUI/settings.xml" ) ; 
}

void testApp::resetAgents() 
{
    quote.resetQuotePaths( ) ; 
    agents.clear() ; 
    
    for ( int i = 0 ; i < a_numAgents ; i++ ) 
    {
        createNewAgent( ) ; 
    }  
    
    bRunAgents = false ; 
}

void testApp::saveProjectFile( ) 
{
    ofFileDialogResult saveResult = ofSystemSaveDialog( "myProject" , "Project Name?" ) ; 
    

    string path = saveResult.getPath() ; //
    
    int index = path.find( ".xml" ) ; 
    if ( index > 0 ) 
        cout << "user added .xml" << endl ; 
    else
        path += ".xml" ; 
    
    projectXml.setValue( "fontPath"  , quote.fontPath ) ; 
    projectXml.setValue( "fontSize" , quote.fontSize ) ; 
    
    for ( int i = 0 ; i < quote.textLines.size() ; i++ ) 
    {
        projectXml.setValue( "textLine" , quote.textLines[i] , i ) ; 
    }
    
    projectXml.saveFile( path ) ; 
    
}

void testApp::openProjectFile( ) 
{
    ofFileDialogResult loadResult = ofSystemLoadDialog(  "Open Project XML" ) ; 
    
    string path = loadResult.getPath() ; //
    
    projectXml.loadFile( path ) ; 
    
    quote.clearQuotes() ; 
    
    int numTagLines = projectXml.getNumTags( "textLine" ) ; 
    for ( int i = 0 ; i < numTagLines ; i++ ) 
    {
        quote.addLine( projectXml.getValue( "textLine", "NO TEXT" , i ) ) ; 
    }
    
    quote.setup( projectXml.getValue( "fontPath", "noFont" ) ,   
                 projectXml.getValue( "fontSize" , 12 ) ) ; 
    
    bRunAgents = true ; 
}

void testApp::keyPressed( int key )
{
    switch ( key ) 
    {
        case 'p':
        case 'P':
            exportPDF() ; 
            break ; 
            
        case 'l':
        case 'L':
            exportPNG() ; 
            break ; 
            
        case 'r':
        case 'R':
            resetAgents() ; 
            break ; 
            
        case 's':
        case 'S':
            saveProjectFile( ) ; 
            break ; 
            
        case 'o':
        case 'O':
            openProjectFile( ) ; 
            break ; 
            
        case ' ':
            bRunAgents = !bRunAgents ; 
            break ; 
    }
}
