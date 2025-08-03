#ifndef GAMEUI_GAME_SCRIPT_FUNCTIONS_HPP
#define GAMEUI_GAME_SCRIPT_FUNCTIONS_HPP

#include "ui/Types.hpp"
#include <cstdint>

struct lua_State;

#define NUM_SCRIPT_FUNCTIONS_GAME 310
#define NUM_SCRIPT_FUNCTIONS_UIBINDINGS 26
#define NUM_SCRIPT_FUNCTIONS_UIMACROS 22
#define NUM_SCRIPT_FUNCTIONS_INPUT_CONTROL 52
#define NUM_SCRIPT_FUNCTIONS_CAMERA 22
#define NUM_SCRIPT_FUNCTIONS_SOUND 23
#define NUM_SCRIPT_FUNCTIONS_SPELL 11
#define NUM_SCRIPT_FUNCTIONS_SCRIPT_EVENTS 7
#define NUM_SCRIPT_FUNCTIONS_SCRIPT_EVENTS_UNIT 169
#define NUM_SCRIPT_FUNCTIONS_MINIMAP 4
#define NUM_SCRIPT_FUNCTIONS_UNIT_COMBAT_LOG 11
#define NUM_SCRIPT_FUNCTIONS_ACTION_BAR 28
#define NUM_SCRIPT_FUNCTIONS_PARTY_INFO 22
#define NUM_SCRIPT_FUNCTIONS_CHAT 89
#define NUM_SCRIPT_FUNCTIONS_AUTO_COMPLETE 2
#define NUM_SCRIPT_FUNCTIONS_SPELL_BOOK 45
#define NUM_SCRIPT_FUNCTIONS_CHARACTER_INFO 33
#define NUM_SCRIPT_FUNCTIONS_LOOT_INFO 17
#define NUM_SCRIPT_FUNCTIONS_ITEM_TEXT 9
#define NUM_SCRIPT_FUNCTIONS_GOSSIP_INFO 12
#define NUM_SCRIPT_FUNCTIONS_QUEST_INFO 47
#define NUM_SCRIPT_FUNCTIONS_QUEST_LOG 67
#define NUM_SCRIPT_FUNCTIONS_CGTAXI_MAP 14
#define NUM_SCRIPT_FUNCTIONS_CLASS_TRAINER 28
#define NUM_SCRIPT_FUNCTIONS_TRADE_SKILL 36
#define NUM_SCRIPT_FUNCTIONS_MERCHANT 21
#define NUM_SCRIPT_FUNCTIONS_TRADE_INFO 14
#define NUM_SCRIPT_FUNCTIONS_CONTAINER 22
#define NUM_SCRIPT_FUNCTIONS_BANK 5
#define NUM_SCRIPT_FUNCTIONS_FRIEND_LIST 31
#define NUM_SCRIPT_FUNCTIONS_PET_INFO 31
#define NUM_SCRIPT_FUNCTIONS_WORLD_MAP 40
#define NUM_SCRIPT_FUNCTIONS_REPUTATION_INFO 15
#define NUM_SCRIPT_FUNCTIONS_TABARD_CREATION 2
#define NUM_SCRIPT_FUNCTIONS_GUILD_REGISTRAR 5
#define NUM_SCRIPT_FUNCTIONS_DUEL_INFO 3
#define NUM_SCRIPT_FUNCTIONS_TUTORIAL 8
#define NUM_SCRIPT_FUNCTIONS_PETITION_INFO 8
#define NUM_SCRIPT_FUNCTIONS_SKILL_INFO 13
#define NUM_SCRIPT_FUNCTIONS_GUILD_INFO 43
#define NUM_SCRIPT_FUNCTIONS_MAIL_INFO 38
#define NUM_SCRIPT_FUNCTIONS_BATTLEFIELD_INFO 51
#define NUM_SCRIPT_FUNCTIONS_TALENT_INFO 17
#define NUM_SCRIPT_FUNCTIONS_AUCTION_HOUSE 30
#define NUM_SCRIPT_FUNCTIONS_STABLE_INFO 14
#define NUM_SCRIPT_FUNCTIONS_RAID_INFO 20
#define NUM_SCRIPT_FUNCTIONS_WORLD_STATE_INFO 2
#define NUM_SCRIPT_FUNCTIONS_MINIGAME_INFO 3
#define NUM_SCRIPT_FUNCTIONS_KNOWLEDGE_BASE 22
#define NUM_SCRIPT_FUNCTIONS_ITEM_SOCKET_INFO 12
#define NUM_SCRIPT_FUNCTIONS_PETITION_VENDOR 8
#define NUM_SCRIPT_FUNCTIONS_ARENA_TEAM_INFO 13
#define NUM_SCRIPT_FUNCTIONS_LOOKING_FOR_GROUP 67
#define NUM_SCRIPT_FUNCTIONS_VOICE 15
#define NUM_SCRIPT_FUNCTIONS_CALENDAR 95
#define NUM_SCRIPT_FUNCTIONS_CGCOMMENTATOR 35
#define NUM_SCRIPT_FUNCTIONS_CGBARBER_SHOP 9
#define NUM_SCRIPT_FUNCTIONS_CGDANCE_STUDIO 1
#define NUM_SCRIPT_FUNCTIONS_GUILD_BANK 29
#define NUM_SCRIPT_FUNCTIONS_GLYPH_INFO 6
#define NUM_SCRIPT_FUNCTIONS_ACHIEVEMENT_INFO 37
#define NUM_SCRIPT_FUNCTIONS_CURRENCY_TYPES 6
#define NUM_SCRIPT_FUNCTIONS_EQUIPMENT_MANAGER 17
#define NUM_SCRIPT_FUNCTIONS_GMTICKET_INFO 15
#define NUM_SCRIPT_FUNCTIONS_BATTLENET_UI 57

