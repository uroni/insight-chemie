#include <string>
#include <Dialogs.hpp>

#pragma hdrstop

#include "lua_macros.h"
#include "lua.h"

#include "CSimMgr.h"

void Sleep2(int time);
void Pause(void);
void Respeed(void);

extern AnsiString app_title;


LUAF(CreateAtom)
{
        c1STRINGARG(CreateAtom);

        std::string name;
        if( lua_isstring(lua,2) )
                name=lua_tostring(lua,2);

        bool set_pos=false;
        float posx=0;
        if( lua_isnumber(lua,3) )
        {
                posx=lua_tonumber(lua,3);
                set_pos=true;
        }
        float posy=0;
        if( lua_isnumber(lua,4) )
                posy=lua_tonumber(lua,4);

        float posz=0;
        if( lua_isnumber(lua,5) )
                posz=lua_tonumber(lua,5);


        int id=simmgr->addAtom(simmgr->getElement(lua_tostring(lua,1) ), name, posx,posy,posz);

        if( set_pos == true )
                simmgr->getAtom(id)->setPosition(core::vector3df(posx, posy, posz) );

        Respeed();

        if( id!=-1 )
                lua_pushnumber(lua,id);
        else
                lua_pushnil(lua);
                
        return 1;
}

LUAF(Connect)
{
        c2INTARG( Connect );

        bool b=simmgr->Connect((int)lua_tonumber(lua,1), (int)lua_tonumber(lua,2));
        Respeed();

        if( b==true )
        {
                lua_pushnumber(lua,1);
                return 1;
        }

        return 0;
}


LUAF(Disconnect)
{
        c2INTARG( Disconnect );

        bool b=simmgr->Disconnect((int)lua_tonumber(lua,1), (int)lua_tonumber(lua,2));
        Respeed();

        PUSHBOOL(b);

        return 1;
}

LUAF(AddAction)
{
        c2STRINGARG( AddAction );

        std::string fname=lua_tostring(lua,2);

        if( lua_isstring(lua,3 ) )
                fname=lua_tostring( lua,3 );

        if( lua_isstring(lua,4 ) )
        {
                fname+=" ";
                fname+=lua_tostring(lua,4);
        }

        simmgr->addAction(lua_tostring(lua,1), lua_tostring(lua,2), fname);

        return 0;
}

LUAF(GetMoleculeName)
{
        c1INTARG( GetMoleculeName );

        CAtom* atom=simmgr->getAtom(lua_tonumber(lua,1) );

        if( atom!=NULL )
                lua_pushstring(lua, atom->getName().c_str() );
        else
                lua_pushnil(lua);

        return 1;
}

LUAF(GetAtomName)
{
        c1INTARG( GetMoleculeName );

        CAtom* atom=simmgr->getAtom(lua_tonumber(lua,1) );

        if( atom!=NULL )
                lua_pushstring(lua, atom->getElementData().name.c_str() );
        else
                lua_pushnil(lua);

        return 1;

}

LUAF(SetMoleculeName)
{
        cINTSTRINGARG( GetMoleculeName );

        CAtom* atom=simmgr->getAtom(lua_tonumber(lua,1) );

        bool b=false;

        if( atom!=NULL )
        {
                std::vector<CAtom*> atoms;
                simmgr->getMolecule(atom, atoms);

                for(size_t i=0;i<atoms.size();++i)
                {
                        atoms[i]->setName( lua_tostring(lua,2) );
                        b=true;
                }
        }

        PUSHBOOL(b);
        return 1;
}

LUAF(lua_Sleep)
{
        c1INTARG(Sleep);

        int n=(int)lua_tonumber(lua,1);

        Sleep2(n);
        return 0;
}

LUAF(lua_Pause)
{
        Pause();
        return 0;
}

LUAF(Alert)
{
        c1STRINGARG(Alert);
        MessageBoxA(0,lua_tostring(lua,1), app_title.c_str(), 0 );

        return 0;
}

