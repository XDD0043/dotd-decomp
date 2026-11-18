// SaveData.cpp - reconstructed original translation unit 0x2cdd8-0x2e880 (GAME_TOC1, main_toc1), 20 functions, 20 live.
// Primary owner: SaveData (not a registered class)
// Other owners: Str (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [x] 0x2cdd8  SaveData_ListLoadListCallback_maybe
//   [x] 0x2ce40  SaveData_ListAutoLoadFixedCallback_maybe
//   [x] 0x2ce80  StaticInitFini_GlobalMemBuffers_maybe  (s_sysBuffer / s_usrBuffer: their static constructors and destructors)
//   [ ] 0x2cf30  _GLOBAL__D_2cf30
//   [ ] 0x2cf40  _GLOBAL__I_2cf40
//   [x] 0x2cf50  Str_UCS2ToUTF8Alloc_maybe
//   [x] 0x2d010  SaveData_ListAutoLoad_maybe
//   [x] 0x2d100  SaveData_FreeWorkBuffer_maybe
//   [x] 0x2d148  SaveData_FreeWorkBuffer2_maybe
//   [x] 0x2d190  SaveData_Delete
//   [x] 0x2d1c0  SaveData_ListLoad_maybe
//   [x] 0x2d2a8  SaveData_StatCallback_maybe
//   [x] 0x2d4d8  SaveData_SaveStatCallback
//   [x] 0x2d640  SaveData_SaveListCallback
//   [x] 0x2d840  SaveData_InitDirNamePrefix
//   [x] 0x2d918  SaveData_LoadOptionsFileCallback_maybe
//   [x] 0x2db88  SaveData_LoadFileCallback_maybe
//   [x] 0x2df90  SaveData_SaveFileCallback_maybe
//   [x] 0x2e418  SaveData_ListSave_maybe
//   [x] 0x2e6b8  SaveData_LoadIconBlobs_maybe
#include "k2000/io/SaveData.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "k2000/io/IKFile.h"
#include "platform/cell/msgdialog.h"

void* g_pSaveDataBlob0 = nullptr;
void* g_pSaveDataBlob1 = nullptr;
uint32_t g_saveDataBlob1Size = 0;
uint32_t g_saveDataBlob0Size = 0;

// 0x0002d148 SaveData_FreeWorkBuffer2_maybe (free through TocBridge_free: LoadIconBlobs mallocs it)
void SaveData_FreeWorkBuffer2() {
    if (g_pSaveDataBlob1 == nullptr) return;
    std::free(g_pSaveDataBlob1);
    g_pSaveDataBlob1 = nullptr;
}

// 0x0002d100 SaveData_FreeWorkBuffer_maybe: the kind-0 blob (0x00c517b4, the level's) freed and cleared.
void SaveData_FreeWorkBuffer() {
    if (g_pSaveDataBlob0 == nullptr) return;
    std::free(g_pSaveDataBlob0);
    g_pSaveDataBlob0 = nullptr;
}

// 0x0002e6b8 SaveData_LoadIconBlobs_maybe
void SaveData_LoadIconBlobs(IKFile* stream, int32_t kind) {
    void* blob = nullptr;
    uint32_t size = 0;
    if (kind == 0) {
        ReadU32LE(stream, &g_saveDataBlob0Size);
        if (g_saveDataBlob0Size == 0) {
            g_pSaveDataBlob0 = nullptr;
            return;
        }
        blob = std::malloc(g_saveDataBlob0Size);
        g_pSaveDataBlob0 = blob;
        size = g_saveDataBlob0Size;
    } else {
        if (kind != 1) return;
        ReadU32LE(stream, &g_saveDataBlob1Size);
        if (g_saveDataBlob1Size == 0) {
            g_pSaveDataBlob1 = nullptr;
            return;
        }
        blob = std::malloc(g_saveDataBlob1Size);
        g_pSaveDataBlob1 = blob;
        size = g_saveDataBlob1Size;
    }
    stream->Read(blob, size);
}

int32_t g_saveDataResult = 0;  // 0x00c517b0

