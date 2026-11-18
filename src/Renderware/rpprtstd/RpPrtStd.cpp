// RpPrtStd.cpp - the RpPrtStd plugin's loading side, ported from the PS3 library code (TOC 0xc25974,
// 0x729798-0x735xxx). See RpPrtStd.h for the native layout.
//
//   [x] 0x7297c8  RpPrtStdEClassSetCallBackArray_maybe
//   [x] 0x729960  RpPrtStdEClassFindByID_maybe
//   [x] 0x7299a0  RpPrtStdEClassFindByPropTab_maybe
//   [x] 0x7299e8  RpPrtStdEClassSetPropTab_maybe
//   [x] 0x729c18  RpPrtStdEClassCreate_maybe
//   [x] 0x729cf8  RpPrtStdEClassStreamRead_maybe
//   [x] 0x729f60  RpPrtStdEClassDestroy_maybe
//   [x] 0x72a408  RpPrtStd_CircularListPush_maybe_3 (and the identical _2, _4, the unnamed one)
//   [x] 0x72b198  RpPrtStdEmitterInit_maybe
//   [x] 0x72b2f0  RpPrtStdEmitterAlloc_maybe (inlined in the stream read and the clone)
//   [x] 0x72c820  RpPrtStdEmitterDestruct_maybe
//   [x] 0x72cad0  RpPrtStdEmitterDestroy_maybe
//   [x] 0x72cb68  RpPrtStdEmitterStreamRead_maybe
//   [x] 0x72d180  RpPrtStdEmitterClone_maybe
//   [x] 0x72d688  RpPrtStdPClassFindByID_maybe
//   [x] 0x72d6c8  RpPrtStdPClassFindByPropTab_maybe
//   [x] 0x72d710  RpPrtStdPClassSetPropTab_maybe
//   [x] 0x72d938  RpPrtStdPClassCreate_maybe
//   [x] 0x72d9e8  RpPrtStdPClassStreamRead_maybe
//   [x] 0x72dbf8  RpPrtStdPClassDestroy_maybe
//   [x] 0x72ddb8  RpPrtStdEmitterStd_InitDefaults_maybe
//   [x] 0x72ddf8  RpPrtStdEmitterStd_Copy_maybe
//   [x] 0x72e028  RpPrtStdEmitterHeader_StreamRead_maybe
//   [x] 0x72e1e8  RpPrtStdPTankData_Release_maybe
//   [x] 0x72ec28  RpPrtStdPropTabDestroy_maybe
//   [x] 0x72edd0  RpPrtStdPropTabGetInfo_maybe (inlined: the tables' fields are read directly)
//   [x] 0x72ee20  RpPrtStdPropTabGetPropIndex
//   [x] 0x72ee88  RW_GetParticlePropertyOffset
//   [x] 0x72ef08  RpPrtStdPropTabFindByID_maybe
//   [x] 0x72f1b8  RpPrtStdPropTabGetOrCreate_maybe
//   [x] 0x72f7b0  RpPrtStdPropTabStreamRead_maybe
//   [x] 0x72fb70  RpPrtStdGlobalGetStreamVersion_maybe (g_streamVersion)
//   [x] 0x72fca8  RpPrtStdAtomicGetEmitter_maybe
//   [x] 0x72ffe0  RpPrtStdAtomicAddEmitter_maybe
//   [x] 0x730158  RpPrtStdAtomicPlugin_Dtor_maybe
//   [x] 0x7301e0  RpPrtStdAtomicStreamRead_maybe
//   [x] 0x730298  RpPrtStdAtomicPlugin_Copy_maybe
//   [x] 0x731408  RpPrtStdEmitterStd_Init_maybe
//   [x] 0x731c98  RpPrtStdEmitterStd_StreamRead_maybe
//   [x] 0x7323a8  RpPrtStdEmitterStdCloneCB_maybe
//   [x] 0x732bd0  RpPrtStdEmitterStd_Destruct_maybe
//   [x] 0x6ef3b0  RpPrtStd_ClearStdClassIfMatch_maybe (RpPrtAdv's table destroy hook)
//   [x] 0x6efe48  _rpPrtStdPropTabFixupLegacy_maybe (RpPrtAdv's table setup hook)
// The running side: RpPrtStdRuntime.cpp, RpPrtStdEmit.cpp, RpPrtStdUpdate.cpp.
#include "Renderware/rpprtstd/RpPrtStd.h"

#include <cstdlib>
#include <cstring>
#include <vector>

#include "Renderware/rpprtstd/RpPrtStdInternal.h"
#include "Renderware/rpprtstd/RpPrtStdRuntime.h"
#include "Renderware/rpworld/RpAtomic.h"
#include "Renderware/rpworld/RpGeometry.h"
#include "Renderware/rwcore/RwCamera.h"
#include "Renderware/rwcore/RwMatrix.h"
#include "k2000/core/Stub.h"
#include "k2000/io/IKFile.h"

namespace rpprtstd {
int32_t g_streamVersion = 0;
}  // namespace rpprtstd

using rpprtstd::Stream;
using rpprtstd::g_streamVersion;

