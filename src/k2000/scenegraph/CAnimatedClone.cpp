// CAnimatedClone.cpp - reconstructed original translation unit 0xc8278-0xc8b70 (GAME_TOC1, main_toc1), 17 functions, 15 live.
// Primary class: CAnimatedClone  key 0x58b  category SceneNode  size 0x70  vtable 0xb17dd0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xc8278  CAnimatedClone_Delete  (DOTD_DECLARE_FACTORIES, CAnimatedClone.h; port-final F05)
//   [x] 0xc82c8  CAnimatedClone_RecursiveRegistration  (the header: nothing registered)
//   [ ] 0xc82d0  RegisterCAnimatedCloneClass
//   [ ] 0xc8348  _GLOBAL__I_c8348
//   [x] 0xc8358  CAnimatedClone_vf58  (CAnimatedClone::UpdateAndExtract)
//   [x] 0xc8500  CAnimatedClone_PostLoad
//   [ ] 0xc8528  CAnimatedClone_Save
//   [x] 0xc8550  CAnimatedClone_Destroy
//   [x] 0xc85a0  CAnimatedClone_DeletingDestructor  (~CAnimatedClone, the header; delete)
//   [x] 0xc85e8  CAnimatedClone_Destructor  (~CAnimatedClone, the header)
//   [ ] 0xc8618  CAnimatedClone_BaseDestructor  [dead: no pointer to its descriptor 0xb4e430]
//   [ ] 0xc8648  CAnimatedClone_Construct  [dead]
//   [ ] 0xc8690  CAnimatedClone_Construct_2  [dead]
//   [x] 0xc86d8  CAnimatedClone_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0xc8780  CAnimatedClone_CreateArray  (DOTD_DECLARE_FACTORIES: 0x70-byte elements, each constructed as Create's)
//   [x] 0xc8850  CAnimatedClone_Create  (the header's constructor, DOTD_DECLARE_FACTORIES)
//   [x] 0xc88b8  CAnimatedClone_Load
//
//   [x] 0x9a23c0  CAnimatedClone_IsKindOfClass  [inline]
//   [x] 0x9a2420  CAnimatedClone_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9a2428  CAnimatedClone_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9a2430  CAnimatedClone_GetSerializationFlags  [inline]
//   [x] 0x9a2438  CAnimatedClone_vf7C  [inline]  (SetNbLods)
//   [x] 0x9a2440  CAnimatedClone_vf80  [inline]  (GetNbLods)
//   [ ] 0x9a2448  KStub_Return2_9a2448  [inline]
//   [ ] 0x9a2450  KStub_Nop_9a2450  [inline]
//   [ ] 0x9a2458  KStub_Return0_9a2458  [inline]
#include "k2000/scenegraph/CAnimatedClone.h"

#include "Renderware/rpteam/RpTeam.h"
#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/animation/AnimBlendSlot.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/io/IKFile.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGMovable.h"

// 0x000c88b8 CAnimatedClone_Load. The halfwords come in one 4-byte read, each half swapped (lhbrx).
int32_t CAnimatedClone::Load(IKFile* file, int32_t type) {
    CNode::Load(file, type);  // 0x000cbd28
    if ((m_sgProperties & 1) == 0) {
        m_unk5c = 0xffffffffu;
    } else {
        ReadU32LE(file, &m_unk5c);
    }
    IKFile_ReadRef(file, &m_pAttachmentHead);
    ReadU16LE(file, &m_ui16NumOriginal);
    ReadU16LE(file, &m_ui16NbLods);
    IKFile_ReadRef(file, &m_pController);
    ReadU32LEWords(file, m_aUnk4c, 4);
    if (((m_sgProperties >> 9) & 3) == 2) AnimBlendSlot_LoadThunk(&m_blendSlot, file, type);  // 0x00079d98
    ReadF32LE(file, &m_unk60);
    return 1;
}

// 0x000c8500 CAnimatedClone_PostLoad
int32_t CAnimatedClone::PostLoad(int32_t type) {
    CAnimatedNode::PostLoad(type);  // 0x000c9d48
    return 1;
}

// 0x000c8550 CAnimatedClone_Destroy
void CAnimatedClone::Destroy() {
    if (m_pRpHAnimHierarchy != nullptr) {
        m_pRpHAnimHierarchy->currentAnim->pCurrentAnim = nullptr;
        m_pRpHAnimHierarchy = nullptr;
    }
    m_pRwPlayerBSphere = nullptr;
    CAnimatedNode::Destroy();  // 0x000c92e0
}

// 0x000c8358 CAnimatedClone_vf58. The camera is the renderer's (0x00c5c90c +0x28) camera's frame position (+0x80 as it is,
// no RwFrameGetLTM sync); the squared distance is fused (dy*dy, then dx and dz fmadds); ble: an unordered distance is
// near. The stamp is the render frame counter as a word in the player's +0xf4.
void CAnimatedClone::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** stages, IKTime* frameClock,
                                      RwCamera* camera, int32_t /*distanceCull*/) {
    if ((m_sgProperties & 4) != 0) return;
    float sphere[4];
    const uint32_t visible = UpdatePoseAndCull(stages, frameClock, sphere, m_pRwPlayerBSphere, camera);  // 0x000cabc8
    uint32_t tooFar = 0;
    if ((m_sgProperties & 0x100) != 0 && ((m_sgProperties >> 7) & 1) != 0) {  // 0x000cbab8
        tooFar = 1;
        const float* world = m_pRwPlayerBSphere;
        const CameraContext* context = g_pRenderStateRenderer->m_cameraContext;
        const RwV3d& position = static_cast<const CSGMovable*>(context->m_pCamera)->m_pRwFrame->ltm.pos;
        const float dy = position.y - world[1];
        const float dx = position.x - world[0];
        const float dz = position.z - world[2];
        const float distance = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        if (!(distance > m_fDistanceLimitSquared)) tooFar = 0;
    }
    if (visible != 0 && tooFar == 0) {
        m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
        RpTeamPlayer* player = m_pTeamPlayer;
        player->unkF4 = g_ui16RenderFrameCounter;
        if (visible == 1) {
            player->flags |= 0x10;
        } else {
            player->flags &= ~0x10u;
        }
    }
    m_pRwFrame->object.privateFlags = static_cast<uint8_t>(m_pRwFrame->object.privateFlags & 0xf7);
}
