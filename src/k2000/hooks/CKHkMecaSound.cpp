// CKHkMecaSound.cpp - reconstructed original translation unit 0x4dfc68-0x4e0920 (GAME_TOC1, main_toc1), 31 functions, 31 live.
// Primary class: CKHkMecaSound  key 0x3482  category Hook  size 0x3c  vtable 0xb2a360
// Other owners: CKHkS08ElectricGaugeBase (2), CKHkS08ElectricGauge (2), KBase3542 (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x4dfc68  CKHkMecaSound_vfCC
//   [ ] 0x4dfc70  RegisterCKHkMecaSoundClass
//   [ ] 0x4dfce8  _GLOBAL__I_4dfce8
//   [x] 0x4dfcf8  CKHkMecaSound_MessageProc  (in the header)
//   [x] 0x4dfd50  CKHkMecaSound_GetInfo  (in the header)
//   [x] 0x4dfda0  CKHkMecaSound_OnDeactivate
//   [x] 0x4dfe40  CKHkMecaSound_OnActivate  (= the inherited slot: CKHkActorBase_d82_maybe_OnActivate)
//   [x] 0x4dfe68  CKHkMecaSound_Resume  (empty / no effect: inherited)
//   [x] 0x4dfe90  CKHkMecaSound_Pause  (empty / no effect: inherited)
//   [x] 0x4dfeb8  CKHkMecaSound_SetDefaultState
//   [x] 0x4dfef0  CKHkMecaSound_Stop  (empty / no effect: inherited, CKHkActorBase_d82_maybe_Stop 0x3f6e50)
//   [x] 0x4dff18  CKHkMecaSound_Start
//   [x] 0x4dff40  CKHkMecaSound_PostLoad  (= the inherited slot)
//   [ ] 0x4dff68  CKHkMecaSound_Save
//   [x] 0x4dff90  CKHkMecaSound_RecursiveRegistration  (= the inherited slot: CKHkActorBase_d82_maybe_LevelReset 0x3f6ee8, then 1)
//   [x] 0x4dffb8  CKHkMecaSound_Destroy  (inherited: CKHkActorBase_d82_maybe_ClearReferences 0x3f6e08 calls vt+0xc0, KStub_Nop_9c0bc8)
//   [x] 0x4dffe0  CKHkMecaSound_DeletingDestructor  (the deleting form of the implicit destructor)
//   [x] 0x4e0028  CKHkMecaSound_Destructor  (the C++ destructor (CKHkActorBase_d82_maybe_BaseDestructor 0x3f73f0))
//   [x] 0x4e0058  CKHkMecaSound_BaseDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x4e0088  CKHkMecaSound_Construct_2  (the C++ constructor: the actor base's, then the vtable)
//   [x] 0x4e00c0  CKHkMecaSound_Construct
//   [x] 0x4e00f8  CKHkMecaSound_DeleteArray
//   [x] 0x4e01a0  CKHkMecaSound_CreateArray
//   [x] 0x4e0258  CKHkMecaSound_Create
//   [x] 0x4e02b0  CKHkMecaSound_Update
//   [x] 0x4e0600  CKHkMecaSound_Load
//   [x] 0x4e0858  CKHkS08ElectricGaugeBase_3542_maybe_Update
//   [x] 0x4e0880  CKHkS08ElectricGauge_BaseResume_maybe  (empty / no effect: inherited)
//   [x] 0x4e08a8  CKHkS08ElectricGauge_BasePause_maybe  (empty / no effect: inherited)
//   [x] 0x4e08d0  CKHkS08ElectricGaugeBase_3542_maybe_OnLevelExit  (CKHkS08ElectricGaugeBase: CKHkActorBase's Stop, empty)
//   [x] 0x4e08f8  KBase3542_ResetRuntime
//
//   [ ] 0x9c62c0  CKHkMecaSound_IsKindOfClass  [inline]
//   [ ] 0x9c6318  CKHkMecaSound_GetClassType  [inline]
//   [ ] 0x9c6320  CKHkMecaSound_GetClassID  [inline]
#include "k2000/hooks/CKHkMecaSound.h"

#include "Spyro2008/groups/CKGrpS08Hero.h"
#include "Spyro2008/hooks/CKHkS08Hero.h"
#include "crt/ppc_ops.h"
#include "k2000/cameras/CKSrvCamera.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/math/IKPath.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Engine.h"

#include "k2000/io/IKFile.h"
#include "Spyro2008/ui/CKHkS08ElectricGaugeBase.h"

