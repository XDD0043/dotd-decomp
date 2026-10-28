// CKSpawnPoolParams.h - the transforms of a spawn pool's instances (key 0x60d, vtable 0xb17968, size 0x20).
// Original unit: CKSpawnPoolParams.cpp. XXL2: K/KModules/KGL/Main/CKSpawnPoolParams.h (m_vrSpawnTransform,
// m_vsMatrixData, m_ui32NbActiveMatrix...); DotD's layout differs, the names here are ours unless noted.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"

class CKSpawnPoolParams : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x18)
    DOTD_DECLARE_FACTORIES(CKSpawnPoolParams)

    // An instance (PS3 0xc bytes): a new matrix, an id, a reference.
    struct SMatrixData {
        CMatrix34* m_pMatrix;       // +0x00 RwMatrixCreate (not loaded)
        uint16_t m_ui16Id;          // +0x04 Load sets 0xffff
        IKSerializable* m_pObject;  // +0x08
    };

    // 0x000b84f0 CKSpawnPoolParams_Create (also CKSpawnPoolParams_Construct 0xb7b50)
    CKSpawnPoolParams() : m_vsMatrixData(nullptr), m_ui32Capacity(1), m_ui32NbMatrixData(0) {}
    ~CKSpawnPoolParams() override {}

    // vt+0x2c 0x000b8660 CKSpawnPoolParams_Load (type 0 only)
    int32_t Load(IKFile* file, int32_t type) override;

    // 0x000b7c78 ShakeMatrixCache_StopAll_maybe: every active instance's matrix back to the identity (the
    // flags 0x20003, the pads kept) and its shake effect (+0x08) stopped.
    void StopAllShakes();
    // 0x000b7d58 ShakeMatrixCache_Start_maybe with the slot -1 (its only caller so far): the active matrices counted
    // again and every shake effect (a CKQuakeCpntUpdater) started.
    void StartAllShakes();

    uint32_t m_unk04;                  // +0x04 read after the reference
    IKSerializable* m_pUnk08;          // +0x08 a reference (the Ghidra struct: a CKQuakeCpnt)
    SMatrixData* m_vsMatrixData;       // +0x0c Mem_AllocAligned16
    uint32_t m_ui32Capacity;           // +0x10 (1 when empty)
    uint32_t m_ui32NbMatrixData;       // +0x14
    uint32_t m_ui32NbActiveMatrix;     // +0x18 _maybe (XXL2 name): Load counts the entries read
    uint32_t m_ui32NbNextActiveMatrix; // +0x1c _maybe (XXL2 name): Load sets 0
};
DOTD_ASSERT_SIZE(CKSpawnPoolParams::SMatrixData, 0xc);
static_assert(CKSpawnPoolParams::kClassKey == 0x60d, "key");
DOTD_ASSERT_SIZE(CKSpawnPoolParams, 0x20);
DOTD_ASSERT_OFFSET(CKSpawnPoolParams, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKSpawnPoolParams, m_pUnk08, 0x08);
DOTD_ASSERT_OFFSET(CKSpawnPoolParams, m_vsMatrixData, 0x0c);
DOTD_ASSERT_OFFSET(CKSpawnPoolParams, m_ui32Capacity, 0x10);
DOTD_ASSERT_OFFSET(CKSpawnPoolParams, m_ui32NbMatrixData, 0x14);
DOTD_ASSERT_OFFSET(CKSpawnPoolParams, m_ui32NbActiveMatrix, 0x18);
DOTD_ASSERT_OFFSET(CKSpawnPoolParams, m_ui32NbNextActiveMatrix, 0x1c);
