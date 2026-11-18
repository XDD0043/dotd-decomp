// CKAttachObjectsCinematicBloc.cpp - reconstructed original translation unit 0x172ba8-0x174a58 (GAME_TOC1, main_toc1), 19 functions, 18 live.
// Primary class: CKAttachObjectsCinematicBloc  key 0x248  category CinematicNode  size 0x84  vtable 0xb1b008
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x172ba8  CKAttachObjectsCinematicBloc_Delete
//   [ ] 0x172bf8  RegisterCKAttachObjectsCinematicBlocClass
//   [ ] 0x172c70  _GLOBAL__I_172c70
//   [x] 0x172c80  CKAttachObjectsCinematicBloc_Update
//   [ ] 0x172ca8  CKAttachObjectsCinematicBloc_CreateMatrix_maybe  [dead]
//   [x] 0x172d20  CKAttachObjectsCinematicBloc_RecursiveRegistration
//   [x] 0x172e40  CKAttachObjectsCinematicBloc_DeleteArray
//   [x] 0x172ee8  CKAttachObjectsCinematicBloc_Create
//   [x] 0x172f40  CKAttachObjectsCinematicBloc_Destroy
//   [x] 0x172f80  CKAttachObjectsCinematicBloc_CreateArray
//   [x] 0x173038  CKAttachObjectsCinematicBloc_AttachToParent_maybe
//   [x] 0x1731f8  CKAttachObjectsCinematicBloc_ApplyAttachment_maybe
//   [x] 0x173488  CKAttachObjectsCinematicBloc_RestoreObject_maybe
//   [x] 0x173720  CKAttachObjectsCinematicBloc_Abort
//   [x] 0x1737e8  CKAttachObjectsCinematicBloc_Stop
//   [x] 0x173a80  CKAttachObjectsCinematicBloc_Start
//   [x] 0x173f38  CKAttachObjectsCinematicBloc_Load
//   [ ] 0x1743a8  CKAttachObjectsCinematicBloc_Save
//   [x] 0x174880  CKAttachObjectsCinematicBloc_Complete
//
//   [ ] 0x9a9308  CKAttachObjectsCinematicBloc_IsKindOfClass  [inline]
//   [ ] 0x9a9340  CKAttachObjectsCinematicBloc_GetClassType  [inline]
//   [ ] 0x9a9348  CKAttachObjectsCinematicBloc_GetClassID  [inline]
//   [ ] 0x9a9350  CKAttachObjectsCinematicBloc_Destructor  [inline]
//   [ ] 0x9a9370  CKAttachObjectsCinematicBloc_DeletingDestructor  [inline]
#include "k2000/cinematics/CKAttachObjectsCinematicBloc.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/scenegraph/CSGLeaf.h"

#include <cstring>

#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/hooks/IKHook.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCinematicSceneData.h"
#include "k2000/logic/CKLevel.h"
#include "k2000/logic/CKSector.h"
#include "k2000/logic/CSGHotSpot.h"
#include "k2000/misc/Engine.h"
#include "k2000/misc/Mat4.h"
#include "k2000/scenegraph/CAnimatedNode.h"
#include "k2000/scenegraph/CSGBranch.h"
#include "k2000/scenegraph/CSGSectorRoot.h"

// 0x00173f38 CKAttachObjectsCinematicBloc_Load
int32_t CKAttachObjectsCinematicBloc::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        IKFile_ReadRef(file, &m_pLeaf);
        IKFile_ReadRef(file, &m_pLeafParent);
        IKFile_ReadRef(file, &m_pAttachLeaf);
        ReadU8(file, &m_bAttachToBone);
        ReadU32LE(file, &m_ui32BoneIndex);
        // Two 0xc-byte reads, each word swapped.
        uint32_t w[3];
        ReadU32LEWords(file, w, 3);
        std::memcpy(&m_v3Pos, w, 0xc);
        ReadU32LEWords(file, w, 3);
        std::memcpy(&m_v3OldPos, w, 0xc);
        ReadU8(file, &m_bRestorePos);
        ReadU8(file, &m_bAttachToHotSpot);
        CMatrix34* matrix = RwMatrixCreate_Thunk();
        m_pMatrixToApply = matrix;
        CMatrix34_LoadMatrix(matrix, file);
        IKFile_ReadRef(file, &m_pHotSpot);
        ReadU8(file, &m_unk78);
    }
    // 0x17426c: a fresh identity matrix, whatever the type.
    CMatrix34* old = RwMatrixCreate_Thunk();
    m_pOldMatrix = old;
    old->m_ui32Flags = 0x20003u;
    old->m_right.x = 1.0f;  // TOC 0xc12654
    old->m_pos.x = 0.0f;
    old->m_at.z = 1.0f;
    old->m_up.y = 1.0f;
    old->m_up.x = 0.0f;
    old->m_right.z = 0.0f;
    old->m_right.y = 0.0f;
    old->m_at.y = 0.0f;
    old->m_at.x = 0.0f;
    old->m_up.z = 0.0f;
    old->m_pos.z = 0.0f;
    old->m_pos.y = 0.0f;
    return 1;
}

