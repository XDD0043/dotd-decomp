// cg_preproc.cpp - see cg_preproc.h.
#include "platform/gfx/cg_preproc.h"

#include <cctype>
#include <cstdint>
#include <cstdlib>
#include <map>
#include <set>

namespace dotd::gfx::cg {
namespace {

enum class Kind { kIdent, kNumber, kString, kPunct, kSpace, kOther };

struct Tok {
    Kind kind;
    std::string text;
};
typedef std::vector<Tok> Toks;

bool IsIdentStart(char c) { return std::isalpha(static_cast<unsigned char>(c)) != 0 || c == '_'; }
bool IsIdentChar(char c) { return std::isalnum(static_cast<unsigned char>(c)) != 0 || c == '_'; }

Toks Tokenize(const std::string& s) {
    Toks out;
    size_t i = 0;
    while (i < s.size()) {
        const char c = s[i];
        if (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\f' || c == '\v') {
            size_t j = i;
            while (j < s.size() && (s[j] == ' ' || s[j] == '\t' || s[j] == '\r' || s[j] == '\n' || s[j] == '\f' || s[j] == '\v')) ++j;
            out.push_back({Kind::kSpace, " "});
            i = j;
        } else if (IsIdentStart(c)) {
            size_t j = i + 1;
            while (j < s.size() && IsIdentChar(s[j])) ++j;
            out.push_back({Kind::kIdent, s.substr(i, j - i)});
            i = j;
        } else if (std::isdigit(static_cast<unsigned char>(c)) != 0 ||
                   (c == '.' && i + 1 < s.size() && std::isdigit(static_cast<unsigned char>(s[i + 1])) != 0)) {
            size_t j = i + 1;  // a preprocessing number: digits, letters, dots and signed exponents
            while (j < s.size()) {
                if (IsIdentChar(s[j]) || s[j] == '.') {
                    ++j;
                } else if ((s[j] == '+' || s[j] == '-') && (s[j - 1] == 'e' || s[j - 1] == 'E') &&
                           !(s.size() > i + 1 && (s[i + 1] == 'x' || s[i + 1] == 'X'))) {
                    ++j;
                } else {
                    break;
                }
            }
            out.push_back({Kind::kNumber, s.substr(i, j - i)});
            i = j;
        } else if (c == '"' || c == '\'') {
            size_t j = i + 1;
            while (j < s.size() && s[j] != c) {
                if (s[j] == '\\' && j + 1 < s.size()) ++j;
                ++j;
            }
            if (j < s.size()) ++j;
            out.push_back({Kind::kString, s.substr(i, j - i)});
            i = j;
        } else {
            static const char* const two[] = {"##", "==", "!=", "<=", ">=", "&&", "||", "<<", ">>", "++", "--",
                                              "+=", "-=", "*=", "/="};
            bool matched = false;
            if (i + 1 < s.size()) {
                for (const char* op : two) {
                    if (s[i] == op[0] && s[i + 1] == op[1]) {
                        out.push_back({Kind::kPunct, std::string(op)});
                        i += 2;
                        matched = true;
                        break;
                    }
                }
            }
            if (matched) continue;
            const bool punct = std::ispunct(static_cast<unsigned char>(c)) != 0;
            out.push_back({punct ? Kind::kPunct : Kind::kOther, std::string(1, c)});
            ++i;
        }
    }
    return out;
}

std::string Join(const Toks& toks) {
    std::string out;
    for (const Tok& t : toks) out += t.text;
    return out;
}

struct Macro {
    bool function = false;
    std::vector<std::string> params;
    Toks body;
};

struct Pass {
    std::map<std::string, Macro> macros;
    std::string error;
    int line = 0;

    bool Fail(const std::string& message) {
        if (error.empty()) error = "line " + std::to_string(line) + ": " + message;
        return false;
    }

    static size_t SkipSpace(const Toks& t, size_t i) {
        while (i < t.size() && t[i].kind == Kind::kSpace) ++i;
        return i;
    }

