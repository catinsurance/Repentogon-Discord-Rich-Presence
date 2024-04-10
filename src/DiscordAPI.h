#pragma once

#include <cstdint>

#include "discord-shit/discord.h"

class DiscordAPI {
public:
	static constexpr std::int64_t clientID = 1209274789714468906;
	static constexpr const char* appName = "Binding of Isaac: Repentance";

	discord::Core* core;
	discord::Activity activity;

	bool isRunning;
public:
	DiscordAPI();

	void Update();
	void SetState(const char* largeIcon, const char* largeIconText, const char* state);
	void SetTimestamp(discord::Timestamp);
private:
	void SetDefaultActivity();
};

extern DiscordAPI discordAPI;