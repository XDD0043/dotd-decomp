// CKHkS08Hero.cpp - reconstructed original translation unit 0x2d8d98-0x2f8520 (GAME_TOC1, main_toc1), 44 functions, 40 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: ProcessHeroContactList (1), CreateCKHkS08HeroArray (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x2d8d98  CKHkS08Hero_TickTimers_maybe  [dead]
//   [x] 0x2d8f38  ProcessHeroContactList
//   [ ] 0x2d9310  CKHkS08Hero_SelectMovementCamera_maybe  [dead: no pointer to its descriptor 0xb98be0, no call]
//   [ ] 0x2d93e0  FUN_002d93e0  [dead]
//   [x] 0x2d9410  CKHkS08Hero_ResetMotionState_maybe
//   [x] 0x2d9698  CKHkS08Hero_SectorUnload  (IKLife::SectorUnload inherited (through 0x345118))
//   [x] 0x2d96c0  CKHkS08Hero_SectorLoaded  (= the inherited slot)
//   [x] 0x2d96e8  CKHkS08Hero_Resume
//   [x] 0x2d9730  CKHkS08Hero_Pause
//   [x] 0x2d97a8  CKHkS08Hero_DeleteArray
//   [x] 0x2d9850  RegisterCKHkS08HeroType  (the two file statics at the end; the registration: Kp3Ported)
//   [ ] 0x2d98d8  _GLOBAL__D_2d98d8
//   [ ] 0x2d98e8  _GLOBAL__I_2d98e8
//   [x] 0x2d98f8  CKHkS08Hero_RecursiveRegistration
//   [x] 0x2daa78  CKHkS08Hero_GetInfo
//   [x] 0x2dacb0  CKHkS08Hero_CanAttachTo_maybe
//   [x] 0x2dafa8  CKHkS08Hero_OnUnlock
//   [x] 0x2db098  CKHkS08Hero_PostLoad
//   [x] 0x2db3d8  CKHkS08Hero_Stop
//   [x] 0x2db9d8  CKHkS08Hero_ClearMovementFloatFields_maybe
//   [x] 0x2dba30  CKHkS08Hero_OnAttachToObject
//   [x] 0x2dbb50  CKHkS08Hero_InitAnimBlendSlot
//   [x] 0x2dbb88  CKHkS08Hero_OnLock
//   [x] 0x2dbc60  CKHkS08Hero_CanDragonSwitch_maybe
//   [x] 0x2dbde0  CKHkS08Hero_LockedUpdate
//   [x] 0x2dbe68  CKHkS08Hero_MessageProc
//   [x] 0x2dc3d8  CKHkS08Hero_ResetControlState_maybe
//   [x] 0x2dc5a0  CKHkS08Hero_OnDetachFromObject
//   [x] 0x2dc660  CKHkS08Hero_UpdateGroundSurfaceFlags_maybe
//   [x] 0x2dc730  CKHkS08Hero_UpdateMovement
//   [x] 0x2dca08  CKHkS08Hero_FreeOwnedResources_maybe
//   [x] 0x2dcb60  CKHkS08Hero_Destroy
//   [x] 0x2dcbc0  CreateCKHkS08HeroArray  (DOTD_DECLARE_FACTORIES, CKHkS08Hero.h: the constructor per element)
//   [x] 0x2dd000  CKHkS08Hero_Create
//   [x] 0x2dd340  CKHkS08Hero_UpdateModeFlagsAndTetherTimers_maybe  (CKHkS08HeroCameraTarget.cpp)
//   [x] 0x2de6d0  UpdateCKHkS08Hero
//   [x] 0x2df070  CKHkS08Hero_InitLocomotionAnimSubStateMachines
//   [x] 0x2df308  CKHkS08Hero_Restart
//   [x] 0x2df3e0  CKHkS08Hero_Start
//   [ ] 0x2df4a0  FUN_002df4a0  [dead]
//   [x] 0x2e2198  CKHkS08Hero_Load
//   [ ] 0x2ec710  FUN_002ec710  [dead]
//   [ ] 0x2eee20  CKHkS08Hero_Save
//   [x] 0x2f8518  CKHkS08Hero_vf180  (CKHkS08Hero.h)
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/fx/IKFx.h"
#include "k2000/hooks/CKHkClimbZone.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/services/CollisionDatas.h"
#include "k2000/services/CKSrvCollision.h"
#include <cmath>
#include "crt/ppc_ops.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"
#include "k2000/services/CTriggerStarter.h"
#include "Spyro2008/logic/CKS08GameState.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/core/Stub.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "Spyro2008/logic/CKS08CarrierHero.h"
#include "k2000/logic/CKAbilityElement.h"
#include "k2000/core/IKInfo.h"

#include "Renderware/rwcore/RwMatrix.h"
#include "Spyro2008/logic/CKS08HeroBlow.h"

#include "k2000/io/IKFile.h"
#include "k2000/math/Math.h"
#include "k2000/memory/Mem.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/services/CKSrvDynamic.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/components/CKImpulsionCpnt.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/misc/CKHkActorBase.h"
#include "Spyro2008/hooks/CKHkS08PowerBucket.h"
#include "Spyro2008/hooks/CKHkS08TransportableWeight.h"
#include "k2000/render/CRenderer.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "Spyro2008/misc/CKS08HeroAbilityHost.h"

namespace {
// 0x00a704cc (TOC +0x1db8 points 4 bytes before it): two rows of 36 floats, hero 0 and the other heroes
// (the rows are identical). Copied over +0x1480..+0x14dc (24) and +0x130c..+0x1338 (12) by the Load.
const float kHeroDefaults_maybe[2][36] = {
    {0x1.99999ap-3f, 0.0f, 0x1.333334p-3f, 0x1p+2f, 0x1.9p+5f, 0x1.4p+3f,
    0x1.99999ap-3f, 0.0f, 0x1.333334p-3f, 0x1p+2f, 0x1.9p+5f, 0x1.4p+3f,
    0x1.99999ap-3f, 0x1.99999ap-3f, 0x1.99999ap-3f, 0x1.4p+3f, 0x1p-1f, 0x1.666666p-1f,
    0x1.99999ap-3f, 0x1.99999ap-3f, 0x1.99999ap-3f, 0x1.4p+3f, 0x1p-1f, 0x1.666666p-1f,
    0x1.99999ap-4f, 0.0f, 0x1.99999ap-1f, 0x1.4p+3f, 0x1.ep+4f, 0x1.ep+3f,
    0x1.99999ap-4f, 0.0f, 0x1.99999ap-1f, 0x1.4p+3f, 0x1.ep+4f, 0x1.ep+3f},
    {0x1.99999ap-3f, 0.0f, 0x1.333334p-3f, 0x1p+2f, 0x1.9p+5f, 0x1.4p+3f,
    0x1.99999ap-3f, 0.0f, 0x1.333334p-3f, 0x1p+2f, 0x1.9p+5f, 0x1.4p+3f,
    0x1.99999ap-3f, 0x1.99999ap-3f, 0x1.99999ap-3f, 0x1.4p+3f, 0x1p-1f, 0x1.666666p-1f,
    0x1.99999ap-3f, 0x1.99999ap-3f, 0x1.99999ap-3f, 0x1.4p+3f, 0x1p-1f, 0x1.666666p-1f,
    0x1.99999ap-4f, 0.0f, 0x1.99999ap-1f, 0x1.4p+3f, 0x1.ep+4f, 0x1.ep+3f,
    0x1.99999ap-4f, 0.0f, 0x1.99999ap-1f, 0x1.4p+3f, 0x1.ep+4f, 0x1.ep+3f},
};
}  // namespace

// 0x002dd000 CKHkS08Hero_Create (inlined constructor): the CKHkS08Hero part, in its store order.
CKHkS08Hero::CKHkS08Hero() {
    m_unkFec = 0;
    m_unk100c = 0;
    m_unk102c = 0;
    m_unk106c = 0;
    m_unk104c = 0;
    // +0x10f0: the embedded AnimBlendSlot (its vtable 0xb16560 is stored here), controller cleared.
    m_animBlendSlot10f0.m_pController = nullptr;
    m_unk13a8.x = 0.0f;  // TOC 0x1da4
    m_unk13b4.x = 0.0f;
    m_unk144c.x = 0.0f;
    m_unk13a8.z = 0.0f;
    m_unk13a8.y = 0.0f;
    m_unk13b4.z = 0.0f;
    m_unk13b4.y = 0.0f;
    m_unk144c.z = 0.0f;
    m_unk144c.y = 0.0f;
    m_unk16b8 = 0;
    m_unk16c4 = 0;
    // C2.2 strict2: the constructor stores none of these. They read 0 in the live dump (a zeroed heap block or a
    // reset that is not ported yet: ResetCombatState 0x2fc938 ...) and the camera-target registration
    // (CKHkS08HeroCameraTarget.cpp) reads them. Remove when the hero resets are ported.
    m_unk1780 = 0.0f;
    // The take-off push byte: ComputeFlightThrustForce_maybe 0x313f50 tests it (then reads the timer +0x1388) on the first
    // flying frame, before LocoState0_Flying's entry clears both. The live stores to +0x1385 (EBOOT scan: LocoState0_Flying,
    // DynamicStage1Flying, UpdateFlyingLocomotion; FUN_00312a48 is dead) are all flight code, so the original reads its
    // fresh heap there, 0 (work/fill_test.py fight2 with fill 3f, found by work/fill_bisect.py).
    m_unk1385 = 0;
    m_unk1784 = 0;
    m_unk1788 = 0.0f;
    m_unk13d1 = 0;
    m_unk13d4 = 0.0f;
    m_unk13d8 = 0;
    m_unk1539 = 0;
    m_ui8MovementMode = 0;
    m_unk1813 = 0;
    m_unk1814 = 0;
    m_unk1815 = 0;
    m_unk1b34 = 0.0f;
    m_unk18d1 = 0xff;
    m_ui8FlyAnimState = 0xff;
    m_unk1961 = 0xff;
    m_ui8GroundAnimState = 0xff;
    m_unk19a9 = 0xff;
    m_ui8ClimbAnimState = 0xff;
    m_unk1a28 = 1;
    m_apUnk1a24 = nullptr;
    m_unk1a34 = 1;
    m_unk1a2c = 0;
    m_unk1a38 = 0;
    m_apUnk1a30 = nullptr;
}

// 0x002d98f8 CKHkS08Hero_RecursiveRegistration: the base's (CKHkS08HeroBase_RecursiveRegistration 0x345b60), then
// every object the hero references (vt+0x24 each with the same type), in the original's order; the null-tested ones
// are tested as the original does. The two trigger starters (+0x114c / +0x1154) call KStub_Return1_2361b0: nothing.
void CKHkS08Hero::RecursiveRegistration(int32_t type) {
    IKHkHero::RecursiveRegistration(type);  // 0x00345b60
    m_unk1a8c->RecursiveRegistration(type);
    for (uint32_t i = 0, n = m_unk1a2c; i != n; ++i) m_apUnk1a24[i]->RecursiveRegistration(type);
    m_apUnk1a30[0]->RecursiveRegistration(type);
    m_apUnk1a30[1]->RecursiveRegistration(type);
    m_apUnk1a30[2]->RecursiveRegistration(type);
    m_unk1a90->RecursiveRegistration(type);
    m_unk1a94->RecursiveRegistration(type);
    m_unk1a98->RecursiveRegistration(type);
    m_unk1a9c->RecursiveRegistration(type);
    m_unk1aa0->RecursiveRegistration(type);
    m_unk1aa4->RecursiveRegistration(type);
    m_unk1ae4->RecursiveRegistration(type);
    m_unkee8->RecursiveRegistration(type);
    m_pCameraTargetNode->RecursiveRegistration(type);
    m_unk19b4->RecursiveRegistration(type);
    m_unk19bc->RecursiveRegistration(type);
    m_unk19d4->RecursiveRegistration(type);
    m_unk19f8->RecursiveRegistration(type);
    m_unk19fc->RecursiveRegistration(type);
    m_pCarrierHero->RecursiveRegistration(type);
    m_apUnkfbc[0]->RecursiveRegistration(type);
    m_apUnkfbc[1]->RecursiveRegistration(type);
    m_apUnkfbc[2]->RecursiveRegistration(type);
    m_apUnkfbc[3]->RecursiveRegistration(type);
    m_apUnkfbc[4]->RecursiveRegistration(type);
    if (m_apAbilities[0] != nullptr) m_apAbilities[0]->RecursiveRegistration(type);
    if (m_apAbilities[1] != nullptr) m_apAbilities[1]->RecursiveRegistration(type);
    if (m_apAbilities[2] != nullptr) m_apAbilities[2]->RecursiveRegistration(type);
    if (m_apAbilities[3] != nullptr) m_apAbilities[3]->RecursiveRegistration(type);
    if (m_apAbilities[4] != nullptr) m_apAbilities[4]->RecursiveRegistration(type);
    if (m_apAbilities[5] != nullptr) m_apAbilities[5]->RecursiveRegistration(type);
    if (m_apAbilities[6] != nullptr) m_apAbilities[6]->RecursiveRegistration(type);
    if (m_apAbilities[7] != nullptr) m_apAbilities[7]->RecursiveRegistration(type);
    if (m_apAbilities[8] != nullptr) m_apAbilities[8]->RecursiveRegistration(type);
    if (m_apAbilities[9] != nullptr) m_apAbilities[9]->RecursiveRegistration(type);
    m_unk19dc->RecursiveRegistration(type);
    m_unk1b1c->RecursiveRegistration(type);
    m_unk1b20->RecursiveRegistration(type);
    m_unk1b24->RecursiveRegistration(type);
    m_unk1a78->RecursiveRegistration(type);
    m_unk1a7c->RecursiveRegistration(type);
    m_pFlightAimCone->RecursiveRegistration(type);
    m_unk1b28->RecursiveRegistration(type);
    m_unk1ae0->RecursiveRegistration(type);
    m_unk19e4->RecursiveRegistration(type);
    m_unk1a00->RecursiveRegistration(type);
    m_unk19f0->RecursiveRegistration(type);
    for (int32_t i = 0; i < 8; ++i) {
        for (int32_t j = 0; j < 4; ++j) {
            if (m_apUnk1070[i][j] != nullptr) m_apUnk1070[i][j]->RecursiveRegistration(type);
        }
    }
    if (m_unk147c != nullptr) m_unk147c->RecursiveRegistration(type);
    m_unk19c4->RecursiveRegistration(type);
    m_unk19cc->RecursiveRegistration(type);
    m_unk1dbc->RecursiveRegistration(type);
    m_unk1b50->RecursiveRegistration(type);
    m_unk1b58->RecursiveRegistration(type);
    m_unk1b54->RecursiveRegistration(type);
    m_unk1b60->RecursiveRegistration(type);
    m_unk1b5c->RecursiveRegistration(type);
    m_unk1b64->RecursiveRegistration(type);
    m_unk1b6c->RecursiveRegistration(type);
    m_unk1b70->RecursiveRegistration(type);
    m_unk1b74->RecursiveRegistration(type);
    m_pFlightImpulsionCpnt->RecursiveRegistration(type);
    m_unk1dc4->RecursiveRegistration(type);
    m_unk1dc8->RecursiveRegistration(type);
    m_unk1dd4->RecursiveRegistration(type);
    m_unk1dd8->RecursiveRegistration(type);
    m_unk1ddc->RecursiveRegistration(type);
    if (m_unk1de0 != nullptr) m_unk1de0->RecursiveRegistration(type);
    m_unk1de4->RecursiveRegistration(type);
    m_unk1de8->RecursiveRegistration(type);
    m_unk1dec->RecursiveRegistration(type);
    m_unk1df0->RecursiveRegistration(type);
    m_unk1ccc->RecursiveRegistration(type);
    m_unk1ce0->RecursiveRegistration(type);
    m_unk1cd0->RecursiveRegistration(type);
    m_unk1ce4->RecursiveRegistration(type);
    m_unk1cd4->RecursiveRegistration(type);
    m_unk1ce8->RecursiveRegistration(type);
    m_unk1cd8->RecursiveRegistration(type);
    m_unk1cec->RecursiveRegistration(type);
    m_unk1cdc->RecursiveRegistration(type);
    m_unk1cf0->RecursiveRegistration(type);
    m_unk1cf8->RecursiveRegistration(type);
    m_unk1a04->RecursiveRegistration(type);
    if (m_unk1164 != nullptr) m_unk1164->RecursiveRegistration(type);
    if (m_unk116c != nullptr) m_unk116c->RecursiveRegistration(type);
    if (m_unk1168 != nullptr) m_unk1168->RecursiveRegistration(type);
    if (m_unk1170 != nullptr) m_unk1170->RecursiveRegistration(type);
}

