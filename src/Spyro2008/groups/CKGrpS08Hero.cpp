// CKGrpS08Hero.cpp - reconstructed original translation unit 0x2c8f78-0x2d4be0 (GAME_TOC1, main_toc1), 135 functions, 111 live.
// Primary class: CKGrpS08Hero  key 0x984  category Group  size 0xafc  vtable 0xb22b00
// Other owners: IKGrpHero (5), GetHeroByDragonIndex (1), GetControlledHeroArray (1), GetCompanionHeroArray (1), GetControlledHeroCount (1), GetCompanionHeroCount (1), GetMaxPlayers (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2c8f78  CKGrpS08Hero_ReinitRuntime
//   [x] 0x2c8fb0  IKGrpHero_Load
//   [ ] 0x2c9838  IKGrpHero_Save
//   [ ] 0x2ca038  CKGrpS08Hero_GetHeroCount
//   [ ] 0x2ca080  GetHeroByDragonIndex
//   [ ] 0x2ca098  CKGrpS08Hero_vfF8_Thunk_maybe  [dead]
//   [ ] 0x2ca0e0  GetControlledHeroArray
//   [ ] 0x2ca0e8  GetCompanionHeroArray
//   [x] 0x2ca0f0  CKGrpS08Hero_GetHeroList  (IKGrpHero::m_apHeroesCopy, read directly)
//   [ ] 0x2ca0f8  CKGrpS08Hero_GetFocusedHero
//   [ ] 0x2ca128  CKGrpS08Hero_GetFocusedHeroNode_maybe
//   [ ] 0x2ca158  CKGrpS08Hero_GetHeroNodeByIndex_maybe  [dead]
//   [ ] 0x2ca170  KStub_Return2_2ca170  [dead]
//   [ ] 0x2ca178  KStub_Return17_2ca178  [dead]
//   [ ] 0x2ca180  FUN_002ca180  [dead]
//   [ ] 0x2ca188  CKGrpS08Hero_IsDragonSwitchPending_maybe
//   [ ] 0x2ca198  CKGrpS08Hero_IsDragonSwitchLockedOrBit2_maybe  [dead]
//   [ ] 0x2ca1b8  CKGrpS08Hero_SetDragonSwitchLocked_maybe
//   [ ] 0x2ca200  CKGrpS08Hero_TestFlagBits12_13_14_maybe  [dead]
//   [ ] 0x2ca238  CKGrpS08Hero_SetFlagBit13_maybe  [dead]
//   [ ] 0x2ca258  CKGrpS08Hero_IsInputBlocked_maybe
//   [ ] 0x2ca268  CKGrpS08Hero_SetInputBlocked_maybe
//   [ ] 0x2ca288  GetControlledHeroCount
//   [ ] 0x2ca290  GetCompanionHeroCount
//   [ ] 0x2ca298  CKGrpS08Hero_vf16C_Thunk_maybe
//   [ ] 0x2ca2e0  CKGrpS08Hero_GetByte50Property_maybe
//   [ ] 0x2ca2e8  CKGrpS08Hero_vf188_Thunk_maybe  [dead]
//   [ ] 0x2ca330  FUN_002ca330  [dead]
//   [ ] 0x2ca358  CKGrpS08Hero_CountHeroesMatchingVf188_maybe  [dead]
//   [ ] 0x2ca438  FUN_002ca438  [dead]
//   [ ] 0x2ca500  FUN_002ca500  [dead]
//   [x] 0x2ca598  CKGrpS08Hero_vf184_Thunk_maybe
//   [ ] 0x2ca5d8  FUN_002ca5d8  [dead]
//   [ ] 0x2ca600  FUN_002ca600  [dead]
//   [ ] 0x2ca718  CKGrpS08Hero_CanSwitchToDragon_Thunk_maybe  [dead]
//   [ ] 0x2ca740  CKGrpS08Hero_RequestDragonSelection_Thunk_maybe
//   [ ] 0x2ca770  CKGrpS08Hero_FindNextSelectableHeroWrapper_maybe
//   [ ] 0x2ca7a0  CKGrpS08Hero_GetPlayerToCompanionDistance_maybe
//   [ ] 0x2ca8b0  CKGrpS08Hero_GetGameManagerVf270OfFirstHeroProperty_maybe
//   [ ] 0x2ca928  CKGrpS08Hero_GetFirstControlledDragonIndex
//   [ ] 0x2ca970  KStub_Nop_2ca970
//   [ ] 0x2ca978  IKGrpHero_vf184
//   [x] 0x2cabd8  GetMaxPlayers_maybe
//   [ ] 0x2cac28  CKGrpS08Hero_QueueTriggerSignalsAtB0_maybe  [dead]
//   [ ] 0x2cac60  CKGrpS08Hero_QueueTriggerSignalsAtA8_maybe  [dead]
//   [ ] 0x2cac98  CKGrpS08Hero_QueueTriggerSignalsAtA0_maybe  [dead]
//   [ ] 0x2cacd0  FUN_002cacd0  [dead]
//   [ ] 0x2cada0  FUN_002cada0  [dead]
//   [x] 0x2caee8  CompareHeroesByPlayerIndex_maybe
//   [x] 0x2caf58  CKGrpS08Hero_FindCatchUpPoint_maybe
//   [ ] 0x2cb0a8  CKGrpS08Hero_FindNextSelectableHero_maybe
//   [ ] 0x2cb280  CKGrpS08Hero_UpdateHeroSpeechAnims_maybe
//   [x] 0x2cb4c0  CKGrpS08Hero_IsDragonSelectable_maybe
//   [x] 0x2cb528  RebuildControlledAndCompanionHeroArrays
//   [x] 0x2cb6f0  CKGrpS08Hero_AssignFollowSlot_maybe
//   [x] 0x2cb9c0  CKGrpS08Hero_CanSwitchToDragon_maybe
//   [x] 0x2cbb08  CKGrpS08Hero_RequestDragonSelection_maybe
//   [x] 0x2cbf10  CKGrpS08Hero_UpdatePartnerInteraction_maybe
//   [x] 0x2cc3f0  SetFocusedDragon
//   [ ] 0x2cc7c0  ApplyRequestedDragonSelection
//   [x] 0x2ccbe0  CKGrpS08Hero_UpdateCatchUpPoints_maybe
//   [ ] 0x2cde60  IKGrpHero_HandleCommandMessage_maybe
//   [ ] 0x2ce1f0  IKGrpHero_HandleMessage
//   [x] 0x2ce2b8  CKGrpS08Hero_Delete
//   [ ] 0x2ce308  CKGrpS08Hero_vfB8
//   [ ] 0x2ce310  CKGrpS08Hero_vfEC
//   [ ] 0x2ce318  GetCKGrpS08HeroCount
//   [ ] 0x2ce320  CKGrpS08Hero_vfF8
//   [ ] 0x2ce330  CKGrpS08Hero_vfFC
//   [x] 0x2ce340  CKGrpS08Hero_vf100
//   [ ] 0x2ce350  CKGrpS08Hero_vf104
//   [ ] 0x2ce360  CKGrpS08Hero_vf108
//   [ ] 0x2ce370  CKGrpS08Hero_GetNbHeroInputBytes_maybe
//   [ ] 0x2ce378  CKGrpS08Hero_vf110
//   [ ] 0x2ce380  CKGrpS08Hero_vf114
//   [ ] 0x2ce388  CKGrpS08Hero_vf118
//   [x] 0x2ce398  CKGrpS08Hero_vf11C
//   [ ] 0x2ce3a8  CKGrpS08Hero_vf120
//   [ ] 0x2ce3b8  CKGrpS08Hero_vf124
//   [ ] 0x2ce3c8  CKGrpS08Hero_vf128
//   [ ] 0x2ce3d0  CKGrpS08Hero_vf12C
//   [ ] 0x2ce3d8  CKGrpS08Hero_vf130
//   [ ] 0x2ce3e0  CKGrpS08Hero_vf134
//   [ ] 0x2ce3f0  CKGrpS08Hero_vf138
//   [ ] 0x2ce3f8  CKGrpS08Hero_vf13C
//   [ ] 0x2ce400  CKGrpS08Hero_vf140
//   [ ] 0x2ce408  CKGrpS08Hero_vf144
//   [ ] 0x2ce410  CKGrpS08Hero_vf148
//   [ ] 0x2ce418  CKGrpS08Hero_vf14C
//   [ ] 0x2ce420  CKGrpS08Hero_vf150
//   [ ] 0x2ce428  CKGrpS08Hero_vf154
//   [ ] 0x2ce448  CKGrpS08Hero_GetMovementEventSound_maybe
//   [ ] 0x2ce460  CKGrpS08Hero_vf15C
//   [ ] 0x2ce468  CKGrpS08Hero_GetSurfaceSoundEntry_maybe
//   [x] 0x2ce480  CKGrpS08Hero_vf164
//   [ ] 0x2ce498  CKGrpS08Hero_vf168
//   [ ] 0x2ce4b0  CKGrpS08Hero_vf18C
//   [ ] 0x2ce4b8  CKGrpS08Hero_vf16C
//   [ ] 0x2ce4d8  CKGrpS08Hero_vf170
//   [ ] 0x2ce4f0  CKGrpS08Hero_vf174
//   [ ] 0x2ce4f8  CKGrpS08Hero_vf178
//   [ ] 0x2ce518  CKGrpS08Hero_GetMaxPartnerDistance_maybe
//   [x] 0x2ce520  CKGrpS08Hero_GetTetherSpringRadius_maybe
//   [ ] 0x2ce540  CKGrpS08Hero_GetTetherDampingRadius_maybe
//   [ ] 0x2ce560  CKGrpS08Hero_GetTetherSpringStiffness_maybe
//   [ ] 0x2ce580  CKGrpS08Hero_GetTetherDampingCoeff_maybe
//   [ ] 0x2ce5a0  CKGrpS08Hero_SectorLoaded
//   [ ] 0x2ce5c8  CKGrpS08Hero_UpdateSwitchPressFeedback_maybe
//   [x] 0x2ce888  CKGrpS08Hero_UpdateFlightAltitudeGap_maybe
//   [x] 0x2ceb30  CKGrpS08Hero_ApplyTetherPullToHero_maybe
//   [ ] 0x2ced38  FUN_002ced38  [dead]
//   [ ] 0x2cee70  CKGrpS08Hero_Stop
//   [ ] 0x2cee98  CKGrpS08Hero_Resume
//   [ ] 0x2ceec0  CKGrpS08Hero_Pause
//   [x] 0x2ceee8  CKGrpS08Hero_Start
//   [ ] 0x2cef40  CKGrpS08Hero_RecursiveRegistration
//   [x] 0x2cf110  CKGrpS08Hero_DeleteArray
//   [x] 0x2cf1b0  CKGrpS08Hero_Create
//   [ ] 0x2cf238  RegisterCKGrpS08HeroClass
//   [ ] 0x2cf2c0  _GLOBAL__D_2cf2c0
//   [ ] 0x2cf2d0  _GLOBAL__I_2cf2d0
//   [x] 0x2cf2e0  CKGrpS08Hero_PostLoad
//   [ ] 0x2cf410  CKGrpS08Hero_Destroy
//   [ ] 0x2cf458  CKGrpS08Hero_ResolveHeroPairDisplacement_maybe  [dead]
//   [x] 0x2cf7c8  UpdateCKGrpS08Hero
//   [ ] 0x2cf940  CKGrpS08Hero_GetInfo
//   [ ] 0x2cfb68  CKGrpS08Hero_MessageProc
//   [x] 0x2cff20  CreateCKGrpS08HeroArray
//   [x] 0x2d0018  CKGrpS08Hero_ScoreCatchUpPointsByCompanionDistance_maybe
//   [x] 0x2d01d8  CKGrpS08Hero_UpdateHeroPairGeometry_maybe
//   [x] 0x2d0a08  CKGrpS08Hero_Restart
//   [x] 0x2d0b60  CKGrpS08Hero_Load
//   [ ] 0x2d2d68  CKGrpS08Hero_Save
//   [ ] 0x2d4b98  FUN_002d4b98  [dead]
//   [ ] 0x2d4bc0  CKGrpS08Hero_GetFocusedHeroCamera_maybe
//
//   [ ] 0x9bd130  CKGrpS08Hero_vfF0  [inline]
//   [x] 0x9bd208  CKGrpS08Hero_CompareCatchUpPoints_maybe  [inline]
//   [ ] 0x9bd280  CKGrpS08Hero_IsKindOfClass  [inline]
//   [ ] 0x9bd2e0  CKGrpS08Hero_GetClassType  [inline]
//   [ ] 0x9bd2e8  CKGrpS08Hero_GetClassID  [inline]
//   [ ] 0x9bd2f0  CKGrpS08Hero_vfCC  [inline]
//   [ ] 0x9bd2f8  CKGrpS08Hero_GetTriggerPropB  [inline]
//   [ ] 0x9bd308  CKGrpS08Hero_GetTriggerPropF  [inline]
//   [ ] 0x9bd318  CKGrpS08Hero_GetTriggerProp7  [inline]
//   [ ] 0x9bd320  CKGrpS08Hero_GetTriggerProp13  [inline]
//   [ ] 0x9bd330  CKGrpS08Hero_IsFocusedHeroFree  [inline]
//   [ ] 0x9bd378  CKGrpS08Hero_IsAverageManaAtLeastHalf_maybe  [inline]
//   [ ] 0x9bd4c0  CKGrpS08Hero_IsFuryGaugeFull_maybe  [inline]
//   [ ] 0x9bd4f8  CKGrpS08Hero_Destructor  [inline]
//   [ ] 0x9bd560  CKGrpS08Hero_DeletingDestructor  [inline]
#include "Spyro2008/groups/CKGrpS08Hero.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

