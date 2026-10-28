// IKBoundingBox.h - the base of the box volumes (key 0x40b, not registered; CKAABB, CKOBB). XXL2:
// K/KModules/KGL/SceneGraph/KBoundingVolume/IKBoundingBox.h, member m_Extent. Its Load is inline: the
// derived Loads (CKAABB_Load 0x9a35d8, CKOBB_Load 0x9a46d8) are its out-of-line copies with
// IKBoundingVolume's Load inlined too.
#pragma once
#include <cstdint>
#include <cstring>

#include "k2000/core/Layout.h"
#include "k2000/io/IKFile.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/scenegraph/IKBoundingVolume.h"

class IKBoundingBox : public IKBoundingVolume {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x10)

    IKBoundingBox() {}  // inlined in the derived Creates: no stores of its own
    ~IKBoundingBox() override {}

    // vt+0x2c 0x009a3018 (Ghidra CKBoundingBox_Load): IKBoundingVolume's Load, then the extent (one 0xc
    // read, each word swapped). No type check.
    int32_t Load(IKFile* file, int32_t type) override {
        IKBoundingVolume::Load(file, type);
        uint32_t words[3];
        ReadU32LEWords(file, words, 3);
        std::memcpy(&m_Extent, words, 0xc);
        return 1;
    }

    CVector3 m_Extent;  // +0x2c the half sizes
};
static_assert(IKBoundingBox::kClassKey == 0x40b, "key");
DOTD_ASSERT_SIZE(IKBoundingBox, 0x38);
DOTD_ASSERT_OFFSET(IKBoundingBox, m_Extent, 0x2c);
