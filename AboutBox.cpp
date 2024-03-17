//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "AboutBox.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TFAboutBox *FAboutBox;

extern AnsiString app_name;
extern AnsiString app_version;

//--------------------------------------------------------------------- 
__fastcall TFAboutBox::TFAboutBox(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------


void __fastcall TFAboutBox::OKButtonClick(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------



void __fastcall TFAboutBox::FormShow(TObject *Sender)
{
        ProductName->Caption=app_name;
        Version->Caption=app_version;
        Copyright->Caption="(c) 2006 Martin Raiber";
        Comments->Caption="Freeware. Keine Garantie auf Funktion - Benutzung auf eigene Gefahr";

}
//---------------------------------------------------------------------------

