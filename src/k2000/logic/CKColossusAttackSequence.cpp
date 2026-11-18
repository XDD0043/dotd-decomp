// Reconstructed original translation unit: 0x46cbe8-0x46faa0 (GAME_TOC1, main_toc1), 39 functions, 29 live.
// Primary class: CKColossusAttackSequence  key 0x7c8c  category Logic  size 0x68  vtable 0xb27558
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x46cbe8  CKColossusAttackSequence_Delete  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x46cc38  CKColossusAttackSequence_Save
//   [ ] 0x46cc40  CKColossusAttackSequence_List24EntryContainsElement_maybe  [dead]
//   [ ] 0x46ccc0  CKColossusAttackSequence_EvalList30EntryCondition_maybe  [dead]
//   [ ] 0x46cd80  CKColossusAttackSequence_EvalList24EntryCondition8_maybe  [dead]
//   [ ] 0x46ce20  CKColossusAttackSequence_EvalList24EntryConditionC_maybe  [dead]
//   [ ] 0x46cee0  CKColossusAttackSequence_StartCurrentList30Entry_maybe  [dead]
//   [ ] 0x46cfa0  CKColossusAttackSequence_StartCurrentList24Entry_maybe  [dead]
//   [ ] 0x46d060  CKColossusAttackSequence_StopCurrentList30Entry_maybe  [dead]
//   [ ] 0x46d0f8  CKColossusAttackSequence_StopCurrentList24Entry_maybe  [dead]
//   [x] 0x46d190  CKColossusAttackSequence_vf84  (Vf84: the header)
//   [x] 0x46d198  CKColossusAttackSequence_vf64  (Vf64: the header)
//   [x] 0x46d1e0  CKColossusAttackSequence_vf6C  (Vf6C)
//   [x] 0x46d2e0  CKColossusAttackSequence_vf70  (Vf70: the header)
//   [ ] 0x46d2f0  RegisterCKColossusAttackSequenceClass
//   [ ] 0x46d368  _GLOBAL__I_46d368
//   [x] 0x46d378  CKColossusAttackSequence_vf78  (Vf78: the header)
//   [x] 0x46d3a0  CKColossusAttackSequence_RecursiveRegistration  (RecursiveRegistration: the header)
//   [x] 0x46d3c8  CKColossusAttackSequence_Construct  (the constructor)
//   [x] 0x46d448  CKColossusAttackSequence_Construct_2  (the constructor)
//   [x] 0x46d4c8  CKColossusAttackSequence_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x46d568  CKColossusAttackSequence_IsList30IndexValid_maybe  [dead]
//   [x] 0x46d598  CKColossusAttackSequence_PostLoad
//   [x] 0x46d7d0  CKColossusAttackSequence_Destroy
//   [ ] 0x46d9b0  CKColossusAttackSequence_IsList24IndexValid_maybe  [dead]
//   [x] 0x46d9e0  CKColossusAttackSequence_vf74  (Vf74)
//   [x] 0x46dae0  CKColossusAttackSequence_Destructor  (the destructor)
//   [x] 0x46db80  CKColossusAttackSequence_DestructBody  (the destructor)
//   [x] 0x46dc20  CKColossusAttackSequence_DeletingDestructor  (the destructor, then delete)
//   [x] 0x46dcd0  CKColossusAttackSequence_Create  (DOTD_DECLARE_FACTORIES: the constructor)
//   [x] 0x46dd60  CKColossusAttackSequence_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x46de70  CKColossusAttackSequence_vf54  (Vf54)
//   [x] 0x46dfc0  CKColossusAttackSequence_TrySwitchToMatchingList24Entry_maybe  (TrySwitchToReaction)
//   [x] 0x46e330  CKColossusAttackSequence_StartAttack_maybe  (Vf50)
//   [x] 0x46e508  CKColossusAttackSequence_AdvanceToNextList30Entry_maybe  (AdvanceToNextMain)
//   [x] 0x46e708  CKColossusAttackSequence_vf80  (Vf80)
//   [x] 0x46eab0  CKColossusAttackSequence_vf7C  (Vf7C)
//   [x] 0x46ecb8  CKColossusAttackSequence_vf60  (Vf60)
//   [x] 0x46eec8  CKColossusAttackSequence_Load
//
//   [x] 0x9c41f8  CKColossusAttackSequence_vf68  [inline]  (the base's Vf68)
//   [x] 0x9c4200  CKColossusAttackSequence_IsKindOfClass  [inline]  (the header)
//   [x] 0x9c4228  CKColossusAttackSequence_GetClassType  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c4230  CKColossusAttackSequence_GetClassID  [inline]  (DOTD_CLASS_KEY)
//   [x] 0x9c4238  CKColossusAttackSequence_vf58  [inline]  (the base's Vf58)
//   [x] 0x9c4240  CKColossusAttackSequence_vf5C  [inline]  (the base's Vf5C)
//   [x] 0x9c4248  FUN_009c4248  [inline]  (SequenceTimeAbove)
//   [x] 0x9c4268  KStub_Return0_9c4268  [inline]  (Vf6C type 1: false)
//   [x] 0x9c4270  FUN_009c4270  [inline]  (SequenceOwnerCountAtMost)
//   [x] 0x9c4298  FUN_009c4298  [inline]  (SequenceMainRanOut)
//   [x] 0x9c42a8  FUN_009c42a8  [inline]  (SequenceHookFlag400)
//   [x] 0x9c42d0  KStub_Return0_9c42d0  [inline]  (Vf6C type 6: false)
//   [x] 0x9c42d8  FUN_009c42d8  [inline]  (ElementTimeAbove)
//   [x] 0x9c42f8  KStub_Return0_9c42f8  [inline]  (the element conditions' type 1: false)
//   [x] 0x9c4300  FUN_009c4300  [inline]  (ElementAnimEndReached)
//   [x] 0x9c4310  FUN_009c4310  [inline]  (ElementHookFlag400)
//
// C2.8 port-final F03 ported the class whole. The conditions 0x9c4338 IsSpyroWithinRadiusXZ / 0x9c43e8
// IsSpyroBeyondRadius are F06's ports (k2000/ui/CKColossusAttackElement.h: ColossusCond_IsHeroWithinRadiusXZ /
// ColossusCond_IsHeroBeyondRadius); only this unit's condition switches call them (vf6C case 3, TrySwitchToReaction).
#include "k2000/logic/CKColossusAttackSequence.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/hooks/CKHkColossus.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKColossusSequenceManager.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/KBase7CCC.h"
#include "k2000/ui/CKColossusAttackElement.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/system/IKTime.h"

