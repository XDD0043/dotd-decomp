// CKExplosionNodeFx.h - the explosion effect node (key 0x1a4c, vtable 0xb1ca38, size 0x50). Original unit:
// CKExplosionNodeFx.cpp (0x1b5d98-0x1b8ab0). Its data is CKExplosionFxData (0x1a8c). Not in XXL2; names ours.
//
// The sub-effects (+0x20) are 12-byte records: a value and, when the value is not positive, an object
// reference (LVL010: CKSrvFxParticlesAccessor). CountSubEffectsOfType / GetNthSubEffectOfType
// (0x1b64a0/0x1b6530) _maybe read the value as a type.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/util/TVector.h"

struct RwMatrix;

class CKExplosionNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x69)
    DOTD_DECLARE_FACTORIES(CKExplosionNodeFx)

    struct SubEffect {
        IKSerializable* m_pObject;  // +0x00 read when m_value <= 0, else set to null
        int32_t m_value;            // +0x04
        uint32_t m_unk08;           // +0x08 not read
    };

    CKExplosionNodeFx();  // inlined in 0x001b6150 CKExplosionNodeFx_Create
    ~CKExplosionNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001b6940 CKExplosionNodeFx_Load
    // vt+0x30 PostLoad 0x1b5fd8 (stays the default in C2.1).

    IKSerializable* m_pFxData;        // +0x14 the inline GetFxData (0x9abc50); Load sets 0 (every type)
    uint32_t m_unk18;                 // +0x18
    uint32_t m_unk1c;                 // +0x1c Load sets 0 (every type)
    TVector<SubEffect, 10> m_subEffects;  // +0x20 the constructor: null, 10, 0
    uint32_t m_unk2c;                 // +0x2c Load sets 0 (every type)
    uint32_t m_unk30;                 // +0x30 Load sets 0 (every type)
    RwMatrix* m_pMatrix;              // +0x34 Load (type 0): RwMatrixCreate
    uint32_t m_unk38;                 // +0x38
    uint32_t m_unk3c;                 // +0x3c
    uint32_t m_unk40;                 // +0x40 Load sets 0 (every type)
    uint32_t m_unk44;                 // +0x44
    int32_t m_unk48;                  // +0x48
    uint32_t m_unk4c;                 // +0x4c
};
static_assert(CKExplosionNodeFx::kClassKey == 0x1a4c, "key");
DOTD_ASSERT_SIZE(CKExplosionNodeFx::SubEffect, 0xc);
DOTD_ASSERT_SIZE(CKExplosionNodeFx, 0x50);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_subEffects, 0x20);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_pMatrix, 0x34);
DOTD_ASSERT_OFFSET(CKExplosionNodeFx, m_unk40, 0x40);
