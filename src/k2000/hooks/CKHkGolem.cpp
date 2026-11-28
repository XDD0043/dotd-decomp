// CKHkGolem.cpp - reconstructed original translation unit 0x4bed00-0x4c4a00 (GAME_TOC1, main_toc1), 45 functions, 42 live.
// Primary class: CKHkGolem  key 0x3182  category Hook  size 0xc0  vtable 0xb29260
// Other owners: GolemAttack (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4bed00  CKHkGolem_GetHealthPercent_maybe
//   [x] 0x4bed50  CKHkGolem_SetByte45_maybe
//   [x] 0x4bed58  CKHkGolem_SpawnBonuses_maybe
//   [x] 0x4beda0  CKHkGolem_CreatePhaseCondition
//   [x] 0x4befc0  CKHkGolem_UpdateProjectileLaunchers_maybe
//   [x] 0x4bf248  CKHkGolem_Resume  (empty / no effect: inherited)
//   [x] 0x4bf270  CKHkGolem_Pause  (empty / no effect: inherited)
//   [x] 0x4bf298  CKHkGolem_Stop
//   [x] 0x4bf308  CKHkGolem_PostLoad
//   [x] 0x4bf348  CKHkGolem_MessageProc
//   [ ] 0x4bf5d0  CKHkGolem_Save
//   [x] 0x4bf5f8  CKHkGolem_RecursiveRegistration  (= the inherited slot: CKHkActorBase_d82_maybe_LevelReset 0x3f6ee8, then 1)
//   [ ] 0x4bf620  CKHkGolem_Construct_2  [dead]
//   [x] 0x4bf6b8  CKHkGolem_Construct
//   [x] 0x4bf750  CKHkGolem_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [ ] 0x4bf7f8  RegisterCKHkGolemClass
//   [ ] 0x4bf880  _GLOBAL__D_4bf880
//   [ ] 0x4bf890  _GLOBAL__I_4bf890
//   [x] 0x4bf8a0  CKHkGolem_AddObjectToList2C_maybe
//   [x] 0x4bf970  CKHkGolem_Start
//   [x] 0x4bf9f8  CKHkGolem_SetTime54ToNow_maybe
//   [x] 0x4bfa18  CKHkGolem_Restart
//   [x] 0x4bfb88  CKHkGolem_ReleaseAllEntryObjects_maybe
//   [x] 0x4bfc88  CKHkGolem_OnDeactivate
//   [x] 0x4bfdf0  CKHkGolem_SetActiveWithBossGauge_maybe
//   [x] 0x4c00c8  CKHkGolem_OnActivate
//   [x] 0x4c0388  CKHkGolem_Destroy
//   [x] 0x4c0678  CKHkGolem_GetInfo
//   [x] 0x4c07c0  CKHkGolem_RemoveObjectFromList2C_maybe
//   [x] 0x4c0850  CKHkGolem_Destructor
//   [x] 0x4c09b0  CKHkGolem_BaseDestructor
//   [x] 0x4c0b10  CKHkGolem_DeletingDestructor  (the deleting form of the destructor)
//   [x] 0x4c0c80  CKHkGolem_GetHealthPercentInt_maybe
//   [x] 0x4c0ce0  CKHkGolem_Create
//   [ ] 0x4c0d88  CKHkGolem_SaveRefArray_maybe  [dead]
//   [x] 0x4c0ec8  CKHkGolem_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x4c0ff0  CKHkGolem_LoadRefArray34_maybe
//   [x] 0x4c11c0  CKHkGolem_Load
//   [x] 0x4c2288  GolemAttack_TriggerStepExplosions_maybe
//   [x] 0x4c2758  CKHkGolem_SpawnFxAt_maybe
//   [ ] 0x4c29f8  CKHkGolem_AcquireIndexedFxNodes_maybe  [dead]
//   [x] 0x4c2dc8  CKHkGolem_SpawnContactParticleFx_maybe
//   [x] 0x4c31c0  CKHkGolem_ProcessContacts_maybe
//   [x] 0x4c3998  CKHkGolem_UpdateAnimMarkEvents_maybe
//   [x] 0x4c4838  CKHkGolem_Update
//
//   [x] 0x9c56e8  CKHkGolem_IsKindOfClass  [inline]
//   [ ] 0x9c5740  CKHkGolem_GetClassType  [inline]
//   [ ] 0x9c5748  CKHkGolem_GetClassID  [inline]
//   [x] 0x9c5750  CKHkGolem_GetTriggerProp2  [inline]
//   [x] 0x9c5760  CKHkGolem_vf100  [inline]
//   [x] 0x9c5768  CKHkGolem_vf104  [inline]
//   [x] 0x9c5770  CKHkGolem_vf108  [inline]
//   [x] 0x9c5778  KStub_Nop_9c5778  [inline]
//   [x] 0x9c5780  KStub_Nop_9c5780  [inline]
//   [x] 0x9c5788  CKHkGolem_vfFC_GetCount_maybe  [inline]
//   [x] 0x9c5790  CKHkGolem_vfF8_GetAt_maybe  [inline]
#include "k2000/hooks/CKHkGolem.h"

#include <new>

#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "k2000/system/CTimeManager.h"
#include "k2000/system/IKTime.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rtanim/RtAnim.h"
#include "crt/ppc_ops.h"
#include "Spyro2008/groups/CKGrpS08Meca.h"
#include "Spyro2008/logic/CKS08GameManager.h"
#include "k2000/components/CKBonusData.h"
#include "k2000/core/IKInfo.h"
#include "k2000/core/Stub.h"
#include "k2000/fx/IKFx.h"
#include "k2000/graphical/CKAnmKeyFrameController.h"
#include "k2000/logic/CKGolemAttackCommon.h"
#include "k2000/logic/CKGolemPhaseManager.h"
#include "k2000/logic/CKMarkedFX.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/animation/CKAnimationMarkContainer.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/GolemPhaseCondAnd.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/KBase201.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "k2000/logic/CKDamage.h"
#include "k2000/logic/fx/CKParticlesEffectNodeFx.h"
#include "k2000/math/Math.h"
#include "k2000/misc/OnNewHit.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"
#include <cmath>
#include "platform/fps.h"

// 0x004bf6b8 CKHkGolem_Construct (the same body inlined in CKHkGolem_Create 0x4c0ce0): the four vectors
// empty with capacity 1.
CKHkGolem::CKHkGolem() {
    m_pAttachedObjects = 0;
    m_pContactHistory = 0;
    m_unk34.m_ui32NbElt = 1;
    m_unk34.m_pBlock = nullptr;
    m_unk34.m_ui32NbUsedElt = 0;
    m_unk58.m_ui32NbElt = 1;
    m_unk58.m_pBlock = nullptr;
    m_unk58.m_ui32NbUsedElt = 0;
    m_unk64.m_ui32NbElt = 1;
    m_unk64.m_pBlock = nullptr;
    m_unk64.m_ui32NbUsedElt = 0;
    m_unk70.m_ui32NbElt = 1;
    m_unk70.m_ui32NbUsedElt = 0;
    m_unk70.m_pBlock = nullptr;
}

