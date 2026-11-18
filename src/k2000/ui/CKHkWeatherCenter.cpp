// CKHkWeatherCenter.cpp - reconstructed original translation unit 0x5acb48-0x5ae528 (GAME_TOC2, main_toc2), 29 functions, 23 live.
// Primary owner: CKHkWeatherCenter (not a registered class)
// Other owners: RegisterCKHkWeatherCenterClass (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5acb48  CKHkWeatherCenter_Destroy
//   [x] 0x5acb98  CKHkWeatherCenter_Construct  [dead]
//   [ ] 0x5acbe8  CKHkWeatherCenter_Construct_2  [dead]
//   [ ] 0x5acc38  RegisterCKHkWeatherCenterClass
//   [ ] 0x5accb0  _GLOBAL__I_5accb0
//   [x] 0x5accc0  CKHkWeatherCenter_ApplyPreset_maybe  (ApplyPreset)
//   [x] 0x5acf10  CKHkWeatherCenter_ClearReferences  (Destroy)
//   [x] 0x5acfb0  CKHkWeatherCenter_DestroyArray
//   [ ] 0x5ad050  CKHkWeatherCenter_PushPreset_maybe  [dead]
//   [ ] 0x5ad1e8  CKHkWeatherCenter_SetBasePresetByObject_maybe  [dead]
//   [ ] 0x5ad2b8  CKHkWeatherCenter_RemovePreset_maybe  [dead]
//   [x] 0x5ad440  CKHkWeatherCenter_Create
//   [x] 0x5ad4b0  CKHkWeatherCenter_CreateArray
//   [ ] 0x5ad578  CKHkWeatherCenter_Destructor_2  [dead]
//   [x] 0x5ad5d8  CKHkWeatherCenter_DeletingDestructor  (the destructor, then delete)
//   [x] 0x5ad660  CKHkWeatherCenter_Destructor  (~CKHkWeatherCenter)
//   [x] 0x5ad6c0  CKHkWeatherCenter_PostLoad  (PostLoad)
//   [ ] 0x5ad708  CKHkWeatherCenter_Save
//   [x] 0x5ad730  CKHkWeatherCenter_LevelReset  (RecursiveRegistration: IKHook's (inherited), then 1)
//   [x] 0x5ad758  CKHkWeatherCenter_HandleMessage  (MessageProc)
//   [x] 0x5ad878  CKHkWeatherCenter_ResolveTriggerProperty  (GetInfo)
//   [x] 0x5ad8f0  CKHkWeatherCenter_Load
//   [x] 0x5add18  CKHkWeatherCenter_vf50  (Start, empty: IKHook's)
//   [x] 0x5add20  CKHkWeatherCenter_vf70  (Pause, empty: IKHook's)
//   [x] 0x5add28  CKHkWeatherCenter_vf78  (Resume, empty: IKHook's)
//   [x] 0x5add30  CKHkWeatherCenter_OnLevelExit_maybe  (Stop)
//   [x] 0x5adda8  CKHkWeatherCenter_ResetToInitialState_maybe  (SetDefaultState)
//   [x] 0x5adea8  CKHkWeatherCenter_UpdateCloudUVScroll_maybe  (UpdateCloudUVScroll)
//   [x] 0x5ae200  CKHkWeatherCenter_Update  (Update)
//
//   [ ] 0x9cbed8  CKHkWeatherCenter_IsKindOf  [inline]
//   [ ] 0x9cbf20  CKHkWeatherCenter_GetClassGroup  [inline]
//   [ ] 0x9cbf28  CKHkWeatherCenter_GetClassId  [inline]
//   [x] 0x9cbf30  CKHkWeatherCenter_GetTriggerPropC8  [inline]  (the GetInfo accessor)
#include "k2000/ui/CKHkWeatherCenter.h"

#include <cstring>

