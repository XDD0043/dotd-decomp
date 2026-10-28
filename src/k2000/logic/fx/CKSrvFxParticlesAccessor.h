// CKSrvFxParticlesAccessor.h - an accessor of a particle component (key 0x2c0c, vtable 0xb1dea0, size 0x8).
// Original unit: CKSrvFxParticlesAccessor.cpp (0x1d8bf0-0x1d9080). Base: KBase1DCC (0x1dcc), like
// CKQuakeCameraLauncher: +0x50/+0x54 get and set the accessed object at +0x04. No XXL2 class of this name.
// The most numerous level class (LVL010: 1844 objects); CKExplosionNodeFx's sub-effects reference them.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/KBase1DCC.h"

class CKSrvFxParticlesAccessor : public KBase1DCC {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0xb0)
    DOTD_DECLARE_FACTORIES(CKSrvFxParticlesAccessor)

    CKSrvFxParticlesAccessor() : m_pParticles(nullptr) {}  // 0x001d8e40 CKSrvFxParticlesAccessor_Construct

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d8c78 CKSrvFxParticlesAccessor_Load
    IKSerializable* Vf50() override { return m_pParticles; }   // vt+0x50 0x1d8ba0
    void Vf54(IKSerializable* object) override { m_pParticles = object; }  // vt+0x54 0x1d8ba8

    // +0x04 the accessed object (Ghidra draft: CKParticlesCpnt*; LVL010 references class 0x646, a component).
    IKSerializable* m_pParticles;
};
static_assert(CKSrvFxParticlesAccessor::kClassKey == 0x2c0c, "key");
DOTD_ASSERT_SIZE(CKSrvFxParticlesAccessor, 0x8);
DOTD_ASSERT_OFFSET(CKSrvFxParticlesAccessor, m_pParticles, 0x04);
