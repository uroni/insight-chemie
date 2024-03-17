//---------------------------------------------------------------------------
#include <vcl.h>
#include <float.h>
#include <map>

#pragma hdrstop
#include "script.h"
#include "irrlicht/irrlicht.h"

#include "LoadingScreen.h"
#include "MainScreen.h"

#include "types.h"
#include "meshlist.h"
#include "CAtom.h"
#include "CSimMgr.h"

#define D_DEFINE_SETTINGS
#include "settings.h"

#define D_DEFINE_RESOURCES
#include "resources.h"

#include "engine-req.h"
#include "EventReceiver.h"

#include "translation.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "Unit2"
#pragma resource "*.dfm"

TFLoadingScreen *FLoadingScreen;

irr::gui::IGUIStaticText* dbgtext;
LUA *lua;

AnsiString app_name="Insight Chemie";
AnsiString app_version="v1.1";
AnsiString app_title="Insight Chemie v1.1";


//---------------------------------------------------------------------------
__fastcall TFLoadingScreen::TFLoadingScreen(TComponent* Owner)
        : TForm(Owner)
{
FMainScreen=new TFMainScreen(NULL);
}
//---------------------------------------------------------------------------

//--
using namespace irr;
//--

void Sleep2(int time)
{
        unsigned int start=GetTickCount();
        while(GetTickCount()<start+time )
        {
                Sleep(5);
                Application->ProcessMessages();
        }
}


void __fastcall TFLoadingScreen::Timer1Timer(TObject *Sender)
{
        ProgressBar1->Position+=10;
        if(ProgressBar1->Position>=100)
        {
                Timer1->Enabled=false;
                FMainScreen->Show();
                Visible=false;
        }

        switch(ProgressBar1->Position)
        {
        case 10:
                {
                        StatusBar1->SimpleText="Lade 3D-Engine...";
                        LoadIrrlicht();
                }break;
        case 20:
                {
                        StatusBar1->SimpleText="Lade Ressourcen...";
                        LoadResources();
                }break;
        case 30:
                {
                        StatusBar1->SimpleText="Lade Elemente...";
                        simmgr->LoadElements("elements.cfg");
                }break;
        case 40:
                {
                        StatusBar1->SimpleText="Lade Skripte...";
                        LoadScripts();
                }break;
        case 80:
                {
                        StatusBar1->SimpleText="Lade Verbindungen...";
                        LoadConnections();
                }
        case 90:
                {
                        StatusBar1->SimpleText="Starte Simulation...";
                        simmgr->init();
                }break;

        }
                
}
//---------------------------------------------------------------------------

void __fastcall TFLoadingScreen::FormCreate(TObject *Sender)
{
        Caption=app_title;
        
        ProgressBar1->Max=100;

        StatusBar1->SimpleText="Lade Einstellungen...";
        ReadSettings("settings.cfg");
}
//---------------------------------------------------------------------------


#define SETVALUE_FLOAT(x) tmp=ml.getvalue(#x); if(tmp!=""){ x=atof(tmp.c_str()); }
#define SETVALUE_BOOL(x) tmp=ml.getvalue(#x); if(tmp=="false") x=false; else x=true;
#define SETVALUE_INT(x) tmp=ml.getvalue(#x); if(tmp!=""){ x=atoi(tmp.c_str() ); }

