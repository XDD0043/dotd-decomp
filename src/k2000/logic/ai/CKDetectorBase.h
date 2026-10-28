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
    DOTD_DECLARE_FACTORIES(CKDetectorBase)

    CKDetectorBase() {}  // inlined in 0x001a88c0 CKDetectorBase_Create: only the vtable
    ~CKDetectorBase() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001a8a88 CKDetectorBase_Load

    virtual void Detect() {}  // vt+0x50 0x1a8c70 CKDetectorBase_CheckDetection_maybe (XXL2 Detect)  STUB(C2.2)
    // vt+0x54 0x009aaf78 (XXL2 GetDetectionType): when bit (type + 1) of m_baData is set, bit 4; else 0.
    virtual int32_t GetDetectionType(int32_t type) {
        if ((ppc::slw(1u, static_cast<uint32_t>(type) + 1) & m_baData) == 0) return 0;
        return static_cast<int32_t>((m_baData >> 4) & 1);
    }
    virtual void SetEnabled(uint32_t enabled);  // vt+0x58 0x001a8948 CKDetectorBase_SetEnabled_maybe
    virtual int32_t Vf5C() { return 0; }        // vt+0x5c 0x009aaf58

    uint32_t m_baData;                      // +0x04 XXL2 CBitArray m_baData (bit 4 enabled, bit 5 enabled at load)
    IKSerializable* m_pGeometry;            // +0x08 XXL2 m_pGeometry (CMultiGeometry)
    CKDetectedMovable* m_pDetectedMovable;  // +0x0c XXL2 m_pDetectedMovable
    uint32_t m_ui32NumSector;               // +0x10 XXL2 m_ui32NumSector
};
DOTD_ASSERT_SIZE(CKDetectorBase, 0x14);
DOTD_ASSERT_OFFSET(CKDetectorBase, m_baData, 0x04);
DOTD_ASSERT_OFFSET(CKDetectorBase, m_pGeometry, 0x08);
DOTD_ASSERT_OFFSET(CKDetectorBase, m_pDetectedMovable, 0x0c);
DOTD_ASSERT_OFFSET(CKDetectorBase, m_ui32NumSector, 0x10);
