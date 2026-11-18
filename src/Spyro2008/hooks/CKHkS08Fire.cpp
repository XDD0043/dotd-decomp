// CKHkS08Fire.cpp - reconstructed original translation unit 0x4da838-0x4dfc68 (GAME_TOC1, main_toc1), 42 functions, 37 live.
// Primary class: CKHkS08Fire  key 0x3442  category Hook  size 0xd8  vtable 0xb2a268
// Other owners: CKHkMecaSound (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x4da838  CKHkS08Fire_ReleaseStageFxRefs_maybe  [dead]
//   [ ] 0x4da930  CKHkS08Fire_ReleaseFlameFxRefByIndex_maybe  [dead]
//   [ ] 0x4da9b0  CKHkS08Fire_ReleaseFlameFxRefs_maybe  [dead]
//   [ ] 0x4daae8  RegisterCKHkS08FireClass
//   [ ] 0x4dab60  _GLOBAL__I_4dab60
//   [x] 0x4dab70  CKHkS08Fire_StopSounds_maybe
//   [ ] 0x4dac18  CKHkS08Fire_InitCollisionVolume_maybe  [dead: no pointer to its descriptor 0xbce068, no call]
//   [x] 0x4dace8  CKHkS08Fire_ProcessPowerBucketContacts_maybe
//   [x] 0x4daef8  CKHkS08Fire_GetInfo
//   [x] 0x4dafd8  CKHkS08Fire_SetDefaultState
//   [x] 0x4db010  CKHkS08Fire_Resume  (inherited: CKHkActorBase's)
//   [x] 0x4db038  CKHkS08Fire_Pause  (inherited: CKHkActorBase's)
//   [x] 0x4db060  CKHkS08Fire_Stop  (inherited: CKHkActorBase's)
//   [x] 0x4db088  CKHkS08Fire_PostLoad
//   [x] 0x4db0f0  CKHkS08Fire_RecursiveRegistration  (inherited: CKHkActorBase's)
//   [ ] 0x4db118  CKHkS08Fire_Construct_2  [dead: no pointer to its descriptor 0xbce0b0, no call]
//   [x] 0x4db178  CKHkS08Fire_DeleteArray
//   [ ] 0x4db218  CKHkS08Fire_Destructor_2  [dead: no pointer to its descriptor 0xbce0d0, no call]
//   [x] 0x4db290  CKHkS08Fire_DeletingDestructor  (the destructor)
//   [x] 0x4db318  CKHkS08Fire_Destructor  (the destructor)
//   [x] 0x4db390  CKHkS08Fire_Destroy
//   [x] 0x4db3d0  CKHkS08Fire_Construct
//   [ ] 0x4db430  CKHkS08Fire_Save
//   [x] 0x4db458  CKHkS08Fire_CreateArray
//   [x] 0x4db538  CKHkS08Fire_Create
//   [x] 0x4db5a8  CKHkS08Fire_OnDeactivate
//   [x] 0x4db7c8  CKHkS08Fire_Load
//   [x] 0x4dc2c0  CKHkS08Fire_MessageProc
//   [x] 0x4dc850  CKHkS08Fire_Restart
//   [x] 0x4dcc78  CKHkS08Fire_Start
//   [x] 0x4dcdb0  CKHkS08Fire_Update
//   [ ] 0x4dcfc0  CKHkS08Fire_AcquireFlameFxNode_maybe  [dead]
//   [x] 0x4dd2a0  CKHkS08Fire_StartFlameStage_maybe
//   [x] 0x4dddd0  CKHkS08Fire_OnActivate
//   [x] 0x4de0a0  CKHkS08Fire_State3  (FlameState(3))
//   [x] 0x4de748  CKHkS08Fire_State2  (FlameState(2))
//   [x] 0x4dee10  CKHkS08Fire_State0
//   [x] 0x4df490  CKHkS08Fire_State1  (FlameState(1))
//   [x] 0x4dfb58  CKHkMecaSound_Delete  (DOTD_DECLARE_FACTORIES, k2000/hooks/CKHkMecaSound.h)
//   [x] 0x4dfba8  CKHkMecaSound_Restart  (empty: the inherited IKUpdatable default)
//   [x] 0x4dfbb0  CKHkMecaSound_vfC8  (CKHkMecaSound::ApplyStatePreset, k2000/hooks/CKHkMecaSound.h)
//   [ ] 0x4dfbc0  FUN_004dfbc0  [dead]
//
//   [ ] 0x9c6250  CKHkS08Fire_IsKindOfClass  [inline]
//   [ ] 0x9c62a8  CKHkS08Fire_GetClassType  [inline]
//   [ ] 0x9c62b0  CKHkS08Fire_GetClassID  [inline]
//   [ ] 0x9c62b8  CKHkS08Fire_GetTriggerProp9A  [inline]
#include "Spyro2008/hooks/CKHkS08Fire.h"

