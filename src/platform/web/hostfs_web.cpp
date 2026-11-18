// hostfs_web.cpp - the web build's host file access (platform/hostfs.h): the game's files stay on the user's disk,
// unconverted, and web/serve.py serves the USRDIR folder next to the page. Nothing is downloaded up front.
//   - A listing of the whole folder (serve.py's /usrdir.manifest: one line per file or directory with its size
//     and time) is fetched by the page before main() and answers Stat and List, so opening a directory or
//     building the game's file index costs no request. Names are matched without case, as on the Windows disk
//     the native build reads.
//   - Reads are HTTP range requests, synchronous as the callers expect. A synchronous binary request is only
//     allowed off the browser's main thread: the game's worker threads (the level loader) make their own, the
//     main thread hands its request to the I/O thread below and waits for it.
//   - Small reads go through a cache of 1 MB blocks (the least recently used block is dropped), and reading a
//     block asks the I/O thread for the one after it, so a file read in sequence (a video, a sound stream)
//     does not stall the frame once per block. A read of a block or more goes straight into the caller's buffer.
// Paths outside the served root (saves, caches) go to the C library, which is Emscripten's in-memory file system.
#ifdef __EMSCRIPTEN__

#ifndef _GNU_SOURCE
#define _GNU_SOURCE  // fopencookie
#endif
#include <dirent.h>
#include <emscripten.h>
#include <emscripten/threading.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <thread>
#include <unordered_map>

#include "platform/hostfs.h"
#include "platform/log.h"
#include "platform/web/web.h"

// The listing text and the absolute URL of the served folder, set up by web/index.html before main() runs.
EM_JS_DEPS(dotd_hostfs_deps, "$stringToNewUTF8,$UTF8ToString");
EM_JS(char*, dotd_web_manifest_text, (), { return stringToNewUTF8(Module['dotdManifest'] || ''); });
EM_JS(char*, dotd_web_usrdir_url, (), {
    return stringToNewUTF8(new URL(Module['dotdUsrdirUrl'] || 'usrdir/', location.href).href);
});
// One range request, synchronous: bytes [offset, offset + length) of url into dst. Returns the byte count or a
// negative number. Worker threads only (the browser's main thread may not make a synchronous binary request).
EM_JS(int, dotd_web_fetch_range, (const char* url, double offset, int length, uint8_t* dst), {
    try {
        var xhr = new XMLHttpRequest();
        xhr.open('GET', UTF8ToString(url), false);
        xhr.responseType = 'arraybuffer';
        xhr.setRequestHeader('Range', 'bytes=' + offset + '-' + (offset + length - 1));
        xhr.send(null);
        if (xhr.status !== 206 && xhr.status !== 200) return -xhr.status;
        var data = new Uint8Array(xhr.response);
        if (xhr.status === 200) data = data.subarray(offset, offset + length);  // the server ignored the range
        if (data.length > length) data = data.subarray(0, length);
        HEAPU8.set(data, dst);
        return data.length;
    } catch (e) {
        return -1;
    }
});

