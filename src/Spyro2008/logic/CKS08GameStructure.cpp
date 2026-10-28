// CKS08GameStructure.cpp - reconstructed original translation unit 0x50f2c8-0x5122f8 (GAME_TOC1, main_toc1), 41 functions, 38 live.
// Primary class: CKS08GameStructure  key 0x798c  category Logic  size 0x254  vtable 0xb2b5d8
// Other owners: PlayerProgress (1), ComputeCynderHealthCapacity (1), ComputeSpyroHealthCapacity (1), CountManaUpgradesEarned (1), CountHealthUpgradesEarned (1), ComputeCynderManaCapacity (1), ComputeSpyroManaCapacity (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x50f2c8  CKS08GameStructure_ResetProgress_maybe
//   [ ] 0x50f590  CKS08GameStructure_ShowCenterMessageOnce_maybe
//   [ ] 0x50f638  CKS08GameStructure_CountLevelItemsByCategory_maybe
//   [ ] 0x50f730  CKS08GameStructure_CountItemsByCategory_maybe
//   [x] 0x50f958  CKS08GameStructure_vf58
//   [x] 0x50f980  CKS08GameStructure_vf5C
//   [ ] 0x50f9a8  CKS08GameStructure_PostLoad
//   [ ] 0x50f9d0  CKS08GameStructure_Save
//   [ ] 0x50f9f8  CKS08GameStructure_RecursiveRegistration
//   [ ] 0x50fa20  CKS08GameStructure_DestroyGame
//   [x] 0x50fc58  CKS08GameStructure_Destroy
//   [ ] 0x50fc80  CKS08GameStructure_Construct_2
//   [x] 0x50fdd8  CKS08GameStructure_Construct
//   [x] 0x50ff30  CKS08GameStructure_DeleteArray
//   [ ] 0x50ffd0  RegisterCKS08GameStructureClass
//   [ ] 0x510058  _GLOBAL__D_510058
//   [ ] 0x510068  _GLOBAL__I_510068
//   [ ] 0x510078  CKS08GameStructure_IsArmorPieceCollected_maybe
//   [ ] 0x510158  CKS08GameStructure_CountCollectedOfTypeInLevel_maybe
//   [ ] 0x510238  CKS08GameStructure_CountCollectedOfTypeAllLevels_maybe  [dead]
//   [ ] 0x5102e0  CKS08GameStructure_AreInfoPopupsEnabled_maybe
//   [x] 0x5102f0  CKS08GameStructure_CreateArray
//   [x] 0x5104c8  CreateCKS08GameStructure
//   [x] 0x510640  CKS08GameStructure_RecordBestCombo_maybe
//   [x] 0x5106c0  CKS08GameStructure_SetUnlockFlagByte_maybe
//   [ ] 0x510748  PlayerProgress_AddElementGems_maybe
//   [x] 0x5108d0  CKS08GameStructure_Load
//   [ ] 0x510da0  CKS08GameStructure_Destructor
//   [x] 0x511060  ComputeCynderHealthCapacity
//   [x] 0x5111a0  ComputeSpyroHealthCapacity
//   [ ] 0x5112e0  CountManaUpgradesEarned_maybe
//   [ ] 0x511458  CountHealthUpgradesEarned_maybe
//   [x] 0x5115d0  ComputeCynderManaCapacity
//   [x] 0x511710  ComputeSpyroManaCapacity
//   [ ] 0x511850  GetManaItemsTowardNextUpgrade_maybe
//   [ ] 0x511980  GetHealthItemsTowardNextUpgrade_maybe
//   [ ] 0x511ab0  CKS08GameStructure_Destructor_2
//   [ ] 0x511d70  CKS08GameStructure_DeletingDestructor
//   [ ] 0x512040  KBase730C_SetItemState
//   [ ] 0x512208  FUN_00512208  [dead]
//   [ ] 0x512280  FUN_00512280  [dead]
//
//   [ ] 0x9c7208  CKS08GameStructure_IsKindOfClass  [inline]
//   [x] 0x9c7230  CKS08GameStructure_GetClassType  [inline]
//   [x] 0x9c7238  CKS08GameStructure_GetClassID  [inline]
#include "Spyro2008/logic/CKS08GameStructure.h"

