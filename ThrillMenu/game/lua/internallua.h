#pragma once
extern "C" {
#include "lua.h"
}

namespace internallua {

	//luaL_getfield
	typedef int(__fastcall* _luaL_getfield)(lua_State* L, int index, const char* k);
	inline _luaL_getfield luaL_getfield = (_luaL_getfield)0x76F320;

	//luaL_loadstring
	typedef int(__fastcall* _luaL_loadstring)(lua_State* L, const char* s);
	inline _luaL_loadstring luaL_loadstring = (_luaL_loadstring)0x79AB20;

	//luaL_loadfilex
	typedef int(__fastcall* _luaL_loadfilex)(lua_State* L, const char* filename);
	inline _luaL_loadfilex luaL_loadfilex = (_luaL_loadfilex)0x77E5B0;

	//luaL_loadbuffer
	typedef int(__fastcall* _luaL_loadbuffer)(lua_State* L, const char* buff, size_t sz, const char* name);
	inline _luaL_loadbuffer luaL_loadbuffer = (_luaL_loadbuffer)0x77E790;

	//lua_pcall
	typedef int(__fastcall* _lua_pcall)(lua_State* L, int nargs, int nresults, int errfunc);
	inline _lua_pcall lua_pcall = (_lua_pcall)0x76FC80;

	//lua_load
	typedef int(__fastcall* _lua_load)(lua_State* L, lua_Reader reader, void* data, const char* chunkname);
	inline _lua_load lua_load = (_lua_load)0x76FD70;

	//lua_toboolean
	typedef int(__fastcall* _lua_toboolean)(lua_State* L, int index);
	inline _lua_toboolean lua_toboolean = (_lua_toboolean)0x401070;

	//lua_tolstring
	typedef const char* (__fastcall* _lua_tolstring)(lua_State* L, int idx, size_t* len);
	inline _lua_tolstring lua_tolstring = (_lua_tolstring)0x76E810;

	//reader_string getS in lua source
	typedef const char*(__fastcall* _reader_string)(lua_State* L, void* data, size_t* size);
	inline _reader_string reader_string = (_reader_string)0x77E770;
}