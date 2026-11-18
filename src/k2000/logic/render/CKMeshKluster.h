// CKMeshKluster.h - a sector's collision meshes (key 0x108c, vtable 0xb14138, size 0x3c). Original unit:
// CKMeshKluster.cpp. XXL2: K/KCore/Level/CKMeshKluster.h (IKSerializable + CSBaseNode<CKMeshKluster*>);
// its Load reads the same members in the same order.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"
#include "k2000/core/Layout.h"
#include "k2000/math/CBBox.h"

class IKTime;

class CKMeshKluster : public IKSerializable {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 0x42)
    int32_t IsKindOfClass(uint32_t key) override { return key == 0x108c || key == 0xc; }  // vt+0x08 0x994018
    DOTD_DECLARE_FACTORIES(CKMeshKluster)

    CKMeshKluster() { m_pNext = nullptr; }  // inlined in 0x00031618 CKMeshKluster_Create
    ~CKMeshKluster() override {}

    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x00031df8 CKMeshKluster_Load
    // vt+0x10 0x000314c8 CKMeshKluster_Destroy: the ground, wall, collision mesh and active ground arrays freed.
    void Destroy() override;

    // The sector's klusters are told by CKSector (vt+0x50 / vt+0x54 of CKSector, with the sector index).
    // vt+0x50 0x000324e0 CKMeshKluster_RebuildActiveGroundList_maybe (XXL2 PreSectorLoaded): the level's
    // ground-list-dirty bit set, then UpdateDynamicGrounds' work.
    virtual void SectorLoaded_maybe(int32_t sector);
    // vt+0x54 0x00031358 CKMeshKluster_vf54: no active ground.
    virtual void SectorUnload_maybe(int32_t /*sector*/) { m_ui16NbActiveGround = 0; }
    // vt+0x58 0x00032328 CKMeshKluster_UpdateDynamicGrounds (XXL2 Update -> UpdateCollisionMeshAndActiveGroundArray):
    // the update index toggled (0 <-> 1), every ground's Update (vt+0x5c: the moving grounds take their parents'
    // matrices), the active grounds (engine flag bit 0) listed again while the level's ground-list-dirty bit is set,
    // the list sorted by the bottom of the grounds' boxes (highest first; PS3 qsort), then the walls' Update.
    virtual void UpdateDynamicGrounds(IKTime* frameClock);

    CKMeshKluster* m_pNext;              // +0x04 XXL2 CSBaseNode<CKMeshKluster*>::m_pNext
    CBBox m_BBox;                        // +0x08
    IKSerializable** m_apGround;         // +0x20 CGround* (Mem_AllocAligned16)
    IKSerializable** m_apActiveGround;   // +0x24 CGround*; m_ui16NbGround slots, filled at run time
    IKSerializable** m_apWall;           // +0x28 CWall*
    IKSerializable** m_apCollisionMesh;  // +0x2c CCollisionMesh*
    uint8_t m_ui8UpdateIndex;            // +0x30 the Load sets 0
    uint8_t m_pad31;
    uint16_t m_ui16NbGround;             // +0x32
    uint16_t m_ui16NbActiveGround;       // +0x34 the Load sets 0
    uint16_t m_ui16NbWall;               // +0x36
    uint16_t m_ui16NbCollisionMesh;      // +0x38
    uint16_t m_pad3a;
};
DOTD_ASSERT_SIZE(CKMeshKluster, 0x3c);
DOTD_ASSERT_OFFSET(CKMeshKluster, m_pNext, 0x04);
DOTD_ASSERT_OFFSET(CKMeshKluster, m_BBox, 0x08);
DOTD_ASSERT_OFFSET(CKMeshKluster, m_apGround, 0x20);
DOTD_ASSERT_OFFSET(CKMeshKluster, m_apActiveGround, 0x24);
DOTD_ASSERT_OFFSET(CKMeshKluster, m_apWall, 0x28);
DOTD_ASSERT_OFFSET(CKMeshKluster, m_apCollisionMesh, 0x2c);
DOTD_ASSERT_OFFSET(CKMeshKluster, m_ui8UpdateIndex, 0x30);
DOTD_ASSERT_OFFSET(CKMeshKluster, m_ui16NbGround, 0x32);
DOTD_ASSERT_OFFSET(CKMeshKluster, m_ui16NbActiveGround, 0x34);
DOTD_ASSERT_OFFSET(CKMeshKluster, m_ui16NbWall, 0x36);
DOTD_ASSERT_OFFSET(CKMeshKluster, m_ui16NbCollisionMesh, 0x38);
