// Reconstructed original translation unit: 0x5ba9f8-0x5bb7e8 (GAME_TOC2, main_toc2), 12 functions, 11 live.
// Primary owner: CKBonusCpnt (not a registered class)
// Other owners: RegisterCKBonusCpntClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5ba9f8  CKBonusCpnt_Destroy  (the registry factory Delete: DOTD_DECLARE_FACTORIES(CKBonusCpnt), CKBonusCpnt.h)
//   [ ] 0x5baa48  CKBonusCpnt_Save
//   [ ] 0x5baa50  RegisterCKBonusCpntClass
//   [ ] 0x5baac8  _GLOBAL__I_5baac8
//   [x] 0x5baad8  CKBonusCpnt_ClearReferences  (Destroy, vt+0x10)
//   [x] 0x5bab00  CKBonusCpnt_DestroyArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x5baba0  CKBonusCpnt_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x5bac40  CKBonusCpnt_GetSplineLockProjectileType_maybe  [dead]
//   [x] 0x5bace0  CKBonusCpnt_Create  (DOTD_DECLARE_FACTORIES: the header's constructor)
//   [x] 0x5bad28  CKBonusCpnt_ComputeSpinBobMatrix_maybe  (CKBonusCpnt::ComputeSpinBobMatrix; called by CKGrpBonusPool::UpdateBonuses)
//   [x] 0x5bb108  CKBonusCpnt_LevelReset  (RecursiveRegistration, vt+0x24)
//   [x] 0x5bb1f0  CKBonusCpnt_Load
//
//   [ ] 0x9cce70  CKBonusCpnt_GetClassGroup  [inline]
//   [ ] 0x9cce78  CKBonusCpnt_GetClassId  [inline]
//   [ ] 0x9cce80  CKBonusCpnt_Destructor  [inline]
//   [ ] 0x9ccec0  CKBonusCpnt_IsKindOf  [inline]
//   [ ] 0x9ccef8  CKBonusCpnt_DeletingDestructor  [inline]
#include "k2000/ui/CKBonusCpnt.h"

#include <cstring>

#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/system/IKTime.h"

namespace {
uint32_t Bits(float x) {
    uint32_t b;
    std::memcpy(&b, &x, sizeof b);
    return b;
}
// The game's inlined floorf: the truncation (fctiwz, fcfid, frsp); kept as is when it equals x (the difference's bits
// are 0) or when x's exponent bits are above 0x4b7fffff (|x| >= 2^24, infinities, NaN); a negative x takes the
// truncation less 1 (sign of the word), a positive one the truncation.
float InlineFloorf(float x) {
    const int32_t t = ppc::fctiwz(x);
    const float truncated = ppc::frsp(static_cast<double>(t));
    if (Bits(truncated - x) == 0) return x;
    if (static_cast<int32_t>(Bits(x) & 0x7f800000u) > 0x4b7fffff) return x;
    if (static_cast<int32_t>(Bits(x)) >= 0) return truncated;
    return ppc::frsp(static_cast<double>(static_cast<int32_t>(static_cast<uint32_t>(t) - 1u)));
}
// The game's inlined sine for a clear sign bit, the library's sinf of the negation (negated) otherwise.
float GameSinf(float x) {
    return static_cast<int32_t>(Bits(x)) < 0 ? -crt::LibSinf(-x) : crt::InlineSinf(x);  // TocBridge 0x98fdd0 -> 0x9a1390
}
}  // namespace

// 0x005baad8 CKBonusCpnt_ClearReferences (vt+0x10)
void CKBonusCpnt::Destroy() {
    RwMatrixDestroy(reinterpret_cast<RwMatrix*>(m_pRotationMatrix));  // TocBridge 0x990520 -> RwMatrixDestroy_Thunk 0x23f968
}

// 0x005bb108 CKBonusCpnt_LevelReset (vt+0x24)
void CKBonusCpnt::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) {
        g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
        if (type == 0) m_pSoundDictionary->RecursiveRegistration(0);
    }
    m_pUnk48->RecursiveRegistration(type);
}

