// CKHkCrumblyZoneMultiState.cpp - reconstructed original translation unit 0x411100-0x413fe8 (GAME_TOC1, main_toc1), 38 functions, 34 live.
// Primary class: CKHkCrumblyZoneMultiState  key 0x34c2  category Hook  size 0x8c  vtable 0xb259d0
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x411100  CKHkCrumblyZoneMultiState_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x411150  CKHkCrumblyZoneMultiState_SetDefaultState
//   [x] 0x411160  CKHkCrumblyZoneMultiState_SetGameState
//   [ ] 0x411190  CKHkCrumblyZoneMultiState_CallVfF0ForCurrentState_maybe  [dead]
//   [ ] 0x4111e0  CKHkCrumblyZoneMultiState_ResetStateHitPoints_maybe  [dead]
//   [x] 0x411250  CKHkCrumblyZoneMultiState_AdvanceToNextState_maybe
//   [x] 0x411338  CKHkCrumblyZoneMultiState_GoToPreviousState
//   [x] 0x411410  CKHkCrumblyZoneMultiState_GetHitDamage_maybe
//   [x] 0x4114b8  CKHkCrumblyZoneMultiState_vf104
//   [x] 0x4114c0  CKHkCrumblyZoneMultiState_IsInStateProperty_maybe  (the accessor of id 0x15e in GetInfo)
//   [ ] 0x4114e8  RegisterCKHkCrumblyZoneMultiStateClass
//   [ ] 0x411560  _GLOBAL__I_411560
//   [x] 0x411570  CKHkCrumblyZoneMultiState_GetTotalHealthProperty_maybe  (the accessor of id 0x15f in GetInfo)
//   [x] 0x411598  CKHkCrumblyZoneMultiState_UpdateShakes_maybe
//   [ ] 0x4117e0  CKHkCrumblyZoneMultiState_ResetPiecesFlag2AndShake74_maybe  [dead]
//   [ ] 0x411900  CKHkCrumblyZoneMultiState_ResetPiecesFlag1AndShake6C_maybe  [dead]
//   [ ] 0x411a20  CKHkCrumblyZoneMultiState_DisableAllStates_maybe  [dead: no pointer to its descriptor 0xbb5490, no call]
//   [x] 0x411ac8  CKHkCrumblyZoneMultiState_Stop
//   [x] 0x411af0  CKHkCrumblyZoneMultiState_GetInfo
//   [x] 0x411c20  CKHkCrumblyZoneMultiState_PostLoad
//   [ ] 0x411cc0  CKHkCrumblyZoneMultiState_Save
//   [x] 0x411ce8  CKHkCrumblyZoneMultiState_RecursiveRegistration  (= the inherited slot: CKHkActorBase_d82_maybe_LevelReset 0x3f6ee8, the trigger starters' KStub_Return1_2361b0, then 1)
//   [x] 0x411d58  CKHkCrumblyZoneMultiState_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x411df8  CKHkCrumblyZoneMultiState_Create
//   [x] 0x411e78  CKHkCrumblyZoneMultiState_Update
//   [x] 0x411f88  CKHkCrumblyZoneMultiState_Destroy
//   [x] 0x412020  CKHkCrumblyZoneMultiState_SetVisible_maybe
//   [x] 0x4120a0  CKHkCrumblyZoneMultiState_SetState_maybe
//   [x] 0x4122b8  CKHkCrumblyZoneMultiState_Start
//   [x] 0x412368  CKHkCrumblyZoneMultiState_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x412458  CKHkCrumblyZoneMultiState_MessageProc
//   [x] 0x4128c8  CKHkCrumblyZoneMultiState_Restart
//   [x] 0x4129c8  CKHkCrumblyZoneMultiState_OnDeactivate
//   [x] 0x412a78  CKHkCrumblyZoneMultiState_OnActivate
//   [x] 0x412bd8  CKHkCrumblyZoneMultiState_PlayBreakFx_maybe
//   [x] 0x412f98  CKHkCrumblyZoneMultiState_Load
//   [x] 0x413740  CKHkCrumblyZoneMultiState_PlayCrumbleFx_maybe
//   [x] 0x413c78  CKHkCrumblyZoneMultiState_PlayHitFxAt_maybe
//
//   [x] 0x9c25c0  CKHkCrumblyZoneMultiState_IsKindOfClass  [inline]  (in the header)
//   [ ] 0x9c2618  CKHkCrumblyZoneMultiState_GetClassType  [inline]
//   [ ] 0x9c2620  CKHkCrumblyZoneMultiState_GetClassID  [inline]
//   [ ] 0x9c2628  CKHkCrumblyZoneMultiState_Destructor  [inline]
//   [ ] 0x9c26c8  CKHkCrumblyZoneMultiState_DeletingDestructor  [inline]
#include "k2000/hooks/CKHkCrumblyZoneMultiState.h"
#include "Spyro2008/hooks/CKHkS08CrumblyZoneMultiState.h"
#include "k2000/core/IKInfo.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/CKGrpMeca.h"
#include "k2000/logic/CKCrumblyZoneElement.h"
#include "k2000/core/Stub.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/logic/CKCrumblyZoneState.h"
#include "k2000/components/CKBoundingCpnt.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/components/CKQuakeCpntUpdater.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/logic/CKDamage.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

