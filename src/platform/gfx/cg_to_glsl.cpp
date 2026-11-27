// cg_to_glsl.cpp - see cg_to_glsl.h. A single-pass, type-directed translator for the Cg subset the game's
// uber-shader uses: scalars, vectors and matrices of float / int / bool, sampler2D / samplerCUBE, structs with
// semantics, typedef, arrays, function overloading with in / out / inout parameters, if / for / while / do,
// the usual operators with Cg's implicit conversions (scalar to vector, vector truncation, int / bool / float),
// swizzles and matrix element swizzles (._m30_m31), casts, initializer lists, and the stdlib calls the shader
// makes (mul, lerp, frac, saturate, tex2D, ddx, ...). Anything else is an error, never silently wrong output.
#include "platform/gfx/cg_to_glsl.h"

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <map>
#include <set>
#include <sstream>

#include "platform/hostfs.h"
#include "platform/self_decrypt.h"

namespace dotd::gfx::cg {
namespace {

struct CgError {
    std::string message;
};

// ---- lexer -------------------------------------------------------------------------------------------
enum class T { kEof, kIdent, kInt, kFloat, kPunct };
struct Token {
    T kind = T::kEof;
    std::string text;
    int line = 0;
};

std::vector<Token> Lex(const std::string& s) {
    std::vector<Token> out;
    int line = 1;
    size_t i = 0;
    while (i < s.size()) {
        const char c = s[i];
        if (c == '\n') {
            ++line;
            ++i;
        } else if (std::isspace(static_cast<unsigned char>(c)) != 0) {
            ++i;
        } else if (c == '#') {  // a #pragma line (the preprocessor keeps only those): pack_matrix must be row_major
            size_t j = i;
            while (j < s.size() && s[j] != '\n') ++j;
            const std::string text = s.substr(i, j - i);
            if (text.find("pack_matrix") != std::string::npos && text.find("row_major") == std::string::npos) {
                throw CgError{"line " + std::to_string(line) + ": only #pragma pack_matrix (row_major) is supported"};
            }
            i = j;
        } else if (std::isalpha(static_cast<unsigned char>(c)) != 0 || c == '_') {
            size_t j = i + 1;
            while (j < s.size() && (std::isalnum(static_cast<unsigned char>(s[j])) != 0 || s[j] == '_')) ++j;
            out.push_back({T::kIdent, s.substr(i, j - i), line});
            i = j;
        } else if (std::isdigit(static_cast<unsigned char>(c)) != 0 ||
                   (c == '.' && i + 1 < s.size() && std::isdigit(static_cast<unsigned char>(s[i + 1])) != 0)) {
            size_t j = i;
            bool isFloat = false;
            if (c == '0' && j + 1 < s.size() && (s[j + 1] == 'x' || s[j + 1] == 'X')) {
                j += 2;
                while (j < s.size() && std::isxdigit(static_cast<unsigned char>(s[j])) != 0) ++j;
            } else {
                while (j < s.size() && std::isdigit(static_cast<unsigned char>(s[j])) != 0) ++j;
                if (j < s.size() && s[j] == '.') {
                    isFloat = true;
                    ++j;
                    while (j < s.size() && std::isdigit(static_cast<unsigned char>(s[j])) != 0) ++j;
                }
                if (j < s.size() && (s[j] == 'e' || s[j] == 'E')) {
                    size_t k = j + 1;
                    if (k < s.size() && (s[k] == '+' || s[k] == '-')) ++k;
                    if (k < s.size() && std::isdigit(static_cast<unsigned char>(s[k])) != 0) {
                        isFloat = true;
                        j = k;
                        while (j < s.size() && std::isdigit(static_cast<unsigned char>(s[j])) != 0) ++j;
                    }
                }
            }
            std::string text = s.substr(i, j - i);
            if (j < s.size() && (s[j] == 'f' || s[j] == 'F' || s[j] == 'h' || s[j] == 'H')) {
                isFloat = true;
                ++j;
            } else if (j < s.size() && (s[j] == 'u' || s[j] == 'U' || s[j] == 'l' || s[j] == 'L')) {
                ++j;
            }
            out.push_back({isFloat ? T::kFloat : T::kInt, text, line});
            i = j;
        } else {
            static const char* const ops[] = {"<<=", ">>=", "++", "--", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=",
                                              "==",  "!=",  "<=", ">=", "&&", "||", "<<", ">>", "->"};
            bool matched = false;
            for (const char* op : ops) {
                const size_t n = std::strlen(op);
                if (s.compare(i, n, op) == 0) {
                    out.push_back({T::kPunct, op, line});
                    i += n;
                    matched = true;
                    break;
                }
            }
            if (!matched) {
                out.push_back({T::kPunct, std::string(1, c), line});
                ++i;
            }
        }
    }
    out.push_back({T::kEof, "", line});
    return out;
}

// ---- types -------------------------------------------------------------------------------------------
enum class B { kVoid, kBool, kInt, kFloat, kSampler2D, kSamplerCube, kStruct };

struct Ty {
    B b = B::kVoid;
    int rows = 1;  // vector length, or matrix rows
    int cols = 1;  // matrix columns
    bool mat = false;
    int st = -1;   // struct index
    int arr = 0;   // array length (0: not an array)
    bool operator==(const Ty& o) const {
        return b == o.b && rows == o.rows && cols == o.cols && mat == o.mat && st == o.st && arr == o.arr;
    }
    bool operator!=(const Ty& o) const { return !(*this == o); }
    bool Numeric() const { return b == B::kBool || b == B::kInt || b == B::kFloat; }
    bool Scalar() const { return Numeric() && !mat && rows == 1 && arr == 0; }
    bool Vector() const { return Numeric() && !mat && rows > 1 && arr == 0; }
    bool Matrix() const { return Numeric() && mat && arr == 0; }
    bool Sampler() const { return b == B::kSampler2D || b == B::kSamplerCube; }
};

Ty ScalarOf(B b) {
    Ty t;
    t.b = b;
    return t;
}
Ty VectorOf(B b, int n) {
    Ty t;
    t.b = b;
    t.rows = n;
    return t;
}

struct Field {
    std::string name;
    std::string glsl;
    Ty ty;
    std::string semantic;
};
struct StructDef {
    std::string name;
    std::vector<Field> fields;
};

struct Val {
    std::string code;
    Ty ty;
    bool lval = false;
    bool literal = false;   // a numeric literal: code is its text
    bool isCtor = false;    // a vector constructor call (the multi-assignment form)
    std::vector<Val> ctorArgs;
};

struct Var {
    Ty ty;
    std::string glsl;
    bool constInt = false;
    int constValue = 0;
};

struct Param {
    Ty ty;
    int qual = 0;  // 0 in, 1 out, 2 inout
};
struct Func {
    Ty ret;
    std::vector<Param> params;
    std::string glsl;
};

const std::set<std::string>& Reserved() {
    static const std::set<std::string> kReserved = {
        // GLSL keywords and reserved words
        "attribute", "varying", "layout", "centroid", "flat", "smooth", "noperspective", "patch", "sample", "subroutine",
        "common", "partition", "active", "asm", "class", "union", "enum", "typedef", "template", "this", "packed", "goto",
        "inline", "noinline", "volatile", "public", "static", "extern", "external", "interface", "long", "short",
        "double", "half", "fixed", "unsigned", "superp", "input", "output", "hvec2", "hvec3", "hvec4", "fvec2", "fvec3",
        "fvec4", "sampler3DRect", "filter", "sizeof", "cast", "namespace", "using", "lowp", "mediump", "highp",
        "precision", "invariant", "discard", "resource", "shared", "coherent", "restrict", "readonly", "writeonly",
        "buffer", "uniform", "in", "out", "inout", "const", "bool", "int", "uint", "float", "vec2", "vec3", "vec4",
        "mat2", "mat3", "mat4", "main", "switch", "case", "default", "sampler1D", "sampler2D", "sampler3D",
        // builtin functions the translation calls (a Cg variable of that name would hide them)
        "radians", "degrees", "sin", "cos", "tan", "asin", "acos", "atan", "sinh", "cosh", "tanh", "pow", "exp", "log",
        "exp2", "log2", "sqrt", "inversesqrt", "abs", "sign", "floor", "trunc", "round", "ceil", "fract", "mod", "modf",
        "min", "max", "clamp", "mix", "step", "smoothstep", "length", "distance", "dot", "cross", "normalize",
        "reflect", "refract", "faceforward", "matrixCompMult", "transpose", "determinant", "inverse", "texture",
        "textureLod", "textureGrad", "textureProj", "texelFetch", "dFdx", "dFdy", "fwidth", "any", "all", "not",
        "lessThan", "greaterThan", "equal", "notEqual", "cg_fmod", "gl_Position", "gl_FragDepth", "gl_FragCoord"};
    return kReserved;
}

std::string SafeName(const std::string& name) {
    if (Reserved().count(name) != 0 || name.compare(0, 3, "gl_") == 0 || name.find("__") != std::string::npos) {
        return name + "_cg";
    }
    return name;
}

// ---- the translator ---------------------------------------------------------------------------------
class Translator {
public:
    Translator(const std::string& text, Stage stage, const std::string& entry)
        : tokens_(Lex(text)), stage_(stage), entry_(entry) {}

    void Run(Translation* out) {
        while (Peek().kind != T::kEof) TopLevel();
        EmitWrapper(out);
        std::string src = "#version 330 core\n";
        if (usesLodBias_) {
            // PSGL's texture LOD bias (device.h kPsglLodBias). Desktop GL has it as a texture parameter (device.cpp); GLSL ES
            // (the web build) has no such parameter, so there the pixel shader's implicit-LOD lookups carry it.
            src += "#ifdef GL_ES\n#define DOTD_LOD_BIAS -0.2578125\n#else\n#define DOTD_LOD_BIAS 0.0\n#endif\n";
        }
        if (usesFmod_) {
            src +=
                "float cg_fmod(float x, float y) { return x - y * trunc(x / y); }\n"
                "vec2 cg_fmod(vec2 x, vec2 y) { return x - y * trunc(x / y); }\n"
                "vec3 cg_fmod(vec3 x, vec3 y) { return x - y * trunc(x / y); }\n"
                "vec4 cg_fmod(vec4 x, vec4 y) { return x - y * trunc(x / y); }\n";
        }
        src += decls_ + body_ + wrapper_;
        out->glsl = src;
        out->uniforms = uniforms_;
        out->samplers = samplers_;
    }

private:
    std::vector<Token> tokens_;
    size_t pos_ = 0;
    Stage stage_;
    bool usesLodBias_ = false;
    std::string entry_;

