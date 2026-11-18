// CKHkMovableCharacter.cpp - reconstructed original translation unit 0x59cb80-0x5a7d20 (GAME_TOC2, main_toc2), 66 functions, 64 live.
// Primary owner: CKHkMovableCharacter (not a registered class)
// Other owners: RegisterCKHkMovableCharacterClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x59cb80  CKHkMovableCharacter_Destroy  (DOTD_DECLARE_FACTORIES)
//   [x] 0x59cbd0  CKHkMovableCharacter_vfB4  (empty: IKHook's KGLObjectAttached)
//   [x] 0x59cbd8  CKHkMovableCharacter_ResetRuntime
//   [x] 0x59cc50  CKHkMovableCharacter_vf70  (Pause, empty: IKHook's)
//   [x] 0x59cc58  CKHkMovableCharacter_vf78  (Resume, empty: IKHook's)
//   [x] 0x59cc60  CKHkMovableCharacter_PushTargetInsideBounds_maybe  (PushTargetInsideBounds)
//   [ ] 0x59d008  FUN_0059d008  [dead]
//   [ ] 0x59d030  RegisterCKHkMovableCharacterClass
//   [ ] 0x59d0a8  _GLOBAL__I_59d0a8
//   [ ] 0x59d0b8  CKHkMovableCharacter_UpdateShadowFade_maybe  [dead: no pointer to its descriptor 0xbecc68, no call]
//   [ ] 0x59d270  CKHkMovableCharacter_ApplySpin_maybe  [dead: no pointer to its descriptor 0xbecc70, no call]
//   [x] 0x59d328  CKHkMovableCharacter_UpdateMoveSound_maybe  (UpdateMoveSound, wired in Update)
//   [x] 0x59d490  CKHkMovableCharacter_UpdateLocomotionAnim_maybe  (UpdateLocomotionAnim, wired in Update)
//   [ ] 0x59d738  CKHkMovableCharacter_SnapToGround_maybe  [dead: no pointer to its descriptor 0xbecc88, no call]
//   [x] 0x59d870  CKHkMovableCharacter_ProcessHitContacts_maybe
//   [x] 0x59dd60  CKHkMovableCharacter_OnLevelExit_maybe
//   [ ] 0x59dd90  CKHkMovableCharacter_Save
//   [x] 0x59ddb8  CKHkMovableCharacter_LevelReset  (RecursiveRegistration: IKHook's (inherited), then 1)
//   [x] 0x59dde0  CKHkMovableCharacter_DirectionToYaw_maybe  (DirectionToYaw)
//   [x] 0x59de98  CKHkMovableCharacter_DestroyArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x59df38  CKHkMovableCharacter_GetComponentByKey_maybe  (GetComponent)
//   [x] 0x59dfe8  CKHkMovableCharacter_ClearReferences  (Destroy, header)
//   [x] 0x59dff8  CKHkMovableCharacter_vf40  (GetInfo)
//   [x] 0x59e050  CKHkMovableCharacter_vf38
//   [x] 0x59e060  CKHkMovableCharacter_vf3C  (SetGameState)
//   [x] 0x59e080  CKHkMovableCharacter_Create
//   [x] 0x59e1e0  CKHkMovableCharacter_InitMovementFields_maybe
//   [ ] 0x59e488  CKHkMovableCharacter_PostLoadInitMovement_maybe  [dead]
//   [x] 0x59e4d8  CKHkMovableCharacter_PostLoad
//   [x] 0x59e5a0  CKHkMovableCharacter_CreateArray
//   [x] 0x59e7a8  CKHkMovableCharacter_HandleMessage
//   [x] 0x59ed48  CKHkMovableCharacter_UpdateFade_maybe
//   [x] 0x59efa8  CKHkMovableCharacter_UpdateGroundContact_maybe  (UpdateGroundContact, wired in Update)
//   [x] 0x59f160  CKHkMovableCharacter_ProbeGround_maybe  (ProbeGround)
//   [x] 0x59f338  CKHkMovableCharacter_SetUniformScale_maybe
//   [x] 0x59f5c8  CKHkMovableCharacter_UpdateLookAtNearbyEntity_maybe
//   [x] 0x59f840  CKHkMovableCharacter_UpdateInputIcon_maybe
//   [x] 0x59fb18  CKHkMovableCharacter_UpdateHeroProximity_maybe  (UpdateHeroProximity, wired in Update)
//   [x] 0x59fc60  CKHkMovableCharacter_OnDeactivate
//   [x] 0x59fe48  CKHkMovableCharacter_ApplyPoseToNode_maybe
//   [x] 0x5a02d0  CKHkMovableCharacter_GetHeadingDirection_maybe  (GetHeadingDirection)
//   [x] 0x5a0498  CKHkMovableCharacter_ResetTargetIfOutOfBounds_maybe  (ResetTargetIfOutOfBounds)
//   [x] 0x5a0590  CKHkMovableCharacter_ClampToMoveBounds_maybe  (ClampToMoveBounds)
//   [x] 0x5a0698  CKHkMovableCharacter_CheckNavCellBlocked_maybe  (CheckNavCellBlocked)
//   [x] 0x5a08c0  CKHkMovableCharacter_CheckBlockingCollision_maybe  (CheckBlockingCollision)
//   [x] 0x5a0ab0  CKHkMovableCharacter_ProbeGroundAtTarget_maybe  (ProbeGroundAtTarget)
//   [x] 0x5a0e50  CKHkMovableCharacter_PickRandomWanderTarget_maybe  (PickRandomWanderTarget)
//   [x] 0x5a12c0  CKHkMovableCharacter_InitRuntimeState_maybe
//   [x] 0x5a1860  CKHkMovableCharacter_ReinitRuntime
//   [x] 0x5a1998  CKHkMovableCharacter_OnActivate
//   [x] 0x5a1b28  CKHkMovableCharacter_TurnTowardDirectionFlat_maybe  (TurnTowardDirectionFlat)
//   [x] 0x5a1f18  CKHkMovableCharacter_TurnTowardDirectionAligned_maybe  (TurnTowardDirectionAligned)
//   [x] 0x5a23c0  CKHkMovableCharacter_Update
//   [x] 0x5a30f0  CKHkMovableCharacter_Load
//   [x] 0x5a44e8  CKHkMovableCharacter_UpdateRandomActionTimer_maybe
//   [x] 0x5a4668  CKHkMovableCharacter_State3
//   [x] 0x5a4800  CKHkMovableCharacter_ChooseState_maybe
//   [x] 0x5a4998  CKHkMovableCharacter_MoveAlongPath_maybe  (MoveAlongPath)
//   [x] 0x5a4ef8  CKHkMovableCharacter_State1  (State1)
//   [x] 0x5a5010  CKHkMovableCharacter_State5  (State5)
//   [x] 0x5a5698  CKHkMovableCharacter_State4  (State4)
//   [x] 0x5a5f00  CKHkMovableCharacter_State2  (with the wander walk)
//   [x] 0x5a64e8  CKHkMovableCharacter_State0  (with the walk)
//   [x] 0x5a6ce8  CKHkMovableCharacter_MoveToWithPathfinding_maybe  (MoveToWithPathfinding)
//   [x] 0x5a7080  CKHkMovableCharacter_TurnTowardPoint_maybe  (TurnTowardPoint)
//   [x] 0x5a7458  CKHkMovableCharacter_State6  (State6)
//
//   [ ] 0x9cba10  CKHkMovableCharacter_IsKindOf  [inline]
//   [ ] 0x9cba58  CKHkMovableCharacter_GetClassGroup  [inline]
//   [ ] 0x9cba60  CKHkMovableCharacter_GetClassId  [inline]
//   [x] 0x9cba68  CKHkMovableCharacter_IsVisible_maybe  [inline]  (the GetInfo accessor)
//   [ ] 0x9cba80  CKHkMovableCharacter_DeletingDestructor  [inline]
//   [ ] 0x9cbb20  CKHkMovableCharacter_Destructor  [inline]
#include "k2000/ui/CKHkMovableCharacter.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "k2000/ai/CKPathStepCpnt.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/components/CKSekensLauncherCpnt.h"
#include "k2000/components/CKShadowCpnt.h"
#include "k2000/core/IKInfo.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "Renderware/rtanim/RtAnim.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CKSrvShadow.h"
#include "k2000/services/KBase201.h"
#include "k2000/components/CKBonusData.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/system/IKTime.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/logic/ai/CKFlaggedPath.h"
#include "k2000/logic/fx/CKInputIconNodeFx.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/misc/NavGrid.h"
#include "k2000/services/CollisionDatas.h"

namespace {

// 0x00c50d40 / 0x00c50d64: the shared Y axis and the null vector (filled by static initialisers in the original).
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

// 0x00010690 Math_Sqrtf: the double square root of the float argument, rounded to float.
float MathSqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }

// rand() & 0xffff over 65535 (fcfid, frsp, fdivs by the TOC float 65535.0f).
float RandUnit() { return static_cast<float>(static_cast<uint16_t>(Rand_Int())) / 65535.0f; }

