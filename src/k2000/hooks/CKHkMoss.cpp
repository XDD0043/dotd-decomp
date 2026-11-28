// Reconstructed original translation unit: 0x41be10-0x41e248 (GAME_TOC1, main_toc1), 29 functions, 27 live.
// Primary class: CKHkMoss  key 0x2282  category Hook  size 0x94  vtable 0xb25f00
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x41be10  CKHkMoss_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x41be60  CKHkMoss_Restart  (empty: the inherited slot's body)
//   [x] 0x41be68  CKHkMoss_vfC8  (empty: the inherited ApplyStatePreset's body)
//   [ ] 0x41be70  RegisterCKHkMossClass
//   [ ] 0x41bee8  _GLOBAL__I_41bee8
//   [x] 0x41bef8  CKHkMoss_SetDefaultState  (= the inherited slot: KStub_Nop_3f72a0)
//   [x] 0x41bf20  CKHkMoss_GetInfo
//   [x] 0x41bf70  CKHkMoss_Resume  (empty / no effect: inherited, KStub_Nop_3f6e60)
//   [x] 0x41bf98  CKHkMoss_Pause  (empty / no effect: inherited, KStub_Nop_3f6e58)
//   [x] 0x41bfc0  CKHkMoss_Stop  (empty / no effect: inherited, CKHkActorBase_d82_maybe_Stop 0x3f6e50)
//   [x] 0x41bfe8  CKHkMoss_Start  (= the inherited slot: CKHkActorBase_d82_maybe_ResetRuntime (empty))
//   [x] 0x41c010  CKHkMoss_PostLoad  (= the inherited slot: CKHkActorBase_d82_maybe_PostLoad, then 1)
//   [ ] 0x41c038  CKHkMoss_Save
//   [x] 0x41c060  CKHkMoss_RecursiveRegistration  (= the inherited slot: CKHkActorBase_d82_maybe_RecursiveRegistration, then 1)
//   [x] 0x41c088  CKHkMoss_Destroy  (= the inherited slot: CKHkActorBase_d82_maybe_Destroy (vt+0xc0, empty))
//   [ ] 0x41c0b0  CKHkMoss_Construct  [dead]
//   [x] 0x41c110  CKHkMoss_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x41c1b0  CKHkMoss_BaseDestructor  (CKHkMoss.cpp ~CKHkMoss)
//   [x] 0x41c220  CKHkMoss_MessageProc
//   [ ] 0x41c388  CKHkMoss_Construct_2  [dead]
//   [x] 0x41c3e8  CKHkMoss_DeletingDestructor  (the deleting form of ~CKHkMoss)
//   [x] 0x41c460  CKHkMoss_Destructor  (CKHkMoss.cpp ~CKHkMoss)
//   [x] 0x41c4d0  CKHkMoss_SetActive
//   [x] 0x41ce20  CKHkMoss_OnDeactivate
//   [x] 0x41ce58  CKHkMoss_OnActivate
//   [x] 0x41cec0  CKHkMoss_Update
//   [x] 0x41d810  CKHkMoss_Create  (DOTD_DECLARE_FACTORIES; the constructor in CKHkMoss.h)
//   [x] 0x41d880  CKHkMoss_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x41d960  CKHkMoss_Load
//
//   [ ] 0x9c2f88  CKHkMoss_IsKindOfClass  [inline]
//   [ ] 0x9c2fe0  CKHkMoss_GetClassType  [inline]
//   [ ] 0x9c2fe8  CKHkMoss_GetClassID  [inline]
//   [x] 0x9c2ff0  CKHkMoss_vfF0  [inline]  (CKHkMoss.h VfF0)
#include "k2000/hooks/CKHkMoss.h"

#include <cmath>
#include <cstring>

#include "Renderware/rpprtstd/RpPrtStd.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/ai/CKSrvPathFinding.h"
#include "k2000/core/IKInfo.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/UpdateParticleNodeSizeBoundingRadius.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/math/Math.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"
#include "k2000/scenegraph/CFogBoxNodeFx.h"
#include "k2000/scenegraph/CParticlesNodeFx.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/scenegraph/IKBoundingBox.h"
#include "k2000/services/CKSrvCollision.h"
#include "k2000/system/IKTime.h"

namespace {
// 0x00010690 Math_Sqrtf: the double square root rounded to float.
float MathSqrtf(float x) { return static_cast<float>(std::sqrt(static_cast<double>(x))); }
CKSoundDictionaryID* SoundsOf(IKSerializable* dictionary) { return static_cast<CKSoundDictionaryID*>(dictionary); }
CSGMovable* Movable(IKSerializable* node) { return static_cast<CSGMovable*>(node); }
CKGrpS08Hero* HeroGroup() { return static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]); }  // engine +0x8c -> +0x08

