// CKFlaggedPathCinematicBloc.cpp - reconstructed original translation unit 0x177cf0-0x17a760 (GAME_TOC1, main_toc1), 24 functions, 23 live.
// Primary class: CKFlaggedPathCinematicBloc  key 0x148  category CinematicNode  size 0x100  vtable 0xb1b268
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x177cf0  CKFlaggedPathCinematicBloc_Delete
//   [ ] 0x177d40  RegisterCKFlaggedPathCinematicBlocClass
//   [ ] 0x177db8  _GLOBAL__I_177db8
//   [x] 0x177dc8  CKFlaggedPathCinematicBloc_SnapTargetToGround_maybe
//   [x] 0x177e60  CKFlaggedPathCinematicBloc_StepActorTowards_maybe
//   [x] 0x178050  CKFlaggedPathCinematicBloc_Stop
//   [x] 0x178230  CKFlaggedPathCinematicBloc_RecursiveRegistration
//   [ ] 0x178308  CKFlaggedPathCinematicBloc_InitGroundProbe_maybe  [dead]
//   [x] 0x178430  CKFlaggedPathCinematicBloc_DeleteArray
//   [x] 0x1784d0  CKFlaggedPathCinematicBloc_Create
//   [x] 0x178580  CKFlaggedPathCinematicBloc_PathState2_maybe
//   [x] 0x178660  CKFlaggedPathCinematicBloc_PathState1_maybe
//   [x] 0x178740  CKFlaggedPathCinematicBloc_PathState0_maybe
//   [x] 0x178828  CKFlaggedPathCinematicBloc_Destroy
//   [x] 0x178880  CKFlaggedPathCinematicBloc_CreateArray
//   [x] 0x1789d0  CKFlaggedPathCinematicBloc_UpdateActorGroundContact_maybe
//   [x] 0x178c80  CKFlaggedPathCinematicBloc_MoveActorAlongPath
//   [x] 0x178ff0  CKFlaggedPathCinematicBloc_Update
//   [x] 0x179320  CKFlaggedPathCinematicBloc_Load
//   [ ] 0x179778  CKFlaggedPathCinematicBloc_Save
//   [x] 0x179bf0  CKFlaggedPathCinematicBloc_Complete
//   [x] 0x179dc8  CKFlaggedPathCinematicBloc_RunStateMachine_maybe
//   [x] 0x179ff0  CKFlaggedPathCinematicBloc_MessageProc
//   [x] 0x17a260  CKFlaggedPathCinematicBloc_Start
//
//   [ ] 0x9a95e0  CKFlaggedPathCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9618  CKFlaggedPathCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9620  CKFlaggedPathCinematicBloc_GetClassID  [inline]
//   [x] 0x9a9628  CKFlaggedPathCinematicBloc_Abort  [inline]
//   [x] 0x9a9638  CKFlaggedPathCinematicBloc_UsesActor_maybe  [inline]
//   [x] 0x9a9640  CKFlaggedPathCinematicBloc_IsExclusiveOnActor_maybe  [inline]
//   [x] 0x9a9648  CKFlaggedPathCinematicBloc_GetAnimCount_maybe  [inline]
//   [x] 0x9a9650  CKFlaggedPathCinematicBloc_GetAnimIndex_maybe  [inline]
//   [ ] 0x9a9670  CKFlaggedPathCinematicBloc_Destructor  [inline]
//   [ ] 0x9a9690  CKFlaggedPathCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKFlaggedPathCinematicBloc.h"
#include "k2000/logic/CKSavingManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/ppc_ops.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/logic/ai/CKFlaggedPath.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"

