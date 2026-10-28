// CKCrumblyZoneCpnt.h - the particle emitters of a crumbly zone (key 0xc6, vtable 0xb25690, size 0x10).
// Original unit: CKCrumblyZoneCpnt.cpp. XXL2: K/KMeca/CrumblyZone/CKCrumblyZoneCpnt.h (IKMecaCpnt base,
// m_apImpulseEmitters, m_ui32NbImpEmitters, m_bResetDone): the same members and Load order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKMecaCpntBase.h"

class CKCrumblyZoneCpnt : public IKMecaCpnt {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x3)
    DOTD_DECLARE_FACTORIES(CKCrumblyZoneCpnt)

    // XXL2 CKCrumblyZoneCpnt::SImpulsePart (m_pImpulsePart, m_ui32ImpulseNumFrame). The array constructor
    // in the Load sets the second word to 0 only.
    struct SImpulsePart {
        SImpulsePart() { m_ui32ImpulseNumFrame = 0; }
        IKSerializable* m_pImpulsePart;  // +0x00 XXL2 CParticlesNodeFx*
        uint32_t m_ui32ImpulseNumFrame;  // +0x04
    };

    CKCrumblyZoneCpnt() {}  // 0x00402250 CKCrumblyZoneCpnt_Create (0x401b60 Construct): the base, the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004022a8 CKCrumblyZoneCpnt_Load
    void Vf58() override { m_unk0d = 0; }  // vt+0x58 0x9c10f0 CKCrumblyZoneCpnt_vf58

    SImpulsePart* m_apImpulseEmitters;  // +0x04 OperatorNewArray (count cookie in front)
    uint32_t m_ui32NbImpEmitters;       // +0x08
    uint8_t m_bResetDone;               // +0x0c not set by the constructor or the Load
    uint8_t m_unk0d;                    // +0x0d runtime (Vf58 clears it)
    uint8_t m_pad0e[2];
};
DOTD_ASSERT_SIZE(CKCrumblyZoneCpnt::SImpulsePart, 0x8);
DOTD_ASSERT_SIZE(CKCrumblyZoneCpnt, 0x10);
DOTD_ASSERT_OFFSET(CKCrumblyZoneCpnt, m_apImpulseEmitters, 0x04);
DOTD_ASSERT_OFFSET(CKCrumblyZoneCpnt, m_ui32NbImpEmitters, 0x08);
