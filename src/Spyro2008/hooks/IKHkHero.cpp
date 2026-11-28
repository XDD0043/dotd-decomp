// IKHkHero.cpp - reconstructed original translation unit 0x344ef0-0x34f9f0 (GAME_TOC1, main_toc1), 39 functions, 30 live.
// Primary owner: IKHkHero (not a registered class)
// Other owners: CKHkS08HeroBase (8), CKHkS08Hero (6), UpdateHeroMovementAndContacts (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x344ef0  KStub_ReturnFloat0_344ef0  [dead]
//   [ ] 0x344ef8  FUN_00344ef8  [dead]
//   [x] 0x345080  CKHkS08Hero_vf144
//   [x] 0x3450f0  CKHkS08Hero_OnSectorActivate_Base_maybe  (= the inherited slot)
//   [x] 0x345118  CKHkS08Hero_OnSectorDeactivate_Base_maybe  (IKLife::SectorUnload inherited)
//   [x] 0x345140  IKHkHero_FreeBuffers_maybe
//   [x] 0x3452c0  IKHkHero_FreeBuffers_maybe  (IKHkHero::Destroy: FreeBuffers)
//   [ ] 0x3452c8  IKHkHero_InitGroundProbe_maybe  [dead]
//   [x] 0x345408  IKHkHero_InitRuntimeTables_maybe
//   [x] 0x345b60  CKHkS08HeroBase_LevelReset_maybe  (IKHkHero::RecursiveRegistration)
//   [x] 0x345e20  IKHkHero_IsSelfControlledProperty_maybe
//   [x] 0x345e40  IKHkHero_GetNotFlag354Bit0Property_maybe
//   [x] 0x345e50  IKHkHero_AttachNodeToHotspot_maybe
//   [ ] 0x345f68  IKHkHero_UpdateTimerElapsed_maybe  [dead]
//   [ ] 0x345ff8  IKHkHero_StampTimer_maybe  [dead]
//   [ ] 0x346060  IKHkHero_vf170  [dead: only in the abstract IKHkHero vtable 0xb22f10 (vt+0x170), which only IKHkHero's destructors 0x9be9a8 / 0x9bea98 install; CKHkS08Hero, the only hero, has 0x2dbc60 CKHkS08Hero_CanDragonSwitch_maybe in that slot of its vtable 0xb22c98 (C2.8 port-final F07)]
//   [ ] 0x3460e0  IKHkHero_vf16C  [dead: only in the abstract IKHkHero vtable 0xb22f10 (vt+0x16c), which only IKHkHero's destructors 0x9be9a8 / 0x9bea98 install; CKHkS08Hero, the only hero, has 0x340f40 CKHkS08Hero_TryUseInteractable_maybe in that slot of its vtable 0xb22c98 (C2.8 port-final F07)]
//   [x] 0x3462b0  IKHkHero_vf50
//   [x] 0x3462c0  IKHkHero_ResolveTriggerProperty_maybe
//   [x] 0x346388  IKHkHero_GetDistanceToPartnerProperty_maybe
//   [x] 0x346400  IKHkHero_PostLoad
//   [x] 0x346480  IKHkHero_ResetRuntimeState_maybe
//   [x] 0x347528  IKHkHero_OnDisable_maybe  (IKHkHero::OnUnlock, IKHkHero.h)
//   [x] 0x347530  UpdateHeroMovementAndContacts_maybe
//   [x] 0x348010  CKHkS08Hero_ApplyControlAssignment_maybe
//   [x] 0x348220  CKHkS08HeroBase_HandleMessage_maybe
//   [x] 0x348ac0  CKHkS08Hero_ResetToDefaultState_maybe
//   [x] 0x348f00  CKHkS08Hero_ExitAllStateMachines_maybe
//   [ ] 0x3492e0  CKHkS08HeroBase_LoadArrayU32U8_maybe  [dead]
//   [x] 0x3493c0  CKHkS08HeroBase_LoadArray2xVec3_2xU32_5xU8_maybe
//   [ ] 0x349608  CKHkS08HeroBase_LoadArray3xU32_maybe  [dead]
//   [x] 0x349730  CKHkS08HeroBase_LoadArray2xVec3_4xU8_maybe
//   [x] 0x349930  CKHkS08HeroBase_Load_maybe
//   [ ] 0x34c788  IKHkHero_SaveArrayU32U8_maybe  [dead]
//   [ ] 0x34c880  IKHkHero_SaveArray2xVec3_2xU32_5xU8_maybe  [left: save-only: called from IKHkHero_Save 0x34d020 (the Save path) and from 0x2ec710, which nothing reaches (no pointer to its descriptor 0xb98f00)]
//   [ ] 0x34cbf0  IKHkHero_SaveArray3xU32_maybe  [dead]
//   [ ] 0x34cd38  IKHkHero_SaveArray2xVec3_4xU8_maybe  [left: save-only: called from IKHkHero_Save 0x34d020 (the Save path) and from 0x2ec710, which nothing reaches (no pointer to its descriptor 0xb98f00)]
//   [ ] 0x34d020  IKHkHero_Save
//   [x] 0x34f970  CKHkS08HeroBase_AdvanceAnimTime
#include "Spyro2008/hooks/IKHkHero.h"
#include "k2000/hooks/CKHkPressionStone.h"
#include "k2000/misc/CKGrpMeca.h"
#include "k2000/services/CKSrvCollision.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/graphical/animation/CAnimationManager.h"

#include <cstdlib>
#include <cstring>

#include "Spyro2008/groups/IKGrpHero.h"
#include "k2000/core/IKInfo.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/system/IKTime.h"
#include "k2000/render/CRenderer.h"
#include "crt/ppc_ops.h"
#include "Spyro2008/logic/CKS08GameSpawnPoint.h"
#include "k2000/core/Stub.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/IKGameStructure.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/math/Quat.h"
#include "k2000/logic/ai/CKMarkerBeacon.h"
#include <cmath>
#include "k2000/scenegraph/CAnimatedNode.h"

namespace {
// 0x002ce398 CKGrpS08Hero_vf11C and 0x002ce3b8 CKGrpS08Hero_vf124 (CKGrpS08Hero vt+0x11c / vt+0x124): the
// number of speed modes and of jumps per hero, from the constant tables at 0x00a70480 / 0x00a70490.
// BUG(original): no bound check; a hero index above 15 reads the following constants (not reproduced:
// the heroes are 0 and 1).
const uint8_t kNbSpeedModes_maybe[16] = {1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0};
const uint8_t kNbJumps_maybe[16] = {2, 2, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0};
uint8_t CKGrpS08Hero_GetNbSpeedModes(uint8_t hero) { return kNbSpeedModes_maybe[hero & 15]; }
uint8_t CKGrpS08Hero_GetNbJumps(uint8_t hero) { return kNbJumps_maybe[hero & 15]; }
}  // namespace

// The IKHkHero part of 0x002dd000 CKHkS08Hero_Create, in its store order (the ground-contact members and the
// path-finding component set their own defaults).
IKHkHero::IKHkHero() {
    m_unk80 = 0;
    m_ui8IANbStates = 0xff;
    m_ui8IACurrentState = 0xff;
    m_ui8FightNbStates = 0xff;
    m_ui8FightCurrentState = 0xff;
    m_pDamageContactHistory = nullptr;
    m_pTouchContactHistory = nullptr;
    m_ui8AnimNbStates = 0xff;
    m_ui8AnimCurrentState = 0xff;
    m_unk1a0 = nullptr;
    m_PFCharacter.m_bits = 0x407;
    m_PFCharacter.m_fMaxStepHeight = 0x1.99999ap-3f;  // 0.2 (TOC 0x1e30)
    m_PFCharacter.m_fMaxStepRise = 1.0f;
    m_PFCharacter.m_fRadius = g_pfGridScale.m_halfCellSize * 0x1.99999ap-3f;
    m_ui8DynamicNbStates = 0xff;
    m_ui8DynamicCurrentState = 0xff;
}

// 0x00349730 CKHkS08HeroBase_LoadArray2xVec3_4xU8_maybe (XXL2 IKHkHero::ReadHeroInitialState); `type` unused.
void IKHkHero::ReadHeroInitialState(IKFile* file, int32_t /*type*/, SHeroInitialState* states, uint32_t count) {
    for (uint32_t i = 0; i < count; ++i) {
        SHeroInitialState& s = states[i];
        // each vector: one 12-byte read, then its three words swapped
        ReadF32LE(file, &s.m_vPos.x);
        ReadF32LE(file, &s.m_vPos.y);
        ReadF32LE(file, &s.m_vPos.z);
        ReadF32LE(file, &s.m_vDir.x);
        ReadF32LE(file, &s.m_vDir.y);
        ReadF32LE(file, &s.m_vDir.z);
        ReadU8(file, &s.m_ui8TrackedLeader);
        ReadU8(file, &s.m_ui8Leader);
        uint8_t b = 0;
        ReadU8(file, &b);
        s.m_unk1c = b;
        ReadU8(file, &s.m_unk20);
    }
}

// 0x003493c0 CKHkS08HeroBase_LoadArray2xVec3_2xU32_5xU8_maybe (XXL2 IKHkHero::ReadHeroSpeedMode); `type` unused.
void IKHkHero::ReadHeroSpeedMode(IKFile* file, int32_t /*type*/, SHeroSpeedMode* modes, uint32_t count) {
    for (uint32_t i = 0; i < count; ++i) {
        SHeroSpeedMode& m = modes[i];
        for (int k = 0; k < 3; ++k) ReadF32LE(file, &m.m_afHSpeeds[k]);      // one 12-byte read
        for (int k = 0; k < 3; ++k) ReadF32LE(file, &m.m_afAnimHSpeeds[k]);  // one 12-byte read
        ReadF32LE(file, &m.m_fMaxHSpeed);
        ReadU16LE(file, &m.m_aui16YRotSpeeds[0]);  // one 4-byte read, each half swapped
        ReadU16LE(file, &m.m_aui16YRotSpeeds[1]);
        ReadU8(file, &m.m_ui8Threshold);
        ReadU8(file, &m.m_bDefaultEnable);
        ReadRaw(file, m.m_abAnimMustBeTurned, 3);
    }
}

