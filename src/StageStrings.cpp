#include "GameInfoStrings.h"
#include "ConfigHandler.h"

char* stageToTitle(int stb) {
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

char* moddedStageToTitle(const char* stageName) {
	if (!modOptions.Get("Customization", "ShowModdedStages")) {
		return "Exploring the unknown depths below";
	}

	std::string strStageName = std::string(stageName);
	if (strStageName == "Boiler" || strStageName == "Boiler 2" || strStageName == "Boiler XL") {
		return "Boiling in the Boiler";
	}

	if (strStageName == "Glacier" || strStageName == "Glacier 2" || strStageName == "Glacier XL") {
		return "Slipping through Glacier";
	}

	if (strStageName == "Tomb" || strStageName == "Tomb 2" || strStageName == "Tomb XL") {
		return "Raiding the Tomb";
	}

	if (strStageName == "The Future" || strStageName == "The Future 2" || strStageName == "The Future XL") {
		return "Seeing into The Future";
	}

	// Default
	return "Exploring the unknown depths below";
}