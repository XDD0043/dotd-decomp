// savedata.cpp - cellSaveData on the host (savedata.h). C2.8 save-menu: new platform code.
#include "platform/cell/savedata.h"

#include <algorithm>
#include <chrono>
#include <climits>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <mutex>
#include <string>
#include <system_error>
#include <vector>

#include "platform/cell/msgdialog.h"
#include "platform/log.h"

namespace fs = std::filesystem;

namespace {
std::mutex g_rootMutex;
std::string g_root;          // empty: the default, resolved on first use
std::string g_lastDirName;   // the folder this run saved last (the list's answer next time)

std::string DefaultRoot() {
    if (const char* env = std::getenv("DOTD_SAVEDATA_DIR")) {
        if (*env != 0) return env;
    }
    if (const char* local = std::getenv("LOCALAPPDATA")) {
        if (*local != 0) return (fs::path(local) / "dotd" / "savedata").string();
    }
    if (const char* home = std::getenv("HOME")) {
        if (*home != 0) return (fs::path(home) / ".local" / "share" / "dotd" / "savedata").string();
    }
    return (fs::temp_directory_path() / "dotd-savedata").string();
}

std::string Root() {
    std::lock_guard<std::mutex> lock(g_rootMutex);
    if (g_root.empty()) g_root = DefaultRoot();
    return g_root;
}

// The pacer (savedata.h): the worker's state as SaveDataAdvance sees it.
enum WorkerState { kIdle, kPending, kRunning, kWaiting };
std::mutex g_paceMutex;
std::condition_variable g_paceCv;
dotd::platform::SaveDataPacer g_pacer = nullptr;
WorkerState g_workerState = kIdle;
int32_t g_waitFrame = -1;
int32_t g_frame = INT32_MIN;

void Gate(int32_t stage) {
    dotd::platform::SaveDataPacer pacer;
    {
        std::lock_guard<std::mutex> lock(g_paceMutex);
        pacer = g_pacer;
    }
    if (pacer == nullptr) return;
    const int32_t target = pacer(stage);
    if (target < 0) return;
    std::unique_lock<std::mutex> lock(g_paceMutex);
    g_waitFrame = target;
    g_workerState = kWaiting;
    g_paceCv.notify_all();
    g_paceCv.wait(lock, [target] { return g_frame >= target || g_pacer == nullptr; });
    g_workerState = kRunning;
}

struct Folder {
    std::string name;
    fs::file_time_type mtime;
};

std::vector<Folder> ListFolders(const std::string& root, const char* prefix) {
    std::vector<Folder> out;
    std::error_code ec;
    if (!fs::is_directory(root, ec)) return out;
    const size_t prefixLength = prefix != nullptr ? std::strlen(prefix) : 0;
    for (const fs::directory_entry& entry : fs::directory_iterator(root, ec)) {
        if (!entry.is_directory(ec)) continue;
        const std::string name = entry.path().filename().string();
        if (name.size() >= 32 || name.compare(0, prefixLength, prefix != nullptr ? prefix : "") != 0) continue;
        out.push_back({name, fs::last_write_time(entry.path(), ec)});
    }
    // CELL_SAVEDATA_SORTTYPE_MODIFIEDTIME, CELL_SAVEDATA_SORTORDER_DESCENT (the game's list): the newest first.
    std::sort(out.begin(), out.end(), [](const Folder& a, const Folder& b) { return a.mtime > b.mtime; });
    return out;
}

void CopyField(char* dst, size_t size, const std::string& text) {
    std::memset(dst, 0, size);
    std::memcpy(dst, text.data(), std::min(size - 1, text.size()));
}

void ReadParam(const fs::path& folder, CellSaveDataSystemFileParam* param) {
    std::ifstream in(folder / "PARAM.TXT", std::ios::binary);
    std::string title, subTitle, detail, line;
    std::getline(in, title);
    std::getline(in, subTitle);
    while (std::getline(in, line)) detail += (detail.empty() ? "" : "\n") + line;
    CopyField(param->title, sizeof(param->title), title);
    CopyField(param->subTitle, sizeof(param->subTitle), subTitle);
    CopyField(param->detail, sizeof(param->detail), detail);
}

bool WriteParam(const fs::path& folder, const CellSaveDataSystemFileParam* param) {
    std::ofstream out(folder / "PARAM.TXT", std::ios::binary | std::ios::trunc);
    auto field = [](const char* text, size_t size) { return std::string(text, strnlen(text, size)); };
    out << field(param->title, sizeof(param->title)) << '\n'
        << field(param->subTitle, sizeof(param->subTitle)) << '\n'
        << field(param->detail, sizeof(param->detail)) << '\n';
    return static_cast<bool>(out);
}

bool WriteFile(const fs::path& path, const void* data, uint32_t size, bool truncate) {
    std::fstream out(path, std::ios::binary | std::ios::out | (truncate ? std::ios::trunc : std::ios::in));
    if (!out && !truncate) out.open(path, std::ios::binary | std::ios::out);
    if (!out) return false;
    if (size != 0) out.write(static_cast<const char*>(data), size);
    return static_cast<bool>(out);
}

const char* ContentFileName(uint32_t fileType) {
    switch (fileType) {
    case CELL_SAVEDATA_FILETYPE_CONTENT_ICON0: return "ICON0.PNG";
    case CELL_SAVEDATA_FILETYPE_CONTENT_ICON1: return "ICON1.PAM";
    case CELL_SAVEDATA_FILETYPE_CONTENT_PIC1: return "PIC1.PNG";
    case CELL_SAVEDATA_FILETYPE_CONTENT_SND0: return "SND0.AT3";
    default: return nullptr;
    }
}
}  // namespace

