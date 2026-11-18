// CKMoveCpnt.cpp - reconstructed original translation unit 0x24c378-0x24d2a8 (GAME_TOC1, main_toc1), 20 functions, 19 live.
// Primary class: CKMoveCpnt  key 0x968c  category Logic  size 0x34  vtable 0xb20e48
// Other owners: CKMoveCpntUpdater (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x24c378  CKMoveCpnt_Delete
//   [x] 0x24c3c8  CKMoveCpnt_ResetUpdater
//   [x] 0x24c3e0  CKMoveCpnt_PauseUpdater
//   [x] 0x24c3f0  CKMoveCpnt_ResumeUpdater
//   [x] 0x24c400  CKMoveCpnt_ResetTrackTimeToStart_maybe
//   [ ] 0x24c4a0  RegisterCKMoveCpntClass
//   [ ] 0x24c518  _GLOBAL__I_24c518
//   [x] 0x24c528  CKMoveCpnt_Sample
//   [x] 0x24c988  CKMoveCpnt_Advance
//   [x] 0x24c9e8  CKMoveCpnt_DeleteArray
//   [x] 0x24ca88  CKMoveCpnt_CreateArray
//   [x] 0x24cb48  CKMoveCpnt_Create
//   [ ] 0x24cb98  CKMoveCpnt_Save
//   [x] 0x24cba0  CKMoveCpnt_RecursiveRegistration  (1: the inherited default)
//   [x] 0x24cba8  CKMoveCpnt_PostLoad  (1: the inherited default)
//   [x] 0x24cbb0  CKMoveCpnt_Destroy
//   [x] 0x24cbf8  CKMoveCpnt_StartUpdater
//   [x] 0x24ccb8  CKMoveCpnt_Load
//   [x] 0x24d250  CKMoveCpntUpdater_Delete  (the registry factory: DOTD_DECLARE_FACTORIES)
//   [ ] 0x24d2a0  KStub_Nop_24d2a0  [dead]
//
//   [ ] 0x9ba000  CKMoveCpnt_IsKindOfClass  [inline]
//   [x] 0x9ba030  CKMoveCpnt_GetClassType  [inline]
//   [x] 0x9ba038  CKMoveCpnt_GetClassID  [inline]
//   [ ] 0x9ba040  CKMoveCpnt_Destructor  [inline]
//   [ ] 0x9ba098  CKMoveCpnt_DeletingDestructor  [inline]
#include "k2000/logic/CKMoveCpnt.h"

#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/components/CKCurve2DCpnt.h"
#include "k2000/components/CKMoveCpntUpdater.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/ai/CKFlaggedPath.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/memory/Mem.h"

#include "crt/ppc_ops.h"

// 0x0024ccb8 CKMoveCpnt_Load
int32_t CKMoveCpnt::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk04);
    ReadU8(file, &m_unk08);
    ReadU8(file, &m_unk09);
    IKFile_ReadRef(file, &m_pUnk0c);
    IKFile_ReadRef(file, &m_pUnk10);
    ReadU8(file, &m_unk14);
    ReadU8(file, &m_unk15);
    ReadU8(file, &m_unk16);
    uint8_t hasMatrix = 0;
    ReadU8(file, &hasMatrix);
    if (hasMatrix == 0) {
        m_pMatrix = nullptr;
    } else {
        // RwMatrixCreate_Thunk 0x0023fa68 (an RwMatrix: the CMatrix34 layout)
        m_pMatrix = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
        CMatrix34_LoadMatrix(m_pMatrix, file);
    }
    for (float& v : m_unk1c) ReadF32LE(file, &v);  // one 0xc-byte read, then three swaps
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // The capacity is set to the count before the block is allocated (the old block is not freed); the
    // reserve that follows never grows it.
    m_vTracks.m_ui32NbElt = count;
    m_vTracks.m_pBlock = static_cast<Track*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Track))));
    if (m_vTracks.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_vTracks.m_pBlock = static_cast<Track*>(
            Mem_ReallocAligned16(m_vTracks.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Track))));
        m_vTracks.m_ui32NbElt = capacity;
    }
    m_vTracks.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) {
        Track& track = m_vTracks.m_pBlock[i];
        IKFile_ReadRef(file, &track.m_pCurve);
        ReadU32LE(file, &track.m_unk04);
        ReadF32LE(file, &track.m_unk08);
        ReadF32LE(file, &track.m_unk0c);
        ReadF32LE(file, &track.m_unk10);
        ReadF32LE(file, &track.m_unk14);
    }
    return 1;
}

void CKMoveCpnt::ResetUpdater(CKMoveCpntUpdater* updater) {
    updater->m_bPaused = 0;
    updater->m_fTime = 0.0f;
    updater->m_bRunning = 0;
}

