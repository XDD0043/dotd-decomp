// CKBhvBlockSpeech.h - a behaviour block that plays a speech (DotD) (key 0xa54c, vtable 0xb2fcf0, size 0x18). Original unit: CKBhvBlockSpeech.cpp.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase9C8C.h"

class IKFile;

class CKBhvBlockSpeech : public KBase9C8C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x295)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9cd450
        return key == 0xa54c || key == 0xc || key == 0x9c8c;
    }
    DOTD_DECLARE_FACTORIES(CKBhvBlockSpeech)

    // 0x005c5410 CKBhvBlockSpeech_Create: CKBhvBlockBase_maybe_Construct, then the vtable (CKBhvBlockSpeech_Construct 0x5c5330).
    CKBhvBlockSpeech() {}
    ~CKBhvBlockSpeech() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005c5520 CKBhvBlockSpeech_Load
    // vt+0x60 0x005c5040 CKBhvBlockSpeech_IsFinished_maybe: 1 once the sekens is done; else, its line finished, the
    // +0x11 byte; else 0.
    uint8_t CanLeave(IKSerializable* user) override;
    // vt+0x64 0x005c50c8 CKBhvBlockSpeech_StartSpeech_maybe: the dictionary's first animation played on the user's node
    // (cut, or blended over +0x14 when it is above 0), then the sekens played when the launcher holds one.
    void Enter(IKSerializable* user) override;
    // vt+0x68 0x005c4fe8 CKBhvBlockSpeech_Stop_maybe: for its own user with +0x10 set, the sekens stopped.
    void Leave(IKSerializable* user) override;
    // vt+0x6c 0x005c4f28 CKBhvBlockSpeech_Update: the user's node advanced by dt; the sekens done tells the user (vt+0x64).
    void Update(IKTime* clock) override;
    // RecursiveRegistration 0x5c5200 and Destroy 0x5c5228 only call KBase9C8C's (0x5c57b8 / 0x5c57c0): inherited.

    IKSerializable* m_unk04;  // +0x04 the user (a CKNPCBehaviourBlockUser, KBase9CCC)
    IKSerializable* m_unk08;  // +0x08 a CAnimationDictionary (its first word is played)
    IKSerializable* m_unk0c;  // +0x0c a CKSekensLauncherCpnt (its sekens 0)
    uint8_t m_unk10;          // +0x10 Leave stops the sekens
    uint8_t m_unk11;          // +0x11 CanLeave's answer once the sekens' line is finished
    uint8_t m_pad12[2];
    float m_unk14;            // +0x14 the blend time (<= 0: a cut)
};
DOTD_ASSERT_SIZE(CKBhvBlockSpeech, 0x18);
DOTD_ASSERT_OFFSET(CKBhvBlockSpeech, m_unk04, +0x04);
DOTD_ASSERT_OFFSET(CKBhvBlockSpeech, m_unk08, +0x08);
DOTD_ASSERT_OFFSET(CKBhvBlockSpeech, m_unk0c, +0x0c);
DOTD_ASSERT_OFFSET(CKBhvBlockSpeech, m_unk10, +0x10);
DOTD_ASSERT_OFFSET(CKBhvBlockSpeech, m_unk11, +0x11);
DOTD_ASSERT_OFFSET(CKBhvBlockSpeech, m_unk14, +0x14);
