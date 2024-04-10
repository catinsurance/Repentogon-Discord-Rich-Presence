cmake_minimum_required(VERSION 3.13.0)

set ("CMAKE_CXX_STANDARD" 17)
set (CMAKE_BUILD_TYPE "Debug")

project (IsaacDiscord)

include_directories(${CMAKE_SOURCE_DIR}/include "${CMAKE_SOURCE_DIR}/libs/lua" 
    "${CMAKE_SOURCE_DIR}/libzhl"
    "${CMAKE_SOURCE_DIR}/libs/rapidxml" "${CMAKE_SOURCE_DIR}/libs/rapidjson/include/rapidjson" 
    "${CMAKE_SOURCE_DIR}/libs/mINI/src/mini" "${CMAKE_SOURCE_DIR}/local_libs/discord_game_sdk")

# Zydis
option(ZYDIS_BUILD_TOOLS "" OFF)
option(ZYDIS_BUILD_EXAMPLES "" OFF)
option(ZYDIS_BUILD_DOXYGEN "" OFF)
add_subdirectory("libs/zydis")
target_compile_options("Zydis" PUBLIC "/MD")

# libcurl
# option(BUILD_TESTING "" OFF)
# option(BUILD_CURL_EXE "" OFF)
# option(BUILD_SHARED_LIBS "" OFF)
# option(BUILD_STATIC_LIBS "" ON)
# option(ENABLE_THREADED_RESOLVER "" OFF)
# option(CURL_USE_SCHANNEL "" ON)
# # Disable everything except HTTPS, we don't need to compile most of this.
# option(CURL_DISABLE_DICT "" ON)
# option(CURL_DISABLE_FILE "" ON)
# option(CURL_DISABLE_FTP "" ON)
# option(CURL_DISABLE_GOPHER "" ON)
# option(CURL_DISABLE_IMAP "" ON)
# option(CURL_DISABLE_LDAP "" ON)
# option(CURL_DISABLE_LDAPS "" ON)
# option(CURL_DISABLE_MQTT "" ON)
# option(CURL_DISABLE_POP3 "" ON)
# option(CURL_DISABLE_RTSP "" ON)
# option(CURL_DISABLE_SMB "" ON)
# option(CURL_DISABLE_SMTP "" ON)
# option(CURL_DISABLE_TELNET "" ON)
# option(CURL_DISABLE_TFTP "" ON)
# add_subdirectory("libs/curl")

# Lua
FILE(GLOB LUA_SRC ${CMAKE_SOURCE_DIR}/libs/lua/*.c)
list(REMOVE_ITEM LUA_SRC "${CMAKE_SOURCE_DIR}/libs/lua/onelua.c")
add_compile_definitions(LUA_BUILD_AS_DLL)
add_library(Lua5.4 SHARED ${LUA_SRC})

if(NOT ${CURL_INCLUDE_DIR})
    set(CURL_INCLUDE_DIR "libs/curl/include")
endif()

# IsaacGPT
file(GLOB_RECURSE ISAACDISCORD_SRC ${CMAKE_SOURCE_DIR}/src/*.*)
foreach(_source IN ITEMS ${ISAACDISCORD_SRC})
    get_filename_component(_source_path "${_source}" PATH)
    string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_group_path}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

add_library(zhlIsaacDiscord SHARED ${ISAACDISCORD_SRC})
target_include_directories(zhlIsaacDiscord PUBLIC ${CURL_INCLUDE_DIR})
target_link_libraries(zhlIsaacDiscord Lua5.4 "Zydis" "${CMAKE_SOURCE_DIR}/libzhl/libzhl.lib" "${CMAKE_SOURCE_DIR}/bin/discord_game_sdk.dll.lib")
target_compile_options(zhlIsaacDiscord PUBLIC "/MD")

add_custom_command(TARGET zhlIsaacDiscord COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/bin/discord_game_sdk.dll" "$<TARGET_FILE_DIR:zhlIsaacDiscord>")

# Piracy
# file(GLOB_RECURSE PIRACY_SRC ${CMAKE_SOURCE_DIR}/piracy/*.*)
# foreach(_source IN ITEMS ${PIRACY_SRC})
#     get_filename_component(_source_path "${_source}" PATH)
#     string(REPLACE "${CMAKE_SOURCE_DIR}" "" _group_path "${_source_path}")
#     string(REPLACE "/" "\\" _group_path "${_group_path}")
#     source_group("${_group_path}" FILES "${_source}")
# endforeach()

# add_library(zhlRenzotPiracy SHARED ${PIRACY_SRC})
# target_link_libraries(zhlRenzotPiracy libzhl)
# target_compile_options(zhlRenzotPiracy PUBLIC "/MD")