    std::string decls_;    // global declarations (structs, uniforms, constants, helpers)
    std::string body_;     // functions
    std::string wrapper_;  // attributes, varyings, main()
    bool usesFmod_ = false;
    std::vector<UniformInfo> uniforms_;
    std::vector<SamplerInfo> samplers_;
    std::vector<StructDef> structs_;
    std::map<std::string, Ty> typedefs_;
    std::vector<std::map<std::string, Var>> scopes_ = {{}};
    std::map<std::string, std::vector<Func>> funcs_;
    Ty currentRet_;
    std::string entryText_;

    // ---- token helpers
    const Token& Peek(size_t ahead = 0) const {
        const size_t i = std::min(pos_ + ahead, tokens_.size() - 1);
        return tokens_[i];
    }
    Token Next() {
        Token t = Peek();
        if (pos_ < tokens_.size() - 1) ++pos_;
        return t;
    }
    [[noreturn]] void Fail(const std::string& message) const {
        throw CgError{"line " + std::to_string(Peek().line) + ": " + message};
    }
    bool IsPunct(const char* s, size_t ahead = 0) const { return Peek(ahead).kind == T::kPunct && Peek(ahead).text == s; }
    bool IsIdent(const char* s, size_t ahead = 0) const { return Peek(ahead).kind == T::kIdent && Peek(ahead).text == s; }
    bool AcceptPunct(const char* s) {
        if (!IsPunct(s)) return false;
        Next();
        return true;
    }
    void ExpectPunct(const char* s) {
        if (!AcceptPunct(s)) Fail(std::string("expected '") + s + "' near '" + Peek().text + "'");
    }
    std::string ExpectIdent() {
        if (Peek().kind != T::kIdent) Fail("expected an identifier near '" + Peek().text + "'");
        return Next().text;
    }

    // ---- types
    bool ParseTypeName(const std::string& name, Ty* out) const {
        static const char* const kScalarNames[][2] = {{"float", "f"}, {"half", "f"}, {"fixed", "f"}, {"double", "f"},
                                                       {"int", "i"},   {"uint", "i"},  {"bool", "b"}};
        for (const auto& entry : kScalarNames) {
            const size_t n = std::strlen(entry[0]);
            if (name.compare(0, n, entry[0]) != 0) continue;
            const B base = entry[1][0] == 'f' ? B::kFloat : (entry[1][0] == 'i' ? B::kInt : B::kBool);
            const std::string rest = name.substr(n);
            Ty t;
            t.b = base;
            if (rest.empty()) {
                *out = t;
                return true;
            }
            if (rest.size() == 1 && rest[0] >= '1' && rest[0] <= '4') {
                t.rows = rest[0] - '0';
                *out = t;
                return true;
            }
            if (rest.size() == 3 && rest[0] >= '1' && rest[0] <= '4' && rest[1] == 'x' && rest[2] >= '1' && rest[2] <= '4') {
                t.mat = true;
                t.rows = rest[0] - '0';
                t.cols = rest[2] - '0';
                *out = t;
                return true;
            }
        }
        if (name == "void") {
            *out = Ty();
            return true;
        }
        if (name == "sampler2D" || name == "sampler") {
            *out = ScalarOf(B::kSampler2D);
            return true;
        }
        if (name == "samplerCUBE") {
            *out = ScalarOf(B::kSamplerCube);
            return true;
        }
        auto td = typedefs_.find(name);
        if (td != typedefs_.end()) {
            *out = td->second;
            return true;
        }
        for (size_t i = 0; i < structs_.size(); ++i) {
            if (structs_[i].name == name) {
                Ty t;
                t.b = B::kStruct;
                t.st = static_cast<int>(i);
                *out = t;
                return true;
            }
        }
        return false;
    }
    bool IsTypeToken(size_t ahead = 0) const {
        Ty t;
        return Peek(ahead).kind == T::kIdent && ParseTypeName(Peek(ahead).text, &t);
    }

    std::string GlslType(const Ty& t) const {
        switch (t.b) {
        case B::kVoid: return "void";
        case B::kBool: return t.mat ? "mat" : (t.rows == 1 ? "bool" : "bvec" + std::to_string(t.rows));
        case B::kInt: return t.mat ? "mat" : (t.rows == 1 ? "int" : "ivec" + std::to_string(t.rows));
        case B::kFloat:
            if (t.mat) return t.rows == t.cols ? "mat" + std::to_string(t.rows) : "mat" + std::to_string(t.rows) + "x" + std::to_string(t.cols);
            return t.rows == 1 ? "float" : "vec" + std::to_string(t.rows);
        case B::kSampler2D: return "sampler2D";
        case B::kSamplerCube: return "samplerCube";
        case B::kStruct: return structs_[static_cast<size_t>(t.st)].name;
        }
        return "void";
    }
    std::string CgTypeName(const Ty& t) const {
        std::string base = t.b == B::kFloat ? "float" : (t.b == B::kInt ? "int" : (t.b == B::kBool ? "bool" : GlslType(t)));
        if (t.b == B::kStruct || t.Sampler() || t.b == B::kVoid) return base;
        if (t.mat) return base + std::to_string(t.rows) + "x" + std::to_string(t.cols);
        return t.rows == 1 ? base : base + std::to_string(t.rows);
    }
    std::string Declarator(const Ty& t, const std::string& name) const {
        return GlslType(t) + " " + name + (t.arr > 0 ? "[" + std::to_string(t.arr) + "]" : "");
    }

    // ---- scopes
    void PushScope() { scopes_.emplace_back(); }
    void PopScope() { scopes_.pop_back(); }
    Var* Lookup(const std::string& name) {
        for (size_t i = scopes_.size(); i-- > 0;) {
            auto it = scopes_[i].find(name);
            if (it != scopes_[i].end()) return &it->second;
        }
        return nullptr;
    }
    std::string Declare(const std::string& name, const Ty& ty) {
        Var v;
        v.ty = ty;
        v.glsl = SafeName(name);
        scopes_.back()[name] = v;
        return v.glsl;
    }

    // ---- constant integer expressions (array sizes)
    int ConstInt() { return ConstAdd(); }
    int ConstPrimary() {
        if (AcceptPunct("(")) {
            const int v = ConstAdd();
            ExpectPunct(")");
            return v;
        }
        if (AcceptPunct("-")) return -ConstPrimary();
        if (Peek().kind == T::kInt) return static_cast<int>(std::strtol(Next().text.c_str(), nullptr, 0));
        if (Peek().kind == T::kIdent) {
            Var* v = Lookup(Peek().text);
            if (v != nullptr && v->constInt) {
                Next();
                return v->constValue;
            }
        }
        Fail("array size is not a constant integer");
    }
    int ConstMul() {
        int v = ConstPrimary();
        for (;;) {
            if (AcceptPunct("*")) v *= ConstPrimary();
            else if (AcceptPunct("/")) { const int d = ConstPrimary(); v = d != 0 ? v / d : 0; }
            else return v;
        }
    }
    int ConstAdd() {
        int v = ConstMul();
        for (;;) {
            if (AcceptPunct("+")) v += ConstMul();
            else if (AcceptPunct("-")) v -= ConstMul();
            else return v;
        }
    }

    // ---- conversions
    static std::string FloatLiteral(const std::string& text) {
        std::string s = text;
        if (s.find('.') == std::string::npos && s.find('e') == std::string::npos && s.find('E') == std::string::npos &&
            !(s.size() > 1 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))) {
            s += ".0";
        } else if (s.back() == '.') {
            s += "0";
        } else if (s[0] == '.') {
            s = "0" + s;
        }
        return s;
    }
    static const char* Swz(int n) { return n == 1 ? "x" : n == 2 ? "xy" : n == 3 ? "xyz" : "xyzw"; }

    Val Conv(const Val& v, const Ty& to, bool isCast = false) {
        if (v.ty == to) return v;
        if (to.b == B::kVoid || v.ty.b == B::kVoid) Fail("void value in an expression");
        if (to.arr != 0 || v.ty.arr != 0) Fail("cannot convert array types");
        if (to.b == B::kStruct || v.ty.b == B::kStruct) Fail("cannot convert between struct types");
        if (to.Sampler() || v.ty.Sampler()) Fail("a sampler cannot be converted");
        Val r;
        r.ty = to;
        if (v.ty.Scalar()) {
            std::string elem;
            if (v.literal && to.b == B::kFloat) {
                elem = FloatLiteral(v.code);
            } else if (v.literal && to.b == B::kInt && v.ty.b == B::kInt) {
                elem = v.code;
            } else if (v.ty.b == to.b) {
                elem = v.code;
            } else {
                elem = GlslType(ScalarOf(to.b)) + "(" + v.code + ")";
            }
            r.literal = v.literal && to.Scalar();
            if (to.Scalar()) {
                r.code = elem;
            } else if (to.Vector()) {
                r.code = GlslType(to) + "(" + elem + ")";
            } else if (to.Matrix()) {
                if (!(v.literal && (v.code == "0" || v.code == "0.0" || v.code == "0.f"))) Fail("a scalar cannot fill a matrix");
                r.code = GlslType(to) + "(0.0)";
            }
            return r;
        }
        if (v.ty.Vector()) {
            if (to.Scalar()) {
                r.code = (v.ty.b == to.b ? v.code + ".x" : GlslType(to) + "(" + v.code + ".x)");
                r.lval = v.lval && v.ty.b == to.b;
                return r;
            }
            if (to.Vector()) {
                if (to.rows > v.ty.rows) Fail("cannot extend a " + CgTypeName(v.ty) + " to a " + CgTypeName(to));
                std::string code = v.code;
                bool lval = v.lval;
                if (to.rows < v.ty.rows) code = v.code + "." + Swz(to.rows);
                if (v.ty.b != to.b) {
                    code = GlslType(to) + "(" + code + ")";
                    lval = false;
                }
                r.code = code;
                r.lval = lval;
                return r;
            }
            Fail("cannot convert a vector to a matrix");
        }
        if (v.ty.Matrix() && to.Matrix()) {
            if (to.rows <= v.ty.rows && to.cols <= v.ty.cols) {
                r.code = GlslType(to) + "(" + v.code + ")";
                return r;
            }
            Fail("cannot extend a matrix");
        }
        (void)isCast;
        Fail("cannot convert " + CgTypeName(v.ty) + " to " + CgTypeName(to));
    }

