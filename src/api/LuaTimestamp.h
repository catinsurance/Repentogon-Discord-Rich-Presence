#pragma once

#include "../discord-shit/discord.h"

static const char* TimestampMT = "Timestamp";

struct LuaTimestamp {
	LuaTimestamp(long offset);
	void Offset(long amount);
	discord::Timestamp Get();

	discord::Timestamp timestamp = discord::Timestamp();
	
};