namespace {
// One of IKGrpHero_Load's arrays: count references in a new block (count * 4 bytes on the PS3).
IKSerializable** LoadHeroRefArray(IKFile* file, uint8_t count) {
    IKSerializable** array =
        static_cast<IKSerializable**>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, array, count);
    return array;
}
}  // namespace

// 0x002c8fb0 IKGrpHero_Load
int32_t IKGrpHero::Load(IKFile* file, int32_t type) {
    GroupBasicLoad(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadRaw(file, &m_ui8NumberOfHeros, 1);
    uint8_t count = 0;
    ReadRaw(file, &count, 1);
    m_apHeros = LoadHeroRefArray(file, count);
    IKFile_ReadRef(file, &m_pUnk40);
    m_apUnk44 = LoadHeroRefArray(file, count);
    m_apUnk48 = LoadHeroRefArray(file, count);
    m_apUnk4c = LoadHeroRefArray(file, count);
    for (CTriggerStarter& trigger : m_aTriggers) trigger.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_pUnk58);
    for (uint32_t& word : m_sProperties.m_aui32Words) ReadU32LE(file, &word);
    for (uint16_t& value : m_sProperties.m_aui16Values) ReadU16LE(file, &value);
    ReadRaw(file, &m_sProperties.m_ui8Value, 1);
    return 1;
}

// 0x002d0b60 CKGrpS08Hero_Load
int32_t CKGrpS08Hero::Load(IKFile* file, int32_t type) {
    IKGrpHero::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadF32LE(file, &m_unk10c);
    ReadF32LE(file, &m_unk110);
    ReadF32LE(file, &m_unk114);
    ReadF32LE(file, &m_unk118);
    ReadF32LE(file, &m_unk174);
    ReadF32LE(file, &m_unk178);
    ReadF32LE(file, &m_unk11c);
    ReadF32LE(file, &m_unk120);
    ReadF32LE(file, &m_unk124);
    ReadF32LE(file, &m_unk128);
    ReadF32LE(file, &m_unk12c);
    ReadF32LE(file, &m_unk130);
    ReadF32LE(file, &m_unk134);
    ReadF32LE(file, &m_unk138);
    ReadF32LE(file, &m_unk13c);
    ReadF32LE(file, &m_unk140);
    ReadF32LE(file, &m_unk144);
    ReadF32LE(file, &m_unk194);
    ReadF32LE(file, &m_unk198);
    ReadF32LE(file, &m_unk19c);
    ReadF32LE(file, &m_unk1a8);
    ReadF32LE(file, &m_unk1ac);
    ReadF32LE(file, &m_unk1b0);
    ReadF32LE(file, &m_unk1b4);
    IKFile_ReadRef(file, &m_pUnk2cc);
    ReadF32LE(file, &m_unk148);
    ReadF32LE(file, &m_unk1a0);
    ReadF32LE(file, &m_unk1a4);
    ReadF32LE(file, &m_unk14c);
    ReadF32LE(file, &m_unk150);
    ReadF32LE(file, &m_unk154);
    ReadF32LE(file, &m_unk158);
    ReadF32LE(file, &m_unk1d8);
    ReadF32LE(file, &m_unk1dc);
    ReadF32LE(file, &m_unk1ec);
    ReadU32LE(file, &m_unk1f0);
    ReadF32LE(file, &m_unk1f4);
    ReadF32LE(file, &m_unk1f8);
    ReadRaw(file, &m_unk1fc, 1);
    ReadF32LE(file, &m_unk1e0);
    ReadF32LE(file, &m_unk1e4);
    ReadRaw(file, &m_unk1fd, 1);
    ReadF32LE(file, &m_unk1e8);
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
    ReadF32LE(file, &m_unk258);
    ReadF32LE(file, &m_unk25c);
    ReadF32LE(file, &m_unk260);
    ReadF32LE(file, &m_unk264);
    m_tsUnkab0.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_pUnkad0);
    ReadS32LE(file, &m_unk268);
    ReadS32LE(file, &m_unk26c);
    ReadF32LE(file, &m_unk270);
    ReadF32LE(file, &m_unk274);
    ReadF32LE(file, &m_unk230);
    ReadF32LE(file, &m_unk234);
    ReadF32LE(file, &m_unk238);
    ReadF32LE(file, &m_unk23c);
    ReadU32LE(file, &m_unk240);
    ReadF32LE(file, &m_unk244);
    ReadF32LE(file, &m_unk248);
    ReadF32LE(file, &m_unk24c);
    ReadF32LE(file, &m_unk250);
    ReadF32LE(file, &m_unk254);
    ReadF32LE(file, &m_unk278);
    ReadF32LE(file, &m_unk27c);
    ReadU32LE(file, &m_unk280);
    ReadF32LE(file, &m_unk284);
    ReadU32LE(file, &m_unk288);
    ReadF32LE(file, &m_unk28c);
    ReadF32LE(file, &m_unk290);
    ReadF32LE(file, &m_unk294);
    ReadU32LE(file, &m_unk298);
    ReadU32LE(file, &m_unk29c);
    ReadU32LE(file, &m_unk2a0);
    ReadF32LE(file, &m_unk2a4);
    ReadU32LE(file, &m_unk2a8);
    ReadF32LE(file, &m_unk2ac);
    ReadU32LE(file, &m_unk2b0);
    ReadF32LE(file, &m_unk2b4);
    ReadF32LE(file, &m_unk2b8);
    ReadF32LE(file, &m_unk2bc);
    ReadU32LE(file, &m_unk2c0);
    ReadF32LE(file, &m_unk2c4);
    IKFile_ReadRef(file, &m_pUnkabc);
    ReadF32LE(file, &m_unk17c);
    ReadF32LE(file, &m_unk180);
    ReadF32LE(file, &m_unk184);
    ReadF32LE(file, &m_unk18c);
    ReadF32LE(file, &m_unk188);
    m_tsUnk338.Load(file, K_LEVEL_PLATEFORMS);
    m_tsUnkac0.Load(file, K_LEVEL_PLATEFORMS);
    ReadF32LE(file, &m_unk200);
    ReadF32LE(file, &m_unk1b8);
    IKFile_ReadRef(file, &m_pUnk348);
    IKFile_ReadRef(file, &m_pUnk34c);
    ReadF32LE(file, &m_unk1bc);
    ReadF32LE(file, &m_unk1c0);
    ReadF32LE(file, &m_unk1c4);
    ReadF32LE(file, &m_unk1c8);
    ReadF32LE(file, &m_unk1cc);
    ReadF32LE(file, &m_unk1d0);
    ReadS32LE(file, &m_unk1d4);
    IKFile_ReadRef(file, &m_pUnk354);
    m_tsUnk340.Load(file, K_LEVEL_PLATEFORMS);
    IKFile_ReadRef(file, &m_pUnk358);
    ReadF32LE(file, &m_unk15c);
    ReadF32LE(file, &m_unk160);
    ReadF32LE(file, &m_unk164);
    ReadF32LE(file, &m_unk168);
    ReadF32LE(file, &m_unk16c);
    ReadF32LE(file, &m_unk170);
    IKFile_ReadRef(file, &m_pUnk360);
    ReadF32LE(file, &m_unk190);
    return 1;
}

#include "Spyro2008/hooks/IKHkHero.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/fx/CKHDRFxData.h"
#include "k2000/misc/Engine.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/core/Stub.h"
#include "k2000/logic/ai/CKDetectedMovable.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/services/CKSrvDetect.h"
#include "k2000/services/CKSrvDynamic.h"
#include "k2000/system/IKTime.h"

#include <cmath>
#include <cstring>

#include "crt/Ps3Qsort.h"
#include "crt/ppc_ops.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/logic/CKPFGraphNode.h"
#include "k2000/logic/physics/CGround.h"
#include "k2000/math/Math.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/NavGrid.h"
#include "k2000/system/CTimeManager.h"

namespace {
// 0x002caee8 CompareHeroesByPlayerIndex_maybe: the qsort comparator of the controlled heroes (the PS3 passes
// pointers to the array slots). 0x362ac8 CKHkS08Hero_GetPlayerIndexIfControlled_maybe returns the hero's
// byte +0x26 (sign-extended, compared as an unsigned byte), or 0xff when it is not the controlled one.
uint8_t PlayerIndexIfControlled(const IKHkHero* hero) {
    if (hero->m_ui8Hero != hero->m_ui8TrackedLeader) return 0xff;
    return static_cast<uint8_t>(static_cast<int8_t>(hero->m_ui8Leader));
}

int CompareHeroesByPlayerIndex(IKSerializable* const* a, IKSerializable* const* b) {
    const uint8_t first = PlayerIndexIfControlled(static_cast<const IKHkHero*>(*a));
    const uint8_t second = PlayerIndexIfControlled(static_cast<const IKHkHero*>(*b));
    if (first > second) return 1;
    if (first < second) return -1;
    return 0;
}
}  // namespace

