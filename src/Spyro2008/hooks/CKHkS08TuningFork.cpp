// CKHkS08TuningFork.cpp - reconstructed original translation unit 0x4cdaa0-0x4d3438 (GAME_TOC1, main_toc1), 54 functions, 45 live.
// Primary class: CKHkS08TuningFork  key 0x2d42  category Hook  size 0x174  vtable 0xb29b58
// Other owners: CKHkS08PowerBucket (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4cdaa0  CKHkS08TuningFork_CheckHitByFearScream_maybe
//   [ ] 0x4cdc90  CKHkS08TuningFork_ReleaseRef9C_maybe  [dead]
//   [ ] 0x4cdcf8  RegisterCKHkS08TuningForkClass
//   [ ] 0x4cdd80  _GLOBAL__D_4cdd80
//   [ ] 0x4cdd90  _GLOBAL__I_4cdd90
//   [x] 0x4cdda0  CKHkS08TuningFork_MessageProc
//   [ ] 0x4cdeb8  CKHkS08TuningFork_InitCollisionVolume_maybe  [dead]
//   [x] 0x4cdf88  CKHkS08TuningFork_ApplyVibrationShake_maybe
//   [x] 0x4ce078  CKHkS08TuningFork_Resume  (the actor base's KStub_Nop_3f6e60: inherited)
//   [x] 0x4ce0a0  CKHkS08TuningFork_Pause  (the actor base's KStub_Nop_3f6e58: inherited)
//   [x] 0x4ce0c8  CKHkS08TuningFork_Stop  (the actor base's: inherited)
//   [x] 0x4ce0f0  CKHkS08TuningFork_Start
//   [ ] 0x4ce1c8  CKHkS08TuningFork_Save
//   [x] 0x4ce1f0  CKHkS08TuningFork_RecursiveRegistration  (the actor base's: inherited)
//   [x] 0x4ce218  CKHkS08TuningFork_Construct  [dead]
//   [x] 0x4ce270  CKHkS08TuningFork_DeleteArray
//   [x] 0x4ce310  CKHkS08TuningFork_Restart
//   [x] 0x4ce4b8  CKHkS08TuningFork_IsState1AndFlag121Set_maybe  (CKHkS08TuningFork.h)
//   [x] 0x4ce4e0  CKHkS08TuningFork_GetTriggerProp9A  (GetInfo's accessor)
//   [x] 0x4ce528  CKHkS08TuningFork_GetTriggerProp9B  (GetInfo's accessor)
//   [x] 0x4ce540  CKHkS08TuningFork_StopShakeAndRestorePose_maybe
//   [ ] 0x4ce5f0  CKHkS08TuningFork_StartShakeForState_maybe  [dead]
//   [x] 0x4ce660  CKHkS08TuningFork_IsVibrating_maybe  (CKHkS08TuningFork.h)
//   [x] 0x4ce6a0  CKHkS08TuningFork_BaseDestructor  (C++ destructor chain)
//   [ ] 0x4ce6d0  CKHkS08TuningFork_Construct_2  [dead]
//   [x] 0x4ce728  CKHkS08TuningFork_Destroy
//   [x] 0x4ce768  CKHkS08TuningFork_DeletingDestructor  (C++ deleting destructor)
//   [x] 0x4ce7b0  CKHkS08TuningFork_Destructor  (C++ destructor chain)
//   [x] 0x4ce7e0  CKHkS08TuningFork_GetInfo
//   [x] 0x4ce910  CKHkS08TuningFork_SetPhaseOffsetFrom_maybe
//   [x] 0x4ce960  CKHkS08TuningFork_SetMeshAlpha_maybe
//   [ ] 0x4ceb88  FUN_004ceb88  [dead]
//   [x] 0x4cebc8  CKHkS08TuningFork_ScaleParticles_maybe
//   [x] 0x4cf020  CKHkS08TuningFork_CreateArray
//   [x] 0x4cf0f0  CKHkS08TuningFork_Create
//   [x] 0x4cf158  CKHkS08TuningFork_UpdateFadeAlpha_maybe
//   [ ] 0x4cf380  FUN_004cf380  [dead]
//   [x] 0x4cf3c0  CKHkS08TuningFork_OnDeactivate
//   [x] 0x4cf530  CKHkS08TuningFork_Update
//   [x] 0x4cf788  CKHkS08TuningFork_OnActivate
//   [x] 0x4cfad0  CKHkS08TuningFork_PostLoad
//   [x] 0x4cfbb8  CKHkS08TuningFork_Load
//   [x] 0x4d0e30  CKHkS08TuningFork_TriggerExplosionFx_maybe
//   [x] 0x4d10e0  CKHkS08TuningFork_StartScaledParticleFx_maybe
//   [x] 0x4d17b8  CKHkS08TuningFork_State2
//   [x] 0x4d1b40  CKHkS08TuningFork_PlayShockWaveFx_maybe
//   [x] 0x4d1db0  CKHkS08TuningFork_PlayExplosionFx_maybe
//   [x] 0x4d2058  CKHkS08TuningFork_PlayShockWaveFx_2_maybe
//   [x] 0x4d22c8  CKHkS08TuningFork_State3
//   [x] 0x4d28d0  CKHkS08TuningFork_VibrateState_maybe
//   [x] 0x4d3358  CKHkS08PowerBucket_Delete  (CKHkS08PowerBucket_Delete: DOTD_DECLARE_FACTORIES, CKHkS08PowerBucket.h)
//   [x] 0x4d33a8  CKHkS08PowerBucket_vf190  (CKHkS08PowerBucket::Vf190, CKHkS08PowerBucket.h)
//   [ ] 0x4d33b0  CKHkS08PowerBucket_ReleaseRef1E4_maybe  [dead]
//   [ ] 0x4d3418  FUN_004d3418  [dead]
//
//   [x] 0x9c5db8  CKHkS08TuningFork_IsKindOfClass  (CKHkS08TuningFork.h)
//   [x] 0x9c5e10  CKHkS08TuningFork_GetClassType  (DOTD_CLASS_KEY)
//   [x] 0x9c5e18  CKHkS08TuningFork_GetClassID  (DOTD_CLASS_KEY)
#include "Spyro2008/hooks/CKHkS08TuningFork.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/groups/CKGrpS08Meca.h"
#include "Spyro2008/groups/CKGrpS08TuningFork.h"
#include "Spyro2008/logic/CKS08Damage.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKImpulsionCpnt.h"
#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/core/IKInfo.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/fx/UpdateParticleNodeSizeBoundingRadius.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/logic/fx/CKShockWaveNodeFx.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CKAACylinder.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"

