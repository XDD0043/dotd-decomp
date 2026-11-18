// CKTeleportCinematicBloc.cpp - reconstructed original translation unit 0x18d470-0x18e8d8 (GAME_TOC1, main_toc1), 17 functions, 16 live.
// Primary class: CKTeleportCinematicBloc  key 0x788  category CinematicNode  size 0x88  vtable 0xb1bc98
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x18d470  CKTeleportCinematicBloc_Delete
//   [x] 0x18d4c0  CKTeleportCinematicBloc_Abort
//   [ ] 0x18d4d0  CKTeleportCinematicBloc_InitGroundProbe_maybe  [dead]
//   [ ] 0x18d518  RegisterCKTeleportCinematicBlocClass
//   [ ] 0x18d590  _GLOBAL__I_18d590
//   [x] 0x18d5a0  CKTeleportCinematicBloc_Stop
//   [x] 0x18d780  CKTeleportCinematicBloc_RecursiveRegistration  (inherited: IKCinematicBloc_LevelReset, a tail call)
//   [x] 0x18d7a8  CKTeleportCinematicBloc_DeleteArray
//   [x] 0x18d858  CKTeleportCinematicBloc_Create
//   [x] 0x18d8f8  CKTeleportCinematicBloc_Destroy  (empty: the default)
//   [x] 0x18d900  CKTeleportCinematicBloc_Load
//   [x] 0x18da78  CKTeleportCinematicBloc_CreateArray
//   [ ] 0x18dbb8  CKTeleportCinematicBloc_Save
//   [x] 0x18dd80  CKTeleportCinematicBloc_TeleportToBeacon_maybe
//   [x] 0x18e358  CKTeleportCinematicBloc_Update
//   [x] 0x18e400  CKTeleportCinematicBloc_Start
//   [x] 0x18e6e8  CKTeleportCinematicBloc_Complete
//
//   [ ] 0x9aa450  CKTeleportCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9aa488  CKTeleportCinematicBloc_GetClassType  [inline]
//   [ ] 0x9aa490  CKTeleportCinematicBloc_GetClassID  [inline]
//   [ ] 0x9aa498  CKTeleportCinematicBloc_UsesActor_maybe  [inline]
//   [ ] 0x9aa4a0  CKTeleportCinematicBloc_Destructor  [inline]
//   [ ] 0x9aa4c0  CKTeleportCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKTeleportCinematicBloc.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "crt/xsinf.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/logic/CKCinematicScene.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvBeacon.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"

#include "k2000/io/IKFile.h"

// 0x0018d858 CKTeleportCinematicBloc_Create (the constructor inlined)
CKTeleportCinematicBloc::CKTeleportCinematicBloc() {
    m_baTarget[0] = 0xffff;
    m_baTarget[3] = 0xffff;
    m_baTarget[1] = 0xffff;
    m_baTarget[2] = 0xffff;
    m_DatasIn.m_MasksOfGrdForTest[0] = 1;
    m_DatasIn.m_MasksOfGrdForTest[1] = 8;
    m_DatasInOut.m_ui8SectorNumber = 0;
    m_DatasInOut.m_i32FaceIndex = -1;
    m_DatasInOut.m_eContactStatus = 3;
    m_DatasInOut.m_pGround = nullptr;
}

// 0x0018d900 CKTeleportCinematicBloc_Load
int32_t CKTeleportCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fPauseTime);
        // One 8-byte read, then each half-word swapped (lhbrx).
        uint8_t raw[8];
        ReadRaw(file, raw, 8);
        for (int i = 0; i < 4; ++i) m_baTarget[i] = static_cast<uint16_t>(raw[2 * i] | (raw[2 * i + 1] << 8));
        m_DatasInOut.m_pGround = nullptr;
        m_DatasInOut.m_i32FaceIndex = -1;
        m_DatasInOut.m_eContactStatus = 3;
        m_DatasInOut.m_ui8SectorNumber = 0;
        m_DatasIn.m_fDeltaMax = 0.5f;      // TOC 0xc12dc4
        m_DatasIn.m_fObjectHeight = 1.2f;  // TOC 0xc12dc0 (0x3f99999a)
        m_DatasIn.m_MasksOfGrdForTest[0] = 1;
        m_DatasIn.m_MasksOfGrdForTest[1] = 8;
    }
    return 1;
}

// 0x0018e400 CKTeleportCinematicBloc_Start. Without a pause the actor is teleported at once and the bloc completes.
void CKTeleportCinematicBloc::Start() {
    StartCommon();
    m_fCurrentTime = m_fPauseTime;
    if (m_fPauseTime == 0.0f) {
        TeleportToBeacon();
        Complete();  // vt+0x64
    }
}

