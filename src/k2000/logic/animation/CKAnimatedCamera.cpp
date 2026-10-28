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
//   [ ] 0x5c0120  CKAnimatedCamera_RecursiveRegistration
//   [x] 0x5c0128  CKAnimatedCamera_PostLoad
//   [ ] 0x5c0170  CKAnimatedCamera_Destroy
//   [x] 0x5c0178  CKAnimatedCamera_Load
//   [ ] 0x5c03a0  CKAnimatedCamera_Save
//   [ ] 0x5c05d8  CKAnimatedCamera_DeletingDestructor
//   [ ] 0x5c0618  CKAnimatedCamera_Destructor
//   [ ] 0x5c0630  CKAnimatedCamera_Destructor_2  [dead]
//
//   [ ] 0x9cd230  CKAnimatedCamera_GetClassType  [inline]
//   [ ] 0x9cd238  CKAnimatedCamera_GetClassID  [inline]
//   [ ] 0x9cd240  CKAnimatedCamera_IsKindOfClass  [inline]
#include "k2000/logic/animation/CKAnimatedCamera.h"

#include "k2000/components/CKCameraEventCpnt.h"
#include "k2000/core/Stub.h"
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
// The handle's byte at +0x10 (set while the handle is active: ScriptedCameraHandle_Activate_maybe 0x165bd8).
uint8_t HandleActive(const CKCameraEventCpnt* handle) { return reinterpret_cast<const uint8_t*>(&handle->m_unk10)[0]; }
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
    if (HandleActive(HandleOf(this)) == 0) {
        // ScriptedCameraHandle_Release_maybe 0x166130 (k2000/components/CKCameraEventCpnt.cpp). STUB(C2.8): the scripted
        // camera handles are scripting.
        DOTD_STUB_ONCE("CKAnimatedCamera_End_maybe: ScriptedCameraHandle_Release_maybe 0x166130 (C2.8)");
    }
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
        // camera's real heading (CKSrvCamera +0x5c8) and the node's (LTM at, +0x70), in degrees (x 57.29578f):
        // Vec3_GetYawAngleFromZ 0x244528 and CSGMovable_RotateAboutPoint_maybe 0xd0f80. STUB(C2.7): the turn needs
        // RwFrameRotate / RwFrameTranslate (not ported); only the heroes' abilities start an animated camera.
        DOTD_STUB_ONCE("CKAnimatedCamera_Start_maybe: CSGMovable_RotateAboutPoint_maybe 0xd0f80 (C2.7)");
    } else {
        // CSGMovable_SetIdentity 0xd08f0 (RwFrameSetIdentity). STUB(C2.7): as above.
        DOTD_STUB_ONCE("CKAnimatedCamera_Start_maybe: CSGMovable_SetIdentity 0xd08f0 (C2.7)");
    }
    PlayAnim(start, index & 0xffffu);  // vt+0x60 with the index's low half
    // ScriptedCameraHandle_Reset_maybe 0x165af8 (CKCameraEventCpnt.cpp). STUB(C2.8): the scripted camera handles.
    DOTD_STUB_ONCE("CKAnimatedCamera_Start_maybe: ScriptedCameraHandle_Reset_maybe 0x165af8 (C2.8)");
    m_bActive = 1;
    m_fSpeed = data->GetSpeed(index);   // vt+0x54
    m_fUnk1c = data->GetUnk74(index);   // vt+0x58
    return 1;
}

// 0x005bfad8 CKAnimatedCamera_Update_maybe. The handle's activation (ScriptedCameraHandle_TryActivate_maybe 0x165eb8,
// weight 1.0, with the hot spot's position and its world matrix's at axis) and pose (ScriptedCameraHandle_
// SetPositionAndTarget_maybe 0x165a78) are scripting: STUB(C2.8); without them TryActivate counts as refused (the camera
// ends, as the original does when the service refuses). CSGHotSpot_GetWorldMatrix 0xce970 only feeds them.
uint8_t CKAnimatedCamera::Update(float dt) {
    if (m_bActive == 0) return 0;
    CVector3 position;
    static_cast<CSGHotSpot*>(m_apUnk04[2])->GetWorldPosition(&position);  // 0x000ce790
    CKCameraEventCpnt* handle = HandleOf(this);
    if (HandleActive(handle) == 0) {
        DOTD_STUB_ONCE("CKAnimatedCamera_Update_maybe: ScriptedCameraHandle_TryActivate_maybe 0x165eb8 (C2.8)");
        m_bActive = 0;
        m_fUnk1c = 0.2f;
        m_fSpeed = 1.0f;
        return 0;
    }
    DOTD_STUB_ONCE("CKAnimatedCamera_Update_maybe: ScriptedCameraHandle_SetPositionAndTarget_maybe 0x165a78 (C2.8)");
    CAnimatedNode* node = NodeOf(this);
    node->AddAnimTime(static_cast<double>(dt * m_fSpeed));
    const float now = node->GetAnimTimeNow();
    if (now <= node->GetCurrentAnimDuration()) return 1;
    // ScriptedCameraHandle_Release_maybe 0x166130. STUB(C2.8).
    DOTD_STUB_ONCE("CKAnimatedCamera_Update_maybe: ScriptedCameraHandle_Release_maybe 0x166130 (C2.8)");
    m_fUnk1c = 0.2f;
    m_bActive = 0;
    m_fSpeed = 1.0f;
    return 0;
}
