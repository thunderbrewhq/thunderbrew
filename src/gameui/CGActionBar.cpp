#include "CGActionBar.h"
#include "ui/FrameScript.hpp"
#include <algorithm>

bool CGActionBar::ActionHasRange(const int slot) {
    if (slot > -1 && slot < MAX_SLOT_COUNT) {
        // TODO:
        return true;
    }
    return false;
}

void CGActionBar::EnterWorld() {
    UpdateUsable();
    UpdateShapeShiftBar();
    UpdateOverrideSpellBar();
    UpdateBonusBar();
}

const char* CGActionBar::GetAttackTexture() {
    // TODO:
    return "Interface\\Buttons\\Spell-Reset";
}

int CGActionBar::FindUseEnchantItemPtr(const unsigned int itemId) {
    // TODO:
    return 0;
}

int CGActionBar::CalculateItemCount(const unsigned int itemId) {
    // TODO:
    return 0;
}

void CGActionBar::GetCooldown(const int slot, int& start, int& duration, bool& enable) {
    start = 0;
    duration = 0;

    if (slot > -1 && slot < MAX_SLOT_COUNT) {
        auto item = GetItem(slot);
        if (!item) {
            auto spell = GetSpell(slot, start);
            if (spell != 0) {
                // TODO:
                // Spell_C__GetSpellCooldown
            }
        } else {
            // TODO:
        }
    }
}

unsigned int CGActionBar::GetEquipmentSetID(const int slot) {
    const int value = m_slotActions[slot];

    if (value != 0 && (value & 0xf0000000) == 0x20000000) {
        return value & 0xdfffffff;
    }

    return -1u;
}

unsigned int CGActionBar::GetItem(const int slot) {
    if (slot > -1 && slot < MAX_SLOT_COUNT) {
        if (IsMacro(slot)) {
            // TODO:
            /*
            auto value = FUN_005a7a40(slot);
            if(value != 0) {
                return FUN_005a7a90(slot);
            }
            */
        }

        if (IsItem(slot)) {
            return m_slotActions[slot] & 0x7fffffff;
        }
    }

    return 0;
}

unsigned int CGActionBar::GetMacroID(const int slot) {
    const int value = m_slotActions[slot];

    if (value != 0 && (value & 0xf0000000) == 0x40000000) {
        return value & 0xbfffffff;
    }

    return -1u;
}

unsigned int CGActionBar::GetMultiCastSlotMaskForTotemCategory(const int category) {
    switch (category) {
    case 2:
        return 2;
    case 3:
        return 8;
    case 4:
        return 1;
    case 5:
        return 4;
    case 21:
        return 15;
    default:
        return 0;
    }
}

const char* CGActionBar::GetRangedTexture() {
    // TODO:
    return nullptr;
}

const char* CGActionBar::GetTexture(const int slot) {
    // TODO:
    if (slot < 0 || slot > MAX_SLOT_COUNT - 1) {
        return nullptr;
    }
    return nullptr;
}

bool CGActionBar::HasAction(const int slot) {
    if (IsMacro(slot)) {
        // TODO:
        // auto macro = CGUIMacros::GetMacroIndexById(m_slotActions[slot] & 0xbfffffff);
        // if (macro == -1) {
        //     return false;
        // }
    }

    auto value = m_slotActions[slot];
    if (value == 0 || (value & 0xf0000000) != 0x10000000) {
        return value != 0;
    } else {
        // TODO:
    }
    return false;
}

void CGActionBar::HideGrid() {
    FrameScript_SignalEvent(0xAE, 0);
}

unsigned int CGActionBar::GetSpell(const int slot, int& start) {
    start = 0;
    if (slot > -1 && slot < MAX_SLOT_COUNT) {
        // TODO:
    }
    return 0;
}

void CGActionBar::InitializeGame() {
    std::fill_n(m_slotActions, MAX_SLOT_COUNT, 0);
    std::fill_n(m_slotUseCount, MAX_SLOT_COUNT, 0);
    std::fill_n(m_slotUsable, MAX_SLOT_COUNT, 0);
    std::fill_n(m_slotNoMana, MAX_SLOT_COUNT, 0);

    m_currentPage = 0;
    m_bonusBarOffset = 0;
    m_tempPageActiveFlags = 0;
}

bool CGActionBar::IsConsumableAction(const int slot) {
    if (slot < 0 || slot > MAX_SLOT_COUNT - 1) {
        return false;
    }
    // TODO:
    return false;
}

bool CGActionBar::IsCurrentAction(const int slot) {
    // TODO:
    if (-1 < slot && slot < MAX_SLOT_COUNT && m_slotActions[slot] != 0) {
        return true;
    }
    return false;
}

bool CGActionBar::IsEquipmentSet(const int slot) {
    const int value = m_slotActions[slot];

    if (value != 0 && (value & 0xf0000000) == 0x20000000) {
        return true;
    }

    return false;
}

bool CGActionBar::IsEquippedAction(const int slot) {
    if (slot < 0 || slot > MAX_SLOT_COUNT - 1) {
        return false;
    }
    // TODO:
    return false;
}

bool CGActionBar::IsItem(const int slot) {
    const int value = m_slotActions[slot];

    if (value != 0 && (value & 0xf0000000) == 0x80000000) {
        return true;
    }

    return false;
}

bool CGActionBar::IsMacro(const int slot) {
    const int value = m_slotActions[slot];

    if (value != 0 && (value & 0xf0000000) == 0x40000000) {
        return true;
    }

    return false;
}

