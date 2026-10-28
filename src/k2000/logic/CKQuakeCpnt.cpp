// CKQuakeCpnt.cpp - reconstructed original translation unit 0x24df08-0x24ebb8 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKQuakeCpnt  key 0x364c  category Logic  size 0x14  vtable 0xb20ef8
// Other owners: ShakeEffectDef (2), ShakeEffect (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x24df08  CKQuakeCpnt_Delete
//   [ ] 0x24df58  RegisterCKQuakeCpntClass
//   [ ] 0x24dfd0  _GLOBAL__I_24dfd0
//   [x] 0x24dfe0  CKQuakeCpnt_StopUpdater_maybe
//   [x] 0x24e088  CKQuakeCpnt_DeleteArray
//   [x] 0x24e130  CKQuakeCpnt_Create
//   [x] 0x24e180  CKQuakeCpnt_StartUpdater_maybe
//   [x] 0x24e228  CKQuakeCpnt_CreateArray
//   [ ] 0x24e2f0  CKQuakeCpnt_Save
//   [ ] 0x24e2f8  CKQuakeCpnt_PostLoad
//   [ ] 0x24e300  CKQuakeCpnt_RecursiveRegistration
//   [ ] 0x24e308  CKQuakeCpnt_Destroy
//   [x] 0x24e310  CKQuakeCpnt_Evaluate_maybe
//   [x] 0x24e840  CKQuakeCpnt_Load
//
//   [ ] 0x9ba1a8  CKQuakeCpnt_IsKindOfClass  [inline]
//   [x] 0x9ba1d0  CKQuakeCpnt_GetClassType  [inline]
//   [x] 0x9ba1d8  CKQuakeCpnt_GetClassID  [inline]
//   [ ] 0x9ba1e0  CKQuakeCpnt_Destructor  [inline]
//   [ ] 0x9ba238  CKQuakeCpnt_DeletingDestructor  [inline]
#include "k2000/logic/CKQuakeCpnt.h"

#include "crt/ppc_ops.h"
#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/components/CKSinCurve2DCpnt.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// 0x0024e130 CKQuakeCpnt_Create, the inlined constructor: the entry list only.
CKQuakeCpnt::CKQuakeCpnt() {
    m_entries.m_pBlock = nullptr;
    m_entries.m_ui32NbElt = 1;
    m_entries.m_ui32NbUsedElt = 0;
}

// 0x0024e840 CKQuakeCpnt_Load
int32_t CKQuakeCpnt::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_fDuration);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    // The capacity is set to count before the block is allocated (the old block, if any, is not freed).
    m_entries.m_ui32NbElt = count;
    m_entries.m_pBlock = static_cast<Entry*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Entry))));
    if (m_entries.m_ui32NbElt < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = count + 1;
        uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(Entry));
        if (capacity == 0) {
            capacity = 1;
            bytes = static_cast<uint32_t>(sizeof(Entry));
        }
        m_entries.m_pBlock = static_cast<Entry*>(Mem_ReallocAligned16(m_entries.m_pBlock, bytes));
        m_entries.m_ui32NbElt = capacity;
    }
    m_entries.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) {
        Entry& entry = m_entries.m_pBlock[i];
        IKFile_ReadRef(file, &entry.m_pCurve);
        ReadU32LE(file, &entry.m_ui32Channels);
        ReadF32LE(file, &entry.m_fAmplitude0);
        ReadF32LE(file, &entry.m_fAmplitude3);
        ReadF32LE(file, &entry.m_fAmplitude6);
        ReadF32LE(file, &entry.m_fAmplitude9);
        ReadF32LE(file, &entry.m_fStartTime);
    }
    return 1;
}

namespace {
CKSinCurve2DCpnt* Curve(const CKQuakeCpnt::Entry& entry) { return static_cast<CKSinCurve2DCpnt*>(entry.m_pCurve); }
}  // namespace

// 0x0024e180 CKQuakeCpnt_StartUpdater_maybe
void CKQuakeCpnt::StartEffect(CKQuakeCpntUpdater* effect) const {
    effect->m_bRunning = 1;
    effect->m_fElapsed = 0.0f;
    for (uint32_t i = 0; i < m_entries.m_ui32NbUsedElt; ++i) {
        Curve(m_entries.m_pBlock[i])->StartState(&effect->m_curveStates.m_pBlock[i]);
    }
}

// 0x0024dfe0 CKQuakeCpnt_StopUpdater_maybe
void CKQuakeCpnt::StopEffect(CKQuakeCpntUpdater* effect) const {
    effect->m_bRunning = 0;
    effect->m_fElapsed = 0.0f;
    for (uint32_t i = 0; i < m_entries.m_ui32NbUsedElt; ++i) {
        Curve(m_entries.m_pBlock[i])->ResetState(&effect->m_curveStates.m_pBlock[i]);
    }
}

// 0x0024e310 CKQuakeCpnt_Evaluate_maybe. An entry oscillates once the effect's time reached its start time (not before,
// nor with a NaN time); its value v adds v * amplitude (fmadds) to each output its
// channel bits name, in output order. The entry count is read again after every entry.
void CKQuakeCpnt::Evaluate(float dt, float out[15], CKQuakeCpntUpdater* effect) const {
    for (int32_t i = 0; i < 15; ++i) out[i] = 0.0f;
    if (effect->m_bRunning == 0) return;
    const float elapsed = dt + effect->m_fElapsed;
    effect->m_fElapsed = elapsed;
    if (m_fDuration <= elapsed) {
        effect->m_fElapsed = 0.0f;
        effect->m_bRunning = 0;
        for (uint32_t i = 0; i < m_entries.m_ui32NbUsedElt; ++i) {
            Curve(m_entries.m_pBlock[i])->ResetState(&effect->m_curveStates.m_pBlock[i]);
        }
        return;
    }
    for (uint32_t i = 0; i < m_entries.m_ui32NbUsedElt; ++i) {
        const Entry& entry = m_entries.m_pBlock[i];
        if (!(effect->m_fElapsed >= entry.m_fStartTime)) continue;  // fcmpu + cror gt|eq: NaN is not reached
        const float value = ShakeOscillator_Update(dt, Curve(entry), &effect->m_curveStates.m_pBlock[i]);
        const uint32_t channels = m_entries.m_pBlock[i].m_ui32Channels;
        for (int32_t c = 0; c < 15; ++c) {
            if ((channels & (1u << c)) == 0) continue;
            const float amplitude = c < 3 ? entry.m_fAmplitude0
                                  : c < 6 ? entry.m_fAmplitude3
                                  : c < 9 ? entry.m_fAmplitude6
                                          : entry.m_fAmplitude9;
            out[c] = ppc::fmadds(value, amplitude, out[c]);
        }
    }
}
