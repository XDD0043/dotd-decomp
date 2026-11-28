// CKHkS08Sparx.cpp - reconstructed original translation unit 0x3f4108-0x3f6dc0 (GAME_TOC1, main_toc1), 45 functions, 38 live.
// Primary class: CKHkS08Sparx  key 0x3282  category Hook  size 0xd4  vtable 0xb24be8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3f4108  CKHkS08Sparx_Delete
//   [x] 0x3f4158  CKHkS08Sparx_Construct  [dead]
//   [ ] 0x3f41d8  CKHkS08Sparx_ResetRuntime_2  [dead]
//   [x] 0x3f4250  CKHkS08Sparx_Stop
//   [x] 0x3f4258  CKHkS08Sparx_Pause
//   [x] 0x3f4260  CKHkS08Sparx_Resume
//   [x] 0x3f4268  CKHkS08Sparx_SetTarget_maybe
//   [x] 0x3f4318  CKHkS08Sparx_StopMoveUpdaterIfCurrent_maybe
//   [ ] 0x3f4378  CKHkS08Sparx_AddNodeAnimTime_maybe  [dead]
//   [ ] 0x3f43a0  CKHkS08Sparx_ResolveWallCollision_maybe  [dead]
//   [ ] 0x3f44d0  CKHkS08Sparx_ProbeGround_maybe  [dead]
//   [x] 0x3f4540  CKHkS08Sparx_PostLoad
//   [x] 0x3f4598  CKHkS08Sparx_Save
//   [x] 0x3f45c0  CKHkS08Sparx_RecursiveRegistration
//   [x] 0x3f45e8  CKHkS08Sparx_Destroy
//   [x] 0x3f4610  CKHkS08Sparx_DeleteArray
//   [x] 0x3f46b0  CKHkS08Sparx_SetDirectionVec_maybe
//   [x] 0x3f46d0  RegisterCKHkS08SparxClass (RegisterAllClasses: ClassTable.inc)
//   [x] 0x3f4758  _GLOBAL__D_3f4758 (RegisterCKHkS08SparxClass(0, 0xffff): nothing)
//   [x] 0x3f4768  _GLOBAL__I_3f4768 (RegisterCKHkS08SparxClass(1, 0xffff))
//   [ ] 0x3f4778  CKHkS08Sparx_Construct_2  [dead]
//   [x] 0x3f47f8  CKHkS08Sparx_ResetMoveTargetToCurrentPosition_maybe
//   [x] 0x3f4850  CKHkS08Sparx_SetMoveGoalPosDirFloat70_maybe
//   [x] 0x3f48a8  CKHkS08Sparx_ClearTargetIfCurrentAndPlayAnim_maybe
//   [x] 0x3f4938  CKHkS08Sparx_StartMoveUpdater_maybe
//   [x] 0x3f4a58  CKHkS08Sparx_GetInfo
//   [x] 0x3f4a60  CKHkS08Sparx_MessageProc
//   [x] 0x3f4a70  CKHkS08Sparx_SetDefaultState
//   [x] 0x3f4a78  CKHkS08Sparx_SetGameState
//   [x] 0x3f4a80  CKHkS08Sparx_OnDeactivate
//   [x] 0x3f4b20  CKHkS08Sparx_CreateArray
//   [x] 0x3f4c28  CreateCKHkS08Sparx
//   [x] 0x3f4cc0  CKHkS08Sparx_SetPositionAndDirection_maybe
//   [x] 0x3f4dc8  CKHkS08Sparx_Destructor
//   [x] 0x3f4de8  CKHkS08Sparx_PickRandomPointAround_maybe
//   [x] 0x3f52d0  CKHkS08Sparx_PlaceNearFocusedHero_maybe
//   [x] 0x3f5488  CKHkS08Sparx_OnActivate
//   [x] 0x3f5568  CKHkS08Sparx_SteerTowardTarget_maybe
//   [x] 0x3f5c38  CKHkS08Sparx_MoveTowardTarget_maybe
//   [x] 0x3f5da8  UpdateCKHkS08Sparx
//   [x] 0x3f66e8  CKHkS08Sparx_Restart
//   [x] 0x3f67e8  CKHkS08Sparx_Start
//   [x] 0x3f6860  CKHkS08Sparx_Load
//   [ ] 0x3f6d58  CKHkS08Sparx_Destructor_2  [dead]
//   [x] 0x3f6d78  CKHkS08Sparx_DeletingDestructor
//
//   [x] 0x9c0b18  CKHkS08Sparx_IsKindOfClass  [inline]
//   [x] 0x9c0b60  CKHkS08Sparx_GetClassType  [inline]
//   [x] 0x9c0b68  CKHkS08Sparx_GetClassID  [inline]
#include "Spyro2008/hooks/CKHkS08Sparx.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "crt/ppc_ops.h"
#include "crt/xatan.h"
#include "crt/xsinf.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/components/CKMoveCpntUpdater.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/fx/IKFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/render/CKPointLightFxData.h"
#include "k2000/math/Quat.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CGlowNodeFx.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/system/IKTime.h"

