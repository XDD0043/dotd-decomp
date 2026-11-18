// CKHkS08FlamingTorch.cpp - reconstructed original translation unit 0x4961c0-0x49b440 (GAME_TOC1, main_toc1), 52 functions, 42 live.
// Primary class: CKHkS08FlamingTorch  key 0x2e82  category Hook  size 0x10c  vtable 0xb282e0
// Other owners: CKHkS08FogHorn (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4961c0  CKHkS08FlamingTorch_Delete
//   [ ] 0x496210  CKHkS08FlamingTorch_AttachCollisionNodeToActor_maybe  [dead]
//   [x] 0x4962a8  CKHkS08FlamingTorch_vfC8  (ApplyStatePreset)
//   [ ] 0x4962e0  CKHkS08FlamingTorch_ReleaseFxAt50_maybe  [dead]
//   [ ] 0x496348  FUN_00496348  [dead]
//   [ ] 0x496358  CKHkS08FlamingTorch_StopSound0_maybe  [dead]
//   [ ] 0x4963a0  CKHkS08FlamingTorch_InitCollisionVolume_maybe  [dead]
//   [x] 0x496470  CKHkS08FlamingTorch_DetectElementHits_maybe
//   [x] 0x496758  CKHkS08FlamingTorch_StartFlameFx_maybe
//   [x] 0x496a20  CKHkS08FlamingTorch_Resume  (inherited: CKHkActorBase's)
//   [x] 0x496a48  CKHkS08FlamingTorch_Pause  (inherited: CKHkActorBase's)
//   [x] 0x496a70  CKHkS08FlamingTorch_Stop  (inherited: CKHkActorBase's)
//   [x] 0x496a98  CKHkS08FlamingTorch_SetDefaultState
//   [x] 0x496ae0  CKHkS08FlamingTorch_GetInfo
//   [ ] 0x496bc0  CKHkS08FlamingTorch_Save
//   [x] 0x496be8  CKHkS08FlamingTorch_RecursiveRegistration  (inherited: CKHkActorBase's)
//   [x] 0x496c10  CKHkS08FlamingTorch_Construct  [dead]
//   [x] 0x496c70  CKHkS08FlamingTorch_DeleteArray
//   [ ] 0x496d10  RegisterCKHkS08FlamingTorchClass
//   [ ] 0x496d98  _GLOBAL__D_496d98
//   [ ] 0x496da8  _GLOBAL__I_496da8
//   [x] 0x496db8  CKHkS08FlamingTorch_DeletingDestructor  (the destructor)
//   [x] 0x496e40  CKHkS08FlamingTorch_Destructor  (the destructor)
//   [ ] 0x496eb8  CKHkS08FlamingTorch_Destructor_2  [dead]
//   [ ] 0x496f30  CKHkS08FlamingTorch_Construct_2  [dead]
//   [x] 0x496f90  CKHkS08FlamingTorch_Destroy  (inherited: CKHkActorBase's)
//   [x] 0x496fb8  CKHkS08FlamingTorch_IsLit_maybe  (CKHkS08FlamingTorch.h)
//   [x] 0x496fe0  CKHkS08FlamingTorch_ScaleFlameParticles_maybe
//   [x] 0x4971f0  CKHkS08FlamingTorch_AddHotspotPointsToFx_maybe
//   [x] 0x497478  CKHkS08FlamingTorch_CreateArray
//   [x] 0x497558  CKHkS08FlamingTorch_Create
//   [x] 0x4975c8  CKHkS08FlamingTorch_OnActivate
//   [x] 0x4977a0  CKHkS08FlamingTorch_OnDeactivate
//   [x] 0x497970  CKHkS08FlamingTorch_State1
//   [x] 0x497c98  CKHkS08FlamingTorch_UpdateFlameParticles_maybe
//   [x] 0x498350  CKHkS08FlamingTorch_StartFlameParticles_maybe
//   [x] 0x4987a0  CKHkS08FlamingTorch_State3_Lit_maybe
//   [x] 0x498988  CKHkS08FlamingTorch_State0_Unlit_maybe
//   [x] 0x498a20  CKHkS08FlamingTorch_TriggerHotSpotExplosionFx_maybe
//   [x] 0x498ce0  CKHkS08FlamingTorch_State2
//   [x] 0x498f90  CKHkS08FlamingTorch_Load
//   [x] 0x499bc0  CKHkS08FlamingTorch_PostLoad
//   [x] 0x499db0  CKHkS08FlamingTorch_Start
//   [x] 0x49a008  CKHkS08FlamingTorch_Update
//   [x] 0x49a240  CKHkS08FlamingTorch_vfCC
//   [x] 0x49a4b8  CKHkS08FlamingTorch_MessageProc
//   [x] 0x49ad80  CKHkS08FlamingTorch_Restart
//   [x] 0x49b1b8  CKHkS08FogHorn_Delete  (DOTD_DECLARE_FACTORIES, CKHkS08FogHorn.h)
//   [x] 0x49b208  CKHkS08FogHorn_ApplyStatePreset_maybe  (CKHkS08FogHorn.h)
//   [x] 0x49b230  CKHkS08FogHorn_DetectWindBeamContact
//   [ ] 0x49b430  KStub_ReturnArg4_49b430  [dead]
//   [ ] 0x49b438  KStub_ReturnArg4_49b438  [dead]
//
//   [ ] 0x9c4d18  CKHkS08FlamingTorch_IsKindOfClass  [inline]
//   [ ] 0x9c4d70  CKHkS08FlamingTorch_GetClassType  [inline]
//   [ ] 0x9c4d78  CKHkS08FlamingTorch_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08FlamingTorch.h"

