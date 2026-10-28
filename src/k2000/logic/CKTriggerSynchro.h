// CKTriggerSynchro.h - (key 0x56cc, vtable 0xb20b78, size 0x14). Original unit: CKTriggerSynchro.cpp.
// DotD only (no XXL2 class of this name); the names are ours.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/util/TVector.h"

class CKTriggerSynchro : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x15b)
    DOTD_DECLARE_FACTORIES(CKTriggerSynchro)

    // One entry (0x14 bytes on the PS3): a reference vector, a word and a byte.
    struct Entry {
        // 0x00239ff0 CKTriggerSynchro_LoadEntry (called with type 0).
        void Load(IKFile* file, int32_t type);
        // 0x0023a770 CKTriggerDomainSet_SetEnabled_maybe: the flag byte (+0x10) set, then every referenced
        // domain takes it as its enabled bit (bit 0 of its flags) and enables or disables itself and its
        // sub-domains and triggers, last to first.
        void SetEnabled(uint8_t enabled);

        TVector<IKSerializable*, 4> m_vRefs;  // +0x00 (the files reference CKTriggerDomain objects)
        uint32_t m_unk0c;                     // +0x0c
        uint8_t m_unk10;                      // +0x10 the Load sets 0
        uint8_t m_pad11[3];
    };

    CKTriggerSynchro();  // inlined in 0x00239d48 CKTriggerSynchro_Create
    ~CKTriggerSynchro() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x0023a210 CKTriggerSynchro_Load

    // 0x00239d98 TriggerDomains_FindSetForSector_maybe: the first entry whose sector (+0x0c) is `sector`, or
    // null. Every caller takes it for granted (CKLevel_SectorUnload does not test the result).
    Entry* FindSetForSector(int32_t sector);

    TVector<Entry, 4> m_vEntries;  // +0x04
    IKSerializable* m_unk10;       // +0x10 a reference (CKS08GameModule in the samples)
};
DOTD_ASSERT_SIZE(CKTriggerSynchro::Entry, 0x14);
DOTD_ASSERT_OFFSET(CKTriggerSynchro::Entry, m_unk0c, 0x0c);
DOTD_ASSERT_OFFSET(CKTriggerSynchro::Entry, m_unk10, 0x10);
DOTD_ASSERT_SIZE(CKTriggerSynchro, 0x14);
DOTD_ASSERT_OFFSET(CKTriggerSynchro, m_vEntries, 0x04);
DOTD_ASSERT_OFFSET(CKTriggerSynchro, m_unk10, 0x10);
