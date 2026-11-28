// CKExplosionFxData.cpp - reconstructed original translation unit 0x1b3510-0x1b5d98 (GAME_TOC1, main_toc1), 17 functions, 11 live.
// Primary class: CKExplosionFxData  key 0x1a8c  category Logic  size 0x3c  vtable 0xb1c988
// Other owners: Vt (3), CKExplosionNodeFx (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1b3510  CKExplosionFxData_CreateElementByType_maybe
//   [x] 0x1b36f0  CKExplosionFxData_PostLoad
//   [x] 0x1b37a0  CKExplosionFxData_RecursiveRegistration
//   [ ] 0x1b3920  FUN_001b3920  [dead]
//   [x] 0x1b3990  CKExplosionFxData_GetInfo  (returns 1: the default slot)
//   [x] 0x1b3998  Vt_b1c970_DeletingDestructor_maybe  (C++ deleting destructor)
//   [x] 0x1b39c8  Vt_b1c970_Destructor_maybe  (C++ destructor chain: vtable stores only)
//   [ ] 0x1b39d8  Vt_b1c970_Destructor_2_maybe  [dead]
//   [x] 0x1b39e8  CKExplosionFxData_Destroy
//   [ ] 0x1b3b20  CKExplosionFxData_ReleaseAndDestroyAllEntries_maybe  [dead]
//   [x] 0x1b3c78  CKExplosionFxData_MessageProc
//   [x] 0x1b4328  CKExplosionFxData_Load
//   [ ] 0x1b4ea8  CKExplosionFxData_Save
//   [x] 0x1b5ca8  CKExplosionNodeFx_Delete  (CKExplosionNodeFx's factory Delete: DOTD_DECLARE_FACTORIES)
//   [ ] 0x1b5cf8  FUN_001b5cf8  [dead]
//   [ ] 0x1b5d18  FUN_001b5d18  [dead]
//   [ ] 0x1b5d88  FUN_001b5d88  [dead]
//
//   [ ] 0x9aba20  CKExplosionFxData_IsKindOfClass  [inline]
//   [x] 0x9aba58  CKExplosionFxData_GetClassType  [inline]
//   [x] 0x9aba60  CKExplosionFxData_GetClassID  [inline]
//   [ ] 0x9abad8  CKExplosionFxData_DeletingDestructor  [inline]
//   [ ] 0x9abba0  CKExplosionFxData_Destructor  [inline]
#include "k2000/logic/fx/CKExplosionFxData.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/fx/IKFx.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/math/Quat.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvFx.h"
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

// CVector3 globals the type-1 part copies (initialised at run time; these are their live values):
// 0xc50d40 and 0xc50d64. XXL2 has no such named constants.
const CVector3 kVector3_c50d40 = {0.0f, 1.0f, 0.0f};
const CVector3 kVector3_c50d64 = {0.0f, 0.0f, 0.0f};
}  // namespace

// 0x001ae948 CKExplosionFxData_Create, the inlined constructor: the part list only.
CKExplosionFxData::CKExplosionFxData() {
    m_parts.m_pBlock = nullptr;
    m_parts.m_ui32NbElt = 10;
    m_parts.m_ui32NbUsedElt = 0;
}

