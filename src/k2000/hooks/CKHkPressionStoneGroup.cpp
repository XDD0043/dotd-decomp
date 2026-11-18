// Reconstructed original translation unit: 0x42a308-0x42cce0 (GAME_TOC1, main_toc1), 36 functions, 32 live.
// Primary class: CKHkPressionStoneGroup  key 0x342  category Hook  size 0x64  vtable 0xb261f8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x42a308  CKHkPressionStoneGroup_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x42a358  RegisterCKHkPressionStoneGroupClass
//   [ ] 0x42a3d0  _GLOBAL__I_42a3d0
//   [x] 0x42a3e0  CKHkPressionStoneGroup_ReleaseAllHeroes_maybe
//   [x] 0x42a650  CKHkPressionStoneGroup_OnDeactivate
//   [x] 0x42a688  CKHkPressionStoneGroup_UpdateHeroesOnStones_maybe
//   [ ] 0x42a920  CKHkPressionStoneGroup_UpdateActiveTimeout_maybe  [dead]
//   [x] 0x42a9f8  CKHkPressionStoneGroup_AssignStonesToAIHeroes_maybe
//   [x] 0x42acc0  CKHkPressionStoneGroup_UpdateStoneStates_maybe
//   [x] 0x42b170  CKHkPressionStoneGroup_UpdateOccupantsAndDetachHeroes_maybe
//   [x] 0x42b4b0  CKHkPressionStoneGroup_CheckSolved_maybe
//   [x] 0x42b650  CKHkPressionStoneGroup_Resume  (empty / no effect: inherited, KStub_Nop_3f6e60)
//   [x] 0x42b678  CKHkPressionStoneGroup_Pause  (empty / no effect: inherited, KStub_Nop_3f6e58)
//   [x] 0x42b6a0  CKHkPressionStoneGroup_Stop  (empty / no effect: inherited, CKHkActorBase_d82_maybe_Stop 0x3f6e50)
//   [ ] 0x42b6c8  CKHkPressionStoneGroup_ResetRuntimeState_maybe  [dead]
//   [ ] 0x42b790  CKHkPressionStoneGroup_Save
//   [x] 0x42b7b8  CKHkPressionStoneGroup_RecursiveRegistration  (= the inherited slot: CKHkActorBase_d82_maybe_RecursiveRegistration, then 1)
//   [x] 0x42b7e0  CKHkPressionStoneGroup_FreeBuffers_maybe  (vt+0xc0, CKHkPressionStoneGroup.h VfC0)
//   [x] 0x42b840  CKHkPressionStoneGroup_Destroy  (= the inherited slot: CKHkActorBase_d82_maybe_Destroy (vt+0xc0))
//   [ ] 0x42b868  CKHkPressionStoneGroup_Construct  [dead]
//   [x] 0x42b8c8  CKHkPressionStoneGroup_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x42b968  CKHkPressionStoneGroup_SetDefaultState
//   [x] 0x42ba60  CKHkPressionStoneGroup_DeletingDestructor  (the deleting form of ~CKHkPressionStoneGroup)
//   [x] 0x42bad8  CKHkPressionStoneGroup_MessageProc
//   [ ] 0x42bd58  CKHkPressionStoneGroup_Construct_2  [dead]
//   [x] 0x42bdb8  CKHkPressionStoneGroup_GetInfo
//   [x] 0x42bed0  CKHkPressionStoneGroup_ApplyStatePreset_maybe
//   [x] 0x42bfd0  CKHkPressionStoneGroup_Destructor  (~CKHkPressionStoneGroup)
//   [x] 0x42c040  CKHkPressionStoneGroup_BaseDestructor  (~CKHkPressionStoneGroup)
//   [x] 0x42c0b0  CKHkPressionStoneGroup_Load
//   [x] 0x42c568  CKHkPressionStoneGroup_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x42c648  CKHkPressionStoneGroup_Create  (DOTD_DECLARE_FACTORIES; the constructor in the header)
//   [x] 0x42c6b8  CKHkPressionStoneGroup_Update
//   [x] 0x42c990  CKHkPressionStoneGroup_Start
//   [x] 0x42ca80  CKHkPressionStoneGroup_OnActivate
//   [x] 0x42cb58  CKHkPressionStoneGroup_Restart
//
//   [ ] 0x9c3238  CKHkPressionStoneGroup_IsKindOfClass  [inline]
//   [ ] 0x9c3290  CKHkPressionStoneGroup_GetClassType  [inline]
//   [ ] 0x9c3298  CKHkPressionStoneGroup_GetClassID  [inline]
//   [x] 0x9c32a0  CKHkPressionStoneGroup_GetTriggerProp99  [inline]  (GetInfo)
//   [x] 0x9c32a8  CKHkPressionStoneGroup_GetTriggerProp98  [inline]  (GetInfo)
#include "k2000/hooks/CKHkPressionStoneGroup.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/components/CKSekensLauncherCpnt.h"
#include "k2000/core/IKInfo.h"
#include "k2000/hooks/CKHkPressionStone.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {
CKHkPressionStone* StoneOf(IKSerializable* object) { return static_cast<CKHkPressionStone*>(object); }
CKHkS08Hero* HeroOf(IKSerializable* object) { return static_cast<CKHkS08Hero*>(object); }
CKGrpS08Hero* HeroGroup() { return static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]); }  // engine +0x8c -> +0x08
uint32_t HeroCount() { return HeroGroup()->GetHeroCount(); }  // 0x002ca038

