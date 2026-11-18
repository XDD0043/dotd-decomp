// Reconstructed original translation unit: 0x2bcd8-0x2cc38 (GAME_TOC1, main_toc1), 19 functions, 14 live.
// Primary class: CKSavingManager  key 0x18c  category Logic  size 0x24  vtable 0xb13e78
// Other owners: Stream (3)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x2bcd8  RegisterCKSavingManagerClass
//   [ ] 0x2bd50  _GLOBAL__I_2bd50
//   [x] 0x2bd60  CKSavingManager_GetObjectRefId
//   [x] 0x2bdb8  CKSavingManager_RegisterSerializableObject
//   [ ] 0x2bec0  CKSavingManager_SortObjectsByClassKey_maybe  [dead]
//   [x] 0x2bef8  CKSavingManager_DeleteArray
//   [x] 0x2bfa0  CKSavingManager_Create
//   [x] 0x2c000  CKSavingManager_CreateArray
//   [ ] 0x2c0c8  Stream_ReadBytesRaw_2  [dead]
//   [ ] 0x2c118  Stream_ReadU32ArraySwapped_3  [dead]
//   [ ] 0x2c1b0  Stream_ReadU32ArraySwapped_4  [dead]
//   [x] 0x2c248  CKSavingManager_WriteObjectList
//   [x] 0x2c538  CKSavingManager_SaveObjects
//   [x] 0x2c6c8  CKSavingManager_DeletingDestructor
//   [x] 0x2c748  CKSavingManager_WriteAsHandle
//   [x] 0x2c890  CKSavingManager_WriteAsContiguousHandles
//   [x] 0x2ca18  CKSavingManager_Destructor
//   [ ] 0x2ca80  CKSavingManager_Destructor_2  [dead]
//   [x] 0x2cae8  CKSavingManager_WriteTexture  (no caller ported yet (the save flow, save-menu))
//
//   [x] 0x993be8  CKSavingManager_vf30  [inline]
//   [x] 0x993bf0  CKSavingManager_vf34  [inline]
//   [ ] 0x993bf8  KStub_Return1_993bf8  [inline]
//   [ ] 0x993c00  KStub_Return0_993c00  [inline]
//   [ ] 0x993c08  CKSavingManager_GetClassID  [inline]
//   [ ] 0x993c10  CKSavingManager_GetClassType  [inline]
//   [x] 0x993c18  CKSavingManager_KUInitialize  [inline]
//   [x] 0x993c20  CKSavingManager_KUDestroy  [inline]
//   [ ] 0x993c60  CKSavingManager_Destroy  [inline]
//   [x] 0x993c68  CKSavingManager_vf40  [inline]
//   [x] 0x993c70  CKSavingManager_vf44  [inline]
//   [x] 0x993c78  CKSavingManager_vf28  [inline]
//   [x] 0x993c80  CKSavingManager_vf2C  [inline]
//   [x] 0x993c90  CKSavingManager_vf3C  [inline]
//   [x] 0x993cc0  CKSavingManager_vf38  [inline]
//   [ ] 0x993cf0  KBase97E_IsKindOf  [inline]
//   [ ] 0x993d08  CKSavingManager_IsKindOfClass  [inline]
//   [ ] 0x993d20  KBase97E_DeletingDestructor  [inline]
//   [ ] 0x993d50  KBase97E_Destructor  [inline]
#include "k2000/logic/CKSavingManager.h"

#include "k2000/memory/Mem.h"

// 0x0002bfa0 CKSavingManager_Create (the constructor inlined), in its store order.
CKSavingManager::CKSavingManager() {
    m_vMemCardRegistred.m_pBlock = nullptr;
    m_vMemCardRegistred.m_ui32NbElt = 10;
    m_vMemCardRegistred.m_ui32NbUsedElt = 0;
    m_eCurrentSerializationType = 8;
    m_i8NbStream = 0;
    m_eTargetPlateform = 8;
}
// 0x0002ca18 CKSavingManager_Destructor (0x0002c6c8 CKSavingManager_DeletingDestructor: the same, then the delete): the
// registered-object vector's block freed, its length and block cleared.
CKSavingManager::~CKSavingManager() {
    if (m_vMemCardRegistred.m_pBlock != nullptr) Mem_FreeAligned16(m_vMemCardRegistred.m_pBlock);
    m_vMemCardRegistred.m_ui32NbUsedElt = 0;
    m_vMemCardRegistred.m_pBlock = nullptr;
}
IKBaseClass* CKSavingManager::Create() { return new CKSavingManager(); }
void CKSavingManager::Delete(IKBaseClass* object) { delete object; }

