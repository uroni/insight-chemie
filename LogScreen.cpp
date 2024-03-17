//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "LogScreen.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFLogScreen *FLogScreen;
//---------------------------------------------------------------------------
__fastcall TFLogScreen::TFLogScreen(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFLogScreen::Button1Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------