// 0x001784d0 CKFlaggedPathCinematicBloc_Create (the constructor inlined)
CKFlaggedPathCinematicBloc::CKFlaggedPathCinematicBloc() {
    m_sfSpeed[0] = 0.0f;  // TOC 0xc127d4
    m_sfSpeed[2] = 0.0f;
    m_sfSpeed[1] = 0.0f;
    m_DatasIn.m_MasksOfGrdForTest[0] = 1;
    m_DatasIn.m_MasksOfGrdForTest[1] = 8;
    m_DatasInOut.m_eContactStatus = 3;
    m_DatasInOut.m_ui8SectorNumber = 0;
    m_DatasInOut.m_pGround = nullptr;
    m_DatasInOut.m_i32FaceIndex = -1;
    m_AnimStateEngineUnkCd = 0xff;
    m_AnimStateEngineState = 0;
    m_AnimStateEngineOwner = nullptr;
    m_AnimStateEngineTable = nullptr;
}

namespace {
// 0x00b1b2f8: the state engine's handler table the Load copies (three PS3 pointer-to-member pairs: the
// function descriptors 0xb640a8, 0xb64098, 0xb64090, each with a 0 adjustment). CallStateHandler maps the words
// to the native handlers PathState0/1/2.
constexpr uint32_t kFlaggedPathStateTable[6] = {0x00b640a8u, 0u, 0x00b64098u, 0u, 0x00b64090u, 0u};

// 0x00c50d34 / 0x00c50d40: the shared x and y axes (zero in the EBOOT's BSS; static initialisers fill them).
const CVector3 kAxisX = {1.0f, 0.0f, 0.0f};
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};

// 0x00010690 Math_Sqrtf (fsqrts).
inline float Sqrtf(float x) { return std::sqrt(x); }

CSGMovable* NodeOf(const IKCinematicElement* bloc) {
    return static_cast<CSGMovable*>(static_cast<IKHook*>(static_cast<CKCinematicSceneData*>(bloc->m_pElementData)->m_pHook)->m_pKGLObject);
}

const CGroundContactDatasIn* ContactIn(const CKFlaggedPathCinematicBloc* bloc) {
    return reinterpret_cast<const CGroundContactDatasIn*>(&bloc->m_DatasIn);
}
CGroundContactDatasInOut* ContactInOut(CKFlaggedPathCinematicBloc* bloc) {
    return reinterpret_cast<CGroundContactDatasInOut*>(&bloc->m_DatasInOut);
}

// The look-at vector's words (+0x44 target, +0x50 current, +0x5c speed: an XXL2 CSmoothedCVector3Linear).
float* LookAt(CKFlaggedPathCinematicBloc* bloc) { return reinterpret_cast<float*>(bloc->m_sv3LookAt); }

}  // namespace

// The state engine's handler call (the PS3 calls the pointer-to-member pair of the table's entry `state`).
uint8_t CKFlaggedPathCinematicBloc::CallStateHandler(uint8_t state, int32_t mode, uint8_t other) {
    const uint32_t descriptor = m_AnimStateEngineTable[state * 2];
    CKFlaggedPathCinematicBloc* owner = m_AnimStateEngineOwner;
    if (descriptor == 0x00b640a8u) return owner->PathState0(mode, other);
    if (descriptor == 0x00b64098u) return owner->PathState1(mode, other);
    return owner->PathState2(mode, other);  // 0x00b64090
}

// 0x00178740 CKFlaggedPathCinematicBloc_PathState0_maybe
uint8_t CKFlaggedPathCinematicBloc::PathState0(int32_t mode, uint8_t /*other*/) {
    if (mode == 1) {
        if (m_fBlendingValue == 0.0f) {
            PlayActorAnim(0.0, m_i32Tab[0]);  // 0x0018f7d0
        } else {
            CrossfadeActorAnim(static_cast<double>(m_fBlendingValue), 0.0, m_i32Tab[0], 1);  // 0x0018f900
        }
        m_sfSpeed[0] = 0.0f;
        m_sfSpeed[1] = 0.0f;
        m_sfSpeed[2] = 0.0f;
        return 0;
    }
    if (mode != 0) return 0;
    // Standing until m_fTimeForStatique has passed since it began, then walking.
    return (m_fStatiqueStartTime + m_fTimeForStatique < reinterpret_cast<IKTime*>(m_pTime)->m_afCurrentTime[0]) ? 1 : 0;
}