namespace {

using Condition = CKColossusAttackSequence::Condition;

constexpr float kZero = 0.0f;  // TOC +0x587c

// The meca group (the game manager's +0x0c) the hooks are woken / put to sleep in.
IKBaseGroup* MecaGroup() { return static_cast<IKBaseGroup*>(g_pEngine->m_gameManager->m_unk04[2]); }

// A scene node's frame position (its RwFrame's modelling matrix: frame +0x40).
const RwV3d& NodePosition(IKSerializable* node) { return static_cast<CSGMovable*>(node)->m_pRwFrame->modelling.pos; }

// The first hero's scene node: 0x002ca080 GetHeroByDragonIndex(the game manager's hero group (+0x08), 0) +0x1c.
IKSerializable* FirstHeroNode() {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);
    return static_cast<IKHook*>(group->m_apHeros[0])->m_pKGLObject;
}

// A hook's bit 0x400 (its IKLife bit array, +0x0c; rlwinm / rldicl of bit 10); no hook: 0.
uint8_t HookFlag400(IKHook* hook) {
    if (hook == nullptr) return 0;
    return static_cast<uint8_t>((hook->m_bitArray >> 10) & 1u);
}

// ---- the sequence's conditions (the end condition +0x18, vt+0x6c; table 0xbbf648..0xbbf670 / 0xbbf798) ----
// 0x009c4248 FUN_009c4248: the timer (+0x10) above the block's float (bgt: NaN is false).
uint8_t SequenceTimeAbove(CKColossusAttackSequence* sequence, const Condition* condition) {
    return sequence->m_fTimer > condition->m_fArg ? 1 : 0;
}
// 0x009c4270 FUN_009c4270: the colossus' +0x54 at most the block's count (cmpw / ble: signed).
uint8_t SequenceOwnerCountAtMost(CKColossusAttackSequence* sequence, const Condition* condition) {
    const CKHkColossus* owner = static_cast<const CKHkColossus*>(sequence->m_pOwner);
    return static_cast<int32_t>(owner->m_unk54) <= condition->m_i32Arg ? 1 : 0;
}
// 0x009c4298 FUN_009c4298: flag bit 1 (the main list ran out).
uint8_t SequenceMainRanOut(CKColossusAttackSequence* sequence, const Condition* /*condition*/) {
    return static_cast<uint8_t>((sequence->m_ui32Flags >> 1) & 1u);
}
// 0x009c42a8 FUN_009c42a8: the sequence's hook (+0x64) has its bit 0x400.
uint8_t SequenceHookFlag400(CKColossusAttackSequence* sequence, const Condition* /*condition*/) {
    return HookFlag400(sequence->m_pHook);
}

