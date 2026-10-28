// CKSurfaceParticlesRendable.h - the renderable of a surface particle system (key 0xe0d, vtable 0xb17b58,
// size 0x24; only LVL120 holds one). Original unit: CKSurfaceParticlesRendable.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/IRendableObject.h"

class CKSurfaceParticlesRendable : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x38)
    DOTD_DECLARE_FACTORIES(CKSurfaceParticlesRendable)

    // 0x000c2e20 CKSurfaceParticlesRendable_Create (the constructor inlined)
    CKSurfaceParticlesRendable() {
        m_pLightSet = nullptr;
        m_pNextAccumulatedObject = nullptr;
        m_BitProperties = 0;
        m_pPriorityParent = 0;
    }
    ~CKSurfaceParticlesRendable() override {}

    // vt+0x2c 0x000c3478 CKSurfaceParticlesRendable_Load: IRendableObject's, then (type 0) the owner and
    // four raw bytes.
    int32_t Load(IKFile* file, int32_t type) override;
    void Render() override {}  // vt+0x5c  STUB(C2.2)
    // vt+0x30 0x000c3450 CKSurfaceParticlesRendable_PostLoad: +0x18 from the owner's (+0x24)->+0x9c.
    // STUB(C2.2) (default).

    void* m_unk18;            // +0x18 PostLoad
    IKSerializable* m_pOwner; // +0x1c _maybe the particle system
    uint8_t m_unk20[4];       // +0x20 read raw (file bytes; 0xffffffff in LVL120, _maybe a colour)
};
static_assert(CKSurfaceParticlesRendable::kClassKey == 0xe0d, "key");
DOTD_ASSERT_SIZE(CKSurfaceParticlesRendable, 0x24);
DOTD_ASSERT_OFFSET(CKSurfaceParticlesRendable, m_pOwner, 0x1c);
DOTD_ASSERT_OFFSET(CKSurfaceParticlesRendable, m_unk20, 0x20);