// ---- C2.8 port-all P16 ----

// 0x004ce728 CKHkS08TuningFork_Destroy
void CKHkS08TuningFork::Destroy() {
    CKHkActorBase::Destroy();  // 0x003f6e08
    RwMatrixDestroy(reinterpret_cast<RwMatrix*>(m_pMatrix64));  // RwMatrixDestroy_Thunk 0x23f968 (no null test)
}

// 0x004ce7e0 CKHkS08TuningFork_GetInfo, with 0x004ce4e0 _GetTriggerProp9A and 0x004ce528 _GetTriggerProp9B
int32_t CKHkS08TuningFork::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1_3f7140
    int32_t own = 1;
    if (request == kGetInfoValueAccessor) {
        if (info->m_ui32Id == 0x9a) {
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                const CKHkS08TuningFork* fork = static_cast<CKHkS08TuningFork*>(o);
                if (fork->m_unk130 != 1 && fork->m_unk130 != 2) return 0u;
                return fork->m_unk121 != 0 ? 1u : 0u;
            }, 0);
        } else if (info->m_ui32Id == 0x9b) {
            own = AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                return static_cast<CKHkS08TuningFork*>(o)->m_unk130 == 3 ? 1u : 0u;
            }, 0);
        }
    }
    if (base == 2 || own == 2) return 2;
    if (base == 0) return 0;
    return own;
}

// 0x004ce910 CKHkS08TuningFork_SetPhaseOffsetFrom_maybe (360.0 and 0.0 from the TOC; a NaN passes both loops)
void CKHkS08TuningFork::SetPhaseOffsetFrom(float phase) {
    float offset = phase - m_fUnk70;
    while (offset < 0.0f) offset = offset + 360.0f;
    while (360.0f <= offset) offset = offset - 360.0f;
    m_fUnk74 = offset;
}

// 0x004cfbb8 CKHkS08TuningFork_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08TuningFork::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk30);
        IKFile_ReadRef(file, &m_pUnk4C);
        IKFile_ReadRef(file, &m_pUnk50);
        IKFile_ReadRef(file, &m_pUnk54);
        IKFile_ReadRef(file, &m_pUnk58);
        IKFile_ReadRef(file, &m_pUnk5C);
        IKFile_ReadRef(file, &m_pUnk60);
        ReadU32LE(file, &m_unk2C);
        ReadF32LE(file, &m_fUnk34);
        ReadF32LE(file, &m_fUnk3C);
        IKFile_ReadRef(file, &m_pUnk7C);
        IKFile_ReadRef(file, &m_pUnk84);
        IKFile_ReadRef(file, &m_pUnk100);
        ReadF32LE(file, &m_fUnk104);
        ReadF32LE(file, &m_fUnk10C);
        ReadF32LE(file, &m_fUnk110);
        ReadF32LE(file, &m_fUnk108);
        ReadF32LE(file, &m_fUnk11C);
        ReadF32LE(file, &m_fUnk118);
        IKFile_ReadRef(file, &m_pUnk94);
        IKFile_ReadRef(file, &m_pUnk8C);
        IKFile_ReadRef(file, &m_pUnk20);
        IKFile_ReadRef(file, &m_pUnk24);
        IKFile_ReadRef(file, &m_pUnk114);
        m_unk154.Load(file, K_LEVEL_PLATEFORMS);
        m_unk15C.Load(file, K_LEVEL_PLATEFORMS);
        ReadF32LE(file, &m_fUnk44);
        IKFile_ReadRef(file, &m_pUnkDC);
        IKFile_ReadRef(file, &m_pUnk98);
        ReadF32LE(file, &m_fUnkA0);
        ReadF32LE(file, &m_fUnkA4);
        ReadF32LE(file, &m_fUnkA8);
        ReadF32LE(file, &m_fUnkAC);
        ReadF32LE(file, &m_fUnkB0);
        ReadF32LE(file, &m_fUnkB4);
        ReadF32LE(file, &m_fUnkB8);
        ReadF32LE(file, &m_fUnkBC);
        ReadF32LE(file, &m_fUnkC0);
        ReadF32LE(file, &m_fUnkC4);
        ReadF32LE(file, &m_fUnkC8);
        ReadF32LE(file, &m_fUnkCC);
        ReadF32LE(file, &m_fUnkD0);
        ReadF32LE(file, &m_fUnkD4);
        ReadF32LE(file, &m_fUnkD8);
        IKFile_ReadRef(file, &m_pUnkE0);
        IKFile_ReadRef(file, &m_pUnkE4);
        m_unk16C.Load(file, K_LEVEL_PLATEFORMS);
        m_unk164.Load(file, K_LEVEL_PLATEFORMS);
        ReadF32LE(file, &m_fUnkE8);
        ReadF32LE(file, &m_fUnkEC);
        ReadU8(file, &m_unkF0);
        ReadU8(file, &m_unkF1);
        ReadF32LE(file, &m_fUnkF4);
        ReadF32LE(file, &m_fUnkF8);
        ReadU8(file, &m_unkFC);
        ReadU8(file, &m_unkFD);
        ReadF32LE(file, &m_fUnk128);
        ReadF32LE(file, &m_fUnk68);
        ReadF32LE(file, &m_fUnk6C);
    }
    return 1;
}

// ---- C2.8 port-final F07: the runtime (states, vibration, FX, activation) ----
namespace {

constexpr CVector3 kForkNull = {0.0f, 0.0f, 0.0f};   // 0x00c50d64 (TOC +0x69d0)
constexpr CVector3 kForkAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x69dc)

float ForkSqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }  // 0x00010690

CKSrvFx* ForkFx() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }  // engine +0x60
CKGrpS08TuningFork* ForkGroup() {
    // engine +0x8c -> +0x0c (the meca group) -> +0x44
    return static_cast<CKGrpS08TuningFork*>(static_cast<CKGrpS08Meca*>(g_pEngine->m_gameManager->m_unk04[2])->m_pUnk44);
}
CSGMovable* ForkNode(const CKHkS08TuningFork* fork) { return static_cast<CSGMovable*>(fork->m_pKGLObject); }
CKSoundDictionaryID* ForkSounds(const CKHkS08TuningFork* fork) { return static_cast<CKSoundDictionaryID*>(fork->m_pUnk100); }
const CVector3* FramePos(const RwFrame* frame) { return reinterpret_cast<const CVector3*>(&frame->ltm.pos); }  // +0x80
const CVector3* FrameModellingPos(const RwFrame* frame) {
    return reinterpret_cast<const CVector3*>(&frame->modelling.pos);  // +0x40
}

