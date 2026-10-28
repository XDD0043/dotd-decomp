// capture_camera.cpp - see capture_camera.h.
#include "platform/capture_camera.h"

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "platform/log.h"

namespace dotd::platform::capturecam {
namespace {

// A small JSON reader: enough for capture.json (objects, arrays, strings, numbers, true / false / null).
struct Value {
    enum Kind { kNull, kBool, kNumber, kString, kArray, kObject } kind = kNull;
    double number = 0.0;
    std::string text;
    std::vector<std::unique_ptr<Value>> items;
    std::map<std::string, std::unique_ptr<Value>> members;
    const Value* Member(const char* name) const {
        if (kind != kObject) return nullptr;
        auto found = members.find(name);
        return found == members.end() ? nullptr : found->second.get();
    }
};

struct Parser {
    const char* p;
    const char* end;
    bool ok = true;
    void Skip() {
        while (p < end && std::isspace(static_cast<unsigned char>(*p))) ++p;
    }
    bool Literal(const char* word) {
        const size_t n = std::strlen(word);
        if (static_cast<size_t>(end - p) < n || std::strncmp(p, word, n) != 0) return false;
        p += n;
        return true;
    }
    std::string String() {
        std::string out;
        ++p;  // the opening quote
        while (p < end && *p != '"') {
            if (*p == '\\' && p + 1 < end) {
                ++p;
                const char c = *p++;
                if (c == 'n') out += '\n';
                else if (c == 't') out += '\t';
                else if (c == 'u') p += 4 <= end - p ? 4 : end - p;  // not used by capture.json's keys
                else out += c;
            } else {
                out += *p++;
            }
        }
        if (p < end) ++p;
        else ok = false;
        return out;
    }
    std::unique_ptr<Value> Parse(int depth) {
        auto v = std::make_unique<Value>();
        Skip();
        if (p >= end || depth > 64) {
            ok = false;
            return v;
        }
        if (*p == '{') {
            v->kind = Value::kObject;
            ++p;
            Skip();
            if (p < end && *p == '}') {
                ++p;
                return v;
            }
            while (ok) {
                Skip();
                if (p >= end || *p != '"') {
                    ok = false;
                    break;
                }
                std::string key = String();
                Skip();
                if (p >= end || *p != ':') {
                    ok = false;
                    break;
                }
                ++p;
                v->members[key] = Parse(depth + 1);
                Skip();
                if (p < end && *p == ',') {
                    ++p;
                    continue;
                }
                if (p < end && *p == '}') {
                    ++p;
                    break;
                }
                ok = false;
            }
        } else if (*p == '[') {
            v->kind = Value::kArray;
            ++p;
            Skip();
            if (p < end && *p == ']') {
                ++p;
                return v;
            }
            while (ok) {
                v->items.push_back(Parse(depth + 1));
                Skip();
                if (p < end && *p == ',') {
                    ++p;
                    continue;
                }
                if (p < end && *p == ']') {
                    ++p;
                    break;
                }
                ok = false;
            }
        } else if (*p == '"') {
            v->kind = Value::kString;
            v->text = String();
        } else if (Literal("true")) {
            v->kind = Value::kBool;
            v->number = 1.0;
        } else if (Literal("false")) {
            v->kind = Value::kBool;
        } else if (Literal("null")) {
        } else {
            char* stop = nullptr;
            v->kind = Value::kNumber;
            v->number = std::strtod(p, &stop);
            if (stop == p) ok = false;
            p = stop;
        }
        return v;
    }
};

bool Floats(const Value* v, float* out, int count) {
    if (v == nullptr || v->kind != Value::kArray || static_cast<int>(v->items.size()) != count) return false;
    for (int i = 0; i < count; ++i) {
        if (v->items[i]->kind != Value::kNumber) return false;
        out[i] = static_cast<float>(v->items[i]->number);
    }
    return true;
}

bool ReadCamera(const Value* camera, CameraState* out) {
    if (camera == nullptr) return false;
    const Value* ltm = camera->Member("frame_ltm");
    if (ltm == nullptr) return false;
    bool ok = Floats(ltm->Member("right"), out->right, 3) && Floats(ltm->Member("up"), out->up, 3) &&
              Floats(ltm->Member("at"), out->at, 3) && Floats(ltm->Member("pos"), out->pos, 3) &&
              Floats(camera->Member("viewWindow"), out->viewWindow, 2) && Floats(camera->Member("viewOffset"), out->viewOffset, 2);
    const Value* nearPlane = camera->Member("nearPlane");
    const Value* farPlane = camera->Member("farPlane");
    const Value* fogPlane = camera->Member("fogPlane");
    ok = ok && nearPlane != nullptr && farPlane != nullptr && fogPlane != nullptr;
    if (!ok) return false;
    out->nearPlane = static_cast<float>(nearPlane->number);
    out->farPlane = static_cast<float>(farPlane->number);
    out->fogPlane = static_cast<float>(fogPlane->number);
    return true;
}

bool g_read = false;
bool g_valid = false;
CameraState g_main{};
CameraState g_scene{};

void ReadEnvironment() {
    if (g_read) return;
    g_read = true;
    const char* text = std::getenv("DOTD_CAMERA_FROM");
    if (text == nullptr || *text == 0) return;
    const std::string spec = text;
    const size_t colon = spec.rfind(':');
    if (colon == std::string::npos || colon < 2) {
        DOTD_LOG("capturecam: DOTD_CAMERA_FROM=%s: expected <capture.json>:<moment>\n", text);
        return;
    }
    const std::string path = spec.substr(0, colon);
    const std::string moment = spec.substr(colon + 1);
    std::FILE* file = std::fopen(path.c_str(), "rb");
    if (file == nullptr) {
        DOTD_LOG("capturecam: cannot open %s\n", path.c_str());
        return;
    }
    std::string data;
    char buffer[65536];
    for (size_t got; (got = std::fread(buffer, 1, sizeof buffer, file)) > 0;) data.append(buffer, got);
    std::fclose(file);
    Parser parser{data.data(), data.data() + data.size()};
    std::unique_ptr<Value> root = parser.Parse(0);
    const Value* targets = parser.ok ? root->Member("targets") : nullptr;
    if (targets == nullptr || targets->kind != Value::kArray) {
        DOTD_LOG("capturecam: %s has no targets\n", path.c_str());
        return;
    }
    for (const auto& target : targets->items) {
        const Value* name = target->Member("name");
        if (name == nullptr || name->text != moment) continue;
        const Value* cameras = target->Member("cameras");
        const Value* read = cameras != nullptr ? cameras->Member("at_render") : nullptr;
        const char* which = "at_render";
        if (read == nullptr || read->Member("main") == nullptr) {
            read = cameras != nullptr ? cameras->Member("after_present") : nullptr;
            which = "after_present";
        }
        if (read == nullptr || !ReadCamera(read->Member("main"), &g_main)) break;
        if (!ReadCamera(read->Member("scene"), &g_scene)) g_scene = g_main;
        g_valid = true;
        DOTD_LOG("capturecam: %s %s (%s): main camera at (%.3f, %.3f, %.3f), view window %.4f x %.4f, near %.3f far %.3f\n",
                 path.c_str(), moment.c_str(), which, g_main.pos[0], g_main.pos[1], g_main.pos[2], g_main.viewWindow[0],
                 g_main.viewWindow[1], g_main.nearPlane, g_main.farPlane);
        return;
    }
    DOTD_LOG("capturecam: %s has no camera for the moment %s\n", path.c_str(), moment.c_str());
}

}  // namespace

bool Get(CameraState* main, CameraState* scene) {
    ReadEnvironment();
    if (!g_valid) return false;
    if (main != nullptr) *main = g_main;
    if (scene != nullptr) *scene = g_scene;
    return true;
}

}  // namespace dotd::platform::capturecam
