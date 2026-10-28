// CKInputBlockSequential.cpp - reconstructed original translation unit 0x205290-0x209a90 (GAME_TOC1, main_toc1), 58 functions, 49 live.
// Primary class: CKInputBlockSequential  key 0x624c  category Logic  size 0x8c  vtable 0xb1f230
// Other owners: InputBlock (3), PS3_CKInputBlockPosition (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x205290  CKInputBlockSequential_Delete
//   [ ] 0x2052e0  CKInputBlockSequential_FindActionBlockById_maybe
//   [ ] 0x2054b0  CKInputBlockSequential_GetActiveActionBlock_maybe
//   [ ] 0x2055b8  CKInputBlockSequential_GetActiveBlockStep_maybe  [dead]
//   [x] 0x205660  CKInputBlockSequential_ComputeStepCount_maybe
//   [ ] 0x2057e8  KStub_ReturnFloat0_2057e8  [dead]
//   [ ] 0x2057f0  CKInputBlockSequential_IsAnyActionActive_maybe  [dead]
//   [ ] 0x205930  CKInputBlockSequential_RecomputeCommonValue1C_maybe
//   [ ] 0x205b08  CKInputBlockSequential_RecomputeCommonValue20_maybe
//   [x] 0x205ce0  CKInputBlockSequential_PushActiveChild_maybe
//   [x] 0x205cf0  CKInputBlockSequential_RemoveActiveChild_maybe
//   [ ] 0x205d60  RegisterCKInputBlockSequentialClass
//   [ ] 0x205de8  _GLOBAL__D_205de8
//   [ ] 0x205df8  _GLOBAL__I_205df8
//   [ ] 0x205e08  CKInputBlockSequential_vf90
//   [ ] 0x205e70  CKInputBlockSequential_Save
//   [ ] 0x205e98  CKInputBlockSequential_RecursiveRegistration
//   [ ] 0x205ec0  CKInputBlockSequential_Destroy
//   [x] 0x205f58  CKInputBlockSequential_Construct
//   [ ] 0x205fc8  CKInputBlockSequential_Construct_2
//   [x] 0x206038  CKInputBlockSequential_DeleteArray
//   [ ] 0x2060d8  CKInputBlockSequential_vfA0
//   [ ] 0x2061c0  CKInputBlockSequential_vf70
//   [ ] 0x2062b0  CKInputBlockSequential_vf9C
//   [ ] 0x206398  CKInputBlockSequential_vf80
//   [ ] 0x206498  CKInputBlockSequential_vfB4
//   [ ] 0x206580  CKInputBlockSequential_vfB0
//   [ ] 0x206668  CKInputBlockSequential_vfA8
//   [ ] 0x206750  CKInputBlockSequential_vfA4
//   [ ] 0x206838  CKInputBlockSequential_vf98
//   [ ] 0x206970  CKInputBlockSequential_vf78
//   [ ] 0x206aa8  CKInputBlockSequential_vf60
//   [ ] 0x206bc8  CKInputBlockSequential_vfC0
//   [ ] 0x206c50  CKInputBlockSequential_vfBC
//   [ ] 0x206cd8  CKInputBlockSequential_GetActivePositionNormalizedPtr_maybe  [dead]
//   [ ] 0x206d10  CKInputBlockSequential_vf8C
//   [ ] 0x206e18  CKInputBlockSequential_GetActivePositionScaled_maybe  [dead]
//   [x] 0x206eb0  CKInputBlockSequential_OnActivate
//   [x] 0x207158  CKInputBlockSequential_OnDeactivate
//   [ ] 0x207388  CKInputBlockSequential_DestructBody
//   [ ] 0x207428  CKInputBlockSequential_DeletingDestructor
//   [ ] 0x2074d8  CKInputBlockSequential_Destructor
//   [ ] 0x207578  CKInputBlockSequential_DetachChild_maybe
//   [ ] 0x207740  FUN_00207740  [dead]
//   [ ] 0x207850  FUN_00207850  [dead]
//   [ ] 0x207960  FUN_00207960  [dead]
//   [ ] 0x207a70  FUN_00207a70  [dead]
//   [ ] 0x207c38  CKInputBlockSequential_CollectAnchors_maybe
//   [x] 0x2080e8  CKInputBlockSequential_CreateArray
//   [x] 0x2081e0  CKInputBlockSequential_Create
//   [x] 0x208268  CKInputBlockSequential_Load
//   [x] 0x2088b0  CKInputBlockSequential_Evaluate
//   [x] 0x208c68  CKInputBlockSequential_Update_maybe
//   [ ] 0x2090c8  CKInputBlockSequential_RefreshButtonMaskUpward_maybe
//   [ ] 0x2096b8  InputBlock_AddChild_maybe
//   [ ] 0x209998  PS3_CKInputBlockPosition_vf60
//   [x] 0x209a10  InputBlock_CallActivate_maybe
//   [x] 0x209a50  InputBlock_CallDeactivate_maybe
//
//   [ ] 0x9b1758  CKInputBlockSequential_IsKindOfClass  [inline]
//   [ ] 0x9b1790  CKInputBlockSequential_GetClassType  [inline]
//   [ ] 0x9b1798  CKInputBlockSequential_GetClassID  [inline]
//   [ ] 0x9b17a0  CKInputBlockSequential_vf74  [inline]
//   [ ] 0x9b17b0  CKInputBlockSequential_vf7C  [inline]
//   [x] 0x9b17c0  CKInputBlockSequential_vf94  [inline]
//   [ ] 0x9b17d0  CKInputBlockSequential_vfAC  [inline]
//   [ ] 0x9b17d8  CKInputBlockSequential_vfB8  [inline]
//   [ ] 0x9b17e0  CKInputBlockSequential_vf88  [inline]
#include "k2000/logic/input/CKInputBlockSequential.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKOutputAnchor.h"
#include "k2000/logic/input/CKInputAnchor.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvInput.h"

