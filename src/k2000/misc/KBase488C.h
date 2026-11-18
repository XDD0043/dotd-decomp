// KBase488C.h - the physics joints' unregistered base (key 0x488c; Ghidra CKPxJoint_488c_maybe_*, vtable 0xb1ff70,
// size 0x58). Original unit: CKPxJoint.cpp (0x21d108-0x220020). Base: KBase468C. Its classes are CKPxD6Joint,
// CKPxFixedJoint, CKPxSphericalJoint, CKPxSpringJoint, CKPxPrismaticJoint and CKPxWheelJoint. No game file holds a
// joint (outputs/remake/kp3-class-usage.json). Names ours.
//
// C2.8 port-all P03 wrote this header for its six joints (their constructor, Load and Destroy need it); the bodies are
// inline here and CKPxJoint.cpp's checklist (P09's file) is left as it was: ConstructBase 0x21d1c0 (the constructor
// below), Load 0x21da00, ClearReferences 0x21d158 (Destroy), vf24 0x21d130 / vf28 0x21d108 (RecursiveRegistration /
// Save: the base's, returning 1), BaseDestructor 0x21d9a8 (the destructor). C2.8 port-last Z7: the solver slots +0x58 ..
// +0x64 (KBase488C_vf58 / vf5C / vf64 in CKPxJoint.cpp, the joints' vf60 Solve in their units).
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/core/Stub.h"
#include "k2000/math/CMatrix34.h"
#include "k2000/io/IKFile.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/KBase468C.h"
#include "k2000/util/TVector.h"

class CKPxBody;

class KBase488C : public KBase468C {
public:
    // One anchor (16 bytes): three words read at once, then a word (a limit plane: AddLimitRow).
    struct SAnchor {
        CVector3 m_vNormal;   // +0x00 the plane's normal
        float m_fOffset;      // +0x0c its offset
    };

    // 0x0021d1c0 CKPxJoint_488c_maybe_ConstructBase: the base, the vtable, the anchors (null, 1, 0).
    KBase488C() {
        m_anchors.m_pBlock = nullptr;
        m_anchors.m_ui32NbElt = 1;
        m_anchors.m_ui32NbUsedElt = 0;
    }
    // 0x0021d9a8 CKPxJoint_488c_maybe_BaseDestructor: the anchors' block freed, then the base's.
    ~KBase488C() override {
        if (m_anchors.m_pBlock != nullptr) Mem_FreeAligned16(m_anchors.m_pBlock);  // 0x00052fb8
    }

    int32_t IsKindOfClass(uint32_t key) override { return key == 0x488c || key == 0x468c || key == 0xc; }
    // vt+0x2c 0x0021da00 CKPxJoint_488c_maybe_Load: the base's, then (level data only) a word, four references, a byte,
    // two words (+0x34 first), the anchors (a 16-bit count; none read for 0), three words (one read) and two words.
    int32_t Load(IKFile* file, int32_t type) override {
        KBase468C::Load(file, type);  // 0x00218078
        if (type != K_LEVEL_PLATEFORMS) return 1;
        ReadU32LE(file, &m_unk18);
        IKFile_ReadRef(file, &m_unk1c);
        IKFile_ReadRef(file, &m_unk20);
        IKFile_ReadRef(file, &m_unk24);
        IKFile_ReadRef(file, &m_unk28);
        ReadU8(file, &m_unk2c);
        ReadU32LE(file, &m_unk34);
        ReadU32LE(file, &m_unk30);
        uint16_t count = 0;
        ReadU16LE(file, &count);
        if (count != 0) {
            // A fresh block (BUG(original): a previous one is not freed); the capacity test can never grow it.
            m_anchors.m_ui32NbElt = count;
            m_anchors.m_pBlock = static_cast<SAnchor*>(Mem_AllocAligned16(count * static_cast<uint32_t>(sizeof(SAnchor))));
            if (m_anchors.m_ui32NbElt < count) {
                const uint32_t capacity = static_cast<uint32_t>(count) + 1;
                m_anchors.m_pBlock = static_cast<SAnchor*>(
                    Mem_ReallocAligned16(m_anchors.m_pBlock, capacity * static_cast<uint32_t>(sizeof(SAnchor))));
                m_anchors.m_ui32NbElt = capacity;
            }
            m_anchors.m_ui32NbUsedElt = count;
            for (uint32_t i = 0; i < count; ++i) {
                ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_anchors.m_pBlock[i].m_vNormal), 3);
                ReadF32LE(file, &m_anchors.m_pBlock[i].m_fOffset);
            }
        }
        ReadU32LEWords(file, reinterpret_cast<uint32_t*>(&m_unk44), 3);
        ReadU32LE(file, &m_unk50);
        ReadU32LE(file, &m_unk54);
        return 1;
    }
    // vt+0x10 0x0021d158 CKPxJoint_488c_maybe_ClearReferences: the anchors' block freed, its length and block cleared,
    // then the base's (empty).
    void Destroy() override {
        if (m_anchors.m_pBlock != nullptr) Mem_FreeAligned16(m_anchors.m_pBlock);
        m_anchors.m_ui32NbUsedElt = 0;
        m_anchors.m_pBlock = nullptr;
        KBase468C::Destroy();
    }

    // vt+0x58 0x0021f1e8 KBase488C_vf58 (CKPxJoint.cpp)
    virtual void SetDisabled(int32_t disabled);
    // vt+0x5c 0x0021df28 KBase488C_vf5C (CKPxJoint.cpp): the body that takes the joint's rows (none: no rows).
    virtual CKPxBody* WakeAndPickBody();
    // vt+0x60 (pure in the base): the joint's step (RunFixedSteps calls it per joint of the container +0x54). Every
    // joint overrides it (the D6 joint's since C2.8 port-last Z9); the default is not reached.
    virtual void Solve() { DOTD_STUB_ONCE("KBase488C vt+0x60 Solve: this joint's slot"); }
    // vt+0x64 0x0021d358 KBase488C_vf64 (CKPxJoint.cpp): the limit planes' row.
    virtual void AddLimitRow(CKPxBody* body);

    uint32_t m_unk18;                 // +0x18 the flags (0x4000 visited by WakeBodyIsland, 0x2000 off)
    IKSerializable* m_unk1c;          // +0x1c a reference (the first body _maybe)
    IKSerializable* m_unk20;          // +0x20 a reference
    IKSerializable* m_unk24;          // +0x24 a reference
    IKSerializable* m_unk28;          // +0x28 a reference
    uint8_t m_unk2c;                  // +0x2c
    uint8_t m_pad2d[3];
    uint32_t m_unk30;                 // +0x30
    uint32_t m_unk34;                 // +0x34
    TVector<SAnchor, 1> m_anchors;    // +0x38
    CVector3 m_unk44;                 // +0x44 one 12-byte read (the limit planes' anchor point)
    uint32_t m_unk50;                 // +0x50
    uint32_t m_unk54;                 // +0x54
};
DOTD_ASSERT_SIZE(KBase488C, 0x58);
DOTD_ASSERT_OFFSET(KBase488C, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(KBase488C, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(KBase488C, m_anchors, 0x38);
DOTD_ASSERT_OFFSET(KBase488C, m_unk44, 0x44);
DOTD_ASSERT_OFFSET(KBase488C, m_unk54, 0x54);
