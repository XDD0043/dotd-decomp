// CKSparkNodeFx.cpp - reconstructed original translation unit 0x1d3e68-0x1d4890 (GAME_TOC1, main_toc1), 28 functions, 23 live.
// Primary class: CKSparkNodeFx  key 0x244c  category Logic  size 0x1c  vtable 0xb1d970
// Other owners: StopOwnedSparkEffect (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1d3e68  CKSparkNodeFx_Delete
//   [x] 0x1d3eb8  CKSparkNodeFx_ExtraSlot9C
//   [x] 0x1d3f80  KStub_Nop_1d3f80  (empty: CKHkPushKillObject_UpdateVolumesAndFx_maybe's call does nothing)
//   [x] 0x1d3f88  CKSparkNodeFx_SetParamVec2_40_maybe
//   [ ] 0x1d3fa8  FUN_001d3fa8  [dead]
//   [x] 0x1d3fd8  CKSparkNodeFx_SetParamVec2_50_maybe
//   [ ] 0x1d3ff8  FUN_001d3ff8  [dead]
//   [x] 0x1d4028  CKSparkNodeFx_SetParamFloat_68_maybe
//   [ ] 0x1d4038  FUN_001d4038  [dead]
//   [x] 0x1d4048  CKSparkNodeFx_SetParamVec3_10_maybe
//   [ ] 0x1d4078  FUN_001d4078  [dead]
//   [x] 0x1d40b0  CKSparkNodeFx_SetParamVec3_1c_maybe
//   [ ] 0x1d40e0  FUN_001d40e0  [dead]
//   [ ] 0x1d4118  RegisterCKSparkNodeFxClass
//   [ ] 0x1d4190  _GLOBAL__I_1d4190
//   [x] 0x1d41a0  CKSparkNodeFx_Stop
//   [x] 0x1d4260  CKSparkNodeFx_Start
//   [x] 0x1d44a0  CKSparkNodeFx_PostLoad  (= the inherited slot)
//   [x] 0x1d44c8  CKSparkNodeFx_Load
//   [ ] 0x1d4520  CKSparkNodeFx_Save
//   [x] 0x1d4548  CKSparkNodeFx_RecursiveRegistration
//   [x] 0x1d4570  CKSparkNodeFx_Destroy  (inherited: CKNodeFx3d_Destroy)
//   [x] 0x1d4598  CKSparkNodeFx_DeleteArray
//   [x] 0x1d4640  CKSparkNodeFx_Create
//   [x] 0x1d4698  StopOwnedSparkEffect_maybe
//   [x] 0x1d46c8  CKSparkNodeFx_ExtraSlotA0
//   [x] 0x1d4788  CKSparkNodeFx_Update
//   [x] 0x1d47d8  CKSparkNodeFx_CreateArray
//
//   [ ] 0x9ad3f0  CKSparkNodeFx_IsKindOfClass  [inline]
//   [x] 0x9ad428  CKSparkNodeFx_GetClassType  [inline]
//   [x] 0x9ad430  CKSparkNodeFx_GetClassID  [inline]
//   [x] 0x9ad438  CKSparkNodeFx_GetFxData  [inline]
//   [x] 0x9ad440  CKSparkNodeFx_SetFxData  [inline]
//   [ ] 0x9ad448  CKSparkNodeFx_DeletingDestruct  [inline]
//   [ ] 0x9ad490  CKSparkNodeFx_Destruct  [inline]
#include "k2000/logic/fx/CKSparkNodeFx.h"
#include "k2000/scenegraph/CNode.h"

#include "k2000/io/IKFile.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CKSparkParam.h"
#include "k2000/scenegraph/CSparkNodeFx.h"
#include "k2000/fx/CKSparkFxData.h"

// 0x001d44c8 CKSparkNodeFx_Load
int32_t CKSparkNodeFx::Load(IKFile* file, int32_t type) {
    IKNodeFx::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) m_pSparkNode = m_pNode;
    return 1;
}

// 0x001d3eb8 CKSparkNodeFx_ExtraSlot9C (TOC1 -0x19e0 the engine, +0x14 the dynamic scene root).
void CKSparkNodeFx::ReparentNode(IKSerializable* parent) {
    CNode* node = m_pNode;
    IKSerializable* target = parent != nullptr ? parent : g_pEngine->m_dynamicSceneRoot;
    CSGBranch* current = node->m_pParent;
    if (target == current) return;
    if (current != nullptr) current->RemoveChild(node);   // vt+0x78
    static_cast<CSGBranch*>(target)->AddChild(m_pNode);   // vt+0x70
}

// 0x001d46c8 CKSparkNodeFx_ExtraSlotA0
void CKSparkNodeFx::AttachNodeToHotSpot(IKSerializable* hotSpot) {
    if (hotSpot == nullptr) {
        ReparentNode(nullptr);  // vt+0x9c
        return;
    }
    CNode* node = m_pNode;
    if (node->m_pParent != nullptr) node->m_pParent->RemoveChild(node);  // vt+0x78
    static_cast<CSGHotSpot*>(hotSpot)->AttachVolume(m_pNode);  // 0x000ce2b8
}

