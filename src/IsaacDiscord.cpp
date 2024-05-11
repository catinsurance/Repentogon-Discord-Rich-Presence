#include <ctime>
#include "IsaacRepentance.h"
#include "HookSystem.h"
#include "DiscordAPI.h"
#include "ConfigHandler.h"
#include "GameInfoStrings.h"

int prevState = 0;

enum LastGameState {
	LAST_GAME_STATE_MENU = 0,
	LAST_GAME_STATE_GAME = 1,
	LAST_GAME_STATE_LOADING = 2,
};

int lastGameState = LastGameState::LAST_GAME_STATE_LOADING;
int prevMenu = 0;
int currentMenuIcon = 1;
bool deathScreenShowing = false;
bool luaConfigInit = false;

char* numToTitleIcon(int num) {
	switch (num) {
	case 1:
		return "title_1";
	case 2:
		return "title_2";
	case 3:
		return "title_3";
	case 4:
		return "title_4";
	case 5:
		return "title_5";
	case 6:
		return "title_6";
	case 7:
		return "title_7";
	default:
		return "title_1";
	}

}

char* getStageString() {
	lua_State* L = g_LuaEngine->_state;
	lua_getglobal(L, "StageAPI");
	if (!lua_istable(L, -1)) {
		int stbStage = RoomConfig::GetStageID(g_Game->_stage, g_Game->_stageType, -1);
		return stageToTitle(stbStage);
	}
	else {
		// Check stage name
		lua_getfield(L, -1, "GetCurrentStage");
		int error = lua_pcall(L, 0, 1, 0);
		if (error) {
			// Just return normal stage
			int stbStage = RoomConfig::GetStageID(g_Game->_stage, g_Game->_stageType, -1);
			return stageToTitle(stbStage);
		}
		else {
			// Check if nil

			if (lua_istable(L, -1)) {
				lua_getfield(L, -1, "Name");

				// It's a string.
				if (lua_isstring(L, -1)) {
					const char* moddedStageName = lua_tostring(L, -1);
					char* returnValue = moddedStageToTitle(moddedStageName);
					lua_pop(L, 3);
					return returnValue;
				}
				else {
					// Just return normal stage
					int stbStage = RoomConfig::GetStageID(g_Game->_stage, g_Game->_stageType, -1);
					
					if (lua_isnil(L, -1)) {
						lua_pop(L, 2);
					}
					else {
						lua_pop(L, 3);
					}

					return stageToTitle(stbStage);
				}
			}
			else {
				int stbStage = RoomConfig::GetStageID(g_Game->_stage, g_Game->_stageType, -1);

				if (lua_isnil(L, -1)) {
					lua_pop(L, 1);
				}
				else {
					lua_pop(L, 2);
				}

				return stageToTitle(stbStage);
			}
		}
	}
}

void InitLuaConfig() {
	// Load the ImGui lua file
	std::string scriptPath = std::filesystem::current_path().string() + "/isaac-discord-scripts/ImGuiHandler.lua";
	printf("[DISCORD] Attempting to load %s\n", scriptPath.c_str());
	if (std::filesystem::exists(scriptPath)) {
		printf("[DISCORD] Running config script.\n");
		g_LuaEngine->RunScript(scriptPath.c_str());
	}
	else {
		printf("[DISCORD] Config script did not exist in location. Run failsafe.\n");
		modOptions.luaConfigFailed = true;
	}

	// Initialize settings
	modOptions.InitLua();
}

HOOK_METHOD(MenuManager, Render, () -> void) {
	super();

	if (discordAPI.didntStart) {
		return;
	}

	if (!discordAPI.isRunning) {
		return;
	}

	// Load this here to make sure we load after ImGui and other core scripts
	if (!luaConfigInit) {
		luaConfigInit = true;
		InitLuaConfig();
	}

	if (lastGameState != LastGameState::LAST_GAME_STATE_MENU) {
		lastGameState = LastGameState::LAST_GAME_STATE_MENU;
		modOptions.LoadFromLua();
		RNG rng = RNG();
		rng.SetSeed(max(Random(), 1), 35);
		currentMenuIcon = rng.RandomInt(7) + 1;
		discordAPI.SetStartTimestamp(time(0));
		discordAPI.luaToggle = false;
		deathScreenShowing = false;
	}

	if (discordAPI.luaToggle) {
		return;
	}

	int menu = g_MenuManager->_selectedMenuID;

	if (menu == prevMenu) {
		return;
	}

	prevMenu = menu;

	discordAPI.activity.GetAssets().SetSmallImage("");
	discordAPI.activity.GetAssets().SetSmallText("");

	switch (menu) { // https://repentogon.com/enums/MainMenuType.html
	case 4:
		discordAPI.SetState(numToTitleIcon(currentMenuIcon), "Browsing menus", "Looking at the Daily Run");
		break;
	case 5:
		discordAPI.SetState(numToTitleIcon(currentMenuIcon), "Browsing menus", "Selecting a character");
		break;
	case 6:
		discordAPI.SetState(numToTitleIcon(currentMenuIcon), "Browsing menus", "Selecting a special seed");
		break;
	case 7:
		discordAPI.SetState(numToTitleIcon(currentMenuIcon), "Browsing menus", "Selecting a challenge");
		break;
	case 8:
		discordAPI.SetState(numToTitleIcon(currentMenuIcon), "Browsing menus", "Viewing their item collection");
		break;
	case 9:
		discordAPI.SetState(numToTitleIcon(currentMenuIcon), "Browsing menus", "Checking stats");
		break;
	case 14:
		discordAPI.SetState(numToTitleIcon(currentMenuIcon), "Browsing menus", "Reminiscing on enemies fought");
		break;
	case 15:
		discordAPI.SetState(numToTitleIcon(currentMenuIcon), "Browsing menus", "Selecting a modded challenge");
		break;
	case 16:
		discordAPI.SetState(numToTitleIcon(currentMenuIcon), "Browsing menus", "Viewing their enabled mods");
		break;
	default:
		discordAPI.SetState(numToTitleIcon(currentMenuIcon), "Browsing menus", "Browsing the main menu");
		break;
	}
}

