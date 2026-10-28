// IKGrpHero.cpp - reconstructed original translation unit 0x2c81f0-0x2c8f78 (GAME_TOC1, main_toc1), 18 functions, 16 live.
// Primary owner: IKGrpHero (not a registered class)
// Other owners: CKGrpS08Hero (5), CKGrpS08HeroBase (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x2c81f0  IKGrpHero_EnableMembers
//   [ ] 0x2c82a8  IKGrpHero_FreeArrays_maybe
//   [ ] 0x2c8370  IKGrpHero_ResetPlayerSlotEntries_maybe  [dead]
//   [x] 0x2c83f0  IKGrpHero_AllocRuntimeArrays_maybe
//   [x] 0x2c8598  IKGrpHero_PostLoad
//   [ ] 0x2c85f0  CKGrpS08Hero_ConstructBase_2_maybe  [dead]
//   [ ] 0x2c8660  IKGrpHero_DisableMembers
//   [x] 0x2c8718  CKGrpS08Hero_ConstructBase_maybe
//   [ ] 0x2c8788  IKGrpHero_ResolveTriggerProperty_maybe
//   [x] 0x2c8870  IKGrpHero_Update
//   [ ] 0x2c8a88  CKGrpS08Hero_BaseResume_maybe
//   [x] 0x2c8a90  IKGrpHero_ResetSoundChannelFlags_maybe
//   [ ] 0x2c8ae8  IKGrpHero_OnLevelExit_maybe
//   [ ] 0x2c8af0  CKGrpS08Hero_BasePause_maybe
//   [ ] 0x2c8af8  CKGrpS08Hero_vf60
//   [ ] 0x2c8b00  IKGrpHero_LevelReset
//   [ ] 0x2c8d58  IKGrpHero_ClearReferences
//   [x] 0x2c8dc8  IKGrpHero_ResetRuntimeState_maybe
//
//   [ ] 0x9bd118  IKGrpHero_GetClassGroup  [inline]
//   [ ] 0x9bd120  IKGrpHero_GetClassId  [inline]
//   [ ] 0x9bd128  IKGrpHero_vfCC  [inline]
//   [ ] 0x9bd138  IKGrpHero_vf17C  [inline]
//   [ ] 0x9bd140  IKGrpHero_IsKindOf  [inline]
//   [ ] 0x9bd198  IKGrpHero_Destructor  [inline]
//   [ ] 0x9bd1b8  IKGrpHero_DeletingDestructor  [inline]
// 0x002c8718 CKGrpS08Hero_ConstructBase_maybe is the IKGrpHero constructor: inline in IKGrpHero.h.

#include <cstdlib>
#include <cstring>

#include "Spyro2008/groups/C22SpyroShims.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "k2000/managers/CKSoundManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/sound/SoundVoiceManager.h"
#include "k2000/core/Stub.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/ai/CKDetectedMovable.h"
#include "k2000/services/CKSrvDetect.h"

// 0x002c8a90 IKGrpHero_ResetSoundChannelFlags_maybe: the sound listener follows the camera again.
void IKGrpHero::ResetSoundChannelFlags() {
    CKListener* listener = g_pEngine->m_soundManager->m_pVoiceManager->m_pListener;
    c22spyro::ListenerSetFollowCamera(listener, 1);             // 0x110330
    c22spyro::ListenerSetOrientationFollowCamera(listener, 1);  // 0x110308
}

// 0x002c8598 IKGrpHero_PostLoad
int32_t IKGrpHero::PostLoad(int32_t type) {
    // IKLife_PostLoad 0x00019f68 (k2000/logic/CDefaultGameManager.cpp, family gm; local copy): level type only,
    // bit 2 of the bit array.
    if (type == K_LEVEL_PLATEFORMS) {
        m_bitArray = (m_bitArray & 0xfffffffbu) | 4u;
        AllocRuntimeArrays();
    }
    return 1;
}

// 0x002c83f0 IKGrpHero_AllocRuntimeArrays_maybe
void IKGrpHero::AllocRuntimeArrays() {
    const uint32_t heroes = GetHeroCount();  // vt+0xf4
    const uint32_t maxPlayers = CKGrpS08Hero::GetMaxPlayers();
    // PORT: the pointer arrays take the native pointer size (4 on the PS3).
    m_apControlledHeroes = static_cast<IKSerializable**>(Mem_CallocAligned16(sizeof(IKSerializable*), maxPlayers + 1));
    m_apCompanionHeroes = static_cast<IKSerializable**>(Mem_CallocAligned16(sizeof(IKSerializable*), heroes + 1));
    m_apHeroesCopy = static_cast<IKSerializable**>(Mem_CallocAligned16(sizeof(IKSerializable*), heroes + 1));
    const uint32_t slots = (maxPlayers * m_sProperties.m_ui8Value) & 0xffu;
    m_pUnk74 = Mem_CallocAligned16(0x18, slots);
    m_pUnk78 = Mem_CallocAligned16(0x18, heroes);
    m_pUnk7c = static_cast<uint8_t*>(Mem_CallocAligned16(1, heroes));
    // OperatorNewArray(slots * 0x2c + 4): the count cookie, then the entries (left unset on the PS3 except the
    // four fields below; zeroed here so that runs are deterministic).
    // PORT: the cookie takes the entries' alignment (4 on the PS3, 8 on x64: the ground pointer).
    const size_t cookie = alignof(SPlayerSlot) > 4 ? alignof(SPlayerSlot) : 4;
    uint8_t* block = static_cast<uint8_t*>(std::calloc(1, slots * sizeof(SPlayerSlot) + cookie));
    *reinterpret_cast<uint32_t*>(block) = slots;
    SPlayerSlot* entries = reinterpret_cast<SPlayerSlot*>(block + cookie);
    for (uint32_t i = 0; i < slots; ++i) {
        entries[i].m_ui8SectorNumber = 0;
        entries[i].m_pGround = nullptr;
        entries[i].m_i32FaceIndex = -1;
        entries[i].m_eContactStatus = 3;
    }
    m_pPlayerSlots = entries;
    m_unk66 = 0xff;
    // vt+0xec: CKGrpS08Hero 0x2ce310, empty.
}

