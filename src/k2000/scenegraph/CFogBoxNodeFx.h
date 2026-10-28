// CFogBoxNodeFx.h - a volumetric fog box effect (key 0x68b, vtable 0xb189a0, size 0x838). Original unit:
// CFogBoxNodeFx.cpp. No XXL2 class; the fields keep their offsets (the Ghidra struct's nUnkXX / flUnkXX)
// until named. The read order is the original's (see Load); offsets not read are left as the constructor
// (CNode's only) leaves them.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/INodeFx.h"
#include "k2000/math/CMatrix34.h"

class CFogBoxNodeFx : public INodeFx {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x1a)
    DOTD_DECLARE_FACTORIES(CFogBoxNodeFx)

    // A box (PS3 0x10 bytes): a loaded matrix, 0, 1.0f.
    struct SBox {
        CMatrix34* m_pMatrix;  // +0x00 RwMatrixCreate + CMatrix34_LoadMatrix
        uint32_t m_unk04;      // +0x04 Load sets 0
        float m_unk08;         // +0x08 Load sets 1.0f (TOC -0x5034)
        uint32_t m_unk0c;      // +0x0c not set
    };
    // An entry of the table at +0x728 (0x10 bytes): two floats, two words kept raw.
    struct SEntry728 {
        float m_af[2];       // +0x00 swapped
        uint8_t m_raw08[4];  // +0x08 read raw (file bytes)
        uint8_t m_raw0c[4];  // +0x0c read raw (file bytes)
    };

    CFogBoxNodeFx() {}  // 0x000dcde0 CFogBoxNodeFx_Create: CNode's constructor, then the vtables
    ~CFogBoxNodeFx() override {}

    // vt+0x2c 0x000dd1f8 CFogBoxNodeFx_Load (type 0 only after INodeFx's)
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x000dcb20 CFogBoxNodeFx_PostLoad (STUB(C2.7, particles: the PTank pipeline): the particle buffers and the PTank atomic setup)
    int32_t PostLoad(int32_t type) override;

    uint32_t m_unk2c;              // +0x2c
    float m_unk30;                 // +0x30
    uint32_t* m_pUnk34;            // +0x34 m_ui32NbBoxes words after the boxes (same buffer), not read
    uint32_t m_unk38;              // +0x38
    SBox* m_aBoxes;                // +0x3c Mem_AllocAligned16(m_ui32NbBoxes * 0x14)
    uint32_t m_unk40;              // +0x40 read first
    uint32_t m_ui32NbBoxes;        // +0x44
    void* m_pTexture;              // +0x48 IKFile_ReadTextureRef (resolve 0)
    IKSerializable* m_pGeometry;   // +0x4c PostLoad: the node's first geometry (a CParticleGeometry)
    uint32_t m_unk50;              // +0x50 the count of the +0x7ac / +0x7ec / +0x7f0 arrays
    uint32_t m_unk54;              // +0x54 the count of the +0x834 array
    uint32_t m_unk58;              // +0x58
    float m_unk5c[3];              // +0x5c one 0xc read
    float m_unk68[2];              // +0x68 one 8-byte read
    float m_unk70;                 // +0x70 PostLoad sets -1.0f
    float m_unk74;                 // +0x74
    uint32_t m_aPairs78[200][2];   // +0x78 count x 8 bytes, each word swapped
    uint8_t m_aBytes6b8[100];      // +0x6b8 count / 2 bytes, raw
    uint8_t m_unk71c;              // +0x71c
    uint8_t m_unk71d;              // +0x71d
    uint8_t m_unk71e;              // +0x71e
    uint8_t m_unk71f;              // +0x71f read first among the bytes; 1 selects the +0x7ec/+0x7f0 arrays
    uint8_t m_aUnk720[4];          // +0x720 four bytes, one read each
    uint32_t m_unk724;             // +0x724
    SEntry728 m_aEntries728[8];    // +0x728 a file count of entries
    uint32_t m_unk7a8;             // +0x7a8
    uint32_t* m_pUnk7ac;           // +0x7ac m_unk50 x 7 words (not when +0x71f is 1)
    float m_unk7b0;                // +0x7b0
    float m_unk7b4;                // +0x7b4
    uint32_t m_unk7b8;             // +0x7b8
    float m_unk7bc[4];             // +0x7bc..+0x7c8
    float m_unk7cc;                // +0x7cc
    float m_unk7d0;                // +0x7d0
    float m_unk7d4;                // +0x7d4 PostLoad: 1.0f / +0x7d0
    uint8_t m_unk7d8;              // +0x7d8
    uint8_t m_pad7d9[3];
    float m_unk7dc;                // +0x7dc
    float m_unk7e0;                // +0x7e0
    float m_unk7e4;                // +0x7e4 PostLoad: 1.0f / +0x7e0
    uint8_t m_unk7e8;              // +0x7e8
    uint8_t m_pad7e9[3];
    uint32_t* m_pUnk7ec;           // +0x7ec m_unk50 words (when +0x71f is 1)
    uint32_t* m_pUnk7f0;           // +0x7f0 m_unk50 words (when +0x71f is 1)
    float m_unk7f4;                // +0x7f4
    float m_unk7f8;                // +0x7f8
    uint32_t m_unk7fc;             // +0x7fc
    uint32_t m_unk800;             // +0x800
    float m_unk804;                // +0x804
    float m_unk808;                // +0x808 one 0xc read with the next two
    uint32_t m_unk80c;             // +0x80c
    float m_unk810;                // +0x810
    float m_unk814;                // +0x814
    float m_unk818;                // +0x818
    float m_unk81c;                // +0x81c
    float m_unk820;                // +0x820
    uint32_t m_aUnk824[4];         // +0x824
    uint8_t* m_pUnk834;            // +0x834 m_unk54 x 4 bytes, raw
};
static_assert(CFogBoxNodeFx::kClassKey == 0x68b, "key");
DOTD_ASSERT_SIZE(CFogBoxNodeFx, 0x838);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_aBoxes, 0x3c);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_pTexture, 0x48);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_aPairs78, 0x78);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_aBytes6b8, 0x6b8);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk71f, 0x71f);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_aEntries728, 0x728);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_pUnk7ac, 0x7ac);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk7bc, 0x7bc);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk7d8, 0x7d8);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk7e8, 0x7e8);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_pUnk7f0, 0x7f0);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk800, 0x800);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk820, 0x820);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_pUnk834, 0x834);