// 0x002ca0f8 CKGrpS08Hero_GetFocusedHero (local copy, as CKHkHeroActivator.cpp's)
CKHkS08Hero* FocusedHero(CKGrpS08Hero* group) {
    if (group->m_ui8FocusedDragon == 0xff) return nullptr;
    return static_cast<CKHkS08Hero*>(group->m_apHeros[static_cast<int32_t>(static_cast<int8_t>(group->m_ui8FocusedDragon))]);
}

// The block of the hero's hazard query 0xc32 (CKHkS08Hero_6.cpp's HazardHitQuery, CKHkCrumblyZone.cpp's layout).
struct MossHazardQuery {
    IKSerializable* m_hero;      // +0x00
    IKSerializable* m_volume;    // +0x04
    float m_afKnock[3];          // +0x08 (words)
    CVector3 m_point;            // +0x14
    int32_t m_kind;              // +0x20
    uint8_t m_damage;            // +0x24
};

// A particle node emitting (bit 10 = `on`, bit 19 cleared; on: no emission speed adjustment and the emitter's flags
// 0xa) or not (the emitter's flag 8 cleared).
void SetEmitting(IKSerializable* object, uint8_t on) {
    CParticlesNodeFx* node = static_cast<CParticlesNodeFx*>(object);
    node->m_sgProperties = ((node->m_sgProperties & 0xfffffbffu) | (static_cast<uint32_t>(on) << 10)) & 0xfff7ffffu;
    if (on == 0) {
        node->m_pRpPrtStdEmitter->flag &= 0xfffffff7u;
    } else {
        node->m_fEmissionSpeedAdjustment = 0.0f;
        node->m_pRpPrtStdEmitter->flag |= 0xau;
    }
}

// The node's modelling position (its identity flag cleared, the frame marked dirty).
void SetModellingPosition(IKSerializable* node, float x, float y, float z) {
    RwFrame* frame = Movable(node)->m_pRwFrame;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.pos.z = z;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}

// The original's sign flip (fcmpu / blt / fneg): -x for a negative x, else x (NaN and -0.0 kept).
float FlipNegative(float x) { return x < 0.0f ? -x : x; }
}  // namespace

// 0x0041c460 CKHkMoss_Destructor
CKHkMoss::~CKHkMoss() {
    if (m_vParticleNodes.m_pBlock != nullptr) Mem_FreeAligned16(m_vParticleNodes.m_pBlock);  // 0x00052fb8
    m_vParticleNodes.m_ui32NbUsedElt = 0;
    m_vParticleNodes.m_pBlock = nullptr;
}

// 0x0041d960 CKHkMoss_Load (level type 0 only). The particle list: capacity 1 and a one-element block, grown to
// count + 1 when the count is larger (count + 1 == 0 keeps one), the length, then one reference per element.
int32_t CKHkMoss::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // 0x003f6e98
    if (type != 0) return 1;
    IKFile_ReadRef(file, &m_pGround);
    IKFile_ReadRef(file, &m_pVolume);
    IKFile_ReadRef(file, &m_pPuffParticles);
    IKFile_ReadRef(file, &m_pFogBox);
    IKFile_ReadRef(file, &m_pAmbientParticles);
    IKFile_ReadRef(file, &m_pSounds);
    uint32_t count = 0;
    ReadU32LE(file, &count);
    m_vParticleNodes.m_ui32NbElt = 1;
    m_vParticleNodes.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(sizeof(IKSerializable*)));
    if (m_vParticleNodes.m_ui32NbElt < count) {
        const uint32_t capacity = count + 1;
        if (capacity == 0) {
            m_vParticleNodes.m_pBlock = static_cast<IKSerializable**>(
                Mem_ReallocAligned16(m_vParticleNodes.m_pBlock, sizeof(IKSerializable*)));
            m_vParticleNodes.m_ui32NbElt = 1;
        } else {
            m_vParticleNodes.m_pBlock = static_cast<IKSerializable**>(Mem_ReallocAligned16(
                m_vParticleNodes.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));
            m_vParticleNodes.m_ui32NbElt = capacity;
        }
    }
    m_vParticleNodes.m_ui32NbUsedElt = count;
    for (uint32_t i = 0; i < m_vParticleNodes.m_ui32NbUsedElt; ++i) IKFile_ReadRef(file, &m_vParticleNodes.m_pBlock[i]);
    ReadF32LE(file, &m_fPuffPeriod);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_vVolumePosition), 3);
    ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_vVolumeExtent), 3);
    ReadU8(file, &m_ui8Damage);
    for (float& value : m_afKnock) ReadF32LE(file, &value);
    ReadF32LE(file, &m_fNearDistance);
    ReadF32LE(file, &m_fFarDistance);
    ReadF32LE(file, &m_fNearSizeX);
    ReadF32LE(file, &m_fFarSizeX);
    ReadF32LE(file, &m_fNearSizeY);
    ReadF32LE(file, &m_fFarSizeY);
    ReadF32LE(file, &m_fNavHalfRight);
    ReadF32LE(file, &m_fNavHalfAt);
    return 1;
}

