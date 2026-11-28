// Reconstructed original translation unit: 0x2f8520-0x2fc530 (GAME_TOC1, main_toc1), 34 functions, 27 live.
// Primary class: CKHkS08Hero  key 0x25c2  category Hook  size 0x1e00  vtable 0xb22c98
// Other owners: Vec3 (2), Angle (1), Math (1), GroundProbe (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2f8520  Angle_StepTowardInDirection_maybe
//   [ ] 0x2f85a8  FUN_002f85a8  [dead]
//   [ ] 0x2f85d8  Math_SpringDamperVelocityDelta_maybe  [dead]
//   [x] 0x2f85f0  CKHkS08Hero_GetByte1679_maybe
//   [x] 0x2f85f8  CKHkS08Hero_GetPartnerHero_maybe
//   [ ] 0x2f8620  KStub_ReturnFloat0_2f8620  [dead]
//   [x] 0x2f8628  CKHkS08Hero_PartnerShouldStayClimbing
//   [x] 0x2f8678  CKHkS08Hero_vf174
//   [x] 0x2f86b8  StaticInitAndDestruction_2f86b8  (the two file statics at the end)
//   [ ] 0x2f86e8  _GLOBAL__D_2f86e8
//   [ ] 0x2f86f8  _GLOBAL__I_2f86f8
//   [x] 0x2f8708  CKHkS08Hero_vf178
//   [x] 0x2f87e8  CKHkS08Hero_IsPartnerClimbFlagSet_maybe
//   [x] 0x2f8818  CKHkS08Hero_GetMass_maybe
//   [x] 0x2f8958  FUN_002f8958
//   [x] 0x2f8a08  CKHkS08Hero_ResetMovementFromFrame_maybe
//   [x] 0x2f94b0  CKHkS08Hero_GetMaxGroundSpeed_maybe
//   [x] 0x2f94d0  CKHkS08Hero_GetClimbSpeed_maybe
//   [x] 0x2f9540  CKHkS08Hero_UpdateSlopeAngleAndFlagEC8Bit24_maybe
//   [x] 0x2f96c8  CKHkS08Hero_FollowDynamicGround_maybe
//   [x] 0x2f9bd8  CKHkS08Hero_BlendClimbAttachMatrix_maybe
//   [ ] 0x2f9fa0  KStub_Nop_2f9fa0  [dead]
//   [x] 0x2f9fa8  CKHkS08Hero_HandleClimbZoneContact_maybe
//   [x] 0x2fa6a8  GroundProbe_ComputeRadialAverageNormal_maybe
//   [x] 0x2fa928  CKHkS08Hero_PlayFootstepSounds_maybe
//   [x] 0x2fbbf8  Vec3_AngleBetween
//   [x] 0x2fbd78  Vec3_TiltUpVectorAroundLocalX_maybe
//   [x] 0x2fbfc0  CKHkS08Hero_UpdateBodyTiltSprings_maybe
//   [x] 0x2fc1b0  CKHkS08Hero_IsComboKindFlagSet
//   [x] 0x2fc208  CKHkS08Hero_IsGrabComboKind  (CKHkS08Hero.h)
//   [x] 0x2fc228  CKHkS08Hero_IsAbilityActive
//   [ ] 0x2fc248  FUN_002fc248  [dead]
//   [ ] 0x2fc250  CKHkS08Hero_IsObjectInTargetKindMask_maybe  [dead]
//   [ ] 0x2fc520  CKHkS08Hero_GetFlagEC8Bit7_maybe  [dead]
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/hooks/CKHkClimbZone.h"
#include "k2000/math/Quat.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/ICollisionMesh.h"
#include <cstring>
#include "crt/xatan.h"
#include "k2000/hooks/GroundContact.h"
#include "k2000/math/Math.h"
#include "k2000/math/Vec3.h"
#include "k2000/misc/Mat4.h"
#include "crt/ppc_ops.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/core/Stub.h"
#include "k2000/graphical/animation/CAnimationManager.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/IKGrpHero.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/dictionaries/CAnimationDictionary.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/graphical/animation/CKBlenderController.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/system/IKTime.h"
#include <cmath>

