// CKSrvShadow.cpp - reconstructed original translation unit 0x1fa938-0x1fe788 (GAME_TOC1, main_toc1), 55 functions, 39 live.
// Primary class: CKSrvShadow  key 0x301  category Service  size 0x6c  vtable 0xb1ecb8
// Other owners: ShadowAtlas (3), KObject (1), UpdateActiveSectorWorld (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1fa938  CKSrvShadow_Delete
//   [ ] 0x1fa988  CKSrvShadow_Construct  [dead]
//   [x] 0x1fa9f0  CKSrvShadow_RecursiveRegistration  (returns 1: the root's empty slot)
//   [ ] 0x1fa9f8  CKSrvShadow_Save
//   [x] 0x1faa00  CKSrvShadow_EntryHasTexture_maybe
//   [x] 0x1faa50  CKSrvShadow_Pause
//   [x] 0x1faa58  CKSrvShadow_Resume
//   [x] 0x1faa60  CKSrvShadow_MarkCasterGeometryRecursive_maybe
//   [ ] 0x1fabd0  CKSrvShadow_RemovePendingNodeByCaster_maybe  [dead]
//   [ ] 0x1fac78  CKSrvShadow_FindPendingNodeByCaster_maybe  [dead]
//   [x] 0x1facc8  ShadowAtlas_GetUVMin_maybe
//   [x] 0x1face0  ShadowAtlas_GetUVMax_maybe
//   [ ] 0x1facf8  ShadowAtlas_GetCellCount_maybe  [dead]
//   [ ] 0x1fad00  FUN_001fad00  [dead]
//   [ ] 0x1fad10  FUN_001fad10  [dead]
//   [ ] 0x1fad20  FUN_001fad20  [dead]
//   [ ] 0x1fad30  KObject_LevelResetIfNotNull_2_maybe  [dead]
//   [ ] 0x1fad80  RegisterCKSrvShadowClass
//   [ ] 0x1fae00  _GLOBAL__I_1fae00
//   [x] 0x1fae10  CKSrvShadow_DeleteArray
//   [x] 0x1faeb0  CKSrvShadow_DestroyService
//   [x] 0x1faed8  CKSrvShadow_InitializeService
//   [x] 0x1faf00  CKSrvShadow_Start
//   [x] 0x1fafb8  CKSrvShadow_GetEntryFloat1C_maybe
//   [x] 0x1faff0  CKSrvShadow_GetEntryFloat18_maybe
//   [x] 0x1fb028  CKSrvShadow_GetEntryFloat14_maybe
//   [x] 0x1fb060  CKSrvShadow_GetEntryFloat10_maybe
//   [x] 0x1fb098  CKSrvShadow_GetEntryOrigin_maybe
//   [ ] 0x1fb0e0  FUN_001fb0e0  [dead]
//   [ ] 0x1fb1c0  FUN_001fb1c0  [dead]
//   [ ] 0x1fb280  FUN_001fb280  [dead]
//   [x] 0x1fb2d0  CKSrvShadow_PostLoad
//   [x] 0x1fb3b8  CKSrvShadow_GetEntryTexture_maybe
//   [x] 0x1fb468  CKSrvShadow_RefreshEntryTextures_maybe
//   [ ] 0x1fb520  FUN_001fb520  [dead]
//   [ ] 0x1fb558  CKSrvShadow_PushConfigValueToProjectors_maybe  [dead]
//   [ ] 0x1fb5f0  CKSrvShadow_Construct_2  [dead]
//   [x] 0x1fb658  CKSrvShadow_SectorUnload  (empty: IKUpdatable's default)
//   [x] 0x1fb660  CKSrvShadow_SectorLoaded
//   [x] 0x1fb6f8  CKSrvShadow_RegisterCaster
//   [ ] 0x1fb968  CKSrvShadow_RegisterPendingNode_maybe  [dead]
//   [x] 0x1fb988  CKSrvShadow_IsShadowModeEnabled_maybe
//   [x] 0x1fb9e0  CKSrvShadow_UpdateActiveSectorShadowTexture_maybe
//   [x] 0x1fbb38  CKSrvShadow_DemoteCasterToPending
//   [x] 0x1fbe98  CKSrvShadow_Create
//   [x] 0x1fbf40  CKSrvShadow_CreateArray
//   [x] 0x1fc060  CKSrvShadow_Load
//   [ ] 0x1fcb10  CKSrvShadow_RemoveActiveNodeByCaster_maybe  [dead]
//   [x] 0x1fcc58  CKSrvShadow_Stop
//   [x] 0x1fd068  CKSrvShadow_Destroy
//   [x] 0x1fd658  CKSrvShadow_DeletingDestructor  (the destructor; delete)
//   [x] 0x1fd6f0  CKSrvShadow_UnregisterCaster
//   [x] 0x1fdd68  UpdateCKSrvShadow
//   [x] 0x1fe668  CKSrvShadow_Destructor
//   [x] 0x1fe6f8  CKSrvShadow_Destructor_2  (= 0x1fe668)
//
//   [ ] 0x9b10f8  CKSrvShadow_IsKindOfClass  [inline]
//   [ ] 0x9b1130  CKSrvShadow_GetClassType  [inline]
//   [ ] 0x9b1138  CKSrvShadow_GetClassID  [inline]
//   [ ] 0x9b1140  ShadowProjectorBase_Destructor_maybe  [inline]
//   [ ] 0x9b1150  ShadowProjectorBase_DeletingDestructor_maybe  [inline]
#include "k2000/services/CKSrvShadow.h"

#include <cmath>
#include <cstring>

#include "Renderware/rwcore/RwTexture.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwTexture.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/components/CKShadowCpnt.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/render/MeshShaderPassState.h"
#include "k2000/render/MeshShaderPassState.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/geometry/CGeometry.h"
#include "k2000/logic/render/CMaterial.h"
#include "k2000/scenegraph/CNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "crt/ppc_ops.h"

CKSrvShadow* g_pSrvShadow = nullptr;  // 0x00cea928

// 0x001faed8 CKSrvShadow_InitializeService
int32_t CKSrvShadow::InitializeService() {
    Engine_SetShadowService(this);
    return 1;
}

