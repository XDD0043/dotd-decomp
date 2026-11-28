// Reconstructed original translation unit: 0x419a18-0x41be10 (GAME_TOC1, main_toc1), 32 functions, 27 live.
// Primary class: CKHkLedge  key 0x1582  category Hook  size 0xa0  vtable 0xb25e08
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x419a18  CKHkLedge_Delete  (DOTD_DECLARE_FACTORIES)
//   [x] 0x419a68  CKHkLedge_vfC8  (CKHkLedge.h ApplyStatePreset)
//   [ ] 0x419a90  RegisterCKHkLedgeClass
//   [ ] 0x419b08  _GLOBAL__I_419b08
//   [x] 0x419b18  CKHkLedge_GetInfo
//   [x] 0x419b68  CKHkLedge_IsHeroOnLedge_maybe
//   [ ] 0x419cb0  CKHkLedge_StopVibration_maybe  [dead]
//   [ ] 0x419d28  CKHkLedge_PlayVibration_maybe  [dead]
//   [ ] 0x419da0  CKHkLedge_ResetRuntimeState_maybe  [dead]
//   [x] 0x419e28  CKHkLedge_SetDefaultState  (CKHkLedge.h)
//   [x] 0x419e80  CKHkLedge_Resume  (empty / no effect: inherited, KStub_Nop_3f6e60)
//   [x] 0x419ea8  CKHkLedge_Pause  (empty / no effect: inherited, KStub_Nop_3f6e58)
//   [x] 0x419ed0  CKHkLedge_Stop  (empty / no effect: inherited, CKHkActorBase_d82_maybe_Stop 0x3f6e50)
//   [x] 0x419ef8  CKHkLedge_Start  (= the inherited slot: CKHkActorBase_d82_maybe_ResetRuntime (empty))
//   [ ] 0x419f20  CKHkLedge_Save
//   [x] 0x419f48  CKHkLedge_RecursiveRegistration  (= the inherited slot: CKHkActorBase_d82_maybe_RecursiveRegistration, then 1)
//   [x] 0x419f70  CKHkLedge_Destroy  (= the inherited slot: CKHkActorBase_d82_maybe_Destroy (vt+0xc0, empty))
//   [ ] 0x419f98  CKHkLedge_Construct  [dead]
//   [ ] 0x419fd0  CKHkLedge_Construct_2  [dead]
//   [x] 0x41a008  CKHkLedge_DeleteArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x41a0b0  CKHkLedge_AttachSounds
//   [x] 0x41a118  CKHkLedge_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x41a148  CKHkLedge_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x41a190  CKHkLedge_Destructor  (the C++ destructor (CKHkActorBase_d82_maybe_BaseDestructor))
//   [x] 0x41a1c0  CKHkLedge_MessageProc
//   [x] 0x41a2c0  CKHkLedge_CreateArray  (DOTD_DECLARE_FACTORIES)
//   [x] 0x41a378  CKHkLedge_Create  (DOTD_DECLARE_FACTORIES)
//   [x] 0x41a3d0  CKHkLedge_OnDeactivate
//   [x] 0x41a4d0  CKHkLedge_Restart
//   [x] 0x41a5c0  CKHkLedge_OnActivate
//   [x] 0x41a710  CKHkLedge_Update
//   [x] 0x41b640  CKHkLedge_Load
//
//   [ ] 0x9c2f20  CKHkLedge_IsKindOfClass  [inline]
//   [ ] 0x9c2f78  CKHkLedge_GetClassType  [inline]
//   [ ] 0x9c2f80  CKHkLedge_GetClassID  [inline]
#include "k2000/hooks/CKHkLedge.h"

#include "Renderware/rwcore/RwCamera.h"
#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/components/CKSekensLauncherCpnt.h"
#include "k2000/core/IKInfo.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/fx/IKFx.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKParticlesEffectFxData.h"
#include "k2000/logic/CKProjectileAccessor.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/physics/CDynamicGround.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/managers/CKInput.h"
#include "k2000/managers/CKVibrationData.h"
#include "k2000/math/CBBox.h"
#include "k2000/math/Math.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/FloatApproach.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CSGLeaf.h"
#include "k2000/scenegraph/CSGMovable.h"
#include "k2000/services/CKSrvFx.h"
#include "k2000/services/ICollisionMesh.h"
#include "k2000/system/IKTime.h"
#include "platform/fps.h"