namespace {

// The inlined TVector<IKSerializable*, 1> load: capacity = count (1 when 0), a block for it, the grow
// branch (unreachable: the capacity was just set to the count), the length, then one reference per
// element (vt+0x24 each, not one array read).
void LoadRefVector(IKFile* file, TVector<IKSerializable*, 1>& v) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    if (count == 0) {
        v.m_ui32NbElt = 1;
        v.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    } else {
        v.m_ui32NbElt = count;
        v.m_pBlock = static_cast<IKSerializable**>(
            Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    }
    if (v.m_ui32NbElt < count) {
        uint32_t capacity = count + 1;
        v.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
        v.m_ui32NbElt = capacity;
    }
    v.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < count; ++i) IKFile_ReadRef(file, &v.m_pBlock[i]);
}

}  // namespace

// 0x00412f98 CKHkCrumblyZoneMultiState_Load
int32_t CKHkCrumblyZoneMultiState::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    ReadU32LE(file, &m_unk20);
    ReadU32LE(file, &m_unk24);
    LoadRefVector(file, m_vUnk2C);
    LoadRefVector(file, m_vUnk38);
    IKFile_ReadRef(file, &m_pUnk44);
    IKFile_ReadRef(file, &m_pUnk48);
    IKFile_ReadRef(file, &m_pUnk4C);
    IKFile_ReadRef(file, &m_pUnk68);
    IKFile_ReadRef(file, &m_pUnk6C);
    ReadU16LE(file, &m_unk78);
    m_tsUnk7C.Load(file, K_LEVEL_PLATEFORMS);
    m_tsUnk84.Load(file, K_LEVEL_PLATEFORMS);
    for (float& f : m_afUnk50) ReadF32LE(file, &f);
    for (float& f : m_afUnk5C) ReadF32LE(file, &f);
    IKFile_ReadRef(file, &m_pUnk70);
    IKFile_ReadRef(file, &m_pUnk74);
    return 1;
}

// 0x004122b8 CKHkCrumblyZoneMultiState_Start: every state before the current one (+0x28) gets its +0x08 word
// 0, the others the word of +0x0c (last state first).
void CKHkCrumblyZoneMultiState::Start() {
    CKHkActorBase::Start();
    for (uint32_t i = m_vUnk38.m_ui32NbUsedElt; i != 0; --i) {
        CKCrumblyZoneState* state = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[i - 1]);
        state->m_unk08 = (i - 1) < m_unk28 ? 0.0f : state->m_unk0c;
    }
}