bool SignBitSet(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}
// The game's inlined sine / cosine: the octant polynomials for a non-negative argument, the library sinf / cosf
// (0x9a1390 / 0x9a11d8) for a negative one (the sine's sign flipped back).
float GameSinf(float x) { return SignBitSet(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }
float GameCosf(float x) { return SignBitSet(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }

CSGMovable* NodeOf(const CKHkMovableCharacter* hook) { return static_cast<CSGMovable*>(hook->m_pKGLObject); }
CSGLeaf* LeafOf(const CKHkMovableCharacter* hook) { return static_cast<CSGLeaf*>(hook->m_pKGLObject); }

// The node's position written into its modelling matrix (the identity flag cleared, the frame marked dirty), as the
// original's inlined CSGMovable position set does.
void SetNodePosition(CSGMovable* node, float x, float y, float z) {
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = z;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}

// The sound `index` of the dictionary stopped when it exists (GetSound twice, as the original).
void StopSound(CKSoundDictionaryID* sounds, uint32_t index) {
    if (CKSoundDictionaryID_GetSound(sounds, index) != nullptr) Sound_Stop(CKSoundDictionaryID_GetSound(sounds, index), 0);
}

// The hero group's focused hero node (0x002ca128 CKGrpS08Hero_GetFocusedHeroNode_maybe): +0x66 the index (-1 none).
CSGMovable* FocusedHeroNode(IKGrpHero* group) {
    const int8_t index = static_cast<int8_t>(group->m_unk66);
    if (index == -1) return nullptr;
    return static_cast<CSGMovable*>(group->m_apUnk44[index]);
}
IKGrpHero* HeroGroup() { return static_cast<IKGrpHero*>(g_pEngine->m_gameManager->m_unk04[1]); }

// The distance from the node's LTM position to the focused hero node's (fmuls / fmadds as the original).
float DistanceToNode(const CSGMovable* node, const CSGMovable* hero) {
    const RwV3d& h = FrameLtm(hero->m_pRwFrame)->pos;  // RwFrame +0x80
    const RwV3d& p = FrameLtm(node->m_pRwFrame)->pos;
    const float dy = h.y - p.y;
    const float dx = h.x - p.x;
    const float dz = h.z - p.z;
    return MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
}

// The geometries of the node made opaque (alpha 0xff); a geometry whose blend flag (bit 11) was set has it cleared
// and its properties updated (vt+0x60).
void SetGeometriesOpaque(CGeometry* geometry) {
    for (; geometry != nullptr; geometry = geometry->m_pNext) {
        geometry->m_cGeometryColor[3] = 0xff;
        const uint32_t properties = geometry->m_BitProperties;
        if ((properties & 0x800u) == 0) continue;
        geometry->m_BitProperties = properties & 0xfffff7ffu;
        geometry->UpdateProperties();
    }
}

// DOTD: the state handlers by descriptor (k2000/core/Ps3MemberFn.h; the table PostLoad points +0x2c0 at, filled by
// ResetRuntime).
Ps3MemberFnEntry<CKHkMovableCharacter::StateFn> g_movableStates[] = {
    {0x00bed370u, &CKHkMovableCharacter::State0, "CKHkMovableCharacter_State0 0x5a64e8", false},
    {0x00bed2c0u, &CKHkMovableCharacter::State1, "CKHkMovableCharacter_State1 0x5a4ef8", false},
    {0x00bed368u, &CKHkMovableCharacter::State2, "CKHkMovableCharacter_State2 0x5a5f00", false},
    {0x00bed228u, &CKHkMovableCharacter::State3, "CKHkMovableCharacter_State3 0x5a4668", false},
    {0x00bed360u, &CKHkMovableCharacter::State4, "CKHkMovableCharacter_State4 0x5a5698", false},
    {0x00bed358u, &CKHkMovableCharacter::State5, "CKHkMovableCharacter_State5 0x5a5010", false},
    {0x00bed388u, &CKHkMovableCharacter::State6, "CKHkMovableCharacter_State6 0x5a7458", false},
};

// The shadow ground (+0xd4) from the ground contact (inlined in ProbeGround, ProbeGroundAtTarget and
// MoveToWithPathfinding, as in UpdateGroundContact): its world point, normal and height, +0xf0 bit 4 from the ground's
// engine flag bit 6.
void TakeShadowGround(CKHkMovableCharacter* hook) {
    GroundContact_GetWorldPoint(&hook->m_GContactInOut, &hook->m_shadowPos);    // 0x001a70e0
    GroundContact_GetWorldNormal(&hook->m_GContactInOut, &hook->m_shadowNormal);  // 0x001a71d8
    std::memcpy(&hook->m_unkEC, &hook->m_GContactInOut.m_fdH, sizeof hook->m_unkEC);
    if (((static_cast<const ICollisionMesh*>(hook->m_GContactInOut.m_pGround)->m_ba16EngineFlags >> 6) & 1u) != 0) {
        hook->m_unkF0 = static_cast<uint8_t>(hook->m_unkF0 | 0x10u);
        return;
    }
    if ((hook->m_unkF0 & 0x10u) != 0) hook->m_unkF0 = static_cast<uint8_t>(hook->m_unkF0 ^ 0x10u);
}

// The shadow caster unregistered when the shadow is on, there is a shadow component and the caster is registered.
void UnregisterShadow(CKHkMovableCharacter* hook) {
    if ((hook->m_unk68 & 0x800u) != 0 && hook->m_unk290 != nullptr && hook->m_unkF1 != 0) {
        static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
            ->UnregisterCaster(reinterpret_cast<CKShadowGround*>(&hook->m_shadowPos), hook->m_unk290);
    }
}

CVector3 ToVector(const RwV3d& v) { return {v.x, v.y, v.z}; }
const CVector3* AsVector(const RwV3d* v) { return reinterpret_cast<const CVector3*>(v); }

// The node's modelling position copied into `out` (z, x, y as the original's loads).
void CopyNodePosition(const CKHkMovableCharacter* hook, CVector3* out) {
    const RwV3d& p = NodeOf(hook)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
    out->z = p.z;
    out->x = p.x;
    out->y = p.y;
}

// The length of v (fmuls y, fmadds x, fmadds z) and v normalised by it when it is not 0 (z, x, y).
float NormaliseYxz(CVector3* v) {
    const float length = MathSqrtf(ppc::fmadds(v->z, v->z, ppc::fmadds(v->x, v->x, v->y * v->y)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        v->z = v->z * inverse;
        v->x = v->x * inverse;
        v->y = v->y * inverse;
    }
    return length;
}

// The original's sign of a float for the "passed the target" tests (crnor / mfocrf): -1 below 0, else 1 (NaN 1).
int32_t SignOf(float x) { return x < 0.0f ? -1 : 1; }

// The bounds test the wanderers share (inlined): outside +0x278..+0x284 on x or z.
bool OutsideMoveBounds(const CKHkMovableCharacter* hook, float x, float z) {
    return hook->m_unk278.x > x || hook->m_unk284.x < x || hook->m_unk278.z > z || hook->m_unk284.z < z;
}

// The heading's cosine and sine of 0.1 rad (the inlined polynomials on a positive constant: 0x3f7eb897, 0x3dcc7577).
float FromBits(uint32_t bits) {
    float value;
    std::memcpy(&value, &bits, 4);
    return value;
}

}  // namespace

// Inlined in 0x0059e080 CKHkMovableCharacter_Create: the ground-contact defaults, +0x7c = 0 (TOC2 -0x6abc,
// 0.0f), the embedded CKPathFindingCpnt's constructor, an empty reference vector of capacity 1 and the two
// bytes +0x2c4/+0x2c5 = 0xff.
CKHkMovableCharacter::CKHkMovableCharacter() {
    m_unk7c[0] = 0.0f;
    m_unk7c[2] = 0.0f;
    m_unk7c[1] = 0.0f;
    m_unkF0 = 0;
    m_vUnk294.m_ui32NbElt = 1;
    m_vUnk294.m_ui32NbUsedElt = 0;
    m_vUnk294.m_pBlock = nullptr;
    m_unk2c5 = 0xff;
    m_unk2c4 = 0xff;
}

// 0x005a30f0 CKHkMovableCharacter_Load: no serialization-type branch of its own.
int32_t CKHkMovableCharacter::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    ReadU8(file, &m_unk148);
    ReadU32LE(file, &m_unk140);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk14c), 3);  // one Read(0xc), then three swaps
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk158), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk164), 3);
    ReadF32LE(file, &m_unk170);
    ReadU8(file, &m_unk174);
    uint32_t* const params = reinterpret_cast<uint32_t*>(&m_unk178);  // +0x178..+0x1ef, contiguous
    for (uint32_t i = 0; i < 0x1e; ++i) ReadU32LE(file, &params[i]);
    for (uint32_t i = 0; i < 4; ++i) ReadF32LE(file, &m_unk268[i]);
    ReadF32LE(file, &m_unk2ac);
    ReadU32LE(file, &m_unk2bc);
    IKFile_ReadRef(file, &m_unk138);
    IKFile_ReadRef(file, &m_unk13c);
    IKFile_ReadRef(file, &m_unk144);
    IKFile_ReadRef(file, &m_unk290);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk278), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk284), 3);
    uint16_t count = 0;
    ReadU16LE(file, &count);
    if (count == 0) {
        m_vUnk294.m_ui32NbElt = 1;
        m_vUnk294.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKSerializable*))));
    } else {
        m_vUnk294.m_ui32NbElt = count;
        m_vUnk294.m_pBlock = static_cast<IKSerializable**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        if (m_vUnk294.m_ui32NbElt < count) {  // as in the original: cannot happen
            uint32_t capacity = count + 1u;
            if (capacity == 0) capacity = 1;
            m_vUnk294.m_pBlock = static_cast<IKSerializable**>(
                Mem_ReallocAligned16(m_vUnk294.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
            m_vUnk294.m_ui32NbElt = capacity;
        }
        m_vUnk294.m_ui32NbUsedElt = count;
        for (uint32_t i = 0; i < count; ++i) IKFile_ReadObjectRef(file, &m_vUnk294.m_pBlock[i]);
    }
    IKFile_ReadRef(file, &m_unk2a0[0]);
    IKFile_ReadRef(file, &m_unk2a0[1]);
    IKFile_ReadRef(file, &m_unk2a0[2]);
    m_unk300.Load(file, type);
    m_unk308.Load(file, type);
    m_unk310.Load(file, type);
    m_PFCpnt.CKPathFindingCpnt::Load(file, type);
    IKFile_ReadRef(file, &m_unk2b0[0]);
    IKFile_ReadRef(file, &m_unk2b0[1]);
    IKFile_ReadRef(file, &m_unk2b0[2]);
    return 1;
}

// 0x0059e4d8 CKHkMovableCharacter_PostLoad: IKLife's, the three trigger starters' (TriggerEventList_PostLoad_maybe
// 0x236330: returns at once), then for the level type the movement fields and the state engine (the table at +0x2c8,
// no state, seven states).
int32_t CKHkMovableCharacter::PostLoad(int32_t type) {
    PostLoadLife(type);
    if (type == K_LEVEL_PLATEFORMS) {
        InitMovementFields();
        m_pStateTable = &m_unk2c8[0];
        m_unk2c4 = 0xff;
        m_unk2c5 = 7;
    }
    return 1;
}

// 0x0059e050 CKHkMovableCharacter_vf38 (SetDefaultState): enabled again (+0x130 = 0). The bases' slot is not called.
void CKHkMovableCharacter::SetDefaultState(int32_t /*flag*/) { m_unk130 = 0; }

// 0x0059cbd8 CKHkMovableCharacter_ResetRuntime: bit 9 of the +0x68 word cleared, the seven-state handler table
// at +0x2c8 refilled (pairs: the state's function descriptor and a zero adjustment, the PS3 pointer-to-member
// layout; State6 is stored first at +0x2f8). CallState maps the descriptors to the native handlers.
void CKHkMovableCharacter::Start() {
    m_unk68 &= 0xfffffdffu;
    m_unk2c8[12] = 0x00bed388u;  // State6 (+0x2f8)
    m_unk2c8[13] = 0;
    m_unk2c8[0] = 0x00bed370u;   // State0 (+0x2c8)
    m_unk2c8[2] = 0x00bed2c0u;   // State1 (+0x2d0)
    m_unk2c8[4] = 0x00bed368u;   // State2 (+0x2d8)
    m_unk2c8[6] = 0x00bed228u;   // State3 (+0x2e0)
    m_unk2c8[8] = 0x00bed360u;   // State4 (+0x2e8)
    m_unk2c8[10] = 0x00bed358u;  // State5 (+0x2f0)
    m_unk2c8[1] = 0;
    m_unk2c8[3] = 0;
    m_unk2c8[5] = 0;
    m_unk2c8[7] = 0;
    m_unk2c8[9] = 0;
    m_unk2c8[11] = 0;
}

// 0x005a1860 CKHkMovableCharacter_ReinitRuntime (vt+0x54): unless the life flag bit 2: an enabled character's run-time
// state initialised again (InitRuntimeState(1): its rand draws) and +0x68 bit 11 from the properties' bit 6; a disabled
// one (+0x130) loses its collision volume, gets +0x68 bit 9 and is hidden; then the path request cancelled, +0x68 bits
// 15-16 to 1, 0 and the input icon off.
void CKHkMovableCharacter::Restart() {
    if ((m_bitArray & 4u) != 0) return;
    if (m_unk130 == 0) {
        InitRuntimeState(1);  // 0x005a12c0
        m_unk68 = (m_unk68 & 0xfffff7ffu) | (((m_unk140 >> 6) & 1u) << 11);
    } else {
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->RemoveVolume(static_cast<IKBoundingVolume*>(m_unk144));  // 0x00192bc0
        m_unk68 = (m_unk68 & 0xfffffdffu) | 0x200u;
        CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
        node->m_sgProperties = node->m_sgProperties | 4u;
    }
    m_PFCpnt.CancelPathRequest();  // 0x001e2820
    m_unk68 = (m_unk68 & 0xfffe7fffu) | 0x8000u;
    UpdateInputIcon(0);  // 0x0059f840
}

// The state engine's call of the state `state`: the PS3 table holds the descriptors of CKHkMovableCharacter's pointers
// to member function (the adjustment is 0), mapped to the native handlers; a handler not ported yet leaves the state
// as given (the "other" argument, as the gauge's engine does).
uint8_t CKHkMovableCharacter::CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_movableStates, &m_pStateTable[state * 2u], "CKHkMovableCharacter state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

// 0x0059e1e0 CKHkMovableCharacter_InitMovementFields_maybe: the walk and turn approaches, the path-finding character
// (0x809, 0.5, 0.2, 1) and its validation distance, the ground contact's defaults, the move bounds (shrunk by the
// turn radius when the character wanders), the fade timer, and one rand() draw into +0xf4.
void CKHkMovableCharacter::InitMovementFields() {
    m_pClock = nullptr;
    m_unk68 = 0;
    m_unk24 = 0;
    m_unk25 = 0;
    m_PFCpnt.m_CharacterType.m_bits = 0x809;
    m_PFCpnt.m_CharacterType.m_unk04 = 0.5f;
    m_PFCpnt.m_CharacterType.m_unk08 = 0.2f;   // TOC2 -0x6aac (0x3e4ccccd)
    m_PFCpnt.m_CharacterType.m_unk0c = 1.0f;
    const float half = g_pfGridScale.m_halfCellSize;  // 0x00c40260
    m_PFCpnt.m_fPointValidationDistanceSquared = half <= 0.25f ? half * half : 0.0625f;
    m_unk6c = 0xffff;
    m_unk7c[1] = m_unk17c;
    m_unk7c[0] = m_unk178;
    m_unk7c[2] = 0.0f;
    m_unk94 = kNullVector;
    m_unk88[1] = 2.0f;
    m_unk88[2] = m_unk170;
    m_unk88[0] = m_unk170;
    if (m_unk178 == 0.0f) {
        m_unk65 = 0;
        m_unk64 = 0;
    } else {
        m_unk65 = 1;
        m_unk64 = 1;
    }
    m_GContactIn.m_fObjectHeight = m_unk1e8;
    m_GContactIn.m_fDeltaMax = m_unk1ec;
    m_GContactIn.m_MasksOfGrdForTest[0] = 1;
    m_GContactIn.m_MasksOfGrdForTest[1] = 8;
    m_GContactInOut.m_pGround = nullptr;
    m_GContactInOut.m_eContactStatus = 3;
    m_GContactInOut.m_i32FaceIndex = -1;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_unk74 = 0.0f;
    m_unk70 = nullptr;
    m_unkBC = kNullVector;
    m_unkC8 = kNullVector;
    if (m_unk148 <= 1) {
        const float radius = (m_unk178 * 2.356194496f) / m_unk180;  // TOC2 -0x6aec (0x4016cbe4, 3 pi / 4)
        m_unkA0 = radius;
        m_unkA4.y = m_unk278.y;
        m_unkA4.x = radius + m_unk278.x;
        m_unkA4.z = m_unk278.z + radius;
        m_unkB0.y = m_unk284.y;
        m_unkB0.x = m_unk284.x - radius;
        m_unkB0.z = m_unk284.z - radius;
    } else {
        m_unkA4 = kNullVector;
        m_unkB0 = kNullVector;
    }
    const float unit = RandUnit();
    m_unkF8 = 0.0f;
    m_unkF4 = unit;
}

// 0x005a1998 CKHkMovableCharacter_OnActivate (vt+0xa0, the sector is valid again): a disabled character (+0x130)
// only stays hidden; any other is shown, takes its shadow's alpha and its runtime state (InitRuntimeState), the
// shadow flag (+0x68 bit 11) from +0x140 bit 6, the shadow ground at its position. Either way +0x68 bit 15 is set
// (bit 16 cleared) and the input icon reference dropped.
void CKHkMovableCharacter::VfA0() {
    const uint8_t disabled = m_unk130;
    CSGLeaf* node = LeafOf(this);
    if (disabled != 0) {
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
        m_unk68 = (m_unk68 & 0xfffe7fffu) | 0x8000u;  // bits 15 and 16 cleared, 15 set
        m_unk134 = nullptr;
        return;
    }
    node->m_sgProperties &= 0xfffffffbu;
    if (m_unk290 != nullptr) m_unk100 = static_cast<CKShadowCpnt*>(m_unk290)->m_ShadowColor[3];
    InitRuntimeState(0);
    m_unk68 = (m_unk68 & 0xfffff7ffu) | (((m_unk140 >> 6) & 1u) << 11);
    m_unkF1 = disabled;
    m_unkEC = 0;
    const RwV3d& position = NodeOf(this)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
    m_shadowPos.x = position.x;
    m_shadowPos.z = position.z;
    m_shadowPos.y = position.y;
    m_shadowNormal.x = kAxisY.x;
    m_shadowNormal.z = kAxisY.z;
    m_shadowNormal.y = kAxisY.y;
    m_unk68 &= 0xfffffbffu;
    m_unk68 = (m_unk68 & 0xfffe7fffu) | 0x8000u;
    m_unk134 = nullptr;
}

// 0x0059fc60 CKHkMovableCharacter_OnDeactivate (vt+0xa4, the sector unloads): the collision volume (+0x144) leaves the
// collision service and its parent (vt+0x78) for the dynamic scene root (vt+0x70); with the shadow on (+0x68 bit 11) and
// its caster registered (+0xf1) the caster is unregistered; the shadow component takes back its full alpha (+0x100);
// the looping (3) and the move (1) sounds stop; the input icon is released.
void CKHkMovableCharacter::VfA4() {
    if (m_unk144 != nullptr) {
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->RemoveVolume(static_cast<IKBoundingVolume*>(m_unk144));
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_unk144);
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
        static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(static_cast<IKBoundingVolume*>(m_unk144));  // vt+0x70
    }
    if ((m_unk68 & 0x800u) != 0 && m_unk290 != nullptr && m_unkF1 != 0) {
        static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
            ->UnregisterCaster(reinterpret_cast<CKShadowGround*>(&m_shadowPos), m_unk290);
    }
    if (m_unk290 != nullptr) static_cast<CKShadowCpnt*>(m_unk290)->m_ShadowColor[3] = m_unk100;
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk13c);
    if (sounds != nullptr) {
        StopSound(sounds, 3);
        StopSound(sounds, 1);
    }
    UpdateInputIcon(0);
}

// 0x005a12c0 CKHkMovableCharacter_InitRuntimeState_maybe: the geometries opaque, the looping sound (+0x140 bit 21),
// the shadow, the start pose and the movement fields, the locomotion animation (+0x140 bit 10; a random start time with
// bit 16), the wander target, the hidden flag (+0x140 bit 11), the collision volume put under the node (unless
// `keepShadow`) and registered, the ground under the start position (+0x140 bit 0), the scale, then state 0.
void CKHkMovableCharacter::InitRuntimeState(uint8_t keepShadow) {
    CNode* node = static_cast<CNode*>(m_pKGLObject);
    SetGeometriesOpaque(static_cast<CGeometry*>(node->m_lGeometryList));
    if ((m_unk140 & 0x200000u) != 0 && m_unk13c != nullptr) {
        CKSound* sound = CKSoundDictionaryID_GetSound(static_cast<CKSoundDictionaryID*>(m_unk13c), 3);
        if (sound != nullptr && sound->CountInstances() == 0) {
            CKSound_SetLoop(sound, 1);
            CKSound_Play(0.0f, sound);
        }
    }
    m_unkFC = 0.0f;
    if (keepShadow != 0 && m_unk290 != nullptr) static_cast<CKShadowCpnt*>(m_unk290)->m_ShadowColor[3] = m_unk100;
    ApplyPoseToNode();
    InitMovementFields();
    if ((m_unk140 & 0x400u) != 0) {
        // The animation of index +0x64 in the dictionary +0x138 (DOTD: the dictionary keeps the words; the original's
        // entry is the animation itself); with +0x140 bit 16 it starts at a random time of its duration.
        const uint32_t word = static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_unk138)->m_apAnimations[m_unk64]);
        RtAnimAnimation* animation = CAnimationManager_GetAnimation(word);
        if (animation != nullptr) {
            float start = 0.0f;
            if ((m_unk140 & 0x10000u) != 0) {
                const float duration = animation->duration;
                start = duration * RandUnit();
            }
            static_cast<CAnimatedNode*>(m_pKGLObject)->PlayAnim(start, animation, 0);  // 0x000c98b8
        }
    }
    if (m_unk148 <= 1) PickRandomWanderTarget(AsVector(&NodeOf(this)->m_pRwFrame->modelling.at));  // 0x005a0e50
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | (((m_unk140 >> 11) & 1u) << 2);
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_unk144);
    if (keepShadow == 0 && volume != nullptr) {
        if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
        static_cast<CSGBranch*>(m_pKGLObject)->AddChild(static_cast<IKBoundingVolume*>(m_unk144));  // vt+0x70
    }
    if ((LeafOf(this)->m_sgProperties & 4u) == 0 &&
        ((m_unk140 & 8u) != 0 || (m_unk140 & 0x10u) != 0 || (m_unk140 & 0x20u) != 0 || (m_unk140 & 0x400000u) != 0)) {
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->AddVolume(static_cast<IKBoundingVolume*>(m_unk144));
    }
    if ((m_unk140 & 1u) != 0) {
        if (m_unk148 <= 1) {
            m_GContactIn.m_fDeltaMax = 0.2f;  // TOC2 -0x6aac
            m_GContactIn.m_fObjectHeight = m_unk158.y - m_unk14c.y;
        } else {
            m_GContactIn.m_fDeltaMax = 1000.0f;  // TOC2 -0x6aa8
            m_GContactIn.m_fObjectHeight = 1000.0f;
        }
        RwFrame* frame = NodeOf(this)->m_pRwFrame;
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
            ->GroundProbePoints(&m_GContactIn, &m_GContactInOut, &frame->modelling.pos.x, 1);
        if (m_GContactInOut.m_eContactStatus <= 1) {
            CVector3 point;
            GroundContact_GetWorldPoint(&m_GContactInOut, &point);
            SetNodePosition(NodeOf(this), point.x, point.y, point.z);
        }
        m_GContactIn.m_fObjectHeight = m_unk1e8;
        m_GContactIn.m_fDeltaMax = m_unk1ec;
    }
    SetUniformScale(m_unk1bc);
    const uint8_t previous = m_unk2c4;
    if (previous != 0xff) CallState(previous, nullptr, 2, 0);
    m_unk2c4 = 0;
    CallState(0, nullptr, 1, previous);
}

