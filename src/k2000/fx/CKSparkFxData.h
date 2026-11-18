// CKSparkFxData.h - the data of a spark effect (key 0x24cc, vtable 0xb1d908, size 0x18). Original unit:
// k2000/fx/CKSparkFxData.cpp (0x1d3908-0x1d3e68); Create/CreateArray (0x1ae160/0x1ae0c0) sit in another
// unit. Its node is CKSparkNodeFx (0x244c). No XXL2 class of this name; names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/logic/IKFxData.h"

class CKSparkFxData : public IKFxData {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x93)
    DOTD_DECLARE_FACTORIES(CKSparkFxData)

    CKSparkFxData();  // 0x001d3908 CKSparkFxData_ConstructBase_maybe (called by Create 0x1ae160)

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d39c8 CKSparkFxData_Load
    // vt+0x30 0x001d3940 CKSparkFxData_PostLoad: type 0 creates the identity matrix +0x14 (RwMatrixCreate); 1.
    int32_t PostLoad(int32_t type) override;
    uint32_t GetAssociatedFxClassIdentifier() override { return 0x244c; }  // vt+0x54 0x1d3930
    // vt+0x10 0x001d3e20 CKSparkFxData_ClearReferences (Destroy): the matrix +0x14 destroyed (RwMatrixDestroy) and cleared.
    void Destroy() override;
    // vt+0x1c 0x001d3b00 CKSparkFxData_HandleMessage (MessageProc): 0x1b00 with an object (null: 0) sets the matrix +0x14
    // from the object (its quaternion +0x10, its position +0x04, flag 0x20000 cleared), then an effect of this data is
    // acquired (CKSrvFx::AcquireFx inlined) and released (vt+0x54); returns 0. Other messages return 1.
    // vt+0x40 0x001d3e18 GetInfo: 1 (the default). 0x9ad358 / 0x9ad3b0 destructors: the C++ chain.
    int32_t MessageProc(uint16_t message, void* data) override;

    IKSerializable* m_pSparkParam;  // +0x08 the spark parameters (Ghidra draft: CKSparkParam*); name ours
    IKSerializable* m_unk0c;        // +0x0c the constructor sets 0; the parent node (CKSparkNodeFx_Start)
    IKSerializable* m_unk10;        // +0x10 the constructor sets 0; a hot spot to hang the node under (Start)
    void* m_unk14;                  // +0x14 the constructor sets 0; a heap pointer live (PostLoad)
};
static_assert(CKSparkFxData::kClassKey == 0x24cc, "key");
DOTD_ASSERT_SIZE(CKSparkFxData, 0x18);
DOTD_ASSERT_OFFSET(CKSparkFxData, m_pSparkParam, 0x08);
DOTD_ASSERT_OFFSET(CKSparkFxData, m_unk14, 0x14);