// 0x002f8a08 CKHkS08Hero_ResetMovementFromFrame_maybe: the movement state starts from the scene node's frame (its
// direction vectors and position); `flag` also selects the dragon's HUD panel element.
void CKHkS08Hero::ResetMovementFromFrame(int32_t flag) {
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    m_unk12a0 = frame->modelling.at.x;
    m_unk1288 = frame->modelling.at.x;
    m_unk1290 = frame->modelling.at.z;
    m_unk128c = frame->modelling.at.y;
    m_unk12a8 = frame->modelling.at.z;
    m_unk12a4 = frame->modelling.at.y;
    m_unk1507 = 0;
    m_unk135c = frame->modelling.at.x;
    m_unk1364 = frame->modelling.at.z;
    m_unk1360 = frame->modelling.at.y;
    m_unk1368 = frame->modelling.right.x;
    m_unk1370 = frame->modelling.right.z;
    m_unk136c = frame->modelling.right.y;
    m_ui8MovementMode = 0;
    m_unkec4 &= 0xfffffffeu;
    m_unk127c = 0.0f;
    m_unk1284 = 0.0f;
    m_unk1280 = 0.0f;
    m_unk12e4 = 1.57079637f;
    m_unk161c = 1;
    m_unk1676 = 0;
    m_unk180c = 0;
    m_unk1810 = 0;
    m_unk1811 = 0;
    m_unk12d8 = 0;
    m_unk12e0 = 0;
    m_unk12dc = 0;
    m_unk12e8 = 0;
    m_unk12ec = 0;
    m_unk137c = 0;
    m_unk1504 = 0;
    m_unk161f = 0;
    m_unk1630 = 0;
    m_unk1634 = 0;
    m_unk1628 = 0;
    m_unk1627 = 0;
    m_unk1626 = 0;
    m_unk1679 = 0;
    m_unk1677 = 0;
    m_pCurrentClimbZone = 0;
    m_unk1698 = 0;
    m_unk169c = 0;
    m_pHeldClimbZone = 0;
    m_unk16a0 = 0;
    m_unk16a4 = 0;
    m_unk16a8 = 0;
    m_unk16ac = 0;
    m_unk1678 = 0;
    m_unk16fc = 0;
    m_unk167a = 0;
    m_unk167b = 0;
    m_unk167c = 0;
    m_unk168c = 0;
    m_unk168d = 0;
    m_unk168e = 0;
    m_unk1629 = 0;
    m_unk1675 = 0;
    m_unk167d = 0;
    m_unk13d3 = 0;
    m_unk13b4.x = 0.0f;
    m_unk13b4.y = 1.5f;  // 0x3fc00000
    m_unk13b4.z = 0.0f;
    m_unk1838 = 0;
    m_unk1518 = 0;
    m_unk1534 = 0;
    m_unk1538 = 0;
    m_unk153c = 0;
    m_unk1570 = m_unkd24;
    m_unk156c = m_unkd28;
    m_unk1578 = 0.0f;
    m_unk1580 = 0.0f;
    m_unk157c = 0.0f;
    m_unk1574 = 0;
    m_unk1584 = 0;
    m_unk1588 = 0;
    m_unk1550 = m_unkd24;
    m_unk154c = m_unkd40;
    m_unk1558 = 0.0f;
    m_unk1560 = 0.0f;
    m_unk155c = 0.0f;
    m_unk1568 = 0;
    m_unk1554 = 0;
    m_unk1564 = 0;
    m_unk15b0 = m_unkd2c;
    m_unk15ac = m_unkd30;
    m_unk15b8 = 0.0f;
    m_unk15c0 = 0.0f;
    m_unk15bc = 0.0f;
    m_unk15c8 = 0;
    m_unk15b4 = 0;
    m_unk15c4 = 0;
    m_unk1590 = m_unkd2c;
    m_unk158c = m_unkd44;
    m_unk1598 = 0.0f;
    m_unk15a0 = 0.0f;
    m_unk159c = 0.0f;
    m_unk15a8 = 0;
    m_unk1594 = 0;
    m_unk15a4 = 0;
    m_unk15cc = 0;
    m_unk15d4 = 0.0f;
    m_unk15dc = 0.0f;
    m_unk15d8 = 0.0f;
    m_unk1274 = 200.0f;
    m_unk15ce = 0;
    m_unk15cf = 0;
    m_unk15cd = 0;
    m_unk15d0 = 0;
    m_unk15d1 = 0;
    m_unk15d2 = 0;
    m_unk1278 = 0;
    m_unk1668 = 0.0f;
    m_unk1670 = 0.0f;
    m_unk166c = 0.0f;
    m_bExternalDisplacementActive = 0;
    if (static_cast<IKGrpHero*>(m_pGrpHero)->m_ui8ControlledHeroCount < 2) {
        m_unkec4 = (m_unkec4 & 0xffbfffffu) | 0x400000u;
    }
    m_unk1268 = 0.0f;
    m_unk1270 = 0.0f;
    m_unk126c = 0.0f;
    m_unk1814 = 0;
    m_unk1813 = 0;
    m_unk1815 = 0;
    m_unk181c = frame->modelling.pos.x;
    m_unk1824 = frame->modelling.pos.z;
    m_unk1820 = frame->modelling.pos.y;
    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pCameraTargetNode);
    if (leaf->m_pParent != nullptr) leaf->m_pParent->RemoveChild(leaf);  // vt+0x78
    static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(leaf);  // vt+0x70
    leaf->SetLocalMatrix(&frame->modelling);                                // 0x000d0be8
    leaf->ForceWorldMatrixUpdate();                                         // vt+0x50
    m_unk1308 = 0;
    m_bTakeOffPending = 0;
    m_unk1812 = 0;
    m_unk1304 = 0;
    m_unk1305 = 0;
    if (flag != 0) {
        CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
        if (m_ui8Hero == 0) {
            manager->SelectSpyroHudPanelElement(0);  // after KStub_Nop_4fe310
        } else if (m_ui8Hero == 1) {
            manager->SelectCynderHudPanelElement(0);  // after KStub_Nop_4fe318
        }
    }
    m_unk12f4 = 4.0f;  // TOC1 +0x1f8c
    m_unk12f8 = 1.0f;  // TOC1 +0x1f78
    m_unk19b0 = 0xffff;
    m_unk19d8 = 0;
    m_unk19ac = 0;
    m_unk1434 = 0;
    m_unk1440 = 0;
    m_ui32HeroFlags354 = (m_ui32HeroFlags354 & 0x7fffffffu) | 0x80000000u;
    m_unk1228 = 4;
    m_unk1539 = 0;
    m_unk1530 = 0;
    m_unk1248 = 0.0f;
    m_unk1250 = 0.0f;
    m_unk124c = 0.0f;
    m_unk11cc = 0.0f;
    m_unk11d4 = 0.0f;
    m_unk11d0 = 0.0f;
    m_unk11d8 = 0;
    m_unk11e8 = 0;
    m_unk1258 = 0;
    m_unk1444 = 0;
    m_unk19e0 = 0;
    m_unk19e8 = 0;
    m_unk19f4 = nullptr;
    m_unk11c4 = 0;
    m_unk11f8 = 1.0f;
    m_unk164c = 0.0f;
    m_unk1654 = 0.0f;
    m_unk1650 = 0.0f;
    m_unk1658 = 0.0f;
    m_unk1660 = 0.0f;
    m_unk165c = 0.0f;
    m_unk1728 = 0.0f;
    m_unk1730 = 0.0f;
    m_unk172c = 0.0f;
    m_unk1734 = 0.0f;
    m_unk173c = 0.0f;
    m_unk1738 = 0.0f;
    m_unk1740 = 10;
    m_unk16f4 = 0;
    m_unk16f8 = 0;
    m_unk16f9 = 0;
    m_unk15e0 = 0.0f;
    m_unk15e4 = 0.0f;
    m_unk15e8 = 0.0f;
    m_unk15ec = 0;
    m_unk15f0 = 0.0f;
    m_unk15f4 = 0.0f;
    m_unk15f8 = 0.0f;
    m_unk15fc = 0;
    m_unk1600 = 0;
    m_unk1604 = 0.0f;
    m_unk1608 = 0.0f;
    m_unk160c = 0.0f;
    m_unk11ec = 0.0f;
    m_unk11f0 = 0.0f;
    m_unk11f4 = 0.0f;
    m_unk13d0 = 0;
    m_unk13cd = 0;
    m_unk13cc = 0;
    m_unk13ce = 0;
    m_unk1448 = 0;
    m_unk1839 = 0;
    m_unk144c.x = 0.0f;
    m_unk144c.y = 0.0f;
    m_unk144c.z = 0.0f;
    m_unk17fc = 0.0f;
    m_unk1800 = 0.0f;
    m_unk1804 = 0.0f;
    m_unk1a0c = 0.0f;
    m_unk1a10 = 0.0f;
    m_unk11dc = 0.0f;
    m_unk11e4 = 0.0f;
    m_unk11e0 = 0.0f;
    m_unk174c = m_unkd08;
    m_unk1748 = 0;
    m_unk1198 = 0;
    m_unk11c8 = 0;
    m_gcContact11FC.m_eContactStatus = 3;
    m_gcContact11FC.m_i32FaceIndex = -1;
    m_gcContact11FC.m_ui8SectorNumber = 0;
    m_gcContact11FC.m_pGround = nullptr;
    m_unk11a8 = 0.0f;
    m_unk11b0 = 0.0f;
    m_unk11ac = 0.0f;
    m_unk11b4 = 0.0f;
    m_unk11bc = 0.0f;
    m_unk11b8 = 0.0f;
    m_unk13d8 = 0;
    m_unk13d9 = 0;
    m_unk1418 = m_unk9d8;
    m_unk1414 = m_unk9d4;
    m_unk1420 = 0.0f;  // the up vector 0x00c50d40 (0, 1, 0)
    m_unk1428 = 0.0f;
    m_unk1424 = 1.0f;
    m_unk1430 = 0;
    m_unk141c = 0;
    m_unk142c = 0;
    m_unk13f8 = 0;
    m_unk13f4 = 1.0f;
    m_unk1400 = 0.0f;
    m_unk1408 = 0.0f;
    m_unk1404 = 0.0f;
    m_unk1410 = 0;
    m_unk13fc = 0;
    m_unk140c = 0;
    m_unk13e8 = 0.0f;
    m_unk13f0 = 0.0f;
    m_unk13ec = 0.0f;
    m_unk13dc = 0.0f;
    m_unk13e4 = 0.0f;
    m_unk13e0 = 0.0f;
    m_unk143c = 0;
    m_unk1610 = 0;
    m_unk1614 = 0;
    m_unk1615 = 0;
    m_unk182c = 0;
    m_unk1438 = 0;
    // The first animation of the dictionary restarts on the inactive blend slot.
    // The dictionary entry is the animation pointer in the original (null for none); dotd keeps the word.
    RtAnimAnimation* firstAnimation = CAnimationManager_GetAnimation(
        static_cast<uint32_t>(static_cast<CAnimationDictionary*>(m_pAnimDico)->m_apAnimations[0]));
    if (firstAnimation != nullptr) {
        AnimBlendSlot* slot = GetInactiveAnimBlendSlot();  // 0x00301528
        slot->m_unk14 = 0;
        CKBlenderController* blender = static_cast<CKBlenderController*>(slot->m_pController);
        if (blender != nullptr) blender->m_unk58 = slot->m_unk10 != 0 ? 1.0f : 0.0f;  // TOC1 +0x1f78
        static_cast<CKAnmKeyFrameController*>(blender->m_apControllers[slot->m_unk10])->SetAnim(0.0f, firstAnimation, false);  // 0x0007ab20
    }
    m_unk368 = (m_unk368 & 0xfffffdffu) | 0x200u;
    m_fFlightHeight = 0;
    m_unk1460 = 0;
    m_unk145c = 1.0f;
    m_unk1468 = 0.0f;
    m_unk146c = 0.0f;
    m_unk1470 = 0.0f;
    m_unk1478 = 0;
    m_unk1464 = 0;
    m_unk1474 = 0;
    m_unk1750 = -1.0f;  // TOC1 +0x1f6c
    m_unk1665 = 5;
    m_unk1754 = 0;
    m_unk11c0 = 0;
    m_unk1758 = 1.0f;
    m_unk175c = 0;
    m_unk1764 = 0.0f;
    m_unk176c = 0.0f;
    m_unk1768 = 0.0f;
    m_unk1760 = 0;
    m_unk1774 = 0;
    m_unk1770 = 0;
    m_PFCharacter.m_fMaxStepRise = 2.5f;  // TOC1 +0x1f94 (m_unk3ec)
    m_PFCpnt.m_CharacterType.m_bits = m_PFCharacter.m_bits;
    m_PFCpnt.m_CharacterType.m_fRadius = m_PFCharacter.m_fRadius;
    m_PFCpnt.m_CharacterType.m_fMaxStepHeight = m_PFCharacter.m_fMaxStepHeight;
    m_PFCpnt.m_CharacterType.m_fMaxStepRise = m_PFCharacter.m_fMaxStepRise;
    m_unk1a08 = 0;
    // The game manager's record of this hero (+0xdf8 + hero * 0x20): the two zero vectors, two bytes and a word.
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
    uint32_t* record = &manager->m_unkDF4[1 + m_ui8Hero * 8];
    for (uint32_t k = 0; k < 6; ++k) record[k] = 0;  // 0.0f x 6
    reinterpret_cast<uint8_t*>(&record[6])[0] = 0;  // +0xe10
    reinterpret_cast<uint8_t*>(&record[6])[1] = 0;  // +0xe11
    record[7] = 0;
    ClearMovementFloatFields();  // 0x002db9d8
    m_unk1380 = 0;
    m_unk178c = 0;
    m_unk118e = 0;
    m_unk1398 = 0.0f;
    m_unk13a0 = 0.0f;
    m_unk139c = 0.0f;
    m_unk1195 = 0;
    m_unk118d = 0;
    m_unk1194 = 0;

}