// 0x002e2198 CKHkS08Hero_Load
int32_t CKHkS08Hero::Load(IKFile* file, int32_t type) {
    IKHkHero::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk8dc);
    ReadF32LE(file, &m_unk8e0);
    ReadF32LE(file, &m_unk8f4);
    ReadF32LE(file, &m_unk8f8);
    ReadF32LE(file, &m_unk8fc);
    ReadF32LE(file, &m_unk91c);
    ReadF32LE(file, &m_unk920);
    ReadF32LE(file, &m_unk924);
    ReadF32LE(file, &m_unk928);
    ReadF32LE(file, &m_unk92c);
    ReadF32LE(file, &m_unk93c);
    ReadF32LE(file, &m_unk940);
    ReadF32LE(file, &m_unk944);
    ReadF32LE(file, &m_unk948);
    ReadF32LE(file, &m_unk954);
    ReadF32LE(file, &m_unk958);
    ReadF32LE(file, &m_unk95c);
    ReadF32LE(file, &m_unk960);
    ReadF32LE(file, &m_unk964);
    ReadF32LE(file, &m_unk968);
    ReadF32LE(file, &m_unk96c);
    ReadF32LE(file, &m_unk970);
    ReadF32LE(file, &m_unk978);
    ReadF32LE(file, &m_unk97c);
    ReadF32LE(file, &m_unk980);
    ReadF32LE(file, &m_unk984);
    ReadF32LE(file, &m_unk988);
    ReadF32LE(file, &m_unk98c);
    ReadF32LE(file, &m_unk990);
    ReadF32LE(file, &m_unk994);
    ReadF32LE(file, &m_unk998);
    ReadF32LE(file, &m_unk99c);
    ReadF32LE(file, &m_unk9a0);
    ReadF32LE(file, &m_unk9a4);
    ReadF32LE(file, &m_unk9a8);
    ReadF32LE(file, &m_unk9ac);
    ReadF32LE(file, &m_unk9b0);
    ReadF32LE(file, &m_unka78);
    ReadF32LE(file, &m_unka7c);
    ReadF32LE(file, &m_unka80);
    ReadF32LE(file, &m_unka84);
    ReadF32LE(file, &m_unka8c);
    ReadF32LE(file, &m_unka90);
    ReadF32LE(file, &m_unka94);
    ReadF32LE(file, &m_unka98);
    ReadF32LE(file, &m_unka9c);
    ReadF32LE(file, &m_unkaa0);
    ReadF32LE(file, &m_unkaa4);
    ReadF32LE(file, &m_unkaa8);
    ReadF32LE(file, &m_unkaac);
    ReadU8(file, &m_unkab0);
    ReadF32LE(file, &m_unkad8);
    ReadF32LE(file, &m_unkadc);
    ReadF32LE(file, &m_unkae0);
    ReadF32LE(file, &m_unkae4);
    ReadF32LE(file, &m_unkae8);
    ReadF32LE(file, &m_unkaec);
    ReadF32LE(file, &m_unkaf0);
    ReadF32LE(file, &m_unkaf4);
    // An inlined array reserve + resize (data +0x1a24, capacity +0x1a28, size +0x1a2c): a count, then one
    // reference per element.
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_unk1a28 = 1;
        m_apUnk1a24 = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
        // the size is left as it was (the original branches past its store)
    } else {
        m_unk1a28 = count;
        m_apUnk1a24 = static_cast<IKSerializable**>(Mem_AllocAligned16(count * sizeof(IKSerializable*)));
        // (the original's grow branch, capacity < count, cannot run after this allocation)
        m_unk1a2c = count;
    }
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &m_apUnk1a24[i]);
    IKFile_ReadRef(file, &m_unk1a8c);
    ReadF32LE(file, &m_unkaf8);
    ReadF32LE(file, &m_unkbf0);
    ReadF32LE(file, &m_unkbf4);
    ReadF32LE(file, &m_unkbf8);
    ReadF32LE(file, &m_unkbfc);
    ReadF32LE(file, &m_unkc00);
    ReadF32LE(file, &m_unkc04);
    ReadF32LE(file, &m_unkc08);
    ReadF32LE(file, &m_unkc0c);
    ReadF32LE(file, &m_unkc10);
    ReadF32LE(file, &m_unkc14);
    ReadF32LE(file, &m_unkc18);
    ReadF32LE(file, &m_unkc1c);
    ReadF32LE(file, &m_unkc20);
    ReadF32LE(file, &m_unkc24);
    ReadF32LE(file, &m_unkc28);
    ReadF32LE(file, &m_unkc2c);
    ReadF32LE(file, &m_unkc30);
    ReadF32LE(file, &m_unkc34);
    ReadF32LE(file, &m_unkc38);
    ReadF32LE(file, &m_unkc3c);
    ReadF32LE(file, &m_unkc40);
    ReadF32LE(file, &m_unkc44);
    ReadF32LE(file, &m_unkab4);
    ReadF32LE(file, &m_unkab8);
    ReadF32LE(file, &m_unkabc);
    ReadF32LE(file, &m_unkac0);
    ReadF32LE(file, &m_unkc48);
    ReadF32LE(file, &m_unkc4c);
    ReadF32LE(file, &m_unka88);
    ReadF32LE(file, &m_unk89c);
    ReadF32LE(file, &m_unkc78);
    ReadF32LE(file, &m_unkc74);
    ReadF32LE(file, &m_unkc7c);
    ReadF32LE(file, &m_unkc80);
    ReadF32LE(file, &m_unkc84);
    ReadF32LE(file, &m_unkc50);
    IKFile_ReadRef(file, &m_unk1a90);
    ReadF32LE(file, &m_unkc88);
    ReadF32LE(file, &m_unkc8c);
    ReadF32LE(file, &m_unkc90);
    ReadF32LE(file, &m_unkc94);
    ReadF32LE(file, &m_unkc98);
    ReadF32LE(file, &m_unkc9c);
    ReadF32LE(file, &m_unkca0);
    ReadU32LE(file, &m_unkca4);
    ReadF32LE(file, &m_unkcbc);
    ReadF32LE(file, &m_unkcc0);
    ReadF32LE(file, &m_unkcc4);
    IKFile_ReadRef(file, &m_unk1a94);
    ReadF32LE(file, &m_unk8a0);
    IKFile_ReadRef(file, &m_unk1a98);
    IKFile_ReadRef(file, &m_unk1a9c);
    IKFile_ReadRef(file, &m_unk1aa0);
    ReadF32LE(file, &m_unkcfc);
    ReadF32LE(file, &m_unkd00);
    ReadF32LE(file, &m_unkd04);
    ReadF32LE(file, &m_unk8a4);
    ReadF32LE(file, &m_unk8b0);
    ReadF32LE(file, &m_unk1a3c);
    ReadF32LE(file, &m_unk1a40);
    ReadF32LE(file, &m_unk1a44);
    ReadF32LE(file, &m_unk1a48);
    ReadF32LE(file, &m_unk1a4c);
    ReadF32LE(file, &m_unk1a50);
    ReadF32LE(file, &m_unk1a54);
    ReadF32LE(file, &m_unk1a58);
    ReadF32LE(file, &m_unk1a5c);
    ReadF32LE(file, &m_unk1a60);
    ReadF32LE(file, &m_unk1a64);
    ReadF32LE(file, &m_unk1a68);
    ReadF32LE(file, &m_unk1a6c);
    ReadF32LE(file, &m_unk1a70);
    ReadF32LE(file, &m_unk1a74);
    ReadF32LE(file, &m_unkb20);
    ReadF32LE(file, &m_unkb24);
    ReadF32LE(file, &m_unkb28);
    ReadF32LE(file, &m_unkb2c);
    ReadF32LE(file, &m_unkb30);
    ReadF32LE(file, &m_unkb34);
    ReadF32LE(file, &m_unkb38);
    ReadF32LE(file, &m_unkb3c);
    ReadF32LE(file, &m_unkb40);
    ReadF32LE(file, &m_unk974);
    ReadF32LE(file, &m_unkd1c);
    ReadF32LE(file, &m_unkd20);
    ReadF32LE(file, &m_unkd24);
    ReadF32LE(file, &m_unkd28);
    IKFile_ReadRef(file, &m_unk1ae4);
    IKFile_ReadRef(file, &m_unkee8);
    ReadF32LE(file, &m_unkddc);
    ReadF32LE(file, &m_unkde0);
    ReadF32LE(file, &m_unkde4);
    IKFile_ReadRef(file, &m_pCameraTargetNode);
    ReadF32LE(file, &m_unkd2c);
    ReadF32LE(file, &m_unkd30);
    ReadF32LE(file, &m_unkd34);
    ReadF32LE(file, &m_unkd38);
    ReadF32LE(file, &m_unkd3c);
    ReadF32LE(file, &m_unkd40);
    ReadF32LE(file, &m_unkd44);
    ReadF32LE(file, &m_unke18);
    ReadF32LE(file, &m_unkb0c);
    ReadF32LE(file, &m_unkde8);
    ReadF32LE(file, &m_unkdec);
    ReadU8(file, &m_unke08);
    ReadF32LE(file, &m_unke0c);
    ReadF32LE(file, &m_unk9b4);
    ReadF32LE(file, &m_unk9b8);
    ReadF32LE(file, &m_unk9bc);
    ReadF32LE(file, &m_unk9c0);
    ReadF32LE(file, &m_unkb10);
    ReadF32LE(file, &m_unkb14);
    ReadF32LE(file, &m_unkd80);
    ReadF32LE(file, &m_unkd88);
    ReadF32LE(file, &m_unkd8c);
    ReadF32LE(file, &m_unkd90);
    ReadF32LE(file, &m_unkd94);
    ReadF32LE(file, &m_unkc68);
    ReadF32LE(file, &m_unkc6c);
    ReadF32LE(file, &m_unk8b4);
    ReadF32LE(file, &m_unk8b8);
    ReadF32LE(file, &m_unk8bc);
    ReadF32LE(file, &m_unk8c0);
    ReadF32LE(file, &m_unk9c4);
    ReadF32LE(file, &m_unkb1c);
    IKFile_ReadRef(file, &m_unk19b4);
    ReadS32LE(file, &m_unkd9c);
    IKFile_ReadRef(file, &m_unk19bc);
    IKFile_ReadRef(file, &m_unk19d4);
    ReadF32LE(file, &m_unkb64);
    ReadF32LE(file, &m_unkb68);
    ReadF32LE(file, &m_unk9c8);
    ReadF32LE(file, &m_unkb6c);
    ReadF32LE(file, &m_unkb70);
    ReadF32LE(file, &m_unkb74);
    ReadF32LE(file, &m_unkb78);
    ReadF32LE(file, &m_unkb7c);
    ReadF32LE(file, &m_unk9ec);
    ReadF32LE(file, &m_unkb80);
    ReadF32LE(file, &m_unkb84);
    ReadF32LE(file, &m_unkb88);
    ReadF32LE(file, &m_unkb8c);
    ReadF32LE(file, &m_unkb90);
    ReadF32LE(file, &m_unkb94);
    ReadU32LE(file, &m_unkb98);
    ReadF32LE(file, &m_unkb9c);
    ReadF32LE(file, &m_unk8e4);
    ReadF32LE(file, &m_unk8e8);
    ReadF32LE(file, &m_unke10);
    ReadF32LE(file, &m_unke14);
    ReadF32LE(file, &m_unke1c);
    ReadF32LE(file, &m_unke20);
    ReadF32LE(file, &m_unke24);
    IKFile_ReadRef(file, &m_unk19f8);
    IKFile_ReadRef(file, &m_unk19fc);
    ReadF32LE(file, &m_unk94c);
    ReadF32LE(file, &m_unk9f0);
    ReadF32LE(file, &m_unk8ec);
    ReadF32LE(file, &m_unk9f4);
    ReadF32LE(file, &m_unk9f8);
    ReadF32LE(file, &m_unkac8);
    ReadU8(file, &m_unkacc);
    ReadF32LE(file, &m_unkad0);
    ReadF32LE(file, &m_unkad4);
    ReadF32LE(file, &m_unk9fc);
    ReadF32LE(file, &m_unkac4);
    ReadF32LE(file, &m_unkb44);
    ReadF32LE(file, &m_unkb48);
    ReadF32LE(file, &m_unkb4c);
    ReadF32LE(file, &m_unkb50);
    ReadF32LE(file, &m_unka24);
    ReadF32LE(file, &m_unka28);
    ReadF32LE(file, &m_unka2c);
    ReadF32LE(file, &m_unka30);
    ReadF32LE(file, &m_unkb54);
    ReadF32LE(file, &m_unkb58);
    ReadF32LE(file, &m_unkb5c);
    ReadF32LE(file, &m_unkb60);
    ReadF32LE(file, &m_unka34);
    ReadF32LE(file, &m_unka38);
    ReadF32LE(file, &m_unka3c);
    ReadF32LE(file, &m_unka40);
    ReadS32LE(file, &m_unkda0);
    ReadF32LE(file, &m_unkba8);
    ReadF32LE(file, &m_unkdf0);
    ReadF32LE(file, &m_unkdf4);
    ReadF32LE(file, &m_unkdf8);
    ReadU32LE(file, &m_unkdfc);
    ReadU32LE(file, &m_unke00);
    ReadF32LE(file, &m_unke04);
    ReadF32LE(file, &m_unkd98);
    ReadF32LE(file, &m_unkb18);
    ReadF32LE(file, &m_unke54);
    // The same inlined array (+0x1a30) reserved for 3 and filled with 3 references; each referenced object
    // gets vt+0x98(m_ui8Hero) (as the PostLoad does for +0x1a24's).
    m_unk1a34 = 3;
    m_apUnk1a30 = static_cast<IKSerializable**>(Mem_AllocAligned16(3 * sizeof(IKSerializable*)));
    m_unk1a38 = 3;
    for (uint32_t i = 0; i < 3; ++i) {
        IKFile_ReadRef(file, &m_apUnk1a30[i]);
        static_cast<CKS08HeroBlow*>(m_apUnk1a30[i])->Vf98(m_ui8Hero);  // vt+0x98 0x009bec20 CKS08HeroBlow_vf98
    }
    IKFile_ReadRef(file, &m_unk1aa4);
    IKFile_ReadRef(file, &m_pCarrierHero);
    ReadF32LE(file, &m_unkca8);
    ReadF32LE(file, &m_unkcac);
    ReadF32LE(file, &m_unkcb0);
    ReadF32LE(file, &m_unkcb4);
    ReadF32LE(file, &m_unk1480);
    ReadF32LE(file, &m_unk1484);
    ReadF32LE(file, &m_unk1488);
    ReadF32LE(file, &m_unk148c);
    ReadF32LE(file, &m_unk1490);
    ReadF32LE(file, &m_unk1494);
    ReadF32LE(file, &m_unk1498);
    ReadF32LE(file, &m_unk149c);
    ReadF32LE(file, &m_unk14a0);
    ReadF32LE(file, &m_unk14a4);
    ReadF32LE(file, &m_unk14a8);
    ReadF32LE(file, &m_unk14ac);
    ReadF32LE(file, &m_unk14b0);
    ReadF32LE(file, &m_unk14b4);
    ReadF32LE(file, &m_unk14b8);
    ReadF32LE(file, &m_unk14bc);
    ReadF32LE(file, &m_unk14c0);
    ReadF32LE(file, &m_unk14c4);
    ReadF32LE(file, &m_unk14c8);
    ReadF32LE(file, &m_unk14cc);
    ReadF32LE(file, &m_unk14d0);
    ReadF32LE(file, &m_unk14d4);
    ReadF32LE(file, &m_unk14d8);
    ReadF32LE(file, &m_unk14dc);
    ReadF32LE(file, &m_unk130c);
    ReadF32LE(file, &m_unk1310);
    ReadF32LE(file, &m_unk1314);
    ReadF32LE(file, &m_unk1318);
    ReadF32LE(file, &m_unk131c);
    ReadF32LE(file, &m_unk1320);
    ReadF32LE(file, &m_unk1324);
    ReadF32LE(file, &m_unk1328);
    ReadF32LE(file, &m_unk132c);
    ReadF32LE(file, &m_unk1330);
    ReadF32LE(file, &m_unk1334);
    ReadF32LE(file, &m_unk1338);
    ReadF32LE(file, &m_unke6c);
    ReadF32LE(file, &m_unke70);
    // Hero 0 and the others take +0x1480..+0x14dc and +0x130c..+0x1338 from a constant table, over the
    // values just read.
    const float* defaults = kHeroDefaults_maybe[m_ui8Hero == 0 ? 0 : 1];
    m_unk1480 = defaults[0];
    m_unk1484 = defaults[1];
    m_unk1488 = defaults[2];
    m_unk148c = defaults[3];
    m_unk1490 = defaults[4];
    m_unk1494 = defaults[5];
    m_unk1498 = defaults[6];
    m_unk149c = defaults[7];
    m_unk14a0 = defaults[8];
    m_unk14a4 = defaults[9];
    m_unk14a8 = defaults[10];
    m_unk14ac = defaults[11];
    m_unk14b0 = defaults[12];
    m_unk14b4 = defaults[13];
    m_unk14b8 = defaults[14];
    m_unk14bc = defaults[15];
    m_unk14c0 = defaults[16];
    m_unk14c4 = defaults[17];
    m_unk14c8 = defaults[18];
    m_unk14cc = defaults[19];
    m_unk14d0 = defaults[20];
    m_unk14d4 = defaults[21];
    m_unk14d8 = defaults[22];
    m_unk14dc = defaults[23];
    m_unk130c = defaults[24];
    m_unk1310 = defaults[25];
    m_unk1314 = defaults[26];
    m_unk1318 = defaults[27];
    m_unk131c = defaults[28];
    m_unk1320 = defaults[29];
    m_unk1324 = defaults[30];
    m_unk1328 = defaults[31];
    m_unk132c = defaults[32];
    m_unk1330 = defaults[33];
    m_unk1334 = defaults[34];
    m_unk1338 = defaults[35];
    ReadF32LE(file, &m_unkbac);
    ReadF32LE(file, &m_unkbb0);
    ReadU32LE(file, &m_unkbb4);
    ReadF32LE(file, &m_unkbb8);
    IKFile_ReadObjectRefArray(file, m_apUnkfbc, 5);
    for (int i = 0; i < 10; ++i) IKFile_ReadRef(file, &m_apAbilities[i]);
    ReadRaw(file, &m_unk1c20, 4);
    ReadRaw(file, &m_unk1c34, 4);
    ReadRaw(file, &m_unk1c24, 4);
    ReadRaw(file, &m_unk1c38, 4);
    ReadRaw(file, &m_unk1c28, 4);
    ReadRaw(file, &m_unk1c3c, 4);
    ReadRaw(file, &m_unk1c2c, 4);
    ReadRaw(file, &m_unk1c40, 4);
    ReadRaw(file, &m_unk1c30, 4);
    ReadRaw(file, &m_unk1c44, 4);
    ReadF32LE(file, &m_unke58);
    ReadF32LE(file, &m_unke5c);
    ReadF32LE(file, &m_unke60);
    ReadF32LE(file, &m_unke64);
    ReadF32LE(file, &m_unk8a8);
    ReadF32LE(file, &m_unkbbc);
    ReadF32LE(file, &m_unkbc0);
    IKFile_ReadRef(file, &m_unk19dc);
    ReadU32LE(file, &m_unke28);
    ReadU32LE(file, &m_unke2c);
    ReadF32LE(file, &m_unke30);
    ReadF32LE(file, &m_unkbc8);
    ReadF32LE(file, &m_unkbcc);
    ReadF32LE(file, &m_unkbd0);
    ReadF32LE(file, &m_unkbd4);
    ReadF32LE(file, &m_unk8c4);
    ReadF32LE(file, &m_unk8c8);
    IKFile_ReadRef(file, &m_unk1b1c);
    IKFile_ReadRef(file, &m_unk1b20);
    ReadRaw(file, &m_unk1c48, 4);
    ReadRaw(file, &m_unk1c5c, 4);
    ReadRaw(file, &m_unk1c4c, 4);
    ReadRaw(file, &m_unk1c60, 4);
    ReadRaw(file, &m_unk1c50, 4);
    ReadRaw(file, &m_unk1c64, 4);
    ReadRaw(file, &m_unk1c54, 4);
    ReadRaw(file, &m_unk1c68, 4);
    ReadRaw(file, &m_unk1c58, 4);
    ReadRaw(file, &m_unk1c6c, 4);
    ReadF32LE(file, &m_unkcc8);
    ReadF32LE(file, &m_unkccc);
    ReadF32LE(file, &m_unkce8);
    ReadF32LE(file, &m_unkcec);
    IKFile_ReadRef(file, &m_unk1a78);
    IKFile_ReadRef(file, &m_unk1a7c);
    ReadF32LE(file, &m_unkd48);
    ReadF32LE(file, &m_unkd4c);
    ReadF32LE(file, &m_unkd50);
    ReadF32LE(file, &m_unkd54);
    ReadF32LE(file, &m_unkd58);
    ReadF32LE(file, &m_unkd5c);
    ReadF32LE(file, &m_unkd60);
    ReadF32LE(file, &m_unkd64);
    ReadF32LE(file, &m_unkd68);
    ReadF32LE(file, &m_unkd6c);
    ReadF32LE(file, &m_unkd70);
    ReadF32LE(file, &m_unkd74);
    ReadF32LE(file, &m_unke38);
    ReadF32LE(file, &m_unka00);
    ReadF32LE(file, &m_unka04);
    ReadF32LE(file, &m_unka08);
    ReadS32LE(file, &m_unk1c70);
    ReadS32LE(file, &m_unk1c84);
    ReadS32LE(file, &m_unk1c98);
    ReadS32LE(file, &m_unk1cac);
    ReadS32LE(file, &m_unk1c74);
    ReadS32LE(file, &m_unk1c88);
    ReadS32LE(file, &m_unk1c9c);
    ReadS32LE(file, &m_unk1cb0);
    ReadS32LE(file, &m_unk1c78);
    ReadU32LE(file, &m_unk1c8c);
    ReadS32LE(file, &m_unk1ca0);
    ReadS32LE(file, &m_unk1cb4);
    ReadS32LE(file, &m_unk1c7c);
    ReadU32LE(file, &m_unk1c90);
    ReadS32LE(file, &m_unk1ca4);
    ReadU32LE(file, &m_unk1cb8);
    ReadS32LE(file, &m_unk1c80);
    ReadS32LE(file, &m_unk1c94);
    ReadS32LE(file, &m_unk1ca8);
    ReadS32LE(file, &m_unk1cbc);
    ReadF32LE(file, &m_unke34);
    ReadF32LE(file, &m_unke3c);
    ReadF32LE(file, &m_unkbd8);
    ReadF32LE(file, &m_unkbdc);
    ReadF32LE(file, &m_unkbe0);
    ReadF32LE(file, &m_unkbe4);
    ReadF32LE(file, &m_unkbe8);
    IKFile_ReadRef(file, &m_unk1b24);
    ReadF32LE(file, &m_unkbec);
    ReadF32LE(file, &m_unka44);
    ReadF32LE(file, &m_unke40);
    ReadU32LE(file, &m_unkba0);
    ReadF32LE(file, &m_unkba4);
    ReadF32LE(file, &m_unkc54);
    ReadF32LE(file, &m_unkc58);
    ReadF32LE(file, &m_unkc64);
    IKFile_ReadRef(file, &m_unk1b28);
    IKFile_ReadRef(file, &m_unk1ae0);
    ReadF32LE(file, &m_unkc5c);
    ReadF32LE(file, &m_unkc60);
    ReadF32LE(file, &m_unkd08);
    ReadF32LE(file, &m_unkd10);
    ReadF32LE(file, &m_unkd14);
    ReadF32LE(file, &m_unk930);
    ReadU32LE(file, &m_unk934);
    ReadF32LE(file, &m_unk938);
    ReadF32LE(file, &m_unkafc);
    ReadF32LE(file, &m_unkb00);
    ReadF32LE(file, &m_unkb04);
    ReadF32LE(file, &m_unkb08);
    IKFile_ReadRef(file, &m_unk19e4);
    IKFile_ReadRef(file, &m_unk1a00);
    IKFile_ReadRef(file, &m_unk19f0);
    ReadU32LE(file, &m_unke44);
    ReadF32LE(file, &m_unke48);
    ReadF32LE(file, &m_unke4c);
    ReadF32LE(file, &m_unke50);
    ReadF32LE(file, &m_unke68);
    ReadF32LE(file, &m_unkcb8);
    for (int i = 0; i < 8; ++i) {
        IKFile_ReadRef(file, &m_apUnk1070[i][0]);
        IKFile_ReadRef(file, &m_apUnk1070[i][1]);
        IKFile_ReadRef(file, &m_apUnk1070[i][2]);
        IKFile_ReadRef(file, &m_apUnk1070[i][3]);
    }
    ReadF32LE(file, &m_unk9cc);
    ReadF32LE(file, &m_unk9d0);
    ReadF32LE(file, &m_unkcf0);
    ReadF32LE(file, &m_unkcf4);
    ReadF32LE(file, &m_unkcf8);
    ReadF32LE(file, &m_unkd84);
    ReadF32LE(file, &m_unk950);
    ReadF32LE(file, &m_unka0c);
    ReadF32LE(file, &m_unk9d4);
    ReadF32LE(file, &m_unk9d8);
    ReadF32LE(file, &m_unkd18);
    ReadF32LE(file, &m_unkcd0);
    ReadF32LE(file, &m_unkcd4);
    ReadF32LE(file, &m_unkcd8);
    ReadF32LE(file, &m_unkcdc);
    ReadF32LE(file, &m_unkce0);
    ReadF32LE(file, &m_unkce4);
    ReadF32LE(file, &m_unkbc4);
    ReadF32LE(file, &m_unka10);
    ReadF32LE(file, &m_unka14);
    ReadF32LE(file, &m_unka18);
    ReadU32LE(file, &m_unka1c);
    ReadF32LE(file, &m_unka20);
    ReadF32LE(file, &m_unk9dc);
    ReadF32LE(file, &m_unkd0c);
    ReadF32LE(file, &m_unkda4);
    ReadF32LE(file, &m_unkda8);
    ReadF32LE(file, &m_unkdac);
    ReadF32LE(file, &m_unkdb0);
    ReadF32LE(file, &m_unkdb4);
    ReadF32LE(file, &m_unkdc0);
    ReadF32LE(file, &m_unkdb8);
    ReadF32LE(file, &m_unkdc8);
    ReadF32LE(file, &m_unkdcc);
    ReadF32LE(file, &m_unkdd0);
    ReadF32LE(file, &m_unkdd4);
    ReadF32LE(file, &m_unkd78);
    ReadF32LE(file, &m_unkd7c);
    ReadF32LE(file, &m_unk9e0);
    ReadF32LE(file, &m_unkc70);
    ReadF32LE(file, &m_unk8ac);
    ReadS32LE(file, &m_unka48);
    ReadF32LE(file, &m_unka4c);
    ReadF32LE(file, &m_unka50);
    ReadF32LE(file, &m_unka54);
    IKFile_ReadRef(file, &m_unk147c);
    ReadF32LE(file, &m_unk8f0);
    ReadF32LE(file, &m_unka68);
    ReadF32LE(file, &m_unka6c);
    ReadS32LE(file, &m_unka58);
    ReadF32LE(file, &m_unka5c);
    ReadF32LE(file, &m_unka60);
    ReadF32LE(file, &m_unka64);
    ReadF32LE(file, &m_unkdd8);
    m_tsStartCarrying.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_unk19c4);
    IKFile_ReadRef(file, &m_unk19cc);
    m_tsHit.Load(file, K_LEVEL_PLATEFORMS);
    ReadF32LE(file, &m_unke78);
    ReadF32LE(file, &m_unke7c);
    ReadF32LE(file, &m_unke80);
    ReadF32LE(file, &m_unke88);
    ReadF32LE(file, &m_unke94);
    ReadF32LE(file, &m_unke98);
    ReadS32LE(file, &m_unke9c);
    ReadF32LE(file, &m_unkea0);
    ReadF32LE(file, &m_unkea4);
    IKFile_ReadRef(file, &m_unk1dbc);
    IKFile_ReadRef(file, &m_unk1b50);
    IKFile_ReadRef(file, &m_unk1b54);
    IKFile_ReadRef(file, &m_unk1b58);
    IKFile_ReadRef(file, &m_unk1b60);
    IKFile_ReadRef(file, &m_unk1b5c);
    IKFile_ReadRef(file, &m_unk1b64);
    ReadF32LE(file, &m_unkea8);
    ReadF32LE(file, &m_unkeac);
    IKFile_ReadRef(file, &m_unk1b6c);
    IKFile_ReadRef(file, &m_unk1b70);
    IKFile_ReadRef(file, &m_unk1b74);
    ReadF32LE(file, &m_unk8cc);
    IKFile_ReadRef(file, &m_pFlightImpulsionCpnt);
    ReadF32LE(file, &m_unka70);
    ReadF32LE(file, &m_unka74);
    ReadF32LE(file, &m_unk914);
    ReadF32LE(file, &m_unk918);
    ReadF32LE(file, &m_unk8d0);
    IKFile_ReadRef(file, &m_unk1dc4);
    ReadF32LE(file, &m_unk9e4);
    ReadF32LE(file, &m_unk9e8);
    ReadF32LE(file, &m_unkeb0);
    ReadF32LE(file, &m_unkeb4);
    ReadF32LE(file, &m_unke74);
    ReadF32LE(file, &m_unk900);
    ReadF32LE(file, &m_unk904);
    ReadF32LE(file, &m_unk908);
    ReadF32LE(file, &m_unk90c);
    ReadF32LE(file, &m_unk910);
    IKFile_ReadRef(file, &m_pFlightAimCone);
    ReadF32LE(file, &m_unk8d4);
    ReadF32LE(file, &m_unk8d8);
    IKFile_ReadRef(file, &m_unk1dc8);
    IKFile_ReadRef(file, &m_unk1ccc);
    IKFile_ReadRef(file, &m_unk1cd0);
    IKFile_ReadRef(file, &m_unk1cd4);
    IKFile_ReadRef(file, &m_unk1cd8);
    IKFile_ReadRef(file, &m_unk1cdc);
    IKFile_ReadRef(file, &m_unk1cf8);
    ReadF32LE(file, &m_unk1d00);
    IKFile_ReadRef(file, &m_unk1a04);
    ReadF32LE(file, &m_unkdc4);
    IKFile_ReadRef(file, &m_unk1ce0);
    IKFile_ReadRef(file, &m_unk1ce4);
    IKFile_ReadRef(file, &m_unk1ce8);
    IKFile_ReadRef(file, &m_unk1cec);
    IKFile_ReadRef(file, &m_unk1cf0);
    ReadF32LE(file, &m_unkeb8);
    ReadF32LE(file, &m_unkebc);
    ReadF32LE(file, &m_unkec0);
    ReadF32LE(file, &m_unke84);
    ReadF32LE(file, &m_unke8c);
    ReadF32LE(file, &m_unke90);
    IKFile_ReadRef(file, &m_unk1164);
    IKFile_ReadRef(file, &m_unk1168);
    IKFile_ReadRef(file, &m_unk1170);
    IKFile_ReadRef(file, &m_unk116c);
    ReadS32LE(file, &m_unkdbc);
    IKFile_ReadRef(file, &m_unk1dd4);
    IKFile_ReadRef(file, &m_unk1dd8);
    IKFile_ReadRef(file, &m_unk1ddc);
    IKFile_ReadRef(file, &m_unk1de0);
    IKFile_ReadRef(file, &m_unk1de4);
    IKFile_ReadRef(file, &m_unk1de8);
    IKFile_ReadRef(file, &m_unk1dec);
    IKFile_ReadRef(file, &m_unk1df0);
    return 1;
}