// ==== C2.8 save-menu: the list save ================================================================================
#include "k2000/logic/CDefaultGameManager.h"
#include "k2000/logic/CKSavingManager.h"
#include "k2000/logic/IKPlayer.h"
#include "k2000/logic/ui/CKLocText.h"
#include "k2000/logic/ui/CLocManager.h"
#include "k2000/io/KFileSystem.h"
#include "k2000/memory/KMemBuffer.h"
#include "k2000/memory/Mem.h"
#include "k2000/misc/Engine.h"
#include "platform/cell/l10n.h"
#include "platform/cell/savedata.h"

namespace {
// The save sizes (0x00c40708 / 0x00c4070c, read through the TOC): SYS-DATA (K_GAME_MEMCARD) and USR-DATA (K_OPTIONS_MEMCARD).
constexpr uint32_t kSysDataSize = 0x4000;
constexpr uint32_t kUsrDataSize = 0x400;
// 0x00ac37c0 / 0x00ac37d0 the secure files' names; 0x00a6f3b0 their secure file id.
const char kSysDataName[] = "SYS-DATA";
const char kUsrDataName[] = "USR-DATA";
const uint8_t kSecureFileId[16] = {0x0e, 0x01, 0x0b, 0x00, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x02};

// The block at 0x00c51748.
int32_t s_i32FileStep = 0;                  // 0x00c51748 the file callback's step
KMemBuffer s_sysBuffer;                     // 0x00c5174c the SYS-DATA buffer (StaticInitFini_GlobalMemBuffers_maybe)
KMemBuffer s_usrBuffer;                     // 0x00c5176c the USR-DATA buffer
char s_dirNamePrefix[0x20] = {};            // 0x00c51790 "BLUS30205-SPYRO08-SAVE-" (InitDirNamePrefix)
}  // namespace
extern uint8_t g_unkC517C0;  // 0x00c517c0 (CDefaultGameManager.cpp: InitImpl clears it, IsSaveDataBusy reads it)
namespace {
uint8_t& s_bStatDone = g_unkC517C0;         // 0x00c517c0 the stat callback ran (the list save clears it)
CellSaveDataListNewData s_newData = {};     // 0x00c517c8 the list's new data
CellSaveDataNewDataIcon s_newDataIcon = {};  // 0x00c517d8 its icon (the GAME blob)
char s_newDirName[0x20] = {};               // 0x00c517e8 its folder name
IKFile* s_pUsrFile = nullptr;               // 0x00c51808
IKFile* s_pSysFile = nullptr;               // 0x00c5180c

// The list save's user data (the stack block 0x70 of ListSave): the strings of the system file parameters.
struct SaveStrings {
    char* title;        // text 1000
    char* subTitle;     // the game manager's vt+0xfc
    char* detail;       // the game manager's vt+0xf8
    char* newTitle;     // text 0x130: the new data's title
};

const uint16_t* LocText(uint32_t id) {
    return LocString_GetText(g_pEngine->m_locManager->GetText(id));  // 0x00037028, 0x00035d28
}

// 0x0002d640 SaveData_SaveListCallback: the list shown as it is (at most 0x800 entries, the focus 1); with fewer than
// five saves the new data offers the first folder name prefix + 1..5 not in the list (5 even when it is: BUG(original),
// unreachable with fewer than five folders of the prefix), the GAME blob as its icon.
void SaveListCallback(CellSaveDataCBResult* result, CellSaveDataListGet* get, CellSaveDataListSet* set) {
    s_newData = {};
    s_newDataIcon = {};
    set->fixedList = get->dirList;
    set->fixedListNum = get->dirListNum < 0x801 ? get->dirListNum : 0x800;
    set->focusDirName = nullptr;
    set->focusPosition = 1;
    set->reserved = nullptr;
    if (get->dirListNum < 5) {
        set->newData = &s_newData;
        int32_t n = 0;
        for (;;) {
            ++n;
            std::snprintf(s_newDirName, sizeof(s_newDirName), "%s%d", s_dirNamePrefix, n);  // 0x00ac37e0 "%s%d"
            const uint32_t count = get->dirListNum;
            if (count == 0) break;
            uint32_t i = 0;
            while (std::strcmp(get->dirList[i].dirName, s_newDirName) != 0) {
                if (++i == count) goto found;
            }
            if (n == 5) break;
        }
    found:
        s_newData.dirName = s_newDirName;
        s_newData.icon = &s_newDataIcon;
        s_newData.iconPosition = 0;
        s_newData.reserved = nullptr;
        s_newDataIcon.title = static_cast<SaveStrings*>(result->userdata)->newTitle;
        s_newDataIcon.reserved = nullptr;
        s_newDataIcon.iconBuf = g_pSaveDataBlob1;
        s_newDataIcon.iconBufSize = g_saveDataBlob1Size;
    } else {
        set->newData = nullptr;
    }
    result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
}

// 0x0002d4d8 SaveData_SaveStatCallback: a new save needs the four files' size in KB free (else ERR_NOSPACE with the
// missing KB); the system file parameters from the user data.
void SaveStatCallback(CellSaveDataCBResult* result, CellSaveDataStatGet* get, CellSaveDataStatSet* set) {
    s_bStatDone = 1;
    set->setParam = &get->getParam;
    set->indicator = nullptr;
    set->reCreateMode = 0;
    if (get->isNewData != 0) {
        const uint64_t bytes = static_cast<uint64_t>(g_saveDataBlob1Size) + g_saveDataBlob0Size + kSysDataSize + kUsrDataSize;
        const int32_t left = get->hddFreeSizeKB - static_cast<int32_t>(((bytes + 0x3ff) & 0xffffffffu) >> 10);
        if (left < 0) {
            result->errNeedSizeKB = -left;
            result->result = CELL_SAVEDATA_CBRESULT_ERR_NOSPACE;
            return;
        }
    }
    const SaveStrings* strings = static_cast<const SaveStrings*>(result->userdata);
    std::strcpy(set->setParam->title, strings->title);
    std::strcpy(set->setParam->subTitle, strings->subTitle);
    std::strcpy(set->setParam->detail, strings->detail);
    set->setParam->attribute = 0;
    set->setParam->listParam[0] = 0;
    set->setParam->reserved2[3] = 0;
    set->setParam->reserved2[0] = 0;
    set->setParam->reserved2[1] = 0;
    set->setParam->reserved2[2] = 0;
    s_i32FileStep = 0;
    result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
}

// One secure file: its buffer (the size, zeroed), a memory stream on it (read-write), the saving manager's SaveObjects
// (vt+0x5c) of `type`; the file set then writes the whole buffer.
bool WriteSecureFile(KMemBuffer* buffer, IKFile** file, int32_t type, uint32_t size, const char* name,
                     CellSaveDataFileSet* set) {
    buffer->Init(static_cast<int32_t>(size), 0);  // 0x00048430
    buffer->Resize(static_cast<int32_t>(size));   // 0x00048ec0
    *file = g_pEngine->m_fileSystem->OpenFile(reinterpret_cast<const char*>(buffer), 2, KFileSystem::kDeviceMemory,
                                              KFileSystem::kRootNone, 0, -1, 0);  // 0x0004a288
    if (*file == nullptr) return false;
    if (g_pEngine->m_pSavingManager->SaveObjects(*file, type, size) != 1) return false;  // vt+0x5c
    set->fileOperation = CELL_SAVEDATA_FILEOP_WRITE;
    set->fileBuf = buffer->m_pData;
    set->fileBufSize = size;
    std::memcpy(set->secureFileId, kSecureFileId, sizeof(kSecureFileId));
    set->fileName = name;
    set->fileSize = size;
    set->fileType = CELL_SAVEDATA_FILETYPE_SECUREFILE;
    return true;
}

// 0x0002df90 SaveData_SaveFileCallback_maybe: step 0 ICON0 (the GAME blob), 1 PIC1 (the level blob), 2 SYS-DATA, 3 USR-DATA,
// 4 the streams closed and the buffers freed, OK_LAST. A failed stream or SaveObjects: ERR_FAILURE (the step kept).
void SaveFileCallback(CellSaveDataCBResult* result, CellSaveDataFileGet* /*get*/, CellSaveDataFileSet* set) {
    result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
    switch (s_i32FileStep) {
    case 0:
        set->fileOperation = CELL_SAVEDATA_FILEOP_WRITE;
        set->fileBuf = g_pSaveDataBlob1;
        set->fileBufSize = g_saveDataBlob1Size;
        set->fileSize = g_saveDataBlob1Size;
        set->fileType = CELL_SAVEDATA_FILETYPE_CONTENT_ICON0;
        break;
    case 1:
        set->fileOperation = CELL_SAVEDATA_FILEOP_WRITE;
        set->fileBuf = g_pSaveDataBlob0;
        set->fileBufSize = g_saveDataBlob0Size;
        set->fileType = CELL_SAVEDATA_FILETYPE_CONTENT_PIC1;
        set->fileSize = g_saveDataBlob0Size;
        break;
    case 2:
        if (!WriteSecureFile(&s_sysBuffer, &s_pSysFile, K_GAME_MEMCARD, kSysDataSize, kSysDataName, set)) {
            result->result = CELL_SAVEDATA_CBRESULT_ERR_FAILURE;
            return;
        }
        break;
    case 3:
        if (!WriteSecureFile(&s_usrBuffer, &s_pUsrFile, K_OPTIONS_MEMCARD, kUsrDataSize, kUsrDataName, set)) {
            result->result = CELL_SAVEDATA_CBRESULT_ERR_FAILURE;
            return;
        }
        break;
    default:
        if (s_pSysFile != nullptr) {
            g_pEngine->m_fileSystem->CloseFile(s_pSysFile);  // 0x00049dd8
            s_pSysFile = nullptr;
            s_sysBuffer.Free();  // 0x000483b8
        }
        if (s_pUsrFile != nullptr) {
            g_pEngine->m_fileSystem->CloseFile(s_pUsrFile);
            s_pUsrFile = nullptr;
            s_usrBuffer.Free();
        }
        s_bStatDone = 0;
        result->result = CELL_SAVEDATA_CBRESULT_OK_LAST;
        break;
    }
    result->progressBarInc = 0x19;
    ++s_i32FileStep;
}
}  // namespace

