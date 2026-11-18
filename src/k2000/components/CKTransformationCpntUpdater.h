// CKTransformationCpntUpdater.h - drives a CKTransformationCpnt (key 0x1446, vtable 0xb21108, size 0x10).
// Original unit: CKTransformationCpntUpdater.cpp (0x2520c0-0x252a40). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/logic/CKTransformationCpnt.h"

class CKTransformationCpntUpdater : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x51)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ba620
        return key == 0x1446 || key == 0x6 || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKTransformationCpntUpdater)

    CKTransformationCpntUpdater() {}  // 0x002527f0 CKTransformationCpntUpdater_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x002528c8 CKTransformationCpntUpdater_Load
    int32_t PostLoad(int32_t type) override;            // vt+0x30 0x00252958 CKTransformationCpntUpdater_PostLoad

    // 0x00252718 CKTransformationCpntUpdater_Restart_maybe: the transformation's StartUpdater on this updater.
    void Restart();

    CKTransformationCpnt* m_pTransformation;  // +0x04 (Ghidra draft: CKTransformationCpnt*)
    uint8_t m_unk08;                          // +0x08 running; PostLoad (0x252958) sets 0, StartUpdater 1
    uint8_t m_unk09;                          // +0x09 StartUpdater sets 0
    uint8_t m_pad0a[2];
    float m_unk0c;                            // +0x0c the time of the last Evaluate; PostLoad (0x252958) sets 0.0
};
DOTD_ASSERT_SIZE(CKTransformationCpntUpdater, 0x10);
DOTD_ASSERT_OFFSET(CKTransformationCpntUpdater, m_pTransformation, 0x04);
