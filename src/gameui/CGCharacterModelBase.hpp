#ifndef GAME_UI_CGCHARACTER_MODEL_BASE_HPP
#define GAME_UI_CGCHARACTER_MODEL_BASE_HPP

#include "ui/CSimpleModel.hpp"
#include "ui/CSimpleTop.hpp"

class CGCharacterModelBase : public CSimpleModel {
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
    CGCharacterModelBase(CSimpleFrame* parent);
};

#endif // GAME_UI_CGCHARACTER_MODEL_BASE_HPP