namespace {

// 0x00c50d34 / 0x00c50d40 / 0x00c50d4c / 0x00c50d64: the shared axes and the null vector (zero in the EBOOT's BSS;
// filled by static initialisers).
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};
const CVector3 kAxisZ = {0.0f, 0.0f, 1.0f};
const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};

// The game TOC floats of the unit (TOC +0x44a8..+0x4564).
constexpr float kRandRange = 65535.0f;                 // +0x4520
constexpr float kTwoPi = 0x1.921fb6p+2f;               // +0x4524 6.2831855
constexpr float kPi = 0x1.921fb6p+1f;                  // +0x4528 3.1415927
constexpr float kPiOver4 = 0x1.921fb6p-1f;             // +0x450c 0.78539819
constexpr float kRadiansPerDegree = 0x1.1df468p-6f;    // +0x4544 0.017453291 (0x3c8efa34)
constexpr float kDegreesPerRadian = 0x1.ca5dc2p+5f;    // +0x453c 57.29578 (0x42652ee1)

bool SignBit(float x) {
    int32_t bits;
    std::memcpy(&bits, &x, 4);
    return bits < 0;
}

// The game's sine / cosine as the unit inlines them: the polynomials for a non-negative argument, the library's
// sinf 0x9a1390 / cosf 0x9a11d8 on the negated argument otherwise (the sign bit tested through memory).
float GameSinf(float x) { return SignBit(x) ? -crt::LibSinf(-x) : crt::InlineSinf(x); }
float GameCosf(float x) { return SignBit(x) ? crt::LibCosf(-x) : crt::InlineCosf(x); }

// 0x00010690 Math_Sqrtf: fsqrts.
float Sqrtf(float x) { return std::sqrt(x); }

// 0x002ca0f8 CKGrpS08Hero_GetFocusedHero (local copy; CKGrpS08Hero.cpp, not ported there yet): the focused dragon
// (+0x66, -1 none) among the group's heroes (+0x30).
CKHkS08Hero* FocusedHero() {
    const IKGrpHero* group =
        static_cast<const IKGrpHero*>(static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->m_unk04[1]);
    const int8_t index = static_cast<int8_t>(group->m_ui8FocusedDragon);
    if (index == -1) return nullptr;
    return static_cast<CKHkS08Hero*>(group->m_apHeros[index]);
}

}  // namespace

// A Rand_Int draw (0x00011500) as the float of its low 16 bits (rldicl 48, fcfid, frsp: exact). A macro, so that the
// rand log (DOTD_REPLAY_RANDLOG) names the function that draws.
#define SPARX_RAND_U16() static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu)

// 0x003f4540 CKHkS08Sparx_PostLoad: IKLife_PostLoad 0x19f68 (level type only: bit 2 of the bit array), then for the
// level type a matrix (RwMatrixCreate_Thunk) at +0xc4.
int32_t CKHkS08Sparx::PostLoad(int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) m_bitArray = (m_bitArray & 0xfffffffbu) | 4u;
    if (type == K_LEVEL_PLATEFORMS) m_pMatrixC4 = RwMatrixCreate_Thunk();
    return 1;
}

// 0x003f45e8 CKHkS08Sparx_Destroy: the matrix of +0xc4 given back (RwMatrixDestroy_Thunk 0x23f968).
void CKHkS08Sparx::Destroy() { RwMatrixDestroy_Thunk(m_pMatrixC4); }

// 0x003f45c0 CKHkS08Sparx_RecursiveRegistration: IKHook_LevelReset 0x19ab8 (its KStub_Return1_19c90 does nothing):
// outside the memory-card types 4..7 (cmplwi type - 4, 3) the hook's node registers too (KObject_LevelResetIfNotNull_maybe
// 0x19c98: its vt+0x24 when it has one).
void CKHkS08Sparx::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u && m_pKGLObject != nullptr) m_pKGLObject->RecursiveRegistration(type);
}

// 0x003f6860 CKHkS08Sparx_Load
int32_t CKHkS08Sparx::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pAnimationDictionary);
    IKFile_ReadRef(file, &m_pParticlesNode);
    IKFile_ReadRef(file, &m_pGlowNode);
    IKFile_ReadRef(file, &m_pPointLightFxData);
    IKFile_ReadRef(file, &m_pNode);
    ReadF32LE(file, &m_fl2c);
    ReadF32LE(file, &m_fl30);
    ReadF32LE(file, &m_fl34);
    ReadF32LE(file, &m_fl38);
    ReadF32LE(file, &m_fl3c);
    ReadF32LE(file, &m_fl40);
    ReadF32LE(file, &m_fl44);
    ReadF32LE(file, &m_fl48);
    return 1;
}