// 0x00349930 CKHkS08HeroBase_Load_maybe
int32_t IKHkHero::Load(IKFile* file, int32_t type) {
    IKHook::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pGrpHero);
    // A byte for the hero group, read into a local and stored at +0x2c of m_pGrpHero (stb; the group's
    // m_ui8NumberOfHeros). BUG(original): no null check.
    uint8_t groupByte = 0;
    ReadU8(file, &groupByte);
    static_cast<IKGrpHero*>(m_pGrpHero)->m_ui8NumberOfHeros = groupByte;
    ReadU8(file, &m_ui8Hero);
    ReadU8(file, &m_ui8TrackedLeader);
    ReadU8(file, &m_ui8Leader);
    ReadHeroInitialState(file, K_LEVEL_PLATEFORMS, m_aInitialStates, 1);
    // Five arrays of references, each a count byte then the references (no block when the count is 0).
    uint8_t count = 0;
    ReadU8(file, &count);
    if (count == 0) {
        m_apHotSpots = nullptr;
    } else {
        m_apHotSpots = static_cast<IKSerializable**>(Mem_AllocAligned16(count * sizeof(IKSerializable*)));
        IKFile_ReadObjectRefArray(file, m_apHotSpots, count);
    }
    ReadU8(file, &count);
    if (count == 0) {
        m_apParticles = nullptr;
    } else {
        m_apParticles = static_cast<IKSerializable**>(Mem_AllocAligned16(count * sizeof(IKSerializable*)));
        IKFile_ReadObjectRefArray(file, m_apParticles, count);
    }
    uint8_t nbBoundings = 0;  // kept for m_afBoundingsRadius
    ReadU8(file, &nbBoundings);
    if (nbBoundings == 0) {
        m_apBoundings = nullptr;
    } else {
        m_apBoundings = static_cast<IKSerializable**>(Mem_AllocAligned16(nbBoundings * sizeof(IKSerializable*)));
        IKFile_ReadObjectRefArray(file, m_apBoundings, nbBoundings);
    }
    ReadU8(file, &count);
    if (count == 0) {
        m_apObjects = nullptr;
    } else {
        m_apObjects = static_cast<IKSerializable**>(Mem_AllocAligned16(count * sizeof(IKSerializable*)));
        IKFile_ReadObjectRefArray(file, m_apObjects, count);
    }
    ReadU8(file, &count);
    if (count == 0) {
        m_apTrails = nullptr;
    } else {
        m_apTrails = static_cast<IKSerializable**>(Mem_AllocAligned16(count * sizeof(IKSerializable*)));
        IKFile_ReadObjectRefArray(file, m_apTrails, count);
    }
    IKFile_ReadRef(file, &m_pShadowCpnt);
    ReadU8(file, &count);
    // Allocated even for a count of 0.
    m_apUnk134 = static_cast<IKSerializable**>(Mem_AllocAligned16(count * sizeof(IKSerializable*)));
    IKFile_ReadObjectRefArray(file, m_apUnk134, count);
    IKFile_ReadRef(file, &m_pAnimDico);
    IKFile_ReadRef(file, &m_pSoundDico);
    IKFile_ReadRef(file, &m_pWaterWaveFxData);
    IKFile_ReadRef(file, &m_pWaterSplashFxData);
    IKFile_ReadRef(file, &m_unk1a0);
    ReadU8(file, &m_aui8Unk1a4[0]);
    ReadU8(file, &m_aui8Unk1a4[1]);
    ReadU8(file, &m_aui8Unk1a4[2]);
    ReadU8(file, &m_aui8Unk1a4[3]);
    ReadU8(file, &m_aui8Unk1a4[4]);
    ReadU8(file, &m_aui8Unk1a4[5]);
    ReadU8(file, &m_aui8Unk1a4[6]);
    ReadU8(file, &m_aui8Unk1a4[7]);
    ReadU8(file, &m_aui8Unk1a4[8]);
    ReadU8(file, &m_aui8Unk1a4[9]);
    ReadU8(file, &m_aui8Unk1a4[10]);
    ReadU8(file, &m_aui8Unk1a4[11]);
    ReadU8(file, &m_aui8Unk1a4[12]);
    ReadU8(file, &m_aui8Unk1a4[13]);
    ReadU8(file, &m_aui8Unk1a4[14]);
    ReadU8(file, &m_aui8Unk1a4[15]);
    ReadU8(file, &m_aui8Unk1a4[16]);
    ReadU8(file, &m_aui8Unk1a4[17]);
    ReadU8(file, &m_aui8Unk1a4[18]);
    ReadU8(file, &m_aui8Unk1a4[19]);
    ReadU8(file, &m_aui8Unk1a4[20]);
    ReadU8(file, &m_aui8Unk1a4[21]);
    ReadU8(file, &m_aui8Unk1a4[22]);
    ReadU8(file, &m_aui8Unk1a4[23]);
    // The counts come from the hero group (m_pGrpHero vt+0x11c / vt+0x124 with m_ui8Hero; XXL2 asks
    // IKGrpHero the same way). The group is always the CKGrpS08Hero, whose two methods index constant tables.
    const uint8_t nbSpeedModes = CKGrpS08Hero_GetNbSpeedModes(m_ui8Hero);
    if (nbSpeedModes == 0) {
        m_asSpeedModes = nullptr;
    } else {
        m_asSpeedModes = static_cast<SHeroSpeedMode*>(Mem_AllocAligned16(nbSpeedModes * sizeof(SHeroSpeedMode)));
    }
    ReadHeroSpeedMode(file, K_LEVEL_PLATEFORMS, m_asSpeedModes, nbSpeedModes);
    const uint8_t nbJumps = CKGrpS08Hero_GetNbJumps(m_ui8Hero);
    if (nbJumps == 0) {
        m_asJumps = nullptr;
    } else {
        m_asJumps = static_cast<SHeroJump*>(Mem_AllocAligned16(nbJumps * sizeof(SHeroJump)));
    }
    for (uint32_t i = 0; i < nbJumps; ++i) {
        ReadF32LE(file, &m_asJumps[i].m_fImpulse);
        ReadU8(file, &m_asJumps[i].m_bDefaultEnable);
    }
    if (nbBoundings == 0) {
        m_afBoundingsRadius = nullptr;
    } else {
        m_afBoundingsRadius = static_cast<float*>(Mem_AllocAligned16(nbBoundings * sizeof(float)));
        // one read of nbBoundings words in the original, then each word swapped
        for (uint32_t i = 0; i < nbBoundings; ++i) ReadF32LE(file, &m_afBoundingsRadius[i]);
    }
    ReadF32LE(file, &m_unk1c8);
    ReadF32LE(file, &m_unk1cc);
    ReadF32LE(file, &m_unk1d0);
    ReadF32LE(file, &m_unk1d4);
    ReadU32LE(file, &m_unk1d8);
    ReadF32LE(file, &m_unk1dc);
    ReadU32LE(file, &m_unk1e0);
    ReadF32LE(file, &m_unk1e4);
    ReadU32LE(file, &m_unk1e8);
    ReadF32LE(file, &m_unk1ec);
    ReadF32LE(file, &m_unk1f0);
    // one 8-byte read in the original, then both words swapped
    ReadF32LE(file, &m_unk1f4);
    ReadF32LE(file, &m_unk1f8);
    ReadF32LE(file, &m_unk1fc);
    ReadF32LE(file, &m_unk200);
    ReadF32LE(file, &m_unk204);
    ReadF32LE(file, &m_unk208);
    ReadF32LE(file, &m_unk20c);
    ReadF32LE(file, &m_unk210);
    ReadF32LE(file, &m_unk214);
    ReadF32LE(file, &m_unk218);
    ReadF32LE(file, &m_unk21c);
    ReadF32LE(file, &m_unk220);
    ReadF32LE(file, &m_unk224);
    ReadF32LE(file, &m_unk228);
    ReadF32LE(file, &m_unk22c);
    ReadF32LE(file, &m_unk230);
    ReadF32LE(file, &m_unk234);
    ReadF32LE(file, &m_unk238);
    ReadF32LE(file, &m_unk23c);
    // one 8-byte read in the original, then both words swapped
    ReadF32LE(file, &m_unk240);
    ReadF32LE(file, &m_unk244);
    ReadF32LE(file, &m_unk248);
    ReadF32LE(file, &m_unk24c);
    ReadF32LE(file, &m_unk250);
    ReadF32LE(file, &m_unk254);
    ReadF32LE(file, &m_unk258);
    ReadF32LE(file, &m_unk25c);
    ReadF32LE(file, &m_unk260);
    ReadF32LE(file, &m_unk264);
    ReadF32LE(file, &m_unk268);
    ReadF32LE(file, &m_unk26c);
    ReadF32LE(file, &m_unk270);
    ReadF32LE(file, &m_unk274);
    ReadF32LE(file, &m_unk278);
    ReadF32LE(file, &m_unk27c);
    ReadF32LE(file, &m_unk280);
    ReadF32LE(file, &m_unk284);
    ReadF32LE(file, &m_unk288);
    ReadF32LE(file, &m_unk28c);
    ReadF32LE(file, &m_unk290);
    ReadF32LE(file, &m_unk294);
    ReadF32LE(file, &m_unk298);
    ReadF32LE(file, &m_unk29c);
    ReadF32LE(file, &m_unk2a0);
    ReadF32LE(file, &m_unk2a4);
    ReadF32LE(file, &m_unk2a8);
    ReadF32LE(file, &m_unk2ac);
    ReadF32LE(file, &m_unk2b0);
    ReadF32LE(file, &m_unk2b4);
    ReadF32LE(file, &m_unk2b8);
    ReadF32LE(file, &m_unk2bc);
    ReadF32LE(file, &m_unk2c0);
    ReadF32LE(file, &m_unk2c4);
    ReadF32LE(file, &m_unk2c8);
    ReadF32LE(file, &m_unk2cc);
    ReadF32LE(file, &m_unk2d0);
    ReadF32LE(file, &m_unk2d4);
    ReadF32LE(file, &m_unk2d8);
    ReadF32LE(file, &m_unk2dc);
    ReadF32LE(file, &m_unk2e0);
    ReadF32LE(file, &m_unk2e4);
    ReadF32LE(file, &m_unk2e8);
    ReadF32LE(file, &m_unk2ec);
    ReadF32LE(file, &m_unk2f0);
    ReadF32LE(file, &m_unk2f4);
    ReadF32LE(file, &m_unk2f8);
    ReadF32LE(file, &m_unk2fc);
    ReadF32LE(file, &m_unk300);
    ReadF32LE(file, &m_unk304);
    ReadF32LE(file, &m_unk308);
    ReadF32LE(file, &m_unk30c);
    ReadF32LE(file, &m_unk310);
    ReadF32LE(file, &m_unk314);
    ReadF32LE(file, &m_unk318);
    ReadF32LE(file, &m_unk31c);
    ReadF32LE(file, &m_unk320);
    ReadF32LE(file, &m_unk324);
    ReadF32LE(file, &m_unk328);
    ReadF32LE(file, &m_unk32c);
    ReadS32LE(file, &m_unk330);
    ReadU16LE(file, &m_unk334);
    ReadU16LE(file, &m_unk336);
    ReadU16LE(file, &m_unk338);
    ReadU16LE(file, &m_unk33a);
    ReadU16LE(file, &m_unk33c);
    ReadU16LE(file, &m_unk33e);
    ReadU16LE(file, &m_unk340);
    ReadU8(file, &m_unk342);
    ReadU8(file, &m_unk343);
    ReadU8(file, &m_unk344);
    ReadU8(file, &m_unk345);
    ReadU8(file, &m_unk346);
    ReadU8(file, &m_unk347);
    ReadU8(file, &m_unk348);
    ReadU8(file, &m_unk349);
    ReadU8(file, &m_unk34a);
    ReadU8(file, &m_unk34b);
    ReadU8(file, &m_unk34c);
    ReadU8(file, &m_unk34d);
    ReadU8(file, &m_unk34e);
    ReadU8(file, &m_unk34f);
    ReadU8(file, &m_unk350);
    m_PFCpnt.CKPathFindingCpnt::Load(file, K_LEVEL_PLATEFORMS);
    return 1;
}