// 0x0002bdb8 CKSavingManager_RegisterSerializableObject
void CKSavingManager::RegisterSerializableObject(IKSerializable* object, IKSerializable* /*owner*/) {
    if (static_cast<uint32_t>(m_eCurrentSerializationType - 4) > 3) return;
    TVector<IKSerializable*, 10>& v = m_vMemCardRegistred;
    for (uint32_t i = 0; i < v.m_ui32NbUsedElt; ++i) {
        if (v.m_pBlock[i] == object) return;
    }
    if (v.m_ui32NbElt == v.m_ui32NbUsedElt) {
        uint32_t capacity = v.m_ui32NbElt + 10;
        if (capacity == 0) capacity = 10;
        v.m_pBlock = static_cast<IKSerializable**>(
            Mem_ReallocAligned16(v.m_pBlock, capacity * static_cast<uint32_t>(sizeof(IKSerializable*))));  // 0x00053190
        v.m_ui32NbElt = capacity;
    }
    v.m_pBlock[v.m_ui32NbUsedElt] = object;
    v.m_ui32NbUsedElt = v.m_ui32NbUsedElt + 1;
}

// ==== C2.8 save-menu: the save writers ===========================================================================
#include "k2000/core/IKSerializable.h"
#include "k2000/io/IKFile.h"
#include "k2000/logic/CKCoreManager.h"
#include "k2000/logic/io/CKLoadingManager.h"
#include "k2000/misc/CKGameLoop.h"
#include "k2000/misc/Engine.h"
#include <cstring>

#include "Renderware/rwcore/RwTexture.h"

namespace {
// 0x00c51344 (+0x01 the depth byte, +0x04 the positions): WriteObjectList's stack of the end-offset words' positions.
// The word written first as the placeholder is the stack slot above the one just pushed (a stale value from an
// earlier object, overwritten once the object's end is known).
int8_t s_i8PositionDepth = 0;
uint32_t s_aPositions[0x100] = {};
}  // namespace

// 0x0002bd60 CKSavingManager_GetObjectRefId
int32_t CKSavingManager::GetObjectRefId(IKSerializable* object) {
    if (object == nullptr || static_cast<uint32_t>(m_eCurrentSerializationType - 4) >= 4u) return -1;
    return g_pEngine->m_objectDatabase->GetObjectRefId(object);  // 0x00028820
}

// 0x0002c748 CKSavingManager_WriteAsHandle
uint32_t CKSavingManager::WriteAsHandle(IKFile* file, IKSerializable* object) {
    int32_t id = -1;
    if (object != nullptr && static_cast<uint32_t>(m_eCurrentSerializationType - 4) <= 3u) {
        id = g_pEngine->m_objectDatabase->GetObjectRefId(object);  // 0x00028820 (engine +0x4c)
    }
    const uint32_t written = WriteU32LE(file, static_cast<uint32_t>(id));
    if (id != -3) return written;
    Uuid_Write(object->GetGuid(), file);  // vt+0x44, 0x00245c98
    return written;
}

// 0x0002c248 CKSavingManager_WriteObjectList
int32_t CKSavingManager::WriteObjectList(IKFile* file, IKSerializable** objects, uint32_t count, int32_t type) {
    WriteU32LE(file, count);
    for (uint32_t i = 0; i < count; ++i) {
        IKSerializable* object = objects[i];
        if (file->m_pSavingInterfaces != nullptr) {
            file->m_pSavingInterfaces->WriteAsHandle(file, object);  // vt+0x48
        } else {
            // The pointer's 4 bytes as they are (the PS3's big-endian word; the remake writes its low word).
            const uint32_t raw = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(object));
            const uint8_t b[4] = {static_cast<uint8_t>(raw >> 24), static_cast<uint8_t>(raw >> 16),
                                  static_cast<uint8_t>(raw >> 8), static_cast<uint8_t>(raw)};
            file->Write(b, 4);
        }
        const uint8_t depth = static_cast<uint8_t>(s_i8PositionDepth);
        const uint32_t position = file->Tell();  // vt+0x44
        s_i8PositionDepth = static_cast<int8_t>(depth + 1);
        s_aPositions[depth] = position;
        WriteU32LE(file, s_aPositions[static_cast<uint8_t>(depth + 1)]);  // the placeholder
        object->Save(file, type);  // vt+0x28
        const uint32_t end = file->Tell();
        s_i8PositionDepth = static_cast<int8_t>(s_i8PositionDepth - 1);
        file->Seek(static_cast<int32_t>(s_aPositions[static_cast<uint8_t>(s_i8PositionDepth)]), 0);  // vt+0x2c
        WriteU32LE(file, end);
        file->Seek(static_cast<int32_t>(end), 0);
    }
    return 1;
}