// ---- the entries' conditions (on their element; tables 0xbbf678..0xbbf688 / 0xbbf790, 0xbbf7b0) ----
// 0x009c42d8 FUN_009c42d8: the element's time (+0x34) above the block's float (bgt: NaN is false).
uint8_t ElementTimeAbove(KBase7CCC* element, const Condition* condition) {
    return element->m_fTime > condition->m_fArg ? 1 : 0;
}
// 0x009c4300 FUN_009c4300: the element's flag bit 1 (its animation's end reached).
uint8_t ElementAnimEndReached(KBase7CCC* element, const Condition* /*condition*/) {
    return static_cast<uint8_t>((element->m_ui32Flags >> 1) & 1u);
}
// 0x009c4310 FUN_009c4310: the element's hook (+0x64) has its bit 0x400.
uint8_t ElementHookFlag400(KBase7CCC* element, const Condition* /*condition*/) { return HookFlag400(element->m_pHook); }

// The element conditions of the main and reaction runs (vt+0x7c / +0x80): type 0 the time, 1 never, 2 the animation's
// end, 3 the hook's bit 0x400. BUG(original): another type calls a null descriptor (a fault on the PS3); false here.
uint8_t EvalRunCondition(KBase7CCC* element, const Condition* condition) {
    switch (condition->m_i32Type) {
        case 0: return ElementTimeAbove(element, condition);
        case 1: return 0;  // 0x009c42f8 KStub_Return0_9c42f8
        case 2: return ElementAnimEndReached(element, condition);
        case 3: return ElementHookFlag400(element, condition);
        default: return 0;
    }
}

// The grow-by-one append the unit inlines (Mem_ReallocAligned16 when full; a count of 0 would grow to 1).
template <class T>
void PushBack1(TVector<T, 1>& v, T value) {
    uint32_t used = v.m_ui32NbUsedElt;
    if (v.m_ui32NbElt == used) {
        uint32_t capacity = used + 1;
        if (capacity == 0) capacity = 1;
        v.m_pBlock = static_cast<T*>(Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));  // 0x00053190
        v.m_ui32NbElt = capacity;
        used = v.m_ui32NbUsedElt;
    }
    v.m_pBlock[used] = value;
    v.m_ui32NbUsedElt = v.m_ui32NbUsedElt + 1;
}

// A fresh one-slot block (capacity 1; the old block is not freed).
template <class T>
void FreshBlock1(TVector<T, 1>& v) {
    v.m_ui32NbElt = 1;
    v.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));  // 0x00053198
}

// An entry condition block of the Load (operator new 0x0c, zeroed): the words +0x00, +0x08, +0x04 in that order.
Condition* NewEntryCondition() {
    Condition* condition = new Condition;  // 0x0098d370 OperatorNew(0xc) (the native block keeps the 4th word)
    condition->m_fArg = 0.0f;
    condition->m_i32Type = 0;
    condition->m_i32Arg = 0;
    condition->m_unk0c = 0;
    return condition;
}
void ReadEntryCondition(IKFile* file, Condition* condition) {
    ReadS32LE(file, &condition->m_i32Type);
    ReadF32LE(file, &condition->m_fArg);
    ReadS32LE(file, &condition->m_i32Arg);
}

}  // namespace

// 0x0046bcc8 (CKColossusSequenceManager.cpp's line): CKColossusSequenceManager.h's ColossusElementByIndex.

CKColossusAttackSequence::CKColossusAttackSequence() {
    m_vReactions.m_pBlock = nullptr;
    m_vReactions.m_ui32NbElt = 1;
    m_vReactions.m_ui32NbUsedElt = 0;
    m_vMain.m_ui32NbElt = 1;
    m_vMain.m_ui32NbUsedElt = 0;
    m_vMain.m_pBlock = nullptr;
    m_ui8StateCount = 0xff;
    m_ui8State = 0xff;
    // The rest is what the fresh heap leaves (zero).
    m_pEndCondition = nullptr;
    m_pUnk1C = nullptr;
    m_ui32Flags = 0;
    m_i32Main = 0;
    m_i32Reaction = 0;
    m_pStateTable = nullptr;
    for (uint32_t& word : m_aStateTable) word = 0;
    m_pHook = nullptr;
}

CKColossusAttackSequence::~CKColossusAttackSequence() {
    if (m_vMain.m_pBlock != nullptr) Mem_FreeAligned16(m_vMain.m_pBlock);  // 0x00052fb8
    m_vMain.m_ui32NbUsedElt = 0;
    m_vMain.m_pBlock = nullptr;
    if (m_vReactions.m_pBlock != nullptr) Mem_FreeAligned16(m_vReactions.m_pBlock);
    m_vReactions.m_ui32NbUsedElt = 0;
    m_vReactions.m_pBlock = nullptr;
}

