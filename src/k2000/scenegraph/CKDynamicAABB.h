// CKDynamicAABB.h - a moving axis-aligned collision box (key 0x1cb, vtable 0xb18790, size 0x44). Original unit:
// CKDynamicAABB.cpp (0xd7160-0xd7480); its Load / Save / destructors are out of line from this header (0x9a3c90..).
// No level file holds one (work/level-class-keys.json); C2.8 port-rest R08 ported it from the code. Name of the
// extra vector ours (XXL2 has no CKDynamicAABB; CKDynamicBoundingSphere keeps its old position there).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/io/IKFile.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/scenegraph/CKAABB.h"

class CKDynamicAABB : public CKAABB {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x7)  // vt+0x14 / +0x18 0x9a3c90 / 0x9a3c98
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a3ca0
        return key == 0x1cb || key == 0x44b || key == 0x40b || key == 0x34b || key == 0x20b || key == 0x14b ||
               key == 0xc;
    }
    // 0x000d7160 CKDynamicAABB_Delete, 0x000d7320 CKDynamicAABB_Create, 0x000d7390 CKDynamicAABB_CreateArray (stride
    // 0x44), 0x000d7278 CKDynamicAABB_DeleteArray.
    DOTD_DECLARE_FACTORIES(CKDynamicAABB)

    // Inlined in 0x000d7320 CKDynamicAABB_Create: CSGLeaf's constructor, +0x28 and +0x1c cleared (IKBoundingVolume's),
    // the vtables. The vector is what the fresh heap leaves (zero).
    CKDynamicAABB() { m_v3Unk38 = {0.0f, 0.0f, 0.0f}; }
    // 0x9a3d00 / 0x9a3d48 CKDynamicAABB_Destructor / _DeletingDestructor: the bases'.
    ~CKDynamicAABB() override {}

    // vt+0x70 0x000d71b0 CKDynamicAABB_GetShapeType_maybe: 4 (a swept box) with infos bit 4, else 3 (a box).
    int32_t GetShapeType() const override {
        return static_cast<int32_t>(4u - (((static_cast<uint32_t>(m_ba8Infos) >> 4) & 1u) ^ 1u));
    }
    // vt+0x24 0x000d71c8 CKDynamicAABB_RecursiveRegistration: CKAABB's (0xd6598), inherited.
    // vt+0x2c 0x009a3da8 CKDynamicAABB_Load: IKBoundingBox's (inlined: CSGLeaf's, the volume's, the extent), then the
    // vector (one 0xc read, each word swapped). No type check.
    int32_t Load(IKFile* file, int32_t type) override {
        IKBoundingBox::Load(file, type);
        uint32_t words[3];
        ReadU32LEWords(file, words, 3);
        std::memcpy(&m_v3Unk38, words, 0xc);
        return 1;
    }

    CVector3 m_v3Unk38;  // +0x38 read last
};
static_assert(CKDynamicAABB::kClassKey == 0x1cb, "key");
DOTD_ASSERT_SIZE(CKDynamicAABB, 0x44);
DOTD_ASSERT_OFFSET(CKDynamicAABB, m_v3Unk38, 0x38);
