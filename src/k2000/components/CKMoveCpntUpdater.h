// CKMoveCpntUpdater.h - drives a CKMoveCpnt on a node (key 0x12c6, vtable 0xb20ea0, size 0x10). Original
// unit: CKMoveCpntUpdater.cpp (0x24d2a8-0x24df50). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class CKMoveCpnt;

class CKMoveCpntUpdater : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryComponent, 0x4b)
    DOTD_DECLARE_FACTORIES(CKMoveCpntUpdater)

    CKMoveCpntUpdater() {}  // 0x0024dd70 CKMoveCpntUpdater_Create: the vtable only

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0024de48 CKMoveCpntUpdater_Load

    CKMoveCpnt* m_pMoveCpnt;  // +0x04 (CKMoveCpntUpdater_GetMoveCpnt 0x24d2a8; LVL010 refs of key 0x968c)
    uint32_t m_unk08;         // +0x08 runtime (Start/Stop/Pause); not set by the constructor or the Load
    uint32_t m_unk0c;         // +0x0c runtime
};
DOTD_ASSERT_SIZE(CKMoveCpntUpdater, 0x10);
DOTD_ASSERT_OFFSET(CKMoveCpntUpdater, m_pMoveCpnt, 0x04);
