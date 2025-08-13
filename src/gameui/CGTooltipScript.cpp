#include "gameui/CGTooltipScript.hpp"
#include "gameui/CGTooltip.hpp"
#include "ui/FrameScript.hpp"
#include "ui/CSimpleFontString.hpp"
#include "ui/Util.hpp"
#include "gx/Coordinate.hpp"
#include "util/Lua.hpp"
#include "util/Unimplemented.hpp"
#include "util/StringTo.hpp"

static int32_t Script_AddFontStrings(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));

    CSimpleFontString* arguments[2] = {};

    for (int32_t i = 2; i < 4; ++i) {
        if (lua_type(L, i) != LUA_TTABLE) {
            return luaL_error(L, "Usage: %s:AddFontStrings(leftstring, rightstring)", tooltip->GetDisplayName());
        }

        lua_rawgeti(L, i, 0);
        auto fontString = static_cast<CSimpleFontString*>(lua_touserdata(L, -1));
        lua_settop(L, -2);

        if (!fontString) {
            return luaL_error(L, "%s:AddFontStrings(): Couldn't find 'this' in fontstring", tooltip->GetDisplayName());
        }

        if (!fontString->IsA(CSimpleFontString::GetObjectType())) {
            return luaL_error(L, "%s:AddFontStrings(): Wrong object type, expected fontstring", tooltip->GetDisplayName());
        }

        arguments[i - 2] = fontString;
    }

    tooltip->AddFontStrings(arguments[0], arguments[1]);
    return 0;
}

static int32_t Script_SetMinimumWidth(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));

    if (!lua_isnumber(L, 2)) {
        return luaL_error(L, "Usage: %s:SetMinimumWidth(width [,force])", tooltip->GetDisplayName());
    }

    tooltip->m_minWidth = lua_tonumber(L, 2);
    tooltip->m_minWidthForced = StringToBOOL(L, 3, 0);
    return 0;
}

static int32_t Script_GetMinimumWidth(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));
    lua_pushnumber(L, tooltip->m_minWidth);
    if (tooltip->m_minWidthForced) {
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }
    return 2;
}

static int32_t Script_SetPadding(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));

    float value = lua_tonumber(L, 2);
    value /= CoordinateGetAspectCompensation() * 1024.0f;
    tooltip->m_padding = NDCToDDCWidth(value);
    return 0;
}

static int32_t Script_GetPadding(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));
    lua_pushnumber(L, tooltip->m_padding);
    return 1;
}

static int32_t Script_IsOwned(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));

    if (lua_type(L, 2) != LUA_TTABLE) {
        return luaL_error(L, "Usage: %s:IsOwned(frame)", tooltip->GetDisplayName());
    }

    lua_rawgeti(L, 2, 0);
    auto frame = static_cast<CSimpleFrame*>(lua_touserdata(L, -1));
    lua_settop(L, -2);

    if (!frame) {
        return luaL_error(L, "%s:IsOwned(): Couldn't find 'this' in frame object", tooltip->GetDisplayName());
    }

    if (!frame->IsA(CSimpleFrame::GetObjectType())) {
        return luaL_error(L, "%s:IsOwned(): Wrong object type, expected frame", tooltip->GetDisplayName());
    }

    if (tooltip->m_owner == frame) {
        lua_pushnumber(L, 1.0);
    } else {
        lua_pushnil(L);
    }
    return 1;
}

static int32_t Script_GetOwner(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));

    if (tooltip->m_owner) {
        if (!tooltip->m_owner->lua_registered) {
            tooltip->m_owner->RegisterScriptObject(nullptr);
        }
        lua_rawgeti(L, LUA_REGISTRYINDEX, tooltip->m_owner->lua_objectRef);
    } else {
        lua_pushnil(L);
    }

    return 1;
}

static int32_t Script_SetOwner(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));

    tooltip->Hide();

    if (lua_type(L, 2) != LUA_TTABLE) {
        return luaL_error(L, "Usage: %s:SetOwner(frame)", tooltip->GetDisplayName());
    }

    lua_rawgeti(L, 2, 0);
    auto frame = static_cast<CSimpleFrame*>(lua_touserdata(L, -1));
    lua_settop(L, -2);

    if (!frame) {
        return luaL_error(L, "%s:SetOwner(): Couldn't find 'this' in frame object", tooltip->GetDisplayName());
    }

    if (!frame->IsA(CSimpleFrame::GetObjectType())) {
        return luaL_error(L, "%s:SetOwner(): Wrong object type, expected frame", tooltip->GetDisplayName());
    }

    if (frame == tooltip) {
        return luaL_error(L, "%s:SetOwner(): Can't set owner to self", tooltip->GetDisplayName());
    }

    int32_t anchorPoint = 0;
    if (lua_isstring(L, 3)) {
        StringToAnchorPoint(lua_tolstring(L, 3, nullptr), anchorPoint);
    }

    float xoffset = 0.0f;
    if (lua_isnumber(L, 4)) {
        float value = lua_tonumber(L, 4);
        value /= CoordinateGetAspectCompensation() * 1024.0f;
        xoffset = NDCToDDCWidth(value);
    }

    float yoffset = 0.0f;
    if (lua_isnumber(L, 5)) {
        float value = lua_tonumber(L, 5);
        value /= CoordinateGetAspectCompensation() * 1024.0f;
        yoffset = NDCToDDCWidth(value);
    }

    tooltip->SetOwner(frame, static_cast<TOOLTIP_ANCHORPOINT>(anchorPoint), xoffset, yoffset);
}