#include <cstring>

#include "k2000/io/IKFile.h"
#include "k2000/core/IKInfo.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Mat4.h"
#include "Renderware/rwcore/RwCamera.h"
#include "crt/ppc_ops.h"
#include "k2000/core/Ps3MemberFn.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/render/CKPointLightFxData.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CKAACylinder.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGSectorRoot.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/system/IKTime.h"

#include <cmath>

namespace {
// One 12-byte read, then the three words swapped (the inlined swap of the original).
void ReadVector(IKFile* file, CVector3* dst) {
    uint32_t words[3];
    ReadU32LEWords(file, words, 3);
    std::memcpy(dst, words, sizeof(words));
}
}  // namespace

// 0x004db7c8 CKHkS08Fire_Load: the actor base, then the level data (type 0 only). The trigger starters
// are loaded with type 0.
int32_t CKHkS08Fire::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pUnk38);
        IKFile_ReadRef(file, &m_pUnk40);
        IKFile_ReadRef(file, &m_pUnk48);
        IKFile_ReadRef(file, &m_pUnk54);
        ReadF32LE(file, &m_fUnk60);
        ReadF32LE(file, &m_fUnk5C);
        ReadU8(file, &m_unk50);
        ReadF32LE(file, &m_fUnk20);
        ReadF32LE(file, &m_fUnk24);
        IKFile_ReadRef(file, &m_pUnk2C);
        // 0x4dbaa0: a new matrix (RwMatrixCreate_Thunk 0x0023fa68), then its pos, at, up and right rows.
        // The first store clears rwMATRIXINTERNALIDENTITY (0x20000), the others also the type bits (3).
        m_pMatrix64 = RwMatrixCreate_Thunk();
        CMatrix34* matrix = m_pMatrix64;
        ReadVector(file, &matrix->m_pos);
        matrix->m_ui32Flags &= 0xfffdffffu;
        ReadVector(file, &m_pMatrix64->m_at);
        m_pMatrix64->m_ui32Flags &= 0xfffdfffcu;
        ReadVector(file, &m_pMatrix64->m_up);
        m_pMatrix64->m_ui32Flags &= 0xfffdfffcu;
        ReadVector(file, &m_pMatrix64->m_right);
        m_pMatrix64->m_ui32Flags &= 0xfffdfffcu;
        m_unk6C.Load(file, K_LEVEL_PLATEFORMS);
        m_unk74.Load(file, K_LEVEL_PLATEFORMS);
        ReadU8(file, &m_unk7C);
        ReadU8(file, &m_unk7D);
        ReadU8(file, &m_unk7E);
        IKFile_ReadRef(file, &m_pUnk30);
        IKFile_ReadRef(file, &m_pUnkA8);
        IKFile_ReadRef(file, &m_pUnkC8);
        IKFile_ReadRef(file, &m_pUnkAC);
        IKFile_ReadRef(file, &m_pUnkCC);
        IKFile_ReadRef(file, &m_pUnkB0);
        IKFile_ReadRef(file, &m_pUnkD0);
        IKFile_ReadRef(file, &m_pUnkB4);
        IKFile_ReadRef(file, &m_pUnkD4);
    }
    return 1;
}