// 0x00205f58 CKInputBlockSequential_Construct
CKInputBlockSequential::CKInputBlockSequential() {
    m_vUnk2c.m_pBlock = nullptr;
    m_vUnk2c.m_ui32NbElt = 1;
    m_vUnk2c.m_ui32NbUsedElt = 0;
    m_vUnk38.m_ui32NbElt = 1;
    m_vUnk38.m_pBlock = nullptr;
    m_vUnk38.m_ui32NbUsedElt = 0;
    m_unk44 = nullptr;
}

// 0x00208268 CKInputBlockSequential_Load
int32_t CKInputBlockSequential::Load(IKFile* file, int32_t type) {
    KBase628C::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    m_unk18 = 3;
    ReadS32LE(file, &m_unk1c);
    ReadS32LE(file, &m_unk20);
    ReadS32LE(file, &m_unk24);
    m_unk28 = 0.0f;
    ReadRaw(file, &m_unk88, 1);

    // The word vector: sized like the reference vectors (1 when 0), then one Read of count words.
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        m_vUnk2c.m_ui32NbElt = 1;
        m_vUnk2c.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(4));
    } else {
        m_vUnk2c.m_ui32NbElt = count;
        m_vUnk2c.m_pBlock = static_cast<uint32_t*>(Mem_AllocAligned16(count * 4));
    }
    if (m_vUnk2c.m_ui32NbElt < count) {  // as in the original: cannot happen
        uint32_t capacity = count + 1;
        if (capacity == 0) capacity = 1;
        m_vUnk2c.m_pBlock = static_cast<uint32_t*>(Mem_ReallocAligned16(m_vUnk2c.m_pBlock, capacity * 4));
        m_vUnk2c.m_ui32NbElt = capacity;
    }
    m_vUnk2c.m_ui32NbUsedElt = count;
    ReadU32LEWords(file, m_vUnk2c.m_pBlock, count);

    KAnchor_LoadRefVector(file, &m_vUnk38);
    m_unk54 = nullptr;
    m_unk44 = nullptr;
    m_unk48 = 0;
    m_unk4c = nullptr;
    m_unk50 = nullptr;
    ReadF32LE(file, &m_unk58);
    ReadF32LE(file, &m_unk5c);
    ReadF32LE(file, &m_unk60);
    m_unk6c = 0.0f;
    m_unk64 = 0.0f;
    m_unk68 = 0.0f;
    IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_apUnk70), 2);
    IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_apUnk78), 2);
    IKFile_ReadObjectRefArray(file, reinterpret_cast<IKSerializable**>(m_apUnk80), 2);
    m_unk88 = static_cast<uint8_t>((m_unk88 & 0xf0) | (m_unk88 & 0x03));  // rlwinm pair: bits 2 and 3 cleared
    return 1;
}

// The +0x88 pulse bits, as the original's rlwinm pairs write them.
namespace {
inline uint8_t ClearPulseBits(uint8_t b) { return static_cast<uint8_t>((b & 0xf0) | (b & 0x03)); }  // bits 2, 3
inline uint8_t ClearBit2(uint8_t b) { return static_cast<uint8_t>((b & 0xf8) | (b & 0x03)); }
inline uint8_t ClearBit3(uint8_t b) { return static_cast<uint8_t>((b & 0xf0) | (b & 0x07)); }

// The step index of the current block (+0x50), else of +0x4c, when that block is active; else -1 (inlined
// twice in CKInputBlockSequential_Update_maybe).
int32_t CurrentStepIndex(const CKInputBlockSequential* block) {
    KBase60CC* current = block->m_unk50;
    if (current == nullptr || current->m_unk0e == 0) {
        current = block->m_unk4c;
        if (current == nullptr || current->m_unk0e == 0) return -1;
    }
    return static_cast<KBase628C*>(current)->GetStepIndex();  // vt+0x94
}
}  // namespace

