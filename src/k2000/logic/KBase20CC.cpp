// KBase20CC.cpp - reconstructed original translation unit 0x1cbc50-0x1cd4a0 (GAME_TOC1, main_toc1), 16 functions, 14 live.
// Primary owner: KBase20CC (not a registered class)
// Other owners: InitializeParticleEffectFxData (2), CKParticlesEffectNodeFx (2)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1cbc50  KBase20CC_PostLoad
//   [ ] 0x1cbd30  KBase20CC_Save
//   [x] 0x1cbd58  KBase20CC_LevelReset  (CKParticlesEffectFxData_RecursiveRegistration: KStub_Return1_1d8340, nothing: the default slot)
//   [ ] 0x1cbd80  InitializeParticleEffectFxData_2  [dead]
//   [x] 0x1cbdb0  InitializeParticleEffectFxData
//   [x] 0x1cbde0  KBase20CC_ResolveTriggerProperty  (GetInfo: returns 1, the default slot)
//   [x] 0x1cbde8  KBase20CC_DeleteOwnedEntries_maybe  (CKParticlesEffectFxData::DeleteOwnedEntries)
//   [x] 0x1cbef8  KBase20CC_ClearReferences  (CKParticlesEffectFxData::Destroy)
//   [x] 0x1cbf38  KBase20CC_DeletingDestructor  (the destructor; delete)
//   [x] 0x1cbfb0  KBase20CC_Destructor  (~CKParticlesEffectFxData)
//   [x] 0x1cc018  KBase20CC_Destructor_2  (~CKParticlesEffectFxData (a second copy))
//   [x] 0x1cc080  KBase20CC_Load
//   [x] 0x1cc750  KBase20CC_HandleMessage
//   [x] 0x1cd350  CKParticlesEffectNodeFx_Delete  (CKParticlesEffectNodeFx's factory Delete: DOTD_DECLARE_FACTORIES)
//   [x] 0x1cd3a0  CKParticlesEffectNodeFx_Destroy  (CKParticlesEffectNodeFx::Destroy, CKParticlesEffectNodeFx.h: empty (IKNodeFx's is not called))
//   [ ] 0x1cd3a8  FUN_001cd3a8  [dead]
//
//   [ ] 0x9acc98  KBase20CC_IsKindOf  [inline]
//   [x] 0x9accd0  KBase20CC_GetClassGroup  [inline]
//   [x] 0x9accd8  KBase20CC_GetClassId  [inline]
#include "k2000/logic/CKParticlesEffectFxData.h"

#include <cstring>
#include <new>

#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/math/Quat.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvFx.h"

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
    m_bScreenSpace = 0;
}

// 0x001cc080 KBase20CC_Load
int32_t CKParticlesEffectFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk0c);
    ReadU8(file, &m_ui8Flags);
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