// 0x0002cf50 Str_UCS2ToUTF8Alloc_maybe: the text's UTF-8 in a zeroed Mem_AllocAligned16 block (its length + 1).
char* Str_UCS2ToUTF8Alloc(const uint16_t* text) {
    size_t length = 0;
    while (text[length] != 0) ++length;  // Wcs_Length 0x10a18
    size_t sourceLength = length;
    size_t utf8Length = 0;
    UCS2stoUTF8s(text, &sourceLength, nullptr, &utf8Length);
    uint8_t* utf8 = static_cast<uint8_t*>(Mem_AllocAligned16(static_cast<uint32_t>(utf8Length + 1)));
    std::memset(utf8, 0, utf8Length + 1);
    UCS2stoUTF8s(text, &sourceLength, utf8, &utf8Length);
    return reinterpret_cast<char*>(utf8);
}

// 0x0002d840 SaveData_InitDirNamePrefix: the title id (0x00c4b1d4 "BLUS30205"), '-', the save name (TOC1 -0x7a2c
// "SPYRO08"), then "-SAVE-" (TOC1 -0x7a28, seven bytes with its terminator).
void SaveData_InitDirNamePrefix() {
    std::strcpy(s_dirNamePrefix, "BLUS30205");
    std::strcat(s_dirNamePrefix, "-");
    std::strcat(s_dirNamePrefix, "SPYRO08");
    std::strcat(s_dirNamePrefix, "-SAVE-");
}

