// CKPlayAnimCinematicBloc.cpp - reconstructed original translation unit 0x184ca0-0x186430 (GAME_TOC1, main_toc1), 19 functions, 16 live.
// Primary class: CKPlayAnimCinematicBloc  key 0xc8  category CinematicNode  size 0x9c  vtable 0xb1b7d8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x184ca0  CKPlayAnimCinematicBloc_Delete
//   [ ] 0x184cf0  CKPlayAnimCinematicBloc_InitGroundProbe_maybe  [dead]
//   [x] 0x184d38  CKPlayAnimCinematicBloc_Abort
//   [ ] 0x184d58  RegisterCKPlayAnimCinematicBlocClass
//   [ ] 0x184dd0  _GLOBAL__I_184dd0
//   [x] 0x184de0  CKPlayAnimCinematicBloc_AdvanceAnim_maybe
//   [ ] 0x184f68  CKPlayAnimCinematicBloc_SnapToGround_maybe  [dead]
//   [ ] 0x1850e8  FUN_001850e8  [dead]
//   [x] 0x185250  CKPlayAnimCinematicBloc_Stop
//   [ ] 0x185430  CKPlayAnimCinematicBloc_RecursiveRegistration
//   [x] 0x1854c0  CKPlayAnimCinematicBloc_DeleteArray
//   [x] 0x185560  CKPlayAnimCinematicBloc_Create
//   [ ] 0x1855f0  CKPlayAnimCinematicBloc_Destroy
//   [x] 0x1855f8  CKPlayAnimCinematicBloc_CreateArray
//   [x] 0x185710  CKPlayAnimCinematicBloc_Start
//   [x] 0x185ad8  CKPlayAnimCinematicBloc_Load
//   [ ] 0x185d40  CKPlayAnimCinematicBloc_Save
//   [x] 0x185f18  CKPlayAnimCinematicBloc_Update
//   [x] 0x186240  CKPlayAnimCinematicBloc_Complete
//
//   [ ] 0x9a9d28  CKPlayAnimCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9d60  CKPlayAnimCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9d68  CKPlayAnimCinematicBloc_GetClassID  [inline]
//   [x] 0x9a9d70  CKPlayAnimCinematicBloc_UsesActor_maybe  [inline]
//   [x] 0x9a9d78  CKPlayAnimCinematicBloc_IsExclusiveOnActor_maybe  [inline]
//   [x] 0x9a9d80  CKPlayAnimCinematicBloc_GetAnimCount_maybe  [inline]
//   [x] 0x9a9d88  CKPlayAnimCinematicBloc_GetAnimIndex_maybe  [inline]
//   [ ] 0x9a9d98  CKPlayAnimCinematicBloc_DeletingDestructor  [inline]
//   [ ] 0x9a9de0  CKPlayAnimCinematicBloc_Destructor  [inline]
#include "k2000/cinematics/CKPlayAnimCinematicBloc.h"

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/system/IKTime.h"

#include "k2000/io/IKFile.h"

// 0x00185560 CKPlayAnimCinematicBloc_Create (the constructor inlined)
CKPlayAnimCinematicBloc::CKPlayAnimCinematicBloc() {
    m_DatasIn.m_MasksOfGrdForTest[0] = 1;
    m_DatasIn.m_MasksOfGrdForTest[1] = 8;
    m_DatasInOut.m_ui8SectorNumber = 0;
    m_DatasInOut.m_i32FaceIndex = -1;
    m_DatasInOut.m_eContactStatus = 3;
    m_DatasInOut.m_pGround = nullptr;
}

