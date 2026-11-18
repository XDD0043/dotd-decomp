// CKErrorTable.cpp - reconstructed original translation unit 0x1dbb0-0x1dea0 (GAME_TOC1, main_toc1), 8 functions, 5 live.
// Primary owner: CKErrorTable (not a registered class)
// Other owners: CreateErrorObjects (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x1dbb0  CKErrorTable_Construct_maybe
//   [ ] 0x1dbc8  CKErrorTable_GetErrorMessage  [dead]
//   [x] 0x1dc70  CKErrorTable_DestroyObjects_maybe
//   [x] 0x1dd30  CreateErrorObjects_maybe
//   [ ] 0x1de38  CKErrorTable_Destructor_2  [dead]
//   [ ] 0x1de48  CKErrorTable_Construct_2_maybe  [dead]
//   [x] 0x1de60  CKErrorTable_DeletingDestructor
//   [x] 0x1de90  CKErrorTable_Destructor
#include "k2000/misc/JobQueue.h"

#include "k2000/core/IKBaseClass.h"
#include "k2000/core/Stub.h"
#include "k2000/misc/ClassManager.h"
#include "k2000/misc/ClassRegistry.h"
#include "k2000/misc/Engine.h"

// 0x0001dbb0 CKErrorTable_Construct_maybe
CKErrorTable::CKErrorTable() : m_ppObjects(nullptr), m_ui32MaxId(0) {
    dotd::trace::Boot("create CKErrorTable");  // trace only (not in the original)
}

// 0x0001de90 CKErrorTable_Destructor (0x0001de60 the deleting one): the root vtable only.
CKErrorTable::~CKErrorTable() {}

// 0x0001dd30 CreateErrorObjects_maybe. Slot 0 is not written (new[] leaves it as the heap has it).
void CKErrorTable::CreateErrorObjects() {
    m_ui32MaxId = static_cast<uint32_t>(g_pEngine->m_classManager->GetMaxClassId(kCategoryError));
    m_ppObjects = new IKBaseClass*[(m_ui32MaxId + 1u) & 0x3fffffffu];  // OperatorNewArray(((max + 1) & 0x3fffffff) << 2)
    if (m_ui32MaxId == 0) return;
    uint32_t id = 1;
    do {
        while (ClassRegistry_GetClassDebugName(kCategoryError, id) == nullptr) {
            m_ppObjects[id] = nullptr;
            ++id;
            if (m_ui32MaxId < id) return;
        }
        m_ppObjects[id] = ClassRegistry_CreateObject(kCategoryError, id);
        ++id;
    } while (id <= m_ui32MaxId);
}

// 0x0001dc70 CKErrorTable_DestroyObjects_maybe: each object's deleting destructor (vt+0x04), not the class manager's.
void CKErrorTable::DestroyObjects() {
    if (m_ppObjects == nullptr) return;
    for (uint32_t id = 1; id <= m_ui32MaxId; ++id) {
        if (m_ppObjects[id] != nullptr) delete m_ppObjects[id];
    }
    delete[] m_ppObjects;  // OperatorDeleteArray
    m_ppObjects = nullptr;
}