// The inlined geometry alpha walk (CKFearScream's SetMeshAlpha): every geometry takes `alpha` and the "alpha blended"
// property bit 11 (vt+0x60 when it changes); 0xff clears it, and a geometry with property bit 12 and a material of
// mode 1..6 keeps 0xff without blending.
void ForkSetGeometryAlpha(CNode* node, uint8_t alpha) {
    for (CGeometry* geometry = static_cast<CGeometry*>(node->m_lGeometryList); geometry != nullptr;
         geometry = geometry->m_pNext) {
        uint32_t blend = 0;
        uint8_t value = 0xff;
        if (alpha != 0xff) {
            blend = 1;
            value = alpha;
            if ((geometry->m_BitProperties & 0x1000u) != 0) {
                const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
                if (mode != 0 && mode <= 6) {
                    blend = 0;
                    value = 0xff;
                }
            }
        }
        geometry->m_cGeometryColor[3] = value;
        const uint32_t bits = geometry->m_BitProperties;
        if (((bits >> 11) & 1u) != blend) {
            geometry->m_BitProperties = (bits & 0xfffff7ffu) | (blend << 11);
            geometry->UpdateProperties();  // vt+0x60
        }
    }
}

// The alpha byte of `t` between `from` and `to`: fmadds(t, to - from, from), above 254 -> 0xfe, else its fctiwz low
// byte (NaN: 0).
uint8_t ForkAlpha(float t, uint8_t from, uint8_t to) {
    const float base = static_cast<float>(static_cast<int32_t>(from));
    const float span = static_cast<float>(static_cast<int32_t>(to) - static_cast<int32_t>(from));
    const float v = ppc::fmadds(t, span, base);
    if (v > 254.0f) return 0xfe;  // TOC +0x6990
    return static_cast<uint8_t>(ppc::fctiwz(v));
}

// One particle node of the effect scaled: its size property's start (x, y) and end (x, y) floats each set to `t`
// times the given value (each followed by the bounding radius update), then the standard initial velocity.
void ForkScaleNode(CParticlesNodeFx* node, float t, float v0, float v1, float v2, float v3, float v4) {
    const float values[5] = {v0, v1, v2, v3, v4};
    static const int32_t kSizeIndex[4] = {0, 1, 4, 5};  // +0x00, +0x04, +0x10, +0x14
    for (int32_t k = 0; k < 4; ++k) {
        const float value = values[k];
        const int32_t offset = RpPrtStdPropTabGetPropOffset(node->m_pRpPrtStdEmitter->emtClass->propTab,
                                                            rpPRTSTDPROPERTYCODEEMITTERPRTSIZE);  // TocBridge 0x98e120
        if (offset != -1) {
            reinterpret_cast<float*>(reinterpret_cast<uint8_t*>(node->m_pRpPrtStdEmitter) + offset)[kSizeIndex[k]] =
                value * t;
        }
        UpdateParticleNodeSizeBoundingRadius(node);  // 0x000e5c80
    }
    RpPrtStdEmitter* emitter = node->m_pRpPrtStdEmitter;
    reinterpret_cast<RpPrtStdEmitterStandard*>(reinterpret_cast<uint8_t*>(emitter) + emitter->emtClass->propTab->propOffset[1])
        ->prtInitVel = t * values[4];  // +0x50
}

// 0x0023fba8 Mat4_RotateAboutPoint_maybe (CKMeshPopNodeFx.cpp's local copy): `m` turned by `angle` degrees about `axis`
// through `point`.
void ForkRotateAboutPoint(float angle, CMatrix34* m, const CVector3* point, const CVector3* axis) {
    m->m_pos.x = m->m_pos.x - point->x;
    m->m_pos.y = m->m_pos.y - point->y;
    m->m_pos.z = m->m_pos.z - point->z;
    m->m_ui32Flags = m->m_ui32Flags & 0xfffdffffu;
    RwMatrixRotate(reinterpret_cast<RwMatrix*>(m), reinterpret_cast<const RwV3d*>(axis), angle, rwCOMBINEPOSTCONCAT);
    m->m_pos.x = m->m_pos.x + point->x;
    m->m_pos.y = m->m_pos.y + point->y;
    m->m_pos.z = m->m_pos.z + point->z;
}

// The angle brought into [0, 360) by whole turns, as the states do it (a NaN passes both loops).
float ForkWrap360(float angle) {
    if (!(angle >= 0.0f)) {  // bge
        do {
            angle = angle + 360.0f;  // TOC +0x6988
        } while (angle < 0.0f);
    }
    while (angle >= 360.0f) angle = angle - 360.0f;
    return angle;
}

// The geometry of a node shown (+0x10 bit 2 cleared) or hidden (set).
void ForkShow(IKSerializable* node, bool shown) {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    leaf->m_sgProperties = shown ? (leaf->m_sgProperties & 0xfffffffbu) : ((leaf->m_sgProperties & 0xfffffffbu) | 4u);
}

// A node's frame moved to `position` (modelling position, identity flag cleared, marked dirty).
void ForkPlaceNode(IKSerializable* node, const CVector3* position) {
    RwFrame* frame = static_cast<CSGMovable*>(node)->m_pRwFrame;
    frame->modelling.pos.z = position->z;
    frame->modelling.pos.x = position->x;
    frame->modelling.pos.y = position->y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// The cylinder (+0x114) owned by the fork and sized from +0x11c (radius) and +0x118 (height): the inlined set-up of
// PostLoad and OnActivate.
void ForkSetUpCylinder(CKHkS08TuningFork* fork) {
    CKAACylinder* cylinder = static_cast<CKAACylinder*>(fork->m_pUnk114);
    cylinder->m_ui16PropertiesFlags = 0;
    cylinder->m_ui8OwnerType = 0;
    static_cast<CKAACylinder*>(fork->m_pUnk114)->m_ui8OwnerType = 1;
    static_cast<CKAACylinder*>(fork->m_pUnk114)->m_pOwner = fork;
    cylinder = static_cast<CKAACylinder*>(fork->m_pUnk114);
    cylinder->m_ba8Infos = static_cast<uint8_t>((cylinder->m_ba8Infos & 0x7fu) | 0x80u);
    const float radius = fork->m_fUnk11C;
    cylinder->m_fCylinderRadius = radius;
    cylinder->m_fRadius =
        ForkSqrtf(ppc::fmadds(cylinder->m_fCylinderHalfHeight, cylinder->m_fCylinderHalfHeight, radius * radius));
    const float half = fork->m_fUnk118 * 0.5f;  // TOC +0x6960
    cylinder->m_fCylinderHalfHeight = half;
    cylinder->m_fRadius =
        ForkSqrtf(ppc::fmadds(half, half, cylinder->m_fCylinderRadius * cylinder->m_fCylinderRadius));
}

}  // namespace