namespace {

RpPrtStdEmitterClass* s_eClasses = nullptr;   // 0x00cfbad4
RpPrtStdParticleClass* s_pClasses = nullptr;  // 0x00cfbad8
RpPrtStdPropertyTable* s_propTabs = nullptr;  // 0x00cfbadc
std::vector<int32_t> s_roundedSizes;          // 0x00cfbaf4 / 0x00cfbaf8: GetOrCreate's scratch
std::vector<int32_t> s_streamTable;           // RpPrtStd globals +0x88 / +0x8c: the stream's ids and sizes
RpPrtStdShimStats s_stats = {};               // DEV

// The native growth of an emitter property: the emitter header, the standard property, the PTank property
// and the point list hold pointers (see RpPrtStd.h, RpPrtStdRuntime.h). Particle properties hold none.
int32_t NativeGrowth(int32_t propID, bool emitterTable) {
    if (!emitterTable) return 0;
    if (propID == rpPRTSTDPROPERTYCODEEMITTER) return static_cast<int32_t>(sizeof(RpPrtStdEmitter)) - 0x28;
    if (propID == rpPRTSTDPROPERTYCODEEMITTERSTANDARD)
        return static_cast<int32_t>(sizeof(RpPrtStdEmitterStandard)) - 0xb4;
    if (propID == rpPRTSTDPROPERTYCODEEMITTERPTANK) return static_cast<int32_t>(sizeof(RpPrtStdEmitterPTank)) - 0x34;
    if (propID == rpPRTADVPROPERTYCODEEMITTERPOINTLIST)
        return static_cast<int32_t>(sizeof(RpPrtAdvEmtPointList)) - 0x18;
    if (propID == rpPRTADVPROPERTYCODEEMITTERPRTEMITTER) return static_cast<int32_t>(sizeof(RpPrtAdvEmtPrtEmt)) - 0x14;
    return 0;
}

// RpPrtStd_CircularListPush_maybe_3 (0x72a408; the emitter lists): `item` after `list`'s head, and the
// new head.
RpPrtStdEmitter* PushEmitter(RpPrtStdEmitter* list, RpPrtStdEmitter* item) {
    if (list != nullptr) {
        item->next = list->next;
        list->next = item;
        return item;
    }
    item->next = item;
    return item;
}

// Whether `table` holds exactly these properties: the same count, and each stream id found with the stream
// size equal to the table's ROUNDED size. BUG(original): the stream sizes are compared with the rounded
// sizes, so a table only matches when every size is a multiple of 16 (DotD's tables never match).
bool TableMatches(const RpPrtStdPropertyTable* table, int32_t numProp, const int32_t* ids, const int32_t* sizes) {
    if (table->numProp != numProp) return false;
    for (int32_t i = 0; i < numProp; ++i) {
        int32_t j = 0;
        while (table->propID[j] != ids[i]) {
            if (++j == numProp) return false;
        }
        if (sizes[i] != table->propSize[j]) return false;
    }
    return true;
}

RpPrtStdPropertyTable* FindMatchingTable(int32_t numProp, const int32_t* ids, const int32_t* sizes) {
    RpPrtStdPropertyTable* table = s_propTabs;
    if (table == nullptr) return nullptr;
    do {
        if (TableMatches(table, numProp, ids, sizes)) return table;
        table = table->next;
    } while (table != s_propTabs);
    return nullptr;
}

// 0x0072f1b8 RpPrtStdPropTabGetOrCreate_maybe: an equal table (one more reference), or a new one: the sizes
// rounded up to 16, the offsets their running sum (the last entry the total), the id a hash of the ids.
// `emitterTable`: native only (which growth applies).
RpPrtStdPropertyTable* PropTabGetOrCreate(int32_t numProp, const int32_t* ids, const int32_t* sizes, bool emitterTable) {
    if (static_cast<int32_t>(s_roundedSizes.size()) < numProp) s_roundedSizes.resize(numProp);
    int32_t idSum = 0;
    for (int32_t i = 0; i < numProp; ++i) {
        s_roundedSizes[i] = (sizes[i] + NativeGrowth(ids[i], emitterTable) + 0xf) & ~0xf;
        idSum += ids[i];
    }
    const uint32_t hashHigh = numProp < 1 ? 0u : static_cast<uint32_t>(idSum >> 10);
    const uint32_t hashLow = numProp < 1 ? 0u : static_cast<uint32_t>(idSum) << 10;
    if (RpPrtStdPropertyTable* existing = FindMatchingTable(numProp, ids, sizes)) {
        ++existing->refCount;
        return existing;
    }
    // One allocation (numProp * 16 + 0x47 bytes, the table 16-byte aligned in it): here the table, then the
    // four arrays (ids, offsets, rounded sizes, stream sizes; numProp + 1 entries each).
    RpPrtStdPropertyTable* table = new RpPrtStdPropertyTable();
    int32_t* arrays = new int32_t[4 * (numProp + 1)]();
    table->propPtr = arrays;
    table->refCount = 1;
    table->maxProp = 0;
    table->propID = arrays;
    table->propOffset = arrays + (numProp + 1);
    table->propSize = arrays + 2 * (numProp + 1);
    table->propSizeUA = arrays + 3 * (numProp + 1);
    if (numProp > 0) std::memcpy(table->propID, ids, numProp * sizeof(int32_t));
    int32_t offset = 0;
    for (int32_t i = 0; i < numProp; ++i) {
        table->propOffset[i] = offset;
        table->propSizeUA[i] = sizes[i];
        table->propSize[i] = s_roundedSizes[i];
        offset += s_roundedSizes[i];
    }
    table->propOffset[numProp > 0 ? numProp : 0] = offset;
    table->numProp = numProp;
    table->id = static_cast<int32_t>(hashHigh | (static_cast<uint32_t>(numProp * 0x10 + 0x10) & 0xffffu) | hashLow);
    table->next = table;
    if (s_propTabs != nullptr) {
        table->next = s_propTabs->next;
        s_propTabs->next = table;
    }
    s_propTabs = table;
    return table;
}

// 0x0072ef08 RpPrtStdPropTabFindByID_maybe
RpPrtStdPropertyTable* PropTabFindByID(int32_t id) {
    RpPrtStdPropertyTable* table = s_propTabs;
    if (table == nullptr) return nullptr;
    do {
        if (table->id == id) return table;
        table = table->next;
    } while (table != s_propTabs);
    return nullptr;
}

// Unlinks `item` from a circular list whose head is `head` (the destroys' common part): the head moves to
// the item's predecessor, or the list empties.
template <typename T, typename Next>
void Unlink(T*& head, T* item, Next nextOf) {
    if (head == nullptr) return;
    if (nextOf(item) == item && head == item) {
        head = nullptr;
        return;
    }
    T* previous = head;
    while (nextOf(previous) != item) {
        previous = nextOf(previous);
        if (previous == head) return;  // not in the list
    }
    nextOf(previous) = nextOf(item);
    nextOf(item) = item;
    if (head == item) head = previous;
}

// 0x006ef3b0 RpPrtStd_ClearStdClassIfMatch_maybe (the destroy hook RpPrtAdv's open, 0x6efe00, puts at
// globals +0x78): RpPrtAdv's cached tables (0x00cf9e14 particle, else 0x00cf9e10 emitter) forget a destroyed
// table. The 0x1000001 update's cache (0x00cf9e18) is not cleared.
void AdvForgetTable(const RpPrtStdPropertyTable* table) {
    if (rpprtstd::g_advOffsets.particleTable == table) {
        rpprtstd::g_advOffsets.particleTable = nullptr;
    } else if (rpprtstd::g_advOffsets.emitterTable == table) {
        rpprtstd::g_advOffsets.emitterTable = nullptr;
    }
}

// 0x0072ec28 RpPrtStdPropTabDestroy_maybe: one reference less; at none, unlinked, forgotten by the offset
// cache (0x00cfbb08 particle table, else 0x00cfbb04 emitter table) and the destroy hook (globals +0x78),
// and freed.
int32_t PropTabDestroy(RpPrtStdPropertyTable* table) {
    if (table == nullptr) return 0;
    if (--table->refCount > 0) return 1;
    Unlink(s_propTabs, table, [](RpPrtStdPropertyTable* t) -> RpPrtStdPropertyTable*& { return t->next; });
    if (rpprtstd::g_offsets.particleTable == table) {
        rpprtstd::g_offsets.particleTable = nullptr;
    } else if (rpprtstd::g_offsets.emitterTable == table) {
        rpprtstd::g_offsets.emitterTable = nullptr;
    }
    AdvForgetTable(table);
    rpprtstd::g_propTabDestroyGeneration.fetch_add(1, std::memory_order_release);  // DEV: the other threads' caches
    delete[] table->propPtr;
    delete table;
    return 1;
}

// 0x006efe48 _rpPrtStdPropTabFixupLegacy_maybe (the setup hook RpPrtAdv's open puts at globals +0x74, run
// on every table read): streams before version 3 stored the advanced properties without their stride
// words. The particle table (its first size 0x10) shrinks multi colour / tex coords step / size by 0xc and
// multi tex coords by 0x14 (the rounded size from the old stream size + 3, resp. - 5); the emitter table
// grows them by 0xc / 0x14 (rounded from + 0x1b / + 0x23). Then the offsets from the first size on, the last
// entry the total.
void PropTabFixupLegacy(RpPrtStdPropertyTable* table) {
    if (g_streamVersion > 2) return;
    const int32_t numProp = table->numProp;
    int32_t offset = table->propSize[0];
    const bool particle = offset == 0x10;
    for (int32_t i = 1; i < numProp; ++i) {
        const int32_t id = table->propID[i];
        const int32_t old = table->propSizeUA[i];
        int32_t size = table->propSize[i];
        int32_t unaligned = old;
        if (particle) {
            if (id == rpPRTADVPROPERTYCODEEMITTERPRTMULTICOLOR || id == rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDSSTEP ||
                id == rpPRTADVPROPERTYCODEEMITTERPRTMULTISIZE) {
                size = static_cast<int32_t>(static_cast<uint32_t>(old + 3) & 0xfffffff0u);
                unaligned = old - 0xc;
            } else if (id == rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDS) {
                size = static_cast<int32_t>(static_cast<uint32_t>(old - 5) & 0xfffffff0u);
                unaligned = old - 0x14;
            }
        } else {
            if (id == rpPRTADVPROPERTYCODEEMITTERPRTMULTICOLOR || id == rpPRTADVPROPERTYCODEEMITTERPRTMULTISIZE) {
                size = static_cast<int32_t>(static_cast<uint32_t>(old + 0x1b) & 0xfffffff0u);
                unaligned = old + 0xc;
            } else if (id == rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDS ||
                       id == rpPRTADVPROPERTYCODEEMITTERPRTMULTITEXCOORDSSTEP) {
                size = static_cast<int32_t>(static_cast<uint32_t>(old + 0x23) & 0xfffffff0u);
                unaligned = old + 0x14;
            }
        }
        table->propSizeUA[i] = unaligned;
        table->propSize[i] = size;
        table->propOffset[i] = offset;
        offset += table->propSize[i];
    }
    // With fewer than two properties the total goes to entry 1 (the PS3's arrays always have room for it).
    table->propOffset[numProp > 1 ? numProp : 1] = offset;
}

// 0x0072f7b0 RpPrtStdPropTabStreamRead_maybe: id, count, the ids, the sizes; an equal table is shared.
// `emitterTable`: native only (see PropTabGetOrCreate).
RpPrtStdPropertyTable* PropTabStreamRead(Stream* stream, bool emitterTable) {
    const int32_t id = stream->ReadInt32();
    const int32_t numProp = stream->ReadInt32();
    const int32_t count = numProp < 1 ? 0 : numProp;
    if (static_cast<int32_t>(s_streamTable.size()) < 2 * count) s_streamTable.resize(2 * count);
    int32_t* ids = s_streamTable.data();
    int32_t* sizes = ids + count;
    if (count > 0) {
        stream->ReadWords(ids, count * 4);
        stream->ReadWords(sizes, count * 4);
    }
    RpPrtStdPropertyTable* table = FindMatchingTable(numProp, ids, sizes);
    if (table != nullptr) {
        ++table->refCount;
    } else {
        table = PropTabGetOrCreate(numProp, ids, sizes, emitterTable);
    }
    if (table != nullptr) table->id = id;
    // Streams before version 3: in a table whose first size is not 0x10 (the emitter table) the standard
    // property (1) grows by 0xc (the size rounded from the old stream size + 0x1b; natively plus its pointer
    // growth), and the offsets are laid out again from the first size, the last entry the total.
    // BUG(original): the table is used without a null check (an allocation failure).
    if (g_streamVersion < 3 && table->propSize[0] != 0x10) {
        int32_t offset = table->propSize[0];
        const int32_t numProp = table->numProp;
        for (int32_t i = 1; i < numProp; ++i) {
            if (table->propID[i] == rpPRTSTDPROPERTYCODEEMITTERSTANDARD) {
                const int32_t old = table->propSizeUA[i];
                table->propSizeUA[i] = old + 0xc;
                table->propSize[i] = static_cast<int32_t>(
                    static_cast<uint32_t>(old + 0x1b + NativeGrowth(rpPRTSTDPROPERTYCODEEMITTERSTANDARD, emitterTable)) &
                    0xfffffff0u);
            }
            table->propOffset[i] = offset;
            offset += table->propSize[i];
        }
        table->propOffset[numProp > 1 ? numProp : 1] = offset;
    }
    PropTabFixupLegacy(table);  // the setup hook (globals +0x74); it returns at once for version 3
    return table;
}

// 0x00729960 / 0x007299a0 RpPrtStdEClassFindByID_maybe / FindByPropTab_maybe
RpPrtStdEmitterClass* EClassFindByID(int32_t id) {
    RpPrtStdEmitterClass* eClass = s_eClasses;
    if (eClass == nullptr) return nullptr;
    do {
        if (eClass->id == id) return eClass;
        eClass = eClass->next;
    } while (eClass != s_eClasses);
    return nullptr;
}
RpPrtStdEmitterClass* EClassFindByPropTab(const RpPrtStdPropertyTable* table) {
    RpPrtStdEmitterClass* eClass = s_eClasses;
    if (eClass == nullptr) return nullptr;
    do {
        if (eClass->propTab == table) return eClass;
        eClass = eClass->next;
    } while (eClass != s_eClasses);
    return nullptr;
}
// 0x0072d688 / 0x0072d6c8 RpPrtStdPClassFindByID_maybe / FindByPropTab_maybe
RpPrtStdParticleClass* PClassFindByID(int32_t id) {
    RpPrtStdParticleClass* pClass = s_pClasses;
    if (pClass == nullptr) return nullptr;
    do {
        if (pClass->id == id) return pClass;
        pClass = pClass->next;
    } while (pClass != s_pClasses);
    return nullptr;
}
RpPrtStdParticleClass* PClassFindByPropTab(const RpPrtStdPropertyTable* table) {
    RpPrtStdParticleClass* pClass = s_pClasses;
    if (pClass == nullptr) return nullptr;
    do {
        if (pClass->propTab == table) return pClass;
        pClass = pClass->next;
    } while (pClass != s_pClasses);
    return nullptr;
}

template <typename T>
void InsertClass(T*& head, T* item) {
    item->next = item;
    if (head != nullptr) {
        item->next = head->next;
        head->next = item;
    }
    head = item;
}

// The classes' object size: the sum of the table's rounded sizes (0x7299e8, 0x72d710, the stream reads).
int32_t TableObjectSize(const RpPrtStdPropertyTable* table) {
    int32_t size = 0;
    for (int32_t i = 0; i < table->numProp; ++i) size += table->propSize[i];
    return size;
}

// 0x00729c18 RpPrtStdEClassCreate_maybe. BUG(original): the id is left as a stack address (the callers
// set it).
RpPrtStdEmitterClass* EClassCreate() {
    RpPrtStdEmitterClass* eClass = new RpPrtStdEmitterClass();
    eClass->refCount = 1;
    InsertClass(s_eClasses, eClass);
    return eClass;
}
// 0x007299e8 RpPrtStdEClassSetPropTab_maybe
void EClassSetPropTab(RpPrtStdEmitterClass* eClass, RpPrtStdPropertyTable* table) {
    if (eClass->propTab != nullptr) PropTabDestroy(eClass->propTab);
    ++table->refCount;
    eClass->propTab = table;
    eClass->objSize = TableObjectSize(table);
}
// 0x00729f60 RpPrtStdEClassDestroy_maybe
void EClassDestroy(RpPrtStdEmitterClass* eClass) {
    if (--eClass->refCount > 0) return;
    Unlink(s_eClasses, eClass, [](RpPrtStdEmitterClass* c) -> RpPrtStdEmitterClass*& { return c->next; });
    delete[] eClass->callback;
    if (eClass->propTab != nullptr) PropTabDestroy(eClass->propTab);
    delete eClass;
}
// 0x00729cf8 RpPrtStdEClassStreamRead_maybe: id and table id; a class of that id is shared.
RpPrtStdEmitterClass* EClassStreamRead(Stream* stream) {
    const int32_t id = stream->ReadInt32();
    const int32_t tableID = stream->ReadInt32();
    if (RpPrtStdEmitterClass* existing = EClassFindByID(id)) {
        ++existing->refCount;
        return existing;
    }
    RpPrtStdEmitterClass* eClass = EClassCreate();
    RpPrtStdPropertyTable* table = PropTabFindByID(tableID);
    ++table->refCount;
    eClass->propTab = table;
    eClass->objSize = TableObjectSize(table);
    eClass->id = id;
    eClass->callback = nullptr;
    eClass->numCallback = 0;
    rpprtstd::EClassBuildCallBackArray(eClass);  // the globals' setup callback (+0x6c)
    return eClass;
}

// 0x0072d938 RpPrtStdPClassCreate_maybe
RpPrtStdParticleClass* PClassCreate() {
    RpPrtStdParticleClass* pClass = new RpPrtStdParticleClass();
    pClass->refCount = 1;
    InsertClass(s_pClasses, pClass);
    return pClass;
}
// 0x0072d710 RpPrtStdPClassSetPropTab_maybe
void PClassSetPropTab(RpPrtStdParticleClass* pClass, RpPrtStdPropertyTable* table) {
    if (pClass->propTab != nullptr) PropTabDestroy(pClass->propTab);
    ++table->refCount;
    pClass->propTab = table;
    pClass->objSize = TableObjectSize(table);
}
// 0x0072dbf8 RpPrtStdPClassDestroy_maybe
void PClassDestroy(RpPrtStdParticleClass* pClass) {
    if (--pClass->refCount > 0) return;
    Unlink(s_pClasses, pClass, [](RpPrtStdParticleClass* c) -> RpPrtStdParticleClass*& { return c->next; });
    if (pClass->propTab != nullptr) PropTabDestroy(pClass->propTab);
    delete pClass;
}
// The particle class setup callback (globals +0x70: RpPrtStdPClass_BuildStdCallBackArray_maybe 0x6ef410).
void PClassSetup(RpPrtStdParticleClass* pClass) { rpprtstd::PClassBuildCallBackArray(pClass); }
// 0x0072d9e8 RpPrtStdPClassStreamRead_maybe
RpPrtStdParticleClass* PClassStreamRead(Stream* stream) {
    const int32_t id = stream->ReadInt32();
    const int32_t tableID = stream->ReadInt32();
    if (RpPrtStdParticleClass* existing = PClassFindByID(id)) {
        ++existing->refCount;
        return existing;
    }
    RpPrtStdParticleClass* pClass = PClassCreate();
    RpPrtStdPropertyTable* table = PropTabFindByID(tableID);
    ++table->refCount;
    pClass->propTab = table;
    pClass->objSize = TableObjectSize(table);
    pClass->id = id;
    PClassSetup(pClass);
    return pClass;
}

// 0x0072ddb8 RpPrtStdEmitterStd_InitDefaults_maybe: the PTank property's defaults.
void PTankInitDefaults(RpPrtStdEmitterPTank* ptank) {
    ptank->emitFlags = 0xffffffffu;
    ptank->dataOutPtrs = nullptr;
    ptank->strDstBlend = 2;
    ptank->strVtxABlend = 1;
    ptank->dataFlags = 0;
    ptank->platFlags = 0;
    ptank->updateFlags = 0xffffffffu;
    ptank->maxPrt = 0;
    ptank->pTank = nullptr;
    ptank->dataInPtrs = nullptr;
    ptank->strSrcBlend = 2;
}

// 0x0072ddf8 RpPrtStdEmitterStd_Copy_maybe: the PTank property's settings (words 0, 1, 3, 4, 5, 10, 11, 12).
void PTankCopy(RpPrtStdEmitterPTank* dst, const RpPrtStdEmitterPTank* src) {
    dst->dataFlags = src->dataFlags;
    dst->platFlags = src->platFlags;
    dst->maxPrt = src->maxPrt;
    dst->updateFlags = src->updateFlags;
    dst->emitFlags = src->emitFlags;
    dst->strSrcBlend = src->strSrcBlend;
    dst->strDstBlend = src->strDstBlend;
    dst->strVtxABlend = src->strVtxABlend;
}

// 0x0072e028 RpPrtStdEmitterHeader_StreamRead_maybe (the PTank property). The update and emit flags are raw
// reads (RwStreamRead): the PS3 word is the file's bytes as they are, the byte-reversed little-endian value.
void PTankStreamRead(Stream* stream, RpPrtStdEmitterPTank* ptank) {
    uint8_t raw[4];
    for (uint32_t* flags : {&ptank->updateFlags, &ptank->emitFlags}) {
        stream->Read(raw, 4);
        *flags = (static_cast<uint32_t>(raw[0]) << 24) | (static_cast<uint32_t>(raw[1]) << 16) |
                 (static_cast<uint32_t>(raw[2]) << 8) | raw[3];
    }
    stream->ReadWords(&ptank->strSrcBlend, 4);
    stream->ReadWords(&ptank->strDstBlend, 4);
    stream->ReadWords(&ptank->strVtxABlend, 4);
}

// 0x00731408 RpPrtStdEmitterStd_Init_maybe (create, slot 5): the standard property's defaults and the
// emitter flags 0x7f. TOC 0x00c222ac = 1.0.
RpPrtStdEmitter* StdInit(RpAtomic*, RpPrtStdEmitter* emitter, void*) {
    const int32_t offset = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERSTANDARD);
    if (offset < 0) return emitter;
    RpPrtStdEmitterStandard* std = reinterpret_cast<RpPrtStdEmitterStandard*>(rpprtstd::PropertyAt(emitter, offset));
    emitter->flag |= 0x7f;
    std->prtUV[3] = 1.0f;
    std->texture = nullptr;
    std->seed = 1;
    std->prtColor.alpha = 0xff;
    std->prtDelta2DRotate = 0.0f;
    std->maxPrt = 0;
    std->prtSize.x = 1.0f;
    std->prtSize.y = 1.0f;
    std->prtColor.red = 0xff;
    std->prtColor.green = 0xff;
    std->prtColor.blue = 0xff;
    std->prtUV[0] = 0.0f;
    std->prtUV[1] = 0.0f;
    std->prtUV[2] = 1.0f;
    std->prtUV[4] = 0.0f;
    std->prtUV[5] = 0.0f;
    std->prtUV[6] = 0.0f;
    std->prtUV[7] = 0.0f;
    return emitter;
}

