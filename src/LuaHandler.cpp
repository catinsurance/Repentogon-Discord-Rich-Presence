
#include "ConfigHandler.h"
#include "LuaCore.h"
#include <HookSystem.h>

IsaacDiscordOptions modOptions;

LUA_FUNCTION(Lua_DiscordRichPresence_SaveAndReload) {
	modOptions.LoadFromLua();
	modOptions.SaveAll();
	return 1;
}

// Register a global we can call to update the Discord Rich Presence.
// I plan to add more stuff to this in the future.
HOOK_METHOD(LuaEngine, RegisterClasses, () -> void) {
	super();

	lua_State* L = g_LuaEngine->_state;
	lua::LuaStackProtector protector(L);

	lua_pushcfunction(L, Lua_DiscordRichPresence_SaveAndReload);
	lua_setglobal(L, "DiscordRichPresence_SaveAndReload");

}

HOOK_STATIC(Isaac, Shutdown, () -> void, __cdecl) {
	super();
	modOptions.LoadFromLua(); // Get config values from lua
	modOptions.SaveAll(); // Save
}