// 0x0041bf20 CKHkMoss_GetInfo
int32_t CKHkMoss::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    if (base == 2) return 2;
    return base == 0 ? 0 : 1;
}

// 0x0041c220 CKHkMoss_MessageProc
int32_t CKHkMoss::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0xc32) {
        MossHazardQuery* query = static_cast<MossHazardQuery*>(data);
        query->m_afKnock[0] = m_afKnock[0];
        query->m_afKnock[1] = m_afKnock[1];
        query->m_afKnock[2] = m_afKnock[2];
        const RwFrame* frame = Movable(m_pKGLObject)->m_pRwFrame;
        query->m_point = {frame->modelling.pos.x, frame->modelling.pos.y, frame->modelling.pos.z};  // frame +0x40
        query->m_damage = static_cast<CKHkS08Hero*>(query->m_hero)->IsPlayerControlled() == 0 ? 0 : m_ui8Damage;  // 0x00362af0
        own = 0;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// 0x0041ce58 CKHkMoss_OnActivate
void CKHkMoss::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    SetActive(VfF0());      // vt+0xf0
    m_fPuffTimer = 0.0f;    // stw 0
}

// 0x0041ce20 CKHkMoss_OnDeactivate
void CKHkMoss::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    SetActive(0);
}

// 0x0041c4d0 CKHkMoss_SetActive. The fog box's box keyed by this moss (the save points' and air currents' scheme, see
// CKHkS08AirCurrent.cpp's PlaceRecord / RemoveRecord): an existing one gets scale 1, else a free one becomes the moss's
// (identity first, scale 1 (TOC +0x4cd8), one more active box); either way its matrix takes the node's LTM (all 0x40
// bytes) and its emitter particles are randomised (rand draws for a new one).
void CKHkMoss::SetActive(uint8_t active) {
    const uint32_t p = active;
    m_bitArray = (m_bitArray & 0xfffffff7u) | (p << 3);
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pKGLObject);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | (((p ^ 1u) << 2) & 0x3fcu);
    for (uint32_t i = 0; m_vParticleNodes.m_ui32NbUsedElt > i; ++i) SetEmitting(m_vParticleNodes.m_pBlock[i], active);
    SetEmitting(m_pAmbientParticles, active);
    CFogBoxNodeFx* fog = static_cast<CFogBoxNodeFx*>(m_pFogBox);
    const uintptr_t id = reinterpret_cast<uintptr_t>(this);
    bool stopAmbient = active == 0;
    if (fog != nullptr) {
        if (active != 0) {
            CMatrix34 ltm;
            std::memcpy(&ltm, &Movable(m_pKGLObject)->m_pRwFrame->ltm, sizeof(CMatrix34));  // frame +0x50
            const uint32_t count = fog->m_unk40;
            int32_t index = static_cast<int32_t>(count) - 1;
            for (; index >= 0; --index) {
                if (fog->m_aBoxes[index].m_unk04 == id) break;
            }
            int32_t isNew = 0;
            bool place = true;
            if (index >= 0) {
                fog->m_aBoxes[index].m_unk08 = 1.0f;
            } else if (fog->m_ui32NbBoxes == count) {
                place = false;
            } else {
                CMatrix34* box = fog->m_aBoxes[count].m_pMatrix;
                box->m_right.z = 0.0f;
                box->m_ui32Flags = 0x20003u;
                box->m_pos.x = 0.0f;
                box->m_at.z = 1.0f;
                box->m_up.y = 1.0f;
                box->m_right.x = 1.0f;
                box->m_up.x = 0.0f;
                box->m_right.y = 0.0f;
                box->m_at.y = 0.0f;
                box->m_at.x = 0.0f;
                box->m_up.z = 0.0f;
                box->m_pos.z = 0.0f;
                box->m_pos.y = 0.0f;
                fog->m_aBoxes[fog->m_unk40].m_unk04 = id;
                fog->m_aBoxes[fog->m_unk40].m_unk08 = 1.0f;
                fog->m_unk40 = fog->m_unk40 + 1;
                isNew = 1;
                index = static_cast<int32_t>(count);
            }
            if (place && index != -1) {
                std::memcpy(fog->m_aBoxes[index].m_pMatrix, &ltm, sizeof(CMatrix34));
                fog->RandomizeEmitterParticles(isNew, static_cast<uint32_t>(index));  // 0x000da968
            }
        } else {
            const uint32_t count = fog->m_unk40;
            int32_t index = static_cast<int32_t>(count) - 1;
            for (; index >= 0; --index) {
                if (fog->m_aBoxes[index].m_unk04 == id) break;
            }
            if (index >= 0) {
                const uint32_t last = count - 1;
                fog->m_unk40 = last;
                if (static_cast<uint32_t>(index) != last) {
                    std::memcpy(fog->m_aBoxes[index].m_pMatrix, fog->m_aBoxes[last].m_pMatrix, sizeof(CMatrix34));
                    fog->m_aBoxes[index].m_unk04 = fog->m_aBoxes[last].m_unk04;
                }
                fog->m_aBoxes[fog->m_unk40].m_unk04 = 0;
            }
        }
    }
    if (stopAmbient) Sound_Stop(SoundsOf(m_pSounds)->GetSound(0), 0);  // 0x00112bc0, 0x001111b0
    CKSrvCollision* collision = static_cast<CKSrvCollision*>(g_pEngine->m_srvCollision);
    if (m_pVolume != nullptr) {
        IKBoundingBox* volume = static_cast<IKBoundingBox*>(m_pVolume);
        if (active == 0) {
            collision->DisableVolume(volume);  // 0x001920e8
            volume = static_cast<IKBoundingBox*>(m_pVolume);
            if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
            static_cast<CSGBranch*>(g_pEngine->m_dynamicSceneRoot)->AddChild(static_cast<CSGLeaf*>(m_pVolume));  // vt+0x70
        } else {
            collision->EnableVolume(volume);  // 0x00192090
            volume = static_cast<IKBoundingBox*>(m_pVolume);
            if (volume->m_pParent != nullptr) volume->m_pParent->RemoveChild(volume);  // vt+0x78
            volume = static_cast<IKBoundingBox*>(m_pVolume);
            const float x = m_vVolumeExtent.x;
            const float y = m_vVolumeExtent.y;
            const float z = m_vVolumeExtent.z;
            volume->m_Extent.x = x;
            volume->m_Extent.z = z;
            volume->m_Extent.y = y;
            volume->m_fRadius = MathSqrtf(ppc::fmadds(z, z, ppc::fmadds(x, x, y * y)));  // 0x00010690
            static_cast<CSGBranch*>(m_pKGLObject)->AddChild(static_cast<CSGLeaf*>(m_pVolume));  // vt+0x70
            Movable(m_pVolume)->SetIdentity();  // 0x000d08f0
            SetModellingPosition(m_pVolume, m_vVolumePosition.x, m_vVolumePosition.y, m_vVolumePosition.z);
        }
    }
    if (m_fNavHalfRight == 0.0f) return;  // TOC +0x4ce0
    const float a = m_fNavHalfRight;
    const float b = m_fNavHalfAt;
    const RwMatrix& ltm = Movable(m_pKGLObject)->m_pRwFrame->ltm;
    const float atX = ltm.at.x;
    const float atZ = ltm.at.z;
    const float rightX = ltm.right.x;
    const float rightZ = ltm.right.z;
    CPFPoint point;
    point.m_position = {ltm.pos.x, ltm.pos.y, ltm.pos.z};
    point.m_i16GraphNodeIndex = 0xffff;
    CVector3 low = {ltm.pos.x, ltm.pos.y, ltm.pos.z};
    CVector3 high = low;
    low.x = low.x - ppc::fmadds(FlipNegative(atX), b, std::fabs(rightX) * a);
    low.z = low.z - ppc::fmadds(std::fabs(atZ), b, std::fabs(rightZ) * a);
    high.x = high.x + ppc::fmadds(std::fabs(atX), b, FlipNegative(rightX) * a);
    high.z = high.z + ppc::fmadds(FlipNegative(atZ), b, FlipNegative(rightZ) * a);
    CKSrvPathFinding* pathFinding = static_cast<CKSrvPathFinding*>(g_pEngine->m_srvPathFinding);
    pathFinding->FindSectorForPoint(&point);                                 // 0x001e5ca0
    pathFinding->SetBoxBlocked(point.m_i16GraphNodeIndex, &low, &high, active);          // 0x001e5f60
}

