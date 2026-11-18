// CKInputIconNodeFx.h - the input-icon effect node (key 0x458c, vtable 0xb1d098, size 0x3c). Original unit:
// CKInputIconNodeFx.cpp. Its data is CKInputIconFxData (0x45cc). Not in XXL2; names ours. Load reads only the
// IKNodeFx part.
//
// The icon is the node's (+0x10) first geometry: a quad whose material shows either the data's texture (+0x40) or the
// glyph of a font (data +0x08) for a controller button (the data's input sequence +0x0c, or the action block of an
// input block sequence +0x28). It is placed in the world (facing the camera, pulled toward it by data +0x2c) or on the
// screen (data +0x30: at the effect's position as screen coordinates; data +0x33: the world position projected), and
// scaled between two sizes by the camera distance (data +0x14..+0x28).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/fx/IKNodeFx.h"
#include "k2000/math/CMatrix34.h"

class CKInputBlockSequential;
class KBase628C;

class CKInputIconNodeFx : public IKNodeFx {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x116)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9ac750
        return key == 0x458c || key == 0x148c || key == 0x154c || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CKInputIconNodeFx)

    // Inlined in 0x001c5d48 CKInputIconNodeFx_Create (0x001c4ab0 Construct / 0x001c4af0 Construct_2: the same).
    CKInputIconNodeFx() : m_pFxData(nullptr) {}
    ~CKInputIconNodeFx() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001c4a10 CKInputIconNodeFx_Load
    void RecursiveRegistration(int32_t type) override;  // vt+0x24 0x001c4a60 CKInputIconNodeFx_RecursiveRegistration
    // vt+0x30 PostLoad 0x1c49e8: IKNodeFx_PostLoad, then 1 (the IKNodeFx default does the same).

    void Vf64() override;                                // vt+0x64 0x001c5a88 CKInputIconNodeFx_Start
    void Stop() override;                                // vt+0x6c 0x001c4968 CKInputIconNodeFx_Stop
    void Vf70() override;                                // vt+0x70 0x001c4588 CKInputIconNodeFx_OnPause: hidden (vt+0x60)
    void Update(IKTime* frameClock) override;            // vt+0x78 0x001c5558 CKInputIconNodeFx_Update
    void StopIfLinkedTo(int32_t sector) override;        // vt+0x7c 0x001c44d0 CKInputIconNodeFx_StopIfLinkedTo
    IKFxData* GetFxData() override;                      // vt+0x80 0x009ac798 [inline]
    void SetFxData(IKFxData* data) override;             // vt+0x84 0x009ac7a0 [inline]

    // 0x001c45c8 CKInputIconNodeFx_SetPosition_maybe: the position, plus the data's offset (+0x34) when there is data.
    void SetPosition(const CVector3* position);
    // 0x001c4bd8 InputIconFx_UpdateWorldPosition_maybe: the position = the matrix's position plus the data's offset
    // (+0x34; the null vector without data) taken through the matrix's axes.
    void UpdateWorldPosition(const CMatrix34* matrix);
    // 0x001c46c8 CKInputIconNodeFx_ApplyDisplayMode_maybe: the geometries' screen/world render flags and the node
    // moved under `parent` (or the screen / dynamic scene root).
    void ApplyDisplayMode(IKSerializable* parent);
    // 0x001c4d30 CKInputIconNodeFx_UpdatePlacement_maybe: the node's frame (position, orientation, scale).
    void UpdatePlacement();
    // 0x001c5da8 CKInputIconNodeFx_SetAlpha_maybe (C2.8 sequence: the sequence manager's button icons): the geometry's
    // alpha (0xff is kept as 0xfe) with render flag 11 (translucent) set; a material of modes 1..6 with render flag 12
    // stays opaque (0xff, flag 11 clear). UpdateProperties (vt+0x60) when flag 11 changes.
    void SetAlpha(uint8_t alpha);

    IKSerializable* m_pFxData;   // +0x14 the inline GetFxData (0x9ac798); the constructor sets 0; Stop clears it
    CVector3 m_vPosition;        // +0x18 the icon's position (world, or screen coordinates with data +0x30); Start: data +0x34
    int32_t m_i32BlockId;        // +0x24 the action block's step index to show (-1: the sequence's active block); Start -1
    CKInputBlockSequential* m_pInputBlocks;  // +0x28 an input block sequence (null: the data's input sequence); Start 0
    KBase628C* m_pActionBlock;   // +0x2c the action block found by Update (0 otherwise)
    float m_fBlinkTimer;         // +0x30 seconds since the glyph last alternated (Update)
    int32_t m_i32BlinkPhase;     // +0x34 0 / 1: added to the glyph while the block waits (vt+0x7c)
    int32_t m_i32Config;         // +0x38 the input configuration (-1: the data's +0x10); Start -1
};
static_assert(CKInputIconNodeFx::kClassKey == 0x458c, "key");
DOTD_ASSERT_SIZE(CKInputIconNodeFx, 0x3c);
DOTD_ASSERT_OFFSET(CKInputIconNodeFx, m_pFxData, 0x14);
DOTD_ASSERT_OFFSET(CKInputIconNodeFx, m_vPosition, 0x18);
DOTD_ASSERT_OFFSET(CKInputIconNodeFx, m_i32BlockId, 0x24);
DOTD_ASSERT_OFFSET(CKInputIconNodeFx, m_pActionBlock, 0x2c);
DOTD_ASSERT_OFFSET(CKInputIconNodeFx, m_i32Config, 0x38);
