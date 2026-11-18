// CKParticlesSequencerCpnt.cpp - reconstructed original translation unit 0x1dab88-0x1dcb28 (GAME_TOC1, main_toc1), 32 functions, 24 live.
// Primary class: CKParticlesSequencerCpnt  key 0xc86  category Component  size 0x28  vtable 0xb1df58
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1dab88  CKParticlesSequencerCpnt_Delete
//   [ ] 0x1dabd8  CKParticlesSequencerCpnt_Construct  [dead]
//   [ ] 0x1dabe8  CKParticlesSequencerCpnt_Construct_2  [dead]
//   [x] 0x1dabf8  CKParticlesSequencerCpnt_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x1dac00  CKParticlesSequencerCpnt_PostLoad  (returns 1: the default)
//   [ ] 0x1dac08  FUN_001dac08  [dead]
//   [x] 0x1dac20  CKParticlesSequencerCpnt_vf50  (Vf50, the header)
//   [ ] 0x1dac28  FUN_001dac28  [dead]
//   [ ] 0x1dac40  KStub_Return1_1dac40  [dead]
//   [ ] 0x1dac48  FUN_001dac48  [dead]
//   [ ] 0x1dad18  RegisterCKParticlesSequencerCpntClass
//   [ ] 0x1dad90  _GLOBAL__I_1dad90
//   [ ] 0x1dada0  FUN_001dada0  [dead]
//   [x] 0x1dae70  CKParticlesSequencerCpnt_DeleteArray
//   [x] 0x1daf18  CKParticlesSequencerCpnt_BaseDestructor  (the component base's destructor: the C++ chain)
//   [x] 0x1daf48  CKParticlesSequencerCpnt_DeletingDestructor  (the component base's destructor + delete)
//   [x] 0x1daf90  CKParticlesSequencerCpnt_Destructor  (the component base's destructor: the C++ chain)
//   [x] 0x1dafc0  CKParticlesSequencerCpnt_AttachSequenceFxTo_maybe  (AttachSequenceFxTo)
//   [x] 0x1db130  CKParticlesSequencerCpnt_CreateArray
//   [x] 0x1db1c8  CKParticlesSequencerCpnt_Create
//   [ ] 0x1db200  CKParticlesSequencerCpnt_Save
//   [x] 0x1db208  CKParticlesSequencerCpnt_Destroy
//   [ ] 0x1db390  FUN_001db390  [dead]
//   [x] 0x1db508  CKParticlesSequencerCpnt_LoadSequence_maybe
//   [x] 0x1db948  CKParticlesSequencerCpnt_Load
//   [x] 0x1dbb90  CKParticlesSequencerCpnt_ReleaseSequenceFx_maybe  (ReleaseSequenceFx)
//   [x] 0x1dbd60  CKParticlesSequencerCpnt_StartSequence_maybe  (StartSequence)
//   [x] 0x1dbf50  CKParticlesSequencerCpnt_StopAll_maybe  (StopAll)
//   [x] 0x1dc0d8  CKParticlesSequencerCpnt_StopSequence_maybe  (StopSequence)
//   [x] 0x1dc338  CKParticlesSequencerCpnt_vf54  (Vf54)
//   [x] 0x1dc4c0  CKParticlesSequencerCpnt_PlaySequence_maybe  (PlaySequence)
//   [x] 0x1dc7d0  CKParticlesSequencerCpnt_Update  (Update)
//
//   [x] 0x9adb68  CKParticlesSequencerCpnt_IsKindOfClass  [inline]
//   [x] 0x9adb90  CKParticlesSequencerCpnt_GetClassType  [inline]
//   [x] 0x9adb98  CKParticlesSequencerCpnt_GetClassID  [inline]
#include "k2000/components/CKParticlesSequencerCpnt.h"

#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/io/IKFile.h"

