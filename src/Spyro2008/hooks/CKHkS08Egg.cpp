// CKHkS08Egg.cpp - reconstructed original translation unit 0x472af8-0x4740f0 (GAME_TOC1, main_toc1), 29 functions, 28 live.
// Primary class: CKHkS08Egg  key 0x2ac2  category Hook  size 0x70  vtable 0xb27820
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x472af8  CKHkS08Egg_Delete
//   [x] 0x472b48  CKHkS08Egg_vfB4  (empty: the hook's default slot)
//   [x] 0x472b50  CKHkS08Egg_GetInfo  (inherited: CKHkActorBase's (1; no info of its own))
//   [x] 0x472ba0  CKHkS08Egg_SpawnHatchFx_maybe
//   [x] 0x472e58  CKHkS08Egg_SetDefaultState
//   [x] 0x472e80  CKHkS08Egg_Update  (inherited, empty)
//   [ ] 0x472ea8  CKHkS08Egg_UpdateVisibilityFromFightZone_maybe  [dead]
//   [x] 0x472f98  CKHkS08Egg_Resume  (empty / no effect: inherited)
//   [x] 0x472fc0  CKHkS08Egg_Pause  (empty / no effect: inherited)
//   [x] 0x472fe8  CKHkS08Egg_Stop  (inherited, CKHkActorBase's Stop: empty)
//   [x] 0x473010  CKHkS08Egg_PostLoad  (= the inherited slot)
//   [x] 0x473038  CKHkS08Egg_RecursiveRegistration  (inherited: CKHkActorBase's; the trigger starter's is KStub_Return1)
//   [x] 0x473090  CKHkS08Egg_Destroy  (inherited, empty)
//   [x] 0x4730b8  CKHkS08Egg_DeleteArray
//   [x] 0x473160  CKHkS08Egg_Create
//   [ ] 0x4731d0  RegisterCKHkS08EggClass
//   [ ] 0x473258  _GLOBAL__D_473258
//   [ ] 0x473268  _GLOBAL__I_473268
//   [x] 0x473278  CKHkS08Egg_OnDeactivate
//   [x] 0x4732d0  CKHkS08Egg_OnActivate
//   [x] 0x473398  CKHkS08Egg_ReleaseNextEnemy_maybe
//   [x] 0x473510  CKHkS08Egg_MessageProc
//   [x] 0x473630  CKHkS08Egg_AssignEnemy_maybe
//   [x] 0x4736d0  CKHkS08Egg_GetSpawnPoint_maybe
//   [x] 0x473740  CKHkS08Egg_CreateArray
//   [x] 0x473828  CKHkS08Egg_Load
//   [ ] 0x473c90  CKHkS08Egg_Save
//   [x] 0x473ea8  CKHkS08Egg_Restart
//   [x] 0x473fc8  CKHkS08Egg_Start
//
//   [ ] 0x9c45a8  CKHkS08Egg_IsKindOfClass  [inline]
//   [ ] 0x9c4600  CKHkS08Egg_GetClassType  [inline]
//   [ ] 0x9c4608  CKHkS08Egg_GetClassID  [inline]
//   [ ] 0x9c4610  CKHkS08Egg_Destructor  [inline]
//   [ ] 0x9c4668  CKHkS08Egg_DeletingDestructor  [inline]
#include "Spyro2008/hooks/CKHkS08Egg.h"
#include "Spyro2008/groups/C22SpyroShims.h"
#include "k2000/groups/CKGrpSquad.h"
#include "k2000/groups/CKGrpFightZone.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/hooks/CKHkS08Enemy.h"
#include "k2000/fx/IKFx.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/memory/Mem.h"