// 0x003462b0 IKHkHero_vf50: the skin controller is the scene node's animation controller (CAnimatedNode +0x30).
void IKHkHero::Start() {
    m_unk164 = static_cast<CAnimatedNode*>(m_pKGLObject)->m_pController;
}

namespace {
// 0x009be8f8 / 0x009be920 / 0x009be970 IKHkHero_CompareEntriesByByte10Desc*: the rows by the top byte of their
// last word (the byte at +0x10), the largest first.
int CompareRowsByByte10Desc(const void* a, const void* b) {
    const uint32_t ka = static_cast<const SHeroStateRow*>(a)->m_key >> 24;
    const uint32_t kb = static_cast<const SHeroStateRow*>(b)->m_key >> 24;
    return ka < kb ? 1 : (ka > kb ? -1 : 0);
}
// 0x009be948 IKHkHero_CompareEntriesByByte12Desc_maybe: by the third byte (+0x12), the largest first.
int CompareRowsByByte12Desc(const void* a, const void* b) {
    const uint32_t ka = (static_cast<const SHeroStateRow*>(a)->m_key >> 8) & 0xffu;
    const uint32_t kb = (static_cast<const SHeroStateRow*>(b)->m_key >> 8) & 0xffu;
    return ka < kb ? 1 : (ka > kb ? -1 : 0);
}

// One state table of InitRuntimeTables (the same code inlined four times): a copy of the group's rows sorted
// by their state id, and a second array of the first pointer to member function of each sorted row (8 bytes
// each). `current` starts on that array, the state id on 0xff (no state).
void BuildStateTable(const SHeroStateRow* source, uint8_t count, int (*compare)(const void*, const void*),
                     SHeroStateRow*& rows, SHeroStateHandler*& handlers, uint8_t& countOut, SHeroStateHandler*& current,
                     uint8_t& state) {
    const uint32_t bytes = static_cast<uint32_t>(count) * 4u + static_cast<uint32_t>(count) * 0x10u;
    rows = static_cast<SHeroStateRow*>(Mem_AllocAligned16(bytes));
    std::memcpy(rows, source, bytes);
    std::qsort(rows, count, sizeof(SHeroStateRow), compare);
    handlers = static_cast<SHeroStateHandler*>(Mem_AllocAligned16(static_cast<uint32_t>(count) << 3));
    for (uint32_t i = 0; i < count; ++i) {
        handlers[i].m_aPtmf[0] = rows[i].m_aPtmf0[0];
        handlers[i].m_aPtmf[1] = rows[i].m_aPtmf0[1];
    }
    countOut = count;
    current = handlers;
    state = 0xff;
}

// +0x58 of an animation controller, whatever its class, takes the bits of 1.0f (a CKBlenderController's blend
// weight; a CKAnmKeyFrameController's animation word, which SetAnim overwrites).
void StoreOneAtWord58(IKSerializable* controller) {
    const uint32_t key = (static_cast<uint32_t>(controller->GetClassID()) << 6) | static_cast<uint32_t>(controller->GetClassType());
    if (key == CKBlenderController::kClassKey) {
        static_cast<CKBlenderController*>(controller)->m_unk58 = 1.0f;
    } else if (key == CKAnmKeyFrameController::kClassKey) {
        static_cast<CKAnmKeyFrameController*>(controller)->m_unk58 = reinterpret_cast<RtAnimAnimation*>(static_cast<uintptr_t>(0x3f800000u));
    }
}
}  // namespace

// 0x00345408 IKHkHero_InitRuntimeTables_maybe
void IKHkHero::InitRuntimeTables() {
    IKGrpHero* group = static_cast<IKGrpHero*>(m_pGrpHero);
    m_aui8JoyInputs = static_cast<uint8_t*>(Mem_CallocAligned16(1, group->GetHeroRuntimeBlockSize()));  // vt+0x10c
    m_unk81 = 0;
    m_unk88 = 0;
    const uint32_t slotCount = group->GetNbAnimBlendSlots(m_ui8Hero);  // vt+0x134
    if (slotCount == 0) {
        m_pAnimBlendSlots = nullptr;
    } else {
        // OperatorNewArray(n * 0x18 + 4): the count cookie, then the slots (vtable, controller 0).
        m_pAnimBlendSlots = new AnimBlendSlot[slotCount];
        for (uint32_t i = 0; i < slotCount; ++i) m_pAnimBlendSlots[i].m_pController = nullptr;
        // Each slot takes the controller of the same index (vt+0x08 AnimBlendSlot_InitThunk).
        for (uint32_t i = 0; i < slotCount; ++i) m_pAnimBlendSlots[i].Init(m_apUnk134[i]);
        // The blenders' weights: the root blender (the scene node's controller), then down its first
        // controllers; from the second one on, the previous blender's second controller as well.
        IKSerializable* controller = nullptr;
        for (uint32_t i = 0; i < slotCount; ++i) {
            if (i == 0) {
                controller = static_cast<CAnimatedNode*>(m_pKGLObject)->m_pController;
            } else {
                CKBlenderController* previous = static_cast<CKBlenderController*>(controller);
                IKSerializable* second = previous->m_apControllers[1];
                controller = previous->m_apControllers[0];
                StoreOneAtWord58(second);
            }
            StoreOneAtWord58(controller);
        }
    }
    BuildStateTable(group->GetHeroStatesA(), group->GetNbHeroStatesA(), CompareRowsByByte10Desc, m_unka0, m_unka4, m_ui8IANbStates,
                    m_unka8, m_ui8IACurrentState);  // vt+0x144 / +0x148
    BuildStateTable(group->GetHeroStatesB(), group->GetNbHeroStatesB(), CompareRowsByByte10Desc, m_unkc0, m_unkc4, m_ui8FightNbStates,
                    m_unkc8, m_ui8FightCurrentState);  // vt+0x14c / +0x150
    BuildStateTable(group->GetHeroStatesD(), group->GetNbHeroStatesD(), CompareRowsByByte12Desc, m_unk140, m_unk144, m_ui8AnimNbStates,
                    m_unk148, m_ui8AnimCurrentState);  // vt+0x13c / +0x140
    BuildStateTable(group->GetHeroStatesC(), group->GetNbHeroStatesC(), CompareRowsByByte10Desc, m_unk520, m_unk524, m_ui8DynamicNbStates,
                    m_unk528, m_ui8DynamicCurrentState);  // vt+0x128 / +0x12c
    VfD4();
}

// 0x00346400 IKHkHero_PostLoad: IKLife_PostLoad, and for the level data the runtime tables and the hero's blend
// slot (vt+0xd8).
int32_t IKHkHero::PostLoad(int32_t type) {
    PostLoadLife(type);
    if (type == K_LEVEL_PLATEFORMS) {
        InitRuntimeTables();
        InitAnimBlendSlot();
    }
    return 1;
}

namespace {
// 0x004f85a8 CKS08GameManager_vf290 (the game manager's vt+0x290): the current spawn point's record for a hero.
const CKS08GameSpawnPoint::Slot* GetHeroStartSlot(CDefaultGameManager* gm, uint8_t hero) {
    IKGameStructure* structure = static_cast<IKGameStructure*>(gm->m_gameStructure);
    if (structure != nullptr) {
        CKGameSpawnPoint* spawnPoint = structure->m_pCurrentSpawnPoint;
        if (spawnPoint != nullptr) return static_cast<CKS08GameSpawnPoint*>(spawnPoint)->ResolveSlotPosition(hero);
    }
    return nullptr;
}

}  // namespace