// 0x0018e358 CKTeleportCinematicBloc_Update
void CKTeleportCinematicBloc::Update(IKTime* time) {
    if (CheckSekensStop() == 0) return;
    if (m_fCurrentTime <= 0.0f) {
        TeleportToBeacon();
        Complete();  // vt+0x64
    } else {
        m_fCurrentTime = m_fCurrentTime - time->m_afDeltaTime[0];
    }
}

// 0x0018e6e8 CKTeleportCinematicBloc_Complete: the completion inlined, then the pause counter reloaded.
void CKTeleportCinematicBloc::Complete() {
    CompleteBloc();
    m_fCurrentTime = m_fPauseTime;
}

// 0x0018d5a0 CKTeleportCinematicBloc_Stop
void CKTeleportCinematicBloc::Stop() {
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x0018d4c0 CKTeleportCinematicBloc_Abort
void CKTeleportCinematicBloc::Abort() { m_DataFlags &= 0xfffffffeu; }

// 0x0018dd80 CKTeleportCinematicBloc_TeleportToBeacon_maybe
void CKTeleportCinematicBloc::TeleportToBeacon() {
    const uint8_t* beacon = static_cast<CKSrvBeacon*>(g_pEngine->m_srvBeacon)->GetBeaconData(m_baTarget);
    // BUG(original): a sector without klusters is read from the low addresses 0, 2, 4 and 6; zeros here.
    const int16_t* values = reinterpret_cast<const int16_t*>(beacon);
    const int8_t yawByte = beacon != nullptr ? static_cast<int8_t>(beacon[6]) : static_cast<int8_t>(0);
    float position[3];  // the beacon's position, tenths
    position[0] = static_cast<float>(values != nullptr ? values[0] : 0) * 0.1f;
    position[1] = static_cast<float>(values != nullptr ? values[1] : 0) * 0.1f;
    position[2] = static_cast<float>(values != nullptr ? values[2] : 0) * 0.1f;
    const float angle = (static_cast<float>(yawByte) * 3.1415927f) * 0.0078125f;
    float sine;
    float cosine;
    int32_t angleBits;
    std::memcpy(&angleBits, &angle, 4);
    if (angleBits < 0) {  // the sign bit: the library's sinf / cosf with the negated argument
        sine = -crt::LibSinf(-angle);
        cosine = crt::LibCosf(-angle);
    } else {
        sine = crt::InlineSinf(angle);
        cosine = crt::InlineCosf(angle);
    }
    // The heading (sine, 0, cosine) normalised.
    float y = 0.0f;
    const float length = static_cast<float>(std::sqrt(static_cast<double>(ppc::fmadds(cosine, cosine, ppc::fmadds(sine, sine, 0.0f)))));
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        cosine = cosine * inverse;
        sine = sine * inverse;
        y = inverse * 0.0f;
    }
    CKCinematicSceneData* data = static_cast<CKCinematicSceneData*>(m_pElementData);
    CSGMovable* node = static_cast<CSGMovable*>(static_cast<IKHook*>(data->m_pHook)->m_pKGLObject);
    RwFrame* frame = node->m_pRwFrame;
    bool onGround = false;
    if ((m_DataFlags & 0x80) != 0) {
        static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_DatasIn, &m_DatasInOut, position, 1);
        onGround = m_DatasInOut.m_eContactStatus != 3 && m_DatasInOut.m_pGround != nullptr &&
                   m_DatasInOut.m_pGround->GetClassID() != 0x13;
    }
    if (onGround) {
        frame->modelling.pos.x = m_DatasInOut.m_ProjectionOnGround.x;
        frame->modelling.pos.z = m_DatasInOut.m_ProjectionOnGround.z;
        frame->modelling.pos.y = m_DatasInOut.m_ProjectionOnGround.y;
    } else {
        frame->modelling.pos.x = position[0];
        frame->modelling.pos.z = position[2];
        frame->modelling.pos.y = position[1];
    }
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
    constexpr float kUp[3] = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (the shared Y axis)
    frame->modelling.at.y = y;
    frame->modelling.at.z = cosine;
    frame->modelling.at.x = sine;
    frame->modelling.flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(frame);
    frame->modelling.up.x = kUp[0];
    frame->modelling.up.y = kUp[1];
    frame->modelling.up.z = kUp[2];
    frame->modelling.flags &= 0xfffdfffcu;
    RwFrame_MarkDirty(frame);
    // right = up x at
    const float upYAtX = kUp[1] * sine;
    const float upXAtZ = kUp[0] * cosine;
    const float upZAtY = kUp[2] * y;
    const float rightZ = ppc::fmsubs(kUp[0], y, upYAtX);
    const float rightY = ppc::fmsubs(kUp[2], sine, upXAtZ);
    const float rightX = ppc::fmsubs(kUp[1], cosine, upZAtY);
    frame->modelling.flags &= 0xfffdfffcu;
    frame->modelling.right.z = rightZ;
    frame->modelling.right.y = rightY;
    frame->modelling.right.x = rightX;
    RwFrame_MarkDirty(frame);
    node->Scale(m_unk2c);
}