// 0x002f85f0 CKHkS08Hero_GetByte1679_maybe
uint8_t CKHkS08Hero::GetByte1679() { return m_unk1679; }

// 0x002f85f8 CKHkS08Hero_GetPartnerHero_maybe: the group's other hero (index 1 for hero 0, else index 0).
CKHkS08Hero* CKHkS08Hero::GetPartnerHero() {
    IKGrpHero* group = static_cast<IKGrpHero*>(m_pGrpHero);
    return static_cast<CKHkS08Hero*>(group->m_apHeros[m_ui8Hero == 0 ? 1 : 0]);
}

// 0x002f8628 CKHkS08Hero_PartnerShouldStayClimbing: ShouldStayClimbing of the partner.
uint8_t CKHkS08Hero::PartnerShouldStayClimbing() { return GetPartnerHero()->ShouldStayClimbing(); }

// 0x002f8678 CKHkS08Hero_vf174 (vt+0x174): the frame's position adjustment (+0x1268) becomes the previous one
// (+0x5c0) and starts again from the zero vector (TOC +0x1f64).
void CKHkS08Hero::Vf174() {
    m_unk5c0 = m_unk1268;
    m_unk5c8 = m_unk1270;
    m_unk5c4 = m_unk126c;
    m_unk1270 = kHeroZeroVector.z;
    m_unk1268 = kHeroZeroVector.x;
    m_unk126c = kHeroZeroVector.y;
}

// 0x002f8708 CKHkS08Hero_vf178 (vt+0x178): IKHkHero_StartJumpOrFall_maybe unless +0xec8 bit 27; an AI partner of a group with flag
// 0x80, with +0x1538 below 2 and +0x354 bit 1, asked with `flag` gets +0x358 bit 20.
void CKHkS08Hero::Vf178(IKTime* clock, uint8_t flag) {
    if ((m_unkec8 & 0x8000000u) == 0) {
        StartJumpOrFall(clock, flag);  // 0x0035e3e8 IKHkHero_StartJumpOrFall_maybe
    }
    if (m_ui8Hero == m_ui8TrackedLeader) return;
    if ((static_cast<CKGrpS08Hero*>(m_pGrpHero)->m_ui32PairStateFlags & 0x80u) == 0) return;
    if (m_unk1538 > 1) return;
    if (flag == 0) return;
    if ((m_ui32HeroFlags354 & 2u) == 0) return;
    m_ui32HeroFlags358 = (m_ui32HeroFlags358 & 0xffefffffu) | 0x100000u;
}

// 0x002f87e8 CKHkS08Hero_IsPartnerClimbFlagSet_maybe: the partner's +0x1679.
uint8_t CKHkS08Hero::IsPartnerClimbFlagSet() { return GetPartnerHero()->m_unk1679; }

// 0x002fc228 CKHkS08Hero_IsAbilityActive: +0x1ac5 or +0x1ac6.
uint8_t CKHkS08Hero::IsAbilityActive() {
    if (m_unk1ac5 != 0) return 1;
    return m_unk1ac6;
}

// 0x002f9540 CKHkS08Hero_UpdateSlopeAngleAndFlagEC8Bit24_maybe: the slope of the ground normal (+0x11c4, degrees from
// Math_Acosf of +0x568 clamped to [-1, 1]) and the run-start flag +0xec8 bit 24 (the push +0x127c zeroed): set when the
// speed +0x1378 is not above +0xbcc without +0xec4 bit 17, +0x12d0 is below +0xbd0, the hero is on the ground, no combo
// runs, and (for the partner) the hero group's gap (+0x314 + +0x318) is below its tether spring radius.
void CKHkS08Hero::UpdateSlopeAngleAndFlagEC8Bit24() {
    float cosine = m_unk568;
    if (cosine <= -1.0f) {
        cosine = -1.0f;  // TOC +0x1f6c
    } else if (cosine >= 1.0f) {
        cosine = 1.0f;   // TOC +0x1f78
    }
    m_unk11c4 = crt::Acosf(cosine) * 57.2957801818847656f;  // TOC +0x1f98
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    float gapA;
    float gapB;
    std::memcpy(&gapA, &group->m_unk2d4[16], 4);  // +0x314
    std::memcpy(&gapB, &group->m_fHero1ToMidDist, 4);      // +0x318
    bool start = m_unkbcc >= m_unk1378 && (m_unkec4 & 0x20000u) == 0 && !(m_unk12d0 >= m_unkbd0) &&
                 (m_ui32HeroFlags354 & 1u) == 0 && IsAnyComboKindActive() == 0;
    if (start && m_ui8TrackedLeader != m_ui8Hero) {
        const float radius = group->GetTetherSpringRadius();  // 0x002ce520
        start = !(gapB + gapA >= radius);
    }
    if (!start) {
        m_unkec8 &= ~0x1000000u;
        return;
    }
    m_unk127c = kHeroZeroVector.x;  // TOC +0x1f64
    m_unk1284 = kHeroZeroVector.z;
    m_unk1280 = kHeroZeroVector.y;
    m_unkec8 = (m_unkec8 & ~0x1000000u) | 0x1000000u;
}

