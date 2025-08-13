#ifndef GAME_UI_CGTOOLTIP_HPP
#define GAME_UI_CGTOOLTIP_HPP

#include "ui/CSimpleFrame.hpp"
#include "ui/CSimpleTop.hpp"

class CSimpleFontString;

enum TOOLTIP_ANCHORPOINT {
    ANCHOR_LEFT = 0,
    ANCHOR_RIGHT,
    ANCHOR_BOTTOMLEFT,
    ANCHOR_BOTTOM,
    ANCHOR_BOTTOMRIGHT,
    ANCHOR_TOPLEFT,
    ANCHOR_TOP,
    ANCHOR_TOPRIGHT,
    ANCHOR_CURSOR,
    ANCHOR_NONE,
    ANCHOR_PRESERVE,
    ANCHOR_CURSOR_RIGHT,
};

class CGTooltip : public CSimpleFrame {
    public:
    // Static variables
    static int32_t s_metatable;
    static int32_t s_objectType;
    static CImVector s_defaultColor;

    // Static functions
    static CSimpleFrame* Create(CSimpleFrame* parent);
    static void CreateScriptMetaTable();
    static int32_t GetObjectType();
    static void RegisterScriptMethods(lua_State* L);

    // Member functions
    CGTooltip(CSimpleFrame* parent);
    void ClearTooltip();
    void ResetPosition(int32_t a1);
    void SetAnchorType(TOOLTIP_ANCHORPOINT anchorpoint, float xoffset, float yoffset);
    void SetOwner(CSimpleFrame* owner, TOOLTIP_ANCHORPOINT anchorpoint, float xoffset, float yoffset);
    void AddFontStrings(CSimpleFontString* leftstring, CSimpleFontString* rightstring);
    void AddLine(
        const char* leftText,
        const char* rightText,
        const CImVector& leftColor,
        const CImVector& rightColor,
        int32_t wrapped);

    // Virtual member functions
    virtual bool IsA(int32_t type);
    virtual int32_t GetScriptMetaTable();
    virtual ScriptIx* GetScriptByName(const char* name, ScriptData& data);

    // Member variables
    CSimpleFrame* m_owner = nullptr;
    TOOLTIP_ANCHORPOINT m_anchorPoint = ANCHOR_NONE;
    uint32_t m_lines = 0;
    uint32_t m_linesMax = 0;
    TSFixedArray<CSimpleFontString*> m_leftStrings;
    TSFixedArray<CSimpleFontString*> m_rightStrings;
    TSFixedArray<int32_t> m_wrapLine;
    float m_padding = 0.0f;
    float m_minWidth = 0.0f;
    uint32_t m_minWidthForced = 0;
    float m_offsetX = 0.0f;
    float m_offsetY = 0.0f;
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