// 0x00412458 CKHkCrumblyZoneMultiState_MessageProc: the actor base's (0x003f7148) first, then the zone's: 0x400 the
// node's LTM position moved to the current state's volume centre; 0x402 the current state's bit 9; 0x996 / 0x999 the
// state `*data` (silent / with its sound and FX); 0x997 / 0x99a the current state's next one (+0x48 when it is a valid
// index, else the following state, the last one keeping itself); 0x998 / 0x99b its previous one (+0x44, else the one
// before, the first keeping itself); 0x99c the current state hit for `*data` at its centre; 0x99d the current state's
// health (+0x08) raised by `*data` up to its maximum (+0x0c). Those answer 0, any other message 1; merged with the base's
// answer (3 wins, then 2, then 0 when the base answered 0).
int32_t CKHkCrumblyZoneMultiState::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);
    CKCrumblyZoneState* current = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[m_unk28]);
    const uint32_t count = m_vUnk38.m_ui32NbUsedElt;  // +0x40
    // The state after / before the current one (the jump of its +0x48 / +0x44, a signed index, when below the count).
    auto next = [&]() -> uint32_t {
        const int32_t jump = current->m_unk48;
        if (jump >= 0 && count > static_cast<uint32_t>(jump)) return static_cast<uint32_t>(jump);
        return count - 1 > m_unk28 ? m_unk28 + 1 : m_unk28;
    };
    auto previous = [&]() -> uint32_t {
        const int32_t jump = current->m_unk44;
        if (jump >= 0 && count > static_cast<uint32_t>(jump)) return static_cast<uint32_t>(jump);
        return m_unk28 != 0 ? m_unk28 - 1 : m_unk28;
    };
    int32_t own = 0;
    switch (message) {
    case 0x400: {
        SAimPointQuery* query = static_cast<SAimPointQuery*>(data);
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        query->m_point.x = frame->ltm.pos.x;
        query->m_point.y = frame->ltm.pos.y;
        query->m_point.z = frame->ltm.pos.z;
        current->ComputeCenter(&query->m_point);  // 0x00403a00
        break;
    }
    case 0x402:
        *static_cast<uint8_t*>(data) = current->GetFlagBit9() != 0 ? 1 : 0;  // 0x00403be0
        break;
    case 0x996: SetState(*static_cast<const uint32_t*>(data), 0, 0); break;  // vt+0xf0
    case 0x999: SetState(*static_cast<const uint32_t*>(data), 0, 1); break;
    case 0x997: SetState(next(), 0, 0); break;  // AdvanceToNextState / GoToPreviousState's bodies, inlined
    case 0x99a: SetState(next(), 0, 1); break;
    case 0x998: SetState(previous(), 0, 0); break;
    case 0x99b: SetState(previous(), 0, 1); break;
    case 0x99c: {
        // The hit of `*data` (a float) at the current state's centre (from the node's LTM position).
        const float damage = *static_cast<const float*>(data);
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        CVector3 center = {frame->ltm.pos.x, frame->ltm.pos.y, frame->ltm.pos.z};
        current->ComputeCenter(&center);
        static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[m_unk28])->ApplyDamage(damage, &center);  // 0x004047d0
        break;
    }
    case 0x99d: {
        const float health = *static_cast<const float*>(data) + current->m_unk08;
        current->m_unk08 = health > current->m_unk0c ? current->m_unk0c : health;  // bgt
        break;
    }
    default:
        own = 1;
        break;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x00414040 CKHkCrumblyZoneMultiState_CurrentStateHasPieces_maybe
uint8_t CKHkCrumblyZoneMultiState::CurrentStateHasPieces() const {
    const CKCrumblyZoneState* state = static_cast<const CKCrumblyZoneState*>(m_vUnk38.m_pBlock[m_unk28]);
    return static_cast<const CKBoundingCpnt*>(state->m_pBoundingCpnt)->GetVolumeCount() != 0 ? 1 : 0;  // 0x00190408
}