// 0x002cabd8 GetMaxPlayers_maybe: the game manager's vt+0x150.
uint8_t CKGrpS08Hero::GetMaxPlayers() {
    return g_pEngine->m_gameManager->GetMaxPlayers();
}

// 0x002c8f78 CKGrpS08Hero_ReinitRuntime
void CKGrpS08Hero::ReinitRuntime() {
    ResetRuntimeState();
    RebuildControlledAndCompanionHeroArrays();
}

// 0x002cb528 RebuildControlledAndCompanionHeroArrays: sorts the heroes into the controlled ones (the hero is
// its own control owner) and the companions.
void CKGrpS08Hero::RebuildControlledAndCompanionHeroArrays() {
    IKSerializable** controlledCursor = m_apControlledHeroes;
    IKSerializable** companionCursor = m_apCompanionHeroes;
    IKSerializable** allHeroes = m_apHeros;
    const uint32_t heroes = GetHeroCount();  // vt+0xf4
    const uint32_t maxPlayers = GetMaxPlayers();
    m_ui8ControlledHeroCount = 0;
    m_ui8CompanionHeroCount = 0;
    for (uint32_t i = 0; i < heroes; ++i) {
        IKSerializable* hero = allHeroes[i];
        const IKHkHero* heroBase = static_cast<const IKHkHero*>(hero);
        if (heroBase->m_ui8Hero == heroBase->m_ui8TrackedLeader) {
            // BUG(original): the count goes up even when the array is full (it is not capped).
            if (m_ui8ControlledHeroCount < maxPlayers) *controlledCursor++ = hero;
            m_ui8ControlledHeroCount = static_cast<uint8_t>(m_ui8ControlledHeroCount + 1);
        } else {
            if (m_ui8CompanionHeroCount < heroes) *companionCursor++ = hero;
            m_ui8CompanionHeroCount = static_cast<uint8_t>(m_ui8CompanionHeroCount + 1);
        }
    }
    *controlledCursor = nullptr;
    *companionCursor = nullptr;
    const uint32_t sorted = maxPlayers > m_ui8ControlledHeroCount ? m_ui8ControlledHeroCount : maxPlayers;
    // libc qsort(m_apControlledHeroes, sorted, 4, CompareHeroesByPlayerIndex): at most two slots, so an
    // insertion sort gives the result.
    for (uint32_t i = 1; i < sorted; ++i) {
        IKSerializable* item = m_apControlledHeroes[i];
        uint32_t j = i;
        while (j > 0 && CompareHeroesByPlayerIndex(&m_apControlledHeroes[j - 1], &item) > 0) {
            m_apControlledHeroes[j] = m_apControlledHeroes[j - 1];
            --j;
        }
        m_apControlledHeroes[j] = item;
    }
    m_unkf8 = (m_unkf8 & ~0x200u) | 0x200u;
}

// 0x002ceee8 CKGrpS08Hero_Start
void CKGrpS08Hero::Start() {
    ResetSoundChannelFlags();
    Restart();  // vt+0x54
}

// 0x002d0a08 CKGrpS08Hero_Restart
void CKGrpS08Hero::Restart() {
    ReinitRuntime();
    m_unk31c = m_unk178;
    m_unk2c8 = 0;
    m_unk2d0 = 0;
    m_unk320 = 0;
    c22spyro::SrvDynamicSetEntryFlag(static_cast<CKSrvDynamic*>(g_pEngine->m_srvDynamic), this, 1);  // 0x23aff8
    m_unk37c = 0;
    m_vUnka94 = CVector3{0.0f, 0.0f, 0.0f};  // the zero vector 0xc50d64 (TOC 0x1c30)
    m_unkaa0[0] = 0;
    m_unkaa0[1] = 0;
    m_unkaa0[2] = 0;
    m_unka88 = 0;
    m_unk2c8 = (m_unk2c8 & 0xfffffffdu) | 2u;
    m_unkac8 = 0;
    CKHDRFxData* hdr = static_cast<CKHDRFxData*>(m_pUnk358);
    m_unk350 = 0;
    m_unk35c = 0;
    m_unkacc = 0xff;
    hdr->m_unk14 = static_cast<int32_t>((static_cast<uint32_t>(hdr->m_unk14) & 0xfffffffdu) | 2u);
    hdr->m_unk10 = hdr->m_unk0c;
    m_unk36c = -1.0f;  // TOC 0x1c34
    m_unk364 = -1.0f;
    m_unk374 = 0;
    m_unk320 = 1;
    m_unkfc = 0;
    m_unk108 = m_unk10c;
    m_unk100 = m_unk10c;
    m_unk104 = 20.0f;  // TOC 0x1c38
}

namespace {
// The hero state tables (PS3 function descriptors of the state handlers, mapped to native functions by the hero's
// side tables; see SHeroStateRow). The heroes copy and sort them in IKHkHero_InitRuntimeTables_maybe.
// 0x00c4b1e0 (hero state table A, 11 rows)
const SHeroStateRow kHeroStatesA[11] = {
    {{0x00ba29d0u, 0x0u}, {0x00ba29b8u, 0x0u}, 0x00000000u},
    {{0x00ba2a20u, 0x0u}, {0x00ba2a30u, 0x0u}, 0x05000000u},
    {{0x00ba2a90u, 0x0u}, {0x00ba2a48u, 0x0u}, 0x07000000u},
    {{0x00b9f0c8u, 0x0u}, {0x00ba29c0u, 0x0u}, 0x19000000u},
    {{0x00b9f078u, 0x0u}, {0x00ba29c8u, 0x0u}, 0x0f000000u},
    {{0x00b9f0d0u, 0x0u}, {0x00b9eff0u, 0x0u}, 0x08000000u},
    {{0x00b9f0f0u, 0x0u}, {0x00b9eff8u, 0x0u}, 0x09000000u},
    {{0x00b9f0e0u, 0x0u}, {0x00b9efe8u, 0x0u}, 0x0a000000u},
    {{0x00b9efb8u, 0x0u}, {0x00b9efe0u, 0x0u}, 0x14000000u},
    {{0x00b9f0e8u, 0x0u}, {0x00b9ef00u, 0x0u}, 0x65000000u},
    {{0x00b9f0b8u, 0x0u}, {0x00b9ef08u, 0x0u}, 0x64000000u},
};
// 0x00c4b3fc (table B, 13 rows)
const SHeroStateRow kHeroStatesB[13] = {
    {{0x00ba2110u, 0x0u}, {0x00ba2108u, 0x0u}, 0x00000000u},
    {{0x00b9e408u, 0x0u}, {0x00b9e368u, 0x0u}, 0x0a000000u},
    {{0x00b9e480u, 0x0u}, {0x00b9e3a0u, 0x0u}, 0x46000000u},
    {{0x00b9e460u, 0x0u}, {0x00b9e258u, 0x0u}, 0x5a000000u},
    {{0x00b9e400u, 0x0u}, {0x00b9e388u, 0x0u}, 0x0f000000u},
    {{0x00b9e390u, 0x0u}, {0x00b9e378u, 0x0u}, 0x1e000000u},
    {{0x00b9e3f8u, 0x0u}, {0x00b9e380u, 0x0u}, 0x28000000u},
    {{0x00b9d200u, 0x0u}, {0x00b9d020u, 0x0u}, 0x55000000u},
    {{0x00b9e478u, 0x0u}, {0x00b9e398u, 0x0u}, 0x50000000u},
    {{0x00b9e488u, 0x0u}, {0x00b9e370u, 0x0u}, 0x51000000u},
    {{0x00b9e4d0u, 0x0u}, {0x00b9e3e8u, 0x0u}, 0x63000000u},
    {{0x00b9e3f0u, 0x0u}, {0x00b9e260u, 0x0u}, 0x59000000u},
    {{0x00b9d068u, 0x0u}, {0x00b9d028u, 0x0u}, 0x5f000000u},
};
// 0x00c4b398 (table C, 5 rows)
const SHeroStateRow kHeroStatesC[5] = {
    {{0x00b9ba20u, 0x0u}, {0x00b9b8b8u, 0x0u}, 0x14000000u},
    {{0x00b9cbf0u, 0x0u}, {0x00b9c9b0u, 0x0u}, 0x0b000000u},
    {{0x00b9ca58u, 0x0u}, {0x00b9c9f8u, 0x0u}, 0x0a000000u},
    {{0x00b9c510u, 0x0u}, {0x00b9bea8u, 0x0u}, 0x01000000u},
    {{0x00b9bff0u, 0x0u}, {0x00b9beb0u, 0x0u}, 0x00000000u},
};
// 0x00c4b2bc (table D, 11 rows; its state id is the third byte of the last word)
const SHeroStateRow kHeroStatesD[11] = {
    {{0x00b9a348u, 0x0u}, {0x00b99fc0u, 0x0u}, 0x00001e00u},
    {{0x00b9a368u, 0x0u}, {0x00b99fb8u, 0x0u}, 0x00000a00u},
    {{0x00b9a340u, 0x0u}, {0x00b99fb0u, 0x0u}, 0x00001400u},
    {{0x00b9de18u, 0x0u}, {0x00b9dc08u, 0x0u}, 0x00002800u},
    {{0x00b9dd78u, 0x0u}, {0x00b9dc10u, 0x0u}, 0x00006400u},
    {{0x00b9dcc8u, 0x0u}, {0x00b9dc28u, 0x0u}, 0x00005f00u},
    {{0x00b9dd38u, 0x0u}, {0x00b9dcb8u, 0x0u}, 0x00005a00u},
    {{0x00b9ddd0u, 0x0u}, {0x00b9dd70u, 0x0u}, 0x00006900u},
    {{0x00b9dd30u, 0x0u}, {0x00b9dc38u, 0x0u}, 0x00006e00u},
    {{0x00b9ddd8u, 0x0u}, {0x00b9dc18u, 0x0u}, 0x00006a00u},
    {{0x00b9dcd0u, 0x0u}, {0x00b9dc20u, 0x0u}, 0x00006b00u},
};
// 0x00a70498: the number of animation blend slots of each hero.
const uint8_t kNbAnimBlendSlots[2] = {2, 2};
// 0x00c40968 / 0x00c40970 (through the pointers at 0x00b01018): the hot spot index of each body part, per hero.
// 0x00a704c0: the active inner blend layer of each hero.
const uint8_t kActiveInnerBlendSlot[2] = {0xff, 0xff};
const uint8_t kHotSpotIndices[2][8] = {{0, 1, 6, 7, 2, 3, 0, 0}, {0, 1, 6, 7, 2, 3, 0, 0}};
}  // namespace

