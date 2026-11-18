// CKSekensLauncherCpnt.h - the sequences an object can start (key 0xd46, vtable 0xb1ead8, size 0x10).
// Original unit: CKSekensLauncherCpnt.cpp. No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKSekensLauncherCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x35)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9b0e88
        return key == 0xd46 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKSekensLauncherCpnt)

    // 0x001f7c10 CKSekensLauncherCpnt_Create (the constructor 0x1f7668 inlined): null, 10, 0.
    CKSekensLauncherCpnt() {
        m_vSekens.m_pBlock = nullptr;
        m_vSekens.m_ui32NbElt = 10;
        m_vSekens.m_ui32NbUsedElt = 0;
    }
    // 0x001f77b0 CKSekensLauncherCpnt_Destructor (0x1f7f38 Destructor_2 the same, 0x1f7f90 DeletingDestructor + delete):
    // the sekens block freed (the fields left as they are), then the component base.
    ~CKSekensLauncherCpnt() override;
    // vt+0x10 0x001f7ee8 CKSekensLauncherCpnt_Destroy: the sekens block freed, its length and block cleared.
    void Destroy() override;
    // vt+0x1c 0x1f7ec8 MessageProc, vt+0x24 0x1f7ee0 RecursiveRegistration, vt+0x30 0x1f7ed8 PostLoad: return 1, the
    // defaults.
    // 0x001f7958 CKSekensLauncherCpnt_IsSekensPlaying_maybe: the sekens is the sekensor's current or pending one
    // (!IsSekensDone); 0 for an empty slot. `index` is not range-checked.
    uint8_t IsSekensPlaying(uint32_t index) const;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001f7d20 CKSekensLauncherCpnt_Load
    // 0x001f7a18 CKSekensLauncherCpnt_StopSekens_maybe: sekens `index` (not range-checked) cancelled by the sekensor
    // (CKSrvSekensor_CancelSekens_maybe) or, with `stop`, stopped (CKSrvSekensor_StopSekens_maybe); its answer, 1 for an
    // empty slot.
    uint8_t StopSekens(uint32_t index, int32_t stop);
    // C2.7 sparx (the linked beacon's sequences; none of them range-checks `index`):
    // 0x001f7730 CKSekensLauncherCpnt_PlaySekens_maybe: sekens `index` requested from the sekensor (RequestSekens), then
    // whether it is running or waiting (!IsSekensDone); 1 for an empty slot.
    uint8_t PlaySekens(uint32_t index);
    // 0x001f78a8 CKSekensLauncherCpnt_HasSekens: the slot holds a sekens.
    uint8_t HasSekens(uint32_t index) const { return m_vSekens.m_pBlock[index] != nullptr ? 1 : 0; }
    // 0x001f78d8 CKSrvSekensor_IsSekensLineFinished_maybe (a launcher method): the sekens' current line is finished
    // (CKSekens_IsCurrentLineFinished_maybe 0x1f4960); 1 for an empty slot.
    uint8_t IsSekensLineFinished(uint32_t index) const;
    // 0x001f79b0 SekensList_IsEntryDone_maybe: the sekens is neither the sekensor's current nor its pending one; 1 for an
    // empty slot.
    uint8_t IsEntryDone(uint32_t index) const;
    // 0x001f7aa8 CKSekensLauncherCpnt_GetCurrentLineIndex_maybe: the line the sekens plays when it is the current one,
    // else -1.
    int32_t GetCurrentLineIndex(uint32_t index) const;
    // 0x001f7b98 CKSekensLauncherCpnt_IsSekensCurrent: the sekens is the sekensor's current one (0 for an empty slot).
    uint8_t IsSekensCurrent(uint32_t index) const;

    TVector<IKSerializable*, 10> m_vSekens;  // +0x04 references (_maybe CKSekens, from the class name)
};
DOTD_ASSERT_SIZE(CKSekensLauncherCpnt, 0x10);
DOTD_ASSERT_OFFSET(CKSekensLauncherCpnt, m_vSekens, 0x04);
