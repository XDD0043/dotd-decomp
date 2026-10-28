// ISpawnNode.h - the spawn data of the spawn nodes (CSpawnNode +0x24, CSpawnAnimatedNode +0x64; 0x60 bytes,
// no vtable). Original unit: SpawnInstance.cpp (0xd4b30-0xd62b0; Ghidra SpawnNodeInfo / SpawnNodeData).
// XXL2: K/KModules/KGL/SceneGraph/ISpawnNode.h (m_pSpawnPool, m_rwBSphere, m_ui32SectorNum,
// m_pOriginalMatrix, m_ui32MatrixDataIndex); DotD reads a second sphere and six more words.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"

class IKFile;
class IKSerializable;
class CSGMovable;

class ISpawnNode {
public:
    ISpawnNode() {}  // nothing: CSpawnNode_Create only constructs the CNode part

    // 0x000d5198 (Ghidra SpawnNodeInfo_Load). Only K_LEVEL_PLATEFORMS reads.
    void Load(IKFile* file, int32_t type);
    // 0x000d5488 SpawnNodeData_PostLoad_maybe (SpawnInstance.cpp): `node` is the CSpawnNode as a CSGMovable.
    void PostLoad(int32_t type, CSGMovable* node);

    IKSerializable* m_pSpawnPool;  // +0x00 CKSpawnPool (XXL2 order: read first)
    float m_unk04[3];              // +0x04 a second sphere's centre (_maybe), read after the first sphere
    float m_unk10;                 // +0x10 its radius (_maybe)
    float m_rwBSphereCenter[3];    // +0x14 XXL2 m_rwBSphere (RwSphere centre), read after the sector
    float m_rwBSphereRadius;       // +0x20 XXL2 m_rwBSphere radius
    uint32_t m_ui32SectorNum;      // +0x24 (XXL2 reads it right after the pool, as here)
    uint32_t m_unk28;              // +0x28 not read
    void* m_pOriginalMatrix;       // +0x2c Load sets 0 (XXL2 m_pOriginalMatrix, also cleared by its Load)
    uint32_t m_unk30;              // +0x30 not read
    uint32_t m_unk34;              // +0x34 not read (PostLoad clears the byte at +0x34)
    uint32_t m_aUnk38[6];          // +0x38 one 0x18 read, each word swapped
    uint32_t m_aUnk50[4];          // +0x50 not read
};
DOTD_ASSERT_SIZE(ISpawnNode, 0x60);
DOTD_ASSERT_OFFSET(ISpawnNode, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(ISpawnNode, m_rwBSphereCenter, 0x14);
DOTD_ASSERT_OFFSET(ISpawnNode, m_ui32SectorNum, 0x24);
DOTD_ASSERT_OFFSET(ISpawnNode, m_pOriginalMatrix, 0x2c);
DOTD_ASSERT_OFFSET(ISpawnNode, m_aUnk38, 0x38);
