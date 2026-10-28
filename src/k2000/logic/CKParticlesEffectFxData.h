// CKParticlesEffectFxData.h - a particle effect's FX data: a list of parameter blocks (key 0x20cc,
// vtable 0xb1d470, size 0x3c). Original unit: KBase20CC.cpp (0x1cbc50-0x1cd4a0; Ghidra calls the class
// KBase20CC because the class tree lacks it, but its IsKindOfClass 0x9acc98 tests 0x20cc, 0x304c, 0x6 and
// 0xc and ClassTable registers 0x20cc as CKParticlesEffectFxData). Create and CreateArray
// (CreateParticleEffectFxData, ...Array) are in CKMeshPopFxData.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/util/TVector.h"

class CSGLeaf;

class CKParticlesEffectFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x83)
    DOTD_DECLARE_FACTORIES(CKParticlesEffectFxData)

    // 0x6c bytes (OperatorNew(0x6c), no vtable), every word read and byte-swapped. No block in the
    // front-end files, so the word types are not known (_maybe from the 12-byte reads: vectors).
    struct ParameterBlock {
        uint32_t m_unk00;   // +0x00
        uint32_t m_unk04;   // +0x04
        CVector3 m_unk08;   // +0x08 one 12-byte read
        CVector3 m_unk14;   // +0x14 one 12-byte read
        CVector3 m_unk20;   // +0x20 one 12-byte read
        CVector3 m_unk2c;   // +0x2c one 12-byte read
        uint32_t m_unk38;   // +0x38
        uint32_t m_unk3c;   // +0x3c
        uint32_t m_unk40;   // +0x40
        uint32_t m_unk44;   // +0x44
        uint32_t m_unk48;   // +0x48
        uint32_t m_unk4c;   // +0x4c
        uint32_t m_unk50;   // +0x50
        uint32_t m_unk54;   // +0x54
        uint32_t m_unk58;   // +0x58
        uint32_t m_unk5c;   // +0x5c
        uint32_t m_unk60;   // +0x60
        uint32_t m_unk64;   // +0x64
        uint32_t m_unk68;   // +0x68
    };

    CKParticlesEffectFxData();  // 0x001cbdb0 InitializeParticleEffectFxData

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001cc080 KBase20CC_Load
    // vt+0x30 PostLoad 0x1cbc50 (stays the default in C1.3): sets +0x10..+0x24 and +0x34 (an RwMatrix
    // at +0x24).
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x1fcc; }  // vt+0x54 0x1cbc48

    uint8_t m_unk08;                                 // +0x08
    uint8_t m_pad09[3];
    uint32_t m_unk0c;                                // +0x0c
    // +0x10 PostLoad sets 0; the effect's start sets the scene node the effect is attached to (Ghidra
    // pAttachOwner_maybe): its GetSectorIndex (vt+0x6c) tells which sector the effect belongs to.
    CSGLeaf* m_pAttachOwner;
    uint32_t m_unk14;                                // +0x14 PostLoad
    CVector3 m_unk18;                                // +0x18 PostLoad
    void* m_unk24;                                   // +0x24 PostLoad: RwMatrixCreate
    TVector<ParameterBlock*, 1> m_parameterBlocks;   // +0x28 (Ghidra ppParameterBlocks_maybe); the
                                                     // constructor: null, 1, 0
    uint32_t m_unk34;                                // +0x34 PostLoad
    uint8_t m_unk38;                                 // +0x38 the constructor sets 0
    uint8_t m_pad39[3];
};
DOTD_ASSERT_SIZE(CKParticlesEffectFxData::ParameterBlock, 0x6c);
DOTD_ASSERT_SIZE(CKParticlesEffectFxData, 0x3c);
DOTD_ASSERT_OFFSET(CKParticlesEffectFxData, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKParticlesEffectFxData, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKParticlesEffectFxData, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKParticlesEffectFxData, m_parameterBlocks, 0x28);
DOTD_ASSERT_OFFSET(CKParticlesEffectFxData, m_unk38, 0x38);
