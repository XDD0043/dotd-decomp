// SaveData.h - the save data's file-side pieces. Original unit: SaveData.cpp.
#pragma once
#include <cstdint>

class IKFile;

// 0x0002e6b8 SaveData_LoadIconBlobs_maybe: a u32 size and that many bytes (malloc) into the blob of
// kind 0 (a level, IKCommonGameManager mode 0) or kind 1 (GAME, mode 1); a size of 0 clears it.
void SaveData_LoadIconBlobs(IKFile* stream, int32_t kind);

extern void* g_pSaveDataBlob0;       // 0x00c517b4
extern void* g_pSaveDataBlob1;       // 0x00c517b8
extern uint32_t g_saveDataBlob1Size;  // 0x00c517bc
extern uint32_t g_saveDataBlob0Size;  // 0x00c517c4

// 0x00c517b0: the last cellSaveData list call's result (0 = done).
extern int32_t g_saveDataResult;
// 0x0002d010 SaveData_ListAutoLoad_maybe and the other list calls (memcard worker thread). STUB(save data):
// no host save data yet: the list load reports CELL_SAVEDATA_RET_CANCEL after the system's "no saved data"
// message, the other calls CELL_SAVEDATA_ERROR_CBRESULT (0x8002b401).
void SaveData_ListAutoLoad();
void SaveData_ListLoad();
void SaveData_ListSave();
void SaveData_Delete();