// 0x00412a78 CKHkCrumblyZoneMultiState_OnActivate
void CKHkCrumblyZoneMultiState::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    for (uint32_t i = m_vUnk38.m_ui32NbUsedElt; i != 0; --i) {
        CKCrumblyZoneState* state = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[i - 1]);
        state->SetEnabled(0, 1);       // 0x00404050
        state->UpdateNavBlocking(0);   // 0x00404378
    }
    SetState(m_unk28, 1, 0);  // vt+0xf0
    for (uint32_t i = m_vUnk2C.m_ui32NbUsedElt; i != 0; --i) {
        static_cast<CKCrumblyZoneElement*>(m_vUnk2C.m_pBlock[i - 1])->ResetMeshMatrixA();  // 0x00402710
        static_cast<CKCrumblyZoneElement*>(m_vUnk2C.m_pBlock[i - 1])->ResetMeshMatrixB();  // 0x004026d0
    }
}

// 0x004128c8 CKHkCrumblyZoneMultiState_Restart (vt+0x54): unless the life flag bit 2, every state (last first) disabled
// and its path-finding boxes freed, then the current state (+0x28) set again (vt+0xf0, forced, silent). OnActivate's
// body without the pieces' matrices.
void CKHkCrumblyZoneMultiState::Restart() {
    if ((m_bitArray & 4u) != 0) return;
    for (uint32_t i = m_vUnk38.m_ui32NbUsedElt; i != 0; --i) {
        CKCrumblyZoneState* state = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[i - 1]);
        state->SetEnabled(0, 1);       // 0x00404050
        state->UpdateNavBlocking(0);   // 0x00404378
    }
    SetState(m_unk28, 1, 0);  // vt+0xf0
}

// 0x004120a0 CKHkCrumblyZoneMultiState_SetState_maybe
void CKHkCrumblyZoneMultiState::SetState(uint32_t state, uint8_t force, uint8_t sound) {
    if (force == 0) {
        if (m_unk28 == state) return;
        QueueTriggerSignals(&m_tsUnk84);  // 0x00236338
    }
    CKCrumblyZoneState* next = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[state]);
    CKCrumblyZoneState* current = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[m_unk28]);
    if (next->m_pBoundingCpnt != nullptr && current->m_pBoundingCpnt != nullptr) next->CopyContactList(current);  // 0x00403c20
    current->SetEnabled(0, sound);
    current->UpdateNavBlocking(0);
    CKGrpMeca* meca = static_cast<CKGrpMeca*>(g_pEngine->m_gameManager->m_unk04[2]);  // the game manager's +0x0c
    meca->m_unk32 = meca->m_unk32 == 2 ? 3 : 1;
    next->SetEnabled(1, sound);
    next->UpdateNavBlocking(1);
    if (sound != 0) {
        if (m_unk28 < state) {
            PlayCrumbleFx();  // vt+0xf8
        } else {
            PlayBreakFx();    // vt+0xfc
        }
    }
    m_unk28 = state;
    for (uint32_t i = m_vUnk38.m_ui32NbUsedElt; i != 0; --i) {
        CKCrumblyZoneState* s = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[i - 1]);
        if (m_unk28 > i - 1) {
            s->m_unk08 = 0.0f;
        } else {
            s->m_unk08 = s->m_unk0c;
        }
    }
}

// 0x00411af0 CKHkCrumblyZoneMultiState_GetInfo, with 0x004114c0 IsInStateProperty_maybe (`arg` is the current state +0x28)
// and 0x00411570 GetTotalHealthProperty_maybe (CKHkS08CrumblyZoneMultiState_GetTotalHealth_maybe 0x413fe8).
int32_t CKHkCrumblyZoneMultiState::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    if (info->m_ui32Id == 0x15e) {
        return AnswerInfo(info, [](IKSerializable* o, uint32_t state) {
            return static_cast<CKHkCrumblyZoneMultiState*>(o)->m_unk28 == state ? 1u : 0u;
        }, 0);
    }
    if (info->m_ui32Id == 0x15f) {
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return FloatBits(static_cast<CKHkS08CrumblyZoneMultiState*>(o)->GetTotalHealth());
        }, 2);
    }
    return 1;
}

