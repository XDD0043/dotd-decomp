// CKGrpMeca.h - the base of the mechanism groups (key 0x2c4, vtable 0xb24f80, size 0x40). Original unit:
// CKGrpMeca.cpp (0x3f8130 the constructor, Ghidra CKGrpS08Meca_ConstructBase_maybe; 0x3f8778 Load). XXL2:
// K/KMeca/Group/CKGrpMeca.h; its last member m_apMecaCpnts (TVector<IKMecaCpnt*, 10>) is the vector the
// Load reads (same growth step). +0x2c/+0x30 are not set by the constructor or the Load.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/util/TVector.h"

class CKGrpMeca : public IKGroup<IKHook> {
public:
    // 0x003f8130 CKGrpS08Meca_ConstructBase_maybe (CKGrpMeca's constructor): the vector null, 10, 0 and the
    // priority word 0x80000027.
    CKGrpMeca() {
        m_apMecaCpnts = {nullptr, 10, 0};
        m_ui32Priority = 0x80000027u;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x003f8778 CKGrpMeca_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x003f82f8 CKGrpMeca_PostLoad
    void Start() override;  // vt+0x50 0x003f81c0 CKGrpMeca_vf50

    void* m_pUnk2c;                              // +0x2c not set by the constructor or the Load; PostLoad: 300 words
    uint16_t m_unk30;                            // +0x30 runtime (Start: 0)
    uint8_t m_unk32;                             // +0x32 runtime (Start: 0)
    uint8_t m_pad33;
    TVector<IKSerializable*, 10> m_apMecaCpnts;  // +0x34 XXL2 IKMecaCpnt* (LVL010: a CKCrumblyZoneCpnt ref)
};
DOTD_ASSERT_SIZE(CKGrpMeca, 0x40);
DOTD_ASSERT_OFFSET(CKGrpMeca, m_pUnk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKGrpMeca, m_apMecaCpnts, 0x34);