// 0x00205660 CKInputBlockSequential_ComputeStepCount_maybe
void CKInputBlockSequential::ComputeStepCount(int32_t* count, uint8_t flag) {
    uint32_t i = 0;
    while (i < m_vUnk38.m_ui32NbUsedElt) {
        IKSerializable* child = m_vUnk38.m_pBlock[i];
        ++i;
        if (child->IsKindOfClass(0x628c) == 0) continue;  // vt+0x08: KBase628C
        KBase628C* block = static_cast<KBase628C*>(child);
        if (*count <= block->GetStepIndex()) *count = block->GetStepIndex() + 1;  // vt+0x94, called twice
        if (child->IsKindOfClass(0x624c) == 0) continue;  // CKInputBlockSequential
        static_cast<CKInputBlockSequential*>(child)->ComputeStepCount(count, flag);
    }
}

// 0x00205ce0 CKInputBlockSequential_PushActiveChild_maybe
void CKInputBlockSequential::PushActiveChild(KBase60CC* child) {
    child->m_unk04 = m_unk44;
    m_unk44 = child;
}

// 0x00205cf0 CKInputBlockSequential_RemoveActiveChild_maybe (the same unlink as
// CKSrvInput_RemoveActiveBlock_maybe 0x202460).
void CKInputBlockSequential::RemoveActiveChild(KBase60CC* child) {
    KBase60CC* node = m_unk44;
    if (node == nullptr) return;
    if (child == node) {
        m_unk44 = child->m_unk04;
    } else {
        KBase60CC* previous;
        do {
            previous = node;
            node = previous->m_unk04;
            if (node == nullptr) return;
        } while (child != node);
        previous->m_unk04 = child->m_unk04;
        if (child->m_unk04 != nullptr) child->m_unk04 = nullptr;
    }
    child->m_unk04 = nullptr;
}

// 0x00206eb0 CKInputBlockSequential_OnActivate
void CKInputBlockSequential::OnActivate() {
    KBase628C::OnActivate();  // bl 0x209a10
    if (m_unk20 != -1 && m_unk1c != -1 && m_unk08 != nullptr) {
        // This block becomes the current one (+0x50) of each ancestor up to the first with a step index
        // (that one included only when it is the root).
        m_unk50 = this;
        CKInputBlockSequential* parent = static_cast<CKInputBlockSequential*>(m_unk08);
        for (;;) {
            if (parent->GetStepIndex() != -1) {  // vt+0x94
                if (parent->m_unk08 == nullptr) parent->m_unk50 = this;
                break;
            }
            parent->m_unk50 = this;
            if (parent->m_unk08 == nullptr) break;
            parent = static_cast<CKInputBlockSequential*>(parent->m_unk08);
        }
    }
    if (m_unk08 != nullptr && static_cast<KBase60CC*>(m_unk08)->m_unk08 == nullptr) {
        static_cast<CKSrvInput*>(g_pEngine->m_srvInput)->m_unk30 = this;
        static_cast<CKInputBlockSequential*>(m_unk08)->m_unk54 = this;
    }
    m_unk68 = m_unk64;
    m_unk28 = 0.0f;  // stw 0
    m_unk24 = 0;
    m_unk18 = 0;
    ComputeStepCount(&m_unk24, 1);
    m_apUnk70[0]->SetValue(0);  // vt+0x58
    m_apUnk70[1]->SetValue(0);
    m_apUnk78[0]->SetValue(0);
    m_apUnk78[1]->SetValue(0);
    m_apUnk80[0]->SetValue(0);
    m_apUnk80[1]->SetValue(0);
    m_apUnk70[0]->SetValue(1);  // the "activated" pulse
    m_apUnk70[0]->SetValue(0);
}

// 0x00207158 CKInputBlockSequential_OnDeactivate
void CKInputBlockSequential::OnDeactivate() {
    KBase628C::OnDeactivate();  // bl 0x209a50
    m_unk18 = 3;
    m_unk28 = 0.0f;
    for (KBase60CC* child = m_unk44; child != nullptr;) {
        KBase60CC* next = child->m_unk04;
        child->OnDeactivate();  // vt+0x54
        child = next;
    }
    m_unk54 = nullptr;
    m_unk6c = 0.0f;
    m_unk48 = 0;
    m_unk4c = nullptr;
    m_unk50 = nullptr;
    m_unk64 = 0.0f;
    m_unk68 = 0.0f;
    m_apUnk70[0]->SetValue(0);
    m_apUnk70[1]->SetValue(0);
    m_apUnk78[0]->SetValue(0);
    m_apUnk78[1]->SetValue(0);
    m_apUnk80[0]->SetValue(0);
    m_apUnk80[1]->SetValue(0);
    m_unk88 = ClearPulseBits(m_unk88);
    m_apUnk70[1]->SetValue(1);  // the "deactivated" pulse
    m_apUnk70[1]->SetValue(0);
}