// 0x00178660 CKFlaggedPathCinematicBloc_PathState1_maybe
uint8_t CKFlaggedPathCinematicBloc::PathState1(int32_t mode, uint8_t /*other*/) {
    if (mode != 1) return mode == 0 ? 1 : 0;
    if (m_fBlendingValue == 0.0f) {
        PlayActorAnim(0.0, m_i32Tab[1]);
    } else {
        CrossfadeActorAnim(static_cast<double>(m_fBlendingValue), 0.0, m_i32Tab[1], 1);
    }
    m_sfSpeed[0] = m_fWalkSpeed;
    m_sfSpeed[2] = m_fWalkSpeed;
    m_sfSpeed[1] = m_fWalkSpeed;
    return 0;
}

// 0x00178580 CKFlaggedPathCinematicBloc_PathState2_maybe
uint8_t CKFlaggedPathCinematicBloc::PathState2(int32_t mode, uint8_t /*other*/) {
    if (mode != 1) return mode == 0 ? 2 : 0;
    if (m_fBlendingValue == 0.0f) {
        PlayActorAnim(0.0, m_i32Tab[2]);
    } else {
        CrossfadeActorAnim(static_cast<double>(m_fBlendingValue), 0.0, m_i32Tab[2], 1);
    }
    m_sfSpeed[0] = m_fRunSpeed;
    m_sfSpeed[2] = m_fRunSpeed;
    m_sfSpeed[1] = m_fRunSpeed;
    return 0;
}

// 0x00179dc8 CKFlaggedPathCinematicBloc_RunStateMachine_maybe
void CKFlaggedPathCinematicBloc::RunStateMachine() {
    const uint8_t current = m_AnimStateEngineUnkCd;
    if (current != 0xff) {
        const uint8_t next = CallStateHandler(current, 0, current);
        const uint8_t previous = m_AnimStateEngineUnkCd;
        if (next != previous) {
            if (previous != 0xff) CallStateHandler(previous, 2, next);
            const uint8_t left = m_AnimStateEngineUnkCd;
            m_AnimStateEngineUnkCd = next;
            if (next != 0xff) CallStateHandler(next, 1, left);
        }
    }
    AdvanceActorAnim(static_cast<double>(reinterpret_cast<IKTime*>(m_pTime)->m_afDeltaTime[0]));  // 0x0018f450
}

// 0x00177dc8 CKFlaggedPathCinematicBloc_SnapTargetToGround_maybe
void CKFlaggedPathCinematicBloc::SnapTargetToGround() {
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_DatasIn, &m_DatasInOut, &m_v3CurrentPos.x, 1);
    if (m_DatasInOut.m_eContactStatus == 3 || m_DatasInOut.m_pGround == nullptr) return;
    GroundContact_GetWorldPoint(ContactInOut(this), &m_v3CurrentPos);  // 0x001a70e0
}

// 0x00177e60 CKFlaggedPathCinematicBloc_StepActorTowards_maybe
void CKFlaggedPathCinematicBloc::StepActorTowards(CVector3* direction) {
    float* look = LookAt(this);
    look[6] = m_fRotationSpeed;
    look[0] = direction->x;
    look[2] = direction->z;
    look[1] = direction->y;
    const float dt = reinterpret_cast<IKTime*>(m_pTime)->m_afDeltaTime[0];
    if (look[3] != look[0] || look[4] != look[1] || look[5] != look[2]) {
        const float dx = look[0] - look[3];
        const float dy = look[1] - look[4];
        const float step = dt * look[6];
        const float dz = look[2] - look[5];
        const float distance2 = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (step * step > distance2) {
            look[3] = look[0];
            look[5] = look[2];
            look[4] = look[1];
        } else {
            const float scale = step * rwInvSqrt(distance2);  // 0x000114d8 Math_InvSqrtf
            look[5] = ppc::fmadds(dz, scale, look[5]);
            look[3] = ppc::fmadds(dx, scale, look[3]);
            look[4] = ppc::fmadds(dy, scale, look[4]);
        }
    }
    const float x = look[3];
    const float y = look[4];
    direction->x = x;
    const float z = look[5];
    direction->y = y;
    direction->z = z;
    const float length = Sqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));
    if (length == 0.0f) return;
    const float inverse = 1.0f / length;
    direction->z = inverse * direction->z;
    direction->x = inverse * direction->x;
    direction->y = inverse * direction->y;
}