// 0x002dc3d8 CKHkS08Hero_ResetControlState_maybe
void CKHkS08Hero::ResetControlState() {
    float fVar2;
    ResetComboAndAttackCredits();
    if (m_ui8Hero == m_ui8TrackedLeader) {
        m_unk37c = 0.0f;
        fVar2 = 0.0f;
        m_unk384 = 0.0f;
        m_unk380 = fVar2;
        m_unk1378 = 0;
        m_unkec8 = m_unkec8 & 0xffffff7f;
        return;
    }
    m_unkefc = 0;
    m_unkef4 = 0;
    m_unkf10 = 0;
    m_unkf00 = 0;
    m_unkef8 = 0;
    m_unkf24 = 0;
    m_unkf08 = 0;
    m_unkf14 = 0;
    m_unkf0c = 0;
    m_unkf38 = 0;
    m_unkf1c = 0;
    m_unkf28 = 0;
    m_unkf20 = 0;
    m_unkf4c = 0;
    m_unkf30 = 0;
    m_unkf3c = 0;
    m_unkf34 = 0;
    m_unkf60 = 0;
    m_unkf44 = 0;
    m_unkf74 = 0;
    m_unkf50 = 0;
    m_unkf48 = 0;
    m_unkf58 = 0;
    m_unkf64 = 0;
    m_unkf5c = 0;
    m_unkf6c = 0;
    m_unkf78 = 0;
    m_unkf70 = 0;
    m_unkf88 = 0;
    m_unkf80 = 0;
    m_unkf8c = 0;
    m_unkf84 = 0;
    m_unkf9c = 0;
    m_unkfb0 = 0;
    m_unkf94 = 0;
    m_unkfa0 = 0;
    m_unkf98 = 0;
    m_unkfb4 = 0;
    m_unkfa8 = 0;
    m_unkfac = 0;
    m_unkec8 = m_unkec8 & 0xfffffffb;
    m_unkec8 = m_unkec8 & 0xffffff7f;
}