// 0x002c8dc8 IKGrpHero_ResetRuntimeState_maybe (on a CKGrpS08Hero: it clears the derived +0xf8)
void CKGrpS08Hero::ResetRuntimeState() {
    const uint32_t heroes = GetHeroCount();  // vt+0xf4
    std::memcpy(m_apHeroesCopy, m_apHeros, (heroes & 0xffu) * sizeof(IKSerializable*));  // PS3: (heroes << 2) & 0x3fc
    m_apHeroesCopy[heroes] = nullptr;
    m_unk66 = 0xff;
    m_unk65 = 0;
    m_unk70 = 0;
    std::memcpy(&m_unk5c, &m_sProperties.m_aui32Words[0], sizeof(float));
    m_unk6c = -1000.0f;  // TOC 0x1ab0
    m_ui8ControlledHeroCount = 0;
    m_ui8CompanionHeroCount = 0;
    m_unk54 = 0;
    m_unk64 = 0;
    m_unk60 = -1000.0f;
    m_unk68 = -1000.0f;
    for (uint32_t i = 0; i < heroes; ++i) m_pUnk7c[i] = 0xff;
    std::memcpy(&m_unk84, &m_sProperties.m_aui32Words[4], sizeof(float));
    m_vUnk88 = CVector3{0.0f, 0.0f, 0.0f};  // the zero vector 0xc50d64
    m_unkf8 = 0;
    m_unk95 = 0;
    m_unk94 = 0;
    const uint32_t slots = (GetMaxPlayers() * m_sProperties.m_ui8Value) & 0xffu;
    for (uint32_t i = 0; i < slots; ++i) {
        m_pPlayerSlots[i].m_ui8SectorNumber = 0;
        m_pPlayerSlots[i].m_pGround = nullptr;
        m_pPlayerSlots[i].m_i32FaceIndex = -1;
        m_pPlayerSlots[i].m_eContactStatus = 3;
    }
}

// 0x002c8870 IKGrpHero_Update: the hero group's part of its frame: +0xf8 bit 10 from the enemy group (vt+0xf0: a fight
// is on), the controlled and companion lists rebuilt, once (+0xf8 bit 11) the detectors told about every hero's node
// and the focus set, then the catch-up points, the dragon switch and the speech animations; bit 11 set, bit 15 cleared.
void CKGrpS08Hero::UpdateHeroGroup(IKTime* clock) {
    IKSerializable* enemies = g_pEngine->m_gameManager->m_unk04[0];  // +0x04
    if (enemies == nullptr) {
        m_unkf8 &= 0xfffffbffu;
    } else {
        // STUB(C2.7: enemies): CKGrpS08Enemy vt+0xf0 (a fight is on); the first fight starts after the idle checks.
        DOTD_STUB_ONCE("IKGrpHero_Update: CKGrpS08Enemy vt+0xf0 (C2.7)");
        const uint32_t fighting = 0;
        m_unkf8 = (m_unkf8 & 0xfffffbffu) | ((fighting & 0xffu) << 10);
    }
    RebuildControlledAndCompanionHeroArrays();  // 0x002cb528
    if ((m_unkf8 & 0x800u) == 0) {
        CKSrvDetect* detect = static_cast<CKSrvDetect*>(g_pEngine->m_srvDetect);
        for (uint32_t i = 0; i < GetHeroCount(); ++i) {  // vt+0xf4
            IKSerializable* node = static_cast<IKHook*>(m_apHeros[i])->m_pKGLObject;
            for (uint32_t j = 0; j < detect->m_ui32NbDetectedMovable; ++j) {
                static_cast<CKDetectedMovable*>(detect->m_apDetectedMovable[j])->ActivateDetectableNode(node);  // 0x001ab170
            }
        }
        SetFocusedDragon(nullptr, 0);  // 0x002cc3f0
    }
    UpdateCatchUpPoints();              // 0x002ccbe0
    UpdatePartnerInteraction(clock);    // 0x002cbf10
    UpdateHeroSpeechAnims(clock);       // 0x002cb280
    m_unkf8 = ((m_unkf8 & 0xfffff7ffu) | 0x800u) & 0xffff7fffu;
}