namespace {
// The leaf's modelling position set and the frame marked (the matrix flags' bit 17 cleared), as the blocs inline it.
void SetLeafPosition(CSGLeaf* leaf, const CVector3& pos) {
    RwFrame* frame = leaf->m_pRwFrame;
    frame->modelling.pos.z = pos.z;
    frame->modelling.pos.x = pos.x;
    frame->modelling.pos.y = pos.y;
    frame->modelling.flags &= 0xfffdffffu;
    RwFrame_MarkDirty(frame);
}

// The leaf leaves its parent (vt+0x78); the parent and the leaf's position are kept for AttachToParent.
void DetachFromOldParent(CKAttachObjectsCinematicBloc* bloc, CSGLeaf* leaf) {
    if (leaf->m_pParent == nullptr) return;
    bloc->m_pLeafParent = leaf->m_pParent;
    leaf->m_pParent->RemoveChild(leaf);  // vt+0x78
    const RwFrame* frame = leaf->m_pRwFrame;
    bloc->m_v3OldPos.x = frame->modelling.pos.x;
    bloc->m_v3OldPos.z = frame->modelling.pos.z;
    bloc->m_v3OldPos.y = frame->modelling.pos.y;
}
}  // namespace

bool CKAttachObjectsCinematicBloc::HasTarget() const { return m_pElementData != nullptr || m_pAttachLeaf != nullptr; }

// No test of the hook: the original reads the scene data's hook's node (+0x04, +0x1c) as it is.
CSGBranch* CKAttachObjectsCinematicBloc::Target() const {
    if (m_pElementData == nullptr) return static_cast<CSGBranch*>(static_cast<CSGLeaf*>(m_pAttachLeaf));
    IKHook* hook = static_cast<IKHook*>(static_cast<CKCinematicSceneData*>(m_pElementData)->m_pHook);
    return static_cast<CSGBranch*>(hook->m_pKGLObject);
}

// 0x00173a80 CKAttachObjectsCinematicBloc_Start
void CKAttachObjectsCinematicBloc::Start() {
    StartCommon();
    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pLeaf);
    int32_t sector = -2;
    if (leaf != nullptr) sector = static_cast<int32_t>(leaf->GetSectorIndex());  // vt+0x6c
    m_i32SectorIndex = sector;
    if (leaf != nullptr) {
        std::memcpy(m_pOldMatrix, &leaf->m_pRwFrame->modelling, 0x40);
        m_ui32OldBone = leaf->m_ui8BoneParent;
    }
    if (m_bAttachToHotSpot != 0 && HasTarget() && m_pHotSpot != nullptr) {
        ApplyAttachment(1);
        return;
    }
    if (m_bAttachToBone != 0) {
        if (!HasTarget()) {
            Complete();  // vt+0x64
            return;
        }
        if (leaf != nullptr) {
            RestoreObject(1);
            return;
        }
    }
    if (HasTarget() && leaf != nullptr) {
        ApplyAttachment(1);
        return;
    }
    Complete();  // vt+0x64
}

// 0x00174880 CKAttachObjectsCinematicBloc_Complete
void CKAttachObjectsCinematicBloc::Complete() { CompleteBloc(); }

// 0x00172c80 CKAttachObjectsCinematicBloc_Update
void CKAttachObjectsCinematicBloc::Update(IKTime* /*time*/) { CheckSekensStop(); }

// 0x00173720 CKAttachObjectsCinematicBloc_Abort
void CKAttachObjectsCinematicBloc::Abort() {
    m_DataFlags &= 0xfffffffeu;
    if (m_bAttachToHotSpot != 0 && HasTarget() && m_pHotSpot != nullptr) {
        ApplyAttachment(0);
        return;
    }
    if (m_bAttachToBone != 0) {
        if (!HasTarget()) return;
        if (m_pLeaf != nullptr) {
            RestoreObject(0);
            return;
        }
    }
    if (!HasTarget()) return;
    if (m_pLeaf != nullptr) ApplyAttachment(0);
}

// 0x001737e8 CKAttachObjectsCinematicBloc_Stop
void CKAttachObjectsCinematicBloc::Stop() {
    if (m_bAttachToHotSpot != 0 && HasTarget() && m_pHotSpot != nullptr) {
        ApplyAttachment(0);
    } else if (m_bAttachToBone != 0 && HasTarget() && m_pLeaf != nullptr) {
        RestoreObject(0);
    } else if (HasTarget() && m_pLeaf != nullptr) {
        ApplyAttachment(0);
    }
    CompleteBloc();
    Complete();  // vt+0x64
}

