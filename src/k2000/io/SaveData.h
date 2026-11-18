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
// 0x0002d148 SaveData_FreeWorkBuffer2_maybe: the kind-1 blob (0x00c517b8) freed and cleared.
void SaveData_FreeWorkBuffer2();

// 0x0002d100 SaveData_FreeWorkBuffer_maybe: the kind-0 blob (0x00c517b4) freed and cleared.
void SaveData_FreeWorkBuffer();

// 0x00c517b0: the last cellSaveData list call's result (0 = done).
extern int32_t g_saveDataResult;
// The memcard worker's calls (SaveDataRequest_Execute), on platform/cell/savedata: 0x0002d010 SaveData_ListAutoLoad_maybe
// (C2.8 menus-load: the boot's options from the newest save's USR-DATA), 0x0002d1c0 SaveData_ListLoad_maybe (C2.8 menus-load:
// Load game: SYS-DATA and USR-DATA's objects loaded), 0x0002e418 SaveData_ListSave_maybe (C2.8 save-menu) and 0x0002d190
// SaveData_Delete.
void SaveData_ListAutoLoad();
void SaveData_ListLoad();
void SaveData_ListSave();
void SaveData_Delete();
// 0x0002d840 SaveData_InitDirNamePrefix (BootLoad_InitSaveData_maybe 0x14698): the folders' prefix
// "BLUS30205-SPYRO08-SAVE-".
void SaveData_InitDirNamePrefix();
// 0x0002cf50 Str_UCS2ToUTF8Alloc_maybe: a zeroed Mem_AllocAligned16 block with the text in UTF-8.
char* Str_UCS2ToUTF8Alloc(const uint16_t* text);
