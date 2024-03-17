//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "types.h"
#include "settings.h"
#include "meshlist.h"

#include "LoadingScreen.h"


#include "SimParams.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFSimParams *FSimParams;
//---------------------------------------------------------------------------
__fastcall TFSimParams::TFSimParams(TComponent* Owner)
        : TForm(Owner)
{
        ml=new meshlist;
}
//---------------------------------------------------------------------------

void __fastcall TFSimParams::OKClick(TObject *Sender)
{
ml->save();
Visible=false;
}
//---------------------------------------------------------------------------


void __fastcall TFSimParams::FormShow(TObject *Sender)
{        
        ml->open( "settings.cfg" );

        ListBox1->Clear();

        if( ml->selectmesh("simulation") )
        {
                int i=1;
                std::string key;
                while( (key=ml->getkey(i))!="" )
                {
                        ListBox1->Items->Add( key.c_str() );
                        ++i;
                }
        }

        Label2->Caption="";
        Edit1->Text="";
}
//---------------------------------------------------------------------------

void __fastcall TFSimParams::ListBox1Click(TObject *Sender)
{
        int idx=ListBox1->ItemIndex;

        if( idx>-1 && idx < ListBox1->Items->Count )
        {
                Edit1->Text=ml->getvalue( ListBox1->Items->Strings[idx].c_str() ).c_str();

                meshlist desc_ml;
                desc_ml.open("descriptions.dat");
                if( desc_ml.selectmesh("descriptions") )
                {
                        Label2->Caption=desc_ml.getvalue(ListBox1->Items->Strings[idx].c_str()).c_str();
                }
        }
}
//---------------------------------------------------------------------------


void __fastcall TFSimParams::Edit1Change(TObject *Sender)
{
        int idx=ListBox1->ItemIndex;

        if( idx>-1 && idx < ListBox1->Items->Count )
        {
                std::string key=ListBox1->Items->Strings[idx].c_str();
                ml->changevalue(key, Edit1->Text.c_str() );
                ml->save("settings_tmp.cfg");

                FLoadingScreen->ReadSettings("settings_tmp.cfg");
        }
}
//---------------------------------------------------------------------------

void __fastcall TFSimParams::Button1Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------

void __fastcall TFSimParams::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        FLoadingScreen->ReadSettings("settings.cfg");
}
//---------------------------------------------------------------------------

void __fastcall TFSimParams::FormDestroy(TObject *Sender)
{
        delete ml;        
}
//---------------------------------------------------------------------------

