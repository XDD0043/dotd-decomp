// CKSpawnPoolParams.h - the transforms of a spawn pool's instances (key 0x60d, vtable 0xb17968, size 0x20).
// Original unit: CKSpawnPoolParams.cpp. XXL2: K/KModules/KGL/Main/CKSpawnPoolParams.h (m_vrSpawnTransform,
// m_vsMatrixData, m_ui32NbActiveMatrix...); DotD's layout differs, the names here are ours unless noted.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/memory/Mem.h"

class IKTime;

class CKSpawnPoolParams : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x18)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x60d || key == 0xc; }  // vt+0x08 0x9a1040
    DOTD_DECLARE_FACTORIES(CKSpawnPoolParams)

    // An instance (PS3 0xc bytes): a new matrix, an id, a reference.
    struct SMatrixData {
        CMatrix34* m_pMatrix;       // +0x00 RwMatrixCreate (not loaded)
        uint16_t m_ui16Id;          // +0x04 Load sets 0xffff
        IKSerializable* m_pObject;  // +0x08
    };

    // 0x000b84f0 CKSpawnPoolParams_Create (also CKSpawnPoolParams_Construct 0xb7b50)
    CKSpawnPoolParams() : m_vsMatrixData(nullptr), m_ui32Capacity(1), m_ui32NbMatrixData(0) {}
    ~CKSpawnPoolParams() override {
        if (m_vsMatrixData != nullptr) Mem_FreeAligned16(m_vsMatrixData);
        m_ui32NbMatrixData = 0;
        m_vsMatrixData = nullptr;
    }

    // vt+0x2c 0x000b8660 CKSpawnPoolParams_Load (type 0 only)
    int32_t Load(IKFile* file, int32_t type) override;

    // 0x000b7c78 ShakeMatrixCache_StopAll_maybe: every active instance's matrix back to the identity (the
    // flags 0x20003, the pads kept) and its shake effect (+0x08) stopped.
    void StopAllShakes();
    // 0x000b7d58 ShakeMatrixCache_Start_maybe with the slot -1 (its only caller so far): the active matrices counted
    // again and every shake effect (a CKQuakeCpntUpdater) started.
    void StartAllShakes();
    // 0x000b7d58 ShakeMatrixCache_Start_maybe, the whole function (C2.8 port-final F05, SpawnInstance's one-slot calls):
    // the active count as StartAllShakes'; slot -1 starts every active shake, any other slot only its own and, for a
    // looping params block (flag 2 without flag 4), evaluates it once at a random time of its quake's duration
    // (Rand_Int & 0xffff over 65535: one draw).
    void StartShake(uint32_t slot);
    // vt+0x24 0x000b8300 CKSpawnPoolParams_RecursiveRegistration: type 0 only, itself registered, then the +0x08 object's
    // and every instance's object (no null tests).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x10 0x000b8548 CKSpawnPoolParams_Destroy: every instance's matrix destroyed (RwMatrixDestroy_Thunk), the block
    // freed and the count cleared.
    void Destroy() override;
    // 0x000b85f8 CKSpawnPoolParams_Destructor (0x000b8cd0 the deleting one): the block freed, its count and block
    // cleared (the matrices are Destroy's).
    // 0x000b7b78 CKSpawnPoolParams_NextIndex_maybe (SpawnInstance_ApplyTransform_maybe 0xd5a78, P10's): unless both
    // flags 2 and 4 are set, the next instance index (cycling below the active count); else 0.
    uint32_t NextIndex();
    // 0x000b8268 ShakeMatrixCache_GetMatrix_maybe (SpawnInstance_ApplyTransform_maybe's): the instance's matrix, brought
    // up to date once per render frame (UpdateShakeEntry with the frame clock when its stamp is not
    // g_ui16RenderFrameCounter).
    CMatrix34* GetShakeMatrix(uint32_t index, const CVector3* direction, uint8_t oriented);
    // 0x000b7f40 ShakeMatrixCache_UpdateEntry_maybe: while the clock runs, the matrix back to the identity; with a running
    // shake its outputs (EvaluateScaled with the fixed delta, 1) as the matrix, about the basis of `direction` (when
    // `oriented` and the direction is not null; up +y, or x when the direction is within 0.95 of +-y); a shake that ends
    // restarts with flag 2. The entry takes the frame stamp.
    void UpdateShakeEntry(uint32_t index, IKTime* clock, const CVector3* direction, uint8_t oriented);

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
