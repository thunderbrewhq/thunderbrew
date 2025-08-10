#ifndef UI_C_SIMPLE_STATUS_BAR_HPP
#define UI_C_SIMPLE_STATUS_BAR_HPP

#include "ui/CSimpleFrame.hpp"

class CSimpleStatusBar : public CSimpleFrame {
    public:
    // Static variables
    static int32_t s_metatable;
    static int32_t s_objectType;

    // Static functions
    static void CreateScriptMetaTable();
    static int32_t GetObjectType();
    static void RegisterScriptMethods(lua_State* L);

    // Member functions
    CSimpleStatusBar(CSimpleFrame* parent);

    // Virtual member functions
    virtual bool IsA(int32_t type);
    virtual int32_t GetScriptMetaTable();
};

#endif