// 0x00346480 IKHkHero_ResetRuntimeState_maybe: `flag` 0 keeps the node's own position and heading; otherwise the
// hero goes back to its start state: the first initial state of the file, or the record of the current spawn point
// when the game manager has one.
void IKHkHero::ResetRuntimeState(int32_t flag) {
    // The tail of the hero record (+0x848..) belongs to CKHkS08Hero, the only hero hook; the original base code
    // writes it with the same offsets.
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(this);
    float posX, posY, posZ, dirX, dirY, dirZ;
    uint8_t trackedLeader, leader;
    uint32_t startWord = 0;  // the record's word at +0x1c and byte at +0x20 (only used when flag != 0)
    uint32_t startByte = 0;
    if (flag == 0) {
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        posX = frame->modelling.pos.x;
        posZ = frame->modelling.pos.z;
        posY = frame->modelling.pos.y;
        dirZ = frame->modelling.at.z;
        dirX = frame->modelling.at.x;
        dirY = frame->modelling.at.y;
        trackedLeader = m_ui8TrackedLeader;
        leader = m_ui8Leader;
    } else {
        const SHeroInitialState& initial = m_aInitialStates[0];
        posX = initial.m_vPos.x;
        posY = initial.m_vPos.y;
        posZ = initial.m_vPos.z;
        dirX = initial.m_vDir.x;
        dirY = initial.m_vDir.y;
        dirZ = initial.m_vDir.z;
        trackedLeader = initial.m_ui8TrackedLeader;
        leader = initial.m_ui8Leader;
        startWord = initial.m_unk1c;
        startByte = initial.m_unk20;
        CDefaultGameManager* gm = g_pEngine->m_gameManager;
        if (gm != nullptr && gm->IsKindOfClass(0x3b0c) != 0) {  // vt+0x08
            const CKS08GameSpawnPoint::Slot* slot = GetHeroStartSlot(gm, m_ui8Hero);  // vt+0x290
            if (slot != nullptr) {
                posX = slot->m_vPosition[0];
                posY = slot->m_vPosition[1];
                posZ = slot->m_vPosition[2];
                dirX = slot->m_vDirection[0];
                dirY = slot->m_vDirection[1];
                dirZ = slot->m_vDirection[2];
                startByte = slot->m_unk20;
                trackedLeader = slot->m_unk18;
                leader = slot->m_unk19;
                startWord = slot->m_unk1c;
            }
        }
    }
    // (flag == 0: the original also derives two words from m_unk35c / m_unk358 / m_unk3b0 here; they are only
    // used by the flag != 0 block below.)
    m_ui8TrackedLeader = trackedLeader;
    m_ui8Leader = leader;
    m_unk64 = posX;
    m_unk6c = posZ;
    m_unk68 = posY;
    // the up vector (0, 1, 0), 0x00c50d40 (TOC1 +0x2b24)
    m_unk70 = 0.0f;
    m_unk74 = 1.0f;
    m_unk78 = 0.0f;
    m_unk7c = 0;
    m_unk88 = 0;
    m_unk90 = 0;
    m_unk94 = 0;
    m_unk98 = 0;
    m_unk9c = 0;
    m_ui8IACurrentState = 0xff;
    m_unkb0 = 0;
    m_unkbc = 0;
    m_ui8FightCurrentState = 0xff;
    m_unkd0 = 0;
    m_unkd4 = 0;
    m_unkb4 = -1000.0f;  // TOC1 +0x2b28
    m_unkb8 = -1000.0f;
    // the zero vector 0x00c50d64 (TOC1 +0x2b2c)
    m_unkd8 = 0.0f;
    m_unkdc = 0.0f;
    m_unke0 = 0.0f;
    m_unke4 = 0;
    m_unke8 = 0.0f;
    m_unkf0 = 0.0f;
    m_unkec = 0.0f;
    m_unkf4 = 0;
    m_unkf8 = 0.0f;
    m_unk100 = 0.0f;
    m_unkfc = 0.0f;
    m_unk114 = 1.0f;  // TOC1 +0x2ac8
    m_ui8AnimCurrentState = 0xff;
    m_unk15c = 0;
    m_i16CurAnimIndex = 0xffff;
    m_unk104 = 0;
    m_unk108 = 0;
    m_unk118 = 0xff;
    m_unk120 = 0;
    m_pTargetedEnemy = 0;
    m_unk128 = 0;
    m_pTargetedMecaHook = 0;
    m_unk130 = 0;
    m_unk150 = 0;
    m_unk154 = 0;
    m_unk158 = 0;
    m_unk11c = -1000.0f;
    m_unk16c = 0;
    // The hot spots of the six body parts (the group's table 0x00b01018, per hero): the index when that hot spot
    // has a node, else 0xff.
    {
        IKGrpHero* group = static_cast<IKGrpHero*>(m_pGrpHero);
        uint8_t* indices[6] = {&m_unk16d, &m_unk16e, &m_unk16f, &m_unk170, &m_unk171, &m_unk172};
        for (uint8_t i = 0; i < 6; ++i) {
            const uint8_t index = group->GetHotSpotIndex(m_ui8Hero, i);  // vt+0x16c
            if (index == 0xff || static_cast<CSGHotSpot*>(m_apHotSpots[static_cast<int8_t>(index)])->m_pParent == nullptr) {
                *indices[i] = 0xff;
            } else {
                *indices[i] = index;
            }
        }
    }
    // The speed modes and jumps start unlocked as their defaults say.
    {
        const uint32_t speedModes = CKGrpS08Hero_GetNbSpeedModes(m_ui8Hero);  // vt+0x11c
        for (uint32_t i = 0; i < speedModes; ++i) {
            m_asSpeedModes[i].m_bLocked = 0;
            m_asSpeedModes[i].m_bEnable = m_asSpeedModes[i].m_bDefaultEnable;
        }
        const uint32_t jumps = CKGrpS08Hero_GetNbJumps(m_ui8Hero);  // vt+0x124
        for (uint32_t i = 0; i < jumps; ++i) {
            m_asJumps[i].m_bLocked = 0;
            m_asJumps[i].m_bEnable = m_asJumps[i].m_bDefaultEnable;
        }
    }
    m_unk368 = 0;
    m_ui32HeroFlags354 = 0;
    m_ui32HeroFlags358 = 0;
    m_ui32HeroFlags35C = 0;
    m_ui32HeroFlags360 = 0;
    m_ui32HeroFlags364 = 0;
    if (flag != 0) {
        // bit 6 of +0x35c: the partner dragon (not the one that controls) whose start word is 1; bit 22 of +0x358
        // and bit 12 of +0x360 take the start byte.
        uint32_t bit6 = 0;
        if (m_ui8Hero != m_ui8TrackedLeader) {
            const uint32_t value = startWord ^ 1u;
            const int32_t sign = static_cast<int32_t>(value) >> 31;
            const uint32_t magnitude = (static_cast<uint32_t>(sign) ^ value) - static_cast<uint32_t>(sign);
            bit6 = ((magnitude - 1u) >> 25) & 0x40u;
        }
        m_ui32HeroFlags35C = bit6 | (m_ui32HeroFlags35C & 0xffffffbfu);
        m_ui32HeroFlags358 = (m_ui32HeroFlags358 & 0xffbfffffu) | (startByte << 22);
        m_ui32HeroFlags360 = (m_ui32HeroFlags360 & 0xffffefffu) | (startByte << 12);
    }
    // the zero vector twice, the zero vector again, ...
    m_unk370 = 0.0f;
    m_unk378 = 0.0f;
    m_unk374 = 0.0f;
    m_unk37c = 0.0f;
    m_unk384 = 0.0f;
    m_unk380 = 0.0f;
    m_unk388 = 0;
    m_unk38c = 0;
    m_unk390 = 0;
    m_unk392 = 0;
    m_unk394 = 0;
    m_unk395 = 0;
    m_unk398 = 0.0f;
    m_unk39c = 0.0f;
    m_unk3a0 = 0.0f;
    m_unk3a4 = 0.0f;
    m_unk3ac = 0.0f;
    m_unk3a8 = 0.0f;
    m_unk3b0 = 0;
    m_unk3b4 = 0;
    m_unk3b8 = dirX;
    m_unk3bc = dirY;
    m_unk3c0 = dirZ;
    m_unk3c4 = posX;
    m_unk3cc = posZ;
    m_unk3c8 = posY;
    m_unk3d0 = posX;
    m_unk3d8 = posZ;
    m_unk3d4 = posY;
    m_unk3dc = 0;
    // The path-finding character: bits 3..10 cleared, then the word at +0x330 (shifted by 3) merged in, the low
    // three bits replaced by 1, bit 11 set; copied to the component's character type.
    {
        uint32_t bits = m_PFCharacter.m_bits;
        bits = (bits & 0xfffff807u) | (static_cast<uint32_t>(m_unk330) << 3 & 0xfffffff8u);
        m_PFCharacter.m_bits = bits;
        m_PFCharacter.m_fRadius = m_unk218;
        bits = (bits & 0xfffffff8u) | 1u;
        m_PFCharacter.m_bits = bits | 0x800u;
    }
    m_PFCpnt.m_CharacterType.m_bits = m_PFCharacter.m_bits;
    m_PFCpnt.m_CharacterType.m_fMaxStepRise = m_PFCharacter.m_fMaxStepRise;
    m_PFCpnt.m_CharacterType.m_fRadius = m_PFCharacter.m_fRadius;
    m_PFCpnt.m_CharacterType.m_fMaxStepHeight = m_PFCharacter.m_fMaxStepHeight;
    {
        float limit = m_unk27c;
        const float cap = 0.5f;  // 0x00c40260 (TOC1 +0x2b30)
        if (!(limit < cap)) limit = cap;
        m_PFCpnt.m_fPointValidationDistanceSquared = limit * limit;
    }
    {
        const CVector3 destination = {posX, posY, posZ};
        m_PFCpnt.SetDestination(&destination);  // 0x001e3a40
    }
    m_PFCpnt.m_bits70 = (m_PFCpnt.m_bits70 & 0xfffffffeu) | 1u;
    m_unk468 = 0.0f;
    m_unk470 = 0.0f;
    m_unk46c = 0.0f;
    m_unk474 = posX;
    m_unk478 = posY;
    m_unk47c = posZ;
    m_unk480 = 0;
    m_unk484 = -1000.0f;
    m_unk488 = -1000.0f;
    m_unk48c = -1000.0f;
    m_unk490 = 0.0f;
    m_unk494 = 0.0f;
    m_unk498 = 0.0f;
    m_unk49c = 0.0f;
    m_unk4a0 = 0.0f;
    m_unk4a4 = 0.0f;
    m_gcDatasIn.m_MasksOfGrdForTest[0] = 1;
    m_gcDatasIn.m_MasksOfGrdForTest[1] = 0;
    m_gcDatasIn.m_fDeltaMax = m_unk1f0;
    m_gcDatasIn.m_fObjectHeight = Vf160() * m_unk278;  // vt+0x160
    m_ui8DynamicCurrentState = 0xff;
    m_fCurHSpeed = 0;
    m_fCurVSpeed = 0;
    m_unk510 = Vf160() * m_unk278;
    const CVector3 position = {posX, posY, posZ};
    const CVector3 direction = {dirX, dirY, dirZ};
    SetPositionAndDirection(&position, &direction);  // 0x00359988
    ApplyPositionToFrame();                          // 0x00355c00
    m_unk53c = m_unk1fc;
    m_unk564 = 0.0f;
    m_unk568 = 1.0f;
    m_unk56c = 0.0f;
    m_unk570 = m_unk54c;
    m_unk574 = m_unk550;
    m_unk578 = m_unk554;
    m_unk57c = m_unk54c;
    m_unk580 = m_unk550;
    m_unk584 = m_unk554;
    m_unk588 = 0;
    m_unk591 = 0xff;
    m_unk589 = 0;
    m_unk58c = 0;
    m_unk590 = 0xff;
    m_unk594 = 0;
    m_unk598 = 0;
    m_unk59c = nullptr;
    m_unk5a0 = 0;
    m_unk5a4 = 0;
    m_unk5a8 = 0.0f;
    m_unk5ac = 0.0f;
    m_unk5b0 = 0.0f;
    m_unk5b4 = 0.0f;
    m_unk5bc = 0.0f;
    m_unk5b8 = 0.0f;
    m_unk5c0 = 0.0f;
    m_unk5c8 = 0.0f;
    m_unk5c4 = 0.0f;
    m_unk5cc = 0.0f;
    m_unk5d4 = 0.0f;
    m_unk5d0 = 0.0f;
    m_unk5d8 = 0.0f;
    m_unk5e0 = 0.0f;
    m_unk5dc = 0.0f;
    m_unk5e4 = 0.0f;
    m_unk5ec = 0.0f;
    m_unk5e8 = 0.0f;
    m_unk5f0 = 0.0f;
    m_unk5f8 = 0.0f;
    m_unk5f4 = 0.0f;
    m_unk5fc = 0.0f;
    m_unk604 = 0.0f;
    m_unk600 = 0.0f;
    m_unk608 = -1000.0f;
    m_unk60c = 0;
    m_unk660 = 0.0f;
    m_unk668 = 0.0f;
    m_unk664 = 0.0f;
    m_unk66c = 0.0f;
    m_unk674 = 0.0f;
    m_unk670 = 0.0f;
    m_unk678 = 0;
    m_unk67c = 0;
    m_unk680 = 0;
    m_unk684 = 0.0f;
    m_unk68c = 0.0f;
    m_unk688 = 0.0f;
    m_unk690 = 0.0f;
    m_unk694 = 0.0f;
    m_unk698 = 0.0f;
    m_unk69c = 0.0f;
    m_unk6a0 = 0.0f;
    m_unk6a4 = 0.0f;
    m_unk6a8 = 0.0f;
    m_unk6b0 = 0.0f;
    m_unk6ac = 0.0f;
    m_unk6b4 = 0.0f;
    m_unk6bc = 0.0f;
    m_unk6b8 = 0.0f;
    m_unk6c0 = 0;
    m_unk6c4 = 0;
    m_unk6c8 = 0;
    m_unk6cc = 0;
    m_unk6d0 = 1;
    m_unk6d1 = 0;
    m_unk6d4 = 0.0f;
    m_unk6d8 = 0.0f;
    m_unk6dc = 0.0f;
    m_unk6e0 = 0.0f;
    m_unk6e8 = 0.0f;
    m_unk6e4 = 0.0f;
    m_unk6ec = -1000.0f;
    m_unk6f0 = -1000.0f;
    m_unk6f4 = -1000.0f;
    m_unk6f8 = 0.0f;
    m_unk700 = 0.0f;
    m_unk6fc = 0.0f;
    // twelve unit direction vectors from 0x00c50d34.. (TOC1 +0x2b34): (1,0,0), (0,1,0), (0,0,1) in the orders the
    // original stores them
    m_unk704 = 0.0f;
    m_unk70c = 1.0f;
    m_unk708 = 0.0f;
    m_unk710 = 0.0f;
    m_unk718 = 1.0f;
    m_unk714 = 0.0f;
    m_unk71c = 0.0f;
    m_unk720 = 0.0f;
    m_unk724 = 1.0f;
    m_unk728 = 0.0f;
    m_unk72c = 0.0f;
    m_unk730 = 1.0f;
    m_unk734 = 0.0f;
    m_unk738 = 0.0f;
    m_unk73c = 1.0f;
    m_unk740 = 0.0f;
    m_unk744 = 0.0f;
    m_unk748 = 1.0f;
    m_unk74c = 0.0f;
    m_unk750 = 0.0f;
    m_unk758 = 0.0f;
    m_unk754 = 1.0f;
    m_unk75c = 0.0f;
    m_unk764 = 0.0f;
    m_unk760 = 1.0f;
    m_unk768 = 0.0f;
    m_unk76c = 1.0f;
    m_unk770 = 0.0f;
    m_unk778 = 1.0f;
    m_unk774 = 0.0f;
    m_unk77c = 0.0f;
    m_unk784 = 1.0f;
    m_unk780 = 0.0f;
    m_unk788 = 0;
    m_unk78c = 0;
    m_unk790 = -1000.0f;
    m_unk794 = m_unk218;
    m_unk798 = 0.0f;
    m_unk7a0 = 0.0f;
    m_unk79c = 1.0f;
    m_unk7a4 = 0;
    m_unk7a8 = 0;
    m_unk7ac = 0;
    m_unk7b0 = 0;
    m_unk7b4 = 0;
    m_unk7b8 = 0;
    m_unk7bc = 0;
    m_unk7c0 = 0.0f;
    m_unk7c4 = 0.0f;
    m_unk7c8 = 0.0f;
    m_unk7cc = 0.0f;
    m_unk7d0 = 0.0f;
    m_unk7d4 = 0.0f;
    m_unk7d8 = -1000.0f;
    m_unk7dc = 0;
    m_gcDatasIn2_maybe.m_MasksOfGrdForTest[0] = 1;
    m_gcDatasIn2_maybe.m_MasksOfGrdForTest[1] = 8;
    m_gcDatasIn2_maybe.m_fDeltaMax = m_unk1f0;
    m_gcDatasIn2_maybe.m_fObjectHeight = m_unk1f0 + 0.001f;  // TOC1 +0x2b38
    hero->m_unk848 = 0;
    hero->m_unk84c = 0;
    hero->m_unk850 = 0;
    hero->m_unk854 = -1000.0f;
    hero->m_unk858 = 0.0f;
    hero->m_unk860 = 0.0f;
    hero->m_unk85c = 0.0f;
    hero->m_unk864 = 0.0f;
    hero->m_unk868 = 0.0f;
    hero->m_unk86c = 0.0f;
    hero->m_unk888 = 0;
    hero->m_unk880 = -1000.0f;
    hero->m_unk884 = m_unk2e4;
    hero->m_unk870 = -1000.0f;
    hero->m_unk874 = 0;
    hero->m_unk878 = -1000.0f;
    hero->m_unk87c = -1000.0f;
    m_gcContact174.m_ui8SectorNumber = 0;
    m_gcContact174.m_pGround = nullptr;
    m_gcContact174.m_i32FaceIndex = -1;
    m_gcContact174.m_eContactStatus = 3;
    m_gcCurDatasInOut.m_pGround = nullptr;
    m_gcCurDatasInOut.m_i32FaceIndex = -1;
    m_gcCurDatasInOut.m_eContactStatus = 3;
    m_gcCurDatasInOut.m_ui8SectorNumber = 0;
    // The ground under the hero's position (+0x54c) into the current contact.
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->GroundProbePoints(&m_gcDatasIn, &m_gcCurDatasInOut, &m_unk54c, 1);
    CopyGroundContact(m_gcOldDatasInOut, m_gcCurDatasInOut);
    m_gcCurDatasInOut2_maybe.m_pGround = nullptr;
    m_gcOldDatasInOut2_maybe.m_ui8SectorNumber = 0;
    m_gcCurDatasInOut2_maybe.m_i32FaceIndex = -1;
    m_gcCurDatasInOut2_maybe.m_ui8SectorNumber = 0;
    m_gcCurDatasInOut2_maybe.m_eContactStatus = 3;
    m_gcOldDatasInOut2_maybe.m_i32FaceIndex = -1;
    m_gcOldDatasInOut2_maybe.m_eContactStatus = 3;
    m_gcOldDatasInOut2_maybe.m_pGround = nullptr;
    RestoreDefaultVolumes();  // IKHkHero_CallRestoreDefaultVolumes 0x00352bf8: vt+0x130
}

