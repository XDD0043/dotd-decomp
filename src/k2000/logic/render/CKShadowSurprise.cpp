// CKShadowSurprise.cpp - reconstructed original translation unit 0x3d7500-0x3dc3d8 (GAME_TOC1, main_toc1), 29 functions, 29 live.
// Primary class: CKShadowSurprise  key 0xa4cc  category Logic  size 0x274  vtable 0xb247f0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x3d7500  CKShadowSurprise_Delete
//   [x] 0x3d7550  CKShadowSurprise_GetAbilityId
//   [ ] 0x3d7558  CKShadowSurprise_GetFamilyId
//   [ ] 0x3d7560  CKShadowSurprise_IsGroundTrailActive_maybe
//   [ ] 0x3d75c0  CKShadowSurprise_GetFxSound_maybe
//   [ ] 0x3d7798  CKShadowSurprise_ApplyHeroControl
//   [ ] 0x3d7948  CKShadowSurprise_End
//   [ ] 0x3d7ac0  CKShadowSurprise_StopFx
//   [ ] 0x3d7d00  CKShadowSurprise_Start
//   [x] 0x3d7d70  CKShadowSurprise_ResetRuntime
//   [x] 0x3d7e40  CKShadowSurprise_PostLoad
//   [ ] 0x3d7e90  CKShadowSurprise_RecursiveRegistration
//   [ ] 0x3d7eb8  CKShadowSurprise_Destroy
//   [x] 0x3d7ee0  CKShadowSurprise_Construct
//   [x] 0x3d7f18  CKShadowSurprise_DeleteArray
//   [ ] 0x3d7fb8  CKShadowSurprise_DeletingDestructor
//   [ ] 0x3d8000  CKShadowSurprise_Destructor
//   [ ] 0x3d8030  CKShadowSurprise_DestructBody
//   [ ] 0x3d8060  RegisterCKShadowSurpriseClass
//   [ ] 0x3d80e8  _GLOBAL__D_3d80e8
//   [ ] 0x3d80f8  _GLOBAL__I_3d80f8
//   [ ] 0x3d8108  CKShadowSurprise_Construct_2
//   [x] 0x3d8140  CKShadowSurprise_CreateArray
//   [x] 0x3d81f0  CKShadowSurprise_Create
//   [ ] 0x3d8248  CKShadowSurprise_UpdateEffect_maybe
//   [x] 0x3d8ef8  CKShadowSurprise_Load
//   [ ] 0x3d9e48  CKShadowSurprise_Save
//   [ ] 0x3dae90  CKShadowSurprise_SetFxActive
//   [ ] 0x3dbfd0  CKShadowSurprise_UpdateAttack_maybe
//
//   [ ] 0x9c0848  CKShadowSurprise_IsKindOfClass  [inline]
//   [x] 0x9c0898  CKShadowSurprise_GetClassType  [inline]
//   [x] 0x9c08a0  CKShadowSurprise_GetClassID  [inline]
//   [ ] 0x9c08a8  CKShadowSurprise_StartEmitterFx  [inline]
#include "k2000/logic/render/CKShadowSurprise.h"

#include "Spyro2008/logic/CKS08ElementDamage.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGSectorRoot.h"

// 0x003d7d70 CKShadowSurprise_ResetRuntime: the base's reset (0x3dcea0), then the element's own words, and the
// damage object learns the ability id (the damage's vt+0x68 0x9c0b00 CKS08ElementDamage_SetAbilityId_maybe
// stores it at +0x38).
void CKShadowSurprise::ResetRuntime() {
    m_unk26c = 0;
    m_unk270 = 0;
    CKTransformElement::ResetRuntime();
    CKS08ElementDamage* damage = static_cast<CKS08ElementDamage*>(m_unk230);
    m_unk254 = 1.0f;  // TOC +0x4118
    m_unk208 = 0;
    m_unk13c = 0;
    m_unk1e8 = 0;
    m_unk264 = 0;
    m_unk1f8 = 0;
    m_unk260 = 0;
    m_unk13d = 1;
    m_unk258 = 0;
    m_unk25c = 0;
    damage->m_unk38 = GetAbilityId();
}

// 0x005832a8 SceneNode_SetVisibleInLayer_maybe: the node's flag bit 2 (hidden) takes `value`; when its parent is not the root of
// sector `sector`, it leaves its parent (vt+0x78) and joins the root (AddChild vt+0x70, or with `keepWorld` vt+0x74).
static void SceneNode_SetVisibleInLayer(CSGLeaf* node, uint32_t value, int32_t keepWorld, int32_t sector) {
    if (node == nullptr) return;
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | ((value & 0xff) << 2);
    CSGBranch* parent = node->m_pParent;
    CSGBranch* root = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[sector])->m_pSectorRoot;
    if (parent == root) return;
    if (parent != nullptr) parent->RemoveChild(node);
    if (keepWorld == 0) {
        root->AddChild(node);
    } else {
        root->AddChildKeepWorldTransform(node);
    }
}

// 0x003d7e40 CKShadowSurprise_PostLoad: the base's (0x3de488: ResetRuntime), then SceneNode_SetVisibleInLayer_maybe
// 0x5832a8 (node +0x1d4, visible 1, layer 0, sector 0).
int32_t CKShadowSurprise::PostLoad(int32_t type) {
    CKTransformElement::PostLoad(type);
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_unk1d4), 1, 0, 0);
    return 1;
}

// 0x003d8ef8 CKShadowSurprise_Load
int32_t CKShadowSurprise::Load(IKFile* file, int32_t type) {
    CKTransformElement::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_unk1dc);
    IKFile_ReadRef(file, &m_unk1e0);
    IKFile_ReadRef(file, &m_unk1e4);
    IKFile_ReadRef(file, &m_unk1d8);
    IKFile_ReadRef(file, &m_unk22c);
    IKFile_ReadRef(file, &m_unk1ec);
    IKFile_ReadRef(file, &m_unk1f0);
    IKFile_ReadRef(file, &m_unk1f4);
    IKFile_ReadRef(file, &m_unk1d4);
    for (uint32_t i = 0; i < 3; ++i) {
        ReadF32LE(file, &m_unk154[i]);
        ReadU32LE(file, &m_unk160[i]);
        ReadU32LE(file, &m_unk16c[i]);
        ReadU32LE(file, &m_unk178[i]);
        ReadF32LE(file, &m_unk184[i]);
        ReadF32LE(file, &m_unk190[i]);
        ReadF32LE(file, &m_unk19c[i]);
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk1a8[i]), 3);  // one 12-byte read
    }
    ReadF32LE(file, &m_unk1cc);
    ReadF32LE(file, &m_unk1d0);
    for (uint32_t i = 0; i < 6; ++i) ReadF32LE(file, &m_unk234[i]);
    IKFile_ReadRef(file, &m_unk20c);
    IKFile_ReadRef(file, &m_unk210);
    IKFile_ReadRef(file, &m_unk214);
    IKFile_ReadRef(file, &m_unk218);
    IKFile_ReadRef(file, &m_unk24c);
    ReadF32LE(file, &m_unk250);
    IKFile_ReadRef(file, &m_unk220);
    IKFile_ReadRef(file, &m_unk224);
    IKFile_ReadRef(file, &m_unk228);
    IKFile_ReadRef(file, &m_unk21c);
    IKFile_ReadRef(file, &m_unk1fc);
    IKFile_ReadRef(file, &m_unk200);
    IKFile_ReadRef(file, &m_unk204);
    IKFile_ReadRef(file, &m_unk230);
    return 1;
}