// The puff Update inlines for each touching body and each hero on the ground (0.0 TOC +0x4ce0).
void CKHkMoss::Puff(const float* position) {
    const RwMatrix& ltm = Movable(m_pKGLObject)->m_pRwFrame->ltm;  // frame +0x80
    SetModellingPosition(m_pPuffParticles, position[0] - ltm.pos.x, position[1] - ltm.pos.y, position[2] - ltm.pos.z);
    CParticlesNodeFx* puff = static_cast<CParticlesNodeFx*>(m_pPuffParticles);
    if (!(m_fPuffPeriod > 0.0f)) {  // ble: bits 9 and 10 set
        puff->m_sgProperties = ((puff->m_sgProperties | 0x200u) | 0x400u) & 0xfff7ffffu;
        puff->m_fEmissionSpeedAdjustment = 0.0f;
        puff->m_pRpPrtStdEmitter->flag |= 0xau;
    } else {
        puff->m_sgProperties = (puff->m_sgProperties | 0x400u) & 0xfff7ffffu;
        puff->m_fEmissionSpeedAdjustment = 0.0f;
        puff->m_pRpPrtStdEmitter->flag |= 0xau;
        if (m_fPuffTimer <= 0.0f) m_fPuffTimer = m_fPuffPeriod;  // cror lt|eq
    }
    CKSoundDictionaryID* sounds = SoundsOf(m_pSounds);
    if (sounds->GetSound(1)->IsPlaying() != 0) return;  // 0x00111568
    if (sounds->GetSound(2)->IsPlaying() != 0) return;
    const uint32_t index = ((static_cast<uint32_t>(Rand_Int()) >> 15) & 1u) + 1u;  // 0x00011500: rldicl 0x31, 0x3f
    sounds->GetSound(index)->Play(0.0f);
}

