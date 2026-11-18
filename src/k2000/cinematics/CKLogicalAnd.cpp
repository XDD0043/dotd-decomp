// CKLogicalAnd.cpp - reconstructed original translation unit 0x16edf8-0x16f6e8 (GAME_TOC1, main_toc1), 16 functions, 15 live.
// Primary class: CKLogicalAnd  key 0x48  category CinematicNode  size 0x34  vtable 0xb1add8
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x16edf8  CKLogicalAnd_Delete
//   [x] 0x16ee48  CKLogicalAnd_Start
//   [x] 0x16ee50  CKLogicalAnd_Update
//   [ ] 0x16ee58  CKLogicalAnd_UpdateCheckComplete_maybe  [dead]
//   [ ] 0x16eeb8  RegisterCKLogicalAndClass
//   [ ] 0x16ef30  _GLOBAL__I_16ef30
//   [x] 0x16ef40  CKLogicalAnd_Complete
//   [x] 0x16f128  CKLogicalAnd_Load
//   [ ] 0x16f1e0  CKLogicalAnd_Save
//   [x] 0x16f208  CKLogicalAnd_RecursiveRegistration
//   [x] 0x16f298  CKLogicalAnd_DeleteArray
//   [x] 0x16f338  CKLogicalAnd_Create
//   [x] 0x16f3b0  CKLogicalAnd_Abort
//   [x] 0x16f3d0  CKLogicalAnd_Destroy
//   [x] 0x16f428  CKLogicalAnd_CreateArray
//   [x] 0x16f528  CKLogicalAnd_ActivateInput
//
//   [ ] 0x9a8f78  CKLogicalAnd_GetClassType  [inline]
//   [ ] 0x9a8f80  CKLogicalAnd_GetClassID  [inline]
//   [ ] 0x9a8f88  CKLogicalAnd_IsKindOfClass  [inline]
//   [ ] 0x9a8fc0  CKLogicalAnd_Destructor  [inline]
//   [ ] 0x9a9040  CKLogicalAnd_DeletingDestructor  [inline]
#include "k2000/cinematics/CKLogicalAnd.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/misc/Engine.h"

#include "k2000/logic/CKCinematicScene.h"
#include "k2000/memory/Mem.h"

// 0x0016f338 CKLogicalAnd_Create (the constructor inlined)
CKLogicalAnd::CKLogicalAnd() {
    m_apReceived = nullptr;
    m_receivedCapacity = 8;
    m_receivedCount = 0;
}

// 0x0016f128 CKLogicalAnd_Load
int32_t CKLogicalAnd::Load(IKFile* file, int32_t type) {
    BasicLoadCinematicElement(file, type);
    if (type == K_LEVEL_PLATEFORMS) {
        if (m_ui32IncomingNumber == 0) {
            m_receivedCapacity = 1;
            m_apReceived = static_cast<IKCinematicElement**>(Mem_AllocAligned16(static_cast<uint32_t>(sizeof(IKCinematicElement*))));
            return 1;
        }
        m_receivedCapacity = m_ui32IncomingNumber;
        m_apReceived = static_cast<IKCinematicElement**>(
            Mem_AllocAligned16(m_ui32IncomingNumber * static_cast<uint32_t>(sizeof(IKCinematicElement*))));
    }
    return 1;
}

// 0x0016ef40 CKLogicalAnd_Complete: the shared door completion, then the received list emptied.
void CKLogicalAnd::Complete() {
    CompleteDoor();
    m_receivedCount = 0;
}

// 0x0016f3b0 CKLogicalAnd_Abort
void CKLogicalAnd::Abort() {
    m_DataFlags &= 0xfffffffeu;
    m_ui32CurrentIncomingNumber = 0;
    m_receivedCount = 0;
}

// 0x0016f528 CKLogicalAnd_ActivateInput
void CKLogicalAnd::ActivateInput(IKCinematicElement* source) {
    CountIncomingActivation();
    if (source != nullptr) {
        bool known = false;
        for (uint32_t i = 0; i < m_receivedCount; ++i) {
            if (m_apReceived[i] == source) {
                known = true;
                break;
            }
        }
        if (!known) {
            if (m_receivedCapacity == m_receivedCount) {  // grows by 8 elements
                uint32_t capacity = m_receivedCapacity + 8;
                if (capacity == 0) capacity = 8;
                m_apReceived = static_cast<IKCinematicElement**>(
                    Mem_ReallocAligned16(m_apReceived, (capacity & 0x3fffffffu) << 2));
                m_receivedCapacity = capacity;
            }
            m_apReceived[m_receivedCount] = source;
            ++m_receivedCount;
        }
    }
    if (m_receivedCount != m_ui32IncomingNumber) return;
    Complete();  // vt+0x64
}

// 0x0016f208 CKLogicalAnd_RecursiveRegistration
void CKLogicalAnd::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3u) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
    IKLogicalDoor::RecursiveRegistration(type);  // 0x0018fc20
}

// 0x0016f3d0 CKLogicalAnd_Destroy
void CKLogicalAnd::Destroy() {
    if (m_apReceived != nullptr) {
        Mem_FreeAligned16(m_apReceived);
        m_apReceived = nullptr;
    }
    m_receivedCount = 0;
    m_apReceived = nullptr;
}
