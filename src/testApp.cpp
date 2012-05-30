#include "testApp.h"


//--------------------------------------------------------------
void testApp::setup()
{
    bRunAgents = false ; 
    
    instructionsFont.loadFont("GUI/NewMedia Fett.ttf", 16 ) ; 
    
    ofSetLogLevel( OF_LOG_VERBOSE ) ; 
    ofBackground( 0 ) ; 
    ofSetFrameRate( 60 ) ; 
    ofSetVerticalSync( true ) ; 
    
    Tweenzor::init( ) ; 
    
    //This is just an easy way to grab a color from a color palette
    colorPool.addColor( ofColor( 242 , 202 , 82 ) ) ; 
    colorPool.addColor( ofColor( 242 , 163 , 65 ) ) ; 
    colorPool.addColor( ofColor( 217 , 99 , 30 ) ) ; 
    colorPool.addColor( ofColor( 89 , 25 , 2 ) ) ; 
    
    //Add our quote in line by line
    quote.addLine( "TESTING" ) ;
    quote.addLine( "NOW TESTING" ) ;
    quote.setup( "Batang.ttf" , 60 ) ; 
    setupGUI( ) ; 
    splashPageAlpha = 255.0f ; 
    newProjectAlpha = 0.0f ; 
    canvasAlpha = 0.0f ; 
    
    ofPoint center = ofPoint ( ofGetWidth() / 2 , ofGetHeight() / 2 ) ; 
    newProjectBtn.setup( "GUI/new_button.png" ,center.x , center.y - 75 , true )  ; 
    loadProjectBtn.setup( "GUI/load_button.png" ,center.x , center.y + 75 , true )  ;
    loadFontBtn.setup ( "GUI/load_font_button.png" , center.x - 150 , center.y - 175 , true ) ;
    loadFontBtn.hitRect.width *= 0.5f ; 
    loadFontBtn.hitRect.height *= 0.5f ; 
    
    addLineBtn.setup( "GUI/add_text_line.png" ,center.x - 240 , center.y + 35 , true )  ;  
    
    finishSetupBtn.setup( "GUI/finish_setup_button.png" ,center.x , center.y + 300 , true )  ;   
    
    ofEnableAlphaBlending() ; 
    
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
}
 
