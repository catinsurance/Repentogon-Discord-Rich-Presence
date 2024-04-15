
#define MINI_CASE_SENSITIVE
#include "ini.h"

#include <IsaacRepentance.h>
#include <filesystem>

// I heavily referenced Repentogon's saving and loading of
// their config file for this. Thank you, I learned a lot!

// Converts a string to an integer, and if it fails, returns default.
inline int defstoi(const std::string& str, int default) {
	try {
		return std::stoi(str);
	}
	catch (...) {
	}
	return default;
}

struct IsaacDiscordOptions {

	static const char* GetModDataPath() {
		std::string path = std::string((char*)&g_SaveDataPath) + "DiscordRichPresence/";
		if (!CreateDirectory(path.c_str(), NULL)) {
			if (GetLastError() != ERROR_ALREADY_EXISTS) {
				return "";
			}
		}
		return path.c_str();
	}

	void Init() {
		optionsPath = std::string(GetModDataPath());
		optionsPath.append("options.ini");

		mINI::INIFile iniFile(optionsPath);

		// Create options.ini
		if (!std::filesystem::exists(optionsPath)) {
			ini["Customization"]["ShowModdedCharacters"] = "0"; // Show modded character names. Also show portraits if they're supported.
			ini["Customization"]["ShowModdedStages"] = "0"; // Show a generic message with a modded stage's name, or a special title if they're supported.
			ini["Customization"]["ShowTimer"] = "1"; // Show the timer for how long you've been in game/on the menu.
			iniFile.generate(ini, true);
		}

		iniFile.read(ini);
	}

	// Initializes the lua script's copy of the config
	void InitLua() {
		if (luaConfigFailed) {
			return;
		}

		Set("Customization", "ShowModdedCharacters", defstoi(ini["Customization"]["ShowModdedCharacters"], 0));
		Set("Customization", "ShowModdedStages", defstoi(ini["Customization"]["ShowModdedStages"], 0));
		Set("Customization", "ShowTimer", defstoi(ini["Customization"]["ShowTimer"], 1));
	}

	// Loads config from lua
	void LoadFromLua() {
		if (luaConfigFailed) {
			return;
		}

		GetFromLua("Customization", "ShowModdedCharacters", false);
		GetFromLua("Customization", "ShowModdedStages", false);
		GetFromLua("Customization", "ShowTimer", true);
	}

	// Gets the value of (field) in (category) 
	bool Get(char* category, char* field) {
		mINI::INIFile iniFile = optionsPath;
		return ini[category][field] == "1" ? true : false;
	}

	// Updates the boolean field and returns the result
	bool GetFromLua(char* category, char* name, bool default) {
		mINI::INIFile iniFile = optionsPath;

		// Just load default
		if (luaConfigFailed) {
			return default;
		}

		lua_State* L = g_LuaEngine->_state;
		lua_getglobal(L, "DiscordRichPresenceConfig");

		if (lua_istable(L, -1)) {
			lua_getfield(L, -1, category);

			if (lua_istable(L, -1)) {
				lua_getfield(L, -1, name);

				if (!lua_isnil(L, -1)) {
					ini[category][name] = lua_toboolean(L, -1) ? "1" : "0"; // Update bool
					lua_pop(L, 2); // Clear stack
					return ini[category][name] == "1";
				}

				lua_pop(L, 1);
			}
		}

		return default;
	}

	// Sets the value of (field) in (category)
	bool Set(char* category, char* field, bool value) {
		mINI::INIFile iniFile = optionsPath;
		ini[category][field] = value ? "1" : "0";

		if (!luaConfigFailed) {
			lua_State* L = g_LuaEngine->_state;
			lua_getglobal(L, "DiscordRichPresence_Set");

			if (lua_isfunction(L, -1)) {
				lua_pushstring(L, category);
				lua_pushstring(L, field);
				lua_pushboolean(L, value);

				lua_pcall(L, 3, 0, 0); // Run function
			}
		}

		return iniFile.write(ini);
	}

	void SaveAll() {
		mINI::INIFile iniFile = optionsPath;
		iniFile.write(ini, true);
	}

	mINI::INIStructure ini;
	std::string optionsPath;
	bool luaConfigFailed = false;
};

extern IsaacDiscordOptions modOptions;