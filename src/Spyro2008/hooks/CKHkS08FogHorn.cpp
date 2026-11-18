// CKHkS08FogHorn.cpp - reconstructed original translation unit 0x49b440-0x49f968 (GAME_TOC1, main_toc1), 49 functions, 39 live.
// Primary class: CKHkS08FogHorn  key 0x2f02  category Hook  size 0x16c  vtable 0xb283d8
// Other owners: ChargeGauge (5)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x49b440  ChargeGauge_Construct_maybe  [dead]
//   [ ] 0x49b460  ChargeGauge_Construct_2_maybe  [dead]
//   [ ] 0x49b480  ChargeGauge_Update_maybe  [dead: no pointer to its descriptor 0xbc4fd8, no call]
//   [ ] 0x49b528  ChargeGauge_GetRatio_maybe  [dead: no pointer to its descriptor 0xbc4fe0, no call]
//   [ ] 0x49b550  ChargeGauge_Reset_maybe  [dead: no pointer to its descriptor 0xbc4fe8, no call]
//   [ ] 0x49b568  KStub_Nop_49b568  [dead]
//   [ ] 0x49b570  CKHkS08FogHorn_IsBlown_maybe  [dead: no pointer to its descriptor 0xbc4ff8, no call]
//   [ ] 0x49b578  CKHkS08FogHorn_SetNodeAlphaByRatio_maybe  [dead: no pointer to its descriptor 0xbc5000, no call]
//   [ ] 0x49b708  CKHkS08FogHorn_IsNode90Hidden_maybe  [dead]
//   [ ] 0x49b730  RegisterCKHkS08FogHornClass
//   [ ] 0x49b7a8  _GLOBAL__I_49b7a8
//   [ ] 0x49b7b8  CKHkS08FogHorn_InitCollisionVolume_maybe  [dead]
//   [ ] 0x49b888  CKHkS08FogHorn_UpdateFxParamByRatio_maybe  [dead]
//   [x] 0x49b978  CKHkS08FogHorn_UpdateSoundVolume_maybe
//   [x] 0x49ba48  CKHkS08FogHorn_GetInfo
//   [x] 0x49bb28  CKHkS08FogHorn_MessageProc
//   [ ] 0x49bc58  CKHkS08FogHorn_StartShakeEffect_maybe  [dead]
//   [x] 0x49bc80  CKHkS08FogHorn_UpdateBlowAnimation_maybe
//   [ ] 0x49be20  CKHkS08FogHorn_StopShakeEffect_maybe  [dead]
//   [x] 0x49be48  CKHkS08FogHorn_SetDefaultState
//   [x] 0x49be80  CKHkS08FogHorn_Resume  (empty / no effect: inherited)
//   [x] 0x49bea8  CKHkS08FogHorn_Pause  (empty / no effect: inherited)
//   [x] 0x49bed0  CKHkS08FogHorn_Stop  (inherited, empty)
//   [x] 0x49bef8  CKHkS08FogHorn_Start
//   [ ] 0x49bf58  CKHkS08FogHorn_Save
//   [x] 0x49bf80  CKHkS08FogHorn_RecursiveRegistration  (inherited: CKHkActorBase's)
//   [x] 0x49bfa8  CKHkS08FogHorn_Construct
//   [x] 0x49c020  CKHkS08FogHorn_DeleteArray
//   [ ] 0x49c0c0  CKHkS08FogHorn_DestructBody  [dead: no pointer to its descriptor 0xbc5118, no call]
//   [x] 0x49c138  CKHkS08FogHorn_DeletingDestructor  (the destructor; delete)
//   [x] 0x49c1c0  CKHkS08FogHorn_Destructor
//   [x] 0x49c238  CKHkS08FogHorn_Destroy  (header)
//   [x] 0x49c278  CKHkS08FogHorn_GetChargeRatio
//   [ ] 0x49c2b8  CKHkS08FogHorn_Construct_2  [dead: no pointer to its descriptor 0xbc5190, no call]
//   [x] 0x49c330  CKHkS08FogHorn_OnActivate
//   [x] 0x49c548  CKHkS08FogHorn_ResetEffects_maybe
//   [x] 0x49c758  CKHkS08FogHorn_OnDeactivate
//   [x] 0x49c858  CKHkS08FogHorn_SetEnabled
//   [x] 0x49c880  CKHkS08FogHorn_Restart
//   [x] 0x49c958  CKHkS08FogHorn_ScaleEmitterAByCharge_maybe  (ScaleEmitterByCharge(0))
//   [x] 0x49cd10  CKHkS08FogHorn_ScaleEmitterBByCharge_maybe  (ScaleEmitterByCharge(1))
//   [x] 0x49d0c8  CKHkS08FogHorn_CreateArray
//   [x] 0x49d1d8  CKHkS08FogHorn_Create
//   [ ] 0x49d268  CKHkS08FogHorn_SetNodeVisibleWithAlpha_maybe  [dead: no pointer to its descriptor 0xbc5210, no call]
//   [x] 0x49d430  CKHkS08FogHorn_PostLoad
//   [ ] 0x49d518  CKHkS08FogHorn_IsTargetInRangeAndFacing_maybe  [dead]
//   [x] 0x49d8d8  CKHkS08FogHorn_Update
//   [ ] 0x49e748  FUN_0049e748  [dead]
//   [x] 0x49e860  CKHkS08FogHorn_Load
//
//   [ ] 0x9c4d80  CKHkS08FogHorn_IsKindOfClass  [inline]
//   [ ] 0x9c4dd8  CKHkS08FogHorn_GetClassType  [inline]
//   [ ] 0x9c4de0  CKHkS08FogHorn_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08FogHorn.h"
#include "k2000/core/IKInfo.h"
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
#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/fx/UpdateParticleNodeSizeBoundingRadius.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKSparkNodeFx.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/managers/CKInput.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/system/IKTime.h"

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
        ReadF32LE(file, &m_fUnk74);
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
    m_pUnk8C = nullptr;
    Restart();  // vt+0x54
}