//--------------------------------------------------------------
void testApp::draw()
{      
    if ( splashPageAlpha > 0.0f ) 
    {
        ofSetColor( 0 , 0 , 0, splashPageAlpha ) ; 
        ofRect( 0 , 0, ofGetWidth() , ofGetHeight() ) ;
        
        ofSetColor ( 255 , 255 , 255 , splashPageAlpha ) ; 
        newProjectBtn.draw( ) ; 
        loadProjectBtn.draw( ) ; 
    }
    
    if ( newProjectAlpha > 0.0f ) 
    {
        ofSetColor ( 255 , 255 , 255 , newProjectAlpha ) ; 
        ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ; 
        
        ofPoint textStart = ofPoint ( loadFontBtn.hitRect.x + 250 , loadFontBtn.hitRect.y + 20 ) ; 
        
        ofColor titleBack = ofColor ( 225 , 225 , 225 ) ; 
        ofColor titleText = ofColor ( 65 , 65 , 65 ) ; 
        
        ofColor pathBack = ofColor ( 255 , 255 , 255 ) ; 
        ofColor pathText = ofColor( 20 , 20 , 20 ) ; 
        
        //Draw Font PATH Title
        ofSetColor( titleBack , newProjectAlpha ) ;
        ofRect( instructionsFont.getStringBoundingBox( "FONT PATH: " , textStart.x , textStart.y ) ) ; 
        ofSetColor( titleText , newProjectAlpha ) ; 
        instructionsFont.drawString( "FONT PATH: " , textStart.x , textStart.y ) ; 
        
        //Draw Font PATH value
        ofSetColor( pathBack , newProjectAlpha * .25 ) ;
        ofRect( instructionsFont.getStringBoundingBox( quote.fontPath , textStart.x , textStart.y + 40 ) ) ; 
        ofSetColor( pathText , newProjectAlpha ) ; 
        instructionsFont.drawString( quote.fontPath , textStart.x , textStart.y + 40 ) ;
        
        //Draw Font Size TITLE
        ofSetColor( titleBack , newProjectAlpha ) ;
        ofRect( instructionsFont.getStringBoundingBox( "FONT SIZE: " , textStart.x , textStart.y + 140 ) ) ; 

        ofSetColor( titleText , newProjectAlpha ) ; 
        instructionsFont.drawString( "FONT SIZE \n( right / left ) : " , textStart.x , textStart.y + 140 ) ; 
               
        //Draw Font Size VALUE
        ofSetColor( pathBack , newProjectAlpha * .25 ) ;
        ofRect( instructionsFont.getStringBoundingBox( "FONT SIZE: " , textStart.x , textStart.y + 200 ) ) ; 

        ofSetColor( pathText , newProjectAlpha ) ; 
        instructionsFont.drawString( ofToString( quote.fontSize ) , textStart.x , textStart.y + 200 ) ; 
        
        textStart.y = addLineBtn.hitRect.y + 35  ; 
        ofSetColor ( 255 , 255 , 255 , newProjectAlpha ) ; 
        loadFontBtn.draw( ) ;
        fontSize = quote.fontSize ;
        
        int numLines = quote.textLines.size() ; 
        cout << "numLines " << numLines << endl ; 
        ySpacing  = 20.0f ; 
        float totalHeight = numLines * ySpacing ;
        
        ofPushMatrix( ) ;
            //ofTranslate( 0 , totalHeight ) ; 
            addLineBtn.draw( )  ;
        ofPopMatrix( ) ; 
        
        for ( int i = 0 ; i < numLines ; i++ ) 
        {
            ofSetColor( 20 , 20 , 20 ) ;
            cout << "line : " << i << " is : " << quote.textLines[i] << endl ; 
            instructionsFont.drawString( quote.textLines[i] , addLineBtn.hitRect.x + addLineBtn.hitRect.width + 50 ,  textStart.y + (i) * ySpacing ); 
        }
        
        ofSetColor( 255 , newProjectAlpha ) ; 
        finishSetupBtn.draw( )  ;
        
        ofSetColor ( pathText , newProjectAlpha ) ; 
        instructionsFont.drawString( newTextLine , addLineBtn.hitRect.x + addLineBtn.hitRect.width + 50 ,  textStart.y + totalHeight ) ; 
    }
    
    if ( canvasAlpha > 0.0f ) 
    {
        ofSetColor( 215 , canvasAlpha ) ; 
        ofRect( 0 , 0 , ofGetWidth() , ofGetHeight() ) ; 
        
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
        quote.charTranslateOffset.x = ((ofxUISlider *) e.widget)->getScaledValue(); 
    
    if ( name == "CHAR TRANSLATE Y" )
        quote.charTranslateOffset.y = ((ofxUISlider *) e.widget)->getScaledValue(); 
    
    if ( name == "MAX SPEED R OFFSET" ) 
        a_rOffsetMaxSpeed = ((ofxUISlider *) e.widget)->getScaledValue(); 
    
    if ( name == "MAX FORCE R OFFSET"  ) 
        a_rOffsetMaxTurn = ((ofxUISlider *) e.widget)->getScaledValue(); 
    

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


void testApp::setupGUI ( ) 
{
    float canvasHeight = 250 ;
    float sliderLength = 150 ;
    float padding = 15 ; 
    gui = new ofxUICanvas( 0 , ofGetHeight() - canvasHeight , ofGetWidth() , canvasHeight );
    //gui->addWidgetDown(new ofxUILabel("SLIDERS", OFX_UI_FONT_LARGE));             
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 12.0f, a_maxSpeed, "MAX SPEED")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f, 4.0f, a_rOffsetMaxSpeed , "MAX SPEED R OFFSET" )) ;
    gui->addWidgetRight(new ofxUILabel("R - reset , P - export PDF ", OFX_UI_FONT_LARGE));   
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 5.0f, a_maxForce, "MAX FORCE"));
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f, 4.0f, a_rOffsetMaxTurn , "MAX FORCE R OFFSET" )) ; 
    gui->addWidgetRight(new ofxUILabel("SPACE - play/pause , S - save project", OFX_UI_FONT_LARGE));   
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 25.0f, a_targetBuffer, "BUFFER DIST")); 
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 1 , 14 , a_pathSampling, "PATH SAMPLING")); 
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 1 , 125 , a_numAgents, "NUM AGENTS")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f , ofGetWidth()  , quote.charTranslateOffset.x , "CHAR TRANSLATE X")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f , ofGetHeight() , quote.charTranslateOffset.y , "CHAR TRANSLATE Y")); 
    
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    gui->loadSettings( "GUI/settings.xml" ) ; 
    gui->toggleVisible() ; 
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
    
    //gui = new ofxUICanvas( 0 , ofGetHeight() - canvasHeight , ofGetWidth() , canvasHeight );
    //gui->addWidgetDown(new ofxUILabel("SLIDERS", OFX_UI_FONT_LARGE));             
    /*
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 12.0f, a_maxSpeed, "MAX SPEED")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f, 4.0f, a_rOffsetMaxSpeed , "MAX SPEED R OFFSET" )) ;
    gui->addWidgetRight(new ofxUILabel("R - reset , P - export PDF ", OFX_UI_FONT_LARGE));   
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 5.0f, a_maxForce, "MAX FORCE"));
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f, 4.0f, a_rOffsetMaxTurn , "MAX FORCE R OFFSET" )) ; 
    gui->addWidgetRight(new ofxUILabel("SPACE - play/pause , S - save project", OFX_UI_FONT_LARGE));   
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 0.0, 25.0f, a_targetBuffer, "BUFFER DIST")); 
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 1 , 14 , a_pathSampling, "PATH SAMPLING")); 
    gui->addWidgetDown(new ofxUISlider( sliderLength , 15 , 1 , 125 , a_numAgents, "NUM AGENTS")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f , ofGetWidth()  , quote.charTranslateOffset.x , "CHAR TRANSLATE X")); 
    gui->addWidgetRight(new ofxUISlider( sliderLength , 15 , 0.0f , ofGetHeight() , quote.charTranslateOffset.y , "CHAR TRANSLATE Y")); 
    */
    
    projectXml.setValue ( "MAX SPEED" , a_maxSpeed ) ; 
    projectXml.setValue ( "MAX SPEED R OFFSET" , a_rOffsetMaxSpeed ) ; 
    projectXml.setValue ( "MAX FORCE" , a_maxForce ) ; 
    projectXml.setValue ( "MAX FORCE R OFFSET" , a_rOffsetMaxTurn ) ; 
    projectXml.setValue ( "BUFFER DIST" , a_targetBuffer ) ; 
    projectXml.setValue ( "PATH SAMPLING" , a_pathSampling ) ; 
    projectXml.setValue ( "NUM AGENTS" , a_numAgents ) ; 
    projectXml.setValue ( "CHAR TRANSLATE X" , quote.charTranslateOffset.x ) ; 
    projectXml.setValue ( "CHAR TRANSLATE Y" , quote.charTranslateOffset.y ) ; 
    
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
    
    a_maxSpeed = projectXml.getValue ( "MAX SPEED" , a_maxSpeed , a_maxSpeed ) ; 
    a_rOffsetMaxSpeed = projectXml.getValue ( "MAX SPEED R OFFSET" , a_rOffsetMaxSpeed , a_rOffsetMaxSpeed ) ; 
    a_maxForce = projectXml.getValue ( "MAX FORCE" , a_maxForce , a_maxForce ) ; 
    a_rOffsetMaxTurn = projectXml.getValue ( "MAX FORCE R OFFSET" , a_rOffsetMaxTurn , a_rOffsetMaxTurn ) ; 
    a_targetBuffer = projectXml.getValue ( "BUFFER DIST" , a_targetBuffer , a_targetBuffer ) ; 
    a_pathSampling = projectXml.getValue ( "PATH SAMPLING" , a_pathSampling , a_pathSampling ) ; 
    a_numAgents = projectXml.getValue ( "NUM AGENTS" , a_numAgents , a_numAgents ) ; 
    quote.charTranslateOffset.x = projectXml.getValue ( "CHAR TRANSLATE X" , quote.charTranslateOffset.x , quote.charTranslateOffset.x ) ; 
    quote.charTranslateOffset.y = projectXml.getValue ( "CHAR TRANSLATE Y" , quote.charTranslateOffset.y , quote.charTranslateOffset.y ) ; 
    
    bRunAgents = false ; 
}

