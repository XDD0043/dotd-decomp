// ISpawnNode.h - the spawn data of the spawn nodes (CSpawnNode +0x24, CSpawnAnimatedNode +0x64; 0x60 bytes,
// no vtable). Original unit: SpawnInstance.cpp (0xd4b30-0xd62b0; Ghidra SpawnNodeInfo / SpawnNodeData).
// XXL2: K/KModules/KGL/SceneGraph/ISpawnNode.h (m_pSpawnPool, m_rwBSphere, m_ui32SectorNum,
// m_pOriginalMatrix, m_ui32MatrixDataIndex); DotD reads a second sphere and six more words.
#pragma once
#include <cstdint>

#include "k2000/core/Layout.h"
#include "k2000/graphical/CSpawnManager.h"

class IKFile;
class IKSerializable;
class IKTime;
class CSGMovable;
class CNode;
class CKSpawnPoolParams;
class RenderQueue;
struct RwCamera;

class ISpawnNode {
public:
    ISpawnNode() {}  // nothing: CSpawnNode_Create only constructs the CNode part

    // 0x000d5198 (Ghidra SpawnNodeInfo_Load). Only K_LEVEL_PLATEFORMS reads.
    void Load(IKFile* file, int32_t type);
    // 0x000d5488 SpawnNodeData_PostLoad_maybe (SpawnInstance.cpp): `node` is the CSpawnNode as a CSGMovable.
    void PostLoad(int32_t type, CSGMovable* node);
    // 0x000d4ba8 SpawnNodeData_ClearReferences_maybe (CSpawnNode_Destroy): the original matrix destroyed.
    void ClearReferences();

    // ---- The spawn render chain (C2.8 port-final F05), called by CSpawnNode_Enqueue 0xd3960 and
    // CSpawnAnimatedNode_Enqueue 0xd33d8 with the node (`node`) this spawn data belongs to.
    // 0x000d5e20 SpawnInstance_CullAndUpdate_maybe: the sector's params / render param of the pool (none: 0); the
    // distance cull from the camera frame (+0x2c's) to the node, the frustum test of the world sphere (+0x14) with the
    // main camera; the grow scale (+0x5c: 1, or the sine of the fade) and the fade alpha; the shake transform; the
    // geometries' alpha (colour byte 3) and their alpha stage bit (0x800). 1 when the node is to be drawn.
    uint8_t CullAndUpdate(CNode* node, IKTime* clock);
    // 0x000d4df0 SpawnInstance_FindActorInBoundsAndStartShake_maybe: with a shake slot, the spawn manager's actor
    // (CSpawnManager entry, +0x30) inside the box (+0x38 max, +0x44 min) starts this slot's shake along its motion.
    uint8_t FindActorInBoundsAndStartShake(CKSpawnPoolParams* params);
    // 0x000d5a78 SpawnInstance_ApplyTransform_maybe: the original matrix (+0x2c) shaken by the slot's shake matrix and
    // its up axis scaled by +0x5c, as the node's local matrix; its LTM and world sphere updated.
    void ApplyTransform(CNode* node, CKSpawnPoolParams* params, IKTime* clock);
    // 0x000d4bf0 SpawnInstance_EnqueueGeometries_maybe: the geometries' world spheres (`sphere`: every atomic takes it as
    // its bounding sphere first), then each geometry enqueued (vt+0x58 with 0, stages, clock, camera, 0). The spawn data
    // itself is not read.
    void EnqueueGeometries(CNode* node, RenderQueue** stages, IKTime* clock, const float* sphere, RwCamera* camera);

    // The byte at +0x34 (PS3 big-endian: the top byte of m_unk34, as PostLoad clears it).
    uint8_t Byte34() const { return static_cast<uint8_t>(m_unk34 >> 24); }
    void SetByte34(uint8_t value) { m_unk34 = (m_unk34 & 0x00ffffffu) | (static_cast<uint32_t>(value) << 24); }
    // The box words +0x38.. as floats (0..2 the maximum x / y / z, 3..5 the minimum).
    float Bound(uint32_t index) const;

    IKSerializable* m_pSpawnPool;  // +0x00 CKSpawnPool (XXL2 order: read first)
    float m_unk04[3];              // +0x04 a second sphere's centre (_maybe), read after the first sphere
    float m_unk10;                 // +0x10 its radius (_maybe)
    float m_rwBSphereCenter[3];    // +0x14 XXL2 m_rwBSphere (RwSphere centre), read after the sector
    float m_rwBSphereRadius;       // +0x20 XXL2 m_rwBSphere radius
    uint32_t m_ui32SectorNum;      // +0x24 (XXL2 reads it right after the pool, as here)
    uint32_t m_unk28;              // +0x28 not read; PostLoad sets -1: the shake slot (CKSpawnPoolParams index)
    void* m_pOriginalMatrix;       // +0x2c Load sets 0 (XXL2 m_pOriginalMatrix, also cleared by its Load)
    // +0x30 not read; PostLoad clears it: the spawn manager's actor entry inside the box (FindActorInBoundsAndStartShake)
    CSpawnManager::SEntry* m_unk30;
    uint32_t m_unk34;              // +0x34 not read (PostLoad clears the byte at +0x34: the shake latch)
    uint32_t m_aUnk38[6];          // +0x38 one 0x18 read, each word swapped: the box (floats, see Bound)
    float m_aUnk50[4];             // +0x50 not read: the shake direction (PostLoad: +x), +0x5c the grow scale
};
DOTD_ASSERT_SIZE(ISpawnNode, 0x60);
DOTD_ASSERT_OFFSET(ISpawnNode, m_unk04, 0x04);
DOTD_ASSERT_OFFSET(ISpawnNode, m_rwBSphereCenter, 0x14);
DOTD_ASSERT_OFFSET(ISpawnNode, m_ui32SectorNum, 0x24);
DOTD_ASSERT_OFFSET(ISpawnNode, m_pOriginalMatrix, 0x2c);
DOTD_ASSERT_OFFSET(ISpawnNode, m_aUnk38, 0x38);