#include "k2000/io/IKFile.h"
#include "k2000/core/IKInfo.h"
#include "k2000/math/Math.h"
#include "Spyro2008/hooks/CKHkS08FogHorn.h"
#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/components/CKImpulsionCpnt.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/fx/UpdateParticleNodeSizeBoundingRadius.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CKAACylinder.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"

// 0x00498f90 CKHkS08FlamingTorch_Load: the actor base, then the level data (type 0 only). The trigger
// starters are loaded with type 0.
int32_t CKHkS08FlamingTorch::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnkBC);
        IKFile_ReadRef(file, &m_pUnk4C);
        ReadF32LE(file, &m_fUnk30);
        ReadF32LE(file, &m_fUnk34);
        ReadF32LE(file, &m_fUnk44);
        ReadF32LE(file, &m_fUnk3C);
        m_unkAC.Load(file, K_LEVEL_PLATEFORMS);
        IKFile_ReadRef(file, &m_pUnkE0);
        IKFile_ReadRef(file, &m_pUnk94);
        ReadF32LE(file, &m_fUnk48);
        ReadU32LE(file, &m_unk98);
        IKFile_ReadRef(file, &m_pUnk54);
        IKFile_ReadRef(file, &m_pUnk28);
        IKFile_ReadRef(file, &m_pUnk88);
        m_unkB4.Load(file, K_LEVEL_PLATEFORMS);
        IKFile_ReadRef(file, &m_pUnk20);
        IKFile_ReadRef(file, &m_pUnk24);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        // BUG(original): no bound check; a count above 2 would write past the table.
        for (uint32_t i = 0; i < count; ++i) {
            SEntry& entry = m_aUnk5C[i];
            ReadF32LE(file, &entry.m_fUnk8);
            ReadF32LE(file, &entry.m_fUnkC);
            ReadF32LE(file, &entry.m_fUnk0);
            ReadF32LE(file, &entry.m_fUnk4);
            ReadF32LE(file, &entry.m_fUnk10);
        }
        IKFile_ReadRef(file, &m_pUnk9C);
        IKFile_ReadRef(file, &m_pUnkA0);
        IKFile_ReadRef(file, &m_pUnkA4);
        IKFile_ReadRef(file, &m_pUnkA8);
        IKFile_ReadRef(file, &m_pUnk8C);
        IKFile_ReadRef(file, &m_pUnk90);
        IKFile_ReadRef(file, &m_pUnkC0);
        ReadU8(file, &m_unkD8);
        ReadU8(file, &m_unkD9);
        ReadU8(file, &m_unkDA);
        ReadU8(file, &m_unkDD);
        ReadU8(file, &m_unkDE);
        ReadU8(file, &m_unkDF);
    }
    return 1;
}

// 0x0049b230 CKHkS08FogHorn_DetectWindBeamContact
void CKHkS08FogHorn::DetectWindBeamContact() {
    m_bUnk48 = 0;
    for (ICollision* c = static_cast<ICollision*>(static_cast<IKBoundingVolume*>(m_pUnk38)->m_CollisionResList); c != nullptr;
         c = c->m_pNext) {
        IKBoundingVolume* other;
        if (static_cast<IKBoundingVolume*>(c->GetBoundingVolume1())->m_pOwner == this) {  // vt+0x00
            c->GetBoundingVolume1();
            other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2());  // vt+0x04
        } else {
            c->GetBoundingVolume2();
            other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume1());
        }
        if (c->HasContactSet() == 0 || (other->m_ui16PropertiesFlags & 8u) == 0) continue;  // vt+0x08
        IKSerializable* damage = other->m_unk1c;
        IKSerializable* owner = other->m_pOwner;
        if (damage == nullptr) continue;
        if (damage->GetClassID() != 0x267) continue;  // vt+0x18: CKS08ElementDamage
        if (owner->GetClassID() != 0x97) continue;    // CKHkS08Hero
        if (static_cast<CKS08ElementDamage*>(damage)->m_unk20 != 7) continue;  // the damage type
        m_bUnk48 = 1;
    }
}

// 0x00496e40 CKHkS08FlamingTorch_Destructor: the contact history's nodes (+0x2c) back to their pool (in front of the free
// list 0x00ceaa74), the list cleared, then CKHkActorBase's destructor.
CKHkS08FlamingTorch::~CKHkS08FlamingTorch() {
    for (ContactHistoryNode* node = m_unk2C; node != nullptr;) {
        ContactHistoryNode* next = node->m_pNext;  // +0x14
        ContactHistory_FreeNode(node);
        node = next;
    }
    m_unk2C = nullptr;
}

// 0x00496a98 CKHkS08FlamingTorch_SetDefaultState
void CKHkS08FlamingTorch::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);  // KStub_Nop_3f72a0
    m_unkDB[1] = m_unkDD;
    m_unkDB[0] = static_cast<uint8_t>(m_unkD8 ^ 1);
}

// 0x004962a8 CKHkS08FlamingTorch_vfC8
void CKHkS08FlamingTorch::ApplyStatePreset(int32_t state) {
    if (state != 0) {
        m_unkDB[1] = m_unkDF;
        m_unkDB[0] = static_cast<uint8_t>(m_unkDA ^ 1);
        return;
    }
    m_unkDB[1] = m_unkDE;
    m_unkDB[0] = static_cast<uint8_t>(m_unkD9 ^ 1);
}

