#pragma once

#include "../discord-shit/discord.h"

struct LuaTimestamp {
	LuaTimestamp(long offset);
	void Offset(long amount);
	discord::Timestamp Get();

	discord::Timestamp timestamp = discord::Timestamp();
};