Ps3MemberFnEntry<CKHkS08TuningFork::StateFn> g_tuningForkStates[] = {
    {0x00bcbed0u, &CKHkS08TuningFork::State0, "CKHkS08TuningFork_State0_Idle_maybe 0x4cda40", false},
    {0x00bcc290u, &CKHkS08TuningFork::State1, "CKHkS08TuningFork_VibrateState_maybe 0x4d28d0", false},
    {0x00bcc260u, &CKHkS08TuningFork::State2, "CKHkS08TuningFork_State2 0x4d17b8", false},
    {0x00bcc288u, &CKHkS08TuningFork::State3, "CKHkS08TuningFork_State3 0x4d22c8", false},
};

uint8_t CKHkS08TuningFork::CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_tuningForkStates, &m_pStateTable[state * 2u], "CKHkS08TuningFork state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

// The inlined state change of Restart (and CKGrpS08TuningFork_Update): the current state left (phase 2, unless none),
// `next` entered (phase 1) with the previous state.
void CKHkS08TuningFork::ChangeState(uint8_t next, IKTime* clock) {
    const uint8_t previous = m_unk130;
    if (previous != 0xff) CallState(previous, clock, 2, next);
    m_unk130 = next;
    CallState(next, clock, 1, previous);
}

// 0x004cda40 CKHkS08TuningFork_State0_Idle_maybe (its code sits in CKGrpS08TuningFork.cpp's unit): idle; to state 1
// once in a set (+0x2c not -1) and hit by a fear scream (+0x28); entering clears +0x120.
uint8_t CKHkS08TuningFork::State0(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase == 0) {
        if (static_cast<int32_t>(m_unk2C) == -1) return other;
        if (m_bUnk28 == 0) return other;
        return 1;
    }
    if (phase == 1) m_unk120 = 0;
    return other;
}

// 0x004cdaa0 CKHkS08TuningFork_CheckHitByFearScream_maybe: +0x28 set when one of the cylinder's contacts is a volume
// with properties bit 3 owned by the hero (class id 0x97) carrying an element damage (class id 0x267) of type 6.
void CKHkS08TuningFork::CheckHitByFearScream() {
    m_bUnk28 = 0;
    for (ICollision* c = static_cast<ICollision*>(static_cast<IKBoundingVolume*>(m_pUnk114)->m_CollisionResList);
         c != nullptr; c = c->m_pNext) {
        IKSerializable* other;
        if (static_cast<IKBoundingVolume*>(c->GetBoundingVolume1())->m_pOwner == this) {  // vt+0x00
            c->GetBoundingVolume1();
            other = c->GetBoundingVolume2();  // vt+0x04
        } else {
            c->GetBoundingVolume2();
            other = c->GetBoundingVolume1();
        }
        if (c->HasContactSet() == 0) continue;  // vt+0x08
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(other);
        if ((volume->m_ui16PropertiesFlags & 8u) == 0) continue;
        if (volume->m_pOwner->GetClassID() != 0x97) continue;  // vt+0x18
        IKSerializable* damage = volume->m_unk1c;
        if (damage == nullptr) continue;
        if (damage->GetClassID() != 0x267) continue;
        if (static_cast<CKS08Damage*>(damage)->m_ui32DamageType != 6) continue;
        m_bUnk28 = 1;
    }
}

// vt+0x1c 0x004cdda0 CKHkS08TuningFork_MessageProc: the actor messages, then 0x94b (+0x120 set) and 0x94c (the
// cylinder's height +0x118 and radius +0x11c into the query).
int32_t CKHkS08TuningFork::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own;
    if (message == 0x94b) {
        own = 0;
        m_unk120 = 1;
    } else {
        own = 1;
        if (message == 0x94c) {
            own = 0;
            SizeQuery* query = static_cast<SizeQuery*>(data);
            query->m_fHeight = m_fUnk118;
            query->m_fRadius = m_fUnk11C;
        }
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x004cdf88 CKHkS08TuningFork_ApplyVibrationShake_maybe: the quake of the state (1: +0x58, 3: +0x60) started if
// needed, evaluated at `scale` and applied over the rest pose (+0x64) as the node's matrix.
void CKHkS08TuningFork::ApplyVibrationShake(float scale, IKTime* clock) {
    CKQuakeCpntUpdater* quake;
    if (m_unk130 == 1) {
        quake = static_cast<CKQuakeCpntUpdater*>(m_pUnk58);
    } else if (m_unk130 == 3) {
        quake = static_cast<CKQuakeCpntUpdater*>(m_pUnk60);
    } else {
        // BUG(original): in any other state the fork itself is taken as the quake (only states 1 and 3 call this).
        quake = reinterpret_cast<CKQuakeCpntUpdater*>(this);
    }
    if (quake->m_bRunning == 0) quake->Start();  // 0x0024f770
    float out[15];
    quake->EvaluateScaled(clock->m_afDeltaTime[0], scale, out);  // 0x0024f5c8
    CMatrix34 matrix;
    ShakeSample_BuildMatrix(quake, out, &matrix, nullptr);  // 0x0024ee90
    Mat4_TransformPostConcat(&matrix, m_pMatrix64);         // 0x0023f760
    ForkNode(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
}

// vt+0x50 0x004ce0f0 CKHkS08TuningFork_Start: the state table (states 0..3), no state, four states, no particle effect,
// both quakes started, then Restart (vt+0x54).
void CKHkS08TuningFork::Start() {
    CKHkActorBase::Start();  // 0x003f6e48
    m_aStateTable[2] = 0x00bcc290u;  // state 1 (TOC +0x6968)
    m_aStateTable[6] = 0x00bcc288u;  // state 3 (TOC +0x696c)
    m_aStateTable[0] = 0x00bcbed0u;  // state 0 (TOC +0x6964)
    m_aStateTable[4] = 0x00bcc260u;  // state 2 (TOC +0x6970)
    m_aStateTable[1] = 0;
    m_aStateTable[3] = 0;
    m_aStateTable[7] = 0;
    m_aStateTable[5] = 0;
    m_pStateTable = m_aStateTable;
    m_unk130 = 0xff;
    m_unk131 = 4;
    m_pFx9C = nullptr;
    static_cast<CKQuakeCpntUpdater*>(m_pUnk60)->Start();
    static_cast<CKQuakeCpntUpdater*>(m_pUnk58)->Start();
    Restart();  // vt+0x54
}

// vt+0x54 0x004ce310 CKHkS08TuningFork_Restart: +0x120 cleared, the contacts read, back to state 0 (the current state
// left with no clock towards 0), both quakes stopped, the rest pose back (unless +0x0c bit 2) and the phase 0.
void CKHkS08TuningFork::Restart() {
    m_unk120 = 0;
    CheckHitByFearScream();
    const uint8_t previous = m_unk130;
    if (previous != 0xff) CallState(previous, nullptr, 2, 0);
    m_unk130 = 0;
    CallState(0, nullptr, 1, previous);
    m_bUnk28 = 0;
    static_cast<CKQuakeCpntUpdater*>(m_pUnk60)->Stop();  // 0x0024f738
    static_cast<CKQuakeCpntUpdater*>(m_pUnk58)->Stop();
    if ((m_bitArray & 4u) == 0) ForkNode(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pMatrix64));
    m_fUnk70 = 0.0f;  // stw 0
}

// 0x004ce540 CKHkS08TuningFork_StopShakeAndRestorePose_maybe: the state's quake stopped (1: +0x58, 3: +0x60) and the
// rest pose back.
void CKHkS08TuningFork::StopShakeAndRestorePose() {
    if (m_unk130 == 1) {
        static_cast<CKQuakeCpntUpdater*>(m_pUnk58)->Stop();
    } else if (m_unk130 == 3) {
        static_cast<CKQuakeCpntUpdater*>(m_pUnk60)->Stop();
    }
    ForkNode(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pMatrix64));
}

