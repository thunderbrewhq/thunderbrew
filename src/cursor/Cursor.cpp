#include "cursor/Cursor.hpp"
#include "ui/FrameScript.hpp"
#include "gx/Texture.hpp"
#include "gx/Device.hpp"

#include <cstdint>
#include <cstring>

#include <storm/String.hpp>

static CURSORMODE s_cursorMode;
static uint32_t s_cursorResetMode;
static CURSORITEMTYPE s_cursorItemType;
static uint32_t s_cursorItemMips;
static uint32_t s_cursorItemMipsHeight;
static uint32_t s_cursorItemMipsWidth;
static int8_t s_cursorFile;

static uint32_t s_cursorItem[CURSOR_IMAGE_SIZE];

static uint32_t s_cursorImages[NUM_CURSOR_MODES][CURSOR_IMAGE_SIZE];

static const char* s_cursorNames[NUM_CURSOR_MODES] = {
    nullptr, /* NO_CURSOR */
    "Point", /* POINT_CURSOR */
    "Cast", /* CAST_CURSOR */
    "Buy", /* BUY_CURSOR */
    "Attack", /* ATTACK_CURSOR */
    "Interact", /* INTERACT_CURSOR */
    "Speak", /* SPEAK_CURSOR */
    "Inspect", /* INSPECT_CURSOR */
    "Pickup", /* PICKUP_CURSOR */
    "Taxi", /* TAXI_CURSOR */
    "Trainer", /* TRAINER_CURSOR */
    "Mine", /* MINE_CURSOR */
    "Skin", /* SKIN_CURSOR */
    "GatherHerbs", /* GATHER_CURSOR */
    "PickLock", /* LOCK_CURSOR */
    "Mail", /* MAIL_CURSOR */
    "LootAll", /* LOOT_ALL_CURSOR */
    "Repair", /* REPAIR_CURSOR */
    "RepairNPC", /* REPAIRNPC_CURSOR */
    "Item", /* ITEM_CURSOR */
    "SkinHorde", /* SKIN_HORDE_CURSOR */
    "SkinAlliance", /* SKIN_ALLIANCE_CURSOR */
    "Innkeeper", /* INNKEEPER_CURSOR */
    "Quest", /* QUEST_CURSOR */
    "QuestRepeatable", /* QUEST_REPEATABLE_CURSOR */
    "QuestTurnIn", /* QUEST_TURNIN_CURSOR */
    "vehichleCursor", /* VEHICLE_CURSOR */
    "UnablePoint", /* POINT_ERROR_CURSOR */
    "UnableCast", /* CAST_ERROR_CURSOR */
    "UnableBuy", /* BUY_ERROR_CURSOR */
    "UnableAttack", /* ATTACK_ERROR_CURSOR */
    "UnableInteract", /* INTERACT_ERROR_CURSOR */
    "UnableSpeak", /* SPEAK_ERROR_CURSOR */
    "UnableInspect", /* INSPECT_ERROR_CURSOR */
    "UnablePickup", /* PICKUP_ERROR_CURSOR */
    "UnableTaxi", /* TAXI_ERROR_CURSOR */
    "UnableTrainer", /* TRAINER_ERROR_CURSOR */
    "UnableMine", /* MINE_ERROR_CURSOR */
    "UnableSkin", /* SKIN_ERROR_CURSOR */
    "UnableGatherHerbs", /* GATHER_ERROR_CURSOR */
    "UnablePickLock", /* LOCK_ERROR_CURSOR */
    "UnableMail", /* MAIL_ERROR_CURSOR */
    "UnableLootAll", /* LOOT_ALL_ERROR_CURSOR */
    "UnableRepair", /* REPAIR_ERROR_CURSOR */
    "UnableRepairNPC", /* REPAIRNPC_ERROR_CURSOR */
    "UnableItem", /* ITEM_ERROR_CURSOR */
    "UnableSkinHorde", /* SKIN_HORDE_ERROR_CURSOR */
    "UnableSkinAlliance", /* SKIN_ALLIANCE_ERROR_CURSOR */
    "UnableInnkeeper", /* INNKEEPER_ERROR_CURSOR */
    "UnableQuest", /* QUEST_ERROR_CURSOR */
    "UnableQuestRepeatable", /* QUEST_REPEATABLE_ERROR_CURSOR */
    "UnableQuestTurnIn", /* QUEST_TURNIN_ERROR_CURSOR */
    "UnablevehichleCursor" /* VEHICLE_ERROR_CURSOR */
};

