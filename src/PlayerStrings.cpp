#include "GameInfoStrings.h"
#include <string>

std::map<int, std::string> luaPlayerPortrait = {};

char* moddedPlayerToPortrait(const char* name, bool isTainted) {
	std::string strName = std::string(name); // I couldn't compare it before. am I stupid?

	// Samael
	if (strName == "Samael") {
		if (isTainted) {
			return "playerportrait_samael_b";
		}
		else {
			return "playerportrait_samael";
		}
	}
	// Sheriff
	else if (strName == "The Sheriff") {
		return "playerportrait_sheriff";
	}
	// Fiend Folio
	else if (strName == "Fiend") {
		if (isTainted) {
			return "playerportrait_fiend_b";
		}
		else {
			return "playerportrait_fiend";
		}
	}
	else if (strName == "Golem") {
		return "playerportrait_golem";
	}
	// Revelations
	else if (strName == "Sarah") {
		return "playerportrait_sarah";
	}
	else if (strName == "Dante" || strName == "Charon") {
		return "playerportrait_dante";
	}
	// Andromeda
	else if (strName == "Andromeda") {
		return "playerportrait_andromeda";
	}
	else if (strName == "AndromedaB") { // Tainted Andromeda has a separate name for some reason
		return "playerportrait_andromeda_b";
	}
	// Car (lol!)
	else if (strName == "Car") {
		return "playerportrait_car";
	}
	// Bertran
	else if (strName == "Bertran") {
		return "playerportrait_bertran";
	}
	// Sacred Dreams
	else if (strName == "The Dream Guard") {
		return "playerportrait_thedreamguard";
	}
	// Bael
	else if (strName == "Bael") {
		return "playerportrait_bael";
	}
	// Eevee Reunited (Demo) (hi sanio!!)
	else if (strName == "Eevee") {
		return "playerportrait_eevee";
	}
	// Retribution
	else if (strName == "Icarus") {
		return "playerportrait_icarus";
	}
	else if (strName == "Mammon") {
		if (isTainted) {
			return "playerportrait_mammon_b";
		}
		else {
			return "playerportrait_mammon";
		}
	}
	// Arachna
	else if (strName == "Arachna") {
		if (isTainted) {
			return "playerportrait_arachna_b";
		}
		else {
			return "playerportrait_arachna";
		}
	}
	// Sodom and Gomorrah
	else if (strName == "Sodom" || strName == "Gomorrah") {
		if (isTainted) {
			return "playerportrait_sodomgomorrah_b";
		}
		else {
			return "playerportrait_sodomgomorrah";
		}
	}
	// The Deleted
	else if (strName == "Deleted") {
		if (isTainted) {
			return "playerportrait_deleted_b";
		}
		else {
			return "playerportrait_deleted";
		}
	}
	// Felix and Harold
	else if (strName == "Felix") {
		return "playerportrait_felix";
	}
	// Jericho
	else if (strName == "Jericho") {
		return "playerportrait_jericho";
	}
	// Epiphany
	// These characters have zero width spaces in front of their names
	// I wasn't able to compare their character name with my own string (even with \u200b in front)
	// So I'm using .find(). Hopefully this isn't like the slowest possible solution.
	else if (strName.find("Isaac") != std::string::npos) {
		return "playerportrait_epiphany_isaac";
	}
	else if (strName.find("Magdalene") != std::string::npos) {
		return "playerportrait_epiphany_magdalene";
	}
	else if (strName.find("Cain") != std::string::npos) {
		return "playerportrait_epiphany_cain";
	}
	else if (strName.find("Judas") != std::string::npos) {
		return "playerportrait_epiphany_judas";
	}
	else if (strName.find("Samson") != std::string::npos) {
		return "playerportrait_epiphany_samson";
	}
	else if (strName.find("Eden") != std::string::npos) {
		return "playerportrait_epiphany_eden";
	}
	else if (strName.find("Lost") != std::string::npos) {
		return "playerportrait_epiphany_lost";
	}
	else if (strName.find("Keeper") != std::string::npos) {
		return "playerportrait_epiphany_keeper";
	}

	return "unknown";
}

char* playerToPortrait(int playerType) {

	if (luaPlayerPortrait.count(playerType)) {
		std::string portrait = luaPlayerPortrait[playerType];
		return portrait.data();
	}

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
		return "playerportrait_samson";
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