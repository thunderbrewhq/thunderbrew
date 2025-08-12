#ifndef UI_C_SIMPLE_STATUS_BAR_HPP
#define UI_C_SIMPLE_STATUS_BAR_HPP

#include "ui/CSimpleFrame.hpp"

class CSimpleStatusBar : public CSimpleFrame {
    public:
    // Static variables
    static int32_t s_metatable;
    static int32_t s_objectType;

    // Static functions
    static void CreateScriptMetaTable();
    static int32_t GetObjectType();
    static void RegisterScriptMethods(lua_State* L);

    // Member functions
    CSimpleStatusBar(CSimpleFrame* parent);
    void SetOrientation(uint32_t orientation);
    void SetMinMaxValues(float minValue, float maxValue);
    void SetBarTexture(const char* texFile, int32_t layer);
    void SetBarTexture(CSimpleTexture* texture, int32_t layer);
    void SetRotatesTexture(bool rotates);
    void RunOnMinMaxChanged();
    void RunOnValueChanged();

    // Virtual member functions
    virtual void SetValue(float value);
    virtual void SetStatusBarColor(CImVector& color);
    virtual bool IsA(int32_t type);
    virtual int32_t GetScriptMetaTable();
    virtual ScriptIx* GetScriptByName(const char* name, ScriptData& data);
    virtual void LoadXML(XMLNode* node, CStatus* status);

    // Member variables
    uint32_t m_flags = 0;
    float m_minValue = 0.0f;
    float m_maxValue = 0.0f;
    float m_value = 0.0f;
    CSimpleTexture* m_barTexture = nullptr;
    uint32_t m_orientation = 0;
    ScriptIx m_onValueChanged;
    ScriptIx m_onMinMaxChanged;
};

#endif
