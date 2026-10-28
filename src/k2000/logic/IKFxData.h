// IKFxData.h - the FX parameter blocks (key 0x304c; XXL2: KServices/KServiceFx/Effects/IKFxData.h): the
// data an FX node (IKNodeFx, IKFx) is created from. Original unit: IKFxData.cpp (0x1d8348-0x1d84f0, the
// Load and Save; the inline methods are copied into the users' units). PS3 vtable 0xb1dce8, 23 slots.
//
// Its constructor only stores the vtable (every FX data Create stores 0xb1dce8, then its own vtable).
//
// Slots +0x50..+0x58: XXL2 has GetAssociatedFxClassIdentifier (slot 20, pure) and
// GetAssociatedFxClassType (slot 21, returns m_ui8FxType). DotD has one slot more in front: +0x50 returns
// 0 (CKTimeScalingFxData returns 1), +0x54 is pure (each FX data returns the class key of its node, e.g.
// CKFilterFxData 0x19cc) and +0x58 returns this+4. The names follow that alignment (_maybe).
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"

class IKFxData : public IKComponent {
public:
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ad898
        return key == 0x304c || key == 0x6 || key == 0xc;
    }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001d8348 IKFxData_Load
    // vt+0x30 PostLoad: 0x1d8338 returns 1 (the default).
    virtual int32_t Vf50() { return 0; }                 // vt+0x50 0x9ab3a0 (DotD)
    // vt+0x54 pure: the class key of the FX node this data creates (Ghidra *_GetNodeClassKey).
    virtual uint32_t GetAssociatedFxClassIdentifier() = 0;
    virtual uint32_t GetAssociatedFxClassType() { return m_typeIndex; }  // vt+0x58 0x9ab3a8 IKFxData_GetTypeIndex

    // +0x04 the second word of the record. Ghidra IKFxData_GetTypeIndex returns it. XXL2 reads a byte
    // pair here (m_bIsAssociateFxUnique, m_ui8FxType) and its GetAssociatedFxClassType returns
    // m_ui8FxType: _maybe the same member, a u32 in DotD. 0xff in every front-end record.
    uint32_t m_typeIndex;
};
DOTD_ASSERT_SIZE(IKFxData, 0x8);
DOTD_ASSERT_OFFSET(IKFxData, m_typeIndex, 0x04);