#include "crt/ppc_ops.h"
#include "k2000/cameras/CameraContext.h"
#include "k2000/core/IKInfo.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/managers/CKGraphic.h"
#include "k2000/misc/CoreSingletons.h"
#include "k2000/misc/Engine.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CCloudsNodeFx.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/system/IKTime.h"
#include "k2000/ui/CKWeatherPreset.h"

// 0x005ad8f0 CKHkWeatherCenter_Load
int32_t CKHkWeatherCenter::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);  // through TocBridge_CKHook_Load
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pBackgroundSkyNode);
    IKFile_ReadRef(file, &m_pBackgroundCloudsNode);
    IKFile_ReadRef(file, &m_pBackgroundSunNode);
    IKFile_ReadRef(file, &m_pCloudsNodeFx);
    ReadU8(file, &m_ui8NbPreset);
    m_apWeatherPreset = new IKSerializable*[m_ui8NbPreset];  // OperatorNewArray(count * 4)
    IKFile_ReadObjectRefArray(file, m_apWeatherPreset, m_ui8NbPreset);
    IKFile_ReadRef(file, &m_pCurrentWeatherPreset);
    ReadU8(file, &m_ui8StartPreset);
    m_ui8NextPreset = 0;
    m_fInterpolSpeed = 1.0f;  // TOC 0xc1f244 (0x3f800000)
    m_ui8CurrentPreset = 0;
    m_fInterpolRatio = 1.0f;
    // The asked-preset list: every node back to the pool, then one node (preset 0) for this hook.
    for (PresetNode* node = m_lAskedPreset; node != nullptr;) {
        PresetNode* next = node->m_pNext;
        delete node;  // back to the FreeListPool at 0x00ceaa20 in the original
        node = next;
    }
    m_lAskedPreset = nullptr;
    PresetNode* node = new PresetNode;  // FreeListPool at 0x00ceaa20 (FreeListPool_Grow when empty)
    node->m_pNext = m_lAskedPreset;
    m_lAskedPreset = node;
    node->m_pOwner = this;
    node->m_ui8Preset = 0;
    return 1;
}

// ==== port-all P19 ====================================================================================================

namespace {
CKWeatherPreset* AsPreset(IKSerializable* object) { return static_cast<CKWeatherPreset*>(object); }
CCloudsNodeFx* Clouds(const CKHkWeatherCenter* hook) { return static_cast<CCloudsNodeFx*>(hook->m_pCloudsNodeFx); }

// The node's hidden bit (bit 2 of its properties) set to `hidden`.
void SetNodeHidden(IKSerializable* node, uint32_t hidden) {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(node);
    leaf->m_sgProperties = (leaf->m_sgProperties & 0xfffffffbu) | (hidden << 2);
}

// The camera clear colour set to `color` when it differs (the original's compare-then-store).
void SetClearColor(CameraContext* context, uint32_t color) {
    if (context->m_clearColor != color) context->m_clearColor = color;
}

// The geometry's colour from a preset colour (raw bytes); a translucent colour on a geometry whose material blends
// (properties bit 12, material mode 1..6) is made opaque; the blend flag (bit 11) follows the alpha, the properties
// updated (vt+0x60) when it changes.
void ApplyGeometryColor(CGeometry* geometry, const uint8_t* color) {
    std::memcpy(geometry->m_cGeometryColor, color, 4);
    if (color[3] != 0xff && (geometry->m_BitProperties & 0x1000u) != 0) {
        const uint32_t mode = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xfu;
        if (mode > 0 && mode <= 6) geometry->m_cGeometryColor[3] = 0xff;
    }
    const uint32_t blend = geometry->m_cGeometryColor[3] != 0xff ? 1u : 0u;
    const uint32_t properties = geometry->m_BitProperties;
    if (((properties >> 11) & 1u) != blend) {
        geometry->m_BitProperties = (properties & 0xfffff7ffu) | (blend << 11);
        geometry->UpdateProperties();
    }
}

// A UV offset kept in [-1, 1] by whole steps (the original's add / subtract loops; NaN takes one subtraction).
float WrapUnit(float value) {
    const float minusOne = -1.0f;  // TOC2 -0x6710
    const float one = 1.0f;        // TOC2 -0x670c
    if (!(value >= minusOne)) {
        do {
            value = value + one;
        } while (value < minusOne);
    }
    if (!(value <= one)) {
        do {
            value = value - one;
        } while (value > one);
    }
    return value;
}

// The blend byte of the interpolation: (uint8)(int64)(inverse * previous + ratio * next), fmuls then fmadds.
uint8_t BlendByte(float ratio, float inverse, uint8_t previous, uint8_t next) {
    const float scaled = ratio * static_cast<float>(static_cast<double>(next));
    return static_cast<uint8_t>(ppc::fctidz(ppc::fmadds(inverse, static_cast<float>(static_cast<double>(previous)), scaled)));
}
}  // namespace

