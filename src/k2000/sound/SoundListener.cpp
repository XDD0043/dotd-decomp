// SoundListener.cpp - reconstructed original translation unit 0x110108-0x110e40 (GAME_TOC1, main_toc1), 18 functions, 11 live.
// Primary owner: SoundListener (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x110108  SoundListener_Reset_maybe
//   [x] 0x1101a8  SoundListener_GetPosition_maybe
//   [ ] 0x110208  SoundListener_GetOrientationMatrix_maybe  [dead]
//   [ ] 0x110260  SoundListener_SetPositionObject_maybe  [dead]
//   [ ] 0x110270  KStub_Nop_110270  [dead]
//   [ ] 0x110278  FUN_00110278  [dead]
//   [ ] 0x110280  FUN_00110280  [dead]
//   [x] 0x110288  SoundListener_Release_maybe
//   [x] 0x110308  SoundListener_SetOrientationFollowCamera_maybe  (ListenerSetOrientationFollowCamera, Spyro2008/groups/C22SpyroShims.h)
//   [x] 0x110330  SoundListener_SetFollowCamera_maybe
//   [ ] 0x110358  SoundListener_SetOrientationObject_maybe  [dead]
//   [x] 0x110368  SoundListener_Update_maybe
//   [x] 0x1106f0  SoundListener_GetMatrix_maybe
//   [x] 0x110890  SoundListener_Load_maybe
//   [ ] 0x1109b8  SoundListener_Recreate_maybe  [dead: no pointer to its descriptor 0xb583b8, no call]
//   [ ] 0x110ad0  SoundListener_Save_maybe  [dead]
//   [x] 0x110be0  SoundListener_Construct_maybe
//   [ ] 0x110d10  SoundListener_Construct_2_maybe  [dead: no pointer to its descriptor 0xb583e8, no call]
//
//   [x] 0x9a6938  SoundListener_DeletingDestructor_maybe  [inline]
//   [x] 0x9a6968  SoundListener_Destructor_maybe  [inline]
#include "k2000/sound/CKListener.h"

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/io/IKFile.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/sound/CKSoundOutput.h"
#include "k2000/system/IKTime.h"
#include "platform/audio/rwa.h"

namespace {
const CVector3 kZeroVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC 0xc11368), the shared zero vector
// TOC 0x426fffff: the inverse frame time when dt is 0
constexpr float kInverseDtWhenStopped = 0x1.dffffep+5f;

// The camera's or an object's RwFrame (CSGMovable +0x04). STUB(RW): null until the frame hierarchy is
// ported; the callers then use the identity orientation and the origin.
RwFrame* CameraFrame() {
    CameraContext* context = Engine_GetCameraContext();
    if (context == nullptr || context->m_pCamera == nullptr) return nullptr;
    return static_cast<CSGMovable*>(context->m_pCamera)->m_pRwFrame;
}
RwFrame* ObjectFrame(IKSerializable* object) {
    return object != nullptr ? static_cast<CSGMovable*>(object)->m_pRwFrame : nullptr;
}
// RwFrame +0x10: the modelling matrix; +0x50: the LTM.
// (By member, not by byte offset: the x64 RwFrame is laid out differently. C2.2 strict2: the camera node's frame is
// no longer null, so the x64 build now reads it.)
const CMatrix34* FrameMatrix(RwFrame* frame, uint32_t offset) {
    if (frame == nullptr) return nullptr;
    return reinterpret_cast<const CMatrix34*>(offset == 0x50 ? static_cast<const void*>(&frame->ltm)
                                                             : static_cast<const void*>(&frame->modelling));
}
const CMatrix34& Identity() {
    static CMatrix34 identity = {{1, 0, 0}, 0, {0, 1, 0}, 0, {0, 0, 1}, 0, {0, 0, 0}, 0};
    return identity;
}
}  // namespace

