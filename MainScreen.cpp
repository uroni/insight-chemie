//---------------------------------------------------------------------------

#include <windows.h>
#include <vcl.h>
#include "irrlicht/irrlicht.h"
#include <winuser.h>
#include <map>
#include <string>
#include <Dialogs.hpp>
#include <limits>

#pragma hdrstop

#pragma comment (lib, "Irrlicht.lib")

#include "MainScreen.h"
#include "LoadingScreen.h"
#include "SimParams.h"
#include "LogScreen.h"
#include "AboutBox.h"
#include "PresentationScreen.h"

#include "types.h"
#include "settings.h"
#include "CSimMgr.h"
#include "CAtom.h"
#include "3dmath.h"
#include "stringtools.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "DrawFrame"
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TFMainScreen *FMainScreen;

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

IrrlichtDevice *device;
IVideoDriver* driver;
ISceneManager* smgr;
IGUIEnvironment* guienv;
ICameraSceneNode *camera;
ICameraSceneNode *fps_camera;
ICameraSceneNode *m_camera;

CSimMgr* simmgr;

const f32 PPI=3.14159265f;
const f32 BOG=3.14159265 / 180.0f;

bool Button5Pressed;
extern bool helpbox_visible;

extern AnsiString app_title;
extern AnsiString app_name;

//---------------------------------------------------------------------------
__fastcall TFMainScreen::TFMainScreen(TComponent* Owner)
        : TForm(Owner)
{
        rMouseBDown=false;
        lMouseBDown=false;
        mMouseBDown=false;

        Application->OnMessage=HandleMessage;

        simmgr=new CSimMgr();

        selAtom=NULL;
        prevSelAtom=NULL;

        internal_create=false;
}
//---------------------------------------------------------------------------

void Pause(void)
{
        simmgr->AddPresentationItem("PRES_PAUSE","PRES_PAUSE_DESCR","pause();");
        if( simmgr->allowPause()==false )
                return;

        FMainScreen->Button5->Enabled=true;
        Button5Pressed=false;

        while(Button5Pressed==false )
        {
                FMainScreen->ReSpeed();
                Sleep(5);
                Application->ProcessMessages();
        }

        FMainScreen->Button5->Enabled=false;
}

