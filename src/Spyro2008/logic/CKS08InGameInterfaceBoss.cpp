// CKS08InGameInterfaceBoss.cpp - reconstructed original translation unit 0x533848-0x5349a8 (GAME_TOC1, main_toc1), 28 functions, 23 live.
// Primary class: CKS08InGameInterfaceBoss  key 0xa3cc  category Logic  size 0x100  vtable 0xb2bc08
// Other owners: CKS08InGameInterfaceCenter (4)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x533848  CKS08InGameInterfaceBoss_Delete
//   [ ] 0x533898  CKS08InGameInterfaceBoss_Construct  [dead]
//   [x] 0x533940  CKS08InGameInterfaceBoss_RefreshGaugeMarker_maybe
//   [x] 0x533978  CKS08InGameInterfaceBoss_RefreshGaugeValue_maybe
//   [x] 0x5339b0  CKS08InGameInterfaceBoss_ResetWidgets_maybe
//   [ ] 0x5339e8  CKS08InGameInterfaceBoss_Save
//   [x] 0x533a10  CKS08InGameInterfaceBoss_RecursiveRegistration  (inherited: CKMenuBase114c::RecursiveRegistration)
//   [x] 0x533a38  CKS08InGameInterfaceBoss_Destroy  (inherited: CKMenuBase_114c_maybe_Destroy)
//   [x] 0x533a60  CKS08InGameInterfaceBoss_DeleteArray
//   [x] 0x533b00  RegisterCKS08InGameInterfaceBossType  (the class registry: Kp3Ported.inc (gen_kp3_stubs.py); its two -1.0 words before the class record are not used)
//   [ ] 0x533b88  _GLOBAL__D_533b88
//   [ ] 0x533b98  _GLOBAL__I_533b98
//   [ ] 0x533ba8  CKS08InGameInterfaceBoss_Construct_2  [dead]
//   [x] 0x533c50  CKS08InGameInterfaceBoss_CreateArray
//   [x] 0x533d90  CKS08InGameInterfaceBoss_Create
//   [x] 0x533e78  CKS08InGameInterfaceBoss_RefreshGauge_maybe
//   [x] 0x533ed8  CKS08InGameInterfaceBoss_Update_maybe
//   [x] 0x5341f0  CKS08InGameInterfaceBoss_Load
//   [x] 0x534398  CKS08InGameInterfaceBoss_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x5344d0  CKS08InGameInterfaceBoss_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x534608  CKS08InGameInterfaceBoss_Destructor  (CKMenuBase114c's destructor, inlined)
//   [x] 0x534740  CKS08InGameInterfaceCenter_Delete  (CKS08InGameInterfaceCenter::Delete, DOTD_DECLARE_FACTORIES)
//   [x] 0x534790  CKS08InGameInterfaceCenter_vf8C  (CKS08InGameInterfaceCenter.h)
//   [x] 0x5347d0  CKS08InGameInterfaceCenter_vf90  (CKS08InGameInterfaceCenter.h)
//   [x] 0x534810  CKS08InGameInterfaceCenter_RefreshTextElementsB8C0_maybe  (CKS08InGameInterfaceCenter.cpp)
//   [ ] 0x534958  FUN_00534958  [dead]
//   [ ] 0x534970  FUN_00534970  [dead]
//   [ ] 0x534988  FUN_00534988  [dead]
//
//   [x] 0x9c9240  CKS08InGameInterfaceBoss_IsKindOfClass  [inline]
//   [x] 0x9c9280  CKS08InGameInterfaceBoss_GetClassType  [inline]
//   [x] 0x9c9288  CKS08InGameInterfaceBoss_GetClassID  [inline]
//   [x] 0x9c9290  CKS08InGameInterfaceBoss_vfB8  [inline]
//   [x] 0x9c9298  CKS08InGameInterfaceBoss_vfE0  [inline]
//   [x] 0x9c92a0  CKS08InGameInterfaceBoss_vfBC  [inline]
//   [x] 0x9c92a8  CKS08InGameInterfaceBoss_vfC0  [inline]
//   [x] 0x9c92b8  CKS08InGameInterfaceBoss_vfC4  [inline]
//   [x] 0x9c92c0  CKS08InGameInterfaceBoss_vfC8  [inline]
//   [x] 0x9c92d0  CKS08InGameInterfaceBoss_vfCC  [inline]
//   [x] 0x9c92e0  CKS08InGameInterfaceBoss_GetWidgetSlotCount  [inline]
//   [x] 0x9c92e8  CKS08InGameInterfaceBoss_GetWidgetSlots  [inline]
//   [x] 0x9c92f8  CKS08InGameInterfaceBoss_vf84  [inline]
#include "Spyro2008/logic/CKS08InGameInterfaceBoss.h"

