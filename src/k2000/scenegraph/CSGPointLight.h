// CSGPointLight.h - a point light in the scene graph (key 0x94b, vtable 0xb18348, size 0x24). Original
// unit: CSGPointLight.cpp (0xd2338-...; its Delete sits in CSGMovable.cpp's range). No XXL2 class; the
// names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/scenegraph/CSGLeaf.h"

class CSGPointLight : public CSGLeaf {
public:
    DOTD_CLASS_KEY(kCategoryNode, 0x25)
    int32_t IsKindOfClass(uint32_t key) override {  // vt+0x08 0x9a2950
        return key == 0x94b || key == 0x20b || key == 0x14b || key == 0xc;
    }
    DOTD_DECLARE_FACTORIES(CSGPointLight)

    CSGPointLight() {}  // 0x000d2970 CSGPointLight_Create: CSGLeaf's constructor, then the vtable
    ~CSGPointLight() override {}
    // vt+0x10 0x000d26c8 CSGPointLight_Destroy: CSGLeaf's, then the light component reference cleared.
    void Destroy() override;

    // vt+0x2c 0x000d2418 CSGPointLight_Load: CSGLeaf's, then (type 0) the light, a float and a byte.
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x30 0x000d23c0 CSGPointLight_PostLoad: CSGLeaf's, then (type 0) the light component's +0x18 = this
    // node's frame.
    int32_t PostLoad(int32_t type) override;
    // vt+0x58 0x000d2918 CSGPointLight_Enqueue: the light component's colour animation advances; unless hidden (flag 4) the
    // node is stamped with the render frame counter.
    void UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                          int32_t distanceCull) override;

    uint8_t m_unk18;                // +0x18 read last
    uint8_t m_pad19[3];
    float m_unk1c;                  // +0x1c
    IKSerializable* m_pLight;       // +0x20 a CLightComponent (one-element reference array)
};
static_assert(CSGPointLight::kClassKey == 0x94b, "key");
DOTD_ASSERT_SIZE(CSGPointLight, 0x24);
DOTD_ASSERT_OFFSET(CSGPointLight, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CSGPointLight, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CSGPointLight, m_pLight, 0x20);