void updateInGame() {
	if (discordAPI.luaToggle) {
		return;
	}

	if (discordAPI.GetEndTimestamp() > discord::Timestamp()) {
		discordAPI.SetStartTimestamp(time(0));
	}

	prevMenu = 0;

	Entity_Player* player = g_Game->GetPlayer(0);
	if (player != nullptr && !deathScreenShowing) {
		int playerType = player->GetPlayerType();
		char* stageString = getStageString();

		switch (g_Game->GetDifficulty()) { // https://wofsauge.github.io/IsaacDocs/rep/enums/Difficulty.html
		case 0:
			discordAPI.activity.GetAssets().SetSmallImage("normal");
			discordAPI.activity.GetAssets().SetSmallText("Normal");
			break;
		case 1:
			discordAPI.activity.GetAssets().SetSmallImage("hard");
			discordAPI.activity.GetAssets().SetSmallText("Hard");
			break;
		case 2:
			discordAPI.activity.GetAssets().SetSmallImage("greed");
			discordAPI.activity.GetAssets().SetSmallText("Greed");
			break;
		case 3:
			discordAPI.activity.GetAssets().SetSmallImage("greedier");
			discordAPI.activity.GetAssets().SetSmallText("Greedier");
			break;
		}

		EntityConfig_Player* playerConfig = g_Manager->GetEntityConfig()->GetPlayer(playerType);
		if (playerType <= 40 && playerConfig != nullptr) {
			// this is probably all a shit way of doing this lol
			uint32_t unk;

			std::string strippedName = std::string(playerConfig->_name);
			strippedName.erase(strippedName.begin() + 0, strippedName.begin() + 1);

			StringTable* stringTable = g_Manager->GetStringTable();
			const char* charName = stringTable->GetString("Players", 0, strippedName.c_str(), &unk);

			std::string buf("Playing as ");
			buf.append(charName);

			discordAPI.SetState(playerToPortrait(playerType), buf.c_str(), stageString);
		}
		else {
			if (modOptions.Get("Customization", "ShowModdedCharacters")) {
				uint32_t unk;

				std::string name = std::string(playerConfig->_name);

				std::string buf("Playing as ");
				buf.append(name);

				bool isTainted = false;
				if (!playerConfig->_bSkinParentName.empty()) {
					isTainted = true;
				}

				if (luaPlayerPortrait.count(playerType)) {
					std::string portrait = luaPlayerPortrait[playerType];
					discordAPI.SetState(portrait.c_str(), buf.c_str(), stageString);
				}
				else {
					discordAPI.SetState(moddedPlayerToPortrait(name.c_str(), isTainted), buf.c_str(), stageString);
				}

			}
			else {
				discordAPI.SetState("unknown", "Playing as a modded character", stageString);
			}
		}
	}
}

HOOK_METHOD(Game, Update, () -> void) {
	super();

	if (discordAPI.didntStart) {
		return;
	}

	if (!discordAPI.isRunning) {
		return;
	}

	// Reset if restarted run or new game
	if (lastGameState != LastGameState::LAST_GAME_STATE_GAME || deathScreenShowing) {
		lastGameState = LastGameState::LAST_GAME_STATE_GAME;
		modOptions.LoadFromLua();
		discordAPI.SetStartTimestamp(time(0));
		deathScreenShowing = false;
		discordAPI.luaToggle = false;
	}

	// Update every new room, because that's usually a good interval of change.
	updateInGame();
}

// Handle special death screen stuff.
HOOK_METHOD(GameOver, Show, () -> void) {
	super();

	if (discordAPI.didntStart) {
		return;
	}

	if (!discordAPI.isRunning) {
		return;
	}

	if (discordAPI.luaToggle) {
		return;
	}

	deathScreenShowing = true;

	discordAPI.SetState("death", "Game over!", "Contemplating their death");
	discordAPI.UpdateActivity();
}

HOOK_STATIC(Manager, Update, () -> void, __stdcall) {
	super();

	// Didn't start because Discord wasn't open.
	if (discordAPI.didntStart) {
		return;
	}

	discordAPI.Update();
	discordAPI.lastUpdate += 1;

	if (discordAPI.lastUpdate >= discordAPI.updateInterval) {
		discordAPI.UpdateActivity();
		discordAPI.lastUpdate = 0;
	}
}