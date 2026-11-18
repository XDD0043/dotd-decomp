// CKAnimatedCamera.cpp - reconstructed original translation unit 0x5bf8d8-0x5c0648 (GAME_TOC2, main_toc2), 21 functions, 18 live.
// Primary class: CKAnimatedCamera  key 0x9c4c  category Logic  size ?  vtable 0xb2fa60
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5bf8d8  CKAnimatedCamera_Delete
//   [ ] 0x5bf928  CKAnimatedCamera_Construct  [dead]
//   [ ] 0x5bf938  CKAnimatedCamera_Construct_2  [dead]
//   [x] 0x5bf948  CKAnimatedCamera_Reset_maybe
//   [ ] 0x5bf968  RegisterCKAnimatedCameraClass
//   [ ] 0x5bf9e0  _GLOBAL__I_5bf9e0
//   [x] 0x5bf9f0  CKAnimatedCamera_PlayAnim_maybe
//   [x] 0x5bfa38  CKAnimatedCamera_DeleteArray
//   [x] 0x5bfad8  CKAnimatedCamera_Update_maybe
//   [x] 0x5bfd10  CKAnimatedCamera_Start_maybe
//   [x] 0x5bffe8  CKAnimatedCamera_End_maybe
//   [x] 0x5c0058  CKAnimatedCamera_CreateArray
//   [x] 0x5c00e8  CKAnimatedCamera_Create
//   [x] 0x5c0120  CKAnimatedCamera_RecursiveRegistration  (returns 1: the default slot)
//   [x] 0x5c0128  CKAnimatedCamera_PostLoad
//   [x] 0x5c0170  CKAnimatedCamera_Destroy  (empty: the default slot)
//   [x] 0x5c0178  CKAnimatedCamera_Load
//   [ ] 0x5c03a0  CKAnimatedCamera_Save
//   [x] 0x5c05d8  CKAnimatedCamera_DeletingDestructor  (the destructor; delete)
//   [x] 0x5c0618  CKAnimatedCamera_Destructor  (C++ destructor chain: vtable stores only)
//   [ ] 0x5c0630  CKAnimatedCamera_Destructor_2  [dead]
//
//   [ ] 0x9cd230  CKAnimatedCamera_GetClassType  [inline]
//   [ ] 0x9cd238  CKAnimatedCamera_GetClassID  [inline]
//   [ ] 0x9cd240  CKAnimatedCamera_IsKindOfClass  [inline]
#include "k2000/logic/animation/CKAnimatedCamera.h"

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/components/CKCameraEventCpnt.h"
#include "k2000/core/Stub.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/Engine.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/animation/CKAnimatedCameraData.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGBranch.h"

// 0x005c0178 CKAnimatedCamera_Load
int32_t CKAnimatedCamera::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) {
        for (IKSerializable*& ref : m_apUnk04) IKFile_ReadRef(file, &ref);
    }
    return 1;
}

namespace {
CAnimatedNode* NodeOf(const CKAnimatedCamera* camera) { return static_cast<CAnimatedNode*>(camera->m_apUnk04[1]); }
CKCameraEventCpnt* HandleOf(const CKAnimatedCamera* camera) { return static_cast<CKCameraEventCpnt*>(camera->m_apUnk04[3]); }
// The handle's active byte (+0x10, ScriptedCameraHandle_Activate_maybe 0x165bd8).
uint8_t HandleActive(const CKCameraEventCpnt* handle) { return handle->m_bActive; }
}  // namespace

// 0x005c0128 CKAnimatedCamera_PostLoad
int32_t CKAnimatedCamera::PostLoad(int32_t /*type*/) {
    Reset();  // vt+0x5c
    return 1;
}

// 0x005bf948 CKAnimatedCamera_Reset_maybe (TOC2 constants 1.0 and 0.2)
void CKAnimatedCamera::Reset() {
    m_fUnk1c = 0.2f;
    m_bActive = 0;
    m_fSpeed = 1.0f;
}

// 0x005bffe8 CKAnimatedCamera_End_maybe
void CKAnimatedCamera::End() {
    if (m_bActive == 0) return;
    if (HandleActive(HandleOf(this)) == 0) HandleOf(this)->Release();  // 0x00166130 (BUG(original)_maybe: when NOT active, a no-op)
    m_bActive = 0;
    m_fUnk1c = 0.2f;
    m_fSpeed = 1.0f;
}