// 0x00496ae0 CKHkS08FlamingTorch_GetInfo, with its accessor 0x00496fb8 IsLit (descriptor 0x00bc4a88). The actor base's
// answer (KStub_Return1_3f7140: 1) merges to this one's.
int32_t CKHkS08FlamingTorch::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 0x98) return 1;
    return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
        return static_cast<uint32_t>(static_cast<CKHkS08FlamingTorch*>(o)->IsLit());
    }, 0);
}

// ---- C2.8 port-last Z5: the runtime (states, flame particles and lean, element hits, FX, activation) ----
namespace {

constexpr CVector3 kTorchNull = {0.0f, 0.0f, 0.0f};   // 0x00c50d64 (TOC +0x604c)
constexpr CVector3 kTorchAxisZ = {0.0f, 0.0f, 1.0f};  // 0x00c50d4c (TOC +0x6050)
constexpr CVector3 kTorchAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x6054)

float TorchSqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }  // 0x00010690

bool TorchSignBit(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
// The game's inlined cosf / sinf: the octant polynomials for a clear sign bit, the library's cosf 0x009a11d8 / sinf
// 0x009a1390 of the negated angle otherwise (the sine negated back).
float TorchCos(float x) { return TorchSignBit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }
float TorchSin(float x) { return TorchSignBit(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }

CKSrvFx* TorchFx() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }  // engine +0x60
CKSoundDictionaryID* TorchSounds(const CKHkS08FlamingTorch* torch) {
    return static_cast<CKSoundDictionaryID*>(torch->m_pUnkE0);
}
const CVector3* TorchNodePos(const CKHkS08FlamingTorch* torch) {  // the node's frame LTM position (+0x80)
    return reinterpret_cast<const CVector3*>(&static_cast<CSGMovable*>(torch->m_pKGLObject)->m_pRwFrame->ltm.pos);
}
CParticlesNodeFx* TorchParticles(IKSerializable* node) { return static_cast<CParticlesNodeFx*>(node); }

// A particle node set emitting (the inlined CParticlesNodeFx message 0x1a00 with a 1 byte): emitting (0x400) on,
// 0x80000 off, the speed adjustment 0 (a word store) and the emitter active and emitting (0xa).
void TorchStartEmitting(IKSerializable* node) {
    CParticlesNodeFx* fx = TorchParticles(node);
    fx->m_sgProperties = (fx->m_sgProperties | 0x400u) & 0xfff7ffffu;
    fx->m_fEmissionSpeedAdjustment = 0.0f;
    fx->m_pRpPrtStdEmitter->flag |= 0xau;
}
// ... and stopping: 0x400 and 0x80000 off, the emitter's emit flag (0x8) off.
void TorchStopEmitting(IKSerializable* node) {
    CParticlesNodeFx* fx = TorchParticles(node);
    fx->m_sgProperties &= 0xfff7fbffu;
    fx->m_pRpPrtStdEmitter->flag &= 0xfffffff7u;
}
// The node's geometry shown (+0x10 bit 2 cleared) or hidden (set).
void TorchShow(IKSerializable* node, bool shown) {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    leaf->m_sgProperties = shown ? (leaf->m_sgProperties & 0xfffffffbu) : ((leaf->m_sgProperties & 0xfffffffbu) | 4u);
}

// The flame particles' release (the effect's vt+0x58 with the torch, +0x50 cleared), when there are some.
void TorchReleaseParticles(CKHkS08FlamingTorch* torch) {
    if (torch->m_pFx50 == nullptr) return;
    torch->m_pFx50->StopAndRelease(torch);  // vt+0x58
    torch->m_pFx50 = nullptr;
}

// The flame loop (sound 0) stopped when any instance of it plays (the inlined instance count).
void TorchStopLoopIfPlaying(CKHkS08FlamingTorch* torch) {
    CKSound* sound = TorchSounds(torch)->GetSound(0);  // 0x00112bc0
    if (sound != nullptr && sound->CountInstances() != 0) Sound_Stop(sound, 0);  // 0x001111b0
}

// One particle node scaled by `t`: its size property's start (x, y) and end (x, y) floats (+0x00, +0x04, +0x10, +0x14)
// set to `t` times the entry's +0x00..+0x0c (each followed by the bounding radius update), then the standard initial
// velocity to `t` times the entry's +0x10.
void TorchScaleNode(CParticlesNodeFx* node, float t, const CKHkS08FlamingTorch::SEntry& entry) {
    const float values[4] = {entry.m_fUnk0, entry.m_fUnk4, entry.m_fUnk8, entry.m_fUnkC};
    static const int32_t kSizeIndex[4] = {0, 1, 4, 5};
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
        ->prtInitVel = t * entry.m_fUnk10;  // +0x50
}

// The explosion `fx` put at the hot spot +0x94 (its position, turned to its at), triggered and let go at once (vt+0x58).
void TorchTriggerAtHotSpot(CKHkS08FlamingTorch* torch, IKFx* fx) {
    CMatrix34 matrix;
    static_cast<CSGHotSpot*>(torch->m_pUnk94)->GetWorldMatrix(&matrix);  // 0x000ce970
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(static_cast<IKSerializable*>(fx));
    explosion->SetTranslation(&matrix.m_pos, torch);  // 0x001b66e8
    explosion->SetDirection(&matrix.m_at, torch);     // 0x001b5e20
    explosion->Trigger(torch, nullptr);               // 0x001b82a8
    fx->StopAndRelease(torch);                        // vt+0x58
}

}  // namespace