// The RW matrix in a property (RwMatrixStreamRead 0x7572e0 after RwStreamFindChunk(rwID_MATRIX)): the
// struct chunk's right, up, at, pos and type; orthonormalised when the type says so.
void MatrixStreamRead(Stream* stream, uint8_t* out) {
    uint32_t length = 0;
    if (stream->FindChunk(1, &length) == 0) return;
    uint32_t w[13] = {};
    std::vector<uint8_t> bytes(length > 0x34u ? length : 0x34u, 0);
    stream->ReadWords(bytes.data(), length & ~3u);
    std::memcpy(w, bytes.data(), sizeof w);
    RwMatrix matrix;
    std::memset(&matrix, 0, sizeof matrix);
    std::memcpy(&matrix.right, &w[0], 12);
    std::memcpy(&matrix.up, &w[3], 12);
    std::memcpy(&matrix.at, &w[6], 12);
    std::memcpy(&matrix.pos, &w[9], 12);
    matrix.flags = w[12] & rwMATRIXTYPEMASK;
    if (matrix.flags == rwMATRIXTYPEORTHONORMAL) RwMatrixOrthoNormalize(&matrix, &matrix);
    std::memcpy(out, &matrix, sizeof matrix);
}

// _rwStringStreamFindAndRead (RW 3.7 core/src/babinary.c) for the 8-bit string chunk (rwID_STRING 2) the
// game's data holds: the chunk's bytes, at most `capacity` - 1 kept. 0 when the chunk is missing.
int32_t StringStreamFindAndRead(Stream* stream, char* out, uint32_t capacity) {
    uint32_t length = 0;
    if (stream->FindChunk(2, &length) == 0) return 0;
    std::vector<char> bytes(length + 1, 0);
    stream->Read(bytes.data(), length);
    std::strncpy(out, bytes.data(), capacity - 1);
    out[capacity - 1] = 0;
    return 1;
}