namespace dotd::platform::hostfs {

namespace {

constexpr size_t kBlockSize = 1u << 20;
constexpr size_t kCacheBlocks = 64;          // 64 MB at most
constexpr size_t kMaxRequest = 32u << 20;    // a large read is split into requests of this size
constexpr size_t kMaxQueuedReadAhead = 4;

struct Entry {
    std::string url;
    bool isDir = false;
    uint64_t size = 0;
    int64_t mtime = 0;
    std::vector<std::string> children;  // names as on the disk
};

std::string g_root;                              // Config::usrdir, e.g. "/usrdir"
std::unordered_map<std::string, Entry> g_entries;  // by lower-case path below the root ("" = the root); fixed after Init
std::atomic<uint64_t> g_requests(0), g_requestBytes(0);
double g_mainWaitMs = 0.0;      // main thread only: see web::TakeMainThreadReadWait
int g_mainWaitReads = 0;
uint64_t g_mainWaitBytes = 0;

std::string Lower(std::string s) {
    for (char& c : s) {
        if (c >= 'A' && c <= 'Z') c = static_cast<char>(c - 'A' + 'a');
    }
    return s;
}

// Each path segment percent-encoded (the names have spaces and commas at most, but any byte is handled).
std::string EncodePath(const std::string& path) {
    static const char kHex[] = "0123456789ABCDEF";
    std::string out;
    for (unsigned char c : path) {
        const bool plain = (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '/' ||
                           c == '-' || c == '_' || c == '.' || c == '~';
        if (plain) {
            out += static_cast<char>(c);
        } else {
            out += '%';
            out += kHex[c >> 4];
            out += kHex[c & 15];
        }
    }
    return out;
}

// The entry of a path under the root; nullptr for a path outside it (*remote says which) or one not listed.
const Entry* Find(const std::string& path, bool* remote) {
    *remote = false;
    if (g_root.empty() || path.compare(0, g_root.size(), g_root) != 0) return nullptr;
    if (path.size() > g_root.size() && path[g_root.size()] != '/') return nullptr;
    *remote = true;
    size_t begin = g_root.size();
    while (begin < path.size() && path[begin] == '/') ++begin;
    size_t end = path.size();
    while (end > begin && path[end - 1] == '/') --end;
    auto found = g_entries.find(Lower(path.substr(begin, end - begin)));
    return found != g_entries.end() ? &found->second : nullptr;
}

// ---- the I/O thread: the main thread's requests and the read-ahead ------------------------------------------
struct Block {
    std::vector<uint8_t> data;
};
using BlockKey = std::pair<const Entry*, uint64_t>;  // file, block index

struct Job {
    const Entry* entry = nullptr;
    uint64_t offset = 0;
    size_t length = 0;
    uint8_t* dst = nullptr;   // a waiting caller's buffer; nullptr = read-ahead of block `offset / kBlockSize`
    bool done = false;
    bool ok = false;
};

std::mutex g_ioMutex;
std::condition_variable g_ioWake, g_ioDone;
std::deque<Job*> g_ioQueue;   // waiting callers first, then read-ahead (owned by the queue)
size_t g_ioReadAhead = 0;     // read-ahead jobs in the queue
bool g_ioStarted = false;

std::mutex g_cacheMutex;
std::list<BlockKey> g_lru;  // most recent first
std::map<BlockKey, std::pair<std::shared_ptr<Block>, std::list<BlockKey>::iterator>> g_cache;
std::set<BlockKey> g_pending;  // read-ahead blocks asked for and not yet in the cache

bool FetchDirect(const Entry* entry, uint64_t offset, size_t length, uint8_t* dst) {
    double waitedMs = 0.0, loggedMs = 0.0;
    for (int attempt = 0; attempt < 3; ++attempt) {
        const int got = dotd_web_fetch_range(entry->url.c_str(), static_cast<double>(offset), static_cast<int>(length), dst);
        if (got == static_cast<int>(length)) {
            g_requests.fetch_add(1, std::memory_order_relaxed);
            g_requestBytes.fetch_add(length, std::memory_order_relaxed);
            if (waitedMs > 0.0) DOTD_LOG("hostfs: %s arrived after %.1f s", entry->url.c_str(), waitedMs / 1000.0);
            return true;
        }
        if (got == -503) {
            // Download mode (web/sw.js): the file is not in the browser's store yet and is being downloaded now.
            // The read waits for it, as a read waits for the disc: asked again until it is there.
            if (waitedMs == 0.0 || waitedMs - loggedMs >= 5000.0) {
                DOTD_LOG("hostfs: waiting for %s to download", entry->url.c_str());
                loggedMs = waitedMs;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            waitedMs += 100.0;
            --attempt;
            continue;
        }
        DOTD_LOG("hostfs: request %s +%llu len %zu failed (%d), attempt %d", entry->url.c_str(),
                 static_cast<unsigned long long>(offset), length, got, attempt + 1);
    }
    return false;
}

void CacheInsert(const BlockKey& key, const std::shared_ptr<Block>& block) {
    std::lock_guard<std::mutex> lock(g_cacheMutex);
    g_pending.erase(key);
    if (g_cache.count(key) != 0) return;
    g_lru.push_front(key);
    g_cache[key] = {block, g_lru.begin()};
    while (g_cache.size() > kCacheBlocks) {
        g_cache.erase(g_lru.back());
        g_lru.pop_back();
    }
}

size_t BlockLength(const Entry* entry, uint64_t index) {
    const uint64_t start = index * kBlockSize;
    return static_cast<size_t>(std::min<uint64_t>(kBlockSize, entry->size - start));
}

void IoThreadMain() {
    for (;;) {
        Job* job = nullptr;
        {
            std::unique_lock<std::mutex> lock(g_ioMutex);
            g_ioWake.wait(lock, [] { return !g_ioQueue.empty(); });
            job = g_ioQueue.front();
            g_ioQueue.pop_front();
            if (job->dst == nullptr) --g_ioReadAhead;
        }
        if (job->dst != nullptr) {
            const bool ok = FetchDirect(job->entry, job->offset, job->length, job->dst);
            std::lock_guard<std::mutex> lock(g_ioMutex);
            job->ok = ok;
            job->done = true;
            g_ioDone.notify_all();
        } else {
            const BlockKey key(job->entry, job->offset / kBlockSize);
            auto block = std::make_shared<Block>();
            block->data.resize(job->length);
            if (FetchDirect(job->entry, job->offset, job->length, block->data.data())) {
                CacheInsert(key, block);
            } else {
                std::lock_guard<std::mutex> lock(g_cacheMutex);
                g_pending.erase(key);
            }
            delete job;
        }
    }
}

// Bytes [offset, offset + length) of the file into dst, from whichever thread asks.
bool Fetch(const Entry* entry, uint64_t offset, size_t length, uint8_t* dst) {
    if (!emscripten_is_main_browser_thread()) return FetchDirect(entry, offset, length, dst);
    Job job;
    job.entry = entry;
    job.offset = offset;
    job.length = length;
    job.dst = dst;
    const double start = emscripten_get_now();
    struct Waited {
        double start;
        size_t length;
        ~Waited() {
            g_mainWaitMs += emscripten_get_now() - start;
            ++g_mainWaitReads;
            g_mainWaitBytes += length;
        }
    } waited{start, length};
    std::unique_lock<std::mutex> lock(g_ioMutex);
    // Before the read-ahead, after the callers already waiting.
    auto at = g_ioQueue.begin();
    while (at != g_ioQueue.end() && (*at)->dst != nullptr) ++at;
    g_ioQueue.insert(at, &job);
    g_ioWake.notify_one();
    g_ioDone.wait(lock, [&job] { return job.done; });
    return job.ok;
}

void ReadAhead(const Entry* entry, uint64_t index) {
    if (index * kBlockSize >= entry->size) return;
    const BlockKey key(entry, index);
    {
        std::lock_guard<std::mutex> lock(g_cacheMutex);
        if (g_cache.count(key) != 0 || g_pending.count(key) != 0) return;
        g_pending.insert(key);
    }
    Job* job = new Job();
    job->entry = entry;
    job->offset = index * kBlockSize;
    job->length = BlockLength(entry, index);
    std::lock_guard<std::mutex> lock(g_ioMutex);
    if (g_ioReadAhead >= kMaxQueuedReadAhead) {
        std::lock_guard<std::mutex> cacheLock(g_cacheMutex);
        g_pending.erase(key);
        delete job;
        return;
    }
    ++g_ioReadAhead;
    g_ioQueue.push_back(job);
    g_ioWake.notify_one();
}

std::shared_ptr<Block> GetBlock(const Entry* entry, uint64_t index) {
    const BlockKey key(entry, index);
    std::shared_ptr<Block> block;
    {
        std::lock_guard<std::mutex> lock(g_cacheMutex);
        auto found = g_cache.find(key);
        if (found != g_cache.end()) {
            g_lru.splice(g_lru.begin(), g_lru, found->second.second);
            block = found->second.first;
        }
    }
    if (!block) {
        block = std::make_shared<Block>();
        block->data.resize(BlockLength(entry, index));
        if (!Fetch(entry, index * kBlockSize, block->data.size(), block->data.data())) return nullptr;
        CacheInsert(key, block);
    }
    ReadAhead(entry, index + 1);
    return block;
}

size_t ReadRemote(const Entry* entry, uint64_t position, uint8_t* dst, size_t bytes) {
    if (position >= entry->size) return 0;
    bytes = static_cast<size_t>(std::min<uint64_t>(bytes, entry->size - position));
    size_t done = 0;
    if (bytes >= kBlockSize) {
        while (done < bytes) {
            const size_t n = std::min(bytes - done, kMaxRequest);
            if (!Fetch(entry, position + done, n, dst + done)) break;
            done += n;
        }
        return done;
    }
    while (done < bytes) {
        const uint64_t at = position + done;
        const uint64_t index = at / kBlockSize;
        const size_t within = static_cast<size_t>(at - index * kBlockSize);
        const std::shared_ptr<Block> block = GetBlock(entry, index);
        if (!block) break;
        const size_t n = std::min(bytes - done, block->data.size() - within);
        std::memcpy(dst + done, block->data.data() + within, n);
        done += n;
    }
    return done;
}

// ---- fopencookie adaptors (OpenStdio) -------------------------------------------------------------------------
ssize_t CookieRead(void* cookie, char* buffer, size_t bytes);
int CookieSeek(void* cookie, off_t* offset, int whence);
int CookieClose(void* cookie);

}  // namespace

struct File {
    const Entry* entry = nullptr;  // a served file, or
    std::FILE* local = nullptr;    // a file of the in-memory file system
    uint64_t position = 0;
};

namespace {
ssize_t CookieRead(void* cookie, char* buffer, size_t bytes) {
    return static_cast<ssize_t>(Read(static_cast<File*>(cookie), buffer, bytes));
}

int CookieSeek(void* cookie, off_t* offset, int whence) {
    File* file = static_cast<File*>(cookie);
    int64_t base = 0;
    if (whence == SEEK_CUR) base = static_cast<int64_t>(file->position);
    else if (whence == SEEK_END) base = static_cast<int64_t>(file->entry->size);
    else if (whence != SEEK_SET) return -1;
    const int64_t target = base + static_cast<int64_t>(*offset);
    if (target < 0) return -1;
    file->position = static_cast<uint64_t>(target);
    *offset = static_cast<off_t>(target);
    return 0;
}

int CookieClose(void* cookie) {
    Close(static_cast<File*>(cookie));
    return 0;
}
}  // namespace

bool Stat(const std::string& path, Info* info) {
    bool remote = false;
    if (const Entry* entry = Find(path, &remote)) {
        info->isDir = entry->isDir;
        info->size = entry->isDir ? 0 : entry->size;
        info->atime = info->mtime = info->ctime = entry->mtime;
        return true;
    }
    if (remote) return false;
    struct stat st;
    if (::stat(path.c_str(), &st) != 0) return false;
    info->isDir = S_ISDIR(st.st_mode);
    info->size = info->isDir ? 0 : static_cast<uint64_t>(st.st_size);
    info->atime = static_cast<int64_t>(st.st_atime);
    info->mtime = static_cast<int64_t>(st.st_mtime);
    info->ctime = static_cast<int64_t>(st.st_ctime);
    return true;
}

bool List(const std::string& dir, std::vector<std::string>* names) {
    bool remote = false;
    if (const Entry* entry = Find(dir, &remote)) {
        if (!entry->isDir) return false;
        names->insert(names->end(), entry->children.begin(), entry->children.end());
        return true;
    }
    if (remote) return false;
    DIR* d = ::opendir(dir.c_str());
    if (d == nullptr) return false;
    while (const dirent* e = ::readdir(d)) {
        if (std::strcmp(e->d_name, ".") != 0 && std::strcmp(e->d_name, "..") != 0) names->push_back(e->d_name);
    }
    ::closedir(d);
    return true;
}

File* Open(const std::string& path) {
    bool remote = false;
    const Entry* entry = Find(path, &remote);
    if (entry != nullptr && !entry->isDir) {
        File* file = new File();
        file->entry = entry;
        return file;
    }
    std::FILE* local = remote ? nullptr : std::fopen(path.c_str(), "rb");
    if (local == nullptr) {
        DOTD_LOG("fs: cannot open %s", path.c_str());
        return nullptr;
    }
    File* file = new File();
    file->local = local;
    return file;
}

size_t Read(File* file, void* buffer, size_t bytes) {
    if (bytes == 0) return 0;
    if (file->local != nullptr) return std::fread(buffer, 1, bytes, file->local);
    const size_t got = ReadRemote(file->entry, file->position, static_cast<uint8_t*>(buffer), bytes);
    file->position += got;
    return got;
}

bool Seek(File* file, uint64_t position) {
    if (file->local != nullptr) return fseeko(file->local, static_cast<off_t>(position), SEEK_SET) == 0;
    file->position = position;
    return true;
}

void Close(File* file) {
    if (file == nullptr) return;
    if (file->local != nullptr) std::fclose(file->local);
    delete file;
}

std::FILE* OpenStdio(const std::string& path) {
    bool remote = false;
    const Entry* entry = Find(path, &remote);
    if (!remote) return std::fopen(path.c_str(), "rb");
    if (entry == nullptr || entry->isDir) return nullptr;
    File* file = new File();
    file->entry = entry;
    cookie_io_functions_t io = {};
    io.read = &CookieRead;
    io.seek = &CookieSeek;
    io.close = &CookieClose;
    std::FILE* stream = fopencookie(file, "rb", io);
    if (stream == nullptr) delete file;
    return stream;
}

}  // namespace dotd::platform::hostfs

namespace dotd::platform::web {

// The listing: "D\t<path>" for a directory, "F\t<size>\t<mtime>\t<path>" for a file, paths below the root with
// forward slashes, parents before their children.
bool InitHostFs(const std::string& root) {
    using namespace dotd::platform::hostfs;
    g_root = root;
    char* text = dotd_web_manifest_text();
    char* base = dotd_web_usrdir_url();
    std::string baseUrl = base;
    std::free(base);
    if (!baseUrl.empty() && baseUrl.back() != '/') baseUrl += '/';
    g_entries.clear();
    Entry rootEntry;
    rootEntry.isDir = true;
    rootEntry.url = baseUrl;
    g_entries[""] = rootEntry;
    size_t files = 0;
    uint64_t total = 0;
    for (const char* line = text; *line != 0;) {
        const char* end = std::strchr(line, '\n');
        std::string row = end != nullptr ? std::string(line, end) : std::string(line);
        line = end != nullptr ? end + 1 : line + row.size();
        if (!row.empty() && row.back() == '\r') row.pop_back();
        if (row.size() < 3 || row[1] != '\t') continue;
        Entry entry;
        std::string path;
        if (row[0] == 'D') {
            entry.isDir = true;
            path = row.substr(2);
        } else if (row[0] == 'F') {
            const size_t tab1 = row.find('\t', 2);
            const size_t tab2 = tab1 == std::string::npos ? tab1 : row.find('\t', tab1 + 1);
            if (tab2 == std::string::npos) continue;
            entry.size = std::strtoull(row.c_str() + 2, nullptr, 10);
            entry.mtime = std::strtoll(row.c_str() + tab1 + 1, nullptr, 10);
            path = row.substr(tab2 + 1);
            ++files;
            total += entry.size;
        } else {
            continue;
        }
        entry.url = baseUrl + EncodePath(path);
        const size_t slash = path.find_last_of('/');
        const std::string parent = slash == std::string::npos ? std::string() : path.substr(0, slash);
        const std::string name = slash == std::string::npos ? path : path.substr(slash + 1);
        auto parentEntry = g_entries.find(Lower(parent));
        if (parentEntry != g_entries.end()) parentEntry->second.children.push_back(name);
        g_entries[Lower(path)] = entry;
    }
    std::free(text);
    DOTD_LOG("hostfs: %s = %s, %zu files, %.1f MB listed", root.c_str(), baseUrl.c_str(), files, total / 1048576.0);
    if (!g_ioStarted) {
        g_ioStarted = true;
        std::thread(IoThreadMain).detach();
    }
    return files != 0;
}

bool ReadHead(const std::string& path, size_t bytes, std::vector<uint8_t>* out) {
    using namespace dotd::platform::hostfs;
    bool remote = false;
    const Entry* entry = Find(path, &remote);
    out->clear();
    if (entry == nullptr || entry->isDir) return false;
    out->resize(static_cast<size_t>(std::min<uint64_t>(bytes, entry->size)));
    if (!out->empty() && !Fetch(entry, 0, out->size(), out->data())) {
        out->clear();
        return false;
    }
    return true;
}

void TakeMainThreadReadWait(double* ms, int* reads, double* megabytes) {
    using namespace dotd::platform::hostfs;
    *ms = g_mainWaitMs;
    *reads = g_mainWaitReads;
    *megabytes = g_mainWaitBytes / 1048576.0;
    g_mainWaitMs = 0.0;
    g_mainWaitReads = 0;
    g_mainWaitBytes = 0;
}

void LogHostFsStats() {
    DOTD_LOG("hostfs: %llu requests, %.1f MB read",
             static_cast<unsigned long long>(dotd::platform::hostfs::g_requests.load()),
             dotd::platform::hostfs::g_requestBytes.load() / 1048576.0);
}

}  // namespace dotd::platform::web

#endif  // __EMSCRIPTEN__
