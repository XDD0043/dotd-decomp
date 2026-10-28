// CKHkS08FogHorn.cpp - reconstructed original translation unit 0x49b440-0x49f968 (GAME_TOC1, main_toc1), 49 functions, 39 live.
// Primary class: CKHkS08FogHorn  key 0x2f02  category Hook  size 0x16c  vtable 0xb283d8
// Other owners: ChargeGauge (5)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x49b440  ChargeGauge_Construct_maybe  [dead]
//   [ ] 0x49b460  ChargeGauge_Construct_2_maybe  [dead]
//   [ ] 0x49b480  ChargeGauge_Update_maybe
//   [ ] 0x49b528  ChargeGauge_GetRatio_maybe
//   [ ] 0x49b550  ChargeGauge_Reset_maybe
//   [ ] 0x49b568  KStub_Nop_49b568  [dead]
//   [ ] 0x49b570  CKHkS08FogHorn_IsBlown_maybe
//   [ ] 0x49b578  CKHkS08FogHorn_SetNodeAlphaByRatio_maybe
//   [ ] 0x49b708  CKHkS08FogHorn_IsNode90Hidden_maybe  [dead]
//   [ ] 0x49b730  RegisterCKHkS08FogHornClass
//   [ ] 0x49b7a8  _GLOBAL__I_49b7a8
//   [ ] 0x49b7b8  CKHkS08FogHorn_InitCollisionVolume_maybe  [dead]
//   [ ] 0x49b888  CKHkS08FogHorn_UpdateFxParamByRatio_maybe  [dead]
//   [ ] 0x49b978  CKHkS08FogHorn_UpdateSoundVolume_maybe
//   [ ] 0x49ba48  CKHkS08FogHorn_GetInfo
//   [ ] 0x49bb28  CKHkS08FogHorn_MessageProc
//   [ ] 0x49bc58  CKHkS08FogHorn_StartShakeEffect_maybe  [dead]
//   [ ] 0x49bc80  CKHkS08FogHorn_UpdateBlowAnimation_maybe
//   [ ] 0x49be20  CKHkS08FogHorn_StopShakeEffect_maybe  [dead]
//   [x] 0x49be48  CKHkS08FogHorn_SetDefaultState
//   [ ] 0x49be80  CKHkS08FogHorn_Resume
//   [ ] 0x49bea8  CKHkS08FogHorn_Pause
//   [ ] 0x49bed0  CKHkS08FogHorn_Stop
//   [x] 0x49bef8  CKHkS08FogHorn_Start
//   [ ] 0x49bf58  CKHkS08FogHorn_Save
//   [ ] 0x49bf80  CKHkS08FogHorn_RecursiveRegistration
//   [x] 0x49bfa8  CKHkS08FogHorn_Construct
//   [x] 0x49c020  CKHkS08FogHorn_DeleteArray
//   [ ] 0x49c0c0  CKHkS08FogHorn_DestructBody
//   [ ] 0x49c138  CKHkS08FogHorn_DeletingDestructor
//   [ ] 0x49c1c0  CKHkS08FogHorn_Destructor
//   [ ] 0x49c238  CKHkS08FogHorn_Destroy
//   [ ] 0x49c278  CKHkS08FogHorn_GetChargeRatio
//   [ ] 0x49c2b8  CKHkS08FogHorn_Construct_2
//   [ ] 0x49c330  CKHkS08FogHorn_OnActivate
//   [x] 0x49c548  CKHkS08FogHorn_ResetEffects_maybe
//   [ ] 0x49c758  CKHkS08FogHorn_OnDeactivate
//   [ ] 0x49c858  CKHkS08FogHorn_SetEnabled
//   [x] 0x49c880  CKHkS08FogHorn_Restart
//   [ ] 0x49c958  CKHkS08FogHorn_ScaleEmitterAByCharge_maybe
//   [ ] 0x49cd10  CKHkS08FogHorn_ScaleEmitterBByCharge_maybe
//   [x] 0x49d0c8  CKHkS08FogHorn_CreateArray
//   [x] 0x49d1d8  CKHkS08FogHorn_Create
//   [ ] 0x49d268  CKHkS08FogHorn_SetNodeVisibleWithAlpha_maybe
//   [x] 0x49d430  CKHkS08FogHorn_PostLoad
//   [ ] 0x49d518  CKHkS08FogHorn_IsTargetInRangeAndFacing_maybe  [dead]
//   [ ] 0x49d8d8  CKHkS08FogHorn_Update
//   [ ] 0x49e748  FUN_0049e748  [dead]
//   [x] 0x49e860  CKHkS08FogHorn_Load
//
//   [ ] 0x9c4d80  CKHkS08FogHorn_IsKindOfClass  [inline]
//   [ ] 0x9c4dd8  CKHkS08FogHorn_GetClassType  [inline]
//   [ ] 0x9c4de0  CKHkS08FogHorn_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08FogHorn.h"
#include "Spyro2008/groups/C22SpyroShims.h"