#include <cstring>
#include <initializer_list>

#include "Spyro2008/logic/CKS08GameLevel.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/GameVector.h"

// 0x0050fdd8 CKS08GameStructure_Construct: IKGameStructure's, the vtable, then the twelve byte lists.
// The other fields are left as they are.
CKS08GameStructure::CKS08GameStructure() {
    for (TVector<uint8_t, 8>& list : m_avbUnk154) {
        list.m_pBlock = nullptr;
        list.m_ui32NbUsedElt = 0;
        list.m_ui32NbElt = 8;
    }
}

// 0x0050fc58 CKS08GameStructure_Destroy: IKGameStructure's (0x41910).
void CKS08GameStructure::Destroy() { IKGameStructure::Destroy(); }

// 0x005108d0 CKS08GameStructure_Load. It calls IKGameStructure's Load (0x41f90) directly.
int32_t CKS08GameStructure::Load(IKFile* file, int32_t type) {
    IKGameStructure::Load(file, type);
    if (type != K_GAME_PLATEFORMS) return 1;
    ReadU8(file, &HealthDivisor0());
    ReadU8(file, &HealthDivisor1());
    ReadU32LE(file, &m_dwHealthMultiplier);
    ReadU32LE(file, &m_dwHealthBase);
    ReadU32LE(file, &m_unk58);
    ReadU8(file, &m_bManaDivisor0);
    ReadU8(file, &m_bManaDivisor1);
    ReadU32LE(file, &m_dwManaMultiplier);
    ReadU32LE(file, &m_dwManaBase);
    ReadU32LE(file, &m_unk70);
    ReadU32LE(file, &m_unk80);
    ReadU32LE(file, &m_unk7c);
    ReadU32LE(file, &m_unk1ec);
    // Twelve lengths: each list gets a block of exactly that many bytes (one for 0), then the length.
    for (TVector<uint8_t, 8>& list : m_avbUnk154) {
        uint32_t length = 0;
        ReadU32LE(file, &length);
        GameVector_Allocate(&list, length);
        GameVector_Resize(&list, length);  // the capacity is already enough: only the length
    }
    return 1;
}