namespace {
// 0x00c50d64 (TOC +0x4c84): the null vector. 0x00c50d7c (TOC +0x4c8c): the shared down vector (0, -1, 0) (zero in the
// EBOOT's BSS; StaticInitAndDestruction_11578 fills it).
const CVector3 kVectorZero = {0.0f, 0.0f, 0.0f};
const CVector3 kDown = {0.0f, -1.0f, 0.0f};

CKSoundDictionaryID* SoundsOf(IKSerializable* dictionary) { return static_cast<CKSoundDictionaryID*>(dictionary); }
CSGMovable* Movable(IKSerializable* node) { return static_cast<CSGMovable*>(node); }

// The node's modelling position set and the frame marked dirty (its identity flag 0x20000 cleared).
void SetModellingPosition(IKSerializable* node, float x, float y, float z) {
    RwFrame* frame = Movable(node)->m_pRwFrame;
    frame->modelling.pos.z = z;
    frame->modelling.pos.x = x;
    frame->modelling.pos.y = y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);  // 0x00010698
}
}  // namespace

// 0x0041b640 CKHkLedge_Load: no type test (every word read for every serialization type).
int32_t CKHkLedge::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);  // 0x003f6e98
    ReadF32LE(file, &m_unk54);
    ReadF32LE(file, &m_unk58);
    ReadF32LE(file, &m_unk5C);
    ReadF32LE(file, &m_unk60);
    ReadF32LE(file, &m_unk64);
    for (float& value : m_afProjectileOffset) ReadF32LE(file, &value);
    ReadU8(file, &m_ui8HeroMask);
    IKFile_ReadRef(file, &m_pNode);
    IKFile_ReadRef(file, &m_pGround);
    IKFile_ReadRef(file, &m_pSounds);
    IKFile_ReadRef(file, &m_pFallFxData);
    IKFile_ReadRef(file, &m_pShakeFxData);
    for (IKSerializable*& launcher : m_apLauncher) IKFile_ReadRef(file, &launcher);
    IKFile_ReadRef(file, &m_pVibration);
    IKFile_ReadRef(file, &m_pSekens);
    m_tsFall.Load(file, type);
    return 1;
}

// 0x00419b18 CKHkLedge_GetInfo
int32_t CKHkLedge::GetInfo(IKInfo* info, int32_t request) {
    const int32_t base = CKHkActorBase::GetInfo(info, request);  // KStub_Return1 0x3f7140
    if (base == 2) return 2;
    return base == 0 ? 0 : 1;
}

// 0x0041a1c0 CKHkLedge_MessageProc (0.0 TOC +0x4c78)
int32_t CKHkLedge::MessageProc(uint16_t message, void* data) {
    const int32_t base = CKHkActorBase::MessageProc(message, data);  // 0x003f7148
    int32_t own = 1;
    if (message == 0x996) {
        if (m_fShakeTimer == 0.0f && (static_cast<CSGLeaf*>(m_pNode)->m_sgProperties & 4u) == 0) m_fShakeTimer = m_unk60;
        own = 0;
    }
    if (base == 3 || own == 3) return 3;
    if (base == 2 || own == 2) return 2;
    return base == 0 ? 0 : own;
}

// 0x00419b68 CKHkLedge_IsHeroOnLedge_maybe
uint8_t CKHkLedge::IsHeroOnLedge() {
    CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);  // +0x08
    uint8_t found = 0;
    for (int32_t i = static_cast<int32_t>(group->GetHeroCount()) - 1; i != -1 && found == 0; --i) {  // 0x002ca038
        if ((ppc::sraw(m_ui8HeroMask, static_cast<uint32_t>(i) & 0xffu) & 1) == 0) continue;
        CKHkS08Hero* hero = static_cast<CKHkS08Hero*>(group->m_apHeros[i & 0xff]);  // 0x002ca080
        if (m_pGround == hero->GetLedgeGroundContact()) {  // 0x00363770
            found = 1;
            continue;
        }
        if ((m_bitArray & 0x10u) == 0) continue;
        hero = static_cast<CKHkS08Hero*>(group->m_apHeros[i & 0xff]);
        if (m_pGround == hero->GetGroundObject()) found = 1;  // 0x00363c40
    }
    return found;
}

