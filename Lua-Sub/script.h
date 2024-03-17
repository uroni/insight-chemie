#ifndef SCRIPT_H
#define SCRIPT_H

#include <fstream>
#include <string>

extern "C"
{
#ifdef _WIN32
	#include "lua/lua.h"
	#include "lua/lualib.h"
	#include "lua/lauxlib.h"
#else 
	#include <lua50/lua.h>
	#include <lua50/lualib.h>
	#include <lua50/lauxlib.h>
#endif
}



class LUA
{
public:
	LUA(std::string ErrorLogFile="lua.log");
	~LUA(void);
	bool Execute(std::string FileName,std::string function="");
	bool RegisterFunction(std::string funktioname,lua_CFunction function);
	void RegisterGlobal(std::string name,std::string value);
        void RegisterGlobal(std::string name,int value);
	void log(std::string str);
	void LoadLib(luaL_reg* reg,std::string libname="");
	bool Callfunction(std::string function);
	bool Callfunction(std::string function, int argc);
        std::string getError(void);

	lua_State* getState(void);

private:
	lua_State* lua;
	std::fstream errlog;
        std::string error;
};



#endif
