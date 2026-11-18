// CLensFlareFx.h - the lens flare screen effect (key 0x1b4d, vtable 0xb176f8, size 0x30) and its data (CLensFlareData,
// key 0x258d, size 0x28). Original unit: CLensFlareFx.cpp (0xb3170-0xb4808). Not in XXL2. Its Load is IScreenFx's
// (0x9a0bc8: IRendableObject_Load).
//
// Every level has one CLensFlareFx; it shows a CLensFlareData set by CKLensFlareNodeFx_Start (0x1c6af0, which also
// enables it) and is hidden by CKLensFlareNodeFx_Stop. No game file has a CKLensFlareFxData or a CLensFlareData, so
// the flare never shows in DotD.
#pragma once
#include <cstdint>

#include "Renderware/rwcore/RwTypes.h"
#include "k2000/core/Layout.h"
#include "k2000/graphical/fx/IScreenFx.h"

struct RwTexture;

// CLensFlareData (key 0x258d, vtable 0xb176a0, size 0x28): the flare's texture, its elements and its world position.
class CLensFlareData : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x96)
    DOTD_DECLARE_FACTORIES(CLensFlareData)

    // One flare element (0x1c bytes).
    struct Element {
        uint8_t m_unk00;      // +0x00 read, not used by the draw
        uint8_t m_pad01[3];
        float m_fDistance;    // +0x04 the element's place along the line through the screen centre (times its length)
        float m_fSize;        // +0x08 half size / 64
        float m_fU;           // +0x0c the texture coordinates of its top left corner
        float m_fV;           // +0x10
        uint8_t m_Color[4];   // +0x14 RGBA, read raw
        uint8_t m_ui8Flags;   // +0x18 bits 0-2: R, G, B tend to the screen-position colour; bits 3-4: the size mode
        uint8_t m_pad19[3];
    };

    CLensFlareData() {}  // 0x000b3538 CLensFlareData_Create: operator new(0x28), the vtable only
    // vt+0x08 0x9a0b48
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x258d || key == 0xc; }
    void Destroy() override;                            // vt+0x10 0x000b37e0 CLensFlareData_Destroy
    // vt+0x24 0x000b3780 CLensFlareData_RecursiveRegistration: type 0 registers the data.
    void RecursiveRegistration(int32_t type) override;
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x000b43d0 CLensFlareData_Load

    Element* m_pElements;   // +0x04 Mem_AllocAligned16(count * 0x1c)
    RwTexture* m_pTexture;  // +0x08 IKFile_ReadTextureRef (a reference taken)
    uint8_t m_unk0c;        // +0x0c
    uint8_t m_unk0d;        // +0x0d
    uint8_t m_pad0e[2];
    float m_fUSpan;         // +0x10 the texture span of an element
    float m_fVSpan;         // +0x14
    uint8_t m_ui8Count;     // +0x18
    uint8_t m_pad19[3];
    RwV3d m_vPosition;      // +0x1c the flare's source in the world
};
DOTD_ASSERT_SIZE(CLensFlareData::Element, 0x1c);
DOTD_ASSERT_SIZE(CLensFlareData, 0x28);
DOTD_ASSERT_OFFSET(CLensFlareData, m_ui8Count, 0x18);
DOTD_ASSERT_OFFSET(CLensFlareData, m_vPosition, 0x1c);

class CLensFlareFx : public IScreenFx {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x6d)
    DOTD_DECLARE_FACTORIES(CLensFlareFx)

    CLensFlareFx();                  // 0x000b3570 CLensFlareFx_Create (inlined)
    ~CLensFlareFx() override {}      // 0x009a0bf0 / 0x009a0c10 CLensFlareFx_Destructor / _DeletingDestructor: the vtables only
    // vt+0x08 0x9a0b68
    int32_t IsKindOfClass(uint32_t key) override {
        return key == 0x1b4d || key == 0xacd || key == 0xa8d || key == 0xc;
    }
    void Destroy() override;                                // vt+0x10 0x000b39a0 CLensFlareFx_Destroy
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x009a0bc8 CLensFlareFx_Load
    int32_t PostLoad(int32_t type) override;                // vt+0x30 0x000b3970 CLensFlareFx_PostLoad
    // vt+0x24 0x000b3720 CLensFlareFx_RecursiveRegistration: type 0 registers the effect (IScreenFx's registers nothing).
    void RecursiveRegistration(int32_t type) override;
    // vt+0x78 0x000b32e0 CLensFlareFx_vf78 (Clear, as XXL2's screen effects): a bare blr.
    virtual void Clear() {}
    int32_t GetSerializationFlags() override { return 2; }  // vt+0x34 0x9a0ac8
    // vt+0x58 0x000b3838 CLensFlareFx_UpdateAndExtract (Ghidra CLensFlareFx_Enqueue)
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera, int32_t distanceCull) override;
    void Render(IKTime* frameClock) override;                                 // vt+0x5c 0x000b43b8 CLensFlareFx_Render (Ghidra CLensFlareFx_Draw)
    // 0x000b32e8 CLensFlareFx_SetEnabled: bit 8 of the properties = `on` (the whole word shifted in).
    void SetEnabled(int32_t on);

    CLensFlareData* m_pData;  // +0x18 the shown flare (CKLensFlareNodeFx_Start); PostLoad clears it
    float m_afScreen[2];      // +0x1c the source projected to the screen (raster pixels)
    RwV3d m_vPosition;        // +0x24 the source (copied from the data each frame)
};
DOTD_ASSERT_SIZE(CLensFlareFx, 0x30);
DOTD_ASSERT_OFFSET(CLensFlareFx, m_pData, 0x18);
DOTD_ASSERT_OFFSET(CLensFlareFx, m_afScreen, 0x1c);
DOTD_ASSERT_OFFSET(CLensFlareFx, m_vPosition, 0x24);

// 0x000b39c8 DrawLensFlareElements (also its entry 0xb43b0).
void DrawLensFlareElements(CLensFlareFx* fx, CLensFlareData* data);