// 0x002f9fa8 CKHkS08Hero_HandleClimbZoneContact_maybe: the climb zone the hero is in (+0x1694) lets it go when its time
// runs out, then a collision with a climb zone's volume (the owner a CKHkClimbZone, 0x1602) enters or keeps the zone.
// The hero's main sphere (+0x54[1]) in a zone's box makes it the hero's zone (+0x1694, its attach target +0x16d8 and the
// node's matrix +0x16d4) when it is closer than the current target and the partner (if climbing) stays in reach (or it
// is the zone of last frame); the climbing volume (+0x54[8]) touching a zone that faces like the current one (dot > 0.99)
// lists it in front (+0x16b0) or behind (+0x16bc) the hero for the side moves.
void CKHkS08Hero::HandleClimbZoneContact(ICollision*, IKBoundingVolume* own, IKBoundingVolume* other) {
    const int32_t key = CKHkClimbZone::ClimberKey(this);
    if (m_pCurrentClimbZone != nullptr) {
        CKHkClimbZone* current = m_pCurrentClimbZone;
        if (current->m_fUnk58 >= 0.0f && current->m_fUnkC0 >= m_unk88c + current->m_fUnk58) {  // TOC +0x1f4c
            m_unk1629 = 1;
            current->RemoveClimber(key);  // 0x00457180
        }
    }
    IKSerializable* owner = other->m_pOwner;
    if (owner == nullptr || owner->IsKindOfClass(0x1602) == 0) return;  // vt+0x08
    CKHkClimbZone* zone = static_cast<CKHkClimbZone*>(owner);
    CKHkS08Hero* partner = GetPartnerHero();  // the group's other hero, as the original indexes it
    if (static_cast<IKBoundingVolume*>(m_apBoundings[1]) == own) {  // 0x0030cac0 CKHkS08Hero_GetBoundingSphere1_maybe
        m_unk1676 = 1;
        bool closer = true;
        if (m_pCurrentClimbZone != nullptr) {
            CVector3 probe{m_unk54c, m_unk550, m_unk554};
            alignas(16) CMatrix34 attach;
            zone->GetAttachMatrix(&probe, &attach, 0);  // 0x00458a88
            const CMatrix34& target = *m_unk16d8;
            const float ty = m_unk550 - target.m_pos.y;
            const float tx = m_unk54c - target.m_pos.x;
            const float tz = m_unk554 - target.m_pos.z;
            const float ay = m_unk550 - attach.m_pos.y;
            const float ax = m_unk54c - attach.m_pos.x;
            const float az = m_unk554 - attach.m_pos.z;
            const float toTarget = std::sqrt(ppc::fmadds(tz, tz, ppc::fmadds(tx, tx, ty * ty)));  // Math_Sqrtf
            const float toAttach = std::sqrt(ppc::fmadds(az, az, ppc::fmadds(ax, ax, ay * ay)));
            closer = toTarget > toAttach;
        }
        CVector3 probe{m_unk54c, m_unk550, m_unk554};
        alignas(16) CMatrix34 attach;
        bool reach = true;
        if (zone->GetAttachMatrix(&probe, &attach, key) != 0 && partner->ShouldStayClimbing() != 0 &&
            (m_unkec4 & 0x400000u) == 0) {  // 0x00342fa8
            const float py = attach.m_pos.y - partner->m_unk550;
            const float px = attach.m_pos.x - partner->m_unk54c;
            const float pz = attach.m_pos.z - partner->m_unk554;
            const float distance = std::sqrt(ppc::fmadds(pz, pz, ppc::fmadds(px, px, py * py)));
            if (!(distance <= static_cast<CKGrpS08Hero*>(m_pGrpHero)->m_unk108) && m_pHeldClimbZone != zone) reach = false;  // 0x002ce518
        }
        if (closer && reach) {
            m_pCurrentClimbZone = zone;
            m_unk16a0 = zone->m_pUnk4C;
            if (zone == nullptr) {
                m_unk1677 = 0;
            } else {
                CVector3 point{m_unk54c, m_unk550, m_unk554};
                zone->GetAttachMatrix(&point, m_unk16d8, key);
                *m_unk16d4 = *reinterpret_cast<const CMatrix34*>(&static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling);
            }
        }
    }
    float facing = 0.0f;  // TOC +0x1f4c
    if (m_pCurrentClimbZone != nullptr) {
        const CVector3& a = zone->NodeLtm().m_at;
        const CVector3& b = m_pCurrentClimbZone->NodeLtm().m_at;
        facing = ppc::fmadds(a.z, b.z, ppc::fmadds(a.x, b.x, a.y * b.y));
    }
    if (static_cast<IKBoundingVolume*>(GetCollisionVolume8()) != own || m_pCurrentClimbZone == zone || (m_unkec4 & 0x20000000u) != 0 ||
        (m_unkec4 & 0x40000000u) != 0 || !(facing > 0.99f)) {  // 0x0030ce30; TOC +0x1fa4
        return;
    }
    const float px = m_unk54c;
    const float py = m_unk550;
    const float pz = m_unk554;
    const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
    const CVector3 right{frame->modelling.right.x, frame->modelling.right.y, frame->modelling.right.z};
    const CVector3 base = zone->NodeLtm().m_pos;
    CVector3 probe{px, py, pz};
    alignas(16) CMatrix34 attach;
    if (zone->GetAttachMatrix(&probe, &attach, key) != 0 && partner->ShouldStayClimbing() != 0 &&
        (m_unkec4 & 0x400000u) == 0) {
        const float qy = attach.m_pos.y - partner->m_unk550;
        const float qx = attach.m_pos.x - partner->m_unk54c;
        const float qz = attach.m_pos.z - partner->m_unk554;
        const float distance = std::sqrt(ppc::fmadds(qz, qz, ppc::fmadds(qx, qx, qy * qy)));
        if (!(distance <= static_cast<CKGrpS08Hero*>(m_pGrpHero)->m_unk108)) return;
    }
    const float side = ppc::fmadds(base.z - pz, right.z, ppc::fmadds(base.x - px, right.x, (base.y - py) * right.y));
    CKHkClimbZone** list = m_unk16b0;
    uint32_t* count = &m_unk16b8;
    if (side <= 0.0f) {
        list = m_unk16bc;
        count = &m_unk16c4;
    }
    const uint32_t index = *count;
    *count = index + 1;
    if (index < 2) {
        list[index] = zone;
    } else {
        // BUG(original): a third zone in one frame is stored past the two slots (over the count word); not reproduced.
        DOTD_STUB_ONCE("CKHkS08Hero_HandleClimbZoneContact_maybe: a third climb zone in one frame (BUG(original): overflow)");
    }
}

