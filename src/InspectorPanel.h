#ifndef INSPECTORPANEL_H
#define INSPECTORPANEL_H

#include "HitButton.h"
#include "ofxColorPicker.h"
#include "Events.h"

class InspectorPanel
{
    public:
        InspectorPanel() {}
        virtual ~InspectorPanel() {}

        ofRectangle area ;
        ofColor color ;
        ofxColorPicker colorPicker ;


        HitButton addColor ;
        HitButton removeColor ;
        vector<ofColor> colors ;

        vector<string> fontPaths ;
        int currentFont ;

        void setup ( )
        {
            area = ofRectangle( 0 , 0 , 305 , ofGetHeight() - 125 ) ;
            color = ofColor( 125 , 125 , 125 , 125 );
            addColor.setup( "ADD COLOR" , 15 , 315 , 125 , 50 ) ;
            removeColor.setup( "REMOVE LAST COLOR" , 155 , 315 , 125 , 50 ) ;

            colorPicker.setColorRadius( 1.0 ) ;
            colorPicker.setColorAngle( 0.5 ) ;

            //Add default font
            addFont( "Batang.ttf" ) ;
        }

        void addFont( string fontPath )
        {
            currentFont = 0 ;
            fontPaths.push_back( fontPath ) ;
        }

        string getSelectedFontPath( )
        {
            return fontPaths[ currentFont ] ;
        }

        void update ( )
        {
            colorPicker.update();
        }

        void input ( float x , float y )
        {
            if ( addColor.hitTest( x , y ) )
            {
                cout << "hitting add color!" << endl ;
                ofColor c = colorPicker.getColor() ;
                ofNotifyEvent( Events::Instance()->ADD_NEW_COLOR , c ) ;
                addNewColorSwatch( c ) ;
            }
            if ( removeColor.hitTest( x , y ) )
            {
                cout << "hitting remove color!" << endl ;
                removeLastColorSwatch( ) ;
            }
        }

        void draw ( )
        {
            ofSetColor( color ) ;
            ofRect( area ) ;

            ofSetColor( 235 )  ;
            ofDrawBitmapString( "FPS " + ofToString( ofGetFrameRate() ) , 25 , 25 ) ;

            colorPicker.draw( 10 , 10 , 150 , 300 );
            addColor.draw( ) ;
            removeColor.draw( ) ;


            ofPushMatrix( ) ;
            ofTranslate( 225 , 15 , 0 ) ;
            for ( int c = 0 ; c < colors.size() ; c++ )
            {
                ofSetColor( colors[c] ) ;
                ofRect( 15 , 60 * c , 50 , 50 ) ;
            }
            ofPopMatrix( ) ;

        }

        void removeLastColorSwatch ( )
        {
            if ( colors.size() > 0 )
                colors.pop_back() ;
        }

        void addNewColorSwatch ( ofColor c )
        {
            if ( colors.size() < 5 )
                colors.push_back( c ) ;
            else
                cout << "AT MAX COLORS!" << endl ;
        }

    protected:
    private:
};

#endif // INSPECTORPANEL_H
