
#include "ConfigHandler.h"
#include "LuaCore.h"
#include <HookSystem.h>

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

	// Load the enumerators file
	std::string scriptPath = std::filesystem::current_path().string() + "/isaac-discord-scripts/Enums.lua";
	printf("[DISCORD] Attempting to load %s\n", scriptPath.c_str());
	if (std::filesystem::exists(scriptPath)) {
		printf("[DISCORD] Running enums script.\n");
		g_LuaEngine->RunScript(scriptPath.c_str());
	}
	else {
		printf("[DISCORD] Couldn't load enums script.\n");
	}
}

HOOK_STATIC(Isaac, Shutdown, () -> void, __cdecl) {
	super();
	modOptions.LoadFromLua(); // Get config values from lua
	modOptions.SaveAll(); // Save
}