void testApp::mousePressed ( int x , int y , int button )
{
    if ( splashPageAlpha > 0.0f ) 
    {
        if ( newProjectBtn.hitTest( x , y ) == true ) 
        {
            Tweenzor::add( &splashPageAlpha , splashPageAlpha , 0.0f , 0.0f , 0.75f , EASE_OUT_QUAD ) ;
            Tweenzor::add( &newProjectAlpha , newProjectAlpha , 255.0f , 0.0f , 0.75f , EASE_OUT_QUAD ) ;
            cout << " NEW PROJECT!! " << endl ; 
            initProject() ; 
            
        }
        if ( loadProjectBtn.hitTest( x , y ) == true ) 
        {
            cout << " OPENING PROJECT!" << endl ;
            Tweenzor::add( &splashPageAlpha , splashPageAlpha  , 0.0f , 0.0f , 0.75f , EASE_OUT_QUAD ) ; 
            Tweenzor::add( &newProjectAlpha , newProjectAlpha , 255.0f , 0.0f , 0.75f , EASE_OUT_QUAD ) ;
            openProjectFile() ;   
        }
    }
    
    if ( newProjectAlpha > 0.0f ) 
    {
        
        if ( loadFontBtn.hitTest( x , y ) == true )
        {
            ofFileDialogResult ttfResult = ofSystemLoadDialog( "Open any TTF or OTF font" ) ; 
            string path = ttfResult.getPath() ; 
            int ttfIndex = path.find( ".ttf" ) ;
            int otfIndex = path.find( ".otf" ) ; 
            
            if ( ttfIndex > 0 || otfIndex > 0 ) 
            {
                cout << "valid ttf or otf file" << endl ; 
                int lastIndex = path.find_last_of("/") ; 
                string shortName = path.substr( lastIndex+1 ) ; 
                quote.fontPath = shortName ; //ofToDataPath( path )  ; 
                
            }
        }
        
        if ( addLineBtn.hitTest( x , y ) == true ) 
        {
            quote.addLine( newTextLine ) ; 
            newTextLine = "blank" ; 
            //Tweenzor::add( &addLineBtn.hitRect.y , addLineBtn.hitRect.y , addLineBtn.hitRect.y + ySpacing , 0.0f , 0.5f , EASE_OUT_QUAD ) ; 
        }
        
        if ( finishSetupBtn.hitTest( x , y ) )
        {
            quote.init ( ) ; 
            resetAgents() ; 
            Tweenzor::add( &newProjectAlpha , newProjectAlpha  , 0.0f , 0.0f , 0.5f , EASE_OUT_QUAD ) ; 
            Tweenzor::add( &canvasAlpha , canvasAlpha , 255.0f , 0.5f , 0.5f , EASE_OUT_QUAD ) ;
            gui->setVisible( true ) ; 
        }
    }
    
}


void testApp::initProject ( )
{
    quote.clearQuotes() ; 
    newTextLine = "BLANK" ;
    
    
}

void testApp::mouseDragged ( int x , int y , int button ) 
{
    
}

void testApp::mouseReleased( int x , int y , int button ) 
{
    
}

void testApp::keyPressed( int key )
{
    cout << "key : " << key << endl ; 
    if ( canvasAlpha > 0.0f ) 
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
        }
    }
    
    if ( newProjectAlpha > 0.0f ) 
    {
                    
        //bNewTextSizeInit
        
        switch ( key ) 
        {
            //right
            case 356 :
                if ( fontSize > 0 ) 
                    fontSize-- ; 
                break ; 
                //left
            case 358 :
                fontSize += 1 ; 
                break ; 
                           
                        
            case 127 : 
                //st = myString.substr(0, myString.size()-1);
                if ( newTextLine.size() > 0 ) 
                    newTextLine = newTextLine.substr( 0 , newTextLine.size()-1 ) ; 
                break ; 

        }
        
        if ( key != 127 && newTextLine.size() < 40 )
            newTextLine += key ; 
        
        
        
        quote.fontSize = fontSize ; 
    }
        
}