// 0x0002e418 SaveData_ListSave_maybe (the memcard worker): player 0's game state takes the structure's progress (vt+0x58),
// the detail (vt+0xf8, 0x800 bytes of UCS-2), the strings in UTF-8, then cellSaveDataListSave2 with the callbacks (the
// list: the prefix, sorted by time, newest first; the buffer: 5 folders, 4 files, 0xf0 bytes); its result kept, the
// stat flag cleared.
void SaveData_ListSave() {
    uint16_t* detail = new uint16_t[0x400];
    detail[0] = 0;
    CDefaultGameManager* manager = g_pEngine->m_gameManager;
    static_cast<IKPlayer*>(manager->m_players[0])->CopyGameStructure();  // vt+0x58
    manager->BuildSaveDetailText(detail);                                  // vt+0xf8
    SaveStrings strings = {};
    strings.title = Str_UCS2ToUTF8Alloc(LocText(1000));
    strings.subTitle = Str_UCS2ToUTF8Alloc(manager->GetSaveSubtitleText());  // vt+0xfc
    strings.detail = Str_UCS2ToUTF8Alloc(detail);
    strings.newTitle = Str_UCS2ToUTF8Alloc(LocText(0x130));
    delete[] detail;
    char prefix[0x20];
    std::strcpy(prefix, s_dirNamePrefix);
    CellSaveDataSetList setList = {};
    setList.sortType = 0;   // CELL_SAVEDATA_SORTTYPE_MODIFIEDTIME
    setList.sortOrder = 0;  // CELL_SAVEDATA_SORTORDER_DESCENT
    setList.dirNamePrefix = prefix;
    CellSaveDataSetBuf setBuf = {};
    setBuf.dirListMax = 5;
    setBuf.fileListMax = 4;
    setBuf.bufSize = 0xf0;
    setBuf.buf = std::malloc(0xf0);
    g_saveDataResult = cellSaveDataListSave2(0, &setList, &setBuf, &SaveListCallback, &SaveStatCallback, &SaveFileCallback,
                                             0xffffffffu, &strings);
    s_bStatDone = 0;
    char* const texts[4] = {strings.title, strings.subTitle, strings.detail, strings.newTitle};
    for (char* text : texts) {
        if (text != nullptr) Mem_FreeAligned16(text);
    }
    if (setBuf.buf != nullptr) std::free(setBuf.buf);
}

