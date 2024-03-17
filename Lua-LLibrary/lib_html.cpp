#include <string>

#pragma hdrstop

#include "lua_macros.h"
#include "lua.h"
#include "MainScreen.h"
#include "CSimMgr.h"

bool helpbox_visible=false;


LUAF(ShowHTML)
{
        c1STRINGARG(ShowHTML);

        if( helpbox_visible==false )
        {
                FMainScreen->EnableHelpBox();
                helpbox_visible=true;
        }


                AnsiString file=lua_tostring(lua,1);

                file="file://"+ExtractFilePath(ParamStr(0) )+file;

                WideString tmp=file;
                wchar_t *tmp2=tmp.c_bstr();

                FMainScreen->WebBrowser->Navigate( tmp2 );

        return 0;        
}

LUAF(HideHTML)
{
        if( helpbox_visible==true )
        {
                FMainScreen->DisableHelpBox();
                helpbox_visible=false;
        }

        return 0;
}




luaL_reg lib_html [] = {
        {"ShowHTML", ShowHTML},
        {"HideHTML", HideHTML},
	{NULL, NULL}
};