// 0x001faeb0 CKSrvShadow_DestroyService
void CKSrvShadow::DestroyService() { Engine_SetShadowService(nullptr); }

// 0x001fb6f8 CKSrvShadow_RegisterCaster
void CKSrvShadow::RegisterCaster(IKSerializable* shadowCpnt, IKSerializable* node, CKShadowGround* ground,
                                 int32_t force, CKShadowDataSpot* spot, uint8_t recurse) {
    if (ground->m_bUsed_maybe != 0 && force == 0) return;
    ground->m_bUsed_maybe = 1;
    MarkCasterGeometry(node, recurse);  // 0x001faa60
    const uint8_t priority = static_cast<CKShadowCpnt*>(shadowCpnt)->m_ui8Priority;
    if (spot == nullptr) {
        spot = m_lShadowUnused;
        if (spot == nullptr) {
            // no free spot: a waiting slot, if there is one
            CKShadowDataWaiting* waiting = m_lShadowWaitingUnused;
            if (waiting == nullptr) return;
            CKShadowDataWaiting* following = waiting->m_pNext;
            if (following == nullptr) {
                m_lShadowWaitingUnused = nullptr;
            } else {
                waiting->m_pNext = nullptr;
                m_lShadowWaitingUnused = following;
            }
            waiting->m_pShadowedLeaf = node;
            waiting->m_pShadowCpnt = shadowCpnt;
            waiting->m_pShadowGround = ground;
            if (priority == 0) {
                waiting->m_pNext = m_lShadowWaitingHighPriority;
                m_lShadowWaitingHighPriority = waiting;
            } else if (priority == 1) {
                waiting->m_pNext = m_lShadowWaitingLowPriority;
                m_lShadowWaitingLowPriority = waiting;
            }
            return;
        }
        CKShadowDataSpot* following = spot->m_pNext;
        if (following == nullptr) {
            m_lShadowUnused = nullptr;
        } else {
            spot->m_pNext = nullptr;
            m_lShadowUnused = following;
        }
    }
    spot->m_pShadow->SetData(shadowCpnt, node, ground);  // vt+0x0c
    spot->m_pShadowCpnt = shadowCpnt;
    spot->m_pShadowedLeaf = node;
    spot->m_pShadowGround = ground;
    spot->m_pShadow->m_bDrawn = 1;
    if (priority == 0) {
        spot->m_pShadow->SetShadowHided(0);  // vt+0x14
        spot->m_pNext = m_lDrawingShadowHighPriority;
        m_lDrawingShadowHighPriority = spot;
    } else if (priority == 1) {
        spot->m_pShadow->SetShadowHided(0);
        spot->m_pNext = m_lDrawingShadowLowPriority;
        m_lDrawingShadowLowPriority = spot;
    }
}

namespace {
// The test UnregisterCaster 0x1fd6f0 puts a waiting caster through before it takes a freed spot: its leaf was queued this
// frame and is within its component's shadow distance of the focus point (the service camera's real position, +0x598), or
// the component asks to be always visible (+0x2a).
// The distance from a caster's leaf (its frame's stored LTM position, frame +0x80) to the focus point, as UnregisterCaster
// and UpdateCKSrvShadow compute it: y first, fused, Math_Sqrtf (fsqrts).
float FocusDistance(const void* leaf, const CVector3& focus) {
    const RwV3d& pos = FrameLtm(static_cast<const CSGLeaf*>(leaf)->m_pRwFrame)->pos;
    const float dy = pos.y - focus.y;
    const float dx = pos.x - focus.x;
    const float dz = pos.z - focus.z;
    return std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
}
const CVector3& FocusPoint() { return static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera)->m_v3RealPos; }

// (The original computes the distance before the frame test; it has no side effect.)
bool WaitingCasterIsNear(const CKSrvShadow::CKShadowDataWaiting* waiting) {
    const CSGLeaf* leaf = static_cast<const CSGLeaf*>(waiting->m_pShadowedLeaf);
    if (leaf->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter) return false;
    const float distance = FocusDistance(waiting->m_pShadowedLeaf, FocusPoint());
    const CKShadowCpnt* component = static_cast<const CKShadowCpnt*>(waiting->m_pShadowCpnt);
    return component->m_fShadowDistanceMax > distance || component->m_bAlwaysVisible != 0;
}

// A waiting slot taken out of its list and put on the unused list.
void ReleaseWaitingSlot(CKSrvShadow::CKShadowDataWaiting*& list, CKSrvShadow::CKShadowDataWaiting* waiting,
                        CKSrvShadow::CKShadowDataWaiting*& unused) {
    if (list == waiting) {
        list = waiting->m_pNext;
    } else {
        for (CKSrvShadow::CKShadowDataWaiting* it = list; it != nullptr; it = it->m_pNext) {
            if (it->m_pNext == waiting) {
                it->m_pNext = waiting->m_pNext;
                break;
            }
        }
    }
    waiting->m_pNext = unused;
    unused = waiting;
}
}  // namespace

