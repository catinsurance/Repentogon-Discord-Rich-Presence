#include <ctime>

#include "IsaacRepentance.h"
#include "discord-shit/discord.h"
#include "Log.h"

#include "DiscordAPI.h"

DiscordAPI discordAPI;

DiscordAPI::DiscordAPI() : isRunning(true) {
	discord::Core::Create(clientID, DiscordCreateFlags_Default, &core);

	auto log_hook = [](discord::LogLevel level, const char* message) {
		printf("[DISCORD] %s\n", message);
	};

	core->SetLogHook(discord::LogLevel::Debug, log_hook);

	SetDefaultActivity();
}

void DiscordAPI::Update() {
	if (core->RunCallbacks() != discord::Result::Ok) {
		isRunning = false;
	}
}

void DiscordAPI::SetTimestamp(discord::Timestamp timestamp) {
	activity.GetTimestamps().SetStart(timestamp);
}

void DiscordAPI::SetState(const char* largeIcon, const char* largeIconText, const char* state) {
	activity.GetAssets().SetLargeImage(largeIcon);
	activity.GetAssets().SetLargeText(largeIconText);

	activity.SetState(state);

	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
}

void DiscordAPI::SetDefaultActivity() {
	activity.SetName("Binding of Isaac: Repentance");
	activity.SetInstance(false);
	activity.SetType(discord::ActivityType::Playing);

	SetState("loading", "Loading...", "Loading...");
}