LUAF(RemoveMolecule)
{
        c1STRINGARG( RemoveMolecule );

        CAtom* start=simmgr->getAtom( lua_tonumber(lua,1) );

        bool b=false;

        {
        if( start!=NULL )
        {
                std::vector<CAtom*> todel;
                simmgr->getMolecule(start, todel);

                for(size_t i=0;i<todel.size();++i)
                {
                        simmgr->removeAtom( todel[i]->getID() );
                        b=true;
                }
        }
        }

        Respeed();

        PUSHBOOL(b);
        return 0;
}

LUAF(Cap)
{
        c1INTARG(Cap);

        int a1=lua_tonumber(lua,1 );

        int a2=-1;

        if( lua_isnumber(lua,2)==true )
                a2=lua_tonumber(lua,2);

        if( a2!=-1 )
        {
                simmgr->Disconnect(a1, a2, true);
        }
        else
        {
                CAtom* a=simmgr->getAtom( a1 );
                CConnection *con;
                while((con=a->getConnection(0))!=NULL)
                {                                 
                        simmgr->Disconnect( con, a1 );
                }
        }

        Respeed();

        return 0;
}

LUAF(lua_InputBox)
{
        c1STRINGARG( InputBox );

        AnsiString input;
        if( lua_isstring(lua,2)==true )
                input=lua_tostring(lua,2);
                
        bool ret=InputQuery(app_title.c_str(),lua_tostring(lua,1),input);
        if(ret==true)
                lua_pushstring(lua,input.c_str());
        else
                lua_pushnil(lua);
        return 1;
}

LUAF(SetMoleculeID)
{
        c2INTARG( SetMoleculeID );

        CAtom* atom=simmgr->getAtom(lua_tonumber(lua,1) );

        bool b=false;

        if( atom!=NULL )
        {
                std::vector<CAtom*> atoms;
                simmgr->getMolecule(atom, atoms);

                for(size_t i=0;i<atoms.size();++i)
                {
                        atoms[i]->setMoleculeID( (int)lua_tonumber(lua,2) );
                        b=true;
                }
        }

        PUSHBOOL(b);
        return 1;
}

LUAF(HideNewAtoms)
{
        simmgr->HideNewAtoms(true);
        return 0;
}

LUAF(ShowNewAtoms)
{
        simmgr->HideNewAtoms(false);
        return 0;
}

LUAF(SetCurrentCaptureName)
{
        if( lua_isstring(lua,1) )
        {
                simmgr->setCaptureMoleculeName(lua_tostring(lua,1) );
        }
        else
                simmgr->setCaptureMoleculeName("");

        return 0;
}

LUAF(SetAtomPosition)
{
        c4INTARG(SetAtomPosition);

        CAtom* atom=simmgr->getAtom( (int)lua_tonumber(lua,1) );
        if( atom!=NULL)
        {
                core::vector3df position;
                position.X=lua_tonumber(lua,2);
                position.Y=lua_tonumber(lua,3);
                position.Z=lua_tonumber(lua,4);

                atom->setPosition(position);

                lua_pushboolean(lua,1);
        }
        else
                lua_pushnil(lua);
        return 1;
}

LUAF(RemoveAtom)
{
        c1INTARG(RemoveAtom);

        PUSHBOOL(simmgr->removeAtom( (int)lua_tonumber(lua,1) ));
        
        return 1;
}

luaL_reg lib_create [] = {
        {"CreateAtom", CreateAtom},
        {"Connect", Connect},
        {"Disconnect", Disconnect},
        {"AddAction", AddAction },
        {"GetMoleculeName", GetMoleculeName },
        {"GetAtomName", GetAtomName },
        {"SetMoleculeName", SetMoleculeName},
        {"Sleep", lua_Sleep},
        {"sleep", lua_Sleep},
        {"Pause", lua_Pause},
        {"pause", lua_Pause},
        {"Alert", Alert },
        {"alert", Alert },
        {"RemoveMolecule", RemoveMolecule},
        {"Cap", Cap },
        {"InputBox", lua_InputBox },
        {"SetMoleculeID", SetMoleculeID },
        {"HideNewAtoms", HideNewAtoms},
        {"ShowNewAtoms", ShowNewAtoms},
        {"SetCurrentCaptureName", SetCurrentCaptureName},
        {"SetAtomPosition", SetAtomPosition},
        {"RemoveAtom", RemoveAtom},
	{NULL, NULL}
};