// 0x00185ad8 CKPlayAnimCinematicBloc_Load
int32_t CKPlayAnimCinematicBloc::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        BasicLoadCinematicElement(file, K_LEVEL_PLATEFORMS);
        ReadF32LE(file, &m_fAnimTime);
        ReadU32LE(file, &m_ui32AnimChosen);
        ReadF32LE(file, &m_fStartTime);
        ReadU8(file, &m_baPlayAnim);
        ReadF32LE(file, &m_fBeginTime);
        ReadF32LE(file, &m_fEndTime);
        m_DatasIn.m_fObjectHeight = 1.2f;  // TOC 0xc12b2c (0x3f99999a)
        m_DatasIn.m_fDeltaMax = 0.5f;      // TOC 0xc12b30
        m_DatasIn.m_MasksOfGrdForTest[0] = 1;
        m_DatasIn.m_MasksOfGrdForTest[1] = 8;
        m_DatasInOut.m_pGround = nullptr;
        m_DatasInOut.m_ui8SectorNumber = 0;
        m_DatasInOut.m_i32FaceIndex = -1;
        m_DatasInOut.m_eContactStatus = 3;
    }
    return 1;
}

namespace {
// The shadow data an actor keeps (CKCinematicSceneData +0x18, the component 0x486): a position, a normal, a height and flags.
struct ShadowData {
    float m_afPosition[3];
    float m_afNormal[3];
    float m_fHeight;
    uint8_t m_ui8Flags;  // +0x1c
};
}  // namespace

// 0x00185710 CKPlayAnimCinematicBloc_Start
void CKPlayAnimCinematicBloc::Start() {
    StartCommon();
    m_fStartTime = -1.0f;
    m_DatasInOut.m_pGround = nullptr;
    m_DatasInOut.m_ui8SectorNumber = 0;
    m_DatasInOut.m_i32FaceIndex = -1;
    m_DatasInOut.m_eContactStatus = 3;
    CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_pElementData);
    if (data != nullptr && data->m_pHook != nullptr && m_ui32AnimChosen != 0xffffffffu) {
        if (static_cast<double>(m_fBlendingValue) == 0.0) {
            PlayActorAnim(static_cast<double>(m_fBeginTime), static_cast<int32_t>(m_ui32AnimChosen));
        } else {
            double start = 0.0;
            if (((m_baPlayAnim >> 2) & 1) != 0) start = static_cast<double>(m_fBeginTime);
            CrossfadeActorAnim(static_cast<double>(m_fBlendingValue), start, static_cast<int32_t>(m_ui32AnimChosen), 1);
        }
        // The end time is at most the animation's duration (CKAnmKeyFrameController's, through a throw-away controller).
        const uint32_t handle = static_cast<uint32_t>(static_cast<const CAnimationDictionary*>(data->m_pAnimDico)->m_apAnimations[m_ui32AnimChosen]);
        if (handle != 0xffffffffu) {
            float duration = CKAnmKeyFrameController::GetDurationOf(handle);
            if (m_fEndTime <= duration) duration = m_fEndTime;
            m_fEndTime = duration;
        }
        return;
    }
    Complete();  // vt+0x64
}

// 0x00184de0 CKPlayAnimCinematicBloc_AdvanceAnim_maybe
void CKPlayAnimCinematicBloc::AdvanceAnim(IKTime* time) {
    const uint8_t flags = m_baPlayAnim;
    const double dt = static_cast<double>(time->m_afDeltaTime[0]);
    if (((flags >> 2) & 1) == 0) {
        if ((flags & 1) == 0) {
            if (((flags >> 1) & 1) == 0) {
                if (time->m_afCurrentTime[0] < m_fStartTime + m_fAnimTime) {
                    AdvanceActorAnim(dt);
                    m_fTimeElapsed = time->m_afCurrentTime[0];
                    return;
                }
                m_fTimeElapsed = time->m_afCurrentTime[0];
                Complete();  // vt+0x64
                return;
            }
        } else if (((flags >> 1) & 1) == 0) {
            AdvanceActorAnim(dt);
            m_fTimeElapsed = time->m_afCurrentTime[0];
            return;
        }
        if (!IsActorAnimEndReached(dt)) {
            AdvanceActorAnim(dt);
            return;
        }
    } else {
        if (GetActorAnimTime() < static_cast<double>(m_fEndTime) && !IsActorAnimEndReached(dt)) {
            AdvanceActorAnim(dt);
            m_fTimeElapsed = time->m_afCurrentTime[0];
            return;
        }
    }
    Complete();  // vt+0x64
}