// 0x0046eec8 CKColossusAttackSequence_Load: level files only: the base's words, the end condition (four words) and the
// unused block (three), LoadNothing, the two flag bytes (bit 1, bit 2), both counts, the reaction entries (each: its
// element's index, two conditions, two bytes, the hook, the interrupted elements' indices), the main entries (each: the
// index, a condition, the hook) and the sequence's hook. Every word is read and then byte-swapped.
int32_t CKColossusAttackSequence::Load(IKFile* file, int32_t type) {
    if (type != 0) return 1;
    CKColossusAttackSequenceBase::Load(file, type);  // 0x00470480 (the non-virtual copy)
    Condition* end = new Condition;  // 0x0098d370 OperatorNew(0x10)
    end->m_unk0c = 0;
    end->m_i32Type = 0;
    end->m_i32Arg = 0;
    end->m_fArg = 0.0f;
    m_pEndCondition = end;
    ReadS32LE(file, &m_pEndCondition->m_i32Type);
    ReadS32LE(file, &m_pEndCondition->m_i32Arg);
    ReadF32LE(file, &m_pEndCondition->m_fArg);
    ReadU32LE(file, &m_pEndCondition->m_unk0c);
    Condition* unused = new Condition;  // OperatorNew(0x10)
    unused->m_unk0c = 0;
    unused->m_i32Type = 0;
    unused->m_i32Arg = 0;
    unused->m_fArg = 0.0f;
    m_pUnk1C = unused;
    ReadS32LE(file, &m_pUnk1C->m_i32Type);
    ReadS32LE(file, &m_pUnk1C->m_i32Arg);
    ReadF32LE(file, &m_pUnk1C->m_fArg);
    LoadNothing(this, file, 0);  // 0x004703a8 KStub_Return1_4703a8
    uint8_t byte = 0;
    ReadU8(file, &byte);
    m_ui32Flags = (m_ui32Flags & 0xfffffffdu) | (static_cast<uint32_t>(byte) << 1);
    ReadU8(file, &byte);
    m_ui32Flags = (m_ui32Flags & 0xfffffffbu) | (static_cast<uint32_t>(byte) << 2);
    int32_t reactions = 0;
    ReadS32LE(file, &reactions);
    int32_t mains = 0;
    ReadS32LE(file, &mains);
    FreshBlock1(m_vReactions);
    for (int32_t i = 0; i < reactions; ++i) {
        uint32_t index = 0;
        ReadU32LE(file, &index);
        ReactionEntry* entry = new ReactionEntry;  // OperatorNew(0x30)
        entry->m_vFromElements.m_ui32NbElt = 1;
        entry->m_vFromElements.m_pBlock = nullptr;
        entry->m_vFromElements.m_ui32NbUsedElt = 0;
        entry->m_vFromIndices.m_ui32NbElt = 1;
        entry->m_vFromIndices.m_pBlock = nullptr;
        entry->m_vFromIndices.m_ui32NbUsedElt = 0;
        entry->m_ui32Element = index;
        entry->m_pElement = nullptr;  // the fresh heap's (PostLoad sets it)
        entry->m_pad12[0] = 0;
        entry->m_pad12[1] = 0;
        entry->m_pSwitchCondition = NewEntryCondition();
        entry->m_pEndCondition = NewEntryCondition();
        ReadEntryCondition(file, entry->m_pSwitchCondition);
        ReadEntryCondition(file, entry->m_pEndCondition);
        ReadU8(file, &entry->m_ui8Chain);
        ReadU8(file, &entry->m_ui8Unk11);
        entry->m_pHook = nullptr;
        IKFile_ReadRef(file, &entry->m_pHook);
        PushBack1(m_vReactions, entry);
        ReactionEntry* current = m_vReactions.m_pBlock[i];
        FreshBlock1(current->m_vFromIndices);
        uint32_t count = 0;
        ReadU32LE(file, &count);
        for (uint32_t j = 0; j < count; ++j) {
            uint32_t from = 0;
            ReadU32LE(file, &from);
            PushBack1(m_vReactions.m_pBlock[i]->m_vFromIndices, from);
        }
    }
    FreshBlock1(m_vMain);
    for (int32_t i = 0; i < mains; ++i) {
        uint32_t index = 0;
        ReadU32LE(file, &index);
        MainEntry* entry = new MainEntry;  // OperatorNew(0x10)
        entry->m_ui32Element = 0;
        entry->m_pElement = nullptr;
        entry->m_pCondition = nullptr;
        entry->m_pHook = nullptr;
        entry->m_ui32Element = index;
        entry->m_pCondition = NewEntryCondition();
        ReadEntryCondition(file, entry->m_pCondition);
        IKFile_ReadRef(file, &entry->m_pHook);
        PushBack1(m_vMain, entry);
    }
    IKFile_ReadRef(file, &m_pHook);
    return 1;
}

