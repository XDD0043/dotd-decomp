// IKCounter.h - the abstract counter (key 0x218c; XXL2: K/KServices/KServiceCounter/IKCounter.h, no
// members). Original unit: IKCounter.cpp (0x1ffbf8-0x1ffc70). Its Load reads nothing.
#pragma once
#include <cstdint>

#include "k2000/core/IKSerializable.h"

class IKCounter : public IKSerializable {
public:
    ~IKCounter() override {}
    int32_t Load(IKFile* file, int32_t type) override;  // vt+0x2c 0x001ffc58 IKCounter_Load
    // vt+0x24 0x001ffbf8 IKCounter_LevelReset (Ghidra's name; the counters' RecursiveRegistration): registered with the
    // saving manager (vt+0x24, no owner) for type 0. (vt+0x10 0x1ffc68 Destroy: empty, the default.)
    void RecursiveRegistration(int32_t type) override;
};
