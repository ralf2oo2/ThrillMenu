#pragma once
#include <cstring>

namespace internallua {

	//luaL_getfield
	typedef int(__fastcall* _luaL_getfield)(void* L, int index, const char* k);
	inline _luaL_getfield luaL_getfield = (_luaL_getfield)0x76ED70;

	//luaL_setfield
	typedef int(__fastcall* _luaL_setfield)(void* L, int index, const char* k);
	inline _luaL_setfield luaL_setfield = (_luaL_setfield)0x76F320;

	//luaL_loadfilex
	typedef int(__fastcall* _luaL_loadfilex)(void* L, const char* filename);
	inline _luaL_loadfilex luaL_loadfilex = (_luaL_loadfilex)0x77E5B0;

	//luaL_loadbuffer
	typedef int(__fastcall* _luaL_loadbuffer)(void* L, const char* buff, size_t sz, const char* name);
	inline _luaL_loadbuffer luaL_loadbuffer = (_luaL_loadbuffer)0x77E790;

	//luaL_loadstring
	inline int luaL_loadstring(void* L, const char* s) {
		if (!L || !s) return -1;
		return luaL_loadbuffer(L, s, std::strlen(s), s);
	}

	//lua_pcall
	typedef int(__fastcall* _lua_pcall)(void* L, int nargs, int nresults, int errfunc);
	inline _lua_pcall lua_pcall = (_lua_pcall)0x76FC80;

	//lua_toboolean
	typedef int(__fastcall* _lua_toboolean)(void* L, int index);
	inline _lua_toboolean lua_toboolean = (_lua_toboolean)0x401070;

	//lua_tolstring
	typedef const char* (__fastcall* _lua_tolstring)(void* L, int idx, size_t* len);
	inline _lua_tolstring lua_tolstring = (_lua_tolstring)0x76E810;

	//reader_string getS in lua source
	typedef const char*(__fastcall* _reader_string)(void* L, void* data, size_t* size);
	inline _reader_string reader_string = (_reader_string)0x77E770;

	typedef int(__fastcall* _lua_next)(void* L, int idx);
	inline _lua_next lua_next = (_lua_next)0x76ffa0;

	typedef int(__fastcall* _lua_settop)(void* L, int idx);
	inline _lua_settop lua_settop = (_lua_settop)0x76e170;

	inline int lua_gettop(void* L) {
		if (!L) return 0;
		return (*(int*)((char*)L + 8) - *(int*)((char*)L + 12)) >> 4;
	}

	typedef int (*lua_CFunction)(void* L);
	typedef void (__fastcall* _lua_pushcclosure)(void* L, lua_CFunction fn, int n);
	inline _lua_pushcclosure lua_pushcclosure = (_lua_pushcclosure)0x76ead0;

	typedef int(__fastcall* _lua_getinfo)(void* L, char *what, void *ar);
	inline _lua_getinfo lua_getinfo = (_lua_getinfo)0x78a760;

	typedef void *(__fastcall* _index2adr)(void* L, int idx);
	inline _index2adr index2adr = (_index2adr)0x76dd90;

	inline int lua_type(lua_State *L, int idx) {
		void* slot = index2adr(L, idx);
		if (!slot) {
			return -1;
		}

		return *reinterpret_cast<int*>(reinterpret_cast<char*>(slot) + 0xc);
	}

	typedef void *(__fastcall* _lua_topointer)(void* L, int idx);
	inline _lua_topointer lua_topointer = (_lua_topointer)0x7701d0;

	typedef char *(__fastcall* _lua_typename)(void* L, int idx);
	inline _lua_typename lua_typename = (_lua_typename)0x77e8e0;
}