// 0x0002d190 SaveData_Delete: cellSaveDataDelete2 (the system's delete list); its result is not kept.
void SaveData_Delete() { cellSaveDataDelete2(0xffffffffu); }

// ==== C2.8 menus-load: the loads ===================================================================================
#include "k2000/logic/io/CKLoadingManager.h"

namespace {
// One secure file to read: its buffer (the size, zeroed), a read-write memory stream on it (0x0004a288 with the flags 2,
// the memory device, root 2), the file set: a read of the whole file into the buffer.
bool ReadSecureFile(KMemBuffer* buffer, IKFile** file, uint32_t size, const char* name, CellSaveDataFileSet* set) {
    buffer->Init(static_cast<int32_t>(size), 0);  // 0x00048430
    buffer->Resize(static_cast<int32_t>(size));   // 0x00048ec0
    *file = g_pEngine->m_fileSystem->OpenFile(reinterpret_cast<const char*>(buffer), 2, KFileSystem::kDeviceMemory, 2, 0,
                                              -1, 0);
    if (*file == nullptr) return false;
    set->fileOperation = CELL_SAVEDATA_FILEOP_READ;
    set->fileBuf = buffer->m_pData;
    set->fileBufSize = size;
    set->fileName = name;
    set->fileSize = size;
    std::memcpy(set->secureFileId, kSecureFileId, sizeof(kSecureFileId));
    set->fileType = CELL_SAVEDATA_FILETYPE_SECUREFILE;
    return true;
}

// The objects of a read file loaded (CKLoadingManager_LoadSavedObjects_maybe in `mode`: an answer other than 1 makes the
// result ERR_FAILURE), then its stream closed and its buffer freed. The buffer's byte +0x1c is cleared first.
void LoadSecureFile(CellSaveDataCBResult* result, KMemBuffer* buffer, IKFile** file, int32_t mode) {
    buffer->m_bExternal = 0;
    if (g_pEngine->m_objectDatabase->LoadSavedObjects(*file, mode) != 1) {  // 0x0002a7c8 (engine +0x4c)
        result->result = CELL_SAVEDATA_CBRESULT_ERR_FAILURE;
    }
    if (*file != nullptr) {
        g_pEngine->m_fileSystem->CloseFile(*file);  // 0x00049dd8
        *file = nullptr;
        buffer->Free();  // 0x000483b8
    }
}

// 0x0002cdd8 SaveData_ListLoadListCallback_maybe: the list shown as it is (at most 0x800 entries), the focus on the first,
// no new data (newData is not written: the system's zeroed set); the file step 0.
void ListLoadListCallback(CellSaveDataCBResult* result, CellSaveDataListGet* get, CellSaveDataListSet* set) {
    set->fixedList = get->dirList;
    set->fixedListNum = get->dirListNum > 0x800 ? 0x800 : get->dirListNum;
    set->reserved = nullptr;
    set->focusPosition = 1;  // CELL_SAVEDATA_FOCUSPOS_LISTHEAD
    set->focusDirName = nullptr;
    s_i32FileStep = 0;
    result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
}

// 0x0002ce40 SaveData_ListAutoLoadFixedCallback_maybe: the list's first folder (the newest), the file step 1 (USR-DATA
// only); ERR_NODATA without one.
void ListAutoLoadFixedCallback(CellSaveDataCBResult* result, CellSaveDataListGet* get, CellSaveDataFixedSet* set) {
    if (get->dirListNum == 0) {
        result->result = CELL_SAVEDATA_CBRESULT_ERR_NODATA;
        return;
    }
    set->dirName = get->dirList[0].dirName;
    s_i32FileStep = 1;
    result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
}

// 0x0002d2a8 SaveData_StatCallback_maybe: an existing save with fewer listed files than it has is broken; each listed
// ICON0.PNG must have the GAME blob's size, SYS-DATA and USR-DATA theirs (else ERR_BROKEN). No new parameters, recreate
// mode 1 (CELL_SAVEDATA_RECREATE_NO_NOBROKEN). A new folder sets ERR_NODATA first, but the end overwrites it with OK_NEXT:
// BUG(original) (unreachable in a list or auto load, which only offer existing folders).
void StatCallback(CellSaveDataCBResult* result, CellSaveDataStatGet* get, CellSaveDataStatSet* set) {
    const uint32_t count = get->fileNum;
    if (get->isNewData != 0) {
        result->result = CELL_SAVEDATA_CBRESULT_ERR_NODATA;
    } else if (get->fileListNum < count) {
        result->result = CELL_SAVEDATA_CBRESULT_ERR_BROKEN;
        return;
    }
    // BUG(original): the loop runs over fileNum entries of fileList (only fileListNum are listed); the check above makes
    // them equal for an existing save.
    for (uint32_t i = 0; i < count; ++i) {
        const CellSaveDataFileStat& file = get->fileList[i];
        uint64_t expected;
        if (std::strcmp(file.fileName, "ICON0.PNG") == 0) {  // 0x00ac37b0
            expected = g_saveDataBlob1Size;
        } else if (std::strcmp(file.fileName, kSysDataName) == 0) {
            expected = kSysDataSize;
        } else if (std::strcmp(file.fileName, kUsrDataName) == 0) {
            expected = kUsrDataSize;
        } else {
            continue;
        }
        if (file.st_size != expected) {
            result->result = CELL_SAVEDATA_CBRESULT_ERR_BROKEN;
            return;
        }
    }
    set->indicator = nullptr;
    set->reCreateMode = 1;
    set->setParam = nullptr;
    result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
}

// 0x0002db88 SaveData_LoadFileCallback_maybe: step 0 reads SYS-DATA, 1 USR-DATA, then their objects are loaded (SYS-DATA in
// K_GAME_MEMCARD, USR-DATA in K_OPTIONS_MEMCARD) and the answer is OK_LAST. A failed stream: ERR_FAILURE (the step kept).
// A failed load sets ERR_FAILURE, which the OK_LAST after it overwrites: BUG(original).
void LoadFileCallback(CellSaveDataCBResult* result, CellSaveDataFileGet* /*get*/, CellSaveDataFileSet* set) {
    result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
    if (s_i32FileStep == 0) {
        if (!ReadSecureFile(&s_sysBuffer, &s_pSysFile, kSysDataSize, kSysDataName, set)) {
            result->result = CELL_SAVEDATA_CBRESULT_ERR_FAILURE;
            return;
        }
    } else if (s_i32FileStep == 1) {
        if (!ReadSecureFile(&s_usrBuffer, &s_pUsrFile, kUsrDataSize, kUsrDataName, set)) {
            result->result = CELL_SAVEDATA_CBRESULT_ERR_FAILURE;
            return;
        }
    } else {
        LoadSecureFile(result, &s_sysBuffer, &s_pSysFile, K_GAME_MEMCARD);
        LoadSecureFile(result, &s_usrBuffer, &s_pUsrFile, K_OPTIONS_MEMCARD);
        result->result = CELL_SAVEDATA_CBRESULT_OK_LAST;
    }
    result->progressBarInc = 0x32;
    ++s_i32FileStep;
}

// 0x0002d918 SaveData_LoadOptionsFileCallback_maybe: the auto load's file callback: step 1 reads USR-DATA, the next step
// loads its objects (K_OPTIONS_MEMCARD) and answers OK_LAST (the same overwritten ERR_FAILURE: BUG(original)).
void LoadOptionsFileCallback(CellSaveDataCBResult* result, CellSaveDataFileGet* /*get*/, CellSaveDataFileSet* set) {
    result->result = CELL_SAVEDATA_CBRESULT_OK_NEXT;
    if (s_i32FileStep == 1) {
        if (!ReadSecureFile(&s_usrBuffer, &s_pUsrFile, kUsrDataSize, kUsrDataName, set)) {
            result->result = CELL_SAVEDATA_CBRESULT_ERR_FAILURE;
            return;
        }
    } else {
        LoadSecureFile(result, &s_usrBuffer, &s_pUsrFile, K_OPTIONS_MEMCARD);
        result->result = CELL_SAVEDATA_CBRESULT_OK_LAST;
    }
    result->progressBarInc = 0x32;
    ++s_i32FileStep;
}

// The list / auto load's set-up (the stack blocks of 0x2d1c0 / 0x2d010): the prefix, sorted by time, newest first; the
// buffer: 5 folders, 4 files, 0xf0 bytes (malloc).
void LoadSetup(char* prefix, CellSaveDataSetList* setList, CellSaveDataSetBuf* setBuf) {
    std::strcpy(prefix, s_dirNamePrefix);
    *setList = {};
    setList->sortType = 0;   // CELL_SAVEDATA_SORTTYPE_MODIFIEDTIME
    setList->sortOrder = 0;  // CELL_SAVEDATA_SORTORDER_DESCENT
    setList->dirNamePrefix = prefix;
    *setBuf = {};
    setBuf->dirListMax = 5;
    setBuf->fileListMax = 4;
    setBuf->bufSize = 0xf0;
    setBuf->buf = std::malloc(0xf0);
}
}  // namespace

