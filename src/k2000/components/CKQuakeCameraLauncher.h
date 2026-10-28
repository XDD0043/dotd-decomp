// CKQuakeCameraLauncher.h - starts a camera quake (key 0xa86, vtable 0xb1a9f0, size 0x28). Original unit:
// CKQuakeCameraLauncher.cpp (0x1531c8-0x153988). Base: KBase1DCC (0x1dcc). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/CKQuakeCpnt.h"
#include "k2000/logic/KBase1DCC.h"
#include "k2000/math/CMatrix34.h"

class CKQuakeCameraLauncher : public KBase1DCC {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x2a)
    DOTD_DECLARE_FACTORIES(CKQuakeCameraLauncher)

    CKQuakeCameraLauncher() {}  // 0x00153608 CKQuakeCameraLauncher_Create: KBase1DCC, then the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00153750 CKQuakeCameraLauncher_Load
    // vt+0x30 0x001535b8 CKQuakeCameraLauncher_PostLoad: KBase1DCC's, then +0x08 = the camera service's group index of
    // the quake (CKSrvCamera_FindIndexByKey_maybe).
    int32_t PostLoad(int32_t type) override;

    // 0x001533c0 CKQuakeCameraLauncher_Trigger (step 5, FX): with a quake, the camera service starts an idle
    // effect of its group with this launcher as the source (CKSrvCamera_QueueCameraEffect_maybe).
    void Trigger();
    // 0x00153660 CKQuakeCameraLauncher_GetDistanceAttenuation (FX): with +0x24 set 1; otherwise from the distance d between
    // the current camera's position (+0x20) and the source (the attached node's world position, else +0x10): 1 below
    // +0x1c, 0 beyond +0x20, (+0x20 - d) / (+0x20 - +0x1c) between.
    float GetDistanceAttenuation() const;
    IKSerializable* Vf50() override { return m_pQuake; }              // vt+0x50 0x153278
    void Vf54(IKSerializable* object) override {                      // vt+0x54 0x153280
        m_pQuake = static_cast<CKQuakeCpnt*>(object);
    }

    CKQuakeCpnt* m_pQuake;     // +0x04 (Ghidra draft: CKQuakeCpnt*; null in LVL000)
    int32_t m_unk08;           // +0x08 PostLoad: CKSrvCamera_FindIndexByKey_maybe(+0x04), the quake's group index
    IKSerializable* m_unk0c;   // +0x0c an object reference (null in LVL000): the node the source follows (a CSGMovable)
    CVector3 m_unk10;          // +0x10 three byte-swapped words read in one block: the source position
    float m_unk1c;             // +0x1c the full-strength distance
    float m_unk20;             // +0x20 the zero-strength distance
    uint8_t m_unk24;           // +0x24 nonzero: no distance attenuation
    uint8_t m_pad25[3];
};
DOTD_ASSERT_SIZE(CKQuakeCameraLauncher, 0x28);
DOTD_ASSERT_OFFSET(CKQuakeCameraLauncher, m_pQuake, 0x04);
DOTD_ASSERT_OFFSET(CKQuakeCameraLauncher, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKQuakeCameraLauncher, m_unk10, 0x10);
DOTD_ASSERT_OFFSET(CKQuakeCameraLauncher, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKQuakeCameraLauncher, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKQuakeCameraLauncher, m_unk24, 0x24);
