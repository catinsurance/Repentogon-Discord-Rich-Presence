#include <stdio.h>
#include "DiscordAPI.h"

extern "C" __declspec(dllexport) int ModInit(int argc, char** argv) {
	printf("[DISCORD] Mod initialized\n");

	return 0;
}