// 0x0059fe48 CKHkMovableCharacter_ApplyPoseToNode_maybe: unless the node keeps its pose (+0x174), the start position
// and yaw (at = (-sin, 0, cos), up = Y), or the path's point at the start distance (+0x2a0); then the pose is remembered
// (+0x108 position, +0x114 at, +0x120 up).
void CKHkMovableCharacter::ApplyPoseToNode() {
    if (m_unk174 != 0) return;
    CSGMovable* node = NodeOf(this);
    if (m_unk2a0[0] == nullptr) {
        SetNodePosition(node, m_unk164.x, m_unk164.y, m_unk164.z);
        const float yaw = m_unk170;
        CVector3 at;
        at.x = -GameSinf(yaw);
        at.y = 0.0f;
        at.z = GameCosf(yaw);
        node->SetOrientationFromAtUp(&at, &kAxisY);
    } else {
        if (m_unk170 < 0.0f) m_unk170 = 0.0f;
        const float distance = m_unk170;
        m_unk180 = distance;
        // The path's point and direction at the start distance (0x000c4d88 CKFlaggedPath_SetDistanceAndGetPositionUp_maybe,
        // no up), the node placed there, turned along the direction (up Y) and its three axes scaled by +0x1bc.
        CVector3 point;
        CVector3 direction;
        static_cast<CKFlaggedPath*>(m_unk2a0[0])->SetDistanceAndGetPositionUp(distance, &point, &direction, nullptr);
        SetNodePosition(node, point.x, point.y, point.z);
        node->SetOrientationFromAtUp(&direction, &kAxisY);  // 0x000d0918
        RwFrame* frame = NodeOf(this)->m_pRwFrame;
        const float scale = m_unk1bc;
        RwMatrix& m = frame->modelling;
        m.right.x = scale * m.right.x;
        m.right.y = scale * m.right.y;
        m.right.z = scale * m.right.z;
        m.up.x = scale * m.up.x;
        m.up.y = scale * m.up.y;
        m.up.z = scale * m.up.z;
        m.at.x = scale * m.at.x;
        m.at.z = scale * m.at.z;
        m.at.y = scale * m.at.y;
        m.flags &= 0xfffdfffeu;
        RwFrame_MarkDirty(frame);
    }
    const RwFrame* frame = node->m_pRwFrame;
    m_unk108.x = frame->modelling.pos.x;
    m_unk108.z = frame->modelling.pos.z;
    m_unk108.y = frame->modelling.pos.y;
    m_unk114.x = frame->modelling.at.x;
    m_unk114.z = frame->modelling.at.z;
    m_unk114.y = frame->modelling.at.y;
    m_unk120.x = frame->modelling.up.x;
    m_unk120.z = frame->modelling.up.z;
    m_unk120.y = frame->modelling.up.y;
}

// 0x0059f338 CKHkMovableCharacter_SetUniformScale_maybe: the node's modelling matrix with its three axes normalised and
// scaled by `scale` (stored at +0x1bc), at, right then up, through CSGMovable_SetLocalMatrix_maybe.
void CKHkMovableCharacter::SetUniformScale(float scale) {
    m_unk1bc = scale;
    RwMatrix matrix = NodeOf(this)->m_pRwFrame->modelling;
    const auto normalise = [](RwV3d& v) {
        float y = v.y, x = v.x, z = v.z;
        const float length = MathSqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            z = z * inverse;
            x = x * inverse;
            y = y * inverse;
        }
        v.x = x;
        v.y = y;
        v.z = z;
    };
    RwV3d at = matrix.at;
    normalise(at);
    matrix.flags &= 0xfffdfffcu;
    matrix.at.x = scale * at.x;
    matrix.at.y = scale * at.y;
    matrix.at.z = scale * at.z;
    RwV3d right = matrix.right;
    normalise(right);
    matrix.flags &= 0xfffdfffcu;
    matrix.right.y = scale * right.y;
    matrix.right.x = scale * right.x;
    matrix.right.z = scale * right.z;
    RwV3d up = matrix.up;
    normalise(up);
    matrix.flags &= 0xfffdfffcu;
    matrix.up.z = scale * up.z;
    matrix.up.x = scale * up.x;
    matrix.up.y = scale * up.y;
    NodeOf(this)->SetLocalMatrix(&matrix);
}

// 0x0059ed48 CKHkMovableCharacter_UpdateFade_maybe: while the fade timer (+0xf8) runs, the node is shown and its
// geometries take the fade's alpha (in: up to +0x1b4 over +0x1b0 seconds; out with +0x68 bit 9: down to 0, then the
// node is hidden). Alpha 0xff makes every geometry opaque; otherwise a geometry of an opaque material type (1..6,
// render flag 0x1000) stays opaque and the others blend.
void CKHkMovableCharacter::UpdateFade(IKTime* clock) {
    const float timer = m_unkF8;
    if (!(timer > 0.0f)) return;
    CSGLeaf* node = LeafOf(this);
    CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(m_pKGLObject)->m_lGeometryList);
    m_unkF8 = timer - clock->m_afDeltaTime[0];
    node->m_sgProperties &= 0xfffffffbu;
    uint8_t alpha;
    if ((m_unk68 & 0x200u) == 0) {
        if (m_unkF8 > 0.0f) {
            alpha = static_cast<uint8_t>(ppc::fctiwz((1.0f - m_unkF8 / m_unk1b0) * m_unk1b4));
        } else {
            alpha = static_cast<uint8_t>(ppc::fctiwz(m_unk1b4));
        }
    } else if (m_unkF8 > 0.0f) {
        alpha = static_cast<uint8_t>(ppc::fctiwz((m_unkF8 * m_unk1b4) / m_unk1b0));
    } else {
        alpha = 0;
        LeafOf(this)->m_sgProperties = (LeafOf(this)->m_sgProperties & 0xfffffffbu) | 4u;
    }
    if (geometry == nullptr) return;
    if (alpha == 0xff) {
        SetGeometriesOpaque(geometry);
        return;
    }
    for (; geometry != nullptr; geometry = geometry->m_pNext) {
        uint32_t blend = 1;
        uint8_t value = alpha;
        if ((geometry->m_BitProperties & 0x1000u) != 0) {
            const uint32_t type = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
            if (type > 0 && type <= 6) {
                blend = 0;
                value = 0xff;
            }
        }
        geometry->m_cGeometryColor[3] = value;
        const uint32_t properties = geometry->m_BitProperties;
        if (((properties >> 11) & 1u) != blend) {
            geometry->m_BitProperties = (properties & 0xfffff7ffu) | (blend << 11);
            geometry->UpdateProperties();
        }
    }
}

// 0x0059f840 CKHkMovableCharacter_UpdateInputIcon_maybe: `show` 0 releases the input icon effect (vt+0x58); otherwise
// the effect of the data +0x2b8 is taken from the FX service's pool when there is none and follows the node.
void CKHkMovableCharacter::UpdateInputIcon(int32_t show) {
    if (show == 0) {
        IKFx* icon = static_cast<IKFx*>(m_unk134);
        if (icon == nullptr) return;
        icon->StopAndRelease(this);  // vt+0x58
        m_unk134 = nullptr;
        return;
    }
    // The icon effect of the data +0x2b8 from the FX service's pool (the inlined reserving lookup) when there is none,
    // placed by the node's world matrix (0x001c4bd8 InputIconFx_UpdateWorldPosition_maybe).
    if (m_unk134 == nullptr) {
        m_unk134 = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_unk2b0[2]), this);
        if (m_unk134 == nullptr) return;
    }
    static_cast<CKInputIconNodeFx*>(m_unk134)
        ->UpdateWorldPosition(reinterpret_cast<const CMatrix34*>(FrameLtm(NodeOf(this)->m_pRwFrame)));  // RwFrame +0x50
}

// 0x0059d870 CKHkMovableCharacter_ProcessHitContacts_maybe: the collision volume's contacts this frame. A hit by a
// destroying volume (properties bit 3) ends the character (an explosion at its position, the bonus flag, the volume
// unregistered, hidden, +0x310 queued); any other hit marks it hit (+0x68 bits 4 and 6; +0x70 the hitting hook) when
// it can be hit (+0x140 bits 3-5) and is not in state 5.
void CKHkMovableCharacter::ProcessHitContacts() {
    IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_unk144);
    for (ICollision* collision = static_cast<ICollision*>(volume->m_CollisionResList); collision != nullptr;
         collision = collision->m_pNext) {
        IKBoundingVolume* owner = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1());
        IKBoundingVolume* other = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1());
        if (owner->m_pOwner == this) {
            collision->GetBoundingVolume2();
            other = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume2());
        }
        if ((other->m_ui16PropertiesFlags & 8u) != 0) {
            // The destruction's explosion (data +0x2b0) from the FX service's pool (the inlined lookup), at the node.
            IKFx* effect = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_unk2b0[0]), this);
            const RwV3d& at = FrameLtm(NodeOf(this)->m_pRwFrame)->pos;  // +0x80
            const CVector3 position = {at.x, at.y, at.z};
            if (effect != nullptr) {
                CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
                explosion->SetTranslation(&position, this);  // 0x001b66e8
                explosion->Trigger(this, 0);                 // 0x001b82a8
                explosion->ReleaseReservation(this);         // vt+0x54
            }
            if ((m_unk68 & 0x8000u) != 0) m_unk68 = (m_unk68 & 0xfffeffffu) | 0x10000u;
            static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->RemoveVolume(static_cast<IKBoundingVolume*>(m_unk144));
            m_unk68 = (m_unk68 & 0xfffffdffu) | 0x200u;
            LeafOf(this)->m_sgProperties = (LeafOf(this)->m_sgProperties & 0xfffffffbu) | 4u;
            QueueTriggerSignals(&m_unk310);
            return;
        }
        if (((m_unk140 & 8u) != 0 || (m_unk140 & 0x10u) != 0 || (m_unk140 & 0x20u) != 0) && m_unk2c4 != 5) {
            m_unk68 = (m_unk68 & 0xffffffafu) | 0x10u | 0x40u;
            m_unk70 = nullptr;
            if (other->m_pOwner->IsKindOfClass(2) != 0) m_unk70 = other->m_pOwner;
        }
    }
}

// 0x0059f5c8 CKHkMovableCharacter_UpdateLookAtNearbyEntity_maybe: a character that looks at entities (+0x140 bit 2)
// and is not looking yet takes the first entity of +0x294 within +0x1a4: +0x68 bit 3 and the yaw towards it (+0x74,
// from the arc cosine of the direction's z, the side from its x, in [0, 2 pi)).
void CKHkMovableCharacter::UpdateLookAtNearbyEntity() {
    if ((m_unk140 & 4u) == 0 || (m_unk68 & 8u) != 0) return;
    const RwV3d& position = NodeOf(this)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
    const float pz = position.z;
    const float px = position.x;
    const float py = position.y;
    const float kTwoPi = 6.2831854820251465f;  // TOC2 -0x6a9c (0x40c90fdb)
    for (uint32_t i = 0; i < m_vUnk294.m_ui32NbUsedElt; ++i) {
        CSGMovable* entity = static_cast<CSGMovable*>(m_vUnk294.m_pBlock[i]);
        if (entity == nullptr) continue;
        const RwV3d& target = FrameLtm(entity->m_pRwFrame)->pos;  // RwFrame +0x80
        const float dy = py - target.y;
        float dx = px - target.x;
        float dz = pz - target.z;
        const float distance = MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (distance == 0.0f) {
            if (!(m_unk1a4 >= 0.0f)) continue;
        } else {
            const float inverse = 1.0f / distance;
            dz = dz * inverse;
            dx = dx * inverse;
            if (!(m_unk1a4 >= distance)) continue;
        }
        m_unk68 = (m_unk68 & 0xfffffff7u) | 8u;
        float yaw;
        if (dz <= -1.0f) {
            crt::Acosf(-1.0f);  // the result is not used
            yaw = 3.1415927410125732f;  // TOC2 -0x6a98
        } else if (dz >= 1.0f) {
            crt::Acosf(1.0f);
            yaw = 0.0f;
        } else {
            crt::Acosf(dz);  // computed twice, the first result not used
            yaw = crt::Acosf(dz);
            if (dx > 0.0f) yaw = kTwoPi - yaw;
            if (!(yaw >= 0.0f)) {
                m_unk74 = yaw + kTwoPi;
                continue;
            }
        }
        if (yaw >= kTwoPi) yaw = yaw - kTwoPi;
        m_unk74 = yaw;
    }
}

// 0x005a44e8 CKHkMovableCharacter_UpdateRandomActionTimer_maybe: the random action timer runs down; when it is
// below 0 a draw against the probability +0x190 either makes the action due (+0x68 bit 0; the timer stays) or a second
// draw restarts the timer between +0x184 and +0x188. Then the idle sound (3, or 5 in state 4) loops when not playing.
void CKHkMovableCharacter::UpdateRandomActionTimer() {
    const float timer = m_unk78;
    m_unk65 = 0;
    if (timer < 0.0f) {
        if (RandUnit() <= m_unk190) {
            m_unk68 = (m_unk68 & 0xfffffffeu) | 1u;
        } else {
            const float unit = RandUnit();
            m_unk78 = ppc::fmadds(unit, m_unk188 - m_unk184, m_unk184);
        }
    } else {
        m_unk78 = timer - m_pClock->m_afDeltaTime[0];
    }
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk13c);
    if (sounds == nullptr) return;
    CKSound* sound = CKSoundDictionaryID_GetSound(sounds, m_unk2c4 == 4 ? 5u : 3u);
    if (sound == nullptr || sound->CountInstances() != 0) return;
    CKSound_SetLoop(sound, 1);
    CKSound_Play(0.0f, sound);
}

// 0x005a4800 CKHkMovableCharacter_ChooseState_maybe (see the header: the flags' priority order).
uint8_t CKHkMovableCharacter::ChooseState() {
    const uint32_t flags = m_unk68;
    if ((flags & 0x4000u) != 0) return 6;
    const uint32_t properties = m_unk140;
    if ((flags & 8u) == 0 && ((properties & 8u) != 0 || (properties & 0x10u) != 0 || (properties & 0x20u) != 0) &&
        (flags & 0x10u) != 0) {
        return 5;
    }
    if ((properties & 4u) != 0 && (flags & 8u) != 0) {
        if (m_unk148 > 1) return 4;
        const RwV3d& position = NodeOf(this)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
        if (m_unk284.x > position.x && m_unk284.z > position.z && m_unk278.x < position.x && position.z > m_unk278.z) {
            return 4;
        }
    }
    if ((properties & 2u) != 0 && (flags & 1u) != 0) return 3;
    if (m_unk2a0[0] != nullptr) return 1;
    return (properties & 1u) == 0 ? 2 : 0;
}