// 0x0049c880 CKHkS08FogHorn_Restart
void CKHkS08FogHorn::Restart() {
    m_bUnk34 = 0;
    m_bUnk35 = 0;
    m_fUnk2C = 0.0f;  // stw 0
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
    m_bUnk134 = 0;
    m_fUnk58 = 0.0f;
    m_bUnk64 = 0;
    m_bUnk48 = 0;
}

// 0x0049c548 CKHkS08FogHorn_ResetEffects_maybe
void CKHkS08FogHorn::ResetEffects() {
    // The running effect released (vt+0x58 StopAndRelease with this hook as the owner); the pointer stays.
    if (m_pUnk8C != nullptr) m_pUnk8C->StopAndRelease(this);
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

// 0x0049ba48 CKHkS08FogHorn_GetInfo, with 0x0049c278 GetChargeRatio: 0x98 the charge ratio (a float). The actor base
// answers 1.
int32_t CKHkS08FogHorn::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 0x98) return 1;
    return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return FloatBits(static_cast<CKHkS08FogHorn*>(o)->GetChargeRatio()); }, 2);
}

// 0x0049c858 CKHkS08FogHorn_SetEnabled
void CKHkS08FogHorn::SetEnabled(int32_t enabled) {
    if (static_cast<int32_t>(m_unk7B[0]) != enabled) m_fUnk58 = 0.0f;  // stw 0
    m_unk7B[0] = static_cast<uint8_t>(enabled);
    if (enabled == 0) ResetEffects();  // 0x0049c548
}

namespace {
CKGrpS08Hero* HornHeroGroup() { return static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]); }
CSGMovable* HornNode(const CKHkS08FogHorn* horn) { return static_cast<CSGMovable*>(horn->m_pKGLObject); }
CKSoundDictionaryID* HornSounds(const CKHkS08FogHorn* horn) { return static_cast<CKSoundDictionaryID*>(horn->m_pUnk50); }
CKSrvCollision* HornCollision() { return static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision); }

// Sound `index` at the node (its LTM position, frame +0x80) played; `loop` >= 0 sets the loop first.
void PlayHornSound(const CKHkS08FogHorn* horn, uint32_t index, int32_t loop) {
    CKSoundDictionaryID* sounds = HornSounds(horn);
    if (sounds->GetSound(index) == nullptr) return;  // 0x00112bc0
    if (loop >= 0) sounds->GetSound(index)->SetLoop(loop);  // 0x00110fd0
    const RwV3d& p = FrameLtm(HornNode(horn)->m_pRwFrame)->pos;
    const CVector3 position = {p.x, p.y, p.z};
    sounds->GetSound(index)->SetPosition(&position);  // 0x00110fa0
    sounds->GetSound(index)->Play(0.0f);              // 0x00111230 (TOC 0x6088)
}