// 0x001db508 CKParticlesSequencerCpnt_LoadSequence_maybe
int32_t CKParticlesSequencerCpnt::CSequence::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU8(file, &m_bLoop);
    ReadF32LE(file, &m_fSeqDuration);
    ReadU16LE(file, &m_ui16KeyTimeNb);
    ReadU16LE(file, &m_ui16PartStateNb);
    m_afKeyTime = new float[m_ui16KeyTimeNb];  // OperatorNewArray(n * 4)
    m_aUnk0c = new float[m_ui16KeyTimeNb];
    m_aUnk10 = new float[m_ui16KeyTimeNb];
    m_aParticleState = new CParticleState[m_ui16PartStateNb];  // OperatorNewArray(n * 0xc)
    for (uint32_t i = 0; i < m_ui16KeyTimeNb; ++i) {
        ReadF32LE(file, &m_afKeyTime[i]);
        ReadF32LE(file, &m_aUnk0c[i]);
        ReadF32LE(file, &m_aUnk10[i]);
    }
    for (uint32_t i = 0; i < m_ui16PartStateNb; ++i) {
        CParticleState& state = m_aParticleState[i];
        IKFile_ReadRef(file, &state.m_pParticle);
        state.m_aePartState = new uint32_t[m_ui16KeyTimeNb];
        for (uint32_t k = 0; k < m_ui16KeyTimeNb; ++k) ReadU32LE(file, &state.m_aePartState[k]);
        state.m_pMatrixPart = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // RwMatrixCreate_Thunk
        CMatrix34_LoadMatrix(state.m_pMatrixPart, file);
    }
    m_pCentralMatrix = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
    CMatrix34_LoadMatrix(m_pCentralMatrix, file);
    return 1;
}

// 0x001db948 CKParticlesSequencerCpnt_Load
int32_t CKParticlesSequencerCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadU16LE(file, &m_ui16PartNb);
        ReadU16LE(file, &m_ui16SeqNb);
        m_apSequencerParticles = new IKSerializable*[m_ui16PartNb];  // OperatorNewArray(n * 4)
        m_aSequences = new CSequence[m_ui16SeqNb];                   // OperatorNewArray(n * 0x20)
        for (uint32_t i = 0; i < m_ui16PartNb; ++i) IKFile_ReadRef(file, &m_apSequencerParticles[i]);
        for (uint32_t i = 0; i < m_ui16SeqNb; ++i) m_aSequences[i].Load(file, K_LEVEL_PLATEFORMS);
    }
    m_baInfos = 0;
    m_i32CurSeq = -1;
    return 1;
}

// C2.8 port-all P11.

// 0x001db208 CKParticlesSequencerCpnt_Destroy (the counts read again each time)
void CKParticlesSequencerCpnt::Destroy() {
    for (uint32_t s = 0; s < m_ui16SeqNb; ++s) {
        CSequence& seq = m_aSequences[s];
        for (uint32_t i = 0; i < seq.m_ui16PartStateNb; ++i) {
            RwMatrixDestroy(reinterpret_cast<RwMatrix*>(seq.m_aParticleState[i].m_pMatrixPart));  // RwMatrixDestroy_Thunk
            delete[] seq.m_aParticleState[i].m_aePartState;
        }
        delete[] seq.m_aParticleState;
        delete[] seq.m_afKeyTime;
        delete[] seq.m_aUnk0c;
        delete[] seq.m_aUnk10;
        RwMatrixDestroy(reinterpret_cast<RwMatrix*>(seq.m_pCentralMatrix));
    }
    delete[] m_apSequencerParticles;
    delete[] m_aSequences;
}

// C2.8 port-rest R02: the sequence runtime. Nothing replays it (CKHkParticlesSequencer is in LVL060 / LVL080 only).

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "crt/ppc_ops.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/system/IKTime.h"

namespace {
CParticlesNodeFx* AsParticles(IKSerializable* object) { return static_cast<CParticlesNodeFx*>(object); }

// The mask the stops and key state 2 apply to a particle node's properties: 0x400 (emitting) and 0x80000 cleared.
constexpr uint32_t kNotEmitting = 0xfff7fbffu;

// (draw & 0xffff) x -2^-15 (1 + 2^-16) + 1 (TOC1 -0x17a4 0xb8000080, -0x17a0 1.0), fused.
float RandDelayFactor() {
    const float u = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));
    return ppc::fmadds(u, -0x1.0001p-15f, 1.0f);
}