Ps3MemberFnEntry<CKHkS08FlamingTorch::StateFn> g_flamingTorchStates[] = {
    {0x00bc4bd0u, &CKHkS08FlamingTorch::State0, "CKHkS08FlamingTorch_State0_Unlit_maybe 0x498988", false},
    {0x00bc4b00u, &CKHkS08FlamingTorch::State1, "CKHkS08FlamingTorch_State1 0x497970", false},
    {0x00bc4be0u, &CKHkS08FlamingTorch::State2, "CKHkS08FlamingTorch_State2 0x498ce0", false},
    {0x00bc4bc8u, &CKHkS08FlamingTorch::State3, "CKHkS08FlamingTorch_State3_Lit_maybe 0x4987a0", false},
};

uint8_t CKHkS08FlamingTorch::CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_flamingTorchStates, &m_pStateTable[state * 2u], "CKHkS08FlamingTorch state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

void CKHkS08FlamingTorch::ChangeState(uint8_t next) {
    const uint8_t previous = m_unkE8;
    if (previous != 0xff) CallState(previous, nullptr, 2, next);
    m_unkE8 = next;
    CallState(next, nullptr, 1, previous);
}

// 0x00496470 CKHkS08FlamingTorch_DetectElementHits_maybe: the hit flags cleared; while enabled (+0xdb), each contact of
// the cylinder with a volume of properties bit 3 carrying a damage sets +0xc7, an element damage (class id 0x267) of type
// 0 / 1 / 7 sets +0xc4 / +0xc5 / +0xc6, and, while the lean is over (+0xd4 not above 0), the lean direction (+0xc8) is
// taken from the contact point towards the torch, flattened and normalised.
void CKHkS08FlamingTorch::DetectElementHits() {
    m_unkC7 = 0;
    m_unkC4 = 0;
    m_unkC5 = 0;
    m_unkC6 = 0;
    if (m_unkDB[0] == 0) return;
    for (ICollision* c = static_cast<ICollision*>(static_cast<IKBoundingVolume*>(m_pUnk28)->m_CollisionResList);
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
        IKSerializable* damage = volume->m_unk1c;
        if (damage == nullptr) continue;
        m_unkC7 = 1;
        if (damage->GetClassID() == 0x267) {  // vt+0x18: CKS08ElementDamage
            const uint32_t type = static_cast<CKS08ElementDamage*>(damage)->m_unk20;
            if (type == 0) {
                m_unkC4 = 1;
            } else if (type == 1) {
                m_unkC5 = 1;
            } else if (type == 7) {
                m_unkC6 = 1;
            }
        }
        if (!(m_fUnkD4 <= 0.0f)) continue;  // cror eq|lt (a NaN skips)
        const CVector3* point = c->GetWorldContactPoint();  // vt+0x20
        const CVector3* position = TorchNodePos(this);
        const float dy = position->y - point->y;
        const float dx = position->x - point->x;
        const float dz = position->z - point->z;
        m_vUnkC8.y = dy;
        m_vUnkC8.y = 0.0f;
        const float y = m_vUnkC8.y;
        m_vUnkC8.x = dx;
        m_vUnkC8.z = dz;
        const float length = TorchSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, y * y)));
        if (length == 0.0f) continue;
        const float inverse = 1.0f / length;
        const float x = m_vUnkC8.x;
        const float y2 = m_vUnkC8.y;
        const float z = m_vUnkC8.z;
        m_vUnkC8.z = inverse * z;
        m_vUnkC8.x = inverse * x;
        m_vUnkC8.y = inverse * y2;
    }
}

// 0x00496758 CKHkS08FlamingTorch_StartFlameFx_maybe: the flame's effect (+0x54) acquired into +0x58 (the inlined
// CKSrvFx::AcquireFx) and, when there is one, set off at the hot spot +0x94 and let go.
void CKHkS08FlamingTorch::StartFlameFx() {
    m_pFx58 = TorchFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk54), this);
    if (m_pFx58 == nullptr) return;
    TorchTriggerAtHotSpot(this, m_pFx58);
}

// 0x00496fe0 CKHkS08FlamingTorch_ScaleFlameParticles_maybe: each particle node of the flame particles (+0x50) scaled by
// `t` from its entry of the +0x5c table.
void CKHkS08FlamingTorch::ScaleFlameParticles(float t) {
    if (m_pFx50 == nullptr) return;
    const uint32_t count = static_cast<CKParticlesEffectNodeFx*>(static_cast<IKSerializable*>(m_pFx50))->m_ui32NodeCount;
    for (uint32_t i = 0; i != count; ++i) {
        CParticlesNodeFx* node =
            static_cast<CKParticlesEffectNodeFx*>(static_cast<IKSerializable*>(m_pFx50))->m_ppParticleNodes[i];
        if (node == nullptr) continue;
        // BUG(original): no bound check; an effect with more than 2 nodes reads past the table (as Load writes past it).
        TorchScaleNode(node, t, m_aUnk5C[i]);
    }
}

// 0x004971f0 CKHkS08FlamingTorch_AddHotspotPointsToFx_maybe: the world positions of the hot spots +0x9c, +0xa0, +0xa4,
// +0xa8 added as emit points of the particle node +0x8c (up to 64; property bit 13 set for each).
void CKHkS08FlamingTorch::AddHotspotPointsToFx() {
    IKSerializable* const hotSpots[4] = {m_pUnk9C, m_pUnkA0, m_pUnkA4, m_pUnkA8};
    CVector3 position;
    for (IKSerializable* hotSpot : hotSpots) {
        if (hotSpot == nullptr) continue;
        static_cast<CSGHotSpot*>(hotSpot)->GetWorldPosition(&position);  // 0x000ce790
        CParticlesNodeFx* node = TorchParticles(m_pUnk8C);
        if (node == nullptr || node->m_ui8NbActivePoints > 0x3f) continue;
        RwV3d* point = &node->m_pAdvEmtPointList->pointList[node->m_ui8NbActivePoints];
        point->z = position.z;
        point->x = position.x;
        point->y = position.y;
        node->m_sgProperties = (node->m_sgProperties & 0xffffdfffu) | 0x2000u;
        node->m_ui8NbActivePoints = static_cast<uint8_t>(node->m_ui8NbActivePoints + 1);
    }
}

