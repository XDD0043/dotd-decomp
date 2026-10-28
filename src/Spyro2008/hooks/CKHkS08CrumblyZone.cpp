// CKHkS08CrumblyZone.cpp - reconstructed original translation unit 0x4140f0-0x4150b8 (GAME_TOC1, main_toc1), 24 functions, 24 live.
// Primary class: CKHkS08CrumblyZone  key 0x2ec2  category Hook  size 0x1cc  vtable 0xb25ae8
// Other owners: CKHkCrumblyZone (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4140f0  CKHkS08CrumblyZone_Delete
//   [ ] 0x414140  RegisterCKHkS08CrumblyZoneClass
//   [ ] 0x4141b8  _GLOBAL__I_4141b8
//   [ ] 0x4141c8  CKHkS08CrumblyZone_vf100
//   [ ] 0x414230  CKHkS08CrumblyZone_MessageProc
//   [ ] 0x414288  CKHkS08CrumblyZone_OnDeactivate
//   [x] 0x4142b0  CKHkS08CrumblyZone_OnActivate
//   [ ] 0x4142e8  CKHkS08CrumblyZone_Restart
//   [x] 0x414320  CKHkS08CrumblyZone_Start
//   [ ] 0x414358  CKHkS08CrumblyZone_Update
//   [ ] 0x414380  CKHkS08CrumblyZone_vfF4
//   [ ] 0x4143a8  CKHkS08CrumblyZone_vfF0
//   [x] 0x4143d0  CKHkS08CrumblyZone_PostLoad
//   [ ] 0x4143f8  CKHkS08CrumblyZone_Save
//   [ ] 0x414420  CKHkS08CrumblyZone_RecursiveRegistration
//   [x] 0x414448  CKHkS08CrumblyZone_DeleteArray
//   [x] 0x4144e8  CKHkS08CrumblyZone_CreateArray
//   [ ] 0x414638  CKHkS08CrumblyZone_UpdateHeroWeight_maybe
//   [ ] 0x414808  CKHkCrumblyZone_RestoreIfDestroyed_maybe
//   [ ] 0x414840  CKHkCrumblyZone_CrumbleIfIntact_maybe
//   [ ] 0x414880  CKHkS08CrumblyZone_OnHit_maybe
//   [ ] 0x414e00  CKHkCrumblyZone_TryTriggerCollapse_maybe
//   [x] 0x414e60  CKHkS08CrumblyZone_Create
//   [x] 0x414f28  CKHkS08CrumblyZone_Load
//
//   [ ] 0x9c2778  CKHkS08CrumblyZone_IsKindOfClass  [inline]
//   [ ] 0x9c27d8  CKHkS08CrumblyZone_GetClassType  [inline]
//   [ ] 0x9c27e0  CKHkS08CrumblyZone_GetClassID  [inline]
//   [ ] 0x9c27e8  CKHkS08CrumblyZone_DeletingDestructor  [inline]
//   [ ] 0x9c29a8  CKHkS08CrumblyZone_Destructor  [inline]
#include "Spyro2008/hooks/CKHkS08CrumblyZone.h"
#include "Spyro2008/groups/C22SpyroShims.h"

#include "k2000/io/IKFile.h"
#include "k2000/misc/Engine.h"

// 0x004143d0 CKHkS08CrumblyZone_PostLoad: CKHkCrumblyZone_PostLoad (0x406080) only.
int32_t CKHkS08CrumblyZone::PostLoad(int32_t type) { return CKHkCrumblyZone::PostLoad(type); }

// 0x00414f28 CKHkS08CrumblyZone_Load
int32_t CKHkS08CrumblyZone::Load(IKFile* file, int32_t type) {
    CKHkCrumblyZone::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk1BC);
    ReadU8(file, &m_unk1C1);
    ReadU8(file, &m_unk1C2);
    ReadU32LE(file, &m_unk1C4);
    ReadU8(file, &m_unk1C0);
    return 1;
}

namespace {
// 0x00406de0 CKHkCrumblyZone_Start (k2000/hooks/CKHkCrumblyZone.cpp, family hooks; local copy until that
// port lands, see the C2.2 spyro report). The zone goes back to its initial state: the volumes off, the
// "current" flag bits taken from their saved twins.
void CrumblyZoneStart(CKHkCrumblyZone* zone) {
    zone->m_bitArray = zone->m_bitArray & 0xfffff9ffu;  // bits 9, 10
    for (uint32_t i = 0; i < zone->m_vUnkA4.m_ui32NbUsedElt; ++i) {
        c22spyro::CollisionDisableVolume(static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision),
                                         static_cast<IKBoundingVolume*>(zone->m_vUnkA4.m_pBlock[i].m_pUnk0));
    }
    uint32_t w = zone->m_unk154;
    w = (w & ~(1u << 19)) | (((w >> 22) & 1u) << 19);
    w = (w & ~(1u << 20)) | (((w >> 23) & 1u) << 20);
    w = (w & ~1u) | ((w >> 24) & 1u);  // the first byte of the word, its lowest bit
    w = (w & ~2u) | (((w >> 25) & 1u) << 1);
    zone->m_unk154 = w;
    uint32_t f = zone->m_bitArray;
    f = (f & ~(1u << 13)) | (((f >> 15) & 1u) << 13);
    f = (f & ~(1u << 14)) | (((f >> 16) & 1u) << 14);
    zone->m_bitArray = f;
    zone->m_unk144[1] = zone->m_unk150;
    zone->m_unk144[0] = zone->m_unk14C;
    zone->m_unk154 = zone->m_unk154 & 0xeffffff7u;
    zone->m_unk120[8] = 1;  // the byte at +0x128
    for (int i = 0; i < 8; ++i) zone->m_unk120[i] = 0;  // the words at +0x120 / +0x124
    // CKHkActorBase_d82_maybe_ResetRuntime 0x3f6e48: empty.
}
}  // namespace

// 0x00414320 CKHkS08CrumblyZone_Start
void CKHkS08CrumblyZone::Start() {
    CrumblyZoneStart(this);
    m_unk1C8 = 0;
}

// 0x004142b0 CKHkS08CrumblyZone_OnActivate: the base's, then +0x1c8 = 0.
void CKHkS08CrumblyZone::VfA0() {
    CKHkCrumblyZone::VfA0();
    m_unk1C8 = 0;
}
