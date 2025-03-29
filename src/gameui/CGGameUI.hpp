#ifndef GAME_UI_CGGAMEUI_HPP
#define GAME_UI_CGGAMEUI_HPP


#include "ui/CSimpleTop.hpp"
#include "ui/CSimpleFrame.hpp"


class CGGameUI {
    public:
        static void InitializeGame();
        static void Initialize();
        static void RegisterFrameFactories();
        static int32_t HandleDisplaySizeChanged(const CSizeEvent& event);

    public:
        static bool m_reloadUI;
        static CSimpleTop* m_simpleTop;
        static CSimpleFrame* m_UISimpleParent;
        static int32_t m_hasControl;
        static int32_t m_screenWidth;
        static int32_t m_screenHeight;
        static float m_aspect;
};

#endif // GAME_UI_CGGAMEUI_HPP
