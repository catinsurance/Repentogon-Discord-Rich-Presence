#pragma once

#include "IsaacRepentance.h"
#include "LuaTimestamp.h"

const char* ActivityMT = "Activity";

struct LuaActivity {
	void SetLargeImage(const char* image, const char* caption);

	void SetLargeCaption(const char* caption);

	void SetSmallImage(const char* image, const char* caption);

	void SetSmallCaption(const char* caption);

	void SetTitle(const char* title);

	void SetSubtitle(const char* subtitle);

	void SetStartTimestamp(LuaTimestamp timestamp);

	void SetEndTimestamp(LuaTimestamp timestamp);

	void ClearTimestamp();

	void Send();

	char* largeImage;
	char* smallImage;

	char* largeCaption;
	char* smallCaption;

	char* title;
	char* subtitle;

	LuaTimestamp start;
	LuaTimestamp end;

};