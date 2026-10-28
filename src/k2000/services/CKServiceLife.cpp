// CKServiceLife.cpp - reconstructed original translation unit 0x1dece0-0x1dfb50 (GAME_TOC1, main_toc1), 27 functions, 26 live.
// Primary class: CKServiceLife  key 0x41  category Service  size 0x14  vtable 0xb1e150
// Other owners: UpdateLifeServiceBundles (1), ObjectList (1), DeserializeLifeServiceBundleHead (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x1dece0  RegisterCKServiceLifeType
//   [ ] 0x1ded58  _GLOBAL__I_1ded58
//   [ ] 0x1ded68  CKServiceLife_PostLoad
//   [x] 0x1ded90  CKServiceLife_Destroy
//   [ ] 0x1dedc8  ConstructCKServiceLife
//   [x] 0x1dee30  CKServiceLife_Construct
//   [x] 0x1dee98  CKServiceLife_DeleteArray
//   [x] 0x1def40  CKServiceLife_Restart
//   [ ] 0x1defc0  CKServiceLife_FindBundleContaining_maybe  [dead]
//   [ ] 0x1df058  CKServiceLife_RecursiveRegistration
//   [x] 0x1df0e8  UpdateLifeServiceBundles
//   [x] 0x1df168  CKServiceLife_Resume
//   [x] 0x1df1e8  CKServiceLife_Stop
//   [x] 0x1df2a0  CKServiceLife_Pause
//   [x] 0x1df320  CKServiceLife_Start
//   [x] 0x1df3d8  CKServiceLife_BroadcastPostReinit_maybe
//   [x] 0x1df458  ObjectList_SetObjectActive_maybe
//   [ ] 0x1df5c0  CKServiceLife_Save
//   [x] 0x1df670  DeserializeLifeServiceBundleHead
//   [x] 0x1df720  CKServiceLife_SetDefaultState
//   [x] 0x1df798  CKServiceLife_SectorLoaded
//   [x] 0x1df810  CKServiceLife_SectorUnload
//   [x] 0x1df888  CKServiceLife_CreateArray
//   [x] 0x1df9a0  CKServiceLife_Create
//   [ ] 0x1dfa28  CKServiceLife_DeletingDestructor
//   [ ] 0x1dfa90  CKServiceLife_Destructor_2
//   [ ] 0x1dfaf0  CKServiceLife_Destructor
//
//   [ ] 0x9adcb0  CKServiceLife_IsKindOfClass  [inline]
//   [ ] 0x9adce8  CKServiceLife_GetClassType  [inline]
//   [ ] 0x9adcf0  CKServiceLife_GetClassID  [inline]
#include "k2000/services/CKServiceLife.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKBundle.h"
#include "k2000/misc/Engine.h"
#include "k2000/logic/CKBundle.h"
#include "k2000/system/IKTime.h"

// 0x001dee30 CKServiceLife_Construct (the same stores inlined in 0x1df9a0 CKServiceLife_Create): the
// IKService part, the priority, the list head; m_eCurrentState is left as it is.
CKServiceLife::CKServiceLife() {
    m_ui32Priority = 0x78;
    m_lBundleList = nullptr;
    Engine_SetServiceLife(this);
}

// 0x001ded90 CKServiceLife_Destroy: no bundle list (the bundles are level objects).
void CKServiceLife::Destroy() {
    m_lBundleList = nullptr;
}

// 0x001df670 CKServiceLife_Load (Ghidra: DeserializeLifeServiceBundleHead). No type test: every file
// that holds the service gives the head of its bundle list.
int32_t CKServiceLife::Load(IKFile* file, int32_t /*type*/) {
    IKFile_ReadRef(file, &m_lBundleList);
    return 1;
}

