// CKMoveCpnt.h - a node movement built from 2D curves (key 0x968c, category logic, vtable 0xb20e48, size
// 0x34; an IKComponent: IsKindOfClass 0x9ba000 tests 0x968c, 0x6 and 0xc). Original unit: CKMoveCpnt.cpp
// (0x24c378-0x24d2a8). No XXL2 class of this name.
#pragma once
#include <cstdint>

#include "k2000/components/IKComponent.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/util/TVector.h"

class CKMoveCpnt : public IKComponent {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x25a)
    DOTD_DECLARE_FACTORIES(CKMoveCpnt)

    // One track: a curve and four words, all byte-swapped (LVL010: CKCurve2DCpnt refs, 1/2/4, 3.0, pi/2,
    // 0.1, 0) _maybe an axis mask and the curve's scale/range.
    struct Track {
        IKSerializable* m_pCurve;  // +0x00 CKCurve2DCpnt (the files' refs are of key 0x5ac6)
        uint32_t m_unk04;          // +0x04
        float m_unk08;             // +0x08
        float m_unk0c;             // +0x0c
        float m_unk10;             // +0x10
        uint32_t m_unk14;          // +0x14
    };

    // 0x0024cb48 CKMoveCpnt_Create (inlined constructor): the track vector null, 1, 0; nothing else.
    CKMoveCpnt() {
        m_vTracks.m_pBlock = nullptr;
        m_vTracks.m_ui32NbElt = 1;
        m_vTracks.m_ui32NbUsedElt = 0;
    }

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0024ccb8 CKMoveCpnt_Load

    float m_unk04;           // +0x04 (LVL010: 10.0) _maybe the duration
    uint8_t m_unk08;         // +0x08
    uint8_t m_unk09;         // +0x09
    uint8_t m_pad0a[2];
    IKSerializable* m_pUnk0c;  // +0x0c reference (null in the LVL010 samples)
    IKSerializable* m_pUnk10;  // +0x10 reference
    uint8_t m_unk14;         // +0x14
    uint8_t m_unk15;         // +0x15
    uint8_t m_unk16;         // +0x16
    uint8_t m_pad17;
    CMatrix34* m_pMatrix;    // +0x18 RwMatrixCreate + CMatrix34_LoadMatrix when the file's flag byte is set, else 0
    float m_unk1c[3];        // +0x1c..+0x27 three swapped words (_maybe a vector)
    TVector<Track, 1> m_vTracks;  // +0x28
};
DOTD_ASSERT_SIZE(CKMoveCpnt::Track, 0x18);
DOTD_ASSERT_SIZE(CKMoveCpnt, 0x34);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_unk08, 0x08);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_pUnk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_pUnk10, 0x10);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_unk14, 0x14);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_pMatrix, 0x18);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKMoveCpnt, m_vTracks, 0x28);