void __fastcall TFMainScreen::FormClose(TObject *Sender, TCloseAction &Action)
{
        simmgr->setPresentationCapturingEnabled(false);
        Neu1Click(Sender);
        exit(0);
}
//---------------------------------------------------------------------------
void __fastcall TFMainScreen::Timer1Timer(TObject *Sender)
{
        Timer1->Enabled=false;
        
        static _u32 uLastTime=GetTickCount();

        driver->setTransform(video::ETS_WORLD, core::matrix4());
        video::SMaterial m;
        m.Lighting = false;
        driver->setMaterial(m);
        
        driver->beginScene(true, true, SColor(0,0,0,0));

        _u32 ems=GetTickCount()-uLastTime;
        simmgr->Simulate((ems)*trackbar_value );

        uLastTime=GetTickCount();


        smgr->drawAll();
        guienv->drawAll();

        //simmgr->RotateWorld(core::vector3df(0,0,0), center);

        driver->endScene();

        if( Sender==NULL )
        {
                Graphics::TBitmap *bm=new Graphics::TBitmap;

                video::IImage *img=driver->createScreenShot();
                bm->Width=img->getDimension().Width;
                bm->Height=img->getDimension().Height;

                for(int y=0;y<img->getDimension().Height;++y)
                {
                        for(int x=0;x<img->getDimension().Width;++x)
                        {
                                video::SColor col=img->getPixel(x,y);

                                TColor c=(TColor)0x00000000;
                                char* p=(char*)&c;

                                p[2]=col.getBlue();
                                p[1]=col.getGreen();
                                p[0]=col.getRed();

                                bm->Canvas->Pixels[x][y]=c;
                        }
                }

                /*TJPEGImage *jpg = new TJPEGImage();

                jpg->Assign(bm);
                jpg->SaveToFile("tmp.jpg");

                delete jpg;*/
                bm->SaveToFile("tmp.bmp");
                delete bm;
        }

        if(selAtom!=NULL && lMouseBDown==true && selNode!=NULL )
        {
                simmgr->UnfreezeAll(true);
                ReSpeed();
                
                core::vector3df position=selAtom->getPosition();

                core::line3d<f32> line=smgr->getSceneCollisionManager()->getRayFromScreenCoordinates(core::position2d<s32>(LastMousePos.x,LastMousePos.y) );
                position=line.getClosestPoint(position);
                selAtom->setPosition(position);
        }

        CenterCamera((ems)*20);

        MCameraTimerTimer(Sender);
        Timer1->Enabled=true;
}
//---------------------------------------------------------------------------
void __fastcall TFMainScreen::FormShow(TObject *Sender)
{

        zoom=camera_default_distance;

        Timer1->Enabled=true;
        Timer1Timer(Sender);

        TreeView->Left=Screen->Width-300;
//        ListBox1->Left=ComboBox1->Left;
        Button1->Left=TreeView->Left;

        Label1->Left=TreeView->Left;
        Label3->Left=TreeView->Left;
        Label2->Left=Label1->Left+Label1->Width+20;
        Label4->Left=Label1->Left+Label1->Width+20;
        Label9->Left=Label1->Left;
        Label10->Left=Label9->Left+Label9->Width+20;


        Button2->Left=TreeView->Left;
        Button4->Left=TreeView->Left;
        Button3->Left=Button2->Left+Button2->Width+10;
        Button6->Left=Button3->Left;

        Label5->Left=TreeView->Left;

        Label6->Left=TreeView->Left;
        TrackBar1->Left=Label6->Left;

        Label7->Left=TreeView->Left;
        ComboBox1->Left=Label7->Left+10+Label7->Width;

        Button5->Left=TreeView->Left;

        Label8->Left=TreeView->Left;
        //Label8->Width=150;
        Button7->Left=Label8->Left+Label8->Width+5;
        Button8->Left=Label8->Left+Label8->Width+5;

        int top=FDrawFrame1->Top+FDrawFrame1->Height-WebBrowser->Height;

        WebBrowser->Top=top;
        WebBrowser->Left=FDrawFrame1->Left;

        CloseButton->Top=WebBrowser->Top-CloseButton->Height;
        CloseButton->Left=WebBrowser->Left+FDrawFrame1->Width-CloseButton->Width;


        if(FileExists("FirstStart") )
        {
                DeleteFile("FirstStart");
                ExecuteScript("lib\\help\\FirstStart.lua");
        }

        if( auto_slow_down==1 )
        {
                SlowDownTimer->Enabled=true;
        }
        trackbar_value=TrackBar1->Position;
        trackbar_startvalue=trackbar_value;
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::FDrawFrame1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if( Button == mbRight )
        {
                rMouseBDown=true;
                camera=m_camera;
                smgr->setActiveCamera(camera);
        }
        else if( Button == mbLeft &&  lMouseBDown==false)
        {
                lMouseBDown=true;
                ISceneNode *node=smgr->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(core::position2d<s32>(LastMousePos.x,LastMousePos.y) );
                if( node!=NULL )
                {
                        prevSelAtom=selAtom;
                        selAtom=simmgr->FindSceneNode(node);
                        if( selAtom!=NULL )
                        {
                                selNode=selAtom->getNode();
                                selNode->setDebugDataVisible(true);
                                Label2->Caption=selAtom->getElementData().name.c_str();
                                Label4->Caption=selAtom->getName().c_str();
                                if( Label4->Caption=="" )Label4->Caption="unbekannt";

                                Label10->Caption=selAtom->getCharge();

                                BuildComboBox();

                                if( prevSelAtom!=NULL && selAtom!=NULL )
                                {
                                        Label8->Caption=(selAtom->getElementData().name+" und "+prevSelAtom->getElementData().name).c_str();
                                }

                                ComboBox1->Text="Auswählen";
                        }
                        else
                                node=NULL;
                }
        }
        else if( Button == mbMiddle )
        {
                if( camera!=fps_camera )
                {
                        fps_camera->setPosition( m_camera->getPosition() );
                        fps_camera->setRotation( getRotationToTarget(fps_camera->getPosition(), center) );
                }
                
                int X=FMainScreen->Left+FDrawFrame1->Left+FDrawFrame1->Width/2;
                int Y=Screen->Height-(FMainScreen->Top+FDrawFrame1->Top+FDrawFrame1->Height/2);
                SetCursorPos(X,Y);
                
                mMouseBDown=true;
                camera=fps_camera;
                camera->setInputReceiverEnabled(true);
                smgr->setActiveCamera(camera);
        }

        if( ( Button==mbRight || Button==mbLeft ) && rMouseBDown==true && lMouseBDown==true )
        {
                camera=m_camera;
                smgr->setActiveCamera(camera);
        }
}
//---------------------------------------------------------------------------