// RwTextureStreamRead (RW 3.7 core/src/babintex.c, reached through a TOC bridge): within the texture
// chunk, the filter/addressing struct, the name and mask strings, then RwTextureRead(name, mask); the
// extension chunks are skipped (the caller moves past the texture chunk). STUB: the mipmapping globals
// it saves and restores and the filter/addressing applied to a texture read the first time (refCount 1)
// are not modelled; the texture comes from the shim's dictionaries (FindTextureByName).
RwTexture* TextureStreamRead(Stream* stream) {
    uint32_t length = 0;
    if (stream->FindChunk(1, &length) == 0) return nullptr;
    stream->Skip(length);  // filterAndAddress
    char name[0x80] = {};
    char mask[0x80] = {};
    if (StringStreamFindAndRead(stream, name, sizeof name) == 0) return nullptr;
    if (StringStreamFindAndRead(stream, mask, sizeof mask) == 0) return nullptr;
    return static_cast<RwTexture*>(FindTextureByName(name));
}

// 0x00731c98 RpPrtStdEmitterStd_StreamRead_maybe (slot 7): the standard properties in the order 1, 2, 3,
// 8, 5, 4, 6.
RpPrtStdEmitter* StdStreamRead(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    Stream* stream = static_cast<Stream*>(data);
    int32_t offset = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERSTANDARD);
    if (offset >= 0) {
        RpPrtStdEmitterStandard* std =
            reinterpret_cast<RpPrtStdEmitterStandard*>(rpprtstd::PropertyAt(emitter, offset));
        stream->ReadWords(&std->seed, 4);
        stream->ReadWords(&std->maxPrt, 4);
        stream->ReadWords(&std->force, 12);
        stream->ReadWords(&std->unk1c, 4);
        stream->ReadWords(&std->emtPos, 12);
        stream->ReadWords(&std->emtSize, 12);
        stream->ReadWords(&std->emtEmitGap, 4);
        stream->ReadWords(&std->emtEmitGapBias, 4);
        stream->ReadWords(&std->emtPrtEmit, 4);
        stream->ReadWords(&std->emtPrtEmitBias, 4);
        stream->ReadWords(&std->prtInitVel, 4);
        stream->ReadWords(&std->prtInitVelBias, 4);
        stream->ReadWords(&std->prtLife, 4);
        stream->ReadWords(&std->prtLifeBias, 4);
        stream->ReadWords(&std->prtInitDir, 12);
        stream->ReadWords(&std->prtInitDirBias, 12);
        // prtSize: 12 bytes, as the original reads (its third word lands on the colour, read next).
        stream->ReadWords(&std->prtSize, 12);
        // prtColor: an Int32 whose bytes go most significant first.
        const uint32_t color = static_cast<uint32_t>(stream->ReadInt32());
        std->prtColor.red = static_cast<uint8_t>(color >> 24);
        std->prtColor.green = static_cast<uint8_t>(color >> 16);
        std->prtColor.blue = static_cast<uint8_t>(color >> 8);
        std->prtColor.alpha = static_cast<uint8_t>(color);
        for (uint32_t i = 0; i < 4; ++i) stream->ReadWords(&std->prtUV[i * 2], 8);
        stream->ReadWords(&std->unkB0, 4);
        const int32_t hasTexture = stream->ReadInt32();
        uint32_t length = 0;
        if (hasTexture >= 1 && stream->FindChunk(6, &length) != 0) {
            const uint32_t end = stream->position + length;
            std->texture = TextureStreamRead(stream);
            stream->position = end;
        }
        if (g_streamVersion > 2) stream->ReadWords(&std->prtDelta2DRotate, 4);
    }
    offset = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERPRTCOLOR);
    if (offset >= 0) stream->ReadWords(rpprtstd::PropertyAt(emitter, offset), 0x40);
    offset = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERPRTTEXCOORDS);
    if (offset >= 0) stream->ReadWords(rpprtstd::PropertyAt(emitter, offset), 0x40);
    offset = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERPRTMATRIX);
    if (offset >= 0) {
        uint8_t* matrix = rpprtstd::PropertyAt(emitter, offset);
        stream->FindChunk(0xd, nullptr);  // rwID_MATRIX
        MatrixStreamRead(stream, matrix);
        stream->ReadWords(matrix + 0x40, 12);
        stream->ReadWords(matrix + 0x4c, 12);
        stream->ReadWords(matrix + 0x58, 12);
        stream->ReadWords(matrix + 0x64, 12);
        stream->ReadWords(matrix + 0x70, 4);
    }
    offset = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERPRTSIZE);
    if (offset >= 0) stream->ReadWords(rpprtstd::PropertyAt(emitter, offset), 0x20);
    offset = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERPRT2DROTATE);
    if (offset >= 0) stream->ReadWords(rpprtstd::PropertyAt(emitter, offset), 0x10);
    offset = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERPTANK);
    if (offset >= 0)
        PTankStreamRead(stream, reinterpret_cast<RpPrtStdEmitterPTank*>(rpprtstd::PropertyAt(emitter, offset)));
    return emitter;
}