// 0x005bf9f0 CKAnimatedCamera_PlayAnim_maybe: CAnimatedNode_PlayAnim_maybe 0xc98b8 with no restart (r6 0).
void CKAnimatedCamera::PlayAnim(float start, uint32_t index) {
    const CAnimationDictionary* dictionary = static_cast<const CAnimationDictionary*>(m_apUnk04[0]);
    NodeOf(this)->PlayAnim(start, static_cast<uint32_t>(dictionary->m_apAnimations[index]), 0);
}

// 0x005bfd10 CKAnimatedCamera_Start_maybe
uint8_t CKAnimatedCamera::Start(float start, CKAnimatedCameraData* data, CSGBranch* parent) {
    if (m_apUnk04[1] == nullptr || m_bActive != 0) return 0;
    uint32_t index = 0;
    if (data->PickAnimation(&index) == 0) return 0;  // vt+0x50
    CAnimatedNode* node = NodeOf(this);
    if (node->m_pParent != nullptr) static_cast<CSGBranch*>(node->m_pParent)->RemoveChild(node);  // vt+0x78
    parent->AddChild(node);  // vt+0x70
    if (data->GetAlignToCamera(index) != 0) {  // vt+0x5c
        // The node turned about its position (modelling +0x40) and axis (modelling up, +0x20) by the difference of the
        // camera's real heading (CKSrvCamera +0x5c8, copied) and the node's (LTM at, +0x70), in degrees (fsubs, then
        // fmuls by TOC2 -0x616c 57.29578f).
        const CVector3 heading = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_v3RealAxisZ;
        const float cameraYaw = Vec3_GetYawAngleFromZ(&heading);  // 0x00244528 (through its TocBridge)
        RwFrame* frame = node->m_pRwFrame;
        const float nodeYaw = Vec3_GetYawAngleFromZ(reinterpret_cast<const CVector3*>(&FrameLtm(frame)->at));  // stored LTM
        const float degrees = (cameraYaw - nodeYaw) * 57.2957802f;
        node->RotateAboutPoint(degrees, reinterpret_cast<const CVector3*>(&frame->modelling.pos),
                               reinterpret_cast<const CVector3*>(&frame->modelling.up));  // 0x000d0f80
    } else {
        node->SetIdentity();  // 0x000d08f0 CSGMovable_SetIdentity (RwFrameSetIdentity)
    }
    PlayAnim(start, index & 0xffffu);  // vt+0x60 with the index's low half
    HandleOf(this)->Reset();  // 0x00165af8
    m_bActive = 1;
    m_fSpeed = data->GetSpeed(index);   // vt+0x54
    m_fUnk1c = data->GetUnk74(index);   // vt+0x58
    return 1;
}

// 0x005bfad8 CKAnimatedCamera_Update_maybe: the hot spot's world position and its world matrix's at axis; an inactive
// handle is activated there (ScriptedCameraHandle_TryActivate_maybe 0x165eb8: fov scale 1.0, blend +0x1c, not forced;
// refused, the camera ends), an active one is moved there (_SetPositionAndTarget_maybe 0x165a78); then the animation
// runs at +0x18 and past its end the handle is released and the camera ends.
uint8_t CKAnimatedCamera::Update(float dt) {
    if (m_bActive == 0) return 0;
    CSGHotSpot* hotSpot = static_cast<CSGHotSpot*>(m_apUnk04[2]);
    CVector3 position;
    hotSpot->GetWorldPosition(&position);  // 0x000ce790
    alignas(16) CMatrix34 matrix;
    hotSpot->GetWorldMatrix(&matrix);  // 0x000ce970
    const CVector3 direction = matrix.m_at;
    CKCameraEventCpnt* handle = HandleOf(this);
    if (HandleActive(handle) == 0) {
        if (handle->TryActivate(&position, &direction, 1.0f, m_fUnk1c, 0) == 0) {  // TOC2 -0x61a0 1.0
            m_bActive = 0;
            m_fUnk1c = 0.2f;  // TOC2 -0x619c
            m_fSpeed = 1.0f;
            return 0;
        }
    } else {
        handle->SetPositionAndTarget(1.0f, &position, &direction);
    }
    CAnimatedNode* node = NodeOf(this);
    node->AddAnimTime(static_cast<double>(dt * m_fSpeed));
    const float now = node->GetAnimTimeNow();
    if (!(now > node->GetCurrentAnimDuration())) return 1;  // ble: a NaN keeps it running
    handle->Release();  // 0x00166130
    m_fUnk1c = 0.2f;
    m_bActive = 0;
    m_fSpeed = 1.0f;
    return 0;
}
