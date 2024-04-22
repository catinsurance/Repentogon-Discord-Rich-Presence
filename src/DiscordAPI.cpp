#include <ctime>

#include "IsaacRepentance.h"
#include "discord-shit/discord.h"
#include "Log.h"
#include "ConfigHandler.h"

#include "DiscordAPI.h"

DiscordAPI discordAPI;

DiscordAPI::DiscordAPI() : isRunning(true) {
	printf("[DISCORD] Creating discord core\n");

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

void DiscordAPI::UpdateActivity() {
	core->ActivityManager().UpdateActivity(activity, [](discord::Result result) {});
}

void DiscordAPI::SetLargeImage(const char* image) {
	activity.GetAssets().SetLargeImage(image);
}

void DiscordAPI::SetLargeCaption(const char* caption) {
	activity.GetAssets().SetLargeText(caption);
}

const char* DiscordAPI::GetLargeImage() {
	return activity.GetAssets().GetLargeImage();
}

const char* DiscordAPI::GetLargeCaption() {
	return activity.GetAssets().GetLargeText();
}

void DiscordAPI::SetSmallImage(const char* smallIcon) {
	activity.GetAssets().SetSmallImage(smallIcon);
}

void DiscordAPI::SetSmallCaption(const char* caption) {
	activity.GetAssets().SetSmallText(caption);
}

const char* DiscordAPI::GetSmallImage() {
	return activity.GetAssets().GetSmallImage();
}

const char* DiscordAPI::GetSmallCaption() {
	return activity.GetAssets().GetSmallText();
}

void DiscordAPI::SetTitle(const char* title) {
	activity.SetDetails(title);
}

void DiscordAPI::SetSubtitle(const char* subtitle) {
	activity.SetState(subtitle);
}

const char* DiscordAPI::GetTitle() {
	return activity.GetDetails();
}

const char* DiscordAPI::GetSubtitle() {
	return activity.GetState();
}

void DiscordAPI::SetState(const char* largeIcon, const char* largeIconText, const char* state) {
	activity.GetAssets().SetLargeImage(largeIcon);
	activity.GetAssets().SetLargeText(largeIconText);

	activity.SetState(state);
}

discord::Timestamp DiscordAPI::GetStartTimestamp() {
	return activity.GetTimestamps().GetStart();
}

discord::Timestamp DiscordAPI::GetEndTimestamp() {
	return activity.GetTimestamps().GetEnd();
}

void DiscordAPI::SetStartTimestamp(discord::Timestamp timestamp) {
	activity.GetTimestamps().SetEnd(discord::Timestamp());

	if (modOptions.Get("Customization", "ShowTimer")) {
		activity.GetTimestamps().SetStart(timestamp);
	}
	else {
		activity.GetTimestamps().SetStart(discord::Timestamp());
	}
}

void DiscordAPI::SetEndTimestamp(discord::Timestamp timestamp) {
	activity.GetTimestamps().SetStart(discord::Timestamp());

	if (modOptions.Get("Customization", "ShowTimer")) {
		activity.GetTimestamps().SetEnd(timestamp);
	}
	else {
		activity.GetTimestamps().SetEnd(discord::Timestamp());
	}
}

void DiscordAPI::ClearTimestamp() {
	activity.GetTimestamps().SetStart(discord::Timestamp());
	activity.GetTimestamps().SetEnd(discord::Timestamp());
}

void DiscordAPI::SetDefaultActivity() {
	activity.SetName("The Binding of Isaac: Repentance");
	activity.SetInstance(false);
	activity.SetType(discord::ActivityType::Playing);

	SetState("intro_cutscene", "Isaac and his mother...", "Watching the intro cutscene");
	UpdateActivity();
}