// CKHkTransportableObjectSpawner.h - spawns transportable objects (key 0x3042, vtable 0xb28920, size 0x78).
// Original unit: CKHkTransportableObjectSpawner.cpp (0x4a8688-0x4ac108). No XXL2 class. Field names are
// placeholders (C2.1 ports the constructor and Load only).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/util/TVector.h"
#include "k2000/groups/CKGrpTransportableObject.h"

class CKHkTransportableObjectSpawner : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc1)
    DOTD_DECLARE_FACTORIES(CKHkTransportableObjectSpawner)

    // One entry of +0x40 (OperatorNew(0xc) in LoadSpawnEntries): a reference and two words set to 0.
    struct SpawnEntry {
        IKSerializable* m_pUnk0;  // +0x0 reference
        uint32_t m_unk4;          // +0x4 0
        uint32_t m_unk8;          // +0x8 0
    };

    // 0x004aae38 CKHkTransportableObjectSpawner_Create (inlined constructor, the same as the dead
    // 0x4a8bd0 CKHkTransportableObjectSpawner_Construct): the two vectors, empty with capacity 1.
    CKHkTransportableObjectSpawner() {
        m_vUnk2c.m_pBlock = nullptr;
        m_vUnk2c.m_ui32NbElt = 1;
        m_vUnk2c.m_ui32NbUsedElt = 0;
        m_vSpawnEntries.m_ui32NbElt = 1;
        m_vSpawnEntries.m_ui32NbUsedElt = 0;
        m_vSpawnEntries.m_pBlock = nullptr;
    }
    ~CKHkTransportableObjectSpawner() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004aaeb8 CKHkTransportableObjectSpawner_Load
    void SetDefaultState(int32_t flag) override;  // vt+0x38 0x004a87b8 CKHkTransportableObjectSpawner_SetDefaultState
    void Start() override;                        // vt+0x50 0x004a9950 CKHkTransportableObjectSpawner_Start
    // 0x004a9b08 CKHkTransportableObjectSpawner_LoadSpawnEntries_maybe
    void LoadSpawnEntries(IKFile* file);

    IKSerializable* m_unk20;                    // +0x20 reference (LVL010: null or a hook of key 0x542)
    uint8_t m_unk24;                            // +0x24
    uint8_t m_unk25;                            // +0x25 (LVL010: 0 or 1)
    uint8_t m_pad26[2];
    uint32_t m_unk28;                           // +0x28 runtime (Start clears it)
    TVector<void*, 1> m_vUnk2c;                 // +0x2c constructor: empty, capacity 1 (element type unknown)
    CKGrpTransportableObject::Entry* m_pCurrentEntry;  // +0x38 runtime: the group's entry m_unk3c (Start)
    uint32_t m_unk3c;                           // +0x3c (LVL010: 2)
    TVector<SpawnEntry*, 1> m_vSpawnEntries;    // +0x40 LoadSpawnEntries
    uint32_t m_unk4c;                           // +0x4c (LVL010: 1)
    uint32_t m_unk50;                           // +0x50 (LVL010: 0)
    uint32_t m_unk54[2];                        // +0x54
    IKSerializable* m_unk5c;                    // +0x5c reference
    CMatrix34* m_pMatrix;                       // +0x60 RwMatrixCreate in the Load: the spawn frame_maybe
    IKSerializable* m_unk64;                    // +0x64 reference (LVL010: a CKGrpTransportableObject)
    uint8_t m_unk68;                            // +0x68
    uint8_t m_unk69;                            // +0x69 (read last)
    uint8_t m_pad6a[2];
    IKSerializable* m_unk6c;                    // +0x6c reference
    uint32_t m_unk70;                           // +0x70
    uint32_t m_unk74;                           // +0x74
};
DOTD_ASSERT_SIZE(CKHkTransportableObjectSpawner, 0x78);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk25, 0x25);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_vUnk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk3c, 0x3c);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_vSpawnEntries, 0x40);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk4c, 0x4c);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk50, 0x50);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk5c, 0x5c);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_pMatrix, 0x60);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk68, 0x68);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk69, 0x69);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk6c, 0x6c);
DOTD_ASSERT_OFFSET(CKHkTransportableObjectSpawner, m_unk74, 0x74);