// 0x001df320 CKServiceLife_Start: every bundle started (vt+0x50: the hooks' Start), then InitHooks (the lives'
// vt+0x94) of every bundle; the service is running (state 0).
void CKServiceLife::Start() {
    for (CKBundle* bundle = static_cast<CKBundle*>(m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        bundle->Start();
    }
    for (CKBundle* bundle = static_cast<CKBundle*>(m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        bundle->InitHooks();
    }
    m_eCurrentState = 0;
}

// 0x001def40 CKServiceLife_Restart: every bundle restarted (vt+0x54); running.
void CKServiceLife::Restart() {
    for (CKBundle* bundle = static_cast<CKBundle*>(m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        bundle->Restart();
    }
    m_eCurrentState = 0;
}

// 0x001df3d8 CKServiceLife_BroadcastPostReinit_maybe: every bundle's vt+0x60; running.
void CKServiceLife::Vf60() {
    for (CKBundle* bundle = static_cast<CKBundle*>(m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        bundle->Vf60();
    }
    m_eCurrentState = 0;
}

// 0x001df2a0 CKServiceLife_Pause: every bundle paused (vt+0x70); state 1.
void CKServiceLife::Pause() {
    for (CKBundle* bundle = static_cast<CKBundle*>(m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        bundle->Pause();
    }
    m_eCurrentState = 1;
}

// 0x001df168 CKServiceLife_Resume: every bundle resumed (vt+0x78); running.
void CKServiceLife::Resume() {
    for (CKBundle* bundle = static_cast<CKBundle*>(m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        bundle->Resume();
    }
    m_eCurrentState = 0;
}

// 0x001df0e8 UpdateLifeServiceBundles: every bundle updated (vt+0x7c) while the frame clock runs (state 0).
void CKServiceLife::Update(IKTime* frameClock) {
    if (frameClock->m_eCurrentState != 0) return;
    for (CKBundle* bundle = static_cast<CKBundle*>(m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        bundle->Update(frameClock);
    }
}

// 0x001df798 CKServiceLife_SectorLoaded: every bundle told (its vt+0x88).
void CKServiceLife::SectorLoaded(int32_t sector) {
    for (CKBundle* bundle = static_cast<CKBundle*>(m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        bundle->SectorLoaded(sector);
    }
}

// 0x001df720 CKServiceLife_SetDefaultState (C2.4 exit: the hooks' default states, e.g. a crumbly zone's hit points,
// which its OnActivate reads): every bundle in list order, the flag passed as its low byte (rldicl 0x38).
void CKServiceLife::SetDefaultState(int32_t flag) {
    for (CKBundle* bundle = static_cast<CKBundle*>(m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        bundle->SetDefaultState(flag & 0xff);
    }
}

// 0x001df1e8 CKServiceLife_Stop: the hooks of every bundle shut down, then every bundle stopped (vt+0x68).
void CKServiceLife::Stop() {
    for (CKBundle* bundle = static_cast<CKBundle*>(m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        bundle->ShutdownHooks();
    }
    for (CKBundle* bundle = static_cast<CKBundle*>(m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        bundle->Stop();
    }
    m_eCurrentState = 2;
}

// 0x001df810 CKServiceLife_SectorUnload
void CKServiceLife::SectorUnload(int32_t sector) {
    for (CKBundle* bundle = static_cast<CKBundle*>(m_lBundleList); bundle != nullptr; bundle = bundle->m_pNext) {
        bundle->SectorUnload(sector);
    }
}

// 0x001df458 ObjectList_SetObjectActive_maybe
void CKServiceLife::SetObjectActive(IKLife* life, uint32_t active, CKBundle* bundle) {
    bundle->MoveBetweenActiveLists(life, active & 0xff);
    if (m_eCurrentState == 0) {
        if ((life->m_bitArray & 1) == 0) {
            if (active == 0) {
                life->Vf98();
                life->m_bitArray = (life->m_bitArray & 0xfffffffeu) | 1u;
                return;
            }
        } else if (active != 0) {
            life->Vf94();
            life->m_bitArray &= 0xfffffffeu;
            return;
        }
    } else {
        life->m_bitArray = (life->m_bitArray & 0xfffffffeu) | ((active ^ 1u) & 0xffu);
    }
}