// 0x001fd6f0 CKSrvShadow_UnregisterCaster: the caster's ground leaves the drawing list of its component's priority (high 0 or
// low 1; any other value does nothing): the spot is told to hide, the ground's in-use byte cleared and the spot offered to
// the head of the high-priority waiting list, then of the low-priority one, when that caster was queued this frame and is
// near enough (a taker is registered again on the spot, forced); otherwise the spot goes back to the free list. A ground that
// is not drawing but waiting just leaves the waiting list.
// The other half of the bookkeeping (promoting waiting casters, demoting the spots that stop drawing) is UpdateCKSrvShadow's.
void CKSrvShadow::UnregisterCaster(CKShadowGround* ground, IKSerializable* shadowCpnt) {
    const uint8_t priority = static_cast<CKShadowCpnt*>(shadowCpnt)->m_ui8Priority;
    if (priority > 1) return;
    CKShadowDataSpot*& drawing = priority == 0 ? m_lDrawingShadowHighPriority : m_lDrawingShadowLowPriority;
    CKShadowDataWaiting*& waiting = priority == 0 ? m_lShadowWaitingHighPriority : m_lShadowWaitingLowPriority;
    CKShadowDataSpot* spot = nullptr;
    for (CKShadowDataSpot* it = drawing; it != nullptr; it = it->m_pNext) {
        if (it->m_pShadowGround == ground) {
            spot = it;
            break;
        }
    }
    if (spot != nullptr) {
        spot->m_pShadow->SetShadowHided(1);  // vt+0x14
        if (drawing == spot) {
            drawing = spot->m_pNext;
        } else {
            for (CKShadowDataSpot* it = drawing; it != nullptr; it = it->m_pNext) {
                if (it->m_pNext == spot) {
                    it->m_pNext = spot->m_pNext;
                    break;
                }
            }
        }
        spot->m_pNext = nullptr;
        spot->m_pShadowGround->m_bUsed_maybe = 0;
        spot->m_pShadowGround = nullptr;
        spot->m_pShadowedLeaf = nullptr;
        spot->m_pShadowCpnt = nullptr;
        spot->m_pShadow->m_pShadowCpnt = nullptr;
        CKShadowDataWaiting* const heads[2] = {m_lShadowWaitingHighPriority, m_lShadowWaitingLowPriority};
        CKShadowDataWaiting** const lists[2] = {&m_lShadowWaitingHighPriority, &m_lShadowWaitingLowPriority};
        for (int i = 0; i < 2; ++i) {
            CKShadowDataWaiting* head = heads[i];
            if (head == nullptr || !WaitingCasterIsNear(head)) continue;
            IKSerializable* takerCpnt = head->m_pShadowCpnt;
            IKSerializable* takerLeaf = static_cast<IKSerializable*>(head->m_pShadowedLeaf);
            CKShadowGround* takerGround = head->m_pShadowGround;
            ReleaseWaitingSlot(*lists[i], head, m_lShadowWaitingUnused);
            RegisterCaster(takerCpnt, takerLeaf, takerGround, 1, spot, 0);
            return;
        }
        spot->m_pNext = m_lShadowUnused;
        m_lShadowUnused = spot;
        return;
    }
    for (CKShadowDataWaiting* it = waiting; it != nullptr; it = it->m_pNext) {
        if (it->m_pShadowGround != ground) continue;
        it->m_pShadowGround->m_bUsed_maybe = 0;
        it->m_pShadowGround = nullptr;
        it->m_pShadowedLeaf = nullptr;
        it->m_pShadowCpnt = nullptr;
        ReleaseWaitingSlot(waiting, it, m_lShadowWaitingUnused);
        return;
    }
}

namespace {
// One Read of count words, then every word byte-swapped in place (lwbrx/stw), as the original does.
void ReadWordsLE(IKFile* file, uint32_t* words, uint32_t count) {
    uint8_t* bytes = reinterpret_cast<uint8_t*>(words);
    file->Read(bytes, count * 4);
    for (uint32_t i = 0; i < count; ++i) {
        const uint8_t* b = bytes + 4 * i;
        words[i] = static_cast<uint32_t>(b[0]) | (static_cast<uint32_t>(b[1]) << 8) |
                   (static_cast<uint32_t>(b[2]) << 16) | (static_cast<uint32_t>(b[3]) << 24);
    }
}
}  // namespace

// Inlined in CKSrvShadow_Load's new[] loop (0x1fca20): the IKShadow part, then the spot's defaults (the ground probe's
// masks 1, 8; no ground, face -1, status 3, sector 0: the two contact structures' constructors).
CKShadowSpot::CKShadowSpot() {
    m_pNext = nullptr;
    m_pShadowCpnt = nullptr;
}

// Inlined in 0x001fbe98 CKSrvShadow_Create (0x1fa988 CKSrvShadow_Construct is an unreferenced copy): the
// IKService part, the vector, the list heads, the global; the priority last (0). The original does
// not call Engine_SetShadowService here (InitializeService does).
CKSrvShadow::CKSrvShadow() {
    m_unk30.m_ui32NbElt = 1;
    m_unk30.m_pBlock = nullptr;
    m_unk30.m_ui32NbUsedElt = 0;
    m_lShadowUnused = nullptr;
    m_lDrawingShadowHighPriority = nullptr;
    m_lDrawingShadowLowPriority = nullptr;
    m_lShadowWaitingUnused = nullptr;
    m_lShadowWaitingHighPriority = nullptr;
    m_lShadowWaitingLowPriority = nullptr;
    g_pSrvShadow = this;
    m_ui32Priority = 0;
}

