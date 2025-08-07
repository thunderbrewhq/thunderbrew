#ifndef UI_C_SIMPLE_MESSAGE_SCROLL_FRAME_HPP
#define UI_C_SIMPLE_MESSAGE_SCROLL_FRAME_HPP

#include "ui/CSimpleHyperlinkedFrame.hpp"

class CSimpleMessageScrollFrame : public CSimpleHyperlinkedFrame {
    public:
    // Static variables
    static int32_t s_metatable;
    static int32_t s_objectType;

    // Static functions
    static void CreateScriptMetaTable();
    static int32_t GetObjectType();
    static void RegisterScriptMethods(lua_State* L);

    // Member functions
    CSimpleMessageScrollFrame(CSimpleFrame* parent);

    // Virtual member functions
    virtual bool IsA(int32_t type);
    virtual int32_t GetScriptMetaTable();
};

#endif
