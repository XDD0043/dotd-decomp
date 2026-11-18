// CKPxMesh.h - a physics collision mesh (key 0x470c, vtable 0xb20310, size 0x2c). Original unit: CKPxMesh.cpp
// (0x22c4b8-0x22cba8). Base: KBase468C (the physics elements). No game file holds one
// (outputs/remake/kp3-class-usage.json). Names ours.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/misc/KBase468C.h"

class CKPxMesh : public KBase468C {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x11c)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x470c || key == 0x468c || key == 0xc; }
    DOTD_DECLARE_FACTORIES(CKPxMesh)

    CKPxMesh() {}  // 0x0022c6f8 CKPxMesh_Construct: the base, then the vtable
    ~CKPxMesh() override {}
    // vt+0x2c 0x0022c808 CKPxMesh_Load: the base's, then (level data only) a byte, the vertex count and its vertices
    // (3 words each, swapped), the index count and its records (4 halfwords each, swapped).
    int32_t Load(IKFile* file, int32_t type) override;
    // vt+0x10 0x0022c5e0 CKPxMesh_Destroy: both blocks freed (the pointers kept), then the base's (nothing).
    void Destroy() override;
    // vt+0x24 0x0022c5b8 CKPxMesh_RecursiveRegistration: the base's vf24 (returns 1, registers nothing).

    uint8_t m_unk18;         // +0x18 read raw
    uint8_t m_pad19[3];
    float* m_pVertices;      // +0x1c Mem_AllocAligned16(count x 0xc); null without vertices
    uint16_t m_ui16NbVertex;  // +0x20
    uint8_t m_pad22[2];
    uint16_t* m_pRecords;    // +0x24 Mem_AllocAligned16(count x 8): 4 halfwords each (a face, _maybe)
    uint16_t m_ui16NbRecord;  // +0x28
    uint8_t m_pad2a[2];
};
DOTD_ASSERT_SIZE(CKPxMesh, 0x2c);
DOTD_ASSERT_OFFSET(CKPxMesh, m_unk18, 0x18);
DOTD_ASSERT_OFFSET(CKPxMesh, m_pVertices, 0x1c);
DOTD_ASSERT_OFFSET(CKPxMesh, m_ui16NbVertex, 0x20);
DOTD_ASSERT_OFFSET(CKPxMesh, m_pRecords, 0x24);
DOTD_ASSERT_OFFSET(CKPxMesh, m_ui16NbRecord, 0x28);
