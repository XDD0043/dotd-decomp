// CLightManager.cpp - reconstructed original translation unit 0x97e50-0x9e1a0 (GAME_TOC1, main_toc1), 60 functions, 43 live.
// Primary class: CLightManager  key 0x90d  category Graphical  size 0x64  vtable 0xb16f40
// Other owners: CLightSet (13), LightZone (4), CMaterialMode7or8SharedState (2), RegisterCLightManagerAndCLightSetClasses (1), ApplyLightingZone (1), Renderer (1), LightRig (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x97e50  CLightManager_Construct  [dead]
//   [ ] 0x97ee8  CLightSet_GetOwnerSector_maybe  [dead]
//   [x] 0x97ef8  CLightManager_RecursiveRegistration  (CLightManager::RecursiveRegistration)
//   [ ] 0x97ff0  CLightManager_RemovePointLight_maybe  [dead]
//   [ ] 0x98090  RegisterCLightManagerAndCLightSetClasses
//   [ ] 0x98148  _GLOBAL__I_98148
//   [ ] 0x98158  CLightSet_InitBounds_maybe  [dead]
//   [x] 0x981c8  LightZone_AccumulateLights_maybe
//   [ ] 0x989d8  LightZone_ResolveActiveLights_maybe  [dead]
//   [x] 0x98f18  LightZone_UpdateWorldBounds_maybe
//   [ ] 0x99258  LightZone_ComputeBoundsOverlapFraction_maybe  [dead]
//   [x] 0x994e8  ApplyLightingZone
//   [ ] 0x9a5c8  CLightManager_Save
//   [x] 0x9a5f0  Renderer_CreateWorldLights_maybe
//   [x] 0x9ab10  CLightSet_DeleteArray
//   [x] 0x9abb8  CLightManager_DeleteArray
//   [x] 0x9ac58  CLightSet_CreateArray
//   [x] 0x9ad30  CLightManager_GetLightField1C_maybe
//   [x] 0x9ad60  CLightManager_GetLightColor_maybe
//   [ ] 0x9adb8  CLightManager_GetPointLightRadius_maybe  [dead]
//   [x] 0x9adf0  CLightManager_GetLightRadius_maybe
//   [x] 0x9ae28  LightRig_GetNextDistinctLight_maybe
//   [x] 0x9afe0  CLightManager_Update
//   [x] 0x9b068  CLightManager_GetLightPosition_maybe
//   [x] 0x9b0d8  CLightManager_vf70
//   [ ] 0x9b0f8  CLightManager_Construct_2  [dead]
//   [ ] 0x9b190  CLightManager_GetPointLightPosition_maybe  [dead]
//   [x] 0x9b200  CLightManager_PostLoad  (PostLoad: returns 1, the default slot)
//   [x] 0x9b208  CLightManager_ComputeLightCount_maybe
//   [ ] 0x9b338  CLightSet_InitBounds_2_maybe  [dead]
//   [x] 0x9b3a8  CLightManager_DestroyRwLights_maybe
//   [ ] 0x9b5d0  CLightManager_GetPointLightColor_maybe  [dead]
//   [x] 0x9b628  CLightSet_RecursiveRegistration
//   [x] 0x9b770  CLightSet_Create
//   [x] 0x9b7d8  CLightSet_Destroy  (Destroy: empty, the default slot)
//   [x] 0x9b7e0  CLightSet_InitLightLists_maybe
//   [x] 0x9ba90  CLightSet_GrowZoneArrays_maybe
//   [ ] 0x9bc88  CLightSet_Save
//   [x] 0x9c068  CLightManager_Destroy
//   [x] 0x9c150  CLightManager_GatherLightsTouchingSphere_maybe
//   [x] 0x9c308  CLightManager_GatherPointLightsNearFocus_maybe
//   [x] 0x9c540  CompareNodesByCameraDistance_maybe
//   [x] 0x9c660  CLightManager_Create
//   [x] 0x9c730  CLightManager_CreateArray
//   [ ] 0x9c860  FUN_0009c860  [dead]
//   [x] 0x9c8d8  CLightSet_PostLoad  (CLightSet::PostLoad)
//   [x] 0x9c988  CLightManager_Load
//   [x] 0x9cd28  CLightSet_Load
//   [x] 0x9d1a0  CLightManager_Enqueue
//   [ ] 0x9d7b0  CLightManager_Destructor_2  [dead]
//   [x] 0x9d8a8  CSGLight_ComputeZoneOverlapWeights_maybe
//   [x] 0x9ddb0  CLightManager_DeletingDestructor
//   [x] 0x9deb8  CLightManager_Destructor
//   [ ] 0x9dfb0  FUN_0009dfb0  [dead]
//   [ ] 0x9e010  KStub_Return1_9e010  [dead]
//   [x] 0x9e018  CMaterialMode7or8SharedState_Load_maybe  (CMaterialSharedState::Load, CMaterial.cpp)
//   [x] 0x9e100  CMaterialMode7or8SharedState_Release_maybe
//   [ ] 0x9e128  KStub_Return2_9e128  [dead]
//   [x] 0x9e130  CRenderer_Destroy  (the registry factory: CRenderer::Delete, CRenderer.cpp)
//   [ ] 0x9e180  FUN_0009e180  [dead]
//
//   [x] 0x99c9f0  CLightManager_IsKindOfClass  [inline]
//   [x] 0x99ca18  CLightManager_GetClassType  [inline]
//   [x] 0x99ca20  CLightManager_GetClassID  [inline]
//   [x] 0x99ca28  CLightManager_GetSerializationFlags  [inline]
//   [ ] 0x99ca30  CLightManager_Draw  [inline]
//   [x] 0x99ca38  CLightSet_GetClassType  [inline]
//   [x] 0x99ca40  CLightSet_GetClassID  [inline]
//   [x] 0x99ca48  CLightSet_IsKindOfClass  [inline]
//   [x] 0x99ca68  CLightSet_DeletingDestructor  [inline]
//   [x] 0x99cbd0  CLightSet_Destructor  [inline]
#include "k2000/graphical/render/CLightManager.h"

#include <cstring>

#include <cmath>

#include "Renderware/rphanim/RpHAnim.h"
#include "Renderware/rpworld/RpLight.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "crt/Ps3Qsort.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/graphical/render/CLightSet.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/render/CLightComponent.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGLight.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/CSGPointLight.h"

CLightManager* g_pLightManager = nullptr;  // 0x00c5c8ec

namespace {
// Constants of the math unit's static initialiser (StaticInitAndDestruction_11578, Str.cpp; live values).
// STUB: local copies until that unit exports them.
const uint8_t kColorBlack[4] = {0x00, 0x00, 0x00, 0xff};  // 0x00c50df8 CColor (r, g, b, a)
const CVector3 kVectorZero = {0.0f, 0.0f, 0.0f};          // 0x00c50d64
const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};               // 0x00c50d40 (the shared Y axis)