// 0x001cbc50 KBase20CC_PostLoad: the base's PostLoad (0x1d8338 KStub_Return1), then for type 0 the run-time part.
int32_t CKParticlesEffectFxData::PostLoad(int32_t type) {
    IKFxData::PostLoad(type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_pReservedFx = nullptr;
    m_vPosition = {0.0f, 0.0f, 0.0f};  // the vector at 0x00c50d64 (TOC -0x1bf0)
    m_pAttachHotSpot = nullptr;
    m_pAttachOwner = nullptr;
    RwMatrix* matrix = RwMatrixCreate();  // RwMatrixCreate_Thunk 0x23fa68
    m_pLocalMatrix = matrix;
    matrix->flags = 0x20003u;
    matrix->right = {1.0f, 0.0f, 0.0f};  // TOC -0x1bec 1.0f
    matrix->up = {0.0f, 1.0f, 0.0f};
    matrix->at = {0.0f, 0.0f, 1.0f};
    matrix->pos = {0.0f, 0.0f, 0.0f};
    return 1;
}

// 0x001cc750 CKParticlesEffectFxData_MessageProc (Ghidra KBase20CC_HandleMessage)
int32_t CKParticlesEffectFxData::MessageProc(uint16_t message, void* data) {
    if (message == 0x1b02) {
        if (m_pReservedFx != nullptr) {
            m_pReservedFx->StopAndRelease(this);  // vt+0x58
            m_pReservedFx = nullptr;
        }
        return 0;
    }
    if (message != 0x1b00 && message != 0x1b01) return 1;
    IKSerializable* object = *static_cast<IKSerializable* const*>(data);
    if (object == nullptr) return 0;
    if (message == 0x1b01) {
        m_pAttachOwner = static_cast<CSGLeaf*>(object);
    } else {
        // The marker beacon's position and orientation (read through the members: the original reads +0x04 / +0x10 of
        // the object sent; LVL010 sends CKMarkerBeacons).
        const CKMarkerBeacon* marker = static_cast<const CKMarkerBeacon*>(object);
        m_vPosition = marker->m_v3Position;
        CMatrix34* matrix = reinterpret_cast<CMatrix34*>(m_pLocalMatrix);
        Quat_ToMatrixNormalizing(marker->m_qOrientation, matrix);  // 0x00241d78
        matrix->m_pos = marker->m_v3Position;
        matrix->m_ui32Flags &= 0xfffdffffu;
        m_pAttachHotSpot = nullptr;
        m_pAttachOwner = nullptr;
    }
    CKSrvFx* service = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    if ((m_ui8Flags & 8) == 0 && (m_ui8Flags & 4) == 0) {
        if (m_pReservedFx != nullptr) {
            m_pReservedFx->StopAndRelease(this);  // vt+0x58
            m_pReservedFx = nullptr;
        }
        m_pReservedFx = service->AcquireFx(this, this);  // the reserving pool lookup, inlined
        return 0;
    }
    service->StartEffect(this, this);  // inlined (pooled: the first free effect; unique: SetDataAndOwner)
    return 0;
}

// 0x001cbde8 KBase20CC_DeleteOwnedEntries_maybe
void CKParticlesEffectFxData::DeleteOwnedEntries() {
    const uint32_t count = m_parameterBlocks.m_ui32NbUsedElt;
    for (uint32_t i = 0; i != count; ++i) {
        ParameterBlock** blocks = m_parameterBlocks.m_pBlock;
        if (blocks[0] != nullptr) {
            ::operator delete(blocks[0]);  // OperatorDelete_Bridge
            blocks = m_parameterBlocks.m_pBlock;
        }
        const uint32_t used = --m_parameterBlocks.m_ui32NbUsedElt;
        std::memmove(blocks, blocks + 1, static_cast<size_t>(used & 0x3fffffffu) * sizeof(ParameterBlock*));  // x 4 on the PS3
        int32_t capacity = static_cast<int32_t>(m_parameterBlocks.m_ui32NbElt - 1);
        uint32_t bytes = (static_cast<uint32_t>(capacity) & 0x3fffffffu) * static_cast<uint32_t>(sizeof(ParameterBlock*));
        if (static_cast<int32_t>(m_parameterBlocks.m_ui32NbUsedElt) <= capacity) {  // shrink by one
            if (capacity == 0) {
                capacity = 1;
                bytes = static_cast<uint32_t>(sizeof(ParameterBlock*));  // 4 on the PS3
            }
            m_parameterBlocks.m_pBlock = static_cast<ParameterBlock**>(Mem_ReallocAligned16(m_parameterBlocks.m_pBlock, bytes));
            m_parameterBlocks.m_ui32NbElt = static_cast<uint32_t>(capacity);
        }
    }
    m_parameterBlocks.m_ui32NbUsedElt = 0;
    m_parameterBlocks.m_pBlock = static_cast<ParameterBlock**>(Mem_ReallocAligned16(m_parameterBlocks.m_pBlock, static_cast<uint32_t>(sizeof(ParameterBlock*))));
    m_parameterBlocks.m_ui32NbElt = 1;
}

// 0x001cbef8 KBase20CC_ClearReferences (CKParticlesEffectFxData_Destroy)
void CKParticlesEffectFxData::Destroy() {
    RwMatrixDestroy(m_pLocalMatrix);  // RwMatrixDestroy_Thunk 0x0023f968
    m_pLocalMatrix = nullptr;
    DeleteOwnedEntries();
}