// 0x005a64e8 CKHkMovableCharacter_State0 (stand): entering draws the random action timer (speed 0); leaving clears
// +0x68 bit 5 and stops the sounds 3 and 5; the tick runs the random action timer (speed 0).
uint8_t CKHkMovableCharacter::State0(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        if (m_unk178 != 0.0f) return 0;
        const float unit = RandUnit();
        m_unk78 = ppc::fmadds(unit, m_unk188 - m_unk184, m_unk184);
        return 0;
    }
    if (phase == 2) {
        m_unk68 &= 0xffffffdfu;
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk13c);
        if (sounds == nullptr) return 0;
        StopSound(sounds, 3);
        StopSound(sounds, 5);
        return 0;
    }
    if (phase != 0) return 0;
    m_unk65 = 1;
    if (m_unk178 == 0.0f) {
        UpdateRandomActionTimer();
        return 0;
    }
    // The walk towards the target +0x94: the speed approaches +0x178 (the brake: with +0x140 bit 1, inside the braking
    // distance the random action draw decides whether it stops), the next position is checked against the bounds, the
    // blocked cells (+0x140 bit 7), the walls and the ground (unless +0x140 bit 17); a target passed (or a stop) picks the
    // next one: a wall / bound / cell stop walks +0x184 along the turned heading, else a random wander target (a random
    // action due when the draw passed, +0x68 bit 1 -> bit 0). Then the node is placed and turned along its up.
    RwFrame* frame = NodeOf(this)->m_pRwFrame;
    CVector3 up = ToVector(frame->modelling.up);  // RwFrame +0x20
    m_unk7c[1] = m_unk17c;
    const RwV3d& start = frame->modelling.pos;     // RwFrame +0x40
    CVector3 next;
    next.z = m_unk94.z - start.z;
    next.x = m_unk94.x - start.x;
    next.y = m_unk94.y - start.y;
    const float acceleration = m_unk17c;
    const float current = m_unk7c[2];
    bool brake = false;
    if ((m_unk140 & 2u) != 0) {
        const float distance = MathSqrtf(ppc::fmadds(next.z, next.z, ppc::fmadds(next.x, next.x, next.y * next.y)));
        const float square = current * current;
        const float braking = (square + square) / acceleration;
        brake = !(braking < distance);
    }
    if (!brake) {
        m_unk7c[0] = m_unk178;
    } else {
        const uint32_t flags = m_unk68;
        if ((flags & 2u) != 0) {
            m_unk7c[0] = 0.0f;  // a word store
        } else if ((flags & 0x20u) == 0) {
            if (RandUnit() <= m_unk190) m_unk68 = (m_unk68 & 0xfffffffdu) | 2u;
            m_unk68 = (m_unk68 & 0xffffffdfu) | 0x20u;
        }
    }
    const float walk = FloatApproach_Step(m_pClock->m_afDeltaTime[0], m_unk7c);  // 0x002436e8
    const float step = walk * m_pClock->m_afDeltaTime[0];
    frame = NodeOf(this)->m_pRwFrame;
    const RwMatrix& m = frame->modelling;
    next.z = ppc::fmadds(step, m.at.z, m.pos.z);
    next.x = ppc::fmadds(step, m.at.x, m.pos.x);
    next.y = ppc::fmadds(step, m.at.y, m.pos.y);
    const float targetZ = m_unk94.z;
    const float targetX = m_unk94.x;
    CVector3 direction;
    direction.z = targetZ - next.z;
    direction.x = targetX - next.x;
    direction.y = m_unk94.y - next.y;
    const float startZ = m.pos.z;
    const float startX = m.pos.x;
    ClampToMoveBounds(&next, &direction);  // 0x005a0590
    uint32_t properties = m_unk140;
    if ((properties & 0x80u) != 0) {
        CheckNavCellBlocked(&next, &direction);  // 0x005a0698
        properties = m_unk140;
    }
    if ((properties & 0x20000u) == 0) {
        CheckBlockingCollision(&next, &direction);       // 0x005a08c0
        ProbeGroundAtTarget(&next, &direction, &up);     // 0x005a0ab0
    } else {
        next.y = m_unk278.y;
        m_shadowPos = next;
        m_shadowNormal = kAxisY;
        m_unkEC = 0;
    }
    // The flat direction to the target (y 0) normalised; the target is passed once both x and z changed side.
    direction.y = 0.0f;
    float length = MathSqrtf(ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, 0.0f)));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        direction.z = direction.z * inverse;
        direction.x = direction.x * inverse;
        direction.y = direction.y * inverse;
    } else {
        length = 0.0f;
    }
    const bool sameSide =
        SignOf(targetX - startX) == SignOf(direction.x) || SignOf(targetZ - startZ) == SignOf(direction.z);
    const bool passed = !sameSide || length < 0.2f || (m_unk68 & 4u) != 0 || (m_unk68 & 0x80u) != 0 ||
                        (m_unk68 & 0x100u) != 0;  // TOC2 -0x696c
    if (passed) {
        const uint32_t flags = m_unk68;
        if ((flags & 4u) != 0 || (flags & 0x80u) != 0 || (flags & 0x100u) != 0) {
            // Stopped: +0x184 along the (turned) direction from the node.
            const RwV3d& position = NodeOf(this)->m_pRwFrame->modelling.pos;
            const float reach = m_unk184;
            m_unk94.z = ppc::fmadds(reach, direction.z, position.z);
            m_unk94.x = ppc::fmadds(direction.x, reach, position.x);
            m_unk94.y = ppc::fmadds(reach, direction.y, position.y);
            ResetTargetIfOutOfBounds();  // 0x005a0498
        } else {
            if ((flags & 2u) == 0 && (flags & 0x20u) == 0) {
                if (RandUnit() <= m_unk190) m_unk68 = (m_unk68 & 0xfffffffdu) | 2u;
                m_unk68 = (m_unk68 & 0xffffffdfu) | 0x20u;
            }
            if ((m_unk68 & 2u) != 0) m_unk68 = ((m_unk68 & 0xfffffffeu) | 1u) & 0xfffffffdu;
            PickRandomWanderTarget(AsVector(&NodeOf(this)->m_pRwFrame->modelling.at));  // 0x005a0e50
        }
        m_unk68 &= 0xffffffdfu;
        direction.y = m_unk94.y - next.y;
        direction.x = m_unk94.x - next.x;
        direction.z = m_unk94.z - next.z;
        NormaliseYxz(&direction);
    }
    SetNodePosition(NodeOf(this), next.x, next.y, next.z);
    TurnTowardDirectionAligned(&direction, &up);  // 0x005a1f18
    return 0;
}

// 0x005a5f00 CKHkMovableCharacter_State2 (wander): as State0 for the enter and leave phases; the tick runs the random
// action timer (speed 0).
uint8_t CKHkMovableCharacter::State2(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        if (m_unk178 == 0.0f) {
            const float unit = RandUnit();
            m_unk78 = ppc::fmadds(unit, m_unk188 - m_unk184, m_unk184);
        }
    } else if (phase == 2) {
        m_unk68 &= 0xffffffdfu;
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk13c);
        if (sounds != nullptr) {
            StopSound(sounds, 3);
            StopSound(sounds, 5);
        }
    } else if (phase == 0) {
        m_unk65 = 1;
        if (m_unk178 == 0.0f) {
            UpdateRandomActionTimer();
        } else {
            // The wander walk (no bounds, cell, wall or ground checks): the speed approaches +0x178 (the brake as
            // State0's), the height moves towards the target's by at most 0.6 x the speed per second; a target passed (or
            // reached within +0x184 / 100) picks the next wander target without moving this frame; then the turn
            // (TurnTowardDirectionFlat).
            const float current = m_unk7c[2];
            const float square = current * current;
            m_unk7c[1] = m_unk17c;
            const RwV3d& start = NodeOf(this)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
            const float dy = m_unk94.y - start.y;
            const float dx = m_unk94.x - start.x;
            const float dz = m_unk94.z - start.z;
            const float braking = (square + square) / m_unk17c;
            const float distance = MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
            if (braking < distance || (m_unk140 & 2u) == 0) {
                m_unk7c[0] = m_unk178;
            } else {
                const uint32_t flags = m_unk68;
                if ((flags & 2u) != 0) {
                    m_unk7c[0] = 0.0f;  // a word store
                } else if ((flags & 0x20u) == 0) {
                    if (RandUnit() <= m_unk190) m_unk68 = (m_unk68 & 0xfffffffdu) | 2u;
                    m_unk68 = (m_unk68 & 0xffffffdfu) | 0x20u;
                }
            }
            const float walk = FloatApproach_Step(m_pClock->m_afDeltaTime[0], m_unk7c);  // 0x002436e8
            const float dt = m_pClock->m_afDeltaTime[0];
            float height = m_unk94.y;
            const float step = walk * dt;
            const RwMatrix& m = NodeOf(this)->m_pRwFrame->modelling;
            const float ny = ppc::fmadds(step, m.at.y, m.pos.y);
            const float nz = ppc::fmadds(step, m.at.z, m.pos.z);
            const float nx = ppc::fmadds(step, m.at.x, m.pos.x);
            if (ny > height) {
                const float limit = ppc::fmadds(dt, walk * -0.6f, ny);  // TOC2 -0x6978
                if (!(height > limit)) height = limit;
            } else if (!(ny < height)) {  // bge: equal or unordered
                height = ny;
            } else {
                const float limit = ppc::fmadds(dt, walk * 0.6f, ny);  // TOC2 -0x6974
                if (!(height < limit)) height = limit;
            }
            const float targetX = m_unk94.x;
            const float targetZ = m_unk94.z;
            CVector3 direction;
            direction.y = 0.0f;
            direction.x = targetX - nx;
            direction.z = targetZ - nz;
            const float startZ = m.pos.z;
            const float startX = m.pos.x;
            float length = MathSqrtf(ppc::fmadds(direction.z, direction.z, ppc::fmadds(direction.x, direction.x, 0.0f)));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                direction.z = direction.z * inverse;
                direction.x = direction.x * inverse;
                direction.y = direction.y * inverse;
            } else {
                length = 0.0f;
            }
            const bool sameSide =
                SignOf(targetX - startX) == SignOf(direction.x) || SignOf(targetZ - startZ) == SignOf(direction.z);
            if (sameSide && !(m_unk184 * 0.01f > length)) {  // TOC2 -0x6970
                SetNodePosition(NodeOf(this), nx, height, nz);
            } else {
                if ((m_unk68 & 2u) != 0) m_unk68 = ((m_unk68 & 0xfffffffeu) | 1u) & 0xfffffffdu;
                PickRandomWanderTarget(AsVector(&NodeOf(this)->m_pRwFrame->modelling.at));  // 0x005a0e50
                m_unk68 &= 0xffffffdfu;
                direction.y = m_unk94.y - height;
                direction.x = m_unk94.x - nx;
                direction.z = m_unk94.z - nz;
                NormaliseYxz(&direction);
            }
            TurnTowardDirectionFlat(&direction);  // 0x005a1b28
        }
    }
    return 2;
}

// 0x005a4668 CKHkMovableCharacter_State3 (a random action): entering draws its duration (+0x194..+0x198) and, with
// sounds, a second draw picks the sound 0 or 4 and plays it; the tick stops the walk and runs the duration down, the
// action ending (+0x68 bit 0 cleared) once it is below 0 (unless the character is on a path with a flag and no
// duration).
uint8_t CKHkMovableCharacter::State3(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 0) {
        m_unk65 = 0;
        m_unk7c[0] = 0.0f;
        m_unk7c[2] = 0.0f;
        const float timer = m_unk78;
        if (timer < 0.0f) {
            const bool onFlaggedPath = m_unk2a0[0] != nullptr &&
                                       static_cast<const CKPathStepCpnt*>(m_unk2a0[1])->m_ui32Count != 0;  // LVL010: CKPathStepCpnt (+8)
            if (!onFlaggedPath || m_unk198 != 0.0f) {
                m_unk68 &= 0xfffffffeu;
                return 3;
            }
        }
        m_unk78 = timer - m_pClock->m_afDeltaTime[0];
        return 3;
    }
    if (phase != 1) return 3;
    const float unit = RandUnit();
    m_unk78 = ppc::fmadds(unit, m_unk198 - m_unk194, m_unk194);
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk13c);
    if (sounds == nullptr) return 3;
    const uint32_t draw = static_cast<uint32_t>(Rand_Int());
    const uint32_t index = ((draw << 1) & 0x1fffeu) > 0xffffu ? 0u : 4u;
    if (CKSoundDictionaryID_GetSound(sounds, index) == nullptr) return 3;
    CKSound_Play(0.0f, CKSoundDictionaryID_GetSound(sounds, index));
    return 3;
}

// 0x005a23c0 CKHkMovableCharacter_Update
void CKHkMovableCharacter::Update(IKTime* clock) {
    if (m_unk130 != 0) return;
    UpdateFade(clock);
    CSGLeaf* node = LeafOf(this);
    if ((node->m_sgProperties & 4u) != 0) {
        // Hidden: the sounds stopped, the shadow released, a due bonus dropped, the input icon released.
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk13c);
        if (sounds != nullptr) {
            for (uint32_t index = 6; index-- > 0;) StopSound(sounds, index);
        }
        uint32_t flags = m_unk68;
        if ((flags & 0x800u) != 0 && m_unk290 != nullptr && m_unkF1 != 0) {
            static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
                ->UnregisterCaster(reinterpret_cast<CKShadowGround*>(&m_shadowPos), m_unk290);
            flags = m_unk68;
        }
        if ((flags & 0x10000u) != 0) {
            // A random direction (rand() & 0xffff over 65535 times 2 pi) for the bonus.
            const RwV3d& at = FrameLtm(static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame)->pos;  // +0x80
            const CVector3 position = {at.x, at.y, at.z};
            const float angle = RandUnit() * 6.2831854820251465f;  // TOC2 -0x6a9c
            // BUG(original): both components are the cosine (the inlined polynomial twice, the library cosf for a
            // negative angle twice): the bonus goes out along (cos, 0, cos).
            const float c = GameCosf(angle);
            const CVector3 direction = {c, 0.0f, GameCosf(angle)};
            static_cast<KBase201*>(g_pEngine->m_srvBonus)
                ->SpawnBonuses(static_cast<CKBonusData*>(m_unk2b0[1]), &position, &direction, &position, 0);  // 0x00126278
            m_unk68 &= 0xfffeffffu;
        }
        UpdateInputIcon(0);
        return;
    }
    if ((m_unk68 & 0x400u) != 0 && node->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter) {
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
        return;
    }
    ProcessHitContacts();
    if ((m_unk68 & 0x800u) != 0 && m_unk290 != nullptr && m_unkF1 == 0) {
        CSGLeaf* leaf = LeafOf(this);
        if ((leaf->m_sgProperties & 4u) == 0) {
            static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
                ->RegisterCaster(m_unk290, leaf, reinterpret_cast<CKShadowGround*>(&m_shadowPos), 0, nullptr, 0);
        }
    }
    m_unk68 &= 0xffffefffu;
    m_pClock = clock;
    UpdateLookAtNearbyEntity();
    if (m_unk2b0[2] != nullptr) UpdateHeroProximity();  // 0x0059fb18
    if ((m_unk140 & 0x40000u) != 0 && (m_unk68 & 0x4000u) == 0 && m_unk2c4 != 6) {
        CSGMovable* hero = FocusedHeroNode(HeroGroup());
        if (m_unk1c4 >= DistanceToNode(NodeOf(this), hero)) m_unk68 = (m_unk68 & 0xffffbfffu) | 0x4000u;
    }

    // The state engine: the chosen state first (its enter and leave calls without a clock), then the current state's
    // tick and the state it returns.
    const uint8_t chosen = ChooseState();
    uint8_t current = m_unk2c4;
    bool tick = true;
    if (chosen != current) {
        if (current != 0xff) CallState(current, nullptr, 2, chosen);
        m_unk2c4 = chosen;
        if (chosen == 0xff) {
            tick = false;
        } else {
            CallState(chosen, nullptr, 1, current);
            current = m_unk2c4;
        }
    }
    if (tick && current != 0xff) {
        const uint8_t next = CallState(current, clock, 0, current);
        const uint8_t previous = m_unk2c4;
        if (next != previous) {
            if (previous != 0xff) CallState(previous, clock, 2, next);
            m_unk2c4 = next;
            if (next != 0xff) CallState(next, clock, 1, previous);
        }
    }

    if (m_unk178 != 0.0f) UpdateMoveSound();  // 0x0059d328
    uint32_t properties = m_unk140;
    if ((properties & 0x400u) != 0) {
        UpdateLocomotionAnim();  // 0x0059d490
        properties = m_unk140;
    }
    if (m_unk2a0[0] == nullptr) m_unk88[1] = m_unk180;
    const uint32_t spinAxis = (properties >> 12) & 3u;
    if (spinAxis != 0) {
        RwFrame* frame = NodeOf(this)->m_pRwFrame;
        const RwV3d& source = spinAxis == 1 ? FrameLtm(frame)->right : spinAxis == 2 ? FrameLtm(frame)->up : FrameLtm(frame)->at;
        const float axis[3] = {source.x, source.y, source.z};
        NodeOf(this)->RotateInPlace(axis, m_unk1b8 * clock->m_afDeltaTime[0]);
    }
    uint32_t flags = m_unk68;
    if ((flags & 0x800u) != 0 && (flags & 0x1000u) == 0) {
        UpdateGroundContact();  // 0x0059efa8
        flags = m_unk68;
    }
    if ((flags & 0x800u) != 0 && m_unk290 != nullptr) {
        // The shadow fades in (+0xfc > 0) or out (< 0) over +0x1c0 seconds.
        CKShadowCpnt* shadow = static_cast<CKShadowCpnt*>(m_unk290);
        const float timer = m_unkFC;
        if (timer == 0.0f) {
            shadow->m_ShadowColor[3] = m_unk100;
        } else if (timer > 0.0f) {
            const float left = timer - clock->m_afDeltaTime[0];
            m_unkFC = left;
            if (left <= 0.0f) {
                m_unkFC = 0.0f;
                shadow->m_ShadowColor[3] = m_unk100;
            } else {
                shadow->m_ShadowColor[3] = static_cast<uint8_t>(
                    ppc::fctiwz(((m_unk1c0 - left) * static_cast<float>(m_unk100)) / m_unk1c0));
            }
        } else if (timer < 0.0f) {
            const float left = timer + clock->m_afDeltaTime[0];
            m_unkFC = left;
            if (left >= 0.0f) {
                m_unkFC = 0.0f;
                shadow->m_ShadowColor[3] = 0;
                if ((m_unk68 & 0x800u) != 0 && m_unk290 != nullptr && m_unkF1 != 0) {
                    static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
                        ->UnregisterCaster(reinterpret_cast<CKShadowGround*>(&m_shadowPos), m_unk290);
                }
                m_unk68 &= 0xfffff7ffu;
            } else {
                shadow->m_ShadowColor[3] =
                    static_cast<uint8_t>(ppc::fctiwz((static_cast<float>(m_unk100) * std::fabs(left)) / m_unk1c0));
            }
        }
    }
    if (m_unk1bc != 1.0f) SetUniformScale(m_unk1bc);
    if (m_unk2ac != 0.0f) {
        IKGrpHero* group = HeroGroup();
        if (group == nullptr) return;
        CSGMovable* hero = FocusedHeroNode(group);
        if (hero == nullptr) return;
        if (m_unk2ac > DistanceToNode(NodeOf(this), hero)) {
            // The sequence the hero starts by coming near (C2.8 port-all P11): sekens 0 of the launcher +0x2a8 played
            // unless it plays already (0x001f7958 IsSekensPlaying_maybe, 0x001f7730 PlaySekens_maybe; not null-checked).
            CKSekensLauncherCpnt* launcher = static_cast<CKSekensLauncherCpnt*>(m_unk2a0[2]);
            if (launcher->IsSekensPlaying(0) == 0) launcher->PlaySekens(0);
        }
    }
}

