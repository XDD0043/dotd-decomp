// CKFlaggedPath.h - a path with trigger starters at given positions (key 0x5cc, vtable 0xb17bd8, size
// 0x28). Original unit: CKFlaggedPath.cpp. XXL2: K/KServices/KServiceBeacon/CKFlaggedPath.h (m_pPath,
// m_ui32NbOfBeacon, m_fCursorPos, m_bInOrder, m_aBeaconList, m_aTriggerToCallList); DotD adds a vector
// of word pairs at +0x1c.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/services/CTriggerStarter.h"
#include "k2000/util/TVector.h"

class CKFlaggedPath : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x17)
    DOTD_DECLARE_FACTORIES(CKFlaggedPath)

    struct Pair {  // 8 bytes; names ours
        uint32_t m_unk0;
        uint32_t m_unk4;
    };

    CKFlaggedPath();  // inlined in 0x000c44b0 CKFlaggedPath_Create
    ~CKFlaggedPath() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000c4568 CKFlaggedPath_Load

    IKSerializable* m_pPath;                   // +0x04 XXL2 m_pPath (CKSpline4L / CKLine in the files)
    uint32_t m_ui32NbOfBeacon;                 // +0x08 XXL2 m_ui32NbOfBeacon
    float m_fCursorPos;                        // +0x0c XXL2 m_fCursorPos
    uint32_t m_unk10;                          // +0x10 not loaded (XXL2 m_bInOrder _maybe)
    float* m_aBeaconList;                      // +0x14 XXL2 m_aBeaconList (one block with the starters)
    CTriggerStarter* m_aTriggerToCallList;     // +0x18 XXL2 m_aTriggerToCallList
    TVector<Pair, 1> m_vPairs;                 // +0x1c the constructor: null, capacity 1, 0 used
};
DOTD_ASSERT_SIZE(CKFlaggedPath, 0x28);
DOTD_ASSERT_OFFSET(CKFlaggedPath, m_pPath, 0x04);
DOTD_ASSERT_OFFSET(CKFlaggedPath, m_ui32NbOfBeacon, 0x08);
DOTD_ASSERT_OFFSET(CKFlaggedPath, m_fCursorPos, 0x0c);
DOTD_ASSERT_OFFSET(CKFlaggedPath, m_aBeaconList, 0x14);
DOTD_ASSERT_OFFSET(CKFlaggedPath, m_aTriggerToCallList, 0x18);
DOTD_ASSERT_OFFSET(CKFlaggedPath, m_vPairs, 0x1c);
