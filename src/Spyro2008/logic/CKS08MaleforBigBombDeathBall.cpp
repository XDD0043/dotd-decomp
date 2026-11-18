// CKS08MaleforBigBombDeathBall.cpp - reconstructed original translation unit 0x4e7ac0-0x4e9120 (GAME_TOC1, main_toc1), 27 functions, 26 live.
// Primary class: CKS08MaleforBigBombDeathBall  key 0xac0c  category Logic  size 0xd4  vtable 0xb2a790
// Other owners: CKS08MaleforColdBall (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4e7ac0  CKS08MaleforBigBombDeathBall_Delete
//   [ ] 0x4e7b10  RegisterCKS08MaleforBigBombDeathBallClass
//   [ ] 0x4e7b88  _GLOBAL__I_4e7b88
//   [x] 0x4e7b98  CKS08MaleforBigBombDeathBall_Explode
//   [x] 0x4e7ef0  CKS08MaleforBigBombDeathBall_vf5C  (inherited: CKGolemAttackCommon::Vf5C)
//   [x] 0x4e7f18  CKS08MaleforBigBombDeathBall_AttachVolumesToHotSpots_maybe  (inherited: CKGolemAttackCommon::AttachVolumesToHotSpots)
//   [x] 0x4e7f40  CKS08MaleforBigBombDeathBall_StopAttack_maybe  (inherited: CKGolemAttackCommon::StopAttack)
//   [x] 0x4e7f68  CKS08MaleforBigBombDeathBall_StartAttack_maybe
//   [x] 0x4e7fa0  CKS08MaleforBigBombDeathBall_PostLoad  (inherited: CKGolemAttackCommon::PostLoad)
//   [ ] 0x4e7fc8  CKS08MaleforBigBombDeathBall_Save
//   [x] 0x4e7ff0  CKS08MaleforBigBombDeathBall_RecursiveRegistration  (inherited: CKGolemAttackCommon's RecursiveRegistration slot)
//   [x] 0x4e8018  CKS08MaleforBigBombDeathBall_Destroy
//   [x] 0x4e80a0  CKS08MaleforBigBombDeathBall_Destructor  (~CKS08MaleforBigBombDeathBall)
//   [x] 0x4e8110  CKS08MaleforBigBombDeathBall_Construct_2  (the constructor CKS08MaleforBigBombDeathBall() (a second copy))
//   [x] 0x4e8170  CKS08MaleforBigBombDeathBall_Construct
//   [x] 0x4e81d0  CKS08MaleforBigBombDeathBall_DeleteArray
//   [x] 0x4e8270  CKS08MaleforBigBombDeathBall_DestructBody  (~CKS08MaleforBigBombDeathBall)
//   [x] 0x4e82e0  CKS08MaleforBigBombDeathBall_DeletingDestructor  (~CKS08MaleforBigBombDeathBall)
//   [x] 0x4e8358  CKS08MaleforBigBombDeathBall_ComputeSpreadDirections_maybe
//   [x] 0x4e85f8  CKS08MaleforBigBombDeathBall_RandomizeBallParams_maybe
//   [x] 0x4e8720  CKS08MaleforBigBombDeathBall_LaunchBalls_maybe
//   [x] 0x4e8868  CKS08MaleforBigBombDeathBall_Update_maybe
//   [x] 0x4e88f0  CKS08MaleforBigBombDeathBall_Create
//   [x] 0x4e8960  CKS08MaleforBigBombDeathBall_CreateArray
//   [x] 0x4e8a40  CKS08MaleforBigBombDeathBall_Load
//   [x] 0x4e8fb8  CKS08MaleforColdBall_Delete  (CKS08MaleforColdBall::Delete, DOTD_DECLARE_FACTORIES)
//   [ ] 0x4e9008  FUN_004e9008  [dead]
//
//   [ ] 0x9c66a8  CKS08MaleforBigBombDeathBall_IsKindOfClass  [inline]
//   [ ] 0x9c66f8  CKS08MaleforBigBombDeathBall_GetClassType  [inline]
//   [ ] 0x9c6700  CKS08MaleforBigBombDeathBall_GetClassID  [inline]
#include "Spyro2008/logic/CKS08MaleforBigBombDeathBall.h"

#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"

// ==== port-all P13 ==================================================================================================
#include <cmath>

#include "crt/ppc_ops.h"
#include "k2000/hooks/CKHkGolem.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/logic/fx/CKExplosionNodeFx.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/services/CKSrvFx.h"
#include "Renderware/rwcore/RwCamera.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/math/Math.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/system/IKTime.h"

// 0x004e8170 CKS08MaleforBigBombDeathBall_Construct: CKGolemAttackCommon's constructor, then the array header.
CKS08MaleforBigBombDeathBall::CKS08MaleforBigBombDeathBall() {
    m_apEntries = nullptr;
    m_entryCapacity = 1;
    m_entryCount = 0;
}

