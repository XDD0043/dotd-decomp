// CKBhvBlockAnimation.h - a behaviour block that plays an animation (DotD) (key 0x9d0c, vtable 0xb2fb40, size 0x44). Original unit: CKBhvBlockAnimation.cpp.
// A scripted NPC (CKHkScriptedNPC) runs its blocks in turn: entered, the block places the NPC's node (at a marker
// beacon or a position), plays its animation (the dictionary's first word, cut or blended) or a cinematic stream,
// updates it until it ends (or the time limit +0x1c), then tells its user (+0x0c, the CKNPCBehaviourBlockUser) so the
// NPC chains the next one. Each update also plays the sound marks (+0x08) and the marked effects (+0x04).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase9C8C.h"
#include "k2000/math/CMatrix34.h"

class IKFile;

class CKBhvBlockAnimation : public KBase9C8C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x274)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cd330
        return key == 0x9d0c || key == 0xc || key == 0x9c8c;
    }
    DOTD_DECLARE_FACTORIES(CKBhvBlockAnimation)

    // 0x005c2360 CKBhvBlockAnimation_Create: CKBhvBlockBase_maybe_Construct, then the vtable (CKBhvBlockAnimation_Construct 0x5c1e90).
    CKBhvBlockAnimation() {}
    ~CKBhvBlockAnimation() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c23b8 CKBhvBlockAnimation_Load
    // vt+0x30 0x005c2260 CKBhvBlockAnimation_PostLoad: the sound marks' position callback (the NPC's anchor); 1.
    int32_t PostLoad(int32_t type) override;
    void ResetRuntime() override;                   // vt+0x50 0x005c1d70 CKBhvBlockAnimation_ResetRuntime
    void Vf54() override;                           // vt+0x54 0x005c1d48 CKBhvBlockAnimation_vf54
    void Vf58() override;                           // vt+0x58 0x005c1d20 CKBhvBlockAnimation_vf58
    // vt+0x5c 0x005c17f0 CKBhvBlockAnimation_vf5C: 1 (as the base); vt+0x60 the base's (1).
    uint8_t CanEnter(IKSerializable* /*user*/) override { return 1; }
    void Enter(IKSerializable* user) override;      // vt+0x64 0x005c1a60 CKBhvBlockAnimation_vf64
    void Leave(IKSerializable* user) override;      // vt+0x68 0x005c19a8 CKBhvBlockAnimation_vf68
    void Update(IKTime* clock) override;            // vt+0x6c 0x005c1fd0 CKBhvBlockAnimation_Update
    void Prepare() override;                        // vt+0x70 0x005c18d0 CKBhvBlockAnimation_vf70
    void Unprepare() override;                      // vt+0x74 0x005c1880 CKBhvBlockAnimation_vf74
    void PreUpdate(IKTime* clock) override;         // vt+0x78 0x005c1940 CKBhvBlockAnimation_UpdateCinematicStream_maybe
    uint8_t Vf7C() override { return m_unk18; }     // vt+0x7c 0x009cd378 CKBhvBlockAnimation_vf7C: the stream mode

    IKSerializable* m_unk04;  // +0x04 read last: a CKMarkedFX
    IKSerializable* m_unk08;  // +0x08 a CKMarkedSoundDico
    IKSerializable* m_unk0c;  // +0x0c the user (a CKNPCBehaviourBlockUser)
    IKSerializable* m_unk10;  // +0x10 CAnimationDictionary in the files; read first
    IKSerializable* m_unk14;  // +0x14 a CKCinematicStreamCpnt
    uint8_t m_unk18;          // +0x18 the block plays the stream (+0x14) instead of the animation
    uint8_t m_unk19;          // +0x19 the animation's end does not end the block
    uint8_t m_unk1a;          // +0x1a
    uint8_t m_pad1b;
    float m_unk1c;            // +0x1c the time limit (> 0)
    float m_unk20;            // +0x20 not set by the constructor nor the Load: the time since Enter (with a limit)
    uint8_t m_unk24;          // +0x24
    uint8_t m_pad25[3];
    IKSerializable* m_unk28;  // +0x28 a CKMarkerBeacon the node is placed at (+0x2c)
    uint8_t m_unk2c;          // +0x2c
    uint8_t m_pad2d[3];
    CVector3 m_unk30;         // +0x30 one 0xc read, swapped: the position the node is placed at (+0x3c)
    uint8_t m_unk3c;          // +0x3c
    uint8_t m_pad3d[3];
    float m_unk40;            // +0x40 the blend time (<= 0: a cut)
};
DOTD_ASSERT_SIZE(CKBhvBlockAnimation, 0x44);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk04, +0x04);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk08, +0x08);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk0c, +0x0c);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk10, +0x10);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk14, +0x14);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk18, +0x18);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk19, +0x19);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk1a, +0x1a);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk1c, +0x1c);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk20, +0x20);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk24, +0x24);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk28, +0x28);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk2c, +0x2c);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk30, +0x30);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk3c, +0x3c);
DOTD_ASSERT_OFFSET(CKBhvBlockAnimation, m_unk40, +0x40);