// 0x00348ac0 CKHkS08Hero_ResetToDefaultState_maybe: the hero leaves whatever state it is in, plays the first
// animation of its dictionary and starts over from the initial state (shadow on, runtime state reset, control
// assignment applied).
void CKHkS08Hero::ResetToDefaultState() {
    CAnimatedNode* node = static_cast<CAnimatedNode*>(m_pKGLObject);
    node->m_sgProperties = node->m_sgProperties & 0xfffffffbu;
    SetMainShadowActive(1);  // 0x00365e78
    IKTime* clock = g_pEngine->m_timeManager->m_pTime;
    if (m_ui8IACurrentState != 0xff) CallStateHandler(m_unka8[m_ui8IACurrentState].m_aPtmf, clock, 2, 0xff);  // the state's exit
    m_ui8IACurrentState = 0xff;
    if (m_ui8FightCurrentState != 0xff) CallStateHandler(m_unkc8[m_ui8FightCurrentState].m_aPtmf, clock, 2, 0xff);  // the state's exit
    m_ui8FightCurrentState = 0xff;
    if (m_ui8DynamicCurrentState != 0xff) CallStateHandler(m_unk528[m_ui8DynamicCurrentState].m_aPtmf, clock, 2, 0xff);  // the state's exit
    m_ui8DynamicCurrentState = 0xff;
    if (m_ui8AnimCurrentState != 0xff) CallStateHandler(m_unk148[m_ui8AnimCurrentState].m_aPtmf, clock, 2, 0xff);  // the state's exit
    m_ui8AnimCurrentState = 0xff;
    if (node->m_pController != m_unk164) node->SetRootController(m_unk164);  // 0x000c99b8
    // The dictionary entry is the animation pointer in the original (null for none); dotd keeps the word.
    RtAnimAnimation* firstAnimation = CAnimationManager_GetAnimation(
        static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_pAnimDico)->m_apAnimations[0]));
    if (firstAnimation != nullptr) {
        AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
        slot->m_unk14 = 0;
        CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
        if (blender != nullptr) blender->m_unk58 = slot->m_unk10 != 0 ? 1.0f : 0.0f;  // TOC1 +0x2ac8
        static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10])
            ->SetAnim(0.0f, firstAnimation, false);  // 0x0007ab20
    }
    ResetInactiveBlendLayers();  // 0x00351908
    ResetRuntimeState(1);        // 0x00346480
    ApplyControlAssignment(1, 0);  // 0x00348010
    UpdateMovement(clock);       // vt+0x17c
    node->ForceWorldMatrixUpdate();  // vt+0x50
    m_ui32HeroFlags354 = (m_ui32HeroFlags354 & 0xffffefffu) | 0x1000u;
}