// 0x005ad660 CKHkWeatherCenter_Destructor
CKHkWeatherCenter::~CKHkWeatherCenter() {
    for (PresetNode* node = m_lAskedPreset; node != nullptr;) {
        PresetNode* next = node->m_pNext;
        delete node;  // back to the FreeListPool at 0x00ceaa20 in the original
        node = next;
    }
    m_lAskedPreset = nullptr;
}

// 0x005acf10 CKHkWeatherCenter_Destroy
void CKHkWeatherCenter::Destroy() {
    for (uint32_t i = 0; i < m_ui8NbPreset; ++i) m_apWeatherPreset[i]->Destroy();  // vt+0x10
    // BUG(original): the array pointer stays set after it is freed.
    if (m_apWeatherPreset != nullptr) delete[] m_apWeatherPreset;
}

// 0x005accc0 CKHkWeatherCenter_ApplyPreset_maybe (CCloudsNodeFx_ApplyPendingParams_maybe / SetTargetParams_maybe through
// their TOC bridges). The clouds node is not tested for null (the levels that have the hook have one).
void CKHkWeatherCenter::ApplyPreset(uint8_t index) {
    m_fInterpolRatio = 1.0f;
    m_ui8NextPreset = index;
    m_ui8CurrentPreset = index;
    AsPreset(m_pCurrentWeatherPreset)->CopyFrom(AsPreset(m_apWeatherPreset[index]));  // 0x005ae758
    CKWeatherPreset* current = AsPreset(m_pCurrentWeatherPreset);
    const CKWeatherPreset* source = AsPreset(m_apWeatherPreset[index]);
    current->m_unk40[0] = source->m_unk40[0];
    current->m_unk40[1] = source->m_unk40[1];
    if (((AsPreset(m_apWeatherPreset[index])->m_unk48 >> 3) & 1u) == 0) {
        Clouds(this)->ApplyPendingParams(0);  // 0x000d8818
    } else {
        Clouds(this)->ApplyPendingParams(1);
        // The preset's +0x04..+0x37 are the clouds' weather preset (eight floats, three words, two colours).
        Clouds(this)->SetTargetParams(reinterpret_cast<const SCloudsWeatherPreset*>(AsPreset(m_apWeatherPreset[index])->m_unk04));
    }
    if (m_pBackgroundCloudsNode != nullptr) {
        SetNodeHidden(m_pBackgroundCloudsNode, (AsPreset(m_pCurrentWeatherPreset)->m_unk48 >> 1) & 1u);
    }
    if (m_pBackgroundSkyNode != nullptr) {
        const uint8_t flags = AsPreset(m_pCurrentWeatherPreset)->m_unk48;
        if ((flags & 1u) == 0) {
            SetNodeHidden(m_pBackgroundSkyNode, 0);
            CameraContext* context = static_cast<CameraContext*>(g_pEngine->m_cameraContext);
            SetClearColor(context, (context->m_pConfig->backColor & 0xffffff00u) | (flags & 1u));
        } else {
            SetNodeHidden(m_pBackgroundSkyNode, 1);
        }
    }
    if (m_pBackgroundSunNode != nullptr) {
        SetNodeHidden(m_pBackgroundSunNode, (AsPreset(m_pCurrentWeatherPreset)->m_unk48 >> 2) & 1u);
    }
}

