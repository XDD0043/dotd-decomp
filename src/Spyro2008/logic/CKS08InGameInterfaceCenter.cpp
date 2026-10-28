// CKS08InGameInterfaceCenter.cpp - reconstructed original translation unit 0x5349a8-0x5378d8 (GAME_TOC1, main_toc1), 30 functions, 25 live.
// Primary class: CKS08InGameInterfaceCenter  key 0x79cc  category Logic  size 0x26c  vtable 0xb2bd10
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x5349a8  CKS08InGameInterfaceCenter_RefreshCounterHud_maybe  [dead]
//   [x] 0x534a88  CKS08InGameInterfaceCenter_SetGaugeMarker_maybe
//   [x] 0x534ad8  CKS08InGameInterfaceCenter_SetGaugeValue_maybe
//   [ ] 0x534b30  CKS08InGameInterfaceCenter_Save
//   [ ] 0x534b58  CKS08InGameInterfaceCenter_RecursiveRegistration
//   [ ] 0x534b80  CKS08InGameInterfaceCenter_Destroy
//   [x] 0x534ba8  CKS08InGameInterfaceCenter_DeleteArray
//   [ ] 0x534c48  RegisterCKS08InGameInterfaceCenterType
//   [ ] 0x534cd0  _GLOBAL__D_534cd0
//   [ ] 0x534ce0  _GLOBAL__I_534ce0
//   [x] 0x534cf0  CKS08InGameInterfaceCenter_Construct  [dead]
//   [ ] 0x534d98  CKS08InGameInterfaceCenter_Construct_2  [dead]
//   [ ] 0x534e40  CKS08InGameInterfaceCenter_RegisterWidgetCat0_maybe  [dead]
//   [x] 0x535010  CKS08InGameInterfaceCenter_CreateArray
//   [x] 0x535150  CKS08InGameInterfaceCenter_Create
//   [x] 0x535238  CKS08InGameInterfaceCenter_HideFuryGauge_maybe
//   [ ] 0x5352e8  CKS08InGameInterfaceCenter_ShowFuryGauge_2_maybe
//   [ ] 0x5353d0  CKS08InGameInterfaceCenter_ShowFuryGauge_maybe
//   [x] 0x5354c8  CKS08InGameInterfaceCenter_Load
//   [ ] 0x535980  CKS08InGameInterfaceCenter_UpdateVisibility_maybe
//   [ ] 0x535bc8  CKS08InGameInterfaceCenter_DeletingDestructor
//   [ ] 0x535d00  CKS08InGameInterfaceCenter_UpdateMessageDisplay_maybe
//   [ ] 0x536310  CKS08InGameInterfaceCenter_QueueMessage_maybe
//   [ ] 0x5364e0  CKS08InGameInterfaceCenter_ShowOrQueueMessagePair_maybe
//   [ ] 0x536628  CKS08InGameInterfaceCenter_Destructor
//   [ ] 0x536760  CKS08InGameInterfaceCenter_Destructor_2
//   [ ] 0x536898  CKS08InGameInterfaceCenter_ClearWidgetCat1Tables_maybe  [dead]
//   [ ] 0x5369b0  CKS08InGameInterfaceCenter_RebuildWidgetCat1Tables_maybe
//   [ ] 0x536cf0  CKS08InGameInterfaceCenter_Update_maybe
//   [ ] 0x537558  CKS08InGameInterfaceCenter_ResetWidgets_maybe
//
//   [x] 0x9c9300  CKS08InGameInterfaceCenter_IsKindOfClass  [inline]
//   [ ] 0x9c9338  CKS08InGameInterfaceCenter_GetClassType  [inline]
//   [ ] 0x9c9340  CKS08InGameInterfaceCenter_GetClassID  [inline]
//   [x] 0x9c9348  CKS08InGameInterfaceCenter_vfB8  [inline]
//   [x] 0x9c9350  CKS08InGameInterfaceCenter_vfE0  [inline]
//   [x] 0x9c9358  CKS08InGameInterfaceCenter_vfC4  [inline]
//   [x] 0x9c9360  CKS08InGameInterfaceCenter_vfC8  [inline]
//   [x] 0x9c9370  CKS08InGameInterfaceCenter_vfCC  [inline]
//   [x] 0x9c9380  CKS08InGameInterfaceCenter_vfBC  [inline]
//   [x] 0x9c9388  CKS08InGameInterfaceCenter_vfC0  [inline]
//   [x] 0x9c9398  CKS08InGameInterfaceCenter_GetWidgetSlotCount  [inline]
//   [x] 0x9c93a0  CKS08InGameInterfaceCenter_GetWidgetSlots  [inline]
//   [x] 0x9c93b0  CKS08InGameInterfaceCenter_vf84  [inline]
//   [x] 0x9c93b8  CKS08InGameInterfaceCenter_vf88  [inline]
#include "Spyro2008/logic/CKS08InGameInterfaceCenter.h"

