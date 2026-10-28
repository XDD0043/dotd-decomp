// IScreenFx.h - base of the full-screen effects (key 0xacd, vtable 0xb16d10, no fields of its own;
// XXL2: K/KModules/KGL/Main/ScreenFx/IScreenFx.h, no members). Derived: CBackgroundCopyRender,
// CDistortionScreenFx, CLensFlareFx, CPostRenderingFx (CColorizedScreenFx derives from IRendableObject
// directly in DotD: its Create stores the IRendableObject vtable 0xb17218 first).
//
// The methods are inline; their out-of-line copies (0x99c658..0x99c820) are listed in the checklist of
// CBackgroundCopyRender.cpp. The constructor is inlined into every derived Create.
#pragma once
#include <cstdint>

#include "k2000/graphical/IRendableObject.h"

class IScreenFx : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x2b)  // vt+0x14 / +0x18  0x99c680 (13) / 0x99c688 (0x2b)

    ~IScreenFx() override {}  // vt+0x00 / +0x04  0x99c820 / 0x99c790
    // vt+0x08 0x99c658
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xacd || key == 0xa8d || key == 0xc; }
    void Destroy() override { IRendableObject::Destroy(); }       // vt+0x10 0x99c710 (calls 0xa7248)
    void RecursiveRegistration(int32_t /*type*/) override {}      // vt+0x24 0x99c690 (returns 1, registers nothing)
    int32_t Load(IKFile* file, int32_t type) override {           // vt+0x2c 0x99c6c0 IScreenFx_Load
        IRendableObject::Load(file, type);
        return 1;
    }
    int32_t GetSerializationFlags() override { return 1; }        // vt+0x34 0x99c6a0
    // vt+0x58 / +0x5c: pure in IScreenFx (both are __cxa_pure_virtual in 0xb16d10; XXL2 declares
    // UpdateAndExtract and Render pure here).
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera, int32_t distanceCull) override = 0;
    void Render() override = 0;
    // vt+0x70 0x99c738: !(g_pEngine->m_graphic->m_renderer word +0xa4 & 2) (xori 2, bit 1): not while the world
    // stages are skipped.
    int32_t CanBeUpdated() override;
};
