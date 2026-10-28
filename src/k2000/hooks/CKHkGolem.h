// CKHkGolem.h - the golem bosses' hook base (key 0x3182, vtable 0xb29260, size 0xc0). Original unit:
// CKHkGolem.cpp. No XXL2 class. Derives from CKHkActorBase; base of CKHkS08DragonCityGolem(Tail) and
// CKHkS08Malefor. Registered, but no level file holds a plain CKHkGolem.
//
// The Load reads one reference vector (+0x34) and three vectors of heap nodes (+0x58, +0x64, +0x70), each node
// holding a reference and a vector of small heap records (a word and a reference, read word first). The
// vectors grow one element at a time; every Load starts each of them with a fresh one-element block
// (BUG(original): the previous block, if any, is not freed).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/misc/CKHkActorBase.h"
#include "k2000/util/TVector.h"

// The records of the node vectors (::operator new, all words cleared first).
struct CKHkGolemRecord8 {      // 8 bytes (+0x58 nodes)
    IKSerializable* m_pObject;  // +0x00 reference (read second)
    uint32_t m_ui32Value;       // +0x04 (read first; LVL010: 0x34/0x35, kinds_maybe)
};
struct CKHkGolemRecordC {      // 0xc bytes (+0x64 nodes)
    IKSerializable* m_pObject;  // +0x00 reference (read second)
    uint32_t m_ui32Value;       // +0x04 (read first)
    uint32_t m_unk8;            // +0x08 Load 0
};
struct CKHkGolemRecord20 {     // 0x20 bytes (+0x70 nodes)
    IKSerializable* m_pObject;  // +0x00 reference (read second)
    uint32_t m_ui32Value;       // +0x04 (read first)
    uint32_t m_unk8[3];         // +0x08 read after the reference
    uint32_t m_unk14[3];        // +0x14 cleared, not read
};

// The nodes (::operator new; vector constructed empty with capacity 1).
struct CKHkGolemNode18 {                     // 0x18 bytes (+0x58)
    IKSerializable* m_pObject;               // +0x00 reference
    TVector<CKHkGolemRecord8*, 1> m_records; // +0x04
    uint8_t m_unk10;                         // +0x10 read after the second reference
    uint8_t m_pad11[3];
    IKSerializable* m_pObject14;             // +0x14 reference (read second)
};
template <class Record>
struct CKHkGolemNode10 {                     // 0x10 bytes (+0x64, +0x70)
    IKSerializable* m_pObject;               // +0x00 reference
    TVector<Record*, 1> m_records;           // +0x04
};

class CKHkGolem : public CKHkActorBase {
public:
    DOTD_CLASS_KEY(kCategoryHook, 0xc6)

    CKHkGolem();  // 0x004bf6b8 CKHkGolem_Construct (inlined in CKHkGolem_Create 0x4c0ce0)
    ~CKHkGolem() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x004c11c0 CKHkGolem_Load
    int32_t PostLoad(int32_t type) override;  // vt+0x30 0x004bf308 CKHkGolem_PostLoad
    void Start() override;  // vt+0x50 0x004bf970 CKHkGolem_Start
    void LoadObjectVector(IKFile* file, int32_t type);  // 0x004c0ff0 CKHkGolem_LoadRefArray34_maybe

    uint32_t m_unk20;                                       // +0x20 constructor 0
    IKSerializable* m_unk24;                                // +0x24 reference
    IKSerializable* m_unk28;                                // +0x28 reference
    uint32_t m_unk2C;                                       // +0x2c constructor 0
    IKSerializable* m_unk30;                                // +0x30 reference (read first)
    TVector<IKSerializable*, 1> m_unk34;                    // +0x34 references
    uint32_t m_unk40;                                       // +0x40 runtime (Start: 0)
    uint8_t m_unk44;                                        // +0x44 runtime (Start: 0)
    uint8_t m_unk45;                                        // +0x45 runtime (Start: 1)
    uint8_t m_pad46[2];
    uint32_t m_unk48;                                       // +0x48 runtime (Start: 0)
    uint32_t m_unk4C;                                       // +0x4c runtime
    float m_fUnk50;                                         // +0x50 runtime (Start: the game time)
    float m_fUnk54;                                         // +0x54 runtime (Start: the game time)
    TVector<CKHkGolemNode18*, 1> m_unk58;                   // +0x58
    TVector<CKHkGolemNode10<CKHkGolemRecordC>*, 1> m_unk64;  // +0x64
    TVector<CKHkGolemNode10<CKHkGolemRecord20>*, 1> m_unk70; // +0x70
    IKSerializable* m_unk7C;                                // +0x7c reference
    IKSerializable* m_unk80;                                // +0x80 reference
    CMatrix34* m_pUnk84;                                    // +0x84 PostLoad: RwMatrixCreate
    uint32_t m_unk88;                                       // +0x88 (LVL050: 1000)
    uint32_t m_unk8C;                                       // +0x8c
    uint8_t m_unk90;                                        // +0x90
    uint8_t m_pad91[3];
    float m_af94[10];                                       // +0x94 (LVL010/120: 1.0, 0.7, 0.4, ...)
    IKSerializable* m_unkBC;                                // +0xbc reference (read before +0x94)
};
DOTD_ASSERT_SIZE(CKHkGolem, 0xc0);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk20, 0x20);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk24, 0x24);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk30, 0x30);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk34, 0x34);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk58, 0x58);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk64, 0x64);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk70, 0x70);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk7C, 0x7c);
DOTD_ASSERT_OFFSET(CKHkGolem, m_pUnk84, 0x84);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk88, 0x88);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unk90, 0x90);
DOTD_ASSERT_OFFSET(CKHkGolem, m_af94, 0x94);
DOTD_ASSERT_OFFSET(CKHkGolem, m_unkBC, 0xbc);