// The hero detached from what it holds and told so (vt+0x1c message 0xc3b).
void DetachAndNotify(CKHkS08Hero* hero) {
    hero->DetachFromObject();      // 0x00364608
    hero->MessageProc(0xc3b, nullptr);
}

// The hero's walk ended on its stone: unlocked, the attached movement off, +0x35c bit 0 set.
void StopHeroOnStone(CKHkS08Hero* hero) {
    hero->SetLockedToObject(0, nullptr, nullptr);  // 0x003622a8
    hero->SetAttachedMovementEnabled(0);           // 0x00362050
    hero->SetFlag35CBit0IfAttached(1);             // 0x00363e88
}
}  // namespace

// 0x0042bfd0 CKHkPressionStoneGroup_Destructor
CKHkPressionStoneGroup::~CKHkPressionStoneGroup() {
    if (m_vFreeStones.m_pBlock != nullptr) Mem_FreeAligned16(m_vFreeStones.m_pBlock);  // 0x00052fb8
    m_vFreeStones.m_ui32NbUsedElt = 0;
    m_vFreeStones.m_pBlock = nullptr;
}

// 0x0042c0b0 CKHkPressionStoneGroup_Load (level type 0 only). The stones are read one reference at a time.
// BUG(original): the loop's end test is done on the counter plus one as a byte: 255 stones would be allocated and read
// again and again.
int32_t CKHkPressionStoneGroup::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // 0x003f6e98
    if (type != 0) return 1;
    ReadU8(file, &m_ui8StoneCount);
    m_apStones = nullptr;  // stw of the type word (0)
    if (m_ui8StoneCount != 0) {
        m_apStones = static_cast<IKSerializable**>(
            Mem_AllocAligned16(static_cast<uint32_t>(m_ui8StoneCount) * static_cast<uint32_t>(sizeof(IKSerializable*))));
        while (m_ui8StoneCount != 0) {
            uint32_t i = 0;
            do {
                IKFile_ReadRef(file, &m_apStones[i & 0xffu]);
                ++i;
            } while (m_ui8StoneCount > (i & 0xffu));
            if (m_ui8StoneCount <= ((i + 1) & 0xffu)) break;
            m_apStones = static_cast<IKSerializable**>(
                Mem_AllocAligned16(static_cast<uint32_t>(m_ui8StoneCount) * static_cast<uint32_t>(sizeof(IKSerializable*))));
        }
    }
    m_tsSolved.Load(file, 0);  // 0x002361c0
    ReadU8(file, &m_ui8Mode);
    uint8_t value = 0;
    ReadU8(file, &value);
    m_ui8Flags = static_cast<uint8_t>((m_ui8Flags & 0xfeu) | value);
    ReadU8(file, &value);
    m_ui8Flags = static_cast<uint8_t>((m_ui8Flags & 0xfcu) | (m_ui8Flags & 1u) | static_cast<uint8_t>(value << 1));
    ReadU8(file, &value);
    m_ui8Flags = static_cast<uint8_t>((m_ui8Flags & 0x80u) | (m_ui8Flags & 0x3fu) | static_cast<uint8_t>(value << 6));
    ReadF32LE(file, &m_fTimeout);
    ReadU8(file, &m_ui8HeroCount);
    const uint32_t bytes = static_cast<uint32_t>(m_ui8HeroCount) * static_cast<uint32_t>(sizeof(IKSerializable*));
    m_apHeroes = static_cast<IKSerializable**>(Mem_AllocAligned16(bytes));
    m_apAssignedStones = static_cast<IKSerializable**>(Mem_AllocAligned16(bytes));
    IKFile_ReadObjectRefArray(file, m_apHeroes, m_ui8HeroCount);  // vt+0x28, or one read of the words
    ReadU8(file, &m_ui8Presets);
    IKFile_ReadRef(file, &m_pSekens);
    return 1;
}