// 0x00348010 CKHkS08Hero_ApplyControlAssignment_maybe: the hero that the player controls (its tracked leader is
// itself) becomes the group's focused dragon, the other one gets its destination and flags; `isNew` 0 is the
// change of control during the game.
void CKHkS08Hero::ApplyControlAssignment(uint32_t isNew, uint32_t flag) {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if (m_ui8TrackedLeader == m_ui8Hero) {
        if (isNew == 0) {
            group->SetFocusedDragon(this, static_cast<uint8_t>(flag));  // 0x002cc3f0
        } else {
            group->m_ui8FocusedDragon = m_ui8Hero;
        }
        m_PFCpnt.CancelPathRequest();  // 0x001e2820
        m_ui32HeroFlags354 &= 0xfffff7efu;
        m_ui32HeroFlags360 &= 0xbfffffffu;
        m_ui32HeroFlags35C &= 0xdfffff9fu;
        m_ui32HeroFlags358 = (m_ui32HeroFlags358 & 0xfffeffffu) | 0x10000u;
        m_ui32HeroFlags35C &= 0xfffdffffu;
    } else {
        const CVector3* position = reinterpret_cast<const CVector3*>(&m_unk54c);
        if ((isNew & 0xffu) == 0) {
            ResetMoveInput(0);                // 0x00368de0
            UpdateHeroInputDerivedState();    // 0x00368f18
            m_PFCpnt.SetDestination(position);  // 0x001e3a40
            m_unk3b0 = 0;
            m_ui32HeroFlags35C = (m_ui32HeroFlags35C & 0xffffffbfu) | (((group->m_baWorkFlags >> 4) & 1u) << 6);
        } else {
            m_PFCpnt.SetDestination(position);
            m_unk3b0 = 0;
        }
        m_ui32HeroFlags358 = (m_ui32HeroFlags358 & 0xfffeffffu) | 0x10000u;
        if ((m_ui32HeroFlags358 & 1u) != 0) m_unk90->MessageProc(0xc4d, this);  // vt+0x1c
    }
    ResetControlState();  // vt+0xdc
}

namespace {
// The data of message 0x93e (no sender in the EBOOT's code: trigger data): the object and the count CanAttachTo
// takes.
struct SHeroAttachRequest {
    IKSerializable* m_pObject;  // +0x00
    uint8_t m_ui8Count;         // +0x04
};

// The scripted move target of the messages 0xc43 / 0xc3a / 0xc49 / 0xc4a: the position (+0x398..+0x3a0) and the flat
// direction (+0x3a4, +0x3a8 = 0, +0x3ac) normalised (TOC +0x2acc 0.0, +0x2ac8 1.0).
void SetHeroMoveTarget(CKHkS08Hero* hero, const float* position, const float* direction) {
    hero->m_unk398 = position[0];
    hero->m_unk39c = position[1];
    hero->m_unk3a4 = direction[0];
    hero->m_unk3a8 = direction[1];
    hero->m_unk3a8 = 0.0f;
    hero->m_unk3a0 = position[2];
    hero->m_unk3ac = direction[2];
    const float length = std::sqrt(ppc::fmadds(hero->m_unk3ac, hero->m_unk3ac,
                                               ppc::fmadds(hero->m_unk3a4, hero->m_unk3a4,
                                                           hero->m_unk3a8 * hero->m_unk3a8)));  // 0x00010690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;
        hero->m_unk3ac = inverse * hero->m_unk3ac;
        hero->m_unk3a4 = inverse * hero->m_unk3a4;
        hero->m_unk3a8 = inverse * hero->m_unk3a8;
    }
}

// The placement the teleport / track messages carry (`data` points at the reference): a marker beacon (its position
// +0x04, its orientation quaternion +0x10; CKHkTrackerManager_AssignHeroToTrack_maybe 0x4544b8 sends its track
// points), as a matrix (Quat_ToMatrixNormalizing_maybe 0x00241d78; flags bit 17 cleared).
void PlacementMatrix(const CKMarkerBeacon* placement, CMatrix34* m) {
    Quat_ToMatrixNormalizing(placement->m_qOrientation, m);
    m->m_pos = placement->m_v3Position;
    m->m_ui32Flags &= 0xfffdffffu;
}
}  // namespace

// 0x00348220 CKHkS08HeroBase_HandleMessage_maybe (CKHkS08Hero_MessageProc's first step): 1 when the message is not
// handled, 0 when it is, 2 for a bad argument. Category 9: 0x93e (`data`: {object, count byte}) attaches the hero to
// the object (+0x98 / +0x9c, +0x358 bit 14) when it may (vt+0xe0) and nothing is attached. Category 4: 0x400 the aim
// query (vt+0x154, empty for the hero), 0x402 handled. Category 0xc (the jump table 0x00348318, TOC +0x2b44): the
// partner flags (+0x364 bit 14, bit 1; +0x360 bits 12 and 30; +0x35c bits 5, 6, 17, 29), the dragon switches through
// the group (CKGrpS08Hero_RequestDragonSelection_maybe 0x2cbb08, CKGrpS08Hero_FindNextSelectableHero_maybe 0x2cb0a8),
// the teleports (CKHkS08Hero_TeleportTo_maybe 0x36a578) and the scripted move targets of the hero the player does not
// control (+0x24 != +0x25).
int32_t CKHkS08Hero::HeroBaseMessageProc(uint16_t message, void* data) {
    const uint32_t category = (message >> 8) & 0xffu;
    const uint32_t id = message & 0xffu;
    const bool controlled = m_ui8Hero == m_ui8TrackedLeader;
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    if (category == 9) {
        if (id != 0x3e) return 1;
        if (data == nullptr) return 2;
        if ((m_ui32HeroFlags358 & 0x4000u) != 0) return 0;
        const SHeroAttachRequest* request = static_cast<const SHeroAttachRequest*>(data);
        IKSerializable* target = request->m_pObject;
        const uint8_t count = request->m_ui8Count;
        if (CanAttachTo(target, count) == 0 || m_unk98 != 0) return 0;  // vt+0xe0
        m_unk98 = target;
        m_unk9c = count;
        m_ui32HeroFlags358 = (m_ui32HeroFlags358 & ~0x4000u) | 0x4000u;
        return 0;
    }
    if (category == 4) {
        if (id == 0) {
            // vt+0x154 0x002d8c80 CKHkS08Hero_vf154: empty.
            return 0;
        }
        return id == 2 ? 0 : 1;
    }
    if (category != 0xc) return 1;
    switch (id) {
    case 0x0b:
        if (!controlled) m_ui32HeroFlags364 = (m_ui32HeroFlags364 & ~0x4000u) | 0x4000u;
        return 0;
    case 0x0c:
        m_ui32HeroFlags364 &= ~0x4000u;
        return 0;
    case 0x33:
    case 0x34:
    case 0x35: {
        const intptr_t requested = reinterpret_cast<intptr_t>(data);
        if (static_cast<int32_t>(requested) == -1) return 2;
        const uint8_t count = group->GetHeroCount();  // vt+0xf4
        if (!(static_cast<int32_t>(count) > static_cast<int32_t>(requested))) return 2;
        group->RequestDragonSelection(static_cast<uint8_t>(requested), m_ui8Hero, id == 0x35 ? 1 : 0, id == 0x34 ? 1 : 0, 0,
                                      0, 0);  // 0x002cbb08
        return 0;
    }
    case 0x36:
    case 0x37:
    case 0x38:
    case 0x45:
    case 0x4e:
        group->RequestDragonSelection(group->m_ui8FocusedDragon, m_ui8Hero, id == 0x38 ? 1 : 0, id == 0x37 ? 1 : 0,
                                      id == 0x45 ? 1 : 0, 0, id == 0x4e ? 1 : 0);
        return 0;
    case 0x39:
    case 0x3c:
    case 0x3d: {
        if (id != 0x39) {
            if (!controlled) {
                if (id != 0x3d) return 0;
            } else if (id != 0x3c) {
                return 0;
            }
        }
        const CKMarkerBeacon* placement = *static_cast<CKMarkerBeacon* const*>(data);
        alignas(16) CMatrix34 m{};
        PlacementMatrix(placement, &m);
        TeleportTo(&m.m_pos, &m.m_at, 1, 0, 0xffff, 0);  // 0x0036a578
        return 0;
    }
    case 0x3a:
    case 0x49:
    case 0x4a: {
        if (controlled) return 0;
        const CKMarkerBeacon* placement = *static_cast<CKMarkerBeacon* const*>(data);
        if (placement == nullptr) return 0;
        alignas(16) CMatrix34 m{};
        PlacementMatrix(placement, &m);
        const float position[3] = {m.m_pos.x, m.m_pos.y, m.m_pos.z};
        const float direction[3] = {m.m_at.x, m.m_at.y, m.m_at.z};
        SetHeroMoveTarget(this, position, direction);
        if (id == 0x49) {
            m_ui32HeroFlags35C &= ~0x40u;
            m_ui32HeroFlags360 = (m_ui32HeroFlags360 & ~0x40000000u) | 0x40000000u;
        } else if (id == 0x4a) {
            m_ui32HeroFlags35C = (m_ui32HeroFlags35C & 0xdfffffbfu) | 0x20000000u;
        } else {
            m_ui32HeroFlags35C = (m_ui32HeroFlags35C & ~0x60u) | 0x20u;
        }
        return 0;
    }
    case 0x3b:
        if (controlled) return 0;
        m_ui32HeroFlags360 &= ~0x40000000u;
        m_ui32HeroFlags35C &= 0xdfffff9fu;
        return 0;
    case 0x41:
        if (controlled) return 0;
        m_ui32HeroFlags360 &= ~0x40000000u;
        m_ui32HeroFlags35C = (m_ui32HeroFlags35C & 0xdfffff9fu) | 0x40u;
        return 0;
    case 0x42: {
        if (!controlled) return 0;
        const int8_t next = group->FindNextSelectableHero(static_cast<int8_t>(m_ui8Hero));  // 0x002cb0a8, no filter
        if (next == -1) return 0;
        group->RequestDragonSelection(m_ui8Hero, static_cast<uint8_t>(next), 0, 0, 0, 0, 0);
        return 0;
    }
    case 0x43: {
        if (controlled) return 0;
        const float* d = static_cast<const float*>(data);
        SetHeroMoveTarget(this, d, d + 3);
        m_ui32HeroFlags35C = (m_ui32HeroFlags35C & ~0x60u) | 0x20u;
        return 0;
    }
    case 0x44:
        if (controlled) return 0;
        m_ui32HeroFlags35C = (m_ui32HeroFlags35C & ~0x20000u) | 0x20000u;
        return 0;
    case 0x47:
        m_ui32HeroFlags360 = (m_ui32HeroFlags360 & ~0x1000u) | 0x1000u;
        return 0;
    case 0x48:
        m_ui32HeroFlags360 &= ~0x1000u;
        return 0;
    case 0x4b:
        m_ui32HeroFlags364 = (m_ui32HeroFlags364 & ~2u) | 2u;
        return 0;
    case 0x4c:
        m_ui32HeroFlags364 &= ~2u;
        return 0;
    default:
        return 1;
    }
}