void CKMoveCpnt::PauseUpdater(CKMoveCpntUpdater* updater) { updater->m_bPaused = 1; }

void CKMoveCpnt::ResumeUpdater(CKMoveCpntUpdater* updater) { updater->m_bPaused = 0; }

// 0x0024c400 CKMoveCpnt_ResetTrackTimeToStart_maybe: the flagged path's cursor (+0x0c) back to the start: 0, or the
// path's length when that is negative (asked again; `blt`: a NaN length gives 0).
void CKMoveCpnt::ResetTrackTime() {
    CKFlaggedPath* follower = static_cast<CKFlaggedPath*>(m_pUnk10);
    if (follower == nullptr) return;
    float distance = 0.0f;  // TOC -0x58
    if (static_cast<IKPath*>(follower->m_pPath)->GetLength() < 0.0f) {         // vt+0x5c
        distance = static_cast<IKPath*>(follower->m_pPath)->GetLength();        // vt+0x5c
    }
    follower->m_fCursorPos = distance;
}

uint8_t CKMoveCpnt::Sample(float time, float* out, CKMoveCpntUpdater* updater) const {
    for (int32_t i = 0; i < 10; ++i) out[i] = 0.0f;
    if (updater->m_bRunning == 0) return 0;
    uint8_t crossed = 0;
    bool reset = false;
    const float duration = m_unk04;
    if (duration <= time) {
        crossed = !(duration <= updater->m_fTime);
        if (m_unk08 == 0) {
            time = duration;
            reset = m_unk09 != 0;
        } else {
            do {
                time = time - duration;
            } while (duration <= time);
        }
    }
    updater->m_fTime = time;
    for (uint32_t i = 0; i < m_vTracks.m_ui32NbUsedElt; ++i) {
        const Track& track = m_vTracks.m_pBlock[i];
        if (!(track.m_unk14 <= updater->m_fTime)) continue;
        const float v = static_cast<const CKCurve2DCpnt*>(track.m_pCurve)->Evaluate(updater->m_fTime - track.m_unk14);  // 0x00249ea8
        const uint32_t mask = track.m_unk04;
        if ((mask & 1u) != 0) out[0] = ppc::fmadds(v, track.m_unk08, out[0]);
        if ((mask & 2u) != 0) out[1] = ppc::fmadds(v, track.m_unk08, out[1]);
        if ((mask & 4u) != 0) out[2] = ppc::fmadds(v, track.m_unk08, out[2]);
        if ((mask & 8u) != 0) out[3] = ppc::fmadds(v, track.m_unk0c, out[3]);
        if ((mask & 0x10u) != 0) out[4] = ppc::fmadds(v, track.m_unk0c, out[4]);
        if ((mask & 0x20u) != 0) out[5] = ppc::fmadds(v, track.m_unk0c, out[5]);
        if ((mask & 0x40u) != 0) {
            // The path channel: the curve times the path's length (+0x0c, else the flagged path's path).
            IKSerializable* path = m_pUnk0c;
            if (path == nullptr && m_pUnk10 != nullptr) path = static_cast<CKFlaggedPath*>(m_pUnk10)->m_pPath;
            if (path != nullptr) {
                const float before = out[6];
                out[6] = ppc::fmadds(v, static_cast<IKPath*>(path)->GetLength(), before);  // vt+0x5c
            }
        }
        if ((mask & 0x80u) != 0) out[7] = ppc::fmadds(v, track.m_unk10, out[7]);
        if ((mask & 0x100u) != 0) out[8] = ppc::fmadds(v, track.m_unk10, out[8]);
        if ((mask & 0x200u) != 0) out[9] = ppc::fmadds(v, track.m_unk10, out[9]);
    }
    if (reset) {
        updater->m_bPaused = 0;
        updater->m_fTime = 0.0f;
        updater->m_bRunning = 0;
    }
    return crossed;
}

uint8_t CKMoveCpnt::Advance(float dt, float* out, CKMoveCpntUpdater* updater) const {
    if (updater->m_bRunning == 0) return 0;
    float time = updater->m_fTime;
    if (updater->m_bPaused == 0) time = time + dt;
    return Sample(time, out, updater);
}

void CKMoveCpnt::StartUpdater(CKMoveCpntUpdater* updater) {
    updater->m_bRunning = 1;
    updater->m_bPaused = 0;
    updater->m_fTime = 0.0f;
    ResetTrackTime();
}

// 0x0024cbb0 CKMoveCpnt_Destroy (RwMatrixDestroy_Thunk)
void CKMoveCpnt::Destroy() {
    if (m_pMatrix != nullptr) {
        RwMatrixDestroy(reinterpret_cast<RwMatrix*>(m_pMatrix));
        m_pMatrix = nullptr;
    }
}
