// CLensFlareFx.h - the lens flare screen effect (key 0x1b4d, vtable 0xb176f8, size 0x30). Original unit:
// CLensFlareFx.cpp (0xb3170-0xb4808). Not in XXL2. Its Load is IScreenFx's (0x9a0bc8: IRendableObject_Load).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/fx/IScreenFx.h"

class CLensFlareFx : public IScreenFx {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x6d)
    DOTD_DECLARE_FACTORIES(CLensFlareFx)

    CLensFlareFx();                  // 0x000b3570 CLensFlareFx_Create (inlined)
    ~CLensFlareFx() override {}      // STUB(C1.6): 0x9a0bf0 / 0x9a0c10
    // vt+0x08 0x9a0b68
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x1b4d || key == 0xacd || key == 0xa8d || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x009a0bc8 CLensFlareFx_Load
    int32_t GetSerializationFlags() override { return 2; }  // vt+0x34 0x9a0ac8
    void UpdateAndExtract(float, RenderQueue**, IKTime*, RwCamera*, int32_t) override {}                     // vt+0x58 0xb3838  STUB(C1.4)
    void Render() override {}                               // vt+0x5c 0xb43b8  STUB(C1.4)

    uint32_t m_unk18[6];  // +0x18 not written by the constructor or Load (PostLoad clears +0x18)
};
DOTD_ASSERT_SIZE(CLensFlareFx, 0x30);
