// CKQuadtreeAgent.h - the quadtree agents' unregistered abstract base (key 0x600c: GetClassType 0xc and GetClassID
// 0x180 at 0x995900 / 0x995908; vtable 0xb14e90, size 0x34). Original unit: CKQuadtreeAgent.cpp (0x47d78-0x48228).
// Its classes are CKQuadtreeAgentBranch (0x5e4c) and CKQuadtreeAgentLeaf (0x5e8c). No game file holds a quadtree
// (outputs/remake/kp3-class-usage.json). Names ours.
//
// C2.8 port-all P03 wrote this header for the two agents (their Load and vt+0x50 need it); the bodies are inline here
// and CKQuadtreeAgent.cpp's checklist (P10's file) is left as it was: ConstructBase 0x47dc8 (the constructor below),
// vf24 0x47de8 / vf28 0x47de0 (RecursiveRegistration / Save: the defaults), KStub_Nop_47df0 (Destroy: the default),
// Load 0x47df8, BaseDestructor 0x48150 and vf0 0x48138 (the destructor), the inline vf8 / vf14 / vf18.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/io/IKFile.h"

class CKQuadtreeAgent : public IKSerializable {
public:
    CKQuadtreeAgent() { m_unk04 = 0; }  // 0x00047dc8 CKQuadtreeAgent_600c_maybe_ConstructBase: the vtable, +0x04 = 0
    ~CKQuadtreeAgent() override {}      // 0x00048150 CKQuadtreeAgent_600c_maybe_BaseDestructor: vtable stores only

    int32_t IsKindOfClass(uint32_t key) override { return key == 0x600c || key == 0xc; }  // vt+0x08 0x995910
    int32_t GetClassType() override { return 0xc; }    // vt+0x14 0x995900
    int32_t GetClassID() override { return 0x180; }    // vt+0x18 0x995908
    // vt+0x2c 0x00047df8 CKQuadtreeAgent_600c_maybe_Load (level data only): the bounds (two words twice, each 8-byte
    // read swapped word by word), a byte, a reference, a word, three references and a byte.
    int32_t Load(IKFile* file, int32_t type) override {
        if (type != K_LEVEL_PLATEFORMS) return 1;
        ReadF32LE(file, &m_vMin[0]);
        ReadF32LE(file, &m_vMin[1]);
        ReadF32LE(file, &m_vMax[0]);
        ReadF32LE(file, &m_vMax[1]);
        ReadU8(file, &m_unk18);
        IKFile_ReadRef(file, &m_unk1c);
        ReadU32LE(file, &m_unk20);
        IKFile_ReadRef(file, &m_unk24);
        IKFile_ReadRef(file, &m_unk28);
        IKFile_ReadRef(file, &m_unk2c);
        ReadU8(file, &m_bDirty);
        return 1;
    }
    // vt+0x50 0x995888 (shared with CKQuadtreeAgentLeaf_vf50): the bounds are up to date (+0x30 = 0). The branch
    // recomputes them from its children first.
    virtual void UpdateBounds() { m_bDirty = 0; }
    // 0x00047d30 CKQuadtreeCell_InvalidateToRoot_maybe (unit Vt_2.cpp; it works on an agent): this agent and its parents
    // (+0x1c) up to the first one already dirty get their +0x28 cleared and the dirty byte set; when the root was
    // reached, the quadtree (the cell +0x24's +0x20) gets its bytes +0x61 / +0x60 set. Callers: CKQuadtreeAgentBranch's
    // dead AddChild / RemoveChild and CDynamicWall_UpdateQuadtreeBounds_maybe 0x1a6bc0 (CKSrvDetect.cpp, not ported).
    void InvalidateToRoot();

    uint32_t m_unk04;          // +0x04 the constructor: 0
    float m_vMin[2];           // +0x08 the bounds' minimum (x, z _maybe)
    float m_vMax[2];           // +0x10 the bounds' maximum
    uint8_t m_unk18;           // +0x18
    uint8_t m_pad19[3];
    IKSerializable* m_unk1c;   // +0x1c a reference
    uint32_t m_unk20;          // +0x20
    IKSerializable* m_unk24;   // +0x24 a reference
    IKSerializable* m_unk28;   // +0x28 a reference
    IKSerializable* m_unk2c;   // +0x2c a reference
    uint8_t m_bDirty;          // +0x30 the bounds need UpdateBounds (vt+0x50)
    uint8_t m_pad31[3];
};
DOTD_ASSERT_SIZE(CKQuadtreeAgent, 0x34);
DOTD_ASSERT_OFFSET(CKQuadtreeAgent, m_vMin, 0x08);
DOTD_ASSERT_OFFSET(CKQuadtreeAgent, m_vMax, 0x10);
DOTD_ASSERT_OFFSET(CKQuadtreeAgent, m_unk1c, 0x1c);
DOTD_ASSERT_OFFSET(CKQuadtreeAgent, m_unk2c, 0x2c);
DOTD_ASSERT_OFFSET(CKQuadtreeAgent, m_bDirty, 0x30);