// 0x002ce3c8 CKGrpS08Hero_vf128
const SHeroStateRow* CKGrpS08Hero::GetHeroStatesC() { return kHeroStatesC; }
// 0x002ce3f8 CKGrpS08Hero_vf13C
const SHeroStateRow* CKGrpS08Hero::GetHeroStatesD() { return kHeroStatesD; }
// 0x002ce408 CKGrpS08Hero_vf144
const SHeroStateRow* CKGrpS08Hero::GetHeroStatesA() { return kHeroStatesA; }
// 0x002ce418 CKGrpS08Hero_vf14C
const SHeroStateRow* CKGrpS08Hero::GetHeroStatesB() { return kHeroStatesB; }
// 0x002ce3e0 CKGrpS08Hero_vf134
// BUG(original): no bound check on the hero index (the heroes are 0 and 1).
uint8_t CKGrpS08Hero::GetNbAnimBlendSlots(uint8_t hero) { return kNbAnimBlendSlots[hero]; }

// 0x002ce4b8 CKGrpS08Hero_vf16C
// BUG(original): no bound check on the hero index or the part (the heroes are 0 and 1).
uint8_t CKGrpS08Hero::GetHotSpotIndex(uint8_t hero, uint8_t part) { return kHotSpotIndices[hero][part]; }

// 0x002ce398 CKGrpS08Hero_GetNbSpeedModes_maybe (vt+0x11c): the byte of table 0x00a70480 (TOC +0x1bec + 0x38) at the
// hero's index. BUG(original): no bound check (the heroes are 0 and 1).
uint8_t CKGrpS08Hero::GetNbSpeedModesOf(uint8_t hero) {
    static const uint8_t kNbSpeedModes[2] = {1, 1};
    return kNbSpeedModes[hero];
}

// 0x002ce480 CKGrpS08Hero_vf164: the hero's speed-scaled volume index (table 0x00a704b0, signed byte).
// BUG(original): no bound check (the heroes are 0 and 1).
uint8_t CKGrpS08Hero::GetSpeedVolumeIndexOf(uint8_t hero) {
    static const uint8_t kSpeedVolume[2] = {0, 0};
    return kSpeedVolume[hero];
}

// 0x002ce4d8 CKGrpS08Hero_vf170
// BUG(original): no bound check on the hero index (the heroes are 0 and 1).
uint8_t CKGrpS08Hero::GetActiveInnerBlendSlot(uint8_t hero) { return kActiveInnerBlendSlot[hero]; }

namespace {
// The detected-movable lists of the detection service (CKSrvDetect +0x0c / +0x10) asked to follow (Activate) or to stop
// refreshing (Disable) the node `movable`; SetFocusedDragon's inlined loops.
void ActivateInDetectors(CKSrvDetect* detect, IKSerializable* movable) {
    for (uint32_t i = 0; i < detect->m_ui32NbDetectedMovable; ++i) {
        static_cast<CKDetectedMovable*>(detect->m_apDetectedMovable[i])->ActivateDetectableNode(movable);  // 0x001ab170
    }
}
void DisableInDetectors(CKSrvDetect* detect, IKSerializable* movable) {
    for (uint32_t i = 0; i < detect->m_ui32NbDetectedMovable; ++i) {
        static_cast<CKDetectedMovable*>(detect->m_apDetectedMovable[i])->DisablePositionRefreshFor(movable);  // 0x001ab120
    }
}
}  // namespace

// 0x002cc3f0 SetFocusedDragon: `hero` (a player's hero; null: the first controlled one) becomes the focused dragon
// (+0x66, and the game manager's player +0x4a3) when forced, when none is focused or when the hero was not given; the
// detectors then follow the focused hero's detectable nodes (+0x44, +0x48) and the player heroes' (+0x48, +0x4c) and
// stop refreshing the others.
void CKGrpS08Hero::SetFocusedDragon(IKSerializable* heroObject, uint8_t force) {
    CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(heroObject);
    const bool none = hero == nullptr;
    if (none) {
        hero = static_cast<CKHkS08Hero*>(m_apControlledHeroes[0]);
    } else if (hero->m_ui8Hero != hero->m_ui8TrackedLeader) {
        return;
    }
    CKSrvDetect* detect = static_cast<CKSrvDetect*>(g_pEngine->m_srvDetect);
    const uint8_t index = hero->m_ui8Hero;
    const uint8_t count = GetHeroCount();  // vt+0xf4
    if (force != 0 || m_unk66 == 0xff || none) {
        m_unk66 = index;
        const CKHkS08Hero* focused = static_cast<const CKHkS08Hero*>(m_apHeros[static_cast<int8_t>(index)]);
        static_cast<CKS08GameManager*>(g_pEngine->m_gameManager)->m_unk4A3 = focused->m_ui8Leader;
    }
    if (count == 0) return;
    for (uint32_t i = 0; i < count; ++i) {
        const bool focusedHero = static_cast<int32_t>(static_cast<int8_t>(m_unk66)) == static_cast<int32_t>(i);
        if (focusedHero) {
            ActivateInDetectors(detect, m_apUnk44[i]);
        } else {
            DisableInDetectors(detect, m_apUnk44[i]);
        }
        const CKHkS08Hero* other = static_cast<const CKHkS08Hero*>(m_apHeros[i]);
        if (static_cast<int32_t>(static_cast<int8_t>(m_unk66)) == static_cast<int32_t>(i) ||
            other->m_ui8Hero != other->m_ui8TrackedLeader) {
            DisableInDetectors(detect, m_apUnk48[i]);
        } else {
            ActivateInDetectors(detect, m_apUnk48[i]);
        }
    }
    for (uint32_t i = 0; i < count; ++i) {
        const CKHkS08Hero* other = static_cast<const CKHkS08Hero*>(m_apHeros[i]);
        if (other->m_ui8Hero == other->m_ui8TrackedLeader) {
            ActivateInDetectors(detect, m_apUnk4c[i]);
        } else {
            DisableInDetectors(detect, m_apUnk4c[i]);
        }
    }
}

// 0x002cf7c8 UpdateCKGrpS08Hero (vt+0x7c): the hero group's frame: the switch feedback, the dynamic service's flag,
// the co-op focus, IKGrpHero_Update (focus, catch-up points, the dragon switch, the speech animations), the player
// assignments, the fury, the timers, the single-player partner flags, the flight altitude gap and the camera distance
// approach (+0x100 toward +0x120 or +0x10c).
void CKGrpS08Hero::Update(IKTime* clock) {
    UpdateSwitchPressFeedback(clock);  // 0x002ce5c8
    m_unk2c8 &= 0xfffffbffu;
    static_cast<CKSrvDynamic*>(g_pEngine->m_srvDynamic)->SetEntryFlag(this, 1);  // 0x0023aff8
    UpdateCoopFocusedDragon(clock);    // 0x002d6c60
    UpdateHeroGroup(clock);            // 0x002c8870 IKGrpHero_Update
    SynchronizeHeroPlayerAssignments();  // 0x002d63f8
    UpdateFury(clock);                 // 0x002d71f0
    UpdateTimers364(clock);            // 0x002d61b8
    if (m_ui8ControlledHeroCount <= 1) UpdateSinglePlayerPartnerFlags();  // 0x002ca288, 0x002d57a8
    UpdateFlightAltitudeGap();         // 0x002ce888
    m_unk100 = m_unkfc != 0 ? m_unk120 : m_unk10c;
    FloatApproach_Step(clock->m_afDeltaTime[0], &m_unk100);  // 0x002436e8
}

// 0x002ce5c8 CKGrpS08Hero_UpdateSwitchPressFeedback_maybe. STUB(C2.8: switches): the feedback FX of the switches the
// controlled heroes stand on (CKHkS08Hero_SetSwitchFeedbackFxActive_maybe 0x338130). No switch near the start.
void CKGrpS08Hero::UpdateSwitchPressFeedback(IKTime*) {
    DOTD_STUB_ONCE("CKGrpS08Hero_UpdateSwitchPressFeedback_maybe 0x2ce5c8 (C2.8)");
}

namespace {
// The words of m_sProperties are floats in LVL010 (read as such by the original).
float PropertyFloat(const IKGrpHero::SProperties& properties, uint32_t index) {
    float value;
    std::memcpy(&value, &properties.m_aui32Words[index], sizeof(value));
    return value;
}
// +0x2d4..+0x318 are typed as words (m_unk2d4[], m_unk318); the pair geometry stores floats there.
float WordAsFloat(uint32_t word) {
    float value;
    std::memcpy(&value, &word, sizeof(value));
    return value;
}
void StoreFloat(uint32_t* word, float value) { std::memcpy(word, &value, sizeof(value)); }

// 0x009bd208 CKGrpS08Hero_CompareCatchUpPoints_maybe (the qsort comparator of the catch-up points): the usable points
// first (+0x11 clear), by score; a pair of unusable points by score; for an unusable `a` against a usable `b` of the
// same or a lower score, a's +0x11 byte.
int CompareCatchUpPoints(const void* first, const void* second) {
    const CKGrpS08Hero::SCatchUpPoint* a = static_cast<const CKGrpS08Hero::SCatchUpPoint*>(first);
    const CKGrpS08Hero::SCatchUpPoint* b = static_cast<const CKGrpS08Hero::SCatchUpPoint*>(second);
    const uint8_t bUnavailable = b->m_ui8Unavailable;
    if (bUnavailable != 0 && a->m_ui8Unavailable != 0) {
        if (b->m_fScore > a->m_fScore) return -1;
        if (b->m_fScore < a->m_fScore) return 1;
        return 0;
    }
    if (b->m_fScore > a->m_fScore) return -1;
    if (bUnavailable != 0) return -1;
    if (b->m_fScore >= a->m_fScore) return a->m_ui8Unavailable;  // bge (a NaN returns 1)
    return 1;
}

// UpdateCatchUpPoints' inlined cell reads and writes: the point's cell in the grid of the graph node its hint names.
CKPFGraphNode* PointNode(CKSrvPathFinding* service, const CPFPoint* point) {
    return static_cast<CKPFGraphNode*>(service->m_Graph.m_apGraphNodes[point->m_unk0c]);
}
// The cell's palette value is 0xff (a dynamic obstacle): (~value & 0xff) - 1 is negative.
uint8_t IsPointCellBlocked(CKSrvPathFinding* service, const CPFPoint* point) {
    CKPFGraphNode* node = PointNode(service, point);
    uint8_t cell[2];
    node->m_Sector.WorldToCell(&point->m_position, cell);  // 0x001ea3e0
    return g_pfGridPalette[node->m_Sector.m_grid.GetCellFlags(cell)] == 0xff ? 1 : 0;  // 0x001f0fe0
}
void SetPointCellBlocked(CKSrvPathFinding* service, const CPFPoint* point, int32_t blocked) {
    CKPFGraphNode* node = PointNode(service, point);
    uint8_t cell[2];
    node->m_Sector.WorldToCell(&point->m_position, cell);  // 0x001ea3e0
    node->m_Sector.m_grid.SetCellBlocked(cell, blocked);   // 0x001f12d8
}
uint8_t FindSector(CKSrvPathFinding* service, CPFPoint* point) {
    return static_cast<uint8_t>(service->FindSectorForPoint(point));  // 0x001e5ca0
}
}  // namespace