// 0x002088b0 CKInputBlockSequential_Evaluate
void CKInputBlockSequential::Evaluate(uint8_t value) {
    if (value == 0) return;
    KBase628C::Evaluate(value);  // inlined in the original: the same tests and calls
    if (m_apUnk78[1]->m_unk08 != 0) {  // abort
        m_apUnk78[0]->SetValue(0);
        m_apUnk78[1]->SetValue(0);
        m_unk64 = m_unk68;
        Deactivate();  // vt+0x6c
        m_apUnk80[0]->SetValue(0);
        m_unk88 = ClearBit2(m_unk88);
        m_apUnk80[1]->SetValue(1);
        m_unk88 = static_cast<uint8_t>(ClearBit3(m_unk88) | 0x08);
        return;
    }
    if (m_apUnk78[0]->m_unk08 == 0) return;
    m_apUnk78[0]->SetValue(0);  // a step done
    if (m_unk24 < 1)
        m_unk64 = m_unk64 + 0x1p+0f;  // TOC1 -0xf5c: 1.0
    else
        m_unk64 = m_unk64 + 0x1p+0f / static_cast<float>(m_unk24);  // fcfid + frsp, fdivs, fadds
    m_unk6c = m_unk28;
    if (m_unk60 == 0.0f) {  // TOC1 -0xf9c: 0.0
        Deactivate();
    } else {
        m_unk28 = 0.0f;
        m_unk18 = 2;
    }
    m_apUnk80[0]->SetValue(1);
    m_unk88 = static_cast<uint8_t>(ClearBit2(m_unk88) | 0x04);
    m_apUnk80[1]->SetValue(0);
    m_unk88 = ClearBit3(m_unk88);
}

// 0x00208c68 CKInputBlockSequential_Update_maybe
void CKInputBlockSequential::Update(float dt) {
    m_unk28 = m_unk28 + dt;  // fadds
    m_unk88 = ClearPulseBits(m_unk88);
    if (m_unk18 == 1) {
        CDefaultGameManager* manager = g_pEngine->m_gameManager;
        // Any watched action pressed (vt+0x160, as a signed byte) or with a positive value (vt+0x164) ends
        // the block.
        for (uint32_t i = 0; i < m_vUnk2c.m_ui32NbUsedElt;) {
            const uint32_t word = m_vUnk2c.m_pBlock[i];
            ++i;
            if (word == 0xffffffffu) continue;
            const uint32_t action = word & 0xff;
            if (static_cast<int8_t>(manager->IsActionPressed(action, m_unk0f)) < 0) goto ended;
            if (manager->GetActionValue(action, m_unk0f) > 0.0f) goto ended;  // TOC1 -0xf9c: 0.0
        }
        {
            const int32_t before = CurrentStepIndex(this);
            for (KBase60CC* child = m_unk44; child != nullptr;) {
                KBase60CC* next = child->m_unk04;  // read before the update
                if (child->m_unk0e != 0) child->Update(dt);  // vt+0x58
                child = next;
            }
            if (m_unk24 > 0) {
                const int32_t after = CurrentStepIndex(this);
                if (after > before) m_unk64 = m_unk64 + 0x1p+0f / static_cast<float>(m_unk24);
            }
        }
        return;
    }
    if (m_unk18 == 2) {
        if (m_unk28 >= m_unk60) goto ended;  // fcmpu + cror gt|eq
        return;
    }
    if (m_unk18 == 0 && m_unk28 > m_unk5c) {
        m_unk18 = 1;
        m_unk28 = 0.0f;  // stw 0
        Update(dt);      // vt+0x58, the same step again
    }
    return;
ended:
    m_unk64 = m_unk68;
    Deactivate();  // vt+0x6c
    m_apUnk80[0]->SetValue(0);
    m_unk88 = ClearBit2(m_unk88);
    m_apUnk80[1]->SetValue(1);
    m_unk88 = static_cast<uint8_t>(ClearBit3(m_unk88) | 0x08);
}

// 0x00209a10 InputBlock_CallActivate_maybe (KBase628C vt+0x50)
void KBase628C::OnActivate() { Activate(); }

// 0x00209a50 InputBlock_CallDeactivate_maybe (KBase628C vt+0x54)
void KBase628C::OnDeactivate() { Deactivate(); }