// 0x001fc060 CKSrvShadow_Load
int32_t CKSrvShadow::Load(IKFile* file, int32_t type) {
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_ui32NbShadowSpot);
    ReadU32LE(file, &m_ui32NbShadowSpotWaiting);
    if (m_ui32NbShadowSpot != 0) {
        m_aShadowSpot = new CKShadowSpot[m_ui32NbShadowSpot];
        m_aShadowDataSpot = new CKShadowDataSpot[m_ui32NbShadowSpot];
    }
    IKFile_ReadRef(file, &m_pShadowSpotNode);
    IKFile_ReadRef(file, &m_pShadowParticuleGeometry);
    // BUG(original): byte counters (rlwinm 0x18,0x1f) in both list loops: 256 entries or more never end.
    for (uint8_t i = 0; i < m_ui32NbShadowSpot; ++i) {
        CKShadowDataSpot& data = m_aShadowDataSpot[i];
        data.m_pShadowGround = nullptr;
        data.m_pShadowCpnt = nullptr;
        data.m_pShadowedLeaf = nullptr;
        data.m_pShadow = &m_aShadowSpot[i];
        data.m_pNext = m_lShadowUnused;
        m_lShadowUnused = &data;
    }
    m_aShadowWaiting = new CKShadowDataWaiting[m_ui32NbShadowSpotWaiting];
    for (uint8_t i = 0; i < m_ui32NbShadowSpotWaiting; ++i) {
        CKShadowDataWaiting& waiting = m_aShadowWaiting[i];
        waiting.m_pShadowedLeaf = nullptr;
        waiting.m_pShadowCpnt = nullptr;
        waiting.m_pShadowGround = nullptr;
        waiting.m_pNext = m_lShadowWaitingUnused;
        m_lShadowWaitingUnused = &waiting;
    }
    IKFile_ReadTextureRef(file, &m_pShadowTexture, 0);
    if (m_pShadowTexture != nullptr) TextureRef_AddRef(m_pShadowTexture);  // the service keeps one reference
    ReadU8(file, &m_ui8NbShadowsInTextureShadow);
    m_aTextureCoord = new CTexCoord[2 * m_ui8NbShadowsInTextureShadow];
    if (m_ui8NbShadowsInTextureShadow != 0) {
        // BUG(original): a byte counter against 2 * count (cmpw): 128 shadows or more never end.
        for (uint8_t i = 0; static_cast<int32_t>(i) < 2 * m_ui8NbShadowsInTextureShadow; ++i) {
            ReadF32LE(file, &m_aTextureCoord[i].m_fU);
            ReadF32LE(file, &m_aTextureCoord[i].m_fV);
        }
    }
    ReadU8(file, &m_ui8TextureShadowWidth);
    ReadU8(file, &m_ui8TextureShadowHeight);
    ReadF32LE(file, &m_fOffsetShadow);
    ReadU8(file, &m_unk14);
    ReadU32LE(file, &m_unk0c);
    ReadU32LE(file, &m_unk10);
    ReadS32LE(file, &m_unk68);
    ReadU8(file, &m_unk15);
    if (m_unk15 == 0) return 1;

    uint32_t count = 0;
    ReadU32LE(file, &count);
    m_unk30.m_ui32NbElt = 1;
    m_unk30.m_pBlock = static_cast<Entry*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry))));
    if (m_unk30.m_ui32NbElt < count) {  // TVector growth: to count + 1
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_unk30.m_pBlock = static_cast<Entry*>(Mem_ReallocAligned16(m_unk30.m_pBlock, capacity * static_cast<uint32_t>(sizeof(Entry))));
        m_unk30.m_ui32NbElt = capacity;
    }
    m_unk30.m_ui32NbUsedElt = count;
    if (count == 0) {
        file->Seek(4, kSeekCur);  // as in the original: an empty list skips 4 bytes
        return 1;
    }
    for (uint32_t i = 0; i < count; ++i) {
        Entry& entry = m_unk30.m_pBlock[i];
        entry.m_unk28 = nullptr;
        entry.m_unk00 = nullptr;
        ReadU8(file, &entry.m_unk24);
        if (entry.m_unk24 == 0) continue;
        ReadU32LE(file, &entry.m_unk18);
        ReadU32LE(file, &entry.m_unk1c);
        ReadU32LE(file, &entry.m_unk10);
        ReadU32LE(file, &entry.m_unk14);
        ReadU32LE(file, &entry.m_unk20);
        uint32_t vector[3];
        ReadWordsLE(file, vector, 3);  // one 12-byte read
        std::memcpy(&entry.m_unk04, vector, sizeof(vector));
        IKFile_ReadRef(file, &entry.m_unk28);
    }
    return 1;
}

namespace {
// The drawing lists' loop of CKSrvShadow_Stop: each spot told (vt+0x14, 1), its data returned to the unused
// list with its ground flag cleared. BUG(original): a node without a ground is dereferenced at +0x1d.
void ReleaseDrawing(CKSrvShadow::CKShadowDataSpot*& list, CKSrvShadow::CKShadowDataSpot*& unused) {
    while (list != nullptr) {
        CKSrvShadow::CKShadowDataSpot* node = list;
        node->m_pShadow->SetShadowHided(1);
        list = node->m_pNext;
        node->m_pNext = nullptr;
        node->m_pShadowGround->m_bUsed_maybe = 0;
        node->m_pShadowGround = nullptr;
        node->m_pShadowCpnt = nullptr;
        node->m_pShadowedLeaf = nullptr;
        node->m_pShadow->m_pShadowCpnt = nullptr;
        node->m_pNext = unused;
        unused = node;
    }
}

// The waiting lists' loop.
void ReleaseWaiting(CKSrvShadow::CKShadowDataWaiting*& list, CKSrvShadow::CKShadowDataWaiting*& unused) {
    while (list != nullptr) {
        CKSrvShadow::CKShadowDataWaiting* node = list;
        list = node->m_pNext;
        node->m_pNext = nullptr;
        node->m_pShadowGround->m_bUsed_maybe = 0;
        node->m_pShadowGround = nullptr;
        node->m_pShadowCpnt = nullptr;
        node->m_pShadowedLeaf = nullptr;
        node->m_pNext = unused;
        unused = node;
    }
}
}  // namespace

// 0x001faf00 CKSrvShadow_Start
void CKSrvShadow::Start() {
    static_cast<CSGMovable*>(m_pShadowSpotNode)->SetIdentity();  // 0xd08f0
    if (m_unk15 == 0) return;
    for (uint32_t i = 0; i != m_unk30.m_ui32NbUsedElt; ++i) {
        const Entry& entry = m_unk30.m_pBlock[i];
        if (entry.m_unk24 == 0 || entry.m_unk28 == nullptr) continue;
        CSGLeaf* node = static_cast<CSGLeaf*>(entry.m_unk28);
        node->m_sgProperties = (node->m_sgProperties & ~4u) | 4u;
    }
}

