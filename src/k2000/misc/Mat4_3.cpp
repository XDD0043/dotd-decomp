// Reconstructed original translation unit: 0x247548-0x247988 (GAME_TOC1, main_toc1), 4 functions, 2 live.
// Primary owner: Mat4 (not a registered class)
// Other owners: MultiplyMatrix4x4 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x247548  Mat4_InvertGeneral  [platform]  (the VMX 4x4 inverse with the vrefp reciprocal estimate (PS3 hardware estimate + one Newton step): its callers (ShaderMatrixCache.cpp) invert natively in double precision by design)
//   [ ] 0x2476e8  Mat4_PreMultiplyInPlace_maybe  [dead]
//   [x] 0x2477c8  MultiplyMatrix4x4  (its callers (ShaderMatrixCache.cpp) multiply natively in double precision by design)
//   [ ] 0x2478a8  Mat4_MultiplyInPlace_maybe  [dead]
#include "k2000/misc/Mat4.h"

#include "crt/ppc_ops.h"

// 0x002477c8 MultiplyMatrix4x4 (VMX: vspltw / vmaddfp / vaddfp). Its callers (GetShaderViewProjectionMatrix and the
// transposed world-view(-projection) getters, ShaderMatrixCache.cpp) compute natively in double precision by design.
void MultiplyMatrix4x4(float* out, const float* left, const float* right) {
    float result[16];
    for (int row = 0; row < 4; ++row) {
        const float* l = left + 4 * row;
        for (int c = 0; c < 4; ++c) {
            const float even = ppc::fmadds(right[8 + c], l[2], right[0 + c] * l[0]);
            const float odd = ppc::fmadds(right[12 + c], l[3], right[4 + c] * l[1]);
            result[4 * row + c] = even + odd;
        }
    }
    for (int i = 0; i < 16; ++i) out[i] = result[i];
}
