#ifndef HITBUTTON_H
#define HITBUTTON_H


class HitButton
{
    public:
        HitButton()
        {

        }

        virtual ~HitButton()
        {

        }

        ofRectangle area ;
        ofColor color ;
        ofColor textColor ;
        string label ;

        void setup ( string _label , float x , float y , float width , float height )
        {
            label = _label ;
            area = ofRectangle( x , y , width , height ) ;
            color = ofColor( 15 , 15 , 15 ) ;
            textColor = ofColor( 215 , 215 , 215 ) ;
        }

        void update ( )
        {

        }

        bool hitTest ( float x , float y )
        {
            return ( ( x > area.x && x < (area.x + area.width) ) && ( y > area.y && y < (area.y + area.height) ) ) ;
        }

        void draw ( )
        {
            ofSetColor( color ) ;
            ofRect( area ) ;
            ofSetColor( textColor ) ;
            ofDrawBitmapStringHighlight( label , area.x + 5 , area.y + 20 ) ;
        }

    protected:
    private:
};

#endif // HITBUTTON_H
