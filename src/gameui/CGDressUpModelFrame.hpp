#ifndef GAME_UI_CGDRESS_UP_MODEL_FRAME_HPP
#define GAME_UI_CGDRESS_UP_MODEL_FRAME_HPP

#include "ui/CSimpleFrame.hpp"
#include "ui/CSimpleTop.hpp"

class CGDressUpModelFrame : public CSimpleFrame {
    public:
    // Static variables
    static int32_t s_metatable;

    // Static functions
    static CSimpleFrame* Create(CSimpleFrame* parent);
    static void CreateScriptMetaTable();
    static void RegisterScriptMethods(lua_State* L);

    // Virtual member functions
    virtual int32_t GetScriptMetaTable();

    // Member functions
    CGDressUpModelFrame(CSimpleFrame* parent);
};

#endif // GAME_UI_CGDRESS_UP_MODEL_FRAME_HPP