void CGActionBar::PickupAction(const int slot) {
    // TODO:
}

void CGActionBar::RemoveAction(const int slot) {
    if (slot > -1 && slot < MAX_SLOT_COUNT) {
        // TODO:
    }
}

void CGActionBar::PutActionInSlot(const int slot) {
    // TODO:
}

bool CGActionBar::IsSpell(const int slot) {
    const int value = m_slotActions[slot];

    if (value != 0 && (value & 0xf0000000) == 0) {
        return true;
    }

    return false;
}

void CGActionBar::RemoveEquipmentSet(const int equipmentSetId) {
    const int EQUIPMENT_SET_MAX_ID = 10;
    if (equipmentSetId < EQUIPMENT_SET_MAX_ID) {
        for (int i = 0; i < MAX_SLOT_COUNT; i++) {
            if (IsEquipmentSet(i) && GetEquipmentSetID(i) == equipmentSetId) {
                RemoveAction(i);
            }
        }
    }
}

void CGActionBar::RemoveMacro(const int macroId) {
    int start = 0;
    for (int i = 0; i < MAX_SLOT_COUNT; i++) {
        if (GetSpell(i, start) == macroId) {
            auto value = m_slotActions[i];
            if (value != 0 && IsMacro(i)) {
                // TODO:
                // CGUIMacros__FindMacro(value & 0xbfffffff);
                // MACRONODE::FindSpellID();
            }
            RemoveAction(i);
        }
    }
}

void CGActionBar::ReplaceSpell(const int slot, const int spellId) {
    // TODO:
    if (slot > -1 && slot < MAX_SLOT_COUNT) {
    }
}

void CGActionBar::SetAction(const int slot, const int spellId, bool arg1, bool arg2) {
    // TODO:
    if (slot > -1 && slot < MAX_SLOT_COUNT) {
    }
}

void CGActionBar::SetTemporaryActionBarFlags(const unsigned int flags, bool value) {
    if (value) {
        m_tempPageActiveFlags |= flags;
        return;
    }

    m_tempPageActiveFlags &= ~flags;
}

void CGActionBar::ShowGrid() {
    FrameScript_SignalEvent(0xAD, 0);
}

void CGActionBar::SlotChanged(const int slot, bool arg1, bool arg2) {
    if (slot > -1 && slot < MAX_SLOT_COUNT) {
        // TODO:
    }
}

void CGActionBar::UpdateBonusBar() {
    // TODO:
}

void CGActionBar::UpdateCritter(const int slot) {
    // TODO:
}

void CGActionBar::UpdateEquipmentSet(const int equipmentSetId) {
    const int EQUIPMENT_SET_MAX_ID = 10;
    if (equipmentSetId < EQUIPMENT_SET_MAX_ID) {
        for (int i = 0; i < MAX_SLOT_COUNT; i++) {
            if (IsEquipmentSet(i) && GetEquipmentSetID(i) == equipmentSetId) {
                bool noMana = false;
                auto value = UpdateUsableAction(i, noMana);
                m_slotUsable[i] = value;
                m_slotNoMana[i] = noMana;
                FrameScript_SignalEvent(0xB0, "%d", i + 1);
            }
        }
    }
}

void CGActionBar::UpdateItem(const int slot) {
    // TODO:
}

void CGActionBar::UpdateMacro(const int macroId) {
    // TODO:
    for (int i = 0; i < MAX_SLOT_COUNT; i++) {
        if (IsMacro(i) && GetMacroID(i) == macroId) {
            int useCount = 0;
            auto item = GetItem(i);
            if (!item) {
                int start = 0;
                auto spell = GetSpell(i, start);
                if (spell != 0 && start == 0) {
                    // useCount = Spell_C_GetSpellReagentUses(spell);
                }
            } else {
                useCount = CalculateItemCount(GetItem(i));
            }
            m_slotUseCount[i] = useCount;

            bool noMana = false;
            auto usable = UpdateUsableAction(i, noMana);
            m_slotUsable[i] = usable;
            m_slotNoMana[i] = noMana;
            FrameScript_SignalEvent(0xB0, "%d", i + 1);
        }
    }
}

void CGActionBar::UpdateMultiCastBar() {
    // TODO:
}

void CGActionBar::UpdateOverrideSpellBar() {
    // TODO:
}

void CGActionBar::UpdateShapeShiftBar() {
    // TODO:
}

void CGActionBar::UpdateTemporaryActionBar(void* callback) {
    // TODO:
}

void CGActionBar::UpdateUsable() {
    // TODO:
    bool changed = false;
    bool noMana = false;

    for (int i = 0; i < MAX_SLOT_COUNT; ++i) {
        int usable = UpdateUsableAction(i, noMana);
        if (usable != m_slotUsable[i] || noMana != m_slotNoMana[i]) {
            m_slotUsable[i] = usable;
            m_slotNoMana[i] = noMana;
            changed = true;
        }
    }

    if (changed) {
        FrameScript_SignalEvent(0xB2, 0);
    }
}

bool CGActionBar::UpdateUsableAction(const int slot, bool& noMana) {
    // TODO:
    return false;
}

void CGActionBar::UpdateUsablePower() {
    // TODO:
}

void CGActionBar::UseAction(const int slot, void* arg1, void* arg2) {
    // TODO:
}

bool CGActionBar::HasValidTarget(const int slot, void* arg1, void* arg2, void* arg3) {
    // TODO:
    return false;
}
