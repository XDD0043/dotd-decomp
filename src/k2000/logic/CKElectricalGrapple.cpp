// CKElectricalGrapple.cpp - reconstructed original translation unit 0x395018-0x396748 (GAME_TOC1, main_toc1), 27 functions, 27 live.
// Primary class: CKElectricalGrapple  key 0xa00c  category Logic  size 0x158  vtable 0xb237e8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x395018  CKElectricalGrapple_Delete
//   [x] 0x395068  CKElectricalGrapple_GetAbilityId
//   [x] 0x395070  CKElectricalGrapple_ResetRuntime
//   [x] 0x3950b8  CKElectricalGrapple_GetSoundForEvent_maybe
//   [x] 0x395230  CKElectricalGrapple_End
//   [x] 0x3952a8  CKElectricalGrapple_Start
//   [x] 0x3952d8  CKElectricalGrapple_PostLoad
//   [x] 0x395300  CKElectricalGrapple_RecursiveRegistration  (inherited: CKGrabElement_RecursiveRegistration)
//   [x] 0x395328  CKElectricalGrapple_Destroy  (inherited: CKGrabElement_Destroy)
//   [x] 0x395350  CKElectricalGrapple_DeletingDestructor  (C++ destructor chain: vtable stores only)
//   [x] 0x395398  CKElectricalGrapple_Destructor  (C++ destructor chain: vtable stores only)
//   [x] 0x3953c8  CKElectricalGrapple_DestructBody  (C++ destructor chain: vtable stores only)
//   [x] 0x3953f8  CKElectricalGrapple_Construct
//   [x] 0x395430  CKElectricalGrapple_Construct_2  (the same as 0x3953f8 CKElectricalGrapple_Construct)
//   [x] 0x395468  CKElectricalGrapple_DeleteArray
//   [ ] 0x395508  RegisterCKElectricalGrappleClass
//   [ ] 0x395590  _GLOBAL__D_395590
//   [ ] 0x3955a0  _GLOBAL__I_3955a0
//   [x] 0x3955b0  CKElectricalGrapple_Slot80_maybe
//   [x] 0x395630  CKElectricalGrapple_GrabTarget_maybe
//   [x] 0x395678  CKElectricalGrapple_Slot84_maybe
//   [x] 0x395790  CKElectricalGrapple_UpdateGrab_maybe
//   [x] 0x395b88  CKElectricalGrapple_Create
//   [x] 0x395be0  CKElectricalGrapple_CreateArray
//   [x] 0x395c90  CKElectricalGrapple_Load
//   [ ] 0x395ed0  CKElectricalGrapple_Save
//   [x] 0x396120  CKElectricalGrapple_SetFxActive
//
//   [ ] 0x9bfc08  CKElectricalGrapple_IsKindOfClass  [inline]
//   [ ] 0x9bfc58  CKElectricalGrapple_GetClassType  [inline]
//   [ ] 0x9bfc60  CKElectricalGrapple_GetClassID  [inline]
//   [x] 0x9bfc68  CKElectricalGrapple_vf94  [inline]
//   [x] 0x9bfc70  CKElectricalGrapple_StartEmitterFx  [inline]
#include "k2000/logic/CKElectricalGrapple.h"

#include "Spyro2008/misc/CKS08AbilityHostBase.h"
#include "crt/ppc_ops.h"
#include "k2000/dictionaries/CKSoundDictionaryID.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/IKFxData.h"
#include "k2000/logic/render/CKLightningBoltFxData.h"
#include "k2000/logic/render/CKLightningBoltNodeFx.h"
#include "k2000/logic/sound/CKSound.h"
#include "k2000/misc/Engine.h"
#include "k2000/services/CKSrvFx.h"

// 0x00395c90 CKElectricalGrapple_Load: CKGrabElement's data, then (level data only) four references.
int32_t CKElectricalGrapple::Load(IKFile* file, int32_t type) {
    CKGrabElement::Load(file, type);
    if (type == 0) {
        IKFile_ReadRef(file, &m_apLightningBoltFxData[0]);
        IKFile_ReadRef(file, &m_apLightningBoltFxData[1]);
        IKFile_ReadRef(file, &m_apLightningBoltFxData[2]);
        IKFile_ReadRef(file, &m_pSoundDico);
    }
    return 1;
}

