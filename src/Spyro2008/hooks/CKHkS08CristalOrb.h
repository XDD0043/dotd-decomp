// CKHkS08CristalOrb.h - a crystal orb hook (key 0x2b82, vtable 0xb27b08, size 0x154). Original unit:
// CKHkS08CristalOrb.cpp (0x47b688-0x480508). No XXL2 class. The fields are named by offset until their use is known.
//
// The state machine: the table pointer +0x12c (Start: +0x134), the state +0x130 and the count +0x131 (constructor 0xff
// each); Start fills four handler pairs at +0x134 (descriptors 0xbc1f28 State0, 0xbc1ea8 State1, 0xbc1f00 State2,
// 0xbc1c30 State3) and enters state 1. State 0: carried by a hero (message 0x93f attaches it to his hot spot); 1: at
// rest (the interaction offer); 2: thrown (falls and bounces until it lands); 3: handed over (Update: message 0x900
// accepted by +0x30). port-final F06 ported the run time. No level file holds the class (key 0x2b82).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"

class CSGHotSpot;
class IKTime;

class CKHkS08CristalOrb : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xae)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4798
        return key == 0x2b82 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkS08CristalOrb)

    // 0x0047c950 CKHkS08CristalOrb_Create (OperatorNew(0x154), the constructor inlined; the dead _Construct 0x47be50 /
    // _Construct_2 0x47c5c0 are its copies): CKHkActorBase's, the vtable, the ground-contact defaults at +0xac (ground 0,
    // face -1, status 3, sector 0), +0x131 = +0x130 = 0xff.
    CKHkS08CristalOrb() {
        m_ui8NbStates = 0xff;
        m_ui8State = 0xff;
    }
    // 0x0047c4b8 CKHkS08CristalOrb_Destructor / 0x0047c470 _DeletingDestructor: the vtable, then CKHkActorBase's
    // (0x3f73f0). The dead _BaseDestructor 0x47c008 is a copy.
    ~CKHkS08CristalOrb() override {}

    // vt+0x10 0x0047be08 CKHkS08CristalOrb_Destroy: CKHkActorBase's (vt+0xc0), the matrix +0x24 destroyed
    // (RwMatrixDestroy_Thunk 0x23f968), the reference block +0x98 freed (0x52fb8; the pointer is left).
    void Destroy() override;
    // vt+0x24 0x0047bde0 CKHkS08CristalOrb_RecursiveRegistration: CKHkActorBase's (0x3f6ee8, IKHook's): inherited.
    // vt+0x70 0x0047bd50 Pause / vt+0x78 0x0047bd28 Resume: CKHkActorBase's (0x3f6e58 / 0x3f6e60, empty): inherited.
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0047d5f8 CKHkS08CristalOrb_Load
    // vt+0x30 0x0047bd78 CKHkS08CristalOrb_PostLoad: CKHkActorBase's, then the matrix +0x24 created (RwMatrixCreate_Thunk
    // 0x23fa68). 1.
    int32_t PostLoad(int32_t type) override;

    // port-final F06: the run time.
    int32_t MessageProc(uint16_t message, void* data) override;  // vt+0x1c 0x0047c038 CKHkS08CristalOrb_MessageProc
    void Start() override;                                        // vt+0x50 0x0047f520 CKHkS08CristalOrb_Start
    void Restart() override;                                      // vt+0x54 0x0047f6b8 CKHkS08CristalOrb_Restart
    void Stop() override;                                         // vt+0x68 0x0047c758 CKHkS08CristalOrb_Stop
    void Update(IKTime* clock) override;                          // vt+0x7c 0x0047f888 CKHkS08CristalOrb_Update
    void VfA0() override;                                         // vt+0xa0 0x0047c9d8 CKHkS08CristalOrb_OnActivate
    // vt+0xa4: CKHkActorBase's OnDeactivate 0x3f7370 (inherited).

    // The states (the table Start builds at +0x134): (clock, phase 0 tick / 1 enter / 2 leave, the other state) -> next.
    uint8_t State0(IKTime* clock, int32_t phase, uint8_t other);  // 0x0047ee48 CKHkS08CristalOrb_State0_Carried_maybe
    uint8_t State1(IKTime* clock, int32_t phase, uint8_t other);  // 0x0047d250 CKHkS08CristalOrb_State1_Idle_maybe
    uint8_t State2(IKTime* clock, int32_t phase, uint8_t other);  // 0x0047e600 CKHkS08CristalOrb_State2
    // 0x0047b680 KStub_ReturnArg4_47b680 (descriptor 0xbc1c30): State 3, the other state returned.
    uint8_t State3(IKTime* /*clock*/, int32_t /*phase*/, uint8_t other) { return other; }
    using StateFn = uint8_t (CKHkS08CristalOrb::*)(IKTime* clock, int32_t phase, uint8_t other);
    // A handler pair of the table (descriptor, adjust) called natively.
    uint8_t CallState(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other);

    // The helpers (non-virtual).
    void DetachFromCarrierHotSpot();                              // 0x0047bc10 _DetachFromCarrierHotSpot_maybe
    void LerpToCarrierHotSpot(IKTime* clock);                     // 0x0047cc20 _LerpToCarrierHotSpot_maybe
    uint8_t IsPointInInteractionCone(const CVector3* point, const CVector3* direction);  // 0x0047ce98
    void UpdateHeroInteraction();                                 // 0x0047d0b0 _UpdateHeroInteraction_maybe
    void UpdateBounce(IKTime* clock);                             // 0x0047de90 _UpdateBounce_maybe
    void SnapToGround();                                          // 0x0047e968 _SnapToGround_maybe

    IKSerializable* m_pUnk20;      // +0x20 reference (the Load's last): a CKHkS08CristalKey_maybe (Restart reads its
                                   // byte +0x34, which the key loads and never reads itself)
    CMatrix34* m_pMatrix24;        // +0x24 PostLoad: RwMatrixCreate; OnActivate: the node's modelling matrix
    IKSerializable* m_pParent28;   // +0x28 runtime: OnActivate: the node's parent
    IKSerializable* m_pUnk2C;      // +0x2c runtime: the object that took the orb (message 0x900, Update; Start: 0)
    IKSerializable* m_pUnk30;      // +0x30 runtime: an object offered the orb (asked with 0x900, then cleared; Start: 0)
    float m_fUnk34;                // +0x34 the interaction distance (IsPointInInteractionCone)
    float m_fUnk38;                // +0x38 the interaction cone's angle (its cosine)
    uint32_t m_ui32Unk3C;          // +0x3c the carrier hero's hot spot index (message 0x93f: the low byte)
    CSGHotSpot* m_pHotSpot40;      // +0x40 runtime: the carrier hero's hot spot (Start: 0)
    CVector3 m_vUnk44;             // +0x44 runtime (Start: the null vector)
    CVector3 m_vUnk50;             // +0x50 runtime (Start: the null vector)
    uint32_t m_unk5C;              // +0x5c runtime (Start: 0)
    float m_afQuatTarget60[4];     // +0x60 runtime: the hot spot's orientation (x, y, z, w) the lerp turns to
    float m_afQuatStart70[4];      // +0x70 runtime: the node's orientation the lerp starts from
    CVector3 m_vStart80;           // +0x80 runtime: the node's position the lerp starts from
    float m_fLerpTime8C;           // +0x8c runtime: the lerp's time
    float m_fUnk90;                // +0x90 the lerp's duration
    uint8_t m_ui8NbRefs;           // +0x94 the count of +0x98
    uint8_t m_pad95[3];
    IKSerializable** m_apRefs98;   // +0x98 Mem_CallocAligned16(4, count): an animation dictionary per hero
    IKSerializable* m_pHero9C;     // +0x9c runtime: the carrier hero (message 0x93f; Start: 0)
    uint32_t m_unkA0;              // +0xa0 runtime
    uint8_t m_ui8HeroIndexA4;      // +0xa4 runtime: the carrier's dragon index (message 0x93f)
    uint8_t m_padA5[3];
    uint32_t m_unkA8;              // +0xa8 flags: bits 0..9 loaded (each from a byte, OR'ed unmasked); runtime bits 0
                                   // lerping to the hot spot, 1 pick-up animation, 3 attached, 4 landed, 8 at rest,
                                   // 9 handed over
    CGroundContactDatasInOut m_GContactInOut;  // +0xac
    float m_fUnkD8;                // +0xd8 the object height of the ground probes
    float m_fUnkDC;                // +0xdc the radius of the wall sweep
    CVector3 m_vPosE0;             // +0xe0 runtime: the thrown orb's position
    CVector3 m_vVelEC;             // +0xec runtime: its velocity
    CVector3 m_vUnkF8;             // +0xf8 one 12-byte read: the acceleration (gravity)
    CVector3 m_vUnk104;            // +0x104 one 12-byte read: the throw direction (in the hot spot's frame)
    float m_fUnk110;               // +0x110 the throw speed
    float m_fUnk114;               // +0x114 the bounce restitution
    float m_fUnk118;               // +0x118 the bounce speed below which it lands
    IKSerializable* m_pUnk11C;     // +0x11c reference: a scene node shown near a hero (State1), placed at the orb
    float m_fUnk120;               // +0x120 the distance within which +0x11c is shown
    uint32_t m_unk124;             // +0x124 runtime (Start / Restart: 0)
    uint8_t m_unk128;              // +0x128 runtime (Start / Restart: 0)
    uint8_t m_pad129[3];
    uint32_t* m_pStateTable;       // +0x12c Start: m_aStateTable
    uint8_t m_ui8State;            // +0x130 constructor 0xff
    uint8_t m_ui8NbStates;         // +0x131 constructor 0xff
    uint8_t m_pad132[2];
    uint32_t m_aStateTable[8];     // +0x134 four handler pairs (descriptor, adjust)
};
DOTD_ASSERT_SIZE(CKHkS08CristalOrb, 0x154);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_pMatrix24, 0x24);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_pParent28, 0x28);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_pUnk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_fUnk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_ui32Unk3C, 0x3c);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_pHotSpot40, 0x40);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_vUnk44, 0x44);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_vUnk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_unk5C, 0x5c);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_afQuatTarget60, 0x60);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_afQuatStart70, 0x70);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_vStart80, 0x80);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_fLerpTime8C, 0x8c);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_fUnk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_apRefs98, 0x98);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_pHero9C, 0x9c);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_ui8HeroIndexA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_unkA8, 0xa8);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_GContactInOut, 0xac);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_fUnkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_vPosE0, 0xe0);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_vVelEC, 0xec);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_vUnkF8, 0xf8);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_fUnk110, 0x110);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_pUnk11C, 0x11c);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_fUnk120, 0x120);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_unk124, 0x124);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_unk128, 0x128);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_pStateTable, 0x12c);
DOTD_ASSERT_OFFSET(CKHkS08CristalOrb, m_aStateTable, 0x134);