// 0x005bb1f0 CKBonusCpnt_Load. Types 4..7 (the save restores) read nothing; the sound dictionary, the matrix and +0x48
// only for type 0.
int32_t CKBonusCpnt::Load(IKFile* file, int32_t type) {
    if (static_cast<uint32_t>(type) - 4u <= 3u) return 1;
    ReadF32LE(file, &m_fSquareCatchDist);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pSoundDictionary);
    ReadF32LE(file, &m_fSpawnedLifeExpectancy);
    ReadF32LE(file, &m_fRotationSpeed);
    ReadF32LE(file, &m_fFloatingHeight);
    ReadF32LE(file, &m_fDeltaFloatHeight);
    ReadF32LE(file, &m_fVerticalFloatSpeed);
    ReadF32LE(file, &m_fVerticalBounceSpeed);
    ReadF32LE(file, &m_fPickUpAcc);
    ReadF32LE(file, &m_fAccuracy);
    ReadF32LE(file, &m_fPickUpVerticalImpulse);
    ReadF32LE(file, &m_fRotationAcc);
    ReadF32LE(file, &m_fScale);
    ReadF32LE(file, &m_fHalfHeight);
    ReadF32LE(file, &m_fMaxFlyTime);
    ReadU32LE(file, &m_baFlags);
    if (type == K_LEVEL_PLATEFORMS) {
        m_pRotationMatrix = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // TocBridge 0x990570 -> RwMatrixCreate_Thunk 0x23fa68
        IKFile_ReadRef(file, &m_pUnk48);
    }
    ReadF32LE(file, &m_unk4c);
    ReadF32LE(file, &m_unk50);
    return 1;
}

// 0x005bad28 CKBonusCpnt_ComputeSpinBobMatrix_maybe (CKGrpBonusPool_UpdateBonuses_maybe's, for a CKBonusCpnt pool)
void CKBonusCpnt::ComputeSpinBobMatrix(IKTime* clock) {
    const float time = clock->m_afCurrentTime[0];  // +0x04
    const float turns = time * m_fRotationSpeed;
    const float spin = turns - InlineFloorf(turns);
    const float cycles = time * m_fVerticalFloatSpeed;
    const float bob = cycles - InlineFloorf(cycles);
    const float kTwoPi = 6.28318548f;  // TOC2 -0x630c (0x40c90fdb)
    const float kOne = 1.0f;           // TOC2 -0x6330
    CMatrix34* m = m_pRotationMatrix;
    // RwMatrixSetIdentity inlined: flags rwMATRIXTYPEORTHONORMAL | rwMATRIXINTERNALIDENTITY (0x20003).
    m->m_ui32Flags = 0x20003u;
    m->m_pos.x = 0.0f;
    m->m_at.z = kOne;
    m->m_up.y = kOne;
    m->m_right.x = kOne;
    m->m_up.x = 0.0f;
    m->m_right.z = 0.0f;
    m->m_right.y = 0.0f;
    m->m_at.y = 0.0f;
    m->m_at.x = 0.0f;
    m->m_up.z = 0.0f;
    m->m_pos.z = 0.0f;
    m->m_pos.y = 0.0f;
    const float phase = bob * kTwoPi;
    Mat4_SetRotationAboutAxis(spin * kTwoPi, m_pRotationMatrix, 1);  // TocBridge 0x990740 -> 0x241688
    if (((m_baFlags >> 3) & 3u) == 1u) {
        CMatrix34* s = m_pRotationMatrix;
        const float scale = m_fScale;
        s->m_right.x = scale * s->m_right.x;
        s->m_right.y = scale * s->m_right.y;
        s->m_right.z = scale * s->m_right.z;
        s->m_up.x = scale * s->m_up.x;
        s->m_up.y = scale * s->m_up.y;
        s->m_up.z = scale * s->m_up.z;
        s->m_at.x = scale * s->m_at.x;
        s->m_at.z = scale * s->m_at.z;
        s->m_at.y = scale * s->m_at.y;
        s->m_ui32Flags &= 0xfffdfffeu;
    }
    const float base = m_fFloatingHeight;
    const float amplitude = m_fDeltaFloatHeight;
    const float sine = GameSinf(phase);
    CMatrix34* out = m_pRotationMatrix;
    const float zero = 0.0f;  // TOC2 -0x6308
    const float height = ppc::fmadds(sine, amplitude, base);
    out->m_pos.x = out->m_pos.x + zero;
    out->m_pos.y = height + out->m_pos.y;
    out->m_pos.z = out->m_pos.z + zero;
    out->m_ui32Flags &= ~0x20000u;  // rwMATRIXINTERNALIDENTITY
}
