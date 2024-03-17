//---------------------------------------------------------------------------

#ifndef PresentationScreenH
#define PresentationScreenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------

#include <string>
#include <vector>
#include <map>
#include "CSimMgr.h"

class TFPresentationScreen : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TListBox *ListBox1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TButton *Button6;
        TBitBtn *BitBtn1;
        TBitBtn *BitBtn2;
        TButton *Button5;
        TLabel *Label1;
        TLabel *Label2;
        TSaveDialog *SaveDialog1;
        TOpenDialog *OpenDialog1;
        TButton *Button7;
        TCheckBox *CheckBox1;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall ListBox1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
private:	// Anwender-Deklarationen
        void BuildListBox(void);

        int getRealIndex(void);

        void SavePositions(TStringList *lst, int till);
public:		// Anwender-Deklarationen
        bool SavePresentation(AnsiString filename, int till=-1);
        bool LoadPresentation(AnsiString filename);
        bool ExecutePresentation(int till=-1);

        __fastcall TFPresentationScreen(TComponent* Owner);
        std::vector<SPresItem> presentation;
        int current_index;

        void PresentationItemCallback(SPresItem item);

        bool capturing;

        bool Undo(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFPresentationScreen *FPresentationScreen;
//---------------------------------------------------------------------------
#endif