// 0x0041cec0 CKHkMoss_Update. The ambient size: t = (distance - near) / (far - near) to the focused hero (fsubs,
// fdivs), the near size at t <= 0, the far one at t >= 1, else near + t * (far - near) (fmadds); the standard size and the
// PTank's constant size (property 6, changed flag 0x4000) take it, then the node's bounding radius. The ambient sound
// plays while a controlled hero is within 40 (1600.0 squared, TOC +0x4ce8) of the node.
void CKHkMoss::Update(IKTime* frameClock) {
    CKHkActorBase::Update(frameClock);  // 0x003f6e68 (empty)
    if ((m_bitArray & 8u) == 0) {
        if (VfF0() != 0) SetActive(1);  // vt+0xf0
        return;
    }
    if (VfF0() == 0) {
        SetActive(0);
        return;
    }
    if (m_fPuffTimer > 0.0f) {
        m_fPuffTimer = m_fPuffTimer - frameClock->m_afDeltaTime[0];
        if (m_fPuffTimer <= 0.0f) {  // cror lt|eq: the puff particles stop
            CParticlesNodeFx* puff = static_cast<CParticlesNodeFx*>(m_pPuffParticles);
            puff->m_sgProperties &= 0xfff7fbffu;
            puff->m_pRpPrtStdEmitter->flag &= 0xfffffff7u;
        }
    }
    // Every collision of the volume (the list re-read each pass): the particles at its world contact point (vt+0x20).
    if (m_pVolume != nullptr) {
        for (ICollision* collision = static_cast<ICollision*>(static_cast<IKBoundingBox*>(m_pVolume)->m_CollisionResList);
             collision != nullptr; collision = collision->m_pNext) {
            Puff(&collision->GetWorldContactPoint()->x);
        }
    }
    CKGrpS08Hero* group = HeroGroup();
    if (m_pGround != nullptr && group != nullptr) {
        for (uint32_t i = group->m_ui8ControlledHeroCount; i != 0; --i) {  // 0x002ca288
            CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apControlledHeroes[i - 1]);  // 0x002ca0e0
            if (m_pGround != hero->GetGroundObject()) continue;  // 0x00363c40
            Puff(hero->GetPositionPtr());  // 0x00361968
            m_fPuffTimer = m_fPuffPeriod;
        }
    }
    const float* focused = FocusedHero(HeroGroup())->GetPositionPtr();  // 0x002ca0f8, 0x00361968
    const RwMatrix& ltm = Movable(m_pKGLObject)->m_pRwFrame->ltm;
    const float dy = focused[1] - ltm.pos.y;
    const float dx = focused[0] - ltm.pos.x;
    const float dz = focused[2] - ltm.pos.z;
    const float distance = MathSqrtf(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)));
    const float t = (distance - m_fNearDistance) / (m_fFarDistance - m_fNearDistance);
    float sizeX;
    float sizeY;
    if (t <= 0.0f) {  // cror lt|eq
        sizeX = m_fNearSizeX;
        sizeY = m_fNearSizeY;
    } else if (!(t >= 1.0f)) {  // cror gt|eq, bne: NaN interpolates
        sizeX = ppc::fmadds(t, m_fFarSizeX - m_fNearSizeX, m_fNearSizeX);
        sizeY = ppc::fmadds(t, m_fFarSizeY - m_fNearSizeY, m_fNearSizeY);
    } else {
        sizeX = m_fFarSizeX;
        sizeY = m_fFarSizeY;
    }
    CParticlesNodeFx* ambient = static_cast<CParticlesNodeFx*>(m_pAmbientParticles);
    auto standard = [ambient]() {
        RpPrtStdEmitter* emitter = ambient->m_pRpPrtStdEmitter;
        return reinterpret_cast<RpPrtStdEmitterStandard*>(reinterpret_cast<uint8_t*>(emitter) +
                                                          emitter->emtClass->propTab->propOffset[1]);
    };
    standard()->prtSize.x = sizeX;
    standard()->prtSize.y = sizeY;
    const int32_t offset = RpPrtStdPropTabGetPropOffset(ambient->m_pRpPrtStdEmitter->emtClass->propTab,
                                                        rpPRTSTDPROPERTYCODEEMITTERPTANK);  // TocBridge 0x98e120
    if (offset != -1) {
        const RpPrtStdEmitterPTank* ptank = reinterpret_cast<const RpPrtStdEmitterPTank*>(
            reinterpret_cast<const uint8_t*>(ambient->m_pRpPrtStdEmitter) + offset);
        if (ptank->pTank != nullptr) {
            RpPTankData* data = ptank->pTank->ptank;  // atomic + the PTank plugin offset (0x00cf079c)
            std::memcpy(&data->renderC0[0], &sizeX, sizeof sizeX);
            std::memcpy(&data->renderC0[1], &sizeY, sizeof sizeY);
            data->flags40 |= 0x4000u;
        }
    }
    UpdateParticleNodeSizeBoundingRadius(ambient);  // 0x000e5c80
    CKSound* sound = SoundsOf(m_pSounds)->GetSound(0);
    group = HeroGroup();
    bool near = false;
    if (group != nullptr) {
        for (uint32_t i = group->m_ui8ControlledHeroCount; i != 0 && !near; --i) {
            const float* position = static_cast<CKHkS08Hero*>(group->m_apControlledHeroes[i - 1])->GetPositionPtr();
            const float hy = position[1] - ltm.pos.y;
            const float hx = position[0] - ltm.pos.x;
            const float hz = position[2] - ltm.pos.z;
            near = ppc::fmadds(hz, hz, ppc::fmadds(hx, hx, hy * hy)) < 1600.0f;  // blt
        }
    }
    if (!near) {
        Sound_Stop(sound, 0);  // 0x001111b0
        return;
    }
    if (sound->CountInstances() != 0) return;
    sound->Play(0.0f);
}