// 0x001731f8 CKAttachObjectsCinematicBloc_ApplyAttachment_maybe
void CKAttachObjectsCinematicBloc::ApplyAttachment(int32_t attach) {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pLeaf);
    CSGHotSpot* hotSpot = static_cast<CSGHotSpot*>(m_pHotSpot);
    if (attach != 0) {
        DetachFromOldParent(this, leaf);
        if (HasTarget() && m_bAttachToHotSpot == 0) {
            Target()->AddChild(leaf);  // vt+0x70
            if (m_unk78 == 0) static_cast<CSGMovable*>(leaf)->SetIdentity();  // 0x000d08f0
            SetLeafPosition(leaf, m_v3Pos);
            return;
        }
        hotSpot->AttachVolume(leaf);  // 0x000ce2b8
        return;
    }
    if (!HasTarget() || m_bAttachToHotSpot != 0) {
        if (leaf->m_pParent == hotSpot->m_pParent) hotSpot->DetachVolume(leaf);  // 0x000ce690
    } else {
        CSGBranch* target = Target();
        if (target == leaf->m_pParent) target->RemoveChild(leaf);  // vt+0x78
    }
    AttachToParent();
}

// 0x00173038 CKAttachObjectsCinematicBloc_AttachToParent_maybe
void CKAttachObjectsCinematicBloc::AttachToParent() {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pLeaf);
    if (leaf->m_pParent != nullptr) return;
    CSGBranch* parent = static_cast<CSGBranch*>(static_cast<CSGLeaf*>(m_pLeafParent));
    bool onBone = false;
    if (parent == nullptr) {
        if (m_i32SectorIndex == -2) {
            parent = static_cast<CSGBranch*>(static_cast<CSGLeaf*>(g_pEngine->m_dynamicSceneRoot));  // engine +0x14
        } else {
            CKSector* sector = static_cast<CKSector*>(g_pEngine->m_level->m_vpSectors.m_pBlock[m_i32SectorIndex]);
            parent = sector->m_pSectorRoot;  // +0x08
        }
    } else if (m_ui32OldBone != 0xff && parent->IsKindOfClass(0x54b) != 0) {  // a CAnimatedNode
        static_cast<CAnimatedNode*>(parent)->AttachChildToBone(m_ui32OldBone, leaf);  // 0x000ca760
        onBone = true;
    }
    if (!onBone) parent->AddChildKeepWorldTransform(leaf);  // vt+0x74
    if (m_bRestorePos == 0) return;
    if (m_pOldMatrix != nullptr) {
        static_cast<CSGMovable*>(leaf)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pOldMatrix));  // 0x000d0be8
    }
    SetLeafPosition(leaf, m_v3OldPos);
}

// 0x00173488 CKAttachObjectsCinematicBloc_RestoreObject_maybe
void CKAttachObjectsCinematicBloc::RestoreObject(int32_t attach) {
    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pLeaf);
    if (attach != 0) {
        DetachFromOldParent(this, leaf);
        static_cast<CAnimatedNode*>(Target())->AttachChildToGroup(static_cast<uint8_t>(m_ui32BoneIndex), leaf);  // 0x000c9218
        SetLeafPosition(leaf, m_v3Pos);
        static_cast<CSGMovable*>(leaf)->SetLocalMatrix(reinterpret_cast<const RwMatrix*>(m_pMatrixToApply));  // 0x000d0be8
        return;
    }
    if (m_pElementData != nullptr) {
        CAnimatedNode* actor = static_cast<CAnimatedNode*>(Target());
        // BUG(original)_maybe: the leaf is compared with the actor's parent (+0x0c), not the leaf's parent with the actor.
        if (leaf == static_cast<CSGLeaf*>(actor->m_pParent)) {
            actor->DetachChild(leaf);  // 0x000c9150
            AttachToParent();
            return;
        }
    }
    CSGBranch* parent = leaf->m_pParent;
    if (static_cast<CSGBranch*>(static_cast<CSGLeaf*>(m_pAttachLeaf)) == parent) {
        static_cast<CAnimatedNode*>(parent)->DetachChild(leaf);  // 0x000c9150
    } else if (parent != nullptr) {
        parent->RemoveChild(leaf);  // vt+0x78
    }
    AttachToParent();
}

// 0x00172f40 CKAttachObjectsCinematicBloc_Destroy
void CKAttachObjectsCinematicBloc::Destroy() {
    RwMatrixDestroy_Thunk(m_pOldMatrix);      // 0x0023f968
    RwMatrixDestroy_Thunk(m_pMatrixToApply);
}

// 0x00172d20 CKAttachObjectsCinematicBloc_RecursiveRegistration
void CKAttachObjectsCinematicBloc::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKCinematicBloc::RecursiveRegistration(type);  // 0x0018e8d8
    CSGLeaf* leaf = static_cast<CSGLeaf*>(m_pLeaf);
    if (leaf != nullptr && leaf->m_pParent == nullptr) leaf->RecursiveRegistration(type);  // vt+0x24
    if (m_pHotSpot != nullptr) m_pHotSpot->RecursiveRegistration(type);
}