// 0x002d9410 CKHkS08Hero_ResetMotionState_maybe
void CKHkS08Hero::ResetMotionState(int32_t flag) {
    uint32_t uVar2;
    ResetMovementFromFrame(flag);
    ResetCombatState(flag);
    InitInputActionTable();
        SetUnk890(1.0f);  // vt+0x19c, TOC 0x1da0
    SetUnk894(1.0f);  // vt+0x198
    m_unkfd0 = m_unk64;
    m_unkfd4 = m_unk68;
    m_unkfd8 = m_unk6c;
    m_unkfdc = 0x0;
    uVar2 = 0x0;
    m_unkfe0 = 0x3f800000;
    m_unkfe4 = uVar2;
    m_unkfe8 = 0;
    m_unkff0 = m_unk64;
    m_unkff4 = m_unk68;
    m_unkff8 = m_unk6c;
    m_unkffc = 0x0;
    uVar2 = 0x0;
    m_unk1000 = 0x3f800000;
    m_unk1004 = uVar2;
    m_unk1008 = 0;
    m_unk1010 = m_unk64;
    uVar2 = 0x0;
    m_unk1014 = m_unk68;
    m_unk1018 = m_unk6c;
    m_unk101c = uVar2;
    uVar2 = 0x0;
    m_unk1020 = 0x3f800000;
    m_unk1024 = uVar2;
    m_unk1028 = 0;
    m_unk1030 = m_unk64;
    m_unk1034 = m_unk68;
    m_unk1038 = m_unk6c;
    m_unk103c = 0x0;
    uVar2 = 0x3f800000;
    m_unk1044 = 0x0;
    m_unk1040 = uVar2;
    m_unk1048 = 0;
    m_unk1050 = m_unk64;
    m_unk1054 = m_unk68;
    m_unk1058 = m_unk6c;
    m_unk105c = 0x0;
    uVar2 = 0x3f800000;
    m_unk1064 = 0x0;
    m_unk1060 = uVar2;
    m_unk1068 = 0;
    m_unk368 = m_unk368 & 0xfffffbff | 0x400;
    m_ui32HeroFlags358 = (m_ui32HeroFlags358 & 0xbfffffff | 0x40000000);
    m_unk1124 = 0x0;
    uVar2 = 0x0;
    m_unk112c = 0x0;
    m_unk1128 = uVar2;
    m_unk113c = 0;
    m_unk1130 = 0x0;
    uVar2 = 0x0;
    m_unk1138 = 0x0;
    m_unk1134 = uVar2;
    m_unk1148 = 0;
    m_unk1144 = 0;
    m_unk1140 = 0;
}

// 0x002df070 CKHkS08Hero_InitLocomotionAnimSubStateMachines
void CKHkS08Hero::InitLocomotionAnimSubStateMachines() {
    m_unk183c = 0x00b9a150u;
    m_unk1844 = 0x00b9a190u;
    m_unk184c = 0x00b9a198u;
    m_unk1854 = 0x00b9a1f8u;
    m_unk185c = 0x00b9a1f0u;
    m_unk1864 = 0x00b99fe0u;
    m_unk186c = 0x00b9a0b8u;
    m_unk1874 = 0x00b9a020u;
    m_unk1884 = 0x00b9a000u;
    m_unk188c = 0x00b99fd8u;
    m_unk1894 = 0x00b99fd0u;
    m_unk1840 = 0;
    m_unk1848 = 0;
    m_unk1850 = 0;
    m_unk18a4 = 0x00b9a0c0u;
    m_unk189c = 0x00b99ff8u;
    m_unk18ac = 0x00b99ff0u;
    m_unk18b4 = 0x00b9a240u;
    m_unk18bc = 0x00b9a110u;
    m_unk18c4 = 0x00b9a238u;
    m_unk187c = 0x00b9a200u;
    m_unk1858 = 0;
    m_unk1860 = 0;
    m_unk1868 = 0;
    m_unk1870 = 0;
    m_unk1878 = 0;
    m_unk1888 = 0;
    m_unk1890 = 0;
    m_unk1898 = 0;
    m_unk18a0 = 0;
    m_unk18a8 = 0;
    m_unk18b0 = 0;
    m_unk18b8 = 0;
    m_unk18c0 = 0;
    m_unk18c8 = 0;
    m_unk1880 = 0;
    m_unk18d1 = 0x12;
    m_unk18cc = &m_unk183c;
    m_ui8FlyAnimState = 0xff;
    m_unk18d4 = 0x00b9a108u;
    m_unk18dc = 0x00b9a1a8u;
    m_unk18e4 = 0x00b9a1a0u;
    m_unk18ec = 0x00b9a028u;
    m_unk18f4 = 0x00b9a050u;
    m_unk18fc = 0x00b9a1e8u;
    m_unk1904 = 0x00b9a1e0u;
    m_unk190c = 0x00b9a118u;
    m_unk1914 = 0x00b99fe8u;
    m_unk191c = 0x00b99fc8u;
    m_unk1924 = 0x00b9a120u;
    m_unk192c = 0x00b9a260u;
    m_unk1934 = 0x00b9a258u;
    m_unk193c = 0x00b9a248u;
    m_unk1944 = 0x00b9a1d8u;
    m_unk18d8 = 0;
    m_unk18e0 = 0;
    m_unk18e8 = 0;
    m_unk18f0 = 0;
    m_unk18f8 = 0;
    m_unk1900 = 0;
    m_unk194c = 0x00b9a1d0u;
    m_unk1954 = 0x00b9a1c8u;
    m_unk1908 = 0;
    m_unk1910 = 0;
    m_unk1918 = 0;
    m_unk1920 = 0;
    m_unk1928 = 0;
    m_unk1930 = 0;
    m_unk1938 = 0;
    m_unk1940 = 0;
    m_unk1948 = 0;
    m_unk1950 = 0;
    m_unk1958 = 0;
    m_unk1961 = 0x11;
    m_ui8GroundAnimState = 0xff;
    m_unk195c = &m_unk18d4;
    m_unk1994 = 0x00b9a088u;
    m_unk19a0 = 0;
    m_unk1964 = 0x00b9a090u;
    m_unk196c = 0x00b9a148u;
    m_unk1974 = 0x00b9a1b8u;
    m_unk197c = 0x00b9a1b0u;
    m_unk1984 = 0x00b9a100u;
    m_unk198c = 0x00b9a298u;
    m_unk199c = 0x00b9a1c0u;
    m_unk1968 = 0;
    m_unk1970 = 0;
    m_unk1978 = 0;
    m_unk1980 = 0;
    m_unk1988 = 0;
    m_unk1990 = 0;
    m_unk1998 = 0;
    m_unk19a9 = 8;
    m_unk19a4 = &m_unk1964;
    m_ui8ClimbAnimState = 0xff;
}

// 0x002df3e0 CKHkS08Hero_Start
// 0x002d9730 CKHkS08Hero_Pause
void CKHkS08Hero::Pause() {
    if (m_unk1a08 != nullptr) {
        IKFx* cursor = m_unk1a08;
        cursor->StopAndRelease(this);  // vt+0x58
        m_unk1a08 = nullptr;
    }
}

// 0x002d96e8 CKHkS08Hero_Resume: ShouldStayClimbing is asked for its answer only (the base's Resume is empty).
void CKHkS08Hero::Resume() {
    if (ShouldStayClimbing() == 0) {
        // CKHkS08Hero_BaseResume_maybe 0x344e18: empty.
    }
}

void CKHkS08Hero::Start() {
    IKHkHero::Start();
    ResetMotionState(1);
    ResetToDefaultState();
    ResetMotionState(1);
    m_unked8 = 0;
    m_unkec4 = 0;
    m_unkec8 = 0;
    m_unkecc = 0;
    m_ui32StatusFlagsED0 = 0;
    m_ui32StatusFlagsED4 = 0;
    ResetMotionState(1);
    InitLocomotionAnimSubStateMachines();
    m_pCurrentComboNode = m_unk1a8c;
    DisableSwingTrails();
    static_cast<CKS08CarrierHero*>(m_pCarrierHero)->Reset();  // vt+0x68 0x4b4118
}

// 0x002df308 CKHkS08Hero_Restart (vt+0x54, the level restart): the default state (which makes the controlled hero the
// group's focused dragon again: ApplyControlAssignment), no swing trails, the motion state and the locomotion
// sub-machines reset, the root combo back, a running ability cancelled (vt+0x5c with 0), the status words cleared and
// the carried object dropped (the carrier's vt+0x70).
void CKHkS08Hero::Restart() {
    ResetToDefaultState();  // 0x00348ac0
    DisableSwingTrails();   // 0x00334e20
    ResetMotionState(1);    // 0x002d9410
    InitLocomotionAnimSubStateMachines();  // 0x002df070
    m_pCurrentComboNode = m_unk1a8c;
    if (m_pActiveAbility != nullptr) static_cast<CKAbilityElement*>(m_pActiveAbility)->Stop(0);  // vt+0x5c
    m_unked8 = 0;
    m_unkec4 = 0;
    m_unkec8 = 0;
    m_unkecc = 0;
    m_ui32StatusFlagsED0 = 0;
    m_ui32StatusFlagsED4 = 0;
    static_cast<CKS08CarrierHero*>(m_pCarrierHero)->DropCarriedObjectAndReset();  // vt+0x70 0x4b3e40
}

// 0x009bd698 CKHkS08Hero_vf198 (an inline copy in the original): a float stored at +0x894.
void CKHkS08Hero::SetUnk894(float value) {
    m_unk894 = value;
}

// 0x009bd6a8 CKHkS08Hero_vf19C: a float at +0x890; a value that is not above 0 (TOC 0x1da4) stores 1.0 (TOC 0x1da0).
void CKHkS08Hero::SetUnk890(float value) {
    m_unk890 = (value <= 0.0f) ? 1.0f : value;
}

// 0x002d8c58 CKHkS08Hero_vfD4 (vt+0xd4): five state bytes cleared.
void CKHkS08Hero::VfD4() {
    m_unk106d = 0;
    m_unkfed = 0;
    m_unk100d = 0;
    m_unk102d = 0;
    m_unk104d = 0;
}

// 0x002dbb50 CKHkS08Hero_InitAnimBlendSlot (vt+0xd8): the embedded blend slot takes the scene node's
// animation controller.
void CKHkS08Hero::InitAnimBlendSlot() {
    m_animBlendSlot10f0.Init(static_cast<CAnimatedNode*>(m_pKGLObject)->m_pController);  // 0x0007a710
}

// 0x002dba30 CKHkS08Hero_OnAttachToObject (vt+0x120)
void CKHkS08Hero::OnAttachToObject() {
    m_unkedc = 0;
    m_unkec8 &= ~4u;
    CKImpulsionCpnt* impulsion = static_cast<CKImpulsionCpnt*>(m_pFlightImpulsionCpnt);
    impulsion->m_fImpulseTimer = 0.0f;
    impulsion->m_fValue = 0.0f;
    impulsion->m_fSpeed = 0.0f;
    if (m_unk90->GetClassID() == 0x247) return;  // vt+0x18
    // The zero vector 0x00c50d64 (x, then z, then y as the original stores them).
    m_unk1268 = 0.0f;
    m_unk1270 = 0.0f;
    m_unk126c = 0.0f;
    SetMovementMode(0);  // 0x340c18
    m_unkec8 &= ~0x80u;
    m_ui32StatusFlagsED0 &= ~0xcu;
    m_fCurVSpeed = 0.0f;
    m_unk5b4 = 0.0f;
    m_unk5bc = 0.0f;
    m_unk5b8 = 0.0f;
}

// A carried object's weight (its vt+0x104) by its class: 0x009c5460 CKHkS08TransportableKey_vf104 (TOC +0x6334, 0.0),
// 0x009c5550 CKHkS08TransportableWeight_vf104 (+0x18c), 0x009c5ea8 CKHkS08PowerBucket_vf104 (+0x1f4 while the byte +0x1f0
// is set, else +0x18c). The hero carries no other class (the carrier's pickups are these three).
float CarriedObjectWeight(IKSerializable* object) {
    switch (object->GetClassID()) {  // vt+0x18
    case 0xc3: {  // CKHkS08PowerBucket (key 0x30c2)
        const CKHkS08PowerBucket* bucket = static_cast<const CKHkS08PowerBucket*>(object);
        return (bucket->m_unk1f0 >> 24) != 0 ? bucket->m_unk1f4 : bucket->m_unk18c;
    }
    case 0xc5:  // CKHkS08TransportableWeight (key 0x3142)
        return static_cast<const CKHkS08TransportableWeight*>(object)->m_unk18c;
    default:
        return 0.0f;
    }
}

// 0x002dc5a0 CKHkS08Hero_OnDetachFromObject (vt+0x124)
void CKHkS08Hero::OnDetachFromObject() {
    if (m_unk90->GetClassID() == 0x247) return;  // vt+0x18
    // The zero vector 0x00c50d64 (x, then z, then y as the original stores them).
    m_unk1268 = 0.0f;
    m_unk1270 = 0.0f;
    m_unk126c = 0.0f;
    SetMovementMode(0);  // 0x340c18
    m_unkec8 &= 0xffffff7fu;
    m_ui32StatusFlagsED0 &= 0xfffffff3u;
}