// 0x003f67e8 CKHkS08Sparx_Start
void CKHkS08Sparx::Start() {
    m_ui32Flags = (m_ui32Flags & 0xffffffecu) | 0x10u;
    m_unk78 = 0;
    m_fSpeed = 0.0f;  // stw 0
    m_GContactIn.m_MasksOfGrdForTest[0] = 1;
    m_GContactIn.m_MasksOfGrdForTest[1] = 0;
    m_GContactIn.m_fDeltaMax = 0.1f;      // TOC +0x44a8 (0x3dcccccd)
    m_GContactIn.m_fObjectHeight = 1.0f;  // TOC +0x44ac
    m_GContactInOut.m_i32FaceIndex = -1;
    m_GContactInOut.m_eContactStatus = 3;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_GContactInOut.m_pGround = nullptr;
    m_pMoveUpdaterC0 = nullptr;  // +0xc0
    m_pTargetB8 = nullptr;  // +0xb8
}

// 0x003f66e8 CKHkS08Sparx_Restart (vt+0x54): Start's body; then, unless the life flag bit 2, the point light released
// (vt+0x58 with the Sparx as owner) and its data put back on the Sparx's node with no hot spot.
void CKHkS08Sparx::Restart() {
    m_ui32Flags = (m_ui32Flags & 0xffffffecu) | 0x10u;
    m_unk78 = 0;
    m_fSpeed = 0.0f;  // stw 0
    m_GContactIn.m_MasksOfGrdForTest[0] = 1;
    m_GContactIn.m_MasksOfGrdForTest[1] = 0;
    m_GContactIn.m_fDeltaMax = 0.1f;      // TOC +0x44a8 (0x3dcccccd)
    m_GContactIn.m_fObjectHeight = 1.0f;  // TOC +0x44ac
    m_GContactInOut.m_i32FaceIndex = -1;
    m_GContactInOut.m_eContactStatus = 3;
    m_GContactInOut.m_ui8SectorNumber = 0;
    m_GContactInOut.m_pGround = nullptr;
    m_pMoveUpdaterC0 = nullptr;  // +0xc0
    m_pTargetB8 = nullptr;       // +0xb8
    if ((m_bitArray & 4u) != 0) return;
    if (m_pPointLightBC != nullptr) {
        static_cast<IKFx*>(m_pPointLightBC)->StopAndRelease(this);  // vt+0x58
        m_pPointLightBC = nullptr;
    }
    CKPointLightFxData* light = static_cast<CKPointLightFxData*>(m_pPointLightFxData);
    light->m_pAttachHotSpot = nullptr;
    light->m_pAttachNode = m_pKGLObject;
}

// 0x003f4268 CKHkS08Sparx_SetTarget_maybe
uint8_t CKHkS08Sparx::SetTarget(IKSerializable* beacon) {
    if (m_pTargetB8 != nullptr && m_pTargetB8->MessageProc(0x940, this) != 0) return 0;  // vt+0x1c
    m_pTargetB8 = beacon;
    m_ui32Flags = (m_ui32Flags & 0xffffffefu) | 0x10u;
    return 1;
}

// 0x003f48a8 CKHkS08Sparx_ClearTargetIfCurrentAndPlayAnim_maybe
void CKHkS08Sparx::ClearTargetIfCurrentAndPlayAnim(IKSerializable* beacon) {
    if (m_pTargetB8 != beacon) return;
    m_pTargetB8 = nullptr;
    const uint32_t first = static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_pAnimationDictionary)->m_apAnimations[0]);
    static_cast<CAnimatedNode*>(m_pKGLObject)->PlayAnim(0.0, first, 0);  // 0x000c98b8
    m_ui32Flags = (m_ui32Flags & 0xfffffffbu) | 4u;
}

// 0x003f4318 CKHkS08Sparx_StopMoveUpdaterIfCurrent_maybe
void CKHkS08Sparx::StopMoveUpdaterIfCurrent(CKMoveCpntUpdater* updater) {
    if (m_pMoveUpdaterC0 != updater) return;
    m_pMoveUpdaterC0->Stop();  // 0x0024dc60
    m_pMoveUpdaterC0 = nullptr;
}

// 0x003f47f8 CKHkS08Sparx_ResetMoveTargetToCurrentPosition_maybe: the node's modelling position, the null vector, -1
// (TOC +0x44cc).
void CKHkS08Sparx::ResetMoveTargetToCurrentPosition() {
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    m_v3Goal.x = frame->modelling.pos.x;
    m_v3Goal.z = frame->modelling.pos.z;
    m_v3Goal.y = frame->modelling.pos.y;
    m_v3GoalDir.x = kNullVector.x;
    m_v3GoalDir.z = kNullVector.z;
    m_v3GoalDir.y = kNullVector.y;
    m_fGoalSpeed = -1.0f;
}

// 0x003f4850 CKHkS08Sparx_SetMoveGoalPosDirFloat70_maybe
void CKHkS08Sparx::SetMoveGoal(const CVector3* position, const CVector3* direction, float speed) {
    m_v3Goal.x = position->x;
    m_v3Goal.z = position->z;
    m_v3Goal.y = position->y;
    m_v3GoalDir.x = direction->x;
    m_v3GoalDir.z = direction->z;
    m_v3GoalDir.y = direction->y;
    m_fGoalSpeed = speed;
    m_ui32Flags &= 0xffffffefu;
}

