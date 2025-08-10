#ifndef GAME_UI_CGTOOLTIP_HPP
#define GAME_UI_CGTOOLTIP_HPP

#include "ui/CSimpleFrame.hpp"
#include "ui/CSimpleTop.hpp"

class CGTooltip : public CSimpleFrame {
    public:
    // Static variables
    static int32_t s_metatable;
    static int32_t s_objectType;

    // Static functions
    static CSimpleFrame* Create(CSimpleFrame* parent);
    static void CreateScriptMetaTable();
    static int32_t GetObjectType();
    static void RegisterScriptMethods(lua_State* L);

    // Member functions
    CGTooltip(CSimpleFrame* parent);

    // Virtual member functions
    virtual bool IsA(int32_t type);
    virtual int32_t GetScriptMetaTable();
    virtual ScriptIx* GetScriptByName(const char* name, ScriptData& data);

    // Members
    ScriptIx m_onTooltipSetDefaultAnchor;
    ScriptIx m_onTooltipCleared;
    ScriptIx m_onTooltipAddMoney;
    ScriptIx m_onTooltipSetUnit;
    ScriptIx m_onTooltipSetItem;
    ScriptIx m_onTooltipSetSpell;
    ScriptIx m_onTooltipSetQuest;
    ScriptIx m_onTooltipSetAchievement;
    ScriptIx m_onTooltipSetEquipmentSet;
    ScriptIx m_onTooltipSetFrameStack;
};

#endif // GAME_UI_CGTOOLTIP_HPP
