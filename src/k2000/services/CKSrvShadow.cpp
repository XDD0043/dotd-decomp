// CKSrvShadow.cpp - reconstructed original translation unit 0x1fa938-0x1fe788 (GAME_TOC1, main_toc1), 55 functions, 39 live.
// Primary class: CKSrvShadow  key 0x301  category Service  size 0x6c  vtable 0xb1ecb8
// Other owners: ShadowAtlas (3), KObject (1), UpdateActiveSectorWorld (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1fa938  CKSrvShadow_Delete
//   [ ] 0x1fa988  CKSrvShadow_Construct  [dead]
//   [ ] 0x1fa9f0  CKSrvShadow_RecursiveRegistration
//   [ ] 0x1fa9f8  CKSrvShadow_Save
//   [x] 0x1faa00  CKSrvShadow_EntryHasTexture_maybe
//   [ ] 0x1faa50  CKSrvShadow_Pause
//   [ ] 0x1faa58  CKSrvShadow_Resume
//   [x] 0x1faa60  CKSrvShadow_MarkCasterGeometryRecursive_maybe
//   [ ] 0x1fabd0  CKSrvShadow_RemovePendingNodeByCaster_maybe  [dead]
//   [ ] 0x1fac78  CKSrvShadow_FindPendingNodeByCaster_maybe  [dead]
//   [ ] 0x1facc8  ShadowAtlas_GetUVMin_maybe
//   [ ] 0x1face0  ShadowAtlas_GetUVMax_maybe
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
//   [ ] 0x1faf00  CKSrvShadow_Start
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
//   [ ] 0x1fb658  CKSrvShadow_SectorUnload
//   [ ] 0x1fb660  CKSrvShadow_SectorLoaded
//   [x] 0x1fb6f8  CKSrvShadow_RegisterCaster
//   [ ] 0x1fb968  CKSrvShadow_RegisterPendingNode_maybe  [dead]
//   [x] 0x1fb988  CKSrvShadow_IsShadowModeEnabled_maybe
//   [x] 0x1fb9e0  CKSrvShadow_UpdateActiveSectorShadowTexture_maybe
//   [ ] 0x1fbb38  CKSrvShadow_DemoteCasterToPending
//   [x] 0x1fbe98  CKSrvShadow_Create
//   [x] 0x1fbf40  CKSrvShadow_CreateArray
//   [x] 0x1fc060  CKSrvShadow_Load
//   [ ] 0x1fcb10  CKSrvShadow_RemoveActiveNodeByCaster_maybe  [dead]
//   [x] 0x1fcc58  CKSrvShadow_Stop
//   [ ] 0x1fd068  CKSrvShadow_Destroy
//   [ ] 0x1fd658  CKSrvShadow_DeletingDestructor
//   [x] 0x1fd6f0  CKSrvShadow_UnregisterCaster
//   [ ] 0x1fdd68  UpdateCKSrvShadow
//   [ ] 0x1fe668  CKSrvShadow_Destructor
//   [ ] 0x1fe6f8  CKSrvShadow_Destructor_2
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
    spot->m_pShadow->m_unk4c = (spot->m_pShadow->m_unk4c & 0x00ffffffu) | 0x01000000u;  // the byte at +0x4c = 1
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
bool WaitingCasterIsNear(const CKSrvShadow::CKShadowDataWaiting* waiting) {
    const CSGLeaf* leaf = static_cast<const CSGLeaf*>(waiting->m_pShadowedLeaf);
    if (leaf->m_ui16LastRenderedFrame != g_ui16RenderFrameCounter) return false;
    const CKShadowCpnt* component = static_cast<const CKShadowCpnt*>(waiting->m_pShadowCpnt);
    const CKSrvCamera* camera = static_cast<const CKSrvCamera*>(g_pEngine->m_srvCamera);
    const RwMatrix* pose = RwFrameGetLTM(const_cast<RwFrame*>(leaf->m_pRwFrame));
    const float dy = pose->pos.y - camera->m_v3RealPos.y;
    const float dx = pose->pos.x - camera->m_v3RealPos.x;
    const float dz = pose->pos.z - camera->m_v3RealPos.z;
    const double distance = static_cast<float>(std::sqrt(static_cast<double>(dz * dz + dx * dx + dy * dy)));  // Math_Sqrtf
    return distance < static_cast<double>(component->m_fShadowDistanceMax) || component->m_bAlwaysVisible != 0;
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
// STUB(C2.7): the spots' per-frame update (UpdateCKSrvShadow 0x1fdd68 with CKShadowSpot_Update 0x1ff2c0), the other half of the
// bookkeeping (promoting waiting casters, demoting out-of-range ones: CKSrvShadow_DemoteCasterToPending 0x1fbb38, only
// called from there) is with the shadow spots' draw: the spots are particles (the shadow CParticleGeometry's PTank arrays,
// +0x24, drawn by the shared PTank pipeline); the ground probe it uses (CKSrvCollision GroundProbePoints) is ported (step 3).
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

// Inlined in CKSrvShadow_Load's new[] loop (0x1fca20): the IKShadow part, then the spot's defaults.
CKShadowSpot::CKShadowSpot() {
    m_pNext = nullptr;
    m_pShadowCpnt = nullptr;
    m_unk5c = 8;
    m_unk58 = 1;
    m_unk88 = 0;
    m_unk60 = 0;
    m_unk64 = -1;
    m_unk74 = 3;
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

// 0x001fcc58 CKSrvShadow_Stop: every shadow being drawn (high, then low priority) and every waiting one
// (high, then low) given back to its unused list.
void CKSrvShadow::Stop() {
    ReleaseDrawing(m_lDrawingShadowHighPriority, m_lShadowUnused);
    ReleaseDrawing(m_lDrawingShadowLowPriority, m_lShadowUnused);
    ReleaseWaiting(m_lShadowWaitingHighPriority, m_lShadowWaitingUnused);
    ReleaseWaiting(m_lShadowWaitingLowPriority, m_lShadowWaitingUnused);
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