// 0x0046d598 CKColossusAttackSequence_PostLoad: the base's (vt+0x78), then every entry's element looked up in the
// colossus' list and every reaction entry's interrupted elements (a fresh one-slot block, then appended).
int32_t CKColossusAttackSequence::PostLoad(int32_t type) {
    CKColossusAttackSequenceBase::PostLoad(type);  // 0x00470428
    CKHkColossus* owner = static_cast<CKHkColossus*>(m_pOwner);
    for (uint32_t i = 0; i < m_vMain.m_ui32NbUsedElt; ++i) {
        MainEntry* entry = m_vMain.m_pBlock[i];
        entry->m_pElement = ColossusElementByIndex(owner, static_cast<int32_t>(entry->m_ui32Element));  // 0x0046bcc8
    }
    for (uint32_t i = 0; i < m_vReactions.m_ui32NbUsedElt; ++i) {
        ReactionEntry* entry = m_vReactions.m_pBlock[i];
        entry->m_pElement = ColossusElementByIndex(owner, static_cast<int32_t>(entry->m_ui32Element));
        entry = m_vReactions.m_pBlock[i];
        FreshBlock1(entry->m_vFromElements);
        for (uint32_t j = 0; j < entry->m_vFromIndices.m_ui32NbUsedElt; ++j) {
            KBase7CCC* element = ColossusElementByIndex(owner, static_cast<int32_t>(entry->m_vFromIndices.m_pBlock[j]));
            PushBack1(entry->m_vFromElements, element);
        }
    }
    return 1;
}

// 0x0046d7d0 CKColossusAttackSequence_Destroy: the base's (empty), both condition blocks deleted, every main entry (its
// condition, then itself) and every reaction entry (its conditions, both blocks freed and cleared, itself) deleted. The
// lists keep their lengths (BUG(original): the destructor frees their blocks only).
void CKColossusAttackSequence::Destroy() {
    CKColossusAttackSequenceBase::Destroy();  // 0x00470478 KStub_Nop_470478
    delete m_pEndCondition;  // 0x00a3ce18
    delete m_pUnk1C;
    for (uint32_t i = 0; i < m_vMain.m_ui32NbUsedElt; ++i) {
        if (m_vMain.m_pBlock[i]->m_pCondition != nullptr) delete m_vMain.m_pBlock[i]->m_pCondition;
        delete m_vMain.m_pBlock[i];
    }
    for (uint32_t i = 0; i < m_vReactions.m_ui32NbUsedElt; ++i) {
        if (m_vReactions.m_pBlock[i]->m_pSwitchCondition != nullptr) delete m_vReactions.m_pBlock[i]->m_pSwitchCondition;
        ReactionEntry* entry = m_vReactions.m_pBlock[i];
        if (entry->m_pEndCondition != nullptr) {
            delete entry->m_pEndCondition;
            entry = m_vReactions.m_pBlock[i];
            if (entry == nullptr) continue;
        }
        if (entry->m_vFromIndices.m_pBlock != nullptr) Mem_FreeAligned16(entry->m_vFromIndices.m_pBlock);
        entry->m_vFromIndices.m_ui32NbUsedElt = 0;
        entry->m_vFromIndices.m_pBlock = nullptr;
        if (entry->m_vFromElements.m_pBlock != nullptr) Mem_FreeAligned16(entry->m_vFromElements.m_pBlock);
        entry->m_vFromElements.m_ui32NbUsedElt = 0;
        entry->m_vFromElements.m_pBlock = nullptr;
        delete entry;
    }
}

// 0x0046d9e0 CKColossusAttackSequence_vf74: fresh one-slot blocks for both lists (the old ones not freed), two new
// condition blocks {1, 0, 0, 0} (the old ones not deleted), no hook, no flags. The base's vt+0x74 is not called.
void CKColossusAttackSequence::Vf74() {
    FreshBlock1(m_vReactions);
    FreshBlock1(m_vMain);
    Condition* end = new Condition;  // OperatorNew(0x10)
    end->m_i32Arg = 0;
    end->m_fArg = 0.0f;
    end->m_unk0c = 0;
    m_pEndCondition = end;
    end->m_i32Type = 1;
    m_pEndCondition->m_fArg = 0.0f;
    m_pEndCondition->m_i32Arg = 0;
    Condition* unused = new Condition;
    unused->m_i32Arg = 0;
    unused->m_fArg = 0.0f;
    unused->m_unk0c = 0;
    m_pUnk1C = unused;
    unused->m_i32Type = 1;
    m_pUnk1C->m_fArg = 0.0f;
    m_pUnk1C->m_i32Arg = 0;
    m_pHook = nullptr;
    m_ui32Flags = 0;
}

