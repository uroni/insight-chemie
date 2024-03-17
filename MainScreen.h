//---------------------------------------------------------------------------

#ifndef MainScreenH
#define MainScreenH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "DrawFrame.h"
#include <ComCtrls.hpp>

#include "irrlicht/irrlicht.h"
#include <Menus.hpp>
#include <ImgList.hpp>
#include <Dialogs.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
#include <Graphics.hpp>
#include <vector>
#include <map>
#include <string>

class CAtom;
class SConnectionFunction;

//---------------------------------------------------------------------------
class TFMainScreen : public TForm
{
__published:	// Von der IDE verwaltete Komponenten
        TTimer *Timer1;
        TFDrawFrame *FDrawFrame1;
        TMainMenu *MainMenu1;
        TMenuItem *Datei1;
        TMenuItem *Optionen1;
        TButton *Button1;
        TMenuItem *Neu1;
        TTimer *MCameraTimer;
        TLabel *Label1;
        TLabel *Label2;
        TButton *Button2;
        TButton *Button3;
        TButton *Button4;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TTreeView *TreeView;
        TImageList *TreeViewImages;
        TMenuItem *Bearbeiten1;
        TMenuItem *Verbinden1;
        TMenuItem *Trennen1;
        TMenuItem *Speichern1;
        TMenuItem *Laden1;
        TSaveDialog *SaveDialog1;
        TOpenDialog *OpenDialog1;
        TTrackBar *TrackBar1;
        TLabel *Label6;
        TLabel *Label7;
        TComboBox *ComboBox1;
        TButton *Button5;
        TCppWebBrowser *WebBrowser;
        TMenuItem *SkripteneuLaden1;
        TMenuItem *Log2;
        TMenuItem *Hilfe1;
        TMenuItem *Einfhrung1;
        TButton *CloseButton;
        TMenuItem *Lschen1;
        TButton *Button6;
        TMenuItem *Atomansicht1;
        TLabel *Label8;
        TButton *Button7;
        TButton *Button8;
        TMenuItem *Beenden1;
        TLabel *Label9;
        TLabel *Label10;
        TTimer *SlowDownTimer;
        TMenuItem *Bilderzeugen1;
        TSaveDialog *SaveDialog2;
        TMenuItem *Info1;
        TMenuItem *Ansicht1;
        TMenuItem *Simulationsparameter2;
        TMenuItem *Aktionen1;
        TMenuItem *Rckgngig1;
        TMenuItem *N1;
        TMenuItem *N2;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FDrawFrame1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FDrawFrame1MouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Simulationsparameter1Click(TObject *Sender);
        void __fastcall Testen1Click(TObject *Sender);
        void __fastcall Neu1Click(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Reload1Click(TObject *Sender);
        void __fastcall FDrawFrame1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall FormMouseWheel(TObject *Sender, TShiftState Shift,
          int WheelDelta, TPoint &MousePos, bool &Handled);
        void __fastcall MCameraTimerTimer(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Verbinden1Click(TObject *Sender);
        void __fastcall Trennen1Click(TObject *Sender);
        void __fastcall Speichern1Click(TObject *Sender);
        void __fastcall Laden1Click(TObject *Sender);
        void __fastcall TreeViewDblClick(TObject *Sender);
        void __fastcall ComboBox1Change(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall WebBrowserBeforeNavigate2(TObject *Sender,
          LPDISPATCH pDisp, Variant *URL, Variant *Flags,
          Variant *TargetFrameName, Variant *PostData, Variant *Headers,
          VARIANT_BOOL *Cancel);
        void __fastcall SkripteneuLaden1Click(TObject *Sender);
        void __fastcall Log2Click(TObject *Sender);
        void __fastcall Einfhrung1Click(TObject *Sender);
        void __fastcall CloseButtonClick(TObject *Sender);
        void __fastcall Lschen1Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Atomansicht1Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
        void __fastcall Beenden1Click(TObject *Sender);
        void __fastcall SlowDownTimerTimer(TObject *Sender);
        void __fastcall TrackBar1Change(TObject *Sender);
        void __fastcall Bilderzeugen1Click(TObject *Sender);
        void __fastcall FormDestroy(TObject *Sender);
        void __fastcall Info1Click(TObject *Sender);
        void __fastcall Simulationsparameter2Click(TObject *Sender);
        void __fastcall Aktionen1Click(TObject *Sender);
        void __fastcall Rckgngig1Click(TObject *Sender);
        void __fastcall Test1Click(TObject *Sender);
private:	// Anwender-Deklarationen
        bool rMouseBDown;
        bool lMouseBDown;
        bool mMouseBDown;
        TPoint LastMousePos;

        irr::scene::ISceneNode* selNode;
        CAtom* selAtom;
        CAtom* prevSelAtom;

        irr::core::vector3df center;
        irr::core::vector3df target;

        irr::f32 trackbar_value;
        irr::f32 trackbar_startvalue;

        irr::f32 zoom;

        TWndMethod  OldWndProc;

        std::map<int, SConnectionFunction*> conn_functs;

        bool internal_create;

        void IterateAtoms(CAtom* currnode, std::vector<CAtom*> &atoms);
public:		// Anwender-Deklarationen
        __fastcall TFMainScreen(TComponent* Owner);
        void __fastcall HandleMessage(MSG& msg, bool& Handled);

        void CreateScriptSections(void);
        void CreateScriptSections_iter(AnsiString dir, TTreeNode* Parent);
        void ExecuteScript(void);
        bool ExecuteScript_iter(AnsiString &path, TTreeNode* Node);
        void ExecuteScript( AnsiString filename );
        bool ExecuteFunction( AnsiString function );

        void RegisterGlobal( std::string key, int value );

        void BuildComboBox(void);

        void CenterCamera(irr::f32 time);

        void EnableHelpBox(void);
        void DisableHelpBox(void);

        void SlowDown(void);
        void ReSpeed(void);
        void SaveState(void);

        void ResetSelection(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TFMainScreen *FMainScreen;
//---------------------------------------------------------------------------

namespace MainScreen
{
        TStringList * getDirs(AnsiString dir);
        TStringList * getFiles(AnsiString dir);
}


#endif