// 0x003f4938 CKHkS08Sparx_StartMoveUpdater_maybe: the 0x40 bytes of the modelling matrix (flags and pads included).
void CKHkS08Sparx::StartMoveUpdater(CKMoveCpntUpdater* updater) {
    if (m_pMoveUpdaterC0 != nullptr) return;
    m_pMoveUpdaterC0 = updater;
    updater->Start();  // 0x0024dc98
    std::memcpy(m_pMatrixC4, &static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling, sizeof(CMatrix34));
}

// 0x003f4cc0 CKHkS08Sparx_SetPositionAndDirection_maybe
void CKHkS08Sparx::SetPositionAndDirection(const CVector3* position, const CVector3* direction) {
    m_ui32Flags = (m_ui32Flags & 0xfffffffeu) | 1u;
    m_v3Goal.x = position->x;
    m_v3Goal.z = position->z;
    m_v3Goal.y = position->y;
    m_v3GoalDir.x = direction->x;
    m_v3GoalDir.z = direction->z;
    m_v3GoalDir.y = direction->y;
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    node->SetOrientationFromAtUp(direction, &kAxisY);  // 0x000d0918
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = position->z;
    frame->modelling.pos.x = position->x;
    frame->modelling.pos.y = position->y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
    m_v3Direction.x = direction->x;
    m_v3Direction.z = direction->z;
    m_v3Direction.y = direction->y;
}

// 0x003f4de8 CKHkS08Sparx_PickRandomPointAround_maybe. The draws: (r / 65535) * 2pi - pi (fmsubs), then
// (r / 65535) * (+0x40 - +0x3c) + +0x3c and (r / 65535) * (+0x48 - +0x44) + +0x44 (fmadds). The candidates: step s
// (1..7 on the first ring, 0..7 on the next three, then 8.. one each on four more) turns the angle by s * pi / 4, ring
// k adds k / 8 of the band to the radius (past +0x40 it wraps back by the band: bgt, a NaN keeps it). A candidate
// counts at a squared x / z distance from the node's modelling position of at least 4 (bge: a NaN counts too) when
// the ground probe finds a contact (status 0). After the ninth ring the centre raised by +0x44.
CVector3 CKHkS08Sparx::PickRandomPointAround(const CVector3* center) {
    const float baseAngle = ppc::fmsubs(SPARX_RAND_U16() / kRandRange, kTwoPi, kPi);
    const float baseRadius = ppc::fmadds(SPARX_RAND_U16() / kRandRange, m_fl40 - m_fl3c, m_fl3c);
    const float u = SPARX_RAND_U16() / kRandRange;
    const float height = ppc::fmadds(u, m_fl48 - m_fl44, m_fl44);
    const float ringStep = (m_fl40 - m_fl3c) * 0.125f;  // TOC +0x452c
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    const float nodeX = frame->modelling.pos.x;
    const float nodeZ = frame->modelling.pos.z;
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    CVector3 out;
    int32_t ring = 0;
    int32_t step = 1;
    float turn = static_cast<float>(step) * kPiOver4;
    for (;;) {
        float radius = ppc::fmadds(ringStep, static_cast<float>(ring), baseRadius);
        if (radius > m_fl40) radius = radius + (m_fl3c - m_fl40);
        const float angle = baseAngle + turn;
        out.y = center->y;
        out.z = center->z;
        out.x = center->x;
        out.x = ppc::fmadds(radius, GameSinf(angle), center->x);
        const float z = out.z;
        out.z = ppc::fmadds(radius, GameCosf(angle), z);
        out.y = height + out.y;
        const float dx = out.x - nodeX;
        const float dz = out.z - nodeZ;
        if (!(ppc::fmadds(dx, dx, dz * dz) < 4.0f)) {  // TOC +0x4530
            collision->GroundProbePoints(&m_GContactIn, &m_GContactInOut, &out.x, 1);  // 0x00196540
            if (m_GContactInOut.m_eContactStatus == 0) return out;
        }
        if (ring > 7) {
            out.y = center->y;
            out.z = center->z;
            out.x = center->x;
            out.y = center->y + m_fl44;
            return out;
        }
        ++step;
        if (step <= 7) {
            turn = static_cast<float>(step) * kPiOver4;
            continue;
        }
        ++ring;
        if (ring > 3) {
            turn = static_cast<float>(step) * kPiOver4;
        } else {
            step = 0;
            turn = 0.0f;  // TOC +0x44ec
        }
    }
}

// 0x003f52d0 CKHkS08Sparx_PlaceNearFocusedHero_maybe
void CKHkS08Sparx::PlaceNearFocusedHero() {
    CVector3 position = kNullVector;
    CKHkS08Hero* hero = FocusedHero();
    CVector3 facing = kAxisZ;  // TOC +0x4534
    if (hero != nullptr) {
        const float* p = hero->GetPositionPtr();  // 0x00361968
        const CVector3 center = {p[0], p[1], p[2]};
        position = PickRandomPointAround(&center);
        const float* forward = &hero->m_unk540;  // 0x00361a50 CKHkS08Hero_GetForwardDirPtr_maybe
        facing.x = forward[0];
        facing.y = forward[1];
        facing.z = forward[2];
        m_ui32Flags = (m_ui32Flags & 0xfffffffeu) | 1u;
    }
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = position.z;
    frame->modelling.pos.x = position.x;
    frame->modelling.pos.y = position.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
    node->SetOrientationFromAtUp(&facing, &kAxisY);  // 0x000d0918
    m_v3Goal.x = position.x;
    m_v3Direction.x = facing.x;
    m_v3Direction.z = facing.z;
    m_v3Direction.y = facing.y;
    m_v3Goal.z = position.z;
    m_v3Goal.y = position.y;
    m_ui32Flags = (m_ui32Flags & 0xfffffffbu) | 4u;
}

