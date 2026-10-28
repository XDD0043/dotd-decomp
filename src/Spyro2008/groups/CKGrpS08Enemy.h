// CKGrpS08Enemy.h - DotD's enemy group (key 0xa44, vtable 0xb215f8, size 0x290). Original unit:
// CKGrpS08Enemy.cpp (Spyro2008/groups/CKGrpS08Enemy_2.cpp: 0x269118 Load, 0x267630 Create). No XXL2 class
// of this name; the names are placeholders (reference classes from the LVL010 live dump, _maybe).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKGrpEnemy.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKGrpS08Enemy : public IKGrpEnemy {
public:
    DOTD_CLASS_KEY(kCategoryGroup, 0x29)
    DOTD_DECLARE_FACTORIES(CKGrpS08Enemy)

    // Three floats and a count: the Load pushes 1, 2, 3 at the count, then reads the three floats over them.
    struct SFloat3List {
        float m_af[3];         // +0x00
        uint32_t m_ui32NbElt;  // +0x0c
    };

    // 0x00267630 CKGrpS08Enemy_Create (after the IKGrpEnemy constructor), in its order.
    CKGrpS08Enemy() {
        m_vUnk164 = {nullptr, 1, 0};
        m_vUnk180 = {nullptr, 1, 0};
        m_vUnk19c = {nullptr, 1, 0};
        m_vUnk1b0 = {nullptr, 1, 0};
        m_aFloat3Lists[3].m_ui32NbElt = 0;
        m_aFloat3Lists[0].m_ui32NbElt = 0;
        m_aFloat3Lists[1].m_ui32NbElt = 0;
        m_aFloat3Lists[2].m_ui32NbElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00269118 CKGrpS08Enemy_Load
    void Start() override;                              // vt+0x50 0x00268eb8 CKGrpS08Enemy_Start (C2.2)
    uint8_t GetNbAnimLayers(uint8_t kind) override;                      // vt+0x108 0x009bb4f8
    uint8_t GetNbTrailNodes(uint8_t kind) override;                      // vt+0x128 0x009bb570
    uint8_t GetNbAnimLayerSlots(uint8_t kind, uint8_t layer) override;   // vt+0x130 0x009bb590

    CTriggerStarter m_aTriggers[5];       // +0x124 Ghidra aEvt124; loaded from the first to the last
    uint32_t m_unk14c[(0x164 - 0x14c) / 4];  // +0x14c..+0x160
    TVector<uint32_t, 1> m_vUnk164;       // +0x164 not loaded
    uint32_t m_unk170[3];                 // +0x170..+0x178
    IKSerializable* m_pUnk17c;            // +0x17c reference (LVL010: a CKCommonBaseGroup)
    TVector<IKSerializable*, 1> m_vUnk180;  // +0x180 references, at most 9 kept
    uint32_t m_unk18c;                    // +0x18c
    IKSerializable* m_pUnk190;            // +0x190 reference (LVL010: a CKGrpS08WeaponPool)
    uint32_t m_unk194;                    // +0x194
    IKSerializable* m_pUnk198;            // +0x198 reference (LVL010: a CKCommonBaseGroup)
    TVector<uint32_t, 1> m_vUnk19c;       // +0x19c the Load only gives it a block
    float m_unk1a8;                       // +0x1a8
    IKSerializable* m_pUnk1ac;            // +0x1ac (LVL010: a CKGrpS08ShieldPool; not loaded)
    TVector<uint32_t, 1> m_vUnk1b0;       // +0x1b0 not loaded
    uint8_t m_unk1bc;                     // +0x1bc a byte (Start clears it)
    uint8_t m_pad1bd[3];
    uint32_t m_unk1c0[4];                 // +0x1c0..+0x1cc
    uint32_t m_unk1d0[3];                 // +0x1d0..+0x1d8
    uint32_t m_unk1dc;                    // +0x1dc
    float m_unk1e0;                       // +0x1e0 Start: 20.0f (TOC 0x518)
    IKSerializable* m_pUnk1e4;            // +0x1e4 reference (LVL010: a CKQuakeCameraLauncher)
    uint32_t m_unk1e8;                    // +0x1e8
    IKSerializable* m_pUnk1ec;            // +0x1ec reference (LVL010: a CKS08AccessoryManager)
    float m_unk1f0;                       // +0x1f0 Start: 0.3f (TOC 0x51c)
    uint32_t m_unk1f4;                    // +0x1f4
    SFloat3List m_aFloat3Lists[4];        // +0x1f8 / +0x208 / +0x218 / +0x228
    float m_unk238[11];                   // +0x238..+0x260
    IKSerializable* m_pUnk264;            // +0x264 reference (LVL010: a CKCameraEventCpnt)
    float m_unk268[10];                   // +0x268..+0x28c
};
static_assert(CKGrpS08Enemy::kClassKey == 0xa44, "key");
DOTD_ASSERT_SIZE(CKGrpS08Enemy, 0x290);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_aTriggers, 0x124);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_vUnk164, 0x164);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_pUnk17c, 0x17c);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_vUnk180, 0x180);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_pUnk190, 0x190);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_unk194, 0x194);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_pUnk198, 0x198);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_vUnk19c, 0x19c);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_vUnk1b0, 0x1b0);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_pUnk1e4, 0x1e4);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_pUnk1ec, 0x1ec);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_aFloat3Lists, 0x1f8);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_unk238, 0x238);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_pUnk264, 0x264);
DOTD_ASSERT_OFFSET(CKGrpS08Enemy, m_unk268, 0x268);
