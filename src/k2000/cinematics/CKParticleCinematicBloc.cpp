// CKParticleCinematicBloc.cpp - reconstructed original translation unit 0x1803c0-0x1814d0 (GAME_TOC1, main_toc1), 15 functions, 15 live.
// Primary class: CKParticleCinematicBloc  key 0x308  category CinematicNode  size 0x48  vtable 0xb1b610
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1803c0  RegisterCKParticleCinematicBlocClass
//   [ ] 0x180438  _GLOBAL__I_180438
//   [x] 0x180448  CKParticleCinematicBloc_Load
//   [ ] 0x180610  CKParticleCinematicBloc_Save
//   [x] 0x180780  CKParticleCinematicBloc_DeleteArray  (DOTD_DECLARE_FACTORIES(CKParticleCinematicBloc))
//   [x] 0x180828  CKParticleCinematicBloc_Create  (CKParticleCinematicBloc())
//   [x] 0x180880  CKParticleCinematicBloc_RecursiveRegistration
//   [x] 0x1809a0  CKParticleCinematicBloc_PostLoad
//   [x] 0x180a38  CKParticleCinematicBloc_Update
//   [x] 0x180b10  CKParticleCinematicBloc_Destroy
//   [x] 0x180b48  CKParticleCinematicBloc_CreateArray  (DOTD_DECLARE_FACTORIES(CKParticleCinematicBloc))
//   [x] 0x180c00  CKParticleCinematicBloc_Stop
//   [x] 0x180e60  CKParticleCinematicBloc_Abort
//   [x] 0x180f00  CKParticleCinematicBloc_Start
//   [x] 0x1812e0  CKParticleCinematicBloc_Complete
//
//   [ ] 0x9a9a88  CKParticleCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9ac0  CKParticleCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9ac8  CKParticleCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9ad0  CKParticleCinematicBloc_Destructor  [inline]
//   [ ] 0x9a9af0  CKParticleCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKParticleCinematicBloc.h"

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/system/IKTime.h"

namespace {
CParticlesNodeFx* NodeAt(const CKParticleCinematicBloc* bloc, uint32_t index) {
    return static_cast<CParticlesNodeFx*>(bloc->m_apParticleArray[index]);
}
}  // namespace

// 0x00180448 CKParticleCinematicBloc_Load: the element part, then (level files only) the node count, the node references
// (none: a null array) and the activation time.
int32_t CKParticleCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32ParticleNb);
    if (m_ui32ParticleNb == 0) {
        m_apParticleArray = nullptr;
    } else {
        m_apParticleArray = new IKSerializable*[m_ui32ParticleNb];  // OperatorNewArray(count * 4)
        IKFile_ReadObjectRefArray(file, m_apParticleArray, m_ui32ParticleNb);
    }
    ReadF32LE(file, &m_fTimeForActivation);
    return 1;
}

// 0x00180b10 CKParticleCinematicBloc_Destroy
void CKParticleCinematicBloc::Destroy() {
    if (m_apParticleArray != nullptr) delete[] m_apParticleArray;  // OperatorDeleteArray; the pointer is kept
}

// 0x00180880 CKParticleCinematicBloc_RecursiveRegistration
void CKParticleCinematicBloc::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
    const uint32_t count = m_ui32ParticleNb;
    if (count == 0) return;
    for (uint32_t i = 0; i != count; ++i) {
        CParticlesNodeFx* node = NodeAt(this, i);
        if (node != nullptr && node->m_pParent == nullptr) node->RecursiveRegistration(type);  // vt+0x24
    }
}

// 0x001809a0 CKParticleCinematicBloc_PostLoad
int32_t CKParticleCinematicBloc::PostLoad(int32_t type) {
    IKCinematicBloc::PostLoad(type);  // 0x0018eac0 IKCinematicBloc_PostLoad (1)
    if (type != K_LEVEL_PLATEFORMS) return 1;
    for (uint32_t i = 0; i < m_ui32ParticleNb; ++i) {
        CParticlesNodeFx* node = NodeAt(this, i);
        node->m_sgProperties = (node->m_sgProperties & 0xffffefffu) | 0x1000u;
    }
    return 1;
}

void CKParticleCinematicBloc::StopNodes() {
    if (m_apParticleArray == nullptr || (m_DataFlags & 0x200) != 0 || m_ui32ParticleNb == 0) return;
    for (uint32_t i = 0; i < m_ui32ParticleNb; ++i) {
        CParticlesNodeFx* node = NodeAt(this, i);
        node->m_sgProperties &= 0xfff7fbffu;
        node->m_pRpPrtStdEmitter->flag &= 0xfffffff7u;  // the emit flag (0x8) off
    }
}

// 0x00180f00 CKParticleCinematicBloc_Start: the blocs' common start, the start time -1 (TOC -0x2fe4), then every node
// emitting (0x1a00's code: 0x400 set, 0x80000 cleared; with flag 0x80 also shown, 0x200: 0x1a01's), its emission speed
// adjustment 0 and its emitter active and emitting (0xa). Without nodes, with flag 0x80 or with flag 0x200 the bloc is
// completed at once (vt+0x64).
void CKParticleCinematicBloc::Start() {
    StartCommon();
    m_fStartTime = -1.0f;
    const uint32_t count = m_ui32ParticleNb;
    if (m_apParticleArray == nullptr) {
        Complete();  // vt+0x64
        return;
    }
    if ((m_DataFlags & 0x80) == 0) {
        for (uint32_t i = 0; i < count; ++i) {
            CParticlesNodeFx* node = NodeAt(this, i);
            uint32_t properties = (node->m_sgProperties & 0xfffffbffu) | 0x400u;
            node->m_sgProperties = properties & 0xfff7ffffu;
            node->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
            node->m_pRpPrtStdEmitter->flag |= 0xau;
        }
        if ((m_DataFlags & 0x200) == 0) return;
    } else {
        for (uint32_t i = 0; i < count; ++i) {
            CParticlesNodeFx* node = NodeAt(this, i);
            uint32_t properties = (node->m_sgProperties & 0xfffffdffu) | 0x200u;
            properties = (properties & 0xfffffbffu) | 0x400u;
            node->m_sgProperties = properties & 0xfff7ffffu;
            node->m_fEmissionSpeedAdjustment = 0.0f;
            node->m_pRpPrtStdEmitter->flag |= 0xau;
        }
    }
    Complete();  // vt+0x64
}

// 0x00180a38 CKParticleCinematicBloc_Update: (unless its sekens stopped it) the start time taken from the scalable game
// time (+0x04) on the first update; a timed bloc (flag 0x100) is stopped (vt+0x6c) once the activation time is past
// (bge: not before start + time).
void CKParticleCinematicBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0) return;
    if (m_fStartTime == -1.0f) m_fStartTime = time->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
    if ((m_DataFlags & 0x100) == 0) return;
    if (m_fTimeForActivation + m_fStartTime >= time->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME]) return;
    Stop();  // vt+0x6c
}

// 0x00180c00 CKParticleCinematicBloc_Stop: the completion (inlined), the nodes stopped, then Complete (vt+0x64).
void CKParticleCinematicBloc::Stop() {
    CompleteBloc();
    StopNodes();
    Complete();  // vt+0x64
}

// 0x00180e60 CKParticleCinematicBloc_Abort: not running, the nodes stopped, the start time -1.
void CKParticleCinematicBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    StopNodes();
    m_fStartTime = -1.0f;
}

// 0x001812e0 CKParticleCinematicBloc_Complete: the completion, the start time -1.
void CKParticleCinematicBloc::Complete() {
    CompleteBloc();
    m_fStartTime = -1.0f;
}
