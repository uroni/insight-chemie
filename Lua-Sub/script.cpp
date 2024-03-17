#include <string>
#include <fstream>
#include <iostream>
#include <map>

#pragma hdrstop

#include "script.h"
#include "lua_macros.h"
#include "stringtools.h"

//libs

#include "lib_create.h"
#include "lib_html.h"


using namespace std;

void LUA::LoadLib(luaL_reg* reg,std::string libname)
{
	if(libname.size()>0)
	{
		lua_newtable(lua);
		for(int i=0;reg[i].name!=NULL;i++)
		{
			lua_pushstring(lua,reg[i].name);
			lua_pushcfunction(lua,reg[i].func);
			lua_settable(lua,-3);
		}
		lua_setglobal(lua,libname.c_str() );
	}
	else
	{
		for(int i=0;reg[i].name!=NULL;i++)
		{
			RegisterFunction(reg[i].name,reg[i].func);
		}
	}
}


LUA::LUA(string ErrorLogFile)
{
	lua = lua_open();
	if(lua==0)return;


	lua_baselibopen(lua);
	lua_tablibopen(lua);
	lua_iolibopen(lua);
	lua_strlibopen(lua);
	lua_mathlibopen(lua);
	lua_dblibopen(lua);

        LoadLib(&lib_html);
        LoadLib(&lib_create);

	errlog.open(ErrorLogFile.c_str(),ios::out|ios::binary);
}



LUA::~LUA(void)
{
	if(lua)
		lua_close(lua);
	if(errlog.is_open()==true)
		errlog.close();
}

bool LUA::Execute(string FileName,string function)
{
        this->RegisterGlobal("currdir",ExtractFilePath( FileName) );

	if( FileName!=""&&luaL_loadfile( lua,FileName.c_str() )!=0)
	{
                error="Error compiling "+FileName+":\r\n\t\t"+lua_tostring(lua,-1);
		errlog << error <<"\r\n";
		/*if(FileName!="errors.lua")
		{
			this->RegisterGlobal("CompileError",lua_tostring(lua, -1) );
			this->Execute("errors.lua");
			this->Execute("errors.lua","comperror");
		} */
		return false;
	}	

	int err=1;
	int args=0;
	if(function!=""&&function.find("pushed")!=0)
	{
			lua_pushstring(lua, function.c_str() );
			lua_gettable(lua, LUA_GLOBALSINDEX);
			if(!lua_isfunction(lua,-1))
			{
				error="Error running script "+FileName+":\r\n\t\tFunction "+function+" does not exist";
                                errlog << error << "\r\n";
				return false;
			}	
	}
	else if(function.find("pushed")==0)
	{
			args=atoi(&function[6] );
			if(!lua_isfunction(lua,-1-args))
			{
				error="Error running script "+FileName+":\r\n\t\tFunction "+function+" does not exist";
                                errlog << error << "\r\n";
				return false;
			}	
	}
			
	err=lua_pcall( lua, args, LUA_MULTRET ,0);
	if(err!=0)
	{
		error="Error running script "+FileName+":\r\n\t\t"+lua_tostring(lua, -1)+"\r\n";
                errlog << error << "\r\n";
		errlog.sync();
		/*this->RegisterGlobal("ExeptionError",lua_tostring(lua, -1) );
		this->Execute("errors.lua");
		this->Execute("errors.lua","FatalException");*/

		return false;
	}
	
	return true;
}

bool LUA::RegisterFunction(std::string funktioname, lua_CFunction function)
{
	lua_register(lua,funktioname.c_str(),function);
	return true;
}

void LUA::RegisterGlobal(std::string name,std::string value)
{
	lua_pushstring(lua,value.c_str() );
	lua_setglobal(lua,name.c_str() );
}

void LUA::RegisterGlobal(std::string name,int value)
{
        lua_pushnumber(lua,value);
	lua_setglobal(lua,name.c_str() );
}

void LUA::log(string str)
{
	errlog << str << "\r\n";
}

lua_State* LUA::getState(void)
{
	return lua;
}

bool LUA::Callfunction(std::string function)
{
	lua_getglobal(lua,function.c_str() );
	int err=lua_pcall( lua, 0, LUA_MULTRET, 0);
	if(err!=0)
	{
		error="Error running function "+function+": "+lua_tostring(lua, -1);
		/*this->RegisterGlobal("ExeptionError",str );
		this->Execute("errors.lua");
		this->Execute("errors.lua","FatalException");*/
		return false;
	}
	return true;
}

bool LUA::Callfunction(string function, int argc)
{
	int err=lua_pcall( lua, argc, LUA_MULTRET, 0);
	if(err!=0)
	{
		error="Error running function "+function+": "+lua_tostring(lua, -1);
		/*this->RegisterGlobal("ExeptionError",str );
		this->Execute("errors.lua");
		this->Execute("errors.lua","FatalException");*/
		return false;
	}
	return true;
}

std::string LUA::getError(void)
{
        return error;
}