// 0x0042b7e0 CKHkPressionStoneGroup_FreeBuffers_maybe
void CKHkPressionStoneGroup::VfC0() {
    Mem_FreeAligned16(m_apAssignedStones);  // 0x00052fb8
    Mem_FreeAligned16(m_apHeroes);
    if (m_apStones != nullptr) {
        Mem_FreeAligned16(m_apStones);
        m_apStones = nullptr;
    }
}

// 0x0042b968 CKHkPressionStoneGroup_SetDefaultState
void CKHkPressionStoneGroup::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);  // KStub_Nop_3f72a0
    m_unk5C = 1;
    if (flag != 0) {
        uint8_t state = 0;
        if ((m_ui8Flags & 8u) != 0) state = m_ui8Flags & 1u;
        ApplyStatePreset(state);  // vt+0xc8
        m_unk5C = 0;
        return;
    }
    ApplyStatePreset(0);
    m_unk5C = 0;
}

// 0x0042bed0 CKHkPressionStoneGroup_ApplyStatePreset_maybe (the stones from the last)
void CKHkPressionStoneGroup::ApplyStatePreset(int32_t state) {
    uint8_t first;
    uint8_t second;
    if (state == 0) {
        first = m_ui8Presets;
        second = static_cast<uint8_t>(m_ui8Presets >> 2);
    } else {
        first = static_cast<uint8_t>(m_ui8Presets >> 1);
        second = static_cast<uint8_t>(m_ui8Presets >> 3);
    }
    const uint32_t solved = first & 1u;
    const uint8_t old = m_ui8Flags;
    const uint8_t kept = static_cast<uint8_t>((old & 0x70u) | (solved << 7));
    m_ui8Flags = static_cast<uint8_t>(kept | (old & 7u) | (solved << 3));
    if (m_unk5C == 0) m_ui8Flags = static_cast<uint8_t>(kept | (solved << 3) | (old & 3u));
    for (uint32_t i = static_cast<uint32_t>(m_ui8StoneCount) - 1u; (i & 0xffu) != 0xffu; --i) {
        CKHkPressionStone* stone = StoneOf(m_apStones[i & 0xffu]);
        stone->m_bitArray = (stone->m_bitArray & 0xffdfffffu) | (solved << 21);
        stone->m_bitArray = (stone->m_bitArray & 0xefffffffu) | (static_cast<uint32_t>(second & 1u) << 28);
    }
}

// 0x0042bdb8 CKHkPressionStoneGroup_GetInfo
int32_t CKHkPressionStoneGroup::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    bool unknown = true;
    if (request == kGetInfoValueAccessor) {
        if (info->m_ui32Id == 0x98) {
            AnswerInfo(info, [](IKSerializable* o, uint32_t) {  // 0x009c32a8
                return static_cast<uint32_t>((static_cast<CKHkPressionStoneGroup*>(o)->m_ui8Flags >> 2) & 1u);
            }, 0);
            unknown = false;
        } else if (info->m_ui32Id == 0x99) {
            AnswerInfo(info, [](IKSerializable* o, uint32_t) {  // 0x009c32a0
                return static_cast<uint32_t>(static_cast<CKHkPressionStoneGroup*>(o)->m_ui8Enabled);
            }, 0);
            unknown = false;
        }
    }
    if (base == 2) return 2;
    if (!unknown) return 0;
    return base == 0 ? 0 : 1;
}

