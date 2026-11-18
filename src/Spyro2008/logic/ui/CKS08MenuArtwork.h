// CKS08MenuArtwork.h - the "Menu Artwork" screen (key 0x840c, vtable 0xb2d8e8, size 0xb8 from 0x56d228 CKS08MenuArtwork_Create). DotD only.
// Original unit: CKS08MenuArtwork.cpp (0x56cd80-0x56d6b8). No game file holds one (C2.8 port-rest R11): every slot but
// the accessors is CKMenuBase114c's.
#pragma once
#include <cstdint>

#include "Spyro2008/logic/CKMenuBase114c.h"
#include "k2000/core/Layout.h"

class CKS08MenuArtwork : public CKMenuBase114c {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x210)
    DOTD_DECLARE_FACTORIES(CKS08MenuArtwork)

    CKS08MenuArtwork() {}  // 0x56d228 CKS08MenuArtwork_Create: the CKMenuBase114c part only
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ca790
        return key == 0x840c || key == 0x114c || key == 0x730c || key == 0xc;
    }
    // vt+0x2c 0x56cf00 CKS08MenuArtwork_Load: CKMenuBase114c's (0x51a160), then 1.
    int32_t Load(IKFile* file, int32_t type) override {
        CKMenuBase114c::Load(file, type);
        return 1;
    }
    // vt+0x24 0x56cf50 CKS08MenuArtwork_RecursiveRegistration / vt+0x10 0x56cf78 CKS08MenuArtwork_Destroy: CKMenuBase114c's
    // (inherited).
    const char* GetMenuName() override { return "Menu Artwork"; }                        // vt+0xb8 0x9ca7e0 (0x00acbb70)
    uint8_t VfBC() override { return 1; }                                                // vt+0xbc 0x9ca818
    IKSerializable** VfC0() override { return m_apMessageOuts; }                         // vt+0xc0 0x9ca820
    uint8_t VfC4() override { return 6; }                                                // vt+0xc4 0x9ca7f0
    IKSerializable** VfC8() override { return m_apMessageIns; }                          // vt+0xc8 0x9ca7f8
    uint8_t* VfCC() override { return m_abMessageInFlags; }                              // vt+0xcc 0x9ca808
    int32_t GetMenuId() override { return 0x1; }                                         // vt+0xe0 0x9ca7e8

    IKSerializable* m_apMessageIns[6];           // +0x94
    uint8_t m_abMessageInFlags[6];               // +0xac MessageProc sets one per VfC8 entry
    uint8_t m_unkb2[2];
    IKSerializable* m_apMessageOuts[1];          // +0xb4
};
static_assert(CKS08MenuArtwork::kClassKey == 0x840c, "key");
DOTD_ASSERT_SIZE(CKS08MenuArtwork, 0xb8);
DOTD_ASSERT_OFFSET(CKS08MenuArtwork, m_apMessageIns, 0x94);
DOTD_ASSERT_OFFSET(CKS08MenuArtwork, m_abMessageInFlags, 0xac);
DOTD_ASSERT_OFFSET(CKS08MenuArtwork, m_apMessageOuts, 0xb4);