// 0x004ce960 CKHkS08TuningFork_SetMeshAlpha_maybe: the glow mesh (+0xe0) faded between +0xf0 and +0xf1 at `t`, scaled
// between +0xe8 and +0xec and put at node +0x4c's position.
void CKHkS08TuningFork::SetMeshAlpha(float t) {
    if (m_pUnkE0 == nullptr) return;
    CNode* mesh = static_cast<CNode*>(m_pUnkE0);
    if (mesh->m_lGeometryList != nullptr) ForkSetGeometryAlpha(mesh, ForkAlpha(t, m_unkF0, m_unkF1));
    const float from = m_fUnkE8;
    const float span = m_fUnkEC - from;
    static_cast<CSGMovable*>(m_pUnkE0)->SetIdentity();  // 0x000d08f0
    static_cast<CSGMovable*>(m_pUnkE0)->SetUniformScale(from + span * t);  // 0x000d0970
    ForkPlaceNode(m_pUnkE0, FramePos(static_cast<CSGMovable*>(m_pUnk4C)->m_pRwFrame));
}

// 0x004cebc8 CKHkS08TuningFork_ScaleParticles_maybe: the particle effect's (+0x9c) three nodes scaled by `t`
// (+0xa0..+0xb0, +0xb4..+0xc4, +0xc8..+0xd8).
void CKHkS08TuningFork::ScaleParticles(float t) {
    if (m_pFx9C == nullptr) return;
    CKParticlesEffectNodeFx* effect = static_cast<CKParticlesEffectNodeFx*>(static_cast<IKSerializable*>(m_pFx9C));
    if (effect->m_ppParticleNodes[0] != nullptr) ForkScaleNode(effect->m_ppParticleNodes[0], t, m_fUnkA0, m_fUnkA4, m_fUnkA8, m_fUnkAC, m_fUnkB0);
    if (effect->m_ppParticleNodes[1] != nullptr) ForkScaleNode(effect->m_ppParticleNodes[1], t, m_fUnkB4, m_fUnkB8, m_fUnkBC, m_fUnkC0, m_fUnkC4);
    if (effect->m_ppParticleNodes[2] != nullptr) ForkScaleNode(effect->m_ppParticleNodes[2], t, m_fUnkC8, m_fUnkCC, m_fUnkD0, m_fUnkD4, m_fUnkD8);
}

// 0x004cf158 CKHkS08TuningFork_UpdateFadeAlpha_maybe: the second mesh (+0xe4) faded between +0xfc and +0xfd at `t`,
// scaled between +0xf4 and +0xf8 and put at the hot spot +0xdc.
void CKHkS08TuningFork::UpdateFadeAlpha(float t) {
    if (m_pUnkE4 == nullptr) return;
    CNode* mesh = static_cast<CNode*>(m_pUnkE4);
    if (mesh->m_lGeometryList != nullptr) ForkSetGeometryAlpha(mesh, ForkAlpha(t, m_unkFC, m_unkFD));
    const float from = m_fUnkF4;
    const float span = m_fUnkF8 - from;
    static_cast<CSGMovable*>(m_pUnkE4)->SetIdentity();
    static_cast<CSGMovable*>(m_pUnkE4)->SetUniformScale(from + span * t);
    CVector3 position;
    static_cast<CSGHotSpot*>(m_pUnkDC)->GetWorldPosition(&position);  // 0x000ce790
    ForkPlaceNode(m_pUnkE4, &position);
}

// vt+0xa4 0x004cf3c0 CKHkS08TuningFork_OnDeactivate: the rest pose back, the particle effect let go, the cylinder
// switched off and moved under sector 0's root.
void CKHkS08TuningFork::VfA4() {
    ForkNode(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pMatrix64));
    m_bUnk28 = 0;
    if (m_pFx9C != nullptr) {
        m_pFx9C->StopAndRelease(this);  // vt+0x58
        m_pFx9C = nullptr;
    }
    IKBoundingVolume* cylinder = static_cast<IKBoundingVolume*>(m_pUnk114);
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->DisableVolume(cylinder);  // 0x001920e8
    cylinder = static_cast<IKBoundingVolume*>(m_pUnk114);
    if (cylinder->m_pParent != nullptr) {
        cylinder->m_pParent->RemoveChild(cylinder);  // vt+0x78
        cylinder = static_cast<IKBoundingVolume*>(m_pUnk114);
    }
    static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[0])->m_pSectorRoot->AddChild(cylinder);  // vt+0x70
    if (m_pFx9C != nullptr) {
        m_pFx9C->StopAndRelease(this);
        m_pFx9C = nullptr;
    }
}