// count little-endian floats: one read, then each word byte-swapped (lwbrx on the PS3).
void ReadF32ArrayLE(IKFile* file, float* dst, uint32_t count) {
    uint8_t bytes[0x18];
    file->Read(bytes, count * 4);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = bytes + 4 * i;
        const uint32_t bits = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                              (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
        std::memcpy(&dst[i], &bits, 4);
    }
}
}  // namespace

// 0x0009c660 CLightManager_Create (= CLightManager_Construct 0x97e50), in the original's store order;
// +0x0c and +0x4c are left as they are.
CLightManager::CLightManager() {
    m_pNextAccumulatedObject = nullptr;
    m_BitProperties = 0;
    m_pPriorityParent = 0;
    m_pLightSet = nullptr;
    m_vLightSets.m_ui32NbElt = 2;
    m_vLightSets.m_pBlock = nullptr;
    m_vLightSets.m_ui32NbUsedElt = 0;
    m_vUnk24.m_ui32NbElt = 1;
    m_vUnk24.m_pBlock = nullptr;
    m_vUnk24.m_ui32NbUsedElt = 0;
    m_vUnk30.m_ui32NbElt = 1;
    m_vUnk30.m_pBlock = nullptr;
    m_vUnk30.m_ui32NbUsedElt = 0;
    m_vUnk3c.m_ui32NbElt = 1;
    m_vUnk3c.m_pBlock = nullptr;
    m_vUnk3c.m_ui32NbUsedElt = 0;
    g_pLightManager = this;
    m_aHardwareDirectionalLights[3] = nullptr;
    m_pPreviousLightSet = nullptr;
    m_pAmbientLight = nullptr;
    m_aHardwareDirectionalLights[0] = nullptr;
    m_aHardwareDirectionalLights[1] = nullptr;
    m_aHardwareDirectionalLights[2] = nullptr;
}

// 0x0009deb8 CLightManager_Destructor: the four vectors' blocks freed (Destroy has normally done it), last
// declared first; the light-set vector's fields are left.
CLightManager::~CLightManager() {
    if (m_vUnk3c.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk3c.m_pBlock);
    m_vUnk3c.m_pBlock = nullptr;
    m_vUnk3c.m_ui32NbUsedElt = 0;
    if (m_vUnk30.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk30.m_pBlock);
    m_vUnk30.m_pBlock = nullptr;
    m_vUnk30.m_ui32NbUsedElt = 0;
    if (m_vUnk24.m_pBlock != nullptr) Mem_FreeAligned16(m_vUnk24.m_pBlock);
    m_vUnk24.m_ui32NbUsedElt = 0;
    m_vUnk24.m_pBlock = nullptr;
    if (m_vLightSets.m_pBlock != nullptr) Mem_FreeAligned16(m_vLightSets.m_pBlock);
}

// 0x0009c068 CLightManager_Destroy: the light-set list and the three other lists freed.
void CLightManager::Destroy() {
    IRendableObject::Destroy();  // 0xa7248
    if (m_vLightSets.m_pBlock != nullptr) Mem_FreeAligned16(m_vLightSets.m_pBlock);
    m_vLightSets.m_ui32NbUsedElt = 0;
    m_vLightSets.m_pBlock = nullptr;
    if (m_vUnk30.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnk30.m_pBlock);
        m_vUnk30.m_pBlock = nullptr;
    }
    m_vUnk30.m_ui32NbUsedElt = 0;
    m_vUnk30.m_pBlock = nullptr;
    if (m_vUnk3c.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnk3c.m_pBlock);
        m_vUnk3c.m_pBlock = nullptr;
    }
    m_vUnk3c.m_ui32NbUsedElt = 0;
    m_vUnk3c.m_pBlock = nullptr;
    if (m_vUnk24.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnk24.m_pBlock);
        m_vUnk24.m_pBlock = nullptr;
    }
    m_vUnk24.m_ui32NbUsedElt = 0;
    m_vUnk24.m_pBlock = nullptr;
}

// 0x0009c988 CLightManager_Load
int32_t CLightManager::Load(IKFile* file, int32_t type) {
    IRendableObject::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count != 0) {
        if (m_vLightSets.m_pBlock == nullptr) {
            m_vLightSets.m_ui32NbElt = count;
            m_vLightSets.m_pBlock =
                static_cast<CLightSet**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(CLightSet*))));
        }
        if (m_vLightSets.m_ui32NbElt < count) {  // grows in steps of 2
            uint32_t capacity = (count & ~1u) + 2;
            if (capacity == 0) capacity = 2;
            m_vLightSets.m_pBlock = static_cast<CLightSet**>(Mem_ReallocAligned16(
                m_vLightSets.m_pBlock, capacity * static_cast<uint32_t>(sizeof(CLightSet*))));
            m_vLightSets.m_ui32NbElt = capacity;
        }
        m_vLightSets.m_ui32NbUsedElt = count;
        IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_vLightSets.m_pBlock), count);
    }
    count = 0;
    ReadU32LE(file, &count);
    if (count == 0) return 1;
    m_vUnk24.m_ui32NbElt = count;
    m_vUnk24.m_pBlock =
        static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    if (m_vUnk24.m_ui32NbElt < count) {  // as in the original: cannot happen right after the assignment
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_vUnk24.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(m_vUnk24.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        m_vUnk24.m_ui32NbElt = capacity;
    }
    m_vUnk24.m_ui32NbUsedElt = count;
    IKFile_ReadObjectRefArray(file, m_vUnk24.m_pBlock, count);
    // Both reserved with count entries (the original keeps the count == 0 case: capacity 1).
    m_vUnk30.m_ui32NbElt = count == 0 ? 1 : count;
    m_vUnk30.m_pBlock =
        static_cast<IKSerializable**>(Mem_AllocAligned16(m_vUnk30.m_ui32NbElt * static_cast<uint32_t>(sizeof(IKSerializable*))));
    m_vUnk3c.m_ui32NbElt = count == 0 ? 1 : count;
    m_vUnk3c.m_pBlock =
        static_cast<IKSerializable**>(Mem_AllocAligned16(m_vUnk3c.m_ui32NbElt * static_cast<uint32_t>(sizeof(IKSerializable*))));
    return 1;
}

// 0x0009b770 CLightSet_Create, in the original's store order.
CLightSet::CLightSet() {
    m_afAccumulatedLightRatio.m_pBlock = nullptr;
    m_afAccumulatedLightRatio.m_ui32NbElt = 10;
    m_afAccumulatedLightRatio.m_ui32NbUsedElt = 0;
    m_avpAccumulatedLight.m_ui32NbElt = 10;
    m_avpAccumulatedLight.m_pBlock = nullptr;
    m_avpAccumulatedLight.m_ui32NbUsedElt = 0;
    m_pFollowedLeaf = nullptr;
    m_unk74 = -1;
}