// 0x004db318 CKHkS08Fire_Destructor: the contact history's nodes (+0x58) back to their pool, the list cleared.
CKHkS08Fire::~CKHkS08Fire() {
    for (ContactHistoryNode* node = m_unk58; node != nullptr;) {
        ContactHistoryNode* next = node->m_pNext;  // +0x14
        ContactHistory_FreeNode(node);
        node = next;
    }
    m_unk58 = nullptr;
}

// 0x004db088 CKHkS08Fire_PostLoad
int32_t CKHkS08Fire::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);  // 0x003f6e70
    if (type == K_LEVEL_PLATEFORMS) {
        m_unkB8[3] = 0;  // +0xc4
        m_unkB8[0] = 0;  // +0xb8
        m_unkB8[1] = 0;  // +0xbc
        m_unkB8[2] = 0;  // +0xc0
    }
    return 1;
}

// 0x004dafd8 CKHkS08Fire_SetDefaultState
void CKHkS08Fire::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);  // KStub_Nop_3f72a0
    m_unk50 = m_unk7E;
}

// 0x004daef8 CKHkS08Fire_GetInfo, with its accessor 0x009c62b8 (the state +0x84; descriptor 0x00bce0c0).
int32_t CKHkS08Fire::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor || info->m_ui32Id != 0x9a) return 1;
    return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
        return static_cast<uint32_t>(static_cast<CKHkS08Fire*>(o)->m_unk84);
    }, 1);
}

// 0x004db390 CKHkS08Fire_Destroy
void CKHkS08Fire::Destroy() {
    CKHkActorBase::Destroy();  // 0x003f6e08
    RwMatrixDestroy_Thunk(m_pMatrix64);  // 0x0023f968
}

// 0x004dab70 CKHkS08Fire_StopSounds_maybe
void CKHkS08Fire::StopSounds() {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pUnk2C);
    for (uint32_t i = 0; i < 3; ++i) {
        CKSound* sound = sounds->GetSound(i);  // 0x00112bc0
        if (sound != nullptr) sound->Stop(0);  // 0x001111b0
    }
}

// ==== C2.8 port-rest R10: the runtime ====

namespace {
// DOTD: the fire's state handlers by descriptor (the rows Start writes; TOC +0x6c7c / +0x6c80 / +0x6c84 / +0x6c88).
Ps3MemberFnEntry<CKHkS08Fire::StateFn> g_fireStates[] = {
    {0x00bce1f8u, &CKHkS08Fire::State0, "CKHkS08Fire_State0 0x4dee10", false},
    {0x00bce200u, &CKHkS08Fire::State1, "CKHkS08Fire_State1 0x4df490", false},
    {0x00bce1f0u, &CKHkS08Fire::State2, "CKHkS08Fire_State2 0x4de748", false},
    {0x00bce1e8u, &CKHkS08Fire::State3, "CKHkS08Fire_State3 0x4de0a0", false},
};

CKSrvFx* FireSrvFx() { return static_cast<CKSrvFx*>(g_pEngine->m_srvFx); }

// An effect let go (vt+0x58 StopAndRelease) and its slot cleared, when there is one.
void ReleaseFx(IKFx*& slot, CKHkS08Fire* owner) {
    if (slot == nullptr) return;
    slot->StopAndRelease(owner);
    slot = nullptr;
}

// StartFlameStage's inlined acquisition: the particles data's bit 4 (+0x08) cleared, its start matrix (+0x24) at the
// fire's position, then a free effect of it (CKSrvFx::AcquireFx inlined).
IKFx* AcquireStageFx(CKHkS08Fire* fire, IKSerializable* object) {
    CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(object);
    data->m_unk08 = static_cast<uint8_t>((data->m_unk08 & 0xe0u) | (data->m_unk08 & 0x0fu));
    RwMatrix* start = data->m_unk24;
    const CMatrix34* matrix = fire->m_pMatrix64;
    start->pos.x = matrix->m_pos.x;
    start->pos.y = matrix->m_pos.y;
    start->pos.z = matrix->m_pos.z;
    start->flags &= 0xfffdffffu;
    return FireSrvFx()->AcquireFx(data, fire);
}

// The stages' sound `index` looped at the fire's position unless an instance plays (CountInstances inlined).
void PlayStageSound(CKHkS08Fire* fire, uint32_t index) {
    CKSound* sound = static_cast<CKSoundDictionaryID*>(fire->m_pUnk2C)->GetSound(index);  // 0x00112bc0
    if (sound == nullptr) return;
    if (sound->CountInstances() != 0) return;
    sound->SetPosition(&fire->m_pMatrix64->m_pos);  // 0x00110fa0
    sound->SetLoop(1);                              // 0x00110fd0
    sound->Play(0.0f);                              // 0x00111230; TOC +0x6c8c
}

// The volume under sector 0's root of the game manager's level (OnActivate; the bucket's Start does the same).
void ReparentVolume(CSGLeaf* volume) {
    if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
    CKLevel* level = g_pEngine->m_gameManager->m_level;  // engine +0x8c, +0x18
    static_cast<CKSector*>(level->m_vpSectors.m_pBlock[0])->m_pSectorRoot->AddChild(volume);  // vt+0x70
}
}  // namespace