namespace {
// The level's bolt data (+0x140).
CKLightningBoltFxData* BoltData(CKElectricalGrapple* grapple) {
    return static_cast<CKLightningBoltFxData*>(grapple->m_apLightningBoltFxData[grapple->m_dwLevelIndex]);
}
// A sound attached to the user's scene node (host vt+0x08, its +0x1c) and played from its start (TOC +0x35b0 0.0).
void PlayAttached(CKS08AbilityHostBase* host, CKSound* sound) {
    sound->SetAttachObject(static_cast<IKHook*>(host->GetOwner())->m_pKGLObject);  // 0x00111350
    sound->Play(0.0f);                                                             // 0x00111230
}
}  // namespace

// 0x003952a8 CKElectricalGrapple_Start
void CKElectricalGrapple::Start(CKS08AbilityHostBase* host) {
    m_pLoopSound = nullptr;
    CKGrabElement::Start(host);
}

// 0x00395230 CKElectricalGrapple_End
void CKElectricalGrapple::End(int32_t forced) {
    if (m_pLoopSound != nullptr) {
        m_pLoopSound->Stop(0);  // 0x001111b0 Sound_Stop
        m_pLoopSound = nullptr;
    }
    CKGrabElement::End(forced);
}

// 0x00395070 CKElectricalGrapple_ResetRuntime
void CKElectricalGrapple::ResetRuntime() {
    CKGrabElement::ResetRuntime();
    m_pLoopSound = nullptr;
    m_bHotspotIndex = 2;
    m_pBolt = nullptr;
}

// 0x003950b8 CKElectricalGrapple_GetSoundForEvent_maybe
CKSound* CKElectricalGrapple::GetSoundForEvent(int32_t event) {
    CKSoundDictionaryID* sounds = static_cast<CKSoundDictionaryID*>(m_pSoundDico);
    if (event == 0) return sounds->GetSound(0);  // 0x00112bc0
    if (event == 4) return sounds->GetSound(4);
    if (event != 1) return nullptr;
    const auto playable = [sounds](uint32_t index) {
        return sounds->GetSound(index) != nullptr && sounds->GetSound(index)->GetSample() != nullptr;  // 0x00111000
    };
    if (m_dwLevelIndex == 2) {
        if (playable(3)) return sounds->GetSound(3);
        if (playable(2)) return sounds->GetSound(2);
    } else if (m_dwLevelIndex == 1) {
        if (playable(2)) return sounds->GetSound(2);
    }
    return sounds->GetSound(1);
}

// 0x00396120 CKElectricalGrapple_SetFxActive. The bolt comes from the FX service pool (the inlined lookup,
// CKSrvFx::AcquireFx), reserved by the grapple.
void CKElectricalGrapple::SetFxActive(int32_t on) {
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    if (on == 0) {
        if (m_pBolt != nullptr) {
            m_pBolt->StopAndRelease(this);  // vt+0x58
            m_pBolt = nullptr;
        }
        if (m_pLoopSound == nullptr) return;
        CKSound* stop = GetSoundForEvent(4);
        if (stop != nullptr) PlayAttached(m_pHost, stop);
        m_pLoopSound->Stop(0);  // 0x001111b0 Sound_Stop
        m_pLoopSound = nullptr;
        return;
    }
    IKSerializable* grabbed = m_pHost->GetGrabHotspot(this);  // vt+0xe4
    CKLightningBoltFxData* data = BoltData(this);
    data->m_pSourceHotSpot = m_pHost->GetHotspot(2);  // vt+0xcc
    data->m_pTargetNode = nullptr;
    data->m_pTargetHotSpot = grabbed;
    data->m_pSourceNode = nullptr;
    m_pBolt = static_cast<CKLightningBoltNodeFx*>(fxService->AcquireFx(BoltData(this), this));
    if (m_pBolt != nullptr) {
        if (grabbed == nullptr) {
            const CVector3 point = m_pHost->GetTargetAimPoint(1, 0);  // vt+0xdc
            m_pBolt->SetTargetPoint(&point, this);                     // 0x0057a9d0
        }
        ApplyDamageParams(1);                                            // vt+0x8c
        m_pBolt->SetDamageOwner(m_pHost->GetOwner(), this);              // 0x0057aa10, host vt+0x08
        m_pBolt->SetDamageCategory(m_pHost->GetCollisionGroup(), this);  // 0x0057aa60, vt+0xb0
        m_pBolt->SetDamageFlags(m_pHost->GetCollisionMask(), this);      // 0x0057aa88, vt+0xb4
        m_pBolt->SetDamage(m_pElementDamage, this);                              // 0x0057aab0
        m_pBolt->SetUnk1e8(m_pTarget, this);                             // 0x0057aa38
        m_pBolt->SetActiveForOwner(this, 1);                             // 0x00581380
    }
    CKSound* start = GetSoundForEvent(0);
    if (start != nullptr) PlayAttached(m_pHost, start);
    m_pLoopSound = GetSoundForEvent(1);
    if (m_pLoopSound == nullptr) return;
    PlayAttached(m_pHost, m_pLoopSound);
}