// 0x002f94d0 CKHkS08Hero_GetClimbSpeed_maybe: the climbing speed: +0xc64 on a ceiling or a frame (+0x1744); on a wall
// +0xc50 / +0xe5c going up (+0x378 > 0) and +0xc54 / +0xc58 down (+0xec8 bit 16 the second).
float CKHkS08Hero::GetClimbSpeed() {
    if (m_unk1744 != 0) return m_unkc64;
    if (m_unk378 > 0.0f) return (m_unkec8 & 0x10000u) == 0 ? m_unkc50 : m_unke5c;
    return (m_unkec8 & 0x10000u) != 0 ? m_unkc58 : m_unkc54;
}

// 0x002f9bd8 CKHkS08Hero_BlendClimbAttachMatrix_maybe: the mount blend: the rotation slerped from `from` to `to` by the
// smoothed blend (1 - +0x1750 / +0x1754; +0x1750 clamped at 0), the position from `from`'s to the attach target's
// (+0x16d8, +0x794 out along its up).
CMatrix34 CKHkS08Hero::BlendClimbAttachMatrix(const CMatrix34* from, const CMatrix34* to) {
    alignas(16) CMatrix34 a = *from;
    alignas(16) CMatrix34 b = *to;
    float qa[4];
    float qb[4];
    Quat_FromMatrix(qa, reinterpret_cast<const float*>(&a));  // 0x002420f8
    Quat_FromMatrix(qb, reinterpret_cast<const float*>(&b));
    float t = m_unk1750 / m_unk1754;
    if (t < 0.0f) {  // TOC +0x1f4c
        m_unk1750 = 0.0f;
        t = 1.0f;  // TOC +0x1f78
    } else {
        t = 1.0f - t;
    }
    // TocBridge_Math_SmoothStep_maybe 0x98f350 -> 0x582bc8: 3t^2 - 2t^3 inside (0, 1).
    const float s = Math_SmoothStep(t);
    float q[4];
    Quat_Slerp(s, q, qa, qb);  // 0x00242728
    alignas(16) CMatrix34 rotation;
    // 0x00241d78 Quat_ToMatrixNormalizing_maybe (inline here: the rotation of q over its squared length, flags 3).
    {
        const float y = q[1], x = q[0], z = q[2], w = q[3];
        float n = y * y;
        n = ppc::fmadds(x, x, n);
        n = ppc::fmadds(z, z, n);
        n = ppc::fmadds(w, w, n);
        const float k = 2.0f / n;
        const float zs = z * k, xs = x * k, ys = y * k;
        const float zz = z * zs, xx = x * xs, yy = y * ys, xz = z * xs, yz = y * zs, wx = w * xs, wz = w * zs, xy = x * ys,
                    wy = w * ys;
        rotation.m_pos = {0.0f, 0.0f, 0.0f};
        rotation.m_ui32Flags = 3;
        rotation.m_at.y = yz - wx;
        rotation.m_up.z = wx + yz;
        rotation.m_up.x = xy - wz;
        rotation.m_at.x = wy + xz;
        rotation.m_right.y = wz + xy;
        rotation.m_right.z = xz - wy;
        rotation.m_up.y = 1.0f - (xx + zz);
        rotation.m_at.z = 1.0f - (xx + yy);
        rotation.m_right.x = 1.0f - (yy + zz);
    }
    const CMatrix34& target = *m_unk16d8;
    const float out = m_unk794;
    const CVector3 end{ppc::fmadds(target.m_up.x, out, target.m_pos.x), ppc::fmadds(target.m_up.y, out, target.m_pos.y),
                       ppc::fmadds(target.m_up.z, out, target.m_pos.z)};
    const CVector3 start = a.m_pos;
    // 0x003342c0 Vec3_LerpByRangeClamped_maybe (0, 1, s): `start` to `end`.
    CVector3 position;
    if (s >= 0.0f && s <= 1.0f) {
        position = {ppc::fmadds(s, end.x - start.x, start.x), ppc::fmadds(s, end.y - start.y, start.y),
                    ppc::fmadds(s, end.z - start.z, start.z)};
    } else if (1.0f < s) {
        position = end;
    } else if (0.0f <= s) {
        position = kHeroZeroVector;
    } else {
        position = start;
    }
    rotation.m_pos = position;
    rotation.m_ui32Flags &= 0xfffdffffu;
    return rotation;
}

// 0x002f8520 Angle_StepTowardInDirection_maybe: `current` turned towards `target` by speed * dt radians the short way
// round forward (`backwards` 0) or backward, wrapped into [0, 2*pi]; the target itself once within the step.
float Angle_StepTowardInDirection(float current, float target, float speed, float dt, uint32_t backwards) {
    constexpr float kTwoPi = 6.28318548202514648f;  // TOC1 +0x1f48
    if (current == target) return current;
    float difference = target - current;
    const float step = speed * dt;
    if (difference < 0.0f) difference = difference + kTwoPi;
    if (backwards != 0) {
        if (kTwoPi - difference < step) return target;
        const float next = current - step;
        if (!(next < 0.0f)) return next;
        return next + kTwoPi;
    }
    if (difference < step) return target;
    const float next = current + step;
    if (!(next >= kTwoPi)) return next;
    return next - kTwoPi;
}

// 0x002f8818 CKHkS08Hero_GetMass_maybe: the base mass +0x1258 times the factor of the movement mode (on the ground
// +0xe58 unless +0xec4 bit 24, flying +0xe60 with +0x13d8, climbing +0xe68), plus +0xe54 (with +0xecc bit 11: the
// remap of +0x388 over [0, +0x948] to [+0xe54, +0x950], clamped to that range), plus +0x1b2c with +0xed4 bit 0.
float CKHkS08Hero::GetMass() {
    float mass = m_unk1258;
    const int8_t mode = static_cast<int8_t>(GetMovementMode());  // 0x003401b8
    if (mode == 1) {
        if (m_unk13d8 != 0) mass = mass * m_unke60;
    } else if (mode == 2) {
        mass = mass * m_unke68;
    } else if (mode == 0) {
        if ((m_unkec4 & 0x1000000u) == 0) mass = mass * m_unke58;
    }
    float extra = m_unke54;
    if ((m_unkecc & 0x800u) != 0) {
        const float remapped = Math_RemapClamped(0.0f, m_unk948, AsF32(m_unk388), m_unke54, m_unk950);  // 0x00333618
        const float low = m_unke54;
        const float high = m_unk950;
        if (remapped <= low) {
            extra = low;
        } else if (remapped >= high) {
            extra = high;
        } else {
            extra = remapped;
        }
    }
    float armor = 0.0f;  // TOC1 +0x1f4c
    if ((m_ui32StatusFlagsED4 & 1u) != 0) armor = m_fExtraMass;
    return armor + (mass + extra);
}

// 0x002f8958 FUN_002f8958 (CKHkS08Hero_BlendGroundNormals_maybe): (a * weight + b * count) / (2 * weight), each part
// added to the zero vector first (0x00c50d64).
CVector3 CKHkS08Hero::BlendGroundNormals(const CVector3* a, const CVector3* b, float weight, float count) {
    const float scale = 1.0f / (weight + weight);  // TOC1 +0x1f78
    const float ax = weight * (kHeroZeroVector.x + a->x);
    const float ay = weight * (kHeroZeroVector.y + a->y);
    const float az = weight * (kHeroZeroVector.z + a->z);
    const float sx = ppc::fmadds(kHeroZeroVector.x + b->x, count, ax);
    const float sy = ppc::fmadds(kHeroZeroVector.y + b->y, count, ay);
    const float sz = ppc::fmadds(kHeroZeroVector.z + b->z, count, az);
    return CVector3{scale * sx, scale * sy, scale * sz};
}

