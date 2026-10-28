// CKLoadingManager.h - the object database and KP3 loader (key 0x1cc, vtable 0xb13dc8, size 0x23c).
// Original units: CKLoadingManager.cpp (file loaders, class table, references), io/Kp3.cpp (category
// and class loops), io/Kp3Writer.cpp (DecodeObjectId). See outputs/remake/research/kp3-loading.md.
//
// A KP3 file is read in two passes: every object's Load, then every object's PostLoad, in the same
// order. Objects of a class are created up front as one contiguous array (ClassManager CreateArray), so
// a reference is an index into that array and is valid before the target is loaded. Global classes are
// engine singletons handed over by their owners (Engine_GetGlobalInstances).
#pragma once
#include <cstdint>

#include "k2000/core/IKUpdatable.h"
#include "k2000/core/Layout.h"

class IKFile;

// One class of the level's class table (CKObjectTypeRecord, 0x1c bytes).
struct CKIDBundleLoad {
    enum Instantiation : uint8_t { kGlobal = 0, kLevelUnique = 1, kSectorShared = 2 };

    void* instances;          // +0x00 array start (m_ui16SizeOfClass apart); Global: the object (count 1) or an IKSerializable* array
    IKSerializable** m_apGameRecreableInstances;   // +0x04 GAME objects this level adds data to, found by UUID
    uint32_t m_ui32TyIdInst;        // +0x08 key | count << 17 (count = level count; a sector overwrites it)
    uint32_t m_i32Seek;           // +0x0c
    uint16_t m_ui16NbInstOffset;         // +0x10 index of the first object of this block (read per class block)
    uint16_t m_ui16NbCommunInst;      // +0x12
    uint16_t m_ui16NbGameInst;       // +0x14
    uint16_t m_ui16SizeOfClass;          // +0x16 sizeof the class (from CreateArray); not set for Global
    uint8_t m_ui8StreamType;    // +0x18 Instantiation
    uint8_t m_bIsGUID;          // +0x19 the objects (and globs) carry UUIDs in the class table
    uint8_t pad1a[2];
};

// One category of the class table (0xc bytes).
struct CKTypeBundleLoad {
    CKIDBundleLoad* m_pID;   // +0x00 the category's slice of CKLoadingManager::m_pIdBundleLoad
    uint16_t m_ui16NbReadID;  // +0x04
    uint16_t m_ui16NbCommunReadID;   // +0x06
    uint32_t m_i32Seek;         // +0x08 file offset where the next category starts
};

// The load progress block (0x00c50f24).
struct KLoadProgress {
    uint8_t unk00;
    uint8_t nesting;   // +0x01 +1 around every object Load
    uint8_t pad02[2];
    float scale;       // +0x04 100 / file size (LoadKp3Stream)
    IKFile* stream;    // +0x08 the sector file being loaded (LoadSectorFile); cleared after LoadLevel
};
extern KLoadProgress g_loadProgress;

// Unregistered key 0x93e (vtable 0xb13e08): what an IKFile calls back into when it loads
// (IKFile::m_pLoadingInterfaces, +0x10). XXL2 IKLoadingInterfaces : IKBaseClass, slots 9..11 (+0x24..+0x2c,
// pure here): ReadHandle(IKFile*, IKSerializable*&), ReadContiguousHandles(IKFile*, IKSerializable*&,
// UInt32), ReadTexture(IKFile*, CTexture*&).
class IKLoadingInterfaces : public IKBaseClass {
public:
    // vt+0x24: reads one object reference (a "handle") into *object (null, UUID or index). Returns the
    // bytes read.
    virtual uint32_t ReadHandle(IKFile* stream, IKSerializable** object) = 0;
    // vt+0x28: count references.
    virtual uint32_t ReadContiguousHandles(IKFile* stream, IKSerializable** objects, uint32_t count) = 0;
    // vt+0x2c: a texture name -> the texture, or null.
    virtual uint32_t ReadTexture(IKFile* stream, void** texture) = 0;
};

// The object at CKLoadingManager +0x238: a vtable and an atomic reference count at +4; the last release
// calls its vt+0x04 (the deleting destructor). Nothing in the remake sets it yet.
class KRefCounted {
public:
    virtual ~KRefCounted() {}
    uint32_t m_refCount;  // +0x04
};

class CKLoadingManager : public IKLoadingInterfaces {
public:
    DOTD_CLASS_KEY(kCategoryLogic, 7)

    CKLoadingManager();                              // 0x000293c0 CKLoadingManager_Create (inlined constructor)
    ~CKLoadingManager() override;                    // 0x00028e30

