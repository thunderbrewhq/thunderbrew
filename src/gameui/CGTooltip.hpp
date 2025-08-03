#ifndef GAME_UI_CGTOOLTIP_HPP
#define GAME_UI_CGTOOLTIP_HPP

#include "ui/CSimpleFrame.hpp"
#include "ui/CSimpleTop.hpp"

class CGTooltip : public CSimpleFrame {
    public:
    CGTooltip(CSimpleFrame* parent);

    static CSimpleFrame* Create(CSimpleFrame* parent);
};

#endif // GAME_UI_CGTOOLTIP_HPP