// 0x002f94b0 CKHkS08Hero_GetMaxGroundSpeed_maybe
float CKHkS08Hero::GetMaxGroundSpeed() const { return (m_unkec8 & 0x4000000u) != 0 ? m_unk11f8 : m_unkaf4; }

// 0x002fa6a8 GroundProbe_ComputeRadialAverageNormal_maybe: `count` points around `center` at `radius` (the direction
// turned by i * 2*pi / count for the i-th), raised by `lift`, probed (GroundContact_ProbeGroundPoint); the (local) normals
// of the grounds found whose point is less than `maxDrop` above the centre are summed and the sum normalised.
CVector3 GroundProbe_ComputeRadialAverageNormal(const CVector3* center, const CVector3* direction, float radius, float lift,
                                                float maxDrop, int32_t count) {
    CVector3 sum = kHeroZeroVector;
    const float step = 6.28318548202514648f / static_cast<float>(static_cast<double>(count));  // TOC1 +0x1f48
    CGroundContactDatasInOut contact;
    for (int32_t i = 0; i != count; ++i) {
        contact.m_pGround = nullptr;
        contact.m_i32FaceIndex = -1;
        contact.m_eContactStatus = 3;
        contact.m_ui8SectorNumber = 0;
        CVector3 point;
        Vec3_GenerateRadialPointsXZ(step * static_cast<float>(static_cast<double>(i)), radius, center, direction, &point, 1,
                                    nullptr);
        point.y = point.y + lift;
        if (GroundContact_ProbeGroundPoint(&contact, &point, nullptr) && point.y - center->y < maxDrop) {
            sum.x = sum.x + contact.m_Normal.x;
            sum.y = sum.y + contact.m_Normal.y;
            sum.z = sum.z + contact.m_Normal.z;
        }
    }
    if (sum.x != kHeroZeroVector.x || sum.y != kHeroZeroVector.y || sum.z != kHeroZeroVector.z) {
        const float length = std::sqrt(ppc::fmadds(sum.z, sum.z, ppc::fmadds(sum.x, sum.x, sum.y * sum.y)));  // Math_Sqrtf
        if (length != 0.0f) {
            const float inv = 1.0f / length;  // TOC1 +0x1f78
            sum.z = inv * sum.z;
            sum.x = inv * sum.x;
            sum.y = inv * sum.y;
        }
    }
    return sum;
}

namespace {
// The normalisation of a vector in place the tilt code repeats (y*y, x fused, z fused; inverse length times each).
void NormaliseInPlace(CVector3* v) {
    const float length = std::sqrt(ppc::fmadds(v->z, v->z, ppc::fmadds(v->x, v->x, v->y * v->y)));  // Math_Sqrtf
    if (length == 0.0f) return;
    const float inv = 1.0f / length;  // TOC1 +0x1f78
    v->z = inv * v->z;
    v->x = inv * v->x;
    v->y = inv * v->y;
}
}  // namespace

// 0x002fbbf8 Vec3_AngleBetween: the angle (radians, Math_Acosf) between `a` and `b`, both normalised in place first;
// the cosine clamped to [-1, 1].
float Vec3_AngleBetween(CVector3* a, CVector3* b) {
    NormaliseInPlace(a);
    NormaliseInPlace(b);
    const float dot = ppc::fmadds(b->z, a->z, ppc::fmadds(b->x, a->x, b->y * a->y));
    if (dot <= -1.0f) return crt::Acosf(-1.0f);  // TOC1 +0x1f6c
    if (dot >= 1.0f) return crt::Acosf(1.0f);    // TOC1 +0x1f78
    return crt::Acosf(dot);
}

// 0x002fbd78 Vec3_TiltUpVectorAroundLocalX_maybe: `up` and `at` normalised (in place); the basis they make
// (Mat4_SetBasisFromUpAt) turned by `angle` radians about its x axis gives the new up; `up` when they make none.
CVector3 Vec3_TiltUpVectorAroundLocalX(float angle, CVector3* up, CVector3* at) {
    NormaliseInPlace(up);
    NormaliseInPlace(at);
    CMatrix34 basis;
    basis.m_pos = kHeroZeroVector;
    basis.m_right.x = 1.0f;
    basis.m_pos.x = 0.0f;
    basis.m_ui32Flags = 0x20003;
    basis.m_at.z = 1.0f;
    basis.m_up.y = 1.0f;
    basis.m_up.x = 0.0f;
    basis.m_right.z = 0.0f;
    basis.m_right.y = 0.0f;
    basis.m_at.y = 0.0f;
    basis.m_at.x = 0.0f;
    basis.m_up.z = 0.0f;
    basis.m_pos.z = 0.0f;
    basis.m_pos.y = 0.0f;
    if (!Mat4_SetBasisFromUpAt(&basis, up, at)) return *up;
    Mat4_RotateLocalXDeg(angle * 57.2957801818847656f, &basis);  // TOC1 +0x1f98
    return basis.m_up;
}

// 0x002fbfc0 CKHkS08Hero_UpdateBodyTiltSprings_maybe: two damped springs follow the target up's angles in the y / z
// (pitch: +0x137c, its speed +0x12e8, stiffness +0xab4, damping +0xab8) and x / y planes (roll: +0x12e4, +0x12ec, +0xabc,
// +0xac0), stepped by the frame's dt (+0x88c); the up vector is the Y axis tilted by the roll (less pi/2) about the
// Z axis' basis, then by the pitch about the X axis'. (`current` is not read.)
CVector3 CKHkS08Hero::UpdateBodyTiltSprings(const CVector3* /*current*/, const CVector3* target) {
    constexpr float kPi = 3.14159274101257324f;      // TOC1 +0x1fbc
    constexpr float kTwoPi = 6.28318548202514648f;   // TOC1 +0x1f48
    const CVector3 kAxisX{1.0f, 0.0f, 0.0f};         // 0x00c50d34 (TOC1 +0x1fc4)
    const CVector3 kAxisZ{0.0f, 0.0f, 1.0f};         // 0x00c50d4c (TOC1 +0x1fc0)
    float pitch = Vec3_GetAngleInYZPlane(target);
    if (pitch > kPi) pitch = pitch - kTwoPi;
    {
        const float position = m_unk137c;
        const float force = m_unkab4 * (position - pitch);
        const float speed = ppc::fmadds(ppc::fmsubs(m_unk12e8, -m_unkab8, force), m_unk88c, m_unk12e8);
        m_unk12e8 = speed;
        m_unk137c = ppc::fmadds(speed, m_unk88c, position);
    }
    float roll = Vec3_GetAngleInXYPlane(target);
    if (roll > kPi) roll = roll - kTwoPi;
    {
        const float position = m_unk12e4;
        const float force = m_unkabc * (position - roll);
        const float speed = ppc::fmadds(ppc::fmsubs(m_unk12ec, -m_unkac0, force), m_unk88c, m_unk12ec);
        m_unk12ec = speed;
        m_unk12e4 = ppc::fmadds(speed, m_unk88c, position);
    }
    CVector3 up = kHeroAxisY;  // TOC1 +0x1f90
    CVector3 tiltUp = up;
    CVector3 tiltAt = kAxisZ;
    up = Vec3_TiltUpVectorAroundLocalX(m_unk12e4 - 1.57079637050628662f, &tiltUp, &tiltAt);  // TOC1 +0x1f7c
    tiltUp = up;
    tiltAt = kAxisX;
    up = Vec3_TiltUpVectorAroundLocalX(m_unk137c, &tiltUp, &tiltAt);
    return up;
}