// 0x002caf58 CKGrpS08Hero_FindCatchUpPoint_maybe
CKGrpS08Hero::SCatchUpPoint* CKGrpS08Hero::FindCatchUpPoint(CKHkS08Hero* hero) {
    const uint8_t index = hero->m_ui8Hero;
    const CKHkS08Hero* controlling = hero->GetControllingHero();  // 0x00344e68
    const uint32_t count = m_sProperties.m_ui8Value;
    const int8_t held = static_cast<int8_t>(m_pUnk7c[index]);
    if (count == 0) return nullptr;
    SCatchUpPoint* points = static_cast<SCatchUpPoint*>(m_pUnk74) + controlling->m_ui8Leader * count;
    SCatchUpPoint* first = nullptr;
    if (held == -1) {
        for (uint32_t i = 0; i < count; ++i) {
            if (first == nullptr) first = &points[i];
        }
        return first;
    }
    SCatchUpPoint* match = nullptr;
    for (uint32_t i = 0; i < count; ++i) {
        if (first == nullptr) first = &points[i];
        if (points[i].m_i8Index == held) match = &points[i];
    }
    if (match == nullptr) return first;
    if (first == nullptr) return nullptr;
    // +0xd4: the score margin that keeps the point held.
    return match->m_fScore >= first->m_fScore + PropertyFloat(m_sProperties, 5) ? first : match;  // bge
}

// 0x002cb4c0 CKGrpS08Hero_IsDragonSelectable_maybe (vt+0x188): a controlled dragon always; another one when it is enabled (+0x1a4), not
// +0x358 bit 22 and not +0x360 bit 12.
uint8_t CKGrpS08Hero::IsDragonSelectable(uint8_t dragon) {
    const CKHkS08Hero* hero = static_cast<const CKHkS08Hero*>(m_apHeros[dragon]);
    if (hero->m_ui8Hero == hero->m_ui8TrackedLeader) return 1;
    if (hero->m_aui8Unk1a4[0] == 0) return 0;
    if ((hero->m_unk358 & 0x400000u) != 0) return 0;
    return static_cast<uint8_t>(((hero->m_unk360 >> 12) & 1u) ^ 1u);
}

// 0x002cb6f0 CKGrpS08Hero_AssignFollowSlot_maybe
const CVector3* CKGrpS08Hero::AssignFollowSlot(CKHkS08Hero* hero) {
    const uint8_t index = hero->m_ui8Hero;
    const uint8_t player = hero->GetControllingHero()->m_ui8Leader;  // 0x00344e68
    int8_t* held = reinterpret_cast<int8_t*>(m_pUnk7c);
    const int8_t previous = held[index];
    SCatchUpPoint* first = nullptr;  // the first free point no other hero of the player holds
    SCatchUpPoint* same = nullptr;   // the free point the hero held
    if (m_sProperties.m_ui8Value == 0) {
        held[index] = -1;
        return nullptr;
    }
    SCatchUpPoint* points = static_cast<SCatchUpPoint*>(m_pUnk74) + player * m_sProperties.m_ui8Value;
    for (uint32_t i = 0; i < m_sProperties.m_ui8Value; ++i) {
        SCatchUpPoint* point = &points[i];
        if (point->m_ui8Unavailable != 0) continue;
        if (first == nullptr) {
            const uint8_t pointIndex = static_cast<uint8_t>(point->m_i8Index);
            bool heldByOther = false;
            for (uint32_t j = 0; j < GetHeroCount(); ++j) {  // vt+0xf4 each time
                if (j == index) continue;
                const CKHkS08Hero* other = static_cast<CKHkS08Hero*>(m_apHeros[j])->GetControllingHero();
                if (player != other->m_ui8Leader) continue;
                if (static_cast<int32_t>(held[j]) == static_cast<int32_t>(pointIndex)) {
                    heldByOther = true;
                    break;
                }
            }
            if (!heldByOther) first = point;
        }
        if (point->m_i8Index != previous || point->m_i8Index == -1) continue;
        same = point;
    }
    SCatchUpPoint* chosen = first;
    if (same != nullptr) {
        if (first == nullptr) {
            chosen = nullptr;
        } else if (same->m_fScore < first->m_fScore + PropertyFloat(m_sProperties, 5)) {  // blt
            chosen = same;
        }
    }
    if (chosen == nullptr) {
        held[index] = -1;
        return nullptr;
    }
    held[index] = chosen->m_i8Index;
    chosen->m_ui8Unavailable = 1;
    return &chosen->m_vPosition;
}

// 0x002cb9c0 CKGrpS08Hero_CanSwitchToDragon_maybe: a controlled dragon always; another one unless +0xf8 bit 1 or 2,
// a hero standing on a ground of property 0x40, or vt+0x188.
uint8_t CKGrpS08Hero::CanSwitchToDragon(uint8_t dragon) {
    const CKHkS08Hero* target = static_cast<const CKHkS08Hero*>(m_apHeros[dragon]);
    if (target->m_ui8Hero == target->m_ui8TrackedLeader) return 1;
    if ((m_unkf8 & 2u) != 0 || (m_unkf8 & 4u) != 0) return 0;
    const uint8_t count = GetHeroCount();  // vt+0xf4
    for (uint32_t i = 0; i != count; ++i) {
        const CGround* ground = static_cast<const CGround*>(static_cast<CKHkS08Hero*>(m_apHeros[i])->GetGroundInfo());
        if (ground != nullptr && (ground->m_ui16PropertiesFlags & 0x40u) != 0) return 0;  // 0x00361b68, +0x38
    }
    return IsDragonSelectable(dragon) != 0 ? 1 : 0;  // vt+0x188
}

// 0x002cbb08 CKGrpS08Hero_RequestDragonSelection_maybe: a new request (+0xf8 bit 5 clear, or another selected or
// requested dragon) stores the time (+0x60), the dragons (+0x64 / +0x65), +0xf8 bits 6 / 7 / 8 and fires trigger 4
// once; `immediate` hands it to vt+0x180 at once, else after +0x5c seconds the requested dragon is checked: one that
// cannot play is skipped (the next index), one that is the selected one or cannot be switched to drops the request.
void CKGrpS08Hero::RequestDragonSelection(uint8_t selected, uint8_t requested, uint8_t flag6, uint8_t flag7,
                                          uint8_t immediate, uint8_t applyArg, uint8_t forceFlag8) {
    const float now = g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[0];
    const bool renew = (m_unkf8 & 0x20u) == 0 || m_unk64 != selected || m_unk65 != requested;
    if (renew) {
        m_unk60 = now;
        m_unk64 = selected;
        m_unk65 = requested;
        uint32_t flags = (m_unkf8 & ~0x40u) | ((static_cast<uint32_t>(flag6) << 6) & 0x3fc0u);
        flags = (flags & ~0x80u) | ((static_cast<uint32_t>(flag7) << 7) & 0x7f80u);
        m_unkf8 = flags;
        if (forceFlag8 != 0 || (m_unkf8 & 0x10000u) != 0) {
            m_unkf8 = (flags & ~0x100u) | 0x100u;
        } else {
            m_unkf8 = flags & ~0x100u;
        }
        if ((m_unkf8 & 0x20u) == 0) QueueTriggerSignals(&m_aTriggers[4]);  // +0xb8; 0x00236338
        m_unkf8 = (m_unkf8 & ~0x20u) | 0x20u;
    }
    if (immediate != 0) {
        ProcessDragonSwitchRequest(applyArg);  // vt+0x180
        return;
    }
    if (!(now - m_unk60 >= m_unk5c)) return;  // cror gt|eq
    const CKHkS08Hero* target = static_cast<const CKHkS08Hero*>(m_apHeros[m_unk65]);
    // 0x00363ca0 IKHkHero_GetFlag360Bit12_maybe (IKHkHero_2.cpp; inlined here): +0x360 bit 12.
    if (((target->m_unk360 >> 12) & 1u) != 0 || target->m_aui8Unk1a4[0] == 0) {
        m_unk65 = static_cast<uint8_t>(m_unk65 + 1);
        if (!(m_unk65 < GetHeroCount())) m_unk65 = immediate;  // vt+0xf4; `immediate` is 0 here
        return;
    }
    if (m_unk65 == m_unk64 || CanSwitchToDragon(m_unk65) == 0 || (m_unkf8 & 8u) != 0 || (m_unkf8 & 2u) != 0) {
        m_unk65 = m_unk64;
        m_unkf8 &= ~0x20u;
        return;
    }
    // STUB(C2.7, moved from C2.6: the dragon switch changes who the player controls and shows the HUD feedback; ApplyRequestedDragonSelection 0x2cc7c0 is 4.7 KB with the control assignment, the queued trigger signals and the HUD panels): the original asks both heroes' vt+0x170
    // (CKHkS08Hero_CanDragonSwitch_maybe 0x2dbc60, CKHkS08Hero.cpp) and returns when either refuses, then calls vt+0x180
    // (ProcessDragonSwitchRequest, stubbed). Only the Select button gets here.
    DOTD_STUB_ONCE("CKGrpS08Hero_RequestDragonSelection_maybe: CKHkS08Hero_CanDragonSwitch_maybe 0x2dbc60 (C2.7, moved from C2.6)");
    ProcessDragonSwitchRequest(applyArg);  // vt+0x180
}

// 0x002cbf10 CKGrpS08Hero_UpdatePartnerInteraction_maybe: the Select button of a controlled hero (+0x360 bit 17) once
// +0xec seconds after the last switch (+0x6c) requests the next dragon (RequestDragonSelection, also every frame while a
// request is pending, +0xf8 bit 5); +0xf8 bit 15 runs a timer (+0x70) toward the interaction target.
void CKGrpS08Hero::UpdatePartnerInteraction(IKTime* clock) {
    if ((m_unkf8 & 0x20000u) != 0) {
        m_unk65 = m_unk64;
        m_unk6c = -1000.0f;  // TOC 0x1b60
        m_unkf8 &= ~0x20u;
    }
    const uint8_t count = GetHeroCount();  // vt+0xf4
    uint32_t flags = m_unkf8;
    uint8_t requested = m_unk65;
    uint8_t pressed = 0;
    // BUG(original): the loop over the heroes tests the first hero's +0x0c bit 1 every time.
    const bool blocked = (flags & 8u) != 0 ||
                         (count > 0 && m_apHeros[0] != nullptr &&
                          (static_cast<CKHkS08Hero*>(m_apHeros[0])->m_bitArray & 2u) != 0);
    if (!blocked && clock->m_afCurrentTime[0] - m_unk6c >= PropertyFloat(m_sProperties, 11) && count > 0) {  // +0xec
        for (uint32_t i = 0; i < count; ++i) {
            const CKHkS08Hero* hero = static_cast<const CKHkS08Hero*>(m_apHeros[i]);
            if (hero == nullptr) continue;
            if (hero->m_ui8Hero != hero->m_ui8TrackedLeader) continue;
            if ((hero->m_unk360 & 0x20000u) == 0) continue;
            pressed = 1;
            if (static_cast<int32_t>(static_cast<int8_t>(m_unk66)) != static_cast<int32_t>(i)) continue;
            if ((flags & 0x20u) == 0) requested = static_cast<uint8_t>(i);
            requested = static_cast<uint8_t>(requested + 1);
            if (count <= requested) requested = 0;
            m_unk64 = static_cast<uint8_t>(i);
        }
    }
    if ((flags & 0x20u) != 0 || m_unk64 != requested) {
        RequestDragonSelection(m_unk64, requested, 0, 0, 0, 0, 0);  // 0x002cbb08
        flags = m_unkf8;
    }
    if ((flags & 0x8000u) != 0) {
        float timer;
        std::memcpy(&timer, &m_unk70, sizeof(timer));
        timer = timer + clock->m_afDeltaTime[0];
        std::memcpy(&m_unk70, &timer, sizeof(timer));
        if (timer > 0.7f) {  // TOC 0x1b64
            if (pressed != 0) m_unk68 = clock->m_afCurrentTime[0];
            // STUB(C2.8: interaction targets): SetHeroInteractionTarget 0x4ee770 (CKS08GameManager_2.cpp) with the
            // game manager, the group, 0 and player 0. +0xf8 bit 15 is not set in the idle and walk runs.
            DOTD_STUB_ONCE("CKGrpS08Hero_UpdatePartnerInteraction_maybe: SetHeroInteractionTarget 0x4ee770 (C2.8)");
        }
    } else {
        m_unk70 = 0;
    }
    // The rest (no +0x54, +0xe8 seconds after +0x68, two controlled heroes, none of +0xf8 bits 12..14) measures the
    // focused hero's distance to the other player's against +0xe0 and drops the result: nothing is written.
}