int32_t CopyCursorImage(uint32_t* image, MipBits* mipImages, uint32_t width, uint32_t height) {
    if (mipImages) {
        if (width == 32 && height == 32) {
            memcpy(image, mipImages->mip[0], CURSOR_IMAGE_BYTES);
            return 1;
        }

        if (width == 64 && height == 64) {
            // Downsample /2

            auto end = image + 1024;

            auto topRow = mipImages->mip[0];

            auto dest = image;

            while (dest < end) {
                auto bottomRow = topRow + 64;

                auto topPixels = topRow;
                auto bottomPixels = bottomRow;

                // Merge 4 pixels into one
                while (bottomPixels < bottomRow) {
                    *dest++ = ((topPixels[0].b + topPixels[1].b + bottomPixels[0].b + bottomPixels[1].b) / 4) |
                              (((topPixels[0].g + topPixels[1].g + bottomPixels[0].g + bottomPixels[1].g) / 4) << 8) |
                              (((topPixels[0].r + topPixels[1].r + bottomPixels[0].r + bottomPixels[1].r) / 4) << 16) |
                              (((topPixels[0].a + topPixels[1].a + bottomPixels[0].a + bottomPixels[1].a) / 4) << 24);

                    topPixels += 2;
                    bottomPixels += 2;
                }

                // Advance two rows
                topRow += 128;
            }

            return 1;
        }
    }

    // failure

    memset(image, 0, CURSOR_IMAGE_BYTES);
    return 0;
}

void UpdateCursor() {
    auto cursor = g_theGxDevicePtr->CursorLock();

    if (s_cursorItemType == CURSOR_EMPTY) {
        // update the cursor to the current mode's image
        memcpy(cursor, s_cursorImages[s_cursorMode], CURSOR_IMAGE_BYTES);
    } else {
        if (s_cursorItemMips == 0) {
            // merge the icon with the cursor bitmap
            // so the pointer in the top left remains
            int32_t i = 0;
            int32_t j = CURSOR_IMAGE_SIZE/4;

            while (j) {
                auto pixel1 = s_cursorImages[CURSOR_ITEM][i];
                if (!(pixel1 & 0xFF000000)) {
                    pixel1 = s_cursorItem[i];
                }
                cursor[i] = pixel1;

                auto pixel2 = s_cursorImages[CURSOR_ITEM][i + 1];
                if (!(pixel2 & 0xFF000000)) {
                    pixel2 = s_cursorItem[i + 1];
                }
                cursor[i + 1] = pixel2;

                auto pixel3 = s_cursorImages[CURSOR_ITEM][i + 2];
                if (!(pixel3 & 0xFF000000)) {
                    pixel3 = s_cursorItem[i + 2];
                }
                cursor[i + 2] = pixel3;

                auto pixel4 = s_cursorImages[CURSOR_ITEM][i + 3];
                if (!(pixel4 & 0xFF000000)) {
                    pixel4 = s_cursorItem[i + 3];
                }
                cursor[i + 3] = pixel4;

                j--;
            }
        } else {
            memcpy(cursor, s_cursorImages[CURSOR_ITEM], CURSOR_IMAGE_BYTES);
        }
    }

    g_theGxDevicePtr->CursorUnlock(0, 0);
}

void CursorInitialize() {
    s_cursorMode = POINT_CURSOR;
    s_cursorResetMode = 1;
    s_cursorItemType = CURSOR_EMPTY;
    s_cursorItemMips = 0;
    s_cursorItemMipsHeight = 0;
    s_cursorItemMipsWidth = 0;

    char cursorFilename[STORM_MAX_PATH];

    for (uint32_t mode = 0; mode < NUM_CURSOR_MODES; mode++) {
        auto cursorName = s_cursorNames[mode];
        auto cursorImage = s_cursorImages[mode];

        if (cursorName) {
            SStrPrintf(cursorFilename, STORM_MAX_PATH, "Interface\\Cursor\\%s.blp", cursorName);

            uint32_t width;
            uint32_t height;
            PIXEL_FORMAT dataFormat = PIXEL_ARGB8888;

            auto mipImages = TextureLoadImage(cursorFilename, &width, &height, &dataFormat, nullptr, nullptr, nullptr, 0);

            if (mipImages) {
                CopyCursorImage(cursorImage, mipImages, width, height);
                TextureFreeMippedImg(mipImages, dataFormat, width, height);
            } else {
                memset(cursorImage, 0, CURSOR_IMAGE_BYTES);
            }
        } else {
            memset(cursorImage, 0, CURSOR_IMAGE_BYTES);
        }
    }

    s_cursorFile = 0;
    UpdateCursor();
}

void CursorSetMode(CURSORMODE mode) {
    if (mode != NUM_CURSOR_MODES && s_cursorMode != mode) {
        s_cursorMode = mode;
        UpdateCursor();
        FrameScript_SignalEvent(275, nullptr);
    }
}

void CursorResetCursor() {
    // TODO
}