// 0x0042bad8 CKHkPressionStoneGroup_MessageProc (the stones from the last)
int32_t CKHkPressionStoneGroup::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 0;
    if (message == 0x997) {
        m_ui8Enabled = 1;
        if ((m_ui8Flags & 1u) != 0) m_ui8Flags &= 0x7fu;
        for (uint32_t i = static_cast<uint32_t>(m_ui8StoneCount) - 1u; (i & 0xffu) != 0xffu; --i) {
            CKHkPressionStone* stone = StoneOf(m_apStones[i & 0xffu]);
            if ((m_ui8Presets & 0x10u) != 0) stone->StopHotspotHold();  // 0x004275c8
            stone->m_bitArray &= 0xffdfffffu;
        }
    } else if (message == 0x940 || message == 0x996) {
        ReleaseAllHeroes(1);
    } else if (message == 0x998) {
        m_ui8Enabled = 0;
    } else if (message == 0x999) {
        const uint8_t b = m_ui8Flags;
        m_ui8Flags = static_cast<uint8_t>((((b >> 4) & 7u) << 4) | (b & 7u) | 0x88u);
        for (uint32_t i = static_cast<uint32_t>(m_ui8StoneCount) - 1u; (i & 0xffu) != 0xffu; --i) {
            CKHkPressionStone* stone = StoneOf(m_apStones[i & 0xffu]);
            stone->m_bitArray = (stone->m_bitArray & 0xffdfffffu) | 0x200000u;
        }
    } else {
        own = 1;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// The reset Start / OnActivate / Restart inline (the assigned stones from the last; +0x58 an integer zero).
void CKHkPressionStoneGroup::ResetRuntime() {
    m_unk54 = 0;
    m_unk55 = 1;
    m_fHoldStart = 0.0f;
    m_unk23 = 1;
    m_ui8Enabled = 1;
    for (uint32_t i = static_cast<uint32_t>(m_ui8HeroCount) - 1u; (i & 0xffu) != 0xffu; --i) m_apAssignedStones[i & 0xffu] = nullptr;
    if (m_vFreeStones.m_pBlock == nullptr) {
        m_vFreeStones.m_ui32NbElt = 1;
        m_vFreeStones.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    }
    m_ui8Flags = static_cast<uint8_t>((m_ui8Flags & 0xe0u) | (m_ui8Flags & 0xfu));
}

// 0x0042c990 CKHkPressionStoneGroup_Start
void CKHkPressionStoneGroup::Start() {
    CKHkActorBase::Start();  // 0x003f6e48 (empty)
    m_unk5C = 0;
    m_ui8Flags &= 0x7fu;
    ResetRuntime();
}

// 0x0042ca80 CKHkPressionStoneGroup_OnActivate
void CKHkPressionStoneGroup::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    ResetRuntime();
}

// 0x0042a650 CKHkPressionStoneGroup_OnDeactivate
void CKHkPressionStoneGroup::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    ReleaseAllHeroes(1);
}

// 0x0042cb58 CKHkPressionStoneGroup_Restart: the reset; an enabled group (flag bit 2 clear) timing (+0x21 bit 2) or with
// the solved preset (bit 7) presses its stones again (message 0x998 to each, from the last).
void CKHkPressionStoneGroup::Restart() {
    ResetRuntime();
    if ((m_bitArray & 4u) != 0) return;
    if (((m_ui8Flags >> 2) & 1u) == 0 && static_cast<int8_t>(m_ui8Flags) >= 0) return;
    for (uint32_t i = static_cast<uint32_t>(m_ui8StoneCount) - 1u; (i & 0xffu) != 0xffu; --i) {
        m_apStones[i & 0xffu]->MessageProc(0x998, nullptr);  // vt+0x1c
    }
}

// The walk AssignStonesToAIHeroes / UpdateHeroesOnStones inline: the stone's node read first, then the hero attached to
// the group (mode 0); attached, its attached movement on and its destination the node's LTM position facing its at row
// (vt+0xcc: timeout 0.0 (TOC +0x4e78), flag4 1, flag31 0).
void CKHkPressionStoneGroup::SendHeroToStone(IKSerializable* object, IKSerializable* stone) {
    CKHkS08Hero* hero = HeroOf(object);
    IKSerializable* node = StoneOf(stone)->m_pKGLObject;
    if (hero->AttachToObject(this, 0) == 0) return;  // 0x00362360
    hero->SetAttachedMovementEnabled(1);              // 0x00362050
    const RwMatrix& ltm = static_cast<CSGMovable*>(node)->m_pRwFrame->ltm;
    const CVector3 position = {ltm.pos.x, ltm.pos.y, ltm.pos.z};
    const CVector3 at = {ltm.at.x, ltm.at.y, ltm.at.z};
    hero->SetMoveDestination(0.0f, &position, &at, 0, 1, 0);  // vt+0xcc 0x0032a548
}