// 0x0059e7a8 CKHkMovableCharacter_MessageProc
int32_t CKHkMovableCharacter::MessageProc(uint16_t message, void* data) {
    if (((message >> 8) & 0xffu) != 4) return 1;
    CSGLeaf* node = LeafOf(this);
    // Hiding: the shadow released, the sounds 5..0 stopped, the collision volume removed.
    auto hideTail = [this]() {
        if ((m_unk68 & 0x800u) != 0 && m_unk290 != nullptr && m_unkF1 != 0) {
            static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
                ->UnregisterCaster(reinterpret_cast<CKShadowGround*>(&m_shadowPos), m_unk290);
        }
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk13c);
        if (sounds != nullptr) {
            for (uint32_t index = 6; index-- > 0;) StopSound(sounds, index);
        }
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->RemoveVolume(static_cast<IKBoundingVolume*>(m_unk144));  // 0x00192bc0
        return 0;
    };
    // Showing: the collision volume back when the character collides (+0x140 bits 3, 4, 5 or 22).
    auto showTail = [this]() {
        if ((m_unk140 & 0x400038u) != 0) {
            static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->AddVolume(static_cast<IKBoundingVolume*>(m_unk144));  // 0x00192b80
        }
        return 0;
    };
    switch (message & 0xffu) {
        case 0x00:
            if ((m_unk140 & 0x4000u) == 0) return 3;
            return 0;
        case 0x02:
            if ((m_unk140 & 0x4000u) == 0) return 3;
            *static_cast<uint8_t*>(data) = 1;
            return 0;
        case 0x96:
            if (*static_cast<const int32_t*>(data) == 1) {
                // Fading in (a hidden character only).
                if ((node->m_sgProperties & 4u) != 0) {
                    m_unk68 &= 0xfffffdffu;
                    if (m_unkF8 <= 0.0f) m_unkF8 = m_unk1b0;
                }
                return showTail();
            }
            // Fading out (a shown character only), then hidden at once.
            if ((node->m_sgProperties & 4u) == 0) {
                m_unk68 = (m_unk68 & 0xfffffdffu) | 0x200u;
                if (m_unkF8 <= 0.0f) m_unkF8 = m_unk1b0;
            }
            return hideTail();
        case 0x97:
            m_unk25 = static_cast<uint8_t>(m_unk25 + 1);
            if (m_unk24 > m_unk25) return 0;
            m_unk68 &= 0xfffffffcu;
            return 0;
        case 0x98:
            if (*static_cast<const int32_t*>(data) == 1) {
                node->m_sgProperties &= 0xfffffffbu;
                SetGeometriesOpaque(static_cast<CGeometry*>(static_cast<CNode*>(m_pKGLObject)->m_lGeometryList));
                return showTail();
            }
            node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
            return hideTail();
        case 0x99:
            m_unk180 = 0.0f;
            m_unk68 &= 0xfffffffcu;
            {
                // The path +0x2a0 back to distance 0 (0x000c4d88 CKFlaggedPath_SetDistanceAndGetPositionUp_maybe into a stack
                // point that is not read; not null-checked).
                CVector3 point;
                static_cast<CKFlaggedPath*>(m_unk2a0[0])->SetDistanceAndGetPositionUp(0.0f, &point, nullptr, nullptr);
            }
            m_unk25 = 0;
            m_unk24 = 0;
            return 0;
        case 0x9a:
            m_unk68 = (m_unk68 & 0xfffffbffu) | 0x400u;
            return 0;
        case 0x9b:
            m_unk68 = (m_unk68 & 0xfffff7ffu) | 0x800u;
            m_unkFC = m_unk1c0;
            return 0;
        case 0x9c:
            m_unk68 = (m_unk68 & 0xfffff7ffu) | 0x800u;
            m_unkFC = -m_unk1c0;
            return 0;
        case 0x9d:
            m_unk68 &= 0xfffe7fffu;
            return 0;
        default:
            return 1;
    }
}

// 0x0059e060 CKHkMovableCharacter_vf3C (SetGameState): (x >> 31) - ((x >> 31) ^ x) has its sign bit set for any x != 0.
int32_t CKHkMovableCharacter::SetGameState(const SApplyGameState* state) {
    m_unk130 = state->m_ui32GameStateId != 0 ? 1 : 0;
    return 1;
}

// 0x0059dff8 CKHkMovableCharacter_vf40 (GetInfo), with 0x009cba68 CKHkMovableCharacter_IsVisible_maybe.
int32_t CKHkMovableCharacter::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 0xc) return 1;
    return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
        const CSGLeaf* node = LeafOf(static_cast<CKHkMovableCharacter*>(o));
        return ((node->m_sgProperties ^ 4u) >> 2) & 1u;
    }, 0);
}

// 0x0059df38 CKHkMovableCharacter_GetComponentByKey_maybe (CKSrvShadow_RegisterCaster through its TOC bridge)
IKSerializable* CKHkMovableCharacter::GetComponent(uint32_t key) {
    if (key != 0x486) return nullptr;
    if ((m_unk68 & 0x800u) != 0 && m_unk290 != nullptr && m_unkF1 == 0) {
        static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
            ->RegisterCaster(m_unk290, m_pKGLObject, reinterpret_cast<CKShadowGround*>(&m_shadowPos),
                             0, nullptr, 0);
    }
    return reinterpret_cast<IKSerializable*>(&m_shadowPos);
}

// 0x0059fb18 CKHkMovableCharacter_UpdateHeroProximity_maybe (GetControlledHeroCount / GetControlledHeroArray /
// CKHkS08Hero_GetPositionPtr through their TOC bridges): the input icon shown while a controlled hero is within +0x2bc of
// the node's LTM position (fsubs, fmuls, two fmadds against the radius squared), else hidden.
void CKHkMovableCharacter::UpdateHeroProximity() {
    const RwV3d& position = FrameLtm(NodeOf(this)->m_pRwFrame)->pos;  // RwFrame +0x80
    const float pz = position.z;
    const float px = position.x;
    const float py = position.y;
    IKGrpHero* heroes = HeroGroup();
    for (int32_t i = 0; static_cast<int32_t>(heroes->m_ui8ControlledHeroCount) > i; ++i) {
        const float* hero = static_cast<CKHkS08Hero*>(heroes->m_apControlledHeroes[i])->GetPositionPtr();
        const float radius = m_unk2bc;
        const float dy = hero[1] - py;
        const float dx = hero[0] - px;
        const float dz = hero[2] - pz;
        const float distance2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (distance2 < radius * radius) {
            UpdateInputIcon(1);
            return;
        }
    }
    UpdateInputIcon(0);
}

// 0x0059d328 CKHkMovableCharacter_UpdateMoveSound_maybe (the dictionary's GetSound, CKSound_SetLoop_maybe, CKSound_Play
// and Sound_Stop through their TOC bridges): a character standing still (walk speed +0x84 0) without a looping sound
// (+0x140 bit 21) stops its walk (3) and look-at (5) sounds; else the state's sound (5 looking at an entity, 3 otherwise)
// starts looping when no instance of it plays.
void CKHkMovableCharacter::UpdateMoveSound() {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk13c);
    if (sounds == nullptr) return;
    if (m_unk7c[2] == 0.0f && (m_unk140 & 0x200000u) == 0) {
        StopSound(sounds, 3);
        StopSound(sounds, 5);
        return;
    }
    CKSound* sound = CKSoundDictionaryID_GetSound(sounds, m_unk2c4 == 4 ? 5 : 3);
    if (sound == nullptr) return;
    if (sound->CountInstances() != 0) return;
    CKSound_SetLoop(sound, 1);
    CKSound_Play(0.0f, sound);  // TOC2 -0x6abc
}

// 0x0059efa8 CKHkMovableCharacter_UpdateGroundContact_maybe (GroundProbePoints_maybe, GroundContact_GetWorldPoint /
// GetWorldNormal_maybe and CKSrvShadow_UnregisterCaster through their TOC bridges): +0x68 bit 12 set, the ground under
// the node's modelling position probed; on a ground (status 0..2) the shadow ground takes the contact's world point,
// normal and height, and +0xf0 bit 4 the ground's engine flag bit 6; with no ground (status 3) a registered shadow is
// unregistered.
void CKHkMovableCharacter::UpdateGroundContact() {
    m_unk68 = (m_unk68 & 0xffffefffu) | 0x1000u;
    const RwV3d& position = NodeOf(this)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
    const float probe[3] = {position.x, position.y, position.z};
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_GContactIn, &m_GContactInOut, probe, 1);
    const int32_t status = static_cast<int32_t>(m_GContactInOut.m_eContactStatus);
    if (status < 0) return;
    if (status < 3) {
        GroundContact_GetWorldPoint(&m_GContactInOut, &m_shadowPos);    // 0x001a70e0
        GroundContact_GetWorldNormal(&m_GContactInOut, &m_shadowNormal);  // 0x001a71d8
        std::memcpy(&m_unkEC, &m_GContactInOut.m_fdH, sizeof m_unkEC);  // the height above the ground (a word copy)
        if (((static_cast<const ICollisionMesh*>(m_GContactInOut.m_pGround)->m_ba16EngineFlags >> 6) & 1u) != 0) {
            m_unkF0 = static_cast<uint8_t>(m_unkF0 | 0x10u);
            return;
        }
        if ((m_unkF0 & 0x10u) != 0) m_unkF0 = static_cast<uint8_t>(m_unkF0 ^ 0x10u);
        return;
    }
    if (status == 3 && (m_unk68 & 0x800u) != 0 && m_unk290 != nullptr && m_unkF1 != 0) {
        static_cast<CKSrvShadow*>(g_pEngine->m_srvShadow)
            ->UnregisterCaster(reinterpret_cast<CKShadowGround*>(&m_shadowPos), m_unk290);
    }
}

// 0x0059d490 CKHkMovableCharacter_UpdateLocomotionAnim_maybe (CAnimatedNode_GetActiveAnim / CrossfadeToAnim / AddAnimTime /
// IsAnimEndReached, Rand_Int and QueueTriggerSignals through their TOC bridges): a new animation index (+0x65 against
// +0x64, or the node playing another animation) crossfades to it over 0.3 s once (+0x68 bit 13 marks the change frame),
// for the stand and look-at animations (0 / 4) with +0x140 bit 16 from a random time of its duration (one draw). Else
// the animation advances by the frame time scaled per index (1 walk: by the walk speed (at least 0.8) over +0x178;
// 2: over +0x19c) and +0x268..+0x274; at its end the starter +0x300 fires, and +0x308 for the walk.
void CKHkMovableCharacter::UpdateLocomotionAnim() {
    CAnimatedNode* node = static_cast<CAnimatedNode*>(m_pKGLObject);
    const int32_t* animations = static_cast<CAnimationDictionary*>(m_unk138)->m_apAnimations;
    bool change = true;
    if (m_unk64 == m_unk65) {
        const uint32_t active = node->GetActiveAnim();  // 0x000c9720
        if (static_cast<uint32_t>(animations[m_unk65]) == active) change = false;
    }
    if (change && (m_unk68 & 0x2000u) == 0) {
        const uint8_t index = m_unk65;
        float start = 0.0f;  // TOC2 -0x6abc
        if (index == 4 || index == 0) {
            const uint32_t word = static_cast<uint32_t>(animations[index]);
            RtAnimAnimation* animation = CAnimationManager_GetAnimation(word);
            if (animation != nullptr && (m_unk140 & 0x10000u) != 0) {
                const float duration = animation->duration;
                start = duration * RandUnit();  // rand & 0xffff over 65535 (TOC2 -0x6ab8)
            }
        }
        const uint32_t word = static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_unk138)->m_apAnimations[m_unk65]);
        node->CrossfadeToAnim(0.30000001192092896, start, word, 1);  // 0x000c8eb0, blend TOC2 -0x6ab4
        m_unk68 = (m_unk68 & 0xffffdfffu) | 0x2000u;
        m_unk64 = m_unk65;
        return;
    }
    float dt = m_pClock->m_afDeltaTime[0];
    m_unk68 &= 0xffffdfffu;
    float speed = m_unk7c[2];
    const float minimum = 0.8f;  // TOC2 -0x6ab0
    if (speed < minimum) speed = minimum;
    switch (m_unk64) {
        case 1:
            if (m_unk178 != 0.0f) dt = dt * (speed / m_unk178);
            dt = dt * m_unk268[1];
            break;
        case 2:
            if (m_unk19c != 0.0f && m_unk178 != 0.0f) dt = dt * (speed / m_unk19c);
            dt = dt * m_unk268[2];
            break;
        case 0:
            dt = dt * m_unk268[0];
            break;
        case 3:
            dt = dt * m_unk268[3];
            break;
        default:
            break;
    }
    node->AddAnimTime(dt);  // 0x000c9638
    if (!node->IsAnimEndReached(dt)) return;  // 0x000ca368
    QueueTriggerSignals(&m_unk300);
    if (m_unk64 == 1) QueueTriggerSignals(&m_unk308);
}

// ---- C2.8 lvl020-walkers: the walking machinery (path following, wander, the bounds / nav-cell / wall checks, the turns,
// states 1 / 4 / 5 / 6) ----

