// CKGroundCpnt.cpp - reconstructed original translation unit 0x190e40-0x191b00 (GAME_TOC1, main_toc1), 32 functions, 27 live.
// Primary class: CKGroundCpnt  key 0x1206  category Component  size 0x10  vtable 0xb1bed8
// Other owners: CKSrvCollision (8), CollisionMeshArray (5)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x190e40  CKGroundCpnt_Delete
//   [ ] 0x190e90  CKGroundCpnt_Construct  [dead]
//   [ ] 0x190eb0  CKGroundCpnt_Construct_2  [dead]
//   [ ] 0x190ed0  RegisterCKGroundCpntClass
//   [ ] 0x190f48  _GLOBAL__I_190f48
//   [ ] 0x190f58  CollisionMeshArray_SetActiveAt
//   [ ] 0x190f98  CKGroundCpnt_Destructor_2
//   [x] 0x190ff0  CKGroundCpnt_DeleteArray
//   [ ] 0x191090  CollisionMeshArray_GetAt
//   [ ] 0x1910a8  CollisionMeshArray_SetActive_maybe
//   [ ] 0x191128  CollisionMeshArray_IsActiveAt_maybe  [dead]
//   [ ] 0x191148  CollisionMeshArray_GetCount_maybe
//   [x] 0x191150  CKGroundCpnt_CreateArray
//   [x] 0x191210  CKGroundCpnt_Create
//   [ ] 0x191260  CKGroundCpnt_Save
//   [x] 0x191268  CKGroundCpnt_Load
//   [ ] 0x191410  CKGroundCpnt_MessageProc
//   [ ] 0x191418  CKGroundCpnt_RecursiveRegistration
//   [ ] 0x191420  CKGroundCpnt_PostLoad
//   [ ] 0x191428  CKGroundCpnt_Destroy
//   [ ] 0x191478  CKGroundCpnt_DeletingDestructor
//   [ ] 0x1914d8  CKGroundCpnt_Destructor
//   [ ] 0x191530  CKSrvCollision_Delete
//   [ ] 0x191580  CKSrvCollision_Start
//   [ ] 0x191588  CKSrvCollision_Restart
//   [ ] 0x191590  CKSrvCollision_Pause
//   [ ] 0x191598  CKSrvCollision_Stop
//   [ ] 0x1915a0  CKSrvCollision_Resume
//   [x] 0x1915a8  CKSrvCollision_DeactivateTestsOfDisabledVolumes_maybe
//   [ ] 0x191a38  CKSrvCollision_ReleaseDynSphere_maybe
//   [ ] 0x191a60  FUN_00191a60  [dead]
//   [ ] 0x191ac0  FUN_00191ac0  [dead]
//
//   [ ] 0x9aa690  CKGroundCpnt_IsKindOfClass  [inline]
//   [x] 0x9aa6b8  CKGroundCpnt_GetClassType  [inline]
//   [x] 0x9aa6c0  CKGroundCpnt_GetClassID  [inline]
#include "k2000/components/CKGroundCpnt.h"

#include "k2000/components/TVectorLoad.h"
#include "k2000/scenegraph/IKBoundingVolume.h"
#include "k2000/services/CKSrvCollision.h"

// 0x00191268 CKGroundCpnt_Load
int32_t CKGroundCpnt::Load(IKFile* file, int32_t type) {
    if (type == K_LEVEL_PLATEFORMS) TVector_LoadRefs(m_vGrounds, file);
    return 1;
}

namespace {
// The contact-to-test lists (by hand in the original; XXL2 TSPriorityList / TSNodeList): a contact's next in its list
// (+0x0c), the next of another priority in the awake list (+0x10) and the link +0x14 (CKSrvCollision.cpp).
inline CContactToTest*& Next(CContactToTest* c) { return c->m_apSameStateNext[0]; }
inline CContactToTest*& Skip(CContactToTest* c) { return c->m_apSameStateNext[1]; }
inline CContactToTest*& Multi(CContactToTest* c) { return c->m_pMultiUse; }
inline uint8_t VolumeInfos(const CContactToTest* contact, int side) {
    return static_cast<IKBoundingVolume*>(contact->m_apBoundingVolume[side])->m_ba8Infos;
}
}  // namespace
#define NEXT(c) Next(c)
#define SKIP(c) Skip(c)
#define MULTI(c) Multi(c)