// vt+0x7c 0x004cf530 CKHkS08TuningFork_Update: the contacts read, the impulsions (+0x20, +0x24) in states 1 / 3, then
// the state machine.
void CKHkS08TuningFork::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68
    CheckHitByFearScream();
    uint8_t state = m_unk130;
    if (state == 3 || state == 1) {
        static_cast<CKImpulsionCpnt*>(m_pUnk20)->Update(clock->m_afDeltaTime[0]);  // 0x0024bd40
        static_cast<CKImpulsionCpnt*>(m_pUnk24)->Update(clock->m_afDeltaTime[0]);
        state = m_unk130;
    }
    if (state == 0xff) return;
    const uint8_t next = CallState(state, clock, 0, state);
    const uint8_t current = m_unk130;
    if (next == current) return;
    if (current != 0xff) CallState(current, clock, 2, next);
    m_unk130 = next;
    if (next != 0xff) CallState(next, clock, 1, current);
}

// vt+0xa0 0x004cf788 CKHkS08TuningFork_OnActivate: the node's modelling matrix kept as the rest pose (+0x64), the
// cylinder switched on and hung under the node, set up again, both meshes moved to the node and hidden, the phase 0.
void CKHkS08TuningFork::VfA0() {
    std::memcpy(m_pMatrix64, &ForkNode(this)->m_pRwFrame->modelling, 0x40);  // 16 words
    m_bUnk28 = 0;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->EnableVolume(static_cast<IKBoundingVolume*>(m_pUnk114));
    IKBoundingVolume* cylinder = static_cast<IKBoundingVolume*>(m_pUnk114);
    if (cylinder->m_pParent != nullptr) {
        cylinder->m_pParent->RemoveChild(cylinder);  // vt+0x78
        cylinder = static_cast<IKBoundingVolume*>(m_pUnk114);
    }
    static_cast<CSGBranch*>(m_pKGLObject)->AddChild(cylinder);  // vt+0x70
    ForkSetUpCylinder(this);
    if (m_pUnkE0 != nullptr) {
        ForkPlaceNode(m_pUnkE0, FramePos(ForkNode(this)->m_pRwFrame));
        ForkShow(m_pUnkE0, false);
    }
    if (m_pUnkE4 != nullptr) {
        ForkPlaceNode(m_pUnkE4, FramePos(ForkNode(this)->m_pRwFrame));
        ForkShow(m_pUnkE4, false);
    }
    m_fUnk70 = 0.0f;
}

// vt+0x30 0x004cfad0 CKHkS08TuningFork_PostLoad: the actor base's, the rest pose matrix created (+0x64), the cylinder
// set up.
int32_t CKHkS08TuningFork::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);  // 0x003f6e70
    m_pMatrix64 = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // 0x0023fa68
    ForkSetUpCylinder(this);
    return 1;
}

// 0x004d0e30 CKHkS08TuningFork_TriggerExplosionFx_maybe: an explosion of +0x84 at the hot spot +0xdc, triggered and let
// go (+0x80 keeps it).
void CKHkS08TuningFork::TriggerExplosionFx() {
    m_pFx80 = ForkFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk84), this);
    if (m_pFx80 == nullptr) return;
    CVector3 position;
    static_cast<CSGHotSpot*>(m_pUnkDC)->GetWorldPosition(&position);
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(static_cast<IKSerializable*>(m_pFx80));
    explosion->SetTranslation(&position, this);  // 0x001b66e8
    static_cast<CKExplosionNodeFx*>(static_cast<IKSerializable*>(m_pFx80))->Trigger(this, nullptr);  // 0x001b82a8
    m_pFx80->ReleaseReservation(this);  // vt+0x54
}

// 0x004d10e0 CKHkS08TuningFork_StartScaledParticleFx_maybe: without a running one, the particle effect of +0x98 attached
// to the hot spot +0xdc acquired into +0x9c and its three nodes scaled by `t`.
void CKHkS08TuningFork::StartScaledParticleFx(float t) {
    if (m_pFx9C != nullptr) return;
    CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_pUnk98);
    if (m_pUnkDC == nullptr) {
        data->m_pAttachHotSpot = nullptr;
        data->m_pAttachOwner = static_cast<CSGLeaf*>(m_pKGLObject);
    } else {
        data->m_pAttachOwner = nullptr;
        data->m_pAttachHotSpot = m_pUnkDC;
    }
    data = static_cast<CKParticlesEffectFxData*>(m_pUnk98);
    data->m_pAttachOwner = nullptr;
    data->m_pAttachHotSpot = m_pUnkDC;
    m_pFx9C = ForkFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk98), this);
    if (m_pFx9C == nullptr) return;
    ScaleParticles(t);  // the same three node scalings, inlined
}