// 0x002dbde0 CKHkS08Hero_LockedUpdate (vt+0x80): a locked hero (a cinematic holds it) counts the model fade timer
// +0x1178 and the link bolt timer +0x1184 down by the frame's delta while positive, then fades its model and updates
// the partner link bolts.
void CKHkS08Hero::Vf80(IKTime* clock) {
    const float dt = clock->m_afDeltaTime[0];
    if (m_unk1178 > 0.0f) m_unk1178 = m_unk1178 - dt;  // TOC1 +0x1da4 = 0.0 (ble: NaN keeps it)
    if (m_unk1184 > 0.0f) m_unk1184 = m_unk1184 - dt;
    UpdateModelFade(dt);         // 0x003346d8
    UpdatePartnerLinkBolt();     // 0x00337898
}

// 0x002dbe68 CKHkS08Hero_MessageProc (vt+0x1c): HeroBaseMessageProc first (0x00348220), then the hero's own messages:
// 0x94d clears +0xec8 bits 22 / 23; 0xc13 drops the carried object (+0xfb8's vt+0x80, its vt+0xf8 with the null
// vector) and clears them too; 0xc14 (`data`: the strength) while climbing and +0x1744 clear starts the 0.05 s downward
// impulse record +0x1758 (TOC +0x1e20, the down vector 0x00c50d7c); 0xc19 shows the carried power bucket (vt+0x194 1);
// 0xc1c sets +0xed0 bit 2 on the hero the player does not control; 0xc20..0xc23 set the bytes +0x1174 / +0x1175 (and
// a positive `data` the times +0x1178 / +0x117c), 0xc24 / 0xc25 the byte +0x1181 (and +0x1184 / +0x1188); 0x400 writes
// hot spot 4's position into the aim query, 0x402 answers "hittable". The answer: 3 or 2 from either side wins, else 0
// when the hero handled it, else the base's (0 or 1). The jump table 0x002dbfe4 (TOC +0x1e1c).
int32_t CKHkS08Hero::MessageProc(uint16_t message, void* data) {
    const int32_t base = HeroBaseMessageProc(message, data);  // 0x00348220
    const uint32_t category = (message >> 8) & 0xffu;
    const uint32_t id = message & 0xffu;
    int32_t own = 1;
    // The timers of 0xc20..0xc25: a positive `data` (TOC +0x1da4 0.0; ble) sets both of a pair.
    auto timers = [&](float* a, float* b) {
        const float value = *static_cast<const float*>(data);
        if (!(value <= 0.0f)) {
            *a = value;
            *b = value;
        }
    };
    if (category == 9) {
        if (id == 0x4d) {
            m_unkec8 &= 0xff3fffffu;
            own = 0;
        }
    } else if (category == 0xc) {
        switch (id) {
        case 0x13: {
            own = 0;
            CKS08CarrierHero* carrier = static_cast<CKS08CarrierHero*>(m_pCarrierHero);
            if (carrier == nullptr) break;
            IKSerializable* carried = carrier->GetCarriedObject();  // vt+0x80
            if (carried == nullptr) break;
            // STUB(C2.8: carrying): the carried object's vt+0xf8 (the carrier, the null vector 0x00c50d64 = TOC +0x1dc0);
            // LVL010 carries nothing before the power buckets.
            DOTD_STUB_ONCE("CKHkS08Hero_MessageProc 0x2dbe68: message 0xc13, the carried object's vt+0xf8 (C2.8)");
            m_unkec8 &= 0xff3fffffu;
            break;
        }
        case 0x14: {
            if (data == nullptr) {
                own = 2;
                break;
            }
            own = 0;
            if (ShouldStayClimbing() == 0 || m_unk1744 != 0) break;  // 0x00342fa8
            // The impulse record +0x1758 (HeroTimedImpulse's layout): magnitude `data`, duration 0.05, started along
            // the down vector (the null vector first, as the inlined reset writes it).
            const float duration = 0.0500000007f;  // TOC +0x1e20
            m_unk1758 = *static_cast<const float*>(data);
            std::memcpy(&m_unk175c, &duration, sizeof duration);
            m_unk1764 = 0.0f;  // 0x00c50d64
            m_unk1768 = 0.0f;
            m_unk176c = 0.0f;
            m_unk1770 = 0;
            m_unk1774 = 0;
            m_unk1760 = 0;
            m_unk1764 = 0.0f;  // 0x00c50d7c (0, -1, 0)
            m_unk1768 = -1.0f;
            m_unk176c = 0.0f;
            m_unk1774 = 0;
            std::memcpy(&m_unk1770, &m_unk175c, sizeof m_unk1770);
            m_unk1760 = 1;
            break;
        }
        case 0x19: {
            own = 0;
            IKSerializable* bucket = GetCarriedPowerBucket();  // 0x003401f0
            if (bucket != nullptr) static_cast<CKHkS08PowerBucket*>(bucket)->SetCarriedShown(1);  // vt+0x194
            break;
        }
        case 0x1c:
            own = 0;
            if (m_ui8Hero != m_ui8TrackedLeader) m_ui32StatusFlagsED0 = (m_ui32StatusFlagsED0 & ~4u) | 4u;
            break;
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
            if (data == nullptr) {
                own = 2;
                break;
            }
            timers(&m_unk1178, &m_unk117c);
            m_unk1174 = (id == 0x20 || id == 0x22) ? 1 : 0;
            m_unk1175 = (id == 0x22 || id == 0x23) ? 1 : 0;
            own = 0;
            break;
        case 0x24:
        case 0x25:
            if (data == nullptr) {
                own = 2;
                break;
            }
            timers(&m_unk1184, &m_unk1188);
            m_unk1181 = id == 0x24 ? 1 : 0;
            own = 0;
            break;
        default:
            break;
        }
    } else if (category == 4) {
        if (id == 0) {
            if (data == nullptr) {
                own = 2;
            } else {
                CVector3 at;
                static_cast<CSGHotSpot*>(GetHotSpot(4))->GetWorldPosition(&at);  // 0x00361b70, 0x000ce790
                static_cast<SAimPointQuery*>(data)->m_point = at;
                own = 0;
            }
        } else if (id == 2) {
            if (data == nullptr) {
                own = 2;
            } else {
                *static_cast<uint8_t*>(data) = 1;
                own = 0;
            }
        }
    }
    if (base == 3) return 3;
    if (own == 2 || base == 2) return 2;
    if (own == 0) return 0;
    return base != 0 ? 1 : 0;
}

// 0x002dacb0 CKHkS08Hero_CanAttachTo_maybe (vt+0xe0): whether the hero may attach to `object` (`count`: the carrier's
// attachments, _maybe). Always to the classes 0x18c2 / 0xa88c / 0x784c; with +0xed4 bit 3 only to a 0x91cc. Not
// while attached to a 0x91cc, nor from a 0x1a02 to a 0x1a02, nor with +0xed4 bit 6; a contextual mechanism (0x2a82)
// when the hero is its own tracked leader; not during a combo (unless +0xec8 bit 27); and with a carrier hero
// holding an object, only for a count above 1.
uint8_t CKHkS08Hero::CanAttachTo(IKSerializable* object, int32_t count) {
    if (object->IsKindOfClass(0x18c2) != 0 || object->IsKindOfClass(0xa88c) != 0 || object->IsKindOfClass(0x784c) != 0) {
        return 1;
    }
    // 0x0032a428 CKHkS08Hero_GetFlagED4Bit3_maybe
    if (((m_ui32StatusFlagsED4 >> 3) & 1u) != 0 && object->IsKindOfClass(0x91cc) == 0) return 0;
    if (m_unk90 != nullptr) {
        if (m_unk90->IsKindOfClass(0x91cc) != 0) return 0;
        if (m_unk90 != nullptr && m_unk90->IsKindOfClass(0x1a02) != 0 && object->IsKindOfClass(0x1a02) != 0) return 0;
    }
    if ((m_ui32StatusFlagsED4 & 0x40u) != 0) return 0;
    if (m_ui8Hero == m_ui8TrackedLeader && object->IsKindOfClass(0x2a82) != 0) return 1;
    if (IsAnyComboKindActive() != 0 && (m_unkec8 & 0x8000000u) == 0) return 0;  // 0x002fd030
    CKS08CarrierHero* carrier = static_cast<CKS08CarrierHero*>(m_pCarrierHero);
    if (carrier == nullptr) return 1;
    if (carrier->GetCarriedObject() == nullptr) return 1;  // vt+0x80
    return count > 1 ? 1 : 0;
}

// 0x002db098 CKHkS08Hero_PostLoad
int32_t CKHkS08Hero::PostLoad(int32_t type) {
    IKHkHero::PostLoad(type);  // 0x00346400
    // The blows of the combo tree learn their hero (vt+0x98 of CKS08HeroBlow, 0x009bec20: a byte at +0x2c).
    for (uint32_t i = 0; i < m_unk1a2c; ++i) static_cast<CKS08HeroBlow*>(m_apUnk1a24[i])->m_ui8Hero = m_ui8Hero;
    m_pCurrentComboNode = m_unk1a8c;
    if (type == K_LEVEL_PLATEFORMS) {
        m_unk16d8 = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // RwMatrixCreate_Thunk 0x0023fa68
        m_unk16d4 = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
        // The three callbacks are the PS3's function descriptors (TOC1 +0x1ac0 / +0x1ac4 / +0x1ac8: 0xb9b258,
        // 0xb9b360, 0xb9b308; CallDynamicHook maps them); the dynamic service calls them each physics step.
        CKSrvDynamic* dynamic = static_cast<CKSrvDynamic*>(g_pEngine->m_srvDynamic);
        dynamic->RegisterHook(this, 0, 200, {0x00b9b258u, 0}, {0x00b9b360u, 0}, {0x00b9b308u, 0});
        dynamic->SetNativeDispatch(this, &CKHkS08Hero::DispatchDynamicHook);  // DOTD
        m_unk16dc = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
        m_unk16e0 = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
        m_unk16e4 = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
        m_unk16e8 = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
        m_unk16ec = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
        m_unk16f0 = reinterpret_cast<CMatrix34*>(RwMatrixCreate());
        m_unk1724 = 0.4f;  // TOC1 +0x1ae0: 0x3ecccccd
        m_pAbilityHost = nullptr;
        m_tsStartCarrying.PostLoad(0);  // TriggerEventList_PostLoad_maybe 0x00236330
        m_tsHit.PostLoad(0);
        m_unk1a08 = nullptr;
        m_unk1dcc = nullptr;
    }
    // The first node of each of the eight attach sets is marked (bit 2 of its scene properties).
    for (uint32_t set = 0; set < 8; ++set) {
        if (m_apUnk1070[set][0] != nullptr) {
            CSGLeaf* node = static_cast<CSGLeaf*>(m_apUnk1070[set][0]);
            node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
        }
    }
    m_unk19d0 = nullptr;
    m_unk19b8 = nullptr;
    m_unk19c0 = nullptr;
    m_unk19c8 = nullptr;
    SceneNode_SetVisibleInLayer(static_cast<CSGLeaf*>(m_unk1de0), 1, 0, 0);  // 0x005832a8
    return 1;
}

// 0x002db9d8 CKHkS08Hero_ClearMovementFloatFields_maybe
void CKHkS08Hero::ClearMovementFloatFields() {
    m_unk1778 = 0;
    m_unk177c = 0;
    m_unk115c = 0;
    m_unk1160 = 0;
    m_unk1780 = 0;
    m_unk1784 = 0;
    m_unk1788 = 0;
    m_unk1618 = 0;
    m_unk1350 = 0;
    m_unk1348 = 0;
    m_unk134c = 0;
    m_unk1354 = 0;
    m_unk1b04 = 0;
    m_unk1afc = 0;
    m_unk1b00 = 0;
}