// 0x001fbb38 CKSrvShadow_DemoteCasterToPending
void CKSrvShadow::DemoteCasterToPending(IKSerializable* leaf, IKSerializable* shadowCpnt) {
    const uint8_t priority = static_cast<const CKShadowCpnt*>(shadowCpnt)->m_ui8Priority;
    // BUG(original): another priority reads an unset register (the caller's: UpdateCKSrvShadow's service pointer) as the
    // spot to give back, which would overwrite the service's first word. The game's components are 0 or 1; nothing here.
    if (priority > 1) return;
    CKShadowDataSpot*& drawing = priority == 0 ? m_lDrawingShadowHighPriority : m_lDrawingShadowLowPriority;
    CKShadowDataWaiting*& waitingList = priority == 0 ? m_lShadowWaitingHighPriority : m_lShadowWaitingLowPriority;
    CKShadowDataSpot* spot = drawing;
    while (spot != nullptr && spot->m_pShadowedLeaf != leaf) spot = spot->m_pNext;
    if (spot == nullptr) return;
    CKShadowDataWaiting* waiting = m_lShadowWaitingUnused;
    if (waiting != nullptr) {
        CKShadowDataWaiting* following = waiting->m_pNext;
        if (following == nullptr) {
            m_lShadowWaitingUnused = nullptr;
        } else {
            waiting->m_pNext = nullptr;
            m_lShadowWaitingUnused = following;
        }
        spot->m_pShadow->SetShadowHided(1);  // vt+0x14
        CKShadowDataSpot* head = drawing;
        if (head != nullptr) {
            if (spot == head) {
                drawing = spot->m_pNext;
                spot->m_pNext = nullptr;
            } else {
                for (CKShadowDataSpot* previous = head; previous->m_pNext != nullptr; previous = previous->m_pNext) {
                    if (previous->m_pNext != spot) continue;
                    previous->m_pNext = spot->m_pNext;
                    spot->m_pNext = nullptr;
                    break;
                }
            }
        }
        waiting->m_pShadowCpnt = shadowCpnt;
        waiting->m_pShadowedLeaf = spot->m_pShadowedLeaf;
        waiting->m_pShadowGround = spot->m_pShadowGround;
        waiting->m_pNext = waitingList;
        waitingList = waiting;
        spot->m_pShadowGround = nullptr;
        spot->m_pShadowCpnt = nullptr;
        spot->m_pShadowedLeaf = nullptr;
        spot->m_pShadow->m_pShadowCpnt = nullptr;
    }
    // BUG(original): without a free waiting slot the spot is given back while still linked in its drawing list.
    spot->m_pNext = m_lShadowUnused;
    m_lShadowUnused = spot;
}

namespace {
// UpdateCKSrvShadow's promotion of one waiting caster: a caster drawn this frame (or always visible) within its component's
// shadow distance leaves its list (searched from the head) for the unused list and is registered again, forced. The next
// caster (read before) is returned.
CKSrvShadow::CKShadowDataWaiting* PromoteIfNear(CKSrvShadow* service, CKSrvShadow::CKShadowDataWaiting*& list,
                                                CKSrvShadow::CKShadowDataWaiting* entry, const CVector3& focus) {
    const float distance = FocusDistance(entry->m_pShadowedLeaf, focus);
    const CKShadowCpnt* component = static_cast<const CKShadowCpnt*>(entry->m_pShadowCpnt);
    CKSrvShadow::CKShadowDataWaiting* next = entry->m_pNext;
    if (static_cast<const CSGLeaf*>(entry->m_pShadowedLeaf)->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter &&
        component->m_bAlwaysVisible == 0) {
        return next;
    }
    if (!(component->m_fShadowDistanceMax > distance)) return next;
    CKSrvShadow::CKShadowDataWaiting* head = list;
    if (head != nullptr) {
        if (entry == head) {
            list = next;
        } else {
            for (CKSrvShadow::CKShadowDataWaiting* previous = head; previous->m_pNext != nullptr; previous = previous->m_pNext) {
                if (previous->m_pNext != entry) continue;
                previous->m_pNext = entry->m_pNext;
                break;
            }
        }
    }
    entry->m_pNext = service->m_lShadowWaitingUnused;
    service->m_lShadowWaitingUnused = entry;
    service->RegisterCaster(entry->m_pShadowCpnt, static_cast<IKSerializable*>(entry->m_pShadowedLeaf), entry->m_pShadowGround,
                            1, nullptr, 0);  // 0x1fb6f8
    return next;
}

// UpdateCKSrvShadow's queueing of the drawn spots past the limit (from `spot` on): each gets a waiting slot (while there are
// free ones) with its caster, at the head of `waitingList`; the spots stay in their drawing list.
void QueueOverflow(CKSrvShadow* service, CKSrvShadow::CKShadowDataSpot* spot, CKSrvShadow::CKShadowDataWaiting*& waitingList) {
    for (; spot != nullptr; spot = spot->m_pNext) {
        CKSrvShadow::CKShadowDataWaiting* waiting = service->m_lShadowWaitingUnused;
        if (waiting == nullptr) continue;
        CKSrvShadow::CKShadowDataWaiting* following = waiting->m_pNext;
        if (following != nullptr) {
            waiting->m_pNext = nullptr;
            service->m_lShadowWaitingUnused = following;
        } else {
            service->m_lShadowWaitingUnused = nullptr;
        }
        waiting->m_pShadowCpnt = spot->m_pShadowCpnt;
        waiting->m_pShadowedLeaf = spot->m_pShadowedLeaf;
        waiting->m_pShadowGround = spot->m_pShadowGround;
        waiting->m_pNext = waitingList;
        waitingList = waiting;
    }
}

// The PTank array slots of the next drawn spot.
struct SpotSlots {
    uint8_t* matrices;  // 0x40 bytes per spot (an RwMatrix)
    uint8_t* uvs;       // 0x10 (four floats)
    uint8_t* colors;    // 4 (RwRGBA)
};

// UpdateCKSrvShadow's update of one drawing list: every spot updated (vt+0x10) until `drawn` reaches the service's spot count;
// a spot drawn (0) takes the next slots, one that stops drawing (1) is demoted if it was drawn, one that asks (2) is
// unregistered. The spots past the limit are queued as waiting again (`waitingList`).
void UpdateDrawingList(CKSrvShadow* service, CKSrvShadow::CKShadowDataSpot* spot, CKSrvShadow::CKShadowDataWaiting*& waitingList,
                       IKTime* clock, SpotSlots* slots, uint32_t* drawn) {
    if (spot == nullptr) return;
    if (!(service->m_ui32NbShadowSpot > *drawn)) {
        QueueOverflow(service, spot, waitingList);
        return;
    }
    for (;;) {
        const int32_t result = spot->m_pShadow->Update(clock, reinterpret_cast<CMatrix34*>(slots->matrices),
                                                       reinterpret_cast<float*>(slots->uvs), slots->colors);  // vt+0x10
        CKSrvShadow::CKShadowDataSpot* next = spot->m_pNext;
        if (result == 1) {
            CKShadowSpot* shadow = spot->m_pShadow;
            if (shadow->m_bDrawn != 0) {
                shadow->m_bDrawn = 0;
                service->DemoteCasterToPending(spot->m_pShadow->m_pLeaf, spot->m_pShadowCpnt);  // 0x1fbb38
            }
        } else if (result == 2) {
            service->UnregisterCaster(static_cast<CKShadowGround*>(spot->m_pShadow->m_pGround), spot->m_pShadowCpnt);  // 0x1fd6f0
        } else if (result == 0) {
            slots->matrices += 0x40;
            slots->uvs += 0x10;
            slots->colors += 4;
            *drawn = *drawn + 1;
            spot->m_pShadow->m_bDrawn = 1;
        }
        if (next == nullptr) return;
        spot = next;
        if (!(service->m_ui32NbShadowSpot > *drawn)) {
            QueueOverflow(service, spot, waitingList);
            return;
        }
    }
}
}  // namespace

