// CKBlurNodeFx.cpp - reconstructed original translation unit 0x571be0-0x5721e0 (GAME_TOC2, main_toc2), 14 functions, 14 live.
// Primary class: CKBlurNodeFx  key 0x30c  category Logic  size ?  vtable 0xb2dd80
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x571be0  CKBlurNodeFx_Delete
//   [x] 0x571c30  CKBlurNodeFx_Destroy  (CKBlurNodeFx.h: empty (IKNodeFx's is not called))
//   [x] 0x571c38  CKBlurNodeFx_RecursiveRegistration
//   [x] 0x571c90  CKBlurNodeFx_PostLoad
//   [x] 0x571c98  CKBlurNodeFx_Start
//   [ ] 0x571d38  RegisterCKBlurNodeFxClass
//   [ ] 0x571db0  _GLOBAL__I_571db0
//   [x] 0x571dc0  CKBlurNodeFx_Load
//   [ ] 0x571de8  CKBlurNodeFx_Save
//   [x] 0x571e10  CKBlurNodeFx_DeleteArray
//   [x] 0x571eb0  CKBlurNodeFx_CreateArray
//   [x] 0x571f60  CKBlurNodeFx_Update
//   [x] 0x572080  CKBlurNodeFx_Stop
//   [x] 0x572188  CKBlurNodeFx_Create
//
//   [ ] 0x9cad08  CKBlurNodeFx_IsKindOfClass  [inline]
//   [x] 0x9cad40  CKBlurNodeFx_GetClassType  [inline]
//   [x] 0x9cad48  CKBlurNodeFx_GetClassID  [inline]
//   [x] 0x9cad50  CKBlurNodeFx_GetFxData  [inline]
//   [x] 0x9cad58  CKBlurNodeFx_SetFxData  [inline]
//   [ ] 0x9cad60  CKBlurNodeFx_Destruct  [inline]
//   [ ] 0x9cad80  CKBlurNodeFx_DeletingDestruct  [inline]
#include "k2000/logic/fx/CKBlurNodeFx.h"

#include "k2000/graphical/CBlurData.h"
#include "k2000/graphical/render/CPostRenderingFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/fx/CKBlurFxData.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/IKTime.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

namespace {
CPostRenderingFx* PostRenderingFx() {
    return static_cast<CPostRenderingFx*>(g_pEngine->m_coreManager->GetObjectByClassKey(0x38d));  // vt+0x58
}
}  // namespace

// 0x00571dc0 CKBlurNodeFx_Load
int32_t CKBlurNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);  // through TocBridge_IKNodeFx_Load
    return 1;
}

// 0x00571c98 CKBlurNodeFx_Start
void CKBlurNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfe);
    CPostRenderingFx* postFx = PostRenderingFx();
    postFx->m_BitProperties = (postFx->m_BitProperties & 0xfffffeffu) | 0x100u;
    postFx->m_pBlurData = static_cast<CKBlurFxData*>(m_pFxData)->m_unk08;
    m_fTime = 0.0f;  // stw 0
}

// 0x00572080 CKBlurNodeFx_Stop
void CKBlurNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfe) | 1);
    CPostRenderingFx* postFx = PostRenderingFx();
    if (postFx->m_pBlurData == static_cast<CKBlurFxData*>(m_pFxData)->m_unk08) {
        postFx->m_BitProperties &= 0xfffffeffu;
    }
    Vf60();  // vt+0x60
}

// 0x00571f60 CKBlurNodeFx_Update (vt+0x78)
void CKBlurNodeFx::Update(IKTime* frameClock) {
    CPostRenderingFx* postFx = PostRenderingFx();
    CKBlurFxData* data = static_cast<CKBlurFxData*>(m_pFxData);
    if (postFx->m_pBlurData == data->m_unk08) {
        if ((data->m_unk0c & 1u) == 0) return;
        m_fTime = m_fTime + frameClock->m_afDeltaTime[0];
        if (data->m_unk10 > m_fTime) {
            static_cast<CBlurData*>(static_cast<CKBlurFxData*>(m_pFxData)->m_unk08)->m_fBlurGlobalIntensity =
                BlurCurve_EvaluateLinear(m_fTime, data);  // 0x005712a8
            return;
        }
    }
    Stop();  // vt+0x6c
}

// 0x00571c38 CKBlurNodeFx_RecursiveRegistration
void CKBlurNodeFx::RecursiveRegistration(int32_t /*type*/) {
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
}