// 0x0034f970 CKHkS08HeroBase_AdvanceAnimTime: the active slot's active controller runs on by `dt` (+0x154 keeps it).
void CKHkS08Hero::AdvanceAnimTimeBase(float dt) {
    AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
    CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
    CKAnmKeyFrameController* controller = static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10]);
    controller->m_unk50 = dt + controller->m_unk50;
    m_unk154 = dt;
}

// 0x00347530 UpdateHeroMovementAndContacts_maybe: the hero's frame between the timers and the camera target: the
// per-frame flags (+0x354..+0x368: the animation ends this frame, the path, the flight and fall marks), the object
// height (+0x510), the distance to the focused dragon (+0xbc), the time the player's hero was last drawn (+0xb4 /
// +0xb8), the moving-ground mark; then the contacts, the hazards, the control machine, the interaction, the action
// machine, the locomotion (machine and position), a pending teleport, UpdateMovement, the animation machine, the
// volumes and the footsteps; at the end the frame's flags and the ground's surface flags (+0x358 bits 23..27, +0x360
// bit 13) and the per-frame displacement vectors cleared.
void CKHkS08Hero::UpdateMovementAndContacts(IKTime* clock) {
    if ((m_ui32HeroFlags360 & 0x1000u) != 0) return;
    m_ui32HeroFlags354 = (m_ui32HeroFlags354 & 0xffd7ffffu) & 0xbdeffffdu;
    AnimBlendSlot* slot = GetAnimBlendSlot();  // vt+0x194
    const float dt = clock->m_afDeltaTime[0];
    const float speed = Vf158();               // vt+0x158: the animation speed
    uint32_t endBit = 0;
    CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
    CKAnmKeyFrameController* controller = static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10]);
    if (controller->m_unk58 != nullptr) {
        // Bit 15: the animation reaches its end within this frame's step.
        const float duration = controller->GetDuration();  // 0x0007ab60
        const float time = controller->m_unk50;
        const int32_t loops = ppc::fctiwz(time / duration);
        const float whole = static_cast<float>(static_cast<double>(loops));  // fcfid, frsp
        const float next = ppc::fmadds(dt, speed, time - duration * whole);
        if (duration <= next) endBit = 0x8000u;  // cror lt|eq
    }
    uint32_t flags354 = (m_ui32HeroFlags354 & 0xffff7fffu) | endBit;
    m_ui32HeroFlags354 = flags354;
    uint32_t pathBit = 0;
    if (m_ui8Hero != m_ui8TrackedLeader && (m_unk3b0 & 0x40u) != 0) {
        // The path component's state word (+0x424) has neither flag 0x01 nor 0x40.
        if ((m_PFCpnt.m_ui32Action & 0x41u) == 0) pathBit = 0x20u;
    }
    m_ui32HeroFlags354 = (flags354 & 0xffffffdfu) | pathBit;
    const uint32_t flags35c = m_ui32HeroFlags35C & 0xfff7ffffu;
    m_ui32HeroFlags35C = flags35c;
    uint32_t bit27 = 0;
    if ((m_ui32HeroFlags35C & 0x8000000u) != 0 && (m_ui32HeroFlags358 & 1u) == 0) bit27 = (m_ui32HeroFlags354 & 1u) << 27;
    m_ui32HeroFlags35C = (flags35c & 0xf7ffffffu) | bit27;
    uint32_t bit25 = 0;
    if ((m_ui32HeroFlags360 & 0x2000000u) != 0 && (m_ui32HeroFlags358 & 1u) == 0) bit25 = (m_ui32HeroFlags354 & 1u) << 25;
    uint32_t flags360 = (m_ui32HeroFlags360 & 0xfdffffffu) | bit25;
    m_ui32HeroFlags360 = flags360;
    bool keep3 = false;
    if ((flags360 & 8u) != 0) keep3 = m_fCurHSpeed != 0.0f || (flags360 & 4u) != 0;  // TOC +0x2acc
    flags360 = (flags360 & 0xfffffff7u) | (keep3 ? 8u : 0u);
    m_ui32HeroFlags360 = flags360;
    uint32_t bit5 = 0;
    if ((m_ui32HeroFlags360 & 0x20u) != 0 && (m_ui32HeroFlags358 & 4u) == 0 && (m_ui32HeroFlags354 & 1u) != 0) {
        bit5 = m_unk550 >= m_unk478 ? 0x20u : 0u;  // cror gt|eq
    }
    flags360 = (flags360 & 0xffffffdfu) | bit5;
    m_ui32HeroFlags360 = flags360;
    uint32_t bit26 = 0;
    if ((m_ui32HeroFlags360 & 0x4000000u) != 0) {
        const float since = clock->m_afCurrentTime[0] - m_unk790;
        bit26 = !(since >= m_unk234) ? 0x4000000u : 0u;  // bge: a NaN counts as early
    }
    m_ui32HeroFlags360 = (flags360 & 0xfbffffffu) | bit26;
    m_ui32HeroFlags364 &= 0xbfffffffu;
    m_unk368 &= 0xfffffffbu;
    m_unk589 = m_unk588;
    m_unk588 = SelectMoveEntryIndexForSpeed(m_fCurHSpeed);  // 0x00369ac8
    bool fromHotSpots = false;
    if ((m_ui32HeroFlags354 & 1u) != 0 && (m_ui32HeroFlags358 & 4u) == 0) {
        if (static_cast<int8_t>(m_unk16d) != -1 && m_unk16e != 0xff && (m_unk368 & 0x200u) == 0) fromHotSpots = true;
    }
    if (fromHotSpots) {
        // An airborne hero (+0x354 bit 0): the height between its two hot spots m_unk16d / m_unk16e, at least 0.1
        // (TOC +0x2b3c).
        CVector3 low;
        CVector3 high;
        static_cast<CSGHotSpot*>(m_apHotSpots[static_cast<int8_t>(m_unk16d)])->GetWorldPosition(&low);   // 0x000ce790
        static_cast<CSGHotSpot*>(m_apHotSpots[static_cast<int8_t>(m_unk16e)])->GetWorldPosition(&high);
        const float height = high.y - low.y;
        m_unk510 = height >= 0.1f ? height : 0.1f;
    } else {
        m_unk510 = Vf160() * m_unk278;  // vt+0x160
    }
    m_unkbc = 0.0f;
    IKGrpHero* group = static_cast<IKGrpHero*>(m_pGrpHero);
    const int8_t focus = static_cast<int8_t>(group->m_ui8FocusedDragon);
    if (m_ui8Hero == m_ui8TrackedLeader && focus != -1 && static_cast<int32_t>(focus) != static_cast<int32_t>(m_ui8TrackedLeader)) {
        const CKHkS08Hero* focused = static_cast<const CKHkS08Hero*>(group->m_apHeros[static_cast<uint8_t>(focus)]);
        const float dy = m_unk550 - focused->m_unk550;
        const float dx = m_unk54c - focused->m_unk54c;
        const float dz = m_unk554 - focused->m_unk554;
        m_unkbc = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
    }
    if (m_ui8TrackedLeader == m_ui8Hero) {
        if (static_cast<CSGLeaf*>(m_pKGLObject)->m_ui16LastRenderedFrame == g_ui16RenderFrameCounter) {
            m_unkb4 = -1000.0f;  // TOC +0x2b28
            if (m_unkb8 == -1000.0f) m_unkb8 = clock->m_afCurrentTime[0];
        } else {
            if (m_unkb4 == -1000.0f) m_unkb4 = clock->m_afCurrentTime[0];
            m_unkb8 = -1000.0f;
        }
    }
    if (m_ui8TrackedLeader == m_ui8Hero) {
        if ((m_ui32HeroFlags358 & 8u) != 0 || (m_ui32HeroFlags358 & 4u) != 0) {
            m_unk368 = (m_unk368 & 0xfffffffbu) | 4u;
        } else if ((m_ui32HeroFlags354 & 1u) == 0 && m_fCurHSpeed == 0.0f && m_gcCurDatasInOut.m_pGround != nullptr) {
            // A standing hero on the ground of a pression stone (an active actor of the meca group, game manager +0xc,
            // list +0x2c, of class 0x542: its vt+0xe4 grounds, vt+0xe8 each) gets +0x368 bit 2.
            CKGrpMeca* meca = static_cast<CKGrpMeca*>(g_pEngine->m_gameManager->m_unk04[2]);
            IKSerializable* ground = m_gcCurDatasInOut.m_pGround;  // +0x4b8
            if (meca != nullptr) {
                bool found = false;
                for (IKHook** actor = meca->m_pUnk2c; !found && *actor != nullptr; ++actor) {
                    if ((*actor)->IsKindOfClass(0x542) == 0) continue;  // vt+0x08
                    const CKHkPressionStone* stone = static_cast<const CKHkPressionStone*>(*actor);
                    for (uint32_t k = stone->GetGroundCount(); k != 0; --k) {  // vt+0xe4
                        if (ground == stone->GetGround(k - 1)) {         // vt+0xe8
                            found = true;
                            break;
                        }
                    }
                }
                if (found) m_unk368 = (m_unk368 & 0xfffffffbu) | 4u;
            }
        }
    }
    ResolveHeroContactMovement(clock);            // 0x00353528
    UpdateHazardAndSavedPositionRespawn(clock);   // 0x00355328
    UpdateControlStateMachine(clock);             // 0x003688a8
    TryUseInteractable();                         // vt+0x16c
    UpdateActionStateMachine(clock);              // 0x003656b0
    UpdateLocomotionAndResolvePosition(clock);    // 0x00360c50
    ProcessPendingTeleport(1, 1);                 // 0x0036ad50
    UpdateMovement(clock);                        // vt+0x17c
    UpdateAnimStateMachine(clock);                // 0x00352468
    UpdateSpeedScaledVolumeRadius();              // 0x00352dd0
    UpdateFootsteps(clock);                       // 0x003678f8
    const uint32_t ecResult = VfEC();             // vt+0xec
    m_ui32HeroFlags354 = (m_ui32HeroFlags354 & 0xfeffffffu) | ((ecResult << 24) & 0xff000000u);
    m_ui32HeroFlags358 &= 0xfffe3f9fu;
    m_ui32HeroFlags35C &= 0xffffbfffu;
    uint32_t keep13 = 0;
    if ((m_ui32HeroFlags358 & 2u) == 0) keep13 = ((m_ui32HeroFlags354 >> 13) & 1u) << 13;
    m_ui32HeroFlags354 = ((m_ui32HeroFlags354 & 0xffffdfffu) | keep13) & 0xffffefffu;
    m_ui32HeroFlags35C &= 0xfeffffffu;
    uint32_t bit4 = 0;
    if ((m_ui32HeroFlags360 & 0x10u) != 0) bit4 = ((m_ui32HeroFlags360 >> 2) & 1u) << 4;
    m_ui32HeroFlags360 = ((m_ui32HeroFlags360 & 0xffffffefu) | bit4) & 0xfffff7bfu;
    m_ui32HeroFlags35C &= 0xffffffefu;
    m_ui32HeroFlags364 &= 0xc5b3de9fu;
    if (static_cast<int32_t>(m_gcCurDatasInOut.m_eContactStatus) <= 1) {
        // The ground's surface flags: +0x358 bit 23 (and up) the game manager's vt+0x138 0x4f88f8, bits 24 / 25 / 26 /
        // 27 the ground's property bits 1 / 0 / 2 / 3, +0x360 bit 13 its bit 4.
        const ICollisionMesh* ground = static_cast<const ICollisionMesh*>(m_gcCurDatasInOut.m_pGround);
        const uint32_t kind = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->GetGroundSurfaceBit(ground);
        uint32_t flags = (m_ui32HeroFlags358 & ~0x800000u) | ((kind << 23) & 0x7f800000u);
        const uint32_t props = ground->m_ui16PropertiesFlags;
        flags = (flags & ~0x1000000u) | (((props >> 1) & 1u) << 24);
        flags = (flags & ~0x2000000u) | ((props & 1u) << 25);
        flags = (flags & ~0x4000000u) | (((props >> 2) & 1u) << 26);
        flags = (flags & ~0x8000000u) | (((props >> 3) & 1u) << 27);
        m_ui32HeroFlags358 = flags;
        m_ui32HeroFlags360 = (m_ui32HeroFlags360 & ~0x2000u) | (((props >> 4) & 1u) << 13);
    } else {
        m_ui32HeroFlags358 &= 0xf07fffffu;
        m_ui32HeroFlags360 &= 0xffffdfffu;
    }
    const CVector3& zero = kHeroZeroVector;  // TOC +0x2b2c
    m_unk5e4 = zero.x;
    m_unk5e8 = zero.y;
    m_unk5ec = zero.z;
    m_unk5f0 = zero.x;
    m_unk5f4 = zero.y;
    m_unk5f8 = zero.z;
    m_unk5fc = zero.x;
    m_unk600 = zero.y;
    m_unk604 = zero.z;
    m_unk9c = 0;
    m_unk591 = m_unk590;
    m_unk98 = 0;
}

