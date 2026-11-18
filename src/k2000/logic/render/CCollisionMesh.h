// CCollisionMesh.h - a plain collision mesh (key 0x38c, vtable 0xb1c040, size 0x3c): ICollisionMesh's members only.
// Original unit: CCollisionMesh.cpp (0x1a14e8-0x1a1c58). No game file holds one (outputs/remake/kp3-class-usage.json).
// XXL2 has the class (KServiceCollision/KCollisionMesh); names from ICollisionMesh.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/services/ICollisionMesh.h"

class CCollisionMesh : public ICollisionMesh {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xe)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9aab28
        return key == 0x38c || key == 0x34c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CCollisionMesh)

    CCollisionMesh() {}  // 0x001a18b8 CCollisionMesh_Create: only the vtable
    ~CCollisionMesh() override {}

    // vt+0x2c 0x001a1700 CCollisionMesh_Load: the buffer size, the buffer (Mem_AllocAligned16), then ICollisionMesh's.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x24 0x001a1538 CCollisionMesh_RecursiveRegistration: registered with the saving manager unless the type is 4..7.
    void RecursiveRegistration(int32_t type) override;
    const CMatrix34* GetWorldMatrix() const override { return nullptr; }          // vt+0x50 0x001a15a0
    const CMatrix34* GetInvertedWorldMatrix() const override { return nullptr; }  // vt+0x54 0x001a15a8
    // vt+0x58 0x001a1988 CCollisionMesh_RaycastTriangles_maybe (XXL2 FindLineIntersection): CGround's face walk with
    // its own bounds: u in 1e-5..0.99999, v >= 1e-5, u + v <= 0.99999, t in (1e-5, 0.99999) and below the time `out`
    // holds (a NaN passes the u and t tests).
    uint8_t FindLineIntersection(const CLine* line, CLineCollisionDatas* out, uint8_t backFaces) const override;
    void Update(uint8_t /*updateIndex*/) override {}  // vt+0x5c 0x001a15b0 CCollisionMesh_RefreshTransform_maybe (blr)
    // vt+0x60 0x001a17b0 CCollisionMesh_FreeGeometry (XXL2 MyDestroy): KStub_Nop_1a6bb8, the buffer freed, the counts
    // and the triangle pointer cleared.
    void MyDestroy() override;
};
static_assert(CCollisionMesh::kClassKey == 0x38c, "key");
DOTD_ASSERT_SIZE(CCollisionMesh, 0x3c);