    static IKBaseClass* Create();                       // 0x000293c0 CKLoadingManager_Create
    static void Delete(IKBaseClass* object);

    int32_t IsKindOfClass(uint32_t key) override { return key == 0x1cc || key == 0x93e; }  // vt+0x08 0x993b58
    uint32_t ReadHandle(IKFile* stream, IKSerializable** object) override;                // vt+0x24 0x295d8
    uint32_t ReadContiguousHandles(IKFile* stream, IKSerializable** objects, uint32_t count) override;  // vt+0x28 0x29480
    uint32_t ReadTexture(IKFile* stream, void** texture) override;                  // vt+0x2c 0x28250
    void Destroy() override {}                       // vt+0x10 0x993b50 (empty)
    virtual int32_t KUInitialize() { return 1; }     // vt+0x30 0x993b08 (called once after creation; XXL2: KError)
    virtual int32_t KUDestroy() {                    // vt+0x34 0x993b10: Destroy, returning its r3
        Destroy();
        return 1;
    }

    uint32_t LoadGameFile();                         // 0x0002ac30 GAME.KP3 (mode 1); 1 = ok, 0 = aborted
    uint32_t LoadLevel(int32_t level);               // 0x0002a198 LVLnnn\LVLnnn.KP3 (mode 0)
    uint32_t LoadKp3Stream(IKFile* stream, int8_t sector);  // 0x00029e00 (sector -1 = the level file)
    uint32_t LoadLocFile(int32_t language, int32_t mode, int32_t level);  // 0x0002a868 mode 3 GLC, 2 LLC
    void ReadLevelClassTable(IKFile* stream);       // 0x00029700
    void ReadSectorClassCounts(IKFile* stream);     // 0x000290d0
    // 0x0002a420: loads stream `sector` (STRlllss.KP3) when no stream is loaded and its state is 3
    // (unloaded). synchronous = 0 only records the request (no caller does that). The callback, when
    // given, gets (context, sector, ok). Returns 0 when refused.
    typedef void (*SectorLoadedFn)(void* context, int8_t sector, uint8_t ok);
    uint32_t LoadSector(int8_t sector, int32_t synchronous, void* context, SectorLoadedFn callback);
    // 0x00027e68: an encoded object id -> the object (the original overwrites the 4-byte id with the
    // pointer in place; host pointers can be wider, so the port returns it).
    IKSerializable* DecodeObjectId(uint32_t id);
    uint8_t UnloadLevel();                           // 0x00028678 UnloadSector(-1) (Cleanup)
    uint8_t UnloadGameObjects();                     // 0x00028b70 GAME.KP3's objects (Cleanup)
    // 0x000283a8: one stream's objects destroyed, or (-1) the current stream's, then the level's, then the
    // class table freed. Returns 1.
    uint8_t UnloadSector(int8_t sector);

    CKTypeBundleLoad* m_pTypeBundleLoad;          // +0x04 15 groups (new[] with a count cookie)
    CKIDBundleLoad* m_pIdBundleLoad;      // +0x08 every class of the class table, in file order
    IKSerializable** m_apKGameRegisteredInstances;          // +0x0c the GAME object list, in file order
    uint32_t m_ui32KGameNbRegisteredInstances;        // +0x10 2668 for GAME.KP3
    uint32_t m_i32NbLoadedInstances;          // +0x14 objects loaded from the level/sector file
    uint32_t m_ui32NumPointer;                  // +0x18
    uint8_t m_ui8NbStreams;             // +0x1c
    uint8_t m_pad1d[3];
    int32_t m_i32NumCurrentLevel;      // +0x20 (an Int32 here; XXL2: UInt8 m_ui8NumCurrentLevel)
    // +0x24 the loaded streams (sectors); [0] is the current one, -1 = none (the constructor sets all
    // four to 0xff).
    int8_t m_ai8LoadedStream[4];
    int32_t m_aeStreamStates[127];     // +0x28 EStreamState: 0 LOADING, 1 LOADED, 2 UNLOADING, 3 UNLOADED
    int32_t m_eSerializationType;                // +0x224 ESerializationType, or 4..8
    uint32_t m_kGameGUID[4];     // +0x228
    KRefCounted* m_unk238;             // +0x238 a refcounted object (count at +4), released by the destructor; never set yet
};
DOTD_ASSERT_SIZE(CKIDBundleLoad, 0x1c);
DOTD_ASSERT_SIZE(CKTypeBundleLoad, 0xc);
DOTD_ASSERT_SIZE(CKLoadingManager, 0x23c);
DOTD_ASSERT_OFFSET(CKLoadingManager, m_ui32KGameNbRegisteredInstances, 0x10);
DOTD_ASSERT_OFFSET(CKLoadingManager, m_ai8LoadedStream, 0x24);
DOTD_ASSERT_OFFSET(CKLoadingManager, m_eSerializationType, 0x224);
DOTD_ASSERT_OFFSET(CKLoadingManager, m_kGameGUID, 0x228);