void StopHornSound(const CKHkS08FogHorn* horn, uint32_t index) {
    CKSoundDictionaryID* sounds = HornSounds(horn);
    if (sounds->GetSound(index) != nullptr) sounds->GetSound(index)->Stop(0);  // 0x001111b0
}

// The rumble requests (CKInput_AddRumbleRequest_maybe 0x1049d8): the device is 1 when the hero group controls two heroes
// ((count ^ 2) - 1, its sign bit; GetControlledHeroCount 0x2ca288).
void HornRumble(CKHkS08FogHorn* horn, float duration, int8_t index, uint8_t motor, uint8_t value) {
    const uint8_t count = HornHeroGroup()->m_ui8ControlledHeroCount;
    const uint8_t device = count == 2 ? 1 : 0;
    g_pEngine->m_input->AddRumbleRequest(duration, horn, index, device, motor, value);
}

// An emitter node that runs is stopped: bits 10 and 19 cleared, the emitter's emit flag off.
void StopHornEmitter(CParticlesNodeFx* node) {
    if ((node->m_sgProperties & 0x400u) == 0) return;
    node->m_sgProperties &= 0xfff7fbffu;
    node->m_pRpPrtStdEmitter->flag &= 0xfffffff7u;
}

// An emitter node that does not run is started: shown (bit 2), running (bit 10), not pending (bit 19), the speed
// adjustment 0, the emitter active and emitting.
void StartHornEmitter(CParticlesNodeFx* node) {
    node->m_sgProperties &= 0xfffffffbu;
    node->m_sgProperties = ((node->m_sgProperties & 0xfffffbffu) | 0x400u) & 0xfff7ffffu;
    node->m_fEmissionSpeedAdjustment = 0.0f;  // +0x4c
    node->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;
}

// The mesh +0x90's alpha walk (as CKBeamBreath's SetMeshAlpha, the alpha computed per geometry): alpha = `ratio` *
// (+0x95 - +0x94) + +0x94 (fmadds), 0xfe above 254, else the low byte of fctiwz.
void SetHornMeshAlpha(const CKHkS08FogHorn* horn, CNode* node, float ratio) {
    for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr; geometry = geometry->m_pNext) {
        const int32_t low = horn->m_unk94;
        const int32_t span = static_cast<int32_t>(horn->m_unk95) - low;
        const float value = ppc::fmadds(ratio, static_cast<float>(static_cast<double>(span)), static_cast<float>(static_cast<double>(low)));
        uint8_t alpha = 0xfe;
        if (!(value > 254.0f)) alpha = static_cast<uint8_t>(ppc::fctiwz(value));  // TOC 0x608c
        uint32_t blend = 0;
        if (alpha != 0xff) {
            blend = 1;
            if ((geometry->m_BitProperties & 0x1000u) != 0) {
                const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
                if (mode != 0 && mode <= 6) {
                    blend = 0;
                    alpha = 0xff;
                }
            }
        }
        geometry->m_cGeometryColor[3] = alpha;
        const uint32_t bits = geometry->m_BitProperties;
        if (((bits >> 11) & 1u) != blend) {
            geometry->m_BitProperties = (bits & 0xfffff7ffu) | (blend << 11);
            geometry->UpdateProperties();  // vt+0x60
        }
    }
}

// RW_GetParticlePropertyOffset (TocBridge 0x98e120) of the node's emitter.
int32_t HornPropOffset(CParticlesNodeFx* node, int32_t propID) {
    return RpPrtStdPropTabGetPropOffset(node->m_pRpPrtStdEmitter->emtClass->propTab, propID);
}
}  // namespace

CKHkS08FogHorn::~CKHkS08FogHorn() {
    for (ContactHistoryNode* node = m_pContactHistory; node != nullptr;) {
        ContactHistoryNode* next = node->m_pNext;  // +0x14
        ContactHistory_FreeNode(node);
        node = next;
    }
    m_pContactHistory = nullptr;
}

