// CKSrvFx.cpp - reconstructed original translation unit 0x1ab2b0-0x1ad058 (GAME_TOC1, main_toc1), 36 functions, 36 live.
// Primary class: CKSrvFx  key 0x381  category Service  size 0x30  vtable 0xb1c590
// Other owners: CKFlashFxData (1), CKElectricArcFxData (1), CKQuadFxData (1), CKLightningObjectFxData (1), CKFilterFxData (1), CKExplosionFxData (1), CKHedgeHopTrailFxData (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1ab2b0  CKSrvFx_Delete
//   [x] 0x1ab300  CKSrvFx_InitializeService
//   [x] 0x1ab308  CKSrvFx_DestroyService
//   [ ] 0x1ab310  CKSrvFx_RecursiveRegistration
//   [ ] 0x1ab460  RegisterCKSrvFxClass
//   [ ] 0x1ab4d8  _GLOBAL__I_1ab4d8
//   [ ] 0x1ab4e8  CKSrvFx_Start
//   [x] 0x1ab558  CKSrvFx_Destroy
//   [x] 0x1ab6e0  CKSrvFx_DeleteArray
//   [x] 0x1ab788  CKSrvFx_Construct
//   [ ] 0x1ab7e8  CKSrvFx_Construct_2
//   [x] 0x1ab848  CKSrvFx_SectorUnload
//   [x] 0x1ab990  CKSrvFx_PostLoad
//   [x] 0x1abc50  CKSrvFx_Stop
//   [ ] 0x1abe28  CKSrvFx_Restart
//   [x] 0x1ac000  UpdateCKSrvFx
//   [ ] 0x1ac210  CKSrvFx_Pause
//   [ ] 0x1ac3c0  CKSrvFx_Resume
//   [ ] 0x1ac570  CKSrvFx_Save
//   [x] 0x1ac578  CKSrvFx_CreateArray
//   [x] 0x1ac688  CKSrvFx_Create
//   [x] 0x1ac708  CKSrvFx_Load
//   [ ] 0x1acbf8  CKFlashFxData_Delete
//   [ ] 0x1acc48  CKElectricArcFxData_Delete
//   [ ] 0x1acc98  CKQuadFxData_Delete
//   [ ] 0x1acce8  CKLightningObjectFxData_Delete
//   [ ] 0x1acd38  CKFilterFxData_Delete
//   [ ] 0x1acd88  CKExplosionFxData_Delete
//   [ ] 0x1acdd8  CKHedgeHopTrailFxData_Delete
//   [ ] 0x1ace28  CKShockWaveFxData_Destroy
//   [ ] 0x1ace78  CKFireBallFxData_Delete
//   [ ] 0x1acec8  CKParticlesEffectFxData_Destroy
//   [ ] 0x1acf18  CKSparkFxData_Destroy
//   [ ] 0x1acf68  CKLensFlareFxData_Delete
//   [ ] 0x1acfb8  CKDistortionFxData_Delete
//   [ ] 0x1ad008  CKMeshPopFxData_Delete
//
//   [ ] 0x9ab2f0  CKSrvFx_IsKindOfClass  [inline]
//   [ ] 0x9ab328  CKSrvFx_GetClassType  [inline]
//   [ ] 0x9ab330  CKSrvFx_GetClassID  [inline]
//   [ ] 0x9ab338  CKSrvFx_Destructor  [inline]
//   [ ] 0x9ab358  CKSrvFx_DeletingDestructor  [inline]
//   [ ] 0x9ab3a0  KStub_Return0_9ab3a0  [inline]
//   [ ] 0x9bdc18  CKSrvFx_AcquireFx  [inline]
//   [ ] 0x9c6468  CKSrvFx_AcquireFx_2  [inline]
#include "k2000/services/CKSrvFx.h"

#include "k2000/components/CKParticlesCpnt.h"
#include "k2000/fx/IKFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"