// 0x0009b7e0 CLightSet_InitLightLists_maybe (XXL2 CLightSet::InitializeData). Both outer lists get 10
// lists of 10 entries; the lists past 10 (none: the constructor leaves them empty) are freed.
void CLightSet::InitializeData() {
    typedef TVector<float, 10> RatioList;
    typedef TVector<IKSerializable*, 10> LightList;
    m_afAccumulatedLightRatio.m_ui32NbElt = 10;
    m_afAccumulatedLightRatio.m_pBlock =
        static_cast<RatioList*>(Mem_AllocAligned16(10 * static_cast<uint32_t>(sizeof(RatioList))));
    m_avpAccumulatedLight.m_ui32NbElt = 10;
    m_avpAccumulatedLight.m_pBlock =
        static_cast<LightList*>(Mem_AllocAligned16(10 * static_cast<uint32_t>(sizeof(LightList))));

    if (m_afAccumulatedLightRatio.m_ui32NbElt < 10) {  // as in the original: cannot happen
        m_afAccumulatedLightRatio.m_pBlock = static_cast<RatioList*>(
            Mem_ReallocAligned16(m_afAccumulatedLightRatio.m_pBlock, 20 * static_cast<uint32_t>(sizeof(RatioList))));
        m_afAccumulatedLightRatio.m_ui32NbElt = 20;
    }
    for (uint32_t i = m_afAccumulatedLightRatio.m_ui32NbUsedElt; i < 10; ++i) {
        RatioList& list = m_afAccumulatedLightRatio.m_pBlock[i];
        list.m_ui32NbElt = 10;
        list.m_pBlock = nullptr;
        list.m_ui32NbUsedElt = 0;
    }
    for (uint32_t i = 10; i < m_afAccumulatedLightRatio.m_ui32NbUsedElt; ++i) {
        RatioList& list = m_afAccumulatedLightRatio.m_pBlock[i];
        if (list.m_pBlock != nullptr) Mem_FreeAligned16(list.m_pBlock);
        list.m_ui32NbUsedElt = 0;
        list.m_pBlock = nullptr;
    }
    m_afAccumulatedLightRatio.m_ui32NbUsedElt = 10;

    if (m_avpAccumulatedLight.m_ui32NbElt < 10) {  // as in the original: cannot happen
        m_avpAccumulatedLight.m_pBlock = static_cast<LightList*>(
            Mem_ReallocAligned16(m_avpAccumulatedLight.m_pBlock, 20 * static_cast<uint32_t>(sizeof(LightList))));
        m_avpAccumulatedLight.m_ui32NbElt = 20;
    }
    for (uint32_t i = m_avpAccumulatedLight.m_ui32NbUsedElt; i < 10; ++i) {
        LightList& list = m_avpAccumulatedLight.m_pBlock[i];
        list.m_ui32NbElt = 10;
        list.m_pBlock = nullptr;
        list.m_ui32NbUsedElt = 0;
    }
    for (uint32_t i = 10; i < m_avpAccumulatedLight.m_ui32NbUsedElt; ++i) {
        LightList& list = m_avpAccumulatedLight.m_pBlock[i];
        if (list.m_pBlock != nullptr) Mem_FreeAligned16(list.m_pBlock);
        list.m_ui32NbUsedElt = 0;
        list.m_pBlock = nullptr;
    }
    m_avpAccumulatedLight.m_ui32NbUsedElt = 10;

    for (uint32_t i = 0; i < 10; ++i) {
        RatioList& ratios = m_afAccumulatedLightRatio.m_pBlock[i];
        ratios.m_ui32NbElt = 10;
        ratios.m_pBlock = static_cast<float*>(Mem_AllocAligned16(10 * static_cast<uint32_t>(sizeof(float))));
        LightList& lights = m_avpAccumulatedLight.m_pBlock[i];
        lights.m_ui32NbElt = 10;
        lights.m_pBlock =
            static_cast<IKSerializable**>(Mem_AllocAligned16(10 * static_cast<uint32_t>(sizeof(IKSerializable*))));
    }
    m_i32MaxOcclusionLevel[1] = -1;
    m_i32MaxOcclusionLevel[0] = -1;
}

// 0x0009cd28 CLightSet_Load. After the lists are built it resets the five light components' colour and
// direction (BUG(original)?: a null component reference would crash; LVL000 has none).
int32_t CLightSet::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk78);
    ReadU32LE(file, &m_baProperties);
    ReadF32ArrayLE(file, reinterpret_cast<float*>(&m_xLocalInfluenceBox), 6);  // one 0x18-byte read
    IKFile_ReadRef(file, &m_pFollowedLeaf);
    ReadS32LE(file, &m_unk74);
    IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_apLightComponent), 5);
    InitializeData();
    for (CLightComponent* component : m_apLightComponent) {
        std::memcpy(component->m_cLightColor, kColorBlack, 4);
        component->m_v3Dir = kVectorZero;
    }
    for (uint32_t i = 0; i < 10; ++i) {
        m_afAccumulatedLightRatio.m_pBlock[i].m_ui32NbUsedElt = 0;
        m_avpAccumulatedLight.m_pBlock[i].m_ui32NbUsedElt = 0;
    }
    return 1;
}

// ==== C2.4 step 6: the light rig, the zones' light accumulation and the point lights ====================================