namespace GameScript {
    extern FrameScript_Method s_ScriptFunctions_Game[NUM_SCRIPT_FUNCTIONS_GAME];
    extern FrameScript_Method s_ScriptFunctions_UIBindings[NUM_SCRIPT_FUNCTIONS_UIBINDINGS];
    extern FrameScript_Method s_ScriptFunctions_UIMacros[NUM_SCRIPT_FUNCTIONS_UIMACROS];
    extern FrameScript_Method s_ScriptFunctions_InputControl[NUM_SCRIPT_FUNCTIONS_INPUT_CONTROL];
    extern FrameScript_Method s_ScriptFunctions_Camera[NUM_SCRIPT_FUNCTIONS_CAMERA];
    extern FrameScript_Method s_ScriptFunctions_Sound[NUM_SCRIPT_FUNCTIONS_SOUND];
    extern FrameScript_Method s_ScriptFunctions_Spell[NUM_SCRIPT_FUNCTIONS_SPELL];
    extern FrameScript_Method s_ScriptFunctions_ScriptEvents[NUM_SCRIPT_FUNCTIONS_SCRIPT_EVENTS];
    extern FrameScript_Method s_ScriptFunctions_ScriptEventsUnit[NUM_SCRIPT_FUNCTIONS_SCRIPT_EVENTS_UNIT];
    extern FrameScript_Method s_ScriptFunctions_Minimap[NUM_SCRIPT_FUNCTIONS_MINIMAP];
    extern FrameScript_Method s_ScriptFunctions_UnitCombatLog[NUM_SCRIPT_FUNCTIONS_UNIT_COMBAT_LOG];
    extern FrameScript_Method s_ScriptFunctions_ActionBar[NUM_SCRIPT_FUNCTIONS_ACTION_BAR];
    extern FrameScript_Method s_ScriptFunctions_PartyInfo[NUM_SCRIPT_FUNCTIONS_PARTY_INFO];
    extern FrameScript_Method s_ScriptFunctions_Chat[NUM_SCRIPT_FUNCTIONS_CHAT];
    extern FrameScript_Method s_ScriptFunctions_AutoComplete[NUM_SCRIPT_FUNCTIONS_AUTO_COMPLETE];
    extern FrameScript_Method s_ScriptFunctions_SpellBook[NUM_SCRIPT_FUNCTIONS_SPELL_BOOK];
    extern FrameScript_Method s_ScriptFunctions_CharacterInfo[NUM_SCRIPT_FUNCTIONS_CHARACTER_INFO];
    extern FrameScript_Method s_ScriptFunctions_LootInfo[NUM_SCRIPT_FUNCTIONS_LOOT_INFO];
    extern FrameScript_Method s_ScriptFunctions_ItemText[NUM_SCRIPT_FUNCTIONS_ITEM_TEXT];
    extern FrameScript_Method s_ScriptFunctions_GossipInfo[NUM_SCRIPT_FUNCTIONS_GOSSIP_INFO];
    extern FrameScript_Method s_ScriptFunctions_QuestInfo[NUM_SCRIPT_FUNCTIONS_QUEST_INFO];
    extern FrameScript_Method s_ScriptFunctions_QuestLog[NUM_SCRIPT_FUNCTIONS_QUEST_LOG];
    extern FrameScript_Method s_ScriptFunctions_CGTaxiMap[NUM_SCRIPT_FUNCTIONS_CGTAXI_MAP];
    extern FrameScript_Method s_ScriptFunctions_ClassTrainer[NUM_SCRIPT_FUNCTIONS_CLASS_TRAINER];
    extern FrameScript_Method s_ScriptFunctions_TradeSkill[NUM_SCRIPT_FUNCTIONS_TRADE_SKILL];
    extern FrameScript_Method s_ScriptFunctions_Merchant[NUM_SCRIPT_FUNCTIONS_MERCHANT];
    extern FrameScript_Method s_ScriptFunctions_TradeInfo[NUM_SCRIPT_FUNCTIONS_TRADE_INFO];
    extern FrameScript_Method s_ScriptFunctions_Container[NUM_SCRIPT_FUNCTIONS_CONTAINER];
    extern FrameScript_Method s_ScriptFunctions_Bank[NUM_SCRIPT_FUNCTIONS_BANK];
    extern FrameScript_Method s_ScriptFunctions_FriendList[NUM_SCRIPT_FUNCTIONS_FRIEND_LIST];
    extern FrameScript_Method s_ScriptFunctions_PetInfo[NUM_SCRIPT_FUNCTIONS_PET_INFO];
    extern FrameScript_Method s_ScriptFunctions_WorldMap[NUM_SCRIPT_FUNCTIONS_WORLD_MAP];
    extern FrameScript_Method s_ScriptFunctions_ReputationInfo[NUM_SCRIPT_FUNCTIONS_REPUTATION_INFO];
    extern FrameScript_Method s_ScriptFunctions_TabardCreation[NUM_SCRIPT_FUNCTIONS_TABARD_CREATION];
    extern FrameScript_Method s_ScriptFunctions_GuildRegistrar[NUM_SCRIPT_FUNCTIONS_GUILD_REGISTRAR];
    extern FrameScript_Method s_ScriptFunctions_DuelInfo[NUM_SCRIPT_FUNCTIONS_DUEL_INFO];
    extern FrameScript_Method s_ScriptFunctions_Tutorial[NUM_SCRIPT_FUNCTIONS_TUTORIAL];
    extern FrameScript_Method s_ScriptFunctions_PetitionInfo[NUM_SCRIPT_FUNCTIONS_PETITION_INFO];
    extern FrameScript_Method s_ScriptFunctions_SkillInfo[NUM_SCRIPT_FUNCTIONS_SKILL_INFO];
    extern FrameScript_Method s_ScriptFunctions_GuildInfo[NUM_SCRIPT_FUNCTIONS_GUILD_INFO];
    extern FrameScript_Method s_ScriptFunctions_MailInfo[NUM_SCRIPT_FUNCTIONS_MAIL_INFO];
    extern FrameScript_Method s_ScriptFunctions_BattlefieldInfo[NUM_SCRIPT_FUNCTIONS_BATTLEFIELD_INFO];
    extern FrameScript_Method s_ScriptFunctions_TalentInfo[NUM_SCRIPT_FUNCTIONS_TALENT_INFO];
    extern FrameScript_Method s_ScriptFunctions_AuctionHouse[NUM_SCRIPT_FUNCTIONS_AUCTION_HOUSE];
    extern FrameScript_Method s_ScriptFunctions_StableInfo[NUM_SCRIPT_FUNCTIONS_STABLE_INFO];
    extern FrameScript_Method s_ScriptFunctions_RaidInfo[NUM_SCRIPT_FUNCTIONS_RAID_INFO];
    extern FrameScript_Method s_ScriptFunctions_WorldStateInfo[NUM_SCRIPT_FUNCTIONS_WORLD_STATE_INFO];
    extern FrameScript_Method s_ScriptFunctions_MinigameInfo[NUM_SCRIPT_FUNCTIONS_MINIGAME_INFO];
    extern FrameScript_Method s_ScriptFunctions_KnowledgeBase[NUM_SCRIPT_FUNCTIONS_KNOWLEDGE_BASE];
    extern FrameScript_Method s_ScriptFunctions_ItemSocketInfo[NUM_SCRIPT_FUNCTIONS_ITEM_SOCKET_INFO];
    extern FrameScript_Method s_ScriptFunctions_PetitionVendor[NUM_SCRIPT_FUNCTIONS_PETITION_VENDOR];
    extern FrameScript_Method s_ScriptFunctions_ArenaTeamInfo[NUM_SCRIPT_FUNCTIONS_ARENA_TEAM_INFO];
    extern FrameScript_Method s_ScriptFunctions_LookingForGroup[NUM_SCRIPT_FUNCTIONS_LOOKING_FOR_GROUP];
    extern FrameScript_Method s_ScriptFunctions_Voice[NUM_SCRIPT_FUNCTIONS_VOICE];
    extern FrameScript_Method s_ScriptFunctions_Calendar[NUM_SCRIPT_FUNCTIONS_CALENDAR];
    extern FrameScript_Method s_ScriptFunctions_CGCommentator[NUM_SCRIPT_FUNCTIONS_CGCOMMENTATOR];
    extern FrameScript_Method s_ScriptFunctions_CGBarberShop[NUM_SCRIPT_FUNCTIONS_CGBARBER_SHOP];
    extern FrameScript_Method s_ScriptFunctions_CGDanceStudio[NUM_SCRIPT_FUNCTIONS_CGDANCE_STUDIO];
    extern FrameScript_Method s_ScriptFunctions_GuildBank[NUM_SCRIPT_FUNCTIONS_GUILD_BANK];
    extern FrameScript_Method s_ScriptFunctions_GlyphInfo[NUM_SCRIPT_FUNCTIONS_GLYPH_INFO];
    extern FrameScript_Method s_ScriptFunctions_AchievementInfo[NUM_SCRIPT_FUNCTIONS_ACHIEVEMENT_INFO];
    extern FrameScript_Method s_ScriptFunctions_CurrencyTypes[NUM_SCRIPT_FUNCTIONS_CURRENCY_TYPES];
    extern FrameScript_Method s_ScriptFunctions_EquipmentManager[NUM_SCRIPT_FUNCTIONS_EQUIPMENT_MANAGER];
    extern FrameScript_Method s_ScriptFunctions_GMTicketInfo[NUM_SCRIPT_FUNCTIONS_GMTICKET_INFO];
    extern FrameScript_Method s_ScriptFunctions_BattlenetUI[NUM_SCRIPT_FUNCTIONS_BATTLENET_UI];
}

