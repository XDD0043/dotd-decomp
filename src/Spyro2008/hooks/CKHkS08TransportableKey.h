// CKHkS08TransportableKey.h - a transportable key hook (key 0x3082, vtable 0xb28c08, size 0x130).
// Original unit: CKHkS08TransportableKey.cpp (0x4ac580-0x4b08d8). No XXL2 class. Base of
// CKHkS08TransportableWeight. Field names are placeholders where the code does not say more.
//
// The state machine (+0x110 table, +0x114 current state, +0x115 count): 0 carried (a carrier holds it), 1 at rest (on
// the ground or a receiver, following a moving ground), 2 falling (thrown or dropped: velocity, gravity, bounces).
#pragma once
#include <cstdint>

#include "Spyro2008/misc/CKHkS08TransportableBase.h"
#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"

class CKSound;

class CKHkS08TransportableKey : public CKHkS08TransportableBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc2)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c53b8
        return key == 0x3082 || key == 0x3002 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe ||
               key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08TransportableKey)

    // 0x004ad128 (Ghidra CKHkS08TransportableWeight_ConstructBase_maybe; it sets this class's vtable
    // 0xb28c08), inlined in 0x004aebf8 CKHkS08TransportableKey_Create: the ground-contact defaults at
    // +0x4c (no CGroundContactDatasIn before it: +0x44 is a loaded reference) and +0x114/+0x115 = 0xff.
    CKHkS08TransportableKey() {
        m_unk115 = 0xff;
        m_unk114 = 0xff;
    }
    // 0x004ad688 CKHkS08TransportableKey_Destructor / 0x004ad610 _BaseDestructor: the vtable, then the base's.
    ~CKHkS08TransportableKey() override {}

    // vt+0x10 0x004ace88 CKHkS08TransportableKey_Destroy: the base's (empty), the two matrices destroyed (RwMatrixDestroy).
    void Destroy() override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004aeee8 CKHkS08TransportableKey_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x004acfe0 CKHkS08TransportableKey_PostLoad
    void Start() override;  // vt+0x50 0x004af358 CKHkS08TransportableKey_Start (C2.2)
    void Restart() override;            // vt+0x54 0x004adb08 CKHkS08TransportableKey_Restart
    // vt+0x68 0x004ace10 CKHkS08TransportableKey_Stop: the base's (0x4ac038, empty).
    void Stop() override {}
    void Update(IKTime* clock) override;  // vt+0x7c 0x004aff00 CKHkS08TransportableKey_Update
    void VfA0() override;                 // vt+0xa0 0x004ad2c8 CKHkS08TransportableKey_OnActivate
    void VfA4() override;                 // vt+0xa4 0x004ad8f0 CKHkS08TransportableKey_OnDeactivate

    uint8_t VfF0(IKSerializable* carrier) override;  // vt+0xf0 0x004afd08 CKHkS08TransportableKey_vfF0
    uint8_t VfF4(IKSerializable* carrier) override;  // vt+0xf4 0x004ad1f8 CKHkS08TransportableKey_vfF4
    uint8_t VfFC(IKSerializable* carrier) override;  // vt+0xfc 0x004ad4b0 CKHkS08TransportableKey_vfFC
    // vt+0x100 0x004ac4e0 CKHkS08TransportableKey_vf100: carried (+0x48 not null).
    uint8_t Vf100() override { return m_pCarrier != nullptr ? 1 : 0; }
    float Vf104() override;  // vt+0x104 0x9c5460 CKHkS08TransportableKey_vf104: the constant 0x00c2bca8
    void Vf108() override;              // vt+0x108 0x004af670 CKHkS08TransportableKey_vf108
    void Vf10C() override;              // vt+0x10c 0x004af510 CKHkS08TransportableKey_vf10C
    uint8_t Vf110() override { return m_unk114 != 0xff ? 1 : 0; }  // vt+0x110 0x004ad1e0
    IKSerializable* Vf114() override { return m_pCarrier; }        // vt+0x114 0x9c5428
    CSGHotSpot* Vf118() override { return reinterpret_cast<CSGHotSpot*>(m_unk34); }  // vt+0x118 0x9c5430
    void ResetStateMachine() override;  // vt+0x11c 0x004af8e8 CKHkS08TransportableKey_ResetStateMachine_maybe
    void Vf120() override { Vf17C(); }  // vt+0x120 0x004ac5d0 CKHkS08TransportableKey_vf120: vt+0x17c
    void Vf124() override;              // vt+0x124 0x004ac580 CKHkS08TransportableKey_vf124
    // vt+0x128 0x004ac500 CKHkS08TransportableKey_vf128: +0x24 = placed, +0xbc = 0.
    void Vf128(uint8_t placed) override {
        m_unk24 = placed;
        m_bLanded = 0;
    }
    void Vf134(IKSerializable* receiver) override;  // vt+0x134 0x004af750 CKHkS08TransportableKey_vf134
    void Vf138(uint8_t value) override { m_bUnkBD = value; }  // vt+0x138 0x9c5438
    uint8_t Vf13C() override { return m_bUnkBD; }              // vt+0x13c 0x9c5440
    void Vf154(const CGroundContactDatasInOut* contact) override;  // vt+0x154 0x004ad3e0 CKHkS08TransportableKey_vf154
    // C2.8 port-rest R10: vt+0xf8 0x004af9a8 _vfF8 (let go), vt+0x160 0x004adcf0 _vf160 (the fall's step), vt+0x168
    // 0x004ae250 _PlayImpactFeedback_maybe (the impact's sound and surface effect by the speed along the normal).
    uint8_t VfF8(IKSerializable* carrier, const CVector3* velocity) override;
    uint8_t Vf160(IKTime* clock) override;
    void Vf168() override;
    void Vf158(uint8_t value) override { m_bUnk10C = value; }  // vt+0x158 0x9c5448
    // vt+0x15c 0x9c5450 CKHkS08TransportableKey_vf15C: the byte +0x10c.
    uint8_t Vf15C() override { return m_bUnk10C; }
    // vt+0x164 0x004ada30 CKHkS08TransportableKey_vf164: the velocity reflected on the normal and scaled by +0xb4; slower
    // than +0xb8 (and +0xb8 not 0): the velocity unchanged.
    void Vf164(CVector3* out, const CVector3* velocity, const CVector3* normal) override;
    // vt+0x16c 0x004ac8f0 / +0x170 0x004ad5b0 / +0x174 0x004ad5e0: the sounds 0 / 1 / 2 of the dictionary +0x44.
    virtual CKSound* Vf16C();
    virtual CKSound* Vf170();
    virtual CKSound* Vf174();
    // vt+0x178 0x004ad198 CKHkS08TransportableKey_vf178: on a ground that is not a slide (property 0x200), its point (the
    // contact's projection) kept in +0xfc.
    virtual void Vf178();
    void Vf17C() override;              // vt+0x17c 0x004ac610 CKHkS08TransportableKey_vf17C
    void Vf180() override;              // vt+0x180 0x004ac888 CKHkS08TransportableKey_vf180
    uint8_t Vf184() override { return 1; }  // vt+0x184 0x9c5458
    // 0x004aca38 CKHkS08TransportableKey_UpdateGroundAttachment_maybe
    void UpdateGroundAttachment(IKTime* clock, const CVector3* point);

    // The states (the table Start builds at +0x118).
    uint8_t State0(IKTime* clock, int32_t phase, uint8_t other);  // 0x004ad0b0 CKHkS08TransportableKey_State0_maybe
    uint8_t State1(IKTime* clock, int32_t phase, uint8_t other);  // 0x004ad6b8 CKHkS08TransportableKey_State1
    uint8_t State2(IKTime* clock, int32_t phase, uint8_t other);  // 0x004ae688 CKHkS08TransportableKey_State2

    // The state engine's handler signature (clock, phase 0 tick / 1 enter / 2 leave, the other state) -> next state.
    using StateFn = uint8_t (CKHkS08TransportableKey::*)(IKTime* clock, int32_t phase, uint8_t other);
    // A handler pair of the table at +0x118 (descriptor, adjust) called natively; not ported: the state as given.
    uint8_t CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other);
    // The machine's switch as the code inlines it: the current state left (phase 2, other `next`), `next` entered (phase 1,
    // other the old state; none when `next` is 0xff).
    void SwitchState(uint8_t next, IKTime* clock, uint8_t leaveOther);
    // One tick (phase 0) and the switch to the state it returns.
    void RunStateMachine(IKTime* clock);

    // +0x24..+0x33 runtime: now CKHkS08TransportableBase's m_unk24..m_unk30 (Start writes +0x25 and +0x28).
    IKSerializable* m_unk34;                   // +0x34 reference (LVL010: a CSGHotSpot or null): the grip (vt+0x118)
    IKSerializable* m_unk38;                   // +0x38 reference (LVL010/LVL040: a CNode or null): a marker shown at rest
    IKSerializable* m_unk3c;                   // +0x3c reference: a CKParticlesEffectFxData (vt+0x17c)
    IKSerializable* m_unk40;                   // +0x40 runtime (PostLoad 0x4acfe0 clears it): an effect (vf180 releases it)
    IKSerializable* m_unk44;                   // +0x44 reference (LVL010: a CKSoundDictionaryID)
    IKSerializable* m_pCarrier;                // +0x48 runtime: the carrier holding it (vt+0x114)
    CGroundContactDatasInOut m_GContactInOut;  // +0x4c
    float m_unk78;                             // +0x78: the probe / wall height
    float m_unk7c;                             // +0x7c: the wall radius
    CVector3 m_vPosition;                      // +0x80 runtime: the position while falling
    CVector3 m_vVelocity;                      // +0x8c runtime
    CVector3 m_unk98;                          // +0x98 one 12-byte read (LVL010: 0, -20, 0: the gravity)
    uint32_t m_unkA4[4];                       // +0xa4..+0xb3 runtime
    float m_unkB4;                             // +0xb4: the bounce factor (vt+0x164)
    float m_unkB8;                             // +0xb8: the bounce's minimum speed (vt+0x164)
    uint8_t m_bLanded;                         // +0xbc runtime: the fall ended (State2)
    uint8_t m_bUnkBD;                          // +0xbd runtime (Start: 1; vt+0x138 / vt+0x13c)
    uint8_t m_padBE[2];
    IKSerializable* m_pDynamicGround;          // +0xc0 runtime: the ground it rests on (an ICollisionMesh)
    CVector3 m_vProbePoint;                    // +0xc4 runtime: FLT_MAX x3 = none
    CVector3 m_vUnkD0;                         // +0xd0 runtime (Start: 0)
    int32_t m_i32PendingState;                 // +0xdc runtime: -1 none; State2 returns it
    uint8_t m_bInStateUpdate;                  // +0xe0 runtime: set while the machine ticks (Update)
    uint8_t m_padE1[3];
    float m_unkE4;                             // +0xe4 runtime (vt+0x134: 0x00c4ace0; State2's enter: 0)
    float m_unkE8;                             // +0xe8
    CMatrix34* m_unkEC;                        // +0xec runtime (PostLoad: an RwMatrix)
    float m_unkF0;                             // +0xf0
    float m_unkF4;                             // +0xf4
    float m_unkF8;                             // +0xf8
    CVector3 m_vGroundPoint;                   // +0xfc runtime: the last ground point (vt+0x178)
    CMatrix34* m_unk108;                       // +0x108 runtime (PostLoad: an RwMatrix): the pose in the moving ground's space
    uint8_t m_bUnk10C;                         // +0x10c runtime (Start: 0; vt+0x158 / vt+0x15c)
    uint8_t m_pad10D[3];
    void* m_pUnk110;                           // +0x110 Start: points to the state table at +0x118
    uint8_t m_unk114;                          // +0x114 constructor 0xff: the current state
    uint8_t m_unk115;                          // +0x115 constructor 0xff: the number of states (Start: 3)
    uint8_t m_pad116[2];
    uint32_t m_unk118[6];                      // +0x118..+0x12f runtime: the state table
};
DOTD_ASSERT_SIZE(CKHkS08TransportableKey, 0x130);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_pCarrier, 0x48);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_GContactInOut, 0x4c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk78, 0x78);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk7c, 0x7c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_vPosition, 0x80);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_vVelocity, 0x8c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk98, 0x98);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkB4, 0xb4);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkB8, 0xb8);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_bLanded, 0xbc);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_pDynamicGround, 0xc0);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_vProbePoint, 0xc4);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_i32PendingState, 0xdc);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_bInStateUpdate, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkE4, 0xe4);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkE8, 0xe8);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkF0, 0xf0);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkF4, 0xf4);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unkF8, 0xf8);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_vGroundPoint, 0xfc);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk108, 0x108);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_bUnk10C, 0x10c);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk114, 0x114);
DOTD_ASSERT_OFFSET(CKHkS08TransportableKey, m_unk115, 0x115);