int32_t cellSaveDataListSave2(uint32_t /*version*/, CellSaveDataSetList* setList, CellSaveDataSetBuf* setBuf,
                              CellSaveDataListCallback funcList, CellSaveDataStatCallback funcStat,
                              CellSaveDataFileCallback funcFile, uint32_t /*container*/, void* userdata) {
    const std::string root = Root();
    const char* prefix = setList != nullptr ? setList->dirNamePrefix : "";
    std::vector<Folder> folders = ListFolders(root, prefix);
    const uint32_t max = setBuf != nullptr && setBuf->dirListMax != 0 ? setBuf->dirListMax : 0xffffffffu;
    if (folders.size() > max) folders.resize(max);

    // The list callback.
    std::vector<CellSaveDataDirList> dirList(folders.size());
    for (size_t i = 0; i < folders.size(); ++i) {
        std::memset(&dirList[i], 0, sizeof(dirList[i]));
        CopyField(dirList[i].dirName, sizeof(dirList[i].dirName), folders[i].name);
    }
    CellSaveDataCBResult result = {};
    result.userdata = userdata;
    CellSaveDataListGet listGet = {};
    listGet.dirNum = static_cast<uint32_t>(folders.size());
    listGet.dirListNum = static_cast<uint32_t>(folders.size());
    listGet.dirList = dirList.empty() ? nullptr : dirList.data();
    CellSaveDataListSet listSet = {};
    funcList(&result, &listGet, &listSet);
    if (result.result < 0) return CELL_SAVEDATA_ERROR_CBRESULT;

    // The system's list (no UI): the folder saved last in this run when listed, else the new data offered, else the first
    // of the fixed list (the newest).
    std::string dirName;
    bool isNew = false;
    for (uint32_t i = 0; i < listSet.fixedListNum && dirName.empty(); ++i) {
        if (!g_lastDirName.empty() && g_lastDirName == listSet.fixedList[i].dirName) dirName = g_lastDirName;
    }
    if (dirName.empty() && listSet.newData != nullptr && listSet.newData->dirName != nullptr) {
        dirName = listSet.newData->dirName;
        isNew = true;
    }
    if (dirName.empty() && listSet.fixedListNum != 0) dirName = listSet.fixedList[0].dirName;
    if (dirName.empty()) return CELL_SAVEDATA_RET_CANCEL;
    const fs::path folder = fs::path(root) / dirName;
    std::error_code ec;
    if (fs::exists(folder, ec)) isNew = false;

    Gate(dotd::platform::kSaveDataStageStat);

    // The stat callback.
    CellSaveDataStatGet statGet = {};
    const fs::space_info space = fs::space(fs::exists(root, ec) ? fs::path(root) : fs::temp_directory_path(), ec);
    const uint64_t freeKB = ec ? 0x7fffffffu : space.available / 1024;
    statGet.hddFreeSizeKB = static_cast<int32_t>(std::min<uint64_t>(freeKB, 0x7fffffffu));
    statGet.isNewData = isNew ? 1u : 0u;
    CopyField(statGet.dir.dirName, sizeof(statGet.dir.dirName), dirName);
    if (!isNew) ReadParam(folder, &statGet.getParam);
    CellSaveDataStatSet statSet = {};
    result = {};
    result.userdata = userdata;
    funcStat(&result, &statGet, &statSet);
    if (result.result < 0) return CELL_SAVEDATA_ERROR_CBRESULT;
    CellSaveDataSystemFileParam param = statSet.setParam != nullptr ? *statSet.setParam : statGet.getParam;

    Gate(dotd::platform::kSaveDataStageFile);

    // The file callback until OK_LAST.
    fs::create_directories(folder, ec);
    if (ec) {
        DOTD_LOG("savedata: cannot create %s", folder.string().c_str());
        return CELL_SAVEDATA_ERROR_ACCESS_ERROR;
    }
    for (int32_t step = 0; step < 0x1000; ++step) {
        CellSaveDataFileGet fileGet = {};
        CellSaveDataFileSet fileSet = {};
        result = {};
        result.userdata = userdata;
        funcFile(&result, &fileGet, &fileSet);
        if (result.result < 0) return CELL_SAVEDATA_ERROR_CBRESULT;
        if (result.result != CELL_SAVEDATA_CBRESULT_OK_NEXT) break;  // OK_LAST: the file set is not processed
        const char* name = fileSet.fileType <= CELL_SAVEDATA_FILETYPE_NORMALFILE ? fileSet.fileName
                                                                                : ContentFileName(fileSet.fileType);
        if (name == nullptr) continue;
        const fs::path path = folder / name;
        if (fileSet.fileOperation == CELL_SAVEDATA_FILEOP_DELETE) {
            fs::remove(path, ec);
        } else if (fileSet.fileOperation == CELL_SAVEDATA_FILEOP_WRITE ||
                   fileSet.fileOperation == CELL_SAVEDATA_FILEOP_WRITE_NOTRUNC) {
            const uint32_t size = std::min(fileSet.fileSize, fileSet.fileBufSize);
            if (!WriteFile(path, fileSet.fileBuf, size, fileSet.fileOperation == CELL_SAVEDATA_FILEOP_WRITE)) {
                DOTD_LOG("savedata: cannot write %s", path.string().c_str());
                return CELL_SAVEDATA_ERROR_ACCESS_ERROR;
            }
        }
    }
    WriteParam(folder, &param);
    g_lastDirName = dirName;
    DOTD_LOG("savedata: saved %s", folder.string().c_str());

    Gate(dotd::platform::kSaveDataStageDone);
    return CELL_SAVEDATA_RET_OK;
}

