//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainScreen.h"
#include "PresentationScreen.h"
#include "LoadingScreen.h"
#include "translation.h"
#include "stringtools.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFPresentationScreen *FPresentationScreen;

void PresentationItemCallback(SPresItem item)
{
        FPresentationScreen->PresentationItemCallback(item);
}


//---------------------------------------------------------------------------
__fastcall TFPresentationScreen::TFPresentationScreen(TComponent* Owner)
        : TForm(Owner)
{
        current_index=0;
        capturing=false;
}
//---------------------------------------------------------------------------
void __fastcall TFPresentationScreen::Button1Click(TObject *Sender)
{
        if( capturing==false )
        {
                capturing=true;
                simmgr->setPresentationCapturingEnabled(true);
                Button1->Caption=Translate("PRES_STOP_CAPTURING").c_str();
        }
        else
        {
                capturing=false;
                simmgr->setPresentationCapturingEnabled(false);
                Button1->Caption=Translate("PRES_START_CAPTURING").c_str();
        }
}
//---------------------------------------------------------------------------


void TFPresentationScreen::PresentationItemCallback(SPresItem item)
{
        if( current_index-1< presentation.size() && current_index-1>=0
                && item.newmol==false && item.molname!="" && presentation[current_index-1].molname==item.molname )
        {
                SPresItem *curr_item=&presentation[current_index-1];
                curr_item->data+="\r\n"+item.data;
                curr_item->description="";

        }
        else
        {
                presentation.insert( presentation.begin()+current_index, item);
                ++current_index;
        }
        
        BuildListBox();
}

void TFPresentationScreen::BuildListBox(void)
{
        ListBox1->Items->Clear();

        for(size_t i=0;i<presentation.size();++i)
        {
                SPresItem *item=&presentation[i];
                if( item->molname!="" )
                {
                        ListBox1->Items->Add((Translate("PRES_CREATE")+" "+item->molname).c_str());
                }
                else
                {
                        ListBox1->Items->Add( Translate(item->title).c_str() );
                }
        }

        ListBox1->ItemIndex=current_index-1;

        if( current_index>presentation.size() )
                current_index=presentation.size();
}

int TFPresentationScreen::getRealIndex(void)
{
        int idx=ListBox1->ItemIndex;
        return idx;
}

void __fastcall TFPresentationScreen::ListBox1Click(TObject *Sender)
{
        int idx=getRealIndex();
        if( idx!=-1 )
        {
                ExecutePresentation(idx);
                current_index=idx+1;

                std::string txt=presentation[idx].description;
                std::string key=getuntil("|", txt);
                if( key!="" )
                        txt.erase(0,key.size()+1);
                else
                        key=txt;

                Label2->Caption=Translate(key, txt).c_str();
        }
        else
        {
                Button7Click(Sender);                
        }
}
//---------------------------------------------------------------------------

void __fastcall TFPresentationScreen::Button2Click(TObject *Sender)
{
        if( SaveDialog1->Execute() )
        {
                SavePresentation(SaveDialog1->FileName);                
        }

        FLoadingScreen->restoreCurrentDir();
}
//---------------------------------------------------------------------------

bool TFPresentationScreen::SavePresentation(AnsiString filename, int till)
{
        TStringList *lst=new TStringList;

        for(size_t i=0;i<presentation.size();++i)
        {
                SPresItem *item=&presentation[i];

                if( item->title=="PRES_PAUSE" )
                        SavePositions(lst, (int)i);
                
                if( till>-1 && i>till )
                        lst->Add("HideNewAtoms()");

                if( item->molname!="" )
                {
                        lst->Add(("SetCurrentCaptureName(\""+item->molname+"\");").c_str());
                }

                lst->Add( item->data.c_str() );

                if( item->molname!="" )
                {
                        lst->Add("SetCurrentCaptureName(nil);\r\n");
                }
        }

        if( till!=-1 && till!=presentation.size()-1)
                lst->Add("ShowNewAtoms()");

        SavePositions(lst, (int)presentation.size());

        try
        {
        lst->SaveToFile(filename);
        }
        catch(...)
        {
                delete lst;
                return false;
        }

        delete lst;
        return true;
}

bool TFPresentationScreen::LoadPresentation(AnsiString filename)
{
        /*TStringList *lst=new TStringList;

        try{
        lst->LoadFromFile(filename);
        }
        catch(...){ delete lst; return false; }

        for(int i=0;i<lst->Count;++i)
        {
                std::string line=lst->Strings[i].c_str();

                if( line.find("--")!=-1 && line.find("|")!=-1 )
                {
                        SPresItem item;
                        item.data=line;

                        std::string comment=getafter("--", line);
                        item.title=getuntil("|", comment);
                        comment.erase(0, item.title.size()+1);
                        item.description=comment;

                        simmgr->AddPresentationItem(item.title, item.description, item.data);
                }
        }

        BuildListBox();

        return true;*/

        simmgr->setPresentationCapturingEnabled(true);
        FMainScreen->ExecuteScript(filename);
        simmgr->setPresentationCapturingEnabled(capturing);
        
        return true;        
}