namespace {
// The sector the level is in (engine +0x90 -> +0x18).
int32_t CurrentSector() { return g_pEngine->m_level->m_currentSector; }

// Math_Sqrtf 0x10690: the double square root rounded to float, as a double.
double MathSqrtf(double x) { return static_cast<double>(static_cast<float>(std::sqrt(x))); }

// A colour byte as the rig stores it: the compiler used `(float)b * 0.003921569f` (float form) in some places and
// `(float)((double)b * 0.003921568859368563)` (double form) in others of ApplyLightingZone; the two can differ in the last bit.
float UnitF(uint32_t b) { return static_cast<float>(b) * 0.003921569f; }
float UnitD(uint32_t b) { return static_cast<float>(static_cast<double>(b) * 0.003921568859368563); }

enum ColorForm { kFloatForm, kMixedForm, kDoubleForm };

// The colour of a rig light: the grey flag (private flags: 1 when red = green = blue) and the four floats at +0x18. kMixedForm:
// red in double form, the rest in float form (the first two lights of the zone branch).
void SetRigColor(RpLight* light, const uint8_t rgba[4], ColorForm form) {
    light->object.privateFlags = (rgba[1] == rgba[0] && rgba[2] == rgba[1]) ? 1 : 0;
    for (int i = 0; i < 4; ++i) {
        const bool doubleForm = form == kDoubleForm || (form == kMixedForm && i == 0);
        light->color[i] = doubleForm ? UnitD(rgba[i]) : UnitF(rgba[i]);
    }
}

// The direction of a rig light: the `at` axis of its frame's LTM (+0x70).
void SetRigDirection(RpLight* light, const CVector3& direction) {
    RwFrame* frame = RpLightGetFrame(light);
    frame->ltm.at.x = direction.x;
    frame->ltm.at.y = direction.y;
    frame->ltm.at.z = direction.z;
}

// The renderer's world (renderer +0x34, RpWorld.h), the one the rig's lights are added to.
RpWorld* RendererWorld() { return g_pEngine->m_graphic->m_renderer->m_pWorld; }
void RemoveFromWorld(RpLight* light) {
    if (RpLightGetWorld(light) != nullptr) RpWorldRemoveLight(RendererWorld(), light);
}
void AddToWorld(RpLight* light) {
    if (RpLightGetWorld(light) == nullptr) RpWorldAddLight(RendererWorld(), light);
}
bool IsBlack(const uint8_t rgba[4]) { return std::memcmp(rgba, kColorBlack, 4) == 0; }

// 0x0023dd68 RGBA8_ScaleClamped: each byte times `scale`, clamped to 0..255 (a negative scale clamps the other way round: the
// products are taken as shorts and anything below 1 is 0).
void RGBA8_ScaleClamped(double scale, uint8_t* rgba) {
    for (int i = 0; i < 4; ++i) {
        const int16_t product = static_cast<int16_t>(ppc::fctiwz(scale * static_cast<double>(rgba[i])));
        if (scale < 0.0) {
            rgba[i] = product < 1 ? 0 : static_cast<uint8_t>(product);
        } else {
            rgba[i] = product < 0xff ? static_cast<uint8_t>(product) : 0xff;
        }
    }
}

// 0x0023e2f8 RGBA_AddScaledSaturate: dst += scale * src per byte, saturating at 255 (0 for a negative scale).
void RGBA_AddScaledSaturate(double scale, uint8_t* dst, const uint8_t* src) {
    for (int i = 0; i < 4; ++i) {
        const int16_t product = static_cast<int16_t>(ppc::fctiwz(scale * static_cast<double>(src[i])));
        if (scale < 0.0) {
            dst[i] = product < static_cast<int16_t>(dst[i]) ? static_cast<uint8_t>(dst[i] + static_cast<uint8_t>(product)) : 0;
        } else {
            dst[i] = static_cast<int32_t>(product) < 0xff - static_cast<int32_t>(dst[i]) ? static_cast<uint8_t>(dst[i] + static_cast<uint8_t>(product)) : 0xff;
        }
    }
}

// The red byte of a rig light as LightRig_GetNextDistinctLight packs it: (int)(float * 255.0), the low byte.
uint32_t PackedByte(float channel) { return static_cast<uint32_t>(ppc::fctiwz(static_cast<double>(channel) * 255.0)) & 0xff; }
uint32_t PackedColor(const RpLight* light) {
    return (PackedByte(light->color[0]) << 24) | (PackedByte(light->color[1]) << 16) | (PackedByte(light->color[2]) << 8) | PackedByte(light->color[3]);
}
}  // namespace

// 0x0009a5f0 Renderer_CreateWorldLights_maybe: an ambient light and four directional lights (each on a frame of its own), every
// one black and in the world.
void CLightManager::CreateWorldLights() {
    auto blacken = [](RpLight* light, ColorForm form) {
        RpWorldAddLight(RendererWorld(), light);
        light->object.flags = 1;  // rpLIGHTLIGHTATOMICS
        SetRigColor(light, kColorBlack, form);
    };
    m_pAmbientLight = RpLightCreate(rpLIGHTAMBIENT);
    blacken(m_pAmbientLight, kFloatForm);
    for (RpLight*& light : m_aHardwareDirectionalLights) {
        light = RpLightCreate(rpLIGHTDIRECTIONAL);
        blacken(light, kDoubleForm);
        RpLightSetFrame(light, RwFrameCreate());
    }
}

// 0x0009b3a8 CLightManager_DestroyRwLights_maybe
void CLightManager::DestroyRwLights() {
    if (m_pAmbientLight != nullptr) {
        RpWorldRemoveLight(RendererWorld(), m_pAmbientLight);
        RpLightDestroy(m_pAmbientLight);
        m_pAmbientLight = nullptr;
    }
    for (RpLight*& light : m_aHardwareDirectionalLights) {
        if (light == nullptr) continue;
        RemoveFromWorld(light);
        RwFrame* frame = RpLightGetFrame(light);
        RpLightSetFrame(light, nullptr);
        RpLightDestroy(light);
        RwFrameDestroy(frame);
        light = nullptr;
    }
}

// 0x000994e8 ApplyLightingZone. The sector test comes first: a zone of another sector leaves the rig as it is (the zone is
// still remembered). BUG(original)?: with `flat` set the directional lights leave the world but keep the colours of the zone
// applied before, so ComputeLightCount still counts them.
void CLightManager::ApplyLightingZone(const CLightSet* zone, uint8_t flat) {
    if (zone == nullptr) {
        SetRigColor(m_pAmbientLight, kColorBlack, kFloatForm);
        for (int i = 0; i < 4; ++i) {
            RpLight* light = m_aHardwareDirectionalLights[i];
            SetRigColor(light, kColorBlack, i == 0 ? kFloatForm : kDoubleForm);
            SetRigDirection(light, kAxisY);
            RemoveFromWorld(light);
        }
        m_ui8PreviousFlat = flat;
        m_pPreviousLightSet = zone;
        return;
    }
    if (zone->m_unk78 != 0 && static_cast<uint32_t>(CurrentSector()) != zone->m_unk78) {
        m_ui8PreviousFlat = flat;
        m_pPreviousLightSet = zone;
        return;
    }
    if (flat == 0) {
        SetRigColor(m_pAmbientLight, zone->m_apLightComponent[0]->m_cLightColor, kMixedForm);
        for (int i = 0; i < 4; ++i) {
            const CLightComponent* component = zone->m_apLightComponent[i + 1];
            RpLight* light = m_aHardwareDirectionalLights[i];
            SetRigColor(light, component->m_cLightColor, i < 1 ? kMixedForm : kDoubleForm);
            SetRigDirection(light, component->m_v3Dir);
            if (IsBlack(component->m_cLightColor)) {
                RemoveFromWorld(light);
            } else {
                AddToWorld(light);
            }
        }
    } else {
        // One ambient colour: the mean of the components that are not black, the directional lights out of the world.
        float sum[4] = {0.0f, 0.0f, 0.0f, 0.0f};  // red, green, blue, alpha
        int64_t used = 0;
        for (int i = 0; i < 5; ++i) {
            const uint8_t* rgba = zone->m_apLightComponent[i]->m_cLightColor;
            if (IsBlack(rgba)) continue;
            ++used;
            for (int c = 0; c < 4; ++c) sum[c] += static_cast<float>(rgba[c]);
        }
        const float count = static_cast<float>(used);
        uint8_t mean[4];
        for (int c = 0; c < 4; ++c) {
            // (int)(sum / count) & 0xff: 0 / 0 is NaN, which the PPC conversion turns into the lowest int.
            mean[c] = static_cast<uint8_t>(static_cast<uint32_t>(ppc::fctiwz(static_cast<double>(sum[c] / count))) & 0xff);
        }
        m_pAmbientLight->object.privateFlags = (mean[0] == mean[1] && mean[2] == mean[1]) ? 1 : 0;
        for (int c = 0; c < 4; ++c) m_pAmbientLight->color[c] = static_cast<float>(mean[c]) * 0.003921569f;
        for (RpLight* light : m_aHardwareDirectionalLights) RemoveFromWorld(light);
    }
    m_ui8PreviousFlat = flat;
    m_pPreviousLightSet = zone;
}