    Val AsBool(const Val& v) {
        if (v.ty.b == B::kBool && v.ty.Scalar()) return v;
        if (!v.ty.Scalar()) {
            if (v.ty.Vector()) return AsBool(Conv(v, ScalarOf(v.ty.b)));
            Fail("a condition must be a scalar");
        }
        Val r;
        r.ty = ScalarOf(B::kBool);
        r.code = "(" + v.code + " != " + (v.ty.b == B::kFloat ? "0.0" : "0") + ")";
        return r;
    }

    // The common numeric base of two operands (bool counts as int in arithmetic).
    static B CommonBase(B a, B b) {
        if (a == B::kFloat || b == B::kFloat) return B::kFloat;
        return B::kInt;
    }

    // ---- expressions --------------------------------------------------------------------------------
    Val ParseExpr() { return ParseAssign(); }

    Val ParseAssign() {
        Val lhs = ParseTernary();
        static const char* const kAssign[] = {"=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>="};
        for (const char* op : kAssign) {
            if (!IsPunct(op)) continue;
            Next();
            Val rhs = ParseAssign();
            if (std::strcmp(op, "=") == 0 && lhs.isCtor) return MultiAssign(lhs, rhs);
            if (!lhs.lval) Fail("assignment to something that is not a variable");
            Val r;
            r.ty = lhs.ty;
            if (std::strcmp(op, "=") == 0) {
                r.code = "(" + lhs.code + " = " + Conv(rhs, lhs.ty).code + ")";
            } else {
                const std::string bin = std::string(op).substr(0, std::strlen(op) - 1);
                Val computed = Binary(bin, lhs, rhs);  // validates the operands and gives the result type
                const bool compoundOk = (lhs.ty.Scalar() || lhs.ty.Vector()) && !(bin == "%" && lhs.ty.b == B::kFloat) &&
                                        lhs.ty.b != B::kBool;
                if (compoundOk && (rhs.ty.Scalar() || rhs.ty.Vector())) {
                    const Val rc = rhs.ty.Scalar() ? Conv(rhs, ScalarOf(lhs.ty.b)) : Conv(rhs, lhs.ty);
                    r.code = "(" + lhs.code + " " + op + " " + rc.code + ")";
                } else {
                    r.code = "(" + lhs.code + " = " + Conv(computed, lhs.ty).code + ")";
                }
            }
            return r;
        }
        return lhs;
    }

    // float4(a, b) = expr  ->  a statement-expression block is not possible here; the form is accepted only as
    // an expression statement, so it is returned as a GLSL "lambda-less" sequence via a temporary.
    Val MultiAssign(const Val& ctor, const Val& rhs) {
        Val value = Conv(rhs, ctor.ty);
        const std::string temp = "cg_tmp" + std::to_string(tempCount_++);
        std::string code = "{ " + GlslType(ctor.ty) + " " + temp + " = " + value.code + "; ";
        int at = 0;
        for (const Val& part : ctor.ctorArgs) {
            if (!part.lval) Fail("multi-assignment to something that is not a variable");
            const int n = part.ty.Scalar() ? 1 : part.ty.rows;
            code += part.code + " = " + temp + "." + std::string(Swz(at + n)).substr(static_cast<size_t>(at), static_cast<size_t>(n)) + "; ";
            at += n;
        }
        code += "}";
        Val r;
        r.ty = ctor.ty;
        r.code = code;
        r.literal = false;
        multiAssignCode_ = true;
        return r;
    }
    int tempCount_ = 0;
    bool multiAssignCode_ = false;

    Val ParseTernary() {
        Val cond = ParseBinary(0);
        if (!AcceptPunct("?")) return cond;
        Val a = ParseAssign();
        ExpectPunct(":");
        Val b = ParseAssign();
        Val c = AsBool(cond);
        Ty target = a.ty;
        if (a.ty != b.ty) {
            if (a.ty.Numeric() && b.ty.Numeric() && !a.ty.Matrix() && !b.ty.Matrix()) {
                const B base = CommonBase(a.ty.b, b.ty.b);
                const int n = (a.ty.Scalar() && b.ty.Scalar()) ? 1 : std::max(a.ty.Scalar() ? 1 : a.ty.rows, b.ty.Scalar() ? 1 : b.ty.rows);
                target = n == 1 ? ScalarOf(base) : VectorOf(base, n);
            } else {
                Fail("the two branches of ?: have different types");
            }
        }
        Val r;
        r.ty = target;
        r.code = "(" + c.code + " ? " + Conv(a, target).code + " : " + Conv(b, target).code + ")";
        return r;
    }

    static int Precedence(const std::string& op) {
        if (op == "||") return 1;
        if (op == "&&") return 2;
        if (op == "|") return 3;
        if (op == "^") return 4;
        if (op == "&") return 5;
        if (op == "==" || op == "!=") return 6;
        if (op == "<" || op == ">" || op == "<=" || op == ">=") return 7;
        if (op == "<<" || op == ">>") return 8;
        if (op == "+" || op == "-") return 9;
        if (op == "*" || op == "/" || op == "%") return 10;
        return -1;
    }

    Val ParseBinary(int minPrec) {
        Val lhs = ParseUnary();
        for (;;) {
            if (Peek().kind != T::kPunct) return lhs;
            const std::string op = Peek().text;
            const int prec = Precedence(op);
            if (prec < 0 || prec < minPrec || prec == 0) return lhs;
            Next();
            Val rhs = ParseBinary(prec + 1);
            lhs = Binary(op, lhs, rhs);
        }
    }

    Val Binary(const std::string& op, const Val& a, const Val& b) {
        Val r;
        if (!a.ty.Numeric() || !b.ty.Numeric() || a.ty.arr != 0 || b.ty.arr != 0) Fail("bad operands to '" + op + "'");
        if (op == "&&" || op == "||") {
            r.ty = ScalarOf(B::kBool);
            r.code = "(" + AsBool(a).code + " " + op + " " + AsBool(b).code + ")";
            return r;
        }
        const bool isCompare = op == "==" || op == "!=" || op == "<" || op == ">" || op == "<=" || op == ">=";
        if (a.ty.Matrix() || b.ty.Matrix()) {
            if (isCompare) Fail("matrix comparison is not supported");
            if (a.ty.Matrix() && b.ty.Matrix()) {
                if (a.ty != b.ty) Fail("matrix operands differ in size");
                r.ty = a.ty;
                r.code = op == "*" ? "matrixCompMult(" + a.code + ", " + b.code + ")" : "(" + a.code + " " + op + " " + b.code + ")";
                return r;
            }
            const Val& m = a.ty.Matrix() ? a : b;
            const Val& s = a.ty.Matrix() ? b : a;
            if (!s.ty.Scalar()) Fail("matrix and vector operands need mul()");
            r.ty = m.ty;
            const Val sc = Conv(s, ScalarOf(B::kFloat));
            r.code = a.ty.Matrix() ? "(" + m.code + " " + op + " " + sc.code + ")" : "(" + sc.code + " " + op + " " + m.code + ")";
            return r;
        }
        if (isCompare) {
            if (!a.ty.Scalar() || !b.ty.Scalar()) Fail("vector comparison is not supported");
            const B base = (a.ty.b == B::kBool && b.ty.b == B::kBool) ? B::kBool : CommonBase(a.ty.b, b.ty.b);
            r.ty = ScalarOf(B::kBool);
            r.code = "(" + Conv(a, ScalarOf(base)).code + " " + op + " " + Conv(b, ScalarOf(base)).code + ")";
            return r;
        }
        const bool intOnly = op == "&" || op == "|" || op == "^" || op == "<<" || op == ">>";
        B base = CommonBase(a.ty.b, b.ty.b);
        if (intOnly) base = B::kInt;
        if (op == "%" && base == B::kFloat) {
            // Cg's % on floats is fmod
            usesFmod_ = true;
            const int n = (a.ty.Scalar() && b.ty.Scalar()) ? 1 : std::max(a.ty.Scalar() ? 1 : a.ty.rows, b.ty.Scalar() ? 1 : b.ty.rows);
            const Ty t = n == 1 ? ScalarOf(B::kFloat) : VectorOf(B::kFloat, n);
            r.ty = t;
            r.code = "cg_fmod(" + Conv(a, t).code + ", " + Conv(b, t).code + ")";
            return r;
        }
        int n;
        if (a.ty.Scalar() && b.ty.Scalar()) n = 1;
        else if (a.ty.Scalar()) n = b.ty.rows;
        else if (b.ty.Scalar()) n = a.ty.rows;
        else n = std::min(a.ty.rows, b.ty.rows);
        r.ty = n == 1 ? ScalarOf(base) : VectorOf(base, n);
        auto operand = [&](const Val& v) {
            if (v.ty.Scalar()) return Conv(v, ScalarOf(base)).code;
            return Conv(v, VectorOf(base, n)).code;
        };
        r.code = "(" + operand(a) + " " + op + " " + operand(b) + ")";
        return r;
    }