// 0x002f96c8 CKHkS08Hero_FollowDynamicGround_maybe
uint8_t CKHkS08Hero::FollowDynamicGround(IKTime* /*clock*/, IKSerializable* groundObject) {
    if (groundObject == nullptr || groundObject->GetClassID() != 0x13) return 0;  // vt+0x18
    ICollisionMesh* ground = static_cast<ICollisionMesh*>(groundObject);
    CMatrix34* last = m_unk16f0;
    if ((last->m_ui32Flags & 0x20003u) == 0x20003u) {
        *last = *ground->GetInvertedWorldMatrix();  // vt+0x54
        return 0;
    }
    CVector3 local;
    Mat4_TransformPoints(last, &local, reinterpret_cast<const CVector3*>(&m_unk54c), 1);
    CVector3 world;
    Mat4_TransformPoints(ground->GetWorldMatrix(), &world, &local, 1);  // vt+0x50
    m_unk54c = world.x;
    m_unk550 = world.y;
    m_unk554 = world.z;
    CSGMovable* node = static_cast<CSGMovable*>(m_pKGLObject);
    const RwFrame* frame = node->m_pRwFrame;
    CVector3 up;
    CVector3 right;
    CVector3 at;
    Mat4_TransformVectors(m_unk16f0, &local, reinterpret_cast<const CVector3*>(&frame->modelling.up), 1);
    Mat4_TransformVectors(ground->GetWorldMatrix(), &up, &local, 1);
    Mat4_TransformVectors(m_unk16f0, &local, reinterpret_cast<const CVector3*>(&frame->modelling.right), 1);
    Mat4_TransformVectors(ground->GetWorldMatrix(), &right, &local, 1);
    Mat4_TransformVectors(m_unk16f0, &local, reinterpret_cast<const CVector3*>(&frame->modelling.at), 1);
    Mat4_TransformVectors(ground->GetWorldMatrix(), &at, &local, 1);
    CMatrix34 matrix;
    // BUG(original): the flags word is the stack's leftover with bits 0, 1 and 17 cleared; 0 here (no optimisation hints).
    matrix.m_ui32Flags = 0;
    matrix.m_right = right;
    matrix.m_up = up;
    matrix.m_at = at;
    matrix.m_pos = world;
    matrix.m_ui32Flags &= 0xfffdfffcu;
    node->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(&matrix));  // 0x000d0be8
    *m_unk16f0 = *ground->GetInvertedWorldMatrix();  // vt+0x54
    return 1;
}

namespace {
// The looping sounds PlayFootstepSounds keeps up with a speed: the volume and the pitch of sound `first` approach
// (FloatApproach_Step over the frame's dt, from the sound's volume x volume scale and speed x pitch) the remaps of
// `speed` (group floats `from` [0..3] for the volume, [4..7] for the pitch; approach speeds `rates`), and both sounds
// (`second`, 0xffffffff none) get them.
void UpdateSpeedSounds(CKHkS08Hero* hero, IKTime* clock, uint32_t first, uint32_t second, float speed,
                       const float from[8], const float rates[2]) {
    CKSoundDictionaryID* dictionary = static_cast<CKSoundDictionaryID*>(hero->m_pSoundDico);
    const float volumeTarget = Math_RemapClamped(from[0], from[1], speed, from[2], from[3]);  // 0x00333618
    const float pitchTarget = Math_RemapClamped(from[4], from[5], speed, from[6], from[7]);
    CKSound* sound = dictionary->GetSound(first);  // 0x00112bc0
    float approach[3] = {volumeTarget, rates[0], sound->m_fVolume * sound->m_fVolumeScale};
    const float volume = FloatApproach_Step(clock->m_afDeltaTime[0], approach);  // 0x002436e8
    sound = dictionary->GetSound(first);
    float approachPitch[3] = {pitchTarget, rates[1], sound->m_fSpeed * sound->m_fPitch};
    const float pitch = FloatApproach_Step(clock->m_afDeltaTime[0], approachPitch);
    dictionary->GetSound(first)->SetBaseVolume(volume);  // 0x00110ee8
    if (second != 0xffffffffu) dictionary->GetSound(second)->SetBaseVolume(volume);
    dictionary->GetSound(first)->SetSpeed(pitch);  // 0x00110e98
    if (second != 0xffffffffu) dictionary->GetSound(second)->SetSpeed(pitch);
}

// The horizontal speed (velocity +0x127c / +0x1284; Math_Sqrtf of fused squares from 0), a -0 made 0.
float HorizontalSpeed(const CKHkS08Hero* hero) {
    float speed = std::sqrt(ppc::fmadds(hero->m_unk1284, hero->m_unk1284, ppc::fmadds(hero->m_unk127c, hero->m_unk127c, 0.0f)));
    if (speed == 0.0f) speed = 0.0f;  // TOC +0x1f4c
    return speed;
}
}  // namespace