// 0x0059cc60 CKHkMovableCharacter_PushTargetInsideBounds_maybe: the wander target's height clamped into the bounds
// (+0xa4..+0xb0 y); a target outside the bounds on x or z is put on the side it left by, the turn radius (+0xa0) beside the
// character along the other axis: past a corner the axis the heading (`at`) leans on less picks the side, past one side
// the bounds' centre (x or z) picks the direction of the step.
void CKHkMovableCharacter::PushTargetInsideBounds(const CVector3* at) {
    const RwV3d& position = NodeOf(this)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
    const float pz = position.z;
    const float px = position.x;
    // BUG(original): the centre (f6 / f7) is only computed for a wanderer (+0x148 < 2); any other caller reads what the
    // registers held. 0 here.
    float cx = 0.0f;
    float cz = 0.0f;
    if (m_unk148 <= 1) {
        cx = ppc::fmadds(m_unk284.x - m_unk278.x, 0.5f, m_unk278.x);  // TOC2 -0x6af0
        cz = ppc::fmadds(m_unk284.z - m_unk278.z, 0.5f, m_unk278.z);
    }
    if (m_unk94.y > m_unkB0.y) {
        m_unk94.y = m_unkB0.y;
    } else if (m_unk94.y < m_unkA4.y) {
        m_unk94.y = m_unkA4.y;
    }
    const float tx = m_unk94.x;
    const bool lowX = tx < m_unkA4.x;
    const float radius = m_unkA0;
    // |at.x| > |at.z| (the sign bits cleared through memory, as the original).
    const auto leansOnX = [at]() { return std::fabs(at->x) > std::fabs(at->z); };
    if (lowX && m_unk94.z < m_unkA4.z) {
        if (leansOnX()) {
            m_unk94.x = m_unkA4.x;
            m_unk94.z = pz + radius;
        } else {
            m_unk94.z = m_unkA4.z;
            m_unk94.x = px + radius;
        }
        return;
    }
    const bool highX = tx > m_unkB0.x;
    if (highX && m_unk94.z > m_unkB0.z) {
        if (leansOnX()) {
            m_unk94.x = m_unkB0.x;
            m_unk94.z = pz - radius;
        } else {
            m_unk94.z = m_unkB0.z;
            m_unk94.x = px - radius;
        }
        return;
    }
    if (lowX && m_unk94.z > m_unkB0.z) {
        if (leansOnX()) {
            m_unk94.x = m_unkA4.x;
            m_unk94.z = pz - radius;
        } else {
            m_unk94.z = m_unkB0.z;
            m_unk94.x = px + radius;
        }
        return;
    }
    if (highX && m_unk94.z < m_unkA4.z) {  // bge: an unordered z goes on
        if (leansOnX()) {
            m_unk94.x = m_unkB0.x;
            m_unk94.z = pz + radius;
        } else {
            m_unk94.z = m_unkA4.z;
            m_unk94.x = px - radius;
        }
        return;
    }
    if (lowX) {
        m_unk94.x = m_unkA4.x;
        m_unk94.z = !(pz < cz) ? pz - radius : pz + radius;  // bge: unordered steps back
        return;
    }
    if (highX) {
        m_unk94.x = m_unkB0.x;
        m_unk94.z = pz < cz ? pz + radius : pz - radius;
        return;
    }
    float side;
    if (m_unk94.z < m_unkA4.z) {
        side = m_unkA4.z;
    } else {
        side = m_unkB0.z;
        if (!(m_unk94.z > side)) return;  // blelr
    }
    m_unk94.z = side;
    m_unk94.x = px < cx ? px + radius : px - radius;
}

// 0x0059dde0 CKHkMovableCharacter_DirectionToYaw_maybe (`this` not read): the yaw of the direction in [0, 2 pi): the arc
// cosine of its z (0 at or above 1, pi at or below -1), mirrored when x > 0.
float CKHkMovableCharacter::DirectionToYaw(const CVector3* direction) {
    constexpr float kTwoPi = 6.2831854820251465f;  // TOC2 -0x6a9c
    crt::Acosf(direction->z);  // the result is not used
    const float z = direction->z;
    float yaw;
    if (z >= 1.0f) {
        yaw = 0.0f;
    } else if (z <= -1.0f) {
        yaw = 3.1415927410125732f;  // TOC2 -0x6a98
    } else {
        yaw = crt::Acosf(z);
        if (direction->x > 0.0f) yaw = kTwoPi - yaw;
        if (yaw < 0.0f) return yaw + kTwoPi;  // bge: an unordered yaw goes to the wrap test
    }
    if (yaw >= kTwoPi) yaw = yaw - kTwoPi;
    return yaw;
}


// 0x0059f160 CKHkMovableCharacter_ProbeGround_maybe: +0x68 bit 12 set, the ground under `position` probed; on a ground
// (status 0..2) `position` and `normal` take the contact's world point and normal, then the shadow ground the same (unless
// the status became 3); with no ground (status 3) a registered shadow is unregistered.
void CKHkMovableCharacter::ProbeGround(CVector3* position, CVector3* normal) {
    m_unk68 = (m_unk68 & 0xffffefffu) | 0x1000u;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_GContactIn, &m_GContactInOut, &position->x, 1);
    const int32_t status = static_cast<int32_t>(m_GContactInOut.m_eContactStatus);
    if (status < 0) return;
    if (status <= 2) {
        GroundContact_GetWorldPoint(&m_GContactInOut, position);
        GroundContact_GetWorldNormal(&m_GContactInOut, normal);
        if (m_GContactInOut.m_eContactStatus == 3) return;
        TakeShadowGround(this);
        return;
    }
    if (status == 3) UnregisterShadow(this);
}

// 0x005a02d0 CKHkMovableCharacter_GetHeadingDirection_maybe: in state 4 `out` is turned by 0.1 rad about y (in place);
// otherwise `out` = (blend of the node's at and right by +0xf4, 0, ...) * 0.5, +0xf4 reset to 0.4 first unless the
// character was stopped by a wall, a bound or a blocked cell (+0x68 bits 2, 8, 7).
void CKHkMovableCharacter::GetHeadingDirection(CVector3* out) {
    if (m_unk2c4 == 4) {
        const float c = FromBits(0x3f7eb897u);  // cos 0.1 (TOC2 -0x6a08)
        const float s = FromBits(0x3dcc7577u);  // sin 0.1 (TOC2 -0x6a00)
        const float z = out->z;
        const float x = out->x;
        out->x = ppc::fmsubs(c, x, s * z);
        out->z = ppc::fmadds(s, x, c * z);
        return;
    }
    const uint32_t flags = m_unk68;
    if ((flags & 4u) == 0 && (flags & 0x100u) == 0 && (flags & 0x80u) == 0) m_unkF4 = 0.4f;  // TOC2 -0x6a10
    const RwMatrix& m = NodeOf(this)->m_pRwFrame->modelling;  // RwFrame +0x10
    out->y = 0.0f;  // a word store
    out->x = ppc::fmadds(m_unkF4, m.right.x, (1.0f - m_unkF4) * m.at.x) * 0.5f;
    out->z = ppc::fmadds(m_unkF4, m.right.z, (1.0f - m_unkF4) * m.at.z) * 0.5f;
}

// 0x005a0498 CKHkMovableCharacter_ResetTargetIfOutOfBounds_maybe (the second argument is not read): a wanderer whose
// target left the bounds walks +0x184 along the heading from where it is instead.
void CKHkMovableCharacter::ResetTargetIfOutOfBounds() {
    const RwV3d& position = NodeOf(this)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
    const float pz = position.z;
    const float px = position.x;
    const float py = position.y;
    if (m_unk148 > 1) return;
    if (!OutsideMoveBounds(this, m_unk94.x, m_unk94.z)) return;
    CVector3 heading = {0.0f, 0.0f, 0.0f};  // BUG(original): an uninitialised stack vector (state 4 turns it in place)
    GetHeadingDirection(&heading);
    m_unk94.x = ppc::fmadds(m_unk184, heading.x, px);
    m_unk94.z = ppc::fmadds(m_unk184, heading.z, pz);
    m_unk94.y = ppc::fmadds(m_unk184, heading.y, py);
}

// 0x005a0590 CKHkMovableCharacter_ClampToMoveBounds_maybe: a wanderer's next position outside the bounds: `direction` the
// heading, +0x68 bit 8 set (bits 0, 3, 5 cleared), the walk speed and its target 0, `position` back on the node's; inside,
// bit 8 cleared.
void CKHkMovableCharacter::ClampToMoveBounds(CVector3* position, CVector3* direction) {
    if (m_unk148 > 1) return;
    if (!OutsideMoveBounds(this, position->x, position->z)) {
        m_unk68 &= 0xfffffeffu;
        return;
    }
    GetHeadingDirection(direction);
    m_unk68 = ((m_unk68 & 0xfffffeffu) | 0x100u) & 0xffffffd6u;
    m_unk7c[0] = 0.0f;  // word stores
    m_unk7c[2] = 0.0f;
    CopyNodePosition(this, position);
}

// 0x005a0698 CKHkMovableCharacter_CheckNavCellBlocked_maybe: the path-finding cell under the next position (its graph node
// remembered in +0x6c) tested in walkability mode 2 with every dynamic bit: a blocked cell turns the character (the
// heading), sets +0x68 bit 7 (bits 0, 3, 5 cleared) and keeps it where it is; an open one clears bit 7. Nothing when no
// node holds the point.
void CKHkMovableCharacter::CheckNavCellBlocked(CVector3* position, CVector3* direction) {
    CKSrvPathFinding* service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    CPFPoint point;
    point.m_unk0c = m_unk6c;
    point.m_position = *position;
    if (static_cast<uint8_t>(service->FindSectorForPoint(&point)) == 0) return;  // 0x001e5ca0
    m_unk6c = point.m_unk0c;
    float fracX;
    float fracZ;
    uint8_t cell[4];
    service->PointToCell(&point, &fracX, &fracZ, cell);  // 0x001e5148
    CPFGrid& grid = static_cast<CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[m_unk6c])->m_Sector.m_grid;
    PathFinding_SetWalkabilityMode(2);  // 0x001f1158
    grid.m_ui8DynamicMask = 0xff;
    const uint8_t palette = g_pfGridPalette[grid.GetCellFlags(cell)];  // 0x001f0fe0, the palette 0x00cea90b
    if (!PFPaletteBlocked(palette)) {
        m_unk68 &= 0xffffff7fu;
        return;
    }
    GetHeadingDirection(direction);
    m_unk68 = ((m_unk68 & 0xffffff7fu) | 0x80u) & 0xffffffd6u;
    CopyNodePosition(this, position);
}

// 0x005a08c0 CKHkMovableCharacter_CheckBlockingCollision_maybe: a cylinder (radius +0x1a8, twice as high) swept from the
// node's world position to the next position against the walls: stopped (1) keeps the world position, slid or pushed out
// (2, 3) adds the slide; either way the heading is taken and +0x68 bit 2 set (bits 0, 3, 5 cleared).
void CKHkMovableCharacter::CheckBlockingCollision(CVector3* position, CVector3* direction) {
    const RwV3d& world = FrameLtm(NodeOf(this)->m_pRwFrame)->pos;  // RwFrame +0x80
    const float sz = world.z;
    const float sx = world.x;
    const float sy = world.y;
    CLine line;
    line.m_start = {sx, sy, sz};
    line.m_VectDir.z = position->z - sz;
    line.m_VectDir.x = position->x - sx;
    line.m_VectDir.y = position->y - sy;
    CSlideGroundEdgeDatasOut out;
    std::memset(&out, 0, sizeof out);  // BUG(original): an uninitialised stack block (read only when 2 or 3 is returned)
    const float radius = m_unk1a8;
    const uint8_t result = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
                               ->ResolveSweptCylinderWalls(&line, radius, radius + radius, &out, nullptr, nullptr, 1);  // 0x0019aa68
    if (result == 1) {
        GetHeadingDirection(direction);
        position->z = sz;
        position->x = sx;
        position->y = sy;
    } else if (result == 2 || result == 3) {
        GetHeadingDirection(direction);
        position->x = position->x + out.m_v3BouncingVector.x;
        position->y = position->y + out.m_v3BouncingVector.y;
        position->z = position->z + out.m_v3BouncingVector.z;
    } else {
        return;
    }
    m_unk68 = ((m_unk68 & 0xfffffffbu) | 4u) & 0xffffffd6u;
}

// 0x005a0ab0 CKHkMovableCharacter_ProbeGroundAtTarget_maybe: +0x68 bit 12 set, the ground under the next position
// probed. On a ground (status 0 / 1) the shadow ground follows it; a step higher or lower than +0x1ec keeps the character
// where it is (heading, +0x68 bit 2), else it stands on the ground point and `up` becomes the ground's normal (Y with
// +0x140 bit 15). Status 2 / 3: heading, bit 2 (bits 0, 3, 5 cleared), kept in place, the shadow unregistered at 3.
void CKHkMovableCharacter::ProbeGroundAtTarget(CVector3* position, CVector3* direction, CVector3* up) {
    m_unk68 = (m_unk68 & 0xffffefffu) | 0x1000u;
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_GContactIn, &m_GContactInOut, &position->x, 1);
    const int32_t status = static_cast<int32_t>(m_GContactInOut.m_eContactStatus);
    if (status < 0) return;
    if (status <= 1) {
        CVector3 point;
        GroundContact_GetWorldPoint(&m_GContactInOut, &point);
        if (m_GContactInOut.m_eContactStatus != 3) TakeShadowGround(this);
        const float step = std::fabs(position->y - point.y);  // the sign bit cleared through memory
        if (m_unk1ec < step) {
            m_unk68 = (m_unk68 & 0xfffffffbu) | 4u;
            CopyNodePosition(this, position);
            GetHeadingDirection(direction);
            return;
        }
        m_unk68 &= 0xfffffffbu;
        position->x = point.x;
        position->z = point.z;
        position->y = point.y;
        if ((m_unk140 & 0x8000u) != 0) {
            *up = kAxisY;  // 0x00c50d40
        } else {
            *up = m_GContactInOut.m_Normal;
        }
        return;
    }
    if (status > 3) return;
    GetHeadingDirection(direction);
    m_unk68 = ((m_unk68 & 0xfffffffbu) | 4u) & 0xffffffd6u;
    CopyNodePosition(this, position);
    if (m_GContactInOut.m_eContactStatus == 3) UnregisterShadow(this);
}

// 0x005a0e50 CKHkMovableCharacter_PickRandomWanderTarget_maybe: a new target at a random distance (+0x184..+0x188) and a
// random angle (+-+0x18c) from the heading `at`, at a random height in the bounds unless the character keeps to the
// ground (+0x140 bit 0); a free wanderer is pushed back inside the bounds (PushTargetInsideBounds), a grounded one whose
// target left them walks +0x184 along the heading instead.
void CKHkMovableCharacter::PickRandomWanderTarget(const CVector3* at) {
    const float distance = ppc::fmadds(RandUnit(), m_unk188 - m_unk184, m_unk184);
    const float draw = static_cast<float>(static_cast<uint16_t>(Rand_Int()));
    // (rand & 0xffff) * -1/32767.5 + 1 (TOC2 -0x69f8 0xb8000080): [-1, 1] times the angle +0x18c.
    const float angle = ppc::fmadds(draw, FromBits(0xb8000080u), 1.0f) * m_unk18c;
    CopyNodePosition(this, &m_unk94);
    const float c = GameCosf(angle);
    const float s = GameSinf(angle);
    const float atZ = at->z;
    const float sz = s * atZ;
    const float cz = c * atZ;
    const float x0 = m_unk94.x;
    const float y0 = m_unk94.y;
    const float z0 = m_unk94.z;
    m_unk94.y = y0 + 0.0f;  // TOC2 -0x6abc
    m_unk94.x = ppc::fmadds(distance, ppc::fmsubs(c, at->x, sz), x0);
    m_unk94.z = ppc::fmadds(distance, ppc::fmadds(s, at->x, cz), z0);
    if ((m_unk140 & 1u) == 0) {
        const float low = m_unkA4.y;
        const float high = m_unkB0.y;
        m_unk94.y = ppc::fmadds(high - low, RandUnit(), low);
    }
    if ((m_unk140 & 1u) == 0) {
        PushTargetInsideBounds(at);  // 0x0059cc60
        return;
    }
    const RwV3d& position = NodeOf(this)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
    const float pz = position.z;
    const float px = position.x;
    const float py = position.y;
    if (m_unk148 > 1) return;
    if (!OutsideMoveBounds(this, m_unk94.x, m_unk94.z)) return;
    CVector3 heading = {0.0f, 0.0f, 0.0f};  // BUG(original): an uninitialised stack vector (state 4 turns it in place)
    GetHeadingDirection(&heading);
    m_unk94.x = ppc::fmadds(m_unk184, heading.x, px);
    m_unk94.z = ppc::fmadds(m_unk184, heading.z, pz);
    m_unk94.y = ppc::fmadds(m_unk184, heading.y, py);
}

