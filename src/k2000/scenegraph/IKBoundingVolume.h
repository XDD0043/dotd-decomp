// IKBoundingVolume.h - the base of the collision volumes (key 0x34b, not registered; vtable 0xb13020).
// XXL2: K/KModules/KGL/SceneGraph/KBoundingVolume/IKBoundingVolume.h, the same members in the same order
// plus DotD's word at +0x1c. Its methods are inline: the out-of-line copies sit with CKBoundingSphere
// (CKBoundingSphere.cpp's checklist).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CSGLeaf.h"

class IKBoundingVolume : public CSGLeaf {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0xd)

    // Inlined in every derived Create (CKBoundingSphere_Create 0xd70c8, ...): +0x28, then +0x1c.
    IKBoundingVolume() {
        m_CollisionResList = nullptr;
        m_unk1c = nullptr;
    }
    ~IKBoundingVolume() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00991ca0 (Ghidra CKBoundingShape_Load)
    // vt+0x30 0x009916a8 IKBoundingVolume_PostLoad (every derived volume's slot): no damage (+0x1c), then
    // CSGLeaf_PostLoad 0xcf0f8.
    int32_t PostLoad(int32_t type) override {
        m_unk1c = nullptr;
        return CSGLeaf::PostLoad(type);
    }

    // The shape numbers CKSrvCollision's test matrix (m_IntersectionMatrix[shape1][shape2]) is indexed by: 0 sphere,
    // 1 oriented box, 2 moving sphere, 3 axis-aligned box, 4 moving axis-aligned box, 5 vertical cylinder.
    enum EShape { kSphere = 0, kOBB = 1, kSweptSphere = 2, kAABB = 3, kSweptAABB = 4, kCylinder = 5 };
    // vt+0x70 (pure in IKBoundingVolume's vtable 0xb13020; Ghidra *_GetShapeType_maybe).
    virtual int32_t GetShapeType() const = 0;

    uint8_t m_ba8Infos;               // +0x18 XXL2 CBitArray8; read raw together with the next byte
    uint8_t m_ui8OwnerType;           // +0x19
    uint16_t m_ui16PropertiesFlags;   // +0x1a
    IKSerializable* m_unk1c;          // +0x1c DotD (the Ghidra struct types it CKS08Damage*); the constructor sets 0
    float m_fRadius;                  // +0x20
    IKSerializable* m_pOwner;         // +0x24
    void* m_CollisionResList;         // +0x28 XXL2 ListOfCollisions (a list head); the constructor and Load set 0
};
static_assert(IKBoundingVolume::kClassKey == 0x34b, "key");
DOTD_ASSERT_SIZE(IKBoundingVolume, 0x2c);
DOTD_ASSERT_OFFSET(IKBoundingVolume, m_ba8Infos, 0x18);
DOTD_ASSERT_OFFSET(IKBoundingVolume, m_ui8OwnerType, 0x19);
DOTD_ASSERT_OFFSET(IKBoundingVolume, m_ui16PropertiesFlags, 0x1a);
DOTD_ASSERT_OFFSET(IKBoundingVolume, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(IKBoundingVolume, m_fRadius, 0x20);
DOTD_ASSERT_OFFSET(IKBoundingVolume, m_pOwner, 0x24);
DOTD_ASSERT_OFFSET(IKBoundingVolume, m_CollisionResList, 0x28);

// 0x00991ca0 (Ghidra CKBoundingShape_Load; slot +0x2c of the IKBoundingVolume vtable 0xb13020). No type
// check.
inline int32_t IKBoundingVolume::Load(IKFile* file, int32_t type) {
    CSGLeaf::Load(file, type);
    uint8_t infos[2];
    ReadRaw(file, infos, 2);  // one 2-byte read, not swapped
    m_ba8Infos = infos[0];
    m_ui8OwnerType = infos[1];
    ReadU16LE(file, &m_ui16PropertiesFlags);
    ReadF32LE(file, &m_fRadius);
    IKFile_ReadRef(file, &m_pOwner);
    m_CollisionResList = nullptr;
    return 1;
}