static int32_t Script_GetAnchorType(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));
    lua_pushstring(L, AnchorPointToString(tooltip->m_anchorPoint));
    return 1;
}

static int32_t Script_SetAnchorType(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));

    int32_t anchorPoint = 0;
    if (lua_isstring(L, 2)) {
        StringToAnchorPoint(lua_tolstring(L, 3, nullptr), anchorPoint);
    } else {
        return luaL_error(L, "Usage: %s:SetAnchorType( anchorType [,Xoffset] [,Yoffset] )", tooltip->GetDisplayName());
    }

    float xoffset = 0.0f;
    if (lua_isnumber(L, 3)) {
        float value = lua_tonumber(L, 3);
        value /= CoordinateGetAspectCompensation() * 1024.0f;
        xoffset = NDCToDDCWidth(value);
    }

    float yoffset = 0.0f;
    if (lua_isnumber(L, 4)) {
        float value = lua_tonumber(L, 4);
        value /= CoordinateGetAspectCompensation() * 1024.0f;
        yoffset = NDCToDDCWidth(value);
    }

    tooltip->SetAnchorType(static_cast<TOOLTIP_ANCHORPOINT>(anchorPoint), xoffset, yoffset);
    return 0;
}

static int32_t Script_ClearLines(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));
    tooltip->ClearTooltip();
    return 0;
}

static int32_t Script_AddLine(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));

    const char* line = lua_isstring(L, 2) ? lua_tolstring(L, 2, nullptr) : nullptr;

    CImVector color = CGTooltip::s_defaultColor;
    if (lua_isnumber(L, 3)) {
        FrameScript_GetColorNoAlpha(L, 3, color);
    }

    bool wrapped = StringToBOOL(L, 6, 0);

    tooltip->AddLine(line, nullptr, color, color, wrapped);
    return 0;
}

static int32_t Script_AddDoubleLine(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));

    const char* leftLine = lua_isstring(L, 2) ? lua_tolstring(L, 2, nullptr) : nullptr;
    const char* rightLine = lua_isstring(L, 3) ? lua_tolstring(L, 3, nullptr) : nullptr;

    CImVector leftColor = CGTooltip::s_defaultColor;
    if (lua_isnumber(L, 4)) {
        FrameScript_GetColorNoAlpha(L, 4, leftColor);
    }

    CImVector rightColor = CGTooltip::s_defaultColor;
    if (lua_isnumber(L, 7)) {
        FrameScript_GetColorNoAlpha(L, 7, rightColor);
    }

    bool wrapped = StringToBOOL(L, 10, 0);

    tooltip->AddLine(leftLine, rightLine, leftColor, rightColor, wrapped);
    return 0;
}

