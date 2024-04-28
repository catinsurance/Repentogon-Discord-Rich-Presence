#include <map>
#include <string>

// Takes the stage STB id and returns a title for it.
char* stageToTitle(int stb);

// Take a modded stage name and returns a title for it.
char* moddedStageToTitle(const char* stageName);

// Returns a modded player name and returns a portrait for it.
char* moddedPlayerToPortrait(const char* name, bool isTainted);

// Returns a player id and returns a portrait for it.
char* playerToPortrait(int playerType);

extern std::map<int, std::string> luaPlayerPortrait;
extern std::map<int, std::string> luaStageTitle;
