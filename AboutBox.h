//----------------------------------------------------------------------------
#ifndef AboutBoxH
#define AboutBoxH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
//----------------------------------------------------------------------------
class TFAboutBox : public TForm
{
__published:
	TPanel *Panel1;
	TLabel *ProductName;
	TLabel *Version;
	TLabel *Copyright;
	TLabel *Comments;
	TButton *OKButton;
        TImage *ProgramIcon;
        void __fastcall OKButtonClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:
public:
	virtual __fastcall TFAboutBox(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TFAboutBox *FAboutBox;
//----------------------------------------------------------------------------
#endif    
