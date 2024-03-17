//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>

class EventReceiver;
//---------------------------------------------------------------------------
class TFLoadingScreen : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TProgressBar *ProgressBar1;
        TStatusBar *StatusBar1;
        TTimer *Timer1;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
private:	// Anwender-Deklarationen
        void LoadIrrlicht(void);
        void LoadResources(void);
        void LoadElements(AnsiString sfile);
        void LoadConnections(void);
        void LoadConnections_iter(AnsiString dir, TStringList *dir_lst);

        EventReceiver* myeventres;


public:		// Anwender-Deklarationen
        __fastcall TFLoadingScreen(TComponent* Owner);
        void LoadScripts(void);
        void ReadSettings(AnsiString sfile);

        void restoreCurrentDir(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFLoadingScreen *FLoadingScreen;
//---------------------------------------------------------------------------
#endif
 