// 0x007323a8 RpPrtStdEmitterStdCloneCB_maybe (slot 10): the standard properties copied into `data`.
RpPrtStdEmitter* StdClone(RpAtomic*, RpPrtStdEmitter* emitter, void* data) {
    RpPrtStdEmitter* clone = static_cast<RpPrtStdEmitter*>(data);
    struct Copy {
        int32_t propID;
        uint32_t bytes;
    };
    int32_t from = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERSTANDARD);
    int32_t to = rpprtstd::EmitterPropOffset(clone, rpPRTSTDPROPERTYCODEEMITTERSTANDARD);
    // BUG(original): the clone's offset is tested against 0, not -1. The texture's reference count (+0x54)
    // goes up.
    if (from >= 0 && to != 0) {
        std::memcpy(rpprtstd::PropertyAt(clone, to), rpprtstd::PropertyAt(emitter, from),
                    sizeof(RpPrtStdEmitterStandard));
        RwTexture* texture = reinterpret_cast<RpPrtStdEmitterStandard*>(rpprtstd::PropertyAt(clone, to))->texture;
        if (texture != nullptr) TextureRef_AddRef(texture);
    }
    static const Copy kCopies[] = {
        {rpPRTSTDPROPERTYCODEEMITTERPRTCOLOR, 0x40},
        {rpPRTSTDPROPERTYCODEEMITTERPRTTEXCOORDS, 0x40},
        {rpPRTSTDPROPERTYCODEEMITTERPRTMATRIX, 0x80},
        {rpPRTSTDPROPERTYCODEEMITTERPRTSIZE, 0x20},
        {rpPRTSTDPROPERTYCODEEMITTERPRT2DROTATE, 0x10},
    };
    for (const Copy& copy : kCopies) {
        from = rpprtstd::EmitterPropOffset(emitter, copy.propID);
        to = rpprtstd::EmitterPropOffset(clone, copy.propID);
        if (from >= 0 && to >= 0)
            std::memcpy(rpprtstd::PropertyAt(clone, to), rpprtstd::PropertyAt(emitter, from), copy.bytes);
    }
    from = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERPTANK);
    to = rpprtstd::EmitterPropOffset(clone, rpPRTSTDPROPERTYCODEEMITTERPTANK);
    if (from >= 0 && to >= 0)
        PTankCopy(reinterpret_cast<RpPrtStdEmitterPTank*>(rpprtstd::PropertyAt(clone, to)),
                  reinterpret_cast<const RpPrtStdEmitterPTank*>(rpprtstd::PropertyAt(emitter, from)));
    return clone;
}