    Val ParseUnary() {
        if (Peek().kind == T::kPunct) {
            const std::string op = Peek().text;
            if (op == "-" || op == "+") {
                Next();
                Val v = ParseUnary();
                if (!v.ty.Numeric()) Fail("bad operand to unary " + op);
                Val r = v;
                r.lval = false;
                if (v.ty.b == B::kBool) r = Conv(v, Ty{B::kInt, v.ty.rows, 1, false, -1, 0});
                if (op == "-") {
                    r.code = (r.literal && r.code[0] != '-') ? "-" + r.code : "(-" + r.code + ")";
                    if (!r.literal || r.code[0] != '-') r.literal = false;
                }
                return r;
            }
            if (op == "!") {
                Next();
                Val v = ParseUnary();
                Val r;
                r.ty = ScalarOf(B::kBool);
                if (v.ty.Vector()) Fail("'!' on a vector");
                r.code = "(!" + AsBool(v).code + ")";
                return r;
            }
            if (op == "~") {
                Next();
                Val v = Conv(ParseUnary(), ScalarOf(B::kInt));
                v.code = "(~" + v.code + ")";
                v.lval = false;
                return v;
            }
            if (op == "++" || op == "--") {
                Next();
                Val v = ParseUnary();
                if (!v.lval) Fail("'" + op + "' needs a variable");
                Val r = v;
                r.code = "(" + op + v.code + ")";
                r.lval = false;
                return r;
            }
            if (op == "(" && IsTypeToken(1) && IsPunct(")", 2)) {
                Ty to;
                ParseTypeName(Peek(1).text, &to);
                Next();
                Next();
                Next();
                Val v = ParseUnary();
                return Conv(v, to, true);
            }
        }
        return ParsePostfix(ParsePrimary());
    }

    Val ParsePostfix(Val v) {
        for (;;) {
            if (IsPunct(".")) {
                Next();
                const std::string member = ExpectIdent();
                v = Member(v, member);
            } else if (IsPunct("[")) {
                Next();
                Val idx = ParseExpr();
                ExpectPunct("]");
                v = Index(v, idx);
            } else if (IsPunct("++") || IsPunct("--")) {
                const std::string op = Next().text;
                if (!v.lval) Fail("'" + op + "' needs a variable");
                Val r = v;
                r.code = "(" + v.code + op + ")";
                r.lval = false;
                v = r;
            } else {
                return v;
            }
        }
    }

    Val Index(const Val& base, const Val& idx) {
        Val r;
        const Val i = idx.ty.Scalar() ? Conv(idx, ScalarOf(B::kInt)) : (Fail("array index must be a scalar"), idx);
        r.lval = base.lval;
        if (base.ty.arr > 0) {
            r.ty = base.ty;
            r.ty.arr = 0;
        } else if (base.ty.Matrix()) {
            r.ty = base.ty.cols == 1 ? ScalarOf(base.ty.b) : VectorOf(base.ty.b, base.ty.cols);  // a row of M = a column of the stored transpose
        } else if (base.ty.Vector()) {
            r.ty = ScalarOf(base.ty.b);
        } else {
            Fail("indexing something that is not an array, vector or matrix");
        }
        r.code = base.code + "[" + i.code + "]";
        return r;
    }

    Val Member(const Val& base, const std::string& member) {
        Val r;
        if (base.ty.b == B::kStruct && base.ty.arr == 0) {
            const StructDef& def = structs_[static_cast<size_t>(base.ty.st)];
            for (const Field& f : def.fields) {
                if (f.name == member) {
                    r.ty = f.ty;
                    r.code = base.code + "." + f.glsl;
                    r.lval = base.lval;
                    return r;
                }
            }
            Fail("struct " + def.name + " has no member " + member);
        }
        if (base.ty.Matrix() && member.size() >= 3 && member[0] == '_') {
            // ._m30_m31 (zero based) or ._11_12 (one based): elements (row, column) of M = [row][column] of the stored transpose
            std::vector<std::string> elems;
            size_t i = 0;
            while (i < member.size()) {
                if (member[i] != '_') Fail("bad matrix swizzle ." + member);
                ++i;
                int origin = 1;
                if (i < member.size() && member[i] == 'm') {
                    origin = 0;
                    ++i;
                }
                if (i + 2 > member.size() || std::isdigit(static_cast<unsigned char>(member[i])) == 0 ||
                    std::isdigit(static_cast<unsigned char>(member[i + 1])) == 0) {
                    Fail("bad matrix swizzle ." + member);
                }
                const int row = member[i] - '0' - (origin == 1 ? 1 : 0);
                const int col = member[i + 1] - '0' - (origin == 1 ? 1 : 0);
                i += 2;
                if (row < 0 || row >= base.ty.rows || col < 0 || col >= base.ty.cols) Fail("matrix swizzle out of range ." + member);
                elems.push_back(base.code + "[" + std::to_string(row) + "][" + std::to_string(col) + "]");
            }
            if (elems.empty() || elems.size() > 4) Fail("bad matrix swizzle ." + member);
            r.ty = elems.size() == 1 ? ScalarOf(base.ty.b) : VectorOf(base.ty.b, static_cast<int>(elems.size()));
            if (elems.size() == 1) {
                r.code = elems[0];
                r.lval = base.lval;
            } else {
                r.code = GlslType(r.ty) + "(";
                for (size_t k = 0; k < elems.size(); ++k) r.code += (k ? ", " : "") + elems[k];
                r.code += ")";
            }
            return r;
        }
        if (base.ty.Numeric() && !base.ty.Matrix() && base.ty.arr == 0) {
            const int dim = base.ty.rows;
            static const char* const kSets[] = {"xyzw", "rgba", "stpq"};
            const char* set = nullptr;
            for (const char* s : kSets) {
                if (member.find_first_not_of(s) == std::string::npos) set = s;
            }
            if (set == nullptr || member.empty() || member.size() > 4) Fail("bad swizzle ." + member);
            std::string canon;
            bool repeated = false;
            for (char ch : member) {
                const int idx = static_cast<int>(std::strchr(set, ch) - set);
                if (idx >= dim) Fail("swizzle ." + member + " exceeds the vector size");
                if (canon.find("xyzw"[idx]) != std::string::npos) repeated = true;
                canon += "xyzw"[idx];
            }
            const int n = static_cast<int>(canon.size());
            r.ty = n == 1 ? ScalarOf(base.ty.b) : VectorOf(base.ty.b, n);
            if (base.ty.Scalar()) {
                r.code = n == 1 ? base.code : GlslType(r.ty) + "(" + base.code + ")";
                r.lval = n == 1 && base.lval;
            } else {
                r.code = base.code + "." + canon;
                r.lval = base.lval && !repeated;
            }
            return r;
        }
        Fail("member access on a non-struct value");
    }

    Val ParsePrimary() {
        const Token t = Peek();
        if (t.kind == T::kInt) {
            Next();
            Val v;
            v.ty = ScalarOf(B::kInt);
            v.code = t.text;
            v.literal = true;
            return v;
        }
        if (t.kind == T::kFloat) {
            Next();
            Val v;
            v.ty = ScalarOf(B::kFloat);
            v.code = FloatLiteral(t.text);
            v.literal = true;
            return v;
        }
        if (t.kind == T::kPunct && t.text == "(") {
            Next();
            Val v = ParseExpr();
            ExpectPunct(")");
            if (v.literal) return v;
            Val r = v;
            if (!v.isCtor && v.code.size() > 0 && v.code[0] != '(') r.code = "(" + v.code + ")";
            return r;
        }
        if (t.kind != T::kIdent) Fail("unexpected '" + t.text + "' in an expression");
        if (t.text == "true" || t.text == "false") {
            Next();
            Val v;
            v.ty = ScalarOf(B::kBool);
            v.code = t.text;
            return v;
        }
        Ty ctorTy;
        if (IsPunct("(", 1)) {
            if (ParseTypeName(t.text, &ctorTy) && ctorTy.b != B::kStruct && !ctorTy.Sampler() && ctorTy.b != B::kVoid) {
                Next();
                return Constructor(ctorTy);
            }
            Next();
            return Call(t.text);
        }
        Next();
        Var* v = Lookup(t.text);
        if (v == nullptr) Fail("undeclared identifier " + t.text);
        Val r;
        r.ty = v->ty;
        r.code = v->glsl;
        r.lval = !v->ty.Sampler();
        if (v->constInt) {
            r.lval = false;
        }
        return r;
    }

    Val Constructor(const Ty& to) {
        ExpectPunct("(");
        std::vector<Val> args;
        if (!IsPunct(")")) {
            do {
                args.push_back(ParseAssign());
            } while (AcceptPunct(","));
        }
        ExpectPunct(")");
        Val r;
        r.ty = to;
        if (to.Matrix()) {
            const int total = to.rows * to.cols;
            if (args.size() == static_cast<size_t>(to.rows) && args[0].ty.Vector()) {
                // rows given as vectors: the stored transpose takes them as its columns
                r.code = GlslType(to) + "(";
                for (size_t k = 0; k < args.size(); ++k) {
                    r.code += (k ? ", " : "") + Conv(args[k], VectorOf(to.b, to.cols)).code;
                }
                r.code += ")";
                return r;
            }
            int comps = 0;
            for (const Val& a : args) comps += a.ty.Scalar() ? 1 : (a.ty.Vector() ? a.ty.rows : 99);
            if (comps != total) Fail("wrong number of arguments for " + CgTypeName(to));
            r.code = GlslType(to) + "(";
            for (size_t k = 0; k < args.size(); ++k) {
                r.code += (k ? ", " : "") + (args[k].ty.Scalar() ? Conv(args[k], ScalarOf(B::kFloat)).code : Conv(args[k], VectorOf(B::kFloat, args[k].ty.rows)).code);
            }
            r.code += ")";
            return r;
        }
        if (to.Scalar()) {
            if (args.size() != 1) Fail("a scalar constructor takes one argument");
            return Conv(args[0], to, true);
        }
        // vector
        int comps = 0;
        for (const Val& a : args) {
            if (!a.ty.Numeric() || a.ty.Matrix() || a.ty.arr != 0) Fail("bad vector constructor argument");
            comps += a.ty.Scalar() ? 1 : a.ty.rows;
        }
        if (args.size() == 1 && args[0].ty.Scalar()) {
            r.code = GlslType(to) + "(" + Conv(args[0], ScalarOf(to.b)).code + ")";
            return r;
        }
        if (comps != to.rows) Fail("wrong number of components for " + CgTypeName(to));
        r.code = GlslType(to) + "(";
        for (size_t k = 0; k < args.size(); ++k) {
            const Val& a = args[k];
            const Val cv = a.ty.Scalar() ? Conv(a, ScalarOf(to.b)) : Conv(a, VectorOf(to.b, a.ty.rows));
            r.code += (k ? ", " : "") + cv.code;
        }
        r.code += ")";
        r.isCtor = true;
        r.ctorArgs = args;
        return r;
    }