// 0x004e8a40 CKS08MaleforBigBombDeathBall_Load: CKGolemAttackCommon's data, then, for K_LEVEL_PLATEFORMS only,
// five words, a reference, a counted array of two-float entries, and words and references.
int32_t CKS08MaleforBigBombDeathBall::Load(IKFile* file, int32_t type) {
    CKGolemAttackCommon::Load(file, type);
    if (type != 0) return 1;

    ReadS32LE(file, &m_unkac);
    ReadF32LE(file, &m_unkb0);
    ReadF32LE(file, &m_unkb4);
    ReadF32LE(file, &m_unkb8);
    ReadF32LE(file, &m_unkbc);
    IKFile_ReadRef(file, &m_unk98);

    uint32_t count = 0;
    ReadU32LE(file, &count);
    // BUG(original): a fresh one-entry block every Load; the old block is not freed and the count is kept.
    m_entryCapacity = 1;
    m_apEntries = static_cast<Entry**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(Entry*))));
    for (uint32_t i = 0; i < count; ++i) {
        Entry* entry = new Entry;
        ReadF32LE(file, &entry->m_unk00);
        ReadF32LE(file, &entry->m_unk04);
        if (m_entryCapacity == m_entryCount) {
            uint32_t capacity = m_entryCount + 1;
            if (capacity == 0) capacity = 1;
            m_apEntries = static_cast<Entry**>(
                Mem_ReallocAligned16(m_apEntries, capacity * static_cast<uint32_t>(sizeof(Entry*))));
            m_entryCapacity = capacity;
        }
        m_apEntries[m_entryCount] = entry;
        m_entryCount = m_entryCount + 1;
    }

    ReadF32LE(file, &m_unka8);
    IKFile_ReadRef(file, &m_unk9c);
    ReadF32LE(file, &m_unka0);
    IKFile_ReadRef(file, &m_unkc0);
    IKFile_ReadRef(file, &m_unkc4);
    return 1;
}

// 0x004e80a0 CKS08MaleforBigBombDeathBall_Destructor
CKS08MaleforBigBombDeathBall::~CKS08MaleforBigBombDeathBall() {
    if (m_apEntries != nullptr) Mem_FreeAligned16(m_apEntries);
    m_entryCount = 0;
    m_apEntries = nullptr;
}

// 0x004e8018 CKS08MaleforBigBombDeathBall_Destroy
void CKS08MaleforBigBombDeathBall::Destroy() {
    CKGolemAttackCommon::Destroy();
    for (uint32_t i = 0; i < m_entryCount; ++i) {
        if (m_apEntries[i] != nullptr) delete m_apEntries[i];  // OperatorDelete
    }
}

// 0x004e7f68 CKS08MaleforBigBombDeathBall_StartAttack_maybe
void CKS08MaleforBigBombDeathBall::StartAttack() {
    CKGolemAttackCommon::StartAttack();
    m_unka4 = 0;
}

// 0x004e8868 CKS08MaleforBigBombDeathBall_Update_maybe: cror (the time at least +0xa0).
void CKS08MaleforBigBombDeathBall::Update(IKTime* clock) {
    CKGolemAttackCommon::Update(clock);
    const float time = static_cast<CAnimatedNode*>(Golem()->m_pKGLObject)->GetAnimTimeNow();  // 0x000c95f0
    if (m_unka4 != 0 || !(m_unka0 <= time)) return;
    LaunchBalls();
    Explode();
}

// 0x004e8358 CKS08MaleforBigBombDeathBall_ComputeSpreadDirections_maybe
uint8_t CKS08MaleforBigBombDeathBall::ComputeSpreadDirections() {
    if (m_unkac == 0) return 0;
    if (Golem()->GetReference(6) == nullptr) return 0;  // vt+0xf8
    const RwFrame* frame = static_cast<CSGLeaf*>(Golem()->m_pKGLObject)->m_pRwFrame;
    float x = frame->ltm.at.x;
    float z = frame->ltm.at.z;
    float y = 0.0f;  // TOC1 +0x6e40
    const float length = std::sqrt(ppc::fmadds(z, z, ppc::fmadds(x, x, 0.0f)));  // Math_Sqrtf 0x10690
    if (length != 0.0f) {
        const float inverse = 1.0f / length;  // TOC1 +0x6e34
        z = z * inverse;
        x = x * inverse;
        y = inverse * 0.0f;
    }
    if (m_unkac == 1) {
        m_apEntries[0]->m_vDir = CVector3{x, y, z};
        return 1;
    }
    float spread = m_unka8;
    const float step = (spread + spread) / static_cast<float>(static_cast<uint32_t>(m_unkac - 1));  // fcfid of the u32
    if (m_unkac == 0) return 1;
    // BUG(original): +0xac directions are written into the entries without a test of the entry count.
    for (uint32_t i = 0;;) {
        CVector3 out;
        CVector3 v = {x, y, z};
        CVector3 axis = {0.0f, 1.0f, 0.0f};  // 0x00c50d40, the shared Y axis
        const float angle = ppc::fmsubs(step, static_cast<float>(i), spread) * 0x1.1df468p-6f;  // TOC1 +0x6e3c: pi / 180
        Vec3_RotateTowardByAngle(&out, &v, &axis, angle);  // 0x005841a8 (bridge 0x98f300)
        float ox = out.x;
        float oy = out.y;
        float oz = out.z;
        const float olength = std::sqrt(ppc::fmadds(oz, oz, ppc::fmadds(ox, ox, oy * oy)));
        if (olength != 0.0f) {
            const float inverse = 1.0f / olength;
            oz = oz * inverse;
            ox = ox * inverse;
            oy = oy * inverse;
        }
        m_apEntries[i]->m_vDir = CVector3{ox, oy, oz};
        ++i;
        if (static_cast<uint32_t>(m_unkac) <= i) break;
        spread = m_unka8;
    }
    return 1;
}