// 0x0072b198 RpPrtStdEmitterInit_maybe: the header cleared (next = itself), the properties zeroed, the
// PTank defaults, then every create callback (slot 5); null when one fails.
RpPrtStdEmitter* EmitterInit(RpPrtStdEmitter* emitter, void* data) {
    emitter->activeBatch = nullptr;
    emitter->next = emitter;
    emitter->flag = 0;
    emitter->atomic = nullptr;
    emitter->prtActive = 0;
    emitter->prtBatchMaxPrt = 0;
    emitter->prtClass = nullptr;
    emitter->inactiveBatch = nullptr;
    RpPrtStdEmitterClass* eClass = emitter->emtClass;
    std::memset(reinterpret_cast<uint8_t*>(emitter) + sizeof(RpPrtStdEmitter), 0,
                eClass->objSize - static_cast<int32_t>(sizeof(RpPrtStdEmitter)));
    const int32_t ptank = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERPTANK);
    if (ptank >= 0) PTankInitDefaults(reinterpret_cast<RpPrtStdEmitterPTank*>(rpprtstd::PropertyAt(emitter, ptank)));
    for (int32_t i = 0; i < eClass->numCallback; ++i) {
        RpPrtStdEmitterCallBack create = eClass->callback[i].callback[rpPRTSTDEMITTERCALLBACKCREATE];
        if (create != nullptr && create(nullptr, emitter, data) != emitter) return nullptr;
    }
    return emitter;
}

// The allocation the stream read and the clone make (0x72b2f0 RpPrtStdEmitterAlloc_maybe): the class's
// object size + 0x28 (the RW malloc does not clear it; calloc here), one more class reference.
RpPrtStdEmitter* EmitterAlloc(RpPrtStdEmitterClass* eClass) {
    void* memory = std::calloc(1, static_cast<size_t>(eClass->objSize) + 0x28);
    if (memory == nullptr) return nullptr;
    RpPrtStdEmitter* emitter = static_cast<RpPrtStdEmitter*>(memory);
    ++eClass->refCount;
    emitter->emtClass = eClass;
    return emitter;
}

// The emitter's particle batches freed (inlined in 0x72c820 RpPrtStdEmitterDestruct_maybe, 0x72cb68 and
// 0x72d180): the active ring, then the inactive one, each from its head's next. An active batch first runs
// its class's batch-destroy callbacks (particle slot 3, with (null, batch, null)); when they all return the
// batch its count, new index and link are cleared. Every batch is freed (RwFree, Engine +0x10c; the batches
// are malloc'ed, RpPrtStdRuntime.cpp). Then the live count and both rings are cleared.
void FreeParticleBatches(RpPrtStdEmitter* emitter) {
    RpPrtStdParticleBatch* const rings[2] = {static_cast<RpPrtStdParticleBatch*>(emitter->activeBatch),
                                             static_cast<RpPrtStdParticleBatch*>(emitter->inactiveBatch)};
    for (int32_t r = 0; r < 2; ++r) {
        if (rings[r] == nullptr) continue;
        RpPrtStdParticleBatch* const first = rings[r]->next;
        RpPrtStdParticleBatch* batch = first;
        for (;;) {
            RpPrtStdParticleBatch* const next = batch->next;
            if (r == 0) {
                const RpPrtStdParticleClass* pClass = batch->prtClass;
                bool cleared = true;
                for (int32_t i = 0; i < pClass->numCallback; ++i) {
                    RpPrtStdParticleCallBack destroy = pClass->callback[i].callback[rpPRTSTDPARTICLECALLBACKDESTROY];
                    if (destroy != nullptr && destroy(nullptr, batch, nullptr) != batch) {
                        cleared = false;
                        break;
                    }
                }
                if (cleared) {
                    batch->numPrt = 0;
                    batch->newPrt = 0;
                    batch->next = nullptr;
                }
            }
            std::free(batch);
            if (first == next) break;
            batch = next;
        }
    }
    emitter->prtActive = 0;
    emitter->activeBatch = nullptr;
    emitter->inactiveBatch = nullptr;
}

// The part of 0x72cb68 / 0x72d180 for an emitter that already has a particle class: its batches freed and
// the class released. After EmitterInit the class is always null, so it never runs there.
void ReleaseParticleClass(RpPrtStdEmitter* emitter) {
    if (emitter->prtClass == nullptr) return;
    FreeParticleBatches(emitter);
    PClassDestroy(emitter->prtClass);
}

// 0x0072e1e8 RpPrtStdPTankData_Release_maybe: the PTank atomic off its frame, the frame and the atomic
// destroyed; the pointer arrays' block freed (natively the three blocks), the capacity and the in / out
// pointers cleared. BUG(original): the stride pointer (+0x24, part of the same PS3 block) is left dangling.
void PTankRelease(RpPrtStdEmitterPTank* ptank) {
    RpAtomic* pTank = ptank->pTank;
    if (pTank != nullptr) {
        RwFrame* frame = pTank->frame;
        RpAtomicSetFrame(pTank, nullptr);
        if (frame != nullptr) RwFrameDestroy(frame);
        RpAtomicDestroy(ptank->pTank);
    }
    ptank->pTank = nullptr;
    if (ptank->dataInPtrs != nullptr) {
        std::free(ptank->dataInPtrs);
        std::free(ptank->dataOutPtrs);
        std::free(ptank->dataStride);
    }
    ptank->maxPrt = 0;
    ptank->dataInPtrs = nullptr;
    ptank->dataOutPtrs = nullptr;
}

