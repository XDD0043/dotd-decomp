// CKObjectManager.cpp - reconstructed original translation unit 0x5aeb88-0x5af6a8 (GAME_TOC2, main_toc2), 21 functions, 16 live.
// Primary class: CKObjectManager  key 0x538c  category Logic  size ?  vtable 0xb2ee80
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x5aeb88  CKObjectManager_Delete  (the registry factories: DOTD_DECLARE_FACTORIES)
//   [ ] 0x5aebd8  RegisterCKObjectManagerClass
//   [ ] 0x5aec50  _GLOBAL__I_5aec50
//   [ ] 0x5aec60  CKObjectManager_ClearReferences_2  [dead]
//   [ ] 0x5aeca0  CKObjectManager_Construct  [dead]
//   [ ] 0x5aecf0  CKObjectManager_Construct_2  [dead]
//   [x] 0x5aed40  CKObjectManager_DeleteArray  (the registry factories: DOTD_DECLARE_FACTORIES)
//   [ ] 0x5aede8  CKObjectManager_Save
//   [x] 0x5aeec0  CKObjectManager_Load
//   [x] 0x5aef90  CKObjectManager_RecursiveRegistration
//   [x] 0x5aeff8  CKObjectManager_Destroy
//   [x] 0x5af038  CKObjectManager_CreateArray  (the registry factories: DOTD_DECLARE_FACTORIES)
//   [x] 0x5af120  CKObjectManager_Create  (the registry factories: DOTD_DECLARE_FACTORIES)
//   [x] 0x5af188  CKObjectManager_InitRefArray_maybe
//   [x] 0x5af198  CKObjectManager_SaveRefArray_maybe
//   [x] 0x5af2b0  CKObjectManager_LoadRefArray_maybe
//   [ ] 0x5af400  CKObjectManager_GetRefByIndex_maybe  [dead]
//   [ ] 0x5af418  CKObjectManager_GetRefByIndex_2_maybe  [dead]
//   [x] 0x5af430  CKObjectManager_InitRefArray_2_maybe
//   [x] 0x5af440  CKObjectManager_SaveRefArray_2_maybe
//   [x] 0x5af558  CKObjectManager_LoadRefArray_2_maybe
//
//   [ ] 0x9cbf80  CKObjectManager_GetClassType  [inline]
//   [ ] 0x9cbf88  CKObjectManager_GetClassID  [inline]
//   [ ] 0x9cbf90  CKObjectManager_IsKindOfClass  [inline]
//   [ ] 0x9cbfb0  CKObjectManager_Destructor  [inline]
//   [ ] 0x9cbfc8  CKObjectManager_DeletingDestructor  [inline]
#include "k2000/logic/CKObjectManager.h"

#include "k2000/io/IKFile.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"

namespace {
void LoadRefs(IKFile* file, IKSerializable*** block, uint32_t* count) {
    ReadU32LE(file, count);
    if (*count == 0) {
        *block = nullptr;
        return;
    }
    *block = static_cast<IKSerializable**>(Mem_AllocAligned16(*count * static_cast<uint32_t>(sizeof(IKSerializable*))));
    IKFile_ReadObjectRefArray(file, *block, *count);  // the resolver's vt+0x28, else the raw ids
}

void SaveRefs(IKFile* file, IKSerializable** block, uint32_t count) {
    WriteU32LE(file, count);
    if (count == 0) return;
    if (file->m_pSavingInterfaces != nullptr) {
        file->m_pSavingInterfaces->WriteAsContiguousHandles(file, block, count);  // vt+0x4c
        return;
    }
    for (uint32_t i = 0; i < count; ++i) {  // the block's words as they are in memory (big-endian pointers)
        const uint32_t raw = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(block[i]));
        const uint8_t b[4] = {static_cast<uint8_t>(raw >> 24), static_cast<uint8_t>(raw >> 16),
                              static_cast<uint8_t>(raw >> 8), static_cast<uint8_t>(raw)};
        file->Write(b, 4);
    }
}
}  // namespace

// 0x005aeec0 CKObjectManager_Load
int32_t CKObjectManager::Load(IKFile* file, int32_t /*type*/) {
    IKFile_ReadRef(file, &m_unk04);
    LoadRefArray2(file);
    LoadRefArray(file);
    return 1;
}

// 0x005aef90 CKObjectManager_RecursiveRegistration
void CKObjectManager::RecursiveRegistration(int32_t type) {
    if (static_cast<uint32_t>(type - 4) > 3) g_pEngine->m_pSavingManager->RegisterSerializableObject(this, nullptr);
}

// 0x005aeff8 CKObjectManager_Destroy (the pointers kept, as in the original)
void CKObjectManager::Destroy() {
    Mem_FreeAligned16(m_apUnk08);
    Mem_FreeAligned16(m_apUnk10);
}

// 0x005af2b0 CKObjectManager_LoadRefArray_maybe / 0x005af558 CKObjectManager_LoadRefArray_2_maybe
void CKObjectManager::LoadRefArray(IKFile* file) { LoadRefs(file, &m_apUnk10, &m_ui32NbUnk10); }
void CKObjectManager::LoadRefArray2(IKFile* file) { LoadRefs(file, &m_apUnk08, &m_ui32NbUnk08); }

// 0x005af198 CKObjectManager_SaveRefArray_maybe / 0x005af440 CKObjectManager_SaveRefArray_2_maybe
void CKObjectManager::SaveRefArray(IKFile* file) { SaveRefs(file, m_apUnk10, m_ui32NbUnk10); }
void CKObjectManager::SaveRefArray2(IKFile* file) { SaveRefs(file, m_apUnk08, m_ui32NbUnk08); }