// Every key's delay redrawn (PlaySequence / the loop of Update): one Rand_Int per key, in key order.
void RedrawKeyDelays(CKParticlesSequencerCpnt::CSequence* seq) {
    for (uint32_t i = 0; i < seq->m_ui16KeyTimeNb; i = static_cast<uint16_t>(i + 1)) {
        const float factor = RandDelayFactor();
        seq->m_aUnk0c[i] = factor * seq->m_aUnk10[i];
    }
}

// A particle state's node placed at its matrix times `place` (the matrix copied first; RwMatrixTransform post-concat).
void PlaceAt(CParticlesNodeFx* node, const CMatrix34* stateMatrix, const CMatrix34* place) {
    CMatrix34 matrix = *stateMatrix;
    Mat4_TransformPostConcat(&matrix, place);  // 0x0023f760
    node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
}

// StopAll / StopSequence(1)'s cut: the node stops emitting (0x000e6938), 0x4 set and 0x400 | 0x80000 cleared, the
// emitter's emit flag off, the point list's last point 0.
void CutParticles(CParticlesNodeFx* node) {
    node->StopEmitting();
    node->m_sgProperties = ((node->m_sgProperties & ~0x4u) | 0x4u) & kNotEmitting;
    node->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
    if (node->m_pAdvEmtPointList != nullptr) node->m_pAdvEmtPointList->lastPoint = 0;
}
}  // namespace

// 0x001dc338 CKParticlesSequencerCpnt_vf54
void CKParticlesSequencerCpnt::Vf54(int32_t sector) {
    if ((m_baInfos & 0x2u) == 0) return;
    const uint32_t count = m_aSequences[m_i32CurSeq].m_ui16PartStateNb;
    for (uint32_t i = 0; i < count; ++i) {
        CSGLeaf* node = static_cast<CSGLeaf*>(m_aSequences[m_i32CurSeq].m_aParticleState[i].m_pParticle);
        if (node == nullptr || node->m_pParent == nullptr) continue;
        if (node->m_pParent->GetSectorIndex() == 0) continue;  // vt+0x6c
        if (static_cast<int32_t>(static_cast<CSGLeaf*>(m_aSequences[m_i32CurSeq].m_aParticleState[i].m_pParticle)
                                     ->m_pParent->GetSectorIndex()) != sector)
            continue;
        StopSequence(1);
        return;
    }
}

// 0x001dafc0 CKParticlesSequencerCpnt_AttachSequenceFxTo_maybe
void CKParticlesSequencerCpnt::AttachSequenceFxTo(IKSerializable* node) {
    if (m_i32CurSeq < 0 || node == nullptr) return;
    const uint32_t count = m_aSequences[m_i32CurSeq].m_ui16PartStateNb;
    for (uint32_t i = 0; i < count; ++i) {
        CParticleState* state = &m_aSequences[m_i32CurSeq].m_aParticleState[i];
        CSGLeaf* particle = static_cast<CSGLeaf*>(state->m_pParticle);
        if (particle == nullptr) continue;
        if (particle->m_pParent != nullptr) particle->m_pParent->RemoveChild(particle);  // vt+0x78
        static_cast<CSGBranch*>(node)->AddChild(static_cast<CSGLeaf*>(state->m_pParticle));  // vt+0x70
        AsParticles(state->m_pParticle)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(state->m_pMatrixPart));
    }
    m_baInfos = static_cast<uint8_t>(((m_baInfos & ~0x2u) | 0x2u) & ~0x4u);
}