void TFMainScreen::BuildComboBox(void)
{
        if( selAtom==NULL )
                return;

        ComboBox1->Items->Clear();
        std::vector<std::string> actions=simmgr->getActions( selAtom->getName() );
        for(size_t i=0;i<actions.size();++i)
        {
                ComboBox1->Items->Add(actions[i].c_str() );
        }

        std::vector<SConnectionFunction*> conn=simmgr->getConnectionFunctions( selAtom->getName() );
        conn_functs.clear();
        for(size_t i=0;i<conn.size();++i)
        {
                std::string text="Verknüpfen mit ";
                std::vector<std::string> mols;
                for(size_t j=0;j<conn[i]->molecules.size();++j)
                {
                        std::string name=conn[i]->molecules[j];
                        if( name!=selAtom->getName() )
                                mols.push_back( name );
                }

                bool ok=true;
                std::map<std::string,bool> amols=simmgr->getMoleculeNamesMap();
                for( size_t j=0;j<mols.size();++j)
                {
                        std::map<std::string,bool>::iterator iter=amols.find(mols[j]);
                        if( iter==amols.end() )
                        {
                                ok=false;
                                break;
                        }
                }

                if( ok==false )
                        continue;

                for( size_t j=0;j<mols.size();++j)
                {
                        if( j+1>=mols.size() )
                                text+=mols[j];
                        else if( j+2>=mols.size() )
                                text+=" und "+mols[j];
                        else
                                text+=mols[j]+", ";
                }

                if( conn[i]->name != "main" )
                        text+=" - "+conn[i]->name;

                conn_functs[ComboBox1->Items->Count]=conn[i];
                ComboBox1->Items->Add(text.c_str() );
        }
        
}


void __fastcall TFMainScreen::FDrawFrame1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        if( (Button==mbRight || Button==mbLeft ) && rMouseBDown==true && lMouseBDown==true )
        {
                fps_camera->setPosition( camera->getPosition() );
                fps_camera->setRotation( camera->getRotation() );
        }

        if( Button == mbRight )
        {
                rMouseBDown=false;
        }
        else if( Button == mbLeft )
        {
                lMouseBDown=false;
                if( selNode!=NULL )
                {
                        selNode->setDebugDataVisible(false);
                        selNode=NULL;
                }
        }
        else if( Button == mbMiddle )
        {
                mMouseBDown=false;
                camera->setInputReceiverEnabled(false);
        }
}
//---------------------------------------------------------------------------


void __fastcall TFMainScreen::HandleMessage(MSG& msg, bool& Handled)
{
        if(mMouseBDown==true)
        {
                if(msg.message==WM_KEYDOWN)
                {
                        SEvent sevt;
                        sevt.KeyInput.PressedDown=true;

                        sevt.KeyInput.Key=(EKEY_CODE)msg.wParam;
                        sevt.KeyInput.Char=0;
                        sevt.EventType=EET_KEY_INPUT_EVENT;
                        sevt.KeyInput.Shift=false;
                        sevt.KeyInput.Control=false;

                        camera->OnEvent(sevt);
                        Handled=true;
                }
        }
        if(msg.message==WM_KEYUP)
        {
                SEvent evt;
                evt.KeyInput.PressedDown=false;
                evt.KeyInput.Key=(EKEY_CODE)msg.wParam;
                evt.EventType=EET_KEY_INPUT_EVENT;
                if(mMouseBDown==false)
                        camera->setInputReceiverEnabled(true);

                camera->OnEvent(evt);

                if(mMouseBDown==false)
                        camera->setInputReceiverEnabled(false);
        }
}





