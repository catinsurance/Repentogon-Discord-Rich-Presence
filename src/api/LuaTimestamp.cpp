#include "LuaTimestamp.h"
#include "LuaCore.h"
#include "HookSystem.h"
#include "IsaacRepentance.h"

#include <ctime>

const char* TimestampMT = "Timestamp";

LuaTimestamp::LuaTimestamp(long offset) {
	timestamp = discord::Timestamp(time(0)) + discord::Timestamp(offset);
}

void LuaTimestamp::Offset(long amount) {
	timestamp += discord::Timestamp(amount);
}

discord::Timestamp LuaTimestamp::Get() {
	return timestamp;
}
 
LUA_FUNCTION(Lua_DiscordTimestamp_Constructor) {
	int offset = (int) luaL_optinteger(L, 1, 0);

	LuaTimestamp timestamp = LuaTimestamp(offset);
	LuaTimestamp* toLua = (LuaTimestamp*)lua_newuserdata(L, sizeof(LuaTimestamp));
	*toLua = timestamp;
	luaL_setmetatable(L, TimestampMT);

	return 1;
}

LUA_FUNCTION(Lua_DiscordTimestamp_Offset) {
	LuaTimestamp* timestamp = lua::GetUserdata<LuaTimestamp*>(L, 1, TimestampMT);
	long amount = (long) luaL_checkinteger(L, 2);
	
	timestamp->Offset(amount);

	return 0;
}

static void RegisterTimestamp(lua_State* L) {
	luaL_Reg functions[] = {
		{ "Offset", Lua_DiscordTimestamp_Offset },
		{ NULL , NULL }
	};
	lua::RegisterNewClass(L, TimestampMT, TimestampMT, functions);
	lua_register(L, TimestampMT, Lua_DiscordTimestamp_Constructor);
}

HOOK_METHOD(LuaEngine, RegisterClasses, () -> void) {
	super();

	lua_State* L = _state;
	lua::LuaStackProtector protector(L);

	RegisterTimestamp(_state);
}