    // ---- calls
    std::vector<Val> ParseArgs() {
        ExpectPunct("(");
        std::vector<Val> args;
        if (!IsPunct(")")) {
            do {
                args.push_back(ParseAssign());
            } while (AcceptPunct(","));
        }
        ExpectPunct(")");
        return args;
    }

    Val Call(const std::string& name) {
        std::vector<Val> args = ParseArgs();
        auto it = funcs_.find(name);
        if (it != funcs_.end()) return CallUser(name, it->second, args);
        return Builtin(name, args);
    }

    // Conversion cost of passing `arg` to an in parameter of type `to`; -1: impossible.
    int Cost(const Val& arg, const Ty& to) const {
        const Ty& from = arg.ty;
        if (from == to) return 0;
        if (from.arr != 0 || to.arr != 0 || from.b == B::kStruct || to.b == B::kStruct || from.Sampler() || to.Sampler()) return -1;
        if (from.Scalar()) {
            if (to.Scalar()) return 1;
            if (to.Vector()) return 2;
            return -1;
        }
        if (from.Vector()) {
            if (to.Scalar()) return 3;
            if (to.Vector()) return to.rows < from.rows ? 3 : -1;
            return -1;
        }
        if (from.Matrix() && to.Matrix()) return (to.rows <= from.rows && to.cols <= from.cols) ? 3 : -1;
        return -1;
    }

    Val CallUser(const std::string& name, const std::vector<Func>& candidates, const std::vector<Val>& args) {
        const Func* best = nullptr;
        int bestCost = 1 << 30;
        for (const Func& f : candidates) {
            if (f.params.size() != args.size()) continue;
            int total = 0;
            bool ok = true;
            for (size_t i = 0; i < args.size() && ok; ++i) {
                if (f.params[i].qual != 0) {
                    // out / inout: an l-value of exactly the parameter's type (a base conversion cannot be written back)
                    if (!args[i].lval) ok = false;
                    else if (args[i].ty != f.params[i].ty) ok = false;
                } else {
                    const int c = Cost(args[i], f.params[i].ty);
                    if (c < 0) ok = false;
                    else total += c;
                }
            }
            if (ok && total < bestCost) {
                best = &f;
                bestCost = total;
            }
        }
        if (best == nullptr) Fail("no overload of " + name + " matches the arguments");
        Val r;
        r.ty = best->ret;
        r.code = best->glsl + "(";
        for (size_t i = 0; i < args.size(); ++i) {
            r.code += (i ? ", " : "") + (best->params[i].qual != 0 ? args[i].code : Conv(args[i], best->params[i].ty).code);
        }
        r.code += ")";
        return r;
    }

    // Arguments of a componentwise builtin converted to float with a common size.
    std::vector<Val> Unify(const std::vector<Val>& args, size_t count) {
        if (args.size() != count) Fail("wrong number of arguments");
        int dim = 0;
        for (const Val& a : args) {
            if (!a.ty.Numeric() || a.ty.Matrix() || a.ty.arr != 0) Fail("bad argument type");
            if (a.ty.Vector()) dim = dim == 0 ? a.ty.rows : std::min(dim, a.ty.rows);
        }
        if (dim == 0) dim = 1;
        const Ty t = dim == 1 ? ScalarOf(B::kFloat) : VectorOf(B::kFloat, dim);
        std::vector<Val> out;
        for (const Val& a : args) out.push_back(Conv(a, t));
        return out;
    }

    Val Builtin(const std::string& name, const std::vector<Val>& args) {
        Val r;
        auto unary = [&](const char* glsl) {
            std::vector<Val> u = Unify(args, 1);
            r.ty = u[0].ty;
            r.code = std::string(glsl) + "(" + u[0].code + ")";
            return r;
        };
        auto nary = [&](const char* glsl, size_t count) {
            std::vector<Val> u = Unify(args, count);
            r.ty = u[0].ty;
            r.code = std::string(glsl) + "(";
            for (size_t i = 0; i < u.size(); ++i) r.code += (i ? ", " : "") + u[i].code;
            r.code += ")";
            return r;
        };
        static const std::map<std::string, const char*> kUnary = {
            {"abs", "abs"},   {"floor", "floor"}, {"ceil", "ceil"},         {"frac", "fract"}, {"sqrt", "sqrt"},
            {"rsqrt", "inversesqrt"}, {"sin", "sin"}, {"cos", "cos"},       {"tan", "tan"},    {"asin", "asin"},
            {"acos", "acos"}, {"atan", "atan"},   {"exp", "exp"},           {"exp2", "exp2"},  {"log", "log"},
            {"log2", "log2"}, {"round", "round"}, {"trunc", "trunc"},       {"sign", "sign"},  {"radians", "radians"},
            {"degrees", "degrees"}, {"ddx", "dFdx"}, {"ddy", "dFdy"},      {"fwidth", "fwidth"}};
        auto u = kUnary.find(name);
        if (u != kUnary.end()) return unary(u->second);
        if (name == "saturate") {
            std::vector<Val> a = Unify(args, 1);
            r.ty = a[0].ty;
            r.code = "clamp(" + a[0].code + ", 0.0, 1.0)";
            return r;
        }
        if (name == "max" || name == "min" || name == "pow" || name == "step") return nary(name.c_str(), 2);
        if (name == "atan2") return nary("atan", 2);
        if (name == "fmod") {
            usesFmod_ = true;
            return nary("cg_fmod", 2);
        }
        if (name == "clamp" || name == "smoothstep") return nary(name.c_str(), 3);
        if (name == "lerp") return nary("mix", 3);
        if (name == "reflect") return nary("reflect", 2);
        if (name == "normalize") return unary("normalize");
        if (name == "dot" || name == "distance") {
            std::vector<Val> a = Unify(args, 2);
            r.ty = ScalarOf(B::kFloat);
            r.code = name + "(" + a[0].code + ", " + a[1].code + ")";
            return r;
        }
        if (name == "length") {
            std::vector<Val> a = Unify(args, 1);
            r.ty = ScalarOf(B::kFloat);
            r.code = "length(" + a[0].code + ")";
            return r;
        }
        if (name == "cross") {
            if (args.size() != 2) Fail("cross takes two arguments");
            const Ty v3 = VectorOf(B::kFloat, 3);
            r.ty = v3;
            r.code = "cross(" + Conv(args[0], v3).code + ", " + Conv(args[1], v3).code + ")";
            return r;
        }
        if (name == "any" || name == "all") {
            if (args.size() != 1 || !args[0].ty.Numeric() || args[0].ty.Matrix()) Fail(name + " takes one vector or scalar");
            r.ty = ScalarOf(B::kBool);
            if (args[0].ty.Scalar()) {
                r.code = AsBool(args[0]).code;
            } else if (args[0].ty.b == B::kBool) {
                r.code = name + "(" + args[0].code + ")";
            } else {
                const std::string zero = (args[0].ty.b == B::kFloat ? "vec" : "ivec") + std::to_string(args[0].ty.rows) + "(0)";
                r.code = name + "(notEqual(" + args[0].code + ", " + zero + "))";
            }
            return r;
        }
        if (name == "transpose") {
            if (args.size() != 1 || !args[0].ty.Matrix()) Fail("transpose takes a matrix");
            r.ty = Ty{B::kFloat, args[0].ty.cols, args[0].ty.rows, true, -1, 0};
            r.code = "transpose(" + args[0].code + ")";
            return r;
        }
        if (name == "mul") return Mul(args);
        if (name == "modf") {
            if (args.size() != 2 || !args[1].lval) Fail("modf(x, out ip)");
            if (args[0].ty.Numeric() && args[1].ty.Scalar() && args[1].ty.b == B::kFloat) {
                r.ty = ScalarOf(B::kFloat);
                r.code = "modf(" + Conv(args[0], ScalarOf(B::kFloat)).code + ", " + args[1].code + ")";
                return r;
            }
            Fail("modf is supported on floats only");
        }
        if (name == "tex2D" || name == "tex2Dgrad" || name == "tex2Dproj" || name == "tex2Dlod" || name == "texCUBE") {
            if (args.empty() || !args[0].ty.Sampler()) Fail(name + " needs a sampler");
            r.ty = VectorOf(B::kFloat, 4);
            const bool cube = name == "texCUBE";
            const Val uv = Conv(args.at(1), cube ? VectorOf(B::kFloat, 3) : VectorOf(B::kFloat, name == "tex2Dproj" || name == "tex2Dlod" ? 4 : 2));
            if ((name == "tex2D" || cube) && stage_ == Stage::kPixel) {  // (a bias argument is a fragment shader's only)
                usesLodBias_ = true;
                r.code = "texture(" + args[0].code + ", " + uv.code + ", DOTD_LOD_BIAS)";
            } else if (name == "tex2D" || cube) {
                r.code = "texture(" + args[0].code + ", " + uv.code + ")";
            } else if (name == "tex2Dproj") {
                r.code = "textureProj(" + args[0].code + ", " + uv.code + ")";
            } else if (name == "tex2Dlod") {
                r.code = "textureLod(" + args[0].code + ", " + uv.code + ".xy, " + uv.code + ".w)";
            } else {
                r.code = "textureGrad(" + args[0].code + ", " + uv.code + ", " + Conv(args.at(2), VectorOf(B::kFloat, 2)).code +
                         ", " + Conv(args.at(3), VectorOf(B::kFloat, 2)).code + ")";
            }
            return r;
        }
        Fail("unknown function " + name);
    }