// 0x00473828 CKHkS08Egg_Load: the actor base, then the same reads for every serialization type (the
// trigger starter gets the caller's type).
int32_t CKHkS08Egg::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    ReadU32LE(file, &m_unk54);
    // BUG(original): a new block of capacity 1 replaces the old one (leaked) and the length is not
    // reset; the elements are written from index 0 while the length keeps counting.
    m_vUnk20.m_ui32NbElt = 1;
    m_vUnk20.m_pBlock = static_cast<CVector3*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(CVector3))));
    for (uint32_t i = 0; i < m_unk54; ++i) {
        const uint32_t used = m_vUnk20.m_ui32NbUsedElt;
        if (m_vUnk20.m_ui32NbElt == used) {
            uint32_t capacity = used + 1;
            uint32_t bytes = capacity * static_cast<uint32_t>(sizeof(CVector3));
            if (capacity == 0) {
                capacity = 1;
                bytes = static_cast<uint32_t>(sizeof(CVector3));
            }
            m_vUnk20.m_pBlock = static_cast<CVector3*>(Mem_ReallocAligned16(m_vUnk20.m_pBlock, bytes & ~3u));
            m_vUnk20.m_ui32NbElt = capacity;
        }
        m_vUnk20.m_ui32NbUsedElt = used + 1;
        uint32_t words[3];  // one 12-byte read, then the three words swapped
        ReadU32LEWords(file, words, 3);
        std::memcpy(&m_vUnk20.m_pBlock[i], words, sizeof(words));
    }
    IKFile_ReadRef(file, &m_pUnk2C);
    ReadU32LE(file, &m_unk34);
    ReadF32LE(file, &m_fUnk38);
    ReadF32LE(file, &m_fUnk3C);
    ReadU32LE(file, &m_unk40);
    IKFile_ReadRef(file, &m_pUnk44);
    ReadF32LE(file, &m_fUnk48);
    ReadU8(file, &m_unk50);
    ReadF32LE(file, &m_fUnk5C);
    m_unk68.Load(file, type);
    ReadU8(file, &m_unk64);
    return 1;
}

// 0x00472e58 CKHkS08Egg_SetDefaultState: only the empty base call (KStub_Nop_3f72a0).
void CKHkS08Egg::SetDefaultState(int32_t /*flag*/) {}

// 0x00473fc8 CKHkS08Egg_Start
void CKHkS08Egg::Start() {
    // CKHkActorBase_d82_maybe_ResetRuntime 0x3f6e48: empty.
    CSGLeaf* object = static_cast<CSGLeaf*>(m_pKGLObject);
    if ((m_bitArray & 4u) != 0) {
        c22spyro::SetBeByte(m_unk30, 0, 0);  // the byte at +0x30
        m_unk60 = 0;
        m_pUnk4C = nullptr;
        m_unk58 = 0;
        return;
    }
    // CKGrpSquad_GetFightZone 0x25ab50: the squad's parent group; its byte +0x10e.
    CKGrpSquad* squad = static_cast<CKGrpSquad*>(m_pUnk2C);
    if (squad != nullptr && static_cast<CKGrpFightZone*>(squad->m_pParent)->m_unk10e != 0) {
        c22spyro::SetBeByte(m_unk30, 0, 1);
        object->m_sgProperties = (object->m_sgProperties & 0xfffffffbu) | (static_cast<uint32_t>(m_unk50) << 2);
        m_unk60 = 0;
        m_pUnk4C = nullptr;
        m_unk58 = 0;
        return;
    }
    c22spyro::SetBeByte(m_unk30, 0, 0);
    object->m_sgProperties = (object->m_sgProperties & 0xfffffffbu) | 4u;
    m_unk60 = 0;
    m_pUnk4C = nullptr;
    m_unk58 = 0;
}

namespace {
// The egg's scene node frame's LTM position (+0x1c -> +0x04 -> +0x80).
CVector3 EggNodePosition(const CKHkS08Egg* egg) {
    const RwV3d& at = FrameLtm(static_cast<const CSGMovable*>(egg->m_pKGLObject)->m_pRwFrame)->pos;
    return CVector3{at.x, at.y, at.z};
}
}  // namespace

// 0x00473ea8 CKHkS08Egg_Restart (vt+0x54): an egg whose squad's fight zone may arm (+0x10e) opens (the byte +0x30) with
// its node's hidden bit from +0x50; any other closes and hides; with the life flag bit 2 it only closes. No waiting
// enemy, the counters +0x58 / +0x60 cleared.
void CKHkS08Egg::Restart() {
    if ((m_bitArray & 4u) == 0) {
        CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
        if (m_pUnk2C != nullptr && static_cast<CKGrpSquad*>(m_pUnk2C)->GetFightZone()->m_unk10e != 0) {  // 0x0025ab50
            c22spyro::SetBeByte(m_unk30, 0, 1);
            node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | (static_cast<uint32_t>(m_unk50) << 2);
        } else {
            c22spyro::SetBeByte(m_unk30, 0, 0);
            node->m_sgProperties = node->m_sgProperties | 4u;
        }
    } else {
        c22spyro::SetBeByte(m_unk30, 0, 0);
    }
    m_unk60 = 0;
    m_pUnk4C = nullptr;
    m_unk58 = 0;
}