#include "Spyro2008/logic/HudGaugeOps.h"
#include "Spyro2008/logic/HudSideOps.h"
#include "k2000/io/IKFile.h"

// 0x005341f0 CKS08InGameInterfaceBoss_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08InGameInterfaceBoss::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadF32LE(file, &m_fUnkec);
    m_fUnkfc = 0x1.4p+3f;  // 10.0 (lfs TOC1+0x7988)
    m_fUnkf4 = 0x1.4p+2f;  // 5.0 (TOC1+0x7980)
    m_fUnkf8 = 0x1p+3f;    // 8.0 (TOC1+0x7984)
    IKFile_ReadRef(file, &m_pGauge);
    IKFile_ReadRef(file, &m_pGaugeUpdater);
    return 1;
}

// 0x005339b0 CKS08InGameInterfaceBoss_ResetWidgets_maybe (vt+0x98)
void CKS08InGameInterfaceBoss::ResetWidgets() {
    CKMenuBase114c::ResetWidgets();
    m_fTime = 0.0f;
}

// 0x00533ed8 CKS08InGameInterfaceBoss_Update_maybe (vt+0xdc): the timed panel (bit 0 of +0xe0 for +0xec seconds, then
// message out 2), the gauge set to +0xf4 / +0xfc with its marker at +0xf8 / +0xfc, then ticked onto slots 0-2.
uint8_t CKS08InGameInterfaceBoss::OnMenuState(int32_t phase, uint8_t /*other*/) {
    if (phase == 1) {
        m_baFlagsE0 = static_cast<uint8_t>(m_baFlagsE0 & 0xfe);
    } else if (phase == 2) {
        if (hudside::Element(this, 0) != nullptr && hudside::Element(this, 1) != nullptr && hudside::Element(this, 2) != nullptr) {
            hudside::Element(this, 0)->Disable();
            hudside::Element(this, 1)->Disable();
            hudside::Element(this, 2)->Disable();
        }
    } else if (phase == 0) {
        const float dt = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[IKTime::FIXED_GAME_TIME];
        if ((m_baFlagsE0 & 1) != 0) {
            m_fTime = dt + m_fTime;
            if (m_fUnkec <= m_fTime) {
                m_baFlagsE0 = static_cast<uint8_t>(m_baFlagsE0 & 0xfe);
                hudside::PostMessage(this, 2);
            }
        }
        CKSuperGaugeCpntUpdater* updater = static_cast<CKSuperGaugeCpntUpdater*>(m_pGaugeUpdater);
        hudgauge::SuperGaugeSetValue(m_fUnkf4 / m_fUnkfc, updater, 1);  // 0x250dd8
        hudgauge::SuperGaugeSetMarker(m_fUnkf8 / m_fUnkfc, updater);     // 0x250da8
        if (hudside::Element(this, 0) != nullptr && hudside::Element(this, 1) != nullptr && hudside::Element(this, 2) != nullptr) {
            hudside::Element(this, 0)->Enable();
            hudside::Element(this, 1)->Enable();
            hudside::Element(this, 2)->Enable();
            GaugeSample samples[3];
            updater->Tick(dt, samples);
            GaugeSamples_ApplyToElements2d(updater, samples, this, 0, 1, 2);
        }
    }
    return static_cast<uint8_t>(GetMenuId());
}

// 0x00533940 CKS08InGameInterfaceBoss_RefreshGaugeMarker_maybe
void CKS08InGameInterfaceBoss::RefreshGaugeMarker() {
    hudgauge::SuperGaugeSetMarker(m_fUnkf8 / m_fUnkfc, static_cast<CKSuperGaugeCpntUpdater*>(m_pGaugeUpdater));  // 0x250da8
}

// 0x00533978 CKS08InGameInterfaceBoss_RefreshGaugeValue_maybe
void CKS08InGameInterfaceBoss::RefreshGaugeValue() {
    hudgauge::SuperGaugeSetValue(m_fUnkf4 / m_fUnkfc, static_cast<CKSuperGaugeCpntUpdater*>(m_pGaugeUpdater), 1);  // 0x250dd8
}

// 0x00533e78 CKS08InGameInterfaceBoss_RefreshGauge_maybe
void CKS08InGameInterfaceBoss::RefreshGauge() {
    CKSuperGaugeCpntUpdater* updater = static_cast<CKSuperGaugeCpntUpdater*>(m_pGaugeUpdater);
    hudgauge::SuperGaugeSetValue(m_fUnkf4 / m_fUnkfc, updater, 1);  // 0x250dd8
    hudgauge::SuperGaugeSetMarker(m_fUnkf8 / m_fUnkfc, updater);     // 0x250da8
}