// 0x001789d0 CKFlaggedPathCinematicBloc_UpdateActorGroundContact_maybe. The shadow data (the scene data's +0x18): the
// point, the normal (+0x0c), the height (+0x18) and a flag byte (+0x1c, bit 4: the ground's engine flag 6).
void CKFlaggedPathCinematicBloc::UpdateActorGroundContact() {
    float* shadow = reinterpret_cast<float*>(static_cast<CKCinematicSceneData*>(m_pElementData)->m_pShadowData);
    if (shadow == nullptr) return;
    // On the ground the move found (m_bPutOnGround), else with flag 9 a probe of its own.
    bool onGround = m_bPutOnGround != 0 && m_DatasInOut.m_eContactStatus != 3 && m_DatasInOut.m_pGround != nullptr;
    if (!onGround && (m_DataFlags & 0x200) != 0) {
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_DatasIn, &m_DatasInOut, &m_v3CurrentPos.x, 1);
        onGround = m_DatasInOut.m_eContactStatus != 3 && m_DatasInOut.m_pGround != nullptr;
    }
    if (!onGround) {
        shadow[3] = kAxisY.x;
        shadow[5] = kAxisY.z;
        shadow[4] = kAxisY.y;
        shadow[0] = m_v3CurrentPos.x;
        shadow[6] = 0.2f;  // 0x3e4ccccd
        shadow[1] = m_v3CurrentPos.y;
        shadow[2] = m_v3CurrentPos.z;
        return;
    }
    GroundContact_GetWorldPoint(ContactInOut(this), reinterpret_cast<CVector3*>(&shadow[0]));   // 0x001a70e0
    GroundContact_GetWorldNormal(ContactInOut(this), reinterpret_cast<CVector3*>(&shadow[3]));  // 0x001a71d8
    shadow[6] = m_DatasInOut.m_fdH;
    // The flag byte after the seven floats (a byte field of the shadow data).
    uint8_t* flags = reinterpret_cast<uint8_t*>(&shadow[7]);
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_DatasInOut.m_pGround);
    if (((ground->m_ba16EngineFlags >> 6) & 1) != 0) {
        *flags = static_cast<uint8_t>(*flags | 0x10);
    } else if ((*flags & 0x10) != 0) {
        *flags = static_cast<uint8_t>(*flags ^ 0x10);
    }
}

// 0x00178c80 CKFlaggedPathCinematicBloc_MoveActorAlongPath
void CKFlaggedPathCinematicBloc::MoveActorAlongPath() {
    CSGMovable* node = NodeOf(this);
    FloatApproach_Step(reinterpret_cast<IKTime*>(m_pTime)->m_afDeltaTime[0], m_sfSpeed);  // 0x002436e8 (target, rate, current)
    CVector3 direction = {0.0f, 0.0f, 0.0f};
    CKFlaggedPath* path = static_cast<CKFlaggedPath*>(m_pFlaggedPath);
    if (m_AnimStateEngineUnkCd != 0) {
        m_fDist = ppc::fmadds(m_sfSpeed[2], reinterpret_cast<IKTime*>(m_pTime)->m_afDeltaTime[0], m_fDist);
    }
    path->SetDistanceAndGetPosition(m_fDist, &m_v3CurrentPos, &direction, nullptr);  // 0x000c4eb8
    if (m_bPutOnGround != 0) {
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_DatasIn, &m_DatasInOut, &m_v3CurrentPos.x, 1);
        if (m_DatasInOut.m_eContactStatus != 3 && m_DatasInOut.m_pGround != nullptr) {
            GroundContact_GetWorldPoint(ContactInOut(this), &m_v3CurrentPos);
        }
    }
    UpdateActorGroundContact();
    RwFrame* frame = node->m_pRwFrame;
    frame->modelling.pos.z = m_v3CurrentPos.z;
    frame->modelling.pos.x = m_v3CurrentPos.x;
    frame->modelling.pos.y = m_v3CurrentPos.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(node->m_pRwFrame);
    if ((m_DataFlags & 0x80) != 0) {
        StepActorTowards(&direction);
    } else {
        const float* look = LookAt(this);
        direction.x = look[3];
        direction.y = look[4];
        direction.z = look[5];
    }
    if (!(direction.y < 0.99f) || !(direction.y > -0.99f)) {
        node->SetBasisFromAtRight(&direction, &kAxisX);  // 0x000d09d8
    } else {
        node->SetOrientationFromAtUp(&direction, &kAxisY);  // 0x000d0918
    }
    if ((m_DataFlags & 0x100) != 0 && m_fAngleRotate != 0.0f) {
        CMatrix34 turned = *reinterpret_cast<const CMatrix34*>(&node->m_pRwFrame->modelling);
        Mat4_RotateLocalYDeg(m_fAngleRotate, &turned);  // 0x002413d0
        node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&turned));  // 0x000d0be8
    }
    node->Scale(m_unk2c);  // 0x000d0d88
}