    // Splits the tokens after the '(' at `open` into top-level comma separated arguments; `close` gets the index
    // of the matching ')'.
    bool CollectArgs(const Toks& in, size_t open, std::vector<Toks>* args, size_t* close) {
        int depth = 0;
        Toks current;
        for (size_t i = open + 1; i < in.size(); ++i) {
            const Tok& t = in[i];
            if (t.kind == Kind::kPunct && t.text == "(") {
                ++depth;
            } else if (t.kind == Kind::kPunct && t.text == ")") {
                if (depth == 0) {
                    args->push_back(current);
                    *close = i;
                    return true;
                }
                --depth;
            } else if (t.kind == Kind::kPunct && t.text == "," && depth == 0) {
                args->push_back(current);
                current.clear();
                continue;
            }
            current.push_back(t);
        }
        return Fail("unterminated macro call");
    }

    static Toks Trim(const Toks& t) {
        size_t a = 0, b = t.size();
        while (a < b && t[a].kind == Kind::kSpace) ++a;
        while (b > a && t[b - 1].kind == Kind::kSpace) --b;
        return Toks(t.begin() + static_cast<long>(a), t.begin() + static_cast<long>(b));
    }

    Toks Expand(const Toks& in, std::set<std::string>& disabled) {
        Toks out;
        size_t i = 0;
        while (i < in.size()) {
            const Tok& tok = in[i];
            auto it = tok.kind == Kind::kIdent ? macros.find(tok.text) : macros.end();
            if (it == macros.end() || disabled.count(tok.text) != 0) {
                out.push_back(tok);
                ++i;
                continue;
            }
            const Macro& m = it->second;
            if (!m.function) {
                disabled.insert(tok.text);
                Toks exp = Expand(m.body, disabled);
                disabled.erase(tok.text);
                out.insert(out.end(), exp.begin(), exp.end());
                ++i;
                continue;
            }
            const size_t open = SkipSpace(in, i + 1);
            if (open >= in.size() || in[open].text != "(" || in[open].kind != Kind::kPunct) {
                out.push_back(tok);
                ++i;
                continue;
            }
            std::vector<Toks> args;
            size_t close = 0;
            if (!CollectArgs(in, open, &args, &close)) return out;
            if (args.size() == 1 && Trim(args[0]).empty() && m.params.empty()) args.clear();
            if (args.size() != m.params.size()) {
                Fail("macro " + tok.text + " called with " + std::to_string(args.size()) + " arguments, expects " +
                     std::to_string(m.params.size()));
                return out;
            }
            for (Toks& a : args) a = Trim(a);
            // Substitute the parameters; operands of ## and # stay unexpanded.
            Toks sub;
            for (size_t b = 0; b < m.body.size(); ++b) {
                const Tok& bt = m.body[b];
                if (bt.kind == Kind::kIdent) {
                    size_t p = 0;
                    while (p < m.params.size() && m.params[p] != bt.text) ++p;
                    if (p < m.params.size()) {
                        // Is it next to ##?
                        size_t prev = b;
                        bool pasteBefore = false;
                        while (prev > 0) {
                            --prev;
                            if (m.body[prev].kind == Kind::kSpace) continue;
                            pasteBefore = m.body[prev].kind == Kind::kPunct && m.body[prev].text == "##";
                            break;
                        }
                        const size_t next = SkipSpace(m.body, b + 1);
                        const bool pasteAfter = next < m.body.size() && m.body[next].kind == Kind::kPunct && m.body[next].text == "##";
                        if (pasteBefore || pasteAfter) {
                            sub.insert(sub.end(), args[p].begin(), args[p].end());
                        } else {
                            Toks exp = Expand(args[p], disabled);
                            sub.insert(sub.end(), exp.begin(), exp.end());
                        }
                        continue;
                    }
                }
                sub.push_back(bt);
            }
            // ## pasting.
            Toks pasted;
            for (size_t b = 0; b < sub.size(); ++b) {
                if (sub[b].kind == Kind::kPunct && sub[b].text == "##") {
                    while (!pasted.empty() && pasted.back().kind == Kind::kSpace) pasted.pop_back();
                    size_t n = SkipSpace(sub, b + 1);
                    if (!pasted.empty() && n < sub.size()) {
                        pasted.back().text += sub[n].text;
                        if (pasted.back().kind == Kind::kPunct) pasted.back().kind = sub[n].kind;
                        b = n;
                        continue;
                    }
                    continue;
                }
                pasted.push_back(sub[b]);
            }
            disabled.insert(tok.text);
            Toks exp = Expand(pasted, disabled);
            disabled.erase(tok.text);
            out.insert(out.end(), exp.begin(), exp.end());
            i = close + 1;
        }
        return out;
    }