    // mul: see the matrix convention in cg_to_glsl.h (the GLSL matrix is the transpose).
    Val Mul(const std::vector<Val>& args) {
        if (args.size() != 2) Fail("mul takes two arguments");
        const Val& a = args[0];
        const Val& b = args[1];
        Val r;
        if (a.ty.Matrix() && b.ty.Vector()) {
            const Val v = Conv(b, VectorOf(B::kFloat, a.ty.cols));
            r.ty = a.ty.rows == 1 ? ScalarOf(B::kFloat) : VectorOf(B::kFloat, a.ty.rows);
            r.code = "(" + v.code + " * " + a.code + ")";
            return r;
        }
        if (a.ty.Vector() && b.ty.Matrix()) {
            const Val v = Conv(a, VectorOf(B::kFloat, b.ty.rows));
            r.ty = b.ty.cols == 1 ? ScalarOf(B::kFloat) : VectorOf(B::kFloat, b.ty.cols);
            r.code = "(" + b.code + " * " + v.code + ")";
            return r;
        }
        if (a.ty.Matrix() && b.ty.Matrix()) {
            if (a.ty.cols != b.ty.rows) Fail("mul: matrix sizes do not match");
            r.ty = Ty{B::kFloat, a.ty.rows, b.ty.cols, true, -1, 0};
            r.code = "(" + b.code + " * " + a.code + ")";
            return r;
        }
        if (a.ty.Vector() && b.ty.Vector() && a.ty.rows == b.ty.rows) {
            r.ty = ScalarOf(B::kFloat);
            r.code = "dot(" + a.code + ", " + b.code + ")";
            return r;
        }
        Fail("mul: unsupported operand types " + CgTypeName(a.ty) + ", " + CgTypeName(b.ty));
    }

    // ---- initializers
    Val ParseInitializer(const Ty& target) {
        if (!IsPunct("{")) return Conv(ParseAssign(), target);
        Next();
        std::vector<Val> items;
        Ty elem = target;
        if (target.arr > 0) elem.arr = 0;
        else if (target.Vector()) elem = ScalarOf(target.b);
        else if (target.Matrix()) elem = VectorOf(target.b, target.cols);
        else Fail("initializer list for a non-aggregate");
        while (!IsPunct("}")) {
            items.push_back(ParseInitializer(elem));
            if (!AcceptPunct(",")) break;
        }
        ExpectPunct("}");
        Val r;
        r.ty = target;
        if (target.arr > 0) {
            if (items.size() != static_cast<size_t>(target.arr)) Fail("initializer list size does not match the array");
            r.code = GlslType(elem) + "[" + std::to_string(target.arr) + "](";
        } else {
            if (items.size() != static_cast<size_t>(target.Vector() ? target.rows : target.rows)) Fail("initializer list size does not match");
            r.code = GlslType(target) + "(";
        }
        for (size_t i = 0; i < items.size(); ++i) r.code += (i ? ", " : "") + items[i].code;
        r.code += ")";
        return r;
    }

    // ---- statements ---------------------------------------------------------------------------------
    bool StartsDeclaration() const {
        size_t k = 0;
        while (Peek(k).kind == T::kIdent &&
               (Peek(k).text == "const" || Peek(k).text == "static" || Peek(k).text == "uniform" || Peek(k).text == "row_major" ||
                Peek(k).text == "column_major" || Peek(k).text == "in" || Peek(k).text == "out" || Peek(k).text == "inout")) {
            ++k;
        }
        if (!IsTypeToken(k)) return false;
        return Peek(k + 1).kind == T::kIdent;
    }

    void ParseLocalDeclaration(std::string* out, bool allowLeakyFor = false) {
        bool isConst = false;
        while (Peek().kind == T::kIdent &&
               (Peek().text == "const" || Peek().text == "static" || Peek().text == "uniform" || Peek().text == "row_major" ||
                Peek().text == "column_major")) {
            if (Peek().text == "const") isConst = true;
            Next();
        }
        Ty base;
        if (!ParseTypeName(Peek().text, &base)) Fail("expected a type");
        Next();
        (void)allowLeakyFor;
        do {
            const std::string name = ExpectIdent();
            Ty ty = base;
            if (AcceptPunct("[")) {
                ty.arr = ConstInt();
                ExpectPunct("]");
            }
            if (AcceptPunct(":")) Next();  // a semantic on a local: ignored
            std::string init;
            Val initVal;
            bool hasInit = false;
            if (AcceptPunct("=")) {
                initVal = ParseInitializer(ty);
                hasInit = true;
            }
            const std::string glsl = Declare(name, ty);
            if (isConst && hasInit && ty.Scalar() && ty.b == B::kInt && initVal.literal) {
                Var* v = Lookup(name);
                v->constInt = true;
                v->constValue = static_cast<int>(std::strtol(initVal.code.c_str(), nullptr, 0));
            }
            *out += (isConst && hasInit ? "const " : "") + Declarator(ty, glsl) + (hasInit ? " = " + initVal.code : "") + ";\n";
        } while (AcceptPunct(","));
        ExpectPunct(";");
    }

    void ParseStatement(std::string* out) {
        if (IsPunct("{")) {
            Next();
            PushScope();
            *out += "{\n";
            while (!IsPunct("}")) ParseStatement(out);
            Next();
            *out += "}\n";
            PopScope();
            return;
        }
        if (AcceptPunct(";")) return;
        if (IsIdent("if")) {
            Next();
            ExpectPunct("(");
            Val c = AsBool(ParseExpr());
            ExpectPunct(")");
            *out += "if (" + c.code + ") {\n";
            PushScope();
            ParseStatement(out);
            PopScope();
            *out += "}\n";
            if (IsIdent("else")) {
                Next();
                *out += "else {\n";
                PushScope();
                ParseStatement(out);
                PopScope();
                *out += "}\n";
            }
            return;
        }
        if (IsIdent("for")) {
            ParseFor(out);
            return;
        }
        if (IsIdent("while")) {
            Next();
            ExpectPunct("(");
            Val c = AsBool(ParseExpr());
            ExpectPunct(")");
            *out += "while (" + c.code + ") {\n";
            PushScope();
            ParseStatement(out);
            PopScope();
            *out += "}\n";
            return;
        }
        if (IsIdent("do")) {
            Next();
            *out += "do {\n";
            PushScope();
            ParseStatement(out);
            PopScope();
            if (!IsIdent("while")) Fail("expected while after do");
            Next();
            ExpectPunct("(");
            Val c = AsBool(ParseExpr());
            ExpectPunct(")");
            ExpectPunct(";");
            *out += "} while (" + c.code + ");\n";
            return;
        }
        if (IsIdent("return")) {
            Next();
            if (AcceptPunct(";")) {
                *out += "return;\n";
                return;
            }
            Val v = ParseExpr();
            ExpectPunct(";");
            if (currentRet_.b == B::kVoid) Fail("returning a value from a void function");
            *out += "return " + Conv(v, currentRet_).code + ";\n";
            return;
        }
        if (IsIdent("break") || IsIdent("continue") || IsIdent("discard")) {
            *out += Next().text + ";\n";
            ExpectPunct(";");
            return;
        }
        if (IsIdent("asm")) Fail("asm blocks are not supported");
        if (StartsDeclaration()) {
            ParseLocalDeclaration(out);
            return;
        }
        multiAssignCode_ = false;
        Val v = ParseExpr();
        ExpectPunct(";");
        *out += v.code + (multiAssignCode_ ? "\n" : ";\n");
    }

    void ParseFor(std::string* out) {
        Next();
        ExpectPunct("(");
        PushScope();
        std::string init;
        std::string pre;
        if (!IsPunct(";")) {
            if (StartsDeclaration()) {
                // Cg's leaky scope: the loop variable belongs to the enclosing block.
                bool isConst = false;
                while (IsIdent("const") || IsIdent("static")) {
                    if (IsIdent("const")) isConst = true;
                    Next();
                }
                (void)isConst;
                Ty base;
                ParseTypeName(Peek().text, &base);
                Next();
                std::string parts;
                do {
                    const std::string name = ExpectIdent();
                    Var* existing = nullptr;
                    auto it = scopes_[scopes_.size() - 2].find(name);
                    if (it != scopes_[scopes_.size() - 2].end()) existing = &it->second;
                    ExpectPunct("=");
                    Val v = ParseAssign();
                    if (existing != nullptr && existing->ty == base) {
                        parts += (parts.empty() ? "" : ", ") + existing->glsl + " = " + Conv(v, base).code;
                    } else {
                        Var decl;
                        decl.ty = base;
                        decl.glsl = SafeName(name);
                        scopes_[scopes_.size() - 2][name] = decl;
                        pre += Declarator(base, decl.glsl) + ";\n";
                        parts += (parts.empty() ? "" : ", ") + decl.glsl + " = " + Conv(v, base).code;
                    }
                } while (AcceptPunct(","));
                init = parts;
            } else {
                init = ParseExpr().code;
            }
        }
        ExpectPunct(";");
        std::string cond = "true";
        if (!IsPunct(";")) cond = AsBool(ParseExpr()).code;
        ExpectPunct(";");
        std::string iter;
        if (!IsPunct(")")) iter = ParseExpr().code;
        ExpectPunct(")");
        *out += pre + "for (" + init + "; " + cond + "; " + iter + ") {\n";
        PushScope();
        ParseStatement(out);
        PopScope();
        *out += "}\n";
        PopScope();
    }