// 0x00110be0 SoundListener_Construct_maybe. The stores in the original's order.
CKListener::CKListener() {
    m_fDopplerScale = 1.0f;
    m_fRolloffFactor = 1.0f;
    m_fRatioVelocity = 1.0f;
    m_pRwaListener = RwaListener_Create();  // RwaListener_Create_maybe(4, 0, 0)
    RwaPS3Driver_SetListener(static_cast<RwaOutput*>(g_pEngine->m_soundManager->m_pOutput->m_rwaOutput), m_pRwaListener);
    m_pMatrix = RwMatrixCreate_Thunk();
    m_pLeafObjectAttachedForPosition = nullptr;
    m_pLeafObjectAttachedForOrientation = nullptr;
    m_vOldPosition.x = kZeroVector.x;
    m_vOldPosition.z = kZeroVector.z;
    m_vOldPosition.y = kZeroVector.y;
    m_pMatrix->m_ui32Flags = 0x20003;
    m_pMatrix->m_right.x = 1.0f;
    m_pMatrix->m_pos.x = 0.0f;
    m_pMatrix->m_at.z = 1.0f;
    m_pMatrix->m_up.y = 1.0f;
    m_pMatrix->m_up.x = 0.0f;
    m_pMatrix->m_right.z = 0.0f;
    m_pMatrix->m_right.y = 0.0f;
    m_pMatrix->m_at.y = 0.0f;
    m_pMatrix->m_at.x = 0.0f;
    m_pMatrix->m_up.z = 0.0f;
    m_pMatrix->m_pos.z = 0.0f;
    m_pMatrix->m_pos.y = 0.0f;
    m_unk3c = 0;
    m_unk38 = 0;
    m_unk28.x = kZeroVector.x;
    m_unk28.z = kZeroVector.z;
    m_unk28.y = kZeroVector.y;
    m_unk40 = 1;
}

// 0x00110890 SoundListener_Load_maybe
int32_t CKListener::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        ReadF32LE(file, &m_fDopplerScale);
        ReadF32LE(file, &m_fRolloffFactor);
        ReadF32LE(file, &m_fRatioVelocity);
    }
    return 1;
}

// 0x00110108 SoundListener_Reset_maybe: follows the camera again; the matrix back to the identity.
void CKListener::Reset() {
    m_pLeafObjectAttachedForPosition = nullptr;
    m_pLeafObjectAttachedForOrientation = nullptr;
    m_vOldPosition.x = kZeroVector.x;
    m_vOldPosition.z = kZeroVector.z;
    m_vOldPosition.y = kZeroVector.y;
    CMatrix34* m = m_pMatrix;
    m->m_ui32Flags = 0x20003;
    m->m_at.z = 1.0f;
    m->m_up.y = 1.0f;
    m->m_right.x = 1.0f;
    m->m_pos.x = 0.0f;
    m->m_up.x = 0.0f;
    m->m_right.z = 0.0f;
    m->m_right.y = 0.0f;
    m->m_at.y = 0.0f;
    m->m_at.x = 0.0f;
    m->m_up.z = 0.0f;
    m->m_pos.z = 0.0f;
    m->m_pos.y = 0.0f;
    m_unk3c = 0;
    m_unk38 = 0;
    m_unk28.x = kZeroVector.x;
    m_unk28.z = kZeroVector.z;
    m_unk28.y = kZeroVector.y;
}

// 0x001101a8 SoundListener_GetPosition_maybe: the camera frame's position (modelling matrix), the
// object's LTM position, or the origin.
const CVector3* CKListener::GetPosition() {
    if (m_unk38 == 0) {
        const CMatrix34* m = FrameMatrix(CameraFrame(), 0x10);
        return m != nullptr ? &m->m_pos : &kZeroVector;  // STUB(RW): the origin without a frame
    }
    if (m_unk38 != 1) return &kZeroVector;
    const CMatrix34* m = FrameMatrix(ObjectFrame(m_pLeafObjectAttachedForPosition), 0x50);
    return m != nullptr ? &m->m_pos : &kZeroVector;
}