// ==== C2.8 menus-load: the loads ===================================================================================
namespace {
std::vector<CellSaveDataDirList> DirList(const std::vector<Folder>& folders) {
    std::vector<CellSaveDataDirList> dirList(folders.size());
    for (size_t i = 0; i < folders.size(); ++i) {
        std::memset(&dirList[i], 0, sizeof(dirList[i]));
        CopyField(dirList[i].dirName, sizeof(dirList[i].dirName), folders[i].name);
    }
    return dirList;
}

// The stat and file stages of a load (the folder exists).
int32_t LoadFolder(const std::string& root, const std::string& dirName, CellSaveDataSetBuf* setBuf,
                   CellSaveDataStatCallback funcStat, CellSaveDataFileCallback funcFile, void* userdata) {
    const fs::path folder = fs::path(root) / dirName;
    std::error_code ec;
    Gate(dotd::platform::kSaveDataStageStat);

    // The stat callback: the folder's parameters and its files (the system's own PARAM.SFO / PARAM.TXT not listed).
    std::vector<CellSaveDataFileStat> files;
    for (const fs::directory_entry& entry : fs::directory_iterator(folder, ec)) {
        if (!entry.is_regular_file(ec)) continue;
        const std::string name = entry.path().filename().string();
        if (name == "PARAM.TXT" || name == "PARAM.SFO" || name.size() >= 13) continue;
        CellSaveDataFileStat stat = {};
        stat.fileType = name == "ICON0.PNG"   ? CELL_SAVEDATA_FILETYPE_CONTENT_ICON0
                        : name == "ICON1.PAM" ? CELL_SAVEDATA_FILETYPE_CONTENT_ICON1
                        : name == "PIC1.PNG"  ? CELL_SAVEDATA_FILETYPE_CONTENT_PIC1
                        : name == "SND0.AT3"  ? CELL_SAVEDATA_FILETYPE_CONTENT_SND0
                                              : CELL_SAVEDATA_FILETYPE_SECUREFILE;
        stat.st_size = static_cast<uint64_t>(entry.file_size(ec));
        CopyField(stat.fileName, sizeof(stat.fileName), name);
        files.push_back(stat);
    }
    std::sort(files.begin(), files.end(),
              [](const CellSaveDataFileStat& a, const CellSaveDataFileStat& b) { return std::strcmp(a.fileName, b.fileName) < 0; });
    CellSaveDataStatGet statGet = {};
    const fs::space_info space = fs::space(folder, ec);
    const uint64_t freeKB = ec ? 0x7fffffffu : space.available / 1024;
    statGet.hddFreeSizeKB = static_cast<int32_t>(std::min<uint64_t>(freeKB, 0x7fffffffu));
    statGet.isNewData = 0;
    CopyField(statGet.dir.dirName, sizeof(statGet.dir.dirName), dirName);
    ReadParam(folder, &statGet.getParam);
    statGet.fileNum = static_cast<uint32_t>(files.size());
    const uint32_t listMax = setBuf != nullptr && setBuf->fileListMax != 0 ? setBuf->fileListMax : 0xffffffffu;
    statGet.fileListNum = std::min(statGet.fileNum, listMax);
    statGet.fileList = files.empty() ? nullptr : files.data();
    CellSaveDataStatSet statSet = {};
    CellSaveDataCBResult result = {};
    result.userdata = userdata;
    funcStat(&result, &statGet, &statSet);
    if (result.result < 0) return CELL_SAVEDATA_ERROR_CBRESULT;
    if (result.result != CELL_SAVEDATA_CBRESULT_OK_NEXT) return CELL_SAVEDATA_RET_OK;  // OK_LAST: no file stage

    Gate(dotd::platform::kSaveDataStageFile);

    // The file callback until OK_LAST (excSize: the previous read's bytes).
    uint32_t excSize = 0;
    for (int32_t step = 0; step < 0x1000; ++step) {
        CellSaveDataFileGet fileGet = {};
        fileGet.excSize = excSize;
        CellSaveDataFileSet fileSet = {};
        result = {};
        result.userdata = userdata;
        funcFile(&result, &fileGet, &fileSet);
        if (result.result < 0) return CELL_SAVEDATA_ERROR_CBRESULT;
        if (result.result != CELL_SAVEDATA_CBRESULT_OK_NEXT) break;
        const char* name = fileSet.fileType <= CELL_SAVEDATA_FILETYPE_NORMALFILE ? fileSet.fileName
                                                                                : ContentFileName(fileSet.fileType);
        excSize = 0;
        if (name == nullptr || fileSet.fileOperation != CELL_SAVEDATA_FILEOP_READ) continue;
        std::ifstream in(folder / name, std::ios::binary);
        if (!in) {
            DOTD_LOG("savedata: cannot read %s", (folder / name).string().c_str());
            return CELL_SAVEDATA_ERROR_ACCESS_ERROR;
        }
        in.seekg(fileSet.fileOffset);
        const uint32_t size = std::min(fileSet.fileSize, fileSet.fileBufSize);
        in.read(static_cast<char*>(fileSet.fileBuf), size);
        excSize = static_cast<uint32_t>(in.gcount());
    }
    g_lastDirName = dirName;
    DOTD_LOG("savedata: loaded %s", folder.string().c_str());
    Gate(dotd::platform::kSaveDataStageDone);
    return CELL_SAVEDATA_RET_OK;
}
}  // namespace

