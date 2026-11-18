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
    // 0x005ad660 CKHkWeatherCenter_Destructor (0x5ad5d8 deleting): the asked-preset nodes back to the pool, the list
    // empty; then the bases' vtables.
    ~CKHkWeatherCenter() override;

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x005ad8f0 CKHkWeatherCenter_Load
    // vt+0x10 0x005acf10 CKHkWeatherCenter_Destroy: every preset's Destroy (vt+0x10), then the preset array freed
    // (OperatorDeleteArray; the pointer is not cleared).
    void Destroy() override;
    // vt+0x1c 0x005ad758 CKHkWeatherCenter_MessageProc: 0x73 asks for preset data[3] (ignored past the count): the last
    // asked node takes it, applied when it is the first node's; 0x74 shows the clouds (a first byte 0) or hides them,
    // when they are not already so. Both answer 0, anything else 1.
    int32_t MessageProc(uint16_t message, void* data) override;
    // vt+0x30 0x005ad6c0 CKHkWeatherCenter_PostLoad: IKLife_PostLoad, then preset 0 applied; 1.
    int32_t PostLoad(int32_t type) override;
    // vt+0x38 0x005adda8 CKHkWeatherCenter_SetDefaultState: the clouds shown, the asked list reset to one node holding the
    // start preset (+0x40), that preset applied.
    void SetDefaultState(int32_t flag) override;
    // vt+0x40 0x005ad878 CKHkWeatherCenter_GetInfo: 200 the accessor 0x9cbf30 GetTriggerPropC8 (the clouds hidden:
    // m_ba8Infos bit 0 clear), value type 0.
    int32_t GetInfo(IKInfo* info, int32_t request) override;
    // vt+0x68 0x005add30 CKHkWeatherCenter_OnLevelExit_maybe: the clouds hidden, the camera clear colour back to the
    // config's (alpha 0).
    void Stop() override;
    // vt+0x7c 0x005ae200 CKHkWeatherCenter_Update: while the interpolation runs (+0x48 < 1), the ratio advances (+0x44
    // per second); past 1 the next preset is applied, else the current preset's two colours (+0x3c, +0x38) are the
    // blend of the previous and next presets'. Then UpdateCloudUVScroll.
    void Update(IKTime* frameClock) override;
    // vt+0x24 0x5ad730: IKHook's RecursiveRegistration (inherited). vt+0x50 / +0x70 / +0x78 0x5add18 / 0x5add20 /
    // 0x5add28: empty (IKHook's).

    // 0x005accc0 CKHkWeatherCenter_ApplyPreset_maybe: preset `index` copied into the current preset (with its UV scroll
    // speeds), the clouds node's pending parameters applied (and the preset's cloud parameters set with its bit 3), the
    // three background nodes shown or hidden by the preset's bits 1 (clouds), 0 (sky; shown: the camera clear colour back
    // to the config's) and 2 (sun).
    void ApplyPreset(uint8_t index);
    // 0x005adea8 CKHkWeatherCenter_UpdateCloudUVScroll_maybe: the background clouds' first geometry coloured (+0x3c) and
    // its UV offset scrolled (+0x40 / +0x44 per second, kept in [-1, 1]) unless the preset hides them; the sky's
    // geometries coloured (+0x38), or with the sky hidden the camera clear colour set from +0x38 (alpha 0).
    void UpdateCloudUVScroll(IKTime* frameClock);

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