// 0x0002d1c0 SaveData_ListLoad_maybe (the memcard worker's load): cellSaveDataListLoad2 with the list (0x2cdd8), stat
// (0x2d2a8) and file (0x2db88) callbacks, no user data; its result kept.
void SaveData_ListLoad() {
    char prefix[0x20];
    CellSaveDataSetList setList;
    CellSaveDataSetBuf setBuf;
    LoadSetup(prefix, &setList, &setBuf);
    g_saveDataResult = cellSaveDataListLoad2(0, &setList, &setBuf, &ListLoadListCallback, &StatCallback, &LoadFileCallback,
                                             0xffffffffu, nullptr);
    if (setBuf.buf != nullptr) std::free(setBuf.buf);
}

// 0x0002d010 SaveData_ListAutoLoad_maybe (the boot's options load): cellSaveDataListAutoLoad without the error dialog, with
// the fixed (0x2ce40), stat (0x2d2a8) and options file (0x2d918) callbacks; its result kept.
void SaveData_ListAutoLoad() {
    char prefix[0x20];
    CellSaveDataSetList setList;
    CellSaveDataSetBuf setBuf;
    LoadSetup(prefix, &setList, &setBuf);
    g_saveDataResult = cellSaveDataListAutoLoad(0, 0, &setList, &setBuf, &ListAutoLoadFixedCallback, &StatCallback,
                                                &LoadOptionsFileCallback, 0xffffffffu, nullptr);
    if (setBuf.buf != nullptr) std::free(setBuf.buf);
}
