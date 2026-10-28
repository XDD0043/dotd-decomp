// CSGLight.cpp - reconstructed original translation unit 0xcf6e0-0xd07b8 (GAME_TOC1, main_toc1), 18 functions, 13 live.
// Primary class: CSGLight  key 0x80b  category SceneNode  size 0x64  vtable 0xb18270
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0xcf6e0  CSGLight_Delete
//   [ ] 0xcf730  CSGLight_GetBoundsFlag_maybe  [dead]
//   [ ] 0xcf740  CSGLight_RemoveFromRefList_maybe  [dead]
//   [ ] 0xcf7d8  CSGLight_FreeLightDataArray_maybe  [dead]
//   [ ] 0xcf868  RegisterCSGLightClass
//   [ ] 0xcf8e0  _GLOBAL__I_cf8e0
//   [ ] 0xcf8f0  CSGLight_PostLoad
//   [ ] 0xcf978  CSGLight_RecursiveRegistration
//   [ ] 0xcfa20  CSGLight_Destroy
//   [x] 0xcfab0  CSGLight_DeleteArray
//   [x] 0xcfb50  CSGLight_Create
//   [x] 0xcfbc0  CSGLight_Enqueue
//   [ ] 0xcfd88  CSGLight_MessageProc
//   [x] 0xcfd90  CSGLight_CreateArray
//   [ ] 0xcfe70  CSGLight_AddToRefList_maybe  [dead]
//   [ ] 0xcff68  CSGLight_SetBoundsFlag_maybe  [dead]
//   [x] 0xd0008  CSGLight_Load
//   [ ] 0xd03b8  CSGLight_Save
//
//   [ ] 0x9a27d8  CSGLight_IsKindOfClass  [inline]
//   [x] 0x9a2810  CSGLight_GetClassType  [inline]
//   [x] 0x9a2818  CSGLight_GetClassID  [inline]
//   [ ] 0x9a2820  CSGLight_Destructor  [inline]
//   [ ] 0x9a2890  CSGLight_DeletingDestructor  [inline]
#include "k2000/scenegraph/CSGLight.h"

#include "k2000/io/IKFile.h"
#include <cfloat>

#include "Renderware/rwcore/RwCamera.h"
#include "k2000/logic/render/CLightComponent.h"
#include "k2000/memory/Mem.h"
#include "k2000/render/CRenderer.h"

// Inlined in 0x000cfb50 CSGLight_Create.
CSGLight::CSGLight() {
    m_apLightSets = nullptr;
    m_ui32LightSetCapacity = 2;
    m_ui32NbLightSets = 0;
}

// 0x000d0008 CSGLight_Load: the light's own fields only in level files.
int32_t CSGLight::Load(IKFile* file, int32_t type) {
    CSGLeaf::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_eLightBoxType);
    ReadU32LE(file, &m_ui32NbActiveLights);
    m_aplightParameters = static_cast<IKSerializable**>(
        Mem_AllocAligned16(m_ui32NbActiveLights * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, m_aplightParameters, m_ui32NbActiveLights);
    {
        // One 0x18-byte read, then each word byte-swapped (lwbrx).
        uint8_t bytes[0x18];
        file->Read(bytes, 0x18);
        uint32_t* words = reinterpret_cast<uint32_t*>(&m_xLocalInfluenceBBox);
        for (int i = 0; i < 6; ++i) {
            const uint8_t* b = bytes + 4 * i;
            words[i] = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                       (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
        }
    }
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count != 0) {
        m_ui32LightSetCapacity = count;
        m_apLightSets =
            static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
        if (m_ui32LightSetCapacity < count) {  // as in the original: cannot happen right after the assignment
            uint32_t capacity = (count & ~1u) + 2;
            if (capacity == 0) capacity = 2;
            m_apLightSets = static_cast<IKSerializable**>(
                Mem_ReallocAligned16(m_apLightSets, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
            m_ui32LightSetCapacity = capacity;
        }
        m_ui32NbLightSets = count;
        IKFile_ReadObjectRefArray(file, m_apLightSets, count);
    }
    ReadU32LE(file, &m_ui32OcclusionLevel);
    return 1;
}

// 0x000cfbc0 CSGLight_Enqueue. The first line clears bit 3 of the frame's private flags. A dynamic light (flag 0x10) takes its local
// box again as the box around the origin with the same half extents (BBox_SetFromCenterExtents_maybe 0x23d550 with the centre
// 0x00c50d64 and half the size), and every non-hidden light whose stamp is 0 (not stamped yet) or that is dynamic puts its world
// box at the frame's LTM position. The stamp is the render frame counter.
void CSGLight::UpdateAndExtract(float /*maxDistanceSquared*/, RenderQueue** /*stages*/, IKTime* frameClock, RwCamera* /*camera*/,
                                int32_t /*distanceCull*/) {
    m_pRwFrame->object.privateFlags = static_cast<RwUInt8>(m_pRwFrame->object.privateFlags & ~8u);
    for (uint32_t i = 0; i < m_ui32NbActiveLights; ++i) static_cast<CLightComponent*>(m_aplightParameters[i])->UpdateColorAnimation(frameClock);
    if ((m_sgProperties & 4) != 0) return;
    bool makeWorldBox = true;
    if ((m_sgProperties & 0x10) == 0) {
        makeWorldBox = m_ui16LastRenderedFrame == 0;
    } else {
        const float half[3] = {(m_xLocalInfluenceBBox.m_sup.x - m_xLocalInfluenceBBox.m_inf.x) * 0.5f, (m_xLocalInfluenceBBox.m_sup.y - m_xLocalInfluenceBBox.m_inf.y) * 0.5f,
                               (m_xLocalInfluenceBBox.m_sup.z - m_xLocalInfluenceBBox.m_inf.z) * 0.5f};
        // The two corners (centre +- half, the centre being the null vector) folded into a maximum and a minimum.
        const float corners[2][3] = {{0.0f + half[0], 0.0f + half[1], 0.0f + half[2]}, {0.0f - half[0], 0.0f - half[1], 0.0f - half[2]}};
        float* box = &m_xLocalInfluenceBBox.m_sup.x;
        for (int axis = 0; axis < 3; ++axis) {
            box[axis] = -FLT_MAX;
            box[3 + axis] = FLT_MAX;
        }
        for (const auto& corner : corners) {
            for (int axis = 0; axis < 3; ++axis) {
                if (corner[axis] < box[3 + axis]) box[3 + axis] = corner[axis];
                if (box[axis] < corner[axis]) box[axis] = corner[axis];
            }
        }
    }
    if (makeWorldBox) {
        const RwV3d& position = RwFrameGetLTM(m_pRwFrame)->pos;
        m_xWorldInfluenceBBox.m_sup = {m_xLocalInfluenceBBox.m_sup.x + position.x, m_xLocalInfluenceBBox.m_sup.y + position.y, m_xLocalInfluenceBBox.m_sup.z + position.z};
        m_xWorldInfluenceBBox.m_inf = {m_xLocalInfluenceBBox.m_inf.x + position.x, m_xLocalInfluenceBBox.m_inf.y + position.y, m_xLocalInfluenceBBox.m_inf.z + position.z};
    }
    m_ui16LastRenderedFrame = g_ui16RenderFrameCounter;
    ComputeZoneOverlapWeights();
}