uint8_t CKHkS08Fire::CallState(uint8_t state, IKTime* clock, int32_t phase, uint8_t other) {
    StateFn fn = ResolvePs3MemberFn(g_fireStates, &m_pStateTable[state * 2u], "CKHkS08Fire state handler");
    if (fn == nullptr) return other;
    return (this->*fn)(clock, phase, other);
}

void CKHkS08Fire::SwitchState(uint8_t next, IKTime* clock) {
    const uint8_t old = m_unk84;
    if (old != 0xff) CallState(old, clock, 2, next);
    m_unk84 = next;
    if (next != 0xff) CallState(next, clock, 1, old);
}

// 0x004dcc78 CKHkS08Fire_Start
void CKHkS08Fire::Start() {
    CKHkActorBase::Start();  // 0x003f6e48
    m_unk88[2] = 0x00bce200u;  // State1 (TOC +0x6c80)
    m_unk88[4] = 0x00bce1f0u;  // State2 (TOC +0x6c84)
    m_unk88[0] = 0x00bce1f8u;  // State0 (TOC +0x6c7c)
    m_unk88[6] = 0x00bce1e8u;  // State3 (TOC +0x6c88)
    m_unk88[1] = 0;
    m_unk88[3] = 0;
    m_unk88[5] = 0;
    m_unk88[7] = 0;
    m_unk84 = 0xff;
    m_unk85 = 4;
    m_pStateTable = m_unk88;
    m_pStageFx0 = nullptr;
    m_pStageFx1 = nullptr;
    m_pStageFx2 = nullptr;
    m_pStageFx3 = nullptr;
    m_unk7F = 1;
    CKAACylinder* volume = static_cast<CKAACylinder*>(m_pUnk54);
    volume->m_ui8OwnerType = 0;
    volume->m_ui16PropertiesFlags = 0;
    volume->m_ui8OwnerType = 1;
    volume->m_pOwner = this;
    volume->m_ba8Infos = static_cast<uint8_t>((volume->m_ba8Infos & 0x7fu) | 0x80u);
    const float radius = m_fUnk5C;
    volume->m_fCylinderRadius = radius;
    volume->m_fRadius = std::sqrt(ppc::fmadds(volume->m_fCylinderHalfHeight, volume->m_fCylinderHalfHeight,
                                              radius * radius));  // 0x00010690
    const float halfHeight = m_fUnk60 * 0.5f;  // TOC +0x6c4c
    volume->m_fCylinderHalfHeight = halfHeight;
    volume->m_fRadius = std::sqrt(ppc::fmadds(halfHeight, halfHeight,
                                              volume->m_fCylinderRadius * volume->m_fCylinderRadius));
}