// 0x001ab788 CKSrvFx_Construct (the same stores inlined in 0x1ac688 CKSrvFx_Create).
CKSrvFx::CKSrvFx() {
    m_ui32Priority = 0x64;
    Engine_SetSrvFx(this);
}

// 0x001ab558 CKSrvFx_Destroy: every mapping's effect arrays and its type table, the emitter array, the table, the flat and the
// unique effect arrays freed.
void CKSrvFx::Destroy() {
    if (m_apMappingIndexTable != nullptr) {
        for (uint32_t i = 0; i < m_ui32EltNb; ++i) {
            CMappingindex& mapping = m_apMappingIndexTable[i];
            if (mapping.m_aUnderMapping == nullptr) continue;
            for (uint32_t k = 0; k < mapping.m_ui32NbTypeFx; ++k) {
                Mem_FreeAligned16(mapping.m_aUnderMapping[k].m_apFxArrayForTypeId);
            }
            delete[] mapping.m_aUnderMapping;
        }
    }
    if (m_apPartEmitter != nullptr) {
        Mem_FreeAligned16(m_apPartEmitter);
        m_apPartEmitter = nullptr;
    }
    // BUG(original): the three arrays below are freed and their pointers kept (the next Load replaces them).
    if (m_apMappingIndexTable != nullptr) delete[] m_apMappingIndexTable;
    if (m_apFxArray != nullptr) Mem_FreeAligned16(m_apFxArray);
    if (m_apUniqueFxArray != nullptr) delete[] m_apUniqueFxArray;
}

// 0x001ac708 CKSrvFx_Load (XXL2 also has CMappingindex::Load; on the PS3 it is inlined).
int32_t CKSrvFx::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32EltNb);
    if (m_ui32EltNb == 0) {
        m_apMappingIndexTable = nullptr;
    } else {
        m_apMappingIndexTable = new CMappingindex[m_ui32EltNb];
        for (uint32_t i = 0; i < m_ui32EltNb; ++i) {
            CMappingindex& mapping = m_apMappingIndexTable[i];
            ReadU32LE(file, &mapping.m_ui32NbTypeFx);
            if (mapping.m_ui32NbTypeFx == 0) {
                mapping.m_aUnderMapping = nullptr;
            } else {
                mapping.m_aUnderMapping = new CUnderMappingindex[mapping.m_ui32NbTypeFx];
                for (uint32_t j = 0; j < mapping.m_ui32NbTypeFx; ++j) {
                    CUnderMappingindex& under = mapping.m_aUnderMapping[j];
                    ReadU32LE(file, &under.m_ui32MaxSize);
                    ReadS32LE(file, &under.m_i32FxTypeId);
                    under.m_apFxArrayForTypeId = nullptr;
                    if (under.m_ui32MaxSize == 0) continue;
                    under.m_apFxArrayForTypeId = static_cast<IKSerializable**>(
                        Mem_AllocAligned16(under.m_ui32MaxSize * static_cast<uint32_t>(sizeof(IKSerializable*))));
                    for (uint32_t k = 0; k < under.m_ui32MaxSize; ++k) IKFile_ReadRef(file, &under.m_apFxArrayForTypeId[k]);
                }
            }
            ReadU32LE(file, &mapping.m_ui32ClassId);
        }
    }
    m_apFxArray = nullptr;
    ReadU32LE(file, &m_ui32NbPartEmitter);
    if (m_ui32NbPartEmitter == 0) {
        m_apPartEmitter = nullptr;
    } else {
        m_apPartEmitter = static_cast<IKSerializable**>(
            Mem_AllocAligned16(m_ui32NbPartEmitter * static_cast<uint32_t>(sizeof(IKSerializable*))));
        for (uint32_t i = 0; i < m_ui32NbPartEmitter; ++i) IKFile_ReadRef(file, &m_apPartEmitter[i]);
    }
    ReadU32LE(file, &m_ui32UniqueFxArraySize);
    if (m_ui32UniqueFxArraySize == 0) {
        m_apUniqueFxArray = nullptr;
    } else {
        m_apUniqueFxArray = new IKSerializable*[m_ui32UniqueFxArraySize];
        IKFile_ReadObjectRefArray(file, m_apUniqueFxArray, m_ui32UniqueFxArraySize);
    }
    return 1;
}

