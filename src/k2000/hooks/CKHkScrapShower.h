// CKHkScrapShower.h - a hook that drops scrap pieces around a point (key 0x1242, vtable 0xb285c8, size
// 0x12c). Original unit: CKHkScrapShower.cpp (0x4a40d0-0x4a66d0). No XXL2 class. Field names are
// placeholders (C2.1 ported the Load and the constructor, C2.8 port-all P18 the rest); the purposes are _maybe from the
// code and the LVL060 / LVL090 data (21 objects).
//
// The shower drops one piece of scrap at a time: while enabled (+0x0c bit 5) and the detector (+0x84, or the detector
// group +0x9c) holds a hero (bit 8), a delay (+0xe0, drawn between the +0x58 / +0x5c pair of the current step +0x128)
// runs down; then the hook's node is put on the ground near the hero (PickDropPosition: in front of a moving hero, else
// around him or inside the box +0x88 / +0x94), gets a blob shadow from the component (+0x30) and a falling sound; after
// +0x60 seconds the piece (a projectile of the component's accessor) is launched from +0x2c above the node, and when the
// fall time (+0xdc) has passed too the shadow and sound stop, the next delay is drawn and the camera may shake.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/services/CKSrvShadow.h"
#include "k2000/services/CTriggerStarter.h"

