// CKAdvancedCameraCinematicBloc.h - a scripted camera move (key 0x208, vtable 0xb1af70, size 0xb0). Original unit: CKAdvancedCameraCinematicBloc.cpp.
// Not in XXL2. Ten references (CKCurve2DCpnt in the Ghidra struct at +0x5c), a byte and three words.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/IKCinematicBloc.h"

class IKFile;

class CKAdvancedCameraCinematicBloc : public IKCinematicBloc {
public:
    DOTD_CLASS_KEY(kCategoryCinematic, 0x8)
    DOTD_DECLARE_FACTORIES(CKAdvancedCameraCinematicBloc)
    DOTD_BLOC_IS_KIND_OF()

    // 0x00170b58 CKAdvancedCameraCinematicBloc_Create: IKCinematicBloc_Construct, then the vtable.
    CKAdvancedCameraCinematicBloc() {}
    ~CKAdvancedCameraCinematicBloc() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00172560 CKAdvancedCameraCinematicBloc_Load

    IKSerializable* m_apUnk38[10];  // +0x38 the LVL010 object: CKCamera..., then CKCurve2DCpnt-like components (0x5ac6)
    uint8_t m_unk60;                // +0x60
    uint8_t m_pad61[3];
    float m_unk64;                  // +0x64 10.0 in LVL010
    uint32_t m_unk68;               // +0x68
    uint32_t m_unk6c;               // +0x6c
    uint32_t m_unk70[16];           // +0x70 not set by the constructor nor the Load
};
DOTD_ASSERT_SIZE(CKAdvancedCameraCinematicBloc, 0xb0);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_apUnk38, +0x38);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_unk60, +0x60);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_unk64, +0x64);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_unk68, +0x68);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_unk6c, +0x6c);
DOTD_ASSERT_OFFSET(CKAdvancedCameraCinematicBloc, m_unk70, +0x70);