// 0x00412020 CKHkCrumblyZoneMultiState_SetVisible_maybe
void CKHkCrumblyZoneMultiState::SetVisible(int32_t visible) {
    static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[m_unk28])->SetEnabled(static_cast<uint8_t>(visible), 1);  // 0x00404050
    CKGrpMeca* meca = static_cast<CKGrpMeca*>(g_pEngine->m_gameManager->m_unk04[2]);  // the game manager's +0x0c
    meca->m_unk32 = meca->m_unk32 == 2 ? 3 : 1;
}

// 0x00411250 CKHkCrumblyZoneMultiState_AdvanceToNextState_maybe: the current state's next one (+0x48, a signed index,
// when below the count; else the following state, the last one keeping itself) set (vt+0xf0, not forced).
void CKHkCrumblyZoneMultiState::AdvanceToNextState(uint8_t sound) {
    const uint32_t current = m_unk28;
    const int32_t jump = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[current])->m_unk48;
    const uint32_t count = m_vUnk38.m_ui32NbUsedElt;
    if (jump >= 0 && static_cast<uint32_t>(jump) < count) {
        SetState(static_cast<uint32_t>(jump), 0, sound);  // vt+0xf0
        return;
    }
    SetState(current < count - 1 ? current + 1 : current, 0, sound);
}

// 0x00411338 CKHkCrumblyZoneMultiState_GoToPreviousState: the previous one (+0x44, else the one before, the first
// keeping itself).
void CKHkCrumblyZoneMultiState::GoToPreviousState(uint8_t sound) {
    const uint32_t current = m_unk28;
    const int32_t jump = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[current])->m_unk44;
    if (jump >= 0 && static_cast<uint32_t>(jump) < m_vUnk38.m_ui32NbUsedElt) {
        SetState(static_cast<uint32_t>(jump), 0, sound);  // vt+0xf0
        return;
    }
    SetState(current != 0 ? current - 1 : current, 0, sound);
}

// 0x004129c8 CKHkCrumblyZoneMultiState_OnDeactivate (vt+0xa4; CKHkS08CrumblyZoneMultiState's 0x415168 calls it): the actor
// base's, then every state (last first) off with its sound and its path-finding boxes freed.
void CKHkCrumblyZoneMultiState::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    for (uint32_t i = m_vUnk38.m_ui32NbUsedElt; i != 0; --i) {
        CKCrumblyZoneState* state = static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[i - 1]);
        state->SetEnabled(0, 1);      // 0x00404050
        state->UpdateNavBlocking(0);  // 0x00404378
    }
}

namespace {
// The pieces of the current state whose entry has its +0x02 byte reset to their loaded matrices (last first; the crumble
// and break effects' tail).
void ResetMarkedPieces(CKHkCrumblyZoneMultiState* zone) {
    const CKCrumblyZoneState* state = static_cast<const CKCrumblyZoneState*>(zone->m_vUnk38.m_pBlock[zone->m_unk28]);
    for (uint32_t i = state->m_vEntries.m_ui32NbUsedElt; i != 0; --i) {
        const CKCrumblyZoneState* now = static_cast<const CKCrumblyZoneState*>(zone->m_vUnk38.m_pBlock[zone->m_unk28]);
        if (now->m_vEntries.m_pBlock[i - 1].m_unk02 == 0) continue;
        static_cast<CKCrumblyZoneElement*>(zone->m_vUnk2C.m_pBlock[i - 1])->ResetMeshMatrixA();  // 0x00402710
        static_cast<CKCrumblyZoneElement*>(zone->m_vUnk2C.m_pBlock[i - 1])->ResetMeshMatrixB();  // 0x004026d0
    }
}
}  // namespace

