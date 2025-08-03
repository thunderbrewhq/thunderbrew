#include "gameui/CGTooltip.hpp"

CGTooltip::CGTooltip(CSimpleFrame* parent) : CSimpleFrame(parent) {
}

CSimpleFrame* CGTooltip::Create(CSimpleFrame* parent) {
    // TODO:  Data = CDataAllocator__GetData(0, ".?AVCGTooltip@@", -2);

    auto m = SMemAlloc(sizeof(CGTooltip), __FILE__, __LINE__, 0);
    return m ? (new (m) CGTooltip(parent)) : nullptr;
}