    // ---- top level -----------------------------------------------------------------------------------
    void TopLevel() {
        if (AcceptPunct(";")) return;
        if (IsIdent("struct")) {
            ParseStruct();
            return;
        }
        if (IsIdent("typedef")) {
            Next();
            Ty t;
            if (!ParseTypeName(Peek().text, &t)) Fail("typedef of an unknown type");
            Next();
            const std::string name = ExpectIdent();
            ExpectPunct(";");
            typedefs_[name] = t;
            return;
        }
        bool isUniform = false, isConst = false, isStatic = false;
        while (Peek().kind == T::kIdent && (Peek().text == "uniform" || Peek().text == "const" || Peek().text == "static" ||
                                            Peek().text == "extern" || Peek().text == "row_major" || Peek().text == "column_major" ||
                                            Peek().text == "shared")) {
            if (Peek().text == "uniform") isUniform = true;
            if (Peek().text == "const") isConst = true;
            if (Peek().text == "static") isStatic = true;
            Next();
        }
        (void)isStatic;
        Ty base;
        if (!ParseTypeName(Peek().text, &base)) Fail("expected a declaration near '" + Peek().text + "'");
        Next();
        std::string name = ExpectIdent();
        if (IsPunct("(")) {
            ParseFunction(base, name);
            return;
        }
        for (;;) {
            Ty ty = base;
            if (AcceptPunct("[")) {
                ty.arr = ConstInt();
                ExpectPunct("]");
            }
            std::string semantic;
            char regClass = 0;
            int regIndex = 0;
            if (AcceptPunct(":")) {
                semantic = ExpectIdent();
                if (semantic == "register") {
                    ExpectPunct("(");
                    const std::string reg = ExpectIdent();
                    ExpectPunct(")");
                    regClass = reg[0];
                    regIndex = std::atoi(reg.c_str() + 1);
                    semantic.clear();
                }
            }
            Val init;
            bool hasInit = false;
            if (AcceptPunct("=")) {
                init = ParseInitializer(ty);
                hasInit = true;
            }
            if (ty.arr == 0 && ty.Numeric() == false && !ty.Sampler() && ty.b != B::kStruct) Fail("bad global type");
            const std::string glsl = Declare(name, ty);
            if (ty.Sampler()) {
                decls_ += "uniform " + Declarator(ty, glsl) + ";\n";
                samplers_.push_back({glsl, regIndex});
            } else if (isUniform) {
                decls_ += "uniform " + Declarator(ty, glsl) + ";\n";
                UniformInfo info;
                info.name = glsl;
                Ty plain = ty;
                plain.arr = 0;
                info.cgType = CgTypeName(plain);
                info.glslType = GlslType(plain);
                info.arraySize = ty.arr;
                info.registerClass = regClass != 0 ? regClass : 'c';
                info.registerIndex = regIndex;
                info.registerCount = (plain.Matrix() ? plain.rows : 1) * std::max(1, ty.arr);
                uniforms_.push_back(info);
            } else {
                if (isConst && hasInit && ty.Scalar() && ty.b == B::kInt && init.literal) {
                    Var* v = Lookup(name);
                    v->constInt = true;
                    v->constValue = static_cast<int>(std::strtol(init.code.c_str(), nullptr, 0));
                }
                decls_ += (isConst && hasInit ? "const " : "") + Declarator(ty, glsl) + (hasInit ? " = " + init.code : "") + ";\n";
            }
            if (AcceptPunct(",")) {
                name = ExpectIdent();
                continue;
            }
            break;
        }
        ExpectPunct(";");
    }

    void ParseStruct() {
        Next();
        const std::string name = ExpectIdent();
        StructDef def;
        def.name = SafeName(name);
        ExpectPunct("{");
        while (!IsPunct("}")) {
            Ty base;
            while (IsIdent("uniform") || IsIdent("const") || IsIdent("static")) Next();
            if (!ParseTypeName(Peek().text, &base)) Fail("expected a member type near '" + Peek().text + "'");
            Next();
            do {
                Field f;
                f.name = ExpectIdent();
                f.glsl = SafeName(f.name);
                f.ty = base;
                if (AcceptPunct("[")) {
                    f.ty.arr = ConstInt();
                    if (f.ty.arr <= 0) Fail("zero-sized array member " + f.name);
                    ExpectPunct("]");
                }
                if (AcceptPunct(":")) f.semantic = ExpectIdent();
                def.fields.push_back(f);
            } while (AcceptPunct(","));
            ExpectPunct(";");
        }
        Next();
        AcceptPunct(";");
        std::string text = "struct " + def.name + " {\n";
        for (const Field& f : def.fields) text += "  " + Declarator(f.ty, f.glsl) + ";\n";
        if (def.fields.empty()) text += "  float cg_unused;\n";
        text += "};\n";
        decls_ += text;
        structs_.push_back(def);
    }

    void ParseFunction(const Ty& ret, const std::string& name) {
        Func f;
        f.ret = ret;
        f.glsl = SafeName(name);
        ExpectPunct("(");
        std::vector<std::string> paramNames;
        std::vector<std::string> paramSemantics;
        if (!IsPunct(")")) {
            do {
                int qual = 0;
                while (Peek().kind == T::kIdent && (Peek().text == "in" || Peek().text == "out" || Peek().text == "inout" ||
                                                     Peek().text == "uniform" || Peek().text == "const")) {
                    if (Peek().text == "out") qual = 1;
                    if (Peek().text == "inout") qual = 2;
                    Next();
                }
                Ty pt;
                if (!ParseTypeName(Peek().text, &pt)) Fail("expected a parameter type near '" + Peek().text + "'");
                if (pt.b == B::kVoid && IsPunct(")", 1)) {
                    Next();
                    break;
                }
                Next();
                std::string pname = ExpectIdent();
                if (AcceptPunct("[")) {
                    pt.arr = ConstInt();
                    ExpectPunct("]");
                }
                std::string sem;
                if (AcceptPunct(":")) sem = ExpectIdent();
                f.params.push_back({pt, qual});
                paramNames.push_back(pname);
                paramSemantics.push_back(sem);
            } while (AcceptPunct(","));
        }
        ExpectPunct(")");
        std::string retSemantic;
        if (AcceptPunct(":")) retSemantic = ExpectIdent();
        funcs_[name].push_back(f);
        if (AcceptPunct(";")) return;  // prototype
        // the definition
        PushScope();
        std::string head = GlslType(f.ret) + " " + f.glsl + "(";
        for (size_t i = 0; i < f.params.size(); ++i) {
            const std::string glsl = Declare(paramNames[i], f.params[i].ty);
            const char* q = f.params[i].qual == 0 ? "" : (f.params[i].qual == 1 ? "out " : "inout ");
            head += (i ? ", " : "") + std::string(q) + Declarator(f.params[i].ty, glsl);
        }
        head += ")";
        currentRet_ = f.ret;
        ExpectPunct("{");
        std::string bodyText;
        PushScope();
        while (!IsPunct("}")) ParseStatement(&bodyText);
        Next();
        PopScope();
        PopScope();
        body_ += head + " {\n" + bodyText + "}\n";
        if (name == entry_) {
            entryFunc_ = f;
            entryParams_ = paramNames;
            entrySemantics_ = paramSemantics;
            entryRetSemantic_ = retSemantic;
            entryFound_ = true;
        }
    }

    Func entryFunc_;
    std::vector<std::string> entryParams_;
    std::vector<std::string> entrySemantics_;
    std::string entryRetSemantic_;
    bool entryFound_ = false;

    // ---- entry wrapper -------------------------------------------------------------------------------
    static int AttributeLocation(const std::string& semantic) {
        if (semantic == "POSITION" || semantic == "POSITION0") return 0;
        if (semantic == "BLENDWEIGHT" || semantic == "BLENDWEIGHT0") return 1;
        if (semantic == "NORMAL" || semantic == "NORMAL0") return 2;
        if (semantic == "COLOR" || semantic == "COLOR0") return 3;
        if (semantic == "COLOR1") return 4;
        if (semantic == "FOG" || semantic == "TESSFACTOR") return 5;
        if (semantic == "PSIZE") return 6;
        if (semantic == "BLENDINDICES" || semantic == "BLENDINDICES0") return 7;
        if (semantic == "TANGENT" || semantic == "TANGENT0") return 14;
        if (semantic == "BINORMAL" || semantic == "BINORMAL0") return 15;
        if (semantic.compare(0, 8, "TEXCOORD") == 0) {
            const int n = semantic.size() > 8 ? std::atoi(semantic.c_str() + 8) : 0;
            if (n >= 0 && n < 8) return 8 + n;
        }
        return -1;
    }

