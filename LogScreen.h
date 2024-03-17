//---------------------------------------------------------------------------

#ifndef LogScreenH
#define LogScreenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFLogScreen : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TButton *Button1;
        TMemo *Memo1;
        void __fastcall Button1Click(TObject *Sender);
private:	// Anwender-Deklarationen
public:		// Anwender-Deklarationen
        __fastcall TFLogScreen(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFLogScreen *FLogScreen;
//---------------------------------------------------------------------------
#endif
