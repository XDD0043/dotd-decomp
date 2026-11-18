// CKBundle.cpp - reconstructed original translation unit 0x1dcb28-0x1de6d8 (GAME_TOC1, main_toc1), 33 functions, 29 live.
// Primary class: CKBundle  key 0xcc  category Logic  size 0x18  vtable 0xb1dfb8
// Other owners: InitializeCKBundleInstance (1), CreateCKBundleArray (1), ObjectList (1), UpdateCKBundleObjects (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1dcb28  CKBundle_Delete
//   [x] 0x1dcb78  InitializeCKBundleInstance  (CKBundle::CKBundle)
//   [ ] 0x1dcba8  FUN_001dcba8  [dead]
//   [ ] 0x1dcc30  FUN_001dcc30  [dead]
//   [ ] 0x1dcd30  FUN_001dcd30  [dead]
//   [x] 0x1dcd40  CKBundle_vf94
//   [ ] 0x1dcd60  RegisterCKBundleClass
//   [ ] 0x1dcde0  _GLOBAL__I_1dcde0
//   [x] 0x1dcdf0  CKBundle_DeleteArray
//   [ ] 0x1dce98  CKBundle_ContainsObject_maybe  [dead]
//   [x] 0x1dcf10  CKBundle_RecursiveRegistration
//   [x] 0x1dd030  CKBundle_Stop
//   [x] 0x1dd120  CKBundle_Resume
//   [x] 0x1dd210  CKBundle_Pause
//   [x] 0x1dd300  CKBundle_BroadcastPostReinit_maybe
//   [x] 0x1dd3f0  CKBundle_Restart
//   [x] 0x1dd4e0  CKBundle_InitHooks_maybe
//   [x] 0x1dd5e8  CKBundle_Start
//   [x] 0x1dd6d8  CKBundle_AddHook_maybe
//   [x] 0x1dd788  CKBundle_ShutdownHooks_maybe
//   [x] 0x1dd890  ConstructCKBundle  (CKBundle::CKBundle)
//   [x] 0x1dd8c0  CKBundle_RemoveHook_maybe
//   [x] 0x1dd988  CKBundle_SectorLoaded
//   [x] 0x1dda88  CKBundle_SectorUnload
//   [x] 0x1ddb88  CKBundle_PostLoad  (returns 1: the root's default)
//   [x] 0x1ddb90  CKBundle_SetDefaultState
//   [x] 0x1ddc90  CKBundle_Destroy
//   [x] 0x1ddca0  CreateCKBundleArray
//   [x] 0x1ddd70  CKBundle_Create
//   [x] 0x1dddc8  ObjectList_MoveBetweenActiveLists_maybe
//   [x] 0x1de010  UpdateCKBundleObjects
//   [x] 0x1de128  CKBundle_Load
//   [ ] 0x1de438  CKBundle_Save
//
//   [ ] 0x9adba0  CKBundle_GetClassType  [inline]
//   [ ] 0x9adba8  CKBundle_GetClassID  [inline]
//   [ ] 0x9adbb0  CKBundle_IsKindOfClass  [inline]
//   [ ] 0x9adbd8  CKBundle_DeletingDestructor  [inline]
//   [ ] 0x9adc20  CKBundle_Destructor  [inline]
#include "k2000/logic/CKBundle.h"

#include "k2000/core/Stub.h"
#include "k2000/groups/IKBaseGroup.h"
#include "k2000/hooks/IKLife.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

namespace {

// The flags the bundle walks share (the original keeps them in globals; only CKBundle's functions touch
// them): 0xcea901 and 0xc40258 for the Start/Stop/... walks, 0xcea902 for the update walk. Each walk sets
// the first to 1, so after the group (the first element) it continues with the awake list.
bool g_walkRestart = false;    // 0xcea901
bool g_walkPending = false;    // 0xc40258
bool g_updateRestart = false;  // 0xcea902

// The walk of CKBundle_Start and its siblings: `call` on the group, then on the awake list; when the
// restart flag was raised meanwhile, on the asleep list too. onlyBit0Clear is InitHooks' test (a life whose
// bit 0 is set is not called).
template <class F>
void WalkLives(CKBundle* bundle, F call, bool onlyBit0Clear) {
    g_walkRestart = true;
    IKLife* life = static_cast<IKLife*>(static_cast<IKBaseGroup*>(bundle->m_pGroup));
    if (life == nullptr) return;
    for (;;) {
        do {
            if (!onlyBit0Clear || (life->m_bitArray & 1) == 0) call(life);
            if (!g_walkRestart) {
                life = life->m_pNext;
            } else {
                g_walkRestart = false;
                g_walkPending = true;
                life = bundle->m_lAwakeLifeList;
            }
        } while (life != nullptr);
        if (!g_walkPending) break;
        g_walkPending = false;
        life = bundle->m_lAsleepLifeList;
        if (life == nullptr) return;
    }
}

}  // namespace