// 0x004dc850 CKHkS08Fire_Restart (the switches are the inlined ones; no clock).
void CKHkS08Fire::Restart() {
    ReleaseFx(m_pStageFx1, this);
    ReleaseFx(m_pStageFx2, this);
    ReleaseFx(m_pStageFx3, this);
    for (IKFx*& light : m_unkB8) ReleaseFx(light, this);
    if ((m_bitArray & 4u) != 0) {
        if (m_unk84 != 0xff) CallState(m_unk84, nullptr, 2, 0xff);
        m_unk84 = 0xff;
        return;
    }
    StopSounds();
    if (m_unk50 == m_unk84) return;
    m_unk7F = 0;
    SwitchState(m_unk50, nullptr);
    m_unk7F = 1;
}

// 0x004dcdb0 CKHkS08Fire_Update: the frame (phase 0 with the state itself); another state answered: the switch (the leave
// with the next state, the enter with the state re-read before it).
void CKHkS08Fire::Update(IKTime* clock) {
    CKHkActorBase::Update(clock);
    const uint8_t state = m_unk84;
    if (state == 0xff) return;
    const uint8_t next = CallState(state, clock, 0, state);
    if (next == m_unk84) return;
    SwitchState(next, clock);
}

// 0x004dddd0 CKHkS08Fire_OnActivate: the actor base's; the volume under sector 0's root at the fire's position raised by
// half its height (+0x60 * 0.5) and switched on; a current state restarts its stage (StartFlameStage), else the preset
// state (+0x50) is entered with the trigger starters quiet.
void CKHkS08Fire::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    CSGLeaf* volume = static_cast<CSGLeaf*>(m_pUnk54);
    ReparentVolume(volume);
    RwFrame* frame = static_cast<CSGLeaf*>(m_pUnk54)->m_pRwFrame;
    const CVector3& pos = m_pMatrix64->m_pos;
    frame->modelling.pos.z = pos.z;
    frame->modelling.pos.x = pos.x;
    frame->modelling.pos.y = ppc::fmadds(m_fUnk60, 0.5f, pos.y);  // TOC +0x6c4c
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->EnableVolume(static_cast<IKBoundingVolume*>(m_pUnk54));  // 0x00192090
    if (m_unk84 != 0xff) {
        StartFlameStage(static_cast<int8_t>(m_unk84));
        return;
    }
    m_unk7F = 0;
    SwitchState(m_unk50, nullptr);
    m_unk7F = 1;
}

// 0x004db5a8 CKHkS08Fire_OnDeactivate: the actor base's; the volume off; the stage effects 1..3 let go (BUG(original):
// not stage 0's, +0x34), the sounds stopped, the lights let go.
void CKHkS08Fire::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision)->DisableVolume(static_cast<IKBoundingVolume*>(m_pUnk54));  // 0x001920e8
    ReleaseFx(m_pStageFx1, this);
    ReleaseFx(m_pStageFx2, this);
    ReleaseFx(m_pStageFx3, this);
    StopSounds();
    for (IKFx*& light : m_unkB8) ReleaseFx(light, this);
}

// 0x004dc2c0 CKHkS08Fire_MessageProc (the jump table 0x4dc464 / 0x4dc32c / 0x4dc6c4 / 0x4dc77c / 0x4dc594).
int32_t CKHkS08Fire::MessageProc(uint16_t message, void* /*data*/) {
    const uint32_t index = static_cast<uint16_t>(message - 0x996u);
    if (index > 4) return 1;
    if (index == 4) {
        if (m_unk84 > 2) return 0;
        m_unk7F = 0;
        SwitchState(static_cast<uint8_t>(m_unk84 + 1), nullptr);
        m_unk7F = 1;
        return 0;
    }
    m_unk7F = 0;
    SwitchState(static_cast<uint8_t>(index), nullptr);
    m_unk7F = 1;
    return 0;
}

