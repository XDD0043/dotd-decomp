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
    DOTD_DECLARE_FACTORIES(CKGameVideo)

    // 0x00042a40 CKGameVideo_Create: IKGameObject_ConstructBase, then the vtable.
    CKGameVideo() {}
    ~CKGameVideo() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00042b50 CKGameVideo_Load

    IKSerializable* m_unk18;  // +0x18 read second
    IKSerializable* m_unk1c;  // +0x1c read first
    uint32_t m_unk20;         // +0x20
};
DOTD_ASSERT_SIZE(CKGameVideo, 0x24);
DOTD_ASSERT_OFFSET(CKGameVideo, m_unk18, +0x18);
DOTD_ASSERT_OFFSET(CKGameVideo, m_unk1c, +0x1c);
DOTD_ASSERT_OFFSET(CKGameVideo, m_unk20, +0x20);