namespace {
// The inlined TVector start: capacity 1 and a fresh one-element block (the old block is not freed).
template <class T>
void StartVector(TVector<T, 1>& vector) {
    vector.m_ui32NbElt = 1;
    vector.m_pBlock = static_cast<T*>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(T))));
}

// The inlined TVector push (growth step 1).
template <class T>
void Push(TVector<T, 1>& vector, T element) {
    if (vector.m_ui32NbElt == vector.m_ui32NbUsedElt) {
        uint32_t capacity = vector.m_ui32NbUsedElt + 1;
        if (capacity == 0) capacity = 1;
        vector.m_pBlock = static_cast<T*>(
            Mem_ReallocAligned16(vector.m_pBlock, capacity * static_cast<uint32_t>(sizeof(T))));
        vector.m_ui32NbElt = capacity;
    }
    vector.m_pBlock[vector.m_ui32NbUsedElt] = element;
    vector.m_ui32NbUsedElt++;
}

// A record's common head: the word, then the reference.
template <class Record>
void ReadRecordHead(IKFile* file, Record* record) {
    ReadU32LE(file, &record->m_ui32Value);
    IKFile_ReadRef(file, &record->m_pObject);
}
}  // namespace

// 0x004c0ff0 CKHkGolem_LoadRefArray34_maybe: a count, then that many references pushed one by one (read into
// a local first). The type argument (always 0) is not used.
void CKHkGolem::LoadObjectVector(IKFile* file, int32_t /*type*/) {
    uint32_t count = 0;
    ReadU32LE(file, &count);
    StartVector(m_unk34);
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* object = nullptr;
        IKFile_ReadRef(file, &object);
        Push(m_unk34, object);
    }
}

// 0x004c11c0 CKHkGolem_Load
int32_t CKHkGolem::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type != K_LEVEL_PLATEFORMS) return 1;
    IKFile_ReadRef(file, &m_pPhaseManager);
    LoadObjectVector(file, K_LEVEL_PLATEFORMS);

    uint32_t count = 0;
    ReadU32LE(file, &count);
    StartVector(m_unk58);
    for (uint32_t i = 0; i < count; ++i) {
        CKHkGolemNode18* node = static_cast<CKHkGolemNode18*>(::operator new(sizeof(CKHkGolemNode18)));
        node->m_records.m_pBlock = nullptr;
        node->m_records.m_ui32NbUsedElt = 0;
        node->m_records.m_ui32NbElt = 1;
        IKFile_ReadRef(file, &node->m_pObject);
        IKFile_ReadRef(file, &node->m_pObject14);
        ReadU8(file, &node->m_unk10);
        uint32_t records = 0;
        ReadU32LE(file, &records);
        StartVector(node->m_records);
        for (uint32_t j = 0; j < records; ++j) {
            CKHkGolemRecord8* record = static_cast<CKHkGolemRecord8*>(::operator new(sizeof(CKHkGolemRecord8)));
            record->m_pObject = nullptr;
            record->m_ui32Value = 0;
            ReadRecordHead(file, record);
            Push(node->m_records, record);
        }
        Push(m_unk58, node);
    }

    ReadU32LE(file, &count);
    StartVector(m_unk64);
    for (uint32_t i = 0; i < count; ++i) {
        auto* node = static_cast<CKHkGolemNode10<CKHkGolemRecordC>*>(
            ::operator new(sizeof(CKHkGolemNode10<CKHkGolemRecordC>)));
        node->m_records.m_pBlock = nullptr;
        node->m_records.m_ui32NbUsedElt = 0;
        node->m_records.m_ui32NbElt = 1;
        IKFile_ReadRef(file, &node->m_pObject);
        uint32_t records = 0;
        ReadU32LE(file, &records);
        StartVector(node->m_records);
        for (uint32_t j = 0; j < records; ++j) {
            CKHkGolemRecordC* record = static_cast<CKHkGolemRecordC*>(::operator new(sizeof(CKHkGolemRecordC)));
            record->m_pObject = nullptr;
            record->m_ui32Value = 0;
            record->m_unk8 = nullptr;
            ReadRecordHead(file, record);
            record->m_unk8 = nullptr;
            Push(node->m_records, record);
        }
        Push(m_unk64, node);
    }

    ReadU32LE(file, &count);
    StartVector(m_unk70);
    for (uint32_t i = 0; i < count; ++i) {
        auto* node = static_cast<CKHkGolemNode10<CKHkGolemRecord20>*>(
            ::operator new(sizeof(CKHkGolemNode10<CKHkGolemRecord20>)));
        node->m_records.m_pBlock = nullptr;
        node->m_records.m_ui32NbUsedElt = 0;
        node->m_records.m_ui32NbElt = 1;
        IKFile_ReadRef(file, &node->m_pObject);
        uint32_t records = 0;
        ReadU32LE(file, &records);
        StartVector(node->m_records);
        for (uint32_t j = 0; j < records; ++j) {
            CKHkGolemRecord20* record = static_cast<CKHkGolemRecord20*>(::operator new(sizeof(CKHkGolemRecord20)));
            record->m_pObject = nullptr;
            record->m_ui32Value = 0;
            record->m_unk8 = 0;
            record->m_unkC = 0.0f;
            record->m_unk10 = 0;
            record->m_unk14 = 0.0f;
            record->m_unk18 = 0.0f;
            record->m_unk1C = 0;
            ReadRecordHead(file, record);
            ReadU32LE(file, &record->m_unk8);
            ReadF32LE(file, &record->m_unkC);
            ReadU32LE(file, &record->m_unk10);
            Push(node->m_records, record);
        }
        Push(m_unk70, node);
    }

    IKFile_ReadRef(file, &m_pHitExplosionFx);
    IKFile_ReadRef(file, &m_pContactParticlesFx);
    ReadS32LE(file, &m_i32MaxHealth);
    IKFile_ReadRef(file, &m_pBonusTable);
    IKFile_ReadRef(file, &m_pDefaultStepDamage);
    ReadU8(file, &m_bShowBossGauge);
    IKFile_ReadRef(file, &m_pMarkedFx);
    for (float& value : m_af94) ReadF32LE(file, &value);
    return 1;
}

