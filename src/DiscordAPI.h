#pragma once

#include <cstdint>

#include "discord-shit/discord.h"
#include "api/LuaTimestamp.h"

class DiscordAPI {
public:
	static constexpr std::int64_t clientID = 1209274789714468906;
	static constexpr const char* appName = "Binding of Isaac: Repentance";
	static const int updateInterval = 10;

	discord::Core* core;
	discord::Activity activity;

	bool isRunning;
	bool didntStart;
	bool luaToggle = false; // Did Lua disable the plugin?
	int lastUpdate = 0;
public:
	DiscordAPI();

	void Update();
	void UpdateActivity();
	
	void SetLargeImage(const char* largeIcon);
	void SetLargeCaption(const char* caption);
	
	const char* GetLargeImage();
	const char* GetLargeCaption();

	void SetSmallImage(const char* smallIcon);
	void SetSmallCaption(const char* caption);

	const char* GetSmallImage();
	const char* GetSmallCaption();

	void SetTitle(const char* title);
	void SetSubtitle(const char* subtitle);

	const char* GetTitle();
	const char* GetSubtitle();

	void SetState(const char* largeIcon, const char* largeIconText, const char* state);
	
	discord::Timestamp GetStartTimestamp();
	discord::Timestamp GetEndTimestamp();

	void SetStartTimestamp(discord::Timestamp);
	void SetEndTimestamp(discord::Timestamp);

	void ClearTimestamp();
private:
	void SetDefaultActivity();
};

extern DiscordAPI discordAPI;