// CFogBoxNodeFx.h - a volumetric fog box effect (key 0x68b, vtable 0xb189a0, size 0x838). Original unit:
// CFogBoxNodeFx.cpp. No XXL2 class; the fields keep their offsets (the Ghidra struct's nUnkXX / flUnkXX)
// until named. The read order is the original's (see Load); offsets not read are left as the constructor
// (CNode's only) leaves them.
//
// The particles: every box (m_aBoxes, the active ones first: m_unk40 of m_ui32NbBoxes) shows the same m_unk50
// particles, simulated once a frame in the box's space by the first visible box and copied to the others (the
// PTank holds m_ui32NbBoxes x m_unk50 particles: positions, colours, 2D rotations). The simulation mode is +0x71f
// (LVL010: 0 drift to random targets in the box, 1 ring (the air currents' boxes), 3 rise through the box).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/INodeFx.h"
#include "k2000/math/CMatrix34.h"

class CParticleGeometry;

class CFogBoxNodeFx : public INodeFx {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x1a)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a4da8
        return key == 0x68b || key == 0x50b || key == 0xcb || key == 0x24b || key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CFogBoxNodeFx)

    // A box (PS3 0x10 bytes): a loaded matrix, its record id (the air currents' AddRecords: 1-based), a scale and the
    // distance from the camera to its centre minus the radius (UpdateParticles).
    struct SBox {
        CMatrix34* m_pMatrix;  // +0x00 RwMatrixCreate + CMatrix34_LoadMatrix
        uintptr_t m_unk04;     // +0x04 Load sets 0; the record id (air currents) or the owner hook (save points)
        float m_unk08;         // +0x08 Load sets 1.0f (TOC -0x5034): the scale (z extent, mode 3)
        float m_fDistance;     // +0x0c UpdateParticles
    };
    // An entry of the colour keys at +0x728 (0x10 bytes): the time and its random part, the colour range.
    struct SEntry728 {
        float m_af[2];       // +0x00 swapped: the duration, its random part
        uint8_t m_raw08[4];  // +0x08 read raw (file bytes): the colour's low end
        uint8_t m_raw0c[4];  // +0x0c read raw (file bytes): the colour's high end
    };
    // A particle (0x1c bytes, +0x7ac): the target, the current position (box space) and the speed.
    struct SParticle {
        float m_target[3];    // +0x00
        float m_position[3];  // +0x0c
        float m_fSpeed;       // +0x18
    };
    // A particle's colour (0x20 bytes, +0x7a8): moves from the current to the target at the speed, then to the next
    // colour key.
    struct SParticleColor {
        uint8_t m_target[4];   // +0x00
        uint8_t m_current[4];  // +0x04
        float m_fSpeed;        // +0x08
        float m_colorF[4];     // +0x0c
        uint32_t m_ui32Key;    // +0x1c
    };
    // A PTank particle of a box (0x10 bytes, +0x830): its position, colour and rotation entries, its index.
    struct SParticleRef {
        float* m_pPosition;   // +0x00
        uint8_t* m_pColor;    // +0x04
        uint16_t m_ui16Index; // +0x08 box * m_unk50 + particle
        uint16_t m_pad0a;
        float* m_pRotation;   // +0x0c (flag 0x2000)
    };

    // 0x000dcde0 CFogBoxNodeFx_Create (the constructor inlined): CNode's, the colour keys (1, 0, white, white), the
    // fade ramp and the arrays cleared.
    CFogBoxNodeFx();
    ~CFogBoxNodeFx() override {}

    // vt+0x1c 0x000dab30 CFogBoxNodeFx_MessageProc: 0x1a00 / 0x1a01 fade in / out (+0x808).
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x10 0x000da5c0 CFogBoxNodeFx_Destroy: CNode's, then every array freed and cleared (a sector reload
    // re-runs Load / PostLoad on the same object) and the boxes' matrices destroyed with their buffer.
    void Destroy() override;
    // vt+0x2c 0x000dd1f8 CFogBoxNodeFx_Load (type 0 only after INodeFx's)
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x000dcb20 CFogBoxNodeFx_PostLoad: the radius, the particle arrays, the PTank constants, the particles
    // (InitParticles: rand draws), the colours (rand draws), the boxes reset (type 0).
    int32_t PostLoad(int32_t type) override;
    // vt+0x58 0x000def38 CFogBoxNodeFx_UpdateParticles_maybe: the boxes in the camera's frustum are listed, the first
    // one simulates the particles (colour keys and targets: rand draws), the others copy them; then the boxes'
    // transforms and the near / far fades; the geometry queued; the children traversed.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;

    // 0x000dbfa0 CFogBoxNodeFx_AllocParticleArrays_maybe
    void AllocParticleArrays();
    // 0x000dc8b0 CFogBoxNodeFx_InitParticles_maybe: the random values (0x2000) and the particles by mode.
    void InitParticles();
    // 0x000dae70 CFogBoxNodeFx_InitParticleRandomValues_maybe: per particle a rotation and its speed (2 rand draws).
    void InitParticleRandomValues();
    // 0x000dbae0 CFogBoxNodeFx_InitParticlesRandomInBox_maybe (mode 0): 4 rand draws per particle.
    void InitParticlesRandomInBox();
    // 0x000dc618 CFogBoxNodeFx_RandomizeParticlePositions_maybe (mode 3): 4 rand draws per particle.
    void RandomizeParticlePositions();
    // 0x000db1a0 CFogBoxNodeFx_InitParticleColors_maybe: 3 rand draws per particle (mode 4: no draw).
    void InitParticleColors();
    // 0x000da968 CFogBoxNodeFx_RandomizeEmitterParticles_maybe: 3 rand draws per particle (mode 0 with 0x20000).
    void RandomizeEmitterParticles(int32_t enable, uint32_t box);
    // The colour key step of every simulated particle (inlined in each mode): toward the target; on it, the next key
    // (3 rand draws).
    void StepParticleColor(SParticleColor* color, float dt);

    float m_fTime;                 // +0x2c the time (UpdateParticles adds the frame time)
    float m_unk30;                 // +0x30 the radius of a box (PostLoad)
    SBox** m_apVisibleBoxes;       // +0x34 m_ui32NbBoxes pointers after the boxes (same buffer)
    uint32_t m_ui32NbVisibleBoxes; // +0x38
    SBox* m_aBoxes;                // +0x3c Mem_AllocAligned16(m_ui32NbBoxes * 0x14)
    uint32_t m_unk40;              // +0x40 read first: the active boxes
    uint32_t m_ui32NbBoxes;        // +0x44
    void* m_pTexture;              // +0x48 IKFile_ReadTextureRef (resolve 0)
    CParticleGeometry* m_pGeometry;  // +0x4c PostLoad: the node's first geometry (a CParticleGeometry)
    uint32_t m_unk50;              // +0x50 the particles per box (the count of the +0x7ac / +0x7ec / +0x7f0 arrays)
    uint32_t m_unk54;              // +0x54 the count of the +0x834 array (the PTank's particles)
    uint32_t m_unk58;              // +0x58 the particles drawn this frame
    float m_unk5c[3];              // +0x5c one 0xc read: the box's half extents
    float m_unk68[2];              // +0x68 one 8-byte read: the particle size
    float m_unk70;                 // +0x70 PostLoad sets -1.0f: the next flipbook frame's time
    float m_unk74;                 // +0x74 the flipbook interval
    uint32_t m_aPairs78[200][2];   // +0x78 count x 8 bytes, each word swapped: the flipbook tex coords
    uint8_t m_aBytes6b8[100];      // +0x6b8 count / 2 bytes, raw: the flipbook frames
    uint8_t m_unk71c;              // +0x71c the flipbook frame
    uint8_t m_unk71d;              // +0x71d the flipbook columns
    uint8_t m_unk71e;              // +0x71e the flipbook rows
    uint8_t m_unk71f;              // +0x71f read first among the bytes: the mode; 1 selects the +0x7ec/+0x7f0 arrays
    uint8_t m_aUnk720[4];          // +0x720 four bytes, one read each (+0x720: the blend mode)
    uint32_t m_unk724;             // +0x724 the colour keys
    SEntry728 m_aEntries728[8];    // +0x728 a file count of entries
    SParticleColor* m_aColors;     // +0x7a8 InitParticleColors: m_unk50 entries
    SParticle* m_pUnk7ac;          // +0x7ac m_unk50 particles (not when +0x71f is 1)
    float m_unk7b0;                // +0x7b0 the particle speed
    float m_unk7b4;                // +0x7b4 its random part
    float* m_pRandomValues;        // +0x7b8 InitParticleRandomValues: m_unk50 x (rotation, speed)
    float m_unk7bc[4];             // +0x7bc..+0x7c8 the rotation speed and its random part, the rotation, its part
    float m_unk7cc;                // +0x7cc the near fade start
    float m_unk7d0;                // +0x7d0 the near fade length
    float m_unk7d4;                // +0x7d4 PostLoad: 1.0f / +0x7d0
    uint8_t m_unk7d8;              // +0x7d8 the near fade exponent
    uint8_t m_pad7d9[3];
    float m_unk7dc;                // +0x7dc the far fade end
    float m_unk7e0;                // +0x7e0 the far fade length
    float m_unk7e4;                // +0x7e4 PostLoad: 1.0f / +0x7e0
    uint8_t m_unk7e8;              // +0x7e8 the far fade exponent
    uint8_t m_pad7e9[3];
    float* m_pUnk7ec;              // +0x7ec m_unk50 words (when +0x71f is 1): the start angles (radians)
    float* m_pUnk7f0;              // +0x7f0 m_unk50 words (when +0x71f is 1): the angular speeds (radians per second)
    float m_unk7f4;                // +0x7f4
    float m_unk7f8;                // +0x7f8
    void* m_pUnk7fc;               // +0x7fc a buffer (Destroy frees it); no writer is ported
    float m_unk800;                // +0x800 the rotation speed of the first visible box (mode 3; degrees per second)
    float m_unk804;                // +0x804 the fade's target on message 0x1a00
    float m_unk808;                // +0x808 one 0xc read with the next two: a FloatApproach {target, speed, current}
    float m_unk80c;                // +0x80c
    float m_unk810;                // +0x810 the fade (mode 3's alpha)
    float m_unk814;                // +0x814 the swirl radius (mode 3)
    float m_unk818;                // +0x818 its random part
    float m_unk81c;                // +0x81c the swirl speed
    float m_unk820;                // +0x820 its random part
    float* m_pSwirlRadius;         // +0x824 RandomizeParticlePositions: m_unk50 floats (mode 3)
    float* m_pSwirlSpeed;          // +0x828 m_unk50 floats (mode 3)
    float* m_pSortKeys;            // +0x82c AllocParticleArrays: m_unk54 floats
    SParticleRef* m_aParticleRefs; // +0x830 AllocParticleArrays: m_unk54 entries
    uint8_t* m_pUnk834;            // +0x834 m_unk54 x 4 bytes, raw
};
static_assert(CFogBoxNodeFx::kClassKey == 0x68b, "key");
DOTD_ASSERT_SIZE(CFogBoxNodeFx, 0x838);
DOTD_ASSERT_SIZE(CFogBoxNodeFx::SBox, 0x10);
DOTD_ASSERT_SIZE(CFogBoxNodeFx::SParticle, 0x1c);
DOTD_ASSERT_SIZE(CFogBoxNodeFx::SParticleColor, 0x20);
DOTD_ASSERT_SIZE(CFogBoxNodeFx::SParticleRef, 0x10);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_fTime, 0x2c);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_aBoxes, 0x3c);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_pTexture, 0x48);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_aPairs78, 0x78);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_aBytes6b8, 0x6b8);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk71f, 0x71f);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_aEntries728, 0x728);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_aColors, 0x7a8);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_pUnk7ac, 0x7ac);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk7bc, 0x7bc);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk7d8, 0x7d8);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk7e8, 0x7e8);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_pUnk7f0, 0x7f0);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk800, 0x800);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_unk820, 0x820);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_pSwirlRadius, 0x824);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_aParticleRefs, 0x830);
DOTD_ASSERT_OFFSET(CFogBoxNodeFx, m_pUnk834, 0x834);
