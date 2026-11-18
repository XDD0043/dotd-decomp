// savedata.h - cellSaveData as the game uses it (the list save with its three callbacks, the delete), on the host.
// C2.8 save-menu. The PS3 keeps a title's save data in system folders (dev_hdd0/home/<user>/savedata/<dirName>/: the
// files the file callback writes, ICON0.PNG, PIC1.PNG and PARAM.SFO) and shows its own list UI between the callbacks.
// Here the folders are under the save root (SaveDataRoot: %LOCALAPPDATA%\dotd\savedata, DOTD_SAVEDATA_DIR, or a test's
// SetSaveDataRoot), never the game folder; the files are the game's buffers written as they are; PARAM.SFO is replaced
// by PARAM.TXT (the title, subtitle and detail strings, UTF-8 lines). The system's list UI is answered without one
// (SaveDataChooseList: the folder saved or loaded last in this run, else the new data the list callback offers, else the
// newest folder). The structures follow the Cell SDK's (cell/sysutil_savedata.h) with host types: the game's callbacks
// are ported code that only touches the named fields.
#pragma once
#include <cstddef>
#include <cstdint>

enum : int32_t {
    CELL_SAVEDATA_RET_OK = 0,
    CELL_SAVEDATA_RET_CANCEL = 1,
    CELL_SAVEDATA_ERROR_CBRESULT = static_cast<int32_t>(0x8002b401u),
    CELL_SAVEDATA_ERROR_ACCESS_ERROR = static_cast<int32_t>(0x8002b402u),
    CELL_SAVEDATA_ERROR_INTERNAL = static_cast<int32_t>(0x8002b403u),
    CELL_SAVEDATA_ERROR_PARAM = static_cast<int32_t>(0x8002b404u),
    CELL_SAVEDATA_ERROR_NOSPACE = static_cast<int32_t>(0x8002b405u),
};
enum : int32_t {  // CellSaveDataCBResult::result
    CELL_SAVEDATA_CBRESULT_OK_LAST_NOCONFIRM = 2,
    CELL_SAVEDATA_CBRESULT_OK_LAST = 1,
    CELL_SAVEDATA_CBRESULT_OK_NEXT = 0,
    CELL_SAVEDATA_CBRESULT_ERR_NOSPACE = -1,
    CELL_SAVEDATA_CBRESULT_ERR_FAILURE = -2,
    CELL_SAVEDATA_CBRESULT_ERR_BROKEN = -3,
    CELL_SAVEDATA_CBRESULT_ERR_NODATA = -4,
    CELL_SAVEDATA_CBRESULT_ERR_INVALID = -5,
};
enum : uint32_t {
    CELL_SAVEDATA_FILEOP_READ = 0,
    CELL_SAVEDATA_FILEOP_WRITE = 1,
    CELL_SAVEDATA_FILEOP_DELETE = 2,
    CELL_SAVEDATA_FILEOP_WRITE_NOTRUNC = 3,
    CELL_SAVEDATA_FILETYPE_SECUREFILE = 0,
    CELL_SAVEDATA_FILETYPE_NORMALFILE = 1,
    CELL_SAVEDATA_FILETYPE_CONTENT_ICON0 = 2,
    CELL_SAVEDATA_FILETYPE_CONTENT_ICON1 = 3,
    CELL_SAVEDATA_FILETYPE_CONTENT_PIC1 = 4,
    CELL_SAVEDATA_FILETYPE_CONTENT_SND0 = 5,
};

struct CellSaveDataSetList {
    uint32_t sortType;
    uint32_t sortOrder;
    const char* dirNamePrefix;
    void* reserved;
};
struct CellSaveDataSetBuf {
    uint32_t dirListMax;
    uint32_t fileListMax;
    uint32_t reserved[6];
    uint32_t bufSize;
    void* buf;
};
struct CellSaveDataDirList {  // 0x30 bytes on the PS3
    char dirName[32];
    char listParam[8];
    char reserved[8];
};
struct CellSaveDataListGet {
    uint32_t dirNum;
    uint32_t dirListNum;
    CellSaveDataDirList* dirList;
};
struct CellSaveDataNewDataIcon {
    const char* title;
    uint32_t iconBufSize;
    void* iconBuf;
    void* reserved;
};
struct CellSaveDataListNewData {
    uint32_t iconPosition;
    const char* dirName;
    CellSaveDataNewDataIcon* icon;
    void* reserved;
};
struct CellSaveDataListSet {
    uint32_t focusPosition;
    const char* focusDirName;
    uint32_t fixedListNum;
    CellSaveDataDirList* fixedList;
    CellSaveDataListNewData* newData;
    void* reserved;
};
struct CellSaveDataCBResult {
    int32_t result;
    uint32_t progressBarInc;
    int32_t errNeedSizeKB;
    const char* invalidMsg;
    void* userdata;
};
struct CellSaveDataDirStat {
    int64_t st_atime;
    int64_t st_mtime;
    int64_t st_ctime;
    char dirName[32];
};
struct CellSaveDataSystemFileParam {
    char title[128];
    char subTitle[128];
    char detail[1024];
    uint32_t attribute;
    char reserved2[4];
    char listParam[8];
    char reserved[256];
};
struct CellSaveDataFileStat {  // 0x38 bytes on the PS3
    uint32_t fileType;
    char reserved1[4];
    uint64_t st_size;
    int64_t st_atime;
    int64_t st_mtime;
    int64_t st_ctime;
    char fileName[13];
    char reserved2[3];
};
struct CellSaveDataStatGet {
    int32_t hddFreeSizeKB;
    uint32_t isNewData;
    CellSaveDataDirStat dir;
    CellSaveDataSystemFileParam getParam;
    uint32_t bind;
    int32_t sizeKB;
    int32_t sysSizeKB;
    uint32_t fileNum;
    uint32_t fileListNum;            // C2.8 menus-load: the files listed (at most the setBuf's fileListMax)
    CellSaveDataFileStat* fileList;
};
struct CellSaveDataFixedSet {  // the auto load's fixed callback (C2.8 menus-load)
    const char* dirName;
    CellSaveDataNewDataIcon* newIcon;
    uint32_t option;
};
struct CellSaveDataStatSet {
    CellSaveDataSystemFileParam* setParam;
    uint32_t reCreateMode;
    void* indicator;
};
struct CellSaveDataFileGet {
    uint32_t excSize;
};
struct CellSaveDataFileSet {
    uint32_t fileOperation;
    void* reserved;
    uint32_t fileType;
    uint8_t secureFileId[16];
    const char* fileName;
    uint32_t fileOffset;
    uint32_t fileSize;
    uint32_t fileBufSize;
    void* fileBuf;
};