// state 1 0x00497970 CKHkS08FlamingTorch_State1: the torch catches fire: the impulsion +0x20 (kicked again by each
// element 0 hit) grows the flame (0.8 of it until full); at full flame the flame FX, the emit points, the particle node
// +0x90 emitting and shown, the "lit" trigger (+0xac), state 3; when it dies down the particles let go, state 0.
uint8_t CKHkS08FlamingTorch::State1(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        CKImpulsionCpnt* impulsion = static_cast<CKImpulsionCpnt*>(m_pUnk20);
        if (m_unkC4 != 0) impulsion->Impulse(1.0f);  // 0x0024bce0
        static_cast<CKImpulsionCpnt*>(m_pUnk20)->Update(clock->m_afDeltaTime[0]);  // 0x0024bd40
        const float value = static_cast<CKImpulsionCpnt*>(m_pUnk20)->m_unk24;
        float level;
        if (!(value >= 1.0f)) {  // cror eq|gt
            level = value * 0.8f;  // TOC +0x6014
            m_fUnk84 = level;
        } else {
            level = 1.0f;
            m_fUnk84 = 1.0f;
        }
        ScaleFlameParticles(level);
        TorchSounds(this)->GetSound(0)->SetVolume(m_fUnk84);  // 0x00110f10 (no null test)
        const float now = static_cast<CKImpulsionCpnt*>(m_pUnk20)->m_unk24;
        if (now >= 1.0f) {
            StartFlameFx();
            AddHotspotPointsToFx();
            if (m_pUnk90 != nullptr) {
                TorchStartEmitting(m_pUnk90);
                TorchShow(m_pUnk90, true);
            }
            QueueTriggerSignals(&m_unkAC);  // 0x00236338 (the torch as sender)
            return 3;
        }
        if (!(now <= 0.0f)) return other;  // cror eq|lt
        TorchReleaseParticles(this);
        return 0;
    }
    if (phase != 1) return other;
    m_unkC5 = 0;
    m_fUnk38 = 0.0f;
    m_fUnk84 = 0.0f;
    CKImpulsionCpnt* impulsion = static_cast<CKImpulsionCpnt*>(m_pUnk20);
    impulsion->m_unk04[1] = 0.0f;
    static_cast<CKImpulsionCpnt*>(m_pUnk20)->m_unk04[0] = 1.0f;
    static_cast<CKImpulsionCpnt*>(m_pUnk20)->m_unk24 = 0.0f;
    static_cast<CKImpulsionCpnt*>(m_pUnk20)->Impulse(1.0f);
    TorchSounds(this)->GetSound(0)->SetLoop(1);                    // 0x00110fd0
    TorchSounds(this)->GetSound(0)->SetPosition(TorchNodePos(this));  // 0x00110fa0
    TorchSounds(this)->GetSound(0)->SetVolume(0.0f);
    TorchSounds(this)->GetSound(0)->Play(0.0f);  // 0x00111230
    return other;
}

// 0x00497c98 CKHkS08FlamingTorch_UpdateFlameParticles_maybe: the lean: while +0xd4 counts down (from 1), the angle is
// 0.9 cos((1 - left) * 3pi/4) (halved below 0); the flame particles (+0x50) turned by it from the up axis towards the lean
// direction (+0xc8, normalised; the Z axis when it is null): at = sin * Y + cos * lean, up = cos * Y + sin * lean.
void CKHkS08FlamingTorch::UpdateFlameParticles(IKTime* clock) {
    float angle = 0.0f;  // f31
    if (!(m_fUnkD4 <= 0.0f)) {  // ble (a NaN counts down)
        const float left = m_fUnkD4 - clock->m_afDeltaTime[0];
        const float x = (1.0f - left) * 2.3561945f;  // TOC +0x6044 (0x4016cbe4)
        m_fUnkD4 = left;
        angle = TorchCos(x) * 0.9f;  // TOC +0x6048 (0x3f666666)
        if (angle < 0.0f) angle = angle * 0.5f;  // TOC +0x5fcc
    }
    if (m_pFx50 == nullptr) return;
    if (m_vUnkC8.x == kTorchNull.x && m_vUnkC8.y == kTorchNull.y && m_vUnkC8.z == kTorchNull.z) {
        m_vUnkC8 = kTorchAxisZ;
    } else {
        const float x = m_vUnkC8.x;
        const float y = m_vUnkC8.y;
        const float z = m_vUnkC8.z;
        const float length = TorchSqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            m_vUnkC8.z = inverse * m_vUnkC8.z;
            m_vUnkC8.x = inverse * m_vUnkC8.x;
            m_vUnkC8.y = inverse * m_vUnkC8.y;
        }
    }
    const CVector3 axis = kTorchAxisY;
    const float c1 = TorchCos(angle);
    CVector3 up = {c1 * axis.x, c1 * axis.y, c1 * axis.z};
    const float s1 = TorchSin(angle);
    up.x = ppc::fmadds(s1, m_vUnkC8.x, up.x);
    up.y = ppc::fmadds(s1, m_vUnkC8.y, up.y);
    up.z = ppc::fmadds(s1, m_vUnkC8.z, up.z);
    const float s2 = TorchSin(angle);
    CVector3 at = {s2 * axis.x, s2 * axis.y, s2 * axis.z};
    const float c2 = TorchCos(angle);
    at.z = ppc::fmadds(c2, m_vUnkC8.z, at.z);
    at.x = ppc::fmadds(c2, m_vUnkC8.x, at.x);
    at.y = ppc::fmadds(c2, m_vUnkC8.y, at.y);
    SetOwnedParticleEffectTransform(static_cast<CKParticlesEffectNodeFx*>(static_cast<IKSerializable*>(m_pFx50)), &at,
                                    &up, this);  // 0x001cdc08
}