// 0x004dd2a0 CKHkS08Fire_StartFlameStage_maybe
void CKHkS08Fire::StartFlameStage(int32_t stage) {
    switch (stage) {
    case 0:
        if (m_pStageFx0 != nullptr) return;
        m_pStageFx0 = AcquireStageFx(this, m_pUnk30);
        return;
    case 1:
        if (m_pStageFx1 == nullptr) m_pStageFx1 = AcquireStageFx(this, m_pUnk38);
        PlayStageSound(this, 0);
        return;
    case 2:
        if (m_pStageFx2 == nullptr) m_pStageFx2 = AcquireStageFx(this, m_pUnk40);
        PlayStageSound(this, 1);
        return;
    case 3:
        if (m_pStageFx3 == nullptr) m_pStageFx3 = AcquireStageFx(this, m_pUnk48);
        PlayStageSound(this, 2);
        return;
    default:
        return;
    }
}

// The states' inlined light acquisition: light `n` (+0xa8) at the position (+0x4) of its object (+0xc8) when there is
// one, then a free effect of it (CKSrvFx::AcquireFx inlined).
IKFx* CKHkS08Fire::AcquireLightFx(uint32_t n) {
    IKSerializable* const lights[4] = {m_pUnkA8, m_pUnkAC, m_pUnkB0, m_pUnkB4};
    IKSerializable* const places[4] = {m_pUnkC8, m_pUnkCC, m_pUnkD0, m_pUnkD4};
    CKPointLightFxData* light = static_cast<CKPointLightFxData*>(lights[n]);
    if (places[n] != nullptr) {
        // The object's +0x4..+0xc (a CSGHotSpot's relative position_maybe).
        const CVector3& at = static_cast<CSGHotSpot*>(places[n])->m_v3RelativePosition;
        light->m_vPosition.z = at.z;
        light->m_vPosition.x = at.x;
        light->m_vPosition.y = at.y;
    }
    return FireSrvFx()->AcquireFx(light, this);
}

// 0x004dace8 CKHkS08Fire_ProcessPowerBucketContacts_maybe
void CKHkS08Fire::ProcessPowerBucketContacts(IKTime* clock) {
    const float kTime = -1000.0f;  // TOC (0xc08f400000000000 as a double)
    for (ICollision* c = static_cast<ICollision*>(static_cast<IKBoundingVolume*>(m_pUnk54)->m_CollisionResList); c != nullptr;
         c = c->m_pNext) {
        IKBoundingVolume* other;
        if (static_cast<IKBoundingVolume*>(c->GetBoundingVolume1())->m_pOwner == this) {  // vt+0x00
            c->GetBoundingVolume1();
            other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2());  // vt+0x04
        } else {
            c->GetBoundingVolume2();
            other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume1());
        }
        if (c->HasContactSet() == 0) continue;  // vt+0x08
        IKSerializable* owner = other->m_pOwner;
        if (ContactHistory_Touch(kTime, kTime, &m_unk58, other, owner) == 0) continue;  // TocBridge 0x98f380
        if (owner->GetClassID() != 0xc3) continue;  // vt+0x18: a CKHkS08PowerBucket
        m_ui8NextState = m_unk84 == 0 ? 0xff : static_cast<uint8_t>(m_unk84 - 1);
    }
    ContactHistory_Update(&m_unk58, clock);  // TocBridge 0x98f430
}

// 0x004dee10 CKHkS08Fire_State0: the smallest flame. Enter: from a higher state (1..0xfe) the starter +0x74, from 0
// itself the starter +0x6c (with +0x7f); stage 0 started, its light acquired, the state time 0. Leave: stage 0's effect
// and light let go. Frame: stage 0 and its light kept, the state time advanced. Answers `other`.
uint8_t CKHkS08Fire::State0(IKTime* clock, int32_t phase, uint8_t other) {
    if (phase == 1) {
        if (static_cast<uint8_t>(other - 1u) <= 0xfdu) {
            if (m_unk7F != 0) QueueTriggerSignals(&m_unk74);  // 0x00236338
        } else if (other != 0xff && m_unk7F != 0) {
            QueueTriggerSignals(&m_unk6C);
        }
        StartFlameStage(0);
        if (m_unkB8[0] == nullptr) m_unkB8[0] = AcquireLightFx(0);
        m_fStateTime = 0.0f;  // a word 0
        return other;
    }
    if (phase == 2) {
        ReleaseFx(m_pStageFx0, this);
        ReleaseFx(m_unkB8[0], this);
        return other;
    }
    if (phase != 0) return other;
    StartFlameStage(0);
    if (m_unkB8[0] == nullptr) m_unkB8[0] = AcquireLightFx(0);
    m_fStateTime = m_fStateTime + clock->m_afDeltaTime[0];  // +0x1c
    return other;
}