// 0x001fdd68 UpdateCKSrvShadow
void CKSrvShadow::Update(IKTime* clock) {
    if (clock->m_eCurrentState != 0) return;
    const CVector3& focus = FocusPoint();
    CParticleGeometry* geometry = static_cast<CParticleGeometry*>(m_pShadowParticuleGeometry);
    RpPTankLockStruct lock;
    SpotSlots slots;
    slots.matrices = RpPTankAtomicLock(geometry->m_pRpAtomic, &lock, 8, 0x40000000) != 0 ? lock.data : nullptr;  // rpPTANKDFLAGMATRIX
    slots.uvs = RpPTankAtomicLock(geometry->m_pRpAtomic, &lock, 0x80, 0x40000000) != 0 ? lock.data : nullptr;  // VTX2TEXCOORDS
    slots.colors = RpPTankAtomicLock(geometry->m_pRpAtomic, &lock, 2, 0x40000000) != 0 ? lock.data : nullptr;  // COLOR

    // A full set of spots: each high-priority waiting caster drawn this frame and near enough takes the spot of the
    // low-priority drawn caster at the same place in its list.
    if (m_lShadowWaitingHighPriority != nullptr && m_lDrawingShadowLowPriority != nullptr && m_lShadowUnused == nullptr) {
        CKShadowDataWaiting* waiting = m_lShadowWaitingHighPriority;
        CKShadowDataSpot* drawing = m_lDrawingShadowLowPriority;
        for (;;) {
            const float distance = FocusDistance(waiting->m_pShadowedLeaf, focus);
            CKShadowDataSpot* next = drawing->m_pNext;
            if (static_cast<const CSGLeaf*>(waiting->m_pShadowedLeaf)->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter &&
                static_cast<const CKShadowCpnt*>(waiting->m_pShadowCpnt)->m_fShadowDistanceMax > distance) {
                DemoteCasterToPending(drawing->m_pShadow->m_pLeaf, drawing->m_pShadowCpnt);  // 0x1fbb38
            }
            drawing = next;
            waiting = waiting->m_pNext;
            if (waiting == nullptr || drawing == nullptr) break;
        }
    }

    // The waiting casters that are near (high, then low priority) registered again; the count is read after each.
    if (m_ui32NbShadowSpot != 0) {
        bool lowPriority = true;
        for (CKShadowDataWaiting* waiting = m_lShadowWaitingHighPriority; waiting != nullptr;) {
            waiting = PromoteIfNear(this, m_lShadowWaitingHighPriority, waiting, focus);
            if (m_ui32NbShadowSpot == 0) {
                lowPriority = false;
                break;
            }
        }
        if (lowPriority) {
            for (CKShadowDataWaiting* waiting = m_lShadowWaitingLowPriority; waiting != nullptr;) {
                waiting = PromoteIfNear(this, m_lShadowWaitingLowPriority, waiting, focus);
                if (m_ui32NbShadowSpot == 0) break;
            }
        }
    }

    uint32_t drawn = 0;
    UpdateDrawingList(this, m_lDrawingShadowHighPriority, m_lShadowWaitingHighPriority, clock, &slots, &drawn);
    UpdateDrawingList(this, m_lDrawingShadowLowPriority, m_lShadowWaitingLowPriority, clock, &slots, &drawn);

    // RpPTankAtomicSetActiveParticlesCount (the changed-count flag 0x800000, the count), then the unlock (vt+0x8c).
    geometry = static_cast<CParticleGeometry*>(m_pShadowParticuleGeometry);
    geometry->m_pRpAtomic->ptank->flags40 |= 0x800000u;
    geometry->m_pRpAtomic->ptank->numPrt = drawn;
    static_cast<CParticleGeometry*>(m_pShadowParticuleGeometry)->UnlockPTank();
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pShadowSpotNode);
    if (drawn == 0) {
        node->m_sgProperties = (node->m_sgProperties & ~4u) | 4u;
    } else {
        node->m_sgProperties &= ~4u;
    }
}

// 0x001fcc58 CKSrvShadow_Stop: every shadow being drawn (high, then low priority) and every waiting one
// (high, then low) given back to its unused list.
void CKSrvShadow::Stop() {
    ReleaseDrawing(m_lDrawingShadowHighPriority, m_lShadowUnused);
    ReleaseDrawing(m_lDrawingShadowLowPriority, m_lShadowUnused);
    ReleaseWaiting(m_lShadowWaitingHighPriority, m_lShadowWaitingUnused);
    ReleaseWaiting(m_lShadowWaitingLowPriority, m_lShadowWaitingUnused);
}

