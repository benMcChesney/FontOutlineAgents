#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup()
{
    bRunAgents = false ; 
    
    
    
    ofSetLogLevel( OF_LOG_VERBOSE ) ; 
    ofBackground( 0 ) ; 
    ofSetFrameRate( 60 ) ; 
    ofSetVerticalSync( true ) ; 
    
    Tweenzor::init( ) ; 
    colorPicker.setColorRadius( 1.0 );
    
    //This is just an easy way to grab a color from a color palette
    colorPool.addColor( ofColor( 242 , 202 , 82 ) ) ; 
    colorPool.addColor( ofColor( 242 , 163 , 65 ) ) ; 
    colorPool.addColor( ofColor( 217 , 99 , 30 ) ) ; 
    colorPool.addColor( ofColor( 89 , 25 , 2 ) ) ; 
    
    //Add our quote in line by line
    quote.setup( "Batang.ttf" , 60 ) ; 
    
    //void addWordBlock ( string word , ofPoint position , int fontSize ) ; 
    float padding = 50 ; 
   // quote.addWordBlock( "WORD1", ofPoint( ofRandom( ofGetWidth() ) , ofRandom( padding , ofGetHeight() - padding ) )  , quote.fontSize ) ;
   // quote.addWordBlock( "WORD2", ofPoint( ofRandom( ofGetWidth() ) , ofRandom( padding , ofGetHeight() - padding ) )  , quote.fontSize ) ;
    quote.addWordBlock( "WORD3", ofPoint( ofRandom( ofGetWidth() ) , ofRandom( padding , ofGetHeight() - padding ) )  , quote.fontSize ) ;
    setupGUI( ) ; 
    
    canvasAlpha = 255.0f ; 
    
    ofPoint center = ofPoint ( ofGetWidth() / 2 , ofGetHeight() / 2 ) ; 

  
    
    //agentTypes.push_back("ribbon" ) ; 
    //agentTypes.push_back("circles" ) ;
    //agentTypes.push_back("triangle" ) ; 
    
    ofEnableAlphaBlending() ; 
    bDebugDraw = false ; 
    
}

void testApp::createNewWordBlock() 
{
    quote.addWordBlock( "" , ofPoint( ofGetWidth() / 2 , ofGetHeight() / 2 ) , newFontSize , true ) ; 
}

//--------------------------------------------------------------
void testApp::update()
{
    Tweenzor::update( ofGetElapsedTimeMillis() ) ; 
    
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
    
    colorPicker.update();
}
 
