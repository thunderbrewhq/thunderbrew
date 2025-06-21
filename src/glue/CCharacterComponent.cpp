#include "glue/CCharacterComponent.hpp"

#include <algorithm>

#include <common/ObjectAlloc.hpp>
#include <common/Processor.hpp>
#include "console/Types.hpp"
#include "console/CVar.hpp"
#include "model/CM2Model.hpp"
#include "db/Db.hpp"

CVar* CCharacterComponent::g_componentTextureLevelVar = nullptr;
CVar* CCharacterComponent::g_componentThreadVar = nullptr;
CVar* CCharacterComponent::g_componentCompressVar = nullptr;

uint32_t* CCharacterComponent::s_heap = nullptr;


static bool ComponentVarHandler(CVar*, const char*, const char*, void*) {
    return true;
}

ComponentData::ComponentData() {
    this->m_unkFlag &= 0xFFFFFFFC;
    memset(&this->m_info, 0, sizeof(this->m_info));
    this->m_model = nullptr;

    DefaultGeosets();
}

ComponentData::ComponentData(const CHARACTER_INFO& info) {
    this->m_unkFlag &= 0xFFFFFFFC;
    memset(&this->m_info, 0, sizeof(this->m_info));
    this->m_model = nullptr;

    this->m_info.raceID = info.raceID;
    this->m_info.sexID = info.sexID;
    this->m_info.classID = info.classID;
    this->m_info.skinID = info.skinID;
    this->m_info.faceID = info.faceID;
    this->m_info.hairStyleID = info.hairStyleID;
    this->m_info.hairColorID = info.hairColorID;
    this->m_info.facialFeatureID = info.facialHairStyleID;

    DefaultGeosets();
}

void ComponentData::DefaultGeosets() {
    this->m_geosets[0] = 1;
    this->m_geosets[1] = 101;
    this->m_geosets[2] = 201;
    this->m_geosets[3] = 301;
    this->m_geosets[7] = 702;
    this->m_geosets[4] = 401;
    this->m_geosets[5] = 501;
    this->m_geosets[6] = 601;
    this->m_geosets[8] = 801;
    this->m_geosets[9] = 901;
    this->m_geosets[10] = 1001;
    this->m_geosets[11] = 1101;
    this->m_geosets[12] = 1201;
    this->m_geosets[13] = 1301;
    this->m_geosets[14] = 1401;
    this->m_geosets[15] = 1501;
    this->m_geosets[16] = 1601;
    this->m_geosets[17] = 1701;
    this->m_geosets[18] = 1801;
}

void CCharacterComponent::Initialize() {
    CCharacterComponent::g_componentTextureLevelVar = CVar::Register(
        "componentTextureLevel",
        "Number of mip levels used for character component textures",
        0x1,
        "8",
        &ComponentVarHandler,
        CATEGORY::DEBUG,
        0,
        nullptr,
        false);

    CCharacterComponent::g_componentThreadVar = CVar::Register(
        "componentThread",
        "Multi thread character component processing",
        0x1,
        "1",
        &ComponentVarHandler,
        CATEGORY::DEBUG,
        0,
        nullptr,
        false);

    CCharacterComponent::g_componentCompressVar = CVar::Register(
        "componentCompress",
        "Character component texture compression",
        0x1,
        "1",
        &ComponentVarHandler,
        CATEGORY::DEBUG,
        0,
        nullptr,
        false);

    uint32_t mipLevels = CCharacterComponent::g_componentTextureLevelVar->GetInt();
    int32_t useThreads = CCharacterComponent::g_componentThreadVar->GetInt();
    int32_t useCompression = CCharacterComponent::g_componentCompressVar->GetInt();

    if (!useThreads || OsGetProcessorCount() < 2) {
        useThreads = 0;

        if (mipLevels > 8) {
            mipLevels = 8;
        }

        useCompression = 0;
    }

    if (mipLevels > 9) {
        mipLevels = 9;
    }

    if (mipLevels < 7) {
        mipLevels = 7;
    }

    CCharacterComponent::Initialize(GxTex_Rgb565, mipLevels, useThreads, useCompression);
}

void CCharacterComponent::Initialize(EGxTexFormat format, uint32_t mipLevels, int32_t useThreads, int32_t useCompression) {
    CCharacterComponent::s_heap = static_cast<uint32_t*>(ALLOC(sizeof(uint32_t)));
    if (CCharacterComponent::s_heap) {
        *CCharacterComponent::s_heap = ObjectAllocAddHeap(sizeof(CCharacterComponent), 32, "CCharacterComponent", true);
    }

    // TODO
}

CCharacterComponent* CCharacterComponent::AllocComponent() {

    uint32_t handle;
    void* memory;

    if (ObjectAlloc(*CCharacterComponent::s_heap, &handle, &memory, false) && memory) {
        auto component = new (memory) CCharacterComponent();
        component->m_handle = handle;
        return component;
    }
    return nullptr;
}

void CCharacterComponent::FreeComponent(CCharacterComponent* component) {
    component->~CCharacterComponent();
    // TODO: ObjectFree()
}

void CCharacterComponent::ValidateComponentData(ComponentData* data, COMPONENT_CONTEXT context) {
}

CCharacterComponent::CCharacterComponent() {
}

CCharacterComponent::~CCharacterComponent() {
}

void CCharacterComponent::SetRandomSkin(COMPONENT_CONTEXT context) {
}

void CCharacterComponent::SetRandomHairColor(COMPONENT_CONTEXT context) {
}

void CCharacterComponent::SetRandomHairStyle(COMPONENT_CONTEXT context) {
}

void CCharacterComponent::SetRandomFace(COMPONENT_CONTEXT context) {
}

void CCharacterComponent::SetRandomFacialFeature(COMPONENT_CONTEXT context) {
}

bool CCharacterComponent::Init(ComponentData* data, const char* a3) {
    this->m_data = *data;
    return false;
}

bool CCharacterComponent::RenderPrep(int32_t a2) {
    // TODO: Proper implementation
    GeosRenderPrep(a2);
    return false;
}

void CCharacterComponent::GeosRenderPrep(int32_t a2) {

    bool eyeGlowFlag = false;

    // Death Knight
    if (this->m_data.m_info.classID == 6) {
        eyeGlowFlag = true;
    } else {
        // TODO: ComponentGetSectionsRecord
    }

    this->m_data.m_model->SetGeometryVisible(0, 2000, 0);
    this->m_data.m_model->SetGeometryVisible(0, 0, 1);
    for (int i = 0; i < 19; ++i) {
        if (i == 17 && eyeGlowFlag) {
            this->m_data.m_model->SetGeometryVisible(1703, 1703, 1);
        } else {
            this->m_data.m_model->SetGeometryVisible(this->m_data.m_geosets[i], this->m_data.m_geosets[i], 1);
        }
    }
}

void CCharacterComponent::GetInfo(CHARACTER_CREATE_INFO* info) {
    if (info) {
        *info = this->m_data.m_info;
    }
}