void __fastcall TFPresentationScreen::Button3Click(TObject *Sender)
{
        if( OpenDialog1->Execute() )
        {
                FMainScreen->Neu1Click(Sender);
                simmgr->ResetCapturing();
                presentation.clear();
                current_index=0;
                simmgr->setAllowPause(false);
                LoadPresentation( OpenDialog1->FileName );
        }
        FLoadingScreen->restoreCurrentDir();
}
//---------------------------------------------------------------------------

void __fastcall TFPresentationScreen::Button7Click(TObject *Sender)
{
        presentation.clear();
        BuildListBox();
        current_index=0;
        Label2->Caption="";
        simmgr->ResetCapturing();
        simmgr->setPresentationCapturingEnabled(false);
        FMainScreen->Neu1Click(NULL);
        simmgr->setPresentationCapturingEnabled(capturing);
}
//---------------------------------------------------------------------------

bool TFPresentationScreen::ExecutePresentation(int till)
{
        if( till!=-1 )
                simmgr->setAllowPause(false);
                
        int idx=ListBox1->ItemIndex;
        SavePresentation("tmp.lua", till);
        Button7Click(NULL);
        simmgr->setPresentationCapturingEnabled(true);
        simmgr->ResetCapturing();
        FMainScreen->ExecuteScript("tmp.lua");
        simmgr->setPresentationCapturingEnabled(capturing);
        DeleteFile("tmp.lua");
        ListBox1->ItemIndex=idx;

        simmgr->setAllowPause(true);
} 

void __fastcall TFPresentationScreen::Button6Click(TObject *Sender)
{
        if( presentation.size()==0 )
                return;
                
        if(presentation.size()==1 && current_index==0)
                current_index=1;
        presentation.erase( presentation.begin()+current_index-1 );
        BuildListBox();

        ListBox1->ItemIndex=current_index-1;

        if( current_index>presentation.size() )
        {
                current_index=presentation.size();
                ListBox1->ItemIndex=current_index-1;
        }

        ListBox1Click(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TFPresentationScreen::BitBtn1Click(TObject *Sender)
{
        if( presentation.size()==0 )
                return;
                
        int idx=current_index-1;
        if( idx-1>=0 && idx<presentation.size() )
        {
                SPresItem item=presentation[idx];
                presentation[idx]=presentation[idx-1];
                presentation[idx-1]=item;
                BuildListBox();

                ListBox1->ItemIndex=idx-1;
                
                ListBox1Click(Sender);
        }
}
//---------------------------------------------------------------------------

void __fastcall TFPresentationScreen::BitBtn2Click(TObject *Sender)
{
        if( presentation.size()==0 )
                return;
                
        int idx=current_index-1;
        if( idx+1<presentation.size() && idx>=0 )
        {
                SPresItem item=presentation[idx];
                presentation[idx]=presentation[idx+1];
                presentation[idx+1]=item;
                BuildListBox();

                ListBox1->ItemIndex=idx+1;

                ListBox1Click(Sender);
        }

}
//---------------------------------------------------------------------------

void __fastcall TFPresentationScreen::Button5Click(TObject *Sender)
{
        SPresItem item;
        item.title="PRES_PAUSE";
        item.description="PRES_PAUSE_DESCR";
        item.data="pause();";

        presentation.insert(presentation.begin()+current_index, item);
        ++current_index;

        BuildListBox();
}
//---------------------------------------------------------------------------

void __fastcall TFPresentationScreen::Button4Click(TObject *Sender)
{
        simmgr->setAllowPause(true);
        ExecutePresentation();        
}
//---------------------------------------------------------------------------


void TFPresentationScreen::SavePositions(TStringList *lst, int till)
{
        if( CheckBox1->Checked==false )
                return;
                
        std::vector<int> ids=simmgr->getCapturedAtomIDs();
        for(size_t i=0;i<ids.size();++i)
        {
             std::string cid=simmgr->getCaptureID(ids[i]);
             bool found=false;
             for(size_t i=0;i<presentation.size() && (int)i<=till;++i)
             {
                if( presentation[i].data.find("local "+cid+"=")!=-1 )
                {
                        found=true;
                        break;
                }
             }
             if( found==true )
             {
                     CAtom* atom=simmgr->getAtom(ids[i]);
                     if( atom!=NULL )
                     {
                        core::vector3df position=atom->getPosition();
                        std::string data="SetAtomPosition("+cid+", "+convert(position.X)+", "+convert(position.Y)+", "+convert(position.Z)+");";
                        lst->Add(data.c_str() );
                     }
             }
        }
}

bool TFPresentationScreen::Undo(void)
{
        if( presentation.size()>0 && current_index>=0 && current_index<presentation.size()+1 )
        {
                Button6Click(NULL);
                return true;
        }
        else
                return false;
}



