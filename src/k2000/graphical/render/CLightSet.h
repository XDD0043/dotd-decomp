// CLightSet.h - the lights that affect a group of objects (key 0x94d, vtable 0xb16ee8, size 0x7c). Its
// code is in CLightManager.cpp (0x97e50-0x9e1a0). XXL2: K/KModules/KGL/Main/CLightManager.h, the same
// members in the same order; DotD adds +0x74 and +0x78.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CBBox.h"
#include "k2000/util/TVector.h"

class CLightComponent;

class CLightSet : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryGraphical, 0x25)
    DOTD_DECLARE_FACTORIES(CLightSet)

    CLightSet();                   // 0x0009b770 CLightSet_Create (inlined)
    ~CLightSet() override {}       // STUB(C1.6): 0x99cbd0 / 0x99ca68 (frees the light lists)
    // vt+0x08 0x99ca48
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x94d || key == 0xc; }
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0009cd28 CLightSet_Load
    // 0x0009b7e0 CLightSet_InitLightLists_maybe (XXL2 CLightSet::InitializeData): sizes both lists to 10
    // lists of 10 entries each, sets both occlusion levels to -1.
    void InitializeData();

    // C2.4 step 6 (all in CLightManager.cpp). 0x00098f18 LightZone_UpdateWorldBounds_maybe: the world influence box from the
    // local one: moved by the followed leaf's frame (or its bone, +0x74), by the camera's for kind 3, as it is otherwise; the
    // volume; the accumulation lists of the first ten occlusion levels emptied.
    void UpdateWorldBounds();
    // 0x0009ba90 CLightSet_GrowZoneArrays_maybe: the accumulation lists grown to hold occlusion level `level`.
    void GrowZoneArrays(uint32_t level);
    // 0x000981c8 LightZone_AccumulateLights_maybe: the components of one group (mode 0: 0-2, mode 1: 3-4) made from the lights
    // of occlusion level `level` (their colours and directions weighted by their overlap ratios), over those of the lower levels
    // for the part that is not covered.
    void AccumulateLights(uint32_t level, uint32_t mode);

    uint32_t m_baProperties;                                     // +0x04 (XXL2 CBitArray)
    TVector<TVector<float, 10>, 10> m_afAccumulatedLightRatio;   // +0x08 the constructor sets capacity 10
    TVector<TVector<IKSerializable*, 10>, 10> m_avpAccumulatedLight;  // +0x14 const CSGLight*; capacity 10
    int32_t m_i32MaxOcclusionLevel[2];                           // +0x20 InitializeData sets -1, -1
    CLightComponent* m_apLightComponent[5];                      // +0x28 references
    CBBox m_xLocalInfluenceBox;                                  // +0x3c
    CBBox m_xWorldInfluenceBox;                                  // +0x54 not written by Load
    float m_fWorldInfluenceBoxVolume;                            // +0x6c not written by Load
    IKSerializable* m_pFollowedLeaf;                             // +0x70 CSGLeaf reference; the constructor sets 0
    int32_t m_unk74;                                             // +0x74 the constructor sets -1; PostLoad -1 when
                                                                 //       (m_baProperties & 3) != 2 (Ghidra nSpUnkInt): the bone
                                                                 //       of the followed leaf the box follows (-1: its frame)
    uint32_t m_unk78;                                            // +0x78 read first (Ghidra nOgSector): the sector the set
                                                                 //       belongs to (0: any)
};
DOTD_ASSERT_SIZE(CLightSet, 0x7c);
DOTD_ASSERT_OFFSET(CLightSet, m_baProperties, 0x04);
DOTD_ASSERT_OFFSET(CLightSet, m_afAccumulatedLightRatio, 0x08);
DOTD_ASSERT_OFFSET(CLightSet, m_avpAccumulatedLight, 0x14);
DOTD_ASSERT_OFFSET(CLightSet, m_i32MaxOcclusionLevel, 0x20);
DOTD_ASSERT_OFFSET(CLightSet, m_apLightComponent, 0x28);
DOTD_ASSERT_OFFSET(CLightSet, m_xLocalInfluenceBox, 0x3c);
DOTD_ASSERT_OFFSET(CLightSet, m_pFollowedLeaf, 0x70);
DOTD_ASSERT_OFFSET(CLightSet, m_unk74, 0x74);
DOTD_ASSERT_OFFSET(CLightSet, m_unk78, 0x78);