// 0x004bf308 CKHkGolem_PostLoad (CKHkS08DragonCityGolem_PostLoad 0x4d5c10 is this one with no addition): the
// actor base's, then a new matrix at +0x84 whatever the type.
int32_t CKHkGolem::PostLoad(int32_t type) {
    CKHkActorBase::PostLoad(type);
    m_pSavedMatrix = reinterpret_cast<CMatrix34*>(RwMatrixCreate());  // RwMatrixCreate_Thunk 0x23fa68
    return 1;
}

// 0x004bf970 CKHkGolem_Start: the run-time state cleared and the two time stamps set to the clock's game time
// (the frame clock's accumulated scalable time, IKTime +0x04). KStub_Nop_5cebf0(+0xbc, this) is empty.
void CKHkGolem::Start() {
    CKHkActorBase::Start();
    const float now = g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
    m_i32DamageMark = 0;
    m_i32TotalDamageTaken = 0;
    m_bBossFightRunning = 0;
    m_fLastMarkGameTime = now;
    m_fStartGameTime = now;
    m_bEnabled = 1;
}

// ---- C2.8: the golem at run time ----

float GolemClockTime() {
    return g_pEngine->m_timeManager->m_pTime->m_afCurrentTime[IKTime::SCALABLE_GAME_TIME];
}

CKGolemPhaseManager* CKHkGolem::PhaseManager() const { return static_cast<CKGolemPhaseManager*>(m_pPhaseManager); }

namespace {
CSGLeaf* NodeOf(const CKHkGolem* golem) { return static_cast<CSGLeaf*>(golem->m_pKGLObject); }
CKS08GameManager* GameManager() { return static_cast<CKS08GameManager*>(g_pEngine->m_gameManager); }
// The game manager's meca group (+0x0c, a CKGrpS08Meca): its byte +0x4c is set while a boss fight with health runs
// (the byte is the first of the PS3 word, the high byte here as in CKGrpS08Meca_Start).
void SetBossFightByte(uint8_t on) {
    CKGrpS08Meca* meca = static_cast<CKGrpS08Meca*>(g_pEngine->m_gameManager->m_unk04[2]);
    meca->m_unk4c = (meca->m_unk4c & 0x00ffffffu) | (static_cast<uint32_t>(on) << 24);
}
}  // namespace

// 0x004bf9f8 CKHkGolem_SetTime54ToNow_maybe
void CKHkGolem::SetTime54ToNow() { m_fLastMarkGameTime = GolemClockTime(); }

// 0x004becc8 CKHkGolem_ApplyDamagePoints_maybe
void CKHkGolem::ApplyDamagePoints(int32_t points) {
    const int32_t health = m_i32Health - points;
    m_i32TotalDamageTaken = m_i32TotalDamageTaken + points;
    m_i32Health = health;
    if (health < 0) m_i32Health = 0;
}

// 0x004bed00 CKHkGolem_GetHealthPercent_maybe: 0 without a maximum; else health / maximum x 100 (the integers as
// floats: fcfid / frsp).
float CKHkGolem::GetHealthPercent() const {
    if (m_i32MaxHealth < 1) return 0.0f;
    const float health = static_cast<float>(static_cast<double>(static_cast<int64_t>(m_i32Health)));
    const float maximum = static_cast<float>(static_cast<double>(static_cast<int64_t>(m_i32MaxHealth)));
    return health / maximum * 100.0f;
}

// 0x004c0c80 CKHkGolem_GetHealthPercentInt_maybe: the same truncated (fctiwz).
int32_t CKHkGolem::GetHealthPercentInt() const {
    if (m_i32MaxHealth < 1) return 0;
    const float health = static_cast<float>(static_cast<double>(static_cast<int64_t>(m_i32Health)));
    const float maximum = static_cast<float>(static_cast<double>(static_cast<int64_t>(m_i32MaxHealth)));
    return static_cast<int32_t>(health / maximum * 100.0f);
}

// 0x004beda0 CKHkGolem_CreatePhaseCondition (the factory's body is GolemPhaseCond::Create).
GolemPhaseCond* CKHkGolem::CreatePhaseCondition(uint32_t id) { return GolemPhaseCond::Create(id); }

// 0x004c2dc8 CKHkGolem_SpawnContactParticleFx_maybe: with a hot spot, the particle data +0x80 loses its flag bit 4 and
// an effect of it is acquired (CKSrvFx::AcquireFx inlined, the reserving copy); the effect is placed at `point` and
// oriented along `direction` (normalised in place) with an up axis built from it (a vector with three equal components
// gets x + 1 first), then its reservation is released. (The hot spot's world position is read and not used.)
void CKHkGolem::SpawnContactParticleFx(CSGHotSpot* hotSpot, const CVector3* point, CVector3* direction) {
    if (hotSpot == nullptr) return;
    CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_pContactParticlesFx);
    data->m_ui8Flags = static_cast<uint8_t>(data->m_ui8Flags & ~0x10u);
    IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);
    if (fx == nullptr) return;
    const float one = 1.0f;    // TOC1 +0x6720
    const float zero = 0.0f;   // TOC1 +0x668c
    const float z = direction->z;
    float x = direction->x;
    const float y = direction->y;
    if (z == x && x == y && z == y) x = x + one;
    CVector3 up;
    up.x = ppc::fmsubs(x, z, y * y);
    up.y = ppc::fmsubs(y, direction->x, z * direction->z);
    up.z = ppc::fmsubs(z, direction->y, x * direction->x);
    float length = std::sqrt(ppc::fmadds(up.z, up.z, ppc::fmadds(up.x, up.x, up.y * up.y)));  // Math_Sqrtf 0x10690
    if (length != zero) {
        const float scale = one / length;
        up.z = up.z * scale;
        up.x = up.x * scale;
        up.y = up.y * scale;
    }
    length = std::sqrt(ppc::fmadds(direction->z, direction->z,
                                   ppc::fmadds(direction->x, direction->x, direction->y * direction->y)));
    if (length != zero) {
        const float scale = one / length;
        direction->z = scale * direction->z;
        direction->x = scale * direction->x;
        direction->y = scale * direction->y;
    }
    CVector3 unused;
    hotSpot->GetWorldPosition(&unused);  // 0x000ce790 (the result is not used)
    CKParticlesEffectNodeFx* effect = static_cast<CKParticlesEffectNodeFx*>(fx);
    SetOwnedParticleEffectPosition(effect, point, this);            // 0x001cdce0
    SetOwnedParticleEffectTransform(effect, direction, &up, this);  // 0x001cdc08
    fx->ReleaseReservation(this);                                   // vt+0x54
}