// 0x0050f2c8 CKS08GameStructure_ResetProgress_maybe (from the assembly; the stores in its order, word or
// byte as there). The run-time fields are raw bytes: Word/Byte write at their PS3 offsets in m_unk84,
// m_unk1e4 and m_unk1f0.
void CKS08GameStructure::ResetProgress() {
    auto bytes = [this](uint32_t offset) -> uint8_t* {
        if (offset >= 0x1f0) return &m_unk1f0[offset - 0x1f0];
        if (offset >= 0x1e4) return &m_unk1e4[offset - 0x1e4];
        return &m_unk84[offset - 0x84];
    };
    auto word = [&](uint32_t offset, uint32_t value) { std::memcpy(bytes(offset), &value, 4); };
    auto byte = [&](uint32_t offset, uint8_t value) { *bytes(offset) = value; };
    m_unk4c = m_dwHealthBase;
    m_unk54 = m_unk58;
    m_unk64 = m_dwManaBase;
    m_unk6c = m_unk70;
    word(0xa0, 0);
    m_pCurrentSpawnPoint = nullptr;  // +0x08
    m_unk74 = 0;
    m_unk78 = 0;
    for (uint32_t o : {0x84u, 0x88u, 0x9cu, 0x98u, 0x94u, 0x90u, 0x8cu, 0xb0u, 0xacu, 0xa8u, 0xa4u}) word(o, 0);
    for (int32_t i = 1; i >= 0; --i) {  // two triples of 3
        byte(0xb6 + i * 3, 3);
        byte(0xb5 + i * 3, 3);
        byte(0xb4 + i * 3, 3);
    }
    byte(0xfc, 0);  word(0x144, 0); byte(0xba, 0); byte(0xbb, 0);
    word(0x100, 0); byte(0x104, 0); word(0x108, 0);
    byte(0xec, 0);  word(0xf0, 0);  byte(0xf4, 0); word(0xf8, 0);
    byte(0xdc, 0);  word(0xe0, 0);  byte(0xe4, 0); word(0xe8, 0);
    byte(0xcc, 0);  word(0xd0, 0);  byte(0xd4, 0); word(0xd8, 0);
    byte(0xbc, 0);  word(0xc0, 0);  byte(0xc4, 0); word(0xc8, 0);
    for (uint32_t o : {0x110u, 0x118u, 0x148u, 0x10cu, 0x114u, 0x12cu, 0x128u, 0x124u, 0x120u, 0x11cu, 0x140u, 0x130u,
                       0x13cu, 0x138u, 0x134u})
        word(o, 0);
    // The twelve byte lists: every used byte cleared (the length kept).
    for (TVector<uint8_t, 8>& list : m_avbUnk154) {
        for (uint32_t i = list.m_ui32NbUsedElt; i != 0; --i) list.m_pBlock[i - 1] = 0;
    }
    byte(0x1e9, 0);
    word(0x1f0, m_unk4c);
    word(0x1f4, m_unk54);
    word(0x1f8, m_unk64);
    word(0x1fc, m_unk6c);
    word(0x224, 0);
    for (uint32_t o = 0x1e4; o <= 0x1e8; ++o) byte(o, 0);
    for (uint32_t o : {0x200u, 0x204u, 0x208u, 0x20cu, 0x220u, 0x21cu, 0x218u, 0x214u, 0x210u, 0x234u, 0x230u, 0x22cu,
                       0x228u})
        word(o, 0);
    for (int32_t i = 1; i >= 0; --i) {
        byte(0x23a + i * 3, 3);
        byte(0x239 + i * 3, 3);
        byte(0x238 + i * 3, 3);
    }
    byte(0x250, 0);
    for (uint32_t o = 0x23f; o <= 0x24f; ++o) byte(o, 0);
}

// ---- C1.6 gm ----
uint8_t& CKS08GameStructure::RtByte(uint32_t offset) {
    if (offset >= 0x1f0) return m_unk1f0[offset - 0x1f0];
    if (offset >= 0x1e4) return m_unk1e4[offset - 0x1e4];
    return m_unk84[offset - 0x84];
}

uint32_t CKS08GameStructure::RtWord(uint32_t offset) const {
    uint32_t value;
    std::memcpy(&value, &const_cast<CKS08GameStructure*>(this)->RtByte(offset), 4);
    return value;
}

void CKS08GameStructure::SetRtWord(uint32_t offset, uint32_t value) { std::memcpy(&RtByte(offset), &value, 4); }

// 0x0050f958 CKS08GameStructure_vf58: IKGameStructure's (0x41448).
void CKS08GameStructure::Vf58() { IKGameStructure::Vf58(); }

// 0x0050f980 CKS08GameStructure_vf5C: IKGameStructure's (0x41598).
void CKS08GameStructure::ApplyGameStateToLevel() { IKGameStructure::ApplyGameStateToLevel(); }

namespace {
// The four capacity functions' shared part: the sum over the stages of CountStatEntriesByCategory(stage,
// category, include ^ 1), cached per mode in the run-time bytes at `base` (include != 0: flag +0, count
// +4) and `base + 8` (include == 0: flag +0, count +4), then (count / divisor) * multiplier + base value.
uint32_t CountCapacityItems(CKS08GameStructure* structure, uint8_t include, uint8_t category, uint32_t base) {
    const uint32_t flagOffset = include == 0 ? base + 8 : base;
    if (structure->RtByte(flagOffset) != 0) return structure->RtWord(flagOffset + 4);
    uint32_t total = 0;
    for (uint32_t i = structure->m_vpStages.m_ui32NbUsedElt; i != 0; --i) {
        total += CountStatEntriesByCategory(static_cast<CKS08GameLevel*>(structure->m_vpStages.m_pBlock[i - 1]), category,
                                            include ^ 1);
    }
    structure->SetRtWord(flagOffset + 4, total);
    structure->RtByte(flagOffset) = 1;
    return total;
}
}  // namespace