// 0x00185f18 CKPlayAnimCinematicBloc_Update
void CKPlayAnimCinematicBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0) return;
    if (m_fStartTime == -1.0f) m_fStartTime = time->m_afCurrentTime[0];
    AdvanceAnim(time);
    CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_pElementData);
    RwFrame* frame = static_cast<CSGMovable*>(static_cast<IKHook*>(data->m_pHook)->m_pKGLObject)->m_pRwFrame;
    bool onGround = false;
    if (((m_baPlayAnim >> 3) & 1) != 0) {
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_DatasIn, &m_DatasInOut, &frame->modelling.pos.x, 1);
        if (m_DatasInOut.m_eContactStatus != 3 && m_DatasInOut.m_pGround != nullptr && m_DatasInOut.m_pGround->GetClassID() != 0x13) {
            m_v3Pos = m_DatasInOut.m_ProjectionOnGround;
            frame->modelling.pos.x = m_v3Pos.x;
            frame->modelling.pos.y = m_v3Pos.y;
            frame->modelling.pos.z = m_v3Pos.z;
            frame->modelling.flags &= 0xfffdffffu;
            RwFrame_MarkDirty(frame);
            onGround = true;
        }
    }
    if (!onGround) {
        m_v3Pos.x = frame->modelling.pos.x;
        m_v3Pos.z = frame->modelling.pos.z;
        m_v3Pos.y = frame->modelling.pos.y;
    }
    ShadowData* shadow = static_cast<ShadowData*>(static_cast<void*>(data->m_pShadowData));
    if (shadow == nullptr) return;
    if (((m_baPlayAnim >> 3) & 1) == 0) {
        shadow->m_afNormal[0] = 0.0f;  // the shared Y axis 0x00c50d40
        shadow->m_afNormal[1] = 1.0f;
        shadow->m_afNormal[2] = 0.0f;
        shadow->m_afPosition[0] = m_v3Pos.x;
        shadow->m_afPosition[1] = m_v3Pos.y;
        shadow->m_afPosition[2] = m_v3Pos.z;
        shadow->m_fHeight = 0.2f;  // 0x3e4ccccd
        return;
    }
    if (m_DatasInOut.m_eContactStatus != 3) {
        // The shadow on the ground under the actor: its point and normal, the height above it, and flag 0x10 for a
        // ground with engine flag 0x40.
        const CGroundContactDatasInOut* contact = reinterpret_cast<const CGroundContactDatasInOut*>(&m_DatasInOut);
        GroundContact_GetWorldPoint(contact, reinterpret_cast<CVector3*>(shadow->m_afPosition));
        GroundContact_GetWorldNormal(contact, reinterpret_cast<CVector3*>(shadow->m_afNormal));
        shadow->m_fHeight = m_DatasInOut.m_fdH;
        if (((static_cast<const ICollisionMesh*>(m_DatasInOut.m_pGround)->m_ba16EngineFlags >> 6) & 1) != 0) {
            shadow->m_ui8Flags = static_cast<uint8_t>(shadow->m_ui8Flags | 0x10);
            return;
        }
        if ((shadow->m_ui8Flags & 0x10) != 0) shadow->m_ui8Flags = static_cast<uint8_t>(shadow->m_ui8Flags ^ 0x10);
    }
}

// 0x00186240 CKPlayAnimCinematicBloc_Complete
void CKPlayAnimCinematicBloc::Complete() {
    CompleteBloc();
    m_fStartTime = -1.0f;
}

// 0x00185250 CKPlayAnimCinematicBloc_Stop
void CKPlayAnimCinematicBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x00184d38 CKPlayAnimCinematicBloc_Abort
void CKPlayAnimCinematicBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    m_fStartTime = -1.0f;
}