// 0x001d4260 CKSparkNodeFx_Start
void CKSparkNodeFx::Vf64() {
    m_baFxData = static_cast<uint8_t>(m_baFxData & 0xfeu);
    Vf5C();  // vt+0x5c show
    CKSparkFxData* data = static_cast<CKSparkFxData*>(m_pFxData);
    CSparkNodeFx* spark = static_cast<CSparkNodeFx*>(m_pSparkNode);
    if (data->m_unk10 != nullptr) {
        AttachNodeToHotSpot(data->m_unk10);  // vt+0xa0 (twice, as the original)
        AttachNodeToHotSpot(data->m_unk10);
        RwMatrix local = spark->m_pRwFrame->modelling;
        RwMatrixTransform(&local, static_cast<const RwMatrix*>(data->m_unk14), rwCOMBINEPOSTCONCAT);  // 0x0023f760
        spark->SetLocalMatrix(&local);  // 0x000d0be8
    } else {
        ReparentNode(data->m_unk0c);  // vt+0x9c
        spark->SetLocalMatrix(static_cast<const RwMatrix*>(data->m_unk14));
    }
    spark->ForceWorldMatrixUpdate();  // vt+0x50
    spark->SetParams(static_cast<CKSparkParam*>(data->m_pSparkParam));  // 0x000e7b20
    spark->InitSparks();  // 0x000e9250
}

// 0x001d41a0 CKSparkNodeFx_Stop
void CKSparkNodeFx::Stop() {
    m_baFxData = static_cast<uint8_t>((m_baFxData & 0xfeu) | 1u);
    Vf60();  // vt+0x60 hide
    CSparkNodeFx* spark = static_cast<CSparkNodeFx*>(m_pSparkNode);
    if (spark->m_unk40 != 0) spark->ReleaseAllSparks();  // 0x000e7c90
    ReparentNode(nullptr);  // vt+0x9c
    static_cast<CSparkNodeFx*>(m_pSparkNode)->m_pSparkParam->m_pTexture94 = nullptr;
}

// 0x001d4788 CKSparkNodeFx_Update
void CKSparkNodeFx::Update(IKTime* /*frameClock*/) {
    if (static_cast<CSparkNodeFx*>(m_pSparkNode)->m_unk40 == 0) Stop();  // vt+0x6c
}

// 0x001d4698 StopOwnedSparkEffect_maybe
void StopOwnedSparkEffect(CKSparkNodeFx* effect, const IKSerializable* owner) {
    if ((effect->m_baFxData & 2u) == 0) return;
    if (effect->m_pOwner != owner) return;
    static_cast<CSparkNodeFx*>(effect->m_pSparkNode)->m_unk41 = 1;
}

namespace {
CKSparkParam* SparkParam(CNode* node) { return reinterpret_cast<CSparkNodeFx*>(node)->m_pSparkParam; }  // +0x18 -> +0x50
}  // namespace

// 0x001d3f88 CKSparkNodeFx_SetParamVec2_40_maybe
void CKSparkNodeFx::SetParamVec2_40(const float* v) {
    CKSparkParam* param = SparkParam(m_pSparkNode);
    param->m_afUnk04[15] = v[0];  // +0x40
    param->m_afUnk04[16] = v[1];
}

// 0x001d3fd8 CKSparkNodeFx_SetParamVec2_50_maybe
void CKSparkNodeFx::SetParamVec2_50(const float* v) {
    CKSparkParam* param = SparkParam(m_pSparkNode);
    param->m_afUnk04[19] = v[0];  // +0x50
    param->m_afUnk04[20] = v[1];
}

// 0x001d4028 CKSparkNodeFx_SetParamFloat_68_maybe
void CKSparkNodeFx::SetParamFloat_68(float value) { SparkParam(m_pSparkNode)->m_afUnk04[25] = value; }  // +0x68

// 0x001d4048 CKSparkNodeFx_SetParamVec3_10_maybe
void CKSparkNodeFx::SetParamVec3_10(const float* v) {
    CKSparkParam* param = SparkParam(m_pSparkNode);
    param->m_afUnk04[5] = v[2];  // +0x10..+0x18
    param->m_afUnk04[3] = v[0];
    param->m_afUnk04[4] = v[1];
}

// 0x001d40b0 CKSparkNodeFx_SetParamVec3_1c_maybe
void CKSparkNodeFx::SetParamVec3_1c(const float* v) {
    CKSparkParam* param = SparkParam(m_pSparkNode);
    param->m_afUnk04[8] = v[2];  // +0x1c..+0x24
    param->m_afUnk04[6] = v[0];
    param->m_afUnk04[7] = v[1];
}

// 0x001d4548 CKSparkNodeFx_RecursiveRegistration: IKNodeFx's (0x1d88c0 CKNodeFx3d_LevelReset): the node's
// registration (its vt+0x24) when there is one.
void CKSparkNodeFx::RecursiveRegistration(int32_t type) {
    IKNodeFx::RecursiveRegistration(type);
}