void TFLoadingScreen::ReadSettings(AnsiString sfile)
{
        meshlist ml;
        ml.open(sfile.c_str() );

        ml.selectmesh("video");

        string driver=ml.getvalue("driver");
        if(driver=="OpenGL")
        {
                s_video_driver=2;
        }
        else if(driver=="Direct3D")
        {
                s_video_driver=1;
        }
        else
        {
                s_video_driver=0;
        }


        ml.selectmesh("simulation");

        string tmp;

        SETVALUE_FLOAT(catom_core_exp);
        SETVALUE_FLOAT(catom_core_coreforcescale);
        SETVALUE_BOOL(catom_draw_elcoreline);
        SETVALUE_FLOAT(catom_elektron_force);
        SETVALUE_FLOAT(catom_bank_force);
        SETVALUE_INT(catom_numsteps);
        SETVALUE_FLOAT(catom_bank_distance);
        SETVALUE_FLOAT(catom_connection_forcescale);
        SETVALUE_FLOAT(catom_inter_connection_forcescale);
        SETVALUE_FLOAT(catom_inter_connection_distance_multi);
        SETVALUE_FLOAT(catom_connection_backdrift);
        SETVALUE_FLOAT(catom_connection_backdrift_changing);
        SETVALUE_FLOAT(catom_connection_change_limit );
        SETVALUE_FLOAT( catom_connection_size );
        SETVALUE_FLOAT( catom_connection_length );
        SETVALUE_FLOAT( catom_bank_distance );
        SETVALUE_FLOAT( catom_connection2bank_force );
        SETVALUE_FLOAT( catom_bank2connection_force );
        SETVALUE_FLOAT( catom_connection2connection_force );
        SETVALUE_INT( catom_change_cap );
        SETVALUE_INT( catom_freezetime );
        SETVALUE_FLOAT( catom2catom_force_scale );
        SETVALUE_FLOAT( catom2catom_distance_cap );
        SETVALUE_INT( catom_allow_freeze );
        SETVALUE_FLOAT( mouse_wheel_unit );
        SETVALUE_FLOAT( camera_default_distance );
        SETVALUE_FLOAT( camera_mouse_scale );
        SETVALUE_FLOAT( catom_connection_visible_distance );
        SETVALUE_FLOAT( catom_connection_transparent_distance );
        SETVALUE_FLOAT( camera_position_center_speed );
        SETVALUE_FLOAT( camera_target_center_speed );
        SETVALUE_FLOAT( camera_zoom_scale );
        SETVALUE_FLOAT( time_cap );
        SETVALUE_FLOAT( mouse_wheel_camera_unit );
        SETVALUE_FLOAT( catom_connection_centerscale );
        SETVALUE_FLOAT( catom_stepsize );
        SETVALUE_FLOAT( auto_slow_down );
        SETVALUE_FLOAT( auto_slow_down_time );
        SETVALUE_FLOAT( catom_connection_distance_cap_sq );
        SETVALUE_FLOAT( catom_plane_force );
}

void TFLoadingScreen::LoadIrrlicht(void)
{
        if(!InitTranslation())
        {
                Timer1->Enabled=false;
                Application->MessageBoxA((app_name+" couldn't find or initialize the language.cfg file.").c_str(),app_title.c_str(),0);
                exit(54);
        }

        int fwidth=Screen->Width-350;
        FMainScreen->FDrawFrame1->Left=25;
        FMainScreen->FDrawFrame1->Width=fwidth;
        FMainScreen->FDrawFrame1->Height=FMainScreen->FDrawFrame1->Width;

        _control87((_control87(0, 0) | ~0011), MCW_EM);
        _control87(MCW_EM,MCW_EM);

        if(FMainScreen->FDrawFrame1->Width%2!=0)
                FMainScreen->FDrawFrame1->Width--;
        if(FMainScreen->FDrawFrame1->Height%2!=0)
                FMainScreen->FDrawFrame1->Height--;

        if(s_video_driver==2)
                device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::s32>(FMainScreen->FDrawFrame1->Width, FMainScreen->FDrawFrame1->Height), 16, false, true, false, 0, IRRLICHT_SDK_VERSION, FMainScreen->FDrawFrame1->Handle);
        else if(s_video_driver==1)
                device = irr::createDevice(irr::video::EDT_DIRECTX8,  irr::core::dimension2d<irr::s32>(FMainScreen->FDrawFrame1->Width, FMainScreen->FDrawFrame1->Height), 16, false, true, false, 0, IRRLICHT_SDK_VERSION, FMainScreen->FDrawFrame1->Handle);
        else
                device = irr::createDevice(irr::video::EDT_SOFTWARE,  irr::core::dimension2d<irr::s32>(FMainScreen->FDrawFrame1->Width, FMainScreen->FDrawFrame1->Height), 16, false, true, false, 0, IRRLICHT_SDK_VERSION, FMainScreen->FDrawFrame1->Handle);


        myeventres=new EventReceiver;
        device->setEventReceiver( myeventres );

        driver = device->getVideoDriver();
        smgr = device->getSceneManager();
        guienv = device->getGUIEnvironment();

        /*dbgtext=guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		        irr::core::rect<int>(10,10,200,22), true);

        irr::scene::IAnimatedMesh* mesh = smgr->getMesh("sydney.md2");
        irr::scene::IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode( mesh );

        node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
        node->setFrameLoop(0, 310);
        node->setMaterialTexture( 0, driver->getTexture("sydney.bmp") ); */

        SKeyMap keyMap[8];
        keyMap[0].Action = EKA_MOVE_FORWARD;
        keyMap[0].KeyCode = KEY_UP;
        keyMap[1].Action = EKA_MOVE_FORWARD;
        keyMap[1].KeyCode = KEY_KEY_W;

        keyMap[2].Action = EKA_MOVE_BACKWARD;
        keyMap[2].KeyCode = KEY_DOWN;
        keyMap[3].Action = EKA_MOVE_BACKWARD;
        keyMap[3].KeyCode = KEY_KEY_S;

        keyMap[4].Action = EKA_STRAFE_LEFT;
        keyMap[4].KeyCode = KEY_LEFT;
        keyMap[5].Action = EKA_STRAFE_LEFT;
        keyMap[5].KeyCode = KEY_KEY_A;

        keyMap[6].Action = EKA_STRAFE_RIGHT;
        keyMap[6].KeyCode = KEY_RIGHT;
        keyMap[7].Action = EKA_STRAFE_RIGHT;
        keyMap[7].KeyCode = KEY_KEY_D;

        fps_camera=smgr->addCameraSceneNodeFPS(0,100,500,-1,keyMap,8);
     
        fps_camera->setInputReceiverEnabled(false);

        fps_camera->setFarValue(10000000);

        m_camera=smgr->addCameraSceneNode();
        m_camera->setInputReceiverEnabled(false);

        m_camera->setFarValue(10000000);

        smgr->setActiveCamera(m_camera);

        camera=m_camera;
}

