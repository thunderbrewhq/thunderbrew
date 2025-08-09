#ifndef GAME_UI_CGACTIONBAR_HPP
#define GAME_UI_CGACTIONBAR_HPP

class CGActionBar {
    public:
    static const int MAX_SLOT_COUNT = 144;
    static unsigned int m_slotNoMana[MAX_SLOT_COUNT];
    static unsigned int m_slotUsable[MAX_SLOT_COUNT];
    static unsigned int m_slotUseCount[MAX_SLOT_COUNT];
    static unsigned int m_slotActions[MAX_SLOT_COUNT];

    static int m_currentPage;
    static int m_bonusBarOffset;
    static unsigned int m_tempPageActiveFlags;

    static bool ActionHasRange(const int slot);
    static void EnterWorld();
    static const char* GetAttackTexture();
    static int FindUseEnchantItemPtr(const unsigned int itemId);
    static int CalculateItemCount(const unsigned int itemId);
    static void GetCooldown(const int slot, int& start, int& duration, bool& enable);
    static unsigned int GetEquipmentSetID(const int slot);
    static unsigned int GetItem(const int slot);
    static unsigned int GetMacroID(const int slot);
    static unsigned int GetMultiCastSlotMaskForTotemCategory(const int category);
    static const char* GetRangedTexture();
    static unsigned int GetSpell(const int slot, int& start);
    static const char* GetTexture(const int slot);
    static bool HasAction(const int slot);
    static void HideGrid();
    static void InitializeGame();
    static bool IsConsumableAction(const int slot);
    static bool IsCurrentAction(const int slot);
    static bool IsEquipmentSet(const int slot);
    static bool IsEquippedAction(const int slot);
    static bool IsItem(const int slot);
    static bool IsMacro(const int slot);
    static bool IsSpell(const int slot);
    static void PickupAction(const int slot);
    static void PutActionInSlot(const int slot);
    static void RemoveAction(const int slot);
    static void RemoveEquipmentSet(const int equipmentSetId);
    static void RemoveMacro(const int macroId);
    static void ReplaceSpell(const int slot, const int spellId);
    static void SetAction(const int slot, const int spellId, bool arg1 = true, bool arg2 = false);
    static void SetTemporaryActionBarFlags(const unsigned int flags, const bool value);
    static void ShowGrid();
    static void SlotChanged(const int slot, bool arg1, bool arg2);
    static void UpdateBonusBar();
    static void UpdateCritter(const int slot);
    static void UpdateEquipmentSet(const int equipmentSetId);
    static void UpdateItem(const int slot);
    static void UpdateMacro(const int macroId);
    static void UpdateMultiCastBar();
    static void UpdateOverrideSpellBar();
    static void UpdateShapeShiftBar();
    static void UpdateTemporaryActionBar(void* callback);
    static void UpdateUsable();
    static bool UpdateUsableAction(const int slot, bool& noMana);
    static void UpdateUsablePower();
    static void UseAction(const int slot, void* arg1, void* arg2);
    static bool HasValidTarget(const int slot, void* arg1, void* arg2, void* arg3);
};

#endif // GAME_UI_CGACTIONBAR_HPP
