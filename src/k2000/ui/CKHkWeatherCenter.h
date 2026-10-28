// CKHkWeatherCenter.h - the weather hook switching between weather presets (key 0x3a82, vtable 0xb2ed60,
// size 0x4c; library-TOC code). Original unit: k2000/ui/CKHkWeatherCenter.cpp. XXL2:
// K/KWeatherCenter/CKHkWeatherCenter.h: the same members in the same order (XXL2's Load reads them in
// the same order too), so the names are XXL2's.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/hooks/IKHook.h"

class CKHkWeatherCenter : public IKHook {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xea)
    DOTD_DECLARE_FACTORIES(CKHkWeatherCenter)

    // A node of m_lAskedPreset (12 bytes; FreeListPool at 0x00ceaa20 in the original, here new/delete
    // like the other pool nodes).
    struct PresetNode {
        uint8_t m_ui8Preset;      // +0x00 the preset index_maybe (the Load's node: 0). The PS3 node's other
        uint8_t m_pad1[3];        //       three bytes keep the pool's free-list link bytes.
        CKHkWeatherCenter* m_pOwner;  // +0x04 the hook_maybe (the Load stores this)
        PresetNode* m_pNext;      // +0x08
    };

    // 0x005ad440 CKHkWeatherCenter_Create (inlined constructor, = 0x005acb98 _Construct): the
    // IKLife/IKHook defaults, then the asked-preset list empty.
    CKHkWeatherCenter() { m_lAskedPreset = nullptr; }
    ~CKHkWeatherCenter() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005ad8f0 CKHkWeatherCenter_Load

    IKSerializable* m_pCloudsNodeFx;          // +0x20 XXL2 CCloudsNodeFx*
    IKSerializable* m_pBackgroundSkyNode;     // +0x24 XXL2 CNode*
    IKSerializable* m_pBackgroundCloudsNode;  // +0x28 XXL2 CNode*
    IKSerializable* m_pBackgroundSunNode;     // +0x2c XXL2 CNode*
    IKSerializable* m_pCurrentWeatherPreset;  // +0x30 XXL2 CKWeatherPreset*
    IKSerializable** m_apWeatherPreset;       // +0x34 XXL2 CKWeatherPreset** (OperatorNewArray, Load)
    uint8_t m_ui8NbPreset;                    // +0x38
    uint8_t m_pad39[3];
    PresetNode* m_lAskedPreset;               // +0x3c XXL2 PresetList (head)
    uint8_t m_ui8StartPreset;                 // +0x40
    uint8_t m_ui8CurrentPreset;               // +0x41 Load 0
    uint8_t m_ui8NextPreset;                  // +0x42 Load 0
    uint8_t m_pad43;
    float m_fInterpolSpeed;                   // +0x44 Load 1.0f
    float m_fInterpolRatio;                   // +0x48 Load 1.0f
};
DOTD_ASSERT_SIZE(CKHkWeatherCenter, 0x4c);
DOTD_ASSERT_OFFSET(CKHkWeatherCenter, m_pCloudsNodeFx, 0x20);
DOTD_ASSERT_OFFSET(CKHkWeatherCenter, m_pBackgroundSkyNode, 0x24);
DOTD_ASSERT_OFFSET(CKHkWeatherCenter, m_pCurrentWeatherPreset, 0x30);
DOTD_ASSERT_OFFSET(CKHkWeatherCenter, m_apWeatherPreset, 0x34);
DOTD_ASSERT_OFFSET(CKHkWeatherCenter, m_ui8NbPreset, 0x38);
DOTD_ASSERT_OFFSET(CKHkWeatherCenter, m_lAskedPreset, 0x3c);
DOTD_ASSERT_OFFSET(CKHkWeatherCenter, m_ui8StartPreset, 0x40);
DOTD_ASSERT_OFFSET(CKHkWeatherCenter, m_fInterpolSpeed, 0x44);
DOTD_ASSERT_OFFSET(CKHkWeatherCenter, m_fInterpolRatio, 0x48);
DOTD_ASSERT_SIZE(CKHkWeatherCenter::PresetNode, 0xc);
