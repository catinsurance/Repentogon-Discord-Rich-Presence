#include <lua.hpp>
#include "LuaCore.h"
#include "IsaacRepentance.h"
#include "HookSystem.h"

HOOK_METHOD(LuaEngine, RegisterClasses, () -> void) {
	super();

	lua_State* L = _state;
	lua::LuaStackProtector protector(L);

	lua_pushboolean(L, true);
	lua_setglobal(L, "_DISCORDRPC");
}