// 0x0002c538 CKSavingManager_SaveObjects. `size` (the save file's) is not read. The list's used count is not reset at the
// start (the previous save's end cleared it).
int32_t CKSavingManager::SaveObjects(IKFile* file, int32_t type, uint32_t /*size*/) {
    m_eCurrentSerializationType = type;
    m_vMemCardRegistred.m_ui32NbElt = 10;
    m_vMemCardRegistred.m_pBlock = static_cast<IKSerializable**>(Mem_AllocAligned16(0x28));  // 0x00053198
    g_pEngine->m_gameLoop->RecursiveRegistration(type);    // engine +0x34, vt+0x24
    g_pEngine->m_coreManager->RecursiveRegistration(type);  // engine +0x2c, vt+0x24
    file->Tell();  // vt+0x44 (the value is not used)
    WriteObjectList(file, m_vMemCardRegistred.m_pBlock, m_vMemCardRegistred.m_ui32NbUsedElt, type);
    file->Tell();
    if (m_vMemCardRegistred.m_pBlock != nullptr) {
        Mem_FreeAligned16(m_vMemCardRegistred.m_pBlock);  // 0x00052fb8
        m_vMemCardRegistred.m_pBlock = nullptr;
    }
    m_vMemCardRegistred.m_ui32NbUsedElt = 0;
    m_vMemCardRegistred.m_pBlock = nullptr;
    m_eCurrentSerializationType = 8;
    m_eTargetPlateform = 8;
    return 1;
}

// 0x0002c000 CKSavingManager_CreateArray
IKBaseClass* CKSavingManager::CreateArray(uint32_t count, uint16_t* elementSize) {
    if (elementSize != nullptr) *elementSize = static_cast<uint16_t>(sizeof(CKSavingManager));
    return new CKSavingManager[count];
}

// 0x0002bef8 CKSavingManager_DeleteArray
void CKSavingManager::DeleteArray(IKBaseClass* first) { delete[] static_cast<CKSavingManager*>(first); }

// 0x0002c890 CKSavingManager_WriteAsContiguousHandles
uint32_t CKSavingManager::WriteAsContiguousHandles(IKFile* file, IKSerializable* const* objects, uint32_t count) {
    uint32_t total = 0;
    for (uint32_t i = 0; i != count; ++i) {
        IKSerializable* object = objects[i];
        int32_t id = -1;
        if (object != nullptr && static_cast<uint32_t>(m_eCurrentSerializationType - 4) < 4u) {
            id = g_pEngine->m_objectDatabase->GetObjectRefId(object);  // 0x00028820
        }
        total += WriteU32LE(file, static_cast<uint32_t>(id));
        if (id == -3) Uuid_Write(object->GetGuid(), file);  // vt+0x44, 0x00245c98
    }
    return total;
}

// 0x0002cae8 CKSavingManager_WriteTexture
uint32_t CKSavingManager::WriteTexture(IKFile* file, const RwTexture* texture) {
    const char* name = "";  // TOC -0x7a84
    uint16_t length = 0;
    if (texture != nullptr) {
        name = texture->name;
        length = static_cast<uint16_t>(std::strlen(name));  // 0x0098d2f0
    }
    const uint8_t le[2] = {static_cast<uint8_t>(length), static_cast<uint8_t>(length >> 8)};
    const uint32_t first = file->Write(le, 2);  // vt+0x20
    return file->Write(name, static_cast<uint32_t>(static_cast<int16_t>(length))) + first;  // extsh
}
