#include <ctime>

#include "IsaacRepentance.h"
#include "discord-shit/discord.h"
#include "Log.h"

#include "DiscordAPI.h"

DiscordAPI discordAPI;

DiscordAPI::DiscordAPI() : isRunning(true) {
	printf("[DISCORD] Creating discord core.\n");

	discord::Result result = discord::Core::Create(clientID, DiscordCreateFlags_NoRequireDiscord, &core);

	if (result != discord::Result::Ok) {
		printf("[DISCORD] Failed to launch Discord Rich Presence client, aborting!\n");
		didntStart = true;
	}
	else {
		auto log_hook = [](discord::LogLevel level, const char* message) {
			printf("[DISCORD] %s\n", message);
		};

		core->SetLogHook(discord::LogLevel::Debug, log_hook);

		SetDefaultActivity();
		didntStart = false;
	}
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
	activity.SetName("The Binding of Isaac: Repentance");
	activity.SetInstance(false);
	activity.SetType(discord::ActivityType::Playing);

	SetState("intro_cutscene", "Isaac and his mother...", "Watching the intro cutscene");
}