    // ---- #if expressions ----------------------------------------------------------------------------
    struct ExprParser {
        const Toks& t;
        size_t i = 0;
        bool ok = true;
        explicit ExprParser(const Toks& toks) : t(toks) {}
        const Tok* Peek() {
            while (i < t.size() && t[i].kind == Kind::kSpace) ++i;
            return i < t.size() ? &t[i] : nullptr;
        }
        bool Is(const char* s) {
            const Tok* p = Peek();
            return p != nullptr && p->kind == Kind::kPunct && p->text == s;
        }
        int64_t Primary() {
            const Tok* p = Peek();
            if (p == nullptr) {
                ok = false;
                return 0;
            }
            if (p->kind == Kind::kNumber) {
                ++i;
                std::string s = p->text;
                while (!s.empty() && (s.back() == 'u' || s.back() == 'U' || s.back() == 'l' || s.back() == 'L')) s.pop_back();
                if (s.find('.') != std::string::npos) {
                    ok = false;
                    return 0;
                }
                return std::strtoll(s.c_str(), nullptr, 0);
            }
            if (p->kind == Kind::kIdent) {
                ++i;
                return 0;  // an undefined identifier is 0
            }
            if (Is("(")) {
                ++i;
                const int64_t v = Ternary();
                if (!Is(")")) ok = false;
                else ++i;
                return v;
            }
            ok = false;
            return 0;
        }
        int64_t Unary() {
            if (Is("!")) { ++i; return !Unary(); }
            if (Is("-")) { ++i; return -Unary(); }
            if (Is("+")) { ++i; return Unary(); }
            if (Is("~")) { ++i; return ~Unary(); }
            return Primary();
        }
        int64_t Mul() {
            int64_t v = Unary();
            for (;;) {
                if (Is("*")) { ++i; v *= Unary(); }
                else if (Is("/")) { ++i; const int64_t d = Unary(); v = d != 0 ? v / d : 0; }
                else if (Is("%")) { ++i; const int64_t d = Unary(); v = d != 0 ? v % d : 0; }
                else return v;
            }
        }
        int64_t Add() {
            int64_t v = Mul();
            for (;;) {
                if (Is("+")) { ++i; v += Mul(); }
                else if (Is("-")) { ++i; v -= Mul(); }
                else return v;
            }
        }
        int64_t Shift() {
            int64_t v = Add();
            for (;;) {
                if (Is("<<")) { ++i; v <<= Add(); }
                else if (Is(">>")) { ++i; v >>= Add(); }
                else return v;
            }
        }
        int64_t Rel() {
            int64_t v = Shift();
            for (;;) {
                if (Is("<=")) { ++i; v = v <= Shift(); }
                else if (Is(">=")) { ++i; v = v >= Shift(); }
                else if (Is("<")) { ++i; v = v < Shift(); }
                else if (Is(">")) { ++i; v = v > Shift(); }
                else return v;
            }
        }
        int64_t Eq() {
            int64_t v = Rel();
            for (;;) {
                if (Is("==")) { ++i; v = v == Rel(); }
                else if (Is("!=")) { ++i; v = v != Rel(); }
                else return v;
            }
        }
        int64_t BitAnd() {
            int64_t v = Eq();
            while (Is("&")) { ++i; v &= Eq(); }
            return v;
        }
        int64_t BitXor() {
            int64_t v = BitAnd();
            while (Is("^")) { ++i; v ^= BitAnd(); }
            return v;
        }
        int64_t BitOr() {
            int64_t v = BitXor();
            while (Is("|")) { ++i; v |= BitXor(); }
            return v;
        }
        int64_t LogAnd() {
            int64_t v = BitOr();
            while (Is("&&")) { ++i; const int64_t r = BitOr(); v = v && r; }
            return v;
        }
        int64_t LogOr() {
            int64_t v = LogAnd();
            while (Is("||")) { ++i; const int64_t r = LogAnd(); v = v || r; }
            return v;
        }
        int64_t Ternary() {
            const int64_t c = LogOr();
            if (Is("?")) {
                ++i;
                const int64_t a = Ternary();
                if (!Is(":")) { ok = false; return 0; }
                ++i;
                const int64_t b = Ternary();
                return c != 0 ? a : b;
            }
            return c;
        }
    };

