extern "C"
{
#ifdef _WIN32
	#include "../lua/lua.h"
	#include "../lua/lualib.h"
	#include "../lua/lauxlib.h"
#else 
	#include <lua50/lua.h>
	#include <lua50/lualib.h>
	#include <lua50/lauxlib.h>
#endif
}