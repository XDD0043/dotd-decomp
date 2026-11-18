// KMemBuffer.cpp - reconstructed original translation unit 0x48350-0x497a0 (GAME_TOC1, main_toc1), 30 functions, 19 live.
// Primary owner: KMemBuffer (not a registered class)
// Other owners: KFileSystem (10), CopyString4Offset (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x48350  KMemBuffer_Construct_2  [dead]
//   [x] 0x48370  KMemBuffer_Construct
//   [ ] 0x48390  KMemBuffer_AttachExternalBuffer_maybe  [dead]
//   [x] 0x483b8  KMemBuffer_Free
//   [x] 0x48430  KMemBuffer_Init
//   [x] 0x484a0  KMemBuffer_EnsureCapacity_maybe
//   [x] 0x48550  KMemBuffer_DeletingDestructor
//   [x] 0x485f8  KMemBuffer_Destructor
//   [ ] 0x48678  KMemBuffer_Destructor_2  [dead]
//   [ ] 0x486f8  KMemBuffer_Equals  [dead]
//   [ ] 0x48768  KMemBuffer_Create  [dead]
//   [ ] 0x487b8  KMemBuffer_WriteDataToStream_maybe  [dead]
//   [ ] 0x48918  KMemBuffer_WriteToStream_maybe  [dead]
//   [ ] 0x489c8  KMemBuffer_CopyFrom_maybe  [dead]
//   [ ] 0x48ac0  KMemBuffer_ReadFromStream_maybe  [dead: no pointer to its descriptor; its only call is from the dead 0x48dc0 KMemBuffer_CreateFromStream_maybe]
//   [ ] 0x48dc0  KMemBuffer_CreateFromStream_maybe  [dead: no pointer to its descriptor 0xb3de58, no call]
//   [x] 0x48ec0  KMemBuffer_Resize
//   [ ] 0x48f78  FUN_00048f78  [dead]
//   [ ] 0x48f88  KFileSystem_GetSaveDevice  [platform]  (the save device (+0x304): platform by design (the PS3 save data stack; the callers read KFileSystem::m_saveDevice))
//   [ ] 0x48f90  KFileSystem_GetPathBuf4_maybe  [dead]
//   [x] 0x48fa0  KFileSystem_GetDataRoot  (KFileSystem::m_dataRoot (+0x104), read directly by its callers (CKStreamWave, PS3_CKVideo, CKCinematicStreamCpnt))
//   [ ] 0x48fb0  FUN_00048fb0  [dead]
//   [ ] 0x48fc0  KFileSystem_ZeroFillStreamAsync_maybe  [platform]  (the PS3 file device's asynchronous zero fill (KFileDevice_OpenAndZeroFillAsync_maybe): the PS3 file stack, replaced by design)
//   [ ] 0x49208  KFileSystem_ZeroFillStream  [platform]  (the PS3 file device's zero fill (KFileDevice_OpenAndZeroFill_maybe): the PS3 file stack, replaced by design)
//   [ ] 0x49368  KFileSystem_SplitExtension  [dead: no pointer to its descriptor; its only call is from the dead 0x52970 KMemoryManager_DumpBlockMapToFile_maybe]
//   [ ] 0x49428  KFileSystem_GetFileName  [dead: no pointer to its descriptor 0xb3dea8, no call]
//   [ ] 0x49540  KFileSystem_GetDirectory  [dead: no pointer to its descriptor 0xb3deb0, no call]
//   [ ] 0x49628  KFileSystem_SetSaveRoot_maybe  [dead: no pointer to its descriptor 0xb3deb8, no call]
//   [x] 0x496c8  KFileSystem_SetDataRoot  (KFileSystem::SetDataRoot)
//   [x] 0x49770  CopyString4Offset  (KFileSystem::SetExecutablePath)
#include "k2000/memory/KMemBuffer.h"

#include <cstring>

#include "k2000/memory/Mem.h"
#include "k2000/io/KFileSystem.h"

// 0x00049770 CopyString4Offset (main: argv[0]): strcpy to +0x04; 1.
void KFileSystem::SetExecutablePath(const char* path) {
    std::strncpy(m_executablePath, path, sizeof(m_executablePath) - 1);  // (the original's unbounded strcpy)
}

// 0x000496c8 KFileSystem_SetDataRoot: a non-empty root that does not end in '\' or '/' gets a '\' appended (the original
// writes it into the caller's string, then copies); then the copy to +0x104. 1.
void KFileSystem::SetDataRoot(const char* root) {
    std::strncpy(m_dataRoot, root, sizeof(m_dataRoot) - 2);
    m_dataRoot[sizeof(m_dataRoot) - 2] = 0;
    const size_t length = std::strlen(m_dataRoot);
    if (length > 0 && m_dataRoot[length - 1] != '\\' && m_dataRoot[length - 1] != '/') {
        m_dataRoot[length] = '\\';
        m_dataRoot[length + 1] = 0;
    }
}

// 0x00048370 KMemBuffer_Construct: inline in KMemBuffer.h.

// 0x000485f8 KMemBuffer_Destructor (0x00048550 KMemBuffer_DeletingDestructor the same, then the delete)
KMemBuffer::~KMemBuffer() {
    if (m_pData == nullptr || m_bExternal != 0) return;
    Mem_FreeAligned16(m_pData);
    m_pData = nullptr;
}

// 0x000483b8 KMemBuffer_Free
void KMemBuffer::Free() {
    if (m_pData == nullptr || m_bExternal != 0) return;
    Mem_FreeAligned16(m_pData);
    m_pData = nullptr;
}

// 0x00048430 KMemBuffer_Init
void KMemBuffer::Init(int32_t capacity, uint32_t granularity) {
    m_ui32Granularity = granularity;
    m_i32Capacity = capacity;
    if (capacity < 10) m_i32Capacity = 10;
    m_bExternal = 0;
    m_i32Size = 0;
    m_readerCount = 0;
    m_writerCount = 0;
    m_pData = static_cast<uint8_t*>(Mem_CallocAligned16(static_cast<uint32_t>(m_i32Capacity), 1));
}

// 0x000484a0 KMemBuffer_EnsureCapacity_maybe. The rounding is (size + granularity - 1) & -granularity (a granularity of
// 0 gives 0, as in the original).
void KMemBuffer::EnsureCapacity(int32_t size) {
    if (m_bExternal != 0) return;
    const int32_t old = m_i32Capacity;
    if (!(old < size)) return;
    const uint32_t capacity = (static_cast<uint32_t>(size) + m_ui32Granularity - 1u) & (0u - m_ui32Granularity);
    m_i32Capacity = static_cast<int32_t>(capacity);
    m_pData = static_cast<uint8_t*>(Mem_ReallocAligned16(m_pData, capacity));
    std::memset(m_pData + old, 0, static_cast<uint32_t>(m_i32Capacity - old));
}

// 0x00048ec0 KMemBuffer_Resize
void KMemBuffer::Resize(int32_t size) {
    m_i32Size = size;
    EnsureCapacity(size);  // inlined in the original
}
