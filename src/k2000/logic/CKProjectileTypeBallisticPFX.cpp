// CKProjectileTypeBallisticPFX.cpp - reconstructed original translation unit 0x586258-0x58e9c0 (GAME_TOC2, main_toc2), 36 functions, 33 live.
// Primary class: CKProjectileTypeBallisticPFX  key 0x140c  category Logic  size ?  vtable 0xb2e208
// Other owners: CKProjectileType (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x586258  CKProjectileTypeBallisticPFX_AddFxEmitPointAndStart_maybe  [dead]
//   [ ] 0x586338  CKProjectileTypeBallisticPFX_vfA8
//   [ ] 0x586340  CKProjectileType_UpdateInstanceTrailSegment_maybe
//   [ ] 0x5864b8  CKProjectileTypeBallisticPFX_vfAC
//   [ ] 0x5864d8  CKProjectileTypeBallisticPFX_GetTargetPositionFromHook_maybe  [dead]
//   [ ] 0x5865a8  RegisterCKProjectileTypeBallisticPFXClass
//   [ ] 0x586620  _GLOBAL__I_586620
//   [ ] 0x586630  CKProjectileTypeBallisticPFX_PlayInstanceSound_maybe
//   [x] 0x5866d8  CKProjectileTypeBallisticPFX_DeleteArray
//   [x] 0x586778  CKProjectileTypeBallisticPFX_CreateArray
//   [ ] 0x586830  CKProjectileTypeBallisticPFX_IsDead
//   [x] 0x5868e8  CKProjectileTypeBallisticPFX_Create
//   [ ] 0x586940  CKProjectileTypeBallisticPFX_ComputeAttractionVector_maybe
//   [ ] 0x586ba0  CKProjectileTypeBallisticPFX_SumAttractionVectors_maybe  [dead]
//   [ ] 0x586d48  CKProjectileTypeBallisticPFX_ComputeSteering_maybe
//   [ ] 0x587218  CKProjectileTypeBallisticPFX_UpdateOrientation
//   [ ] 0x587d00  CKProjectileTypeBallisticPFX_ProcessDamageContacts
//   [ ] 0x588278  CKProjectileTypeBallisticPFX_UpdateMotion
//   [ ] 0x5886d0  CKProjectileTypeBallisticPFX_KillInstance
//   [ ] 0x588d08  CKProjectileTypeBallisticPFX_SpawnAtPoint_maybe
//   [ ] 0x58a0f8  CKProjectileTypeBallisticPFX_LaunchAtPointEx
//   [ ] 0x58a1c8  CKProjectileTypeBallisticPFX_LaunchAtPoint
//   [ ] 0x58a238  CKProjectileTypeBallisticPFX_OnDeath
//   [ ] 0x58a948  CKProjectileTypeBallisticPFX_CollideModeC_maybe
//   [ ] 0x58b498  CKProjectileTypeBallisticPFX_CollideModeB_maybe
//   [ ] 0x58c148  CKProjectileTypeBallisticPFX_CollideSweepA
//   [ ] 0x58c878  CKProjectileTypeBallisticPFX_UpdateCollision
//   [ ] 0x58c948  CKProjectileTypeBallisticPFX_SpawnInstance
//   [ ] 0x58e160  CKProjectileTypeBallisticPFX_LaunchEx
//   [ ] 0x58e240  CKProjectileTypeBallisticPFX_Launch
//   [ ] 0x58e2c0  CKProjectileTypeBallisticPFX_Destroy
//   [ ] 0x58e2e8  CKProjectileTypeBallisticPFX_MessageProc
//   [ ] 0x58e3b8  CKProjectileTypeBallisticPFX_Save
//   [ ] 0x58e3c0  CKProjectileTypeBallisticPFX_PostLoad
//   [ ] 0x58e408  CKProjectileTypeBallisticPFX_RecursiveRegistration
//   [x] 0x58e508  CKProjectileTypeBallisticPFX_Load
//
//   [ ] 0x9cb3d8  CKProjectileTypeBallisticPFX_IsKindOfClass  [inline]
//   [ ] 0x9cb400  CKProjectileTypeBallisticPFX_GetClassType  [inline]
//   [ ] 0x9cb408  CKProjectileTypeBallisticPFX_GetClassID  [inline]
//   [ ] 0x9cb410  CKProjectileTypeBallisticPFX_Destructor  [inline]
//   [ ] 0x9cb430  CKProjectileTypeBallisticPFX_DeletingDestructor  [inline]
#include "k2000/logic/CKProjectileTypeBallisticPFX.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/scenegraph/CSGLeaf.h"

// 0x0058e508 CKProjectileTypeBallisticPFX_Load: IKProjectileType's data, then (level data only) two
// references, per projectile two references, a word, a reference and a byte (13 + 8 * count + 9 bytes).
int32_t CKProjectileTypeBallisticPFX::Load(IKFile* file, int32_t type) {
    IKProjectileType::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk24);
    IKFile_ReadRef(file, &m_unk28);
    m_GrdContDatasIn.m_fDeltaMax = 1.0f;      // TOC1 -0x7128
    m_GrdContDatasIn.m_fObjectHeight = 2.0f;  // TOC1 -0x7124
    const uint32_t count = m_ui8MaxProjectiles;
    // PS3: count << 2 and (count * PS3 record size) masked to 16 bits (rlwinm 0,16,28); a byte count never
    // reaches the mask, so native sizes are used.
    Projectile** list = static_cast<Projectile**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Projectile*))));
    Projectile* projectiles = static_cast<Projectile*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(Projectile))));
    m_aProjectiles = projectiles;
    m_apProjectileList = reinterpret_cast<void**>(list);
    for (uint8_t i = 0; i < m_ui8MaxProjectiles; ++i) {
        Projectile* p = &projectiles[i];
        list[i] = p;
        CSGLeaf* node = nullptr;
        IKFile_ReadRef(file, &node);
        IKFile_ReadRef(file, &p->m_unk80);
        p->m_pNode = node;
        if (node != nullptr) node->m_sgProperties = (node->m_sgProperties & ~0x4u) | 0x4u;
        p->m_unk00 = 0;
        p->m_unk34 = 0;
        p->m_unk0c = {0.0f, 0.0f, 0.0f};  // the vector at 0x00c50d64
        p->m_unk18 = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
        p->m_unk24 = {0.0f, 0.0f, 0.0f};  // 0x00c50d4c (also (0, 0, 0))
        p->m_unk30 = 0;
        p->m_GrdContDatasInOut.m_i32FaceIndex = -1;
        p->m_GrdContDatasInOut.m_eContactStatus = 3;
        p->m_GrdContDatasInOut.m_ui8SectorNumber = 0;
        p->m_GrdContDatasInOut.m_pGround = nullptr;
        p->m_ui8Index = i;
        p->m_unk6c = 1.0f;
        p->m_unk7c = 0;
        p->m_unk64 = 0;
        p->m_unk68 = 0;
        p->m_unk78 = 0;
    }
    ReadS32LE(file, &m_unk2c);
    IKFile_ReadRef(file, &m_unk30);
    ReadU8(file, &Unk22());
    return 1;
}