// 0x001dbb90 CKParticlesSequencerCpnt_ReleaseSequenceFx_maybe
void CKParticlesSequencerCpnt::ReleaseSequenceFx() {
    if (m_i32CurSeq < 0) return;
    const uint32_t count = m_aSequences[m_i32CurSeq].m_ui16PartStateNb;
    for (uint32_t i = 0; i < count; ++i) {
        CParticleState* state = &m_aSequences[m_i32CurSeq].m_aParticleState[i];
        CSGLeaf* particle = static_cast<CSGLeaf*>(state->m_pParticle);
        if (particle == nullptr) continue;
        if (particle->m_pParent != nullptr) particle->m_pParent->RemoveChild(particle);  // vt+0x78
        CSGBranch* root;
        IKHook* owner = static_cast<IKHook*>(m_unk24);
        if (owner != nullptr && static_cast<uint8_t>(owner->IsKindOfClass(2)) != 0 && owner->m_iSectorIndex != 0) {
            CKSector* sector = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[owner->m_iSectorIndex]);
            root = sector->m_pSectorRoot;
        } else {
            root = static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot);  // engine +0x14
        }
        root->AddChild(static_cast<CSGLeaf*>(state->m_pParticle));  // vt+0x70
    }
    m_baInfos = static_cast<uint8_t>(m_baInfos & ~0x2u);
}

// 0x001dbd60 CKParticlesSequencerCpnt_StartSequence_maybe
void CKParticlesSequencerCpnt::StartSequence(const CMatrix34* place) {
    if (m_i32CurSeq < 0) return;
    if ((m_baInfos & 0x2u) != 0) ReleaseSequenceFx();
    m_baInfos = static_cast<uint8_t>((m_baInfos & ~0x4u) | 0x4u);
    const uint32_t count = m_aSequences[m_i32CurSeq].m_ui16PartStateNb;
    for (uint32_t i = 0; i < count; ++i) {
        CParticleState* state = &m_aSequences[m_i32CurSeq].m_aParticleState[i];
        if (state->m_pParticle == nullptr) continue;
        PlaceAt(AsParticles(state->m_pParticle), state->m_pMatrixPart, place);
    }
}

// 0x001dbf50 CKParticlesSequencerCpnt_StopAll_maybe
void CKParticlesSequencerCpnt::StopAll() {
    if ((m_baInfos & 0x2u) != 0) {
        ReleaseSequenceFx();
    } else if ((m_baInfos & 0x4u) != 0) {
        m_baInfos = static_cast<uint8_t>(m_baInfos & ~0x4u);
    }
    for (uint32_t i = 0; i < m_ui16PartNb; ++i) {
        if (m_apSequencerParticles[i] == nullptr) continue;
        CutParticles(AsParticles(m_apSequencerParticles[i]));
    }
    m_i32CurSeq = -1;
    m_fCurSeqTime = 0.0f;  // stw 0
    m_i32CurKeyTime = -1;
    m_i32LastSeq = -1;
    m_baInfos = static_cast<uint8_t>(m_baInfos & ~0x4u);
}

// 0x001dc0d8 CKParticlesSequencerCpnt_StopSequence_maybe. BUG(original): the state count is read from the current
// sequence before any test, so without one (m_i32CurSeq -1) it reads the entry before the array; every caller has one.
void CKParticlesSequencerCpnt::StopSequence(int32_t now) {
    const uint32_t count = m_aSequences[m_i32CurSeq].m_ui16PartStateNb;
    if ((m_baInfos & 0x2u) != 0) {
        ReleaseSequenceFx();
    } else if ((m_baInfos & 0x4u) != 0) {
        m_baInfos = static_cast<uint8_t>(m_baInfos & ~0x4u);
    }
    for (uint32_t i = 0; i < count; ++i) {
        CParticlesNodeFx* node = AsParticles(m_aSequences[m_i32CurSeq].m_aParticleState[i].m_pParticle);
        if (node == nullptr) continue;
        if (now != 0) {
            CutParticles(node);
        } else {
            node->m_sgProperties &= kNotEmitting;
            node->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
            if (node->m_pAdvEmtPointList != nullptr) node->m_pAdvEmtPointList->lastPoint = 0;
        }
    }
    m_i32LastSeq = m_i32CurSeq;
    m_i32CurSeq = -1;
    m_i32CurKeyTime = -1;
    m_baInfos = static_cast<uint8_t>((m_baInfos & ~0x1u) | 0x1u);
}