// The state machine's call: the pair's descriptor word with bit 0 is a virtual function (vtable offset + 1); the
// three entries Vf50 installs are vt+0x7c / +0x80 / +0x84 with no this-adjust.
uint8_t CKColossusAttackSequence::CallState(uint8_t state, IKTime* frameClock, int32_t phase, uint8_t other) {
    const uint32_t* pair = &m_pStateTable[state * 2u];
    switch (pair[0]) {
        case 0x7d: return Vf7C(frameClock, phase, other);
        case 0x81: return Vf80(frameClock, phase, other);
        case 0x85: return Vf84(frameClock, phase, other);
        default: return other;  // not reached: the table only holds these three
    }
}

// 0x0046e330 CKColossusAttackSequence_StartAttack_maybe (vt+0x50): the base's (the timer 0); with main entries the first
// one starts (its hook given to its element, the element started (vt+0x50) and told the sequence); the three-state
// table installed and state 0 entered (no clock, phase 1, from 0xff); no reaction, flags bits 0 / 1 / 3 cleared; the
// sequence's hook woken in the meca group.
void CKColossusAttackSequence::Vf50() {
    CKColossusAttackSequenceBase::Vf50();  // 0x00470400
    if (m_vMain.m_ui32NbUsedElt != 0) {
        m_i32Main = 0;
        MainEntry* first = m_vMain.m_pBlock[0];
        if (first->m_pHook != nullptr) first->m_pElement->m_pHook = first->m_pHook;
        m_vMain.m_pBlock[m_i32Main]->m_pElement->Vf50();
        m_vMain.m_pBlock[m_i32Main]->m_pElement->m_pSequence = this;
    }
    m_aStateTable[0] = 0x7d;
    m_aStateTable[4] = 0x85;
    m_aStateTable[2] = 0x81;
    m_aStateTable[1] = 0;
    m_aStateTable[3] = 0;
    m_aStateTable[5] = 0;
    m_ui8StateCount = 3;
    m_ui8State = 0;
    m_pStateTable = m_aStateTable;
    CallState(0, nullptr, 1, 0xff);
    m_i32Reaction = -1;
    m_ui32Flags = m_ui32Flags & 0xfffffff4u;
    if (m_pHook != nullptr) SetObjectActiveInContext(g_pEngine->m_coreManager, m_pHook, 1, MecaGroup());  // 0x0001cb10
}

// 0x0046de70 CKColossusAttackSequence_vf54: the running element (the reaction one, else a valid main one) stopped
// (vt+0x54) and its hook cleared; flag bit 0 set; the sequence's hook put to sleep in the meca group.
void CKColossusAttackSequence::Vf54() {
    if (m_i32Reaction == -1) {
        const int32_t main = m_i32Main;
        if (main >= 0 && static_cast<uint32_t>(main) < m_vMain.m_ui32NbUsedElt) {
            m_vMain.m_pBlock[main]->m_pElement->Vf54();
            m_vMain.m_pBlock[m_i32Main]->m_pElement->m_pHook = nullptr;
        }
    } else {
        m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->Vf54();
        m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->m_pHook = nullptr;
    }
    m_ui32Flags = (m_ui32Flags & 0xfffffffeu) | 1u;
    if (m_pHook != nullptr) SetObjectActiveInContext(g_pEngine->m_coreManager, m_pHook, 0, MecaGroup());  // 0x0001cb10
}

// 0x0046ecb8 CKColossusAttackSequence_vf60: the base's (the timer advances), then the state machine's frame: the
// current state's update (phase 0) and, when it answers another state, the leave (phase 2) and the enter (phase 1).
void CKColossusAttackSequence::Vf60(IKTime* frameClock) {
    CKColossusAttackSequenceBase::Vf60(frameClock);  // 0x004703e8
    uint8_t current = m_ui8State;
    if (current == 0xff) return;
    const uint8_t next = CallState(current, frameClock, 0, current);
    current = m_ui8State;
    if (next == current) return;
    if (current != 0xff) CallState(current, frameClock, 2, next);
    m_ui8State = next;
    if (next != 0xff) CallState(next, frameClock, 1, current);
}