static int32_t Script_AddTexture(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetText(lua_State* L) {
    auto type = CGTooltip::GetObjectType();
    auto tooltip = static_cast<CGTooltip*>(FrameScript_GetObjectThis(L, type));

    const char* line = lua_isstring(L, 2) ? lua_tolstring(L, 2, nullptr) : nullptr;
    if (!line) {
        return luaL_error(L, "Usage: %s:SetText(\"text\" [, color])", tooltip->GetDisplayName());
    }

    CImVector color = CGTooltip::s_defaultColor;
    if (lua_isnumber(L, 3)) {
        FrameScript_GetColor(L, 3, color);
    }

    bool wrapped = StringToBOOL(L, 7, 0);

    tooltip->ClearTooltip();
    tooltip->AddLine(line, nullptr, color, color, wrapped);
    tooltip->Show();
    return 0;
}

static int32_t Script_AppendText(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_FadeOut(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetHyperlink(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetAction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetPetAction(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetShapeshift(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetPossession(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetTracking(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSpell(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSpellByID(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetGlyph(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetInventoryItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetLootItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetQuestItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetQuestLogItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetTrainerService(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetTradeSkillItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetMerchantItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetMerchantCostItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetTradePlayerItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetTradeTargetItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetBagItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetUnit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetUnitBuff(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetUnitDebuff(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetUnitAura(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetTalent(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSendMailItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetInboxItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetAuctionSellItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetAuctionItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_NumLines(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetQuestRewardSpell(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetQuestLogRewardSpell(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetHyperlinkCompareItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetBuybackItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetLootRollItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSocketedItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetSocketGem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetExistingSocketGem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetGuildBankItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsUnit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetUnit(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_GetSpell(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetTotem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetCurrencyToken(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetBackpackToken(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_IsEquippedItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetQuestLogSpecialItem(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetEquipmentSet(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetFrameStack(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetLFGDungeonReward(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}

static int32_t Script_SetLFGCompletionReward(lua_State* L) {
    WHOA_UNIMPLEMENTED(0);
}


FrameScript_Method CGTooltipMethods[NUM_CGTOOLTIP_SCRIPT_METHODS] = {
    { "AddFontStrings", &Script_AddFontStrings },
    { "SetMinimumWidth", &Script_SetMinimumWidth },
    { "GetMinimumWidth", &Script_GetMinimumWidth },
    { "SetPadding", &Script_SetPadding },
    { "GetPadding", &Script_GetPadding },
    { "IsOwned", &Script_IsOwned },
    { "GetOwner", &Script_GetOwner },
    { "SetOwner", &Script_SetOwner },
    { "GetAnchorType", &Script_GetAnchorType },
    { "SetAnchorType", &Script_SetAnchorType },
    { "ClearLines", &Script_ClearLines },
    { "AddLine", &Script_AddLine },
    { "AddDoubleLine", &Script_AddDoubleLine },
    { "AddTexture", &Script_AddTexture },
    { "SetText", &Script_SetText },
    { "AppendText", &Script_AppendText },
    { "FadeOut", &Script_FadeOut },
    { "SetHyperlink", &Script_SetHyperlink },
    { "SetAction", &Script_SetAction },
    { "SetPetAction", &Script_SetPetAction },
    { "SetShapeshift", &Script_SetShapeshift },
    { "SetPossession", &Script_SetPossession },
    { "SetTracking", &Script_SetTracking },
    { "SetSpell", &Script_SetSpell },
    { "SetSpellByID", &Script_SetSpellByID },
    { "SetGlyph", &Script_SetGlyph },
    { "SetInventoryItem", &Script_SetInventoryItem },
    { "SetLootItem", &Script_SetLootItem },
    { "SetQuestItem", &Script_SetQuestItem },
    { "SetQuestLogItem", &Script_SetQuestLogItem },
    { "SetTrainerService", &Script_SetTrainerService },
    { "SetTradeSkillItem", &Script_SetTradeSkillItem },
    { "SetMerchantItem", &Script_SetMerchantItem },
    { "SetMerchantCostItem", &Script_SetMerchantCostItem },
    { "SetTradePlayerItem", &Script_SetTradePlayerItem },
    { "SetTradeTargetItem", &Script_SetTradeTargetItem },
    { "SetBagItem", &Script_SetBagItem },
    { "SetUnit", &Script_SetUnit },
    { "SetUnitBuff", &Script_SetUnitBuff },
    { "SetUnitDebuff", &Script_SetUnitDebuff },
    { "SetUnitAura", &Script_SetUnitAura },
    { "SetTalent", &Script_SetTalent },
    { "SetSendMailItem", &Script_SetSendMailItem },
    { "SetInboxItem", &Script_SetInboxItem },
    { "SetAuctionSellItem", &Script_SetAuctionSellItem },
    { "SetAuctionItem", &Script_SetAuctionItem },
    { "NumLines", &Script_NumLines },
    { "SetQuestRewardSpell", &Script_SetQuestRewardSpell },
    { "SetQuestLogRewardSpell", &Script_SetQuestLogRewardSpell },
    { "SetHyperlinkCompareItem", &Script_SetHyperlinkCompareItem },
    { "SetBuybackItem", &Script_SetBuybackItem },
    { "SetLootRollItem", &Script_SetLootRollItem },
    { "SetSocketedItem", &Script_SetSocketedItem },
    { "SetSocketGem", &Script_SetSocketGem },
    { "SetExistingSocketGem", &Script_SetExistingSocketGem },
    { "SetGuildBankItem", &Script_SetGuildBankItem },
    { "IsUnit", &Script_IsUnit },
    { "GetUnit", &Script_GetUnit },
    { "GetItem", &Script_GetItem },
    { "GetSpell", &Script_GetSpell },
    { "SetTotem", &Script_SetTotem },
    { "SetCurrencyToken", &Script_SetCurrencyToken },
    { "SetBackpackToken", &Script_SetBackpackToken },
    { "IsEquippedItem", &Script_IsEquippedItem },
    { "SetQuestLogSpecialItem", &Script_SetQuestLogSpecialItem },
    { "SetEquipmentSet", &Script_SetEquipmentSet },
    { "SetFrameStack", &Script_SetFrameStack },
    { "SetLFGDungeonReward", &Script_SetLFGDungeonReward },
    { "SetLFGCompletionReward", &Script_SetLFGCompletionReward }
};