typedef void (*CellSaveDataListCallback)(CellSaveDataCBResult* result, CellSaveDataListGet* get, CellSaveDataListSet* set);
typedef void (*CellSaveDataStatCallback)(CellSaveDataCBResult* result, CellSaveDataStatGet* get, CellSaveDataStatSet* set);
typedef void (*CellSaveDataFileCallback)(CellSaveDataCBResult* result, CellSaveDataFileGet* get, CellSaveDataFileSet* set);
typedef void (*CellSaveDataFixedCallback)(CellSaveDataCBResult* result, CellSaveDataListGet* get, CellSaveDataFixedSet* set);

// cellSaveDataListSave2: the folders of the prefix listed (the list callback), one chosen (no UI here), the stat callback
// with its state (a new folder or the existing PARAM.TXT), then the file callback until it answers OK_LAST. 0, or
// CELL_SAVEDATA_ERROR_CBRESULT when a callback answered an error, CELL_SAVEDATA_ERROR_ACCESS_ERROR on a host write error.
int32_t cellSaveDataListSave2(uint32_t version, CellSaveDataSetList* setList, CellSaveDataSetBuf* setBuf,
                              CellSaveDataListCallback funcList, CellSaveDataStatCallback funcStat,
                              CellSaveDataFileCallback funcFile, uint32_t container, void* userdata);
// C2.8 menus-load. cellSaveDataListLoad2: the folders of the prefix listed (the list callback), one chosen (no UI:
// DOTD_SAVEDATA_LOAD when it names a listed folder, else the folder saved or loaded last in this run when listed, else the
// list's first, the newest), the stat callback with the folder's PARAM.TXT and its files, then the file callback until
// OK_LAST (a read fills fileBuf from the file at fileOffset; excSize the bytes read). An empty list shows the system's
// "There is no saved data." until it is closed and returns CELL_SAVEDATA_RET_CANCEL, as the system's list does.
int32_t cellSaveDataListLoad2(uint32_t version, CellSaveDataSetList* setList, CellSaveDataSetBuf* setBuf,
                              CellSaveDataListCallback funcList, CellSaveDataStatCallback funcStat,
                              CellSaveDataFileCallback funcFile, uint32_t container, void* userdata);
// cellSaveDataListAutoLoad (no dialog: errDialog is not shown): the folders listed for the fixed callback, which names
// the folder (an error answer ends the call with CELL_SAVEDATA_ERROR_CBRESULT), then the stat and file callbacks as above.
int32_t cellSaveDataListAutoLoad(uint32_t version, uint32_t errDialog, CellSaveDataSetList* setList,
                                 CellSaveDataSetBuf* setBuf, CellSaveDataFixedCallback funcFixed,
                                 CellSaveDataStatCallback funcStat, CellSaveDataFileCallback funcFile, uint32_t container,
                                 void* userdata);
// cellSaveDataDelete2: the system's delete list. Without a list UI nothing is deleted: CELL_SAVEDATA_RET_CANCEL.
int32_t cellSaveDataDelete2(uint32_t container);

namespace dotd::platform {
// The folder the save data folders go in (created on the first write). Default: DOTD_SAVEDATA_DIR, else
// %LOCALAPPDATA%\dotd\savedata (the user's profile). Tests and replays set a temporary folder.
void SetSaveDataRoot(const char* path);
const char* SaveDataRoot();

// Reproducible runs (replays; new platform code, not in the original). The PS3's system UI takes frames between the list
// callback and the stat callback (the list dialog), before the file callbacks and before the call returns; a pacer gives,
// for each of those stages, the frame the worker waits for (-1: none). SaveDataAdvance(frame), called before each frame,
// releases the waits up to `frame` and returns once the save data worker is idle or waiting for a later frame, so the
// callbacks and the request's end fall on the same frames in every run. SaveDataRequestPosted / SaveDataWorker mark the
// memcard request's life (SaveDataRequest::Post / Execute).
enum SaveDataStage : int32_t { kSaveDataStageStat = 0, kSaveDataStageFile = 1, kSaveDataStageDone = 2 };
typedef int32_t (*SaveDataPacer)(int32_t stage);
void SetSaveDataPacer(SaveDataPacer pacer);
void SaveDataAdvance(int32_t frame);
void SaveDataRequestPosted();
void SaveDataWorkerBegin();
void SaveDataWorkerEnd();
bool SaveDataWorkerIdle();  // no save data call is pending, running or waiting
}  // namespace dotd::platform