// 0x00413740 CKHkCrumblyZoneMultiState_PlayCrumbleFx_maybe (vt+0xf8): a free explosion of +0x44's data (the effect
// lookup inlined) aimed along the node's LTM at axis, at the node's position plus +0x50, triggered with the LTM's
// rotation (the position the null vector) as its launch matrix; then the marked pieces reset and the quake (+0x74)
// started.
void CKHkCrumblyZoneMultiState::PlayCrumbleFx() {
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pUnk44), this);
    if (fx != nullptr) {
        CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        CVector3 at;
        at.x = frame->ltm.pos.x + m_afUnk50[0];
        at.z = frame->ltm.pos.z + m_afUnk50[2];
        at.y = frame->ltm.pos.y + m_afUnk50[1];
        frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        const CVector3 direction = {frame->ltm.at.x, frame->ltm.at.y, frame->ltm.at.z};
        // The launch matrix (the LTM's rows, the null position, flag 0x20000 cleared) is built on the stack and passed as
        // Trigger's third argument; the explosion keeps it for its projectile sub-effects, whose launch drops it
        // (CKExplosionNodeFx::FireSubEffect): 0 here (x64 cannot keep the stack address in the 32-bit word).
        explosion->SetDirection(&direction, this);  // 0x001b5e20
        explosion->SetTranslation(&at, this);       // 0x001b66e8
        explosion->Trigger(this, 0);                // 0x001b82a8
        explosion->ReleaseReservation(this);        // vt+0x54
    }
    ResetMarkedPieces(this);
    // DOTD: without a quake (+0x74 null) the original reads the low address 4 (zero: nothing happens).
    if (m_pUnk74 != nullptr) static_cast<CKQuakeCpntUpdater*>(m_pUnk74)->Start();  // 0x0024f770
}

// 0x00412bd8 CKHkCrumblyZoneMultiState_PlayBreakFx_maybe (vt+0xfc): the same with +0x48's data at the node's position
// plus +0x5c (no direction, no launch matrix).
void CKHkCrumblyZoneMultiState::PlayBreakFx() {
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pUnk48), this);
    if (fx != nullptr) {
        CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
        const RwFrame* frame = static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame;
        CVector3 at;
        at.x = frame->ltm.pos.x + m_afUnk5C[0];
        at.z = frame->ltm.pos.z + m_afUnk5C[2];
        at.y = frame->ltm.pos.y + m_afUnk5C[1];
        explosion->SetTranslation(&at, this);  // 0x001b66e8
        explosion->Trigger(this, 0);           // 0x001b82a8
        explosion->ReleaseReservation(this);   // vt+0x54
    }
    ResetMarkedPieces(this);
    // DOTD: without a quake (+0x74 null) the original reads the low address 4 (zero: nothing happens).
    if (m_pUnk74 != nullptr) static_cast<CKQuakeCpntUpdater*>(m_pUnk74)->Start();  // 0x0024f770
}

// 0x00411410 CKHkCrumblyZoneMultiState_GetHitDamage_maybe (vt+0xf4)
float CKHkCrumblyZoneMultiState::GetHitDamage(IKBoundingVolume* volume, uint8_t /*touched*/) {
    CKDamage* damage = static_cast<CKDamage*>(volume->m_unk1c);
    // DOTD: the original calls the damage's IsKindOfClass without a null test.
    if (damage == nullptr || damage->IsKindOfClass(0x96cc) == 0) return 0.0f;  // vt+0x08
    const float dt = g_pEngine->m_timeManager->m_pTime->m_afDeltaTime[0];  // +0x48 -> +0x04 -> +0x1c
    if (damage->m_unk0c != 0) return dt * damage->m_unk04;
    return damage->m_unk04;
}

// 0x00413c78 CKHkCrumblyZoneMultiState_PlayHitFxAt_maybe (vt+0x100)
void CKHkCrumblyZoneMultiState::PlayHitFxAt(const CVector3* point) {
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pUnk4C), this);  // inlined
    if (fx != nullptr) {
        CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
        explosion->SetTranslation(point, this);  // 0x001b66e8
        explosion->Trigger(this, 0);             // 0x001b82a8
        explosion->ReleaseReservation(this);     // vt+0x54
    }
    const CKCrumblyZoneState* state = static_cast<const CKCrumblyZoneState*>(m_vUnk38.m_pBlock[m_unk28]);
    for (uint32_t i = state->m_vEntries.m_ui32NbUsedElt; i != 0; --i) {
        const CKCrumblyZoneState* now = static_cast<const CKCrumblyZoneState*>(m_vUnk38.m_pBlock[m_unk28]);
        if (now->m_vEntries.m_pBlock[i - 1].m_unk01 == 0) continue;
        static_cast<CKCrumblyZoneElement*>(m_vUnk2C.m_pBlock[i - 1])->ResetMeshMatrixA();  // 0x00402710
        static_cast<CKCrumblyZoneElement*>(m_vUnk2C.m_pBlock[i - 1])->ResetMeshMatrixB();  // 0x004026d0
    }
    // DOTD: without a quake (+0x6c null) the original reads the low address 4 (zero: nothing happens).
    if (m_pUnk6C != nullptr) static_cast<CKQuakeCpntUpdater*>(m_pUnk6C)->Start();  // 0x0024f770
}