// state 2 0x004d17b8 CKHkS08TuningFork_State2: the vibration grows over +0x44 seconds (the quake +0x60 at 0.8 of the
// ratio, then at the ratio; the phase turns at +0x68 .. +0x6c degrees per second), then state 3.
uint8_t CKHkS08TuningFork::State2(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        m_fUnk48 = 0.0f;
        static_cast<CKQuakeCpntUpdater*>(m_pUnk60)->Start();
        StartScaledParticleFx(0.0f);
        CKSound* sound = ForkSounds(this)->GetSound2(4);  // 0x00112bd8
        if (sound != nullptr) {
            sound->SetPosition(FramePos(ForkNode(this)->m_pRwFrame));  // 0x00110fa0
            sound->SetLoop(1);                                        // 0x00110fd0
            sound->Play(0.0f);                                        // 0x00111230
        }
        if (m_pUnkE4 != nullptr) ForkShow(m_pUnkE4, true);
        UpdateFadeAlpha(0.0f);
        m_fUnk70 = ForkWrap360(m_fUnk70);
        ForkGroup()->SyncGroupPhases(m_unk2C);  // 0x004ccbd8
        return other;
    }
    if (phase == 2) {
        ForkGroup()->ClearGroupSynced(m_unk2C);  // 0x004ccb98
        return other;
    }
    if (phase != 0) return other;
    float time = m_fUnk48 + clock->m_afDeltaTime[0];
    const float total = m_fUnk44;
    m_fUnk48 = time;
    if (time >= total) {
        time = total;
        m_fUnk48 = total;
    }
    const float ratio = time / total;
    if (static_cast<CKQuakeCpntUpdater*>(m_pUnk60)->m_bRunning == 0) static_cast<CKQuakeCpntUpdater*>(m_pUnk60)->Start();
    if (static_cast<CKQuakeCpntUpdater*>(m_pUnk58)->m_bRunning == 0) static_cast<CKQuakeCpntUpdater*>(m_pUnk58)->Start();
    float out[15];
    if (ratio < 1.0f) {
        static_cast<CKQuakeCpntUpdater*>(m_pUnk60)->EvaluateScaled(clock->m_afDeltaTime[0], ratio * 0.8f, out);  // TOC +0x69d8
    } else {
        static_cast<CKQuakeCpntUpdater*>(m_pUnk60)->EvaluateScaled(clock->m_afDeltaTime[0], ratio, out);
    }
    CMatrix34 matrix;
    ShakeSample_BuildMatrix(static_cast<CKQuakeCpntUpdater*>(m_pUnk60), out, &matrix, nullptr);
    const float dt = clock->m_afDeltaTime[0];
    const float slow = dt * m_fUnk68;
    float angle = ppc::fmsubs(ratio * dt, m_fUnk6C, slow);
    angle = ppc::fmadds(ratio, angle, slow);
    angle = angle + m_fUnk70;
    const float turn = ppc::fmadds(ratio, m_fUnk74, angle);
    m_fUnk70 = angle;
    ForkRotateAboutPoint(turn, &matrix, &kForkNull, &kForkAxisY);  // 0x0023fba8
    if (ratio >= 1.0f) m_fUnk70 = m_fUnk70 + m_fUnk74;
    Mat4_TransformPostConcat(&matrix, m_pMatrix64);
    ForkNode(this)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));
    CKSound* sound = ForkSounds(this)->GetSound2(4);
    if (sound != nullptr) sound->SetVolume(ratio);  // 0x00110f10
    ScaleParticles(ratio);
    UpdateFadeAlpha(ratio);
    return (m_fUnk48 >= m_fUnk44) ? 3 : other;
}

// 0x004d1b40 CKHkS08TuningFork_PlayShockWaveFx_maybe: a shock wave of +0x8c at node +0x4c into +0x88, triggered.
void CKHkS08TuningFork::PlayShockWaveFx() {
    m_pFx88 = ForkFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk8C), this);
    if (m_pFx88 == nullptr) return;
    CKShockWaveNodeFx* wave = static_cast<CKShockWaveNodeFx*>(static_cast<IKSerializable*>(m_pFx88));
    wave->SetPosition(FrameModellingPos(static_cast<CSGMovable*>(m_pUnk4C)->m_pRwFrame), this);  // 0x001d2410
    static_cast<CKShockWaveNodeFx*>(static_cast<IKSerializable*>(m_pFx88))->Trigger(this);       // 0x001d2cc8
}

// 0x004d1db0 CKHkS08TuningFork_PlayExplosionFx_maybe: an explosion of +0x7c at node +0x4c (into +0x78), triggered and
// let go.
void CKHkS08TuningFork::PlayExplosionFx() {
    m_pFx78 = ForkFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk7C), this);
    if (m_pFx78 == nullptr) return;
    static_cast<CKExplosionNodeFx*>(static_cast<IKSerializable*>(m_pFx78))
        ->SetTranslation(FrameModellingPos(static_cast<CSGMovable*>(m_pUnk4C)->m_pRwFrame), this);
    static_cast<CKExplosionNodeFx*>(static_cast<IKSerializable*>(m_pFx78))->Trigger(this, nullptr);
    m_pFx78->ReleaseReservation(this);
}

// 0x004d2058 CKHkS08TuningFork_PlayShockWaveFx_2_maybe: a shock wave of +0x94 at node +0x4c into +0x90, triggered.
void CKHkS08TuningFork::PlayShockWaveFx2() {
    m_pFx90 = ForkFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk94), this);
    if (m_pFx90 == nullptr) return;
    static_cast<CKShockWaveNodeFx*>(static_cast<IKSerializable*>(m_pFx90))
        ->SetPosition(FrameModellingPos(static_cast<CSGMovable*>(m_pUnk4C)->m_pRwFrame), this);
    static_cast<CKShockWaveNodeFx*>(static_cast<IKSerializable*>(m_pFx90))->Trigger(this);
}

// state 3 0x004d22c8 CKHkS08TuningFork_State3: the vibration dies over +0x3c seconds (the quake +0x60, the phase at
// +0x6c degrees per second); then back to state 0 when the set lets the fork go.
uint8_t CKHkS08TuningFork::State3(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        QueueTriggerSignals(&m_unk15C);  // 0x00236338 (the fork as sender)
        m_fUnk40 = 0.0f;  // stw 0
        TriggerExplosionFx();
        PlayShockWaveFx2();  // inlined
        CKSound* sound = ForkSounds(this)->GetSound(3);  // 0x00112bc0
        if (sound != nullptr) {
            ForkSounds(this)->GetSound(3)->SetPosition(FramePos(ForkNode(this)->m_pRwFrame));
            ForkSounds(this)->GetSound(3)->Play(0.0f);
        }
        return other;
    }
    if (phase == 2) {
        if (m_pFx90 != nullptr) m_pFx90->StopAndRelease(this);  // vt+0x58 (+0x90 kept)
        if (m_pFx9C != nullptr) {
            m_pFx9C->StopAndRelease(this);
            m_pFx9C = nullptr;
        }
        if (m_pUnkE4 != nullptr) ForkShow(m_pUnkE4, false);
        if (ForkSounds(this)->GetSound(3) != nullptr) Sound_Stop(ForkSounds(this)->GetSound(3), 0);  // 0x001111b0
        if (ForkSounds(this)->GetSound(4) != nullptr) Sound_Stop(ForkSounds(this)->GetSound(4), 0);
        if (other == 0 && ForkSounds(this)->GetSound(5) != nullptr) {
            ForkSounds(this)->GetSound(5)->SetPosition(FramePos(ForkNode(this)->m_pRwFrame));
            ForkSounds(this)->GetSound(5)->Play(0.0f);
        }
        QueueTriggerSignals(&m_unk164);
        return other;
    }
    if (phase != 0) return other;
    const float time = m_fUnk40 + clock->m_afDeltaTime[0];
    m_fUnk40 = time;
    if (time >= m_fUnk3C) {
        if (static_cast<uint8_t>(ForkGroup()->ClearGroupPendingFlagForFork(this, m_unk2C)) != 0) return 0;  // 0x004ccca8
        return other;
    }
    const float ratio = 1.0f - time / m_fUnk3C;
    ApplyVibrationShake(ratio, clock);
    const float angle = ppc::fmadds(ratio * clock->m_afDeltaTime[0], m_fUnk6C, m_fUnk70);
    m_fUnk70 = angle;
    ForkNode(this)->RotateAboutPoint(angle, &kForkNull, &kForkAxisY);  // 0x000d0f80
    ScaleParticles(ratio);
    UpdateFadeAlpha(ratio);
    if (ForkSounds(this)->GetSound(4) == nullptr) return other;
    ForkSounds(this)->GetSound(4)->SetVolume(ratio);
    return other;
}

