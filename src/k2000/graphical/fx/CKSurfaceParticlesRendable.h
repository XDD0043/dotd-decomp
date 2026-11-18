// CKSurfaceParticlesRendable.h - the renderable of a surface particle system (key 0xe0d, vtable 0xb17b58,
// size 0x24; only LVL120 holds one). Original unit: CKSurfaceParticlesRendable.cpp. No XXL2 class.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/IRendableObject.h"

struct CMaterialEffectData;

class CKSurfaceParticlesRendable : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x38)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a1bd0
        return key == 0xe0d || key == 0xa8d || key == 0xc;
    }
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
    // vt+0x5c 0x000c2e78 DrawSurfaceParticleGeometry: the effect's particle geometry drawn at the owner atomic's world
    // sphere, faded by the distance along the main camera's view axis.
    void Render(IKTime* frameClock) override;
    // vt+0x30 0x000c3450 CKSurfaceParticlesRendable_PostLoad: (type 0) +0x18 = the effect data (+0x9c) of the owner
    // geometry's material (+0x24).
    int32_t PostLoad(int32_t type) override;
    // vt+0x10 0x000c2d50 CKSurfaceParticlesRendable_Destroy: IRendableObject's (0xa7248).
    void Destroy() override { IRendableObject::Destroy(); }
    // vt+0x24 0x000c2d28 CKSurfaceParticlesRendable_RecursiveRegistration: IRendableObject's (0xa71e8).
    void RecursiveRegistration(int32_t type) override { IRendableObject::RecursiveRegistration(type); }
    // vt+0x58 0x000c2c48 CKSurfaceParticlesRendable_UpdateAndExtract: added to the stage of its properties' low 5 bits
    // (the queue's vt+0x00 Add).
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;

    // +0x18 PostLoad: the effect data (+0x08 the particle geometry, +0x0c the fade mode, +0x10 / +0x14 the fade start
    // and end distances; +0x14 is also the draw distance).
    CMaterialEffectData* m_unk18;
    IKSerializable* m_pOwner; // +0x1c _maybe the particle system
    uint8_t m_unk20[4];       // +0x20 read raw (file bytes; 0xffffffff in LVL120, _maybe a colour)
};
static_assert(CKSurfaceParticlesRendable::kClassKey == 0xe0d, "key");
DOTD_ASSERT_SIZE(CKSurfaceParticlesRendable, 0x24);
DOTD_ASSERT_OFFSET(CKSurfaceParticlesRendable, m_pOwner, 0x1c);
DOTD_ASSERT_OFFSET(CKSurfaceParticlesRendable, m_unk20, 0x20);

// The material effect block's slots (CMaterial.h's CMaterialEffectData; unit CKSurfaceParticlesRendable.cpp by address).
// CMaterial.cpp (another package) is to call them: CMaterial_RecursiveRegistration 0xbbda8 calls the first when +0x9c
// is set, CMaterial_Destroy 0xbe260 the second, CMaterial_PostLoad 0xbe348 the third.
// 0x000c3680 CMaterialEffectData_LevelReset_maybe: both references' RecursiveRegistration (vt+0x24) with the type.
void CMaterialEffectData_RecursiveRegistration(CMaterialEffectData* data, int32_t type);
// 0x000c3678 KStub_Nop_c3678 (CMaterial_Destroy calls it on the block): nothing.
inline void CMaterialEffectData_Release(CMaterialEffectData* /*data*/) {}
// 0x000c3728 KStub_Nop_c3728 (CMaterial_PostLoad calls it on the block with the type): nothing.
inline void CMaterialEffectData_PostLoad(CMaterialEffectData* /*data*/, int32_t /*type*/) {}