// 0x00110368 SoundListener_Update_maybe: RWA's listener gets the rolloff, the orientation rows, the
// position and (with the Doppler on, +0x40) the velocity.
void CKListener::Update(IKTime* clock) {
    const float dt = clock->m_afDeltaTime[IKTime::FIXED_GAME_TIME];
    const float inverse = dt == 0.0f ? kInverseDtWhenStopped : 1.0f / dt;
    RwaListener* rwa = m_pRwaListener;
    rwa->rolloff = m_fRolloffFactor;
    const CMatrix34* orientation = nullptr;
    if (m_unk3c == 0) {
        orientation = FrameMatrix(CameraFrame(), 0x10);
    } else if (m_unk3c == 1) {
        orientation = FrameMatrix(ObjectFrame(m_pLeafObjectAttachedForOrientation), 0x10);
    }
    if (orientation == nullptr) orientation = &Identity();  // STUB(RW): no frame (the PS3 reads null + 0x10)
    rwa->up[0] = orientation->m_up.x;
    rwa->up[1] = orientation->m_up.y;
    rwa->up[2] = orientation->m_up.z;
    rwa->at[0] = orientation->m_at.x;
    rwa->at[1] = orientation->m_at.y;
    rwa->at[2] = orientation->m_at.z;
    rwa->right[0] = orientation->m_right.x;
    rwa->right[1] = orientation->m_right.y;
    rwa->right[2] = orientation->m_right.z;
    const CVector3* p = GetPosition();  // inlined
    const float px = p->x, pz = p->z, py = p->y;
    rwa->position[0] = px;
    rwa->position[1] = py;
    rwa->position[2] = pz;
    const float k = inverse * m_fRatioVelocity;
    const float vx = (px - m_vOldPosition.x) * k;
    const float vy = (py - m_vOldPosition.y) * k;
    const float vz = (pz - m_vOldPosition.z) * k;
    if (m_unk40 == 0) {
        rwa->doppler = 0.0f;
        rwa->velocity[0] = kZeroVector.x;
        rwa->velocity[1] = kZeroVector.y;
        rwa->velocity[2] = kZeroVector.z;
    } else {
        rwa->doppler = m_fDopplerScale;
        rwa->velocity[0] = vx;
        rwa->velocity[1] = vy;
        rwa->velocity[2] = vz;
    }
    m_unk28.x = vx;
    m_unk28.z = vz;
    m_unk28.y = vy;
    m_vOldPosition.z = pz;
    m_vOldPosition.x = px;
    m_vOldPosition.y = py;
}

// 0x001106f0 SoundListener_GetMatrix_maybe: the orientation source's matrix with the position source's
// position (flag 0x20000 cleared).
CMatrix34* CKListener::GetMatrix() {
    if (m_pRwaListener == nullptr) return nullptr;
    const CMatrix34* source = nullptr;
    if (m_unk3c == 0) {
        source = FrameMatrix(CameraFrame(), 0x10);
    } else if (m_unk3c == 1) {
        source = FrameMatrix(ObjectFrame(m_pLeafObjectAttachedForOrientation), 0x10);
    } else {
        return nullptr;
    }
    if (source == nullptr) source = &Identity();  // STUB(RW): no frame
    const CVector3* p = GetPosition();
    CMatrix34* m = m_pMatrix;
    m->m_right = source->m_right;
    m->m_ui32Flags = source->m_ui32Flags;
    m->m_up = source->m_up;
    m->m_ui32pad1 = source->m_ui32pad1;
    m->m_at = source->m_at;
    m->m_ui32pad2 = source->m_ui32pad2;
    m->m_pos = source->m_pos;
    m->m_ui32pad3 = source->m_ui32pad3;
    m->m_pos.x = p->x;
    m->m_pos.z = p->z;
    m->m_pos.y = p->y;
    m->m_ui32Flags &= ~0x20000u;
    return m;
}

// 0x00110288 SoundListener_Release_maybe
void CKListener::Release() {
    RwaPS3Driver_SetListener(static_cast<RwaOutput*>(g_pEngine->m_soundManager->m_pOutput->m_rwaOutput), nullptr);
    RwaListener_Destroy(m_pRwaListener);  // RwaObject_Destroy_maybe(listener, 0, 0)
    m_pRwaListener = nullptr;
    RwMatrixDestroy_Thunk(m_pMatrix);
    m_pMatrix = nullptr;
}
