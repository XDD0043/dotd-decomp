// CKS08InGameInterfaceProtect.cpp - reconstructed original translation unit 0x53c360-0x53d330 (GAME_TOC1, main_toc1), 21 functions, 19 live.
// Primary class: CKS08InGameInterfaceProtect  key 0xa38c  category Logic  size 0x100  vtable 0xb2bf20
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x53c360  CKS08InGameInterfaceProtect_Delete
//   [ ] 0x53c3b0  CKS08InGameInterfaceProtect_Construct  [dead]
//   [x] 0x53c458  CKS08InGameInterfaceProtect_SyncGaugeMarker_maybe
//   [x] 0x53c4b8  CKS08InGameInterfaceProtect_SyncGaugeValue_maybe
//   [x] 0x53c520  CKS08InGameInterfaceProtect_ResetWidgets_maybe
//   [ ] 0x53c558  CKS08InGameInterfaceProtect_Save
//   [x] 0x53c580  CKS08InGameInterfaceProtect_RecursiveRegistration  (inherited: CKMenuBase114c::RecursiveRegistration)
//   [x] 0x53c5a8  CKS08InGameInterfaceProtect_Destroy  (inherited: CKMenuBase114c::Destroy)
//   [x] 0x53c5d0  CKS08InGameInterfaceProtect_DeleteArray
//   [ ] 0x53c670  RegisterCKS08InGameInterfaceProtectClass
//   [ ] 0x53c6f8  _GLOBAL__D_53c6f8
//   [ ] 0x53c708  _GLOBAL__I_53c708
//   [ ] 0x53c718  CKS08InGameInterfaceProtect_Construct_2  [dead]
//   [x] 0x53c7c0  CKS08InGameInterfaceProtect_CreateArray
//   [x] 0x53c900  CKS08InGameInterfaceProtect_Create
//   [x] 0x53c9e8  CKS08InGameInterfaceProtect_Load
//   [x] 0x53cb90  CKS08InGameInterfaceProtect_UpdateGauge_maybe
//   [x] 0x53cc28  CKS08InGameInterfaceProtect_OnMenuState_maybe
//   [x] 0x53cf88  CKS08InGameInterfaceProtect_Destructor_2  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x53d0c0  CKS08InGameInterfaceProtect_DeletingDestructor  (implicit destructor: CKMenuBase114c's inlined)
//   [x] 0x53d1f8  CKS08InGameInterfaceProtect_Destructor  (implicit destructor: CKMenuBase114c's inlined)
//
//   [x] 0x9c9490  CKS08InGameInterfaceProtect_IsKindOfClass  [inline]
//   [x] 0x9c94d0  CKS08InGameInterfaceProtect_GetClassType  [inline]
//   [x] 0x9c94d8  CKS08InGameInterfaceProtect_GetClassID  [inline]
//   [x] 0x9c94e0  CKS08InGameInterfaceProtect_vfB8  [inline]
//   [x] 0x9c94e8  CKS08InGameInterfaceProtect_vfE0  [inline]
//   [x] 0x9c94f0  CKS08InGameInterfaceProtect_vfBC  [inline]
//   [x] 0x9c94f8  CKS08InGameInterfaceProtect_vfC0  [inline]
//   [x] 0x9c9508  CKS08InGameInterfaceProtect_vfC4  [inline]
//   [x] 0x9c9510  CKS08InGameInterfaceProtect_vfC8  [inline]
//   [x] 0x9c9520  CKS08InGameInterfaceProtect_vfCC  [inline]
//   [x] 0x9c9530  CKS08InGameInterfaceProtect_GetWidgetSlotCount  [inline]
//   [x] 0x9c9538  CKS08InGameInterfaceProtect_GetWidgetSlots  [inline]
//   [x] 0x9c9548  CKS08InGameInterfaceProtect_vf84  [inline]
#include "Spyro2008/logic/CKS08InGameInterfaceProtect.h"

#include "Spyro2008/logic/HudGaugeOps.h"
#include "Spyro2008/logic/HudSideOps.h"
#include "k2000/io/IKFile.h"

// 0x0053c9e8 CKS08InGameInterfaceProtect_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08InGameInterfaceProtect::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadF32LE(file, &m_fUnkec);
    m_fUnkfc = 0x1.4p+3f;  // 10.0 (lfs TOC1+0x7b20)
    m_fUnkf4 = 0x1.4p+2f;  // 5.0 (TOC1+0x7b18)
    m_fUnkf8 = 0x1p+3f;    // 8.0 (TOC1+0x7b1c)
    IKFile_ReadRef(file, &m_pGauge);
    IKFile_ReadRef(file, &m_pGaugeUpdater);
    return 1;
}

// 0x0053c520 CKS08InGameInterfaceProtect_ResetWidgets_maybe (vt+0x98)
void CKS08InGameInterfaceProtect::ResetWidgets() {
    CKMenuBase114c::ResetWidgets();
    m_fTime = 0.0f;
}

// 0x0053c458 CKS08InGameInterfaceProtect_SyncGaugeMarker_maybe: fcmpu / beq, so a NaN ratio is set too.
void CKS08InGameInterfaceProtect::SyncGaugeMarker() {
    CKSuperGaugeCpntUpdater* updater = static_cast<CKSuperGaugeCpntUpdater*>(m_pGaugeUpdater);
    const float ratio = m_fUnkf8 / m_fUnkfc;
    if (static_cast<double>(ratio) != hudgauge::SuperGaugeGetMarker(updater)) {  // 0x250f18
        hudgauge::SuperGaugeSetMarker(ratio, updater);                           // 0x250da8
    }
}

// 0x0053c4b8 CKS08InGameInterfaceProtect_SyncGaugeValue_maybe
void CKS08InGameInterfaceProtect::SyncGaugeValue() {
    CKSuperGaugeCpntUpdater* updater = static_cast<CKSuperGaugeCpntUpdater*>(m_pGaugeUpdater);
    const float ratio = m_fUnkf4 / m_fUnkfc;
    if (static_cast<double>(ratio) != hudgauge::GetGaugeValue(updater)) {  // 0x250b28
        hudgauge::SuperGaugeSetValue(ratio, updater, 1);                    // 0x250dd8
    }
}

// 0x0053cb90 CKS08InGameInterfaceProtect_UpdateGauge_maybe: the value, then the marker.
void CKS08InGameInterfaceProtect::UpdateGauge() {
    SyncGaugeValue();
    SyncGaugeMarker();
}

// 0x0053cc28 CKS08InGameInterfaceProtect_OnMenuState_maybe (vt+0xdc)
uint8_t CKS08InGameInterfaceProtect::OnMenuState(int32_t phase, uint8_t /*other*/) {
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
        const float value = m_fUnkf4 / m_fUnkfc;
        if (static_cast<double>(value) != hudgauge::GetGaugeValue(updater)) {  // 0x250b28
            hudgauge::SuperGaugeSetValue(value, updater, 1);                    // 0x250dd8
        }
        const float marker = m_fUnkf8 / m_fUnkfc;
        if (static_cast<double>(marker) != hudgauge::SuperGaugeGetMarker(updater)) {  // 0x250f18
            hudgauge::SuperGaugeSetMarker(marker, updater);                           // 0x250da8
        }
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