// 0x0009b208 CLightManager_ComputeLightCount_maybe: for each of the four directional lights the vector (red, green, blue,
// 1 - alpha) is compared with 1/255 per lane and the lanes that reach it are summed (vsumsws of the compare masks, each -1);
// the AltiVec code then ANDs that sum with 1 before adding the four lights up, so a light counts when an odd number of its lanes
// reach 1/255 (a light with exactly two non-black colour channels does not count).
uint32_t CLightManager::ComputeLightCount() const {
    constexpr float kThreshold = 0.003921568859368563f;  // 0x3b808081
    uint32_t total = 0;
    for (const RpLight* light : m_aHardwareDirectionalLights) {
        int32_t lanes = 0;
        for (int c = 0; c < 3; ++c) lanes -= light->color[c] >= kThreshold ? 1 : 0;
        lanes -= (1.0f - light->color[3]) >= kThreshold ? 1 : 0;
        total += static_cast<uint32_t>(lanes) & 1u;
    }
    return total;
}

// 0x0009ae28 LightRig_GetNextDistinctLight_maybe. The caller stores the returned index back and asks again.
uint32_t CLightManager::GetNextDistinctLight(uint32_t index, CVector3* direction, uint32_t* color) const {
    if (index > 3) return 4;
    constexpr uint32_t kBlackPacked = 0x000000ff;  // 0x00c50df8 read as a word
    uint32_t packed = PackedColor(m_aHardwareDirectionalLights[index]);
    if (packed == kBlackPacked) {
        for (;;) {
            ++index;
            if (index == 4) return 4;
            packed = PackedColor(m_aHardwareDirectionalLights[index]);
            if (packed != kBlackPacked) break;
        }
    }
    *color = packed;
    const RwFrame* frame = RpLightGetFrame(m_aHardwareDirectionalLights[index]);
    direction->x = frame->ltm.at.x;
    direction->y = frame->ltm.at.y;
    direction->z = frame->ltm.at.z;
    return index + 1;
}

// The rig's ambient colour (ShaderPassState_FillAmbientColorUniform_maybe 0xf52f0 reads +0x18 .. +0x24).
const float* CLightManager::GetAmbientColor() const { return m_pAmbientLight->color; }

// 0x0009b0d8 CLightManager_CanBeUpdated
int32_t CLightManager::CanBeUpdated() { return static_cast<int32_t>(((g_pEngine->m_graphic->m_renderer->m_bitProperties ^ 2) >> 1) & 1); }

// 0x0009afe0 CLightManager_PreUpdate
void CLightManager::PreUpdate(IKTime* /*frameClock*/) {
    ApplyLightingZone(nullptr, 0);
    for (uint32_t i = 0; i < m_vLightSets.m_ui32NbUsedElt; ++i) m_vLightSets.m_pBlock[i]->UpdateWorldBounds();
}

// 0x0009d1a0 CLightManager_UpdateAndExtract
void CLightManager::UpdateAndExtract(float maxDistanceSquared, RenderQueue** stages, IKTime* frameClock, RwCamera* camera,
                                     int32_t distanceCull) {
    for (uint32_t i = 0; i < m_vLightSets.m_ui32NbUsedElt; ++i) {
        CLightSet* set = m_vLightSets.m_pBlock[i];
        for (CLightComponent* component : set->m_apLightComponent) {
            std::memcpy(component->m_cLightColor, kColorBlack, 4);
            component->m_v3Dir = kVectorZero;
        }
        if (set->m_unk78 == 0 || CurrentSector() == static_cast<int32_t>(set->m_unk78)) {
            if (set->m_i32MaxOcclusionLevel[0] != -1) set->AccumulateLights(static_cast<uint32_t>(set->m_i32MaxOcclusionLevel[0]), 0);
            if (set->m_i32MaxOcclusionLevel[1] != -1) set->AccumulateLights(static_cast<uint32_t>(set->m_i32MaxOcclusionLevel[1]), 1);
            // Each direction normalised; a null one becomes the Y axis.
            for (CLightComponent* component : set->m_apLightComponent) {
                float* d = &component->m_v3Dir.x;
                const double length = MathSqrtf(static_cast<double>(ppc::fmadds(d[2], d[2], ppc::fmadds(d[0], d[0], d[1] * d[1]))));
                if (length == 0.0) {
                    component->m_v3Dir = kAxisY;
                } else {
                    const float inverse = 1.0f / static_cast<float>(length);
                    d[2] = inverse * d[2];
                    d[0] = inverse * d[0];
                    d[1] = inverse * d[1];
                }
            }
        }
        set->m_i32MaxOcclusionLevel[1] = -1;
        set->m_i32MaxOcclusionLevel[0] = -1;
    }
    GatherPointLightsNearFocus();
    for (uint32_t i = 0; i < m_vUnk24.m_ui32NbUsedElt; ++i) {
        CSGPointLight* light = static_cast<CSGPointLight*>(m_vUnk24.m_pBlock[i]);
        if (light != nullptr) light->UpdateAndExtract(maxDistanceSquared, stages, frameClock, camera, distanceCull);
    }
}

namespace {
// The camera's world position (CKSrvCamera +0x598) and the light node's frame position (LTM).
CKSrvCamera* SrvCamera() { return static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera); }
const RwV3d& LightPosition(const CSGPointLight* light) { return RwFrameGetLTM(light->m_pRwFrame)->pos; }
float LightRadius(const CSGPointLight* light) { return static_cast<const CLightComponent*>(light->m_pLight)->m_fRadius; }

// 0x0009c540 CompareNodesByCameraDistance_maybe: nearer (distance minus radius) first.
int CompareLightsByCameraDistance(const void* a, const void* b) {
    const CSGPointLight* first = *static_cast<const CSGPointLight* const*>(a);
    const CSGPointLight* second = *static_cast<const CSGPointLight* const*>(b);
    const CVector3& camera = SrvCamera()->m_v3RealPos;
    auto distance = [&camera](const CSGPointLight* light) {
        const RwV3d& p = LightPosition(light);
        const float dy = camera.y - p.y, dx = camera.x - p.x, dz = camera.z - p.z;
        return MathSqrtf(static_cast<double>(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy))));
    };
    const double d1 = distance(first), d2 = distance(second);
    const bool secondNotFarther = static_cast<float>(d2 - static_cast<double>(LightRadius(second))) <= static_cast<float>(d1 - static_cast<double>(LightRadius(first)));
    return (secondNotFarther ? 2 : 0) - 1;
}