// 0x005ad6c0 CKHkWeatherCenter_PostLoad (IKLife_PostLoad through its TOC bridge)
int32_t CKHkWeatherCenter::PostLoad(int32_t type) {
    PostLoadLife(type);
    ApplyPreset(0);
    return 1;
}

// 0x005ad758 CKHkWeatherCenter_MessageProc. 0x73's index is the payload word's low byte (lbz 3 of the PS3 word); 0x74
// tests the payload's first byte (lbz 0).
int32_t CKHkWeatherCenter::MessageProc(uint16_t message, void* data) {
    if (message == 0x73) {
        const uint8_t index = static_cast<uint8_t>(*static_cast<const uint32_t*>(data));
        if (m_ui8NbPreset <= index) return 0;
        PresetNode* last = m_lAskedPreset;
        for (PresetNode* node = m_lAskedPreset; node != nullptr; node = node->m_pNext) last = node;
        last->m_ui8Preset = index;  // the list always holds a node (Load, SetDefaultState)
        if (m_lAskedPreset->m_ui8Preset != index) return 0;
        ApplyPreset(index);
        return 0;
    }
    if (message != 0x74) return 1;
    CCloudsNodeFx* clouds = Clouds(this);
    if (*static_cast<const uint8_t*>(data) == 0) {
        if ((clouds->m_ba8Infos & 1u) != 0) return 0;
        clouds->ApplyPendingParams(1);
    } else {
        if ((clouds->m_ba8Infos & 1u) == 0) return 0;
        clouds->ApplyPendingParams(0);
    }
    return 0;
}

// 0x005ad878 CKHkWeatherCenter_GetInfo (TriggerPropertyRequest_SetGetter_maybe), with 0x009cbf30
// CKHkWeatherCenter_GetTriggerPropC8.
int32_t CKHkWeatherCenter::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 200) return 1;
    return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
        return static_cast<uint32_t>(~Clouds(static_cast<CKHkWeatherCenter*>(o))->m_ba8Infos & 1u);
    }, 0);
}

// 0x005add30 CKHkWeatherCenter_OnLevelExit_maybe
void CKHkWeatherCenter::Stop() {
    if (m_pCloudsNodeFx != nullptr) Clouds(this)->ApplyPendingParams(0);
    CameraContext* context = static_cast<CameraContext*>(g_pEngine->m_cameraContext);
    SetClearColor(context, context->m_pConfig->backColor & 0xffffff00u);
}

// 0x005adda8 CKHkWeatherCenter_SetDefaultState (FreeListPool_Grow through its TOC bridge when the pool is empty)
void CKHkWeatherCenter::SetDefaultState(int32_t /*flag*/) {
    if (m_pCloudsNodeFx != nullptr) Clouds(this)->ApplyPendingParams(1);
    for (PresetNode* node = m_lAskedPreset; node != nullptr;) {
        PresetNode* next = node->m_pNext;
        delete node;  // back to the pool
        node = next;
    }
    m_lAskedPreset = nullptr;
    PresetNode* node = new PresetNode;
    node->m_pNext = m_lAskedPreset;
    m_lAskedPreset = node;
    const uint8_t start = m_ui8StartPreset;
    node->m_pOwner = this;
    node->m_ui8Preset = start;
    ApplyPreset(start);
}