namespace {
// The pools are IKFx pointers (XXL2: IKFx*).
IKFx* FxAt(IKSerializable** pool, uint32_t index) { return static_cast<IKFx*>(pool[index]); }

// CKSrvFx_Stop's loop over one pool.
void StopPool(IKSerializable** pool, uint32_t count) {
    for (uint32_t i = 0; i < count; ++i) {
        IKFx* fx = FxAt(pool, i);
        const uint8_t flags = fx->m_baFxData;
        fx->m_baFxData = static_cast<uint8_t>(flags & 0xfd);
        if ((fx->m_baFxData & 1) != 0) {
            fx->m_baFxData = static_cast<uint8_t>((flags & 0xfc) | 1);
        } else {
            fx->Stop();
            fx->m_baFxData = static_cast<uint8_t>((fx->m_baFxData & 0xfe) | 1);
        }
    }
}
}  // namespace

// 0x001ab848 CKSrvFx_SectorUnload
void CKSrvFx::SectorUnload(int32_t sector) {
    for (uint32_t i = 0; i < m_ui32FxArraySize; ++i) FxAt(m_apFxArray, i)->StopIfLinkedTo(sector);
    for (uint32_t i = 0; i < m_ui32UniqueFxArraySize; ++i) FxAt(m_apUniqueFxArray, i)->StopIfLinkedTo(sector);
    for (uint32_t i = 0; i < m_ui32NbPartEmitter; ++i) static_cast<CKParticlesCpnt*>(m_apPartEmitter[i])->FlushEmissionRequests();
}

// 0x001abc50 CKSrvFx_Stop: every pooled effect that is not stopped yet is stopped (vt+0x6c), and loses its
// reservation (bit 1); then the particle components' queued emissions dropped.
void CKSrvFx::Stop() {
    StopPool(m_apFxArray, m_ui32FxArraySize);
    StopPool(m_apUniqueFxArray, m_ui32UniqueFxArraySize);
    for (uint32_t i = 0; i < m_ui32NbPartEmitter; ++i) static_cast<CKParticlesCpnt*>(m_apPartEmitter[i])->FlushEmissionRequests();
}

// 0x001ac000 UpdateCKSrvFx (vt+0x7c): every running effect of both pools (the stopped bit clear) has its frame (vt+0x78)
// unless the clock is paused (IKTime +0x30) and the effect does not update while paused (vt+0x94); then, unless paused,
// the particle components' queued emissions. STUB(C2.7): ProcessParticleComponentEmissionQueue 0x1da1a8 (the particle
// emitters are not ported).
void CKSrvFx::Update(IKTime* frameClock) {
    for (uint32_t i = 0; i < m_ui32FxArraySize; ++i) {
        IKFx* fx = FxAt(m_apFxArray, i);
        if ((fx->m_baFxData & 1) != 0) continue;
        if (frameClock->m_eCurrentState != 0 && fx->GetUpdateWhenPaused() == 0) continue;
        fx->Update(frameClock);
    }
    for (uint32_t i = 0; i < m_ui32UniqueFxArraySize; ++i) {
        IKFx* fx = FxAt(m_apUniqueFxArray, i);
        if ((fx->m_baFxData & 1) != 0) continue;
        if (frameClock->m_eCurrentState != 0 && fx->GetUpdateWhenPaused() == 0) continue;
        fx->Update(frameClock);
    }
}

