// CKProjectileTypeScrap.cpp - reconstructed original translation unit 0x5929d8-0x596240 (GAME_TOC2, main_toc2), 26 functions, 26 live.
// Primary class: CKProjectileTypeScrap  key 0x134c  category Logic  size ?  vtable 0xb2e3c8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x5929d8  RegisterCKProjectileTypeScrapClass
//   [ ] 0x592a50  _GLOBAL__I_592a50
//   [ ] 0x592a60  CKProjectileTypeScrap_PlayInstanceSound_maybe
//   [ ] 0x592b08  CKProjectileTypeScrap_UpdateRollAxis_maybe
//   [ ] 0x592c20  CKProjectileTypeScrap_ProbeGround_maybe
//   [ ] 0x592cc0  CKProjectileTypeScrap_CollideAndStop_maybe
//   [x] 0x592fd0  CKProjectileTypeScrap_DeleteArray
//   [x] 0x593078  CKProjectileTypeScrap_Create
//   [ ] 0x5930d0  CKProjectileTypeScrap_IsDead
//   [ ] 0x593120  CKProjectileTypeScrap_UpdateMotion
//   [ ] 0x593258  CKProjectileTypeScrap_KillInstance
//   [x] 0x593708  CKProjectileTypeScrap_CreateArray
//   [ ] 0x5937c8  CKProjectileTypeScrap_OnDeath
//   [ ] 0x593c78  CKProjectileTypeScrap_UpdateOrientation
//   [ ] 0x5941a0  CKProjectileTypeScrap_TriggerImpactExplosion_maybe
//   [ ] 0x5944d8  CKProjectileTypeScrap_CollideAndBounce_maybe
//   [ ] 0x5947e0  CKProjectileTypeScrap_UpdateCollision
//   [ ] 0x594928  CKProjectileTypeScrap_LaunchPiece
//   [ ] 0x595a80  CKProjectileTypeScrap_LaunchEx
//   [ ] 0x595b60  CKProjectileTypeScrap_Launch
//   [ ] 0x595be0  CKProjectileTypeScrap_Destroy
//   [ ] 0x595c08  CKProjectileTypeScrap_MessageProc
//   [ ] 0x595da0  CKProjectileTypeScrap_Save
//   [ ] 0x595da8  CKProjectileTypeScrap_PostLoad
//   [ ] 0x595db0  CKProjectileTypeScrap_RecursiveRegistration
//   [x] 0x595e28  CKProjectileTypeScrap_Load
//
//   [ ] 0x9cb608  CKProjectileTypeScrap_IsKindOfClass  [inline]
//   [ ] 0x9cb630  CKProjectileTypeScrap_GetClassType  [inline]
//   [ ] 0x9cb638  CKProjectileTypeScrap_GetClassID  [inline]
//   [ ] 0x9cb640  CKProjectileTypeScrap_ProcessDamageContacts  [inline]
//   [ ] 0x9cb648  CKProjectileTypeScrap_Destructor  [inline]
//   [ ] 0x9cb668  CKProjectileTypeScrap_DeletingDestructor  [inline]
#include "k2000/logic/CKProjectileTypeScrap.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/scenegraph/CSGLeaf.h"

// 0x00595e28 CKProjectileTypeScrap_Load: IKProjectileType's data, then (level data only) a word, per
// projectile two references, and two references (9 + 8 * count + 8 bytes).
int32_t CKProjectileTypeScrap::Load(IKFile* file, int32_t type) {
    IKProjectileType::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk24);
    m_GrdContDatasIn.m_fDeltaMax = 1.0f;      // TOC1 -0x6ea4
    m_GrdContDatasIn.m_fObjectHeight = 2.0f;  // TOC1 -0x6ea0
    const uint32_t count = m_ui8MaxProjectiles;
    // PS3: count << 2 and (count * PS3 record size) masked to 16 bits (rlwinm 0,16,27); a byte count never
    // reaches the mask, so native sizes are used.
    Projectile** list = static_cast<Projectile**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Projectile*))));
    Projectile* projectiles = static_cast<Projectile*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Projectile))));
    m_aProjectiles = projectiles;
    m_apProjectileList = reinterpret_cast<void**>(list);
    for (uint32_t i = 0; i < m_ui8MaxProjectiles; ++i) {
        Projectile* p = &projectiles[i];
        list[i] = p;
        IKFile_ReadRef(file, &p->m_pNode);
        IKFile_ReadRef(file, &p->m_unk10);
        p->m_unk8c = 0;
        p->m_unk04 = 0;
        // BUG(original): no null test (unlike CKProjectileTypeBallisticPFX_Load): a null node reference
        // writes through address 0x10. Every LVL010 sample has a node.
        p->m_pNode->m_sgProperties = (p->m_pNode->m_sgProperties & ~0x4u) | 0x4u;
        p->m_unk14 = {0.0f, 0.0f, 0.0f};  // the vector at 0x00c50d64
        p->m_unk20 = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
        p->m_unk2c = {0.0f, 0.0f, 0.0f};  // 0x00c50d4c (also (0, 0, 0))
        p->m_unk38 = 0;
        p->m_unk3c = {0.0f, 0.0f, 0.0f};  // 0x00c50d34 (also (0, 0, 0))
        p->m_GrdContDatasInOut.m_i32FaceIndex = -1;
        p->m_GrdContDatasInOut.m_eContactStatus = 3;
        p->m_GrdContDatasInOut.m_pGround = nullptr;
        p->m_GrdContDatasInOut.m_ui8SectorNumber = 0;
        p->m_ui32Index = i;
        p->m_unk58 = 0;
        p->m_unk48 = 0;
        p->m_unk4c = 1.0f;
        p->m_unk88 = 0;
        p->m_unk50 = 0;
        p->m_unk54 = 1.0f;
    }
    IKFile_ReadRef(file, &m_unk28);
    IKFile_ReadRef(file, &m_unk2c);
    return 1;
}
