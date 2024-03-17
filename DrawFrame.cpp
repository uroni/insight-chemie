//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DrawFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFDrawFrame *FDrawFrame;
//---------------------------------------------------------------------------
__fastcall TFDrawFrame::TFDrawFrame(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
