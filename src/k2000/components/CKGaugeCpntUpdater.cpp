// CKGaugeCpntUpdater.cpp - reconstructed original translation unit 0x24b2e0-0x24bc70 (GAME_TOC1, main_toc1), 15 functions, 13 live.
// Primary class: CKGaugeCpntUpdater  key 0x1486  category Component  size 0x20  vtable 0xb20d98
// Other owners: GaugeSample (2), SuperGaugeRecord (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x24b2e0  RegisterCKGaugeCpntUpdaterClass
//   [ ] 0x24b358  _GLOBAL__I_24b358
//   [x] 0x24b368  CKGaugeCpntUpdater_Update_maybe
//   [x] 0x24b438  CKGaugeCpntUpdater_DeleteArray
//   [x] 0x24b4d8  CKGaugeCpntUpdater_Create
//   [ ] 0x24b510  GaugeSample_ApplyToElement2dPtr_maybe  [dead]
//   [x] 0x24b600  GaugeSample_ApplyToElement2d_maybe
//   [x] 0x24ba10  CKGaugeCpntUpdater_CreateArray
//   [ ] 0x24baa0  SuperGaugeRecord_Init_maybe  [dead]
//   [ ] 0x24bac8  CKGaugeCpntUpdater_Save
//   [x] 0x24bad0  CKGaugeCpntUpdater_Load
//   [x] 0x24bb60  CKGaugeCpntUpdater_PostLoad
//   [x] 0x24bb90  CKGaugeCpntUpdater_RecursiveRegistration  (returns 1, registers nothing: the default)
//   [x] 0x24bb98  CKGaugeCpntUpdater_Destroy  (empty: the default)
//   [x] 0x24bba0  CKGaugeCpntUpdater_EvaluateSample_maybe  (EvaluateSample; no caller in the original either)
//
//   [ ] 0x9b9f18  CKGaugeCpntUpdater_IsKindOfClass  [inline]
//   [x] 0x9b9f40  CKGaugeCpntUpdater_GetClassType  [inline]
//   [x] 0x9b9f48  CKGaugeCpntUpdater_GetClassID  [inline]
//   [ ] 0x9b9f50  CKGaugeCpntUpdater_DeletingDestructor  [inline]
//   [ ] 0x9b9f98  CKGaugeCpntUpdater_Destructor  [inline]
#include "k2000/components/CKGaugeCpntUpdater.h"

#include <cstring>

#include "Spyro2008/logic/KBase730C.h"
#include "k2000/graphical/fx/CBillboard2d.h"
#include "k2000/graphical/ui/CText2d.h"
#include "k2000/io/IKFile.h"

// 0x0024bb60 CKGaugeCpntUpdater_PostLoad: only for type 0 (the level load).
int32_t CKGaugeCpntUpdater::PostLoad(int32_t type) {
    if (type != 0) return 1;
    m_fFlashTime = 0.0f;
    m_unk18 = 0;
    m_unk08 = 0.0f;
    m_unk0c = 0.0f;
    m_unk10 = 0.0f;
    m_unk14 = 0.0f;
    return 1;
}

// 0x0024bad0 CKGaugeCpntUpdater_Load
int32_t CKGaugeCpntUpdater::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) IKFile_ReadRef(file, &m_pGauge);
    return 1;
}

// 0x0024b218 SuperGaugeRecord_Reset_maybe (CKGaugeCpnt.cpp's range)
void CKGaugeCpntUpdater::Reset() {
    m_fFlashTime = 0.0f;
    m_unk18 = 0;
    m_unk08 = 0.0f;
    m_unk0c = 0.0f;
    m_unk10 = 0.0f;
    m_unk14 = 0.0f;
}

void GaugeSample_Clear(GaugeSample* sample) {
    for (int32_t i = 0; i < 9; ++i) sample->m_transform.m_af[i] = 0.0f;
    for (int32_t i = 0; i < 9; ++i) sample->m_transform.m_abSet[i] = 0;
    for (int32_t i = 0; i < 4; ++i) sample->m_aColor[i] = 0xff;
    sample->m_bHasColor = 0;
}

// 0x0024b368 CKGaugeCpntUpdater_Update_maybe
int32_t CKGaugeCpntUpdater::Update(float dt, GaugeSample* sample) {
    if (m_pGauge != nullptr) {
        m_pGauge->UpdateDisplayedValue(dt, sample, this);
        return 1;
    }
    GaugeSample_Clear(sample);
    return 0;
}

// 0x0024bba0 CKGaugeCpntUpdater_EvaluateSample_maybe
int32_t CKGaugeCpntUpdater::EvaluateSample(float t, GaugeSample* sample) {
    if (m_pGauge != nullptr) {
        m_pGauge->EvaluateSample(t, sample, this);
        return 1;
    }
    GaugeSample_Clear(sample);
    return 0;
}

// 0x0024b600 GaugeSample_ApplyToElement2d_maybe
void GaugeSample_ApplyToElement2d(const GaugeSample* sample, KBase730C* menu, uint32_t slot) {
    IKNode2d* node = static_cast<IKNode2d*>(menu->GetWidgetSlots()[slot].m_pElement);
    const TransformSample& t = sample->m_transform;
    if (t.m_abSet[0] != 0) menu->SetElementX(t.m_af[0], slot);  // vt+0x7c
    if (t.m_abSet[1] != 0) menu->SetElementY(t.m_af[1], slot);  // vt+0x80
    if (t.m_abSet[5] != 0) node->m_f32RotateAngle = t.m_af[5];
    if (t.m_abSet[6] != 0) node->m_v2ConstantScale.m_fX = t.m_af[6];
    if (t.m_abSet[7] != 0) node->m_v2ConstantScale.m_fY = t.m_af[7];
    uint8_t color[4] = {0xff, 0xff, 0xff, 0xff};
    if (sample->m_bHasColor != 0) std::memcpy(color, sample->m_aColor, 4);
    IKSerializable* element = menu->GetWidgetSlots()[slot].m_pElement;
    if (element->IsKindOfClass(0x5cd) != 0) {
        IKText2d* text = static_cast<CText2d*>(static_cast<IKNode2d*>(menu->GetWidgetSlots()[slot].m_pElement));
        text->SetColor(color);  // vt+0x44
        std::memcpy(&text->m_VarColor, color, 4);
    } else if (element->IsKindOfClass(0x3cd) != 0) {
        IKBillboard2d* billboard =
            static_cast<CBillboard2d*>(static_cast<IKNode2d*>(menu->GetWidgetSlots()[slot].m_pElement));
        billboard->SetColor(color);  // vt+0x28
    }
}