// 0x005adea8 CKHkWeatherCenter_UpdateCloudUVScroll_maybe (CMaterial_GetUVTransformMatrix_maybe through its TOC bridge)
void CKHkWeatherCenter::UpdateCloudUVScroll(IKTime* frameClock) {
    if (m_pBackgroundCloudsNode != nullptr && ((AsPreset(m_pCurrentWeatherPreset)->m_unk48 >> 1) & 1u) == 0) {
        // The first geometry only, not tested for null.
        CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(m_pBackgroundCloudsNode)->m_lGeometryList);
        ApplyGeometryColor(geometry, AsPreset(m_pCurrentWeatherPreset)->m_unk3c);
        CMatrix34* uv = static_cast<CMaterial*>(geometry->m_pMaterial)->GetUVTransformMatrix();  // 0x000bb9f8
        const float dt = frameClock->m_afDeltaTime[0];
        const CKWeatherPreset* current = AsPreset(m_pCurrentWeatherPreset);
        float u = ppc::fmadds(current->m_unk40[0], dt, uv->m_pos.x);
        float v = ppc::fmadds(current->m_unk40[1], dt, uv->m_pos.y);
        const float w = uv->m_pos.z;
        u = WrapUnit(u);
        v = WrapUnit(v);
        const float zero = 0.0f;  // TOC2 -0x6708
        uv->m_pos.x = u;
        uv->m_pos.y = v;
        uv->m_pos.z = ppc::fmadds(dt, zero, w);
        uv->m_ui32Flags &= 0xfffdffffu;
    }
    if (m_pBackgroundSkyNode == nullptr) return;
    if ((AsPreset(m_pCurrentWeatherPreset)->m_unk48 & 1u) == 0) {
        for (CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(m_pBackgroundSkyNode)->m_lGeometryList);
             geometry != nullptr; geometry = geometry->m_pNext) {
            ApplyGeometryColor(geometry, AsPreset(m_pCurrentWeatherPreset)->m_unk38);
        }
        return;
    }
    CRenderer* renderer = g_pEngine->m_graphic->m_renderer;
    if ((renderer->m_bitProperties & 2u) != 0) return;
    const uint8_t* color = AsPreset(m_pCurrentWeatherPreset)->m_unk38;  // the PS3 word with its low (alpha) byte 0
    SetClearColor(renderer->m_cameraContext, (static_cast<uint32_t>(color[0]) << 24) |
                                                 (static_cast<uint32_t>(color[1]) << 16) |
                                                 (static_cast<uint32_t>(color[2]) << 8));
}

// 0x005ae200 CKHkWeatherCenter_Update
void CKHkWeatherCenter::Update(IKTime* frameClock) {
    const float one = 1.0f;  // TOC2 -0x670c
    if (!(m_fInterpolRatio < one)) {
        UpdateCloudUVScroll(frameClock);
        return;
    }
    const float ratio = ppc::fmadds(m_fInterpolSpeed, frameClock->m_afDeltaTime[0], m_fInterpolRatio);
    m_fInterpolRatio = ratio;
    if (ratio >= one) {
        ApplyPreset(m_ui8NextPreset);
        UpdateCloudUVScroll(frameClock);
        return;
    }
    {
        const float inverse = one - ratio;
        const CKWeatherPreset* next = AsPreset(m_apWeatherPreset[m_ui8NextPreset]);
        const CKWeatherPreset* previous = AsPreset(m_apWeatherPreset[m_ui8CurrentPreset]);
        uint8_t* out = AsPreset(m_pCurrentWeatherPreset)->m_unk3c;
        for (int k = 0; k < 4; ++k) out[k] = BlendByte(ratio, inverse, previous->m_unk3c[k], next->m_unk3c[k]);
    }
    {
        const float ratio2 = m_fInterpolRatio;
        const float inverse = one - ratio2;
        const CKWeatherPreset* next = AsPreset(m_apWeatherPreset[m_ui8NextPreset]);
        const CKWeatherPreset* previous = AsPreset(m_apWeatherPreset[m_ui8CurrentPreset]);
        uint8_t* out = AsPreset(m_pCurrentWeatherPreset)->m_unk38;
        for (int k = 0; k < 4; ++k) out[k] = BlendByte(ratio2, inverse, previous->m_unk38[k], next->m_unk38[k]);
    }
    UpdateCloudUVScroll(frameClock);
}