//--------------------------------------------------------------
void testApp::draw()
{      
    ofSetColor( 215 , 215 , 215 ) ; 
    ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ; 
        
    //newProjectBook.draw( ) ; 
    quote.drawWordBlocks( ) ; 
    
    //Call the agent draw() ! Nice and simple
    for ( int a = 0 ; a < agents.size() ; a++ )
    {
        ofPushMatrix() ;
            int wordIndex = quote.getQuotePathAt( a )->curLine ; 
            agents[a]->draw() ; 
        ofPopMatrix() ; 
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
    
    if ( name == "NUM AGENTS" ) 
    {
        a_numAgents =(int) ((ofxUISlider *) e.widget)->getScaledValue(); 
        resetAgents( ) ; 
    }
    
    if ( name == "MAX SPEED R OFFSET" ) 
        a_rOffsetMaxSpeed = ((ofxUISlider *) e.widget)->getScaledValue(); 
    
    if ( name == "MAX FORCE R OFFSET"  ) 
        a_rOffsetMaxTurn = ((ofxUISlider *) e.widget)->getScaledValue(); 
    
    if ( name == "TRAIL TYPES" ) 
    {
       // ((ofxUIRadio * ) e.widget)->ge
    }
    
    if ( name == "NEW FONT SIZE" ) 
    {
        newFontSize = ((ofxUISlider *) e.widget)->getScaledValue() ;
    }
    //newFontSize
    /*
     vector<string> hnames; hnames.push_back("LINES"); hnames.push_back("CIRCLES"); hnames.push_back("RECTANGLES");
     gui->addWidgetDown(new ofxUIRadio( radioSize , radioSize , "TRAIL TYPES", hnames, OFX_UI_ORIENTATION_HORIZONTAL));  
     */
   
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

void testApp::updateNewWordBlock ( string _word , float _fontSize ) 
{
    WordBlock * wb = quote.getLastWordBlockRef() ; 
    if ( wb == NULL ) 
    {
        cout << "word block is NULL " << endl ; 
        return ; 
    }
    
    wb->word = _word ; 
    wb->fontSize = _fontSize ; 
    wb->updateWord( ) ; 
}

void testApp::createNewAgent()
{
    int index = agents.size() ; 
    //Create our agent 
    Agent* agent = new RibbonAgent() ; 
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
        //ofTranslate( quote.charTranslateOffset.x , quote.charTranslateOffset.y ) ; 
     //   int wordIndex = quote.getQuotePathAt( i )->curLine ; 
     //   ofTranslate( quote.wordBlocks[ wordIndex ]->translate.x , quote.wordBlocks[ wordIndex ]->translate.y , 0 ) ; 
        //ofSetColor( 0 , 0 , 0 ) ; 
        //ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ; 
        agents[i]->draw( false ) ; 
        ofEndSaveScreenAsPDF() ; 
    }
    
    
    string combinedName = result.getPath() +"_combined.pdf" ; 
    ofBeginSaveScreenAsPDF( combinedName ) ; 
    ofSetColor( 255 , 255 , 255 , 0 ) ; 
    ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ;
    //ofTranslate( quote.charTranslateOffset.x , quote.charTranslateOffset.y ) ; 

    for ( int i = 0 ; i < agents.size() ; i++ ) 
    {
        //string _fileName = result.getPath() +"_"+ ofToString( i ) + ".pdf" ; 
               //ofSetColor( 0 , 0 , 0 ) ; 
        //ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ; 
        agents[i]->draw( false ) ; 
        
    }
    ofEndSaveScreenAsPDF() ; 

    
}


void testApp::setupGUI ( ) 
{
    float canvasHeight = 250 ;
    float sliderLength = 100 ;
    float padding = 15 ; 
    gui = new ofxUICanvas( 0 , ofGetHeight() - canvasHeight , ofGetWidth() , canvasHeight );
    //gui->addWidgetDown(new ofxUILabel("SLIDERS", OFX_UI_FONT_LARGE));         
    gui->addWidgetRight(new ofxUILabel("SPACE - play/pause , S - save project", OFX_UI_FONT_LARGE));  
    gui->addWidgetRight(new ofxUILabel("R - reset , P - export PDF , N - New Word Box , E - Edit Word , BACKSPACE - Delete Word", OFX_UI_FONT_MEDIUM ));   

    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 12.0f, a_maxSpeed, "MAX SPEED")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f, 4.0f, a_rOffsetMaxSpeed , "MAX SPEED R OFFSET" )) ;
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0, 5.0f, a_maxForce, "MAX FORCE"));
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f, 4.0f, a_rOffsetMaxTurn , "MAX FORCE R OFFSET" )) ; 
    
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 50.0f, a_targetBuffer, "BUFFER DIST")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 1 , 14 , a_pathSampling, "PATH SAMPLING")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 1 , 125 , a_numAgents, "NUM AGENTS")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 1 , 125 , newFontSize, "NEW FONT SIZE" ));
    
    //newFontSize
    float radioSize = 45 ; 
    vector<string> hnames; hnames.push_back("LINES"); hnames.push_back("CIRCLES"); hnames.push_back("RECTANGLES");
	gui->addWidgetDown(new ofxUIRadio( radioSize , radioSize , "TRAIL TYPES", hnames, OFX_UI_ORIENTATION_HORIZONTAL));     
    //vector<string> vnames;
    /*
    vnames.push_back("ROCKS");
    vnames.push_back("MY");
    vnames.push_back("SOCKS");
    
    ofxUIRadio *radio = (ofxUIRadio *) gui->addWidgetDown(new ofxUIRadio(sliderLength, sliderLength, "VERTICAL RADIO", vnames, OFX_UI_ORIENTATION_VERTICAL)); 
    radio->activateToggle("SOCKS"); */
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    gui->loadSettings( "GUI/settings.xml" ) ; 
   // gui->toggleVisible() ; 
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
    
    for ( int i = 0 ; i < quote.wordBlocks.size() ; i++ ) 
    {
        projectXml.setValue( "textLine" , quote.wordBlocks[i]->word , i ) ; 
    }
    
    projectXml.setValue ( "MAX SPEED" , a_maxSpeed ) ; 
    projectXml.setValue ( "MAX SPEED R OFFSET" , a_rOffsetMaxSpeed ) ; 
    projectXml.setValue ( "MAX FORCE" , a_maxForce ) ; 
    projectXml.setValue ( "MAX FORCE R OFFSET" , a_rOffsetMaxTurn ) ; 
    projectXml.setValue ( "BUFFER DIST" , a_targetBuffer ) ; 
    projectXml.setValue ( "PATH SAMPLING" , a_pathSampling ) ; 
    projectXml.setValue ( "NUM AGENTS" , a_numAgents ) ; 
    projectXml.saveFile( path ) ; 
    
}

