// IKButton2d.h - the base of the 2D buttons (unregistered key 0x2cd, vtable 0xb15e58, size 0x28: no members of its
// own; XXL2: K/KModules/KGL/2d/IKButton2d.h, Select / Deselect). The buttons are CBillboardButton2d and
// CColorTextButton2d; no game file holds either (outputs/remake/kp3-class-usage.json). Its functions are in the
// CBillboard2d_2.cpp range (0x67cd8..0x67e48). m_baFlags bit 1 = enabled, bit 2 = selected; m_ui8Type 2 = a button.
#pragma once
#include <cstdint>

#include "k2000/ui/IKNode2d.h"

class IKButton2d : public IKNode2d {
public:
    ~IKButton2d() override;                         // vt+0x00 / +0x04 0x9983d8 / 0x998390
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x998368
        return key == 0x2cd || key == 0x24d || key == 0xc;
    }
    // vt+0x10 0x00067ce8 IKButton2d_ClearReferences (Ghidra; IKButton2d_Destroy): IKNode2d's (0x69d68).
    void Destroy() override;
    int32_t GetClassType() override { return kCategoryGraphical; }  // vt+0x14 0x998358
    int32_t GetClassID() override { return 0xb; }                   // vt+0x18 0x998360
    // vt+0x2c 0x00067d38 IKButton2d_Load: IKNode2d's, 1.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x68 0x00067e48 IKButton2d_Hide (IKNode2d's Disable slot): the enabled bit cleared, then Deselect (vt+0x8c).
    void Disable() override;
    // vt+0x88 0x00067d78 Button2d_Select_maybe (XXL2 Select): an enabled button gets the selected bit, and every
    // other button of its scene (type 2, from the owner's first child along m_pNext) is deselected (vt+0x8c).
    virtual void Select();
    // vt+0x8c 0x00067d60 Button2d_Deselect_maybe (XXL2 Deselect): the selected bit cleared.
    virtual void Deselect();
    // 0x00067cd8 Button2d_IsSelected_maybe: the selected bit (m_baFlags bit 2).
    uint8_t IsSelected() const;
};
DOTD_ASSERT_SIZE(IKButton2d, 0x28);

// 0x00067cd8 Button2d_IsSelected_maybe (unit CBillboard2d_2.cpp): bit 2 of the node's flags (+0x05).
inline uint8_t Button2d_IsSelected(const IKNode2d* node) { return static_cast<uint8_t>((node->m_baFlags >> 2) & 1u); }