// 0x004e85f8 CKS08MaleforBigBombDeathBall_RandomizeBallParams_maybe: u16 / 65535.0 (TOC1 +0x6e44), fmadds.
uint8_t CKS08MaleforBigBombDeathBall::RandomizeBallParams() {
    if (ComputeSpreadDirections() == 0) return 0;
    for (uint32_t i = 0; i < m_entryCount; ++i) {
        Entry* entry = m_apEntries[i];
        float draw = static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu) / 65535.0f;  // 0x00011500
        entry->m_unk00 = ppc::fmadds(draw, m_unkbc - m_unkb8, m_unkb8);
        entry = m_apEntries[i];
        draw = static_cast<float>(static_cast<uint32_t>(Rand_Int()) & 0xffffu) / 65535.0f;
        entry->m_unk04 = ppc::fmadds(draw, m_unkb4 - m_unkb0, m_unkb0);
    }
    return 1;
}

// 0x004e8720 CKS08MaleforBigBombDeathBall_LaunchBalls_maybe
uint8_t CKS08MaleforBigBombDeathBall::LaunchBalls() {
    if (RandomizeBallParams() == 0) return 0;
    // BUG(original): the hot spot is not null-tested here (ComputeSpreadDirections did).
    CVector3 position;
    static_cast<const CSGHotSpot*>(Golem()->GetReference(6))->GetWorldPosition(&position);  // 0x000ce790
    for (uint32_t i = 0; i < m_entryCount; ++i) {
        CKProjectileAccessor* accessor = static_cast<CKProjectileAccessor*>(m_unk98);
        if (accessor->m_pProjectileType == nullptr) continue;
        Entry* entry = m_apEntries[i];
        accessor->LaunchEx(&position, &entry->m_vDir, entry->m_unk00, m_unkc4, Golem(), nullptr);  // 0x001f2988
    }
    m_unka4 = 1;
    return 1;
}

// 0x004e7b98 CKS08MaleforBigBombDeathBall_Explode: a pooled effect of the explosion data (+0x9c; the inlined CKSrvFx lookup: reserved, owned
// by the attack, started; none free: nothing) at the golem's hot spot 6 (its world matrix), else at the golem's node
// position, the attack as the damage owner, category 1, flags 0x200, the damage (+0xc0), set off and released.
void CKS08MaleforBigBombDeathBall::Explode() {
    CKSrvFx* fx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    IKFx* effect = fx->AcquireFx(static_cast<IKFxData*>(m_unk9c), this);
    if (effect == nullptr) return;
    CKExplosionNodeFx* explosion = static_cast<CKExplosionNodeFx*>(effect);
    const CSGHotSpot* hotSpot = static_cast<const CSGHotSpot*>(Golem()->GetReference(6));  // vt+0xf8
    if (hotSpot == nullptr) {
        const RwFrame* frame = static_cast<CSGLeaf*>(Golem()->m_pKGLObject)->m_pRwFrame;
        explosion->SetTranslation(reinterpret_cast<const CVector3*>(&frame->ltm.pos), this);  // 0x001b66e8
    } else {
        alignas(16) CMatrix34 matrix;
        hotSpot->GetWorldMatrix(&matrix);                                              // 0x000ce970
        explosion->SetMatrix(reinterpret_cast<const RwMatrix*>(&matrix), this);       // 0x001b6368
    }
    explosion->SetDamageOwner(this, this);    // 0x001b6340
    explosion->SetDamageCategory(1, this);    // 0x001b6318
    explosion->SetDamageFlags(0x200, this);   // 0x001b62f0
    explosion->SetDamage(m_unkc0, this);  // 0x001b62c8
    explosion->Trigger(this, nullptr);        // 0x001b82a8
    explosion->ReleaseReservation(this);      // vt+0x54
}