void PushBack(TVector<IKSerializable*, 1>* list, IKSerializable* entry) {
    if (list->m_ui32NbElt == list->m_ui32NbUsedElt) {
        const uint32_t capacity = list->m_ui32NbUsedElt + 1;
        list->m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(list->m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        list->m_ui32NbElt = capacity;
    }
    list->m_pBlock[list->m_ui32NbUsedElt++] = entry;
}
}  // namespace

// 0x0009c308 CLightManager_GatherPointLightsNearFocus_maybe
void CLightManager::GatherPointLightsNearFocus() {
    m_vUnk30.m_ui32NbUsedElt = 0;
    CKSrvCamera* camera = SrvCamera();
    const double cameraX = camera->m_v3RealPos.x, cameraY = camera->m_v3RealPos.y, cameraZ = camera->m_v3RealPos.z;
    for (uint32_t i = 0; i < m_vUnk24.m_ui32NbUsedElt; ++i) {
        CSGPointLight* light = static_cast<CSGPointLight*>(m_vUnk24.m_pBlock[i]);
        if (light == nullptr || light->m_unk18 == 0) continue;
        const RwV3d& p = LightPosition(light);
        const float radius = LightRadius(light);
        const float sphere[5] = {p.x, p.y, p.z, radius, radius * radius};
        if (camera->TestSphereAgainstFrustum(sphere, 5) == 0) continue;
        const float dy = static_cast<float>(cameraY - static_cast<double>(p.y));
        const float dx = static_cast<float>(cameraX - static_cast<double>(p.x));
        const float dz = static_cast<float>(cameraZ - static_cast<double>(p.z));
        const double distance = MathSqrtf(static_cast<double>(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy))));
        if (static_cast<float>(distance - static_cast<double>(radius)) <= 50.0) PushBack(&m_vUnk30, light);
    }
    if (m_vUnk30.m_ui32NbUsedElt > 1) Ps3Qsort(m_vUnk30.m_pBlock, m_vUnk30.m_ui32NbUsedElt, sizeof(IKSerializable*), CompareLightsByCameraDistance);
}

// 0x0009c150 CLightManager_GatherLightsTouchingSphere_maybe
uint32_t CLightManager::GatherLightsTouchingSphere(const float sphere[4]) {
    m_vUnk3c.m_ui32NbUsedElt = 0;
    uint32_t touching = 0;
    for (uint32_t i = 0; i < m_vUnk30.m_ui32NbUsedElt; ++i) {
        CSGPointLight* light = static_cast<CSGPointLight*>(m_vUnk30.m_pBlock[i]);
        const RwV3d& p = LightPosition(light);
        const float dy = sphere[1] - p.y;
        const float dx = sphere[0] - p.x;
        const float dz = sphere[2] - p.z;
        const double distance = MathSqrtf(static_cast<double>(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy))));
        if (distance <= static_cast<double>(LightRadius(light) + sphere[3])) {
            ++touching;
            PushBack(&m_vUnk3c, light);
        }
    }
    return touching;
}

// 0x0009b068 CLightManager_GetLightPosition_maybe
void CLightManager::GetLightPosition(CVector3* position, int32_t index) const {
    if (index < static_cast<int32_t>(m_vUnk3c.m_ui32NbUsedElt)) {
        const RwV3d& p = LightPosition(static_cast<const CSGPointLight*>(m_vUnk3c.m_pBlock[index]));
        position->x = p.x;
        position->y = p.y;
        position->z = p.z;
    } else {
        *position = kVectorZero;
    }
}

// 0x0009ad60 CLightManager_GetLightColor_maybe: the light component's colour bytes (red first), black without a light.
void CLightManager::GetLightColor(uint8_t color[4], int32_t index) const {
    if (index < static_cast<int32_t>(m_vUnk3c.m_ui32NbUsedElt)) {
        std::memcpy(color, static_cast<const CLightComponent*>(static_cast<const CSGPointLight*>(m_vUnk3c.m_pBlock[index])->m_pLight)->m_cLightColor, 4);
    } else {
        std::memset(color, 0, 4);
    }
}

// 0x0009adf0 CLightManager_GetLightRadius_maybe
float CLightManager::GetLightRadius(int32_t index) const {
    if (index >= static_cast<int32_t>(m_vUnk3c.m_ui32NbUsedElt)) return 0.0f;
    return LightRadius(static_cast<const CSGPointLight*>(m_vUnk3c.m_pBlock[index]));
}

// 0x0009ad30 CLightManager_GetLightField1C_maybe: the point light node's +0x1c.
float CLightManager::GetLightField1C(int32_t index) const {
    if (index >= static_cast<int32_t>(m_vUnk3c.m_ui32NbUsedElt)) return 0.0f;
    return static_cast<const CSGPointLight*>(m_vUnk3c.m_pBlock[index])->m_unk1c;
}

// ---- the zones ------------------------------------------------------------------------------------------------------

// 0x00098f18 LightZone_UpdateWorldBounds_maybe
void CLightSet::UpdateWorldBounds() {
    const uint32_t kind = m_baProperties & 3;
    bool followed = false;
    if (kind == 2) {
        CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pFollowedLeaf);
        if (leaf != nullptr && (m_unk78 == 0 || CurrentSector() == static_cast<int32_t>(m_unk78))) {
            const RwMatrix* ltm = RwFrameGetLTM(leaf->m_pRwFrame);
            RwV3d offset;
            if (m_unk74 != -1) {
                // The bone's position through the leaf's LTM: the translation row of the bone's matrix in the animated node's
                // hierarchy (the hierarchy's matrix array: posed every frame by the node's update, which the lights' PreUpdate
                // precedes: last frame's pose, as in the original).
                const RpHAnimHierarchy* hierarchy = static_cast<CAnimatedNode*>(m_pFollowedLeaf)->m_pRpHAnimHierarchy;
                RwV3dTransformPoints(&offset, &hierarchy->pMatrixArray[m_unk74].pos, 1, ltm);
            } else {
                offset = ltm->pos;
            }
            m_xWorldInfluenceBox.m_inf = {m_xLocalInfluenceBox.m_inf.x + offset.x, m_xLocalInfluenceBox.m_inf.y + offset.y, m_xLocalInfluenceBox.m_inf.z + offset.z};
            m_xWorldInfluenceBox.m_sup = {m_xLocalInfluenceBox.m_sup.x + offset.x, m_xLocalInfluenceBox.m_sup.y + offset.y, m_xLocalInfluenceBox.m_sup.z + offset.z};
            followed = true;
        }
    } else if (kind == 3) {
        const CameraContext* context = g_pEngine->m_graphic->m_renderer->m_cameraContext;
        const RwFrame* frame = static_cast<const CSGMovable*>(context->m_pCamera)->m_pRwFrame;
        const RwV3d& offset = frame->modelling.pos;
        m_xWorldInfluenceBox.m_inf = {m_xLocalInfluenceBox.m_inf.x + offset.x, m_xLocalInfluenceBox.m_inf.y + offset.y, m_xLocalInfluenceBox.m_inf.z + offset.z};
        m_xWorldInfluenceBox.m_sup = {m_xLocalInfluenceBox.m_sup.x + offset.x, m_xLocalInfluenceBox.m_sup.y + offset.y, m_xLocalInfluenceBox.m_sup.z + offset.z};
        followed = true;
    }
    if (!followed) m_xWorldInfluenceBox = m_xLocalInfluenceBox;
    m_fWorldInfluenceBoxVolume = (m_xWorldInfluenceBox.m_sup.x - m_xWorldInfluenceBox.m_inf.x) * (m_xWorldInfluenceBox.m_sup.y - m_xWorldInfluenceBox.m_inf.y) *
                                 (m_xWorldInfluenceBox.m_sup.z - m_xWorldInfluenceBox.m_inf.z);
    for (uint32_t i = 0; i < 10; ++i) {  // the accumulation lists of the first ten occlusion levels emptied
        m_afAccumulatedLightRatio.m_pBlock[i].m_ui32NbUsedElt = 0;
        m_avpAccumulatedLight.m_pBlock[i].m_ui32NbUsedElt = 0;
    }
}

