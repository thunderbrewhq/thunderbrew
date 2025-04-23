#include "ui/CSimpleMovieFrameScript.hpp"
#include "ui/CSimpleMovieFrame.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"
#include "util/StringTo.hpp"
#include <cstdint>


int32_t CSimpleMovieFrame_StartMovie(lua_State* L) {
    auto type = CSimpleMovieFrame::GetObjectType();
    auto movieFrame = static_cast<CSimpleMovieFrame*>(FrameScript_GetObjectThis(L, type));

    if (!lua_isstring(L, 2) || !lua_isnumber(L, 3)) {
        return luaL_error(L, "Usage: %s:StartMovie(\"filename\", volume_0_to_255)", movieFrame->GetDisplayName());
    }

    int32_t volume = static_cast<int32_t>(lua_tointeger(L, 3));
    const char* filename = lua_tolstring(L, 2, nullptr);

    if (movieFrame->StartMovie(filename, volume)) {
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }

    return 1;
}

int32_t CSimpleMovieFrame_StopMovie(lua_State* L) {
    auto type = CSimpleMovieFrame::GetObjectType();
    auto movieFrame = static_cast<CSimpleMovieFrame*>(FrameScript_GetObjectThis(L, type));
    movieFrame->StopMovie();
    return 0;
}

int32_t CSimpleMovieFrame_EnableSubtitles(lua_State* L) {
    auto type = CSimpleMovieFrame::GetObjectType();
    auto movieFrame = static_cast<CSimpleMovieFrame*>(FrameScript_GetObjectThis(L, type));
    bool enabled = StringToBOOL(L, 2, 1);
    // *(movieFrame + 680) = enabled;
    return 0;
}

FrameScript_Method SimpleMovieFrameMethods[NUM_SIMPLE_MOVIE_FRAME_SCRIPT_METHODS] = {
    { "StartMovie",      &CSimpleMovieFrame_StartMovie },
    { "StopMovie",       &CSimpleMovieFrame_StopMovie },
    { "EnableSubtitles", &CSimpleMovieFrame_EnableSubtitles }
};
