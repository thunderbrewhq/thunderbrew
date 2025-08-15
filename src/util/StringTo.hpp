#ifndef UTIL_STRING_TO_HPP
#define UTIL_STRING_TO_HPP

#include <cstdint>

struct lua_State;

uint64_t StringToClickAction(const char* actionStr);

int32_t StringToBOOL(const char*);

bool StringToBOOL(const char*, int32_t);

bool StringToBOOL(lua_State*, int32_t, int32_t);

int32_t StringToDrawLayer(const char*, int32_t&);

int32_t StringToJustify(const char*, uint32_t&);

bool StringToOrientation(const char* string, uint32_t& orientation);

bool StringToAnchorPoint(const char* string, int32_t& point);

uint32_t StringToFontFlags(const char* string);

#endif