// 0x0009ba90 CLightSet_GrowZoneArrays_maybe: empty lists (10 entries reserved) appended to both arrays until `level` exists.
void CLightSet::GrowZoneArrays(uint32_t level) {
    typedef TVector<float, 10> RatioList;
    typedef TVector<IKSerializable*, 10> LightList;
    if (level < m_afAccumulatedLightRatio.m_ui32NbUsedElt) return;
    const uint32_t wanted = level - m_afAccumulatedLightRatio.m_ui32NbUsedElt + 1;
    for (uint32_t n = 0; n < wanted; ++n) {
        if (m_avpAccumulatedLight.m_ui32NbElt == m_avpAccumulatedLight.m_ui32NbUsedElt) {
            const uint32_t capacity = m_avpAccumulatedLight.m_ui32NbUsedElt + 10;
            m_avpAccumulatedLight.m_pBlock = static_cast<LightList*>(Mem_ReallocAligned16(m_avpAccumulatedLight.m_pBlock, capacity * static_cast<uint32_t>(sizeof(LightList))));
            m_avpAccumulatedLight.m_ui32NbElt = capacity;
        }
        LightList& lights = m_avpAccumulatedLight.m_pBlock[m_avpAccumulatedLight.m_ui32NbUsedElt++];
        lights.m_ui32NbElt = 10;
        lights.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(10 * static_cast<uint32_t>(sizeof(IKSerializable*))));
        lights.m_ui32NbUsedElt = 0;
        if (m_afAccumulatedLightRatio.m_ui32NbElt == m_afAccumulatedLightRatio.m_ui32NbUsedElt) {
            const uint32_t capacity = m_afAccumulatedLightRatio.m_ui32NbUsedElt + 10;
            m_afAccumulatedLightRatio.m_pBlock = static_cast<RatioList*>(Mem_ReallocAligned16(m_afAccumulatedLightRatio.m_pBlock, capacity * static_cast<uint32_t>(sizeof(RatioList))));
            m_afAccumulatedLightRatio.m_ui32NbElt = capacity;
        }
        RatioList& ratios = m_afAccumulatedLightRatio.m_pBlock[m_afAccumulatedLightRatio.m_ui32NbUsedElt++];
        ratios.m_ui32NbElt = 10;
        ratios.m_pBlock = static_cast<float*>(Mem_AllocAligned16(10 * static_cast<uint32_t>(sizeof(float))));
        ratios.m_ui32NbUsedElt = 0;
    }
}

// 0x000981c8 LightZone_AccumulateLights_maybe (see the header). The temporaries are indexed by the slot (mode * 3 + the
// light's own component index).
void CLightSet::AccumulateLights(uint32_t level, uint32_t mode) {
    const uint32_t first = mode * 3;
    const uint32_t end = first + (mode == 0 ? 3u : 2u);
    const TVector<float, 10>& ratios = m_afAccumulatedLightRatio.m_pBlock[level];
    const TVector<IKSerializable*, 10>& lights = m_avpAccumulatedLight.m_pBlock[level];
    const uint32_t count = lights.m_ui32NbUsedElt;
    float maxRatio = 0.0f;
    for (uint32_t i = 0; i < count; ++i) {
        const CSGLight* light = static_cast<const CSGLight*>(lights.m_pBlock[i]);
        if (light->m_eLightBoxType == mode && maxRatio <= ratios.m_pBlock[i]) maxRatio = ratios.m_pBlock[i];
    }
    if (maxRatio != 1.0f) {
        if (level != 0) AccumulateLights(level - 1, mode);
        const float scale = 1.0f - maxRatio;
        for (uint32_t s = first; s < end; ++s) {
            CLightComponent* component = m_apLightComponent[s];
            RGBA8_ScaleClamped(static_cast<double>(scale), component->m_cLightColor);
            component->m_v3Dir.x = scale * component->m_v3Dir.x;
            component->m_v3Dir.y = scale * component->m_v3Dir.y;
            component->m_v3Dir.z = scale * component->m_v3Dir.z;
        }
    }
    float sumRatio[8] = {}, sumRed[8] = {}, sumGreen[8] = {}, sumBlue[8] = {};
    CVector3 sumDir[8] = {};
    for (uint32_t i = 0; i < count; ++i) {
        const CSGLight* light = static_cast<const CSGLight*>(lights.m_pBlock[i]);
        const float ratio = ratios.m_pBlock[i];
        if (light->m_eLightBoxType != mode || light->m_ui32NbActiveLights == 0) continue;
        for (uint32_t j = 0; j < light->m_ui32NbActiveLights && first + j < 8; ++j) {
            const CLightComponent* component = static_cast<const CLightComponent*>(light->m_aplightParameters[j]);
            const uint32_t slot = first + j;
            sumRatio[slot] = ratio + sumRatio[slot];
            if ((component->m_baProperties & 0x10) != 0) {
                const float weight = (ratio * static_cast<float>(component->m_cLightColor[3])) / 255.0f;
                sumRed[slot] = ppc::fmadds(weight, static_cast<float>(component->m_cLightColor[0]), sumRed[slot]);
                sumGreen[slot] = ppc::fmadds(weight, static_cast<float>(component->m_cLightColor[1]), sumGreen[slot]);
                sumBlue[slot] = ppc::fmadds(weight, static_cast<float>(component->m_cLightColor[2]), sumBlue[slot]);
            }
            sumDir[slot].x = ppc::fmadds(ratio, component->m_v3Dir.x, sumDir[slot].x);
            sumDir[slot].y = ppc::fmadds(ratio, component->m_v3Dir.y, sumDir[slot].y);
            sumDir[slot].z = ppc::fmadds(ratio, component->m_v3Dir.z, sumDir[slot].z);
        }
    }
    for (uint32_t s = first; s < end; ++s) {
        const float inverse = sumRatio[s] != 0.0f ? 1.0f / sumRatio[s] : 0.0f;
        sumRed[s] = inverse * sumRed[s];
        sumGreen[s] = inverse * sumGreen[s];
        sumBlue[s] = inverse * sumBlue[s];
        sumDir[s].x = inverse * sumDir[s].x;
        sumDir[s].y = inverse * sumDir[s].y;
        sumDir[s].z = inverse * sumDir[s].z;
    }
    for (uint32_t s = first; s < end; ++s) {
        CLightComponent* component = m_apLightComponent[s];
        const uint8_t rgba[4] = {static_cast<uint8_t>(ppc::fctiwz(static_cast<double>(sumRed[s]))), static_cast<uint8_t>(ppc::fctiwz(static_cast<double>(sumGreen[s]))),
                                 static_cast<uint8_t>(ppc::fctiwz(static_cast<double>(sumBlue[s]))), 0xff};
        RGBA_AddScaledSaturate(static_cast<double>(maxRatio), component->m_cLightColor, rgba);
        component->m_v3Dir.x = ppc::fmadds(maxRatio, sumDir[s].x, component->m_v3Dir.x);
        component->m_v3Dir.y = ppc::fmadds(maxRatio, sumDir[s].y, component->m_v3Dir.y);
        component->m_v3Dir.z = ppc::fmadds(maxRatio, sumDir[s].z, component->m_v3Dir.z);
    }
}

