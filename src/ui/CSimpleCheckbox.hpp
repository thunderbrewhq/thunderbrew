#ifndef UI_C_SIMPLE_CHECKBOX_HPP
#define UI_C_SIMPLE_CHECKBOX_HPP

#include "ui/CSimpleButton.hpp"

class CSimpleCheckbox : public CSimpleButton {
    public:
        // Static variables
        static int32_t s_metatable;
        static int32_t s_objectType;

        // Static functions
        static void CreateScriptMetaTable();
        static int32_t GetObjectType();
        static void RegisterScriptMethods(lua_State* L);

        // Member variables
        int32_t m_checked = 0;
        CSimpleTexture* m_checkedTexture = nullptr;
        CSimpleTexture* m_disabledTexture = nullptr;

        // Virtual member functions
        virtual bool IsA(int32_t type);
        virtual int32_t GetScriptMetaTable();
        virtual void Enable(int32_t enabled);
        virtual void SetChecked(int32_t state, int32_t force);
        virtual int32_t GetChecked();
        virtual void OnClick(const char* btn, int32_t a3);

        // Member functions
        CSimpleCheckbox(CSimpleFrame* parent);
};

#endif