// 0x002de6d0 UpdateCKHkS08Hero (vt+0x7c): the hero's frame. Its timers run down (+0x1784 / +0x134c / +0x1354 say
// which ran out this frame), the per-frame flags clear, the frame time is kept (+0x88c dt, +0x1548 the time), the
// player's dragon counts its play time; then the contacts, the carrier (the object the hero carries) and the moving
// ground, UpdateHeroMovementAndContacts, the carry triggers, the camera target and the movement-mode history, the
// status (armor, timed damage) and the AI partner's lost timers.
void CKHkS08Hero::Update(IKTime* clock) {
    const float dt = clock->m_afDeltaTime[0];
    if (m_unk1778 > 0.0f) m_unk1778 = m_unk1778 - dt;
    if (m_unk177c > 0.0f) m_unk177c = m_unk177c - dt;
    if (m_unk115c > 0.0f) m_unk115c = m_unk115c - dt;
    if (m_unk1160 > 0.0f) m_unk1160 = m_unk1160 - dt;
    m_unk1784 = 0;
    if (m_unk1780 > 0.0f) {
        m_unk1780 = m_unk1780 - dt;
        if (m_unk1780 <= 0.0f) m_unk1784 = 1;
    }
    if (m_unk1788 > 0.0f) m_unk1788 = m_unk1788 - dt;
    if (m_unk1618 > 0.0f) m_unk1618 = m_unk1618 - dt;
    m_unk134c = 0;
    if (m_unk1348 > 0.0f) {
        m_unk1348 = m_unk1348 - dt;
        if (m_unk1348 <= 0.0f) m_unk134c = 1;
    }
    m_unk1354 = 0;
    if (m_unk1350 > 0.0f) {
        m_unk1350 = m_unk1350 - dt;
        if (m_unk1350 <= 0.0f) m_unk1354 = 1;
    }
    if (m_unk1afc > 0.0f) m_unk1afc = m_unk1afc - dt;
    if (m_unk1b00 > 0.0f) m_unk1b00 = m_unk1b00 - dt;
    if (m_unk1b04 > 0.0f) m_unk1b04 = m_unk1b04 - dt;
    m_unkec4 &= 0xefffffffu;
    m_unkecc &= 0xfffffaf7u;
    m_ui32StatusFlagsED0 &= 0xffffffbfu;
    m_unkecc &= 0xfdf7ffffu;
    m_ui32StatusFlagsED0 &= 0xefffffffu;
    m_ui32StatusFlagsED4 &= 0xfffffffdu;
    if (m_unk1dd0 == 0) m_unk1dd1 = 0;
    m_unk1dd0 = 0;
    m_ui32StatusFlagsED4 &= 0xffffffdfu;
    m_unk88c = clock->m_afDeltaTime[0];
    m_unk1548 = clock->m_afCurrentTime[0];
    if (m_ui8TrackedLeader == m_ui8Hero) {
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
        IKSerializable* structure = manager->m_gameStructure;
        AddDragonPlayTime(structure, m_ui8TrackedLeader, m_unk88c);  // 0x0050f288 (f1 still holds the frame time)
        CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
        if (group->m_ui8ControlledHeroCount < 2 || group->m_apControlledHeroes[0] == this) {  // GetControlledHeroCount 0x002ca288
            AddPlayerSlotPlayTime(structure, 0, m_unk88c);  // 0x0050f2a8
        } else {
            AddPlayerSlotPlayTime(structure, 1, m_unk88c);
        }
    }
    ProcessHeroContactList();  // 0x002d8f38
    CKS08CarrierHero* carrier = static_cast<CKS08CarrierHero*>(m_pCarrierHero);
    const bool carriedBefore = carrier->GetCarriedObject() != nullptr;  // vt+0x80
    carrier->UpdateStateMachine(clock);                                 // vt+0x74
    const bool carriedAfter = carrier->GetCarriedObject() != nullptr;
    if (carrier->GetCarriedObject() != nullptr) {
        m_unkec8 = (m_unkec8 & 0xff3fffffu) | 0xc00000u;
        // CKGrpS08Hero_GetMaxPartnerDistance_maybe 0x2ce518 (its answer is not used), then the ground: a hero drawn this
        // frame (node +0x16 against the render frame counter 0x00c29694) over a ground of property 0x200 (engine flag
        // bit 1 and property bit 1 clear) less than 0.25 above it drops a carried weight (class 0x3142).
        const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
        if (static_cast<const CSGLeaf*>(m_pKGLObject)->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter &&
            ground != nullptr && (ground->m_ui16PropertiesFlags & 0x200u) != 0 &&
            ((ground->m_ba16EngineFlags >> 1) & 1u) == 0 && (ground->m_ui16PropertiesFlags & 2u) == 0 &&
            GetHeightAboveGround() < 0.25f &&  // 0x0032a008; TOC +0x1e64 (bge: a NaN keeps it)
            carrier->GetCarriedObject()->IsKindOfClass(0x3142) != 0) {
            // STUB(C2.8 carry-mechs): the carried weight's vt+0xf8 (CKHkS08TransportableWeight_vfF8 0x4b4d18 / the power
            // bucket's 0x4d3ae8: the drop, with the carrier and the zero vector 0x00c50d64) belongs to the carry-mechs
            // package's transportable classes; the hero's part (the condition and the flags) is ported.
            DOTD_STUB_ONCE("UpdateCKHkS08Hero: the carried weight's drop vt+0xf8 (C2.8 carry-mechs)");
            m_unkec8 &= 0xff3fffffu;
        }
    }
    m_unk1258 = 0.0f;
    if (carrier != nullptr && carrier->GetCarriedObject() != nullptr) {
        m_unk1258 = CarriedObjectWeight(carrier->GetCarriedObject());  // vt+0x104
    }
    UpdateField794ByAnimAndElementLevel();  // 0x003101e8
    IKSerializable* climbGround = nullptr;
    if ((m_unkec8 & 0x800u) == 0) {
        if (ShouldStayClimbing() == 0 || m_pCurrentClimbZone == nullptr) {  // 0x00342fa8
            m_unkecc &= 0xffffbfffu;
        } else {
            climbGround = m_pCurrentClimbZone->GetGroundByIndex(0);  // 0x00456bf0: the zone's moving body's first ground
            m_unkecc = (m_unkecc & 0xffffbfffu) | 0x4000u;
        }
    } else {
        m_unkecc = (m_unkecc & 0xffffbfffu) | 0x4000u;
        IKSerializable* ground = m_gcContact11FC.m_pGround;
        if (ground != nullptr && ground->GetClassID() == 0x13) climbGround = ground;  // vt+0x18
    }
    if ((m_unkecc & 0x4000u) == 0) {
        // The moving-ground matrix (+0x16f0) back to the identity (flags 0x20003), in the original's store order.
        CMatrix34* matrix = m_unk16f0;
        matrix->m_right.x = 1.0f;  // TOC +0x1da0
        matrix->m_ui32Flags = 0x20003u;
        matrix->m_pos.x = 0.0f;
        matrix->m_at.z = 1.0f;
        matrix->m_up.y = 1.0f;
        matrix->m_up.x = 0.0f;
        matrix->m_right.z = 0.0f;
        matrix->m_right.y = 0.0f;
        matrix->m_at.y = 0.0f;
        matrix->m_at.x = 0.0f;
        matrix->m_up.z = 0.0f;
        matrix->m_pos.z = 0.0f;
        matrix->m_pos.y = 0.0f;
    } else if (FollowDynamicGround(clock, climbGround) && (m_unkec8 & 0x800u) != 0) {  // 0x002f96c8
        // Carried while +0xec8 bit 11: the move +0x11cc against the walls; slid along one, it turns back from it.
        CLine line;
        line.m_start = {m_unk54c, m_unk550, m_unk554};
        line.m_VectDir = {m_unk11cc, m_unk11d0, m_unk11d4};
        CSlideGroundEdgeDatasOut slide;
        if (static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->ResolveWallSegmentMovement(&line, 0.0f, &slide, nullptr,
                                                                                                nullptr, 1) == 2) {
            m_unk11d0 = -slide.m_v3Normal.y;
            m_unk11d4 = -slide.m_v3Normal.z;
            m_unk11cc = -slide.m_v3Normal.x;
        }
    }
    const bool carriedBeforeMove = carrier->GetCarriedObject() != nullptr;
    UpdateMovementAndContacts(clock);  // 0x00347530
    const bool carriedAfterMove = carrier->GetCarriedObject() != nullptr;
    if (!carriedBefore) {
        if (carriedAfter) QueueTriggerSignals(&m_tsStartCarrying);  // 0x00236338
    } else if (!carriedAfter) {
        m_unkec8 &= 0xff3fffffu;
    }
    if (!carriedBeforeMove) {
        if (carriedAfterMove) QueueTriggerSignals(&m_tsStartCarrying);
    } else if (!carriedAfterMove) {
        m_unkec8 &= 0xff3fffffu;
    }
    UpdateModeFlagsAndTetherTimers();  // 0x002dd340
    UpdateHeroStatusAndTimedDamage();  // 0x002fef58
    m_unkecc &= 0xffffcffdu;
    m_bMovementModeChanged = 0;
    m_unkecc &= 0xff7fffdfu;
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    group->m_ui32PairStateFlags = (group->m_ui32PairStateFlags & 0xfffffbffu) | 0x400u;
    m_ui32StatusFlagsED0 &= 0xdfffffffu;
    if (m_ui8Hero == m_ui8TrackedLeader) m_unk368 &= 0xffffdfffu;
    UpdateField1348Timers();  // 0x0033d8f0
}

// 0x002d8f38 ProcessHeroContactList: the climb zone bookkeeping (the zone of last frame kept when it changed; this
// frame's zone, the zone flag +0x1676 and +0x16a0 cleared; +0x16b8 / +0x16c4 unless their status bits of +0xec4), the
// climbing volume (+0x54[8]: on while the climb flags ask for it, else off), then every collision of the hero's volumes
// (9 per dragon, 0x00a704c8): the damage and impulse it gives (HandleHeroContactDamageAndImpulse), the push +0x5e4
// clamped to max(+0x12cc, 1) * dt * 5 (scaled down to that length), and the climb zones' contacts.
void CKHkS08Hero::ProcessHeroContactList() {
    if (m_pHeldClimbZone != 0 && m_pHeldClimbZone != m_unk169c) {
        m_unk1698 = m_unk169c;
        m_unk169c = m_pCurrentClimbZone;
    }
    const uint32_t status = m_unkec4;
    m_pCurrentClimbZone = 0;
    m_unk1676 = 0;
    m_unk16a0 = 0;
    if ((status & 0x20000000u) == 0) m_unk16b8 = 0;
    if ((status & 0x40000000u) == 0) m_unk16c4 = 0;
    if (GetCollisionVolume8() != nullptr) {
        bool switchOff = true;
        if (m_unk1679 != 0 && GetClimbFlag1627Or1626And1628() == 0 &&
            (static_cast<IKBoundingVolume*>(GetCollisionVolume8())->m_ba8Infos & 1) == 0) {
            SetCollisionVolumeEnabled(static_cast<IKBoundingVolume*>(GetCollisionVolume8()), 1);  // 0x00352f10
            switchOff = false;
        } else if (m_unk1679 != 0 && GetClimbFlag1627Or1626And1628() == 0) {
            switchOff = false;
        }
        if (switchOff && (static_cast<IKBoundingVolume*>(GetCollisionVolume8())->m_ba8Infos & 1) != 0) {
            SetCollisionVolumeEnabled(static_cast<IKBoundingVolume*>(GetCollisionVolume8()), 0);
        }
    }
    static const uint8_t kVolumeCount[2] = {9, 9};  // 0x00a704c8, by dragon
    static const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64
    for (uint32_t i = 0; i < kVolumeCount[m_ui8Hero]; ++i) {
        IKBoundingVolume* volume = static_cast<IKBoundingVolume*>(m_apBoundings[i]);
        for (ICollision* collision = static_cast<ICollision*>(volume->m_CollisionResList); collision != nullptr;
             collision = collision->m_pNext) {
            IKBoundingVolume* own;
            IKBoundingVolume* other;
            if (static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1())->m_pOwner == this) {
                own = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1());
                other = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume2());
            } else {
                own = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume2());
                other = static_cast<IKBoundingVolume*>(collision->GetBoundingVolume1());
            }
            HandleHeroContactDamageAndImpulse(collision, own, other);  // 0x0030ce40
            const float length =
                std::sqrt(ppc::fmadds(m_unk5ec, m_unk5ec, ppc::fmadds(m_unk5e4, m_unk5e4, m_unk5e8 * m_unk5e8)));
            const float factor = m_unk12cc > 1.0f ? m_unk12cc : 1.0f;
            const float limit = (factor * m_unk88c) * 5.0f;
            if (!(limit >= length)) {
                const float scale = ((m_unk12cc > 1.0f ? m_unk12cc : 1.0f) * m_unk88c) * 5.0f / length;
                m_unk5ec = ppc::fmadds(scale, m_unk5ec, kNullVector.z);
                m_unk5e4 = ppc::fmadds(scale, m_unk5e4, kNullVector.x);
                m_unk5e8 = ppc::fmadds(scale, m_unk5e8, kNullVector.y);
            }
            HandleClimbZoneContact(collision, own, other);  // 0x002f9fa8
        }
    }
}



// 0x002dc730 CKHkS08Hero_UpdateMovement (vt+0x17c): the model's frame from the hero's movement: on the ground,
// flying, climbing or taking off (by movement mode); the scene leaf +0x1818 (the hero's reference point) takes the
// node's local matrix at the position +0x181c (the y kept while airborne). A hero not in its locomotion (+0xec4 bit 0
// clear) or locked to an object follows its first hot spot with the velocity cleared.
void CKHkS08Hero::UpdateMovement(IKTime* clock) {
    const float dt = clock->m_afDeltaTime[0];
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    CSGMovable* leaf = static_cast<CSGMovable*>(m_pCameraTargetNode);
    if ((m_unkec4 & 1u) != 0 && IsLockedToObject() == 0) {  // 0x00362040
        const int8_t mode = static_cast<int8_t>(GetMovementMode());  // 0x003401b8
        if (mode == 1) {
            UpdateFlyingMovement(dt);  // 0x003141b0
        } else if (mode == 2) {
            if (ShouldStayClimbing() != 0) {  // 0x00342fa8
                UpdateClimbSustainedMovement(dt);  // 0x0031ff88
            } else {
                UpdateClimbMovement(dt);  // 0x0031f6a8
            }
        } else if (mode == 0) {
            if (ShouldJoinPartnerFlight() != 0) {  // 0x00341fa0
                UpdateTakeOffToPartnerMovement(dt);  // 0x0031ce28
            } else {
                UpdateGroundMovement(dt);  // 0x003189a8
            }
        }
        leaf->SetLocalMatrix(&node->m_pRwFrame->modelling);  // 0x000d0be8
        if ((m_ui32HeroFlags354 & 1u) == 0) m_unk1820 = m_unk550;
        if ((m_ui32HeroFlags354 & 0x40000u) != 0) {
            m_unk181c = m_unk54c;
            m_unk1820 = m_unk550;
            m_unk1824 = m_unk554;
        }
    } else {
        const CVector3& zero = kHeroZeroVector;  // TOC +0x1dc0
        m_unk127c = zero.x;
        m_unk1284 = zero.z;
        m_unk1280 = zero.y;
        leaf->SetLocalMatrix(&node->m_pRwFrame->modelling);  // 0x000d0be8
        // The reference point at the first hot spot (+0x4c [0]) in the world, the leaf's frame there, then the model's
        // offset and bank (0x00359388); this branch returns without the tail below.
        CVector3 reference;
        static_cast<CSGHotSpot*>(m_apHotSpots[0])->GetWorldPosition(&reference);  // 0x000ce790
        m_unk181c = reference.x;
        m_unk1820 = reference.y;
        m_unk1824 = reference.z;
        RwFrame* lockedFrame = leaf->m_pRwFrame;
        lockedFrame->modelling.pos.z = m_unk1824;
        lockedFrame->modelling.pos.x = m_unk181c;
        lockedFrame->modelling.pos.y = m_unk1820;
        lockedFrame->modelling.flags &= 0xfffdffffu;
        c22spyro::RwFrameMarkDirty(lockedFrame);  // 0x00010698
        UpdateModelOffsetAndBank(clock);  // 0x00359388
        return;
    }
    RwFrame* frame = leaf->m_pRwFrame;
    frame->modelling.pos.z = m_unk1824;
    frame->modelling.pos.x = m_unk181c;
    frame->modelling.pos.y = m_unk1820;
    frame->modelling.flags &= 0xfffdffffu;
    c22spyro::RwFrameMarkDirty(frame);  // 0x00010698
}