// The type-0 part as CreatePart builds it, in the original's store order.
CKExplosionFxData::PartType0::PartType0() {
    m_overrides.m_emtSize.x = 1.0f;
    m_overrides.m_prtInitDir.x = 0.0f;
    m_overrides.m_prtInitDirBias.x = 0.0f;
    m_overrides.m_force.x = 0.0f;
    m_overrides.m_emtPrtEmitBias = 0;
    m_type = 0;
    m_overrides.m_emtPrtEmit = 0;
    m_overrides.m_prtInitVel = 5.0f;
    m_unk08 = 0.0f;
    m_overrides.m_prtInitVelBias = 1.0f;
    m_overrides.m_prtSize[0] = 1.0f;
    m_overrides.m_prtSize[1] = 1.0f;
    m_overrides.m_prtSize[4] = 1.0f;
    m_overrides.m_prtSize[5] = 1.0f;
    m_overrides.m_prtSize[2] = 0.0f;
    m_overrides.m_prtSize[3] = 0.0f;
    m_overrides.m_prtSize[6] = 0.0f;
    m_overrides.m_prtSize[7] = 0.0f;
    m_overrides.m_emtSize.z = 1.0f;
    m_overrides.m_emtSize.y = 1.0f;
    m_overrides.m_prtInitDir.z = 0.0f;
    m_overrides.m_prtInitDir.y = 0.0f;
    m_overrides.m_prtInitDirBias.z = 0.0f;
    m_overrides.m_prtInitDirBias.y = 0.0f;
    m_overrides.m_force.z = 0.0f;
    m_overrides.m_force.y = 0.0f;
    m_overrides.m_overrideMask = 0x1ff;
}

// The type-1 part as CreatePart builds it, in the original's store order.
CKExplosionFxData::PartType1::PartType1() {
    m_unk14 = 5.0f;
    m_type = 1;
    m_unk08 = 0.0f;  // an integer 0 store
    m_unk18 = 1.0f;
    m_pObject = nullptr;
    m_unk1c = kVector3_c50d40;
    m_unk28 = kVector3_c50d64;
    m_unk10 = 0;
    m_unk34 = kVector3_c50d64;
}

// A part of types 2..8 as CreatePart builds it.
CKExplosionFxData::PartObject::PartObject(uint32_t type) {
    m_unk08 = 0.0f;  // an integer 0 store
    m_pObject = nullptr;
    m_type = type;
}

// 0x001b3510 CKExplosionFxData_CreateElementByType_maybe: OperatorNew(0x70 / 0x40 / 0x10).
CKExplosionFxData::Part* CKExplosionFxData::CreatePart(uint32_t type) {
    if (type == 1) return new PartType1();
    if (type < 1) return new PartType0();
    if (type > 8) return nullptr;
    return new PartObject(type);
}