void TFLoadingScreen::LoadResources(void)
{
        device->getFileSystem()->addZipFileArchive("resources.zip");

        r_neutron_texture=driver->getTexture("neutron.jpg");
        r_neutron_mesh=smgr->getMesh("neutron.ms3d");

        r_proton_texture=driver->getTexture("proton.jpg");
        r_proton_mesh=smgr->getMesh("proton.ms3d");

        r_elektron_texture=driver->getTexture("elektron.jpg");
        r_elektron_mesh=smgr->getMesh("elektron.ms3d");

        r_atom1u_mesh=smgr->getMesh("atom_1u.ms3d");

        driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT,true);

        r_bank_mesh=smgr->getMesh("bank.ms3d");
        r_bank_dot_mesh=smgr->getMesh("bank_dot.ms3d");
        r_bank_texture=driver->getTexture("bank.tga");


        if( r_bank_texture!=NULL )
        {
                for(size_t i=0;i<100;++i)
                {
                        video::IImage* img=driver->createImageFromFile("bank.tga");
                        s32 max_alpha=img->getPixel(0,0).getAlpha();
                        if( img->getColorFormat()==video::ECF_A8R8G8B8 )
                        {
                                s32 *data=(s32*)img->lock();
                                for(int j=0;j<img->getImageDataSizeInPixels();++j)
                                {
                                        video::SColor col(data[j]);

                                        s32 alpha=(unsigned char)(((float)(max_alpha/100.0f)*(float)i));
                                        col.setAlpha(alpha);
                                        data[j]=col.color;
                                }
                                img->unlock();
                        }
                        max_alpha=img->getPixel(0,0).getAlpha();
                        AnsiString name="bank_texture_";
                        name+=i;
                        r_pc_bank_textures[i]=driver->addTexture(name.c_str(),img);
                }
        }

        r_box1_mesh=smgr->getMesh("box1.ms3d");
}

void TFLoadingScreen::LoadScripts(void)
{
        lua=new LUA;
        bool b=lua->Execute("lib\\main.lua");

        if( b==false )
        {
                Timer1->Enabled=false;
                Application->MessageBoxA(lua->getError().c_str(),"ElSim",0);
                exit(0);
        }
}

void TFLoadingScreen::restoreCurrentDir(void)
{
        AnsiString currdir=ExtractFilePath(ParamStr(0) );
        SetCurrentDir( currdir );
}

void TFLoadingScreen::LoadConnections(void)
{
        TStringList *lst=new TStringList;
        LoadConnections_iter("connections", lst);
        delete lst;
}

void TFLoadingScreen::LoadConnections_iter(AnsiString dir, TStringList *dir_lst)
{
        TStringList *dirs=MainScreen::getDirs(dir);
        TStringList *files=MainScreen::getFiles(dir);

        for(int i=0;i<dirs->Count;++i)
        {
                AnsiString ndir=dir+"\\"+dirs->Strings[i];
                TStringList *lst=new TStringList;
                lst->AddStrings(dir_lst);
                lst->Add(dirs->Strings[i]);
                LoadConnections_iter(ndir, lst);
                delete lst;
        }

        for(int i=0;i<files->Count;++i)
        {
                AnsiString fname=files->Strings[i];
                if( fname.Length()>4 )
                        fname.Delete(fname.Length()-3,4);

                SConnectionFunction *conn=new SConnectionFunction;
                conn->name=fname.c_str();

                for(int j=0;j<dir_lst->Count;++j)
                {
                        conn->molecules.push_back( dir_lst->Strings[j].c_str() );
                }

                simmgr->addConnectionFunction( conn );
        }

        delete dirs;
        delete files;
}
void __fastcall TFLoadingScreen::FormDestroy(TObject *Sender)
{
        delete lua;
        delete myeventres;
        delete FMainScreen;    
}
//---------------------------------------------------------------------------

