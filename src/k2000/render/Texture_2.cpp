// Reconstructed original translation unit: 0xc18d0-0xc1b50 (GAME_TOC1, main_toc1), 2 functions, 1 live.
// Primary owner: Texture (not a registered class)
//
// Checklist, address order. [dead] = unreferenced duplicate, do not port.
// [inline] = out-of-line copy of an inline/template method: belongs in the class header.
//   [ ] 0xc18d0  Texture_NameHasM0Option_maybe  [dead]
//   [x] 0xc19d8  Texture_HasUiNamePrefix
#include <cstring>

#include "k2000/dictionaries/CTextureDictionary.h"

// 0x000c19d8 Texture_HasUiNamePrefix (Ghidra's name; it answers the opposite: 1 = mipmaps wanted): the name in
// lower case (the ctype table's upper-case flag); a "=" or "@" followed later by an "x" (a size suffix), or a prefix
// "int_", "out_", "hud_" or "ico_" (TOC1 -0x5884 .. -0x5878) gives 0, anything else 1.
uint8_t Texture_HasUiNamePrefix(const char* name) {
    char lower[0x108];
    std::strcpy(lower, name);
    for (char* c = lower; *c != 0; ++c) {
        if (*c >= 'A' && *c <= 'Z') *c = static_cast<char>(*c + 0x20);
    }
    const char* mark = std::strchr(lower, '=');
    if (mark == nullptr) mark = std::strchr(lower, '@');
    if (mark != nullptr && std::strchr(mark, 'x') != nullptr) return 0;
    if (std::strncmp(lower, "int_", 4) == 0 || std::strncmp(lower, "out_", 4) == 0 ||
        std::strncmp(lower, "hud_", 4) == 0) {
        return 0;
    }
    return std::strncmp(lower, "ico_", 4) != 0 ? 1 : 0;
}