// 0x001b4328 CKExplosionFxData_Load
int32_t CKExplosionFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fDuration);
    ReadF32LE(file, &m_fWaveFinalRadiusPrec);
    ReadF32LE(file, &m_fWaveGrowth);
    ReadF32LE(file, &m_fWaveRadius);
    IKFile_ReadRef(file, &m_pSoundDico);
    IKFile_ReadRef(file, &m_pVibrationPadData);
    ReadU8(file, &m_baExpInfos);
    ReadRaw(file, m_cColor, 4);
    IKFile_ReadRef(file, &m_pQuakeLauncher);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) return 1;
    // The capacity is set to count before the block is allocated (the old block, if any, is not freed).
    m_parts.m_ui32NbElt = count;
    m_parts.m_pBlock = static_cast<Part**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Part*))));
    for (uint32_t i = 0; i < count; ++i) {
        uint32_t partType = 0;
        ReadU32LE(file, &partType);
        Part* created = CreatePart(partType);
        if (m_parts.m_ui32NbElt == m_parts.m_ui32NbUsedElt) {  // full: grow by 10
            uint32_t capacity = m_parts.m_ui32NbUsedElt + 10;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(Part*));
            if (capacity == 0) {
                capacity = 10;
                bytes = 10 * static_cast<uint32_t>(sizeof(Part*));
            }
            m_parts.m_pBlock = static_cast<Part**>(Mem_ReallocAligned16(m_parts.m_pBlock, bytes));
            m_parts.m_ui32NbElt = capacity;
        }
        m_parts.m_pBlock[m_parts.m_ui32NbUsedElt] = created;
        ++m_parts.m_ui32NbUsedElt;
        // The part is read back by the loop index, not by its push position.
        // BUG(original): a type above 8 creates no part, and the next line reads the null part's type.
        Part* part = m_parts.m_pBlock[i];
        const uint32_t kind = part->m_type;
        if (kind == 1) {
            PartType1* p = static_cast<PartType1*>(part);
            IKFile_ReadRef(file, &p->m_pObject);
            ReadU32LE(file, &p->m_unk10);
            ReadF32LE(file, &p->m_unk14);
            ReadF32LE(file, &p->m_unk18);
            ReadWordsLE(file, &p->m_unk1c, 3);
            ReadWordsLE(file, &p->m_unk28, 3);
            ReadWordsLE(file, &p->m_unk34, 3);
        } else if (kind == 0) {
            PartType0* p = static_cast<PartType0*>(part);
            ReadF32LE(file, &p->m_overrides.m_prtInitVel);
            ReadF32LE(file, &p->m_overrides.m_prtInitVelBias);
            ReadF32LE(file, &p->m_overrides.m_prtSize[0]);
            ReadF32LE(file, &p->m_overrides.m_prtSize[1]);
            ReadF32LE(file, &p->m_overrides.m_prtSize[4]);
            ReadF32LE(file, &p->m_overrides.m_prtSize[5]);
            ReadU32LE(file, &p->m_overrides.m_emtPrtEmit);
            ReadU32LE(file, &p->m_overrides.m_emtPrtEmitBias);
            ReadWordsLE(file, &p->m_overrides.m_emtSize, 3);
            ReadWordsLE(file, &p->m_overrides.m_prtInitDir, 3);
            ReadWordsLE(file, &p->m_overrides.m_prtInitDirBias, 3);
            ReadWordsLE(file, &p->m_overrides.m_force, 3);
            ReadF32LE(file, &p->m_overrides.m_prtSize[2]);
            ReadF32LE(file, &p->m_overrides.m_prtSize[3]);
            ReadF32LE(file, &p->m_overrides.m_prtSize[6]);
            ReadF32LE(file, &p->m_overrides.m_prtSize[7]);
        } else if (kind <= 8) {
            IKFile_ReadRef(file, &static_cast<PartObject*>(part)->m_pObject);
        }
        ReadF32LE(file, &part->m_unk08);
    }
    return 1;
}

// 0x001b3c78 CKExplosionFxData_MessageProc
int32_t CKExplosionFxData::MessageProc(uint16_t message, void* data) {
    if (message != 0x1b00 && message != 0x1b02) return 1;
    const uint8_t* object = *static_cast<uint8_t* const*>(data);
    if (object == nullptr) return 0;
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(this, this);  // the inline pool lookup
    if (fx == nullptr) return 0;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
    CMatrix34 matrix;
    if (message == 0x1b00) {
        // The placement: the quaternion at +0x10, the position at +0x04 (the original reads those words of any object;
        // LVL010 sends CKMarkerBeacons, whose m_qOrientation / m_v3Position they are). Read through the members: on a
        // 64-bit host the vtable pointer moves them.
        const CKMarkerBeacon* marker = reinterpret_cast<const CKMarkerBeacon*>(object);
        float q[4];
        std::memcpy(q, marker->m_qOrientation, sizeof q);
        Quat_ToMatrixNormalizing(q, &matrix);  // 0x00241d78
        const CVector3 p = marker->m_v3Position;
        matrix.m_pos.z = p.z;
        matrix.m_pos.x = p.x;
        matrix.m_pos.y = p.y;
        matrix.m_ui32Flags &= 0xfffdffffu;
    } else {
        const IKHook* hook = reinterpret_cast<const IKHook*>(object);
        const CSGMovable* node = static_cast<const CSGMovable*>(hook->m_pKGLObject);  // +0x1c
        if (node != nullptr) {
            // The node frame's LTM (+0x50), its pad words too, orthonormalised.
            std::memcpy(&matrix, FrameLtm(node->m_pRwFrame), sizeof matrix);
        } else {
            matrix = {};
            matrix.m_right.x = 1.0f;  // TOC1 -0x21b0
            matrix.m_ui32Flags = 0x20003u;
            matrix.m_at.z = 1.0f;
            matrix.m_up.y = 1.0f;
        }
        Mat4_OrthoNormalizeInPlace(&matrix);  // 0x0023f648
    }
    explosion->SetMatrix(reinterpret_cast<const RwMatrix*>(&matrix), this);  // 0x001b6368
    explosion->Trigger(this, 0);                                            // 0x001b82a8
    explosion->ReleaseReservation(this);                                    // vt+0x54
    return 0;
}