// 0x003f5488 CKHkS08Sparx_OnActivate (vt+0xa0): placed near the focused hero, the dictionary's first animation from 0;
// the particles shown (node properties bit 10 set, bit 19 cleared), their emission adjustment 0 and the emitter active
// and emitting; the glow shown (bit 2 cleared) and following the node; the point light's data on the node with no hot
// spot, no light node yet (Update acquires one).
void CKHkS08Sparx::VfA0() {
    PlaceNearFocusedHero();
    const uint32_t first = static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_pAnimationDictionary)->m_apAnimations[0]);
    static_cast<CAnimatedNode*>(m_pKGLObject)->PlayAnim(0.0, first, 0);  // 0x000c98b8 (TOC +0x44ec 0.0)
    CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(m_pParticlesNode);
    particles->m_sgProperties = ((particles->m_sgProperties & 0xfffffbffu) | 0x400u) & 0xfff7ffffu;
    particles->m_fEmissionSpeedAdjustment = 0.0f;
    particles->m_pRpPrtStdEmitter->flag |= rpPRTSTDEMITTERFLAGACTIVE | rpPRTSTDEMITTERFLAGEMIT;  // 0xa
    CGlowNodeFx* glow = static_cast<CGlowNodeFx*>(m_pGlowNode);
    glow->m_sgProperties &= 0xfffffffbu;
    CKPointLightFxData* light = static_cast<CKPointLightFxData*>(m_pPointLightFxData);
    light->m_pAttachHotSpot = nullptr;
    light->m_pAttachNode = m_pKGLObject;
    m_pPointLightBC = nullptr;
    glow->m_unk2c = m_pKGLObject;
}

// 0x003f4a80 CKHkS08Sparx_OnDeactivate (vt+0xa4): the particles hidden (properties bits 10 and 19 cleared), the emitter
// stops emitting (bit 3), the point light released (vt+0x58 with the Sparx as owner).
void CKHkS08Sparx::VfA4() {
    CParticlesNodeFx* particles = static_cast<CParticlesNodeFx*>(m_pParticlesNode);
    particles->m_sgProperties &= 0xfff7fbffu;
    particles->m_pRpPrtStdEmitter->flag &= ~static_cast<uint32_t>(rpPRTSTDEMITTERFLAGEMIT);
    if (m_pPointLightBC != nullptr) {
        static_cast<IKFx*>(m_pPointLightBC)->StopAndRelease(this);  // vt+0x58
        m_pPointLightBC = nullptr;
    }
}