// 0x00498350 CKHkS08FlamingTorch_StartFlameParticles_maybe: without running particles, the particle effect data (+0x4c)
// takes the lifetime +0x3c and the hot spot +0x94, its effect is acquired into +0x50 (the inlined CKSrvFx::AcquireFx)
// and its nodes scaled by `t` (ScaleFlameParticles inlined).
void CKHkS08FlamingTorch::StartFlameParticles(float t) {
    if (m_pFx50 != nullptr) return;
    CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_pUnk4C);
    std::memcpy(&data->m_unk0c, &m_fUnk3C, 4);  // lfs / stfs
    data->m_pAttachOwner = nullptr;
    data->m_pAttachHotSpot = m_pUnk94;
    m_pFx50 = TorchFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk4C), this);
    if (m_pFx50 == nullptr) return;
    ScaleFlameParticles(t);
}

// state 3 0x004987a0 CKHkS08FlamingTorch_State3_Lit_maybe: burning (update only): the flame loop stopped if playing, the
// particle node +0x90 emitting and shown, the flame particles started at full size if needed; a hit sets the lean (unless
// an element 1 hit); an element 1 or 7 hit stops +0x90 and puts the torch out (state 2).
uint8_t CKHkS08FlamingTorch::State3(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase != 0) return other;
    TorchStopLoopIfPlaying(this);
    if (m_pUnk90 != nullptr) {
        TorchStartEmitting(m_pUnk90);
        TorchShow(m_pUnk90, true);
    }
    if (m_pFx50 == nullptr) StartFlameParticles(1.0f);
    if (m_unkC7 != 0 && m_unkC5 == 0) m_fUnkD4 = 1.0f;
    if (m_unkC5 == 0 && m_unkC6 == 0) return other;
    if (m_pUnk90 == nullptr) return 2;
    TorchStopEmitting(m_pUnk90);
    return 2;
}

// state 0 0x00498988 CKHkS08FlamingTorch_State0_Unlit_maybe: unlit; an element 0 hit starts the flame particles at size
// 0, switches the collision mesh on and goes to state 1. Entering clears +0xc4.
uint8_t CKHkS08FlamingTorch::State0(IKTime* /*clock*/, int32_t phase, uint8_t other) {
    if (phase == 0) {
        if (m_unkC4 == 0) return other;
        StartFlameParticles(0.0f);
        static_cast<ICollisionMesh*>(m_pUnkC0)->SetActive(1);  // 0x001a6b70
        return 1;
    }
    if (phase == 1) m_unkC4 = 0;
    return other;
}

// 0x00498a20 CKHkS08FlamingTorch_TriggerHotSpotExplosionFx_maybe: an explosion of +0x88 (the inlined CKSrvFx::AcquireFx)
// set off at the hot spot +0x94 and let go.
void CKHkS08FlamingTorch::TriggerHotSpotExplosionFx() {
    IKFx* fx = TorchFx()->AcquireFx(static_cast<IKFxData*>(m_pUnk88), this);
    if (fx == nullptr) return;
    TorchTriggerAtHotSpot(this, fx);
}

// state 2 0x00498ce0 CKHkS08FlamingTorch_State2: going out: the impulsion +0x24 (kicked by element 1 / 7 hits) lowers the
// flame (1 - its value); a hit without element 1 sets the lean; once it reaches 1 the particles let go, the loop stops,
// the "out" trigger (+0xb4), the hot spot explosion, the collision mesh off, state 0; when it dies down to 0 the node
// +0x90 emits again and the torch is lit (state 3).
uint8_t CKHkS08FlamingTorch::State2(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 0) {
        if (m_unkC5 != 0 || m_unkC6 != 0) static_cast<CKImpulsionCpnt*>(m_pUnk24)->Impulse(1.0f);
        if (m_unkC7 != 0 && m_unkC5 == 0) m_fUnkD4 = 1.0f;
        static_cast<CKImpulsionCpnt*>(m_pUnk24)->Update(clock->m_afDeltaTime[0]);
        m_fUnk84 = 1.0f - static_cast<CKImpulsionCpnt*>(m_pUnk24)->m_unk24;
        TorchSounds(this)->GetSound(0)->SetVolume(m_fUnk84);
        ScaleFlameParticles(m_fUnk84);
        const float value = static_cast<CKImpulsionCpnt*>(m_pUnk24)->m_unk24;
        if (value >= 1.0f) {  // cror eq|gt
            TorchReleaseParticles(this);
            Sound_Stop(TorchSounds(this)->GetSound(0), 1);
            QueueTriggerSignals(&m_unkB4);
            TriggerHotSpotExplosionFx();
            static_cast<ICollisionMesh*>(m_pUnkC0)->SetActive(0);
            return 0;
        }
        if (!(value <= 0.0f)) return other;  // cror eq|lt
        if (m_pUnk90 != nullptr) {
            TorchStartEmitting(m_pUnk90);  // the speed adjustment from a float 0 (stfs)
            TorchShow(m_pUnk90, true);
        }
        return 3;
    }
    if (phase != 1) return other;
    m_unk40 = 0;
    static_cast<CKImpulsionCpnt*>(m_pUnk24)->m_unk04[1] = 0.0f;  // stw 0
    static_cast<CKImpulsionCpnt*>(m_pUnk24)->m_unk04[0] = 1.0f;
    static_cast<CKImpulsionCpnt*>(m_pUnk24)->m_unk24 = 0.0f;  // stw 0
    static_cast<CKImpulsionCpnt*>(m_pUnk24)->Impulse(1.0f);
    return other;
}

