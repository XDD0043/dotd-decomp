// CContainer2d.h - a named group of 2D nodes in two scenes, the buttons and the others (key 0x4cd,
// vtable 0xb15ab0, size 0x38). Original unit: CContainer2d.cpp (0x600b0-0x61ab8). XXL2:
// K/KModules/KGL/2d/CContainer2d.h, the same members in the same order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/ui/IKNode2d.h"

class CContainer2d : public IKNode2d {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x13)
    DOTD_DECLARE_FACTORIES(CContainer2d)

    CContainer2d();  // inlined in 0x000614f0 CContainer2d_Create (out-of-line copy 0x60c70 unreferenced)
    ~CContainer2d() override {}                             // vt+0x00 / +0x04  0x997ae8 / 0x997aa0
    int32_t IsKindOfClass(uint32_t key) override {          // vt+0x08 0x997a78
        return key == 0x4cd || key == 0x24d || key == 0xc;
    }

    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x000611b0 CContainer2d_Load
    const char* GetName() override { return m_szName; }     // vt+0x4c 0x601d8
    // vt+0x80 0x00061820 CContainer2d_Scale: Scale on every node of the button scene, then of the others.
    void Scale(const CVector2& scale) override;
    // vt+0x58 0x00060bf0 CContainer2d_OnEvent_maybe: the event to both scenes.
    void RecursiveNodeReach(uint8_t what, void* data) override;
    // vt+0x84 0x00060db8 DrawUIContainerChildScenes: when enabled, both scenes' Render (+0x30 first)
    // inside a pushed Rt2d CTM.
    void Render(IKTime* frameClock) override;

    char* m_szName;                       // +0x28 Mem_AllocAligned16(length + 1); null for a negative length
    IKSerializable* m_pButtonObjects;     // +0x2c CScene2d (a reference)
    IKSerializable* m_pNonButtonObjects;  // +0x30 CScene2d (a reference)
    uint8_t m_bButtonLoop;                // +0x34 (+0x35..+0x37: padding the original never writes)
};
DOTD_ASSERT_SIZE(CContainer2d, 0x38);
DOTD_ASSERT_OFFSET(CContainer2d, m_szName, 0x28);
DOTD_ASSERT_OFFSET(CContainer2d, m_pButtonObjects, 0x2c);
DOTD_ASSERT_OFFSET(CContainer2d, m_pNonButtonObjects, 0x30);
DOTD_ASSERT_OFFSET(CContainer2d, m_bButtonLoop, 0x34);