// state 1 0x004d28d0 CKHkS08TuningFork_VibrateState_maybe: the fork rings: the impulsion +0x20 (its value the
// vibration) is kicked by each fear scream; at full vibration it is held +0x128 seconds (the explosion and the
// trigger +0x154 the first time); when it dies down the set may let the fork go (trigger +0x16c, state 0).
uint8_t CKHkS08TuningFork::State1(IKTime* clock, int32_t phase, uint8_t other) {
    CKImpulsionCpnt* impulsion = static_cast<CKImpulsionCpnt*>(m_pUnk20);
    if (phase == 1) {
        std::memset(&impulsion->m_unk04[1], 0, 4);  // stw 0
        static_cast<CKImpulsionCpnt*>(m_pUnk20)->m_unk04[0] = 1.0f;
        std::memset(&static_cast<CKImpulsionCpnt*>(m_pUnk20)->m_fValue, 0, 4);
        static_cast<CKImpulsionCpnt*>(m_pUnk20)->Impulse(1.0f);  // 0x0024bce0
        PlayShockWaveFx();  // inlined
        if (m_pUnkE0 != nullptr) ForkShow(m_pUnkE0, true);
        SetMeshAlpha(0.0f);
        if (ForkSounds(this)->GetSound(0) != nullptr) {
            ForkSounds(this)->GetSound(0)->SetPosition(FramePos(ForkNode(this)->m_pRwFrame));
            ForkSounds(this)->GetSound(0)->Play(0.0f);
        }
        if (ForkSounds(this)->GetSound(1) != nullptr) {
            ForkSounds(this)->GetSound(1)->SetPosition(FramePos(ForkNode(this)->m_pRwFrame));
            ForkSounds(this)->GetSound(1)->SetLoop(1);
            ForkSounds(this)->GetSound(1)->Play(0.0f);
        }
        m_unk121 = 0;
        m_unk122 = 0;
        return other;
    }
    if (phase == 2) {
        if (m_pFx88 != nullptr) m_pFx88->StopAndRelease(this);  // +0x88 kept
        if (m_pUnkE0 != nullptr) ForkShow(m_pUnkE0, false);
        if (ForkSounds(this)->GetSound(0) != nullptr) Sound_Stop(ForkSounds(this)->GetSound(0), 0);
        if (ForkSounds(this)->GetSound(1) != nullptr) Sound_Stop(ForkSounds(this)->GetSound(1), 0);
        if (other == 0 && ForkSounds(this)->GetSound(2) != nullptr) {
            ForkSounds(this)->GetSound(2)->SetPosition(FramePos(ForkNode(this)->m_pRwFrame));
            ForkSounds(this)->GetSound(2)->Play(0.0f);
        }
        m_unk122 = 0;
        return other;
    }
    if (phase != 0) return other;
    if (m_bUnk28 != 0) static_cast<CKImpulsionCpnt*>(m_pUnk20)->Impulse(1.0f);
    float level;  // f31
    uint8_t held = m_unk122;
    if (held != 0) {
        // L2e50: holding at full vibration.
        const float t = m_fUnk124 + clock->m_afDeltaTime[0];
        m_fUnk124 = t;
        if (!(m_fUnk128 <= t)) goto L29f8;  // cror eq|lt
        static_cast<CKImpulsionCpnt*>(m_pUnk20)->m_fValue = 1.0f;
        m_unk122 = 0;  // stb r29 (the phase, 0)
        goto L2a0c;
    } else {
        const float value = static_cast<CKImpulsionCpnt*>(m_pUnk20)->m_fValue;
        if (value <= 0.0f) {
            // L32f8: died down.
            if (static_cast<uint8_t>(ForkGroup()->ClearGroupPendingFlagForFork(this, m_unk2C)) != 0) {
                QueueTriggerSignals(&m_unk16C);
                m_unk121 = held;  // 0
                return 0;
            }
            held = m_unk122;
            goto L29f8;
        }
        if (!(value >= 1.0f)) goto L2a0c;
        m_fUnk124 = 0.0f;
        m_unk122 = 1;
        held = 1;
        if (m_unk121 == 0) {
            // L3034: the first full vibration: the explosion, the set told, the trigger.
            PlayExplosionFx();  // inlined
            ForkGroup()->AreOtherForksVibrating(this, m_unk2C);  // 0x004ccd48
            QueueTriggerSignals(&m_unk154);
            held = m_unk122;
            m_unk121 = 1;
        }
    }
L29f8:
    level = 1.0f;
    if (held != 0) goto L2a1c;
L2a0c:
    level = static_cast<CKImpulsionCpnt*>(m_pUnk20)->m_fValue;
    if (level < 1.0f) {
        ApplyVibrationShake(level * 0.8f, clock);  // TOC +0x69d8
        goto L2a2c;
    }
L2a1c:
    ApplyVibrationShake(level, clock);
L2a2c: {
    const float angle = ForkWrap360(ppc::fmadds(level * clock->m_afDeltaTime[0], m_fUnk68, m_fUnk70));
    m_fUnk70 = angle;
    ForkNode(this)->RotateAboutPoint(angle, &kForkNull, &kForkAxisY);  // 0x000d0f80
    if (ForkSounds(this)->GetSound(1) != nullptr) ForkSounds(this)->GetSound(1)->SetVolume(level);
    SetMeshAlpha(level);
    return other;
}
}