    bool EvalCondition(const std::string& text, bool* result) {
        Toks toks = Tokenize(text);
        // `defined X` / `defined(X)` before expansion.
        Toks pre;
        for (size_t i = 0; i < toks.size(); ++i) {
            if (toks[i].kind == Kind::kIdent && toks[i].text == "defined") {
                size_t j = SkipSpace(toks, i + 1);
                bool paren = false;
                if (j < toks.size() && toks[j].text == "(") {
                    paren = true;
                    j = SkipSpace(toks, j + 1);
                }
                if (j >= toks.size() || toks[j].kind != Kind::kIdent) return Fail("bad defined");
                const bool def = macros.count(toks[j].text) != 0;
                i = j;
                if (paren) {
                    i = SkipSpace(toks, i + 1);
                    if (i >= toks.size() || toks[i].text != ")") return Fail("bad defined");
                }
                pre.push_back({Kind::kNumber, def ? "1" : "0"});
            } else {
                pre.push_back(toks[i]);
            }
        }
        std::set<std::string> disabled;
        Toks expanded = Expand(pre, disabled);
        if (!error.empty()) return false;
        ExprParser parser(expanded);
        const int64_t v = parser.Ternary();
        if (!parser.ok || parser.Peek() != nullptr) return Fail("bad #if expression: " + text);
        *result = v != 0;
        return true;
    }