// 0x001fd068 CKSrvShadow_Destroy (the level unload): IKService's part (empty) first; every drawn spot of the two
// priority lists hidden and given back, every spot's Destroy (a byte counter, as the original), the spot, data-spot and
// waiting arrays deleted, the waiting lists given back and cleared, the shadow texture destroyed (the pointer is kept:
// BUG(original), as the original), the texture coordinates deleted; with the sector textures (+0x15) every present
// entry's node destroyed (vt+0x10) and the entry vector freed.
void CKSrvShadow::Destroy() {
    IKService::Destroy();
    CKShadowDataSpot** const drawing[2] = {&m_lDrawingShadowHighPriority, &m_lDrawingShadowLowPriority};
    for (CKShadowDataSpot** list : drawing) {
        while (*list != nullptr) {
            CKShadowDataSpot* node = *list;
            node->m_pShadow->SetShadowHided(1);
            *list = node->m_pNext;
            node->m_pNext = m_lShadowUnused;
            m_lShadowUnused = node;
        }
    }
    if (m_ui32NbShadowSpot != 0) {
        uint8_t i = 0;
        do {
            m_aShadowSpot[i].Destroy();
            ++i;
        } while (i < m_ui32NbShadowSpot);
    }
    m_ui32NbShadowSpot = 0;
    if (m_aShadowSpot != nullptr) {
        delete[] m_aShadowSpot;  // the destructors (vt+0x00) last to first, then OperatorDeleteArray
        m_aShadowSpot = nullptr;
    }
    if (m_aShadowDataSpot != nullptr) {
        delete[] m_aShadowDataSpot;
        m_aShadowDataSpot = nullptr;
    }
    m_lShadowUnused = nullptr;
    CKShadowDataWaiting** const waiting[2] = {&m_lShadowWaitingHighPriority, &m_lShadowWaitingLowPriority};
    for (CKShadowDataWaiting** list : waiting) {
        while (*list != nullptr) {
            CKShadowDataWaiting* node = *list;
            *list = node->m_pNext;
            node->m_pNext = m_lShadowWaitingUnused;
            m_lShadowWaitingUnused = node;
        }
    }
    if (m_aShadowWaiting != nullptr) delete[] m_aShadowWaiting;
    m_aShadowWaiting = nullptr;
    m_lShadowWaitingHighPriority = nullptr;
    m_lShadowWaitingLowPriority = nullptr;
    m_lShadowWaitingUnused = nullptr;
    if (m_pShadowTexture != nullptr) RwTextureDestroy(static_cast<RwTexture*>(m_pShadowTexture));
    if (m_aTextureCoord != nullptr) {
        delete[] m_aTextureCoord;
        m_aTextureCoord = nullptr;
    }
    if (m_unk15 != 0) {
        Entry* block = m_unk30.m_pBlock;
        uint32_t count = m_unk30.m_ui32NbUsedElt;
        if (count != 0) {
            uint8_t i = 0;
            do {
                if (block[i].m_unk24 != 0 && block[i].m_unk28 != nullptr) {
                    block[i].m_unk28->Destroy();  // vt+0x10
                    count = m_unk30.m_ui32NbUsedElt;
                    block = m_unk30.m_pBlock;
                }
                ++i;
            } while (i < count);
        }
        m_unk30.m_ui32NbUsedElt = 0;
        if (block != nullptr) {
            Mem_FreeAligned16(block);
            m_unk30.m_pBlock = nullptr;
        }
        m_unk30.m_ui32NbUsedElt = 0;
        m_unk30.m_pBlock = nullptr;
    }
}

// 0x001fe668 CKSrvShadow_Destructor (0x1fe6f8 _Destructor_2 the same, 0x1fd658 _DeletingDestructor then the delete):
// the global cleared, the entry vector's block freed, its length and block cleared.
CKSrvShadow::~CKSrvShadow() {
    g_pSrvShadow = nullptr;
    if (m_unk30.m_pBlock != nullptr) Mem_FreeAligned16(m_unk30.m_pBlock);
    m_unk30.m_ui32NbUsedElt = 0;
    m_unk30.m_pBlock = nullptr;
}

// 0x001faa60 CKSrvShadow_MarkCasterGeometryRecursive_maybe
void CKSrvShadow::MarkCasterGeometry(IKSerializable* node, int32_t recurse) {
    if ((node->IsKindOfClass(0xcb) & 0xff) != 0) {
        CGeometry* geometry = static_cast<CGeometry*>(static_cast<CNode*>(node)->m_lGeometryList);
        while (geometry != nullptr) {
            const uint32_t materialType = (static_cast<CMaterial*>(geometry->m_pMaterial)->m_baProperties >> 3) & 0xf;
            if (materialType - 7 > 2) geometry->m_BitProperties = (geometry->m_BitProperties & 0xffffffc0u) | 0x2b;
            geometry = geometry->m_pNext;
        }
    }
    if (recurse != 0 && (node->IsKindOfClass(0x24b) & 0xff) != 0) {
        for (CSGLeaf* child = static_cast<CSGBranch*>(node)->m_lChildList; child != nullptr; child = child->m_pNext) {
            MarkCasterGeometry(child, 1);
        }
    }
}

// ==== the per-sector shadow textures (C2.4 step 7) ======================================================================
namespace {
// 0x000bb398 GetMaterialTexture_maybe: the RenderWare material's texture unless the material's property bit 12 is set.
RwTexture* GetMaterialTexture(const CMaterial* material) {
    return (material->m_baProperties & 0x1000) == 0 ? material->m_pRpMaterial->texture : nullptr;
}
// The entry's node's first geometry's material (entry +0x28 -> +0x1c -> +0x24); null without a geometry.
const CMaterial* EntryMaterial(const CKSrvShadow::Entry& entry) {
    const CGeometry* geometry = static_cast<const CGeometry*>(static_cast<const CNode*>(entry.m_unk28)->m_lGeometryList);
    return geometry != nullptr ? static_cast<const CMaterial*>(geometry->m_pMaterial) : nullptr;
}
const CKSrvShadow::Entry* EntryOf(const CKSrvShadow* service, uint32_t index) {
    if (index >= service->m_unk30.m_ui32NbUsedElt) return nullptr;
    const CKSrvShadow::Entry* entry = &service->m_unk30.m_pBlock[index];
    return entry->m_unk24 != 0 ? entry : nullptr;
}
}  // namespace

// 0x001faa00 CKSrvShadow_EntryHasTexture_maybe
uint32_t CKSrvShadow::EntryHasTexture(uint32_t index) const {
    const Entry* entry = EntryOf(this, index);
    return entry != nullptr && entry->m_unk00 != nullptr ? 1u : 0u;
}