// 0x0072c820 RpPrtStdEmitterDestruct_maybe: the batches freed, then the class's destroy callbacks (slot 6,
// with (null, emitter, null); null when one fails), the header cleared (the classes kept), the PTank property
// released, one reference less on both classes.
RpPrtStdEmitter* EmitterDestruct(RpPrtStdEmitter* emitter) {
    FreeParticleBatches(emitter);
    RpPrtStdEmitterClass* eClass = emitter->emtClass;
    for (int32_t i = 0; i < eClass->numCallback; ++i) {
        RpPrtStdEmitterCallBack destroy = eClass->callback[i].callback[rpPRTSTDEMITTERCALLBACKDESTROY];
        if (destroy != nullptr && destroy(nullptr, emitter, nullptr) != emitter) return nullptr;
    }
    emitter->activeBatch = nullptr;
    emitter->boundingSphere = 0.0f;  // stw 0
    emitter->next = nullptr;
    emitter->flag = 0;
    emitter->prtActive = 0;
    emitter->prtBatchMaxPrt = 0;
    emitter->inactiveBatch = nullptr;
    const int32_t ptank = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERPTANK);
    if (ptank >= 0) PTankRelease(reinterpret_cast<RpPrtStdEmitterPTank*>(rpprtstd::PropertyAt(emitter, ptank)));
    EClassDestroy(emitter->emtClass);
    PClassDestroy(emitter->prtClass);
    return emitter;
}

// 0x0072cad0 RpPrtStdEmitterDestroy_maybe: destructed and freed (EmitterAlloc's block); 0 when the destruct
// fails (the block is kept).
int32_t EmitterDestroy(RpPrtStdEmitter* emitter) {
    if (EmitterDestruct(emitter) != emitter) return 0;
    std::free(emitter);
    return 1;
}

// 0x00732bd0 RpPrtStdEmitterStd_Destruct_maybe (slot 6): a streamed emitter (flag 0x200) gives its standard
// property's texture back (RwTextureDestroy: one reference less).
RpPrtStdEmitter* StdDestruct(RpAtomic*, RpPrtStdEmitter* emitter, void*) {
    const int32_t offset = rpprtstd::EmitterPropOffset(emitter, rpPRTSTDPROPERTYCODEEMITTERSTANDARD);
    if (offset < 0) return emitter;
    if ((emitter->flag & rpPRTSTDEMITTERFLAGSTREAMREAD) == 0) return emitter;
    RwTexture* texture = reinterpret_cast<RpPrtStdEmitterStandard*>(rpprtstd::PropertyAt(emitter, offset))->texture;
    if (texture != nullptr) TextureRef_Release(texture);
    return emitter;
}

// 0x0072ffe0 RpPrtStdAtomicAddEmitter_maybe
void AtomicAddEmitter(RpAtomic* atomic, RpPrtStdEmitter* emitter) {
    atomic->prtStdEmitters = PushEmitter(atomic->prtStdEmitters, emitter);
    emitter->atomic = atomic;
}

// 0x0072cb68 RpPrtStdEmitterStreamRead_maybe: the emitter class id, the flags, the particle class id, the
// batch size and whether the tables and classes follow (version 3: they do, as four 0x25 chunks: the
// particle table, the emitter table, the particle class, the emitter class); then the emitter, its
// properties from every stream read callback (slot 7), added to the atomic.
RpPrtStdEmitter* EmitterStreamRead(RpAtomic* atomic, Stream* stream) {
    const int32_t eClassID = stream->ReadInt32();
    const uint32_t flags = static_cast<uint32_t>(stream->ReadInt32());
    const int32_t pClassID = stream->ReadInt32();
    const int32_t batchMaxPrt = stream->ReadInt32();
    const int32_t embedded = stream->ReadInt32();
    RpPrtStdEmitterClass* eClass;
    RpPrtStdParticleClass* pClass;
    if (embedded == 0) {
        eClass = EClassFindByID(eClassID);
        pClass = PClassFindByID(pClassID);
    } else {
        if (stream->FindChunk(0x25, nullptr) == 0) return nullptr;
        RpPrtStdPropertyTable* pTable = PropTabStreamRead(stream, false);
        if (stream->FindChunk(0x25, nullptr) == 0) return nullptr;
        RpPrtStdPropertyTable* eTable = PropTabStreamRead(stream, true);
        if (stream->FindChunk(0x25, nullptr) == 0) return nullptr;
        RpPrtStdParticleClass* pClassRead = PClassStreamRead(stream);
        if (stream->FindChunk(0x25, nullptr) == 0) return nullptr;
        eClass = EClassStreamRead(stream);
        pClass = pClassRead;
        if (eTable != nullptr) {
            RpPrtStdEmitterClass* sharing = EClassFindByPropTab(eTable);
            if (sharing != eClass) {
                if (sharing == nullptr) {
                    sharing = EClassCreate();
                    EClassSetPropTab(sharing, eTable);
                    sharing->id = eClass->id;
                    sharing->callback = nullptr;
                    sharing->numCallback = 0;
                    rpprtstd::EClassBuildCallBackArray(sharing);
                } else {
                    ++sharing->refCount;
                }
                EClassDestroy(eClass);
                eClass = sharing;
            }
            RpPrtStdParticleClass* pSharing = PClassFindByPropTab(pTable);
            if (pSharing != pClassRead) {
                if (pSharing == nullptr) {
                    pClass = PClassCreate();
                    PClassSetPropTab(pClass, pTable);
                    pClass->id = pClassRead->id;
                    pClass->callback = nullptr;
                    pClass->numCallback = 0;
                    PClassSetup(pClass);
                } else {
                    ++pSharing->refCount;
                    pClass = pSharing;
                }
                PClassDestroy(pClassRead);
            }
        }
    }
    RpPrtStdEmitter* emitter = EmitterAlloc(eClass);
    if (emitter == nullptr) return nullptr;
    emitter = EmitterInit(emitter, nullptr);
    if (emitter == nullptr) return nullptr;
    emitter->flag = flags | rpPRTSTDEMITTERFLAGSTREAMREAD;
    ReleaseParticleClass(emitter);
    emitter->prtBatchMaxPrt = batchMaxPrt;
    emitter->prtClass = pClass;
    ++pClass->refCount;
    for (int32_t i = 0; i < eClass->numCallback; ++i) {
        RpPrtStdEmitterCallBack read = eClass->callback[i].callback[rpPRTSTDEMITTERCALLBACKSTREAMREAD];
        if (read != nullptr && read(atomic, emitter, stream) != emitter) return nullptr;
    }
    AtomicAddEmitter(atomic, emitter);
    if (embedded != 0) {
        PropTabDestroy(eClass->propTab);
        PropTabDestroy(pClass->propTab);
        EClassDestroy(eClass);
        PClassDestroy(pClass);
    }
    return emitter;
}