#include "k2000/io/IKFile.h"
#include "k2000/core/Stub.h"
#include "crt/ppc_ops.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CKAACylinder.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"

#include <cmath>
#include <cstring>

namespace {
// A float pair read with one 8-byte Read, then both words swapped (the inlined swap of the original).
void ReadFloatPair(IKFile* file, float* dst) {
    uint32_t words[2];
    ReadU32LEWords(file, words, 2);
    std::memcpy(dst, words, sizeof(words));
}
}  // namespace

// 0x0049e860 CKHkS08FogHorn_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08FogHorn::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fUnk40);
        ReadF32LE(file, &m_fUnk44);
        IKFile_ReadRef(file, &m_pUnk4C);
        IKFile_ReadRef(file, &m_pUnk50);
        ReadF32LE(file, &m_fUnk54);
        ReadF32LE(file, &m_fUnk5C);
        ReadF32LE(file, &m_fUnk60);
        IKFile_ReadRef(file, &m_pUnk68);
        IKFile_ReadRef(file, &m_pUnk6C);
        IKFile_ReadRef(file, &m_pUnk7C);
        IKFile_ReadRef(file, &m_pUnk80);
        IKFile_ReadRef(file, &m_pUnk84);
        IKFile_ReadRef(file, &m_pUnk88);
        IKFile_ReadRef(file, &m_pUnk168);
        ReadF32LE(file, &m_fUnkC0);
        ReadF32LE(file, &m_fUnkC4);
        ReadF32LE(file, &m_fUnkC8);
        ReadF32LE(file, &m_fUnkCC);
        ReadF32LE(file, &m_fUnkD0);
        ReadF32LE(file, &m_fUnkD4);
        ReadF32LE(file, &m_fUnkD8);
        ReadF32LE(file, &m_fUnkDC);
        ReadF32LE(file, &m_fUnkE0);
        ReadF32LE(file, &m_fUnkE4);
        ReadU8(file, &m_unkE8);
        ReadU8(file, &m_unkE9);
        ReadF32LE(file, &m_fUnkEC);
        ReadF32LE(file, &m_fUnkF0);
        ReadF32LE(file, &m_fUnkF4);
        ReadF32LE(file, &m_fUnkF8);
        ReadF32LE(file, &m_fUnkFC);
        ReadF32LE(file, &m_fUnk100);
        ReadF32LE(file, &m_fUnk104);
        ReadF32LE(file, &m_fUnk108);
        ReadF32LE(file, &m_fUnk10C);
        ReadF32LE(file, &m_fUnk110);
        ReadU8(file, &m_unk114);
        ReadU8(file, &m_unk115);
        ReadFloatPair(file, m_fUnk98);
        ReadFloatPair(file, m_fUnkA0);
        ReadFloatPair(file, m_fUnkA8);
        ReadFloatPair(file, m_fUnkB0);
        ReadF32LE(file, &m_fUnkB8);
        ReadF32LE(file, &m_fUnkBC);
        IKFile_ReadRef(file, &m_pUnk38);
        ReadU32LE(file, &m_unk74);
        IKFile_ReadRef(file, &m_pUnk90);
        ReadU8(file, &m_unk94);
        ReadU8(file, &m_unk95);
        ReadF32LE(file, &m_fUnk20);
        ReadF32LE(file, &m_fUnk24);
        ReadF32LE(file, &m_fUnk28);
        ReadU8(file, &m_unk78);
        ReadU8(file, &m_unk79);
        ReadU8(file, &m_unk7A);
        m_unk124.Load(file, K_LEVEL_PLATEFORMS);
        m_unk12C.Load(file, K_LEVEL_PLATEFORMS);
        ReadU8(file, &m_unk116);
        ReadU8(file, &m_unk117);
        ReadF32LE(file, &m_fUnk118);
        ReadU8(file, &m_unk11C);
        ReadU8(file, &m_unk11D);
        ReadF32LE(file, &m_fUnk120);
    }
    return 1;
}