// 0x002ccbe0 CKGrpS08Hero_UpdateCatchUpPoints_maybe: for each controlled hero, the m_sProperties.m_ui8Value points of
// its player block (+0x74) around it at radius +0x84, the first half a step past straight behind the camera's axis
// (+0x88, kept within 0.02): those within half +0xf2 degrees of the hero's heading, or all without a companion
// following the hero, are unusable; the others score by their side and their facing to the camera (or, with one
// player, vf17C: the distance to the companion). Sorted, each usable one is put on the nav (ValidateNavPosition with
// the companions' widest character, the player's contacts +0x80), off the nav or more than +0xd8 below / above the hero
// it becomes unusable. When fewer usable points than following companions remain, extra points are searched from the
// hero's nav point (the nearest open cells within +0xdc, with the leader's and the points' cells blocked meanwhile)
// and copied after the usable ones.
void CKGrpS08Hero::UpdateCatchUpPoints() {
    CKSrvPathFinding* service = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    GetHeroCount();  // vt+0xf4 (the answer is not used)
    const float step = 0x1.921fb6p+2f / static_cast<float>(m_sProperties.m_ui8Value);  // 2 pi (TOC 0x1b6c) / count
    const CVector3 axis = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_v3RealAxisZ;  // +0x5c8
    const float tolerance = 0x1.47ae14p-6f;  // 0.02 (TOC 0x1b70)
    if (!(m_vUnk88.x - tolerance <= axis.x) || !(m_vUnk88.x + tolerance >= axis.x) ||
        !(m_vUnk88.y - tolerance <= axis.y) || !(m_vUnk88.y + tolerance >= axis.y) ||
        !(m_vUnk88.z - tolerance <= axis.z) || !(m_vUnk88.z + tolerance >= axis.z)) {
        m_vUnk88.z = axis.z;
        m_vUnk88.x = axis.x;
        m_vUnk88.y = axis.y;
    }
    const CVector3 camera = m_vUnk88;
    const float halfStep = step * 0.5f;
    CVector3 back{-camera.x, -camera.y, -camera.z};
    Vec3_RotateYawFlatNormalized(halfStep, &back);       // 0x00584e40
    const float backYaw = Vec3_GetYawAngleFromX(&back);  // 0x00244638
    // half +0xf2 degrees (0x3c8efa34 per degree, TOC 0x1b78)
    const float halfCone = static_cast<float>(m_sProperties.m_aui16Values[1]) * 0.5f * 0x1.1df468p-6f;
    CPFCharacter character;
    character.m_bits = 0x801;
    character.m_unk04 = g_pfGridScale.m_halfCellSize * 0x1.99999ap-3f;  // 0x00c40260 * 0.2
    character.m_unk08 = 0x1.99999ap-3f;  // 0.2
    character.m_unk0c = 1.0f;
    const float range = PropertyFloat(m_sProperties, 7);  // +0xdc
    const float rangeSq = range * range;
    for (IKSerializable** cursor = m_apControlledHeroes; *cursor != nullptr; ++cursor) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(*cursor);
        const CVector3 position{hero->m_unk54c, hero->m_unk550, hero->m_unk554};
        const CVector3 heading{hero->m_unk540, hero->m_unk544, hero->m_unk548};
        const CPFPoint leaderPoint = hero->m_PFCpnt.m_Destination;  // +0x430
        const uint16_t leaderSector = leaderPoint.m_unk0c;
        const float headingYaw = Vec3_GetYawAngleFromX(&heading);  // 0x00244638
        // The companions following this hero; the widest one's character.
        uint8_t companions = 0;
        character.m_unk04 = 0.0f;
        for (IKSerializable** other = m_apCompanionHeroes; *other != nullptr; ++other) {
            const CKHkS08Hero* companion = static_cast<const CKHkS08Hero*>(*other);
            if (hero->m_ui8Hero != companion->m_ui8TrackedLeader) continue;
            const uint32_t flags35c = companion->m_unk35c;
            if ((flags35c & 0x40u) != 0 && (companion->m_unk3b0 & 0x40u) == 0) continue;
            if ((flags35c & 0x20u) != 0) continue;
            const uint32_t flags360 = companion->m_unk360;
            if ((flags360 & 0x40000000u) != 0) continue;
            if ((flags35c & 0x20000000u) != 0) continue;
            if ((flags360 & 0x1000u) != 0) continue;
            if ((companion->m_unk364 & 0x200u) != 0) continue;
            const uint32_t flags358 = companion->m_unk358;
            if ((flags358 & 8u) != 0 || (flags358 & 4u) != 0) continue;
            if (companion->m_PFCharacter.m_unk04 > character.m_unk04) character = companion->m_PFCharacter;  // +0x3e0
            ++companions;
        }
        const uint32_t block = static_cast<uint8_t>(hero->m_ui8Leader * m_sProperties.m_ui8Value);
        SCatchUpPoint* points = static_cast<SCatchUpPoint*>(m_pUnk74) + block;
        if (m_sProperties.m_ui8Value != 0) {
            float yaw = backYaw;
            float angle = halfStep + 0.0f;  // TOC 0x1b2c
            CVector3 lastDirection;
            for (uint32_t i = 0;;) {
                SCatchUpPoint& point = points[i];
                if (companions == 0) {
                    point.m_vPosition = position;
                    lastDirection = heading;
                    point.m_i8Index = static_cast<int8_t>(i);
                    point.m_fScore = 1.0f;
                    point.m_ui8Unavailable = 1;
                } else {
                    Vec3_GenerateRadialPointsXZ(angle, m_unk84, &position, &heading, &point.m_vPosition, 1,
                                                &lastDirection);  // 0x00585110
                    point.m_i8Index = static_cast<int8_t>(i);
                    const float off = std::fabs(Math_WrapAngleToPi(headingYaw - yaw));  // 0x00582c18
                    if (halfCone > off) {
                        point.m_fScore = 1.0f;
                        point.m_ui8Unavailable = 1;
                    } else {
                        point.m_ui8Unavailable = 0;
                        const float side = std::fabs(ppc::fmadds(
                            heading.z, lastDirection.z, ppc::fmadds(heading.x, lastDirection.x, heading.y * lastDirection.y)));
                        const float facing = ppc::fmadds(
                            camera.z, lastDirection.z, ppc::fmadds(camera.x, lastDirection.x, camera.y * lastDirection.y));
                        // ble: a NaN takes the product.
                        const float bias = facing <= 0.0f ? facing * -2.0f : -0.0f;  // TOC 0x1b84 / 0x1b94
                        point.m_fScore = (side + bias) * 0x1.51eb86p-2f;             // 0.33 (TOC 0x1b88)
                    }
                }
                ++i;
                if (m_sProperties.m_ui8Value <= i) break;
                yaw = yaw + step;
                angle = angle + step;
            }
        }
        ScoreCatchUpPointsByCompanionDistance();  // vt+0x17c
        Ps3Qsort(points, m_sProperties.m_ui8Value, sizeof(SCatchUpPoint), CompareCatchUpPoints);  // 0x0095eab0
        // The usable points put on the nav.
        uint8_t remaining = companions;
        CPFPoint probe = leaderPoint;
        CGroundContactDatasInOut* contacts = m_pPlayerSlots + block;
        for (uint32_t j = 0; j < m_sProperties.m_ui8Value; ++j) {
            SCatchUpPoint& point = points[j];
            if (point.m_ui8Unavailable != 0) continue;
            probe.m_position = point.m_vPosition;
            probe.m_unk0c = leaderSector;
            FindSector(service, &probe);
            uint8_t reachable = static_cast<uint8_t>(hero->GetNavTransitionFlag2IfAllowed(
                static_cast<int16_t>(probe.m_unk0c), static_cast<int16_t>(leaderSector)));  // 0x00369f40
            if (reachable == 0) probe.m_unk0c = leaderSector;
            const uint8_t valid =
                hero->ValidateNavPosition(&contacts[j], &probe, &character, 1, &point.m_ui8Raised);  // 0x0036a2f8
            bool reject = point.m_ui8Unavailable != 0 || valid == 0;
            if (!reject && PropertyFloat(m_sProperties, 6) < std::fabs(position.y - probe.m_position.y)) reject = true;
            point.m_ui8Unavailable = reject ? 1 : 0;
            if (static_cast<int16_t>(probe.m_unk0c) == -1) {
                reachable = 0;
            } else if (static_cast<int16_t>(leaderSector) == static_cast<int16_t>(probe.m_unk0c)) {
                reachable = 1;
            }
            point.m_ui8Reachable = reachable;
            if (point.m_ui8Unavailable != 0) continue;
            point.m_vPosition = probe.m_position;
            --remaining;
        }
        Ps3Qsort(points, m_sProperties.m_ui8Value, sizeof(SCatchUpPoint), CompareCatchUpPoints);  // 0x0095eab0
        const int32_t wanted = static_cast<int8_t>(remaining);
        if (wanted <= 0) continue;
        // The cells' states, then the leader's cell and the reachable points' cells blocked.
        probe = leaderPoint;
        const uint8_t leaderCellBlocked = FindSector(service, &probe) != 0 ? IsPointCellBlocked(service, &probe) : 0;
        for (uint32_t k = 0; k < m_sProperties.m_ui8Value; ++k) {
            SCatchUpPoint& point = points[k];
            if (point.m_ui8Reachable == 0) continue;
            probe.m_position = point.m_vPosition;
            point.m_ui8CellBlocked = FindSector(service, &probe) != 0 ? IsPointCellBlocked(service, &probe) : 0;
        }
        if (static_cast<int16_t>(leaderPoint.m_unk0c) != -1) {
            probe = leaderPoint;
            if (FindSector(service, &probe) != 0) SetPointCellBlocked(service, &probe, 1);
        }
        for (uint32_t k = 0; k < m_sProperties.m_ui8Value; ++k) {
            const SCatchUpPoint& point = points[k];
            if (point.m_ui8Reachable == 0) continue;
            probe.m_position = point.m_vPosition;
            if (FindSector(service, &probe) != 0) SetPointCellBlocked(service, &probe, 1);
        }
        // The extra points: the nearest open cells around the hero's nav point (else the nearest sector's point).
        CPFPoint seed = leaderPoint;
        if (static_cast<int16_t>(leaderPoint.m_unk0c) == -1) seed = service->ClampToNearestSector(&leaderPoint);  // 0x001e5680
        CGroundContactDatasInOut contact = hero->m_gcCurDatasInOut;  // +0x4b8
        SCatchUpPoint* extra = static_cast<SCatchUpPoint*>(m_pUnk78);
        uint32_t found = 0;
        const int32_t seedSector = static_cast<int16_t>(seed.m_unk0c);
        for (int32_t attempt = 0; attempt != wanted; ++attempt) {
            probe = seed;
            CKPFGraphNode* node = PointNode(service, &seed);
            PathFinding_SetWalkabilityMode(character.m_bits & 7u);  // 0x001f1158
            node->m_Sector.m_grid.m_ui8DynamicMask = (character.m_bits & 0x800u) != 0 ? 0xff : 0xf7;
            CVector3 nearest;
            if (node->m_Sector.FindNearestWalkableCell(&probe.m_position, &nearest) == 0) continue;  // 0x001ed6e0
            const float dy = position.y - nearest.y;
            const float dx = position.x - nearest.x;
            const float dz = position.z - nearest.z;
            if (!(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)) < rangeSq)) continue;
            probe.m_position = nearest;
            SCatchUpPoint& point = extra[found];
            if (hero->ValidateNavPosition(&contact, &probe, &character, 1, &point.m_ui8Raised) == 0) continue;
            if (position.y - probe.m_position.y >= PropertyFloat(m_sProperties, 6)) continue;  // bge
            FindSector(service, &probe);
            if (seedSector != static_cast<int16_t>(probe.m_unk0c)) continue;
            point.m_vPosition.x = probe.m_position.x;
            point.m_vPosition.y = probe.m_position.y;
            point.m_fScore = 0.0f;
            point.m_vPosition.z = probe.m_position.z;
            point.m_ui8Unavailable = 0;
            point.m_i8Index = -1;
            point.m_ui8CellBlocked = FindSector(service, &probe) != 0 ? IsPointCellBlocked(service, &probe) : 0;
            if (FindSector(service, &probe) != 0) SetPointCellBlocked(service, &probe, 1);
            ++found;
            if (static_cast<int32_t>(found & 0xffu) == wanted) break;
        }
        found &= 0xffu;
        // The cells given back their states: the extra points' (last first), the leader's, the points'.
        for (uint32_t k = found; k != 0;) {
            --k;
            probe.m_position = extra[k].m_vPosition;
            const uint8_t wasBlocked = extra[k].m_ui8CellBlocked;
            if (FindSector(service, &probe) != 0) SetPointCellBlocked(service, &probe, wasBlocked);
        }
        if (static_cast<int16_t>(leaderPoint.m_unk0c) != -1) {
            probe = leaderPoint;
            if (FindSector(service, &probe) != 0) SetPointCellBlocked(service, &probe, leaderCellBlocked & 1u);
        }
        for (uint32_t k = 0; k < m_sProperties.m_ui8Value; ++k) {
            const SCatchUpPoint& point = points[k];
            if (point.m_ui8Reachable == 0) continue;
            probe.m_position = point.m_vPosition;
            const uint8_t wasBlocked = point.m_ui8CellBlocked;
            if (FindSector(service, &probe) != 0) SetPointCellBlocked(service, &probe, wasBlocked);
        }
        if (found != 0) {
            std::memcpy(points + companions - wanted, extra, found * sizeof(SCatchUpPoint));  // 0x0095c270
        }
    }
}