// 0x004c31c0 CKHkGolem_ProcessContacts_maybe: the base golems' contact test (CKHkS08DragonCityGolem has its own). Every
// collision of the attack's volumes with a contact set, the golem's volume and the other one told apart by the owner:
// the other volume must deal damage (property bit 3); its contact is touched in the history (+0x20, times -1000) and a
// new one with a volume of the attack whose hits count (+0x0c), through a damage without +0x08, hits: the hit explosion
// (+0x7c) at the contact turned toward the attacker, the bonuses, the particle effect at the volume's hot spot, a combo
// hit for a hero (0x25c2) and the damage taken (+0x40) off the health (+0x8c, not below 0). The history ages at the end.
void CKHkGolem::ProcessContacts(IKTime* clock, CKGolemAttackCommon* attack) {
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40 (TOC +0x66ac)
    for (uint32_t i = 0; i < attack->m_unk08Count; ++i) {
        IKBoundingVolume* volume = attack->m_apUnk08[i]->m_unk00;
        for (ICollision* c = static_cast<ICollision*>(volume->m_CollisionResList); c != nullptr; c = c->m_pNext) {
            IKBoundingVolume* own;
            IKBoundingVolume* other;
            if (static_cast<IKBoundingVolume*>(c->GetBoundingVolume1())->m_pOwner == this) {  // vt+0x00
                own = static_cast<IKBoundingVolume*>(c->GetBoundingVolume1());
                other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2());  // vt+0x04
            } else {
                own = static_cast<IKBoundingVolume*>(c->GetBoundingVolume2());
                other = static_cast<IKBoundingVolume*>(c->GetBoundingVolume1());
            }
            if (c->HasContactSet() == 0) continue;  // vt+0x08
            CKGolemAttackCommon::Entry08* entry = nullptr;  // the last entry of this volume
            for (uint32_t k = 0; k < attack->m_unk08Count; ++k) {
                if (attack->m_apUnk08[k]->m_unk00 == own) entry = attack->m_apUnk08[k];
            }
            if ((other->m_ui16PropertiesFlags & 8u) == 0) continue;
            IKSerializable* attacker = other->m_pOwner;
            if (ContactHistory_Touch(-1000.0f, -1000.0f, &m_pContactHistory, other, attacker) == 0) continue;  // 0x0098f380
            if (entry == nullptr) continue;
            CKDamage* damage = static_cast<CKDamage*>(other->m_unk1c);
            if (damage == nullptr || damage->m_i32DamageKind != 0 || entry->m_unk0c == 0) continue;
            const CVector3 contact = *c->GetWorldContactPoint();  // vt+0x20
            const RwFrame* attackerFrame = static_cast<CSGMovable*>(static_cast<IKHook*>(attacker)->m_pKGLObject)->m_pRwFrame;
            const RwFrame* ownFrame = own->m_pRwFrame;
            float dy = attackerFrame->ltm.pos.y - ownFrame->ltm.pos.y;
            float dx = attackerFrame->ltm.pos.x - ownFrame->ltm.pos.x;
            float dz = attackerFrame->ltm.pos.z - ownFrame->ltm.pos.z;
            const float length = std::sqrt(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));  // Math_Sqrtf 0x10690
            if (length != 0.0f) {  // TOC +0x668c
                const float scale = 1.0f / length;  // TOC +0x6720
                dz = dz * scale;
                dx = dx * scale;
                dy = dy * scale;
            }
            CVector3 direction = {dx, dy, dz};
            IKFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(static_cast<IKFxData*>(m_pHitExplosionFx), this);
            if (fx != nullptr) {
                CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(fx);
                explosion->SetPosition(&direction, &contact, this);  // 0x001b6438
                explosion->Trigger(this, nullptr);                   // 0x001b82a8
                fx->ReleaseReservation(this);                        // vt+0x54
            }
            SpawnBonuses(&contact, &kAxisY);  // 0x001265b0 (CKSrvBonus_SpawnBonusesArgSwap_maybe)
            CSGHotSpot* hotSpot = entry->m_unk04;
            CVector3 offset;
            hotSpot->GetWorldPosition(&offset);  // 0x000ce790 (the offset below is not used)
            offset.x = contact.x - offset.x;
            offset.y = contact.y - offset.y;
            offset.z = contact.z - offset.z;
            CMatrix34 matrix;
            hotSpot->GetWorldMatrix(&matrix);  // 0x000ce970 (not used)
            CVector3 point = contact;
            CVector3 along = direction;
            SpawnContactParticleFx(hotSpot, &point, &along);  // 0x004c2dc8
            if (static_cast<uint8_t>(attacker->IsKindOfClass(0x25c2)) != 0) {
                CKS08GameManager* manager = static_cast<CKS08GameManager*>(g_pEngine->m_gameManager);
                const uint8_t dragon = static_cast<CKHkS08Hero*>(attacker)->GetDragonIndex();  // 0x00361960
                const CVector3 hit = *c->GetWorldContactPoint();  // vt+0x20
                OnNewHitW(manager, dragon, &hit);  // OnNewHitW_2 0x004fe5f8
            }
            float amount = damage->m_bContinuous != 0 ? clock->m_afDeltaTime[0] * damage->m_fAmount : damage->m_fAmount;
            // --fps N (not in the original): a per-second damage counts one 60 Hz frame per new contact, as at 60 fps.
            if (dotd::fps::Unlocked() && damage->m_bContinuous != 0) {
                amount = dotd::fps::Dt60(clock->m_afDeltaTime[0]) * damage->m_fAmount;
            }
            const int32_t points = static_cast<int32_t>(ppc::fctidz(amount));  // fctidz, the low word
            m_i32TotalDamageTaken = points + m_i32TotalDamageTaken;
            m_i32Health = m_i32Health - points;
            if (m_i32Health < 0) m_i32Health = 0;
        }
    }
    ContactHistory_Update(&m_pContactHistory, clock);  // 0x0098f430
}

// 0x004bed58 CKHkGolem_SpawnBonuses_maybe: CKSrvBonus_SpawnBonusesArgSwap_maybe 0x1265b0 (the service's SpawnBonuses
// with the position as the base too and every mode) with the golem's table (+0x28).
void CKHkGolem::SpawnBonuses(const CVector3* position, const CVector3* direction) {
    static_cast<KBase201*>(g_pEngine->m_srvBonus)
        ->SpawnBonuses(static_cast<CKBonusData*>(m_pBonusTable), position, direction, position, 0);  // 0x00126278
}