// 0x002fa928 CKHkS08Hero_PlayFootstepSounds_maybe (through the thunk 0x334110, vt+0x118): the tracked leader's looping
// ground sounds 4 / 5 (+0xec4 bit 1) and flight sounds 0xc / 0xd (flying with the game manager's force record of the hero
// not null) follow its speed; the one-shot sounds of the event bits of +0xed8 (cleared at the end) and of +0xecc bits 8
// / 10; the partner-flight sound 0x22 follows the distance to the partner; then, on a plain surface (or a special one with
// +0x13d8), the animation marks' footsteps (+0xedc bits 0..3) of the ground animation sub-state, the flight sub-state
// and the climb (sounds 0x12 / 0x13, 0x14 / 0x15, 6 / 7, 0x1c / 0x1d).
void CKHkS08Hero::PlayFootstepSounds(IKTime* clock) {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(m_pGrpHero);
    CKSoundDictionaryID* dictionary = static_cast<CKSoundDictionaryID*>(m_pSoundDico);
    if ((m_unkec4 & 2u) != 0 && m_ui8Hero == m_ui8TrackedLeader) {
        if (dictionary->GetSound(4) != nullptr && dictionary->GetSound(5) != nullptr) {
            PlaySoundIfIdle(1.0f, 1.0f, 4, 1, 0);  // 0x00333fc8; TOC +0x1f78
            PlaySoundIfIdle(1.0f, 1.0f, 5, 1, 0);
            const float speed = HorizontalSpeed(this);
            const float from[8] = {group->m_unk230, group->m_unk234, group->m_unk238, group->m_unk23c,
                                   AsF32(group->m_unk240), group->m_unk244, group->m_unk248, group->m_unk24c};
            const float rates[2] = {group->m_unk250, group->m_unk254};
            UpdateSpeedSounds(this, clock, 4, 5, speed, from, rates);
        }
    } else {
        StopSound(4);  // 0x003343d8
        StopSound(5);
    }
    CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);  // TOC +0x1f88 -> +0x8c
    bool flight = IsFlyingMovementMode1() != 0 && m_ui8TrackedLeader == m_ui8Hero && manager != nullptr;  // 0x00340188
    if (flight) {
        static const CVector3 kNullVector = {0.0f, 0.0f, 0.0f};  // 0x00c50d64 (TOC +0x1f64)
        const uint32_t* record = &manager->m_unkDF4[1 + m_ui8TrackedLeader * 8u];
        if (AsF32(record[0]) == kNullVector.x && kNullVector.y == AsF32(record[1]) && kNullVector.z == AsF32(record[2])) {
            flight = false;
        }
    }
    if (flight) {
        if (dictionary->GetSound(0xc) != nullptr && dictionary->GetSound(0xd) != nullptr) {
            PlaySoundIfIdle(1.0f, 1.0f, 0xc, 1, 0);
            PlaySoundIfIdle(1.0f, 1.0f, 0xd, 1, 0);
            const float speed = HorizontalSpeed(this);
            const float from[8] = {AsF32(group->m_unk2a0), group->m_unk2a4, AsF32(group->m_unk2a8), group->m_unk2ac,
                                   AsF32(group->m_unk2b0), group->m_unk2b4, group->m_unk2b8, group->m_unk2bc};
            const float rates[2] = {AsF32(group->m_unk2c0), group->m_unk2c4};
            UpdateSpeedSounds(this, clock, 0xc, 0xd, speed, from, rates);
        }
    } else {
        StopSound(0xc);
        StopSound(0xd);
    }
    if ((m_unked8 & 1u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 0, 1);  // 0x00334108
    if ((m_unked8 & 0x20u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 9, 1);
    if ((m_unked8 & 4u) != 0) {
        PlaySoundIfIdle(1.0f, 1.0f, 3, 1, 0);
    } else {
        StopSound(3);
    }
    if ((m_unked8 & 2u) != 0) {
        PlaySoundIfIdleThunk(1.0f, 1.0f, 1, 1);
        PlaySoundIfIdleThunk(1.0f, 1.0f, 2, 1);
    }
    if ((m_unked8 & 0x40u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 8, 1);
    if ((m_unked8 & 0x80u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 0xb, 1);
    if ((m_unkecc & 0x100u) != 0 || (m_unkecc & 0x400u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 0xe, 1);
    static const uint32_t kEventSounds[][2] = {{0x400u, 0xf},      {0x800u, 0x10},    {0x1000u, 0x11},
                                               {0x2000u, 0x16},    {0x4000u, 0x17},   {0x8000u, 0x18},
                                               {0x2000000u, 0x25}, {0x4000000u, 0x1a}, {0x10000u, 0x1a},
                                               {0x20000u, 0x1b},   {0x40000u, 0x19},  {0x80000u, 0x4a}};
    for (const auto& event : kEventSounds) {
        if ((m_unked8 & event[0]) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, event[1], 1);
    }
    if ((m_unked8 & 0x100000u) != 0) {
        PlaySoundIfIdle(1.0f, 1.0f, 0x4b, 1, 0);
    } else {
        StopSound(0x4b);
    }
    if ((m_unked8 & 0x200000u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 0x20, 1);
    if ((m_unked8 & 0x400000u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 0x1e, 1);
    if ((m_unked8 & 0x800000u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 0x21, 1);
    if (ShouldJoinPartnerFlight() != 0 && m_ui8Hero == m_ui8TrackedLeader) {  // 0x00341fa0
        if (dictionary->GetSound(0x22) != nullptr) {
            PlaySoundIfIdle(1.0f, 1.0f, 0x22, 1, 0);
            const float distance =
                std::sqrt(ppc::fmadds(m_unk15f8, m_unk15f8, ppc::fmadds(m_unk15f0, m_unk15f0, m_unk15f4 * m_unk15f4)));
            const float from[8] = {group->m_unk278, group->m_unk27c, AsF32(group->m_unk280), group->m_unk284,
                                   AsF32(group->m_unk288), group->m_unk28c, group->m_unk290, group->m_unk294};
            const float rates[2] = {group->m_unk250, group->m_unk254};
            UpdateSpeedSounds(this, clock, 0x22, 0xffffffffu, distance, from, rates);
        }
    } else {
        StopSound(0x22);
    }
    if ((m_unked8 & 0x1000000u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 0x24, 1);
    const uint8_t surface = GetFootstepSurfaceType();  // 0x003336c0
    if (surface == 0 || surface == 4 || m_unk13d8 != 0) {
        const uint32_t marks = m_unkedc;
        const bool left = (marks & 1u) != 0 || (marks & 4u) != 0;
        if (IsMovementMode0() != 0 && m_ui8GroundAnimState <= 0xb) {  // 0x00340178; the jump table at 0x002fac2c
            float volume = 1.0f;
            float pitch = 1.0f;
            uint32_t sound = 0x12;
            bool play = true;
            switch (m_ui8GroundAnimState) {
                case 0:
                    volume = group->m_unk208;
                    pitch = group->m_unk20c;
                    break;
                case 1:
                    pitch = Math_RemapClamped(m_unkad8, m_unkae4, m_unk12d0, group->m_unk214, group->m_unk21c);
                    volume = Math_RemapClamped(m_unkad8, m_unkae4, m_unk12d0, group->m_unk210, group->m_unk218);
                    break;
                case 2:
                    pitch = Math_RemapClamped(m_unkae0, m_unkaf4, m_unk12d0, group->m_unk224, group->m_unk22c);
                    volume = Math_RemapClamped(m_unkad8, m_unkae4, m_unk12d0, group->m_unk220, group->m_unk228);
                    sound = 0x14;
                    break;
                case 7:
                case 0xb:
                    break;
                default:
                    play = false;
                    break;
            }
            if (play) {
                if (left) PlaySoundIfIdleThunk(volume, pitch, sound, 1);
                if ((m_unkedc & 2u) != 0 || (m_unkedc & 8u) != 0) PlaySoundIfIdleThunk(volume, pitch, sound + 1, 1);
            }
        }
        if (IsFlyingMovementMode1() != 0) {
            const uint8_t state = m_ui8FlyAnimState;
            if (state == 0xb) {
                const float pitch = Math_RemapClamped(m_unkae0, m_unkaf4, m_unk12d0, group->m_unk224, group->m_unk22c);
                const float volume = Math_RemapClamped(m_unkad8, m_unkae4, m_unk12d0, group->m_unk220, group->m_unk228);
                if ((m_unkedc & 1u) != 0 || (m_unkedc & 4u) != 0) PlaySoundIfIdleThunk(volume, pitch, 0x14, 1);
                if ((m_unkedc & 2u) != 0 || (m_unkedc & 8u) != 0) PlaySoundIfIdleThunk(volume, pitch, 0x15, 1);
            } else if (state == 0xa || state == 0x10) {
                if ((m_unkedc & 1u) != 0 || (m_unkedc & 4u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 0x12, 1);
                if ((m_unkedc & 2u) != 0 || (m_unkedc & 8u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 0x13, 1);
            } else if (state == 0xd) {
                if ((m_unkedc & 1u) != 0 || (m_unkedc & 4u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 6, 1);
                if ((m_unkedc & 2u) != 0 || (m_unkedc & 8u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 7, 1);
            }
        }
        if (IsClimbingMovementMode2() != 0 && m_ui8ClimbAnimState == 1) {  // 0x003401a0
            if ((m_unkedc & 1u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 0x1c, 1);
            if ((m_unkedc & 2u) != 0) PlaySoundIfIdleThunk(1.0f, 1.0f, 0x1d, 1);
        }
    }
    m_unked8 = 0;
}

// 0x002fc1b0 CKHkS08Hero_IsComboKindFlagSet
uint8_t CKHkS08Hero::IsComboKindFlagSet() const {
    if (m_unk1abc != 0 || m_unk1abd != 0 || m_unk1ac3 != 0 || m_unk1ac0 != 0 || m_unk1ac1 != 0) return 1;
    return m_unk1ac2;
}

// 0x002f86b8 StaticInitAndDestruction_2f86b8: two file statics (0x00ceadf4, 0x00ceadf8) set to -1.0f. Nothing in the game
// reads them (their only references are the initialiser's TOC entries).
namespace {
[[maybe_unused]] float s_unkceadf4 = -1.0f;
[[maybe_unused]] float s_unkceadf8 = -1.0f;
}  // namespace