// 0x0042a3e0 CKHkPressionStoneGroup_ReleaseAllHeroes_maybe: each hero (from the last) with a stone is let go unless the
// group keeps its heroes (+0x21 bit 6) and this is not forced: detached when it holds the group or the stone, the stone's
// path-finding box blocked again, no stone; in mode 0 a hero without one is detached when it holds the group (or its
// stone). Then the group lets go of every stone.
void CKHkPressionStoneGroup::ReleaseAllHeroes(int32_t force) {
    for (uint32_t i = static_cast<uint32_t>(m_ui8HeroCount) - 1u; (i & 0xffu) != 0xffu; --i) {
        const uint32_t index = i & 0xffu;
        CKHkS08Hero* hero = HeroOf(m_apHeroes[index]);
        const bool mayRelease = (m_ui8Flags & 0x40u) == 0 || force != 0;
        if (m_apAssignedStones[index] != nullptr && mayRelease) {
            if (this == hero->GetAttachedObject() || m_apAssignedStones[index] == hero->GetAttachedObject()) {  // 0x00361d50
                DetachAndNotify(hero);
            }
            StoneOf(m_apAssignedStones[index])->SetNavBlockedForGroup(this, 1);  // 0x0042a1a8
            m_apAssignedStones[index] = nullptr;
            continue;
        }
        if (m_ui8Mode == 0 && mayRelease &&
            (this == hero->GetAttachedObject() ||
             (m_apAssignedStones[index] != nullptr && m_apAssignedStones[index] == hero->GetAttachedObject()))) {
            DetachAndNotify(hero);
        }
    }
    for (uint32_t i = static_cast<uint32_t>(m_ui8StoneCount) - 1u; (i & 0xffu) != 0xffu; --i) {
        StoneOf(m_apStones[i & 0xffu])->SetOccupant(this, 0);  // 0x00425cd0
    }
}

// 0x0042a688 CKHkPressionStoneGroup_UpdateHeroesOnStones_maybe: each hero (from the last) with a stone: an AI hero not
// holding the group is sent to its stone; an AI hero walking there stops on it once arrived (vt+0xd0) and standing on it
// (the stone's hero +0x34); the player's hero holding the group is let go.
void CKHkPressionStoneGroup::UpdateHeroesOnStones(IKTime* frameClock) {
    for (uint32_t i = static_cast<uint32_t>(m_ui8HeroCount) - 1u; (i & 0xffu) != 0xffu; --i) {
        const uint32_t index = i & 0xffu;
        if (m_apAssignedStones[index] == nullptr) continue;
        CKHkS08Hero* hero = HeroOf(m_apHeroes[index]);
        if (hero->IsPlayerControlled() == 0 && hero->GetAttachedObject() != this) {  // 0x00362af0
            SendHeroToStone(hero, m_apAssignedStones[index]);
        } else if (hero->IsPlayerControlled() == 0) {
            if (hero->GetFlag35CBit0IfAttached() == 0 && hero->UpdateMoveTo(frameClock, nullptr) != 0 &&  // 0x00362878, vt+0xd0
                StoneOf(m_apAssignedStones[index])->m_pHero == hero) {
                StopHeroOnStone(hero);
            }
        } else if (hero->IsPlayerControlled() != 0 && this == hero->GetAttachedObject()) {
            DetachAndNotify(hero);
        }
    }
}

// 0x0042a9f8 CKHkPressionStoneGroup_AssignStonesToAIHeroes_maybe: while free stones are left, each AI hero (from the last)
// without a stone gets the first free one (unless another hero has it), when its +0x360 bit 12 is clear and it may attach
// to the group (vt+0xe0): the stone's box freed, the hero sent there, the stone taken off the free list (the last one
// moved first); a playing sekens 3 stopped.
void CKHkPressionStoneGroup::AssignStonesToAIHeroes() {
    for (uint32_t i = static_cast<uint32_t>(m_ui8HeroCount) - 1u; (i & 0xffu) != 0xffu && m_vFreeStones.m_ui32NbUsedElt != 0; --i) {
        const uint32_t index = i & 0xffu;
        CKHkS08Hero* hero = HeroOf(m_apHeroes[index]);
        if (hero->IsPlayerControlled() != 0 || m_apAssignedStones[index] != nullptr) continue;
        IKSerializable* stone = m_vFreeStones.m_pBlock[0];
        uint32_t free = 1;
        for (uint32_t j = static_cast<uint32_t>(m_ui8HeroCount) - 1u; (j & 0xffu) != 0xffu; --j) {
            if (m_apAssignedStones[j & 0xffu] == stone) free = 0;  // (x ^ stone) has no bit: not free
        }
        if (free == 0 || hero->GetFlag360Bit12() != 0) continue;  // 0x00363ca0
        if (hero->CanAttachTo(this, 0) == 0) continue;            // 0x00361d08 (vt+0xe0)
        m_apAssignedStones[index] = stone;
        StoneOf(stone)->SetNavBlockedForGroup(this, 0);
        hero = HeroOf(m_apHeroes[index]);
        if (hero->IsPlayerControlled() == 0 && hero->GetAttachedObject() != this) SendHeroToStone(hero, m_apAssignedStones[index]);
        const uint32_t left = --m_vFreeStones.m_ui32NbUsedElt;
        if (left != 0) m_vFreeStones.m_pBlock[0] = m_vFreeStones.m_pBlock[left];
        CKSekensLauncherCpnt* sekens = static_cast<CKSekensLauncherCpnt*>(m_pSekens);
        if (sekens->IsSekensPlaying(3) != 0) {  // 0x001f7958
            sekens->StopSekens(3, 0);           // 0x001f7a18
            m_unk54 = 0;
        }
    }
}

