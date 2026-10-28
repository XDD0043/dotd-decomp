// cg_preproc.h - the C preprocessor pass for the game's Cg uber-shader (new platform code, not a port).
//
// The game's shader text is plain C-preprocessor input: #define / #undef / #ifdef / #ifndef / #if / #elif /
// #else / #endif / #error / #pragma, object-like and function-like macros (with the ## paste operator:
// DeclareUniform(x_enum, x_type, x_name, x_register, x_count) builds "register(c##x_register)"), comments
// and line continuations. The game builds the define list from a ShaderVariantKey (-Dextern...=value
// arguments of the Cg compiler, ShaderGen_CollectExternFragments_maybe 0xf48c0); Preprocess takes the same
// list.
//
// Output: the text of the active lines with every macro expanded; lines that are removed stay as empty lines
// so errors keep their line numbers. #pragma lines are kept as they are (the translator checks
// "pack_matrix (row_major)"). #error in an active region fails the pass, like the Cg compiler's.
#pragma once
#include <string>
#include <vector>

namespace dotd::gfx::cg {

// One -D argument: name and value text ("1", "0", "4", ...); an empty value defines the name as empty.
struct Define {
    std::string name;
    std::string value;
};

// Returns false with `error` set (line number and message) on #error, an unterminated #if, a bad #if
// expression or a macro call with the wrong argument count.
bool Preprocess(const std::string& source, const std::vector<Define>& defines, std::string* output,
                std::string* error);

}  // namespace dotd::gfx::cg
