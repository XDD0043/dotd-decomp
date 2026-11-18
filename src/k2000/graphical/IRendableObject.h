// IRendableObject.h - base of everything the renderer draws (key 0xa8d, vtable 0xb17218; XXL2:
// K/KModules/KGL/Main/IRendableObject.h): the graphics managers, CScene2d, the geometries, the screen
// effects (IScreenFx 0xacd). Its slots after IKSerializable's are XXL2's 20 and 22..30 (DotD has no
// KUGetUseUniqueNameTrue): co-override agreement over the 13 classes in both games
// (outputs/remake/research/xxl2-symbols.md).
// The constructor is inlined into every derived constructor; the derived ports set the fields.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"

class IKTime;
class RenderQueue;
struct RwCamera;

class IRendableObject : public IKSerializable {
public:
    ~IRendableObject() override {}                                         // vt+0x00 / +0x04  0x9a0580 / 0x9a0540
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xa8d || key == 0xc; }  // vt+0x08 0x9a0520
    void Destroy() override { m_pLightSet = nullptr; }                     // vt+0x10 0xa7248
    void RecursiveRegistration(int32_t type) override;                     // vt+0x24 0xa71e8
    int32_t Load(IKFile* file, int32_t type) override;                     // vt+0x2c 0xa7258
    int32_t GetSerializationFlags() override { return 2; }                 // vt+0x34 0x997cd8
    virtual int32_t KUGetCheckStateTrue() { return 1; }                    // vt+0x50 0x990c10
    virtual void PreUpdate(IKTime* /*time*/) {}                            // vt+0x54 0x990c18
    // vt+0x58 0x997ce0 (empty). XXL2: UpdateAndExtract(IAccumulator**, IKTime*). The PS3 call (RenderGameFrame 0xa1c08, as the
    // scene root's traversal) passes (0.0, the renderer's stage array, the frame clock, the main camera, 0).
    virtual void UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** /*stages*/, IKTime* /*frameClock*/, RwCamera* /*camera*/,
                                  int32_t /*distanceCull*/) {}
    virtual void Render(IKTime* frameClock) = 0;                           // vt+0x5c: the queue's frame clock (r4)
    virtual void UpdateProperties() {}                                     // vt+0x60 0x997b08
    // vt+0x64 0xa71d8: installs the new light set, returns the old one.
    virtual IKSerializable* ChangeLightSet(IKSerializable* lightSet);
    virtual void KUSetLightSet(IKSerializable* lightSet) { m_pLightSet = lightSet; }  // vt+0x68 0x990c20 (XXL2 adds a Bool)
    // vt+0x6c 0xa71b0. XXL2: (Bool&, UInt8&, Bool&, CMaterial::EBlendMode&); defaults 0, 0xff, 0, 0.
    virtual void GetRenderingProperties(uint8_t* first, uint8_t* second, uint8_t* third, uint32_t* blendMode);
    virtual int32_t CanBeUpdated() { return 1; }                           // vt+0x70 0x990c28
    // vt+0x74 0x997ce8: stores the word 0 (XXL2: ComputeSortingCoef(ESortingOrder)). The render queues
    // pass their sorting order: 1 (RenderQueueType6), 2 (RenderQueueType1), ...
    virtual void ComputeSortingCoef(int32_t /*sortingOrder*/) { m_fSortingCoef = 0.0f; }

    IRendableObject* m_pNextAccumulatedObject;  // +0x04 Load sets 0
    // +0x08 where XXL2 has m_pPriorityParent (read as a handle); DotD reads a plain u32 (no handle).
    uint32_t m_pPriorityParent;
    float m_fSortingCoef;                       // +0x0c
    IKSerializable* m_pLightSet;                // +0x10 CLightSet (a handle)
    uint32_t m_BitProperties;                   // +0x14 (XXL2 CBitArray)
};
DOTD_ASSERT_SIZE(IRendableObject, 0x18);
DOTD_ASSERT_OFFSET(IRendableObject, m_pPriorityParent, 0x08);
DOTD_ASSERT_OFFSET(IRendableObject, m_pLightSet, 0x10);
DOTD_ASSERT_OFFSET(IRendableObject, m_BitProperties, 0x14);