// 0x00179ff0 CKFlaggedPathCinematicBloc_MessageProc
int32_t CKFlaggedPathCinematicBloc::MessageProc(uint16_t message, void* data) {
    ElementMessageProc(message, data);  // 0x0018faf8 (its answer is not used)
    if (message == 0x503) {
        m_sfSpeed[0] = m_fSpeedArray[*static_cast<const int32_t*>(data)];
        return 0;
    }
    if (message == 0x504) {
        m_sfSpeed[1] = m_fAccelerateArray[*static_cast<const int32_t*>(data)];
        return 0;
    }
    if (message != 0x502) return 1;
    const uint8_t next = static_cast<uint8_t>(*static_cast<const int32_t*>(data));
    uint8_t left = m_AnimStateEngineUnkCd;
    if (left != 0xff) {
        CallStateHandler(left, 2, next);
        left = m_AnimStateEngineUnkCd;
    }
    m_AnimStateEngineUnkCd = next;
    if (next != 0xff) CallStateHandler(next, 1, left);
    return 0;
}

// 0x0017a260 CKFlaggedPathCinematicBloc_Start: the common start (the actor's scale, the running state; Complete when the
// actor is dead or another bloc holds it), the ground contact reset; with a path and an actor the bloc walks from the
// path's start (the look-at the path's direction with bit 7, else the actor's heading), else it completes.
void CKFlaggedPathCinematicBloc::Start() {
    StartCommon();
    m_DatasInOut.m_pGround = nullptr;
    m_DatasInOut.m_ui8SectorNumber = 0;
    m_DatasInOut.m_i32FaceIndex = -1;
    m_DatasInOut.m_eContactStatus = 3;
    CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_pElementData);
    if (m_pFlaggedPath == nullptr || data == nullptr || data->m_pHook == nullptr) {
        Complete();  // vt+0x64
        return;
    }
    m_fStatiqueStartTime = -1.0f;
    m_fDist = 0.0f;  // stw 0
    m_sfSpeed[0] = m_fWalkSpeed;
    m_sfSpeed[2] = m_fWalkSpeed;
    m_sfSpeed[1] = m_fWalkSpeed;
    CVector3 direction;
    static_cast<CKFlaggedPath*>(m_pFlaggedPath)->SetDistanceAndGetPositionUp(m_fDist, &m_v3CurrentPos, &direction,
                                                                            nullptr);  // 0x000c4d88
    float* look = LookAt(this);
    if ((m_DataFlags & 0x80) != 0) {
        look[3] = direction.x;
        look[5] = direction.z;
        look[4] = direction.y;
    } else {
        const RwV3d& at = NodeOf(this)->m_pRwFrame->modelling.at;
        look[3] = at.x;
        look[5] = at.z;
        look[4] = at.y;
    }
    uint8_t left = m_AnimStateEngineUnkCd;
    if (left != 0xff) {
        CallStateHandler(left, 2, 1);
        left = m_AnimStateEngineUnkCd;
    }
    m_AnimStateEngineUnkCd = 1;
    CallStateHandler(1, 1, left);
}