// 0x0046d1e0 CKColossusAttackSequence_vf6C: the end condition (+0x18; none or type -1: false), through the jump table
// 0x46d258 (TOC +0x5834): 0 the timer, 1 never, 2 the colossus' count, 3 the first hero within an x / z radius, 4 the
// main list ran out, 5 the hook's bit 0x400, 6 never. BUG(original): a type above 6 calls a null descriptor; false here.
uint8_t CKColossusAttackSequence::Vf6C() {
    const Condition* condition = m_pEndCondition;
    if (condition == nullptr || condition->m_i32Type == -1) return 0;
    switch (static_cast<uint32_t>(condition->m_i32Type)) {
        case 0: return SequenceTimeAbove(this, condition);
        case 1: return 0;  // 0x009c4268 KStub_Return0_9c4268
        case 2: return SequenceOwnerCountAtMost(this, condition);
        case 3:  // 0x009c4338 (F06's port): the sequence's owner hook against the condition's radius
            return ColossusCond_IsHeroWithinRadiusXZ(static_cast<IKHook*>(m_pOwner), condition->m_fArg) ? 1 : 0;
        case 4: return SequenceMainRanOut(this, condition);
        case 5: return SequenceHookFlag400(this, condition);
        case 6: return 0;  // 0x009c42d0 KStub_Return0_9c42d0
        default: return 0;
    }
}

// 0x0046dfc0 CKColossusAttackSequence_TrySwitchToMatchingList24Entry_maybe: the first reaction entry whose switch
// condition holds takes over: the running element (the reaction one, else the main one) stopped and its hook cleared,
// the entry's element started with the entry's hook and told the sequence; 1. BUG(original): an entry with no
// interrupted elements, or one that does not list the running element, ends the search (0) instead of being skipped;
// an entry whose condition type is -1 is skipped. Switch condition types: 0 the hero beyond a radius, 1 never (another
// type calls a null descriptor on the PS3; false here).
uint8_t CKColossusAttackSequence::TrySwitchToReaction() {
    uint32_t count = m_vReactions.m_ui32NbUsedElt;
    for (uint32_t i = 0; i < count; ++i) {
        ReactionEntry* entry = m_vReactions.m_pBlock[i];
        const uint32_t n = entry->m_vFromElements.m_ui32NbUsedElt;
        if (n == 0) return 0;
        KBase7CCC* running = m_i32Reaction == -1 ? m_vMain.m_pBlock[m_i32Main]->m_pElement
                                                 : m_vReactions.m_pBlock[m_i32Reaction]->m_pElement;
        uint32_t at = 0;
        while (entry->m_vFromElements.m_pBlock[at] != running) {
            if (++at == n) return 0;
        }
        entry = m_vReactions.m_pBlock[i];
        const Condition* condition = entry->m_pSwitchCondition;
        if (condition->m_i32Type == -1) continue;
        uint8_t holds = 0;
        if (condition->m_i32Type == 0) {
            // 0x009c43e8 (descriptor 0xbbf7b0, F06's port): the element's owner hook against the condition's radius.
            holds = ColossusCond_IsHeroBeyondRadius(entry->m_pElement->m_pOwner, condition->m_fArg) ? 1 : 0;
        } else if (condition->m_i32Type == 1) {
            holds = 0;  // 0x009c42f8 KStub_Return0_9c42f8
        }
        if (holds == 0) {
            count = m_vReactions.m_ui32NbUsedElt;
            continue;
        }
        if (m_i32Reaction == -1) {
            m_vMain.m_pBlock[m_i32Main]->m_pElement->Vf54();
            m_vMain.m_pBlock[m_i32Main]->m_pElement->m_pHook = nullptr;
        } else {
            m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->Vf54();
            m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->m_pHook = nullptr;
        }
        m_i32Reaction = static_cast<int32_t>(i);
        ReactionEntry* next = m_vReactions.m_pBlock[i];
        if (next->m_pHook != nullptr) next->m_pElement->m_pHook = next->m_pHook;
        m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->Vf50();
        m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->m_pSequence = this;
        return 1;
    }
    return 0;
}

// 0x0046e508 CKColossusAttackSequence_AdvanceToNextList30Entry_maybe: the running element (the reaction one, else the
// main one) stopped and its hook cleared; the next main entry, past the end the first one when the list loops (flag
// bit 2) or none (-1, flag bit 1 set, 0); the entry's element started with the entry's hook and told the sequence; 1.
uint8_t CKColossusAttackSequence::AdvanceToNextMain() {
    if (m_i32Reaction == -1) {
        m_vMain.m_pBlock[m_i32Main]->m_pElement->Vf54();
        m_vMain.m_pBlock[m_i32Main]->m_pElement->m_pHook = nullptr;
    } else {
        m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->Vf54();
        m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->m_pHook = nullptr;
    }
    uint32_t next = static_cast<uint32_t>(m_i32Main) + 1;
    m_i32Main = static_cast<int32_t>(next);
    if (m_vMain.m_ui32NbUsedElt <= next) {
        if ((m_ui32Flags & 4u) == 0) {
            m_i32Main = -1;
            m_ui32Flags = m_ui32Flags | 2u;
            return 0;
        }
        next = 0;
        m_i32Main = 0;
    }
    MainEntry* entry = m_vMain.m_pBlock[next];
    if (entry->m_pHook != nullptr) entry->m_pElement->m_pHook = entry->m_pHook;
    m_vMain.m_pBlock[m_i32Main]->m_pElement->Vf50();
    m_vMain.m_pBlock[m_i32Main]->m_pElement->m_pSequence = this;
    return 1;
}

