#define c2STRINGARG( x ) if(lua_isstring(lua,1)==false||lua_isstring(lua,2)==false ){\
	string str=(string)"Not enough arguments for "+(string)#x;\
	luaL_error(lua,str.c_str() );\
	return 0;}

#define c3STRINGARG( x ) if(lua_isstring(lua,1)==false||lua_isstring(lua,2)==false ||lua_isstring(lua,3)==false){\
	string str=(string)"Not enough arguments for "+(string)#x;\
	luaL_error(lua,str.c_str() );\
	return 0;}

#define LUAF(x) static int x(lua_State* lua)

#define c1STRINGARG(x) if(lua_isstring(lua,1)==false){\
	string str=(string)"Not enough arguments for "+(string)#x;\
	luaL_error(lua,str.c_str() );\
	return 0;}

#define PUSHBOOL(x) if(x==false) lua_pushnil(lua); else lua_pushboolean(lua,1);

#define c1INTARG(x) if(lua_isnumber(lua,1)==false){\
	string str=(string)"Not enough arguments for "+(string)#x;\
	luaL_error(lua,str.c_str() );\
	return 0;}

#define c2INTARG(x) if(lua_isnumber(lua,1)==false || lua_isnumber(lua,2)==false){\
	string str=(string)"Not enough arguments for "+(string)#x;\
	luaL_error(lua,str.c_str() );\
	return 0;}

#define c4INTARG(x) if(lua_isnumber(lua,1)==false || lua_isnumber(lua,2)==false|| lua_isnumber(lua,3)==false|| lua_isnumber(lua,4)==false){\
	string str=(string)"Not enough arguments for "+(string)#x;\
	luaL_error(lua,str.c_str() );\
	return 0;}

#define cINTFLOATARG(x) if(lua_isnumber(lua,1)==false||lua_isnumber(lua,2)==false){\
	string str=(string)"Not enough arguments for "+(string)#x;\
	luaL_error(lua,str.c_str() );\
	return 0;}

#define cINTSTRINGARG(x) if(lua_isnumber(lua,1)==false||lua_isstring(lua,2)==false){\
	string str=(string)"Not enough arguments for "+(string)#x;\
	luaL_error(lua,str.c_str() );\
	return 0;}

#define cINT2FLOATINTARG(x) if(lua_isnumber(lua,1)==false||lua_isnumber(lua,2)==false||lua_isnumber(lua,3)==false||lua_isnumber(lua,2)==false){\
	string str=(string)"Not enough arguments for "+(string)#x;\
	luaL_error(lua,str.c_str() );\
	return 0;}