// 0x001dd5e8 CKBundle_Start
void CKBundle::Start() {
    WalkLives(this, [](IKLife* life) { life->Start(); }, false);
}

// 0x001dd3f0 CKBundle_Restart
void CKBundle::Restart() {
    WalkLives(this, [](IKLife* life) { life->Restart(); }, false);
}

// 0x001dd300 CKBundle_BroadcastPostReinit_maybe
void CKBundle::Vf60() {
    WalkLives(this, [](IKLife* life) { life->Vf60(); }, false);
}

// 0x001dd030 CKBundle_Stop
void CKBundle::Stop() {
    WalkLives(this, [](IKLife* life) { life->Stop(); }, false);
}

// 0x001dd210 CKBundle_Pause
void CKBundle::Pause() {
    WalkLives(this, [](IKLife* life) { life->Pause(); }, false);
}

// 0x001dd120 CKBundle_Resume
void CKBundle::Resume() {
    WalkLives(this, [](IKLife* life) { life->Resume(); }, false);
}

// 0x001dd988 CKBundle_SectorLoaded
void CKBundle::SectorLoaded(int32_t sector) {
    WalkLives(this, [sector](IKLife* life) { life->SectorLoaded(sector); }, false);
}

// 0x001dda88 CKBundle_SectorUnload
void CKBundle::SectorUnload(int32_t sector) {
    WalkLives(this, [sector](IKLife* life) { life->SectorUnload(sector); }, false);
}

// 0x001ddb90 CKBundle_SetDefaultState
void CKBundle::SetDefaultState(int32_t flag) {
    WalkLives(this, [flag](IKLife* life) { life->SetDefaultState(flag); }, false);
}

// 0x001dd4e0 CKBundle_InitHooks_maybe
void CKBundle::InitHooks() {
    WalkLives(this, [](IKLife* life) { life->Vf94(); }, true);
}

// 0x001de010 UpdateCKBundleObjects: the group and the awake list only. A life with a flag in bits 0 or 2
// (mask 5) is skipped, one with bit 1 set runs its alternative update (vt+0x80) instead of Update.
// BUG(original): the first test reads the group's flags before the null check of the group pointer.
void CKBundle::Update(IKTime* frameClock) {
    g_updateRestart = true;
    IKLife* life = static_cast<IKLife*>(static_cast<IKBaseGroup*>(m_pGroup));
    bool resume = (life->m_bitArray & 5) != 0;
    if (!resume && life == nullptr) return;
    for (;;) {
        if (!resume) {
            if ((life->m_bitArray & 2) == 0) {
                life->Update(frameClock);
            } else {
                life->Vf80(frameClock);
            }
            if (!g_updateRestart) {
                life = life->m_pNext;
            } else {
                resume = true;
            }
        }
        if (resume) {
            g_updateRestart = false;
            life = m_lAwakeLifeList;
            resume = false;
        }
        while (life != nullptr && (life->m_bitArray & 5) != 0) life = life->m_pNext;
        if (life == nullptr) return;
    }
}

namespace {
// Unlinks `life` from the singly linked list `head` when it is in it (clearing its link); nothing otherwise.
void UnlinkFrom(IKLife*& head, IKLife* life) {
    if (head == nullptr) return;
    if (life == head) {
        head = life->m_pNext;
        life->m_pNext = nullptr;
        return;
    }
    IKLife* prev = head;
    IKLife* cur = prev->m_pNext;
    while (cur != nullptr && cur != life) {
        prev = cur;
        cur = cur->m_pNext;
    }
    if (cur == life) {
        prev->m_pNext = life->m_pNext;
        life->m_pNext = nullptr;
    }
}
}  // namespace

// 0x001dddc8 ObjectList_MoveBetweenActiveLists_maybe
void CKBundle::MoveBetweenActiveLists(IKLife* life, uint32_t active) {
    if (life->IsKindOfClass(2) == 0) return;
    if (active == 0) {
        if ((life->m_bitArray & 1) != 0) return;
        UnlinkFrom(m_lAwakeLifeList, life);
        life->m_pNext = m_lAsleepLifeList;
        m_lAsleepLifeList = life;
    } else if ((life->m_bitArray & 1) != 0) {
        UnlinkFrom(m_lAsleepLifeList, life);
        IKLife* node = m_lAwakeLifeList;
        if (node != nullptr && life->m_ui32Priority < node->m_ui32Priority) {
            IKLife* prev;
            do {
                prev = node;
                node = prev->m_pNext;
                if (node == nullptr) break;
            } while (life->m_ui32Priority < node->m_ui32Priority);
            life->m_pNext = prev->m_pNext;
            prev->m_pNext = life;
            return;
        }
        life->m_pNext = m_lAwakeLifeList;
        m_lAwakeLifeList = life;
    }
}