// 0x0049bb28 CKHkS08FogHorn_MessageProc
int32_t CKHkS08FogHorn::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    switch (message) {
    case 0x94c: {
        FogHornSizeQuery* query = static_cast<FogHornSizeQuery*>(data);
        query->m_fHeight = m_fUnk40;  // +0x10
        query->m_fRadius = m_fUnk44;  // +0x0c
        own = 0;
        break;
    }
    case 0x94b:
        own = 0;
        m_bUnk48 = 1;
        m_bUnk34 = 1;
        break;
    case 0x996:
        m_bUnk34 = 1;
        break;
    case 0x997:
        m_bUnk35 = 1;
        break;
    default:
        break;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// 0x0049c330 CKHkS08FogHorn_OnActivate
void CKHkS08FogHorn::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_pUnk38);
    HornCollision()->EnableVolume(volume);  // 0x00192090
    if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
    static_cast<CSGBranch*>(m_pKGLObject)->AddChild(volume);                   // vt+0x70
    std::memcpy(m_pUnk70, &HornNode(this)->m_pRwFrame->modelling, sizeof(CMatrix34));  // frame +0x10..+0x4f
    static_cast<CKQuakeCpntUpdater*>(m_pUnk6C)->Start();  // 0x0024f770
    CParticlesNodeFx* a = static_cast<CParticlesNodeFx*>(m_pUnk80);
    a->m_sgProperties = (a->m_sgProperties & 0xfffffffbu) | 4u;
    CParticlesNodeFx* b = static_cast<CParticlesNodeFx*>(m_pUnk84);
    b->m_sgProperties = (b->m_sgProperties & 0xfffffffbu) | 4u;
    m_fUnk58 = 0.0f;  // stw 0
    m_bUnk64 = 0;
    if (m_pUnk168 != nullptr) {
        // STUB(C2.8 script-cine): ScriptedCameraHandle_Reset_maybe 0x165af8 (k2000/components/CKCameraEventCpnt.cpp, the
        // script-cine package's file). LVL010's horn has no scripted camera (+0x168 null in the level data).
        DOTD_STUB_ONCE("CKHkS08FogHorn_OnActivate: ScriptedCameraHandle_Reset_maybe 0x165af8 (C2.8 script-cine)");
    }
    m_bUnk134 = 0;
}

// 0x0049c758 CKHkS08FogHorn_OnDeactivate
void CKHkS08FogHorn::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_pUnk38);
    HornCollision()->DisableVolume(volume);  // 0x001920e8
    if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
    CKSector* base = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[0]);
    base->m_pSectorRoot->AddChild(volume);  // vt+0x70
    HornNode(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pUnk70));  // 0x000d0be8
    static_cast<CKQuakeCpntUpdater*>(m_pUnk6C)->Stop();                          // 0x0024f738
    ResetEffects();                                                               // 0x0049c548 (tail call)
}

// 0x0049b978 CKHkS08FogHorn_UpdateSoundVolume_maybe: sound 1's volume = the charge ratio while it plays.
void CKHkS08FogHorn::UpdateSoundVolume() {
    const float ratio = m_fUnk54 == 0.0f ? 1.0f : m_fUnk58 / m_fUnk54;
    CKSoundDictionaryID* sounds = HornSounds(this);
    if (sounds->GetSound(1) == nullptr) return;
    if (sounds->GetSound(1)->CountInstances() == 0) return;  // the +0x68 list walk
    sounds->GetSound(1)->SetVolume(ratio);  // 0x00110f10
}