// 0x0046eab0 CKColossusAttackSequence_vf7C, state 0 (the main list). Frames only (other phases answer `other`): with a
// valid main entry (BUG(original): the bound test lets the index equal the length through), its condition: when it
// holds, a running element with flag bit 2 may hand over to a reaction entry (which then runs, state 1), else the next
// main entry starts (none left: `other`, nothing runs). The main element runs (vt+0x60).
uint8_t CKColossusAttackSequence::Vf7C(IKTime* frameClock, int32_t phase, uint8_t other) {
    if (phase != 0) return other;
    const int32_t main = m_i32Main;
    if (main < 0 || m_vMain.m_ui32NbUsedElt < static_cast<uint32_t>(main)) return other;
    MainEntry* entry = m_vMain.m_pBlock[main];
    const Condition* condition = entry->m_pCondition;
    if (condition->m_i32Type != -1 && EvalRunCondition(entry->m_pElement, condition) != 0) {
        if ((m_vMain.m_pBlock[m_i32Main]->m_pElement->m_ui32Flags & 4u) != 0 && TrySwitchToReaction() != 0) {
            m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->Vf60(frameClock);
            return 1;
        }
        if (AdvanceToNextMain() == 0) return other;
    }
    m_vMain.m_pBlock[m_i32Main]->m_pElement->Vf60(frameClock);
    return other;
}

// 0x0046e708 CKColossusAttackSequence_vf80, state 1 (the reaction list). Frames only: with a valid reaction entry (the
// same lax bound test), its hook with bit 0x400 makes the manager switch to the next sequence (state 2). Else its end
// condition: when it holds, a chained entry (+0x10) stops its element and starts the next reaction entry (the first
// after the last); an unchained one hands over to another reaction entry (its element's flag bit 2) or else goes back
// to the next main entry (whose element runs, state 0). The reaction element runs (vt+0x60).
uint8_t CKColossusAttackSequence::Vf80(IKTime* frameClock, int32_t phase, uint8_t other) {
    if (phase != 0) return other;
    const int32_t reaction = m_i32Reaction;
    if (reaction < 0 || m_vReactions.m_ui32NbUsedElt < static_cast<uint32_t>(reaction)) return other;
    ReactionEntry* entry = m_vReactions.m_pBlock[reaction];
    if (entry->m_pHook != nullptr && (entry->m_pHook->m_bitArray & 0x400u) != 0) {
        m_pManager->SwitchToSequence(m_ui32Index + 1);  // 0x0046b620
        return 2;
    }
    entry = m_vReactions.m_pBlock[reaction];
    const Condition* condition = entry->m_pEndCondition;
    if (condition->m_i32Type != -1 && EvalRunCondition(entry->m_pElement, condition) != 0) {
        ReactionEntry* current = m_vReactions.m_pBlock[m_i32Reaction];
        if (current->m_ui8Chain != 0) {
            current->m_pElement->Vf54();
            m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->m_pHook = nullptr;
            if (static_cast<uint32_t>(m_i32Reaction) < m_vReactions.m_ui32NbUsedElt - 1) {
                m_i32Reaction = m_i32Reaction + 1;
            } else {
                m_i32Reaction = 0;
            }
            ReactionEntry* next = m_vReactions.m_pBlock[m_i32Reaction];
            if (next->m_pHook != nullptr) next->m_pElement->m_pHook = next->m_pHook;
            m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->Vf50();
            m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->m_pSequence = this;
        } else if ((current->m_pElement->m_ui32Flags & 4u) == 0 || TrySwitchToReaction() == 0) {
            AdvanceToNextMain();
            // BUG(original): when the main list ran out (no loop) the index is -1 and the PS3 runs the word before the
            // block as an entry; dotd skips the run.
            if (m_i32Main >= 0) m_vMain.m_pBlock[m_i32Main]->m_pElement->Vf60(frameClock);
            m_i32Reaction = -1;
            return 0;
        }
    }
    m_vReactions.m_pBlock[m_i32Reaction]->m_pElement->Vf60(frameClock);
    return other;
}