// 0x00178ff0 CKFlaggedPathCinematicBloc_Update: on to the path's end (then Complete); the standing time starts with the
// first standing frame; the actor moved, then the state engine's frame (RunStateMachine inlined).
void CKFlaggedPathCinematicBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0) return;  // 0x0018e9e0
    m_pTime = reinterpret_cast<IKSerializable*>(time);
    const float distance = m_fDist;
    if (!(distance < static_cast<IKPath*>(static_cast<CKFlaggedPath*>(m_pFlaggedPath)->m_pPath)->GetLength())) {  // bge
        Complete();  // vt+0x64
        return;
    }
    if (m_AnimStateEngineUnkCd == 0 && m_fStatiqueStartTime == -1.0f) m_fStatiqueStartTime = time->m_afCurrentTime[0];
    MoveActorAlongPath();
    RunStateMachine();
}

// 0x00179bf0 CKFlaggedPathCinematicBloc_Complete
void CKFlaggedPathCinematicBloc::Complete() { CompleteBloc(); }

// 0x00178050 CKFlaggedPathCinematicBloc_Stop: the completion inlined, then Complete (vt+0x64).
void CKFlaggedPathCinematicBloc::Stop() {
    CompleteBloc();
    Complete();
}

// 0x00179320 CKFlaggedPathCinematicBloc_Load
int32_t CKFlaggedPathCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fRunSpeed);
        ReadF32LE(file, &m_fWalkSpeed);
        ReadF32LE(file, &m_fTimeForStatique);
        ReadF32LE(file, &m_fRotationSpeed);
        IKFile_ReadRef(file, &m_pFlaggedPath);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_i32Tab), 3);  // one 0xc read, swapped
        ReadU8(file, &m_bPutOnGround);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_fSpeedArray), 3);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_fAccelerateArray), 3);
        ReadF32LE(file, &m_fAngleRotate);
        m_DatasInOut.m_pGround = nullptr;
        m_DatasInOut.m_i32FaceIndex = -1;
        m_DatasInOut.m_ui8SectorNumber = 0;
        m_DatasInOut.m_eContactStatus = 3;
        m_AnimStateEngineOwner = this;
        uint32_t* table = static_cast<uint32_t*>(Mem_AllocAligned16(0x18));
        m_AnimStateEngineTable = table;
        for (int i = 0; i < 6; ++i) table[i] = kFlaggedPathStateTable[i];
        m_AnimStateEngineState = 3;
        m_fDist = 0.0f;  // the word 0
        m_DatasIn.m_fDeltaMax = 0.5f;      // TOC 0xc127e0
        m_DatasIn.m_fObjectHeight = 1.2f;  // TOC 0xc127dc (0x3f99999a)
        m_DatasIn.m_MasksOfGrdForTest[0] = 1;
        m_DatasIn.m_MasksOfGrdForTest[1] = 8;
        m_pTime = nullptr;
        m_fStatiqueStartTime = -1.0f;      // TOC 0xc127e4
    }
    return 1;
}

// 0x00178230 CKFlaggedPathCinematicBloc_RecursiveRegistration
void CKFlaggedPathCinematicBloc::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
    if (m_pFlaggedPath != nullptr) m_pFlaggedPath->RecursiveRegistration(type);  // vt+0x24
}

// 0x00178828 CKFlaggedPathCinematicBloc_Destroy
void CKFlaggedPathCinematicBloc::Destroy() {
    m_AnimStateEngineOwner = nullptr;
    Mem_FreeAligned16(m_AnimStateEngineTable);
    m_AnimStateEngineState = 0;
    m_AnimStateEngineUnkCd = 0xff;
    m_AnimStateEngineTable = nullptr;
}
