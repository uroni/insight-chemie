//---------------------------------------------------------------------------

#ifndef SimParamsH
#define SimParamsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class meshlist;

class TFSimParams : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TButton *OK;
        TButton *Button1;
        TListBox *ListBox1;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit1;
        void __fastcall OKClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall Edit1Change(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormDestroy(TObject *Sender);
private:	// Anwender-Deklarationen
        meshlist *ml;
public:		// Anwender-Deklarationen
        __fastcall TFSimParams(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFSimParams *FSimParams;
//---------------------------------------------------------------------------
#endif