#include "Spyro2008/logic/HudGaugeOps.h"
#include "k2000/graphical/ui/CKFlashMessageOut.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"

// 0x005354c8 CKS08InGameInterfaceCenter_Load: no type test of its own, so its fields are read whatever the type.
int32_t CKS08InGameInterfaceCenter::Load(IKFile* file, int32_t type) {
    CKMenuBase114c::Load(file, type);
    ReadF32LE(file, &m_fUnk254);
    ReadF32LE(file, &m_fUnk258);
    ReadF32LE(file, &m_fUnk25c);
    IKFile_ReadRef(file, &m_pQuake);
    IKFile_ReadRef(file, &m_pQuakeUpdater);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_fUnk244), 2);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(m_fUnk24c), 2);
    IKFile_ReadRef(file, &m_pGauge20c);
    IKFile_ReadRef(file, &m_pGaugeUpdater210);
    IKFile_ReadRef(file, &m_pGauge214);
    IKFile_ReadRef(file, &m_pGaugeUpdater218);
    ReadF32LE(file, &m_fUnk204);
    return 1;
}

// 0x00534ad8 CKS08InGameInterfaceCenter_SetGaugeValue_maybe
void CKS08InGameInterfaceCenter::SetGaugeValue(float value, int32_t index) {
    hudgauge::SuperGaugeSetValue(value, static_cast<CKSuperGaugeCpntUpdater*>(index == 0 ? m_pGaugeUpdater210 : m_pGaugeUpdater218), 1);
}

// 0x00534a88 CKS08InGameInterfaceCenter_SetGaugeMarker_maybe
void CKS08InGameInterfaceCenter::SetGaugeMarker(float ratio, int32_t index) {
    hudgauge::SuperGaugeSetMarker(ratio, static_cast<CKSuperGaugeCpntUpdater*>(index == 0 ? m_pGaugeUpdater210 : m_pGaugeUpdater218));
}

// 0x00535238 CKS08InGameInterfaceCenter_HideFuryGauge_maybe
void CKS08InGameInterfaceCenter::HideFuryGauge() {
    IKSerializable* message = VfC0()[13];  // +0x34
    if (message != nullptr) static_cast<CKFlashMessageOut*>(message)->PostFlashMessage();
    m_unk200 &= ~0x00ff0000u;
}

// 0x00536310 CKS08InGameInterfaceCenter_QueueMessage_maybe. STUB(C2.7 step 7, HUD).
void CKS08InGameInterfaceCenter::QueueMessage(IKSerializable* /*text*/) {
    DOTD_STUB_ONCE("CKS08InGameInterfaceCenter_QueueMessage_maybe 0x536310 (C2.7 step 7, HUD)");
}

// 0x005364e0 CKS08InGameInterfaceCenter_ShowOrQueueMessagePair_maybe. STUB(C2.7 step 7, HUD).
void CKS08InGameInterfaceCenter::ShowOrQueueMessagePair(IKSerializable* /*first*/, IKSerializable* /*second*/) {
    DOTD_STUB_ONCE("CKS08InGameInterfaceCenter_ShowOrQueueMessagePair_maybe 0x5364e0 (C2.7 step 7, HUD)");
}