// 0x002ceb30 CKGrpS08Hero_ApplyTetherPullToHero_maybe
void CKGrpS08Hero::ApplyTetherPullToHero(float maxDistance, CKHkS08Hero* hero) {
    const float half = maxDistance * 0.5f;  // TOC 0x1c2c
    hero->SetExternalDisplacementFlag(0);   // 0x00329d88
    const CVector3 zero{0.0f, 0.0f, 0.0f};  // the zero vector 0xc50d64 (TOC 0x1c30)
    hero->SetExternalDisplacement(&zero);   // 0x0032a6e8
    uint32_t* distance314 = &m_unk2d4[16];
    uint32_t* distance318 = &m_unk318;
    if (hero->m_ui8Hero == 0) {
        if (WordAsFloat(*distance314) <= half) return;  // ble
    } else {
        const float distance = hero->m_ui8Hero == 1 ? WordAsFloat(*distance318) : 0.0f;
        if (!(distance > half)) return;  // bgt
    }
    hero->SetExternalDisplacementFlag(1);
    float excess;
    uint8_t index = hero->m_ui8Hero;
    if (index == 0) {
        excess = WordAsFloat(*distance314) - half;
        StoreFloat(distance314, half);
        index = hero->m_ui8Hero;
    } else if (index == 1) {
        excess = WordAsFloat(*distance318) - half;
        StoreFloat(distance318, half);
        index = hero->m_ui8Hero;
    } else {
        excess = 0.0f - half;
    }
    CVector3 direction = zero;
    if (index == 0) {
        direction = CVector3{WordAsFloat(m_unk2d4[10]), WordAsFloat(m_unk2d4[11]), WordAsFloat(m_unk2d4[12])};  // +0x2fc
    } else if (index == 1) {
        direction = CVector3{WordAsFloat(m_unk2d4[13]), WordAsFloat(m_unk2d4[14]), WordAsFloat(m_unk2d4[15])};  // +0x308
    }
    const CVector3 displacement{ppc::fmadds(excess, direction.x, zero.x), ppc::fmadds(excess, direction.y, zero.y),
                                ppc::fmadds(excess, direction.z, zero.z)};
    hero->SetExternalDisplacement(&displacement);
}

namespace {
// DOTD: the group's CKSrvDynamic hook by descriptor (PostLoad registers it as the sub-step hook; UpdateCKSrvDynamic
// 0x23ba10 calls it with the fixed step).
Ps3MemberFnEntry<void (CKGrpS08Hero::*)(float)> g_heroGroupDynamicHooks[] = {
    {0x00b97b20u, &CKGrpS08Hero::UpdateHeroPairGeometry, "CKGrpS08Hero_UpdateHeroPairGeometry_maybe 0x2d01d8", false},
};
}  // namespace

// DOTD: CKSrvDynamic's native dispatcher of the group's entry.
void CKGrpS08Hero::DispatchDynamicHook(IKSerializable* object, const uint32_t pair[2], float step) {
    void (CKGrpS08Hero::*fn)(float) = ResolvePs3MemberFn(g_heroGroupDynamicHooks, pair, "CKGrpS08Hero dynamic hook");
    if (fn != nullptr) (static_cast<CKGrpS08Hero*>(object)->*fn)(step);
}

// 0x002cf2e0 CKGrpS08Hero_PostLoad: a level registers the group in CKSrvDynamic (flag 0, key 0xff, the sub-step hook
// 0xb97b20 = UpdateHeroPairGeometry; TOC 0x1c5c) and sets +0x324..+0x334 and +0xab8.
int32_t CKGrpS08Hero::PostLoad(int32_t type) {
    IKGrpHero::PostLoad(type);  // 0x002c8598
    if (type == K_LEVEL_PLATEFORMS) {
        CKSrvDynamic* dynamic = static_cast<CKSrvDynamic*>(g_pEngine->m_srvDynamic);
        dynamic->RegisterHook(this, 0, 0xff, {0x00b97b20u, 0}, {0, 0}, {0, 0});  // 0x0023b480
        dynamic->SetNativeDispatch(this, &CKGrpS08Hero::DispatchDynamicHook);  // DOTD
        m_tsUnkab0.PostLoad(0);  // 0x00236330
        m_unk324 = 50.0f;        // TOC 0x1c60
        m_unk328 = 20.0f;        // TOC 0x1c38
        m_unk330 = 0;
        m_unk334 = 1000;
        m_unk32c = 0;
        m_unkab8 = static_cast<uint8_t>(type);
        m_tsUnk338.PostLoad(0);
        m_tsUnk340.PostLoad(0);
        m_tsUnkac0.PostLoad(0);
    }
    return 1;
}

// 0x002d0018 CKGrpS08Hero_ScoreCatchUpPointsByCompanionDistance_maybe (vt+0x17c)
void CKGrpS08Hero::ScoreCatchUpPointsByCompanionDistance() {
    if (m_ui8ControlledHeroCount > 1) return;
    const CKHkS08Hero* companion = static_cast<const CKHkS08Hero*>(m_apCompanionHeroes[0]);
    SCatchUpPoint* points = static_cast<SCatchUpPoint*>(m_pUnk74);
    float largest = 0.0f;  // TOC 0x1c28
    for (uint32_t i = m_sProperties.m_ui8Value; i != 0;) {
        --i;
        SCatchUpPoint& point = points[i];
        point.m_ui8Unavailable = 0;
        const float dy = point.m_vPosition.y - companion->m_unk550;
        const float dx = point.m_vPosition.x - companion->m_unk54c;
        const float dz = point.m_vPosition.z - companion->m_unk554;
        const float squared = ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy));
        point.m_fScore = std::sqrt(squared);                             // Math_Sqrtf 0x10690
        if (!(largest >= std::sqrt(squared))) largest = std::sqrt(squared);  // bge
    }
    if (largest <= 0.0f) return;  // ble
    for (uint32_t i = m_sProperties.m_ui8Value; i != 0;) {
        --i;
        points[i].m_fScore = points[i].m_fScore / largest;
    }
}

