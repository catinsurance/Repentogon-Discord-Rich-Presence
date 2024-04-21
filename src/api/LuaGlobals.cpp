#include <lua.hpp>
#include "LuaCore.h"
#include "IsaacRepentance.h"
#include "HookSystem.h"

const int API_VERSION = 1;

// Get the API version number.
// Used for backwards compatibility.
LUA_FUNCTION(Lua_DiscordRPC_GetVersion) {
	
	lua_pushinteger(L, API_VERSION);

	return 1;
}

HOOK_METHOD(LuaEngine, RegisterClasses, () -> void) {
	super();

	lua_State* L = _state;
	lua::LuaStackProtector protector(L);

	lua_pushcfunction(L, Lua_DiscordRPC_GetVersion);
	lua_setglobal(L, "_DISCORDRPC_VERSION");
}