// Inlined in 0x001ddd70 CKBundle_Create.
// 0x001dcd40 CKBundle_vf94
uint8_t CKBundle::InitializeData(IKBaseGroup* group) {
    group->m_pKBundle = this;
    m_pGroup = group;
    m_ui32Priority = group->m_ui32Priority;
    return 1;
}

// 0x001dcf10 CKBundle_RecursiveRegistration (returns 1)
void CKBundle::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type) - 4u > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    for (IKLife* life = m_lAwakeLifeList; life != nullptr; life = life->m_pNext) life->RecursiveRegistration(type);
    for (IKLife* life = m_lAsleepLifeList; life != nullptr; life = life->m_pNext) life->RecursiveRegistration(type);
}

// 0x001dcb78 InitializeCKBundleInstance / 0x001dd890 ConstructCKBundle (the same body; inlined in CKBundle_Create)
CKBundle::CKBundle() {
    m_pNext = nullptr;
    m_ui32Priority = 0x7fffffff;
    m_pGroup = nullptr;
    m_lAwakeLifeList = nullptr;
    m_lAsleepLifeList = nullptr;
}

// 0x001de128 CKBundle_Load. No type test and no base Load. The awake list is bubble-sorted by the
// nodes' priority, highest first (unsigned compare), as XXL2's EUL_TSNodeList sort.
int32_t CKBundle::Load(IKFile* file, int32_t /*type*/) {
    IKFile_ReadRef(file, &m_pNext);
    ReadU32LE(file, &m_ui32Priority);
    IKFile_ReadRef(file, &m_pGroup);
    IKFile_ReadRef(file, &m_lAwakeLifeList);
    IKLife* node = m_lAwakeLifeList;
    if (node != nullptr) {
        IKLife* cur = node->m_pNext;
        while (cur != nullptr) {
            bool swapped = false;
            IKLife* prev = nullptr;
            for (;;) {
                IKLife* a = node;
                if (cur->m_ui32Priority > a->m_ui32Priority) {
                    a->m_pNext = cur->m_pNext;  // swap a and cur
                    cur->m_pNext = a;
                    if (prev == nullptr) {
                        m_lAwakeLifeList = cur;
                    } else {
                        prev->m_pNext = cur;
                    }
                    prev = cur;
                    cur = a->m_pNext;
                    swapped = true;
                    if (cur == nullptr) break;
                } else {
                    node = cur;
                    prev = a;
                    cur = cur->m_pNext;
                    if (cur == nullptr) break;
                }
            }
            if (!swapped) break;
            node = m_lAwakeLifeList;
            cur = node->m_pNext;
        }
    }
    IKFile_ReadRef(file, &m_lAsleepLifeList);
    return 1;
}

// 0x001dd788 CKBundle_ShutdownHooks_maybe (XXL2 the counterpart of AwakeOnStart): vt+0x98 on every life whose bit 0
// is clear, the group first, then the awake list and the asleep list (InitHooks' walk).
void CKBundle::ShutdownHooks() {
    WalkLives(this, [](IKLife* life) { life->Vf98(); }, true);
}

// 0x001dd6d8 CKBundle_AddHook_maybe (C2.7 enemy family: the squads take their enemies from the pools)
void CKBundle::AddHook(IKLife* life) {
    if ((life->m_bitArray & 1u) != 0) {
        life->m_pNext = m_lAsleepLifeList;
        m_lAsleepLifeList = life;
        return;
    }
    IKLife* prev = m_lAwakeLifeList;
    if (prev == nullptr || prev->m_ui32Priority <= life->m_ui32Priority) {
        life->m_pNext = m_lAwakeLifeList;
        m_lAwakeLifeList = life;
        return;
    }
    for (IKLife* next = prev->m_pNext; next != nullptr && next->m_ui32Priority > life->m_ui32Priority; next = next->m_pNext) {
        prev = next;
    }
    life->m_pNext = prev->m_pNext;
    prev->m_pNext = life;
}

// 0x001dd8c0 CKBundle_RemoveHook_maybe (a life not in the list is left alone)
void CKBundle::RemoveHook(IKLife* life) {
    IKLife** head = (life->m_bitArray & 1u) != 0 ? &m_lAsleepLifeList : &m_lAwakeLifeList;
    if (*head == nullptr) return;
    if (*head == life) {
        *head = life->m_pNext;
    } else {
        IKLife* prev = *head;
        while (prev->m_pNext != life) {
            if (prev->m_pNext == nullptr) return;
            prev = prev->m_pNext;
        }
        prev->m_pNext = life->m_pNext;
    }
    life->m_pNext = nullptr;
}
