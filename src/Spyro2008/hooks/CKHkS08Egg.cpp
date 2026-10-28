// CKHkS08Egg.cpp - reconstructed original translation unit 0x472af8-0x4740f0 (GAME_TOC1, main_toc1), 29 functions, 28 live.
// Primary class: CKHkS08Egg  key 0x2ac2  category Hook  size 0x70  vtable 0xb27820
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x472af8  CKHkS08Egg_Delete
//   [ ] 0x472b48  CKHkS08Egg_vfB4
//   [ ] 0x472b50  CKHkS08Egg_GetInfo
//   [ ] 0x472ba0  CKHkS08Egg_SpawnHatchFx_maybe
//   [x] 0x472e58  CKHkS08Egg_SetDefaultState
//   [ ] 0x472e80  CKHkS08Egg_Update
//   [ ] 0x472ea8  CKHkS08Egg_UpdateVisibilityFromFightZone_maybe  [dead]
//   [ ] 0x472f98  CKHkS08Egg_Resume
//   [ ] 0x472fc0  CKHkS08Egg_Pause
//   [ ] 0x472fe8  CKHkS08Egg_Stop
//   [ ] 0x473010  CKHkS08Egg_PostLoad
//   [ ] 0x473038  CKHkS08Egg_RecursiveRegistration
//   [ ] 0x473090  CKHkS08Egg_Destroy
//   [x] 0x4730b8  CKHkS08Egg_DeleteArray
//   [x] 0x473160  CKHkS08Egg_Create
//   [ ] 0x4731d0  RegisterCKHkS08EggClass
//   [ ] 0x473258  _GLOBAL__D_473258
//   [ ] 0x473268  _GLOBAL__I_473268
//   [ ] 0x473278  CKHkS08Egg_OnDeactivate
//   [ ] 0x4732d0  CKHkS08Egg_OnActivate
//   [ ] 0x473398  CKHkS08Egg_ReleaseNextEnemy_maybe
//   [ ] 0x473510  CKHkS08Egg_MessageProc
//   [ ] 0x473630  CKHkS08Egg_AssignEnemy_maybe
//   [ ] 0x4736d0  CKHkS08Egg_GetSpawnPoint_maybe
//   [x] 0x473740  CKHkS08Egg_CreateArray
//   [x] 0x473828  CKHkS08Egg_Load
//   [ ] 0x473c90  CKHkS08Egg_Save
//   [ ] 0x473ea8  CKHkS08Egg_Restart
//   [x] 0x473fc8  CKHkS08Egg_Start
//
//   [ ] 0x9c45a8  CKHkS08Egg_IsKindOfClass  [inline]
//   [ ] 0x9c4600  CKHkS08Egg_GetClassType  [inline]
//   [ ] 0x9c4608  CKHkS08Egg_GetClassID  [inline]
//   [ ] 0x9c4610  CKHkS08Egg_Destructor  [inline]
//   [ ] 0x9c4668  CKHkS08Egg_DeletingDestructor  [inline]
#include "Spyro2008/hooks/CKHkS08Egg.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/groups/CKGrpFightZone.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/memory/Mem.h"

// 0x00473828 CKHkS08Egg_Load: the actor base, then the same reads for every serialization type (the
// trigger starter gets the caller's type).
int32_t CKHkS08Egg::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    ReadU32LE(file, &m_unk54);
    // BUG(original): a new block of capacity 1 replaces the old one (leaked) and the length is not
    // reset; the elements are written from index 0 while the length keeps counting.
    m_vUnk20.m_ui32NbElt = 1;
    m_vUnk20.m_pBlock = static_cast<CVector3*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(CVector3))));
    for (uint32_t i = 0; i < m_unk54; ++i) {
        const uint32_t used = m_vUnk20.m_ui32NbUsedElt;
        if (m_vUnk20.m_ui32NbElt == used) {
            uint32_t capacity = used + 1;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(CVector3));
            if (capacity == 0) {
                capacity = 1;
                bytes = static_cast<uint32_t>(sizeof(CVector3));
            }
            m_vUnk20.m_pBlock = static_cast<CVector3*>(Mem_ReallocAligned16(m_vUnk20.m_pBlock, bytes & ~3u));
            m_vUnk20.m_ui32NbElt = capacity;
        }
        m_vUnk20.m_ui32NbUsedElt = used + 1;
        uint32_t words[3];  // one 12-byte read, then the three words swapped
        ReadU32LEWords(file, words, 3);
        std::memcpy(&m_vUnk20.m_pBlock[i], words, sizeof(words));
    }
    IKFile_ReadRef(file, &m_pUnk2C);
    ReadU32LE(file, &m_unk34);
    ReadF32LE(file, &m_fUnk38);
    ReadF32LE(file, &m_fUnk3C);
    ReadU32LE(file, &m_unk40);
    IKFile_ReadRef(file, &m_pUnk44);
    ReadF32LE(file, &m_fUnk48);
    ReadU8(file, &m_unk50);
    ReadF32LE(file, &m_fUnk5C);
    m_unk68.Load(file, type);
    ReadU8(file, &m_unk64);
    return 1;
}

// 0x00472e58 CKHkS08Egg_SetDefaultState: only the empty base call (KStub_Nop_3f72a0).
void CKHkS08Egg::SetDefaultState(int32_t /*flag*/) {}

// 0x00473fc8 CKHkS08Egg_Start
void CKHkS08Egg::Start() {
    // CKHkActorBase_d82_maybe_ResetRuntime 0x3f6e48: empty.
    CSGLeaf* object = static_cast<CSGLeaf*>(m_pKGLObject);
    if ((m_bitArray & 4u) != 0) {
        c22spyro::SetBeByte(m_unk30, 0, 0);  // the byte at +0x30
        m_unk60 = 0;
        m_unk4C = 0;
        m_unk58 = 0;
        return;
    }
    // CKGrpSquad_GetFightZone 0x25ab50: the squad's parent group; its byte +0x10e.
    CKGrpSquad* squad = static_cast<CKGrpSquad*>(m_pUnk2C);
    if (squad != nullptr && static_cast<CKGrpFightZone*>(squad->m_pParent)->m_unk10c[2] != 0) {
        c22spyro::SetBeByte(m_unk30, 0, 1);
        object->m_sgProperties = (object->m_sgProperties & 0xfffffffbu) | (static_cast<uint32_t>(m_unk50) << 2);
        m_unk60 = 0;
        m_unk4C = 0;
        m_unk58 = 0;
        return;
    }
    c22spyro::SetBeByte(m_unk30, 0, 0);
    object->m_sgProperties = (object->m_sgProperties & 0xfffffffbu) | 4u;
    m_unk60 = 0;
    m_unk4C = 0;
    m_unk58 = 0;
}
