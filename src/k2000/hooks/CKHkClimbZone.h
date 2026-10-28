// CKHkClimbZone.h - a zone the hero climbs (key 0x1602, vtable 0xb27120, size 0xc4). Original unit:
// CKHkClimbZone.cpp. No XXL2 class.
//
// step 6 (CLIMB): the zone's box (+0x20, a CKOBB with the half sizes +0x24) hangs under the zone's node (+0x1c)
// while the zone's sector is active (OnActivate / OnDeactivate). The node's frame gives the climb surface: its
// position (the bottom), its at axis (the wall's normal for kind 2, the ray of the attach probe) and, for kinds 0 / 1,
// its up axis; +0x30 is the climbable extent from the bottom (along y for kind 2, along the at axis otherwise). The
// climbers (heroes) are recorded in +0xb4 with their distance range, so two climbers keep apart
// (ResolveClimberOverlap). LVL010 has only kind 2 zones (walls).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"
#include "k2000/math/CMatrix34.h"

class CKHkClimbZone : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x58)
    DOTD_DECLARE_FACTORIES(CKHkClimbZone)

    // 0x009c3ee0 CKHkClimbZone_IsKindOfClass (vt+0x08): the zone (0x1602), CKHkActorBase (0xd82), IKHook (2 / 0x2fe),
    // IKUpdatable (0x3fe) and IKSerializable (0xc). The hero's HandleClimbZoneContact tests the box owner with 0x1602.
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x1602 || key == 0xd82 || key == 2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }

    // 0x00457578 CKHkClimbZone_Construct (inlined in 0x00458698 CKHkClimbZone_Create): the +0xb4 vector
    // empty with a capacity of 1.
    // One climber record of the +0xb4 list (0x10 bytes): the climber's key and its distance to the zone with the
    // clamped range (the original's AddOrUpdateClimber writes them in the order key, +0xc, +8, +4).
    struct Climber {
        int32_t m_key;     // +0x00 the climber (a CKHkS08Hero; the original stores the PS3 pointer)
        float m_fDist;     // +0x04 distance from the climb surface along it
        float m_fHi;       // +0x08 min(dist + dt / 2, m_fUnk30)
        float m_fLo;       // +0x0c max(dist - dt / 2, 0)
    };
    CKHkClimbZone() {
        m_vUnkB4.m_pBlock = nullptr;
        m_vUnkB4.m_ui32NbElt = 1;
        m_vUnkB4.m_ui32NbUsedElt = 0;
    }
    ~CKHkClimbZone() override {}

    void Destroy() override;                                // vt+0x10 0x004574f0 CKHkClimbZone_Destroy
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x004578b8 CKHkClimbZone_MessageProc
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x004595d0 CKHkClimbZone_Load
    int32_t PostLoad(int32_t type) override;                // vt+0x30 0x00457438 CKHkClimbZone_PostLoad
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x00457808 CKHkClimbZone_SetDefaultState
    void Start() override;                        // vt+0x50 0x004573e0 CKHkClimbZone_Start
    void Restart() override;                      // vt+0x54 0x00459520 CKHkClimbZone_Restart
    void Stop() override {}                       // vt+0x68 0x004573b8 CKHkClimbZone_Stop (CKHkActorBase's: empty)
    void Pause() override {}                      // vt+0x70 0x00457390 CKHkClimbZone_Pause (KStub_Nop_3f6e58)
    void Resume() override {}                     // vt+0x78 0x00457368 CKHkClimbZone_Resume (KStub_Nop_3f6e60)
    void Update(IKTime* frameClock) override;     // vt+0x7c 0x00457d68 CKHkClimbZone_Update
    void VfA0() override;                         // vt+0xa0 0x00459290 CKHkClimbZone_OnActivate
    void VfA4() override;                         // vt+0xa4 0x00457678 CKHkClimbZone_OnDeactivate
    void ApplyStatePreset(int32_t state) override;  // vt+0xc8 0x004579d0 CKHkClimbZone_vfC8
    void SetEnabled(int32_t enabled) override;      // vt+0xcc 0x00457c50 CKHkClimbZone_SetCollisionEnabled_maybe

    // 0x00458e98 CKHkClimbZone_AddOrUpdateClimber_maybe (not virtual): a zone that is on (bit 16) takes `active` as
    // its bit 15 (firing the +0x68 trigger when it just became active), and, for a non-zero climber key, records
    // the climber's distance range (the climber's position: `position`, or the zone's own when it is the zero
    // vector). `dt` widens the range by half of it each way.
    void AddOrUpdateClimber(float dt, uint32_t active, const CVector3* position, int32_t climberKey);
    // ---- step 6 CLIMB ----
    uint8_t GetLinkedObjectFlagC23();                       // 0x00456bc8 (_maybe: +0x38's flag bit 23)
    IKSerializable* GetGroundByIndex(uint8_t index);        // 0x00456bf0 (_maybe: +0x38's ground list)
    // 0x00456cc0 CKHkClimbZone_RaycastAttachPoint_maybe: the climb surface hit from `point` (moved 0.5 back along the
    // probe's axis, in place) by a 5-unit ray; the hit into `out`, the attach matrix (position, basis) into `matrix`
    // (may be null). `out` is left alone without a hit. Bit 20 marks a probe done.
    CVector3* RaycastAttachPoint(CVector3* out, CVector3* point, CMatrix34* matrix);
    void RemoveClimber(int32_t climberKey);                 // 0x00457180 (_maybe)
    uint8_t IsAboveBottom(const CVector3* position);        // 0x00457740 (_maybe)
    uint8_t IsBelowTop(const CVector3* position);           // 0x00457768 (_maybe)
    // 0x00457ad8 CKHkClimbZone_ClampMoveToExtent_maybe: the part of `move` along the climb axis that keeps `position`
    // within the extent.
    CVector3 ClampMoveToExtent(const CVector3* position, const CVector3* move);
    // 0x00458708 CKHkClimbZone_ResolveClimberOverlap_maybe: `position` pushed out of the other climbers' ranges into
    // `out`; 0 when no place is left.
    uint8_t ResolveClimberOverlap(const CVector3* position, CVector3* out, int32_t climberKey);
    // 0x00458a88 CKHkClimbZone_GetAttachMatrix_maybe: the attach point of `position` clamped to the extent (cached in
    // +0x78 / +0x84 / +0x90) and the attach matrix; with a climber key the other climbers are kept apart. 0 refused.
    uint8_t GetAttachMatrix(const CVector3* position, CMatrix34* matrix, int32_t climberKey);
    // 0x004591e0 CKHkClimbZone_AttachClimberIfValid_maybe: GetAttachMatrix, then the climber recorded (active).
    uint8_t AttachClimberIfValid(float dt, const CVector3* position, CMatrix34* matrix, int32_t climberKey);
    // DOTD: the climber key of a hero (the original stores the hero's PS3 address in the record's word). Native records
    // keep a small handle instead, so the x64 build fits the 32-bit word.
    static int32_t ClimberKey(const void* climber);
    // DOTD: the zone's node frame and box frame (+0x1c / +0x20, each a CSGMovable's RwFrame) as matrices: the original
    // reads the frames' words at +0x10 (modelling) and +0x50 (LTM).
    const CMatrix34& NodeLtm() const;
    const CMatrix34& NodeModelling() const;
    const CMatrix34& BoxLtm() const;

    IKSerializable* m_pUnk20;                  // +0x20 a CKOBB (struct draft: the climb volume_maybe)
    float m_afUnk24[3];                        // +0x24 the box's half sizes (OnActivate copies them into the box)
    float m_fUnk30;                            // +0x30 the climbable extent from the bottom
    uint8_t m_unk34;                           // +0x34 the kind: 2 a wall (y), 0 / 1 along the node's at axis
    uint8_t m_pad35[3];
    IKSerializable* m_pUnk38;                  // +0x38 a moving body the zone pushes (+0x1ac..+0x1c4) and grounds (+0x20 / +0x24)
    IKSerializable* m_pUnk3C;                  // +0x3c its push's scale source (+0x100)
    float m_fUnk40;                            // +0x40
    IKSerializable* m_pUnk44;                  // +0x44 a CKHkS08FogHorn (its charge ratio scales the push)
    float m_fUnk48;                            // +0x48
    IKSerializable* m_pUnk4C;                  // +0x4c (the hero's +0x16a0 while it is in the zone)
    IKSerializable* m_pUnk50;                  // +0x50 a CGround (struct draft): the kind 2 attach is 0.25 lower
    IKSerializable* m_pUnk54;                  // +0x54 a CKHkCrumblyZone
    float m_fUnk58;                            // +0x58 the time a climber may stay (< 0: no limit)
    float m_fUnk5C;                            // +0x5c the time the zone stays off (< 0: no limit)
    IKSerializable** m_apUnk60;                // +0x60 Mem_AllocAligned16, m_ui8NbUnk60 references
    uint8_t m_ui8NbUnk60;                      // +0x64
    uint8_t m_pad65[3];
    CTriggerStarter m_tsUnk68;                 // +0x68 a climber arrives
    CTriggerStarter m_tsUnk70;                 // +0x70 the last climber leaves
    CVector3 m_vUnk78;                         // +0x78 the position of the cached attach probe
    CVector3 m_vUnk84;                         // +0x84 the cached attach point
    CVector3 m_vUnk90;                         // +0x90 the cached attach matrix's up row
    CVector3 m_vUnk9C;                         // +0x9c the push applied to +0x38 (runtime)
    CVector3 m_vUnkA8;                         // +0xa8 (runtime)
    TVector<Climber, 1> m_vUnkB4;              // +0xb4 PostLoad gives it a 16-byte block
    float m_fUnkC0;                            // +0xc0 the zone's timer (+0x58 / +0x5c)
};
DOTD_ASSERT_SIZE(CKHkClimbZone, 0xc4);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_pUnk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_afUnk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_fUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_pUnk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_fUnk40, 0x40);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_fUnk48, 0x48);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_pUnk54, 0x54);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_fUnk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_apUnk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_ui8NbUnk60, 0x64);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_tsUnk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_tsUnk70, 0x70);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_vUnk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_vUnk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_vUnk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_vUnk9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_vUnkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_vUnkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkClimbZone, m_fUnkC0, 0xc0);
