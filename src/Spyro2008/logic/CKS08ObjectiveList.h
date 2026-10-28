// CKS08ObjectiveList.h - a level's list of objectives (key 0x920c, vtable 0xb2b2f0, size 0xc). Original
// unit: CKS08ObjectiveList.cpp (0x506400-0x506ba8). DotD only: no XXL2 class of this name, so the
// member names are descriptive. Referenced by CKS08GameLevel.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKS08ObjectiveList : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x248)
    DOTD_DECLARE_FACTORIES(CKS08ObjectiveList)

    // One objective, 8 bytes on the PS3 (0x00506750 CKS08ObjectiveList_LoadEntry).
    struct Entry {
        IKSerializable* m_pObject;  // +0x00 a reference (class not identified)
        uint16_t m_ui16Unk4;        // +0x04
        uint16_t m_ui16Unk6;        // +0x06
    };

    CKS08ObjectiveList();  // inlined in 0x00506650 CKS08ObjectiveList_Create (copy 0x506430 unreferenced)
    ~CKS08ObjectiveList() override {}
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x920c || key == 0xc; }  // vt+0x08 0x9c7048
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005069d8 CKS08ObjectiveList_Load

    Entry* m_aEntries;          // +0x04 OperatorNewArray(count * 8); null for no entries
    uint16_t m_ui16NbEntries;   // +0x08 (+0x0a..+0x0b: padding the original never writes)
};
DOTD_ASSERT_SIZE(CKS08ObjectiveList, 0xc);
DOTD_ASSERT_SIZE(CKS08ObjectiveList::Entry, 0x8);
DOTD_ASSERT_OFFSET(CKS08ObjectiveList, m_aEntries, 0x04);
DOTD_ASSERT_OFFSET(CKS08ObjectiveList, m_ui16NbEntries, 0x08);
