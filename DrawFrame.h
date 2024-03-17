//---------------------------------------------------------------------------


#ifndef DrawFrameH
#define DrawFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFDrawFrame : public TFrame
{
__published:	// Von der IDE verwaltete Komponenten
private:	// Anwender-Deklarationen
public:		// Anwender-Deklarationen
        __fastcall TFDrawFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFDrawFrame *FDrawFrame;
//---------------------------------------------------------------------------
#endif