// Utility

void LoadScriptFunctions();
void UIBindingsRegisterScriptFunctions();
void UIMacrosRegisterScriptFunctions();
void InputControlRegisterScriptFunctions();
void CameraRegisterScriptFunctions();
void SoundRegisterScriptFunctions();
void SpellRegisterScriptFunctions();
void ScriptEventsRegisterFunctions();
void MinimapRegisterScriptFunctions();
void UnitCombatLogRegisterScriptFunctions();
void ActionBarRegisterScriptFunctions();
void PartyInfoRegisterScriptFunctions();
void ChatRegisterScriptFunctions();
void AutoCompleteRegisterScriptFunctions();
void SpellBookRegisterScriptFunctions();
void CharacterInfoRegisterScriptFunctions();
void LootInfoRegisterScriptFunctions();
void ItemTextRegisterScriptFunctions();
void GossipInfoRegisterScriptFunctions();
void QuestInfoRegisterScriptFunctions();
void QuestLogRegisterScriptFunctions();
void CGTaxiMapRegisterScriptFunctions();
void ClassTrainerRegisterScriptFunctions();
void TradeSkillRegisterScriptFunctions();
void MerchantRegisterScriptFunctions();
void TradeInfoRegisterScriptFunctions();
void ContainerRegisterScriptFunctions();
void BankRegisterScriptFunctions();
void FriendListRegisterScriptFunctions();
void PetInfoRegisterScriptFunctions();
void WorldMapRegisterScriptFunctions();
void ReputationInfoRegisterScriptFunctions();
void TabardCreationRegisterScriptFunctions();
void GuildRegistrarRegisterScriptFunctions();
void DuelInfoRegisterScriptFunctions();
void TutorialRegisterScriptFunctions();
void PetitionInfoRegisterScriptFunctions();
void SkillInfoRegisterScriptFunctions();
void GuildInfoRegisterScriptFunctions();
void MailInfoRegisterScriptFunctions();
void BattlefieldInfoRegisterScriptFunctions();
void TalentInfoRegisterScriptFunctions();
void AuctionHouseRegisterScriptFunctions();
void StableInfoRegisterScriptFunctions();
void RaidInfoRegisterScriptFunctions();
void WorldStateInfoRegisterScriptFunctions();
void MinigameInfoRegisterScriptFunctions();
void KnowledgeBaseRegisterScriptFunctions();
void ItemSocketInfoRegisterScriptFunctions();
void PetitionVendorRegisterScriptFunctions();
void ArenaTeamInfoRegisterScriptFunctions();
void LookingForGroupRegisterScriptFunctions();
void VoiceRegisterScriptFunctions();
void CalendarRegisterScriptFunctions();
void CGCommentatorRegisterScriptFunctions();
void CGBarberShopRegisterScriptFunctions();
void CGDanceStudioRegisterScriptFunctions();
void GuildBankRegisterScriptFunctions();
void GlyphInfoRegisterScriptFunctions();
void AchievementInfoRegisterScriptFunctions();
void CurrencyTypesRegisterScriptFunctions();
void EquipmentManagerRegisterScriptFunctions();
void GMTicketInfoRegisterScriptFunctions();
void BattlenetUIRegisterScriptFunctions();

#endif