// 0x003f5568 CKHkS08Sparx_SteerTowardTarget_maybe. In order:
// - the node turned along +0xc8 (Y up); the unit vector to the goal (none at distance 0); near = distance 0 or below
//   0.2 (blt);
// - with a target the speed is the goal's (+0x70; -1 the default +0x2c) and the turn rate +0x34 scaled by 4 x that
//   speed / +0x2c;
// - the wanted direction: near a target's goal that has a direction, that direction (unit when not 0); else the
//   direction to the goal, or at distance 0 the node's at axis;
// - the signed turn angle in degrees (the acos of the clamped dot, cror lt|eq / gt|eq; the sign of the cross product's
//   y, unit-scaled, blt: negative); `direction` slerped from the node's rotation to the wanted one (Mat4_SetBasisFromAtUp
//   with Y, X when that fails) by +0x34 degrees x dt (at most 1, blt);
// - a turn sharper than turn rate x dt (bge keeps the speed) slows the speed by |angle| / 90 down to 1; within
//   speed^2 / 2 / +0x38 of the goal (bgt) the speed is at most sqrt(2 x +0x38 x distance) (blt);
// - without a target the hero's speed (+0x530) is added unless the hero's life bit 1, and with +0x54 bit 1 while the
//   node was not drawn this frame the wanted speed is +0x30 plus the hero's speed;
// - +0x74 accelerates / brakes by +0x38 x dt to it (bge / ble / bgt: a NaN wanted speed brakes and is kept);
// - without a target, or before it is reached (+0x54 bit 4), `position` moves by dt x +0x74 along `direction`.
void CKHkS08Sparx::SteerTowardTarget(float dt, CVector3* position, CVector3* direction, const CVector3* goal) {
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    node->SetOrientationFromAtUp(&m_v3Direction, &kAxisY);  // 0x000d0918
    float dy = goal->y - position->y;
    float dx = goal->x - position->x;
    float dz = goal->z - position->z;
    float distance = Sqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    bool near;
    if (distance == 0.0f) {
        distance = 0.0f;
        near = true;
    } else {
        const float inverse = 1.0f / distance;
        dz = dz * inverse;
        dx = dx * inverse;
        dy = dy * inverse;
        near = distance < 0.2f;  // TOC +0x4538
    }
    float speed = m_fl2c;
    float turnRate = m_fl34;
    if (m_pTargetB8 != nullptr) {
        const float wanted = m_fGoalSpeed == -1.0f ? speed : m_fGoalSpeed;
        const float ratio = (wanted * 4.0f) / speed;  // TOC +0x4530
        speed = wanted;
        turnRate = turnRate * ratio;
    }
    const float dirX = direction->x;
    const float dirY = direction->y;
    CVector3 want = {dx, dy, dz};
    const float dirZ = direction->z;
    bool fromGoal = true;
    if (near && m_pTargetB8 != nullptr &&
        (m_v3GoalDir.x != kNullVector.x || m_v3GoalDir.y != kNullVector.y || m_v3GoalDir.z != kNullVector.z)) {
        fromGoal = false;
        want = m_v3GoalDir;
        const float length = Sqrtf(ppc::fmadds(want.z, want.z, ppc::fmadds(want.x, want.x, want.y * want.y)));
        if (length != 0.0f) {
            const float inverse = 1.0f / length;
            want.z = want.z * inverse;
            want.x = want.x * inverse;
            want.y = want.y * inverse;
        }
    }
    if (fromGoal && distance == 0.0f) {
        const RwFrame* frame = node->m_pRwFrame;
        want.x = frame->modelling.at.x;
        want.y = frame->modelling.at.y;
        want.z = frame->modelling.at.z;
    }
    float side = ppc::fmsubs(dirZ, want.x, dirX * want.z);
    const float crossX = ppc::fmsubs(dirY, want.z, dirZ * want.y);
    const float crossZ = ppc::fmsubs(dirX, want.y, dirY * want.x);
    const float crossLength = Sqrtf(ppc::fmadds(crossZ, crossZ, ppc::fmadds(crossX, crossX, side * side)));
    if (crossLength != 0.0f) side = side * (1.0f / crossLength);
    float cosine = ppc::fmadds(dirZ, want.z, ppc::fmadds(dirX, want.x, dirY * want.y));
    if (cosine <= -1.0f) {
        cosine = -1.0f;
    } else if (cosine >= 1.0f) {
        cosine = 1.0f;
    }
    const float angle = crt::Acosf(cosine);  // TocBridge_Math_Acosf 0x98e1a0
    const float sign = side < 0.0f ? -1.0f : 1.0f;
    const float turn = sign * (angle * kDegreesPerRadian);

    const RwFrame* frame = node->m_pRwFrame;
    float from[4];
    Quat_FromMatrix(from, reinterpret_cast<const float*>(&frame->modelling));  // 0x002420f8
    // The original's matrix is uninitialised stack apart from the position (and the flags bit it clears); both basis
    // calls fail only for a null wanted direction, which the code above never makes.
    CMatrix34 matrix = {};
    matrix.m_pos.z = frame->modelling.pos.z;
    matrix.m_pos.x = frame->modelling.pos.x;
    matrix.m_pos.y = frame->modelling.pos.y;
    matrix.m_ui32Flags &= 0xfffdffffu;
    if (static_cast<uint8_t>(Mat4_SetBasisFromAtUp(&matrix, &want, &kAxisY)) == 0) {  // 0x0023fd30
        Mat4_SetBasisFromAtUp(&matrix, &want, &kAxisX);
    }
    float to[4];
    Quat_FromMatrix(to, reinterpret_cast<const float*>(&matrix));
    float t = turnRate * kRadiansPerDegree * dt;
    if (!(t < 1.0f)) t = 1.0f;
    float rotation[4];
    Quat_Slerp(t, rotation, from, to);           // 0x00242728
    Quat_Normalize(rotation);                    // 0x00242180
    Quat_ToMatrixNormalizing(rotation, &matrix);  // 0x00241d78
    const float maxTurn = turnRate * dt;
    const float absTurn = std::fabs(turn);
    direction->z = matrix.m_at.z;
    direction->x = matrix.m_at.x;
    direction->y = matrix.m_at.y;
    float brakeSquare;
    bool slowest = false;
    if (maxTurn < absTurn) {
        if (turn < 0.0f) {
            speed = speed * (turn / 90.0f + 1.0f);  // TOC +0x4548
        } else {
            speed = speed * (turn / -90.0f + 1.0f);  // TOC +0x454c
        }
        if (speed < 1.0f) {
            speed = 1.0f;
            slowest = true;
        }
    }
    if (slowest) {
        brakeSquare = 0.5f;
    } else {
        brakeSquare = (speed * 0.5f) * speed;  // TOC +0x44c0
    }
    float wantedSpeed = speed;
    if (brakeSquare * (1.0f / m_fl38) > distance) {
        const float braking = Sqrtf(distance * (m_fl38 + m_fl38));
        wantedSpeed = speed < braking ? speed : braking;
    }
    CKHkS08Hero* hero = FocusedHero();
    if (m_pTargetB8 == nullptr) {
        if ((hero->m_bitArray & 2u) == 0) wantedSpeed = wantedSpeed + hero->m_fCurHSpeed;  // 0x00361c10
        if ((m_ui32Flags & 2u) != 0 &&
            static_cast<CSGLeaf*>(m_pKGLObject)->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter) {
            wantedSpeed = m_fl30 + hero->m_fCurHSpeed;
        }
    }
    const float current = m_fSpeed;
    if (!(wantedSpeed < current)) {
        if (wantedSpeed > current) {
            m_fSpeed = ppc::fmadds(dt, m_fl38, current);
            if (wantedSpeed < m_fSpeed) m_fSpeed = wantedSpeed;
        }
    } else {
        m_fSpeed = current - dt * m_fl38;
        if (wantedSpeed > m_fSpeed) m_fSpeed = wantedSpeed;
    }
    if (m_pTargetB8 == nullptr || (m_ui32Flags & 0x10u) == 0) {
        const float advance = dt * m_fSpeed;
        position->z = ppc::fmadds(advance, direction->z, position->z);
        position->x = ppc::fmadds(advance, direction->x, position->x);
        position->y = ppc::fmadds(advance, direction->y, position->y);
    }
}