class CKHkScrapShower : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x49)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9c4e50
        return key == 0x1242 || key == 0xd82 || key == 0x2 || key == 0x2fe || key == 0x3fe || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKHkScrapShower)

    // 0x004a5ce0 CKHkScrapShower_Create (inlined constructor, the same as the dead 0x4a4b50
    // CKHkScrapShower_Construct): +0x50 = 0 and the ground-contact defaults (+0xe8 / +0xf8).
    CKHkScrapShower() { m_shadowGround.m_ui8Flags = 0; }
    // 0x004a4df8 CKHkScrapShower_Destructor (= 0x4a4ce8 _BaseDestructor, 0x4a4db0 _DeletingDestructor): the actor base's.
    ~CKHkScrapShower() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004a5d78 CKHkScrapShower_Load

    // ---- C2.8 port-all P18 (CKHkScrapShower.cpp) ----
    // vt+0x40 0x004a4158 CKHkScrapShower_GetInfo: the trigger value 0x9b (0x9c4eb8 GetTriggerProp9B: +0x0c bit 8, a hero is
    // detected), a byte; folded with the actor base's answer.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x50 0x004a4870 CKHkScrapShower_Start: the actor base's, no shadow (+0x124 -1), Restart (vt+0x54), the ground
    // contact reset (+0xe8 1.0 and the height +0x2c, masks 1 / 8; no ground, face -1, status 3, sector 0), then the fall
    // time (+0xdc) of a piece dropped from +0x2c at speed +0xc0 (4.9 t^2 + +0xc0 t - +0x2c = 0).
    void Start() override;
    // vt+0x30 0x004a49c0 CKHkScrapShower_PostLoad: the actor base's, the shadow ground's used byte (+0x51) cleared.
    int32_t PostLoad(int32_t type) override {
        CKHkActorBase::PostLoad(type);
        m_shadowGround.m_bUsed_maybe = 0;
        return 1;
    }
    // vt+0x10 0x004a4a50 CKHkScrapShower_Destroy: the actor base's (vt+0xc0, empty), then the two delay arrays deleted.
    void Destroy() override;
    // vt+0xa0 0x004a4bd0 CKHkScrapShower_OnActivate: the actor base's, then sounds 0..3 of +0xd4 set looping.
    void VfA0() override;
    // vt+0xc8 0x004a4d18 CKHkScrapShower_vfC8 (the state preset): +0x0c bit 5 (enabled) = +0xd9 for 1, +0xd8 for 0.
    void ApplyStatePreset(int32_t state) override;
    // vt+0x38 0x004a4d68 CKHkScrapShower_SetDefaultState: the actor base's (empty), then enabled (+0x0c bit 5).
    void SetDefaultState(int32_t flag) override;
    // vt+0xa4 0x004a4e28 CKHkScrapShower_OnDeactivate: the actor base's, the falling sound stopped (+0x129 -1), a shadow
    // given back (+0x124 -1) and the piece no longer falling (bit 6).
    void VfA4() override;
    void Update(IKTime* clock) override;  // vt+0x7c 0x004a4f18 CKHkScrapShower_Update
    // vt+0x1c 0x004a57f0 CKHkScrapShower_MessageProc: the actor messages, then 0x996 (enable: step 0, its delay drawn),
    // 0x997 (disable), 0x998 (drop now: an enabled shower whose piece is not falling: delay 0, bit 7) and the hero's hazard
    // query 0xc32 (the knock values +0xa4, the node's position, the damage +0xa0 for a player-controlled hero).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x54 0x004a5aa8 CKHkScrapShower_Restart: step 0, no delay, no sound, bits 6-8 cleared; a hook without bit 2
    // gives its shadow back.
    void Restart() override;
    // 0x004a4240 CKHkScrapShower_PickDropPosition_maybe: the node put on the ground at the drop point (1), or 0 (no
    // controlled hero, no ground after four probes, or a hero's ground surface without bit 4).
    uint8_t PickDropPosition();
    // The delay of step `step` (inlined in Update and MessageProc 0x996): a draw between +0x58[step] and +0x5c[step].
    float DrawDelay(uint32_t step) const;

    CVector3 m_unk20;                          // +0x20 a position_maybe (LVL060: near the hook's leaf)
    float m_unk2c;                             // +0x2c the height the piece falls from (LVL060: 50.0)
    IKSerializable* m_unk30;                   // +0x30 reference: the CKScrapShowerCpnt (shadows, projectile, quake)
    // +0x34 runtime: the piece's shadow ground (position = the node's, normal = its up axis, height 0); +0x50 the flags
    // (constructor 0), +0x51 in use (PostLoad 0x4a49c0 clears it, CKSrvShadow sets it).
    CKShadowGround m_shadowGround;
    uint8_t m_ui8NbUnk58;                      // +0x54 the element count of +0x58 / +0x5c
    uint8_t m_pad55[3];
    float* m_unk58;                            // +0x58 OperatorNewArray(count * 4): the delays' one end (LVL060: 100.0)
    float* m_unk5c;                            // +0x5c OperatorNewArray(count * 4): their other end (LVL060: 0)
    // +0x60..+0x83 nine separate 4-byte reads: [0] the delay before the piece is launched (also the lead of the drop in
    // front of a moving hero), [1] the percent chance of that drop, [2] the drop's spread around the hero, [3] / [4] the
    // shadow's scale at the drop / at the fall's end, [5] / [6] the sound's volume, [7] / [8] its speed.
    float m_unk60[9];
    IKSerializable* m_unk84;                   // +0x84 reference: the CKDetectorBase that holds a hero (without +0x9c)
    CVector3 m_unk88;                          // +0x88 one 12-byte read: the drop box's centre (+0x0c bit 3)
    float m_unk94[2];                          // +0x94 one 8-byte read: the drop box's half sizes along x and z
    IKSerializable* m_unk9c;                   // +0x9c reference (LVL060: null; LVL090: a CKHkDetectorGroup)
    uint8_t m_unkA0;                           // +0xa0 the hazard query's damage (LVL060: 100)
    uint8_t m_padA1[3];
    float m_unkA4[3];                          // +0xa4..+0xaf the hazard query's knock values (+0x08..+0x10)
    float m_unkB0[3];                          // +0xb0..+0xbb (read last)
    uint8_t m_unkBC;                           // +0xbc (LVL060: 50)
    uint8_t m_padBD[3];
    float m_unkC0;                             // +0xc0 (LVL060: 7.0)
    CTriggerStarter m_unkC4;                   // +0xc4
    CTriggerStarter m_unkCC;                   // +0xcc
    IKSerializable* m_unkD4;                   // +0xd4 reference (LVL060: a CKSoundDictionaryID_maybe)
    uint8_t m_unkD8;                           // +0xd8
    uint8_t m_unkD9;                           // +0xd9
    uint8_t m_padDA[2];
    float m_fFallTime;                         // +0xdc runtime: the piece's fall time (Start)
    float m_fDelay;                            // +0xe0 runtime: the time left before the next drop
    float m_fDropTime;                         // +0xe4 runtime: the clock's time at the drop
    CGroundContactDatasIn m_GContactIn;        // +0xe8
    CGroundContactDatasInOut m_GContactInOut;  // +0xf8
    int32_t m_i32ShadowIndex;                  // +0x124 runtime: the component entry of the shadow, -1 none
    uint8_t m_ui8Step;                         // +0x128 runtime: the delay pair of the next drop
    int8_t m_i8Sound;                          // +0x129 runtime: the falling sound (0..3 of +0xd4), -1 none
    uint8_t m_pad12a[2];
};
DOTD_ASSERT_SIZE(CKHkScrapShower, 0x12c);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_shadowGround, 0x34);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_ui8NbUnk58, 0x54);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk60, 0x60);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk94, 0x94);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unk9c, 0x9c);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkA0, 0xa0);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkA4, 0xa4);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkB0, 0xb0);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkBC, 0xbc);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkC0, 0xc0);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkC4, 0xc4);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkCC, 0xcc);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkD4, 0xd4);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkD8, 0xd8);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_unkD9, 0xd9);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_GContactIn, 0xe8);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_GContactInOut, 0xf8);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_fFallTime, 0xdc);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_i32ShadowIndex, 0x124);
DOTD_ASSERT_OFFSET(CKHkScrapShower, m_i8Sound, 0x129);
