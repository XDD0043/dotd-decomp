// CSGPointLight.cpp - reconstructed original translation unit 0xd2338-0xd29c8 (GAME_TOC1, main_toc1), 12 functions, 10 live.
// Primary class: CSGPointLight  key 0x94b  category SceneNode  size 0x24  vtable 0xb18348
// Other owners: SceneNode (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xd2338  RegisterCSGPointLightClass
//   [ ] 0xd23b0  _GLOBAL__I_d23b0
//   [x] 0xd23c0  CSGPointLight_PostLoad
//   [x] 0xd2418  CSGPointLight_Load
//   [ ] 0xd2568  CSGPointLight_Save
//   [x] 0xd26c8  CSGPointLight_Destroy
//   [x] 0xd2710  CSGPointLight_DeleteArray
//   [x] 0xd27b8  CSGPointLight_CreateArray
//   [ ] 0xd2870  FUN_000d2870  [dead]
//   [ ] 0xd2910  SceneNode_GetParent_maybe  [dead]
//   [x] 0xd2918  CSGPointLight_Enqueue
//   [x] 0xd2970  CSGPointLight_Create
//
//   [ ] 0x9a2950  CSGPointLight_IsKindOfClass  [inline]
//   [ ] 0x9a2988  CSGPointLight_GetClassType  [inline]
//   [ ] 0x9a2990  CSGPointLight_GetClassID  [inline]
//   [ ] 0x9a2998  CSGPointLight_DeletingDestructor  [inline]
//   [ ] 0x9a29e0  CSGPointLight_Destructor  [inline]
#include "k2000/scenegraph/CSGPointLight.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/render/CLightComponent.h"
#include "k2000/render/CRenderer.h"

// 0x000d23c0 CSGPointLight_PostLoad
int32_t CSGPointLight::PostLoad(int32_t type) {
    CSGLeaf::PostLoad(type);  // 0xcf0f8
    if (type == K_LEVEL_PLATEFORMS) static_cast<CLightComponent*>(m_pLight)->m_pLightFrame = m_pRwFrame;
    return 1;
}

// 0x000d2418 CSGPointLight_Load
int32_t CSGPointLight::Load(IKFile* file, int32_t type) {
    CSGLeaf::Load(file, type);  // 0xcf550
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadObjectRefArray(file, &m_pLight, 1);  // the resolver's vt+0x28 (count 1)
        ReadF32LE(file, &m_unk1c);
        ReadRaw(file, &m_unk18, 1);
    }
    return 1;
}

// 0x000d2918 CSGPointLight_Enqueue
void CSGPointLight::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** /*stages*/, IKTime* frameClock, RwCamera* /*camera*/,
                                     int32_t /*distanceCull*/) {
    static_cast<CLightComponent*>(m_pLight)->UpdateColorAnimation(frameClock);
    if ((m_sgProperties & 4) == 0) m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
}

// C2.8 port-all P11.

// 0x000d26c8 CSGPointLight_Destroy
void CSGPointLight::Destroy() {
    CSGLeaf::Destroy();  // 0x000ceda8
    if (m_pLight != nullptr) m_pLight = nullptr;
}