// 0x003f5c38 CKHkS08Sparx_MoveTowardTarget_maybe (+0x4538: 0.2, blt)
uint8_t CKHkS08Sparx::MoveTowardTarget(float dt) {
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    CVector3 position;
    position.x = node->m_pRwFrame->modelling.pos.x;
    position.y = node->m_pRwFrame->modelling.pos.y;
    position.z = node->m_pRwFrame->modelling.pos.z;
    CVector3 direction = m_v3Direction;
    SteerTowardTarget(dt, &position, &direction, &m_v3Goal);
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = position.z;
    frame->modelling.pos.x = position.x;
    frame->modelling.pos.y = position.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
    node->SetOrientationFromAtUp(&direction, &kAxisY);  // 0x000d0918
    const float dy = position.y - m_v3Goal.y;
    const float dx = position.x - m_v3Goal.x;
    const float dz = position.z - m_v3Goal.z;
    const float square = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    m_ui32Flags = (m_ui32Flags & 0xffffffefu) | (square < 0.2f ? 0x10u : 0u);
    return static_cast<uint8_t>((m_ui32Flags >> 4) & 1u);
}

// 0x003f5da8 UpdateCKHkS08Sparx. In order: the wing node (+0x20) spun 180 degrees about Y; a point light node acquired
// from the effect service for +0x50 when there is none (CKSrvFx's inlined lookup, null when none is free); placed
// near the hero when not placed yet; then
// - led by a target: the move updater drives the node from the matrix +0xc4 (Evaluate, ApplySampleToMatrix,
//   SetLocalMatrix), or without one a goal with a direction is steered to while +0x54 bit 4 is set; the animation
//   advances with +0x54 bit 2;
// - free: none without a focused hero; a new random goal around the hero when the node is within 1 of the goal
//   (blt) and when the goal is nearer the hero than +0x3c or farther than +0x40 in x / z (bgt / blt; +0x54 bit 1
//   cleared first); more than 50 from the goal (bgt 2500) the node is put 10 behind the camera's real position, else
//   +0x54 bit 1 is set when the goal is farther than +0x40 from the hero (ble), the node steers to the goal and its
//   move is swept as a 0.5 x 1 cylinder against the walls (ResolveSweptCylinderWalls, no masks): blocked (1) it stays,
//   slid or pushed (2, 3) it takes the correction, and either way a new random goal; the node moved and turned, its
//   animation advanced;
// then +0xc8 = the node's at axis and, at a speed above 0 (ble), the node rolled about its right axis by 6 x the
// speed degrees (cror lt|eq: 0 at most, cror gt|eq: 45 at least).
void CKHkS08Sparx::Update(IKTime* frameClock) {
    static_cast<CSGMovable*>(m_pNode)->RotateInPlace(&kAxisY.x, 180.0f);  // 0x000d11b0 (TOC +0x4554)
    if (m_pPointLightBC == nullptr) {
        m_pPointLightBC = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pPointLightFxData), this);
    }
    if ((m_ui32Flags & 1u) == 0) PlaceNearFocusedHero();
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    const float x = node->m_pRwFrame->modelling.pos.x;
    const float y = node->m_pRwFrame->modelling.pos.y;
    const float z = node->m_pRwFrame->modelling.pos.z;
    if (m_pTargetB8 != nullptr) {
        CVector3 position = {x, y, z};
        CVector3 direction = m_v3Direction;
        if (m_pMoveUpdaterC0 != nullptr) {
            CMatrix34 matrix;
            std::memcpy(&matrix, m_pMatrixC4, sizeof matrix);
            float sample[10];
            m_pMoveUpdaterC0->Evaluate(frameClock->m_afDeltaTime[0], sample);  // 0x0024db60
            m_pMoveUpdaterC0->ApplySampleToMatrix(sample, &matrix);           // 0x0024d338
            node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
        } else if ((m_v3GoalDir.x != kNullVector.x || m_v3GoalDir.y != kNullVector.y || m_v3GoalDir.z != kNullVector.z) &&
                   (m_ui32Flags & 0x10u) != 0) {
            SteerTowardTarget(frameClock->m_afDeltaTime[0], &position, &direction, &m_v3Goal);
            RwFrame* frame = node->m_pRwFrame;
            frame->modelling.pos.z = position.z;
            frame->modelling.pos.x = position.x;
            frame->modelling.pos.y = position.y;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);  // 0x00010698
            node->SetOrientationFromAtUp(&direction, &kAxisY);  // 0x000d0918
        }
        if ((m_ui32Flags & 4u) != 0) static_cast<CAnimatedNode*>(m_pKGLObject)->AddAnimTime(frameClock->m_afDeltaTime[0]);
    } else {
        CKHkS08Hero* hero = FocusedHero();
        if (hero == nullptr) return;
        const float* p = hero->GetPositionPtr();  // 0x00361968
        const CVector3 heroPos = {p[0], p[1], p[2]};
        const float gx = x - m_v3Goal.x;
        const float gy = y - m_v3Goal.y;
        const float gz = z - m_v3Goal.z;
        const float toGoal = ppc::fmadds(gz, gz, ppc::fmadds(gx, gx, gy * gy));
        if (toGoal < 1.0f) m_v3Goal = PickRandomPointAround(&heroPos);
        const float hz = m_v3Goal.z - heroPos.z;
        const float hx = m_v3Goal.x - heroPos.x;
        m_ui32Flags &= 0xfffffffdu;
        const float around = ppc::fmadds(hx, hx, hz * hz);
        if (m_fl3c * m_fl3c > around || m_fl40 * m_fl40 < around) m_v3Goal = PickRandomPointAround(&heroPos);
        CVector3 position = {x, y, z};
        CVector3 direction = m_v3Direction;
        if (toGoal > 2500.0f) {  // TOC +0x4558
            const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
            position = camera->m_v3RealPos;
            const CVector3& axis = camera->m_v3RealAxisZ;
            position.z = ppc::fmadds(axis.z, -10.0f, position.z);  // TOC +0x455c
            position.x = ppc::fmadds(axis.x, -10.0f, position.x);
            position.y = ppc::fmadds(axis.y, -10.0f, position.y);
        } else {
            const float ey = m_v3Goal.y - heroPos.y;
            const float ex = m_v3Goal.x - heroPos.x;
            const float ez = m_v3Goal.z - heroPos.z;
            if (ppc::fmadds(ez, ez, ppc::fmadds(ex, ex, ey * ey)) > m_fl40 * m_fl40) {
                m_ui32Flags = (m_ui32Flags & 0xfffffffdu) | 2u;
            }
            SteerTowardTarget(frameClock->m_afDeltaTime[0], &position, &direction, &m_v3Goal);
            CLine line;
            line.m_start.x = x;
            line.m_start.y = y;
            line.m_start.z = z;
            line.m_VectDir.x = position.x - x;
            line.m_VectDir.y = position.y - y;
            line.m_VectDir.z = position.z - z;
            CSlideGroundEdgeDatasOut out;  // the callee fills it when it answers 2 / 3
            const uint8_t result = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)
                                       ->ResolveSweptCylinderWalls(&line, 0.5f, 1.0f, &out, nullptr, nullptr, 1);  // 0x0019aa68
            if (result >= 1 && result <= 3) {
                if (result == 1) {
                    position.x = x;
                    position.y = y;
                    position.z = z;
                } else {
                    position.x = position.x + out.m_v3BouncingVector.x;
                    position.y = position.y + out.m_v3BouncingVector.y;
                    position.z = position.z + out.m_v3BouncingVector.z;
                }
                m_v3Goal = PickRandomPointAround(&heroPos);
            }
        }
        RwFrame* frame = node->m_pRwFrame;
        frame->modelling.pos.z = position.z;
        frame->modelling.pos.x = position.x;
        frame->modelling.pos.y = position.y;
        frame->modelling.flags &= 0xfffdffffu;
        RwFrame_MarkDirty(frame);  // 0x00010698
        node->SetOrientationFromAtUp(&direction, &kAxisY);  // 0x000d0918
        static_cast<CAnimatedNode*>(m_pKGLObject)->AddAnimTime(frameClock->m_afDeltaTime[0]);  // 0x000c9638
    }
    RwFrame* frame = node->m_pRwFrame;
    m_v3Direction.z = frame->modelling.at.z;
    m_v3Direction.x = frame->modelling.at.x;
    m_v3Direction.y = frame->modelling.at.y;
    float roll = m_fSpeed;
    if (!(roll > 0.0f)) return;
    roll = roll * 6.0f;  // TOC +0x4560
    if (roll <= 0.0f) {
        roll = 0.0f;
    } else if (roll >= 45.0f) {  // TOC +0x4564
        roll = 45.0f;
    }
    node->RotateInPlace(&frame->modelling.right.x, roll);  // 0x000d11b0
}
