#pragma hdrstop
#include "script.h"
#include "MainScreen.h"
#include "stringtools.h"
#include "CSimMgr.h"

extern LUA *lua;

namespace MainScreen
{
        TStringList * getDirs(AnsiString dir)
        {
                int attr = faAnyFile;
                TSearchRec F;
                TStringList *lst=new TStringList;

                unsigned int erg = FindFirst(dir+String("\\*"),attr,F);
                while (erg == 0)
                {
                        if (F.Attr & faDirectory)
                        {
                                if ((F.Name != ".") && (F.Name != ".."))
                                        lst->Add(F.Name);
                        }
                        erg = FindNext(F);
                }
                FindClose(F);
                return lst;
        }
        TStringList * getFiles(AnsiString dir)
        {
                int attr = faAnyFile;
                TSearchRec F;
                TStringList *lst=new TStringList;

                unsigned int erg = FindFirst(dir+String("\\*"),attr,F);
                while (erg == 0)
                {
                        if (!( F.Attr & faDirectory))
                        {
                                lst->Add(F.Name);
                        }
                        erg = FindNext(F);
                }
                FindClose(F);
                return lst;
        }
}


void TFMainScreen::CreateScriptSections(void)
{
        CreateScriptSections_iter("scripts", NULL);
}

void TFMainScreen::CreateScriptSections_iter(AnsiString dir, TTreeNode* Parent)
{
        TStringList *lst=MainScreen::getDirs(dir);
        for(int i=0;i<lst->Count;++i)
        {
                TTreeNode* node=TreeView->Items->AddChild(Parent, lst->Strings[i]);
                node->ImageIndex=0;
                node->SelectedIndex=0;
                CreateScriptSections_iter(dir+"\\"+lst->Strings[i], node);

        }
        delete lst;

        lst=MainScreen::getFiles(dir);
        for(int i=0;i<lst->Count;++i)
        {
                AnsiString str=lst->Strings[i];
                if( str.Length()>4 )
                        str.Delete(str.Length()-3,4);

                TTreeNode* node=TreeView->Items->AddChild(Parent, str);
                node->ImageIndex=1;
                node->SelectedIndex=1;
        }
        delete lst;

}

void TFMainScreen::ExecuteScript(void)
{
        /*int idx=ComboBox1->ItemIndex;
        if( idx==-1 )
                return;

        int idx2=ListBox1->ItemIndex;
        if( idx2==-1 )
                return;

        AnsiString sname="scripts\\"+ComboBox1->Items->Strings[idx]+"\\"+ListBox1->Items->Strings[idx2]+".lua";
        bool b=lua->Execute(sname.c_str() );
        if( b==false )
        {
                Application->MessageBoxA(lua->getError().c_str(),"ElSim",0);
        }  */

        AnsiString path;
        bool b;

        for(int i=0;i<TreeView->Items->Count;++i)
        {
                path=TreeView->Items->Item[i]->Text;
                b=ExecuteScript_iter(path, TreeView->Items->Item[i]);
                if( b )
                        break;
        }

        if( b==true )
        {
                AnsiString sname="scripts\\"+path+".lua";

                if( FileExists(sname) )
                        ExecuteScript(sname);
        }

}

bool TFMainScreen::ExecuteScript_iter(AnsiString &path, TTreeNode* Node)
{
        for(int i=0;i<Node->Count;++i)
        {
                if( Node->Item[i]->Selected==true )
                {
                        path+="\\"+Node->Item[i]->Text;
                        return true;
                }
                else
                {
                        AnsiString t_path=path+"\\"+Node->Item[i]->Text;
                        bool b=ExecuteScript_iter(t_path, Node->Item[i]);
                        if( b==true )
                        {
                                path=t_path;
                                return true;
                        }
                }
        }
        return false;
}

void TFMainScreen::ExecuteScript( AnsiString filename )
{
        bool name_set=false;
        if( internal_create==true && simmgr->isCapturing()==true )
        {
                std::string data=getFile(filename.c_str() );
                std::string name=getbetween("local name=\"","\"",data);
                simmgr->setCaptureMoleculeName(name);
                name_set=true;
        }

        bool b=lua->Execute(filename.c_str() );

        if( name_set )
                simmgr->setCaptureMoleculeName("");

        if( b==false )
        {
                Application->MessageBoxA(lua->getError().c_str(),"ElSim",0);
        }
}

bool TFMainScreen::ExecuteFunction( AnsiString function )
{
        std::string fname=function.c_str();
        std::string func=getuntil(" ",fname);
        std::string id=getafter(" ",fname);

        lua_getglobal(lua->getState(),func.c_str() );
        lua_pushstring(lua->getState(), id.c_str());

        bool b=lua->Callfunction( func,1 );

        if( b==false )
        {
                Application->MessageBoxA(lua->getError().c_str(),"ElSim",0);
                return false;
        }

        return true;
}

void TFMainScreen::RegisterGlobal( std::string key, int value )
{
        lua->RegisterGlobal( key, value );
}