// 0x004e0600 CKHkMecaSound_Load
int32_t CKHkMecaSound::Load(IKFile* file, int32_t type) {
    CKHkActorBase::Load(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_unk20);
        IKFile_ReadRef(file, &m_unk24);
        ReadF32LE(file, &m_unk28);
        ReadU8(file, &m_unk2C);
        ReadF32LE(file, &m_unk30);
        ReadF32LE(file, &m_unk34);
        return 1;
    }
    return 1;
}

// 0x004dfeb8 CKHkMecaSound_SetDefaultState
void CKHkMecaSound::SetDefaultState(int32_t flag) {
    CKHkActorBase::SetDefaultState(flag);
    m_unk38 = 1;
}

// 0x004dff18 CKHkMecaSound_Start: CKHkActorBase_d82_maybe_ResetRuntime only. 0x004e08f8 KBase3542_ResetRuntime
// is the same call for the unregistered base KBase3542 (no class of its own here).
void CKHkMecaSound::Start() { CKHkActorBase::Start(); }

// 0x004e0858 CKHkS08ElectricGaugeBase_3542_maybe_Update: WorldObjectBase_Update_Nop (0x3f6e68) only.
void CKHkS08ElectricGaugeBase::Update(IKTime* /*clock*/) {}

namespace {
void StopMecaSounds(CKSoundDictionaryID* sounds) {
    if (sounds->GetSound(0) != nullptr) Sound_Stop(sounds->GetSound(0), 0);  // 0x00112bc0, 0x001111b0
    if (sounds->GetSound(1) != nullptr) Sound_Stop(sounds->GetSound(1), 0);
}
}  // namespace

// 0x004e02b0 CKHkMecaSound_Update
void CKHkMecaSound::Update(IKTime* /*frameClock*/) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_unk20);
    if (m_unk38 == 0) {
        StopMecaSounds(sounds);
        return;
    }
    CVector3 listener;
    if (m_unk2C == 0) {
        listener = static_cast<CKSrvCamera*>(g_pEngine->m_srvCamera)->m_v3RealPos;  // +0x598
    } else {
        CKGrpS08Hero* group = static_cast<CKGrpS08Hero*>(g_pEngine->m_gameManager->m_unk04[1]);
        if (group == nullptr) {
            StopMecaSounds(sounds);
            return;
        }
        CKHkS08Hero* hero = group->m_unk66 == 0xff
                                ? nullptr
                                : static_cast<CKHkS08Hero*>(group->m_apHeros[static_cast<int8_t>(group->m_unk66)]);  // 0x002ca0f8
        const float* p = hero->GetPositionPtr();  // 0x00361968
        listener = {p[0], p[1], p[2]};
    }
    IKPath* path = static_cast<IKPath*>(m_unk24);
    CVector3 point;
    CVector3 direction;
    path->GetPointAtDistance(path->GetClosestDistanceAlong(&listener, 1), &point, &direction);  // vt+0x58, vt+0x54
    const float dy = point.y - listener.y;
    const float dx = point.x - listener.x;
    const float dz = point.z - listener.z;
    // The side: the path's direction x the up axis 0x00c50d40 (TOC +0x6cc8), fused.
    const CVector3 up = {0.0f, 1.0f, 0.0f};
    const float sideZ = ppc::fmsubs(up.y, direction.x, direction.y * up.x);
    const float sideY = ppc::fmsubs(direction.z, up.x, up.z * direction.x);
    const float sideX = ppc::fmsubs(direction.y, up.z, direction.z * up.y);
    if (!(ppc::fmadds(dz, dz, ppc::fmadds(dx, dx, dy * dy)) < m_unk28 * m_unk28)) {
        StopMecaSounds(sounds);
        return;
    }
    const float offsets[2] = {m_unk30, m_unk34};
    for (uint32_t k = 0; k < 2; ++k) {
        CKSound* sound = sounds->GetSound(k);
        if (sound == nullptr) continue;
        const float w = offsets[k];
        const CVector3 position = {ppc::fmadds(sideX, w, point.x), ppc::fmadds(sideY, w, point.y),
                                   ppc::fmadds(sideZ, w, point.z)};
        sound->SetPosition(&position);  // 0x00110fa0
        if (sound->CountInstances() != 0) continue;
        sound->Play(0.0f);  // 0x00111230; TOC +0x6ccc
    }
}

// 0x004dfda0 CKHkMecaSound_OnDeactivate
void CKHkMecaSound::VfA4() {
    CKHkActorBase::VfA4();  // 0x003f7370
    StopMecaSounds(static_cast<CKSoundDictionaryID*>(m_unk20));
}
