// Reconstructed original translation unit: 0x2472f0-0x247548 (GAME_TOC1, main_toc1), 4 functions, 3 live.
// Primary owner: ConvertRwMatrixToHomogeneous4x4 (not a registered class)
// Other owners: CopyMatrix4x4 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2472f0  ConvertRwMatrixToHomogeneous4x4
//   [x] 0x2473e0  KStub_Nop_2473e0
//   [ ] 0x2473e8  ConvertRwMatrixToHomogeneous4x4_Transposed_maybe  [dead]
//   [x] 0x2474b8  CopyMatrix4x4
#include "k2000/math/ConvertRwMatrixToHomogeneous4x4.h"

#include <cstring>

#include "Renderware/rwcore/RwTypes.h"

// 0x002472f0 ConvertRwMatrixToHomogeneous4x4: the rows right, up, at, pos with the fourth word 0, 0, 0, 1.0f (the
// matrix's flags word and pads replaced); nothing for a null matrix.
void ConvertRwMatrixToHomogeneous4x4(Homogeneous4x4* out, const RwMatrix* matrix) {
    if (matrix == nullptr) return;
    const RwV3d* rows[4] = {&matrix->right, &matrix->up, &matrix->at, &matrix->pos};
    for (int r = 0; r < 4; ++r) {
        out->m[r][0] = rows[r]->x;
        out->m[r][1] = rows[r]->y;
        out->m[r][2] = rows[r]->z;
        out->m[r][3] = r == 3 ? 1.0f : 0.0f;  // stw 0 / 0x3f800000
    }
}

// 0x002473e0 KStub_Nop_2473e0: the 4x4's constructor (nothing; its destructor 0x2471d0 neither).
void Homogeneous4x4_Construct(Homogeneous4x4*) {}

// 0x002474b8 CopyMatrix4x4
void CopyMatrix4x4(float* out, const float* in) {
    if (in == nullptr) return;
    for (int column = 0; column < 4; ++column) {
        for (int row = 0; row < 4; ++row) out[column + 4 * row] = in[column + 4 * row];  // lfs / stfs
    }
}