int32_t cellSaveDataListLoad2(uint32_t /*version*/, CellSaveDataSetList* setList, CellSaveDataSetBuf* setBuf,
                              CellSaveDataListCallback funcList, CellSaveDataStatCallback funcStat,
                              CellSaveDataFileCallback funcFile, uint32_t /*container*/, void* userdata) {
    const std::string root = Root();
    std::vector<Folder> folders = ListFolders(root, setList != nullptr ? setList->dirNamePrefix : "");
    const uint32_t max = setBuf != nullptr && setBuf->dirListMax != 0 ? setBuf->dirListMax : 0xffffffffu;
    if (folders.size() > max) folders.resize(max);
    std::vector<CellSaveDataDirList> dirList = DirList(folders);
    CellSaveDataCBResult result = {};
    result.userdata = userdata;
    CellSaveDataListGet listGet = {};
    listGet.dirNum = static_cast<uint32_t>(folders.size());
    listGet.dirListNum = static_cast<uint32_t>(folders.size());
    listGet.dirList = dirList.empty() ? nullptr : dirList.data();
    CellSaveDataListSet listSet = {};
    funcList(&result, &listGet, &listSet);
    if (result.result < 0) return CELL_SAVEDATA_ERROR_CBRESULT;
    if (listSet.fixedListNum == 0) {
        dotd::platform::SystemMessageWait("There is no saved data.");
        return CELL_SAVEDATA_RET_CANCEL;
    }
    // The system's list (no UI): DOTD_SAVEDATA_LOAD (the player's choice in a replayed recording, C2.8 lvl020-load: it
    // comes before the folder the boot's options auto load read), else the folder saved or loaded last in this run, else
    // the first.
    std::string dirName;
    const char* wanted = std::getenv("DOTD_SAVEDATA_LOAD");
    for (int pass = 0; pass < 2 && dirName.empty(); ++pass) {
        const std::string want = pass == 1 ? g_lastDirName : (wanted != nullptr ? wanted : "");
        if (want.empty()) continue;
        for (uint32_t i = 0; i < listSet.fixedListNum; ++i) {
            if (want == listSet.fixedList[i].dirName) dirName = want;
        }
    }
    if (dirName.empty()) dirName = listSet.fixedList[0].dirName;
    return LoadFolder(root, dirName, setBuf, funcStat, funcFile, userdata);
}