// ---- the scene-graph lights' share of the zones -------------------------------------------------------------------------

// 0x0009d8a8 CSGLight_ComputeZoneOverlapWeights_maybe: for each of the light's zones (of this sector) that its world box touches,
// the light and the fraction of the zone's volume it covers (1 for a zone of kind 0, or one inside the light's box) are put in
// the zone's lists of the light's occlusion level; the zone remembers the highest level of each box type.
void CSGLight::ComputeZoneOverlapWeights() {
    const CBBox& light = m_xWorldInfluenceBBox;
    for (uint32_t k = 0; k < m_ui32NbLightSets; ++k) {
        CLightSet* zone = static_cast<CLightSet*>(m_apLightSets[k]);
        if (zone->m_unk78 != 0 && CurrentSector() != static_cast<int32_t>(zone->m_unk78)) continue;
        float ratio;
        if ((zone->m_baProperties & 3) == 0) {
            ratio = 1.0f;
        } else {
            const CBBox& box = zone->m_xWorldInfluenceBox;
            if (light.m_sup.x < box.m_inf.x || box.m_sup.x < light.m_inf.x || light.m_sup.z < box.m_inf.z || box.m_sup.z < light.m_inf.z ||
                light.m_sup.y < box.m_inf.y || box.m_sup.y < light.m_inf.y) {
                continue;  // no overlap
            }
            // AABB_ContainsAABB(zone box, light box) 0x23c280: the zone lies inside the light's box.
            const bool zoneInside = AABB_ContainsAABB(&box, &light);
            if (zoneInside) {
                ratio = 1.0f;
            } else {
                auto axis = [](float lightMax, float lightMin, float zoneMax, float zoneMin) {
                    const float top = lightMax <= zoneMax ? zoneMax : lightMax;     // the larger maximum
                    const float bottom = lightMin <= zoneMin ? lightMin : zoneMin;  // the smaller minimum
                    return ((top - bottom) - std::fabs(lightMin - zoneMin)) - std::fabs(lightMax - zoneMax);
                };
                const float x = axis(light.m_sup.x, light.m_inf.x, box.m_sup.x, box.m_inf.x);
                const float y = axis(light.m_sup.y, light.m_inf.y, box.m_sup.y, box.m_inf.y);
                const float z = axis(light.m_sup.z, light.m_inf.z, box.m_sup.z, box.m_inf.z);
                ratio = ((x * y) * z) / zone->m_fWorldInfluenceBoxVolume;
            }
        }
        // The zone keeps the highest occlusion level per box type (the original indexes its +0x28 array at type - 2: +0x20 / +0x24).
        int32_t& highest = zone->m_i32MaxOcclusionLevel[m_eLightBoxType];
        if (highest < static_cast<int32_t>(m_ui32OcclusionLevel)) highest = static_cast<int32_t>(m_ui32OcclusionLevel);
        if (m_ui32OcclusionLevel >= zone->m_avpAccumulatedLight.m_ui32NbUsedElt) zone->GrowZoneArrays(m_ui32OcclusionLevel);
        auto& lights = zone->m_avpAccumulatedLight.m_pBlock[m_ui32OcclusionLevel];
        if (lights.m_ui32NbElt == lights.m_ui32NbUsedElt) {
            const uint32_t capacity = lights.m_ui32NbElt + 10;
            lights.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(lights.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
            lights.m_ui32NbElt = capacity;
        }
        lights.m_pBlock[lights.m_ui32NbUsedElt++] = this;
        auto& ratios = zone->m_afAccumulatedLightRatio.m_pBlock[m_ui32OcclusionLevel];
        if (ratios.m_ui32NbElt == ratios.m_ui32NbUsedElt) {
            const uint32_t capacity = ratios.m_ui32NbElt + 10;
            ratios.m_pBlock = static_cast<float*>(Mem_ReallocAligned16(ratios.m_pBlock, capacity * static_cast<uint32_t>(sizeof(float))));
            ratios.m_ui32NbElt = capacity;
        }
        ratios.m_pBlock[ratios.m_ui32NbUsedElt++] = ratio;
    }
}

// 0x0009b628 CLightSet_RecursiveRegistration (C2.8 save-menu)
#include "k2000/graphical/render/CLightSet.h"
#include "k2000/logic/CKSavingManager.h"
void CLightSet::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    for (CLightComponent* component : m_apLightComponent) component->RecursiveRegistration(0);
}

// 0x00097ef8 CLightManager_RecursiveRegistration
void CLightManager::RecursiveRegistration(int32_t type) {
    if (type != 0) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // vt+0x24
    const uint32_t count = m_vLightSets.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < count; ++i) m_vLightSets.m_pBlock[i]->RecursiveRegistration(0);
}

// 0x0009c8d8 CLightSet_PostLoad: the half extents (sup - inf) * 0.5 (TOC1 -0x62e4), each a fsubs then a fmuls.
int32_t CLightSet::PostLoad(int32_t /*type*/) {
    if ((m_baProperties & 3u) != 2u) {
        m_unk74 = -1;
        m_pFollowedLeaf = nullptr;
        return 1;
    }
    static const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
    CVector3 half;
    half.x = (m_xLocalInfluenceBox.m_sup.x - m_xLocalInfluenceBox.m_inf.x) * 0.5f;
    half.y = (m_xLocalInfluenceBox.m_sup.y - m_xLocalInfluenceBox.m_inf.y) * 0.5f;
    half.z = (m_xLocalInfluenceBox.m_sup.z - m_xLocalInfluenceBox.m_inf.z) * 0.5f;
    BBox_SetFromCenterExtents(&m_xLocalInfluenceBox, &kNullVector, &half);  // 0x0023d550
    return 1;
}