    bool Define(const std::string& rest) {
        size_t i = 0;
        while (i < rest.size() && (rest[i] == ' ' || rest[i] == '\t')) ++i;
        size_t j = i;
        while (j < rest.size() && IsIdentChar(rest[j])) ++j;
        if (j == i) return Fail("#define without a name");
        const std::string name = rest.substr(i, j - i);
        Macro m;
        size_t b = j;
        if (b < rest.size() && rest[b] == '(') {
            m.function = true;
            ++b;
            std::string current;
            for (; b < rest.size() && rest[b] != ')'; ++b) {
                if (rest[b] == ',') {
                    m.params.push_back(current);
                    current.clear();
                } else if (rest[b] != ' ' && rest[b] != '\t') {
                    current += rest[b];
                }
            }
            if (!current.empty() || !m.params.empty()) m.params.push_back(current);
            if (b < rest.size()) ++b;
        }
        Toks body = Tokenize(rest.substr(b));
        m.body = Trim(body);
        macros[name] = m;
        return true;
    }
};

struct Cond {
    bool parentActive;
    bool taken;
    bool active;
};

}  // namespace

bool Preprocess(const std::string& source, const std::vector<Define>& defines, std::string* output,
                std::string* error) {
    Pass pass;
    for (const Define& d : defines) {
        Macro m;
        m.body = Pass::Trim(Tokenize(d.value));
        pass.macros[d.name] = m;
    }
    // Comments out (newlines kept), then line continuations joined (the joined line is followed by blank
    // lines so numbering stays right).
    std::string text;
    text.reserve(source.size());
    for (size_t i = 0; i < source.size();) {
        if (source[i] == '/' && i + 1 < source.size() && source[i + 1] == '*') {
            size_t j = source.find("*/", i + 2);
            if (j == std::string::npos) j = source.size() - 2;
            for (size_t k = i; k < j + 2 && k < source.size(); ++k) {
                if (source[k] == '\n') text += '\n';
            }
            text += ' ';
            i = j + 2;
        } else if (source[i] == '/' && i + 1 < source.size() && source[i + 1] == '/') {
            while (i < source.size() && source[i] != '\n') ++i;
        } else {
            text += source[i++];
        }
    }
    std::vector<std::pair<int, std::string>> lines;
    {
        int number = 1;
        std::string current;
        int start = 1;
        for (size_t i = 0; i < text.size(); ++i) {
            const char c = text[i];
            if (c == '\r') continue;
            if (c == '\\' && i + 1 < text.size() && (text[i + 1] == '\n' || (text[i + 1] == '\r' && i + 2 < text.size() && text[i + 2] == '\n'))) {
                i += text[i + 1] == '\r' ? 2 : 1;
                ++number;
                continue;
            }
            if (c == '\n') {
                lines.push_back({start, current});
                current.clear();
                ++number;
                start = number;
            } else {
                current += c;
            }
        }
        lines.push_back({start, current});
    }

    std::vector<Cond> stack;
    std::string out;
    auto active = [&stack]() { return stack.empty() || stack.back().active; };
    int lastLine = 1;
    for (const auto& entry : lines) {
        pass.line = entry.first;
        // Keep the line count: one output line per source line (joined continuations add blank lines).
        while (lastLine < entry.first) {
            out += '\n';
            ++lastLine;
        }
        lastLine = entry.first + 1;
        const std::string& line = entry.second;
        size_t p = 0;
        while (p < line.size() && (line[p] == ' ' || line[p] == '\t')) ++p;
        if (p < line.size() && line[p] == '#') {
            ++p;
            while (p < line.size() && (line[p] == ' ' || line[p] == '\t')) ++p;
            size_t q = p;
            while (q < line.size() && IsIdentChar(line[q])) ++q;
            const std::string directive = line.substr(p, q - p);
            std::string rest = line.substr(q);
            if (directive == "if" || directive == "ifdef" || directive == "ifndef") {
                Cond c = {active(), false, false};
                if (c.parentActive) {
                    bool value = false;
                    if (directive == "if") {
                        if (!pass.EvalCondition(rest, &value)) {
                            *error = pass.error;
                            return false;
                        }
                    } else {
                        Toks t = Pass::Trim(Tokenize(rest));
                        const bool def = !t.empty() && pass.macros.count(t[0].text) != 0;
                        value = directive == "ifdef" ? def : !def;
                    }
                    c.active = value;
                    c.taken = value;
                }
                stack.push_back(c);
            } else if (directive == "elif") {
                if (stack.empty()) {
                    *error = "line " + std::to_string(pass.line) + ": #elif without #if";
                    return false;
                }
                Cond& c = stack.back();
                c.active = false;
                if (c.parentActive && !c.taken) {
                    bool value = false;
                    if (!pass.EvalCondition(rest, &value)) {
                        *error = pass.error;
                        return false;
                    }
                    c.active = value;
                    c.taken = value;
                }
            } else if (directive == "else") {
                if (stack.empty()) {
                    *error = "line " + std::to_string(pass.line) + ": #else without #if";
                    return false;
                }
                Cond& c = stack.back();
                c.active = c.parentActive && !c.taken;
                c.taken = true;
            } else if (directive == "endif") {
                if (stack.empty()) {
                    *error = "line " + std::to_string(pass.line) + ": #endif without #if";
                    return false;
                }
                stack.pop_back();
            } else if (!active()) {
                // other directives in an inactive region
            } else if (directive == "define") {
                if (!pass.Define(rest)) {
                    *error = pass.error;
                    return false;
                }
            } else if (directive == "undef") {
                Toks t = Pass::Trim(Tokenize(rest));
                if (!t.empty()) pass.macros.erase(t[0].text);
            } else if (directive == "error") {
                *error = "line " + std::to_string(pass.line) + ": #error" + rest;
                return false;
            } else if (directive == "pragma") {
                out += "#pragma" + rest;
            } else if (directive == "include") {
                *error = "line " + std::to_string(pass.line) + ": #include is not supported";
                return false;
            }
            out += '\n';
            continue;
        }
        if (active()) {
            std::set<std::string> disabled;
            Toks expanded = pass.Expand(Tokenize(line), disabled);
            if (!pass.error.empty()) {
                *error = pass.error;
                return false;
            }
            out += Join(expanded);
        }
        out += '\n';
    }
    if (!stack.empty()) {
        *error = "unterminated #if";
        return false;
    }
    *output = out;
    return true;
}

}  // namespace dotd::gfx::cg
