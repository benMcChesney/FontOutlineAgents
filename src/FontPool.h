#ifndef FONTPOOL_H
#define FONTPOOL_H

#include "ofMain.h"
#include "FontData.h"


class FontPool
{
    public:
        FontPool() {}
        virtual ~FontPool() {}

        vector<FontData> pool ;

        void addFont( string fontPath , string _name )
        {
            FontData fd ;
            fd.filePath = fontPath ;
            fd.name = _name ;
            pool.push_back( fd ) ;
        }

        FontData getFontDataByName( string fontName )
        {
            for ( int i = 0 ; i < pool.size() ; i++ )
            {
                if ( fontName == pool[i].name )
                {
                   // ofTrueTypeFont font ;
                   // font.loadFont( pool[i].filePath , fontSize , true , true , true ) ;
                    return pool[i] ;
                }
            }

            cout << "@FontData::getFontDataByPath() no match was found for : " << fontName << endl ;

        }

        static FontPool* Instance()
        {
            static FontPool inst ;
            return &inst ;
        }



    protected:
    private:
};



#endif // FONTPOOL_H