// 0x001dc4c0 CKParticlesSequencerCpnt_PlaySequence_maybe
void CKParticlesSequencerCpnt::PlaySequence(uint32_t index) {
    if (m_ui16SeqNb <= index) return;
    if (m_i32CurSeq > -1 && (m_baInfos & 0x1u) == 0) StopSequence(0);
    m_i32CurSeq = static_cast<int32_t>(index);
    const uint32_t count = m_aSequences[index].m_ui16PartStateNb;
    const CMatrix34* central = m_aSequences[index].m_pCentralMatrix;
    for (uint32_t i = 0; i < count; ++i) {
        CParticleState* state = &m_aSequences[m_i32CurSeq].m_aParticleState[i];
        CParticlesNodeFx* node = AsParticles(state->m_pParticle);
        if (node == nullptr) continue;
        node->m_sgProperties &= 0xfff7fbfbu;  // 0x80000 | 0x400 | 0x4 cleared
        node->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
        PlaceAt(node, m_aSequences[m_i32CurSeq].m_aParticleState[i].m_pMatrixPart, central);
    }
    m_i32CurKeyTime = -1;
    m_fCurSeqTime = 0.0f;  // stw 0
    m_baInfos = static_cast<uint8_t>(m_baInfos & ~0x1u);
    RedrawKeyDelays(&m_aSequences[m_i32CurSeq]);
}

// 0x001dc7d0 CKParticlesSequencerCpnt_Update. The key loop stops at the first state without a particle node.
void CKParticlesSequencerCpnt::Update(IKTime* clock) {
    if ((m_baInfos & 0x1u) != 0 || m_i32CurSeq < 0) return;
    CSequence* seq = &m_aSequences[m_i32CurSeq];
    float time = m_fCurSeqTime;
    if (seq->m_bLoop == 0 && time > seq->m_fSeqDuration) {  // fcmpu, ble: NaN goes on
        StopSequence(1);
        return;
    }
    uint32_t key = static_cast<uint32_t>(m_i32CurKeyTime + 1);
    while (key < seq->m_ui16KeyTimeNb) {
        // fcmpu + cror gt|eq: the key fires when the time is not below its time plus delay (NaN does not fire).
        if (!(time >= seq->m_afKeyTime[key] + seq->m_aUnk0c[key])) break;
        for (uint32_t i = 0; i < seq->m_ui16PartStateNb; ++i) {
            CParticlesNodeFx* node = AsParticles(seq->m_aParticleState[i].m_pParticle);
            if (node == nullptr) break;
            const uint32_t state = seq->m_aParticleState[i].m_aePartState[key];
            if (state == 2) {
                node->m_sgProperties &= kNotEmitting;
                node->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
            } else if (state == 3) {
                uint32_t properties = (node->m_sgProperties & ~0x200u) | 0x200u;
                properties = (properties & ~0x400u) | 0x400u;
                node->m_sgProperties = properties & ~0x80000u;
                node->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
                node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
            } else if (state == 1) {
                const uint32_t properties = (node->m_sgProperties & ~0x400u) | 0x400u;
                node->m_sgProperties = properties & ~0x80000u;
                node->m_fEmissionSpeedAdjustment = 0.0f;  // stw 0
                node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
            }
        }
        m_i32CurKeyTime = static_cast<int32_t>(key);
        ++key;
        if (key != seq->m_ui16KeyTimeNb || seq->m_bLoop == 0) continue;
        // The last key of a looping sequence: the time wraps, the keys start over with new delays.
        time = time - seq->m_fSeqDuration;
        m_i32CurKeyTime = -1;
        m_fCurSeqTime = time;
        RedrawKeyDelays(seq);
        time = m_fCurSeqTime;
        key = 0;
    }
    m_fCurSeqTime = clock->m_afDeltaTime[0] + time;  // clock +0x1c
}