// 0x0072d180 RpPrtStdEmitterClone_maybe: a new emitter of the same classes, flags and batch size, its
// properties copied by every clone callback (slot 10). On a failing callback the clone is destructed
// (RpPrtStdEmitterDestruct_maybe 0x72c820), freed when that worked, and null returned.
RpPrtStdEmitter* EmitterClone(RpPrtStdEmitter* source) {
    RpPrtStdEmitterClass* eClass = source->emtClass;
    RpPrtStdEmitter* clone = EmitterAlloc(eClass);
    if (clone == nullptr) return nullptr;
    clone = EmitterInit(clone, nullptr);
    if (clone == nullptr) return nullptr;
    RpPrtStdParticleClass* pClass = source->prtClass;
    const int32_t batchMaxPrt = source->prtBatchMaxPrt;
    clone->flag = source->flag;
    ReleaseParticleClass(clone);
    clone->prtBatchMaxPrt = batchMaxPrt;
    clone->prtClass = pClass;
    ++pClass->refCount;
    for (int32_t i = 0; i < eClass->numCallback; ++i) {
        RpPrtStdEmitterCallBack copy = eClass->callback[i].callback[rpPRTSTDEMITTERCALLBACKCLONE];
        if (copy != nullptr && copy(source->atomic, source, clone) != clone) {
            EmitterDestroy(clone);
            return nullptr;
        }
    }
    return clone;
}

}  // namespace

namespace rpprtstd {

// 0x007297c8 RpPrtStdEClassSetCallBackArray_maybe: `count` arrays copied into a new block.
void EClassSetCallBackArray(RpPrtStdEmitterClass* eClass, int32_t count, const RpPrtStdEmitterCallBackArray* arrays) {
    RpPrtStdEmitterCallBackArray* copy = new RpPrtStdEmitterCallBackArray[count > 0 ? count : 1];
    for (int32_t i = 0; i < count; ++i) copy[i] = arrays[i];
    delete[] eClass->callback;
    eClass->callback = copy;
    eClass->numCallback = count;
}

// The standard callbacks the builder (RpPrtAdv.cpp) puts first (TOC 0x00c21ce0..0x00c21d04).
// STUB(C2): stream write 0x731640 and stream size 0x7314d8 are not ported (null slots; nothing in the game
// writes RenderWare streams).
RpPrtStdEmitterCallBackArray StandardCallBacks() {
    RpPrtStdEmitterCallBackArray array = {};
    array.callback[rpPRTSTDEMITTERCALLBACKEMIT] = rpprtstd::StdEmit;
    array.callback[rpPRTSTDEMITTERCALLBACKUPDATE] = rpprtstd::StdUpdateTime;
    array.callback[rpPRTSTDEMITTERCALLBACKPOSTEMIT] = rpprtstd::StdScheduleEmit;
    array.callback[rpPRTSTDEMITTERCALLBACKPRERENDER] = rpprtstd::StdRenderPTank;
    array.callback[rpPRTSTDEMITTERCALLBACKCREATE] = StdInit;
    array.callback[rpPRTSTDEMITTERCALLBACKDESTROY] = StdDestruct;
    array.callback[rpPRTSTDEMITTERCALLBACKSTREAMREAD] = StdStreamRead;
    array.callback[rpPRTSTDEMITTERCALLBACKCLONE] = StdClone;
    return array;
}

}  // namespace rpprtstd

int32_t RpPrtStdPropTabGetPropOffset(const RpPrtStdPropertyTable* table, int32_t propID) {
    const int32_t index = RpPrtStdPropTabGetPropIndex(table, propID);
    if (index < 0) return -1;
    return table->propOffset[index];
}

int32_t RpPrtStdPropTabGetPropIndex(const RpPrtStdPropertyTable* table, int32_t propID) {
    for (int32_t i = 0; i < table->numProp; ++i) {
        if (table->propID[i] == propID) return i;
    }
    return -1;
}

void* RpPrtStdEmitterGetProperty(RpPrtStdEmitter* emitter, int32_t propID) {
    const int32_t offset = rpprtstd::EmitterPropOffset(emitter, propID);
    return offset < 0 ? nullptr : rpprtstd::PropertyAt(emitter, offset);
}

RpPrtStdEmitter* RpPrtStdAtomicGetEmitter(RpAtomic* atomic) { return atomic->prtStdEmitters; }

// The count word's top byte is the stream version, the rest the emitter count. The atomic's render
// callback (+0x48) becomes RW_RenderParticleAtomic (0x730ba8) when there are emitters.
uint32_t RpPrtStdAtomicStreamRead(RpAtomic* atomic, const uint8_t* data, uint32_t length) {
    Stream stream{data, length, 0};
    const uint32_t word = static_cast<uint32_t>(stream.ReadInt32());
    g_streamVersion = static_cast<int32_t>(word >> 24);
    const uint32_t count = word & 0xffffffu;
    for (uint32_t i = 0; i < count; ++i) {
        RpPrtStdEmitter* emitter = EmitterStreamRead(atomic, &stream);
        ++s_stats.emittersRead;  // DEV
        if (emitter == nullptr || emitter->atomic != atomic || (emitter->flag & rpPRTSTDEMITTERFLAGSTREAMREAD) == 0 ||
            emitter->emtClass == nullptr || emitter->prtClass == nullptr)
            ++s_stats.badEmitters;
    }
    g_streamVersion = 0;
    if (atomic->prtStdEmitters != nullptr) atomic->renderCallBack = RpPrtStdAtomicRender;
    return stream.position;
}

void RpPrtStdAtomicCopy(RpAtomic* dst, const RpAtomic* src) {
    RpPrtStdEmitter* list = nullptr;
    if (src->prtStdEmitters != nullptr) {
        RpPrtStdEmitter* first = src->prtStdEmitters->next;
        RpPrtStdEmitter* emitter = first;
        do {
            RpPrtStdEmitter* clone = EmitterClone(emitter);
            if (clone != nullptr) {
                clone->atomic = dst;
                list = PushEmitter(list, clone);
            }
            emitter = emitter->next;
        } while (emitter != first);
    }
    dst->prtStdEmitters = list;
    if (list != nullptr) dst->renderCallBack = RpPrtStdAtomicRender;  // as RpAtomicClone copies +0x48
}

// 0x00730158 RpPrtStdAtomicPlugin_Dtor_maybe: every emitter destroyed, from the list head's next on; the
// list cleared.
void RpPrtStdAtomicDestruct(RpAtomic* atomic) {
    RpPrtStdEmitter* list = atomic->prtStdEmitters;
    if (list != nullptr) {
        RpPrtStdEmitter* const first = list->next;
        RpPrtStdEmitter* emitter = first;
        RpPrtStdEmitter* next;
        do {
            next = emitter->next;
            EmitterDestroy(emitter);
            emitter = next;
        } while (first != next);
    }
    atomic->prtStdEmitters = nullptr;
}

RpPrtStdShimStats RpPrtStdShim_Stats() { return s_stats; }

void RpPrtStdShim_NoteStreamRead(uint32_t bytesRead, uint32_t chunkLength) {
    ++s_stats.streamsRead;
    if (bytesRead != chunkLength + 8) ++s_stats.streamLengthMismatches;
}

void RpPrtStdShim_NoteBoundNode(const RpPrtStdEmitter* emitter, const RpPrtAdvEmtPointList* pointList) {
    ++s_stats.nodesBound;
    if (pointList == nullptr) return;
    ++s_stats.nodesWithPointList;
    const uint8_t* list = reinterpret_cast<const uint8_t*>(pointList);
    const uint8_t* block = reinterpret_cast<const uint8_t*>(emitter);
    if (list <= block || list >= block + emitter->emtClass->objSize ||
        reinterpret_cast<const uint8_t*>(pointList->pointList) != list + sizeof(RpPrtAdvEmtPointList))
        ++s_stats.badNodes;
}