// 0x00395790 CKElectricalGrapple_UpdateGrab_maybe
void CKElectricalGrapple::UpdateGrab() {
    CKSrvFx* fxService = static_cast<CKSrvFx*>(g_pEngine->m_srvFx);
    CKLightningBoltFxData* data = BoltData(this);
    data->m_pSourceHotSpot = m_pHost->GetHotspot(2);  // vt+0xcc
    data->m_pTargetNode = nullptr;
    data->m_pSourceNode = nullptr;
    data->m_pTargetHotSpot = nullptr;
    m_pBolt = static_cast<CKLightningBoltNodeFx*>(fxService->AcquireFx(BoltData(this), this));
    if (m_pBolt != nullptr) {
        const CVector3 ground = m_pHost->GetOwnerGroundPoint();  // vt+0x14
        const CVector3 forward = m_pHost->GetAimDirection(0);    // vt+0x24
        const CVector3 point{ppc::fmadds(forward.x, 10.0f, ground.x), ppc::fmadds(forward.y, 10.0f, ground.y),
                             ppc::fmadds(forward.z, 10.0f, ground.z)};  // TOC +0x35a8
        m_pBolt->SetTargetPoint(&point, this);
        m_pBolt->RestartForOwner(0.2f, this);  // TOC +0x35ac
        m_pBolt->ReleaseReservation(this);     // vt+0x54
    }
    m_pBolt = nullptr;  // stw of the found node flag bit 1 (clear there): the bolt is not kept
    CKSound* start = GetSoundForEvent(0);
    if (start != nullptr) PlayAttached(m_pHost, start);
}

// 0x003955b0 CKElectricalGrapple_Slot80_maybe
uint8_t CKElectricalGrapple::Vf80(float /*dt*/) {
    // BUG(original): the direction (r1+0x70) is passed without being set; no host reads it with grab 1 and no target.
    const CVector3 direction{0.0f, 0.0f, 0.0f};
    return m_pHost->GrabEnemy(this, 1, 1, &direction, nullptr, nullptr);  // vt+0xec
}

// 0x00395678 CKElectricalGrapple_Slot84_maybe
void CKElectricalGrapple::Vf84(float /*dt*/) {
    IKSerializable* grabbed = m_pHost->GetGrabHotspot(this);  // vt+0xe4
    CKLightningBoltFxData* data = BoltData(this);
    data->m_pTargetNode = nullptr;
    data->m_pTargetHotSpot = grabbed;
    CKLightningBoltNodeFx* bolt = m_pBolt;
    if (bolt == nullptr || grabbed != nullptr) return;
    const CVector3 point = m_pHost->GetTargetAimPoint(1, 0);  // vt+0xdc
    bolt->SetTargetPoint(&point, this);                        // 0x0057a9d0
}