// 0x004c2758 CKHkGolem_SpawnFxAt_maybe: a pooled effect of the hit explosion's data (+0x7c; the inlined CKSrvFx lookup,
// reserved, owned by the golem, started) placed at `position` turned to `direction`, triggered and released (vt+0x54).
void CKHkGolem::SpawnFxAt(const CVector3* position, const CVector3* direction) {
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    IKFx* effect = fx->AcquireFx(static_cast<IKFxData*>(m_pHitExplosionFx), this);
    if (effect == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
    explosion->SetPosition(direction, position, this);  // 0x001b6438
    explosion->Trigger(this, 0);                        // 0x001b82a8
    explosion->ReleaseReservation(this);                // vt+0x54
}

// 0x004bf8a0 CKHkGolem_AddObjectToList2C_maybe: `object` pushed at the head of the list unless it is there.
void CKHkGolem::AddObject(IKSerializable* object) {
    for (ObjectNode* node = m_pAttachedObjects; node != nullptr; node = node->m_pNext) {
        if (node->m_pObject == object) return;
    }
    ObjectNode* node = new ObjectNode;  // FreeListPool 0x00ceaa30
    node->m_pObject = object;
    node->m_pNext = m_pAttachedObjects;
    m_pAttachedObjects = node;
}

// 0x004c07c0 CKHkGolem_RemoveObjectFromList2C_maybe: the first node of `object` unlinked and back to the pool.
void CKHkGolem::RemoveObject(IKSerializable* object) {
    ObjectNode* head = m_pAttachedObjects;
    if (head == nullptr) return;
    if (head->m_pObject == object) {
        m_pAttachedObjects = head->m_pNext;
        delete head;
        return;
    }
    for (ObjectNode* previous = head; previous->m_pNext != nullptr; previous = previous->m_pNext) {
        ObjectNode* node = previous->m_pNext;
        if (node->m_pObject != object) continue;
        previous->m_pNext = node->m_pNext;
        delete node;
        return;
    }
}

// 0x004bfb88 CKHkGolem_ReleaseAllEntryObjects_maybe: every running particle effect (+0x64 records) stopped and released
// (vt+0x58). BUG(original): the records keep their pointers.
void CKHkGolem::ReleaseAllEntryObjects() {
    for (uint32_t i = 0; i < m_unk64.m_ui32NbUsedElt; ++i) {
        for (uint32_t j = 0; j < m_unk64.m_pBlock[i]->m_records.m_ui32NbUsedElt; ++j) {
            IKFx* effect = m_unk64.m_pBlock[i]->m_records.m_pBlock[j]->m_unk8;
            if (effect != nullptr) effect->StopAndRelease(this);
        }
    }
}

// 0x004bf348 CKHkGolem_MessageProc: the actor base's answer merged with the golem's: 0x996 adds to the health, 0x997
// sets it, 0x998 adds a percentage of the maximum, 0x999 sets one (signed divisions; the health clamped to 0..maximum);
// 0x99a / 0x99b show / hide (vt+0xd0), 0x99c / 0x99d enable / disable (vt+0xcc); 0xc32 answers 0.
int32_t CKHkGolem::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);
    int32_t own = 0;
    const int32_t* value = static_cast<const int32_t*>(data);
    switch (message) {
    case 0x996:
    case 0x997:
    case 0x998:
    case 0x999: {
        int32_t health;
        if (message == 0x996) {
            health = *value + m_i32Health;
        } else if (message == 0x997) {
            health = *value;
        } else if (message == 0x998) {
            health = (*value * m_i32MaxHealth) / 100 + m_i32Health;
        } else {
            health = (*value * m_i32MaxHealth) / 100;
        }
        m_i32Health = health;
        if (health < 0) {
            m_i32Health = 0;
        } else if (m_i32MaxHealth < health) {
            m_i32Health = m_i32MaxHealth;
        }
        break;
    }
    case 0x99a: SetVisible(1); break;
    case 0x99b: SetVisible(0); break;
    case 0x99c: SetEnabled(1); break;
    case 0x99d: SetEnabled(0); break;
    case 0xc32: break;
    default: own = 1; break;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    if (base != 0) return own;
    return 0;
}

// 0x004c0678 CKHkGolem_GetInfo: the trigger values 2 (the health +0x8c, an integer: GetTriggerProp2 0x9c5750) and 5 /
// 6 (the health percentage, a float: 0x4bed00). BUG(original): case 5 falls into case 6 (its integer accessor
// 0x4c0c80 is overwritten).
int32_t CKHkGolem::GetInfo(IKInfo* info, int32_t request) {
    if (request != kGetInfoValueAccessor) return 1;
    switch (info->m_ui32Id) {
    case 2:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return static_cast<uint32_t>(static_cast<CKHkGolem*>(o)->m_i32Health);
        }, 1);
    case 5:
    case 6:
        return AnswerInfo(info, [](IKSerializable* o, uint32_t) {
            return FloatBits(static_cast<CKHkGolem*>(o)->GetHealthPercent());
        }, 2);
    default:
        return 1;
    }
}

// 0x004bfa18 CKHkGolem_Restart: the current phase stopped (vt+0x58), the damage and the health reset, the boss fight
// off, the node hidden, the times now; with the sector loaded (+0x0c bit 2 clear) the node back to its matrix (+0x84),
// every phase restarted (vt+0x60) and reset (vt+0x5c); else only restarted.
void CKHkGolem::Restart() {
    PhaseManager()->StopCurrentPhase();
    m_i32TotalDamageTaken = 0;
    m_i32Health = m_i32MaxHealth;
    m_bBossFightRunning = 0;
    NodeOf(this)->m_sgProperties = (NodeOf(this)->m_sgProperties & 0xfffffffbu) | 4u;
    m_i32DamageMark = 0;
    m_fLastMarkGameTime = GolemClockTime();
    m_fStartGameTime = GolemClockTime();
    if ((m_bitArray & 4u) == 0) {
        static_cast<CSGMovable*>(m_pKGLObject)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pSavedMatrix));  // 0x000d0be8
        PhaseManager()->Vf60();
        PhaseManager()->ResetAllPhases();
        return;
    }
    PhaseManager()->Vf60();
}

// 0x004bf298 CKHkGolem_Stop: the actor base's, the damage 0, the current phase stopped; KStub_Nop_5cebf8(+0xbc).
void CKHkGolem::Stop() {
    CKHkActorBase::Stop();
    m_i32TotalDamageTaken = 0;
    PhaseManager()->StopCurrentPhase();
}