// io/Kp3.cpp: the per-category and per-class loops.
int32_t Kp3_LoadCategoryObjects(CKTypeBundleLoad* group, IKFile* stream, int32_t mode, int8_t sector, uint32_t* loaded);  // 0x26300
int32_t Kp3_LoadClassObjects(CKIDBundleLoad* record, IKFile* stream, int32_t mode, int8_t sector, uint32_t* loaded);  // 0x25e80
void Kp3_PostLoadCategory(CKTypeBundleLoad* group, int32_t mode, int8_t sector);           // 0x25bd0
void Kp3_PostLoadClassObjects(CKIDBundleLoad* record, int32_t mode, int8_t sector);  // 0x259b8
int32_t Kp3_UnloadCategory(CKTypeBundleLoad* group, int8_t sector, uint32_t* loaded);  // 0x25d28
void Kp3_UnloadClassObjects(CKIDBundleLoad* record, int8_t sector, uint32_t* loaded);  // 0x256f8

// 0x000534c8 Thread_YieldDuringLoad (renamed from Sysutil_PollDuringLoad_maybe: it only yields). The
// argument is unused.
void Thread_YieldDuringLoad(int32_t unused);

// Development checks (not in the original): each object's, class's and category's end offset is
// compared with the stream position after it is read. A mismatching object is logged and the stream
// is moved to its end, which is how classes whose Load is not ported yet are skipped.
struct KLoadCheckStats {
    uint32_t objects;             // objects whose end offset was checked
    uint32_t objectMismatches;    // ... and that did not end there (skipped to the end)
    uint32_t portedMismatches;    // ... of those, objects whose class's Load is ported: a bug
    uint32_t classMismatches;     // class blocks that did not end at their end offset
    uint32_t categoryMismatches;  // categories that did not end at their end offset
    uint32_t providerFailures;    // globals no owner handed over
    uint32_t nullObjects;         // objects that were null when loaded (UUID misses, provider failures)
};
KLoadCheckStats& Kp3_LoadCheckStats();
struct KLoadReport {
    char file[64];
    KLoadCheckStats stats;
    // DEV (C2.4): the range of RpGeometryReadLog() entries this file's geometries made.
    uint32_t geometriesBegin;
    uint32_t geometriesEnd;
};
// Every file's checks, in load order (Kp3_ReportLoadChecks appends; tests read them).
const KLoadReport* Kp3_LoadReports(uint32_t* count);
// DEV: the objects skipped to their end offset per class name (" [PORTED]" appended for ported classes)
// since the process started, over every file (level_load_test's C2.1 work list).
void Kp3_ForEachSkippedTotal(void (*visit)(const char* className, uint32_t count, void* context), void* context);
// DEV: objects about to be destroyed by an unload leave the Kp3_DumpObjects list (they are freed).
void Kp3_ForgetLoadedObjects(const void* begin, const void* end);
void Kp3_CheckObjectEnd(IKFile* stream, uint32_t end, IKSerializable* object);
// DEV: every placeholder's Load calls it (Kp3Stubs.h). A ported object whose Load ran placeholder Loads
// and then misses its end is counted as skipped "via placeholders", not as a ported-class mismatch.
void Kp3_NotePlaceholderLoad();
void Kp3_ReportLoadChecks(const char* file);
// DEV: the loaded objects of the ported classes, for work/objects_diff.py (Kp3.cpp). false = not written.
bool Kp3_DumpObjects(const char* path);
// 0x00028ad8 GetObjectDatabaseInstance: object `instance` of class `classIndex` of category `category` in the loading
// manager's class table: in a contiguous array (the record's instantiation byte set), the object itself for a class of
// one object, else from the pointer array.
void* GetObjectDatabaseInstance(CKLoadingManager* database, uint32_t category, uint32_t classIndex, uint32_t instance);
// DEV: calls `visit` for every loaded object in load order (class key = the loader's, as FindClassInfo takes).
void Kp3_ForEachLoadedObject(void (*visit)(IKSerializable* object, uint32_t classKey, void* context), void* context);