// 0x001fb060 / 0x001fb028 / 0x001faff0 / 0x001fafb8: the entry's floats at +0x10, +0x14, +0x18, +0x1c as the words they are read as.
namespace {
float WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof value);
    return value;
}
}  // namespace
float CKSrvShadow::GetEntryFloat10(uint32_t index) const {
    const Entry* entry = EntryOf(this, index);
    return entry != nullptr ? WordAsFloat(entry->m_unk10) : 0.0f;
}
float CKSrvShadow::GetEntryFloat14(uint32_t index) const {
    const Entry* entry = EntryOf(this, index);
    return entry != nullptr ? WordAsFloat(entry->m_unk14) : 0.0f;
}
float CKSrvShadow::GetEntryFloat18(uint32_t index) const {
    const Entry* entry = EntryOf(this, index);
    return entry != nullptr ? WordAsFloat(entry->m_unk18) : 0.0f;
}
float CKSrvShadow::GetEntryFloat1C(uint32_t index) const {
    const Entry* entry = EntryOf(this, index);
    return entry != nullptr ? WordAsFloat(entry->m_unk1c) : 0.0f;
}

// 0x001fb098 CKSrvShadow_GetEntryOrigin_maybe
const float* CKSrvShadow::GetEntryOrigin(uint32_t index) const {
    static const float kNullVector[3] = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
    const Entry* entry = EntryOf(this, index);
    return entry != nullptr ? &entry->m_unk04.x : kNullVector;
}

// 0x001fb3b8 CKSrvShadow_GetEntryTexture_maybe
void* CKSrvShadow::GetEntryTexture(uint32_t index) {
    if (index >= m_unk30.m_ui32NbUsedElt) return nullptr;
    Entry* entry = &m_unk30.m_pBlock[index];
    if (entry->m_unk24 == 0) return nullptr;
    if (entry->m_unk00 == nullptr && static_cast<CNode*>(entry->m_unk28)->m_lGeometryList != nullptr) {
        entry->m_unk00 = GetMaterialTexture(EntryMaterial(*entry));
    }
    return entry->m_unk00;
}

// 0x001fb468 CKSrvShadow_RefreshEntryTextures_maybe
void CKSrvShadow::RefreshEntryTextures() {
    for (uint32_t i = 0; i < m_unk30.m_ui32NbUsedElt; ++i) {
        Entry* entry = &m_unk30.m_pBlock[i];
        if (entry->m_unk28 == nullptr || entry->m_unk24 == 0) continue;
        if (static_cast<CNode*>(entry->m_unk28)->m_lGeometryList != nullptr) entry->m_unk00 = GetMaterialTexture(EntryMaterial(*entry));
    }
}

// 0x001fb988 CKSrvShadow_IsShadowModeEnabled_maybe
uint32_t CKSrvShadow::IsShadowModeEnabled(int32_t mode) const {
    const uint32_t bits = static_cast<uint32_t>(m_unk68);
    if (mode == 0) return bits & 1;
    if (mode == 1) return (bits >> 1) & 1;
    if (mode == 2) return (bits >> 2) & 1;
    return 0;
}

// 0x001fb2d0 CKSrvShadow_PostLoad (after KStub_Return1_1a5b0)
int32_t CKSrvShadow::PostLoad(int32_t /*type*/) {
    if (m_unk15 != 0) RefreshEntryTexturesOfPresent();
    m_ui8ShadowSpotUsed = 0;
    m_unk10 = 99;
    m_unk0c = 0;
    return 1;
}

// PostLoad's loop (the same as RefreshEntryTextures without the node-has-geometry check on the texture, which GetMaterialTexture
// needs: the entry's node must have a geometry).
void CKSrvShadow::RefreshEntryTexturesOfPresent() {
    for (uint32_t i = 0; i < m_unk30.m_ui32NbUsedElt; ++i) {
        Entry* entry = &m_unk30.m_pBlock[i];
        if (entry->m_unk24 == 0) continue;
        if (static_cast<CNode*>(entry->m_unk28)->m_lGeometryList != nullptr) entry->m_unk00 = GetMaterialTexture(EntryMaterial(*entry));
    }
}

// 0x001fb660 CKSrvShadow_SectorLoaded (the bound is unsigned: sector <= count - 1).
void CKSrvShadow::SectorLoaded(int32_t sector) {
    if (m_unk15 == 0 || m_unk30.m_pBlock == nullptr) return;
    if (static_cast<uint32_t>(sector) > m_unk30.m_ui32NbUsedElt - 1u) return;
    Entry* entry = &m_unk30.m_pBlock[sector];
    if (entry->m_unk24 == 0) return;
    if (static_cast<CNode*>(entry->m_unk28)->m_lGeometryList == nullptr) {
        entry->m_unk00 = nullptr;
    } else {
        entry->m_unk00 = GetMaterialTexture(EntryMaterial(*entry));
    }
}

// 0x001fb9e0 CKSrvShadow_UpdateActiveSectorShadowTexture_maybe
void CKSrvShadow::UpdateActiveSectorWorld() {
    if (m_unk15 == 0 || m_unk10 == m_unk0c) return;
    const uint32_t sector = m_unk0c;
    if (sector < m_unk30.m_ui32NbUsedElt) {
        Entry* entry = &m_unk30.m_pBlock[sector];
        if (entry->m_unk24 != 0 && entry->m_unk00 != nullptr) {
            if (static_cast<CNode*>(entry->m_unk28)->m_lGeometryList == nullptr) {
                entry->m_unk00 = nullptr;
            } else {
                entry->m_unk00 = GetMaterialTexture(EntryMaterial(*entry));
                RwTexture* texture = static_cast<RwTexture*>(entry->m_unk00);
                texture->filterAddressing = (texture->filterAddressing & 0xffff00ffu) | 0x3300u;  // clamp / clamp
            }
            if (entry->m_unk00 != nullptr) {
                BindTextureOnUnit(static_cast<RwTexture*>(entry->m_unk00), 5);
                m_unk10 = m_unk0c;
                return;
            }
        }
    }
    BindTextureOnUnit(nullptr, 5);
    m_unk10 = 99;
}