// 0x001ab990 CKSrvFx_PostLoad (type 0 only; the base's PostLoad, 0x1a5b0, returns 1)
int32_t CKSrvFx::PostLoad(int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_ui32FxArraySize = 0;
    for (uint32_t i = 0; i < m_ui32EltNb; ++i) {
        const CMappingindex& mapping = m_apMappingIndexTable[i];
        for (uint32_t j = 0; j < mapping.m_ui32NbTypeFx; ++j) m_ui32FxArraySize += mapping.m_aUnderMapping[j].m_ui32MaxSize;
    }
    if (m_ui32FxArraySize != 0) {
        m_apFxArray = static_cast<IKSerializable**>(
            Mem_AllocAligned16(m_ui32FxArraySize * static_cast<uint32_t>(sizeof(IKSerializable*))));
        uint32_t next = 0;
        for (uint32_t i = 0; i < m_ui32EltNb; ++i) {
            const CMappingindex& mapping = m_apMappingIndexTable[i];
            for (uint32_t j = 0; j < mapping.m_ui32NbTypeFx; ++j) {
                const CUnderMappingindex& under = mapping.m_aUnderMapping[j];
                for (uint32_t k = 0; k < under.m_ui32MaxSize; ++k) m_apFxArray[next++] = under.m_apFxArrayForTypeId[k];
            }
        }
    } else {
        m_apFxArray = nullptr;
    }
    for (uint32_t i = 0; i < m_ui32FxArraySize; ++i) {
        IKFx* fx = FxAt(m_apFxArray, i);
        fx->m_baFxData = static_cast<uint8_t>((fx->m_baFxData & 0xfc) | 1);
        fx->SetOwner(nullptr);
    }
    for (uint32_t i = 0; i < m_ui32UniqueFxArraySize; ++i) {
        IKFx* fx = FxAt(m_apUniqueFxArray, i);
        fx->m_baFxData = static_cast<uint8_t>((fx->m_baFxData & 0xfc) | 1);
        fx->SetOwner(nullptr);
    }
    return 1;
}

// The FX start of the FX data MessageProcs (message 0x1b00) and of CKS08MenuPauseInfo_OnStatePhase, see the header.
IKFx* CKSrvFx::StartEffect(IKFxData* data, const IKSerializable* owner) {
    const uint32_t key = data->GetAssociatedFxClassIdentifier();  // vt+0x54
    if (data->Vf50() == 0) {
        const uint32_t type = data->GetAssociatedFxClassType();  // vt+0x58
        for (uint32_t i = 0; i < m_ui32EltNb; ++i) {
            const CMappingindex& mapping = m_apMappingIndexTable[i];
            if (mapping.m_ui32ClassId != key || mapping.m_ui32NbTypeFx == 0) continue;
            const CUnderMappingindex* under = nullptr;
            for (uint32_t j = 0; j < mapping.m_ui32NbTypeFx; ++j) {
                if (static_cast<uint32_t>(mapping.m_aUnderMapping[j].m_i32FxTypeId) == type) {
                    under = &mapping.m_aUnderMapping[j];
                    break;
                }
            }
            if (under == nullptr) continue;
            for (uint32_t k = 0; k < under->m_ui32MaxSize; ++k) {
                IKFx* fx = FxAt(under->m_apFxArrayForTypeId, k);
                if ((fx->m_baFxData & 1) == 0 || (fx->m_baFxData & 2) != 0) continue;
                fx->SetFxData(data);  // vt+0x84
                fx->SetOwner(owner);  // vt+0x88
                fx->Vf64();           // vt+0x64 Start
                return fx;
            }
            return nullptr;
        }
        return nullptr;
    }
    for (uint32_t i = 0; i < m_ui32UniqueFxArraySize; ++i) {
        IKFx* fx = FxAt(m_apUniqueFxArray, i);
        if (static_cast<uint32_t>((fx->GetClassID() << 6) + fx->GetClassType()) != key) continue;
        fx->SetDataAndOwner(data, owner);  // vt+0x8c
        if ((fx->m_baFxData & 1) != 0 && (fx->m_baFxData & 2) == 0) fx->Vf64();  // vt+0x64 Start
        return fx;
    }
    return nullptr;
}
