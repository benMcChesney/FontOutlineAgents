//
//  ColorPool.h
//  emptyExample
//
//  Created by Ben McChesney on 2/21/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef emptyExample_ColorPool_h
#define emptyExample_ColorPool_h


#include "ofMain.h"

class ColorPool 
{
    public :
        ColorPool ( ) 
        {
        
        }
    
        vector <ofColor> pool ; 
    
    
        //Add a color to our pool
        void addColor ( ofColor _c ) 
        {
            pool.push_back( _c ) ; 
        }
    
        // retrieve a color from the palette
        ofColor getRandomColor ( ) 
        {
            int randIndex = ofRandom ( 0 , pool.size() ) ; 
            return pool[randIndex] ; 
        }
    
        void clear ( ) 
        {
            pool.clear() ; 
        }
};
#endif