int32_t cellSaveDataListAutoLoad(uint32_t /*version*/, uint32_t /*errDialog*/, CellSaveDataSetList* setList,
                                 CellSaveDataSetBuf* setBuf, CellSaveDataFixedCallback funcFixed,
                                 CellSaveDataStatCallback funcStat, CellSaveDataFileCallback funcFile, uint32_t /*container*/,
                                 void* userdata) {
    const std::string root = Root();
    std::vector<Folder> folders = ListFolders(root, setList != nullptr ? setList->dirNamePrefix : "");
    const uint32_t max = setBuf != nullptr && setBuf->dirListMax != 0 ? setBuf->dirListMax : 0xffffffffu;
    if (folders.size() > max) folders.resize(max);
    std::vector<CellSaveDataDirList> dirList = DirList(folders);
    CellSaveDataCBResult result = {};
    result.userdata = userdata;
    CellSaveDataListGet listGet = {};
    listGet.dirNum = static_cast<uint32_t>(folders.size());
    listGet.dirListNum = static_cast<uint32_t>(folders.size());
    listGet.dirList = dirList.empty() ? nullptr : dirList.data();
    CellSaveDataFixedSet fixedSet = {};
    funcFixed(&result, &listGet, &fixedSet);
    if (result.result < 0) return CELL_SAVEDATA_ERROR_CBRESULT;
    if (fixedSet.dirName == nullptr) return CELL_SAVEDATA_ERROR_PARAM;
    std::error_code ec;
    if (!fs::is_directory(fs::path(root) / fixedSet.dirName, ec)) return CELL_SAVEDATA_ERROR_CBRESULT;
    return LoadFolder(root, fixedSet.dirName, setBuf, funcStat, funcFile, userdata);
}

int32_t cellSaveDataDelete2(uint32_t /*container*/) {
    DOTD_LOG("savedata: delete list (no UI): cancelled");
    return CELL_SAVEDATA_RET_CANCEL;
}

namespace dotd::platform {
void SetSaveDataRoot(const char* path) {
    std::lock_guard<std::mutex> lock(g_rootMutex);
    g_root = path != nullptr ? path : "";
}
const char* SaveDataRoot() {
    static thread_local std::string root;
    root = Root();
    return root.c_str();
}

void SetSaveDataPacer(SaveDataPacer pacer) {
    std::lock_guard<std::mutex> lock(g_paceMutex);
    g_pacer = pacer;
    g_paceCv.notify_all();
}
void SaveDataRequestPosted() {
    std::lock_guard<std::mutex> lock(g_paceMutex);
    if (g_pacer != nullptr) g_workerState = kPending;
}
void SaveDataWorkerBegin() {
    std::lock_guard<std::mutex> lock(g_paceMutex);
    g_workerState = kRunning;
    g_paceCv.notify_all();
}
void SaveDataWorkerEnd() {
    std::lock_guard<std::mutex> lock(g_paceMutex);
    g_workerState = kIdle;
    g_paceCv.notify_all();
}
bool SaveDataWorkerIdle() {
    std::lock_guard<std::mutex> lock(g_paceMutex);
    return g_workerState == kIdle;
}
void SaveDataAdvance(int32_t frame) {
    std::unique_lock<std::mutex> lock(g_paceMutex);
    if (g_pacer == nullptr) return;
    g_frame = frame;
    g_paceCv.notify_all();
    const bool settled = g_paceCv.wait_for(lock, std::chrono::seconds(30), [frame] {
        return g_workerState == kIdle || (g_workerState == kWaiting && g_waitFrame > frame);
    });
    if (!settled) DOTD_LOG("savedata: the worker did not settle before frame %d", frame);
}
}  // namespace dotd::platform