// 0x00511060 ComputeCynderHealthCapacity: health items (category 1) / divisor +0x46 * multiplier +0x48 + base +0x50.
int32_t ComputeCynderHealthCapacity(CKS08GameStructure* structure, uint8_t include) {
    const uint32_t total = CountCapacityItems(structure, include, 1, 0xcc);
    return static_cast<int32_t>(ppc::divwu(total, structure->HealthDivisor1()) * structure->m_dwHealthMultiplier +
                                structure->m_dwHealthBase);
}

// 0x005111a0 ComputeSpyroHealthCapacity: the same with divisor +0x45.
int32_t ComputeSpyroHealthCapacity(CKS08GameStructure* structure, uint8_t include) {
    const uint32_t total = CountCapacityItems(structure, include, 1, 0xcc);
    return static_cast<int32_t>(ppc::divwu(total, structure->HealthDivisor0()) * structure->m_dwHealthMultiplier +
                                structure->m_dwHealthBase);
}

// 0x005115d0 ComputeCynderManaCapacity: mana items (category 2) / divisor +0x5d * multiplier +0x60 + base +0x68.
int32_t ComputeCynderManaCapacity(CKS08GameStructure* structure, uint8_t include) {
    const uint32_t total = CountCapacityItems(structure, include, 2, 0xdc);
    return static_cast<int32_t>(ppc::divwu(total, structure->m_bManaDivisor1) * structure->m_dwManaMultiplier +
                                structure->m_dwManaBase);
}

// 0x00511710 ComputeSpyroManaCapacity: the same with divisor +0x5c.
int32_t ComputeSpyroManaCapacity(CKS08GameStructure* structure, uint8_t include) {
    const uint32_t total = CountCapacityItems(structure, include, 2, 0xdc);
    return static_cast<int32_t>(ppc::divwu(total, structure->m_bManaDivisor0) * structure->m_dwManaMultiplier +
                                structure->m_dwManaBase);
}

// 0x00510640 CKS08GameStructure_RecordBestCombo_maybe
void CKS08GameStructure::RecordBestCombo(int32_t dragon, uint32_t combo) {
    uint32_t best = RtWord(0x114 + static_cast<uint32_t>(dragon) * 4);
    if (best < combo) best = combo;
    SetRtWord(0x114 + static_cast<uint32_t>(dragon) * 4, best);
    if (combo > 0x95) {
        // CKS08GameManager_ShowCenterMessage_maybe(owner, 2) 0x501860 (the centre screen's message queue):
        // STUB(C2.7, moved from C2.6: combat), a combo of 150 hits needs the hero.
        if (RtByte(0x24d) == 0) DOTD_STUB_ONCE("CKS08GameStructure_RecordBestCombo_maybe: ShowCenterMessage_maybe (C2.7, moved from C2.6)");
        RtByte(0x24d) = 1;
    }
}

// 0x005102e0 CKS08GameStructure_AreInfoPopupsEnabled_maybe
uint8_t CKS08GameStructure::AreInfoPopupsEnabled() const { return m_pGameManager->m_editedOptions.m_unk05; }

// 0x005106c0 CKS08GameStructure_SetUnlockFlagByte_maybe. STUB(C2.7 step 7, HUD): the centre message 4 of the first unlock of
// index 9 (CKS08GameManager_ShowCenterMessage_maybe 0x501860).
void CKS08GameStructure::SetUnlockFlagByte(int32_t index, uint8_t value) {
    RtByte(static_cast<uint32_t>(0x23f + index)) = value;
    if (value == 0 || index != 9) return;
    if (RtByte(0x24f) == 0) DOTD_STUB_ONCE("CKS08GameStructure_SetUnlockFlagByte_maybe: ShowCenterMessage_maybe(4) 0x501860 (C2.7 HUD)");
    RtByte(0x24f) = 1;
}
