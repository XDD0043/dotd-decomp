// KBase20CC.cpp - reconstructed original translation unit 0x1cbc50-0x1cd4a0 (GAME_TOC1, main_toc1), 16 functions, 14 live.
// Primary owner: KBase20CC (not a registered class)
// Other owners: InitializeParticleEffectFxData (2), CKParticlesEffectNodeFx (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1cbc50  KBase20CC_PostLoad
//   [ ] 0x1cbd30  KBase20CC_Save
//   [ ] 0x1cbd58  KBase20CC_LevelReset
//   [ ] 0x1cbd80  InitializeParticleEffectFxData_2  [dead]
//   [x] 0x1cbdb0  InitializeParticleEffectFxData
//   [ ] 0x1cbde0  KBase20CC_ResolveTriggerProperty
//   [ ] 0x1cbde8  KBase20CC_DeleteOwnedEntries_maybe
//   [ ] 0x1cbef8  KBase20CC_ClearReferences
//   [ ] 0x1cbf38  KBase20CC_DeletingDestructor
//   [ ] 0x1cbfb0  KBase20CC_Destructor
//   [ ] 0x1cc018  KBase20CC_Destructor_2
//   [x] 0x1cc080  KBase20CC_Load
//   [ ] 0x1cc750  KBase20CC_HandleMessage
//   [ ] 0x1cd350  CKParticlesEffectNodeFx_Delete
//   [ ] 0x1cd3a0  CKParticlesEffectNodeFx_Destroy
//   [ ] 0x1cd3a8  FUN_001cd3a8  [dead]
//
//   [ ] 0x9acc98  KBase20CC_IsKindOf  [inline]
//   [x] 0x9accd0  KBase20CC_GetClassGroup  [inline]
//   [x] 0x9accd8  KBase20CC_GetClassId  [inline]
#include "k2000/logic/CKParticlesEffectFxData.h"

#include <cstring>
#include <new>

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// One Read of count words, then every word byte-swapped in place (an lwbrx/stw loop on the PS3). The
// file is little-endian: on a little-endian host the bytes stay as they are.
void ReadWordsLE(IKFile* file, void* dst, uint32_t count) {
    ReadRaw(file, dst, count * 4);
    uint8_t* p = static_cast<uint8_t*>(dst);
    for (uint32_t i = 0; i < count; ++i, p += 4) {
        const uint32_t v = static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8) |
                           (static_cast<uint32_t>(p[2]) << 16) | (static_cast<uint32_t>(p[3]) << 24);
        std::memcpy(p, &v, 4);
    }
}
}  // namespace

// 0x001cbdb0 InitializeParticleEffectFxData: IKFxData, the vtable, the block list, +0x38.
CKParticlesEffectFxData::CKParticlesEffectFxData() {
    m_parameterBlocks.m_pBlock = nullptr;
    m_parameterBlocks.m_ui32NbElt = 1;
    m_parameterBlocks.m_ui32NbUsedElt = 0;
    m_unk38 = 0;
}

// 0x001cc080 KBase20CC_Load
int32_t CKParticlesEffectFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk0c);
    ReadU8(file, &m_unk08);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // The capacity is set to count before the block is allocated (the old block, if any, is not freed).
    m_parameterBlocks.m_ui32NbElt = count;
    m_parameterBlocks.m_pBlock =
        static_cast<ParameterBlock**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(ParameterBlock*))));
    for (uint32_t i = 0; i < count; ++i) {
        ParameterBlock* block = static_cast<ParameterBlock*>(::operator new(sizeof(ParameterBlock)));  // OperatorNew(0x6c)
        if (m_parameterBlocks.m_ui32NbElt == m_parameterBlocks.m_ui32NbUsedElt) {  // full: grow by 1
            uint32_t capacity = m_parameterBlocks.m_ui32NbUsedElt + 1;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(ParameterBlock*));
            if (capacity == 0) {
                capacity = 1;
                bytes = static_cast<uint32_t>(sizeof(ParameterBlock*));
            }
            m_parameterBlocks.m_pBlock =
                static_cast<ParameterBlock**>(Mem_ReallocAligned16(m_parameterBlocks.m_pBlock, bytes));
            m_parameterBlocks.m_ui32NbElt = capacity;
        }
        m_parameterBlocks.m_pBlock[m_parameterBlocks.m_ui32NbUsedElt] = block;
        ++m_parameterBlocks.m_ui32NbUsedElt;
        ReadU32LE(file, &block->m_unk38);
        ReadU32LE(file, &block->m_unk3c);
        ReadU32LE(file, &block->m_unk40);
        ReadU32LE(file, &block->m_unk44);
        ReadU32LE(file, &block->m_unk50);
        ReadU32LE(file, &block->m_unk54);
        ReadU32LE(file, &block->m_unk00);
        ReadU32LE(file, &block->m_unk04);
        ReadWordsLE(file, &block->m_unk08, 3);
        ReadWordsLE(file, &block->m_unk20, 3);
        ReadWordsLE(file, &block->m_unk2c, 3);
        ReadWordsLE(file, &block->m_unk14, 3);
        ReadU32LE(file, &block->m_unk48);
        ReadU32LE(file, &block->m_unk4c);
        ReadU32LE(file, &block->m_unk58);
        ReadU32LE(file, &block->m_unk5c);
        ReadU32LE(file, &block->m_unk60);
        ReadU32LE(file, &block->m_unk64);
        ReadU32LE(file, &block->m_unk68);
    }
    return 1;
}