// 0x00411598 CKHkCrumblyZoneMultiState_UpdateShakes_maybe
void CKHkCrumblyZoneMultiState::UpdateShakes(IKTime* frameClock) {
    for (int pass = 0; pass < 2; ++pass) {
        CKQuakeCpntUpdater* quake = static_cast<CKQuakeCpntUpdater*>(pass == 0 ? m_pUnk6C : m_pUnk74);
        if (quake->m_bRunning == 0) continue;
        float out[15];
        quake->EvaluateScaled(frameClock->m_afDeltaTime[0], 1.0f, out);  // 0x0024f5c8 (TOC +0x4a9c)
        CMatrix34 shake;
        ShakeSample_BuildMatrix(quake, out, &shake, nullptr);  // 0x0024ee90
        const CKCrumblyZoneState* state = static_cast<const CKCrumblyZoneState*>(m_vUnk38.m_pBlock[m_unk28]);
        for (uint32_t i = state->m_vEntries.m_ui32NbUsedElt; i != 0; --i) {
            const CKCrumblyZoneState* now = static_cast<const CKCrumblyZoneState*>(m_vUnk38.m_pBlock[m_unk28]);
            const CKCrumblyZoneState::Entry& entry = now->m_vEntries.m_pBlock[i - 1];
            if ((pass == 0 ? entry.m_unk01 : entry.m_unk02) == 0) continue;
            static_cast<CKCrumblyZoneElement*>(m_vUnk2C.m_pBlock[i - 1])->ApplyWorldMatrix(&shake);  // 0x00403138
        }
    }
}

// 0x00411e78 CKHkCrumblyZoneMultiState_Update (vt+0x7c; WorldObjectBase_Update_Nop first)
void CKHkCrumblyZoneMultiState::Update(IKTime* frameClock) {
    static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[m_unk28])->UpdateState(frameClock);  // 0x00403ec8
    UpdateShakes(frameClock);  // 0x00411598
    for (uint32_t i = 0; i < m_vUnk2C.m_ui32NbUsedElt; ++i) {
        static_cast<CKCrumblyZoneElement*>(m_vUnk2C.m_pBlock[i])->AdvancePieceAnim(frameClock);  // 0x00402990
    }
    CKGrpMeca* meca = static_cast<CKGrpMeca*>(g_pEngine->m_gameManager->m_unk04[2]);  // the game manager's +0x0c
    if (static_cast<int8_t>(meca->m_unk32) > 1) {
        static_cast<CKCrumblyZoneState*>(m_vUnk38.m_pBlock[m_unk28])->UpdateNavBlocking(1);  // 0x00404378
    }
}

// 0x00411f88 CKHkCrumblyZoneMultiState_Destroy
void CKHkCrumblyZoneMultiState::Destroy() {
    CKHkActorBase::Destroy();
    if (m_vUnk2C.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnk2C.m_pBlock);
        m_vUnk2C.m_pBlock = nullptr;
    }
    m_vUnk2C.m_ui32NbUsedElt = 0;
    m_vUnk2C.m_pBlock = nullptr;
    if (m_vUnk38.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vUnk38.m_pBlock);
        m_vUnk38.m_pBlock = nullptr;
    }
    m_vUnk38.m_ui32NbUsedElt = 0;
    m_vUnk38.m_pBlock = nullptr;
}
