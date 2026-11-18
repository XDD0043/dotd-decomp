// CKWaterWaveFxData.cpp - reconstructed original translation unit 0x5710f0-0x571348 (GAME_TOC2, main_toc2), 8 functions, 8 live.
// Primary class: CKWaterWaveFxData  key 0x3b8c  category Logic  size ?  vtable 0xb2dcb0
// Other owners: CKBlurFxData (1), BlurCurve (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5710f0  CKWaterWaveFxData_GetNodeClassKey
//   [x] 0x5710f8  CKWaterWaveFxData_Destroy  (empty)
//   [x] 0x571100  CKWaterWaveFxData_EvaluateCurve_maybe
//   [ ] 0x571140  CKWaterWaveFxData_Save
//   [x] 0x571168  CKWaterWaveFxData_RecursiveRegistration  (IKFxData's, nothing)
//   [x] 0x571190  CKWaterWaveFxData_Load
//   [x] 0x5712a0  CKBlurFxData_GetNodeClassKey
//   [x] 0x5712a8  BlurCurve_EvaluateLinear_maybe
//
//   [ ] 0x9cab48  CKWaterWaveFxData_IsKindOfClass  [inline]
//   [x] 0x9cab80  CKWaterWaveFxData_GetClassType  [inline]
//   [x] 0x9cab88  CKWaterWaveFxData_GetClassID  [inline]
//   [ ] 0x9cab90  CKWaterWaveFxData_Destructor  [inline]
//   [ ] 0x9cabd0  CKWaterWaveFxData_DeletingDestructor  [inline]
#include "k2000/logic/fx/CKWaterWaveFxData.h"

#include "crt/ppc_ops.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/fx/CKBlurFxData.h"

// 0x00571190 CKWaterWaveFxData_Load
int32_t CKWaterWaveFxData::Load(IKFile* file, int32_t type) {
    IKFxData::Load(file, type);  // through TocBridge_IKFxData_Load
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_unk08);
        ReadF32LE(file, &m_unk0c);
    }
    m_unk10 = -m_unk08 / m_unk0c;  // fneg, fdivs
    return 1;
}

// 0x005712a8 BlurCurve_EvaluateLinear_maybe
// BUG(original): the test of the last key reads the key after the array (k1 = keys[n], past the operator new[] block) when
// `t` is at or after the last key's time; and without keys the answer is read before the block (keys[-1]).
float BlurCurve_EvaluateLinear(float t, const CKBlurFxData* data) {
    const uint32_t count = data->m_unk18;
    const CKBlurFxData::Key* keys = data->m_unk14;
    for (uint32_t i = 0; i < count; ++i) {
        const CKBlurFxData::Key& k0 = keys[i];
        if (!(k0.m_unk00 < t || k0.m_unk00 == t)) continue;  // cror lt|eq
        const CKBlurFxData::Key& k1 = keys[i + 1];
        if (t < k1.m_unk00) {
            const float dt = t - k0.m_unk00;
            const float span = k1.m_unk00 - k0.m_unk00;
            return k0.m_unk04 + ((k1.m_unk04 - k0.m_unk04) * dt) / span;
        }
    }
    return keys[static_cast<int32_t>(count) - 1].m_unk04;
}

// 0x00571100 CKWaterWaveFxData_EvaluateCurve_maybe
float CKWaterWaveFxData::EvaluateCurve(float speed) const {
    if (speed < 0.01f) return m_unk08;
    if (m_unk0c < speed) return 0.0f;
    return ppc::fmadds(speed, m_unk10, m_unk08);
}
