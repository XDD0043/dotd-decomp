// CKPointLightNodeFx.cpp - reconstructed original translation unit 0x1cfb08-0x1d0470 (GAME_TOC1, main_toc1), 14 functions, 14 live.
// Primary class: CKPointLightNodeFx  key 0xaa4c  category Logic  size 0x2c  vtable 0xb1d5e8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1cfb08  CKPointLightNodeFx_Delete
//   [x] 0x1cfb58  CKPointLightNodeFx_RecursiveRegistration
//   [ ] 0x1cfbb0  RegisterCKPointLightNodeFxClass
//   [ ] 0x1cfc28  _GLOBAL__I_1cfc28
//   [x] 0x1cfc38  CKPointLightNodeFx_PostLoad
//   [x] 0x1cfc98  CKPointLightNodeFx_Load
//   [ ] 0x1cfd58  CKPointLightNodeFx_Save
//   [x] 0x1cfd80  CKPointLightNodeFx_Destroy  (inherited: CKNodeFx3d_Destroy)
//   [x] 0x1cfda8  CKPointLightNodeFx_DeleteArray
//   [x] 0x1cfe48  CKPointLightNodeFx_Create
//   [x] 0x1cfea0  CKPointLightNodeFx_Start
//   [x] 0x1d0130  CKPointLightNodeFx_Stop
//   [x] 0x1d0218  CKPointLightNodeFx_CreateArray
//   [x] 0x1d02c8  CKPointLightNodeFx_Update
//
//   [ ] 0x9acf70  CKPointLightNodeFx_IsKindOfClass  [inline]
//   [x] 0x9acfb0  CKPointLightNodeFx_GetClassType  [inline]
//   [x] 0x9acfb8  CKPointLightNodeFx_GetClassID  [inline]
//   [x] 0x9acfc0  CKPointLightNodeFx_GetFxData  [inline]
//   [x] 0x9acfc8  CKPointLightNodeFx_SetFxData  [inline]
//   [ ] 0x9acfd0  CKPointLightNodeFx_Destruct  [inline]
//   [ ] 0x9acff0  CKPointLightNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/render/CKPointLightNodeFx.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/render/CKPointLightFxData.h"
#include "k2000/logic/render/CLightComponent.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGPointLight.h"
#include "k2000/system/IKTime.h"

namespace {
// The light takes the data's colour (a word copy), radius (+0x1c) and intensity (the component's +0x10) at `t`.
void ApplyCurves(CSGPointLight* light, const CKPointLightFxData* data, float t) {
    uint8_t color[4];
    data->EvaluateColorLooped(t, color);  // 0x001cf430
    std::memcpy(static_cast<CLightComponent*>(light->m_pLight)->m_cLightColor, color, 4);
    light->m_unk1c = data->EvaluateIntensityLooped(t);  // 0x001cf810
    static_cast<CLightComponent*>(light->m_pLight)->m_fRadius = data->EvaluateRadiusLooped(t);  // 0x001cf898
}
void SetFramePosition(CSGPointLight* light, float x, float y, float z) {
    RwFrame* frame = light->m_pRwFrame;
    frame->modelling.pos = {x, y, z};
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}
}  // namespace

// 0x001cfc98 CKPointLightNodeFx_Load
int32_t CKPointLightNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pPointLight);
    return 1;
}

// 0x001cfc38 CKPointLightNodeFx_PostLoad: IKNodeFx_PostLoad; for the level type the light's byte at +0x18 (the file's
// last byte) is set to the type (0: stb r31).
int32_t CKPointLightNodeFx::PostLoad(int32_t type) {
    IKNodeFx::PostLoad(type);
    if (type == K_LEVEL_PLATEFORMS && m_pPointLight != nullptr) {
        static_cast<CSGPointLight*>(m_pPointLight)->m_unk18 = static_cast<uint8_t>(type);
    }
    return 1;
}

// 0x001cfea0 CKPointLightNodeFx_Start
void CKPointLightNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>((m_baFxData | 2u) & 0xfeu);
    m_fTime = 0.0f;  // stw 0
    m_vOffset = {0.0f, 0.0f, 0.0f};  // TOC -0x1b24: the vector at 0x00c50d64
    CSGPointLight* light = static_cast<CSGPointLight*>(m_pPointLight);
    if (light == nullptr) return;
    const CKPointLightFxData* data = static_cast<const CKPointLightFxData*>(m_pFxData);
    ApplyCurves(light, data, m_fTime);
    SetFramePosition(light, data->m_vPosition.x, data->m_vPosition.y, data->m_vPosition.z);
    if (data->m_pAttachNode != nullptr) {
        if (light->m_pParent != nullptr) light->m_pParent->RemoveChild(light);  // vt+0x78
        static_cast<CSGBranch*>(data->m_pAttachNode)->AddChild(light);  // vt+0x70
    } else if (data->m_pAttachHotSpot != nullptr) {
        if (light->m_pParent != nullptr) light->m_pParent->RemoveChild(light);
        static_cast<CSGHotSpot*>(data->m_pAttachHotSpot)->AttachVolume(light);  // 0x000ce2b8
        const RwV3d& pos = light->m_pRwFrame->modelling.pos;
        m_vOffset = {pos.x, pos.y, pos.z};
    }
    light->m_unk18 = 1;
    light->m_sgProperties &= 0xfffffffbu;
}

// 0x001d0130 CKPointLightNodeFx_Stop
void CKPointLightNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    CSGPointLight* light = static_cast<CSGPointLight*>(m_pPointLight);
    if (light == nullptr) return;
    if (light->m_pParent != nullptr) light->m_pParent->RemoveChild(light);  // vt+0x78
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(light);  // vt+0x70
    light->m_unk18 = 0;
    light->m_sgProperties = (light->m_sgProperties & 0xfffffffbu) | 4u;
}

// 0x001d02c8 CKPointLightNodeFx_Update (vt+0x78)
void CKPointLightNodeFx::Update(IKTime* frameClock) {
    m_fTime = m_fTime + frameClock->m_afDeltaTime[0];
    CSGPointLight* light = static_cast<CSGPointLight*>(m_pPointLight);
    if (light == nullptr) return;
    const CKPointLightFxData* data = static_cast<const CKPointLightFxData*>(m_pFxData);
    ApplyCurves(light, data, m_fTime);
    data = static_cast<const CKPointLightFxData*>(m_pFxData);
    SetFramePosition(light, m_vOffset.x + data->m_vPosition.x, m_vOffset.y + data->m_vPosition.y,
                     m_vOffset.z + data->m_vPosition.z);
    const float life = static_cast<const CKPointLightFxData*>(m_pFxData)->m_unk20;
    const float zero = 0.0f;  // TOC -0x1b20
    if ((life > zero || life == zero) && (m_fTime > life || m_fTime == life)) Stop();  // cror gt|eq twice; vt+0x6c
}

// 0x001cfb58 CKPointLightNodeFx_RecursiveRegistration
void CKPointLightNodeFx::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
