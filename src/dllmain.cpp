#include <stdio.h>
#include "DiscordAPI.h"
#include "ConfigHandler.h"



extern "C" __declspec(dllexport) int ModInit(int argc, char** argv) {
	printf("[DISCORD] Initializing config\n");

	modOptions.Init();

	printf("[DISCORD] Config initialized\n");

	printf("[DISCORD] Mod initialized\n");

	return 0;
}