// 0x0049bc80 CKHkS08FogHorn_UpdateBlowAnimation_maybe: not blown: the node back to its matrix +0x70. Blown: the quake
// (started when it is not running) evaluated over dt * lerp(+0x74, 1, ratio), scaled by the ratio, as a matrix times
// +0x70 into the node.
void CKHkS08FogHorn::UpdateBlowAnimation(IKTime* clock) {
    if (m_bUnk48 == 0) {
        HornNode(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pUnk70));
        return;
    }
    CKQuakeCpntUpdater* quake = static_cast<CKQuakeCpntUpdater*>(m_pUnk6C);
    if (quake->m_bRunning == 0) quake->Start();  // 0x0024f770
    const float kOne = 1.0f;   // TOC 0x6084
    const float kZero = 0.0f;  // TOC 0x6088
    float speed = kOne;
    const float low = m_fUnk74;
    if (low != kOne) {
        const float ratio = m_fUnk54 == kZero ? kOne : m_fUnk58 / m_fUnk54;
        speed = ppc::fmadds(ratio, kOne - low, low);
    }
    const float dt = clock->m_afDeltaTime[0];
    const float scale = m_fUnk54 == kZero ? kOne : m_fUnk58 / m_fUnk54;
    float out[15];
    quake->EvaluateScaled(speed * dt, scale, out);  // 0x0024f5c8
    CMatrix34 m;
    ShakeSample_BuildMatrix(quake, out, &m, nullptr);  // 0x0024ee90
    Mat4_TransformPostConcat(&m, m_pUnk70);            // 0x0023f760
    HornNode(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&m));
}

// 0x0049c958 / 0x0049cd10 CKHkS08FogHorn_ScaleEmitterA/BByCharge_maybe: the emitter's particle sizes (property 5, words
// 0 / 1 / 4 / 5, each followed by the bounding radius update), its initial speed and its colour's alpha (the standard
// property; the PTank's constant colour and its material's too, flag 0x2000) lerped by the charge ratio.
void CKHkS08FogHorn::ScaleEmitterByCharge(uint32_t which) {
    const float ratio = m_fUnk54 == 0.0f ? 1.0f : m_fUnk58 / m_fUnk54;
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(which == 0 ? m_pUnk80 : m_pUnk84);
    // (to, from) pairs: sizes 0, 1, 4, 5, the speed; the alpha bytes.
    const float pa[10] = {m_fUnkC0, m_fUnkC4, m_fUnkC8, m_fUnkCC, m_fUnkD0, m_fUnkD4, m_fUnkD8, m_fUnkDC, m_fUnkE0, m_fUnkE4};
    const float pb[10] = {m_fUnkEC, m_fUnkF0, m_fUnkF4, m_fUnkF8, m_fUnkFC, m_fUnk100, m_fUnk104, m_fUnk108, m_fUnk10C, m_fUnk110};
    const float* p = which == 0 ? pa : pb;  // +0xc0..+0xe4 / +0xec..+0x110
    const uint8_t alphaFrom = which == 0 ? m_unkE8 : m_unk114;
    const uint8_t alphaTo = which == 0 ? m_unkE9 : m_unk115;
    const uint32_t words[4] = {0, 1, 4, 5};
    const uint32_t pairs[4] = {0, 4, 2, 6};  // (c0, c4), (d0, d4), (c8, cc), (d8, dc)
    for (uint32_t k = 0; k < 4; ++k) {
        const int32_t offset = HornPropOffset(node, rpPRTSTDPROPERTYCODEEMITTERPRTSIZE);
        if (offset != -1) {
            const float to = p[pairs[k]];
            const float from = p[pairs[k] + 1];
            reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(node->m_pRpPrtStdEmitter) + offset)[words[k]] =
                ppc::fmadds(ratio, to - from, from);
        }
        UpdateParticleNodeSizeBoundingRadius(node);  // 0x000e5c80
    }
    RpPrtStdEmitter* emitter = node->m_pRpPrtStdEmitter;
    RpPrtStdEmitterStandard* standard =
        reinterpret_cast<RpPrtStdEmitterStandard*>(reinterpret_cast<uint8_t*>(emitter) + emitter->emtClass->propTab->propOffset[1]);
    standard->prtInitVel = ppc::fmadds(ratio, p[8] - p[9], p[9]);  // (+0xe0, +0xe4)
    const int32_t span = static_cast<int32_t>(alphaTo) - static_cast<int32_t>(alphaFrom);
    const float alpha = ppc::fmadds(ratio, static_cast<float>(static_cast<double>(span)),
                                    static_cast<float>(static_cast<double>(static_cast<int32_t>(alphaFrom))));
    RwRGBA color = standard->prtColor;
    color.alpha = static_cast<uint8_t>(ppc::fctiwz(alpha));
    standard->prtColor = color;
    const int32_t offset = HornPropOffset(node, rpPRTSTDPROPERTYCODEEMITTERPTANK);
    if (offset == -1) return;
    RpPrtStdEmitterPTank* ptank = reinterpret_cast<RpPrtStdEmitterPTank*>(reinterpret_cast<uint8_t*>(emitter) + offset);
    if (ptank->pTank == nullptr) return;
    RpPTankData* data = ptank->pTank->ptank;  // the atomic + the PTank plugin offset (TOC 0x60d4)
    data->colorCC[0] = color.red;
    data->colorCC[1] = color.green;
    data->colorCC[2] = color.blue;
    data->colorCC[3] = color.alpha;
    RpPTankAtomicCopyConstantColorToMaterial(ptank->pTank);  // the geometry's first material's colour (+4)
    data->flags40 |= 0x2000u;
}

