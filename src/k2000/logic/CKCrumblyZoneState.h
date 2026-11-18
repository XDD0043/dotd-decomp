// CKCrumblyZoneState.h - one state of a crumbly zone (key 0xa40c, vtable 0xb25758, size 0x4c). Original
// unit: CKCrumblyZoneState.cpp. DotD only (no XXL2 class); the names are ours, the reference types from
// the files (struct draft).
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/util/TVector.h"

class IKTime;
struct ContactHistoryNode;

class CKCrumblyZoneState : public IKSerializable {
public:
    // 0x00403a00 CrumblyZoneState_ComputeCenter_maybe: with volumes in the bounding component (+0x20) `center` becomes the
    // mean of their nodes' LTM positions (summed from the zero vector, times 1 / count); else it is left as it is.
    void ComputeCenter(CVector3* center) const;
    // 0x00404050 CrumblyZoneState_SetEnabled_maybe. On: +0x08 = +0x0c, each entry's piece (the zone's +0x2c, same index)
    // activated with the entry's animation and FX position or deactivated, the grounds (+0x1c) on, the volumes (+0x20)
    // under the zone's node and on, the sound 0 played when `sound` (from 0), the bonus data reset (+0x3c cleared).
    // Off: the first pieces (one per entry) deactivated, the grounds off, the volumes off and under the dynamic scene
    // root, the sound 1 stopped when playing, the contact list (+0x24) given back to its pool, the bonus data reset.
    void SetEnabled(uint8_t on, uint8_t sound);
    // 0x00404378 CrumblyZoneState_UpdateNavBlocking_maybe: with +0x38 bit 0, the path finding's boxes of the grounds
    // blocked or freed.
    void UpdateNavBlocking(uint8_t on);
    // 0x00403c20 CrumblyZoneState_CopyContactList_maybe: this state's contact list (+0x24) replaced by a copy of
    // `from`'s (the entries copied in order, each put in front: the copy is reversed).
    void CopyContactList(const CKCrumblyZoneState* from);
    // 0x00403be0 CKCrumblyZoneState_GetFlagBit9_maybe: bit 9 of +0x38.
    uint8_t GetFlagBit9() const { return static_cast<uint8_t>((m_unk38 >> 9) & 1u); }
    DOTD_CLASS_KEY(kCategoryLogic, 0x290)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0xa40c || key == 0xc; }  // vt+0x08 0x9c1150
    DOTD_DECLARE_FACTORIES(CKCrumblyZoneState)

    // One entry (0x14 bytes on the PS3): three bytes, a word and three words (a vector _maybe).
    struct Entry {
        uint8_t m_unk00;      // +0x00
        uint8_t m_unk01;      // +0x01
        uint8_t m_unk02;      // +0x02
        uint8_t m_pad03;
        uint32_t m_unk04;     // +0x04
        uint32_t m_unk08[3];  // +0x08 read as 12 bytes, then each word swapped
    };

    CKCrumblyZoneState();  // 0x00403770 CKCrumblyZoneState_Construct (inlined in Create)
    // 0x004054b8 CKCrumblyZoneState_Destructor: the contact list (+0x24) given back to its pool (ContactHistory_FreeNode)
    // and cleared, then the entry block (+0x10; Destroy freed it already at a level exit) freed and the vector emptied.
    ~CKCrumblyZoneState() override;
    void Destroy() override;  // vt+0x10 0x00403ff8 CKCrumblyZoneState_Destroy: the entry block freed

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00404d98 CKCrumblyZoneState_Load
    // vt+0x30 0x00403e50 CKCrumblyZoneState_PostLoad: for the level type (0) the bounding component's contact observer
    // gets this state and the member-function pointer {0xbb4578 = OnContact 0x404bc0, 0} (0x190198), +0x08 = 0 and the
    // grounds inactive (0x1910a8); returns 1 (IKSerializable's PostLoad not called).
    int32_t PostLoad(int32_t type) override;
    // 0x00404bc0 CrumblyZoneState_OnContact_maybe, the contact observer's callback (owner = this state; from
    // CollisionContactObserver_DispatchActiveContacts_maybe 0x190410 in UpdateState): a hero's or an enemy's (owner types
    // 2 / 3) hurting volume (properties bit 2 or 3) touches the contact list (-1000 s; its owner unless +0x38 bit 6); the
    // zone's hit damage (vt+0xf4) for it, when positive, applied at the contact point (or the volume's position).
    static void OnContact(void* self, IKSerializable* volume, IKSerializable* contact);
    // 0x004047d0 CrumblyZoneState_ApplyDamage_maybe: a hit of `damage` at `point`. Enough to break the state (its health
    // +0x08 at most `damage`, and above 0): the zone's next state (AdvanceToNextState, with its sound and FX), the health 0,
    // every bonus of the table (+0x34) at the volumes' centre, the trigger list +0x7c and sound 2 (when it has a sample).
    // Less: the health lowered, the zone's hit FX at `point` (vt+0x100), the mode-1 bonuses at the centre, the trigger
    // list and sound 2. A non-positive hit only asks the zone's vt+0x104.
    void ApplyDamage(float damage, const CVector3* point);
    // 0x00403ec8 CKHkCrumblyZoneMultiState_UpdateState_maybe: a timed state (+0x40 > 0) past its time goes back to the
    // previous state (with its sound), else its time runs; the contacts dispatched (OnContact) and aged; sound 1 started
    // when it is not playing.
    void UpdateState(IKTime* frameClock);
    // 0x004038f0 CKCrumblyZoneState_SetVolumesDamage_maybe (not virtual; the damage is its caller's second
    // argument): the bounding component's volumes all take `damage`.
    void SetVolumesDamage(IKSerializable* damage);

    IKSerializable* m_pZone;         // +0x04 CKHkS08CrumblyZoneMultiState in the files
    float m_unk08;                   // +0x08 not loaded; PostLoad sets 0 (a 0 word)
    float m_unk0c;                   // +0x0c
    TVector<Entry, 1> m_vEntries;    // +0x10 the constructor: null, capacity 1, 0 used
    IKSerializable* m_pGroundCpnt;   // +0x1c CKGroundCpnt in the files
    IKSerializable* m_pBoundingCpnt; // +0x20 CKBoundingCpnt in the files
    ContactHistoryNode* m_unk24;  // +0x24 the contact list (ContactHistory, the pool 0x00ceaa70); the constructor
                                         // sets 0
    IKSerializable* m_pSound;        // +0x28 CKSoundDictionaryID in the files
    float m_unk2c;                   // +0x2c
    float m_unk30;                   // +0x30
    IKSerializable* m_pBonusData;    // +0x34 CKBonusData in the files
    uint32_t m_unk38;                // +0x38 read before +0x34
    float m_unk3c;                   // +0x3c not loaded: the time in this state (UpdateState; SetEnabled's 0 word)
    float m_unk40;                   // +0x40
    int32_t m_unk44;                 // +0x44
    int32_t m_unk48;                 // +0x48
};
DOTD_ASSERT_SIZE(CKCrumblyZoneState::Entry, 0x14);
DOTD_ASSERT_SIZE(CKCrumblyZoneState, 0x4c);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_pZone, 0x04);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_vEntries, 0x10);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_pGroundCpnt, 0x1c);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_pBoundingCpnt, 0x20);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_pSound, 0x28);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_pBonusData, 0x34);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_unk38, 0x38);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_unk40, 0x40);
DOTD_ASSERT_OFFSET(CKCrumblyZoneState, m_unk48, 0x48);