// 0x0049d430 CKHkS08FogHorn_PostLoad: CKHkActorBase_d82_maybe_PostLoad 0x3f6e70 -> IKLife_PostLoad 0x19f68 (level
// type only: bit 2 of the bit array), the horn's matrix (RwMatrixCreate_Thunk), then the collision cylinder
// (+0x38) is set up: owner type 1, owner = this, its flag bit 7, half height (+0x30) = the horn's +0x40 * 0.5f
// (TOC +0x60b4), radius (+0x2c) = the horn's +0x44, bounding radius (+0x20) = sqrt(radius^2 + half height^2).
int32_t CKHkS08FogHorn::PostLoad(int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) m_bitArray = (m_bitArray & 0xfffffffbu) | 4u;
    m_pUnk70 = RwMatrixCreate_Thunk();
    CKAACylinder* cylinder = static_cast<CKAACylinder*>(m_pUnk38);
    cylinder->m_ui16PropertiesFlags = 0;
    cylinder->m_ui8OwnerType = 0;
    cylinder = static_cast<CKAACylinder*>(m_pUnk38);
    cylinder->m_ui8OwnerType = 1;
    cylinder = static_cast<CKAACylinder*>(m_pUnk38);
    cylinder->m_pOwner = this;
    cylinder = static_cast<CKAACylinder*>(m_pUnk38);
    cylinder->m_ba8Infos = static_cast<uint8_t>((cylinder->m_ba8Infos & 0x7fu) | 0x80u);
    const float radius = m_fUnk44;
    const float radiusSquared = radius * radius;  // fmuls
    cylinder = static_cast<CKAACylinder*>(m_pUnk38);
    const float oldHalfHeight = cylinder->m_fCylinderHalfHeight;
    cylinder->m_fCylinderRadius = radius;
    // Math_Sqrtf 0x10690 (fsqrts); this first result is overwritten below.
    cylinder->m_fRadius = std::sqrt(ppc::fmadds(oldHalfHeight, oldHalfHeight, radiusSquared));
    cylinder = static_cast<CKAACylinder*>(m_pUnk38);
    const float halfHeight = m_fUnk40 * 0.5f;
    const float cylinderRadiusSquared = cylinder->m_fCylinderRadius * cylinder->m_fCylinderRadius;
    cylinder->m_fCylinderHalfHeight = halfHeight;
    cylinder->m_fRadius = std::sqrt(ppc::fmadds(halfHeight, halfHeight, cylinderRadiusSquared));
    return 1;
}

// 0x0049be48 CKHkS08FogHorn_SetDefaultState (after the empty base call KStub_Nop_3f72a0)
void CKHkS08FogHorn::SetDefaultState(int32_t /*flag*/) {
    m_unk7B[0] = m_unk7A;
}

// 0x0049bef8 CKHkS08FogHorn_Start
void CKHkS08FogHorn::Start() {
    // CKHkActorBase_d82_maybe_ResetRuntime 0x3f6e48: empty.
    m_unk8C = 0;
    Restart();  // vt+0x54
}

// 0x0049c880 CKHkS08FogHorn_Restart
void CKHkS08FogHorn::Restart() {
    m_unk34 = m_unk34 & 0x0000ffffu;  // the bytes at +0x34 and +0x35
    m_unk2C = 0;
    if ((m_bitArray & 4u) == 0) {
        CKSoundDictionaryID* dictionary = static_cast<CKSoundDictionaryID*>(m_pUnk50);
        CKSound* sound = CKSoundDictionaryID_GetSound(dictionary, 1);
        if (sound == nullptr) {
            m_fUnk30 = 0.0f;
        } else {
            sound = CKSoundDictionaryID_GetSound(dictionary, 1);
            m_fUnk30 = sound->m_fVolume * sound->m_fVolumeScale;  // +0x04 * +0x20 (fmuls)
        }
    }
    ResetEffects();
    c22spyro::SetBeByte(m_unk134[0], 0, 0);  // the byte at +0x134
    m_fUnk58 = 0.0f;
    m_unk64 = m_unk64 & 0x00ffffffu;  // the byte at +0x64
    m_unk48 = m_unk48 & 0x00ffffffu;  // the byte at +0x48
}

// 0x0049c548 CKHkS08FogHorn_ResetEffects_maybe
void CKHkS08FogHorn::ResetEffects() {
    if (m_unk8C != 0) {
        // STUB(C2.2): the horn's running effect object is released with its vt+0x58(this). Start clears +0x8c
        // just before the first Restart; only the horn's update sets it, which is not ported yet.
        DOTD_STUB_ONCE("CKHkS08FogHorn::ResetEffects: running effect");
    }
    if ((m_bitArray & 4u) != 0) return;
    CParticlesNodeFx* const nodes[2] = {static_cast<CParticlesNodeFx*>(m_pUnk80), static_cast<CParticlesNodeFx*>(m_pUnk84)};
    for (CParticlesNodeFx* node : nodes) {
        if (node == nullptr) continue;
        node->m_sgProperties = node->m_sgProperties & 0xfff7fbffu;                              // bits 10, 19
        node->m_pRpPrtStdEmitter->flag = node->m_pRpPrtStdEmitter->flag & 0xfffffff7u;        // emit off
    }
    if (m_pUnk90 != nullptr) {
        CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pUnk90);
        leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | 4u;
    }
    CKSoundDictionaryID* dictionary = static_cast<CKSoundDictionaryID*>(m_pUnk50);
    for (uint32_t i = 0; i < 4; ++i) {
        if (CKSoundDictionaryID_GetSound(dictionary, i) != nullptr) {
            Sound_Stop(CKSoundDictionaryID_GetSound(dictionary, i), 0);
        }
    }
}
