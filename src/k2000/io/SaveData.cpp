// SaveData.cpp - reconstructed original translation unit 0x2cdd8-0x2e880 (GAME_TOC1, main_toc1), 20 functions, 20 live.
// Primary owner: SaveData (not a registered class)
// Other owners: Str (1)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0x2cdd8  SaveData_ListLoadListCallback_maybe
//   [ ] 0x2ce40  SaveData_ListAutoLoadFixedCallback_maybe
//   [ ] 0x2ce80  StaticInitFini_GlobalMemBuffers_maybe
//   [ ] 0x2cf30  _GLOBAL__D_2cf30
//   [ ] 0x2cf40  _GLOBAL__I_2cf40
//   [ ] 0x2cf50  Str_UCS2ToUTF8Alloc_maybe
//   [x] 0x2d010  SaveData_ListAutoLoad_maybe
//   [ ] 0x2d100  SaveData_FreeWorkBuffer_maybe
//   [ ] 0x2d148  SaveData_FreeWorkBuffer2_maybe
//   [ ] 0x2d190  SaveData_Delete
//   [ ] 0x2d1c0  SaveData_ListLoad_maybe
//   [ ] 0x2d2a8  SaveData_StatCallback_maybe
//   [ ] 0x2d4d8  SaveData_SaveStatCallback
//   [ ] 0x2d640  SaveData_SaveListCallback
//   [ ] 0x2d840  SaveData_InitDirNamePrefix
//   [ ] 0x2d918  SaveData_LoadOptionsFileCallback_maybe
//   [ ] 0x2db88  SaveData_LoadFileCallback_maybe
//   [ ] 0x2df90  SaveData_SaveFileCallback_maybe
//   [ ] 0x2e418  SaveData_ListSave_maybe
//   [x] 0x2e6b8  SaveData_LoadIconBlobs_maybe
#include "k2000/io/SaveData.h"

#include <cstdlib>

#include "k2000/io/IKFile.h"
#include "platform/cell/msgdialog.h"

void* g_pSaveDataBlob0 = nullptr;
void* g_pSaveDataBlob1 = nullptr;
uint32_t g_saveDataBlob1Size = 0;
uint32_t g_saveDataBlob0Size = 0;

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

// 0x0002d010 SaveData_ListAutoLoad_maybe: cellSaveDataListAutoLoad with the game's callbacks. STUB(save
// data): no save data on the host yet; the callbacks would report "no data".
void SaveData_ListAutoLoad() { g_saveDataResult = static_cast<int32_t>(0x8002b401u); }
// SaveData_ListLoad_maybe (0x2d1c0): cellSaveDataListLoad2 with the game's callbacks (list 0x2cdd8, stat
// 0x2d2a8, file 0x2db88). STUB(save data): no host saves yet. With none the system's list shows "There is no
// saved data." until the player closes it, then the call returns CELL_SAVEDATA_RET_CANCEL (1): the load-game
// flow's vt+0x240(1), back to the main menu (RPCS3's behaviour for an empty list _maybe; not compared live).
void SaveData_ListLoad() {
    dotd::platform::SystemMessageWait("There is no saved data.");
    g_saveDataResult = 1;  // CELL_SAVEDATA_RET_CANCEL
}
// STUB(save data): 0x2e418 SaveData_ListSave_maybe, 0x2d190 SaveData_Delete.
void SaveData_ListSave() { g_saveDataResult = static_cast<int32_t>(0x8002b401u); }
void SaveData_Delete() { g_saveDataResult = static_cast<int32_t>(0x8002b401u); }
