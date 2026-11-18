// CKSoundOutputEffect.h - one output (reverb) environment of a level (key 0x140, vtable 0xb199a8, size
// 0xc). Original unit: CKSoundOutputEffect.cpp (0x115058-0x115b70). XXL2 keeps the same 0x30-byte
// RwaEnvironment inline in CKSoundOutput's environment array (CKOutputEffect::m_rwaOutputEffect); DotD
// makes each one an object. LVL000 holds 23; its CKSoundOutput refers to them (CKSoundOutput::Load), and
// message 0x100 selects one (CKSoundOutputEffect_MessageProc -> SoundOutputEffectMgr_SetCurrent_maybe,
// which hands m_rwaOutputEffect to RwaPS3Driver_SetOutputEffect_maybe).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

// RenderWare Audio's environment (XXL2 RwSrc/Audio/include/null/rwacore.h, 0x30 bytes): the I3DL2
// reverb parameters. The LVL000 values are I3DL2 presets (Generic: -1000, -100, 0, 1.49, 0.83, -2602,
// 0.007, 200, 0.011, 100, 100, 5000; Padded cell: -1000, -6000, 0, 0.17, 0.10, -1204, 0.001, 207, ...).
struct RwaEnvironment {
    int32_t room;               // +0x00 mB
    int32_t roomHF;             // +0x04
    float roomRolloffFactor;    // +0x08
    float decayTime;            // +0x0c s
    float decayHFRatio;         // +0x10
    int32_t reflections;        // +0x14
    float reflectionsDelay;     // +0x18
    int32_t reverb;             // +0x1c
    float reverbDelay;          // +0x20
    float diffusion;            // +0x24
    float density;              // +0x28
    float hfReference;          // +0x2c Hz
};
DOTD_ASSERT_SIZE(RwaEnvironment, 0x30);

class CKSoundOutputEffect : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryManager, 0x5)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x140 || key == 0xc; }  // vt+0x08 0x9a6c40
    DOTD_DECLARE_FACTORIES(CKSoundOutputEffect)

    CKSoundOutputEffect();                              // 0x001152e0 CKSoundOutputEffect_Create (inlined)
    ~CKSoundOutputEffect() override {}                  // 0x009a6c28 CKSoundOutputEffect_Destructor (0x9a6c60 deleting): the vtables only
    // vt+0x10 0x001153a0 CKSoundOutputEffect_Destroy: the environment freed (the pointer is left).
    void Destroy() override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001153c8 CKSoundOutputEffect_Load
    // vt+0x1c 0x00115328 CKSoundOutputEffect_MessageProc (P21): 0x100 makes it the output's current environment
    // (SoundOutputEffectMgr_SetCurrent_maybe) and answers 0; the others 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x24 0x001150a8 CKSoundOutputEffect_RecursiveRegistration (P21): type 0 registers it with the saving manager.
    void RecursiveRegistration(int32_t type) override;
    // vt+0x40 0x00115320 CKSoundOutputEffect_GetInfo and vt+0x30 0x00115398 CKSoundOutputEffect_PostLoad: 1, the defaults.

    RwaEnvironment* m_rwaOutputEffect;  // +0x04 Mem_AllocAligned16(0x30) by Load
    uint32_t m_unk08;                   // +0x08 read first; 0, 1, 2, ... in LVL000 (the effect's index _maybe)
};
DOTD_ASSERT_SIZE(CKSoundOutputEffect, 0xc);
DOTD_ASSERT_OFFSET(CKSoundOutputEffect, m_rwaOutputEffect, 0x04);
DOTD_ASSERT_OFFSET(CKSoundOutputEffect, m_unk08, 0x08);