// 0x001915a8 CKSrvCollision_DeactivateTestsOfDisabledVolumes_maybe (XXL2 AsleepContactToTestIfNecessary): while the
// service's m_Infos bit 1 (a volume was switched off) is set, every awake contact one of whose volumes is off goes
// to the asleep list, with the multi-use contacts that follow it; then the bit is cleared. A transcription of the
// original's list walk (prev / prev2 / prev3 are the three contacts before the current one).
void CKSrvCollision::DeactivateTestsOfDisabledVolumes() {
    if ((m_Infos & 2) == 0) return;
    CContactToTest* cur = m_AwakeList;
    CContactToTest* prev = nullptr;
    CContactToTest* prev2 = nullptr;
    CContactToTest* prev3 = nullptr;
    while (cur != nullptr) {
        CContactToTest* const contact = cur;
        if ((VolumeInfos(contact, 0) & 1) != 0 && (VolumeInfos(contact, 1) & 1) != 0) {
            // Both on: the contact stays awake.
            prev3 = prev2;
            prev2 = prev;
            prev = cur;
            cur = NEXT(contact);
            continue;
        }
        cur->m_ba16Infos = static_cast<uint16_t>(cur->m_ba16Infos & ~0x10u);
        const uint32_t type = contact->m_ba16Infos & 3u;
        if (type == 0) {
            CContactToTest* next;
            if (prev == nullptr) {
                // The head leaves the awake list.
                CContactToTest* head = m_AwakeList;
                next = nullptr;
                if (head != nullptr) {
                    CContactToTest* second = NEXT(head);
                    if (second != nullptr) {
                        NEXT(head) = nullptr;
                        m_AwakeList = second;
                        next = second;
                    } else {
                        m_AwakeList = nullptr;
                    }
                }
            } else {
                CContactToTest* link = MULTI(contact);
                if (link != nullptr) {
                    SKIP(link) = NEXT(contact);
                    if (NEXT(contact) != nullptr) MULTI(NEXT(contact)) = link;
                }
                CContactToTest* removed = NEXT(prev);
                if (removed != nullptr) {
                    NEXT(prev) = NEXT(removed);
                    if (NEXT(removed) != nullptr) NEXT(removed) = nullptr;
                }
                next = NEXT(prev);
                SKIP(prev) = next;
            }
            NEXT(contact) = m_AsleepList;
            m_AsleepList = cur;
            cur = next;
        } else if (type == 1) {
            // The multi-use contacts (type 2) that follow it go to sleep with it.
            CContactToTest* follower = NEXT(contact);
            while (follower != nullptr && (follower->m_ba16Infos & 3u) == 2) {
                NEXT(contact) = NEXT(follower);
                if (NEXT(follower) != nullptr) NEXT(follower) = nullptr;
                NEXT(follower) = m_AsleepList;
                m_AsleepList = follower;
                follower->m_ba16Infos = static_cast<uint16_t>(follower->m_ba16Infos & ~0x10u);
                follower = NEXT(contact);
            }
            if (MULTI(contact) != nullptr) SKIP(MULTI(contact)) = follower;
            if (NEXT(contact) != nullptr) MULTI(NEXT(contact)) = MULTI(contact);
            CContactToTest* moved;
            CContactToTest* next;
            if (prev == nullptr) {
                moved = m_AwakeList;
                next = moved;
                if (moved != nullptr) {
                    next = NEXT(moved);
                    if (next != nullptr) {
                        NEXT(moved) = nullptr;
                        m_AwakeList = next;
                    } else {
                        m_AwakeList = nullptr;
                    }
                }
            } else {
                moved = NEXT(prev);
                if (moved != nullptr) {
                    NEXT(prev) = NEXT(moved);
                    if (NEXT(moved) != nullptr) NEXT(moved) = nullptr;
                }
                next = NEXT(prev);
                SKIP(prev) = next;
            }
            if (moved != nullptr) {
                NEXT(moved) = m_AsleepList;
                m_AsleepList = moved;
            }
            cur = next;
        } else if (type == 2) {
            // A multi-use contact goes to sleep; when it was the only one awake after its partner (the previous
            // contact, of no priority class), the partner goes to sleep too.
            bool withPartner = false;
            CContactToTest* const partner = prev;  // the previous contact (the partner when withPartner)
            if (MULTI(contact) == prev && NEXT(contact) == SKIP(partner) && ((partner->m_ba16Infos >> 2) & 3u) == 0) {
                CContactToTest* link = MULTI(partner);
                CContactToTest* after = NEXT(contact);
                if (link != nullptr) {
                    SKIP(link) = after;
                    after = NEXT(contact);
                }
                withPartner = true;
                if (after != nullptr) MULTI(after) = link;
            }
            CContactToTest* removed = NEXT(partner);
            if (removed != nullptr) {
                NEXT(partner) = NEXT(removed);
                if (NEXT(removed) != nullptr) NEXT(removed) = nullptr;
            }
            NEXT(contact) = m_AsleepList;
            m_AsleepList = cur;
            CContactToTest* next = NEXT(partner);
            if ((partner->m_ba16Infos & 3u) != 1) SKIP(partner) = next;
            if (!withPartner) {
                cur = next;
                continue;
            }
            prev->m_ba16Infos = static_cast<uint16_t>(prev->m_ba16Infos & ~0x10u);
            if (prev2 == nullptr) {
                if (SKIP(partner) != nullptr) MULTI(SKIP(partner)) = prev2;
                CContactToTest* head = m_AwakeList;
                if (head != nullptr) {
                    CContactToTest* second = NEXT(head);
                    if (second != nullptr) {
                        NEXT(head) = prev2;
                        m_AwakeList = second;
                    } else {
                        m_AwakeList = prev2;
                    }
                }
            } else {
                CContactToTest* removed2 = NEXT(prev2);
                if (removed2 != nullptr) {
                    NEXT(prev2) = NEXT(removed2);
                    if (NEXT(removed2) != nullptr) NEXT(removed2) = nullptr;
                }
                SKIP(prev2) = NEXT(prev2);
            }
            NEXT(partner) = m_AsleepList;
            m_AsleepList = prev;
            prev = prev2;
            prev2 = prev3;
            prev3 = nullptr;
            cur = next;
        } else {
            // BUG(original): a type 3 contact loops on itself (no data has one).
            break;
        }
    }
    m_Infos &= ~2u;
}
#undef NEXT
#undef SKIP
#undef MULTI