// 0x0042acc0 CKHkPressionStoneGroup_UpdateStoneStates_maybe: the free list rebuilt from the stones not pressed (each
// one's box freed when a hero has it, else blocked); a pressed stone with a hero standing on it counts, and when it was
// not locked (bit 20) its box is blocked, the hero's sekens played (mode 1, the first hero this frame), the group marked
// (+0x21 bit 4) and, unsolved or solved state, the hero gets the stone; a locked one stops its hero (when it holds the
// group) and frees the box. Then the player's dragon sekens (+4, mode 0), and sekens 3 when every hero stands and stones
// are free; +0x54 says sekens 3 played.
void CKHkPressionStoneGroup::UpdateStoneStates() {
    m_vFreeStones.m_ui32NbUsedElt = 0;
    uint32_t assigned = 0;
    for (uint32_t i = HeroCount() - 1u; (i & 0xffu) != 0xffu; --i) {
        if (m_apAssignedStones[i & 0xffu] != nullptr) ++assigned;
    }
    uint32_t standing = 0;
    int8_t dragon = -1;
    m_ui8Flags = static_cast<uint8_t>((m_ui8Flags & 0xe0u) | (m_ui8Flags & 0xfu));
    for (uint32_t s = static_cast<uint32_t>(m_ui8StoneCount) - 1u; (s & 0xffu) != 0xffu; --s) {
        CKHkPressionStone* stone = StoneOf(m_apStones[s & 0xffu]);
        if ((stone->m_bitArray & 0x20000u) == 0) {
            uint32_t h = static_cast<uint32_t>(m_ui8HeroCount) - 1u;
            for (; (h & 0xffu) != 0xffu; --h) {
                if (m_apAssignedStones[h & 0xffu] == stone) break;
            }
            stone->SetNavBlockedForGroup(this, (h & 0xffu) == 0xffu ? 1 : 0);
            if (m_vFreeStones.m_ui32NbElt == m_vFreeStones.m_ui32NbUsedElt) {
                uint32_t capacity = m_vFreeStones.m_ui32NbUsedElt + 1u;
                if (capacity == 0) capacity = 1;
                m_vFreeStones.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(
                    m_vFreeStones.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));  // 0x00053190
                m_vFreeStones.m_ui32NbElt = capacity;
            }
            m_vFreeStones.m_pBlock[m_vFreeStones.m_ui32NbUsedElt] = stone;
            ++m_vFreeStones.m_ui32NbUsedElt;
            continue;
        }
        if (stone->UpdateStandingHero() == 0) continue;  // 0x00427a28
        ++standing;
        if ((stone->m_bitArray & 0x100000u) == 0) {
            stone->SetNavBlockedForGroup(this, 1);
            if ((m_ui8Flags & 0x10u) == 0 && m_ui8Mode == 1) {
                static_cast<CKSekensLauncherCpnt*>(m_pSekens)->PlaySekens(HeroOf(stone->m_pHero)->GetDragonIndex());  // 0x001f7730
            }
            m_ui8Flags = static_cast<uint8_t>((m_ui8Flags & 0xe0u) | (m_ui8Flags & 0xfu) | 0x10u);
            if ((m_ui8Flags & 8u) == 0 || (m_ui8Flags & 1u) != 0) {
                uint32_t h = static_cast<uint32_t>(m_ui8HeroCount) - 1u;
                for (; (h & 0xffu) != 0xffu; --h) {
                    if (m_apHeroes[h & 0xffu] == stone->m_pHero) break;
                }
                if ((h & 0xffu) == 0xffu) continue;
                if (m_ui8Mode == 0 && stone->UpdateStandingHero() != 0 && HeroOf(stone->m_pHero)->IsPlayerControlled() != 0) {
                    dragon = static_cast<int8_t>(HeroOf(stone->m_pHero)->GetDragonIndex());
                }
                m_apAssignedStones[h & 0xffu] = stone;
            }
        } else {
            CKHkS08Hero* hero = HeroOf(stone->m_pHero);
            if (hero != nullptr && this == hero->GetAttachedObject()) StopHeroOnStone(hero);
            stone->SetNavBlockedForGroup(this, 0);
        }
    }
    if (dragon != -1 && m_vFreeStones.m_ui32NbUsedElt != 0 && m_ui8Mode == 0) {
        static_cast<CKSekensLauncherCpnt*>(m_pSekens)->PlaySekens(static_cast<uint32_t>(dragon + 4));
    }
    if ((standing & 0xffu) == (assigned & 0xffu) && (standing & 0xffu) == (HeroCount() & 0xffu)) {
        if (m_vFreeStones.m_ui32NbUsedElt == 0) return;
        if (m_unk54 != 0) return;
        static_cast<CKSekensLauncherCpnt*>(m_pSekens)->PlaySekens(3);
        m_unk54 = 1;
        return;
    }
    m_unk54 = 0;
}