// 0x004c00c8 CKHkGolem_OnActivate: the actor base's, the full health, every phase reset (vt+0x5c), the node hidden,
// its modelling matrix kept (+0x84), the particle records' effects and the launchers' state forgotten, the marked
// effects' channels reset.
void CKHkGolem::VfA0() {
    CKHkActorBase::VfA0();
    m_i32Health = m_i32MaxHealth;
    PhaseManager()->ResetAllPhases();
    NodeOf(this)->m_sgProperties = (NodeOf(this)->m_sgProperties & 0xfffffffbu) | 4u;
    std::memcpy(m_pSavedMatrix, &static_cast<CSGMovable*>(m_pKGLObject)->m_pRwFrame->modelling, sizeof(CMatrix34));
    for (uint32_t i = 0; i < m_unk64.m_ui32NbUsedElt; ++i) {
        for (uint32_t j = 0; j < m_unk64.m_pBlock[i]->m_records.m_ui32NbUsedElt; ++j) {
            m_unk64.m_pBlock[i]->m_records.m_pBlock[j]->m_unk8 = nullptr;
        }
    }
    for (uint32_t i = 0; i < m_unk70.m_ui32NbUsedElt; ++i) {
        for (uint32_t j = 0; j < m_unk70.m_pBlock[i]->m_records.m_ui32NbUsedElt; ++j) {
            CKHkGolemRecord20* record = m_unk70.m_pBlock[i]->m_records.m_pBlock[j];
            record->m_unk18 = 0.0f;
            record->m_unk1C = 0;
            record->m_unk14 = 0.0f;
        }
    }
    static_cast<CKMarkedFX*>(m_pMarkedFx)->ResetChannels();  // 0x005cf1c0
}

// 0x004bfc88 CKHkGolem_OnDeactivate: the actor base's, the node back to its matrix, the running particle effects
// stopped (StopOwnedParticleEffect), every phase restarted (vt+0x60), the node shown, the marked effects stopped.
void CKHkGolem::VfA4() {
    CKHkActorBase::VfA4();
    static_cast<CSGMovable*>(m_pKGLObject)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pSavedMatrix));
    for (uint32_t i = 0; i < m_unk64.m_ui32NbUsedElt; ++i) {
        for (uint32_t j = 0; j < m_unk64.m_pBlock[i]->m_records.m_ui32NbUsedElt; ++j) {
            IKFx* effect = m_unk64.m_pBlock[i]->m_records.m_pBlock[j]->m_unk8;
            if (effect != nullptr) StopOwnedParticleEffect(effect, this);  // 0x001cdde8
        }
    }
    PhaseManager()->Vf60();
    NodeOf(this)->m_sgProperties &= 0xfffffffbu;
    static_cast<CKMarkedFX*>(m_pMarkedFx)->StopAllChannelNodes2();  // 0x005cfb70
}

// 0x004bfdf0 CKHkGolem_SetActiveWithBossGauge_maybe (vt+0xd4): off, a running boss fight stops its phase, hides the
// node and, with a maximum health, clears the meca group's boss byte. On, a fight not yet running starts its phase
// (vt+0x54), shows the node, resets the launchers, sets the boss gauge (when +0x90: the maximum as health and both
// maxima, then refreshed) and, with a maximum health, sets the boss byte.
void CKHkGolem::VfD4(int32_t on, int32_t /*mode*/) {
    if (on == 0) {
        if (m_bBossFightRunning == 0) return;
        PhaseManager()->StopCurrentPhase();
        m_bBossFightRunning = 0;
        NodeOf(this)->m_sgProperties = (NodeOf(this)->m_sgProperties & 0xfffffffbu) | 4u;
        if (m_i32MaxHealth > 0) SetBossFightByte(0);
        return;
    }
    if (m_bBossFightRunning != 0) return;
    PhaseManager()->StartCurrentPhase();
    m_bBossFightRunning = 1;
    NodeOf(this)->m_sgProperties &= 0xfffffffbu;
    for (uint32_t i = 0; i < m_unk70.m_ui32NbUsedElt; ++i) {
        for (uint32_t j = 0; j < m_unk70.m_pBlock[i]->m_records.m_ui32NbUsedElt; ++j) {
            CKHkGolemRecord20* record = m_unk70.m_pBlock[i]->m_records.m_pBlock[j];
            record->m_unk1C = 0;
            record->m_unk14 = 0.0f;
            record->m_unk18 = 0.0f;
        }
    }
    if (m_bShowBossGauge != 0) {
        CKS08GameManager* manager = GameManager();
        const float maximum = static_cast<float>(static_cast<double>(static_cast<int64_t>(m_i32MaxHealth)));
        manager->SetBossGaugeHealth(maximum);       // 0x004feb00
        manager->SetEnemyGaugeMaxHealth(maximum);   // 0x004fea60
        manager->SetEnemyGaugeMaxHealth2(maximum);  // 0x004fe9c0
        manager->RefreshBossGauge();                // 0x00501ea0
    }
    if (m_i32MaxHealth > 0) SetBossFightByte(1);
}

// 0x004befc0 CKHkGolem_UpdateProjectileLaunchers_maybe: each switched-on launcher record (+0x1c) without an interval
// (0.0) draws one: the base interval +0x0c, then interval + f x -0.5 + f with f = 2 x (Rand_Int's low 16 bits / 65535 x
// interval) (fmadds); its timer grows by the frame time; when the timer reaches the interval (fcmpu + cror: a NaN
// waits) both are cleared and, with a hot spot, the node's accessor launches from the hot spot's world position along
// the Y axis (0x00c50d40) at 25.0 (TOC +0x66b0) when it has a projectile type.
void CKHkGolem::UpdateProjectileLaunchers(IKTime* clock) {
    static const CVector3 kAxisY = {0.0f, 1.0f, 0.0f};  // 0x00c50d40
    for (uint32_t i = 0; i < m_unk70.m_ui32NbUsedElt; ++i) {
        for (uint32_t j = 0; j < m_unk70.m_pBlock[i]->m_records.m_ui32NbUsedElt; ++j) {
            CKHkGolemRecord20* record = m_unk70.m_pBlock[i]->m_records.m_pBlock[j];
            if (record->m_unk1C == 0) continue;
            if (record->m_unk14 == 0.0f) {
                record->m_unk14 = record->m_unkC;
                const float r = static_cast<float>(static_cast<double>(static_cast<uint32_t>(Rand_Int()) & 0xffffu));
                const float interval = record->m_unkC;
                float f = r / 65535.0f * interval;
                f = f + f;
                f = ppc::fmadds(f, -0.5f, f);
                record->m_unk14 = interval + f;
            }
            record->m_unk18 = record->m_unk18 + clock->m_afDeltaTime[IKTime::SCALABLE_GAME_TIME];
            if (!(record->m_unk18 >= record->m_unk14)) continue;
            record->m_unk18 = 0.0f;
            record->m_unk14 = 0.0f;
            if (record->m_pObject == nullptr) continue;
            CVector3 position;
            static_cast<const CSGHotSpot*>(record->m_pObject)->GetWorldPosition(&position);  // 0x000ce790
            CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(m_unk70.m_pBlock[i]->m_pObject);
            if (accessor->m_pProjectileType != nullptr) {
                accessor->Launch(&position, &kAxisY, 25.0f, this, nullptr);  // 0x001f2908
            }
        }
    }
}

