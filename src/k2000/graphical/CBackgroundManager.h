// CBackgroundManager.h - the sky/background roots of the level (key 0x68d, vtable 0xb16d90, size 0x24).
// Original unit: CBackgroundManager.cpp (0x935d0-0x94bf0). XXL2: K/KModules/KGL/Main/CBackgroundManager.h
// (m_apRootNode, m_ui8NbRootNode, ..., and CBackgroundData). A renderer stage manager: created by
// InitializeRendererStages (renderer +0xa8), handed to the loader as the global 13:26.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/IRendableObject.h"

// One background (XXL2 CBackgroundData; 0x1c bytes on the PS3). DotD's Load reads XXL2's fields without
// m_fBaseScaleModel, in XXL2's order, plus a last word; the defaults match XXL2's constructor (10000 and
// 0.33). The names of +0x04 and +0x18 are inferences.
struct CBackgroundData {
    CBackgroundData();  // inlined in CBackgroundManager_Load (operator new(0x1c) and these stores)
    // 0x000944c8 (Ghidra CBackgroundManager_LoadSectorBackground; XXL2 CBackgroundData::Load). Reads only
    // for K_LEVEL_PLATEFORMS; returns 1.
    int32_t Load(IKFile* file, int32_t type);

    IKSerializable* m_pRootNode;    // +0x00 a CNode reference (LVL000: 0x28b)
    uint32_t m_unk04;               // +0x04 never written by the constructor or Load (XXL2 m_fBaseScaleModel _maybe)
    float m_fRadiusModel;           // +0x08 the constructor sets 10000.0
    uint32_t m_eRenderType;         // +0x0c the constructor sets 0
    float m_fPercentFogFadeBegin;   // +0x10 the constructor sets 0.33
    float m_fHorizon;               // +0x14 the constructor sets 0
    uint32_t m_unk18;               // +0x18 bit flags: the constructor sets (x & ~0xf) | 3; read last
};
DOTD_ASSERT_SIZE(CBackgroundData, 0x1c);

class CBackgroundManager : public IRendableObject {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x1a)
    DOTD_DECLARE_FACTORIES(CBackgroundManager)

    CBackgroundManager();                // 0x00093b30 CBackgroundManager_Create (inlined)
    ~CBackgroundManager() override {}    // STUB(C1.6): 0x94b68 / 0x94ba8
    // vt+0x08 0x99c880
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x68d || key == 0xa8d || key == 0xc; }
    void Destroy() override;                                // vt+0x10 0x00093b88 CBackgroundManager_Destroy
    int32_t Load(IKFile* file, int32_t type) override;      // vt+0x2c 0x00094790 CBackgroundManager_Load
    void Init();                                            // 0x00093680 CBackgroundManager_Init_maybe
    // 0x00093690 CBackgroundManager_HideAllBackgrounds_maybe: every background's root node hidden (flag 4 set).
    void HideAllBackgrounds();
    int32_t GetSerializationFlags() override { return 0; }  // vt+0x34 0x99c870
    // vt+0x54 0x000946e0 CBackgroundManager_PreUpdate: the root node of the background of each active sector shown (flag 4 cleared).
    void PreUpdate(IKTime* frameClock) override;
    // vt+0x70 0x00093a50 CBackgroundManager_CanBeUpdated: the renderer's bit 1 (the scene roots are not extracted) is clear.
    int32_t CanBeUpdated() override;
    void Render() override {}                               // vt+0x5c 0x99c878  STUB(C1.4)

    CBackgroundData** m_apRootNode;  // +0x18 operator new[] of count pointers, or null
    uint8_t m_ui8NbRootNode;         // +0x1c
    uint8_t m_unk1d[3];              // +0x1d not written by the constructor or Load (XXL2: m_ui8CurrentBackground,
                                     //       m_bUseFog, m_bUseFogWorld _maybe)
    uint32_t m_unk20;                // +0x20 not written by the constructor or Load (XXL2 m_pObjectToWarnAfterUpdate _maybe)
};
DOTD_ASSERT_SIZE(CBackgroundManager, 0x24);
DOTD_ASSERT_OFFSET(CBackgroundManager, m_apRootNode, 0x18);
DOTD_ASSERT_OFFSET(CBackgroundManager, m_ui8NbRootNode, 0x1c);