// 0x002d01d8 CKGrpS08Hero_UpdateHeroPairGeometry_maybe
void CKGrpS08Hero::UpdateHeroPairGeometry(float dt) {
    CKHkS08Hero* second = static_cast<CKHkS08Hero*>(m_apHeros[1]);
    CKHkS08Hero* first = static_cast<CKHkS08Hero*>(m_apHeros[0]);
    if (m_ui8ControlledHeroCount <= 1) {
        // The answers are not used (0x00342fa8 for the first hero, then for the second when the first says no).
        if (first->ShouldStayClimbing() == 0) second->ShouldStayClimbing();
    }
    // +0x2e0: from the first hero to the second, both moved by their velocities over dt, normalised (+0x2d8 its length).
    {
        const CVector3 to = second->GetAdjustedPosition();    // 0x0032a758
        const CVector3 from = first->GetAdjustedPosition();
        float x = to.x - from.x;
        float y = to.y - from.y;
        float z = to.z - from.z;
        const CVector3 toVelocity = second->GetDerivedVelocity();  // 0x0032a730
        x = ppc::fmadds(dt, toVelocity.x, x);
        y = ppc::fmadds(dt, toVelocity.y, y);
        z = ppc::fmadds(dt, toVelocity.z, z);
        const CVector3 fromVelocity = first->GetDerivedVelocity();
        const float back = -dt;
        y = ppc::fmadds(back, fromVelocity.y, y);
        x = ppc::fmadds(back, fromVelocity.x, x);
        z = ppc::fmadds(back, fromVelocity.z, z);
        float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));  // Math_Sqrtf 0x10690
        if (length != 0.0f) {
            const float inverse = 1.0f / length;  // TOC 0x1c98
            z = inverse * z;
            x = inverse * x;
            y = inverse * y;
        } else {
            length = 0.0f;  // TOC 0x1c28
        }
        StoreFloat(&m_unk2d4[3], x);  // +0x2e0
        StoreFloat(&m_unk2d4[4], y);
        StoreFloat(&m_unk2d4[5], z);
        StoreFloat(&m_unk2d4[1], length);  // +0x2d8
    }
    // The predicted positions.
    const CVector3 firstPosition = first->GetAdjustedPosition();
    const CVector3 secondPosition = second->GetAdjustedPosition();
    const CVector3 firstVelocity = first->GetDerivedVelocity();
    const float ax = ppc::fmadds(dt, firstVelocity.x, firstPosition.x);
    const float ay = ppc::fmadds(dt, firstVelocity.y, firstPosition.y);
    const float az = ppc::fmadds(dt, firstVelocity.z, firstPosition.z);
    const CVector3 secondVelocity = second->GetDerivedVelocity();
    const float bx = ppc::fmadds(dt, secondVelocity.x, secondPosition.x);
    const float bz = ppc::fmadds(dt, secondVelocity.z, secondPosition.z);
    const float by = ppc::fmadds(dt, secondVelocity.y, secondPosition.y);
    // +0x2f0: the tether's middle (kept with +0x2c8 bit 0).
    if ((m_unk2c8 & 1u) == 0) {
        StoreFloat(&m_unk2d4[7], (ax + bx) * 0.5f);  // TOC 0x1c2c
        StoreFloat(&m_unk2d4[8], (ay + by) * 0.5f);
        StoreFloat(&m_unk2d4[9], (az + bz) * 0.5f);
    }
    const float mx = WordAsFloat(m_unk2d4[7]);
    const float my = WordAsFloat(m_unk2d4[8]);
    const float mz = WordAsFloat(m_unk2d4[9]);
    // +0x2fc / +0x308: from each hero to the middle, normalised.
    float d0y = my - ay;
    float d0x = mx - ax;
    float d0z = mz - az;
    const float length0 = std::sqrt(ppc::fmadds(d0z, d0z, ppc::fmadds(d0x, d0x, d0y * d0y)));
    if (length0 != 0.0f) {
        const float inverse = 1.0f / length0;
        d0z = d0z * inverse;
        d0x = d0x * inverse;
        d0y = d0y * inverse;
    }
    float d1y = my - by;
    float d1x = mx - bx;
    float d1z = mz - bz;
    const float length1 = std::sqrt(ppc::fmadds(d1z, d1z, ppc::fmadds(d1x, d1x, d1y * d1y)));
    if (length1 != 0.0f) {
        const float inverse = 1.0f / length1;
        d1z = d1z * inverse;
        d1x = d1x * inverse;
        d1y = d1y * inverse;
    }
    StoreFloat(&m_unk2d4[10], d0x);
    StoreFloat(&m_unk2d4[13], d1x);
    StoreFloat(&m_unk2d4[11], d0y);
    StoreFloat(&m_unk2d4[14], d1y);
    StoreFloat(&m_unk2d4[12], d0z);
    StoreFloat(&m_unk2d4[15], d1z);
    // +0x314 / +0x318: the distances to the middle.
    const float e0y = my - ay;
    const float e0x = mx - ax;
    const float e1y = my - by;
    const float e1x = mx - bx;
    const float e0z = mz - az;
    const float e1z = mz - bz;
    StoreFloat(&m_unk2d4[16], std::sqrt(ppc::fmadds(e0z, e0z, ppc::fmadds(e0x, e0x, e0y * e0y))));
    StoreFloat(&m_unk318, std::sqrt(ppc::fmadds(e1z, e1z, ppc::fmadds(e1x, e1x, e1y * e1y))));
    const float maxDistance = m_unk108;
    ApplyTetherPullToHero(maxDistance, first);   // 0x002ceb30
    ApplyTetherPullToHero(maxDistance, second);
    // +0x2c8 bit 2: the middle is held (bit 0) or bit 11.
    if ((m_unk2c8 & 1u) != 0 || (m_unk2c8 & 0x800u) != 0) {
        m_unk2c8 = (m_unk2c8 & ~4u) | 4u;
    } else {
        m_unk2c8 &= ~4u;
    }
    const uint32_t count = GetHeroCount();  // vt+0xf4
    if ((m_unk2c8 & 1u) != 0) {
        // No tether while the middle is held.
        for (uint32_t i = count; i != 0;) {
            --i;
            static_cast<CKHkS08Hero*>(m_apHeros[i])->m_unkec4 &= ~0x400000u;
        }
    } else if (m_ui8ControlledHeroCount > 1) {
        // Two players: +0xec4 bit 22 follows +0xecc bit 4.
        for (uint32_t i = count; i != 0;) {
            --i;
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_apHeros[i]);
            if ((hero->m_unkecc & 0x10u) != 0) {
                hero->m_unkec4 = (hero->m_unkec4 & ~0x400000u) | 0x400000u;
            } else {
                hero->m_unkec4 &= ~0x400000u;
            }
        }
    } else {
        // One player, last hero first: the tether (bit 22 clear) holds a controlled hero on the ground whose partner's
        // +0x1258 is above 0.1; +0x2c8 bit 1 is set when no hero stays climbing and both +0x1258 are at most 0.1.
        const float threshold = 0x1.99999ap-4f;  // 0.1 (TOC 0x1c9c)
        for (uint32_t i = count; i != 0;) {
            --i;
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_apHeros[i]);
            const bool controlled = hero->m_ui8Hero == hero->m_ui8TrackedLeader;
            bool tether = false;
            if ((controlled || hero->IsFlyingMovementMode1() == 0) && hero->PartnerShouldStayClimbing() == 0 &&
                hero->IsClimbingMovementMode2() == 0) {
                const CKHkS08Hero* partner = hero->GetPartnerHero();  // 0x002f85f8
                tether = partner->m_unk1258 > threshold && hero->m_ui8Hero == hero->m_ui8TrackedLeader;
                if (!tether) hero->m_unkec4 = (hero->m_unkec4 & ~0x400000u) | 0x400000u;
            } else {
                tether = true;
            }
            if (tether) hero->m_unkec4 &= ~0x400000u;
            if ((m_unk2c8 & 0x1000u) != 0) hero->m_unkec4 &= ~0x400000u;
            if ((hero->m_unkec8 & 0x8000000u) != 0) hero->m_unkec4 = (hero->m_unkec4 & ~0x400000u) | 0x400000u;
            if (hero->ShouldStayClimbing() != 0 || hero->PartnerShouldStayClimbing() != 0) {
                m_unk2c8 &= ~2u;
            } else {
                m_unk2c8 = (m_unk2c8 & ~2u) | 2u;
            }
            if (!(hero->m_unk1258 <= threshold)) {  // ble
                m_unk2c8 &= ~2u;
            } else if (hero->GetPartnerHero()->m_unk1258 > threshold) {
                m_unk2c8 &= ~2u;
            }
        }
    }
    CKHkS08Hero* lastSecond = static_cast<CKHkS08Hero*>(m_apHeros[1]);
    CKHkS08Hero* lastFirst = static_cast<CKHkS08Hero*>(m_apHeros[0]);
    lastFirst->m_unk118d = 0;
    lastSecond->m_unk118d = 0;
    // The answers are not used (0x00342fa8).
    if ((lastFirst->ShouldStayClimbing() != 0 || (lastFirst->m_unk354 & 0x40000u) == 0) &&
        (lastFirst->m_unk368 & 0x80u) == 0) {
        lastSecond->ShouldStayClimbing();
    }
}

// 0x002cb280 CKGrpS08Hero_UpdateHeroSpeechAnims_maybe: a hero with a speaker (+0x1a0) talks on its inner speech layer
// (the group's vt+0x170 per hero; vt+0x174 the speech animation). LVL010's heroes have no such layer (0xff).
void CKGrpS08Hero::UpdateHeroSpeechAnims(IKTime*) {
    const uint8_t count = GetHeroCount();  // vt+0xf4 (vt+0x174 is asked first; its answer only matters below)
    for (uint32_t i = 0; i < count; ++i) {
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(m_apHeros[i]);
        const uint8_t layer = GetActiveInnerBlendSlot(static_cast<uint8_t>(i));  // vt+0x170
        if (hero->m_unk1a0 == nullptr || static_cast<int8_t>(layer) == -1) continue;
        // STUB(C2.8: speech): the speech animation played, advanced or faded out on the layer
        // (CKLocSpeaker_IsCurrentSekensSpeaker_maybe, PlayAnimOnInnerBlender, AdvanceInnerBlenderAnimTime) and the
        // layer's AdvanceInactiveTrack.
        DOTD_STUB_ONCE("CKGrpS08Hero_UpdateHeroSpeechAnims_maybe 0x2cb280: speech layer (C2.8)");
    }
}

// 0x002ce888 CKGrpS08Hero_UpdateFlightAltitudeGap_maybe: with two players and one of them flying (neither climbing
// nor on +0x13d8) the higher one's ground level (+0xac8, which one +0xacc); a flying hero above a climbing one sets it
// too; else 0 / 0xff.
void CKGrpS08Hero::UpdateFlightAltitudeGap() {
    const float level = m_unk200;
    CKHkS08Hero* second = static_cast<CKHkS08Hero*>(m_apHeros[1]);
    CKHkS08Hero* first = static_cast<CKHkS08Hero*>(m_apHeros[0]);
    if (m_ui8ControlledHeroCount == 2 && (first->IsFlyingMovementMode1() != 0 || second->IsFlyingMovementMode1() != 0) &&
        first->m_unk13d8 == 0 && first->ShouldStayClimbing() == 0 && second->m_unk13d8 == 0 &&
        second->ShouldStayClimbing() == 0) {
        const float firstHeight = first->IsFlyingMovementMode1() == 0 ? first->GetHeightAboveGround() : first->m_unk1458;
        const float secondHeight = second->IsFlyingMovementMode1() == 0 ? second->GetHeightAboveGround() : second->m_unk1458;
        const float firstLevel = first->m_unk550 - firstHeight;
        const float secondLevel = second->m_unk550 - secondHeight;
        if (firstLevel <= secondLevel) {
            m_unkac8 = secondLevel;
            m_unkacc = 0;
        } else {
            m_unkac8 = firstLevel;
            m_unkacc = 1;
        }
        return;
    }
    if ((first->ShouldStayClimbing() == 0 && first->m_unk13d8 == 0) || second->IsFlyingMovementMode1() == 0) {
        if ((second->ShouldStayClimbing() != 0 || first->m_unk13d8 != 0) && first->IsFlyingMovementMode1() != 0) {
            const float gap = second->m_unk550 - level;
            if (first->m_unk550 - first->m_unk1458 < gap) {
                m_unkac8 = gap;
                m_unkacc = 0;
                return;
            }
        }
    } else {
        const float gap = first->m_unk550 - level;
        if (second->m_unk550 - second->m_unk1458 < gap) {
            m_unkac8 = gap;
            m_unkacc = 1;
            return;
        }
    }
    m_unkac8 = 0.0f;
    m_unkacc = 0xff;
}