// 0x0049d8d8 CKHkS08FogHorn_Update
void CKHkS08FogHorn::Update(IKTime* clock) {
    // WorldObjectBase_Update_Nop 0x3f6e68: empty.
    if (m_unk7B[0] == 0) return;
    const float kZero = 0.0f;  // TOC 0x6088
    const float kOne = 1.0f;   // TOC 0x6084
    const float kHalfway = 0.6f;  // TOC 0x6130
    const float dt = clock->m_afDeltaTime[0];
    m_bUnk48 = 0;
    // The charge (+0x58, at most +0x54): sounding (+0x34) it runs down by +0x60 a second; held (+0x35) it stays; blown
    // (+0x48) the first frame adds +0x5c, the next ones dt; otherwise it runs down. `blowing` is the frame's +0x48.
    uint8_t blowing = 0;
    bool sounding = m_bUnk34 != 0;
    if (!sounding) {
        DetectWindBeamContact();  // 0x0049b230
        sounding = m_bUnk34 != 0;
    }
    if (sounding) {
        const float charge = m_fUnk58 - m_fUnk60 * dt;
        m_bUnk64 = 0;
        m_fUnk58 = charge;
        if (!(charge <= m_fUnk54)) {  // ble
            m_fUnk58 = m_fUnk54;
        } else if (charge < kZero) {
            m_fUnk58 = kZero;
        }
    } else if (m_bUnk35 == 0) {
        float charge;
        if (m_bUnk48 == 0) {
            charge = m_fUnk58 - m_fUnk60 * dt;
            m_bUnk64 = 0;
        } else if (m_bUnk64 == 0) {
            charge = m_fUnk58 + m_fUnk5C;
            m_bUnk64 = 1;
        } else {
            charge = m_fUnk58 + dt;
        }
        m_fUnk58 = charge;
        if (charge > m_fUnk54) {
            m_fUnk58 = m_fUnk54;
        } else if (charge < kZero) {
            m_fUnk58 = kZero;
        }
        blowing = m_bUnk48;
    }
    // The trigger starters: +0x124 when a blow starts, +0x12c when it ends (+0x134 the state between).
    if (m_bUnk134 != 0) {
        if (blowing == 0) {
            QueueTriggerSignals(&m_unk12C);  // 0x00236338
            m_bUnk134 = 0;
        }
    } else if (blowing != 0) {
        QueueTriggerSignals(&m_unk124);
        m_bUnk134 = 1;
    }
    UpdateBlowAnimation(clock);  // 0x0049bc80
    const float ratio = m_fUnk54 == kZero ? kOne : m_fUnk58 / m_fUnk54;
    // The feedback on the ratio's crossings against last frame's (+0x2c).
    float previous = m_fUnk2C;
    if (!(previous <= kZero) && ratio == kZero) {  // ble, beq: emptied
        PlayHornSound(this, 3, -1);
        StopHornSound(this, 1);
        previous = m_fUnk2C;
    }
    if (previous <= kZero && !(ratio <= kZero)) {  // cror lt|eq; ble: started
        HornRumble(this, m_fUnk118, 0, m_unk116, m_unk117);
        PlayHornSound(this, 0, -1);
        PlayHornSound(this, 1, 1);
        previous = m_fUnk2C;
    }
    if (previous < kOne && ratio >= kOne) {  // blt; cror gt|eq: full
        HornRumble(this, m_fUnk120, 1, m_unk11C, m_unk11D);
        previous = m_fUnk2C;
    }
    if (previous < kHalfway && ratio >= kHalfway) {  // bge; cror gt|eq
        PlayHornSound(this, 2, 1);
        previous = m_fUnk2C;
    }
    if (previous >= kHalfway && ratio < kHalfway) StopHornSound(this, 2);  // cror gt|eq; blt
    UpdateSoundVolume();  // 0x0049b978
    CParticlesNodeFx* emitterA = static_cast<CParticlesNodeFx*>(m_pUnk80);
    CParticlesNodeFx* emitterB = static_cast<CParticlesNodeFx*>(m_pUnk84);
    if (ratio == kZero) {
        StopHornEmitter(emitterA);
        StopHornEmitter(static_cast<CParticlesNodeFx*>(m_pUnk84));
        if (m_pUnk8C != nullptr) {
            StopOwnedSparkEffect(static_cast<CKSparkNodeFx*>(m_pUnk8C), this);  // 0x001d4698
            m_pUnk8C = nullptr;
        }
        CSGLeaf* mesh = static_cast<CSGLeaf*>(m_pUnk90);
        if (mesh != nullptr && (mesh->m_sgProperties & 4u) == 0) mesh->m_sgProperties |= 4u;
    } else {
        if ((emitterA->m_sgProperties & 0x400u) == 0) {
            CMatrix34 unused;
            static_cast<CSGHotSpot*>(m_pUnk7C)->GetWorldMatrix(&unused);  // 0x000ce970 (the result is not read)
            StartHornEmitter(static_cast<CParticlesNodeFx*>(m_pUnk80));
        }
        if ((emitterB->m_sgProperties & 0x400u) == 0) StartHornEmitter(static_cast<CParticlesNodeFx*>(m_pUnk84));
        if (m_pUnk8C == nullptr) {
            // CKSrvFx_AcquireFx inlined: the spark effect of the FX data +0x88, hung under the hot spot +0x7c (vt+0xa0).
            CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
            if (fxService != nullptr) {
                IKFx* fx = fxService->AcquireFx(static_cast<IKFxData*>(m_pUnk88), this);
                m_pUnk8C = fx;
                if (fx != nullptr) static_cast<CKSparkNodeFx*>(fx)->AttachNodeToHotSpot(m_pUnk7C);
            }
        }
        CNode* mesh = static_cast<CNode*>(m_pUnk90);
        if (mesh != nullptr && (mesh->m_sgProperties & 4u) != 0) {
            // Shown again: the alpha first taken with the byte +0x94 itself as the ratio (as the original's code), then
            // with the charge ratio below.
            const float first = static_cast<float>(static_cast<double>(m_unk94));
            mesh->m_sgProperties &= 0xfffffffbu;
            mesh = static_cast<CNode*>(m_pUnk90);
            if (mesh != nullptr) SetHornMeshAlpha(this, mesh, first);
        }
        const float alphaRatio = m_fUnk54 == kZero ? kOne : m_fUnk58 / m_fUnk54;
        mesh = static_cast<CNode*>(m_pUnk90);
        if (mesh != nullptr) SetHornMeshAlpha(this, mesh, alphaRatio);
        if (m_pUnk8C != nullptr) {
            const float r = m_fUnk54 == kZero ? kOne : m_fUnk58 / m_fUnk54;
            CKSparkNodeFx* spark = static_cast<CKSparkNodeFx*>(m_pUnk8C);
            const float v40[2] = {ppc::fmadds(r, m_fUnk98[0] - m_fUnkA0[0], m_fUnkA0[0]),
                                  ppc::fmadds(r, m_fUnk98[1] - m_fUnkA0[1], m_fUnkA0[1])};
            const float v50[2] = {ppc::fmadds(r, m_fUnkA8[0] - m_fUnkB0[0], m_fUnkB0[0]),
                                  ppc::fmadds(r, m_fUnkA8[1] - m_fUnkB0[1], m_fUnkB0[1])};
            spark->SetParamVec2_40(v40);                                         // 0x001d3f88
            spark->SetParamVec2_50(v50);                                         // 0x001d3fd8
            spark->SetParamFloat_68(ppc::fmadds(r, m_fUnkB8 - m_fUnkBC, m_fUnkBC));  // 0x001d4028
        }
        ScaleEmitterByCharge(0);  // 0x0049c958
        ScaleEmitterByCharge(1);  // 0x0049cd10
    }
    m_fUnk2C = m_fUnk54 == kZero ? kOne : m_fUnk58 / m_fUnk54;
}