// 0x00473630 CKHkS08Egg_AssignEnemy_maybe
void CKHkS08Egg::AssignEnemy(IKSerializable* enemy) {
    m_pUnk4C = enemy;
    if (m_pUnk2C == nullptr) return;
    const CVector3 at = EggNodePosition(this);
    static_cast<CKHkS08Enemy*>(enemy)->SetPosition(&at);  // 0x00289718
    CKHkS08Enemy* waiting = static_cast<CKHkS08Enemy*>(m_pUnk4C);
    waiting->m_bitArray = (waiting->m_bitArray & 0xf3ffffffu) | 0x0c000000u;
    waiting->m_pSpawnEgg = this;
}

// 0x00473398 CKHkS08Egg_ReleaseNextEnemy_maybe
void CKHkS08Egg::ReleaseNextEnemy() {
    if (m_pUnk2C == nullptr || m_pUnk4C == nullptr) return;
    const uint32_t index = m_unk58;
    if (!(index < m_unk54)) return;
    if (index == 0) {
        CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
        SpawnHatchFx();  // 0x00472ba0
    }
    CKHkS08Enemy* enemy = static_cast<CKHkS08Enemy*>(m_pUnk4C);
    enemy->m_unk688 = m_unk58;
    enemy->m_unk894 = m_fUnk5C * static_cast<float>(m_unk58);
    const uint8_t repeat = m_unk64;
    m_pUnk4C = nullptr;
    if (repeat != 0) return;
    m_unk58 = m_unk58 + 1;
    if (m_unk54 <= m_unk58) {
        c22spyro::SetBeByte(m_unk30, 0, 0);  // the byte at +0x30
        QueueTriggerSignals(&m_unk68);       // 0x00236338
    }
}

// 0x004736d0 CKHkS08Egg_GetSpawnPoint_maybe
CVector3 CKHkS08Egg::GetSpawnPoint(uint32_t index) const {
    if (index < m_vUnk20.m_ui32NbUsedElt) return m_vUnk20.m_pBlock[index];
    return CVector3{0.0f, 0.0f, 0.0f};  // 0x00c50d64
}

// 0x00472ba0 CKHkS08Egg_SpawnHatchFx_maybe (the pooled lookup inlined, as CKSrvFx::AcquireFx)
void CKHkS08Egg::SpawnHatchFx() {
    IKFx* effect = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pUnk44), this);
    if (effect == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
    const CVector3 at = EggNodePosition(this);
    explosion->SetTranslation(&at, this);  // 0x001b66e8
    explosion->Trigger(this, 0);           // 0x001b82a8
    explosion->ReleaseReservation(this);   // vt+0x54
}

// 0x00473510 CKHkS08Egg_MessageProc
int32_t CKHkS08Egg::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    int32_t own;
    if (message == 0x900) {
        own = 0;
        node->m_sgProperties &= 0xfffffffbu;
    } else {
        own = 1;
        if (message == 0x901) {
            own = 0;
            node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
        }
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x004732d0 CKHkS08Egg_OnActivate: the actor base's; in a squad whose fight zone may arm (+0x10e): open (+0x30 byte 1),
// the node hidden as +0x50 says; otherwise closed and hidden.
void CKHkS08Egg::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    if (m_pUnk2C != nullptr && static_cast<CKGrpSquad*>(m_pUnk2C)->GetFightZone()->m_unk10e != 0) {  // 0x0025ab50
        c22spyro::SetBeByte(m_unk30, 0, 1);
        node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | (static_cast<uint32_t>(m_unk50) << 2);
        return;
    }
    c22spyro::SetBeByte(m_unk30, 0, 0);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
}

// 0x00473278 CKHkS08Egg_OnDeactivate: the actor base's; closed (+0x30 byte 0) and shown.
void CKHkS08Egg::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    c22spyro::SetBeByte(m_unk30, 0, 0);
    static_cast<CSGLeaf*>(m_pKGLObject)->m_sgProperties &= 0xfffffffbu;
}