// 0x00345080 CKHkS08Hero_vf144 (vt+0x144): the hero's logical input 6 (the group's vt+0x118) is down (step 4
// INPUT: UpdateHeroInputDerivedState copies it into +0x364 bit 20).
uint8_t CKHkS08Hero::Vf144() {
    const uint8_t action = static_cast<IKGrpHero*>(m_pGrpHero)->GetInputAction(6);
    return m_aui8JoyInputs[action] != 0 ? 1 : 0;  // neg / rldicl 1,63: the sign of -byte
}

// 0x00345b60 CKHkS08HeroBase_LevelReset_maybe (RecursiveRegistration)
void IKHkHero::RecursiveRegistration(int32_t type) {
    IKHook::RecursiveRegistration(type);  // 0x00019ab8
    if (static_cast<uint32_t>(type - 4) <= 3u) return;
    g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);  // engine +0x50, vt+0x24
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    const uint8_t hotSpots = group->GetNbHotSpots(m_ui8Hero);  // vt+0xf8
    for (uint32_t i = 0; i != hotSpots; ++i) m_apHotSpots[i]->RecursiveRegistration(type);
    const uint8_t objects = group->GetNbObjects(m_ui8Hero);  // vt+0x104
    for (uint32_t i = 0; i != objects; ++i) m_apObjects[i]->RecursiveRegistration(type);
    m_pAnimDico->RecursiveRegistration(type);           // +0x13c
    m_pSoundDico->RecursiveRegistration(type);          // +0x168
    m_pShadowCpnt->RecursiveRegistration(type);         // +0x60
    m_pWaterWaveFxData->RecursiveRegistration(type);    // +0x84
    m_pWaterSplashFxData->RecursiveRegistration(type);  // +0x8c
}

// 0x003462c0 IKHkHero_GetInfo, with its accessors 0x345e40 IKHkHero_GetNotFlag354Bit0Property_maybe, 0x346388
// IKHkHero_GetDistanceToPartnerProperty_maybe and 0x345e20 IKHkHero_IsSelfControlledProperty_maybe.
int32_t IKHkHero::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
    case 0:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) { return ~static_cast<IKHkHero*>(o)->m_ui32HeroFlags354 & 1u; }, 0);
    case 1:
        // The controlling dragon (the group's hero +0x25) less this one (+0x54c), its length (Math_Sqrtf 0x10690).
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            IKHkHero* self = static_cast<IKHkHero*>(o);
            const IKHkHero* partner =
                static_cast<const IKHkHero*>(static_cast<IKGrpHero*>(self->m_pGrpHero)->m_apHeros[self->m_ui8TrackedLeader]);
            const float dy = partner->m_unk550 - self->m_unk550;
            const float dx = partner->m_unk54c - self->m_unk54c;
            const float dz = partner->m_unk554 - self->m_unk554;
            const float squared = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
            return FloatBits(static_cast<float>(std::sqrt(static_cast<double>(squared))));
        }, 2);
    case 2:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            const IKHkHero* self = static_cast<const IKHkHero*>(o);
            return self->m_ui8Hero == self->m_ui8TrackedLeader ? 1u : 0u;
        }, 0);
    default:
        return 1;
    }
}

// 0x00345140 IKHkHero_FreeBuffers_maybe
void IKHkHero::FreeBuffers() {
    Mem_FreeAligned16(m_apHotSpots);
    Mem_FreeAligned16(m_apParticles);
    Mem_FreeAligned16(m_apBoundings);
    Mem_FreeAligned16(m_apObjects);
    Mem_FreeAligned16(m_apTrails);
    Mem_FreeAligned16(m_unka0);
    Mem_FreeAligned16(m_unka4);
    Mem_FreeAligned16(m_unkc0);
    Mem_FreeAligned16(m_unkc4);
    Mem_FreeAligned16(m_apUnk134);
    if (m_pAnimBlendSlots != nullptr) delete[] m_pAnimBlendSlots;  // the elements' destructors (vt+0x0), OperatorDeleteArray
    Mem_FreeAligned16(m_unk140);
    Mem_FreeAligned16(m_unk144);
    Mem_FreeAligned16(m_asSpeedModes);
    Mem_FreeAligned16(m_asJumps);
    Mem_FreeAligned16(m_afBoundingsRadius);
    Mem_FreeAligned16(m_aui8JoyInputs);
    Mem_FreeAligned16(m_unk520);
    Mem_FreeAligned16(m_unk524);
}