// vt+0x30 0x00499bc0 CKHkS08FlamingTorch_PostLoad: the actor base's; (type 0) the state table (states 0..3), no
// particles, four states, state 0 entered (from none); the trigger starters' PostLoad; the cylinder owned by the torch
// and sized from +0x34 (radius) and +0x30 (height).
int32_t CKHkS08FlamingTorch::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);  // 0x003f6e70
    if (type == 0) {
        m_aStateTable[0] = 0x00bc4bd0u;  // state 0 (TOC +0x6070)
        m_aStateTable[2] = 0x00bc4b00u;  // state 1 (TOC +0x6074)
        m_aStateTable[4] = 0x00bc4be0u;  // state 2 (TOC +0x6078)
        m_aStateTable[6] = 0x00bc4bc8u;  // state 3 (TOC +0x607c)
        m_pFx50 = nullptr;
        m_aStateTable[7] = 0;
        m_aStateTable[1] = 0;
        m_aStateTable[3] = 0;
        m_aStateTable[5] = 0;
        m_unkE9 = 4;
        m_unkE8 = 0;
        m_pStateTable = m_aStateTable;
        CallState(0, nullptr, 1, 0xff);
    }
    m_unkB4.PostLoad(type);  // 0x00236330
    m_unkAC.PostLoad(type);
    CKAACylinder* cylinder = static_cast<CKAACylinder*>(m_pUnk28);
    cylinder->m_ui16PropertiesFlags = 0;
    cylinder->m_ui8OwnerType = 0;
    static_cast<CKAACylinder*>(m_pUnk28)->m_ui8OwnerType = 1;
    static_cast<CKAACylinder*>(m_pUnk28)->m_pOwner = this;
    cylinder = static_cast<CKAACylinder*>(m_pUnk28);
    cylinder->m_ba8Infos = static_cast<uint8_t>((cylinder->m_ba8Infos & 0x7fu) | 0x80u);
    const float radius = m_fUnk34;
    cylinder->m_fCylinderRadius = radius;
    cylinder->m_fRadius =
        TorchSqrtf(ppc::fmadds(cylinder->m_fCylinderHalfHeight, cylinder->m_fCylinderHalfHeight, radius * radius));
    const float half = m_fUnk30 * 0.5f;  // TOC +0x5fcc
    cylinder->m_fCylinderHalfHeight = half;
    cylinder->m_fRadius = TorchSqrtf(ppc::fmadds(half, half, cylinder->m_fCylinderRadius * cylinder->m_fCylinderRadius));
    return 1;
}

// vt+0x50 0x00499db0 CKHkS08FlamingTorch_Start: the actor base's (empty), the preset state (+0xdc: lit, state 3, else
// unlit, state 0), the hit flags and the flame level cleared, the lean direction the Z axis.
void CKHkS08FlamingTorch::Start() {
    CKHkActorBase::Start();  // 0x003f6e48
    ChangeState(m_unkDB[1] == 0 ? 0 : 3);
    m_unkC6 = 0;
    m_unkC4 = 0;
    m_unkC5 = 0;
    m_fUnk84 = 0.0f;  // stw 0
    m_vUnkC8 = kTorchAxisZ;
}

// vt+0x7c 0x0049a008 CKHkS08FlamingTorch_Update: the actor base's, the element hits, the state machine, the flame
// particles' lean.
void CKHkS08FlamingTorch::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);  // 0x003f6e68
    DetectElementHits();
    const uint8_t state = m_unkE8;
    if (state != 0xff) {
        const uint8_t next = CallState(state, clock, 0, state);
        const uint8_t current = m_unkE8;
        if (next != current) {
            if (current != 0xff) CallState(current, clock, 2, next);
            m_unkE8 = next;
            if (next != 0xff) CallState(next, clock, 1, current);
        }
    }
    UpdateFlameParticles(clock);
}

// vt+0xcc 0x0049a240 CKHkS08FlamingTorch_vfCC: enabled (+0xdb): back to state 0; disabled: the particles let go, the loop
// stopped (GetSound_2), the current state left towards none and no state.
void CKHkS08FlamingTorch::SetEnabled(int32_t enabled) {
    m_unkDB[0] = static_cast<uint8_t>(enabled);
    if (enabled != 0) {
        ChangeState(0);
        return;
    }
    TorchReleaseParticles(this);
    CKSound* sound = TorchSounds(this)->GetSound2(0);  // 0x00112bd8
    if (sound != nullptr) Sound_Stop(sound, 0);
    if (m_unkE8 != 0xff) CallState(m_unkE8, nullptr, 2, 0xff);
    m_unkE8 = 0xff;
}