// 0x001b36f0 CKExplosionFxData_PostLoad (last sound first; a missing sound or one without a sample is skipped)
int32_t CKExplosionFxData::PostLoad(int32_t /*type*/) {
    m_ui32LoadedSoundCount = 0;
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pSoundDico);
    if (sounds == nullptr) return 1;
    for (uint32_t i = sounds->m_ui32NbKSound; i != 0;) {
        --i;
        CKSound* sound = sounds->GetSound(i);  // 0x00112bc0
        if (sound == nullptr || sound->GetSample() == nullptr) continue;  // 0x00111000
        ++m_ui32LoadedSoundCount;
    }
    return 1;
}

// 0x001b37a0 CKExplosionFxData_RecursiveRegistration (C2.8 save-menu)
void CKExplosionFxData::RecursiveRegistration(int32_t type) {
    if (type == 0) {
        m_pSoundDico->RecursiveRegistration(0);
        if (m_pVibrationPadData != nullptr) m_pVibrationPadData->RecursiveRegistration(0);
        m_pQuakeLauncher->RecursiveRegistration(0);
    }
    for (uint32_t i = 0; i < m_parts.m_ui32NbUsedElt; ++i) {
        Part* part = m_parts.m_pBlock[i];
        if (part->m_type < 1) continue;
        // +0x0c: PartType1::m_pObject or PartObject::m_pObject.
        IKSerializable* object = part->m_type == 1 ? static_cast<PartType1*>(part)->m_pObject
                                                   : static_cast<PartObject*>(part)->m_pObject;
        if (object != nullptr) object->RecursiveRegistration(type);
    }
}

// 0x001b39e8 CKExplosionFxData_Destroy
void CKExplosionFxData::Destroy() {
    const uint32_t count = m_parts.m_ui32NbUsedElt;
    uint32_t used = count;
    for (uint32_t i = 0; i != count; ++i) {
        Part** block = m_parts.m_pBlock;
        Part* part = block[0];
        m_parts.m_ui32NbUsedElt = used - 1;
        std::memmove(block, block + 1, static_cast<size_t>(used - 1) * sizeof(Part*));  // (used - 1) * 4 on the PS3
        int32_t capacity = static_cast<int32_t>(m_parts.m_ui32NbElt - 10);
        if (static_cast<int32_t>(m_parts.m_ui32NbUsedElt) <= capacity) {  // shrink by 10
            if (capacity == 0) capacity = 10;  // 0x28 bytes
            m_parts.m_pBlock = static_cast<Part**>(
                Mem_ReallocAligned16(m_parts.m_pBlock, static_cast<uint32_t>((static_cast<uint32_t>(capacity) & 0x3fffffffu) * sizeof(Part*))));
            m_parts.m_ui32NbElt = static_cast<uint32_t>(capacity);
        }
        if (part != nullptr) delete part;  // vt+0x04
        used = m_parts.m_ui32NbUsedElt;
    }
    m_parts.m_ui32NbUsedElt = 0;
    m_parts.m_pBlock = static_cast<Part**>(Mem_ReallocAligned16(m_parts.m_pBlock, static_cast<uint32_t>(10 * sizeof(Part*))));
    m_parts.m_ui32NbElt = 10;
}