// 0x004df490 / 0x004de748 / 0x004de0a0 CKHkS08Fire_State1 / State2 / State3: flame stage `n`. Enter: from a higher
// state (n+1..0xfe) the starter +0x74, from a lower one the starter +0x6c (with +0x7f); stage n started, its light
// acquired, no next state, the state time 0. Leave: stage n's effect and light let go; enabled (+0xc bit 2 clear) its
// sound (n - 1) stopped; no next state. Frame: stage n and its light kept; states 1 / 2 with a duration (+0x20 / +0x24
// above 0) count the state time and ask for the next state once it is reached (<=); state 3 counts it always; a power
// bucket touching asks for the stage below; the next state asked for, else `other`.
uint8_t CKHkS08Fire::FlameState(uint32_t n, IKTime* clock, int32_t phase, uint8_t other) {
    IKFx** const stageFx[4] = {&m_pStageFx0, &m_pStageFx1, &m_pStageFx2, &m_pStageFx3};
    if (phase == 1) {
        if (static_cast<uint8_t>(other - (n + 1u)) <= 0xfeu - (n + 1u)) {
            if (m_unk7F != 0) QueueTriggerSignals(&m_unk74);  // 0x00236338
        } else if (other < n && m_unk7F != 0) {
            QueueTriggerSignals(&m_unk6C);
        }
        StartFlameStage(static_cast<int32_t>(n));
        if (m_unkB8[n] == nullptr) m_unkB8[n] = AcquireLightFx(n);
        m_ui8NextState = 0xff;
        m_fStateTime = 0.0f;  // a word 0
        return other;
    }
    if (phase == 2) {
        ReleaseFx(*stageFx[n], this);
        ReleaseFx(m_unkB8[n], this);
        if ((m_bitArray & 4u) == 0) {
            CKSound* sound = static_cast<CKSoundDictionaryID*>(m_pUnk2C)->GetSound(n - 1);  // 0x00112bc0
            if (sound != nullptr) sound->Stop(0);  // 0x001111b0
        }
        m_ui8NextState = 0xff;
        return other;
    }
    if (phase != 0) return other;
    StartFlameStage(static_cast<int32_t>(n));
    if (m_unkB8[n] == nullptr) m_unkB8[n] = AcquireLightFx(n);
    if (n == 3) {
        m_fStateTime = m_fStateTime + clock->m_afDeltaTime[0];
    } else {
        const float duration = n == 1 ? m_fUnk20 : m_fUnk24;
        if (!(duration <= 0.0f)) {  // ble (TOC +0x6c8c)
            const float time = m_fStateTime + clock->m_afDeltaTime[0];
            m_fStateTime = time;
            if (duration <= time) m_ui8NextState = static_cast<uint8_t>(n + 1);  // cror lt|eq
        }
    }
    ProcessPowerBucketContacts(clock);  // 0x004dace8
    return m_ui8NextState != 0xff ? m_ui8NextState : other;
}

uint8_t CKHkS08Fire::State1(IKTime* clock, int32_t phase, uint8_t other) { return FlameState(1, clock, phase, other); }
uint8_t CKHkS08Fire::State2(IKTime* clock, int32_t phase, uint8_t other) { return FlameState(2, clock, phase, other); }
uint8_t CKHkS08Fire::State3(IKTime* clock, int32_t phase, uint8_t other) { return FlameState(3, clock, phase, other); }