// 0x005a1b28 CKHkMovableCharacter_TurnTowardDirectionFlat_maybe: the yaw approach (+0x88) aimed at the direction's yaw
// (from its clamped x and z) and stepped; the node's at = (-sin, 0, cos) and right = (cos, 0, sin) of the new yaw.
// Returns whether the yaw reached its target.
uint8_t CKHkMovableCharacter::TurnTowardDirectionFlat(const CVector3* direction) {
    constexpr float kTwoPi = 6.2831854820251465f;  // TOC2 -0x6a9c
    float x = direction->x;
    const float z = direction->z;
    if (x <= -1.0f) {
        x = -1.0f;
    } else if (x >= 1.0f) {
        x = 1.0f;
    }
    float yaw;
    bool wrap = true;
    if (z <= -1.0f) {
        crt::Acosf(-1.0f);  // the result is not used
        yaw = 3.1415927410125732f;  // TOC2 -0x6a98
    } else if (z >= 1.0f) {
        crt::Acosf(1.0f);
        yaw = 0.0f;
    } else {
        crt::Acosf(z);  // computed twice, the first result not used
        yaw = crt::Acosf(z);
        if (x > 0.0f) yaw = kTwoPi - yaw;
        if (yaw < 0.0f) {  // bge: an unordered yaw goes to the wrap test
            yaw = yaw + kTwoPi;
            wrap = false;
        }
    }
    if (wrap && yaw >= kTwoPi) yaw = yaw - kTwoPi;
    m_unk88[0] = yaw;
    FloatApproach_StepAngle(m_pClock->m_afDeltaTime[0], m_unk88);  // 0x00243748 (returns the current angle +0x90)
    const float current = m_unk88[2];
    const float c = GameCosf(current);
    const float s = GameSinf(current);
    RwFrame* frame = NodeOf(this)->m_pRwFrame;
    frame->modelling.at.x = -s;
    frame->modelling.at.z = c;
    frame->modelling.at.y = 0.0f;  // a word store
    frame->modelling.flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(frame);
    frame = NodeOf(this)->m_pRwFrame;
    frame->modelling.right.x = c;
    frame->modelling.right.z = s;
    frame->modelling.right.y = 0.0f;
    frame->modelling.flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(frame);
    return current == m_unk88[0] ? 1 : 0;
}

// 0x005a1f18 CKHkMovableCharacter_TurnTowardDirectionAligned_maybe: as TurnTowardDirectionFlat (the direction's three
// components clamped to [-1, 1]), the node then built from `up` (normalised when the character is scaled, +0x1bc not 1)
// and the forward (-sin, 0, cos) (CSGMovable_SetBasisFromUpAndForward). Returns whether the yaw reached its target.
uint8_t CKHkMovableCharacter::TurnTowardDirectionAligned(const CVector3* direction, const CVector3* up) {
    constexpr float kTwoPi = 6.2831854820251465f;  // TOC2 -0x6a9c
    const auto clamp = [](float v) {
        if (v <= -1.0f) return -1.0f;
        if (v >= 1.0f) return 1.0f;
        return v;
    };
    const float x = clamp(direction->x);
    clamp(direction->y);  // clamped and stored on the stack, not read
    const float z = clamp(direction->z);
    crt::Acosf(z);  // the result is not used
    float yaw;
    bool wrap = true;
    if (z >= 1.0f) {
        yaw = 0.0f;
    } else if (z <= -1.0f) {
        yaw = 3.1415927410125732f;  // TOC2 -0x6a98
    } else {
        yaw = crt::Acosf(z);
        if (x > 0.0f) yaw = kTwoPi - yaw;
        if (yaw < 0.0f) {  // bge: an unordered yaw goes to the wrap test
            yaw = yaw + kTwoPi;
            wrap = false;
        }
    }
    if (wrap && yaw >= kTwoPi) yaw = yaw - kTwoPi;
    m_unk88[0] = yaw;
    FloatApproach_StepAngle(m_pClock->m_afDeltaTime[0], m_unk88);  // 0x00243748
    const float current = m_unk88[2];
    const float c = GameCosf(current);
    const float s = GameSinf(current);
    const CVector3 forward = {-s, 0.0f, c};
    CVector3 axis = *up;
    if (m_unk1bc != 1.0f) {
        const float length = MathSqrtf(ppc::fmadds(axis.z, axis.z, ppc::fmadds(axis.x, axis.x, axis.y * axis.y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            axis.z = axis.z * inverse;
            axis.x = axis.x * inverse;
            axis.y = axis.y * inverse;
        }
    }
    NodeOf(this)->SetBasisFromUpAndForward(&axis, &forward);  // 0x000d0a30
    return current == m_unk88[0] ? 1 : 0;
}

// 0x005a4998 CKHkMovableCharacter_MoveAlongPath_maybe: the character on its path (+0x2a0, a CKFlaggedPath) at the signed
// distance +0x180 (negative: walking back). The walk speed approaches `speed` (its acceleration `acceleration`) and the
// distance moves by it: at the end the path is walked back (+0x140 bit 7) or wraps round; at 0 it turns forward again.
// The steps (+0x2a4, a CKPathStepCpnt) crossed this frame count into +0x24; past the count +0x25 the character stops on
// the step (a random action due: +0x68 bits 1 and 5). Without steps the random action timer runs (+0x140 bit 1). The node
// takes the path's point (on the ground with +0x140 bit 0) and turns along the path (up Y with +0x140 bit 15).
void CKHkMovableCharacter::MoveAlongPath(float speed, float acceleration) {
    CVector3 up = kAxisY;  // 0x00c50d40
    CKFlaggedPath* path = static_cast<CKFlaggedPath*>(m_unk2a0[0]);
    const float length = static_cast<IKPath*>(path->m_pPath)->GetLength();  // vt+0x5c
    bool backwards = false;
    if (m_unk180 < 0.0f) {
        m_unk180 = -m_unk180;
        backwards = true;
    }
    m_unk7c[1] = acceleration;
    const float walk = FloatApproach_Step(m_pClock->m_afDeltaTime[0], m_unk7c);  // 0x002436e8
    if ((m_unk68 & 2u) != 0 && walk == 0.0f) m_unk68 = ((m_unk68 & 0xfffffffeu) | 1u) & 0xfffffffdu;
    float distance;
    CVector3 point;
    CVector3 forward;
    bool reverse = backwards;  // r23
    if (!backwards) {
        distance = ppc::fmadds(walk, m_pClock->m_afDeltaTime[0], m_unk180);
    } else {
        distance = m_unk180 - walk * m_pClock->m_afDeltaTime[0];
    }
    if (distance >= length) {
        path->SetDistanceAndGetPosition(length, &point, &forward, &up);  // 0x000c4eb8
        if ((m_unk140 & 0x80u) != 0) {
            distance = -length;
        } else {
            distance = distance - length;
            CVector3 start;
            path->SetDistanceAndGetPositionUp(0.0f, &start, nullptr, nullptr);  // 0x000c4d88 (the point is not read)
        }
    } else if (distance <= 0.0f) {
        distance = 0.0f;
        reverse = false;
    }
    path->SetDistanceAndGetPosition(std::fabs(distance), &point, &forward, &up);  // the sign bit cleared through memory
    if ((m_unk140 & 2u) != 0) {
        CKPathStepCpnt* steps = static_cast<CKPathStepCpnt*>(m_unk2a0[1]);
        if (steps->m_ui32Count != 0) {
            const uint8_t before = m_unk24;
            const uint32_t crossed = steps->CountStepsInRange(m_unk180, distance);  // 0x0059c6f8
            m_unk24 = static_cast<uint8_t>(crossed + before);
            const uint8_t count = m_unk24;
            if (m_unk25 < count) {
                if (count <= static_cast<CKPathStepCpnt*>(m_unk2a0[1])->m_ui32Count) {
                    // Back on the step (0.001 past it).
                    distance = static_cast<CKPathStepCpnt*>(m_unk2a0[1])->m_pSteps[count - 1u] + 0.001f;  // TOC2 -0x699c
                    path->SetDistanceAndGetPosition(std::fabs(distance), &point, &forward, &up);
                }
                m_unk68 = ((((m_unk68 & 0xfffffffdu) | 2u) & 0xffffffdfu) | 0x20u);
            }
        } else if (m_unk78 > 0.0f) {  // ble: an unordered timer draws
            m_unk78 = m_unk78 - m_pClock->m_afDeltaTime[0];
        } else {
            const uint32_t flags = m_unk68;
            if ((flags & 2u) == 0 && (flags & 0x20u) == 0) {
                if (RandUnit() <= m_unk190) {
                    m_unk68 = ((((m_unk68 & 0xfffffffdu) | 2u) & 0xffffffdfu) | 0x20u);
                } else {
                    const float unit = RandUnit();
                    m_unk78 = ppc::fmadds(unit, m_unk188 - m_unk184, m_unk184);
                    m_unk68 &= 0xffffffdfu;
                }
            }
        }
    }
    if ((m_unk68 & 2u) != 0) {
        m_unk7c[0] = 0.0f;  // a word store
    } else {
        m_unk7c[0] = speed;
    }
    if ((m_unk140 & 1u) != 0) ProbeGround(&point, &up);  // 0x0059f160
    if (!reverse) {
        m_unk180 = distance;
    } else {
        m_unk180 = -distance;
        forward.x = -forward.x;
        forward.y = -forward.y;
        forward.z = -forward.z;
    }
    SetNodePosition(NodeOf(this), point.x, point.y, point.z);
    if ((m_unk140 & 0x8000u) != 0) {
        NodeOf(this)->SetBasisFromUpAndForward(&kAxisY, &forward);  // 0x000d0a30
    } else {
        NodeOf(this)->SetBasisFromUpAndForward(&up, &forward);
    }
}

// 0x005a4ef8 CKHkMovableCharacter_State1 (on a path): entering draws the random action timer; leaving clears +0x68 bit 5;
// the tick walks the path at +0x178 (acceleration +0x17c), or runs the random action timer when the speed is 0.
uint8_t CKHkMovableCharacter::State1(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        const float unit = RandUnit();
        m_unk78 = ppc::fmadds(unit, m_unk188 - m_unk184, m_unk184);
        return 1;
    }
    if (phase == 2) {
        m_unk68 &= 0xffffffdfu;
        return 1;
    }
    if (phase != 0) return 1;
    m_unk65 = 1;
    if (m_unk178 == 0.0f) {  // against a word 0 on the stack
        UpdateRandomActionTimer();
    } else {
        MoveAlongPath(m_unk178, m_unk17c);
    }
    return 1;
}

// 0x005a5010 CKHkMovableCharacter_State5 (hit): entering clears +0x68 bit 3 and stops the walk. The tick: hit by another
// movable character (+0x70, key 0x3402) the character turns away from it (the turn direction +0xc8 kept while +0xbc, its
// old heading, is set) and ends the hit (+0x68 bit 4) once turned. Otherwise, with +0x140 bit 8 and a hitter, the first
// tick (+0x68 bit 6) turns away from it, then plays the hit animation (+0x65 3, sound 2); after the animation (+0x140
// bit 10) it turns away again (bit 8) or keeps its heading, and wanders off (PickRandomWanderTarget) unless it stands.
uint8_t CKHkMovableCharacter::State5(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        m_unk68 &= 0xfffffff7u;
        m_unk7c[0] = 0.0f;  // word stores
        m_unk7c[2] = 0.0f;
        return 5;
    }
    if (phase != 0) return 5;
    // The turn away from the hitter: the old heading kept in +0xbc (while it is the null vector), the direction from the
    // hitter's node to this one into +0xc8.
    const auto awayFromHitter = [this]() {
        if (m_unkBC.x == kNullVector.x && m_unkBC.y == kNullVector.y && m_unkBC.z == kNullVector.z) {
            m_unkBC = ToVector(NodeOf(this)->m_pRwFrame->modelling.at);  // RwFrame +0x30
            const RwV3d& self = NodeOf(this)->m_pRwFrame->modelling.pos;
            const RwV3d& other =
                static_cast<CSGMovable*>(static_cast<IKHook*>(m_unk70)->m_pKGLObject)->m_pRwFrame->modelling.pos;
            m_unkC8.x = self.x - other.x;
            m_unkC8.y = self.y - other.y;
            m_unkC8.z = self.z - other.z;
            const float length =
                MathSqrtf(ppc::fmadds(m_unkC8.z, m_unkC8.z, ppc::fmadds(m_unkC8.x, m_unkC8.x, m_unkC8.y * m_unkC8.y)));
            if (length != 0.0f) {
                const float inverse = 1.0f / length;
                m_unkC8.z = inverse * m_unkC8.z;
                m_unkC8.x = inverse * m_unkC8.x;
                m_unkC8.y = inverse * m_unkC8.y;
            }
        }
    };
    if (m_unk70 != nullptr && static_cast<uint8_t>(m_unk70->IsKindOfClass(0x3402)) != 0) {  // vt+0x08
        const CVector3 up = ToVector(NodeOf(this)->m_pRwFrame->modelling.up);  // RwFrame +0x20
        awayFromHitter();
        if (TurnTowardDirectionAligned(&m_unkC8, &up) == 0) return 5;
        m_unkBC = kNullVector;
        m_unk68 &= 0xffffffefu;
        return 5;
    }
    const CVector3 up = ToVector(NodeOf(this)->m_pRwFrame->modelling.up);
    const uint32_t properties = m_unk140;
    const bool turns = (properties & 0x100u) != 0;
    m_unk88[1] = 6.2831854820251465f;  // TOC2 -0x697c
    if (turns && (m_unk68 & 0x40u) != 0 && m_unk70 != nullptr) {
        awayFromHitter();
        if (TurnTowardDirectionAligned(&m_unkC8, &up) == 0) return 5;
        m_unk65 = 3;
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk13c);
        if (sounds != nullptr && CKSoundDictionaryID_GetSound(sounds, 2) != nullptr) {
            CKSound_Play(0.0f, CKSoundDictionaryID_GetSound(sounds, 2));
        }
        m_unk68 &= 0xffffffbfu;
        return 5;
    }
    if (m_unk65 != 3) {
        if (!turns) {
            m_unk65 = 3;
            return 5;
        }
        if (TurnTowardDirectionAligned(&m_unkBC, &up) == 0) return 5;
        m_unkBC = kNullVector;
        m_unk68 &= 0xffffffefu;
        return 5;
    }
    uint32_t flags = properties;
    if ((flags & 0x400u) != 0) {
        if (!static_cast<CAnimatedNode*>(m_pKGLObject)->IsAnimEndReached(m_pClock->m_afDeltaTime[0])) return 5;  // 0x000ca368
        flags = m_unk140;
    }
    CVector3 direction;
    if ((flags & 0x100u) != 0 && m_unk70 != nullptr) {
        const RwV3d& self = NodeOf(this)->m_pRwFrame->modelling.pos;
        const RwV3d& other = static_cast<CSGMovable*>(static_cast<IKHook*>(m_unk70)->m_pKGLObject)->m_pRwFrame->modelling.pos;
        direction.y = self.y - other.y;
        direction.x = self.x - other.x;
        direction.z = self.z - other.z;
        NormaliseYxz(&direction);
    } else {
        direction = ToVector(NodeOf(this)->m_pRwFrame->modelling.at);
        m_unk68 &= 0xffffffefu;
    }
    if (m_unk178 != 0.0f) PickRandomWanderTarget(&direction);  // 0x005a0e50
    m_unk65 = 0;
    return 5;
}

