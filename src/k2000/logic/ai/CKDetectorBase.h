// CKDetectorBase.h - a detection zone watching movables (key 0x270c, vtable 0xb1c3a8, size 0x14).
// Original unit: CKDetectorBase.cpp. XXL2: K/KServices/KServiceDetect/CKDetectorBase.h (m_baData,
// m_pGeometry, m_pDetectedMovable, m_ui32NumSector; the same Load). DotD's slot +0x58 sets the enabled
// bit (XXL2 has IsAccessRestricted there).
#pragma once
#include <cstdint>

#include "crt/ppc_ops.h"
#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class CKDetectedMovable;

class CKDetectorBase : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x9c)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x270c || key == 0xc; }  // vt+0x08 0x9aafa8
    DOTD_DECLARE_FACTORIES(CKDetectorBase)

    CKDetectorBase() {}  // inlined in 0x001a88c0 CKDetectorBase_Create: only the vtable
    ~CKDetectorBase() override {}

    // vt+0x10 0x001a8a78 CKDetectorBase_Destroy: the movables (+0x0c) and the geometry (+0x08) references cleared.
    void Destroy() override;
    // vt+0x1c 0x001a89d8 CKDetectorBase_MessageProc: 0x1100 enables the detector, 0x1101 disables it (vt+0x58), both
    // answer 0; any other message 1. CKDetectorMusic_MessageProc 0x1aa238 and CKDetectorEvent_MessageProc 0x1a9c00 are
    // this function.
    int32_t MessageProc(uint16_t message, void* data) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001a8a88 CKDetectorBase_Load
    // vt+0x38 0x001a88f8 CKDetectorBase_SetDefaultState: flag 0 sets the enabled bit from bit 5 (vt+0x58).
    void SetDefaultState(int32_t flag) override;
    // vt+0x3c 0x001a8658 CKDetectorBase_SetGameState: info 50000 with state byte 0 enables, 1 disables (vt+0x58) and
    // answers 1; anything else 0.
    int32_t SetGameState(const SApplyGameState* state) override;
    // vt+0x40 0x001a8978 CKDetectorBase_GetInfo: value 2 = the enabled bit (accessor 0x9aaf48
    // CKDetectorBase_GetTriggerProp2, a byte); CKDetectorMusic_GetInfo 0x1aa210 is this function.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x24 0x1a8a68 RecursiveRegistration, vt+0x28 0x1a89d0 Save, vt+0x30 0x1a8a70 PostLoad return 1: the defaults.

    // vt+0x50 0x001a8c70 CKDetectorBase_CheckDetection_maybe (XXL2 Detect): an enabled detector's state bits from its
    // movables (CKDetectedMovable entries loaded and flagged +0x15) against its shape (CMultiGeometryBasic): a box or
    // sphere: bit 2 inside (any movable, or every one with +0x04 bit 10), bit 1 entered, bit 3 left (against bit 2 of
    // the last call, GetDetectionType(1)); a rectangle (type 2): bit 1 a movable crossed it since its old position in
    // the shape's direction, bit 3 in the other one. A detector of another sector than the current one, while the clock
    // runs, only loses bits 1-3 (returns 0). Returns 1 when it detected.
    virtual int32_t Detect();
    // vt+0x54 0x009aaf78 (XXL2 GetDetectionType): when bit (type + 1) of m_baData is set, bit 4; else 0.
    virtual int32_t GetDetectionType(int32_t type) {
        if ((ppc::slw(1u, static_cast<uint32_t>(type) + 1) & m_baData) == 0) return 0;
        return static_cast<int32_t>((m_baData >> 4) & 1);
    }
    virtual void SetEnabled(uint32_t enabled);  // vt+0x58 0x001a8948 CKDetectorBase_SetEnabled_maybe
    virtual int32_t Vf5C() { return 0; }        // vt+0x5c 0x009aaf58

    // +0x04 XXL2 CBitArray m_baData: bit 1 entered / crossed, bit 2 inside, bit 3 left / crossed back (Detect), bit 4
    // enabled, bit 5 enabled at load, bit 8 not run by the sector, bit 10 inside only when all movables are.
    uint32_t m_baData;
    IKSerializable* m_pGeometry;            // +0x08 XXL2 m_pGeometry (CMultiGeometry)
    CKDetectedMovable* m_pDetectedMovable;  // +0x0c XXL2 m_pDetectedMovable
    uint32_t m_ui32NumSector;               // +0x10 XXL2 m_ui32NumSector
};
DOTD_ASSERT_SIZE(CKDetectorBase, 0x14);
DOTD_ASSERT_OFFSET(CKDetectorBase, m_baData, 0x04);
DOTD_ASSERT_OFFSET(CKDetectorBase, m_pGeometry, 0x08);
DOTD_ASSERT_OFFSET(CKDetectorBase, m_pDetectedMovable, 0x0c);
DOTD_ASSERT_OFFSET(CKDetectorBase, m_ui32NumSector, 0x10);