void CKHkLedge::ResetShake() {
    m_fShakeTimer = 0.0f;
    m_ui8Alpha = 0xff;
    m_fRespawnTimer = 0.0f;
    m_afShake[3] = m_unk54;
    m_afShake[4] = 0.0f;
    m_afShake[1] = m_unk58;
    m_afShake[2] = 0.0f;
    m_afShake[0] = 0.0f;
}

void CKHkLedge::StopShakeFx() {
    if (m_pShakeFx == nullptr) return;
    m_pShakeFx->StopAndRelease(this);  // vt+0x58
    m_pShakeFx = nullptr;
}

// The vibration's use-time byte 1 and time 0.5 (TOC +0x4c70) before it is stopped.
void CKHkLedge::StopVibration() {
    CKVibrationData* vibration = static_cast<CKVibrationData*>(m_pVibration);
    if (vibration->m_pOwner == nullptr) return;
    vibration->m_bUseTime = 1;
    vibration->m_fTime = 0.5f;
    g_pEngine->m_input->StopVibration(this, static_cast<int8_t>(vibration->m_ui8OwnerIndex));  // 0x00107538
    vibration->m_pOwner = nullptr;
}

// 0x0041a4d0 CKHkLedge_Restart (the reset's zeros are integer stores)
void CKHkLedge::Restart() {
    if ((m_bitArray & 4u) != 0) return;
    const uint32_t down = m_fRespawnTimer < 0.0f ? 1u : 0u;  // fcmpu / blt
    ResetShake();
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pNode);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | (down << 2);
    static_cast<ICollisionMesh*>(m_pGround)->SetActive(static_cast<uint16_t>(down ^ 1u));  // 0x001a6b70
    if (m_unk51 != 0) m_fRespawnTimer = -1.0f;  // TOC +0x4c48
}

// 0x0041a5c0 CKHkLedge_OnActivate
void CKHkLedge::VfA0() {
    CKHkActorBase::VfA0();  // 0x003f7338
    const uint32_t down = m_fRespawnTimer < 0.0f ? 1u : 0u;  // fcmpu / blt against 0.0 (TOC +0x4c78)
    ResetShake();
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pNode);
    node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | (down << 2);
    static_cast<ICollisionMesh*>(m_pGround)->SetActive(static_cast<uint16_t>(down ^ 1u));  // 0x001a6b70
    if (m_unk51 != 0) m_fRespawnTimer = -1.0f;  // TOC +0x4c48
    SetModellingPosition(m_pNode, kVectorZero.x, kVectorZero.y, kVectorZero.z);
    CSGLeaf* hook = static_cast<CSGLeaf*>(m_pKGLObject);
    hook->m_sgProperties &= 0xfffffffbu;
    m_pShakeFx = nullptr;
    static_cast<CKVibrationData*>(m_pVibration)->m_pOwner = nullptr;
}

// 0x0041a3d0 CKHkLedge_OnDeactivate
void CKHkLedge::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    Sound_Stop(SoundsOf(m_pSounds)->GetSound(1), 0);  // 0x00112bc0, 0x001111b0
    static_cast<ICollisionMesh*>(m_pGround)->SetActive(0);  // 0x001a6b70
    StopShakeFx();
    StopVibration();
}

// 0x0041a0b0 CKHkLedge_AttachSounds (the hook node, not `leaf`)
void CKHkLedge::KGLObjectAttached(IKSerializable* /*leaf*/) {
    SoundsOf(m_pSounds)->GetSound2(0)->SetAttachObject(m_pKGLObject);  // 0x00112bd8, 0x00111350
    SoundsOf(m_pSounds)->GetSound2(1)->SetAttachObject(m_pKGLObject);
}