void __fastcall TFMainScreen::Simulationsparameter1Click(TObject *Sender)
{
        FSimParams->Show();        
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Testen1Click(TObject *Sender)
{
        simmgr->setDetail(true);
        simmgr->addAtom(simmgr->getElement("Sauerstoff"),"-",0,0,0);
}
//---------------------------------------------------------------------------






void __fastcall TFMainScreen::Neu1Click(TObject *Sender)
{
        SaveState();

        simmgr->removeAll();

        ResetSelection();
}
//---------------------------------------------------------------------------


void __fastcall TFMainScreen::FormCreate(TObject *Sender)
{
        Caption=app_title;
        SaveDialog1->Filter=app_name+" Skripte|*.lua";
        
        CreateScriptSections();
}
//---------------------------------------------------------------------------


void __fastcall TFMainScreen::Button1Click(TObject *Sender)
{
        SaveState();

        simmgr->setAllowPause(true);
        simmgr->CaptureNewMol();
        internal_create=true;
        ExecuteScript();
        internal_create=false;
        simmgr->CaptureNewMol();

        ReSpeed();

        camera=m_camera;
        smgr->setActiveCamera(camera);

        simmgr->SeparateMolecules();
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Reload1Click(TObject *Sender)
{
        FLoadingScreen->LoadScripts();
}
//---------------------------------------------------------------------------



void __fastcall TFMainScreen::FDrawFrame1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        LastMousePos.x=X;
        if( WebBrowser->Width>0 )
                LastMousePos.y=Y+WebBrowser->Height/2;
        else
                LastMousePos.y=Y;
}
//---------------------------------------------------------------------------



void __fastcall TFMainScreen::FormMouseWheel(TObject *Sender,
      TShiftState Shift, int WheelDelta, TPoint &MousePos, bool &Handled)
{
        if( lMouseBDown == true && selAtom!=NULL )
        {
                int move=mouse_wheel_unit;
                if( WheelDelta > 0 )
                        move*=-1;
                core::vector3df npos=getTargetDistance(selAtom->getPosition(), camera->getPosition(), move );
                selAtom->setPosition(npos);
        }
        else
        {
                camera=m_camera;
                smgr->setActiveCamera(camera);

                core::vector3df target=camera->getTarget();
                core::vector3df pos=camera->getPosition();

                float y=mouse_wheel_camera_unit;

                if( WheelDelta > 0 )
                        y*=-1;

                if( zoom+y>camera_zoom_min_distance || y>0 )
                {
                        zoom+=y;

                        pos=getTargetDistance(target,pos, zoom);
                        camera->setPosition(pos);
                }
                
        }
}
//---------------------------------------------------------------------------





void __fastcall TFMainScreen::MCameraTimerTimer(TObject *Sender)
{
        static int omx,omy;

        int mx=Mouse->CursorPos.x;
        int my=Mouse->CursorPos.y;

        if( lMouseBDown==true && rMouseBDown==true )
        {
                core::vector3df rotation;
                rotation.Y=(omx-mx)*camera_mouse_scale;
                rotation.X=(omy-my)*camera_mouse_scale;

                simmgr->RotateWorld(rotation, center);
        }
        else if( rMouseBDown==true )
        {
                core::vector3df target=camera->getTarget();
                core::vector3df pos=camera->getPosition();

                f32 y=(omy-my)*camera_zoom_scale;

                if( zoom+y>camera_zoom_min_distance || y>0 )
                {
                        zoom+=y;

                        pos=getTargetDistance(target,pos, zoom);
                        camera->setPosition(pos);
                }
        }

        omx=mx;
        omy=my;
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Button2Click(TObject *Sender)
{
        if( selAtom!=NULL )
        {
                SaveState();
                
                simmgr->removeAtom(selAtom->getID());
                
                ResetSelection();
        }
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Button3Click(TObject *Sender)
{
        if( selAtom!=NULL )
        {
                SaveState();
                
                CConnection* connection;
                while( (connection=selAtom->getConnection(0))!=NULL )
                {
                        simmgr->Disconnect(connection);
                }
        }
}
//---------------------------------------------------------------------------



void __fastcall TFMainScreen::Button4Click(TObject *Sender)
{
        if( selAtom!=NULL )
        {
                SaveState();
                
                std::vector<CAtom*> todel;
                simmgr->getMolecule(selAtom, todel);

                for(size_t i=0;i<todel.size();++i)
                {
                        simmgr->removeAtom(todel[i]->getID());
                }
                
                ResetSelection();
        }
}
//---------------------------------------------------------------------------


void TFMainScreen::CenterCamera(f32 time)
{
        if( (lMouseBDown==false && rMouseBDown==false) && camera==m_camera)
        {
                core::vector3df ccenter=simmgr->getSandbox().getCenter();
                core::vector3df newpos=getTarget(ccenter,core::vector3df(0,0,0), zoom);
                camera->setPosition( newpos );

                core::vector3df pos=camera->getPosition();

                f32 step=std::min(time*time, pos.getDistanceFrom( newpos )*time*camera_position_center_speed );

                camera->setPosition( getTargetDistance(pos, newpos, step) );
                //target=camera->getTarget();

                f32 distance=target.getDistanceFrom( ccenter );
                
                step=std::min(time*time, distance*time*camera_target_center_speed );
                target=getTargetDistance(target, ccenter, step);

                if(target.X==std::numeric_limits<f32>::infinity() ||
                        target.Y==std::numeric_limits<f32>::infinity() ||
                        target.Z==std::numeric_limits<f32>::infinity() )
                {
                        target=ccenter;
                }

                camera->setTarget(target);

                /*core::vector3df rot=camera->getRotation();
                rot.Z=0;

                camera->setRotation(rot);*/

                center=ccenter;
        }
}

void __fastcall TFMainScreen::Verbinden1Click(TObject *Sender)
{
        SaveState();
        
        if( selAtom!=NULL && prevSelAtom!=NULL )
        {
                bool b=simmgr->Connect(selAtom->getID(), prevSelAtom->getID() );
                if( b==false )
                        PlaySound("gflkj4343ngldf",NULL, SND_ASYNC);
        }
        else
        {
                Application->MessageBox("Sie müssen zwei Atome nacheinander anklicken um diese verbinden zu können",app_title.c_str(),0);
        }
}
//---------------------------------------------------------------------------


void __fastcall TFMainScreen::Trennen1Click(TObject *Sender)
{
        SaveState();
        
        if( selAtom!=NULL && prevSelAtom!=NULL )
        {
                simmgr->Disconnect(selAtom->getID(), prevSelAtom->getID() );
        }
        else
        {
                Application->MessageBox("Sie müssen zwei Atome nacheinander anklicken um diese verbinden zu können",app_title.c_str(),0);
        }
}
//---------------------------------------------------------------------------



void __fastcall TFMainScreen::Speichern1Click(TObject *Sender)
{
        f32 val=trackbar_value;
        trackbar_value=0;

        bool b=SaveDialog1->Execute();

        if( b==true )
        {
                std::string data=simmgr->getSaveScript();

                std::string filename=SaveDialog1->FileName.c_str();

                if( findextension(filename)!="lua" )
                        filename+=".lua";                

                writestring(data, filename );
        }

        FLoadingScreen->restoreCurrentDir();
        trackbar_value=val;
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Laden1Click(TObject *Sender)
{
        f32 val=trackbar_value;
        trackbar_value=0;

        bool b=OpenDialog1->Execute();

        FLoadingScreen->restoreCurrentDir();

        if( b==true )
        {
                simmgr->setAllowPause(true);
                ExecuteScript( OpenDialog1->FileName );
                ReSpeed();
        }

        trackbar_value=val;
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::TreeViewDblClick(TObject *Sender)
{
        Button1Click(Sender);                
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::ComboBox1Change(TObject *Sender)
{
        int idx=ComboBox1->ItemIndex;

        if( idx!=-1 )
        {
                std::map<int, SConnectionFunction*>::iterator iter=conn_functs.find( idx );
                if( iter!=conn_functs.end() && selAtom!=NULL )
                {
                        std::string fname="connections\\";
                        for(size_t i=0;i<iter->second->molecules.size();++i)
                        {
                                fname+=iter->second->molecules[i]+"\\";

                                int id;
                                if( iter->second->molecules[i]==selAtom->getName() )
                                        id=selAtom->getMoleculeID();
                                else
                                        id=simmgr->getMolceuleIDbyName( iter->second->molecules[i] );

                                RegisterGlobal( "id"+ convert((int)i+1), id );
                        }
                        fname+=iter->second->name+".lua";
                        ExecuteScript(fname.c_str());
                }
                else
                {
                        std::string fname=simmgr->getActionFunction( selAtom->getName(), ComboBox1->Items->Strings[idx].c_str() );

                        ExecuteFunction(fname.c_str() );
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Button5Click(TObject *Sender)
{
        SaveState();
        
        Button5Pressed=true;
        ReSpeed();        
}
//---------------------------------------------------------------------------


void TFMainScreen::EnableHelpBox(void)
{
        WebBrowser->Visible=true;
        FDrawFrame1->Height-=WebBrowser->Height/2;
        WebBrowser->Width=FDrawFrame1->Width;
        CloseButton->Visible=true;
        helpbox_visible=true;
}

void TFMainScreen::DisableHelpBox(void)
{
        WebBrowser->Visible=false;
        FDrawFrame1->Height+=WebBrowser->Height/2;
        WebBrowser->Width=0;
        CloseButton->Visible=false;
        helpbox_visible=false;
}


void __fastcall TFMainScreen::WebBrowserBeforeNavigate2(TObject *Sender,
      LPDISPATCH pDisp, Variant *URL, Variant *Flags,
      Variant *TargetFrameName, Variant *PostData, Variant *Headers,
      VARIANT_BOOL *Cancel)
{
        AnsiString url=*URL;

        bool abort=false;

        if( url.Pos("lua:")==1 )
        {
                abort=true;
                url.Delete(1,4);
                writestring(htmldecode(url.c_str(),false), "tmp.lua");
                ExecuteScript("tmp.lua");
                DeleteFile("tmp.lua");
        }
        else if( url.Pos("exec:")==1 )
        {
                abort=true;
                url.Delete(1,5);
                url=htmldecode(url.c_str(),false).c_str();
                if( url.Length()>1 && url[1]==' ')
                        url.Delete(1,1);

                ExecuteScript( url );
        }

        if( abort==true )
        {
                *Cancel=true;
                PlaySound("Windows XP-Start.wav", NULL, SND_ASYNC);
        }
}
//---------------------------------------------------------------------------


void __fastcall TFMainScreen::SkripteneuLaden1Click(TObject *Sender)
{
        TreeView->Items->Clear();
        CreateScriptSections();
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Log2Click(TObject *Sender)
{
        FLogScreen->Show();        
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Einfhrung1Click(TObject *Sender)
{
        ExecuteScript("lib\\help\\FirstStart.lua");                
}
//---------------------------------------------------------------------------




void __fastcall TFMainScreen::CloseButtonClick(TObject *Sender)
{
        DisableHelpBox();
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Lschen1Click(TObject *Sender)
{        
        Button2Click(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Button6Click(TObject *Sender)
{
        if( selAtom!=NULL )
        {
                SaveState();
                
                std::vector<CAtom*> todel;
                simmgr->getMolecule(selAtom, todel);

                std::string name=InputBox("Molekülname", "Geben Sie jetzt bitte den gewünschten Molekülname ein", "unbekannt" ).c_str();

                for(size_t i=0;i<todel.size();++i)
                {
                        todel[i]->setName(name);
                }
        }        
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Atomansicht1Click(TObject *Sender)
{
        TMenuItem *item=MainMenu1->Items->Items[3]->Items[2];
        if( item->Checked==false )
        {
                simmgr->setDetail(true);
                item->Checked=true;
        }
        else
        {
                simmgr->setDetail(false);
                item->Checked=false;
        }
}
//---------------------------------------------------------------------------


void __fastcall TFMainScreen::Button7Click(TObject *Sender)
{
        Verbinden1Click(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Button8Click(TObject *Sender)
{
        Trennen1Click(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Beenden1Click(TObject *Sender)
{
        Close();        
}
//---------------------------------------------------------------------------



void TFMainScreen::SlowDown(void)
{
        f32 time=SlowDownTimer->Interval;

        f32 step=(time/auto_slow_down_time)*trackbar_startvalue;
        trackbar_value-=step;

        if(trackbar_value <= 0 )
                trackbar_value=0;

        //Label11->Caption=trackbar_value;
}

void Respeed(void)
{
        FMainScreen->ReSpeed();
}

void TFMainScreen::ReSpeed(void)
{
        trackbar_value=TrackBar1->Position;
        
}
void __fastcall TFMainScreen::SlowDownTimerTimer(TObject *Sender)
{
        SlowDown();
}
//---------------------------------------------------------------------------


void __fastcall TFMainScreen::TrackBar1Change(TObject *Sender)
{
        trackbar_value=TrackBar1->Position;

        if( trackbar_value < trackbar_startvalue )
                SlowDownTimer->Enabled=false;
        else
                SlowDownTimer->Enabled=true;

}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Bilderzeugen1Click(TObject *Sender)
{
        f32 val=trackbar_value;
        trackbar_value=0;

        bool b=SaveDialog2->Execute();

        if( b )
        {
                FLoadingScreen->restoreCurrentDir();
                Timer1Timer(NULL);
                CopyFile("tmp.bmp", SaveDialog2->FileName.c_str(), false);
                DeleteFile("tmp.bmp");
        }
        FLoadingScreen->restoreCurrentDir();
        Timer1->Enabled=true;

        trackbar_value=val;
}
//---------------------------------------------------------------------------


void __fastcall TFMainScreen::FormDestroy(TObject *Sender)
{
        simmgr->removeAll();
        delete simmgr;        
}
//---------------------------------------------------------------------------


void __fastcall TFMainScreen::Info1Click(TObject *Sender)
{
        FAboutBox->Show();        
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Simulationsparameter2Click(TObject *Sender)
{
        FSimParams->Show();        
}
//---------------------------------------------------------------------------


void __fastcall TFMainScreen::Aktionen1Click(TObject *Sender)
{
        FPresentationScreen->Show();        
}
//---------------------------------------------------------------------------


void TFMainScreen::SaveState(void)
{
        TMenuItem *item=MainMenu1->Items->Items[1]->Items[0];
        
        simmgr->SaveState();
        item->Enabled=true;
}

void __fastcall TFMainScreen::Rckgngig1Click(TObject *Sender)
{
        TMenuItem *item=MainMenu1->Items->Items[1]->Items[0];

        std::string data;
        bool last;
        simmgr->getLastState(data,last);

        if( last==true )
                item->Enabled=false;

        bool b=false;
        if( simmgr->isCapturing()==true )
        {
                b=FPresentationScreen->Undo();
        }

        ResetSelection();
        ReSpeed();

        if( b==true )
        {
                return;
        }

        simmgr->removeAll();

        writestring(data,"tmp.lua");

        ExecuteScript("tmp.lua");
        DeleteFile("tmp.lua");
}
//---------------------------------------------------------------------------

void __fastcall TFMainScreen::Test1Click(TObject *Sender)
{
        if( selAtom!=NULL )
        {
                selAtom->AddInvisibleConnection(1);
        }
}
//---------------------------------------------------------------------------

void TFMainScreen::ResetSelection(void)
{
        selAtom=NULL;
        Label10->Caption="";
        Label2->Caption="";
        Label4->Caption="";
        Label8->Caption="";
}

