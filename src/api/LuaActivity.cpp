#include <lua.hpp>
#include "LuaCore.h"
#include "IsaacRepentance.h"
#include "HookSystem.h"
#include "../DiscordAPI.h"

LUA_FUNCTION(Lua_Activity_SetLargeImage) {
	const char* imagePath = luaL_checkstring(L, 1);
	const char* caption = luaL_optstring(L, 2, "__NONE__");

	discordAPI.SetLargeImage(imagePath);

	if (caption != "__NONE__") {
		discordAPI.SetLargeCaption(caption);
	}

	return 0;
}

LUA_FUNCTION(Lua_Activity_SetLargeCaption) {
	const char* caption = luaL_checkstring(L, 1);

	discordAPI.SetLargeCaption(caption);

	return 0;
}

LUA_FUNCTION(Lua_Activity_GetLargeImage) {
	lua_pushstring(L, discordAPI.GetLargeImage());
	return 1;
}

LUA_FUNCTION(Lua_Activity_GetLargeCaption) {
	lua_pushstring(L, discordAPI.GetLargeCaption());
	return 1;
}

LUA_FUNCTION(Lua_Activity_SetSmallImage) {
	const char* imagePath = luaL_checkstring(L, 1);
	const char* caption = luaL_optstring(L, 2, "__NONE__");

	discordAPI.SetSmallImage(imagePath);

	if (caption != "__NONE__") {
		discordAPI.SetSmallCaption(caption);
	}

	return 0;
}

LUA_FUNCTION(Lua_Activity_SetSmallCaption) {
	const char* caption = luaL_checkstring(L, 1);

	discordAPI.SetSmallCaption(caption);

	return 0;
}

LUA_FUNCTION(Lua_Activity_GetSmallImage) {
	lua_pushstring(L, discordAPI.GetSmallImage());
	return 1;
}

LUA_FUNCTION(Lua_Activity_GetSmallCaption) {
	lua_pushstring(L, discordAPI.GetSmallCaption());
	return 1;
}

LUA_FUNCTION(Lua_Activity_SetTitle) {
	const char* caption = luaL_checkstring(L, 1);

	discordAPI.SetTitle(caption);

	return 0;
}

LUA_FUNCTION(Lua_Activity_GetTitle) {
	lua_pushstring(L, discordAPI.GetTitle());
	return 1;
}

LUA_FUNCTION(Lua_Activity_SetSubtitle) {
	const char* caption = luaL_checkstring(L, 1);
	
	discordAPI.SetSubtitle(caption);
	
	return 0;
}

LUA_FUNCTION(Lua_Activity_GetSubtitle) {
	lua_pushstring(L, discordAPI.GetSubtitle());
	return 1;
}

LUA_FUNCTION(Lua_Activity_Update) {
	discordAPI.UpdateActivity();

	return 0;
}

LUA_FUNCTION(Lua_Activity_SetStartTimestamp) {
	LuaTimestamp* timestamp = lua::GetUserdata<LuaTimestamp*>(L, 1, TimestampMT);
	
	discordAPI.SetStartTimestamp(timestamp->Get());
	
	return 0;
}

LUA_FUNCTION(Lua_Activity_GetStartTimestamp) {
	discord::Timestamp currentTime = discordAPI.GetStartTimestamp();

	if (currentTime == 0) {
		lua_pushnil(L);
	}
	else {
		LuaTimestamp timestamp = LuaTimestamp(0);
		timestamp.timestamp = currentTime;

		LuaTimestamp* toLua = (LuaTimestamp*)lua_newuserdata(L, sizeof(LuaTimestamp));
		*toLua = timestamp;
		luaL_setmetatable(L, TimestampMT);
	}

	return 1;
}

LUA_FUNCTION(Lua_Activity_SetEndTimestamp) {
	LuaTimestamp* timestamp = lua::GetUserdata<LuaTimestamp*>(L, 1, TimestampMT);

	discordAPI.SetEndTimestamp(timestamp->Get());

	return 0;
}

LUA_FUNCTION(Lua_Activity_GetEndTimestamp) {
	discord::Timestamp currentTime = discordAPI.GetEndTimestamp();

	if (currentTime == 0) {
		lua_pushnil(L);
	}
	else {
		LuaTimestamp timestamp = LuaTimestamp(0);
		timestamp.timestamp = currentTime;

		LuaTimestamp* toLua = (LuaTimestamp*)lua_newuserdata(L, sizeof(LuaTimestamp));
		*toLua = timestamp;
		luaL_setmetatable(L, TimestampMT);
	}

	return 1;
}

LUA_FUNCTION(Lua_Activity_SetDefaultEnabled) {
	const bool toggleOn = lua_toboolean(L, 1);
	if (toggleOn) {
		discordAPI.luaToggle = false;
	}
	else {
		discordAPI.luaToggle = true;
	}

	return 0;
}

LUA_FUNCTION(Lua_Activity_ClearTimestamp) {
	discordAPI.ClearTimestamp();
	return 0;
}

static void RegisterActivity(lua_State* L) {
	lua_newtable(L);

		lua::TableAssoc(L, "SetLargeImage", Lua_Activity_SetLargeImage);
		lua::TableAssoc(L, "GetLargeImage", Lua_Activity_GetLargeImage);
		
		lua::TableAssoc(L, "SetLargeCaption", Lua_Activity_SetLargeCaption);
		lua::TableAssoc(L, "GetLargeCaption", Lua_Activity_GetLargeCaption);
		
		lua::TableAssoc(L, "SetSmallImage", Lua_Activity_SetSmallImage);
		lua::TableAssoc(L, "GetSmallImage", Lua_Activity_GetSmallImage);

		lua::TableAssoc(L, "SetSmallCaption", Lua_Activity_SetSmallCaption);
		lua::TableAssoc(L, "GetSmallCaption", Lua_Activity_GetSmallCaption);

		lua::TableAssoc(L, "GetTitle", Lua_Activity_GetTitle);
		lua::TableAssoc(L, "SetTitle", Lua_Activity_SetTitle);

		lua::TableAssoc(L, "GetSubtitle", Lua_Activity_GetSubtitle);
		lua::TableAssoc(L, "SetSubtitle", Lua_Activity_SetSubtitle);

		lua::TableAssoc(L, "GetStartTimestamp", Lua_Activity_GetStartTimestamp);
		lua::TableAssoc(L, "SetStartTimestamp", Lua_Activity_SetStartTimestamp);

		lua::TableAssoc(L, "GetEndTimestamp", Lua_Activity_GetEndTimestamp);
		lua::TableAssoc(L, "SetEndTimestamp", Lua_Activity_SetEndTimestamp);

		lua::TableAssoc(L, "ClearTimestamp", Lua_Activity_ClearTimestamp);
		
		lua::TableAssoc(L, "SetDefaultActivity", Lua_Activity_SetDefaultEnabled);
		lua::TableAssoc(L, "Update", Lua_Activity_Update);

	lua_setglobal(L, "Activity");
}

HOOK_METHOD(LuaEngine, RegisterClasses, () -> void) {
	super();

	lua_State* L = _state;
	lua::LuaStackProtector protector(L);

	RegisterActivity(_state);
}