// ---- DOTD: the native targets of the hero's state tables (k2000/core/Ps3MemberFn.h) ----
// The rows of the four state machines (CKGrpS08Hero.cpp, 0xc4b1e0 / 0xc4b2bc / 0xc4b398 / 0xc4b3fc) and the
// locomotion animation sub-machines (InitLocomotionAnimSubStateMachines) hold the original's function descriptors;
// this side table maps each descriptor (descriptor -> entry -> Ghidra name) to the member function that ports it.
// A null entry is not ported yet: calling it logs once and changes nothing.
namespace {
using HandlerEntry = Ps3MemberFnEntry<CKHkS08Hero::StateHandlerFn>;
using ConditionEntry = Ps3MemberFnEntry<CKHkS08Hero::StateConditionFn>;

HandlerEntry g_heroStateHandlers[] = {
    // The control machine (0xc4b1e0).
    {0x00ba29d0u, &CKHkS08Hero::CtlInactive, "CKHkS08Hero_CtlState10_Inactive 0x367fc0", false},
    {0x00ba2a20u, &CKHkS08Hero::CtlPlayer, "CKHkS08Hero_CtlState9_Player 0x367ff8", false},
    {0x00ba2a90u, &CKHkS08Hero::CtlPlayerFollowsFocus, "CKHkS08Hero_CtlState8_PlayerFollowsFocus 0x368478", false},
    {0x00b9f0c8u, &CKHkS08Hero::CtlScriptedMoveTo, "CKHkS08Hero_CtlState2_ScriptedMoveTo 0x33e378", false},
    {0x00b9f078u, &CKHkS08Hero::CtlControlLocked, "CKHkS08Hero_CtlState4_ControlLocked 0x33da70", false},
    {0x00b9f0d0u, &CKHkS08Hero::CtlAIFollowGround, "CKHkS08Hero_CtlState7_AIFollowGround 0x33e600", false},
    {0x00b9f0f0u, &CKHkS08Hero::CtlAIFollowFlying, "CKHkS08Hero_CtlState6_AIFollowFlying 0x33f4d0", false},
    {0x00b9f0e0u, &CKHkS08Hero::CtlAIClimbing, "CKHkS08Hero_CtlState5_AIClimbing_maybe 0x33f080", false},
    {0x00b9efb8u, &CKHkS08Hero::CtlAICombat, "CKHkS08Hero_CtlState3_AICombat 0x33d000", false},
    {0x00b9f0e8u, &CKHkS08Hero::CtlAIWarpToCatchUpPoint, "CKHkS08Hero_CtlState0_AIWarpToCatchUpPoint 0x33f150", false},
    {0x00b9f0b8u, &CKHkS08Hero::CtlAIPickCatchUpPoint, "CKHkS08Hero_CtlState1_AIPickCatchUpPoint 0x33e108", false},
    // The action machine (0xc4b3fc).
    {0x00ba2110u, &CKHkS08Hero::ActFreeMovement, "CKHkS08Hero_ActState12_FreeMovement 0x364a30", false},
    {0x00b9e408u, &CKHkS08Hero::ActGroundCombo, "CKHkS08Hero_ActState11_GroundComboKind0 0x330528", false},
    {0x00b9e480u, &CKHkS08Hero::ActGroundGrabCombo, "CKHkS08Hero_ActState7_GroundGrabComboKind1 0x332078", false},
    {0x00b9e460u, &CKHkS08Hero::ActHurtReaction, "CKHkS08Hero_ActState2_HurtReaction 0x330fe8", false},
    {0x00b9e400u, &CKHkS08Hero::ActGroundAltCombo, "CKHkS08Hero_ActState10_GroundAltComboKind2 0x32fce0", false},
    {0x00b9e390u, &CKHkS08Hero::ActClimbCombo, "CKHkS08Hero_ActState9_ClimbComboKind4_maybe 0x32e820", false},
    {0x00b9e3f8u, &CKHkS08Hero::ActFlyingCombo, "CKHkS08Hero_ActState8_FlyingComboKind3 0x32f470", false},
    {0x00b9d200u, &CKHkS08Hero::ActAbility, "CKHkS08Hero_ActState4_AbilityHandler 0x3276d0", false},
    {0x00b9e478u, &CKHkS08Hero::ActGrabDashCombo, "CKHkS08Hero_ActState6_GrabDashComboKind5 0x331540", false},
    {0x00b9e488u, &CKHkS08Hero::ActGrabSlamSeq, "CKHkS08Hero_ActState5_GrabSlamSeq_maybe 0x332a70", false},
    {0x00b9e4d0u, &CKHkS08Hero::ActDead, "CKHkS08Hero_ActState0_Dead 0x3332c0", false},
    {0x00b9e3f0u, &CKHkS08Hero::ActRecovery, "CKHkS08Hero_ActState3_Recovery_maybe 0x32f268", false},
    {0x00b9d068u, &CKHkS08Hero::ActFuryCoop, "CKHkS08Hero_ActState1_FuryCoop_maybe 0x326950", false},
    // The locomotion machine (0xc4b398).
    {0x00b9ba20u, &CKHkS08Hero::LocoFlying, "CKHkS08Hero_LocoState0_Flying 0x315088", false},
    {0x00b9cbf0u, &CKHkS08Hero::LocoClimbSustained, "CKHkS08Hero_LocoState1_ClimbSustained_maybe 0x324780", false},
    {0x00b9ca58u, &CKHkS08Hero::LocoClimb, "CKHkS08Hero_LocoState2_Climb_maybe 0x31f318", false},
    {0x00b9c510u, &CKHkS08Hero::LocoTakeOffToPartner, "CKHkS08Hero_LocoState3_TakeOffToPartner 0x31b658", false},
    {0x00b9bff0u, &CKHkS08Hero::LocoGround, "CKHkS08Hero_LocoState4_Ground 0x319a10", false},
    // The animation machine (0xc4b2bc).
    {0x00b9a348u, &CKHkS08Hero::AnimLocomotionFlying, "CKHkS08Hero_AnimState8_LocomotionFlying 0x30a518", false},
    {0x00b9a368u, &CKHkS08Hero::AnimLocomotionGround, "CKHkS08Hero_AnimState10_LocomotionGround 0x30aa78", false},
    {0x00b9a340u, &CKHkS08Hero::AnimLocomotionClimb, "CKHkS08Hero_AnimState9_LocomotionClimb 0x30a0d8", false},
    {0x00b9de18u, &CKHkS08Hero::AnimComboAnim, "CKHkS08Hero_AnimState7_ComboAnim 0x32cb98", false},
    {0x00b9dd78u, &CKHkS08Hero::AnimHurt, "CKHkS08Hero_AnimState4_Hurt 0x32c628", false},
    {0x00b9dcc8u, &CKHkS08Hero::AnimRecovery, "CKHkS08Hero_AnimState5_Recovery 0x32c170", false},
    {0x00b9dd38u, &CKHkS08Hero::AnimAbility, "CKHkS08Hero_AnimState6_Ability 0x32c520", false},
    {0x00b9ddd0u, &CKHkS08Hero::AnimGuardedHurt, "CKHkS08Hero_AnimState3_GuardedHurt 0x32c780", false},
    {0x00b9dd30u, &CKHkS08Hero::AnimDead, "CKHkS08Hero_AnimState0_Dead 0x32c380", false},
    {0x00b9ddd8u, &CKHkS08Hero::AnimHurtType1, "CKHkS08Hero_AnimState2_HurtType1 0x32c950", false},
    {0x00b9dcd0u, &CKHkS08Hero::AnimFury, "CKHkS08Hero_AnimState1_Fury 0x32c268", false},
    // The flying animation sub-machine (+0x183c, 18 states).
    {0x00b9a150u, &CKHkS08Hero::FlyAnimState00, "CKHkS08Hero_FlyAnimState00_Glide_maybe 0x3059d0", false},
    {0x00b9a190u, &CKHkS08Hero::FlyAnimState01, "CKHkS08Hero_FlyAnimState01_Anim33_36 0x305d20", false},
    {0x00b9a198u, &CKHkS08Hero::FlyAnimState02, "CKHkS08Hero_FlyAnimState02_Anim3A_3D 0x306028", false},
    {0x00b9a1f8u, &CKHkS08Hero::FlyAnimState03, "CKHkS08Hero_FlyAnimState03_LandingApproach_maybe 0x307cf8", false},
    {0x00b9a1f0u, &CKHkS08Hero::FlyAnimState04, "CKHkS08Hero_FlyAnimState04_Anim44 0x307ac8", false},
    {0x00b99fe0u, &CKHkS08Hero::FlyAnimState05, "CKHkS08Hero_FlyAnimState05_Anim43 0x302808", false},
    {0x00b9a0b8u, &CKHkS08Hero::FlyAnimState06, "CKHkS08Hero_FlyAnimState06_Anim3E_3F 0x303d48", false},
    {0x00b9a020u, &CKHkS08Hero::FlyAnimState07, "CKHkS08Hero_FlyAnimState07_Anim40 0x302fe0", false},
    {0x00b9a200u, &CKHkS08Hero::FlyAnimState08, "CKHkS08Hero_FlyAnimState08_Anim5B 0x308028", false},
    {0x00b9a000u, &CKHkS08Hero::FlyAnimState09, "CKHkS08Hero_FlyAnimState09_Grounded_maybe 0x302de0", false},
    {0x00b99fd8u, &CKHkS08Hero::FlyAnimState10, "CKHkS08Hero_FlyAnimState10_Anim48 0x3026f8", false},
    {0x00b99fd0u, &CKHkS08Hero::FlyAnimState11, "CKHkS08Hero_FlyAnimState11_Anim49 0x3025f8", false},
    {0x00b99ff8u, &CKHkS08Hero::FlyAnimState12, "CKHkS08Hero_FlyAnimState12_Anim4A 0x302c98", false},
    {0x00b9a0c0u, &CKHkS08Hero::FlyAnimState13, "CKHkS08Hero_FlyAnimState13_NoAnim 0x304090", false},
    {0x00b99ff0u, &CKHkS08Hero::FlyAnimState14, "CKHkS08Hero_FlyAnimState14_Anim52 0x302bb0", false},
    {0x00b9a240u, &CKHkS08Hero::FlyAnimState15, "CKHkS08Hero_FlyAnimState15_NoAnim 0x3083d0", false},
    {0x00b9a110u, &CKHkS08Hero::FlyAnimState16, "CKHkS08Hero_FlyAnimState16_NoAnim 0x304d00", false},
    {0x00b9a238u, &CKHkS08Hero::FlyAnimState17, "CKHkS08Hero_FlyAnimState17_Anim55 0x3081a0", false},
    // The ground animation sub-machine (+0x18d4, 17 states).
    {0x00b9a108u, &CKHkS08Hero::GroundAnimState00, "CKHkS08Hero_GroundAnimState00_Anim01 0x304a30", false},
    {0x00b9a1a8u, &CKHkS08Hero::GroundAnimState01, "CKHkS08Hero_GroundAnimState01_Anim09 0x306538", false},
    {0x00b9a1a0u, &CKHkS08Hero::GroundAnimState02, "CKHkS08Hero_GroundAnimState02_Anim0C 0x306368", false},
    {0x00b9a028u, &CKHkS08Hero::GroundAnimState03, "CKHkS08Hero_GroundAnimState03_JumpTakeOff_maybe 0x303168", false},
    {0x00b9a050u, &CKHkS08Hero::GroundAnimState04, "CKHkS08Hero_GroundAnimState04_Anim10_11 0x303448", false},
    {0x00b9a1e8u, &CKHkS08Hero::GroundAnimState05, "CKHkS08Hero_GroundAnimState05_Airborne_maybe 0x3076c0", false},
    {0x00b9a1e0u, &CKHkS08Hero::GroundAnimState06, "CKHkS08Hero_GroundAnimState06_AirborneHigh_maybe 0x3072b8", false},
    {0x00b9a118u, &CKHkS08Hero::GroundAnimState07, "CKHkS08Hero_GroundAnimState07_Landing_maybe 0x304dc8", false},
    {0x00b99fe8u, &CKHkS08Hero::GroundAnimState08, "CKHkS08Hero_GroundAnimState08_NoAnim 0x3029f8", false},
    {0x00b99fc8u, &CKHkS08Hero::GroundAnimState09, "CKHkS08Hero_GroundAnimState09_Anim1D 0x302520", false},
    {0x00b9a120u, &CKHkS08Hero::GroundAnimState10, "CKHkS08Hero_GroundAnimState10_HardLanding_maybe 0x3050d0", false},
    {0x00b9a260u, &CKHkS08Hero::GroundAnimState11, "CKHkS08Hero_GroundAnimState11_Anim26_27_2A 0x308f48", false},
    {0x00b9a258u, &CKHkS08Hero::GroundAnimState12, "CKHkS08Hero_GroundAnimState12_NoAnim 0x3089f8", false},
    {0x00b9a248u, &CKHkS08Hero::GroundAnimState13, "CKHkS08Hero_GroundAnimState13_AnimD1 0x308778", false},
    {0x00b9a1d8u, &CKHkS08Hero::GroundAnimState14, "CKHkS08Hero_GroundAnimState14_Anim30 0x307110", false},
    {0x00b9a1d0u, &CKHkS08Hero::GroundAnimState15, "CKHkS08Hero_GroundAnimState15_Anim8F 0x306fc0", false},
    {0x00b9a1c8u, &CKHkS08Hero::GroundAnimState16, "CKHkS08Hero_GroundAnimState16_Anim90 0x306e50", false},
    // The climbing animation sub-machine (+0x1964, 8 states).
    {0x00b9a090u, &CKHkS08Hero::ClimbAnimState00, "CKHkS08Hero_ClimbAnimState00_NoAnim 0x303878", false},
    {0x00b9a148u, &CKHkS08Hero::ClimbAnimState01, "CKHkS08Hero_ClimbAnimState01_Anim5F_65_67_63 0x3054e0", false},
    {0x00b9a1b8u, &CKHkS08Hero::ClimbAnimState02, "CKHkS08Hero_ClimbAnimState02_Anim8B 0x3068e0", false},
    {0x00b9a1b0u, &CKHkS08Hero::ClimbAnimState03, "CKHkS08Hero_ClimbAnimState03_NoAnim 0x306708", false},
    {0x00b9a100u, &CKHkS08Hero::ClimbAnimState04, "CKHkS08Hero_ClimbAnimState04_NoAnim 0x3047a8", false},
    {0x00b9a298u, &CKHkS08Hero::ClimbAnimState05, "CKHkS08Hero_ClimbAnimState05_ClimbEnd_maybe 0x309e68", false},
    {0x00b9a088u, &CKHkS08Hero::ClimbAnimState06, "CKHkS08Hero_ClimbAnimState06_NoAnim 0x303698", false},
    {0x00b9a1c0u, &CKHkS08Hero::ClimbAnimState07, "CKHkS08Hero_ClimbAnimState07_Anim8C 0x306cf0", false},
};

ConditionEntry g_heroStateConditions[] = {
    // The control machine.
    {0x00ba29b8u, &CKHkS08Hero::CtlInactiveCondition, "CKHkS08Hero_CtlState10_Inactive_Condition 0x367f50", false},
    {0x00ba2a30u, &CKHkS08Hero::CtlPlayerCondition, "CKHkS08Hero_CtlState9_Player_Condition 0x368158", false},
    {0x00ba2a48u, &CKHkS08Hero::CtlPlayerFollowsFocusCondition, "CKHkS08Hero_CtlState8_PlayerFollowsFocus_Condition 0x368178", false},
    {0x00ba29c0u, &CKHkS08Hero::CtlScriptedMoveToCondition, "CKHkS08Hero_CtlState2_ScriptedMoveTo_Condition 0x367f58", false},
    {0x00ba29c8u, &CKHkS08Hero::CtlControlLockedCondition, "CKHkS08Hero_CtlState4_ControlLocked_Condition 0x367f98", false},
    {0x00b9eff0u, &CKHkS08Hero::CtlAIFollowGroundCondition, "CKHkS08Hero_CtlState7_AIFollowGround_Condition 0x33d428", false},
    {0x00b9eff8u, &CKHkS08Hero::CtlAIFollowFlyingCondition, "CKHkS08Hero_CtlState6_AIFollowFlying_Condition 0x33d570", false},
    {0x00b9efe8u, &CKHkS08Hero::CtlAIClimbingCondition, "CKHkS08Hero_CtlState5_AIClimbing_maybe_Condition 0x33d330", false},
    {0x00b9efe0u, &CKHkS08Hero::CtlAICombatCondition, "CKHkS08Hero_CtlState3_AICombat_Condition 0x33d250", false},
    {0x00b9ef00u, &CKHkS08Hero::CtlAIWarpToCatchUpPointCondition, "CKHkS08Hero_CtlState0_AIWarpToCatchUpPoint_Condition 0x33caa0", false},
    {0x00b9ef08u, &CKHkS08Hero::CtlAIPickCatchUpPointCondition, "CKHkS08Hero_CtlState1_AIPickCatchUpPoint_Condition 0x33cab0", false},
    // The action machine.
    {0x00ba2108u, &CKHkS08Hero::ActFreeMovementCondition, "CKHkS08Hero_ActState12_FreeMovement_Condition 0x364a28", false},
    {0x00b9e368u, &CKHkS08Hero::ActGroundComboCondition, "CKHkS08Hero_ActState11_GroundComboKind0_Condition 0x32e158", false},
    {0x00b9e3a0u, &CKHkS08Hero::ActGroundGrabComboCondition, "CKHkS08Hero_ActState7_GroundGrabComboKind1_Condition 0x32ecc0", false},
    {0x00b9e258u, &CKHkS08Hero::ActHurtReactionCondition, "CKHkS08Hero_ActState2_HurtReaction_Condition 0x32d4c8", false},
    {0x00b9e388u, &CKHkS08Hero::ActGroundAltComboCondition, "CKHkS08Hero_ActState10_GroundAltComboKind2_Condition 0x32e668", false},
    {0x00b9e378u, &CKHkS08Hero::ActClimbComboCondition, "CKHkS08Hero_ActState9_ClimbComboKind4_maybe_Condition 0x32e3d0", false},
    {0x00b9e380u, &CKHkS08Hero::ActFlyingComboCondition, "CKHkS08Hero_ActState8_FlyingComboKind3_Condition 0x32e488", false},
    {0x00b9d020u, &CKHkS08Hero::ActAbilityCondition, "CKHkS08Hero_ActState4_Ability_Condition 0x326498", false},
    {0x00b9e398u, &CKHkS08Hero::ActGrabDashComboCondition, "CKHkS08Hero_ActState6_GrabDashComboKind5_Condition 0x32eb80", false},
    {0x00b9e370u, &CKHkS08Hero::ActGrabSlamSeqCondition, "CKHkS08Hero_ActState5_GrabSlamSeq_maybe_Condition 0x32e378", false},
    {0x00b9e3e8u, &CKHkS08Hero::ActDeadCondition, "CKHkS08Hero_ActState0_Dead_Condition 0x32f170", false},
    {0x00b9e260u, &CKHkS08Hero::ActRecoveryCondition, "CKHkS08Hero_ActState3_Recovery_maybe_Condition 0x32d4d0", false},
    {0x00b9d028u, &CKHkS08Hero::ActFuryCoopCondition, "CKHkS08Hero_ActState1_FuryCoop_maybe_Condition 0x3267e8", false},
    // The locomotion machine.
    {0x00b9b8b8u, &CKHkS08Hero::LocoFlyingCondition, "CKHkS08Hero_LocoState0_Flying_Condition 0x313780", false},
    {0x00b9c9b0u, &CKHkS08Hero::LocoClimbSustainedCondition, "CKHkS08Hero_LocoState1_ClimbSustained_maybe_Condition 0x31e1e8", false},
    {0x00b9c9f8u, &CKHkS08Hero::LocoClimbCondition, "CKHkS08Hero_LocoState2_Climb_maybe_Condition 0x31f2a0", false},
    {0x00b9bea8u, &CKHkS08Hero::LocoTakeOffToPartnerCondition, "CKHkS08Hero_LocoState3_TakeOffToPartner_Condition 0x317e68", false},
    {0x00b9beb0u, &CKHkS08Hero::LocoGroundCondition, "CKHkS08Hero_LocoState4_Ground_Condition 0x317e90", false},
    // The animation machine.
    {0x00b99fc0u, &CKHkS08Hero::AnimLocomotionFlyingCondition, "CKHkS08Hero_AnimState8_LocomotionFlying_Condition 0x3024f8", false},
    {0x00b99fb8u, &CKHkS08Hero::AnimLocomotionGroundCondition, "CKHkS08Hero_AnimState10_LocomotionGround_Condition 0x3024d0", false},
    {0x00b99fb0u, &CKHkS08Hero::AnimLocomotionClimbCondition, "CKHkS08Hero_AnimState9_LocomotionClimb_Condition 0x3024a8", false},
    {0x00b9dc08u, &CKHkS08Hero::IsComboActive, "CKHkS08Hero_IsComboActive 0x32bb30", false},
    {0x00b9dc10u, &CKHkS08Hero::AnimHurtCondition, "CKHkS08Hero_AnimState4_Hurt_Condition 0x32bb58", false},
    {0x00b9dc28u, &CKHkS08Hero::AnimRecoveryCondition, "CKHkS08Hero_AnimState5_Recovery_Condition 0x32bc08", false},
    {0x00b9dcb8u, &CKHkS08Hero::AnimAbilityCondition, "CKHkS08Hero_AnimState6_Ability_Condition 0x32c130", false},
    {0x00b9dd70u, &CKHkS08Hero::AnimGuardedHurtCondition, "CKHkS08Hero_AnimState3_GuardedHurt_Condition 0x32c5e0", false},
    {0x00b9dc38u, &CKHkS08Hero::AnimDeadCondition, "CKHkS08Hero_AnimState0_Dead_Condition 0x32bed8", false},
    {0x00b9dc18u, &CKHkS08Hero::AnimHurtType1Condition, "CKHkS08Hero_AnimState2_HurtType1_Condition 0x32bb60", false},
    {0x00b9dc20u, &CKHkS08Hero::AnimFuryCondition, "CKHkS08Hero_AnimState1_Fury_Condition 0x32bbc0", false},
};
}  // namespace

