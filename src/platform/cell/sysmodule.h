// sysmodule.h - cellSysmodule. Nothing to load on the host: every module counts as loaded.
#pragma once
#include <cstdint>

int32_t cellSysmoduleLoadModule(uint16_t id);
int32_t cellSysmoduleUnloadModule(uint16_t id);
int32_t cellSysmoduleIsLoaded(uint16_t id);  // CELL_OK = loaded