// 0x0041a710 CKHkLedge_Update. The floats against 0.0 (TOC +0x4c78); the alpha step = the low byte of fctiwz(dt * 100)
// (TOC +0x4c88); the fall's projectiles at the node's LTM position + offset * LTM right row (fmadds), down (0, -1, 0)
// at speed 0.0 with the LTM as the matrix.
void CKHkLedge::Update(IKTime* frameClock) {
    CKHkActorBase::Update(frameClock);  // 0x003f6e68 (empty)
    const float dt = frameClock->m_afDeltaTime[0];  // +0x1c
    CSGLeaf* node = static_cast<CSGLeaf*>(m_pNode);
    CKSoundDictionaryID* sounds = SoundsOf(m_pSounds);
    if ((node->m_sgProperties & 4u) != 0) {
        // Down: the respawn after +0x64 seconds (never with +0x64 == 0 or a negative timer).
        if (m_unk64 != 0.0f && m_fRespawnTimer >= 0.0f) {  // cror gt|eq
            m_fRespawnTimer = dt + m_fRespawnTimer;
            if (m_unk64 < m_fRespawnTimer) {  // bge skips it: NaN keeps it down
                ResetShake();
                node->m_sgProperties &= 0xfffffffbu;
                static_cast<ICollisionMesh*>(m_pGround)->SetActive(1);  // 0x001a6b70
                uint8_t alpha = static_cast<uint8_t>(ppc::fctiwz(dt * 100.0f));
                // --fps N (not in the original): the steps of this frame's 60 Hz frames (1 per frame at 60 fps).
                if (dotd::fps::Unlocked()) alpha = static_cast<uint8_t>(dotd::fps::TruncSteps(100.0f, dt));
                m_ui8Alpha = alpha;  // (a byte: the original's > 0xff test never holds)
                SceneNode_SetAlphaRecursive(m_pNode, alpha, 0);  // 0x0098f570 -> 0x00582c60
            }
        }
        Sound_Stop(sounds->GetSound(1), 0);  // 0x00112bc0, 0x001111b0
        StopShakeFx();
        StopVibration();
        return;
    }
    if (m_ui8Alpha != 0xff) {
        uint32_t step = static_cast<uint32_t>(ppc::fctiwz(dt * 100.0f));
        // --fps N (not in the original): the whole steps of this frame's 60 Hz frames, so the fade keeps its 60 fps
        // speed (trunc(dt x 100) alone is 0 above 100 fps: the respawned ledge would stay invisible).
        if (dotd::fps::Unlocked()) step = static_cast<uint32_t>(dotd::fps::TruncSteps(100.0f, dt));
        const uint32_t sum = static_cast<uint32_t>(m_ui8Alpha) + (step & 0xffu);
        if (static_cast<int32_t>(sum) > 0xff) {
            m_ui8Alpha = 0xff;
            SceneNode_SetAlphaRecursive(m_pNode, 0xff, 0);
        } else {
            m_ui8Alpha = static_cast<uint8_t>(sum);
            SceneNode_SetAlphaRecursive(m_pNode, static_cast<uint8_t>(sum), 0);
        }
    }
    m_fRespawnTimer = 0.0f;
    bool shaking;
    if ((m_bitArray & 8u) == 0 && m_fShakeTimer != 0.0f) {
        shaking = m_fShakeTimer > 0.0f;
    } else if (IsHeroOnLedge() != 0) {
        if (m_fShakeTimer == 0.0f) {
            m_fShakeTimer = m_unk60;
            m_afShake[0] = -m_unk5C;
        }
        shaking = m_fShakeTimer > 0.0f;
    } else if ((m_bitArray & 8u) == 0) {
        shaking = m_fShakeTimer > 0.0f;
    } else {
        m_fShakeTimer = 0.0f;
        shaking = false;
    }
    if (!shaking) {  // ble: NaN takes it
        Sound_Stop(sounds->GetSound(1), 0);
        StopShakeFx();
        StopVibration();
    } else {
        if (m_pShakeFx == nullptr) {
            CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_pShakeFxData);
            data->m_ui8Flags = static_cast<uint8_t>((data->m_ui8Flags & 0xefu) | 0x10u);
            data->m_pAttachHotSpot = nullptr;
            data->m_pAttachOwner = static_cast<CSGLeaf*>(m_pNode);
            m_pShakeFx = static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->AcquireFx(data, this);  // inlined
        }
        const uint8_t onLedge = IsHeroOnLedge();
        CKVibrationData* vibration = static_cast<CKVibrationData*>(m_pVibration);
        if (onLedge == 0) {
            if (vibration->m_pOwner != nullptr) {
                vibration->m_bUseTime = 1;
                vibration->m_fTime = 0.5f;  // TOC +0x4c70
                g_pEngine->m_input->StopVibration(this, static_cast<int8_t>(vibration->m_ui8OwnerIndex));  // 0x00107538
                vibration->m_pOwner = nullptr;
            }
        } else if (vibration->m_pOwner == nullptr) {
            vibration->m_bUseTime = 1;
            vibration->m_fTime = 0.5f;
            vibration->m_pOwner = this;
            g_pEngine->m_input->PlayVibration(vibration);  // 0x00107d38
        }
        m_fShakeTimer = m_fShakeTimer - dt;
        FloatApproachAccel_Step(dt, m_afShake);  // 0x00243800
        const float current = m_afShake[4];
        const float amplitude = m_unk5C;
        if (current >= amplitude) {  // cror gt|eq
            m_afShake[4] = amplitude;
            m_afShake[0] = -m_unk5C;
        } else if (current <= -amplitude) {  // cror lt|eq
            m_afShake[4] = -amplitude;
            m_afShake[0] = m_unk5C;
        }
        SetModellingPosition(m_pNode, kVectorZero.x, m_afShake[4], kVectorZero.z);
        CKSound* loop = sounds->GetSound(1);
        if (loop->CountInstances() == 0) {
            loop->SetLoop(1);  // 0x00110fd0
            loop->Play(0.0f);  // 0x00111230
        }
        if (m_fShakeTimer <= 0.0f) {  // cror lt|eq: the fall
            ResetShake();
            node->m_sgProperties = (node->m_sgProperties & 0xfffffffbu) | 4u;
            static_cast<ICollisionMesh*>(m_pGround)->SetActive(0);  // 0x001a6b70
            StopShakeFx();
            StopVibration();
            CKParticlesEffectFxData* data = static_cast<CKParticlesEffectFxData*>(m_pFallFxData);
            data->m_ui8Flags = static_cast<uint8_t>((data->m_ui8Flags & 0xefu) | 0x10u);
            data->m_pAttachHotSpot = nullptr;
            data->m_pAttachOwner = static_cast<CSGLeaf*>(m_pKGLObject);
            data->m_ui8Flags = static_cast<uint8_t>((data->m_ui8Flags & 0xf7u) | 0x8u);
            static_cast<CKSrvFx*>(g_pEngine->m_srvFx)->StartEffect(data, this);  // inlined
            sounds->GetSound(0)->Play(0.0f);
            for (uint32_t i = 0; i < 3; ++i) {
                CKProjectileAccessor* launcher = static_cast<CKProjectileAccessor*>(m_apLauncher[i]);
                if (launcher->m_pProjectileType == nullptr) continue;
                const float offset = m_afProjectileOffset[i];
                const RwMatrix& ltm = Movable(m_pNode)->m_pRwFrame->ltm;
                CVector3 pos;
                pos.z = ppc::fmadds(offset, ltm.right.z, ltm.pos.z);
                pos.x = ppc::fmadds(offset, ltm.right.x, ltm.pos.x);
                pos.y = ppc::fmadds(offset, ltm.right.y, ltm.pos.y);
                launcher->Launch(&pos, &kDown, 0.0f, this, &Movable(m_pNode)->m_pRwFrame->ltm);  // 0x001f2908
            }
            static_cast<CKSekensLauncherCpnt*>(m_pSekens)->PlaySekens(0);  // 0x001f7730
            QueueTriggerSignals(&m_tsFall);                                 // 0x00236338
        }
    }
    // A ledge hung under another node than its sector's root: its dynamic ground refreshed once (flag 0x20, the
    // inlined CDynamicGround update: the parent's LTM recomputed, the inverse and the world box).
    CKSector* sector = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[m_iSectorIndex]);
    if (static_cast<const void*>(static_cast<CSGLeaf*>(m_pKGLObject)->m_pParent) == static_cast<const void*>(sector->m_pSectorRoot)) return;
    CDynamicGround* ground = static_cast<CDynamicGround*>(m_pGround);
    if ((ground->m_ba16EngineFlags & 0x20u) != 0) return;
    ground->m_ba16EngineFlags = static_cast<uint16_t>((ground->m_ba16EngineFlags & 0xffdfu) | 0x20u);
    if ((ground->m_ba16EngineFlags & 1u) == 0) return;
    Movable(ground->m_pParent)->ForceWorldMatrixUpdate();  // vt+0x50
    const CMatrix34* world = reinterpret_cast<const CMatrix34*>(&Movable(ground->m_pParent)->m_pRwFrame->ltm);
    Mat4_Invert(ground->m_pInvertedWorldMatrix, world);  // 0x0023f878
    BBox_TransformByMatrix(reinterpret_cast<CBBox*>(ground->m_AABB), reinterpret_cast<const CBBox*>(ground->m_OBB),
                           reinterpret_cast<const CMatrix34*>(&Movable(ground->m_pParent)->m_pRwFrame->ltm));  // 0x0023bce0
}
