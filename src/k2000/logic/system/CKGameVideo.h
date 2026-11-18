// CKGameVideo.h - a video of the game structure (GAME.KP3) (key 0x1bcc, vtable 0xb14ae0, size 0x24). Original unit: CKGameVideo.cpp.
// Its own fields come with the game-structure block (type 8), after IKGameObject's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "Spyro2008/logic/IKGameObject.h"

class IKFile;

class CKGameVideo : public IKGameObject {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x6f)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9955f8
        return key == 0x1bcc || key == 0x330c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKGameVideo)

    // 0x00042a40 CKGameVideo_Create: IKGameObject_ConstructBase, then the vtable.
    CKGameVideo() {}
    ~CKGameVideo() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00042b50 CKGameVideo_Load
    // vt+0x54 0x00042708 CKGameVideo_IsCurrentLevel: the +0x18 object's vt+0x54 answer (0 / 1), 0 without one.
    uint8_t GetMatchesThisLevel() override;
    // vt+0x58 0x00042898 CKGameVideo_vf58: IKGameObject's (flag bit 0 cleared), then +0x1c = 0, +0x20 = -1 and flag
    // bit 1 cleared.
    void InitializeGameData() override;
    // The other slots are IKGameObject's: PostLoad 0x428f8, RecursiveRegistration 0x42948, Destroy 0x42970,
    // vt+0x5c 0x42870, vt+0x60 0x42848, vt+0x64 0x42820, vt+0x68 0x427f8 only call them.

    IKSerializable* m_unk18;  // +0x18 read second
    IKSerializable* m_unk1c;  // +0x1c read first
    uint32_t m_unk20;         // +0x20
};
DOTD_ASSERT_SIZE(CKGameVideo, 0x24);
DOTD_ASSERT_OFFSET(CKGameVideo, m_unk18, +0x18);
DOTD_ASSERT_OFFSET(CKGameVideo, m_unk1c, +0x1c);
DOTD_ASSERT_OFFSET(CKGameVideo, m_unk20, +0x20);
