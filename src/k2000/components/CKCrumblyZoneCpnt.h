// CKCrumblyZoneCpnt.h - the particle emitters of a crumbly zone (key 0xc6, vtable 0xb25690, size 0x10).
// Original unit: CKCrumblyZoneCpnt.cpp. XXL2: K/KMeca/CrumblyZone/CKCrumblyZoneCpnt.h (IKMecaCpnt base,
// m_apImpulseEmitters, m_ui32NbImpEmitters, m_bResetDone): the same members and Load order.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKMecaCpntBase.h"

class CKCrumblyZoneCpnt : public IKMecaCpnt {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x3)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c1098
        return key == 0xc6 || key == 0xa06 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKCrumblyZoneCpnt)

    // A queued placement of an impulse emitter (0x2c bytes, from the FreeListPool 0x00ceaab4, whose free list links
    // through +0x00; here new / delete): QueueInstanceTransform's arguments.
    struct ImpulseRequest {
        CVector3 m_position;      // +0x00
        CVector3 m_direction;     // +0x0c normalised (or null)
        CVector3 m_emitterSize;   // +0x18 the zone's +0xcc
        float m_fSpeed;           // +0x24 the force along the direction (0: none)
        ImpulseRequest* m_pNext;  // +0x28 new requests go to the front
    };
    // XXL2 CKCrumblyZoneCpnt::SImpulsePart (m_pImpulsePart, m_ui32ImpulseNumFrame). The array constructor
    // in the Load sets the second word to 0 only; in DotD it is the emitter's queued placements.
    struct SImpulsePart {
        SImpulsePart() { m_pRequests = nullptr; }
        IKSerializable* m_pImpulsePart;  // +0x00 XXL2 CParticlesNodeFx*
        ImpulseRequest* m_pRequests;     // +0x04 XXL2 m_ui32ImpulseNumFrame's place
    };

    CKCrumblyZoneCpnt() {}  // 0x00402250 CKCrumblyZoneCpnt_Create (0x401b60 Construct): the base, the vtable

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004022a8 CKCrumblyZoneCpnt_Load
    // vt+0x30 0x004018d8 CKCrumblyZoneCpnt_PostLoad: CKMecaCpnt_PostLoad 0x3f7a28 (vt+0x50, empty here), then 1.
    int32_t PostLoad(int32_t type) override {
        IKMecaCpnt::PostLoad(type);
        return 1;
    }
    void Vf50() override {}  // vt+0x50 0x9c10e0 CKCrumblyZoneCpnt_vf50 (empty)
    void Vf54() override {}  // vt+0x54 0x9c10e8 CKCrumblyZoneCpnt_vf54 (empty)
    void Vf58() override { m_unk0d = 0; }  // vt+0x58 0x9c10f0 CKCrumblyZoneCpnt_vf58
    // vt+0x10 0x00401950 CKCrumblyZoneCpnt_Destroy: the base's (vt+0x54), then every emitter's queued placements given
    // back to their pool (last emitter first; here deleted), the emitter array deleted and cleared.
    void Destroy() override;
    // vt+0x1c 0x00401d20 CKCrumblyZoneCpnt_MessageProc: 0x902 (the reset) resets every crumbly zone (0x1982) of the meca
    // group (the game manager's +0x0c) that is in sector 0 (CKHkCrumblyZone_ResetStageRecursive_maybe), then 0; any
    // other message 1. (vt+0x24 0x401928 RecursiveRegistration: the base's 0x3f7a70, 1; vt+0x40 0x401d18 GetInfo: 1,
    // the defaults.)
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x60 0x00401e58 CKCrumblyZoneCpnt_vf60 (CKGrpMeca_UpdateMembers_maybe, every frame): each impulse emitter with
    // a queued placement takes the newest one (placed, turned along the direction with the force, its emitter size,
    // emitting); then the path-blocking step +0x0d moves on (1 / 3 -> 2, 2 -> 0).
    void Vf60(IKTime* clock) override;
    // 0x00401bd0 CKCrumblyZoneCpnt_QueueInstanceTransform_maybe: a placement queued on impulse emitter `index` (none
    // below 0 or without a particle node).
    void QueueInstanceTransform(float speed, int32_t index, const CVector3* position, const CVector3* direction,
                                const CVector3* emitterSize);

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