namespace {
// DOTD: the hero's CKSrvDynamic hooks by descriptor (PostLoad registers them: DynamicStage1ByMode at each fixed
// sub-step, UpdateLocomotionByMode once per frame, DynamicStage3PredictPosition with the time left over;
// UpdateCKSrvDynamic 0x23ba10 calls them).
Ps3MemberFnEntry<CKHkS08Hero::DynamicHookFn> g_heroDynamicHooks[] = {
    {0x00b9b258u, &CKHkS08Hero::DynamicStage1ByMode, "CKHkS08Hero_DynamicStage1ByMode_maybe 0x30f778", false},
    {0x00b9b360u, &CKHkS08Hero::UpdateLocomotionByMode, "CKHkS08Hero_UpdateLocomotionByMode_maybe 0x310708", false},
    {0x00b9b308u, &CKHkS08Hero::DynamicStage3PredictPosition, "CKHkS08Hero_DynamicStage3PredictPosition_maybe 0x30ffa0", false},
};
}  // namespace

// A CKSrvDynamic hook pair of the hero: the native function called with the step, or nothing (not ported).
void CKHkS08Hero::CallDynamicHook(const uint32_t pair[2], float step) {
    DynamicHookFn fn = ResolvePs3MemberFn(g_heroDynamicHooks, pair, "CKHkS08Hero dynamic hook");
    if (fn != nullptr) (this->*fn)(step);
}

// DOTD: CKSrvDynamic's native dispatcher of a hero's entry (CKSrvDynamic::SetNativeDispatch).
void CKHkS08Hero::DispatchDynamicHook(IKSerializable* object, const uint32_t pair[2], float step) {
    static_cast<CKHkS08Hero*>(object)->CallDynamicHook(pair, step);
}

// A state handler of a table pair: the native function, or (not ported) the state it was given.
uint8_t CKHkS08Hero::CallStateHandler(const uint32_t pair[2], IKTime* clock, int32_t phase, uint8_t other) {
    StateHandlerFn fn = ResolvePs3MemberFn(g_heroStateHandlers, pair, "CKHkS08Hero state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

// A state condition of a table row: the native function, or (not ported) false.
uint8_t CKHkS08Hero::CallStateCondition(const uint32_t pair[2], IKTime* clock, uint8_t row) {
    StateConditionFn fn = ResolvePs3MemberFn(g_heroStateConditions, pair, "CKHkS08Hero state condition");
    if (fn == nullptr) return 0;
    return (this->*fn)(clock, row);
}

// The transition block each state machine of the hero inlines: the current state's exit handler (phase 2, told the
// state entered), the new current state, its enter handler (phase 1, told the state left). 0xff is no state.
void CKHkS08Hero::SwitchState(const uint32_t* handlers, uint8_t& current, uint8_t next, IKTime* clock) {
    const uint8_t previous = current;
    if (previous != 0xff) CallStateHandler(&handlers[previous * 2u], clock, 2, next);
    current = next;
    if (next != 0xff) CallStateHandler(&handlers[next * 2u], clock, 1, previous);
}

// The update block each state machine inlines: the current state's update (phase 0, told its own index); an answer
// different from the (re-read) current state is a transition.
void CKHkS08Hero::RunState(const uint32_t* handlers, uint8_t& current, IKTime* clock) {
    const uint8_t state = current;
    if (state == 0xff) return;
    const uint8_t next = CallStateHandler(&handlers[state * 2u], clock, 0, state);
    if (next != current) SwitchState(handlers, current, next, clock);
}

// 0x002dc660 CKHkS08Hero_UpdateGroundSurfaceFlags_maybe (vt+0x14c)
void CKHkS08Hero::UpdateGroundSurfaceFlags(IKTime* /*clock*/) {
    const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(GetGroundInfo());  // 0x00361b68
    m_unkec4 &= ~0x40000u;
    m_unkecc &= ~0x10000000u;
    if (ground == nullptr) return;
    uint16_t props = ground->m_ui16PropertiesFlags;
    if ((props & 0x200u) != 0 && m_gcCurDatasInOut.m_fdH < m_unk8e8) {
        m_unkec4 = (m_unkec4 & ~0x40000u) | 0x40000u;
        props = ground->m_ui16PropertiesFlags;
    }
    if (static_cast<int16_t>(props) < 0) m_unkecc = (m_unkecc & ~0x10000000u) | 0x10000000u;
}

// 0x002dbc60 CKHkS08Hero_CanDragonSwitch_maybe (vt+0x170): whether the dragon switch may happen now. Flying: not
// during animation 0x55 (the request dropped). Climbing: yes. On the ground: not on a climb edge (+0x1511, unless the
// partner's climb flag, another owner or +0xec8 bit 10), else yes when +0x1810 was set (cleared) or another hero owns the
// control, else the group's +0x320. A hero with +0xed0 bit 3 drops the request and refuses.
uint8_t CKHkS08Hero::CanDragonSwitch() {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    uint8_t answer;
    const int8_t mode = static_cast<int8_t>(GetMovementMode());  // 0x003401b8
    if (mode == 1) {
        if (m_i16CurAnimIndex == 0x55) {
            group->m_ui8RequestedDragon = group->m_ui8SelectedDragon;
            group->m_baWorkFlags &= ~0x20u;
            answer = 0;
        } else {
            answer = 1;
        }
    } else if (mode == 2) {
        answer = 1;
    } else if (mode == 0) {
        const bool owner = m_ui8Hero == m_ui8TrackedLeader;
        if (m_unk1511 != 0 && IsPartnerClimbFlagSet() == 0 && owner && (m_unkec8 & 0x400u) == 0) {  // 0x002f87e8
            answer = 0;
        } else if (m_unk1810 != 0 || !owner) {
            m_unk1810 = 0;
            answer = 1;
        } else {
            answer = group->m_unk320 != 0 ? 1 : 0;
        }
    } else {
        // BUG(original): another mode answers the low byte of the hero's address (the modes are 0, 1 and 2).
        answer = static_cast<uint8_t>(reinterpret_cast<uintptr_t>(this));
    }
    if ((m_ui32StatusFlagsED0 & 8u) != 0) {
        group->m_ui8RequestedDragon = group->m_ui8SelectedDragon;
        group->m_baWorkFlags &= ~0x20u;
        answer = 0;
    }
    return answer;
}

// 0x002daa78 CKHkS08Hero_GetInfo, with its accessors 0x9bd710 IsClimbingForTrigger, 0x9bd850 / 0x9bd828 / 0x9bd800 /
// 0x9bd7d8 the carrying thunks, 0x9bd760 IsFlying_Thunk2, 0x9bd6e0 IsAirborneActionActive and 0x9bd788
// IsHoldingEnemyInGrabCombo. IKHkHero's answer 2 wins; an id of its own answers 0; else IKHkHero's (0 or 1).
int32_t CKHkS08Hero::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = IKHkHero::GetInfo(info, request);
    bool unknown = true;
    if (request == kGetInfoValueAccessor) {
        unknown = false;
        switch (info->m_ui32Id) {
        case 0x14:
            AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(o);
                if (hero->ShouldStayClimbing() == 0) return 0u;  // 0x00342fa8
                return hero->m_unk1628 == 0 ? 1u : 0u;
            }, 0);
            break;
        case 0x15:
            AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                return static_cast<uint32_t>(static_cast<CKHkS08Hero*>(o)->IsCarryingTransportableKey());  // 0x0032a090
            }, 0);
            break;
        case 0x16:
            AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                return static_cast<uint32_t>(static_cast<CKHkS08Hero*>(o)->IsCarryingTransportableWeight());  // 0x0032a148
            }, 0);
            break;
        case 0x17:
            AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                return static_cast<uint32_t>(static_cast<CKHkS08Hero*>(o)->IsFlyingMovementMode1());  // 0x00340188
            }, 0);
            break;
        case 0x18:
            AnswerInfo(info, [](IKSerializable* o, uint32_t) { return static_cast<uint32_t>(static_cast<CKHkS08Hero*>(o)->m_unk13d8); }, 0);
            break;
        case 0x19:
            AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                return static_cast<uint32_t>(static_cast<CKHkS08Hero*>(o)->IsCarryingPowerBucket());  // 0x0032a200
            }, 0);
            break;
        case 0x1a:
            AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                return static_cast<uint32_t>(static_cast<CKHkS08Hero*>(o)->IsCarryingFilledPowerBucket());  // 0x0032a2b8
            }, 0);
            break;
        case 0xe6:
            AnswerInfo(info, [](IKSerializable* o, uint32_t) {
                const CKHkS08Hero* hero = static_cast<const CKHkS08Hero*>(o);
                if (hero->IsGrabComboKind() == 0) return 0u;  // 0x002fc208
                return hero->m_unk1acc != 0 ? 1u : 0u;
            }, 0);
            break;
        default:
            unknown = true;
            break;
        }
    }
    if (base == 2) return 2;
    if (!unknown) return 0;
    return base != 0 ? 1 : 0;
}

// 0x002db3d8 CKHkS08Hero_Stop
void CKHkS08Hero::Stop() {
    // KStub_Nop_344e20 (IKHkHero's Stop)
    CSGBranch* node = static_cast<CSGBranch*>(m_pKGLObject);
    for (uint32_t i = 0; i < 8; ++i) {  // unrolled in the original
        CSGLeaf* bounding = static_cast<CSGLeaf*>(m_apBoundings[i]);
        CSGBranch* parent = bounding->m_pParent;
        if (static_cast<CSGBranch*>(m_pKGLObject) == parent) continue;
        if (parent != nullptr) parent->RemoveChild(bounding);  // vt+0x78
        node = static_cast<CSGBranch*>(m_pKGLObject);
        node->AddChild(bounding);                              // vt+0x70
    }
    SetCollisionVolumeEnabled(static_cast<IKBoundingVolume*>(m_apBoundings[0]), 0);
    static_cast<CKS08CarrierHero*>(m_pCarrierHero)->DropCarriedObject();  // vt+0x6c
    m_unk218 = m_unk1724;
    IKSerializable** effects[4] = {&m_unk19b8, &m_unk19c0, &m_unk19c8, &m_unk19d0};
    for (IKSerializable** effect : effects) {
        if (*effect != nullptr) {
            static_cast<IKFx*>(*effect)->StopAndRelease(this);  // vt+0x58
            *effect = nullptr;
        }
    }
    if (m_unk1ac5 != 0) CancelAbilityA(0);
    if (m_unk1ac6 != 0) CancelAbilityB(0);
}

// 0x002dca08 CKHkS08Hero_FreeOwnedResources_maybe
void CKHkS08Hero::FreeOwnedResources() {
    if (m_apUnk1a24 != nullptr) {
        Mem_FreeAligned16(m_apUnk1a24);
        m_apUnk1a24 = nullptr;
    }
    m_apUnk1a24 = nullptr;
    m_unk1a2c = 0;
    if (m_apUnk1a30 != nullptr) {
        Mem_FreeAligned16(m_apUnk1a30);
        m_apUnk1a30 = nullptr;
    }
    m_unk1a38 = 0;
    m_apUnk1a30 = nullptr;
    RwMatrixDestroy_Thunk(m_unk16d8);
    RwMatrixDestroy_Thunk(m_unk16d4);
    static_cast<CKSrvDynamic*>(g_pEngine->m_srvDynamic)->UnregisterHook(this);
    RwMatrixDestroy_Thunk(m_unk16dc);
    RwMatrixDestroy_Thunk(m_unk16e0);
    RwMatrixDestroy_Thunk(m_unk16e4);
    RwMatrixDestroy_Thunk(m_unk16e8);
    RwMatrixDestroy_Thunk(m_unk16ec);
    RwMatrixDestroy_Thunk(m_unk16f0);
    if (m_pAbilityHost != nullptr) {
        delete m_pAbilityHost;  // vt+0x04 the deleting destructor
        m_pAbilityHost = nullptr;
    }
}

// 0x002dcb60 CKHkS08Hero_Destroy
void CKHkS08Hero::Destroy() {
    FreeBuffers();  // 0x3452c0
    m_unk1ae0->Destroy();  // vt+0x10
    FreeOwnedResources();
}

// 0x002d9850 RegisterCKHkS08HeroType (_GLOBAL__I_2d98e8): two file statics (0x00ceade8, 0x00ceadec) set to -1.0f, read by
// nothing, then the class registration (2, 0x97; dotd registers its classes through the generated Kp3Ported registry).
namespace {
[[maybe_unused]] float s_unkceade8 = -1.0f;
[[maybe_unused]] float s_unkceadec = -1.0f;
}  // namespace