// 0x0042b170 CKHkPressionStoneGroup_UpdateOccupantsAndDetachHeroes_maybe (mode 1, from Update)
void CKHkPressionStoneGroup::UpdateOccupantsAndDetachHeroes(IKTime* frameClock) {
    const uint8_t b = m_ui8Flags;
    if (((b >> 4) & 1u) != 0) {
        if ((b & 8u) != 0 && (b & 1u) == 0) return;
        for (uint32_t i = static_cast<uint32_t>(m_ui8StoneCount) - 1u; (i & 0xffu) != 0xffu; --i) {
            StoneOf(m_apStones[i & 0xffu])->SetOccupant(this, 1);
        }
        UpdateHeroesOnStones(frameClock);
        AssignStonesToAIHeroes();
        return;
    }
    const bool held = ((b >> 5) & 1u) != 0 && (b & 4u) != 0;
    if (held || m_unk55 != 0) {
        if (!held) return;
        for (uint32_t i = static_cast<uint32_t>(m_ui8StoneCount) - 1u; (i & 0xffu) != 0xffu; --i) {
            StoneOf(m_apStones[i & 0xffu])->SetOccupant(this, 1);
        }
        UpdateHeroesOnStones(frameClock);
        return;
    }
    uint32_t s = static_cast<uint32_t>(m_ui8StoneCount) - 1u;
    for (; (s & 0xffu) != 0xffu; --s) {
        if (StoneOf(m_apStones[s & 0xffu])->m_pHero != nullptr) break;
    }
    if ((s & 0xffu) != 0xffu) {
        m_fHoldStart = frameClock->m_afCurrentTime[0];  // +0x04
        m_unk55 = static_cast<uint8_t>(((b >> 6) & 1u) ^ 1u);
        if (((b >> 6) & 1u) == 0) return;
    }
    // The detach loop, by dragon index (GetHeroByDragonIndex 0x2ca080) into the assigned stones.
    CKGrpS08Hero* group = HeroGroup();
    for (uint8_t d = static_cast<uint8_t>(HeroCount() - 1u); d != 0xff; --d) {
        if (m_apAssignedStones[d] == nullptr) continue;
        if (this != HeroOf(group->m_apHeros[d])->GetAttachedObject()) continue;
        const uint8_t keep = m_ui8Flags & 0x40u;
        if (keep != 0) continue;
        HeroOf(group->m_apHeros[d])->DetachFromObject();
        StoneOf(m_apAssignedStones[d])->SetOccupant(this, 1);
        StoneOf(m_apAssignedStones[d])->SetNavBlockedForGroup(this, 1);
        StoneOf(m_apAssignedStones[d])->SetOccupant(this, 0);
        m_apAssignedStones[d] = nullptr;  // the word of bit 6 (clear)
    }
}

