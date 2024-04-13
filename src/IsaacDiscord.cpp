#include <ctime>
#include "IsaacRepentance.h"
#include "HookSystem.h"
#include "DiscordAPI.h"

int prevState = 0;

enum LastGameState {
	LAST_GAME_STATE_MENU = 0,
	LAST_GAME_STATE_GAME = 1,
	LAST_GAME_STATE_LOADING = 2,
};

int lastGameState = LastGameState::LAST_GAME_STATE_LOADING;
int currentMenuIcon = 1;
bool deathScreenShowing = false;

char* playerToPortrait(int playerType) {
	switch (playerType) {
	case 0:
		return "playerportrait_isaac";
	case 1:
		return "playerportrait_magdalene";
	case 2:
		return "playerportrait_cain";
	case 3:
		return "playerportrait_judas";
	case 4:
		return "playerportrait_bluebaby";
	case 5:
		return "playerportrait_eve";
	case 6:
		return "playerportarit_samson";
	case 7:
		return "playerportrait_azazel";
	case 8:
		return "playerportrait_lazarus";
	case 9:
		return "playerportrait_eden";
	case 10:
		return "playerportrait_thelost";
	case 11:
		return "playerportrait_lazarus2";
	case 12:
		return "playerportrait_darkjudas";
	case 13:
		return "playerportrait_lilith";
	case 14:
		return "playerportrait_keeper";
	case 15:
		return "playerportrait_apollyon";
	case 16:
		return "playerportrait_theforgotten";
	case 17:
		return "playerportrait_theforgotten";
	case 18:
		return "playerportrait_bethany";
	case 19:
		return "playerportrait_jacob";
	case 20:
		return "playerportrait_jacob";
		// Tainteds
	case 21:
		return "playerportrait_isaac_b";
	case 22:
		return "playerportrait_magdalene_b";
	case 23:
		return "playerportrait_cain_b";
	case 24:
		return "playerportrait_judas_b";
	case 25:
		return "playerportrait_bluebaby_b";
	case 26:
		return "playerportrait_eve_b";
	case 27:
		return "playerportarit_samson_b";
	case 28:
		return "playerportrait_azazel_b";
	case 29:
		return "playerportrait_lazarus_b";
	case 30:
		return "playerportrait_eden_b";
	case 31:
		return "playerportrait_thelost_b";
	case 32:
		return "playerportrait_lilith_b";
	case 33:
		return "playerportrait_keeper_b";
	case 34:
		return "playerportrait_apollyon_b";
	case 35:
		return "playerportrait_theforgotten_b";
	case 36:
		return "playerportrait_bethany_b";
	case 37:
		return "playerportrait_jacob_b";
	case 38:
		return "playerportrait_lazarus_b_dead";
	case 39:
		return "playerportrait_jacob_b_darkesau";
	case 40:
		return "playerportrait_theforgotten_b";
	default:
		return "unknown";
	}
}

char* stbToString(int stb) {
	switch (stb) {
	case 1:
		return "Running from Mom in the Basement";
	case 2:
		return "Hiding from spiders in Cellar";
	case 3:
		return "Catching aflame in Burning Basement";
	case 4:
		return "Excavating the Caves";
	case 5:
		return "Exploring the Catacombs";
	case 6:
		return "Drowning in the Flooded Caves";
	case 7:
		return "Fighting off monsters in the Depths";
	case 8:
		return "Paying respects in the Necropolis";
	case 9:
		return "Struggling to see in the darkness of the Dank Depths";
	case 10:
		return "Visiting their future's past in Womb";
	case 11:
		return "Bursting veins in Utero";
	case 12:
		return "Slaying their future's past in Scarred Womb";
	case 13:
		return "Dodging bullet hells against Hush";
	case 14:
		return "Dueling Satan in Sheol";
	case 15:
		return "Repenting in the Cathedral";
	case 16:
		return "Facing their fears in the Dark Room";
	case 17:
		return "Suffocating in the Chest";
	case 26:
		return "Suffering in the Void";
	case 27:
		return "Wishing they had an umbrella in Downpour";
	case 28:
		return "Sifting through sewage in Dross";
	case 29:
		return "Finding diamonds in Mines";
	case 30:
		return "Struggling to breathe in Ashpit";
	case 31:
		return "Fending off the dead in the Mausoleum";
	case 32:
		return "Avoiding pain in Gehenna";
	case 33:
		return "Decomposing in Corpse";
	case 34:
		return "mortis lol";
	case 35:
		return "Living in the light at Home";
	case 36:
		return "Returning home through the Ascent";
	default:
		return "Exploring the unknown depths below";
	}
}

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

HOOK_METHOD(MenuManager, Render, () -> void) {
	super();

	if (discordAPI.didntStart) {
		return;
	}

	if (!discordAPI.isRunning) {
		return;
	}

	if (lastGameState != LastGameState::LAST_GAME_STATE_MENU) {
		lastGameState = LastGameState::LAST_GAME_STATE_MENU;
		RNG rng = RNG();
		rng.SetSeed(max(Random(), 1), 35);
		currentMenuIcon = rng.RandomInt(7) + 1;
		discordAPI.SetTimestamp(time(0));
		deathScreenShowing = false;
	}

	int menu = g_MenuManager->_selectedMenuID;

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

HOOK_METHOD(Game, Render, () -> void) {
	super();

	if (discordAPI.didntStart) {
		return;
	}

	if (!discordAPI.isRunning) {
		return;
	}

	// Reset if restarted run or new game
	if (lastGameState != LastGameState::LAST_GAME_STATE_GAME || g_Game->_frameCount < 1) {
		lastGameState = LastGameState::LAST_GAME_STATE_GAME;
		discordAPI.SetTimestamp(time(0));
		deathScreenShowing = false;
	}

	Entity_Player* player = g_Game->GetPlayer(0);
	if (player != nullptr && !deathScreenShowing) {
		int playerType = player->GetPlayerType();
		int stbStage = RoomConfig::GetStageID(g_Game->_stage, g_Game->_stageType, -1);

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

			discordAPI.SetState(playerToPortrait(playerType), buf.c_str(), stbToString(stbStage));
		}
		else {
			discordAPI.SetState(playerToPortrait(playerType), "Playing as a modded character", stbToString(stbStage));
		}
	}
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

	deathScreenShowing = true;

	discordAPI.SetState("death", "Game over!", "Contemplating their death");
}

HOOK_STATIC(Manager, Update, () -> void, __stdcall) {
	super();

	// Didn't start because Discord wasn't open.
	if (discordAPI.didntStart) {
		return;
	}

	discordAPI.Update();
}