// 0x004c2288 GolemAttack_TriggerStepExplosions_maybe: a mark value 1..vt+0x100 fires every step explosion record of
// value - 1: a pooled effect of the node's data (the inlined CKSrvFx lookup, reserved, owned by the golem, started)
// takes the hot spot's world matrix (+0x10 set) or position after the golem's node made its LTM current (vt+0x50),
// the golem as the damage owner, category 1, flags 0x200, the node's damage (+0x14; else the golem's +0x24), goes off
// and is released (vt+0x54).
void CKHkGolem::TriggerStepExplosions(uint32_t value) {
    if (value == 0 || GetMaxExplosionMark() < value) return;
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    for (uint32_t i = 0; i < m_unk58.m_ui32NbUsedElt; ++i) {
        for (uint32_t j = 0; j < m_unk58.m_pBlock[i]->m_records.m_ui32NbUsedElt; ++j) {
            CKHkGolemNode18* node = m_unk58.m_pBlock[i];
            if (node->m_records.m_pBlock[j]->m_ui32Value != value - 1) continue;
            IKFx* effect = fx->AcquireFx(static_cast<IKFxData*>(node->m_pObject), this);
            if (effect == nullptr) continue;
            CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
            NodeOf(this)->ForceWorldMatrixUpdate();  // vt+0x50
            alignas(16) CMatrix34 matrix;
            static_cast<const CSGHotSpot*>(m_unk58.m_pBlock[i]->m_records.m_pBlock[j]->m_pObject)->GetWorldMatrix(&matrix);
            if (m_unk58.m_pBlock[i]->m_unk10 == 0) {
                explosion->SetTranslation(&matrix.m_pos, this);  // 0x001b66e8
            } else {
                explosion->SetMatrix(reinterpret_cast<const RwMatrix*>(&matrix), this);  // 0x001b6368
            }
            explosion->SetDamageOwner(this, this);    // 0x001b6340
            explosion->SetDamageCategory(1, this);    // 0x001b6318
            explosion->SetDamageFlags(0x200, this);   // 0x001b62f0
            IKSerializable* damage = m_unk58.m_pBlock[i]->m_pObject14;
            if (damage == nullptr) damage = m_pDefaultStepDamage;
            explosion->SetDamage(damage, this);       // 0x001b62c8
            explosion->Trigger(this, 0);              // 0x001b82a8
            explosion->ReleaseReservation(this);      // vt+0x54
        }
    }
}

namespace {
// The particle records of mark value `value` (+0x64) without an effect take one: the node's data gets the hot spot
// (+0x14) and no owner node (+0x10), a pooled effect of it (null when none is free) becomes the record's.
void StartParticleRecords(CKHkGolem* golem, uint32_t value) {
    for (uint32_t i = 0; i < golem->m_unk64.m_ui32NbUsedElt; ++i) {
        for (uint32_t j = 0; j < golem->m_unk64.m_pBlock[i]->m_records.m_ui32NbUsedElt; ++j) {
            CKHkGolemRecordC* record = golem->m_unk64.m_pBlock[i]->m_records.m_pBlock[j];
            if (record->m_ui32Value != value - 1 || record->m_unk8 != nullptr) continue;
            CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(golem->m_unk64.m_pBlock[i]->m_pObject);
            data->m_pAttachOwner = nullptr;            // +0x10
            data->m_pAttachHotSpot = record->m_pObject;  // +0x14
            CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
            record->m_unk8 = fx->AcquireFx(data, golem);
        }
    }
}
// The launcher records of mark value `value` (+0x70) switched on / off, their state cleared.
void SwitchLauncherRecords(CKHkGolem* golem, uint32_t value, uint8_t on) {
    for (uint32_t i = 0; i < golem->m_unk70.m_ui32NbUsedElt; ++i) {
        for (uint32_t j = 0; j < golem->m_unk70.m_pBlock[i]->m_records.m_ui32NbUsedElt; ++j) {
            CKHkGolemRecord20* record = golem->m_unk70.m_pBlock[i]->m_records.m_pBlock[j];
            if (record->m_ui32Value != value - 1) continue;
            record->m_unk1C = on;
            record->m_unk8 = 0;
            record->m_unk18 = 0.0f;
            record->m_unk14 = 0.0f;
        }
    }
}
}  // namespace

