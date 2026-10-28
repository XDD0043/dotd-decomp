// CKHkTrackerManager.h - (key 0xf42, vtable 0xb26f78, size 0x108). Original unit: CKHkTrackerManager.cpp.
// No XXL2 class. Field names are placeholders (C2.1 ports the constructor and Load only).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/util/TVector.h"

class CKHkTrackerManager : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0x3d)
    DOTD_DECLARE_FACTORIES(CKHkTrackerManager)

    struct RefValue {               // 0x8
        IKSerializable* m_pRef;     // +0x0 reference
        uint32_t m_unk4;            // +0x4
    };
    struct ValuesRef {              // 0x10
        uint32_t m_unk0;            // +0x0
        uint32_t m_unk4;            // +0x4
        uint32_t m_unk8;            // +0x8
        IKSerializable* m_pRef;     // +0xc reference
    };
    struct RefByte {                // 0xc (only +0x0 and +0x9 are written by the Load)
        IKSerializable* m_pRef;     // +0x0 reference
        uint8_t m_unk4[5];          // +0x4 uninitialised
        uint8_t m_unk9;             // +0x9
        uint8_t m_padA[2];
    };
    struct Slot {                   // 0x20, six of them at +0x3c
        TVector<RefValue, 1> m_vRefValues;   // +0x00
        uint8_t m_unkC;                      // +0x0c
        uint8_t m_padD[3];
        uint32_t m_unk10;                    // +0x10
        TVector<ValuesRef, 1> m_vValuesRefs; // +0x14
    };

    // 0x00453dd8 CKHkTrackerManager_Create (inlined constructor, the same as 0x451c80
    // CKHkTrackerManager_Construct): every vector empty with capacity 1.
    CKHkTrackerManager() {
        for (Slot& slot : m_aSlots) {
            slot.m_vRefValues.m_pBlock = nullptr;
            slot.m_vRefValues.m_ui32NbUsedElt = 0;
            slot.m_vRefValues.m_ui32NbElt = 1;
            slot.m_vValuesRefs.m_pBlock = nullptr;
            slot.m_vValuesRefs.m_ui32NbUsedElt = 0;
            slot.m_vValuesRefs.m_ui32NbElt = 1;
        }
        m_vRefBytes.m_ui32NbElt = 1;
        m_vRefBytes.m_ui32NbUsedElt = 0;
        m_vRefBytes.m_pBlock = nullptr;
    }
    ~CKHkTrackerManager() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004552f0 CKHkTrackerManager_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x00451b20 CKHkTrackerManager_SetDefaultState
    void Start() override;                        // vt+0x50 0x00451bb8 CKHkTrackerManager_Start

    uint32_t m_unk20[4];                 // +0x20 runtime
    uint8_t m_ui8NbRows;                 // +0x30 the row count of +0x34 and +0x38
    uint8_t m_ui8NbCols34;               // +0x31
    uint8_t m_ui8NbCols38;               // +0x32
    uint8_t m_pad33;
    IKSerializable** m_apRefs34;         // +0x34 rows * cols34 references
    IKSerializable** m_apRefs38;         // +0x38 rows * cols38 references
    Slot m_aSlots[6];                    // +0x3c
    TVector<RefByte, 1> m_vRefBytes;     // +0xfc
};
DOTD_ASSERT_SIZE(CKHkTrackerManager, 0x108);
DOTD_ASSERT_SIZE(CKHkTrackerManager::Slot, 0x20);
DOTD_ASSERT_SIZE(CKHkTrackerManager::RefByte, 0xc);
DOTD_ASSERT_SIZE(CKHkTrackerManager::ValuesRef, 0x10);
DOTD_ASSERT_OFFSET(CKHkTrackerManager::RefByte, m_unk9, 0x9);
DOTD_ASSERT_OFFSET(CKHkTrackerManager, m_ui8NbRows, 0x30);
DOTD_ASSERT_OFFSET(CKHkTrackerManager, m_apRefs34, 0x34);
DOTD_ASSERT_OFFSET(CKHkTrackerManager, m_apRefs38, 0x38);
DOTD_ASSERT_OFFSET(CKHkTrackerManager, m_aSlots, 0x3c);
DOTD_ASSERT_OFFSET(CKHkTrackerManager, m_vRefBytes, 0xfc);