// vt+0x1c 0x0049a4b8 CKHkS08FlamingTorch_MessageProc: the actor messages first (0x90c..0x90f also reach vt+0xd4 there),
// then: 0x90c / 0x996 light the torch with the flame FX, 0x90e lights it without; 0x90d / 0x997 put it out with the hot
// spot explosion, 0x90f without. Lighting: the flame particles at full size, the node +0x90 emitting and shown (unless
// it emits), the loop started (looping, at the node, unless playing) at full volume, state 3, the "lit" trigger (+0xac).
// Putting out: the particles let go, +0x90 stopped and hidden (if it emits), the loop stopped, state 0, the "out"
// trigger (+0xb4). 0 when handled; the answers merged with the actor base's.
int32_t CKHkS08FlamingTorch::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x90e || message == 0x90c || message == 0x996) {
        StartFlameParticles(1.0f);
        ScaleFlameParticles(1.0f);
        if (message != 0x90e) StartFlameFx();
        if (m_pUnk90 != nullptr && (TorchParticles(m_pUnk90)->m_sgProperties & 0x400u) == 0) {
            TorchStartEmitting(m_pUnk90);
            TorchShow(m_pUnk90, true);
        }
        CKSound* sound = TorchSounds(this)->GetSound(0);
        if (sound != nullptr) {
            if (sound->CountInstances() == 0) {
                sound->SetLoop(1);
                sound->SetPosition(TorchNodePos(this));
                sound->Play(0.0f);  // TOC +0x5fd0
            }
            sound->SetVolume(1.0f);
        }
        ChangeState(3);
        QueueTriggerSignals(&m_unkAC);
        own = 0;
    } else if (message == 0x90d || message == 0x997 || message == 0x90f) {
        TorchReleaseParticles(this);
        if (message != 0x90f) TriggerHotSpotExplosionFx();
        if (m_pUnk90 != nullptr && (TorchParticles(m_pUnk90)->m_sgProperties & 0x400u) != 0) {
            TorchStopEmitting(m_pUnk90);
            TorchShow(m_pUnk90, false);
        }
        TorchStopLoopIfPlaying(this);
        ChangeState(0);
        QueueTriggerSignals(&m_unkB4);
        own = 0;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// vt+0x54 0x0049ad80 CKHkS08FlamingTorch_Restart: unless the actor's +0x0c bit 2, the particles let go, the node +0x90
// set as the preset says (+0xdc: emitting and shown; else stopped and hidden) and the loop stopped if playing; then the
// preset's state (3 or 0) and the hit flags and the lean cleared.
void CKHkS08FlamingTorch::Restart() {
    const bool lit = m_unkDB[1] != 0;
    if ((m_bitArray & 4u) == 0) {
        TorchReleaseParticles(this);
        if (m_pUnk90 != nullptr) {
            if (lit) {
                TorchStartEmitting(m_pUnk90);
                TorchShow(m_pUnk90, true);
            } else {
                TorchStopEmitting(m_pUnk90);
                TorchShow(m_pUnk90, false);
            }
        }
        TorchStopLoopIfPlaying(this);
    }
    ChangeState(lit ? 3 : 0);
    m_unkC6 = 0;
    m_fUnkD4 = 0.0f;  // stw 0
    m_unkC4 = 0;
    m_unkC5 = 0;
}

// vt+0xa0 0x004975c8 CKHkS08FlamingTorch_OnActivate: the actor base's; the particle node +0x8c emitting; the cylinder
// switched on; the node +0x90 hung under the hot spot +0x94 (both needed), stopped and hidden; the collision mesh off; the
// cylinder hung under the torch's node; the lean over.
void CKHkS08FlamingTorch::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    if (m_pUnk8C != nullptr) TorchStartEmitting(m_pUnk8C);
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->EnableVolume(static_cast<IKBoundingVolume*>(m_pUnk28));  // 0x00192090
    if (m_pUnk94 != nullptr && m_pUnk90 != nullptr) {
        CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pUnk90);
        if (leaf->m_pParent != nullptr) leaf->m_pParent->RemoveChild(leaf);  // vt+0x78
        static_cast<CSGHotSpot*>(m_pUnk94)->AttachVolume(static_cast<CSGLeaf*>(m_pUnk90));  // 0x000ce2b8
        TorchStopEmitting(m_pUnk90);
        TorchShow(m_pUnk90, false);
    }
    static_cast<ICollisionMesh*>(m_pUnkC0)->SetActive(0);
    IKBoundingVolume* cylinder = static_cast<IKBoundingVolume*>(m_pUnk28);
    if (cylinder->m_pParent != nullptr) {
        cylinder->m_pParent->RemoveChild(cylinder);  // vt+0x78
        cylinder = static_cast<IKBoundingVolume*>(m_pUnk28);
    }
    static_cast<CSGBranch*>(m_pKGLObject)->AddChild(cylinder);  // vt+0x70
    m_fUnkD4 = 0.0f;  // stw 0
}

// vt+0xa4 0x004977a0 CKHkS08FlamingTorch_OnDeactivate: the actor base's; the node +0x8c stopped; the cylinder switched
// off and moved under sector 0's root; the particles let go; the node +0x90 stopped and hidden if it emits.
void CKHkS08FlamingTorch::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    if (m_pUnk8C != nullptr) TorchStopEmitting(m_pUnk8C);
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->DisableVolume(static_cast<IKBoundingVolume*>(m_pUnk28));  // 0x001920e8
    IKBoundingVolume* cylinder = static_cast<IKBoundingVolume*>(m_pUnk28);
    if (cylinder->m_pParent != nullptr) {
        cylinder->m_pParent->RemoveChild(cylinder);  // vt+0x78
        cylinder = static_cast<IKBoundingVolume*>(m_pUnk28);
    }
    static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[0])->m_pSectorRoot->AddChild(cylinder);  // vt+0x70
    TorchReleaseParticles(this);
    if (m_pUnk90 != nullptr && (TorchParticles(m_pUnk90)->m_sgProperties & 0x400u) != 0) {
        TorchStopEmitting(m_pUnk90);
        TorchShow(m_pUnk90, false);
    }
}
