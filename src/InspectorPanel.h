#ifndef INSPECTORPANEL_H
#define INSPECTORPANEL_H

#include "HitButton.h"
#include "ofxColorPicker.h"
#include "Events.h"
#include "FontPool.h"
#include "FontData.h"

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

        vector<FontData> fonts ;
        int currentFont ;

        void setup ( )
        {
            area = ofRectangle( 0 , 0 , 305 , ofGetHeight() - 125 ) ;
            color = ofColor( 125 , 125 , 125 , 125 );

            fontBegin = ofPoint ( 25 , 425 )  ;
            fontYSpacing = 25 ;

            addColor.setup( "ADD COLOR" , 15 , 315 , 125 , 50 ) ;
            removeColor.setup( "REMOVE LAST COLOR" , 155 , 315 , 125 , 50 ) ;

            colorPicker.setColorRadius( 1.0 ) ;
            colorPicker.setColorAngle( 0.5 ) ;

            //Add default font
            addFont( "Batang.ttf" ) ;
            addFont( "CooperBlack.ttf" ) ;
        }

        void addFont( string fontPath )
        {
            //Shorten Font
            int _slashIndex = fontPath.find( "\data" ) ;
            string shortPath = fontPath ;

            if ( _slashIndex > 0 )
            {
                shortPath = fontPath.substr( _slashIndex + 5 ) ;
            }
            cout << "_slashIndex is : " << _slashIndex << endl ;

            currentFont = 0 ;
            FontData fontData ;
            fontData.filePath = fontPath ;
            fontData.name = shortPath ;
            fonts.push_back( fontData ) ;

            cout << "added " << shortPath << " with path of : " << fontPath << endl ;
        }

        string getSelectedFontPath( )
        {
            return fonts[ currentFont ].filePath ;
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

            for ( int i = 0 ; i < fonts.size() ; i++ )
            {
                float fontBlockWidth = 300 ;
                ofRectangle bounds = ofRectangle( fontBegin.x , fontBegin.y + i * fontYSpacing - fontYSpacing/2, fontBlockWidth , fontYSpacing  ) ;
                if ( hitTest( x , y , bounds ) )
                {
                    cout << " hit test SUCCESS on @ " << i << endl ;
                    currentFont = i ;
                    ofNotifyEvent( Events::Instance()->FONT_UPDATED , currentFont ) ;
                }
            }

        }

        bool hitTest ( float x , float y , ofRectangle b )
        {
            return ( ( x > b.x && x < b.x + b.width ) && ( y > b.y && y < b.y + b.height ) ) ;
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

                if ( c == colors.size() - 1 )
                {
                    ofSetLineWidth( 5 ) ;
                    ofNoFill() ;
                    ofSetColor( 255 , 105 , 180 ) ;
                    ofRect( 10 , 60 * c - 5, 60 , 60 ) ;
                    ofFill() ;
                    ofSetColor( colors[c] , 125 ) ;
                    ofRect( 15 , 60 * c , 50 , 50 ) ;
                }
                ofSetColor( colors[c] ) ;
                ofRect( 15 , 60 * c , 50 , 50 ) ;
            }
            ofPopMatrix( ) ;

            ofSetColor( 255 , 255 ,255 ) ;

            //Draw Fonts
            ofPushMatrix();
                ofTranslate( fontBegin.x , fontBegin.y , 0 ) ;
                ofSetColor( 15 , 15 , 15 ) ;
                ofDrawBitmapString( "FONTS LOADED:" , 0 , -25 ) ;

                ofSetColor( 255 , 255 , 255 ) ;
                for ( int i = 0 ; i < fonts.size() ; i++ )
                {
                    if ( currentFont == i )
                        ofDrawBitmapStringHighlight( fonts[ i ].name , 0 , i* fontYSpacing ) ;
                    else
                        ofDrawBitmapString(  fonts[ i ].name , 0 , i * fontYSpacing ) ;
                }

            ofPopMatrix() ;

        }

        ofPoint fontBegin ;
        float fontYSpacing ;

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