// 0x0042b4b0 CKHkPressionStoneGroup_CheckSolved_maybe: free stones left: not timing (+0x21 bit 2 cleared). Else, not yet
// timing: unsolved or solved state, the trigger queued, solved (bit 3), the stones' hot spot hold (bit 28) with +0x22 bit
// 4, and with the timed reset (bit 1) the heroes held from now (+0x55, +0x58 the engine clock's time); then timing (bit 2)
// and +0x23 set.
void CKHkPressionStoneGroup::CheckSolved() {
    if (m_vFreeStones.m_ui32NbUsedElt != 0) {
        m_ui8Flags = static_cast<uint8_t>((m_ui8Flags & 0xf8u) | (m_ui8Flags & 3u));
        return;
    }
    const uint8_t b = m_ui8Flags;
    if ((b & 4u) != 0) return;
    if ((b & 8u) == 0 || (b & 1u) != 0) {
        QueueTriggerSignals(&m_tsSolved);  // 0x00236338
        m_ui8Flags = static_cast<uint8_t>((m_ui8Flags & 0xf0u) | (m_ui8Flags & 7u) | 8u);
        if (((m_ui8Presets >> 4) & 1u) != 0) {
            for (uint32_t i = static_cast<uint32_t>(m_ui8StoneCount) - 1u; (i & 0xffu) != 0xffu; --i) {
                CKHkPressionStone* stone = StoneOf(m_apStones[i & 0xffu]);
                stone->m_bitArray = (stone->m_bitArray & 0xefffffffu) | 0x10000000u;
            }
        }
        if (((m_ui8Flags >> 1) & 1u) != 0) {
            m_unk55 = 1;
            m_fHoldStart = g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[0];  // engine +0x48 -> +0x04 -> +0x04
            m_ui8Flags = static_cast<uint8_t>((m_ui8Flags & 0xf8u) | (m_ui8Flags & 3u) | 4u);
            m_unk23 = 1;
            return;
        }
    }
    m_ui8Flags = static_cast<uint8_t>((m_ui8Flags & 0xf8u) | (m_ui8Flags & 3u) | 4u);
    m_unk23 = 1;
}

// 0x0042c6b8 CKHkPressionStoneGroup_Update: while the heroes are held (+0x55) they are steered to their stones; the hold
// ends (the heroes let go) once the time since +0x58 passes +0x28 (fsubs; ble keeps it on NaN), or at once when a hero is
// on a stone and the group is not timing. An enabled group not solved (or solved state, not preset) updates its stones,
// checks the solution, runs the AI heroes (mode 1), keeps solved stones locked, and a timed solved group lets go of every
// stone and hero once.
void CKHkPressionStoneGroup::Update(IKTime* frameClock) {
    CKHkActorBase::Update(frameClock);  // 0x003f6e68 (empty)
    uint32_t b;
    if (m_unk55 == 0) {
        b = m_ui8Flags;
    } else {
        UpdateHeroesOnStones(frameClock);
        b = m_ui8Flags;
        if ((b & 0x10u) == 0 || ((b >> 2) & 1u) != 0) {
            if (frameClock->m_afCurrentTime[0] - m_fHoldStart > m_fTimeout) {
                ReleaseAllHeroes(0);
                b = m_ui8Flags;
                m_unk55 = 0;
            }
        } else {
            m_unk55 = 0;
        }
    }
    if (!(((b & 8u) == 0 || ((b & 1u) != 0 && (b >> 7) == 0)) && m_ui8Enabled != 0)) return;
    UpdateStoneStates();
    CheckSolved();
    if (m_ui8Mode == 1) UpdateOccupantsAndDetachHeroes(frameClock);
    uint32_t f = m_ui8Flags;
    if ((f & 8u) != 0 && (f & 1u) == 0) {
        for (uint32_t i = static_cast<uint32_t>(m_ui8StoneCount) - 1u; (i & 0xffu) != 0xffu; --i) {
            CKHkPressionStone* stone = StoneOf(m_apStones[i & 0xffu]);
            stone->SetOccupant(this, 1);
            stone->SetNavBlockedForGroup(this, 0);
            stone->m_bitArray = (stone->m_bitArray & 0xffdfffffu) | 0x200000u;
            stone->SetOccupant(this, 0);
        }
        f = m_ui8Flags;
    }
    if ((f & 8u) == 0 || (f & 1u) == 0 || (f & 2u) == 0 || m_unk23 == 0 || ((f >> 4) & 1u) != 0) return;
    m_unk23 = 0;
    for (uint32_t i = static_cast<uint32_t>(m_ui8StoneCount) - 1u; (i & 0xffu) != 0xffu; --i) {
        CKHkPressionStone* stone = StoneOf(m_apStones[i & 0xffu]);
        stone->SetOccupant(this, 1);
        stone->SetNavBlockedForGroup(this, 1);
        stone->SetOccupant(this, 0);
    }
    ReleaseAllHeroes(0);
}
