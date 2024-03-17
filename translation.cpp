#include <string>

#pragma hdrstop

#include "meshlist.h"
#include "stringtools.h"

meshlist trans_ml;


bool InitTranslation(void)
{
        if( trans_ml.open("translation.cfg") )
        {
                if( trans_ml.selectmesh("settings") )
                {
                        std::string lang=trans_ml.getvalue("language");
                        if( trans_ml.selectmesh( lang ) )
                        {
                                return true;
                        }
                }
        }
        return false;

}

std::string Translate(std::string str, std::string vars)
{
        std::string txt=trans_ml.getvalue(str);

        if( vars!="" )
        {
                std::vector<std::string> tok;

                Tokenize(vars,tok, "|" );

                for(size_t i=0;i<tok.size();++i)
                {
                        std::string key=getuntil("=", tok[i] );
                        std::string value=getafter("=", tok[i] );

                        txt=greplace("["+key+"]", value, txt);
                }
        }

        return txt;
}
