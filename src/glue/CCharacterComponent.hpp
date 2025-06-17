#ifndef GLUE_C_CHARACTER_COMPONENT_HPP
#define GLUE_C_CHARACTER_COMPONENT_HPP

#include "net/Types.hpp"
#include "gx/Types.hpp"
#include <storm/Array.hpp>

class CSimpleModelFFX;
class CM2Model;
class CVar;

class ComponentData {
    public:
    ComponentData();
    explicit ComponentData(const CHARACTER_INFO& info);

    public:
    CHARACTER_CREATE_INFO m_info;
    CM2Model* m_model;
    uint32_t m_unkFlag;
};

class CCharacterComponent {
    public:
    enum COMPONENT_CONTEXT
    {
        DEFAULT_CONTEXT = 0,
        CONTEXT_1,
        CONTEXT_2,
        CONTEXT_3
    };

    public:
    // Static variables
    static CVar* g_componentTextureLevelVar;
    static CVar* g_componentThreadVar;
    static CVar* g_componentCompressVar;

    static uint32_t* s_heap;

    // Static functions
    static void Initialize();
    static void Initialize(EGxTexFormat format, uint32_t mipLevels, int32_t useThreads, int32_t useCompression);
    static CCharacterComponent* AllocComponent();
    static void FreeComponent(CCharacterComponent* component);
    static void ValidateComponentData(ComponentData* data, COMPONENT_CONTEXT context = DEFAULT_CONTEXT);

    CCharacterComponent();
    ~CCharacterComponent();

    void SetRandomSkin(COMPONENT_CONTEXT context = DEFAULT_CONTEXT);
    void SetRandomHairColor(COMPONENT_CONTEXT context = DEFAULT_CONTEXT);
    void SetRandomHairStyle(COMPONENT_CONTEXT context = DEFAULT_CONTEXT);
    void SetRandomFace(COMPONENT_CONTEXT context = DEFAULT_CONTEXT);
    void SetRandomFacialFeature(COMPONENT_CONTEXT context = DEFAULT_CONTEXT);

    bool Init(ComponentData* data, const char* a3);
    void RenderPrep(int32_t a2);

    public:
    uint32_t m_handle;
    ComponentData m_data;
};

#endif // GLUE_C_CHARACTER_COMPONENT_HPP