    void EmitWrapper(Translation* out) {
        if (!entryFound_) throw CgError{"entry function " + entry_ + " not found"};
        std::string decl;  // attributes / varyings / outputs
        std::string main = "void main() {\n";
        std::set<int> usedLocations;
        std::vector<std::string> callArgs;
        auto addAttribute = [&](const std::string& glslName, const Ty& ty, const std::string& semantic, const std::string& cgName) {
            const int loc = AttributeLocation(semantic);
            if (loc < 0) throw CgError{"unsupported vertex input semantic " + semantic + " (" + cgName + ")"};
            if (!usedLocations.insert(loc).second) throw CgError{"vertex input semantic " + semantic + " collides with another input"};
            decl += "layout(location = " + std::to_string(loc) + ") in " + Declarator(ty, glslName) + ";\n";
            AttributeInfo info;
            info.name = glslName;
            info.semantic = semantic;
            info.glslType = GlslType(ty);
            info.location = loc;
            out->attributes.push_back(info);
        };
        auto isPosition = [](const std::string& s) { return s == "POSITION" || s == "POSITION0" || s == "SV_Position"; };
        const char* inQual = stage_ == Stage::kVertex ? "out" : "in";
        auto addVarying = [&](const Field& f) {
            const std::string name = "v_" + f.glsl;
            decl += std::string(inQual) + " " + Declarator(f.ty, name) + ";\n";
            VaryingInfo info;
            info.name = name;
            info.semantic = f.semantic;
            Ty plain = f.ty;
            plain.arr = 0;
            info.glslType = GlslType(plain);
            info.arraySize = f.ty.arr;
            out->varyings.push_back(info);
        };

        if (stage_ == Stage::kVertex) {
            for (size_t i = 0; i < entryFunc_.params.size(); ++i) {
                const Ty& pt = entryFunc_.params[i].ty;
                const std::string var = "cg_in" + std::to_string(i);
                if (pt.b == B::kStruct) {
                    const StructDef& def = structs_[static_cast<size_t>(pt.st)];
                    main += "  " + GlslType(pt) + " " + var + ";\n";
                    for (const Field& f : def.fields) {
                        const std::string an = "a_" + f.glsl;
                        addAttribute(an, f.ty, f.semantic, f.name);
                        main += "  " + var + "." + f.glsl + " = " + an + ";\n";
                    }
                } else {
                    const std::string an = "a_" + SafeName(entryParams_[i]);
                    addAttribute(an, pt, entrySemantics_[i], entryParams_[i]);
                    main += "  " + GlslType(pt) + " " + var + " = " + an + ";\n";
                }
                callArgs.push_back(var);
            }
            std::string call = entryFunc_.glsl + "(";
            for (size_t i = 0; i < callArgs.size(); ++i) call += (i ? ", " : "") + callArgs[i];
            call += ")";
            if (entryFunc_.ret.b == B::kStruct) {
                const StructDef& def = structs_[static_cast<size_t>(entryFunc_.ret.st)];
                main += "  " + GlslType(entryFunc_.ret) + " cg_out = " + call + ";\n";
                bool wrotePosition = false;
                for (const Field& f : def.fields) {
                    if (isPosition(f.semantic)) {
                        main += "  gl_Position = " + std::string("cg_out.") + f.glsl + ";\n";
                        wrotePosition = true;
                    } else {
                        addVarying(f);
                        main += "  v_" + f.glsl + " = cg_out." + f.glsl + ";\n";
                    }
                }
                if (!wrotePosition) throw CgError{"the vertex shader returns no POSITION"};
            } else if (isPosition(entryRetSemantic_)) {
                main += "  gl_Position = " + call + ";\n";
            } else {
                throw CgError{"unsupported vertex shader return"};
            }
        } else {
            for (size_t i = 0; i < entryFunc_.params.size(); ++i) {
                const Ty& pt = entryFunc_.params[i].ty;
                const std::string var = "cg_in" + std::to_string(i);
                if (pt.b != B::kStruct) throw CgError{"a pixel shader parameter must be a struct"};
                const StructDef& def = structs_[static_cast<size_t>(pt.st)];
                main += "  " + GlslType(pt) + " " + var + ";\n";
                for (const Field& f : def.fields) {
                    if (isPosition(f.semantic)) continue;  // not a varying
                    addVarying(f);
                    main += "  " + var + "." + f.glsl + " = v_" + f.glsl + ";\n";
                }
                callArgs.push_back(var);
            }
            std::string call = entryFunc_.glsl + "(";
            for (size_t i = 0; i < callArgs.size(); ++i) call += (i ? ", " : "") + callArgs[i];
            call += ")";
            auto colorIndex = [](const std::string& s) { return s == "COLOR" || s == "COLOR0" ? 0 : (s == "COLOR1" ? 1 : (s == "COLOR2" ? 2 : (s == "COLOR3" ? 3 : -1))); };
            if (entryFunc_.ret.b == B::kStruct) {
                const StructDef& def = structs_[static_cast<size_t>(entryFunc_.ret.st)];
                main += "  " + GlslType(entryFunc_.ret) + " cg_out = " + call + ";\n";
                for (const Field& f : def.fields) {
                    if (f.semantic == "DEPTH" || f.semantic == "DEPTH0") {
                        main += "  gl_FragDepth = cg_out." + f.glsl + ";\n";
                        continue;
                    }
                    const int idx = colorIndex(f.semantic);
                    if (idx < 0) throw CgError{"unsupported pixel output semantic " + f.semantic};
                    const std::string name = "o_" + f.glsl;
                    decl += "layout(location = " + std::to_string(idx) + ") out " + GlslType(f.ty) + " " + name + ";\n";
                    if (out->colorOutputs.size() <= static_cast<size_t>(idx)) out->colorOutputs.resize(static_cast<size_t>(idx) + 1);
                    out->colorOutputs[static_cast<size_t>(idx)] = name;
                    main += "  " + name + " = cg_out." + f.glsl + ";\n";
                }
            } else {
                const int idx = colorIndex(entryRetSemantic_);
                if (idx != 0) throw CgError{"unsupported pixel shader return"};
                decl += "layout(location = 0) out " + GlslType(entryFunc_.ret) + " o_color;\n";
                out->colorOutputs.push_back("o_color");
                main += "  o_color = " + call + ";\n";
            }
        }
        if (stage_ == Stage::kPixel && !out->colorOutputs.empty()) {
            // The PS3's fixed-function alpha test (RW alphaTestFunction 1..7 = never, less, equal, less-equal,
            // greater, not-equal, greater-equal; 8 = always: the driver's table 0xa72540 is GL_NEVER 0x200 .. GL_ALWAYS
            // 0x207 in that order) on the first colour output's alpha. Platform addition:
            // the host sets dotd_alphaFunc / dotd_alphaRef (0..1) per draw (RwDevice's render states).
            // Alpha-to-coverage (platform addition, MSAA only: device.cpp SetAlphaTest sets dotd_alphaCoverage to 1 for a
            // test keeping the alpha above the reference, -1 below, with GL_SAMPLE_ALPHA_TO_COVERAGE on): no discard; the
            // alpha becomes the coverage, 0.5 at the reference and steep over one pixel's change of the alpha
            // (fwidth), so the samples are covered where the test would keep them and the cut-out's edge is smooth.
            // (Uniform control flow: fwidth is defined.)
            decl += "uniform int dotd_alphaFunc;\nuniform float dotd_alphaRef;\nuniform int dotd_alphaCoverage;\n";
            // DEV (DOTD_ALPHATEST=0, a measurement only: the cut-out materials then draw solid): no alpha test, so no
            // discard in any pixel shader (a discard anywhere in a shader turns a phone GPU's early depth test off).
            static const bool noAlphaTest = [] {
                const char* env = std::getenv("DOTD_ALPHATEST");
                return env != nullptr && std::strcmp(env, "0") == 0;
            }();
            if (!noAlphaTest)
            main += "  if (dotd_alphaCoverage != 0) {\n    float a = " + out->colorOutputs[0] + ".a;\n    " +
                    out->colorOutputs[0] + ".a = clamp(float(dotd_alphaCoverage) * (a - dotd_alphaRef) / "
                    "max(fwidth(a), 1e-4) + 0.5, 0.0, 1.0);\n  } else"
                    "  if (dotd_alphaFunc >= 1 && dotd_alphaFunc <= 7) {\n    float a = " + out->colorOutputs[0] +
                    ".a;\n    bool keep = dotd_alphaFunc == 1 ? false : dotd_alphaFunc == 2 ? a < dotd_alphaRef : "
                    "dotd_alphaFunc == 3 ? a == dotd_alphaRef : dotd_alphaFunc == 4 ? a <= dotd_alphaRef : "
                    "dotd_alphaFunc == 5 ? a > dotd_alphaRef : dotd_alphaFunc == 6 ? a != dotd_alphaRef : a >= dotd_alphaRef;\n"
                    "    if (!keep) discard;\n  }\n";
        }
        main += "}\n";
        wrapper_ = decl + main;
    }
};

}  // namespace

bool Translate(const std::string& preprocessed, Stage stage, const char* entry, Translation* out, std::string* error) {
    try {
        Translator translator(preprocessed, stage, entry);
        Translation result;
        translator.Run(&result);
        *out = result;
        return true;
    } catch (const CgError& e) {
        *error = e.message;
        return false;
    }
}

bool LoadGameSources(const char* ebootPath, Sources* out, std::string* error) {
    // Through hostfs: on the web the EBOOT is read from the served USRDIR like every other game file.
    std::FILE* file = dotd::platform::hostfs::OpenStdio(ebootPath);
    if (file == nullptr) {
        *error = std::string("cannot open ") + ebootPath;
        return false;
    }
    struct Closer {
        std::FILE* f;
        ~Closer() { std::fclose(f); }
    } closer{file};
    // The disc's EBOOT.BIN (a SELF) is decrypted in memory into the ELF the offsets below are in
    // (platform/self_decrypt.h); a decrypted EBOOT.elf is read in place (only the two blocks: on the web the file is
    // fetched by range).
    std::vector<uint8_t> elf;
    uint8_t magic[4] = {};
    const bool isSelf = std::fread(magic, 1, sizeof magic, file) == sizeof magic && dotd::platform::IsSelf(magic, sizeof magic);
    if (isSelf) {
        std::vector<uint8_t> self;
        std::fseek(file, 0, SEEK_SET);
        uint8_t chunk[1 << 16];
        for (size_t got; (got = std::fread(chunk, 1, sizeof chunk, file)) != 0;) self.insert(self.end(), chunk, chunk + got);
        std::string why;
        if (!dotd::platform::DecryptSelf(self, &elf, &why)) {
            *error = std::string("cannot decrypt ") + ebootPath + ": " + why;
            return false;
        }
    }
    const auto readAt = [&](size_t offset, size_t at, char* buffer, size_t bytes) -> size_t {
        if (isSelf) {
            const size_t from = offset + at;
            if (from >= elf.size()) return 0;
            const size_t n = std::min(bytes, elf.size() - from);
            std::memcpy(buffer, elf.data() + from, n);
            return n;
        }
        if (at == 0) std::fseek(file, static_cast<long>(offset), SEEK_SET);
        return std::fread(buffer, 1, bytes, file);
    };
    struct Block {
        size_t offset;
        const char* firstLine;
        const char* entry;
        std::string* target;
    };
    const Block blocks[] = {{0xc26750, "#pragma pack_matrix (row_major)", "VertexShaderMain", &out->vertex},
                            {0xc19848, "#ifndef externBasicShader", "PixelShaderMain", &out->pixel}};
    for (const Block& b : blocks) {
        std::string text;
        char chunk[4096];
        bool terminated = false;
        while (!terminated && text.size() < (1u << 20)) {
            const size_t got = readAt(b.offset, text.size(), chunk, sizeof chunk);
            if (got == 0) break;
            const char* nul = static_cast<const char*>(std::memchr(chunk, 0, got));
            text.append(chunk, nul != nullptr ? static_cast<size_t>(nul - chunk) : got);
            terminated = nul != nullptr;
        }
        if (!terminated || text.compare(0, std::strlen(b.firstLine), b.firstLine) != 0 || text.find(b.entry) == std::string::npos) {
            *error = std::string("the Cg block at file offset ") + std::to_string(b.offset) + " is not the expected " + b.entry +
                     " source (not the BLUS30205 executable?)";
            return false;
        }
        *b.target = text;
    }
    return true;
}

bool BuildStage(const Sources& sources, Stage stage, const std::vector<Define>& defines, Translation* out,
                std::string* error) {
    std::string text;
    if (!Preprocess(stage == Stage::kVertex ? sources.vertex : sources.pixel, defines, &text, error)) return false;
    return Translate(text, stage, stage == Stage::kVertex ? "VertexShaderMain" : "PixelShaderMain", out, error);
}

}  // namespace dotd::gfx::cg