// 0x005a5698 CKHkMovableCharacter_State4 (looking at an entity): entering plays sound 1 once and loops 5 (3 stopped), and
// aims the yaw at the entity (+0x74; +0x78 the look duration +0x18c on a path); leaving stops 5. The tick (+0x65 2): a
// character that stands ends the look with the animation (+0x140 bit 10); on a path it walks it at +0x19c / +0x1a0 for
// the look duration; else it turns (2 pi per second) to the entity and walks towards it at +0x19c (acceleration +0x1a0),
// through the bounds, the blocked cells, the walls and the ground as State0, the look ending at the bounds or a wall.
uint8_t CKHkMovableCharacter::State4(IKTime* /*clock*/, int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk13c);
        if (sounds != nullptr) {
            if (CKSoundDictionaryID_GetSound(sounds, 1) != nullptr) CKSound_Play(0.0f, CKSoundDictionaryID_GetSound(sounds, 1));
            StopSound(sounds, 3);
            if (CKSoundDictionaryID_GetSound(sounds, 5) != nullptr) CKSound_SetLoop(CKSoundDictionaryID_GetSound(sounds, 5), 1);
            if (CKSoundDictionaryID_GetSound(sounds, 5) != nullptr) CKSound_Play(0.0f, CKSoundDictionaryID_GetSound(sounds, 5));
        }
        if (m_unk2a0[0] != nullptr) m_unk78 = m_unk18c;
        m_unk88[0] = m_unk74;
        return 4;
    }
    if (phase == 2) {
        CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk13c);
        if (sounds != nullptr) StopSound(sounds, 5);
        return 4;
    }
    if (phase != 0) return 4;
    CVector3 up = ToVector(NodeOf(this)->m_pRwFrame->modelling.up);  // RwFrame +0x20
    m_unk65 = 2;
    if (m_unk178 == 0.0f) {
        if ((m_unk140 & 0x400u) != 0 &&
            !static_cast<CAnimatedNode*>(m_pKGLObject)->IsAnimEndReached(m_pClock->m_afDeltaTime[0])) {  // 0x000ca368
            return 4;
        }
        m_unk68 &= 0xfffffff7u;
        return 4;
    }
    if (m_unk2a0[0] != nullptr) {
        if (!(m_unk78 >= 0.0f)) {
            m_unk68 &= 0xfffffff7u;
            return 4;
        }
        MoveAlongPath(m_unk19c, m_unk1a0);
        m_unk78 = m_unk78 - m_pClock->m_afDeltaTime[0];
        return 4;
    }
    m_unk7c[0] = m_unk19c;
    m_unk7c[1] = m_unk1a0;
    const float walk = FloatApproach_Step(m_pClock->m_afDeltaTime[0], m_unk7c);  // 0x002436e8
    m_unk88[1] = 6.2831854820251465f;  // TOC2 -0x697c
    FloatApproach_StepAngle(m_pClock->m_afDeltaTime[0], m_unk88);  // 0x00243748
    const float yaw = m_unk88[2];
    const float c = GameCosf(yaw);
    const float s = GameSinf(yaw);
    CVector3 forward = {-s, 0.0f, c};
    RwFrame* frame = NodeOf(this)->m_pRwFrame;
    frame->modelling.at.x = forward.x;
    frame->modelling.at.z = c;
    frame->modelling.at.y = 0.0f;  // a word store
    frame->modelling.flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(frame);
    frame = NodeOf(this)->m_pRwFrame;
    frame->modelling.right.x = forward.z;
    frame->modelling.right.z = -forward.x;
    frame->modelling.right.y = 0.0f;
    frame->modelling.flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(frame);
    if (m_unk88[0] != yaw) return 4;
    const float step = walk * m_pClock->m_afDeltaTime[0];
    const RwMatrix& m = NodeOf(this)->m_pRwFrame->modelling;
    CVector3 next;
    next.z = ppc::fmadds(step, m.at.z, m.pos.z);
    next.x = ppc::fmadds(step, m.at.x, m.pos.x);
    next.y = ppc::fmadds(step, m.at.y, m.pos.y);
    const auto endLook = [this]() {
        m_unk68 &= 0xfffffff7u;
        m_unk7c[2] = m_unk178;
        m_unk7c[0] = m_unk178;
    };
    if (m_unk148 <= 1 && (m_unk284.x < next.x || next.z > m_unk284.z || m_unk278.x > next.x || !(next.z >= m_unk278.z))) {
        endLook();
    }
    ClampToMoveBounds(&next, &forward);  // 0x005a0590
    uint32_t properties = m_unk140;
    if ((properties & 0x80u) != 0) {
        CheckNavCellBlocked(&next, &forward);  // 0x005a0698
        properties = m_unk140;
    }
    if ((properties & 0x20000u) == 0) {
        CheckBlockingCollision(&next, &forward);      // 0x005a08c0
        ProbeGroundAtTarget(&next, &forward, &up);    // 0x005a0ab0
        if ((m_unk68 & 4u) != 0) endLook();
        if ((m_unk140 & 0x8000u) == 0) {
            NormaliseYxz(&forward);
            const float direction = DirectionToYaw(&forward);  // 0x0059dde0
            m_unk88[2] = direction;
            const uint32_t flags = m_unk68;
            if ((flags & 0x80u) != 0 || (flags & 0x100u) != 0) m_unk88[0] = direction;
            NodeOf(this)->SetBasisFromUpAndForward(&up, &forward);  // 0x000d0a30
        }
    } else {
        next.y = m_unk278.y;
        m_shadowPos = next;
        m_shadowNormal = kAxisY;
        m_unkEC = 0;
    }
    SetNodePosition(NodeOf(this), next.x, next.y, next.z);
    return 4;
}

// 0x005a6ce8 CKHkMovableCharacter_MoveToWithPathfinding_maybe: the path-finding component aimed at `target` (a new request
// when it changed) and updated from `position`; towards its waypoint (result bit 1; the height kept) the character walks
// at the speed +0x12c, accelerating by +0x1e4 up to +0x1e0, and lands on the ground under it (`up` the ground's normal, Y
// with +0x140 bit 15; the shadow ground follows). 0 when the request failed, the path was replanned, the waypoint is the
// position, or there is no ground under it.
uint8_t CKHkMovableCharacter::MoveToWithPathfinding(const CVector3* target, CVector3* position, CVector3* up, IKTime* clock) {
    CVector3 goal = *target;
    const CVector3& last = m_PFCpnt.m_ptTargetPosition.m_position;  // +0x250
    if (!(last.x == goal.x && last.y == goal.y && last.z == goal.z)) {
        if (m_PFCpnt.RequestPathTo(&goal, -1) == 0) return 0;  // 0x001e1520
    }
    const uint32_t result = m_PFCpnt.Update(position);  // 0x001e2b28
    if ((result & 1u) != 0) return 0;
    bool direct = true;
    if ((result & 2u) != 0) {
        goal.x = m_PFCpnt.m_vCurrentTarget.x;
        goal.y = position->y;
        goal.z = m_PFCpnt.m_vCurrentTarget.z;
        direct = false;
    }
    if (goal.x == position->x && goal.y == position->y && goal.z == position->z) return 0;
    if (!direct) {
        float dx = goal.x - position->x;
        float dy = goal.y - position->y;
        float dz = goal.z - position->z;
        float length = MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            dz = dz * inverse;
            dx = dx * inverse;
            dy = dy * inverse;
        } else {
            length = 0.0f;
        }
        float walk = ppc::fmadds(m_unk1c8[7], clock->m_afDeltaTime[0], m_unk12c);  // +0x1e4, +0x12c
        if (!(m_unk1c8[6] > walk)) walk = m_unk1c8[6];                                 // +0x1e0
        m_unk12c = walk;
        const float step = walk * clock->m_afDeltaTime[0];
        if (!(length < step)) {  // bge: an unordered length steps
            position->z = ppc::fmadds(step, dz, position->z);
            position->x = ppc::fmadds(step, dx, position->x);
            position->y = ppc::fmadds(step, dy, position->y);
        } else {
            position->x = goal.x;
            position->z = goal.z;
            position->y = goal.y;
        }
    }
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_GContactIn, &m_GContactInOut, &position->x, 1);
    if (m_GContactInOut.m_eContactStatus > 1) return 0;
    GroundContact_GetWorldPoint(&m_GContactInOut, position);
    if (m_GContactInOut.m_eContactStatus != 3) TakeShadowGround(this);
    if ((m_unk140 & 0x8000u) != 0) {
        *up = kAxisY;
    } else {
        *up = m_GContactInOut.m_Normal;
    }
    return 1;
}

// 0x005a7080 CKHkMovableCharacter_TurnTowardPoint_maybe: `point` 1: towards the point (the flat direction from the
// node); 0: `target` is the direction. The node's at moves towards it by +0x1dc per second (InvSqrt step) and the node
// is turned (`up` normalised in place). Returns 1 for a null direction; otherwise BUG(original): the new at is compared
// with itself +- 0.02 instead of with the goal, so 1 unless a component is not a number.
uint8_t CKHkMovableCharacter::TurnTowardPoint(const CVector3* target, CVector3* up, IKTime* clock, uint8_t point) {
    float gx;
    float gy;
    float gz;
    if (point != 0) {
        const RwV3d& position = NodeOf(this)->m_pRwFrame->modelling.pos;  // RwFrame +0x40
        gx = target->x - position.x;
        gz = target->z - position.z;
        gy = 0.0f;
        const float length = MathSqrtf(ppc::fmadds(gz, gz, ppc::fmadds(gx, gx, 0.0f)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            gz = gz * inverse;
            gx = gx * inverse;
            gy = inverse * 0.0f;
        }
    } else {
        gz = target->z;
        gx = target->x;
        gy = target->y;
    }
    if (kNullVector.x == gx && kNullVector.y == gy && kNullVector.z == gz) return 1;
    const float rate = m_unk1c8[5];  // +0x1dc
    const float dt = clock->m_afDeltaTime[0];
    const RwV3d& at = NodeOf(this)->m_pRwFrame->modelling.at;  // RwFrame +0x30
    float nx = at.x;
    float nz = at.z;
    float ny = at.y;
    if (!(nx == gx && ny == gy && nz == gz)) {
        const float dy = gy - ny;
        const float dx = gx - nx;
        const float step = rate * dt;
        const float dz = gz - nz;
        const float distance2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (step * step > distance2) {
            nx = gx;
            nz = gz;
            ny = gy;
        } else {
            const float scale = step * rwInvSqrt(distance2);  // 0x000114d8 Math_InvSqrtf
            nz = ppc::fmadds(dz, scale, nz);
            nx = ppc::fmadds(dx, scale, nx);
            ny = ppc::fmadds(dy, scale, ny);
        }
    }
    CVector3 next = {nx, ny, nz};
    NormaliseYxz(&next);
    if (next.x == kNullVector.x && next.y == kNullVector.y && next.z == kNullVector.z) next = {gx, gy, gz};
    NormaliseYxz(up);
    NodeOf(this)->SetOrientationFromAtUp(&next, up);  // 0x000d0918
    const float margin = 0.02f;  // TOC2 -0x6964
    if (!(next.x - margin <= next.x) || !(next.x + margin >= next.x)) return 0;
    if (!(next.y - margin <= next.y) || !(next.y + margin >= next.y)) return 0;
    if (!(next.z - margin <= next.z)) return 0;
    return next.z <= next.z + margin ? 1 : 0;
}

// 0x005a7458 CKHkMovableCharacter_State6 (a hero came near), sub-state in m_bitArray bits 17-18: 0 waits (the timer +0x104
// up to +0x1d4 with +0x140 bit 19) turned towards the focused hero, then goes back (2) when the hero is +0x1c8 away; 1
// walks to the hero with the path finder (stops within +0x1cc, or 2 beyond +0x1d0 from home or +0x1c8 from the hero);
// 2 walks home (with bit 19, for at most +0x1d8 seconds) and turns back to the remembered heading, which ends the state
// (+0x68 bit 14 cleared). Entering remembers the pose (+0x108 / +0x114 / +0x120) and sets the path finder there; leaving
// puts the node back.
uint8_t CKHkMovableCharacter::State6(IKTime* clock, int32_t phase, uint8_t /*other*/) {
    const auto setSub = [this](uint32_t sub) { m_bitArray = (m_bitArray & 0xfff9ffffu) | (sub << 17); };
    if (phase == 1) {
        const RwMatrix& m = NodeOf(this)->m_pRwFrame->modelling;
        m_unk108.x = m.pos.x;
        m_unk108.y = m.pos.y;
        m_unk108.z = m.pos.z;
        m_unk114.x = m.at.x;
        m_unk114.z = m.at.z;
        m_unk114.y = m.at.y;
        m_unk120.x = m.up.x;
        m_unk120.z = m.up.z;
        m_unk120.y = m.up.y;
        setSub((m_unk140 & 0x80000u) != 0 ? 1u : 0u);
        m_unk12c = 0.0f;  // word stores
        m_unk104 = 0.0f;
        m_PFCpnt.SetDestination(&m_unk108);  // 0x001e3a40 CKPathFindingCpnt_ResetCurrentPosition
        return 6;
    }
    if (phase == 2) {
        SetNodePosition(NodeOf(this), m_unk108.x, m_unk108.y, m_unk108.z);
        NormaliseYxz(&m_unk114);
        NormaliseYxz(&m_unk120);
        NodeOf(this)->SetOrientationFromAtUp(&m_unk114, &m_unk120);  // 0x000d0918
        return 6;
    }
    if (phase != 0) return 6;
    CVector3 position;
    CopyNodePosition(this, &position);
    CVector3 up = ToVector(NodeOf(this)->m_pRwFrame->modelling.up);  // RwFrame +0x20
    const auto distance = [](const CVector3& a, const CVector3& b) {
        const float dy = a.y - b.y;
        const float dx = a.x - b.x;
        const float dz = a.z - b.z;
        return MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    };
    const auto heroPosition = []() {
        const RwV3d& p = FrameLtm(FocusedHeroNode(HeroGroup())->m_pRwFrame)->pos;  // RwFrame +0x80 (not null-checked)
        return ToVector(p);
    };
    const uint32_t sub = (m_bitArray >> 17) & 3u;
    if (sub == 1) {
        const CVector3 hero = heroPosition();
        if (MoveToWithPathfinding(&hero, &position, &up, clock) == 0) setSub(2);  // 0x005a6ce8
        TurnTowardPoint(&position, &up, clock, 1);                               // 0x005a7080
        bool keep;
        if (m_unk1c8[1] >= distance(position, hero)) {  // +0x1cc
            keep = false;
        } else {
            const uint32_t properties = m_unk140;
            keep = !(((properties & 8u) != 0 || (properties & 0x10u) != 0 || (properties & 0x20u) != 0) &&
                     (m_unk68 & 0x10u) != 0);
        }
        if (keep) {
            SetNodePosition(NodeOf(this), position.x, position.y, position.z);
            m_unk65 = 1;
        } else {
            setSub(0);
        }
        // From home: x first (fmuls y, fmadds x, fmadds z).
        const float dx = position.x - m_unk108.x;
        const float dy = position.y - m_unk108.y;
        const float dz = position.z - m_unk108.z;
        const float home = MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
        if (m_unk1c8[2] <= home || m_unk1c8[0] <= distance(position, hero)) {  // +0x1d0, +0x1c8
            setSub(2);
            m_unk104 = 0.0f;
        }
        return 6;
    }
    if (sub == 0) {
        const float timer = m_unk104;
        if ((m_unk140 & 0x80000u) != 0 && !(timer < m_unk1c8[3])) {  // +0x1d4
            setSub(2);
            m_unk104 = 0.0f;
            return 6;
        }
        m_unk104 = timer + clock->m_afDeltaTime[0];
        const CVector3 hero = heroPosition();
        TurnTowardPoint(&hero, &up, clock, 1);
        m_unk65 = 4;
        if ((m_unk140 & 0x80000u) != 0) return 6;
        if (m_unk1c8[0] <= distance(position, hero)) setSub(2);
        return 6;
    }
    if (sub != 2) return 6;
    const bool walksHome = ((m_unk140 >> 19) & 1u) != 0;
    bool turnBack = !walksHome;
    if (walksHome) {
        const CVector3 home = m_unk108;
        MoveToWithPathfinding(&home, &position, &up, clock);
        const float timer = m_unk104;
        if (m_unk1c8[4] <= timer) {  // +0x1d8
            position = m_unk108;
            turnBack = true;
        } else {
            m_unk104 = timer + clock->m_afDeltaTime[0];
        }
        if (!(distance(position, m_unk108) < 0.1f)) {  // TOC2 -0x6960; bge: unordered walks on
            m_unk65 = 1;
            TurnTowardPoint(&position, &up, clock, 1);
        } else {
            turnBack = true;
        }
        SetNodePosition(NodeOf(this), position.x, position.y, position.z);
    }
    if (!turnBack) return 6;
    if (TurnTowardPoint(&m_unk114, &up, clock, 0) != 0) m_unk68 &= 0xffffbfffu;
    m_unk65 = 0;
    return 6;
}