// 0x004c3998 CKHkGolem_UpdateAnimMarkEvents_maybe: the animation's mark window (the current animation's time now
// brought into [0, duration) (bge / blt / cror: a NaN stays); at 0 with a different evaluated (blended-in) animation,
// that one's evaluated time up to its duration instead; an end before the start starts at 0; an empty window does
// nothing). Channel 0x1f: the value crossed fires the step explosions; 0x21 (up to vt+0x104): a value appearing or
// held starts its particle records, a value ending stops them (vt+0x58); 0x24: vt+0x10c / vt+0x110; 0x22 (up to
// vt+0x108): a value appearing switches its launchers on, a value ending off.
void CKHkGolem::UpdateAnimMarkEvents() {
    CAnimatedNode* node = static_cast<CAnimatedNode*>(m_pKGLObject);
    // 0x000c9720 CAnimatedNode_GetActiveAnim_maybe: the evaluated animation (DOTD: the pointer, not its word).
    RtAnimAnimation* active = node->ActiveController()->m_unk5c;
    RtAnimAnimation* current = node->GetCurrentAnim();                               // 0x000c96d8
    node->GetCurrentAnimTime();  // 0x000c95a8 (unused)
    node->GetAnimTimeNow();      // 0x000c95f0 (unused)
    RtAnimAnimation* animation = node->GetCurrentAnim();
    if (animation == nullptr) {
        animation = node->ActiveController()->m_unk5c;
        if (animation == nullptr) return;
    }
    float to = node->GetAnimTimeNow();
    float duration = animation->duration;  // +0x10
    while (to < 0.0f) to = to + duration;
    float end = duration + 0.0f;
    while (end <= to) to = to - duration;
    float from;
    if (to == 0.0f && active != nullptr && active != current) {
        from = node->GetCurrentAnimTime();
        duration = active->duration;
        while (from < 0.0f) from = from + duration;
        end = duration + 0.0f;
        while (end <= from) from = from - duration;
        animation = active;
        to = duration;
    } else {
        from = node->GetCurrentAnimTime();
        duration = animation->duration;
        while (from < 0.0f) from = from + duration;
        end = duration + 0.0f;
        while (end <= from) from = from - duration;
    }
    if (to < from) from = 0.0f;
    if (to == from) return;

    AnimMark* mark = Anim_GetMarkById(animation, 0x1f);  // 0x00078830
    if (mark != nullptr) {
        const uint32_t value = AnimMark_CrossedValueR3(mark, from, to);  // vt+0x1c
        if (value != 0) TriggerStepExplosions(value);
    }
    mark = Anim_GetMarkById(animation, 0x21);
    if (mark != nullptr) {
        const uint32_t before = AnimMark_ValueAtR3(mark, from);  // vt+0x10
        const uint32_t now = AnimMark_ValueAtR3(mark, to);
        if (before == 0) {
            if (now != 0 && now <= GetMaxParticleMark()) StartParticleRecords(this, now);
        } else if (now == 0) {
            if (before <= GetMaxParticleMark()) {
                for (uint32_t i = 0; i < m_unk64.m_ui32NbUsedElt; ++i) {
                    for (uint32_t j = 0; j < m_unk64.m_pBlock[i]->m_records.m_ui32NbUsedElt; ++j) {
                        CKHkGolemRecordC* record = m_unk64.m_pBlock[i]->m_records.m_pBlock[j];
                        if (record->m_ui32Value != before - 1 || record->m_unk8 == nullptr) continue;
                        record->m_unk8->StopAndRelease(this);  // vt+0x58
                        m_unk64.m_pBlock[i]->m_records.m_pBlock[j]->m_unk8 = nullptr;
                    }
                }
            }
        } else if (before == now && before <= GetMaxParticleMark()) {
            StartParticleRecords(this, before);
        }
    }
    mark = Anim_GetMarkById(animation, 0x24);
    if (mark != nullptr) {
        const uint32_t before = AnimMark_ValueAtR3(mark, from);
        const uint32_t now = AnimMark_ValueAtR3(mark, to);
        if (before == 0) {
            if (now != 0) OnMark24(now);  // vt+0x10c
        } else if (now == 0) {
            OnMark24Off(before);  // vt+0x110
        } else if (before == now) {
            OnMark24(before);
        }
    }
    mark = Anim_GetMarkById(animation, 0x22);
    if (mark == nullptr) return;
    const uint32_t before = AnimMark_ValueAtR3(mark, from);
    const uint32_t now = AnimMark_ValueAtR3(mark, to);
    if (before == 0) {
        if (now != 0 && now <= GetMaxLauncherMark()) SwitchLauncherRecords(this, now, 1);
    } else if (now == 0 && before <= GetMaxLauncherMark()) {
        SwitchLauncherRecords(this, before, 0);
    }
}

// 0x004c4838 CKHkGolem_Update (WorldObjectBase_Update_Nop first): while updated (+0x45) the damage at the frame's start
// kept, the phase manager updated (vt+0x50), the boss gauge set to the health (fight running and +0x90), the launchers,
// the attached objects (vt+0x64) and, outside a QTE phase (0xa10c), the marked effects and the animation marks.
void CKHkGolem::Update(IKTime* clock) {
    if (m_bEnabled == 0) return;
    m_i32FrameStartDamage = m_i32TotalDamageTaken;
    PhaseManager()->UpdateCurrentPhase(clock);
    if (m_bBossFightRunning != 0 && m_bShowBossGauge != 0) {
        CKS08GameManager* manager = GameManager();
        manager->SetBossGaugeHealth(static_cast<float>(static_cast<double>(static_cast<int64_t>(m_i32Health))));  // 0x004feb00
        manager->RefreshBossGauge();  // 0x00501ea0
    }
    UpdateProjectileLaunchers(clock);
    for (ObjectNode* node = m_pAttachedObjects; node != nullptr; node = node->m_pNext) {
        static_cast<CKGolemAttackCommon*>(node->m_pObject)->Vf64();  // vt+0x64 (KBaseC_vf64_3: empty)
    }
    IKSerializable* phase = PhaseManager()->GetCurrentPhase();  // 0x004bd330
    if (phase != nullptr && phase->IsKindOfClass(0xa10c) == 0) {
        static_cast<CKMarkedFX*>(m_pMarkedFx)->UpdateFromAnimMarks(clock);  // 0x005d0640
        UpdateAnimMarkEvents();
    }
}

// ---- C2.8: the golem's teardown ----

namespace {
// The inlined node vector release of CKHkGolem_Destroy: each node's records deleted, its record block freed (the
// vector cleared) and the node deleted.
template <class Node>
void DeleteNodes(TVector<Node*, 1>& nodes) {
    for (uint32_t i = 0; i < nodes.m_ui32NbUsedElt; ++i) {
        Node* node = nodes.m_pBlock[i];
        for (uint32_t j = 0; j < node->m_records.m_ui32NbUsedElt; ++j) {
            if (node->m_records.m_pBlock[j] != nullptr) ::operator delete(node->m_records.m_pBlock[j]);
        }
        if (node->m_records.m_pBlock != nullptr) Mem_FreeAligned16(node->m_records.m_pBlock);
        node->m_records.m_ui32NbUsedElt = 0;
        node->m_records.m_pBlock = nullptr;
        ::operator delete(node);
    }
}
template <class T>
void FreeVector(TVector<T, 1>& vector) {
    if (vector.m_pBlock != nullptr) Mem_FreeAligned16(vector.m_pBlock);
    vector.m_ui32NbUsedElt = 0;
    vector.m_pBlock = nullptr;
}
}  // namespace

// 0x004c0388 CKHkGolem_Destroy: CKHkActorBase_d82_maybe_Destroy (its vt+0xc0, KStub_Nop_9c0bc8 for the golems), the
// three node vectors' nodes and records deleted, the matrix +0x84 destroyed (RwMatrixDestroy_Thunk).
void CKHkGolem::Destroy() {
    DeleteNodes(m_unk58);
    DeleteNodes(m_unk64);
    DeleteNodes(m_unk70);
    RwMatrixDestroy(reinterpret_cast<RwMatrix*>(m_pSavedMatrix));  // 0x00758890
}

// 0x004c09b0 CKHkGolem_BaseDestructor (0x4c0850 CKHkGolem_Destructor calls it): the four vector blocks freed, the
// object list's nodes back to their pool, the contact history's entries back to theirs (DOTD: the entries are left to
// the contact history pool's owner, Math.cpp: no one reads them after the level).
CKHkGolem::~CKHkGolem() {
    FreeVector(m_unk70);
    FreeVector(m_unk64);
    FreeVector(m_unk58);
    FreeVector(m_unk34);
    for (ObjectNode* node = m_pAttachedObjects; node != nullptr;) {
        ObjectNode* next = node->m_pNext;
        delete node;
        node = next;
    }
    m_pAttachedObjects = nullptr;
    m_pContactHistory = nullptr;
}