void testApp::openProjectFile( ) 
{
    ofFileDialogResult loadResult = ofSystemLoadDialog(  "Open Project XML" ) ; 
    
    string path = loadResult.getPath() ; //
    
    projectXml.loadFile( path ) ; 
    
    quote.clearQuotes() ; 
    
    int numTagLines = projectXml.getNumTags( "textLine" ) ; 
    
    int fontSize = projectXml.getValue( "fontSize" , 12 ) ; 
    for ( int i = 0 ; i < numTagLines ; i++ ) 
    {
        //quote.addLine( projectXml.getValue( "textLine", "NO TEXT" , i ) ) ; 
        quote.addWordBlock( projectXml.getValue( "textLine", "NO TEXT" , i ) , ofPoint ( 0 , 0 ) , 0 ) ;   
    }
    
    quote.setup( projectXml.getValue( "fontPath", "noFont" ) ,   
                 fontSize ) ; 
    
    a_maxSpeed = projectXml.getValue ( "MAX SPEED" , a_maxSpeed , a_maxSpeed ) ; 
    a_rOffsetMaxSpeed = projectXml.getValue ( "MAX SPEED R OFFSET" , a_rOffsetMaxSpeed , a_rOffsetMaxSpeed ) ; 
    a_maxForce = projectXml.getValue ( "MAX FORCE" , a_maxForce , a_maxForce ) ; 
    a_rOffsetMaxTurn = projectXml.getValue ( "MAX FORCE R OFFSET" , a_rOffsetMaxTurn , a_rOffsetMaxTurn ) ; 
    a_targetBuffer = projectXml.getValue ( "BUFFER DIST" , a_targetBuffer , a_targetBuffer ) ; 
    a_pathSampling = projectXml.getValue ( "PATH SAMPLING" , a_pathSampling , a_pathSampling ) ; 
    a_numAgents = projectXml.getValue ( "NUM AGENTS" , a_numAgents , a_numAgents ) ; 
   
    bRunAgents = false ; 
}

void testApp::mousePressed ( int x , int y , int button )
{
    //newProjectBook.input( x , y ) ; 
    quote.inputDown ( x , y ) ; 
    
}


void testApp::initProject ( )
{
    quote.clearQuotes() ; 
    newTextLine = "BLANK" ;
    
    
}

void testApp::mouseDragged ( int x , int y , int button ) 
{
    quote.inputMove ( x , y ) ;
}

void testApp::mouseReleased( int x , int y , int button ) 
{
    quote.inputUp ( x , y ) ;
}



void testApp::keyPressed( int key )
{
    cout << "key : " << key << endl ; 
 //   if ( canvasAlpha > 0.0f ) 
 //   {
        WordBlock * wb = quote.getLastWordBlockRef( ) ; 
        if ( wb == NULL ) 
        {
            switch ( key ) 
            {
                case 'p':
                case 'P':
                    exportPDF() ; 
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
                //    openProjectFile( ) ; 
                    break ; 
                    
                case ' ':
                    bRunAgents = !bRunAgents ; 
                    break ; 
                    
                case 'd':
                case 'D':
                    bDebugDraw = !bDebugDraw ; 
                    break ; 

                case 'n':
                case 'N':
                    cout << "new WordBlock" << endl ; 
                    createNewWordBlock() ; 
                    break ; 
                    
                case 13 :
                    cout << "end typing wordBlock" << endl ; 
                    break ; 
                    
                case 'e':
                case 'E':
                   // editWordBlockAt ( mouseX , mouseY ) ; 
                    break ; 
                    
                case 127 :
                    // removeWordBlockAt ( mouseX , mouseY ) ;
                    break ;
                    
            }
        }
        else
        {
            if ( key == 13 ) 
            {
                wb->bEditable = false ;
                return ; 
            }
            
            else if ( key == 127 ) 
            {
                string word = wb->word ; 
                if ( word.size() > 0 ) 
                {
                    string word1 = word.substr( 0 , word.size()-1 ) ; 
                    word = word1 ; 
                }
                wb->word = word ; 
                updateNewWordBlock( wb->word , newFontSize ) ; 
                return ; 
            }

            wb->word += key ; 
            //void testApp::updateNewWordBlock ( string _word , float _fontSize ) 
            updateNewWordBlock( wb->word , newFontSize ) ; 
                               
        }
  //  }
        
}
